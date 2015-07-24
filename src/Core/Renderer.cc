/**********************************************************************************
*                     Copyright (c) 2013-2015 Carson Brownlee
*         Texas Advanced Computing Center, University of Texas at Austin
*                       All rights reserved
* 
*       This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
* 
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
* 
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************************/

#include "Renderer.h"

#include <sstream>

#include <GL/gl.h>

using namespace glr;

  Renderer::Renderer()
: current_renderable(NULL),
  auto_camera(false), num_threads(8), rendering(false), current_color(1,0.714,0.216,1), print_build_time(true), relaunch(false), client_running(false), current_bgcolor(1,1,1,1), render_once(false), usePerVertexColors(false),
  frame_lag(false), rank(-1)
  , use_gl_lights(true), lights_dirty(true), use_gl_material(false), dirty_renderParams(false), new_renderParamsString(""),dirty_sampleGenerator(true)
  , initialized(false)
  , _zNear(0.1), _zFar(100.0)
  , _nid_counter(0), _depth(false), _width(0), _height(0), _frameNumber(0), _realFrameNumber(0),
 current_scene(NULL), next_scene(NULL)
{
  gl_lights.resize(8);
  _mutexes.push_back(new Manta::Mutex("Renderer"));
}


// // get sockaddr, IPv4 or IPv6:
// void *get_in_addr(struct sockaddr *sa)
// {
//   if (sa->sa_family == AF_INET) {
//     return &(((struct sockaddr_in*)sa)->sin_addr);
//   }

//   return &(((struct sockaddr_in6*)sa)->sin6_addr);
// }



// void* Renderer::clientLoop(void* t)
// {
//   fflush(stdout);
//   Renderer* manager = dynamic_cast<Renderer*>((Renderer*)t);
//   assert(manager);
//   int sockfd, numbytes;
//   char buf[1024];
//   struct addrinfo hints, *servinfo, *p;
//   int rv;
//   char s[INET6_ADDRSTRLEN];
//   sleep(1); //give some time for server to start

//   memset(&hints, 0, sizeof hints);
//   hints.ai_family = AF_UNSPEC;
//   hints.ai_socktype = SOCK_STREAM;

//   char* cport = getenv("GLURAY_PORT");
//   string port;
//   if (cport)
//     port = string(cport);
//   else
//     port = "3490";

//   printf("client listening on port %s\n",port.c_str());

//   if ((rv = getaddrinfo("localhost", port.c_str(), &hints, &servinfo)) != 0) {
//     fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
//     pthread_exit(0);
//   }

//   // loop through all the results and connect to the first we can
//   for(p = servinfo; p != NULL; p = p->ai_next) {

//     if ((sockfd = socket(p->ai_family, p->ai_socktype,
//             p->ai_protocol)) == -1) {
//       perror("client: socket");
//       continue;
//     }

//     if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
//       close(sockfd);
//       perror("client: connect");
//       continue;
//     }

//     break;
//   }

//   if (p == NULL) {
//     fprintf(stderr, "client: failed to connect\n");
//     pthread_exit(0);
//   }

//   inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
//       s, sizeof s);
//   printf("client: connecting to %s\n", s);

//   freeaddrinfo(servinfo); // all done with this structure

//   while (1)
//   {
//     if ((numbytes = recv(sockfd, buf, 1024-1, 0)) == -1) {
//       cerr << "error recieving network buffer\n";
//       perror("recv");
//       exit(1);
//     }

//     buf[numbytes] = '\0';

//     printf("client: received '%s'\n",buf);
//     // manager->setRenderParametersString(string(buf), false);
//     // manager->general_mutex.lock();
//     manager->dirty_renderParams = true;
//     manager->new_renderParamsString = string(buf);
//     // manager->general_mutex.unlock();
//   }
// }

