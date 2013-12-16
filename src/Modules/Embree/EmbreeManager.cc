
#include <UseMPI.h>
#ifdef USE_MPI
#include <Engine/Display/NullDisplay.h>
#include <Engine/LoadBalancers/MPI_LoadBalancer.h>
#include <Engine/ImageTraversers/MPI_ImageTraverser.h>
#include <mpi.h>
#endif

#include "defines.h"
#include "EmbreeManager.h"
//#include <X11/Xlib.h>
//#include <X11/Xutil.h>

//#include "../gl_functions.h"
#include "CDTimer.h"
#include "EScene.h"
#include "ERenderable.h"
#include "common.h"
#include <Modules/Manta/AccelWork.h>
#include <OBJScene.h>

#include <Core/Util/Logger.h>

#include <Model/Primitives/KenslerShirleyTriangle.h>
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
#include <stack>
#include <algorithm>

#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>



#include <arpa/inet.h>

#include <GL/gl.h>
//#include <GL/glx.h>
//namespace X11
//{
//#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <X11/Xos.h>
//#include <X11/Xatom.h>
//#include <X11/keysym.h>
//}

//#include "../gl_function_table.h"

using namespace embree;

//ostream& operator<<(ostream& out, GLMaterial& m)
//{
  //out << "GLMaterial:\n";
  //out << "ambient: " << m.ambient[0] << " " << m.ambient[1] << " " << m.ambient[2] << " ";
  //out << "diffuse: " << m.diffuse[0] << " " << m.diffuse[1] << " " << m.diffuse[2] << " ";
  //out << "specular: " << m.specular[0] << " " << m.specular[1] << " " << m.specular[2] << " ";
  //out << "emissive: " << m.emissive[0] << " " << m.emissive[1] << " " << m.emissive[2] << " ";
  //out << "shiny: " << m.shiny;
  //return out;
//}
//ostream& operator<<(ostream& out, GLLight& m)
//{
  //out << "GLLight:\n";
  //out << "ambient: " << m.ambient[0] << " " << m.ambient[1] << " " << m.ambient[2] << " ";
  //out << "diffuse: " << m.diffuse[0] << " " << m.diffuse[1] << " " << m.diffuse[2] << " ";
  //out << "specular: " << m.specular[0] << " " << m.specular[1] << " " << m.specular[2] << " ";
  //out << "pos: " << m.pos[0] << " " << m.pos[1] << " " << m.pos[2] << " ";
  //out << "is pointlight: " << m.w << " is enabled: " << m.enabled;

//}

// generate N points on [0,1]^2
//void getLightSamples( float *u_, float *v_, int n)
//{
  /*
   * taken from Manta, from hammersley from 97 jgt article
   */
  //float p, u, v;
  //int k, kk, pos;

  //for (k=0, pos=0 ; k<n ; k++)
  //{
    //u = 0;
    //for (p=0.5, kk=k ; kk ; p*=0.5, kk>>=1)
      //if (kk & 1)
        //u += p;

    //v = (k + 0.5) / n;

    //u_[k] = u;
    //v_[k] = v;
  //}
//}

EmbreeManager* EmbreeManager::_singleton = NULL;

EmbreeManager* EmbreeManager::singleton()
{
  if (!_singleton)
    _singleton = new EmbreeManager();
  return _singleton;
}


  EmbreeManager::EmbreeManager()
:RenderManager(), current_scene(NULL), next_scene(NULL),
  _nid_counter(0), _depth(false), _width(512), _height(512), _frameNumber(0), _realFrameNumber(0)
{
  rendered = false;
  _camera = NULL;
  g_current_material = NULL;
  _renderer = NULL;
  _tonemapper = NULL;
  _frameBuffer = NULL;
  _backplate = NULL;
  _render_scene = NULL;

  _scene = "default";
  //_scene = "twolevel";
  //_accel = "default";
  _accel = "bvh4";
  _builder = "default";
  _traverser = "default";
  _resetAccumulation = true;
  _format = "RGB8";

  _gVoid = new EGeometryGeneratorVoid();
  _gTriangle = new EGeometryGeneratorTriangles();
  _gTriangleStrip = new EGeometryGeneratorTriangleStrip();
  _gQuads = new EGeometryGeneratorQuads();
  _gQuadStrip = new EGeometryGeneratorQuadStrip();
  _gLines = new EGeometryGeneratorLines();
  _gLineStrip= new EGeometryGeneratorLineStrip();

  _objScene = new OBJScene();

  _xDisplay = NULL;
  _xWin = new Window;
}

EmbreeManager::~EmbreeManager()
{
    _renderer = null;
    _tonemapper = null;
    _frameBuffer = null;
    _backplate = null;
    _render_scene = null;
    rtClearTextureCache();
    rtClearImageCache();
    delete g_device;
    g_device = NULL;
}

