#include "CMakeDefines.h"
#include "RenderManager.h"

#include "defines.h"
#include "CDTimer.h"
#include "MScene.h"
#include "MRenderable.h"
#include <Core/Util/Logger.h>

#include <Engine/PixelSamplers/RegularSampler.h>
#include <Engine/Display/FileDisplay.h>
#include <Image/SimpleImage.h>
#include <Model/Materials/Dielectric.h>
#include <Model/Materials/ThinDielectric.h>
#include <Model/Materials/OrenNayar.h>
#include <Model/Materials/Transparent.h>
#include <Model/AmbientLights/AmbientOcclusionBackground.h>
#include <Model/AmbientLights/AmbientOcclusion.h>
#include <Model/Textures/TexCoordTexture.h>
#include <Model/Textures/Constant.h>
#include <Model/Primitives/Plane.h>
#include <Model/Primitives/Parallelogram.h>
#include <Model/Primitives/Cube.h>
#include <Model/Primitives/Disk.h>

#include <stdio.h>
#include <cassert>
#include <float.h>

#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>

#include <arpa/inet.h>

//#ifdef USE_RIVL
  //#include "RIVLManager.h"
//#endif
//#ifdef USE_EMBREE
  //#include "EmbreeManager.h"
//#endif
#include "MantaManager.h"

  RenderManager::RenderManager()
: current_renderable(NULL),
  auto_camera(false), num_threads(8), rendering(false), current_color(1,0.714,0.216,1), print_build_time(true), relaunch(false), client_running(false), current_bgcolor(1,1,1,1), render_once(false), usePerVertexColors(false),
  frame_lag(false), rank(-1)
  , use_gl_lights(true), lights_dirty(true), use_gl_material(false), dirty_renderParams(false), new_renderParamsString(""),dirty_sampleGenerator(true)
  , initialized(false)
  , _zNear(0.1), _zFar(100.0)
{
  gl_lights.resize(8);
  _mutexes.push_back(new Manta::Mutex("RenderManager"));
}


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in*)sa)->sin_addr);
  }

  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}



void* RenderManager::clientLoop(void* t)
{
  fflush(stdout);
  RenderManager* manager = dynamic_cast<RenderManager*>((RenderManager*)t);
  assert(manager);
  int sockfd, numbytes;
  char buf[1024];
  struct addrinfo hints, *servinfo, *p;
  int rv;
  char s[INET6_ADDRSTRLEN];
  sleep(1); //give some time for server to start

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  char* cport = getenv("GLURAY_PORT");
  string port;
  if (cport)
    port = string(cport);
  else
    port = "3490";

  printf("client listening on port %s\n",port.c_str());

  if ((rv = getaddrinfo("localhost", port.c_str(), &hints, &servinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    pthread_exit(0);
  }

  // loop through all the results and connect to the first we can
  for(p = servinfo; p != NULL; p = p->ai_next) {

    if ((sockfd = socket(p->ai_family, p->ai_socktype,
            p->ai_protocol)) == -1) {
      perror("client: socket");
      continue;
    }

    if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      perror("client: connect");
      continue;
    }

    break;
  }

  if (p == NULL) {
    fprintf(stderr, "client: failed to connect\n");
    pthread_exit(0);
  }

  inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
      s, sizeof s);
  printf("client: connecting to %s\n", s);

  freeaddrinfo(servinfo); // all done with this structure

  while (1)
  {
    if ((numbytes = recv(sockfd, buf, 1024-1, 0)) == -1) {
      cerr << "error recieving network buffer\n";
      perror("recv");
      exit(1);
    }

    buf[numbytes] = '\0';

    printf("client: received '%s'\n",buf);
    // manager->setRenderParametersString(string(buf), false);
    // manager->general_mutex.lock();
    manager->dirty_renderParams = true;
    manager->new_renderParamsString = string(buf);
    // manager->general_mutex.unlock();
  }
}

// Initialize thread to listen to gui client
void RenderManager::initClient()
{
#if RUN_CLIENT
  if (!client_running)
  {
    client_running = true;
    pthread_t thread;
    cout << "run client\n";
    int err = pthread_create(&thread, 0, clientLoop, this);
    if (err){
      printf("ERROR; return code from pthread_create() is %d\n", err);
      exit(-1);
    }
  }
#endif
}

void RenderManager::pushRenderParameters()
{
  render_parameters_stack.push(params);
}

void RenderManager::popRenderParameters()
{
  params = render_parameters_stack.top();
  render_parameters_stack.pop();
}