// // Initialize thread to listen to gui client
// void Renderer::initClient()
// {
// #if RUN_CLIENT
//   if (!client_running)
//   {
//     client_running = true;
//     pthread_t thread;
//     cout << "run client\n";
//     int err = pthread_create(&thread, 0, clientLoop, this);
//     if (err){
//       printf("ERROR; return code from pthread_create() is %d\n", err);
//       exit(-1);
//     }
//   }
// #endif
// }

void Renderer::pushRenderParameters()
{
  render_parameters_stack.push(params);
}

void Renderer::popRenderParameters()
{
  params = render_parameters_stack.top();
  render_parameters_stack.pop();
}

// Check new parameters and call relevant update functions
void Renderer::setRenderParameters(GLuRayRenderParameters& rp, bool need_relaunch)
{
  // general_mutex.lock();

  GLuRayRenderParameters oldp = params;
  params = rp;

  if (params.num_threads != oldp.num_threads)
    setNumThreads(params.num_threads);

  // if (params.num_ao_samples != oldp.num_ao_samples || params.ao_distance != oldp.ao_distance || params.ao_intensity != oldp.ao_intensity)
    // updateRenderer();

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

void Renderer::setRenderParametersString(string in, bool need_relaunch)
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
    //     manager->render();
  }
  else if (mode == "-renderOnce"){
    pushRenderParameters();
    setRenderParameters(rp, need_relaunch);
    render_once = true;
    //render
    //todo: make thread safe
    // render();

    // popGLuRayRenderParameters();
  }
  else
  {
    cerr << "unknown render mode\n";
  }
}

void Renderer::addInstance(Renderable* ren)
{
  // addInstance(ren);
  // if (!ren->isBuilt())
  // {
  //   std::cerr << "addInstance: renderable not build by Renderer\n";
  //   return;
  // }
  // next_scene->instances.push_back(GRInstance(ren, current_transform));
  //   if (!ren->isBuilt())
  //   return;
  // next_scene->instances.push_back(GRInstance(ren, current_transform));
}

// extern Renderer* createEmbreeManager();
// extern Renderer* createOSPRayManager();
// extern Renderer* createRIVLManager();
// extern Renderer* createOptiXManager();

// void Renderer::lock(const int mutex)
// {
//  _mutexes[mutex]->lock();
// }

// void Renderer::unlock(const int mutex)
// {
//   _mutexes[mutex]->unlock();
// }