void EmbreeManager::updateLights()
{
  embreeMutex.lock();
  _lights.resize(0);
  AffineSpace3f transform(one);
  if (params.env_map != "")
  {
    embree::Color LColor(.8, .8, .8);
    Handle<Device::RTLight> hdrLight = g_device->rtNewLight("hdrilight");
    //g_device->rtSetTransform(light, "local2world", copyToArray(space));
    g_device->rtSetFloat3(hdrLight, "L", LColor.r, LColor.g, LColor.b);
    //g_device->rtSetImage(hdrLight, "image", rtLoadImage("/home1/01336/carson/git/embree/models/lines.ppm"));
    //g_device->rtSetImage(hdrLight, "image", rtLoadImage("/work/01336/carson/data/lightProbes/rnl_probe.pfm"));
    std::string lightFile = params.env_map;
    printf("loading hdrLight: %s\n", lightFile.c_str());
    g_device->rtSetImage(hdrLight, "image", rtLoadImage(lightFile));
    g_device->rtCommit(hdrLight);
    _lights.push_back(g_device->rtNewLightPrimitive(hdrLight, NULL, copyToArray(transform)));
  }

  lights_dirty = false;
  double cintensity = params.skyDome_intensity;
  if (cintensity < 0.0)
    cintensity = 0.0;
  double compI = 1.0 - cintensity - params.ao_intensity;
  if (compI < 0.0)
    compI = 0.0;
  if (params.num_skyDome_lights > 0)
  {
    //float minx = -200; float scalex = 30*width_scale;
    //float minz = 400; float scalez = 30*width_scale;
    //float y = 400;
    //Manta::Color c1 = Manta::Color(RGB(0.85, 0.9, 0.6));
    //Manta::Color c2 = Manta::Color(RGB(0.3,0.3,1.0));
    //Manta::Color c4 = Manta::Color(RGB(1.,1.0,1.0));

    //float *u = new float[num_lights];
    //float *v = new float[num_lights];
    //getLightSamples( u, v, num_lights );
    //srand(1);
    //for (int i = 0; i < num_lights; i++) {
    //Manta::Color c3 = Manta::Color(RGB(drand48(), drand48(), drand48()));
    //float rand = drand48(), rand2 = drand48(), rand3 = drand48();
    //Manta::Color col = (c3*rand*.2 + ((c1*rand2 + c2*(1.0-rand2))*rand3*.5 + c4*(1.0-rand3)*.5)*.8) * (intensity/num_lights);
    //lights->add(new PointLight(Vector(minx + u[i] * scalex, y, minz + v[i]*scalez), col));
    //}
    //delete [] u;
    //delete [] v;
  }
  //if ((cintensity < 0.9 || params.num_skyDome_lights <= 0) && !use_gl_lights)
  {
    //lights->add(new PointLight(Vector(-8,0,10), Color(RGBColor(.5,.5,.3))*.1*compI));
    //lights->add(new PointLight(Vector(8,5,6), Color(RGBColor(.6,.67,.9))*.4*compI));
  }

  Manta::Color ambient(RGB(0,0,0));
  bool addedLight = false;
  //TODO: modify light position by modelview!
  if (params.use_gl_lights && use_gl_lights)
  {
    for(int i = 0; i < 8; i++)
    {
      GLLight& l = gl_lights[i];
      if (l.enabled)
      {
        addedLight = true;
        if (l.w == 0)
        {
          cout << "adding gl directional light " << i << ":\n" << l << "\n";
          //lights->add(new DirectionalLight(l.pos, l.diffuse));
          //AffineSpace3f space(LinearSpace3f(1,0,0,0,1,0,0,0,1), Vector3f(0,0,0));
          /*
           *directional light
           */
          //AffineSpace3f as(LinearSpace3f(1,0,0.5,
          //0,1,0-.5,
          //0,0,-.3), Vector3f(0,0,0));
          Handle<Device::RTLight> directionalLight = g_device->rtNewLight("directionallight");
          g_device->rtSetFloat3(directionalLight, "D", l.pos[0], l.pos[1], l.pos[2]);
          g_device->rtSetFloat3(directionalLight, "E", l.diffuse[0], l.diffuse[1], l.diffuse[2]);
          g_device->rtCommit(directionalLight);
          /*//return;*/
          _lights.push_back(g_device->rtNewLightPrimitive(directionalLight, NULL, copyToArray(transform)));
          /*
           *end directional light
           */
    /*AffineSpace3f space = load<AffineSpace3f>(xml->child("AffineSpace"));*/
      /*AffineSpace3f space(LinearSpace3f(1,0,0,0,0,1,0,0,0), Vector3f(-1,0,0));*/

    /*Handle<Device::RTLight> light = g_device->rtNewLight("directionallight");*/
    /*[>g_device->rtSetFloat3(light, "D", space.l.vz.x, space.l.vz.y, space.l.vz.z);<]*/
    /*[>g_device->rtSetFloat3(light, "E", 1, 0, 0);<]*/
          /*g_device->rtSetFloat3(light, "D", 1000,-500,-300);*/
          /*g_device->rtSetFloat3(light, "E", 1.0, 0.8, 0.6);*/
    /*g_device->rtCommit(light);*/
    /*_lights.push_back(g_device->rtNewLightPrimitive(light, NULL, copyToArray(transform)));*/



        }
        else
        {
          cout << "adding gl point light " << i << ":\n" << l << "\n";
          //lights->add(new PointLight(l.pos, l.diffuse));
        }
        if (use_gl_material)
        {
          ambient += l.ambient*0.0f; //TODO: HACK!  ambient should be mix of material properties and ambt... this does this but the material properties are global and old
        }
        else
          ambient += l.ambient*0.5; //TODO: HACK!  ambient should be mix of material properties and amb
      }
    }
    if (!addedLight) //Manta crashes with no lights...
    {
      //lights->add(new PointLight(Vector(10,10,-1), Color(RGBColor(1,1,1))*0.3));
    }
  }
  else
  {
    //lights->add(new PointLight(Vector(8,5,6), Color(RGBColor(.6,.67,.9))*.5*compI));
  }
  if (!use_gl_lights)
    ambient = Manta::Color(RGB(.2,.2,.2));
  if (params.num_ao_samples > 0)
  {
    //  current_material = new AmbientOcclusionCombiner(current_material, 100.0,params.num_ao_samples);
    //lights->setAmbientLight(new AmbientOcclusionBackground(ambient*params.ao_intensity,params.ao_distance,params.num_ao_samples, false, background));
    ambient = Manta::Color(RGB(1,1,1));  //HACK!
    //lights->setAmbientLight(new AmbientOcclusion(ambient*params.ao_intensity,params.ao_distance,params.num_ao_samples, false));
  }
  else {
    //lights->setAmbientLight(new ConstantAmbient(ambient));
  }
  //TODO: tkae out, hardcoded from SC video
  //
          Handle<Device::RTLight> directionalLight = g_device->rtNewLight("directionallight");
          g_device->rtSetFloat3(directionalLight, "D", -100,10,-30);
          /*g_device->rtSetFloat3(directionalLight, "E", 3.8, .7, .5);*/
          g_device->rtSetFloat3(directionalLight, "E", 0.8, .7, .5);
          g_device->rtCommit(directionalLight);
          _lights.push_back(g_device->rtNewLightPrimitive(directionalLight, NULL, copyToArray(transform)));

          /*Handle<Device::RTLight> directionalLight2 = g_device->rtNewLight("directionallight");*/
          /*g_device->rtSetFloat3(directionalLight2, "D", -80,20,-40);*/
          /*g_device->rtSetFloat3(directionalLight2, "E", 0.2, 0.3, 0.5);*/
          /*g_device->rtCommit(directionalLight2);*/
          /*_lights.push_back(g_device->rtNewLightPrimitive(directionalLight2, NULL, copyToArray(transform)));*/
  embreeMutex.unlock();
  //cerr << "setuplights done\n";
}

Renderable* EmbreeManager::createRenderable(GeometryGenerator* gen)
{
  EGeometryGenerator* mg = dynamic_cast<EGeometryGenerator*>(gen);
  assert(mg);
  return new ERenderable(mg);
}

void  EmbreeManager::updateMaterial()
{
  if (!initialized)
    return;
  embreeMutex.lock();

  //TODO: transparency taken from glcolor always for now...
  GLMaterial m = gl_material;
  //TODO: DEBUG: hardcoding mat for debugging
  //m.diffuse = Color(RGB(1.0, 0.713726, .21569));
  //m.diffuse = Color(RGB(0.8, 0.8, 0.8));
  m.specular = Manta::Color(RGB(.1, .1, .1));
  m.ambient = Manta::Color(RGB(0, 0, 0));
  m.shiny = 100;

  if (!use_gl_material)
  {
    m.diffuse = current_color.color;
    m.specular = Manta::Color(RGB(0,0,0));
    m.ambient = Manta::Color(RGB(1.0,1.0,1.0));
    m.shiny = 10;
  }
  else
  {
    //cout << "using gl material: " << m << endl;
    //params.material = "lambertian";
    //if (m.specular[0] > 0.001 || m.specular[1] > 0.001 || m.specular[2] > 0.001)
    if (params.material == "phong")
    {
      if (current_color.a < 0.99)
        params.material = "transparent";
    }
    //printf("using glmaterial with ambient: %f\n", m.ambient);
  }
  //float val = float(rand())/float(RAND_MAX);  //hack to get semittransparency... assume progressive rendering..
  if (0)//params.material == "transparent" || params.material == "glass")// && val > current_color.a)
  {

    g_current_material = g_device->rtNewMaterial("obj");
    float a = current_color.a;
    g_device->rtSetFloat1(g_current_material, "d", a);
    g_device->rtSetFloat3(g_current_material, "Kd",m.diffuse[0],m.diffuse[1],m.diffuse[2]);
    g_device->rtSetFloat1(g_current_material, "Ns",10);
    g_device->rtCommit(g_current_material);

    //g_current_material = g_device->rtNewMaterial("Dielectric");
    //float a = current_color.a;
    //g_device->rtSetFloat3(g_current_material, "transmission", m.diffuse[0], m.diffuse[1], m.diffuse[2]);
    //g_device->rtSetFloat1(g_current_material, "etaOutside",params.ri);
    //g_device->rtSetFloat1(g_current_material, "etaInside",params.ri2);
    //g_device->rtCommit(g_current_material);
  }
  else
  {
    //g_current_material = g_device->rtNewMaterial("Metal");
    //g_device->rtSetFloat1(g_current_material, "eta", params.eta);
    //g_device->rtSetFloat1(g_current_material, "roughness", .005);
    //g_device->rtSetFloat3(g_current_material, "k",m.diffuse[0],m.diffuse[1],m.diffuse[2]);
    //g_device->rtCommit(g_current_material);

    g_current_material = g_device->rtNewMaterial("MetallicPaint");
    g_device->rtSetFloat1(g_current_material, "eta", params.eta);
    g_device->rtSetFloat1(g_current_material, "roughness", .005);
    /*g_device->rtSetFloat1(g_current_material, "glitterSpread", 0.1);*/
    /*g_device->rtSetFloat3(g_current_material, "glitterColor",0.5,.44,.42);*/
    g_device->rtSetFloat3(g_current_material, "shadeColor",m.diffuse[0],m.diffuse[1],m.diffuse[2]);
    g_device->rtCommit(g_current_material);

    //TODO: This is a SC HACK!
    if (m.diffuse[0] == 1.0 && m.diffuse[1] == 1.0 && m.diffuse[2] == 1.0)
    {
    g_current_material = g_device->rtNewMaterial("Matte");
    /*g_device->rtSetFloat1(g_current_material, "glitterSpread", 0.1);*/
    /*g_device->rtSetFloat3(g_current_material, "glitterColor",0.5,.44,.42);*/
    g_device->rtSetFloat3(g_current_material, "reflectance",m.diffuse[0],m.diffuse[1],m.diffuse[2]);
    g_device->rtSetFloat3(g_current_material, "reflectance",m.diffuse[0],m.diffuse[0],m.diffuse[2]);
    g_device->rtCommit(g_current_material);
    }
  }

  bool textured = glIsEnabled(GL_TEXTURE_2D);
  /*textured = false;*/
  if (textured)
  {
    printf("using texture\n");
    int texId;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &texId);
    if (texId != 0)
    {
      printf("loading texture id %d\n", texId);
      Handle<Device::RTTexture>* texHandle = _textures[texId];
      if (texHandle)
      {
        g_current_material = g_device->rtNewMaterial("MatteTextured");
        g_device->rtSetTexture(g_current_material, "Kd", *texHandle);
        g_device->rtSetFloat2(g_current_material, "s0", 0.8f, 0.8f);
        g_device->rtSetFloat2(g_current_material, "ds", 3.0f, 3.0f);
        /*g_device->rtSetFloat3(g_current_material, "shadeColor",m.diffuse[0],m.diffuse[1],m.diffuse[2]);*/
        g_device->rtCommit(g_current_material);
      }
    }
  }