// Check new parameters and call relevant update functions
void RenderManager::setRenderParameters(GLuRayRenderParameters& rp, bool need_relaunch)
{
  // general_mutex.lock();

  GLuRayRenderParameters oldp = params;
  params = rp;

  if (params.num_threads != oldp.num_threads)
    setNumThreads(params.num_threads);

  if (params.num_ao_samples != oldp.num_ao_samples || params.ao_distance != oldp.ao_distance || params.ao_intensity != oldp.ao_intensity)
    updateRenderer();

  if (params.num_samples != oldp.num_samples)
    setNumSamples(0, 0, params.num_samples);

  if (params.shadows != oldp.shadows)
    useShadows(params.shadows);

  if (params.material != oldp.material)
    updateMaterial();

  if (initialized)
  {
    updateLights();
    updateBackground();
    updateCamera();
  }
  relaunch = relaunch || need_relaunch;
  // general_mutex.unlock();
}

void RenderManager::setRenderParametersString(string in, bool need_relaunch)
{
  cout << "setting parameters to : " << in << endl;
  GLuRayRenderParameters rp = params;
  stringstream s(in);
  string arg, mode;
  s >> mode;
  rp.shadows = false;
  rp.env_map = "";
  while (s >> arg)
  {
    if (arg == "-fov")
    {
      s >> rp.camera_vfov;
      rp.camera_hfov = rp.camera_vfov;
    }
    else if (arg == "-spp")
      s >> rp.num_samples;
    else if (arg == "-threads")
      s >> rp.num_threads;
    else if (arg == "-ao")
      s >> rp.num_ao_samples >> rp.ao_distance >> rp.ao_intensity;
    else if (arg == "-rotate")
    {
      static float DEGTOR = M_PI/180.0f;
      s >> rp.rotate_speed >> rp.rotate_offset;
      rp.rotate_speed *= DEGTOR;
      //rp.rotate_offset *= DEGTOR;
    }
    else if (arg == "-env")
      s >> rp.env_map;
    else if (arg == "-shadows")
      rp.shadows = true;
    else if (arg == "-skyDome")
      s >> rp.num_skyDome_lights >> rp.skyDome_size >> rp.skyDome_intensity;
    else if (arg == "-plane")
    {
      rp.add_plane = true;
      s >> rp.plane_normal >> rp.plane_center;
    }
    else if (arg == "-reflectivity")
      s >> rp.reflectivity;
    else if (arg == "-thinLens")
    {
      rp.camera = "thinLens";
      s >> rp.focalDistance >> rp.aperture;
    }
    else if (arg == "-pinhole")
      rp.camera = "pinhole";
    else if (arg == "-lambertian")
      rp.material = "lambertian";
    else if (arg == "-phong")
    {
      rp.material = "phong";
    }
    else if (arg == "-no_gl_lights")
    {
      rp.use_gl_lights = false;
    }
    else if (arg == "-glass")
    {
      rp.material = "glass";
      s >> rp.ri >> rp.ri2;
    }
    else if (arg == "-thinDielectric")
    {
      rp.material = "thinDielectric";
      s >> rp.eta >> rp.thickness;
    }
    else if (arg == "-metal")
      rp.material = "metal";
    else if (arg == "-transparent")
    {
      rp.material = "transparent";
    }
    else if (arg == "-orenNayar")
    {
      rp.material = "orenNayar";
      s >> rp.roughness;
    }
    else if (arg == "-export_obj")
    {
      s >> rp.export_obj;
    }
    else if (arg == "-write_to_file")
    {
      s >> rp.write_to_file;
    }
    else
    {
      cerr << "unrecognized config option: " << arg << endl;
      //assert(0);
    }
  }
  mode = "-apply";  //hardcode for now... renderonce not working as it should
  if (mode == "-apply")
  {
    //todo: make thread safe
    setRenderParameters(rp, need_relaunch);
    //	    manager->render();
  }
  else if (mode == "-renderOnce"){
    pushRenderParameters();
    setRenderParameters(rp, need_relaunch);
    render_once = true;
    //render
    //todo: make thread safe
    //	render();

    //	popGLuRayRenderParameters();
  }
  else
  {
    cerr << "unknown render mode\n";
  }
}

void RenderManager::addInstance(Renderable* ren)
{
  // if (!ren->isBuilt())
  // {
  //   std::cerr << "addInstance: renderable not build by rendermanager\n";
  //   return;
  // }
  // next_scene->instances.push_back(GRInstance(ren, current_transform));
}

extern RenderManager* createEmbreeManager();
extern RenderManager* createOSPRayManager();
extern RenderManager* createRIVLManager();
extern RenderManager* createOptiXManager();

RenderManager* createRenderManager()
{
#ifdef USE_EMBREE
 return createEmbreeManager();
  //return EmbreeManager::singleton();
#endif
#ifdef USE_RIVL
  return createRIVLManager();
  //return RIVLManager::singleton();
#endif
#ifdef USE_OSPRAY
  return createOSPRayManager();
#endif
#ifdef USE_OPTIX
  return createOptiXManager();
#endif
  return MantaManager::singleton();
}


//void RenderManager::lock(const int mutex)
//{
 //_mutexes[mutex]->lock();
//}

//void RenderManager::unlock(const int mutex)
//{
  //_mutexes[mutex]->unlock();
//}