void Renderer::displayFrame()
{
  if (!initialized)
    return;

  if (!_framebuffer.data || !_framebuffer.width || !_framebuffer.height)
    return;

  GLenum glData = 0;
  GLenum glFormat = 0;

  if (_framebuffer.format == "RGBA8")
  {
    glData = GL_UNSIGNED_BYTE;
    glFormat = GL_RGBA;
  }
  else if (_framebuffer.format == "BGRA8")
  {
    glData = GL_UNSIGNED_BYTE;
    glFormat = GL_BGRA;
  }
  else if (_framebuffer.format == "float1")
  {
    glData = GL_FLOAT;
    glFormat    = GL_LUMINANCE;
  }
  else if (_framebuffer.format == "float3")
  {
    glData = GL_FLOAT;
    glFormat    = GL_RGB;
  }
  else if (_framebuffer.format == "float4")
  {
    glData = GL_FLOAT;
    glFormat    = GL_RGBA;
  }
  else
  {
    std::cerr << "GLR_ERROR: unrecognized format type\n";
    return;
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT, _framebuffer.byteAlign);

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_SCISSOR_TEST);
  glDisable(GL_ALPHA_TEST);
  glDisable(GL_BLEND);
  // glDrawBuffer(GL_FRONT);
  // printf("drawing to buffer\n");

  // struct rgba { unsigned char c[4];};
  // for(int i =0;i<_width;i++)
  // {
  //   for(int j =0;j<_height;j++)
  //   {
  //     rgba* c = &(((rgba*)_framebuffer.data)[j*_width + i]);
  //     // c->c[0]=0;
  //     // c->c[1]=255;
  //     // c->c[2]=0;
  //     // c->c[3]=255;
  //   }
  // }

      // NVTX_RangePushA("glDrawPixels");
  glDrawPixels( static_cast<GLsizei>( _framebuffer.width ), static_cast<GLsizei>( _framebuffer.height ),
   glFormat, glData, _framebuffer.data);
    // NVTX_RangePop();


  if (params.write_to_file != "")
  {
    char* data = (char*)_framebuffer.data;
    char* rgba_data = (char*)data;
    DEBUG("writing image\n");
    string filename = params.write_to_file;
    if (params.write_to_file == "generated")
    {
      char cfilename[256];
        #if USE_MPI
      sprintf(cfilename, "render_%04d_%dx%d_%d.rgb", _realFrameNumber, _framebuffer.width, _framebuffer.height, _rank);
        #else
      sprintf(cfilename, "render_%04d_%dx%d.rgb", _realFrameNumber, _framebuffer.width, _framebuffer.height);
        #endif
      filename = string(cfilename);
    }

    printf("writing filename: %s\n", filename.c_str());

      //unsigned char* test = new unsigned char[xres*yres*3];
      //glReadPixels(0,0,xres,yres,GL_RGB, GL_UNSIGNED_BYTE, test);
    FILE* pFile = fopen(filename.c_str(), "w");
    assert(pFile);
    if (_framebuffer.format == "RGBA8")
    {
      fwrite((void*)&rgba_data[0], 1, _width*_height*4, pFile);
      fclose(pFile);
      stringstream s("");
        //TODO: this fudge factor on teh sizes makes no sense... I'm assuming it's because they have row padding in the data but it doesn't show up in drawpixels... perplexing.  It can also crash just a hack for now
      s  << "convert -flip -size " << _framebuffer.width << "x" << _framebuffer.height << " -depth 8 rgba:" << filename << " " << filename << ".png && rm " << filename ;
        /*printf("calling system call \"%s\"\n", s.str().c_str());*/
      system(s.str().c_str());
        //delete []test;

    }
    if (_framebuffer.format == "BGRA8")
    {
      struct Pix { unsigned char r,g,b,a; };        
      Pix rgba_data[_framebuffer.width*_framebuffer.height*sizeof(Pix)];
      for(size_t i=0; i <_framebuffer.width*_framebuffer.height;i++)
      {
        Pix* pix = &((Pix*)data)[i];
        Pix* pix2 = &rgba_data[i];
        pix2->r=pix->b;
        pix2->g=pix->g;
        pix2->b=pix->r;
        pix2->a=pix->a;
      }
      fwrite((void*)&rgba_data[0], 1, _framebuffer.width*_framebuffer.height*4, pFile);
      fclose(pFile);
      stringstream s("");
        //TODO: this fudge factor on teh sizes makes no sense... I'm assuming it's because they have row padding in the data but it doesn't show up in drawpixels... perplexing.  It can also crash just a hack for now
      s  << "convert -flip -size " << _framebuffer.width << "x" << _framebuffer.height << " -depth 8 rgba:" << filename << " " << filename << ".png && rm " << filename ;
        /*printf("calling system call \"%s\"\n", s.str().c_str());*/
      system(s.str().c_str());
        //delete []test;

    }
    else
    {
        // fwrite(data, 1, _width*_height*3, pFile);
        // fclose(pFile);
        // stringstream s("");
        //   //TODO: this fudge factor on teh sizes makes no sense... I'm assuming it's because they have row padding in the data but it doesn't show up in drawpixels... perplexing.  It can also crash just a hack for now
        // s << "convert -flip -size " << _width << "x" << _height << " -depth 8 rgb:" << filename << " " << filename << ".png && rm " << filename;
        // system(s.str().c_str());
    }
      //delete []test;
    _realFrameNumber++;
  }
}