#if 0
  //usePerVertexColors = false;  //TODO: DEBUG
  if (usePerVertexColors)
  {
    Manta::Texture<Manta::Color> *texture = new Manta::TexCoordTexture();
    //    texture = new Constant<Manta::Color>(m.diffuse);
    if (params.material == "phong")
    {
      Texture<Color> *specular =
        new Constant<Manta::Color>
        (m.specular);
      Texture<float> *refl = new Constant<float>(params.reflectivity);

      current_material= new Phong(texture,
          specular, m.shiny,refl);
    }
    else if (params.material == "lambertian")
    {

      //current_material = new Lambertian(Color(RGBColor(0,1,0)));
      current_material = new Lambertian(texture);
    }
    else if (params.material == "metal")
      current_material = new MetalMaterial(texture, m.shiny);
    else if (params.material == "glass")
    {
      //current_material = new Dielectric(params.ri, params.ri2, texture);
    }
    else if (params.material == "thinDielectric")
    {
      //current_material = new ThinDielectric(params.eta, texture, params.thickness, 1);
    }
    else if (params.material == "orenNayar")
      current_material = new OrenNayar(texture);
    else if (params.material == "transparent")
    {
      if (current_color.a < 0.95)
        current_material = new Transparent(texture, current_color.a);
      else
      {

        Texture<Color> *specular =
          new Constant<Manta::Color>
          (m.specular);
        Texture<float> *refl = new Constant<float>(params.reflectivity);

        current_material= new Phong(texture,
            specular, m.shiny,refl);
      }
    }
    else
      assert(0);
  }
  else
  {
    if (params.material == "phong")
      current_material= new Phong(m.diffuse,
          m.specular, m.shiny, (ColorComponent)params.reflectivity);
    else if (params.material == "lambertian")
      current_material = new Lambertian(m.diffuse);
    else if (params.material == "metal")
      current_material = new MetalMaterial(m.diffuse, 10);
    else if (params.material == "glass")
    {
      current_material = new Dielectric(params.ri, params.ri2, current_color.color);
    }
    else if (params.material == "thinDielectric")
      current_material = new ThinDielectric(params.eta, m.diffuse, params.thickness, 1);
    else if (params.material == "orenNayar")
      current_material = new OrenNayar(m.diffuse, 1);
    else if (params.material == "transparent")
      current_material = new Transparent(m.diffuse, current_color.a);
    else
      assert(0);
  }
#endif
  embreeMutex.unlock();
}

void EmbreeManager::useShadows(bool st)
{
}

void EmbreeManager::setSize(int w, int h)
{
  if (initialized && (w != params.width || h != params.height))
  {
    embreeMutex.lock();
    params.width = w;
    params.height = h;
    _width = w; _height = h;
    _frameBuffer = g_device->rtNewFrameBuffer(_format.c_str(),w,h,2/*num buffers*/);
    _resetAccumulation = true;
    embreeMutex.unlock();
    updateCamera();
  }
}

struct networkSetupInfo
{
  std::string hostname;
  unsigned int port;
};

void EmbreeManager::init()
{
  if (initialized)
    return;

  try {
    if (g_device == NULL)
    {
      printf("creating default device\n");
      string deviceStr = "default";
#if 0 //later for data parallel apps
#if USE_MPI

      int numProcs = ;
      if (numProcs > 1)
      {
        MPI_Status stat;
        if (_rank == 0)
        {

          deviceStr = "network ";
          for(int i = 1; i < numProcs; i++)
          {
            networkSetupInfo ni;
            MPI_Recv(&ni, sizeof(NetworkSetupInfo), MPI_BYTE, i, MPI_ANY, MPI_COMM_WORLD, stat);
            MPI_Barrier(MPI_COMM_WORLD);
            string host = ni.hostname;
            string port = ni.port;
            deviceStr += " " + host + ":" + port;
          }
        }
        else
        {

          networkSetupInfo ni;
          ni.hostname = string(cmd("hostname"));
          ni.port = 8483+_rank; //TODO: test for open ports
          network::socket_t socket;
          try
          {
            socket = network::bind(port);
          }
          catch
          {

          }
          MPI_Send(&ni, sizeof(NetworkSetupInfo), MPI_BYTE, 0, MPI_ANY, MPI_COMM_WORLD, stat);
          MPI_Barrier(MPI_COMM_WORLD);
          printf("rank %d listening on port %d\n", _rank, port);
          network::socket_t client = network::listen(socket);
          new NetworkServer(client, Device::rtCreateDevice(g_device_type.c_str(), g_threads,g_encoding,g_verbose);
              }


              }

#endif USE_MPI

              //
              //  load in host file
              //    - assumes format of " hostname:port "
              //
              string hostsFile = GetVarString("GLURAY_HOST_LIST");
              if (hostsFile != "")
              {
              ifstream in(hostsFile.c_str());
              if (in)
              {
              deviceStr = "network ";
              string fileString;
              in.seekg(0, std::ios::end);
              fileString.reserve(in.tellg());
              in.seekg(0, std::ios::beg);
              fileString.assign((std::istreambuf_iterator<char>(in)),
                  std::istreambuf_iterator<char>());
              for(size_t i = 0; i < fileString.size(); i++)
              {
                if (!strcmp(&fileString[i],"\n"))
                  fileString.erase(i--,1);
              }
              deviceStr += fileString;
              }
          printf("connecting to servers: %s\n", deviceStr.c_str());
              }
#endif
          g_device = Device::rtCreateDevice(deviceStr.c_str(),params.num_threads/*numthreads*/);
    }


    _renderer = g_device->rtNewRenderer("pathtracer");
    g_device->rtSetInt1(_renderer, "sampler.spp", params.num_samples);
    g_device->rtCommit(_renderer);

    _tonemapper = g_device->rtNewToneMapper("default");
    g_device->rtSetFloat1(_tonemapper, "gamma", 1.0);
    g_device->rtSetBool1(_tonemapper, "vignetting", 1.0);
    g_device->rtCommit(_tonemapper);

    _frameBuffer = g_device->rtNewFrameBuffer(_format.c_str(), _width, _height, 2/*numBuffers*/);
    _backplate = NULL;
  }
  catch (const std::exception& e) {
    std::cout << "Error: EmbreeManager: " << e.what() << std::endl;
    return;
  }
  catch (...) {
    exit(__LINE__);
    return;
  }

  rendering = true;
  //embree::CDTest();

  _rank = -1;
#ifdef USE_MPI
  _rank = MPI::COMM_WORLD.Get_rank();
  MPI_Comm_size(MPI_COMM_WORLD, &_numProcs);
  GetVar<int>("GLURAY_CACHEFRAC", cacheFraction);
  GetVar<bool>("GLURAY_DEPTH", _depth);
#endif
  cerr << "initializing GLuRay\n";
  //lights = new LightSet();
  gl_lights[0].diffuse = Manta::Color(RGB(1,1,1));
  gl_lights[0].specular = Manta::Color(RGB(1,1,1));
  gl_lights[0].pos = Vector(0,0,1);
  gl_lights[0].w = 0;
  updateLights();
  setColor(current_color.color[0], current_color.color[2], current_color.color[3], current_color.a);
  updateMaterial();
  //  current_material= new Phong(Color(RGBColor(1,1,1)),
  //			      Color(RGBColor(.6,.6,.6)), 32, (ColorComponent)params.reflectivity);
  //current_material = new AmbientOcclusion(current_material, 100.0,20);
  current_normal = Vector(0,1,0);
  current_transform.initWithIdentity();
  current_bgcolor = params.bgcolor;
  //  background = new ConstantBackground(current_bgcolor.color);
  //camera = new PinholeCamera(params.camera_eye, params.camera_dir, params.camera_up, params.camera_hfov, params.camera_vfov);
  updateBackground();
  updateCamera();
  if (!current_scene)
    current_scene = new EScene();
  if (!next_scene)
    next_scene = new EScene();
  //DEBUG: insert dummy object to avoid DynBVH from crashing!
  //   if (scene->world->getVectorOfObjects().empty())
  //current_scene->world->add(new Sphere(new Lambertian(Color(RGBColor(current_bgcolor.color[0],current_bgcolor.color[1],current_bgcolor.color[2]))), Vector(0,0,0), Manta::Real(0e-6)));

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

  //if (params.accumulate)
  //{
  //pthread_t thread;
  //int err = pthread_create(&thread, 0, renderloop, this);
  //if (err){
  //printf("error creating embree render loop. return code from pthread_create() is %d\n", err);
  //exit(-1);
  //}
  //}
  cout << "initialization done\n";
  initialized = true;
}

//TODO: updating pixelsampler mid flight crashes manta
void EmbreeManager::setNumSamples(int,int,int samples)
{
  cout << "setting samples\n";
  params.num_samples = samples;
  stringstream s;
  if (params.num_samples > 1)
    s << "regularsample (-numberOfSamples " << params.num_samples << ")";
  else
    s << "singlesample";
  //if(!factory->selectPixelSampler(s.str()))
  //{}
  vector<string> args;
  args.push_back("-numberOfSamples");
  args.push_back("8");
  //PixelSampler* ps = new RegularSampler(args);
  //rtrt->setPixelSampler(ps);
  //  assert(0);
  cout << "set num samples to: " << samples << endl;
}

void EmbreeManager::setNumThreads(int t)
{
}



size_t EmbreeManager::generateNID()
{
  return ++_nid_counter;
}

Renderable* EmbreeManager::getRenderable(size_t nid)
{
  return _map_renderables[nid];
}

void* EmbreeManager::renderLoop(void* t)
{
  EmbreeManager* em = dynamic_cast<EmbreeManager*>((EmbreeManager*)t);
  assert(em);
  while (true)
  {
    //em->render();
    if (em->rendered)
    {
      //glDisable(GL_DEPTH_TEST);
      em->internalRender();
      em->displayFrame();
    }
    //em->displayFrame();
    usleep(2000);
  }
  //bool accum = (!em->_resetAccumulation && em->_accumulate);
  //g_device->rtRenderFrame(em->_renderer,em->_camera,em->_render_scene,em->_tonemapper,em->_frameBuffer,accum);
  //em->displayFrame();
}

void EmbreeManager::internalRender()
{
  if (!initialized)
    return;
  //if (!rendered)
  //return;
  embreeMutex.lock();
  bool accum = (!_resetAccumulation && params.accumulate);
  _resetAccumulation = false;
  //printf("render frame\n");
  g_device->rtRenderFrame(_renderer,_camera,_render_scene,_tonemapper,_frameBuffer,accum);
  embreeMutex.unlock();
}


void EmbreeManager::render()
{
  if (!initialized)
    return;

  printf("attempted render\n");
  if (next_scene->instances.size() == 0)
    return;
  printf("rendering\n");
  //if (rendered && params.accumulate)
  //displayFrame();
  rendered = true;
  std::vector<Handle<Device::RTPrimitive> > prims;
  AffineSpace3f transform(one);

  if (lights_dirty)
    updateLights();
  for(std::vector<embree::Handle<embree::Device::RTPrimitive> >::iterator itr = _lights.begin(); itr != _lights.end(); itr++)
    prims.push_back(*itr);

  /*if (_frameNumber+1 == params.export_obj)*/
    /*exportOBJ(next_scene);*/

  //TODO: HACK for SC Vid
  if (params.write_to_file != "")
  {
    /*static int _frameNumber1 = 0;*/
    //TODO: SC VIDEO HACK!
    //!!!!!!!!!!!!!!!!!!!!!
    if (_frameNumber > 2)
    {
      //TODO: SC VIDEO HACK!
      static int numberOfFrames = 0;
      static bool once = false;
      if (!once)
      {
        once = true;
        GetVar<int>("GR_FrameNumber", _realFrameNumber);
        _realFrameNumber--;
        GetVar<int>("GR_NumberOfFrames", numberOfFrames);
        /*_frameNumber = max(_realFrameNumber,3);*/
      }
      printf("setting values framenumber: %d numframes: %d\n", _realFrameNumber, numberOfFrames);
      float aperture = 0.0f;
      float focalDistance = 0.0f;
      float interp = 0;
      if (numberOfFrames > 0)
        interp = float(std::max(_realFrameNumber,0))/float(numberOfFrames);
      params.focalDistance = 125 + 200*interp;
      params.aperture = 1.0*(1.0-interp) + 0.1;
      updateCamera();
    }
    static int realSPP = params.num_samples;
    params.num_samples = 1;
    if(_frameNumber > 3)
       params.num_samples = realSPP;
  }
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  embreeMutex.lock();
  //printf("adding %d instances to scene\n", next_scene->instances.size());
  for(vector<GRInstance>::iterator itr = next_scene->instances.begin(); itr != next_scene->instances.end(); itr++)
  {
    Manta::AffineTransform mt = itr->transform;
    Renderable* ren = itr->renderable;
    ERenderable* er = dynamic_cast<ERenderable*>(ren);
    if (er->isBuilt())
    {
      AffineSpace3f et(LinearSpace3f(mt(0,0), mt(0,1), mt(0,2), mt(1,0), mt(1,1), mt(1,2), mt(2,0),mt(2,1),mt(2,2)), Vector3f(mt(0,3),mt(1,3),mt(2,3)));
      //AffineSpace3f et(LinearSpace3f(mt(0,0), mt(1,0), mt(2,0), mt(0,1), mt(1,1), mt(2,1), mt(0,2),mt(1,2),mt(2,2)), Vector3f(mt(3,0),mt(3,1),mt(3,2)));
      prims.push_back(g_device->rtNewShapePrimitive(er->_data->d_mesh, er->_data->d_material, copyToArray(et)));
    }
  }
  next_scene->instances.resize(0);
  embreeMutex.unlock();

  Handle<Device::RTScene> scene = g_device->rtNewScene(_scene.c_str());
  g_device->rtSetString(scene,"accel",_accel.c_str());
  g_device->rtSetString(scene,"builder",_builder.c_str());
  g_device->rtSetString(scene,"traverser",_traverser.c_str());
  //printf("creating scene with %d prims\n", prims.size());
  for (size_t i=0; i<prims.size(); i++)
    g_device->rtSetPrimitive(scene,i,prims[i]);
  g_device->rtCommit(scene);
  _render_scene = scene;


  //glDrawPixels(fb->size.x, fb->size.y, GL_RGBA, GL_UNSIGNED_BYTE, fb->h_mem);

  static CDTimer timer;
  timer.start();

  if (dirty_renderParams)
  {
    printf("\n\nUPDATING RENDER PARAMS\n\n");
    GLuRayRenderParameters p = params;
    setRenderParametersString(new_renderParamsString, false);
    GLuRayRenderParameters p2 = params;
    cout << "\n\nCOMPARISON: " << p.num_samples << " " << p2.num_samples << endl << endl;
    //if(p.num_samples != p2.num_samples || p.shadows != p2.shadows)
    //{
    //cout << "\n\nNEEDS RELAUNCH\n\n";
    ////relaunch = true;
    //}
    dirty_renderParams = false;
  }

  _resetAccumulation = true;
  embreeMutex.unlock();
  if (!params.accumulate)
  {
    internalRender();
    displayFrame();
    prims.clear();
    g_device->rtClear(scene);
  }
  static bool once = false;
  if (!once)
  {
    once = true;
    if (params.accumulate)
    {
      pthread_t thread;
      int err = pthread_create(&thread, 0, renderLoop, this);
      if (err){
        printf("ERROR creating Embree render loop. return code from pthread_create() is %d\n", err);
        exit(-1);
      }
    }

  }

  /*rtClearTextureCache();*/
  /*rtClearImageCache();*/
  /*delete g_device;*/
  /*g_device = NULL;*/
  /*initialized = false;*/
  /*init();*/


}
Display* dis2;
Window win2;


void EmbreeManager::displayFrame()
{
  if (!rendering)
    return;
  if (_rank > 0)
    return;
  lock(0);
  LOGSTARTC("EmbreeManager::displayFrame", 0.1,0.5,0.0);

  DEBUG("copying image\n");
  static CDTimer displayTimer;
  displayTimer.start();

  g_device->rtSwapBuffers(_frameBuffer);


  /* draw image in OpenGL */

  //glPixelStorei(GL_UNPACK_ROW_LENGTH, _width);
  //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  //glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_SCISSOR_TEST);
  glDisable(GL_ALPHA_TEST);
  glDrawBuffer(GL_BACK);


  //printf("gldrawpixels %d %d \n", _width, _height);
  void* data = g_device->rtMapFrameBuffer(_frameBuffer);

  //for (size_t i = 0; i < _width*_height/8; i++)
  //{
  //struct rgba { unsigned char r,g,b,a; };
  //struct rgb { unsigned char r,g,b; };
  //char* ptr = &((char*)data)[i*3];
  ////rgba* val = &(((rgba*)ptr)[i]);
  //rgb* val = &(((rgb*)ptr)[i]);
  ////rgba color = {0,0,255,255};
  //rgb color = {0,0,255};
  //*val = color;
  //}

  if (_format == "RGB_FLOAT32")
    glDrawPixels(_width,_height,GL_RGB,GL_FLOAT,data);
  else if (_format == "RGBA8")
    glDrawPixels(_width,_height,GL_RGBA,GL_UNSIGNED_BYTE,data);
  else if (_format == "RGB8")
    glDrawPixels(_width,_height,GL_RGB,GL_UNSIGNED_BYTE,data);
  else
    throw std::runtime_error("unkown format: "+_format);

  /*
   *X Test
   */
#if 0

  //static Display* dis;
  //static Window win;
  char green[] = "#00FF00";

  static bool once = false;
  if (!once)
  {
    once = true;
    //dis = XOpenDisplay(0);
    //int screen = DefaultScreen(dis);
    //win = XCreateSimpleWindow(dis, RootWindow(dis, 0), 1, 1, _width, _height, 0, BlackPixel (dis, 0), BlackPixel(dis,0));
    ////Widget w;
    ////Pixmap pixmap = XCreateBitmapFromData(XtDisplay(w),RootWindowOfScreen(XtScreen(w)), data, _width, _height);
    ////Pixmap pixmap = XCreatePixmapFromBitmapData(dis,win, (char*)data, _width, _height, BlackPixel(dis,0), BlackPixel(dis,0), 4);
    //XMapWindow(dis,win);

    //XColor green_col;
    //Colormap colormap;
    //colormap = DefaultColormap(dis, 0);
    //char green[] = "#00FF00";
    //GC green_gc = XCreateGC(dis, win, 0, 0);
    //XSetForeground(dis, green_gc, green_col.pixel);
    //XDrawRectangle(dis,win,green_gc,50,50,200,200);
    //XFlush(dis);
    Display *dis;
    Window win;

    XEvent report;
    GC green_gc;
    XColor green_col;
    Colormap colormap;
    //
    //
    /*
     * Try changing the green[] = below to a different color.
     * The color can also be from /usr/X11R6/lib/X11/rgb.txt, such as RoyalBlue4.
     * A # (number sign) is only needed when using hexadecimal colors.
     * */

    //int main()
    {
      dis = XOpenDisplay(NULL);
      win = XCreateSimpleWindow(dis, RootWindow(dis, 0), 1, 1, _width, _height, 0, BlackPixel (dis, 0), BlackPixel(dis, 0));
      XMapWindow(dis, win);
      colormap = DefaultColormap(dis, 0);
      green_gc = XCreateGC(dis, win, 0, 0);
      XParseColor(dis, colormap, green, &green_col);
      XAllocColor(dis, colormap, &green_col);
      XSetForeground(dis, green_gc, green_col.pixel);

      XSelectInput(dis, win, ExposureMask | KeyPressMask | ButtonPressMask);

      XDrawRectangle(dis, win, green_gc, 1, 1, 497, 497);
      //XDrawRectangle(dis, win, green_gc, 50, 50, 398,   398);
      Pixmap pixmap = XCreatePixmapFromBitmapData(dis,win, (char*)data, _width, _height, BlackPixel(dis,0), BlackPixel(dis,0), 4);
      XFlush(dis);
      _xDisplay = dis;
      *_xWin = win;

      //while (1)  {
      //XNextEvent(dis, &report);
      //switch           (report.type) {
      //case Expose:
      //fprintf(stdout, "I have been exposed.\n");
      //XDrawRectangle(dis, win, green_gc, 1, 1, 497, 497);
      //XDrawRectangle(dis, win, green_gc, 50, 50, 398, 398);
      //XFlush(dis);
      //break;
      //case KeyPress:
      //[>Close the program if q is pressed.<]
      //if (XLookupKeysym(&report.xkey, 0) == XK_q) {
      //exit(0);
      //}
      //break;
      //}
      //}

      //return 0;
    }

  }
  GC green_gc;
  XColor green_col;
  Colormap colormap;
  colormap = DefaultColormap(_xDisplay, 0);
  green_gc = XCreateGC(_xDisplay, *_xWin, 0, 0);
  //XParseColor(_xDisplay, colormap, green, &green_col);
  //XAllocColor(_xDisplay, colormap, &green_col);
  //XSetForeground(_xDisplay, green_gc, green_col.pixel);
  //XDrawRectangle(_xDisplay, *_xWin, green_gc, 50, 50, 398,   398);
  Screen* screen = XDefaultScreenOfDisplay(_xDisplay);
  int screen2 = DefaultScreen(_xDisplay);
  int depth = DefaultDepth(_xDisplay,screen2);
  printf("xdepth: %d\n", depth);
  Pixmap pixmap = XCreatePixmapFromBitmapData(_xDisplay,*_xWin, (char*)data, _width, _height, BlackPixel(_xDisplay,0), BlackPixel(_xDisplay,0), depth);
  //Pixmap pixmap = XCreatePixmap(_xDisplay,*_xWin,_width,_height,DefaultDepthOfScreen(screen));
  //XFillRectangle(_xDisplay,pixmap,green_gc,0,0,_width,_height);
  XSetFillStyle(_xDisplay,green_gc,FillTiled);
  XSetTile(_xDisplay, green_gc, pixmap);
  //XSetRegion(_xDisplay,green_gc,region);
  XFillRectangle(_xDisplay,*_xWin, green_gc,0,0,_width,_height);
  //XCopyArea(_xDisplay,pixmap,*_xWin, green_gc, 0,0,_width,_height,0,0);
  //XColor green_col;
  //Colormap colormap;
  //
  //colormap = DefaultColormap(dis, 0);
  //char green[] = "#00FF00";
  //GC green_gc = XCreateGC(dis, win, 0, 0);
  //XSetForeground(dis, green_gc, green_col.pixel);
  //XDrawRectangle(dis,win,green_gc,1,1,200,200);
  //XFlush(dis);


#endif
  /*
   *END X Test
   */

  glFinish();
  g_device->rtUnmapFrameBuffer(_frameBuffer);

  DEBUG("copy image done\n");


  //TODO: HACK
  if (params.write_to_file != "")
  {
    /*static int _frameNumber = 0;*/
    //TODO: SC VIDEO HACK!
    //!!!!!!!!!!!!!!!!!!!!!
    if (_frameNumber > 3)
    {
      //TODO: SC VIDEO HACK!
      /*static int numberOfFrames = 0;*/
      /*static int _realFrameNumber = 0;*/
      /*static bool once = false;*/
      /*if (!once)*/
      /*{*/
        /*once = true;*/
        /*GetVar<int>("GR_FrameNumber", _realFrameNumber);*/
        /*GetVar<int>("GR_NumberOfFrames", numberOfFrames);*/
        /*_frameNumber = _realFrameNumber;*/
      /*}*/
      /*float aperture = 0.0f;*/
      /*float focalDistance = 0.0f;*/
      /*float interp = 0;*/
      /*if (numberOfFrames > 0)*/
        /*interp = float(_frameNumber)/float(numberOfFrames);*/
      /*params.focalDistance = 125 + 200*interp;*/
      /*params.aperture = 0.6*(1.0-interp) + 0.1;*/
      /*updateCamera();*/
      //!!!!!!!!!!!!!!!!!!!!!
      char* rgba_data = (char*)data;
      DEBUG("writing image\n");
      string filename = params.write_to_file;
      if (params.write_to_file == "generated")
      {
        char cfilename[256];
#if USE_MPI
        sprintf(cfilename, "render_%04d_%dx%d_%d.rgb", _realFrameNumber, _width, _height, _rank);
#else
        sprintf(cfilename, "render_%04d_%dx%d.rgb", _realFrameNumber, _width, _height);
#endif
        filename = string(cfilename);
      }

      printf("writing filename: %s\n", filename.c_str());

      //unsigned char* test = new unsigned char[xres*yres*3];
      //glReadPixels(0,0,xres,yres,GL_RGB, GL_UNSIGNED_BYTE, test);
      FILE* pFile = fopen(filename.c_str(), "w");
      assert(pFile);
      if (_format == "RGBA8")
      {
        fwrite((void*)&rgba_data[0], 1, _width*_height*4, pFile);
        fclose(pFile);
        stringstream s("");
        //TODO: this fudge factor on teh sizes makes no sense... I'm assuming it's because they have row padding in the data but it doesn't show up in drawpixels... perplexing.  It can also crash just a hack for now
        s  << "convert -flip -size " << _width << "x" << _height << " -depth 8 rgba:" << filename << " " << filename << ".png && rm " << filename ;
        /*printf("calling system call \"%s\"\n", s.str().c_str());*/
        system(s.str().c_str());
        //delete []test;

      }
      else
      {
        fwrite(data, 1, _width*_height*3, pFile);
        fclose(pFile);
        stringstream s("");
        //TODO: this fudge factor on teh sizes makes no sense... I'm assuming it's because they have row padding in the data but it doesn't show up in drawpixels... perplexing.  It can also crash just a hack for now
        s << "convert -flip -size " << _width << "x" << _height << " -depth 8 rgb:" << filename << " " << filename << ".png && rm " << filename;
        system(s.str().c_str());
      }
      //delete []test;
    }
    _frameNumber++;
    _realFrameNumber++;
  }

  DEBUG("draw pixels done \n");
  displayTimer.stop();
  //printf("rank: %d display time: %f\n", _rank, displayTimer.getDelta());
  LOGSTOP("EmbreeManager::displayFrame");
  unlock(0);
  embreeMutex.unlock();
}

void EmbreeManager::syncInstances()
{}

void EmbreeManager::updateCamera()
{
  embreeMutex.lock();
  //  cout << "updateCamera\n";
  GLuRayRenderParameters& p = params;
  float angle = p.camera_vfov;
  float aspectRatio = float(_width)/float(_height);

  //p.camera_hfov=p.camera_vfov=22.6;
  embree::Vector3f camPos = embree::Vector3f(p.camera_eye.x(), p.camera_eye.y(), p.camera_eye.z());
  Manta::Vector lookat = (p.camera_eye + p.camera_dir);
  embree::Vector3f camLookAt = embree::Vector3f(lookat.x(), lookat.y(), lookat.z());
  embree::Vector3f camUp = embree::Vector3f(p.camera_up.x(), p.camera_up.y(), p.camera_up.z());
  AffineSpace3f camTransform = AffineSpace3f::lookAtPoint(camPos, camLookAt, camUp);
  AffineSpace3f space(camTransform.l,camTransform.p);
/*#if DEBUG_MSGS*/
  printf("update camera hfov:%f vfov%f angle %f aspect %f focalDistance %f aperture %f eye %f %f %f lookat %f %f %f up %f %f %f \n", p.camera_hfov, p.camera_vfov, angle, aspectRatio, p.focalDistance, p.aperture, camPos[0], camPos[1], camPos[2], camLookAt[0], camLookAt[1], camLookAt[2],
      camUp[0], camUp[1], camUp[2]);
/*#endif*/
  float camRadius = 0.0f;
  if (p.camera != "pinhole")
    camRadius = p.aperture;
  if (camRadius == 0.0f)
  {
    _camera = g_device->rtNewCamera("pinhole");
    g_device->rtSetTransform(_camera, "local2world", copyToArray(space));
    g_device->rtSetFloat1(_camera, "angle", angle);
    g_device->rtSetFloat1(_camera, "aspectRatio", aspectRatio);
    g_device->rtCommit(_camera);
  }
  else
  {
    _camera = g_device->rtNewCamera("depthoffield");
    g_device->rtSetTransform(_camera, "local2world", copyToArray(space));
    g_device->rtSetFloat1(_camera, "angle", angle);
    g_device->rtSetFloat1(_camera, "aspectRatio", aspectRatio);
    g_device->rtSetFloat1(_camera, "lensRadius", camRadius);
    g_device->rtSetFloat1(_camera, "focalDistance", p.focalDistance);
    g_device->rtCommit(_camera);
  }
  embreeMutex.unlock();
}

void EmbreeManager::updateBackground()
{
#if 0
  //  cout << "updateBackground\n";
  current_bgcolor = params.bgcolor;
  if (params.env_map == "" || params.env_map == "none")
    background = new ConstantBackground(current_bgcolor.color);
  else
  {
    EnvMapBackground::MappingType mapping_type = EnvMapBackground::DebevecSphere;
    //CylindricalEqualArea;

    ImageTexture<Color>* t = LoadColorImageTexture( params.env_map, &std::cerr );
    t->setInterpolationMethod(ImageTexture<Color>::Bilinear);
    Vector up( 0.0f, 1.0f, 0.0f );
    Vector right( 1.0f, 0.0f, 0.0f );

    background =  new EnvMapBackground( t,
        mapping_type, right, up ) ;
  }
  //  cout << "done updateBackground\n";
#endif
}

void EmbreeManager::addInstance(Renderable* ren)
{
  if (!rendering)
    return;
  if (!ren->isBuilt())
    return;
  next_scene->instances.push_back(GRInstance(ren, current_transform));
}

void EmbreeManager::addRenderable(Renderable* ren)
{
  //TODO: memory leaks appear to be happening entirely because of the geometry sent down to embree.  Commenting them out fixes memory usage... need to debug embree geom clearing.
  ERenderable* er = dynamic_cast<ERenderable*>(ren);
  if (!er)
    return;
  ren->glMaterial = gl_material;
  Manta::Mesh* mesh = er->_data->mesh;
  size_t numTriangles = mesh->vertex_indices.size()/3;
  size_t numNormals = mesh->vertexNormals.size();
  size_t numTexCoords = mesh->texCoords.size();
  size_t numPositions = mesh->vertices.size();
  printf("addrenderable called mesh indices/3 vertices normals texcoords: %d %d %d %d \n", mesh->vertex_indices.size()/3, mesh->vertices.size(), mesh->vertexNormals.size(),
      mesh->texCoords.size());
  /*if (mesh->vertex_indices.size()/3 <= 4700)  //TODO: HACK: this is a hack for the DNS videos*/
  /*return;*/

  /*if (numPositions < mesh->vertex_indices.size())*/
  /*{*/
  /*printf("warning: vertex/indices mismatch ignoring renderable %d %d \n", numPositions, mesh->vertex_indices.size());*/
  /*return;*/
  /*}*/
  if (numNormals > 0 && (numNormals < numPositions))
  {
    size_t diff = numPositions - numNormals;
    for(size_t i=0; i < diff;i++)
      mesh->vertexNormals.push_back(Vector(0,0,-1));
  }
  if (numTexCoords > 0 && (numTexCoords < numPositions))
  {
    size_t diff = numPositions - numTexCoords;
    for(size_t i=0; i < diff;i++)
      mesh->texCoords.push_back(Vector(0,0,0));
  }
  if (numTexCoords == 0)
  {
    //TODO: SC HACK, contour with normals was crashing.  Don't have time to debug embree
    mesh->vertexNormals.resize(0);
    numNormals = 0;
  }
  printf("addrenderable after refit mesh indices/3 vertices normals texcoords: %d %d %d %d \n", mesh->vertex_indices.size()/3, mesh->vertices.size(), mesh->vertexNormals.size(),
      mesh->texCoords.size());

  /*mesh->vertices.resize(0);*/
  /*mesh->vertex_indices.resize(0);*/
  /*mesh->vertices.push_back(Vector(0,0,0));*/
  /*mesh->vertices.push_back(Vector(0,1,0));*/
  /*mesh->vertices.push_back(Vector(1,0,0));*/
  /*mesh->vertex_indices.push_back(0);*/
  /*mesh->vertex_indices.push_back(1);*/
  /*mesh->vertex_indices.push_back(2);*/

  //TODO: THIS IS DEBUG CODE
  /*numTexCoords = 0;*/
  /*numNormals = 0;*/
  /*if (numPositions > 300)*/
  /*numPositions = 300;*/
  /*if (numTriangles > 100)*/
  /*numTriangles = 100;*/
  //!!!!!!!!!!!!!!!!!!!!!

  embreeMutex.lock();
  /*float positionsV[] = {-1000, 0, -1000, 1000, 0, -1000, 1000, 0, 1000, -1000, 0, 1000};*/
  /*float* pv = (float*)alignedMalloc(sizeof(float)*3*4);*/
  /*for(int i =0; i < 12; i++)*/
  /*pv[i] = positionsV[i];*/
  embree::Vec3f* vertices = (embree::Vec3f*)alignedMalloc(sizeof(embree::Vec3f)*numPositions);
  for(size_t i = 0; i < numPositions; i++)
    vertices[i] = embree::Vec3f(mesh->vertices[i].x(), mesh->vertices[i].y(), mesh->vertices[i].z());
  Handle<Device::RTData> positions = g_device->rtNewData("immutable_managed",numPositions*sizeof(Manta::Vector), &vertices[0]);
  size_t numMotions = 0;
  embree::Vec3f* nv = (embree::Vec3f*)alignedMalloc(sizeof(embree::Vec3f)*numNormals);
  for(size_t i = 0; i < numNormals; i++)
    nv[i] = embree::Vec3f(mesh->vertexNormals[i].x(), mesh->vertexNormals[i].y(), mesh->vertexNormals[i].z());
  Handle<Device::RTData> normals = g_device->rtNewData("immutable_managed",numNormals*sizeof(embree::Vec3f), &nv[0]);
  embree::Vec2f* tv = (embree::Vec2f*)alignedMalloc(sizeof(embree::Vec2f)*numTexCoords);
  for(size_t i = 0; i < numTexCoords; i++)
    tv[i] = embree::Vec2f(mesh->texCoords[i].x(), mesh->texCoords[i].y());
  Handle<Device::RTData> texcoords = g_device->rtNewData("immutable_managed",numTexCoords*sizeof(embree::Vec2f), tv);
  embree::Vec3i* vertex_indices = (embree::Vec3i*)alignedMalloc(sizeof(embree::Vec3i)*numTriangles);
  for(size_t i = 0, mi = 0; i < numTriangles; i++, mi+=3)
  {
    vertex_indices[i] = embree::Vec3i(mesh->vertex_indices[mi+0], mesh->vertex_indices[mi+1], mesh->vertex_indices[mi+2]);
  }
  Handle<Device::RTData> triangles = g_device->rtNewData("immutable_managed",numTriangles*sizeof(embree::Vec3i), &vertex_indices[0]);

  Handle<Device::RTShape> d_mesh = g_device->rtNewShape("trianglemesh");
  if (numPositions) g_device->rtSetArray(d_mesh, "positions", "float3", positions, numPositions, sizeof(embree::Vec3f), 0);
  mesh->vertices.resize(0);
  //if (numMotions  ) g_device->rtSetArray(d_mesh, "motions"  , "float3", motions  , numMotions  , sizeof(embree::Vec3f), 0);
  if (numNormals  ) g_device->rtSetArray(d_mesh, "normals"  , "float3", normals  , numNormals  , sizeof(embree::Vec3f), 0);
  mesh->vertexNormals.resize(0);
  if (numTexCoords) g_device->rtSetArray(d_mesh, "texcoords", "float2", texcoords, numTexCoords, sizeof(embree::Vec2f ), 0);
  mesh->texCoords.resize(0);
  if (numTriangles) g_device->rtSetArray(d_mesh, "indices"  , "int3"  , triangles, numTriangles, sizeof(embree::Vec3i ), 0);
  mesh->vertex_indices.resize(0);
  g_device->rtSetString(d_mesh,"accel",g_mesh_accel.c_str());
  g_device->rtSetString(d_mesh,"builder",g_mesh_builder.c_str());
  g_device->rtSetString(d_mesh,"traverser",g_mesh_traverser.c_str());
  g_device->rtSetBool1(d_mesh, "calculateTangents", false);
  /*
   *TODO: CARSON:  need to specify local transforms for each mesh instance?
   */
  g_device->rtCommit(d_mesh);
  g_device->rtClear(d_mesh);

  er->_data->d_mesh = d_mesh;
  er->_data->d_material = g_current_material;

  er->setBuilt(true);
  next_scene->renderables.push_back(er);
  _newRenderables.push_back(er);
  embreeMutex.unlock();

  /*for(size_t vi = 0; vi < mesh->vertices.size(); vi++)*/
  /*{*/
  /*OBJVertex v;*/
  /*Vector& mv = mesh->vertices[vi];*/
  /*v.x = mv[0];*/
  /*v.y = mv[1];*/
  /*v.z = mv[2];*/
  /*_objScene->vertices.push_back(v);*/
  /*}*/
  /*OBJGroup group;*/
  /*for(size_t vi = 0; vi < mesh->vertex_indices.size(); vi++)*/
  /*{*/
  /*if ( (vi + 2) >= mesh->vertex_indices.size())*/
  /*break;*/
  /*OBJFace f;*/
  /*size_t mvi0 = mesh->vertex_indices[vi];*/
  /*size_t mvi1 = mesh->vertex_indices[vi+1];*/
  /*size_t mvi2 = mesh->vertex_indices[vi+2];*/
  /*f.vertexIndices.push_back(mvi0);*/
  /*f.vertexIndices.push_back(mvi1);*/
  /*f.vertexIndices.push_back(mvi2);*/
  /*group.faces.push_back(f);*/
  /*}*/
  /*_objScene->groups.push_back(group);*/

#if 0
  MRenderable* mr = dynamic_cast<MRenderable*>(ren);
  static int counter = 0;
  MPI_Comm_group(mworld, &world_group);

  //mr->setBuilt(false);
  next_scene->renderables.push_back(mr);
  _newRenderables.push_back(mr);
  printf("rank: %d %s: size: %d done\n", _rank, __FUNCTION__, mr->getNumPrims());
#endif
}

void EmbreeManager::deleteRenderable(Renderable* ren)
{
  //TODO: DELETE RENDERABLES
  ERenderable* er = dynamic_cast<ERenderable*>(ren);
  printf("deleting renderable of size: %d\n", er->_data->mesh->vertex_indices.size()/3);
  embreeMutex.lock();
  /*if (er->isBuilt())*/
  /*g_device->rtClear(er->_data->d_mesh);*/
  er->setBuilt(false);
  /*er->_data->mesh->vertexNormals.resize(0);*/
  delete er->_data->mesh;  //embree handles clearing the data... not sure how to get it to not do that with rtclear yet
  embreeMutex.unlock();
}

Handle<Device::RTImage> createRandomImage(Device *device, size_t width, size_t height)
{
  if (1)//random<bool>())
  {
    char* data = new char[3 * width * height];
    for (size_t y=0; y < height; y++) {
      for (size_t x=0; x < width; x++) {
        size_t ofs = y * width + x;
        data[3 * ofs + 0] = 255;//char(x * y);
        data[3 * ofs + 1] = 0;//char(y * x);
        data[3 * ofs + 2] = 0;//char(x + y);
      }
    }
    Handle<Device::RTImage> image = device->rtNewImage("RGB8", width, height, data);
    delete[] data;
    return(image);
  }
  else {
    Col3f* data = new Col3f[3 * width * height];
    for (size_t y=0; y < height; y++) {
      for (size_t x=0; x < width; x++) {
        size_t ofs = y * width + x;
        data[ofs].r = char(x * y) / 255.0f;
        data[ofs].g = char(y * x) / 255.0f;
        data[ofs].b = char(x + y) / 255.0f;
      }
    }
    Handle<Device::RTImage> image = device->rtNewImage("RGB_FLOAT32", width, height, data);
    delete[] data;
    return(image);
  }
}


void EmbreeManager::exportOBJ(EScene* scene)
{
  ofstream out("output.obj");
  /*if (out)*/
  /*{*/
  /*out << *_objScene;*/
  /*out.close();*/
  /*}*/
  /*return;*/

  OBJScene objScene;
  size_t indexCounter = 0;
  size_t normalIndexCounter = 0;
  size_t textureIndexCounter = 0;

  for(vector<GRInstance>::iterator itr = scene->instances.begin(); itr != scene->instances.end(); itr++)
  {
    Manta::AffineTransform mt = itr->transform;
    Renderable* ren = itr->renderable;
    ERenderable* er = dynamic_cast<ERenderable*>(ren);
    if (!er)
    {
      printf("exportOBJ ERROR - wrong instance type\n");
      continue;
    }
    Manta::Mesh* mesh = er->_data->mesh;
    printf("objexport called mesh size: %d\n", mesh->vertex_indices.size()/3);
    printf("objexport called mesh texcoords: %d\n", mesh->texCoords.size());
    fflush(stdout);
    /*if (mesh->vertex_indices.size()/3 < 100)  //TODO: HACK: this is a hack for the DNS videos*/
    /*continue;*/
    /*AffineSpace3f et(LinearSpace3f(mt(0,0), mt(0,1), mt(0,2), mt(1,0), mt(1,1), mt(1,2), mt(2,0),mt(2,1),mt(2,2)), Vector3f(mt(0,3),mt(1,3),mt(2,3)));*/
    //AffineSpace3f et(LinearSpace3f(mt(0,0), mt(1,0), mt(2,0), mt(0,1), mt(1,1), mt(2,1), mt(0,2),mt(1,2),mt(2,2)), Vector3f(mt(3,0),mt(3,1),mt(3,2)));
    /*prims.push_back(g_device->rtNewShapePrimitive(er->_data->d_mesh, er->_data->d_material, copyToArray(et)));*/
    for(size_t vi = 0; vi < mesh->vertices.size(); vi++)
    {
      OBJVertex v;
      Vector mv = mesh->vertices[vi];
      /*printf("premult %f %f %f\n", mv[0], mv[1], mv[2]);*/
      mv = mt.multiply_vector(mv);
      /*printf("postmult %f %f %f\n", mv[0], mv[1], mv[2]);*/
      v.x = mv[0]+mt(0,3);
      v.y = mv[1]+mt(1,3);
      v.z = mv[2]+mt(2,3);
      objScene.vertices.push_back(v);
    }
    for(size_t ni = 0; ni < mesh->vertexNormals.size(); ni++)
    {
      OBJNormal v;
      Vector mv = mesh->vertexNormals[ni];
      /*printf("premult %f %f %f\n", mv[0], mv[1], mv[2]);*/
      /*mv = mt.multiply_vector(mv);*/
      /*printf("postmult %f %f %f\n", mv[0], mv[1], mv[2]);*/
      v.x = mv[0];
      v.y = mv[1];
      v.z = mv[2];
      objScene.normals.push_back(v);
    }
    for(size_t ni = 0; ni < mesh->texCoords.size(); ni++)
    {
      OBJTexCoord v;
      Vector mv = mesh->texCoords[ni];
      /*printf("premult %f %f %f\n", mv[0], mv[1], mv[2]);*/
      /*mv = mt.multiply_vector(mv);*/
      /*printf("postmult %f %f %f\n", mv[0], mv[1], mv[2]);*/
      v.u = mv[0];
      v.v = mv[1];
      v.w = mv[2];
      objScene.texCoords.push_back(v);
    }
    std::stringstream name;
    name << "Group" << itr - scene->instances.begin()+1;
    OBJGroup group(name.str());
    OBJMaterial mat(name.str()+"Mat");
    group.material = mat.name;
    GLMaterial glMat = er->glMaterial;
    mat.Kd = Vector(glMat.diffuse[0], glMat.diffuse[1], glMat.diffuse[2]);
    mat.Ka = Vector(glMat.ambient[0], glMat.ambient[1], glMat.ambient[2]);
    mat.Ks = Vector(glMat.specular[0], glMat.specular[1], glMat.specular[2]);
    mat.Ns = glMat.shiny;
    objScene.materials.push_back(mat);
    for(size_t vi = 0; vi < mesh->vertex_indices.size(); vi++)
    {
      if ( (vi + 2) >= mesh->vertex_indices.size())
        break;
      OBJFace f;
      size_t mvi0 = mesh->vertex_indices[vi++];
      size_t mvi1 = mesh->vertex_indices[vi++];
      size_t mvi2 = mesh->vertex_indices[vi];
      /*printf("adding vertex indices: %d\n", mesh->vertex_indices[vi]);*/
      f.vertexIndices.push_back(mvi0+indexCounter+1);
      f.vertexIndices.push_back(mvi1+indexCounter+1);
      f.vertexIndices.push_back(mvi2+indexCounter+1);
      if (mesh->texCoords.size() > 0)
      {
        f.textureIndices.push_back(mvi0+textureIndexCounter+1);
        f.textureIndices.push_back(mvi1+textureIndexCounter+1);
        f.textureIndices.push_back(mvi2+textureIndexCounter+1);
      }
      if (mesh->vertexNormals.size() > 0)
      {
        f.normalIndices.push_back(mvi0+normalIndexCounter+1);
        f.normalIndices.push_back(mvi1+normalIndexCounter+1);
        f.normalIndices.push_back(mvi2+normalIndexCounter+1);
      }
      group.faces.push_back(f);
    }
    objScene.groups.push_back(group);
    indexCounter += mesh->vertices.size();
    textureIndexCounter += mesh->texCoords.size();
    normalIndexCounter += mesh->vertexNormals.size();
  }

  /*ofstream out("output.obj");*/
  printf("outputting scene\n");
  fflush(stdout);
  if (out)
  {
    out << objScene;
    out.close();
  }
  printf("done outputting scene\n");
  fflush(stdout);
}

void EmbreeManager::addTexture(int handle, int target, int level, int internalFormat, int width, int height, int border, int format, int type, void* data)
{
  if(!initialized)
    return;
  if (border != 0)
    return;
  if (format != GL_RGBA)
    return;
  if (type != GL_UNSIGNED_BYTE)
    return;
  /*g_device->rtSetTexture(g_current_material, "map_d" , rtLoadTexture("/work/01336/carson/data/lightProbes/rnl_probe.pfm"));*/
  unsigned char* udata = (unsigned char*)data;

  printf("creating texture\n");
  int packAlignment, unpackAlignment;
  glGetIntegerv(GL_PACK_ALIGNMENT, &packAlignment);
  glGetIntegerv(GL_UNPACK_ALIGNMENT, &unpackAlignment);
  printf("creating texture 2\n");
  Handle<Device::RTTexture> texture = g_device->rtNewTexture("image");
  unsigned char* buff = new unsigned char[4*width*height];
  for (size_t y=0; y < height; y++) {
    for (size_t x=0; x < width; x++) {
      size_t ofs = y * width + x;
      if (udata)
      {
        buff[4 * ofs + 0] = udata[4*ofs+0];//float(x)/float(width)*255.0f;//udata[4*ofs+0];
        buff[4 * ofs + 1] = udata[4*ofs+1];
        buff[4 * ofs + 2] = udata[4*ofs+2];
      }
      else
      {
        buff[4 * ofs + 0] = 128;//udata[4*ofs+0];//float(x)/float(width)*255.0f;//udata[4*ofs+0];
        buff[4 * ofs + 1] = 0;//udata[4*ofs+1];
        buff[4 * ofs + 2] = 0;//udata[4*ofs+2];
      }
    }
  }
  Handle<Device::RTImage> image = g_device->rtNewImage("RGBA8", width, height, buff);
  delete[] buff;

  /*Handle<Device::RTImage> image = createRandomImage(g_device, width, height); // g_device->rtNewImage("RGBA8", width, height, data);*/
  /*g_device->rtSetImage(texture, "image", image);*/
  g_device->rtSetImage(texture, "image",
      rtLoadImage("/work/01336/carson/FIU_Videos/SC_AnimatedStreamlines/colormap2.ppm"));
  /*rtLoadImage("/home1/01336/carson/colormap.ppm"));*/
  printf("creating texture 3\n");
  g_device->rtCommit(texture);
  _textures[handle] = new Handle<Device::RTTexture>(texture);
  /*_textures[handle] = NULL;*/
  /*Handle<Device::RTTexture>* tex = new Handle<Device::RTTexture>();*/
  printf("add texture id %d\n", handle);
}

void EmbreeManager::deleteTexture(int handle)
{

}

GeometryGenerator* EmbreeManager::getGeometryGenerator(int type)
{
  switch(type)
  {
    case GL_TRIANGLES:
      {
        return _gTriangle;
      }
    case GL_TRIANGLE_STRIP:
      {
        return _gTriangleStrip;
      }
    case GL_QUADS:
      {
        return _gQuads;
      }
    case GL_QUAD_STRIP:
      {
        return _gQuadStrip;
      }
    case GL_LINES:
      {
        //			gen = rm->GLines;
        //break;
      }
    case GL_LINE_STRIP:
      {
        //			gen = rm->GLineStrip;
        //break;
      }
    case GL_POLYGON:
      {
        //this is temporary for visit, need to support other than quads
        //break;
      }
    default:
      {
        return _gVoid;
      }
  }
}

RenderManager* createEmbreeManager(){ return EmbreeManager::singleton(); }
