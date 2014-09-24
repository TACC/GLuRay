// #include <optixu/optixpp_namespace.h>
// #include <optixu/optixu_math_namespace.h>
// #include <optixu/optixu_aabb_namespace.h>
// #include <sutil.h>
// #include <GLUTDisplay.h>
// #include <PlyLoader.h>
// #include <ObjLoader.h>
// #include "commonStructs.h"
// #include <string>
// #include <iostream>
// #include <fstream>
// #include <cstdlib>
// #include <cstring>
// #include "random.h"
// #include "MeshScene.h"


#include <UseMPI.h>
#ifdef USE_MPI
#include <Engine/Display/NullDisplay.h>
#include <Engine/LoadBalancers/MPI_LoadBalancer.h>
#include <Engine/ImageTraversers/MPI_ImageTraverser.h>
#include <mpi.h>
#endif

#include "defines.h"
#include "OptiXManager.h"
//#include <X11/Xlib.h>
//#include <X11/Xutil.h>

//#include "../gl_functions.h"
#include "CDTimer.h"
#include "OScene.h"
#include "ORenderable.h"
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

OptiXManager* OptiXManager::_singleton = NULL;

OptiXManager* OptiXManager::singleton()
{
  if (!_singleton)
    _singleton = new OptiXManager();
  return _singleton;
}


OptiXManager::OptiXManager()
:RenderManager(), current_scene(NULL), next_scene(NULL),
_nid_counter(0), _depth(false), _width(0), _height(0), _frameNumber(0), _realFrameNumber(0)
{
  initialized=false;
  printf("%s::%s\n",typeid(*this).name(),__FUNCTION__);
  _format = "RGBA8";

  _gVoid = new OGeometryGeneratorVoid();
  _gTriangle = new OGeometryGeneratorTriangles();
  _gTriangleStrip = new OGeometryGeneratorTriangleStrip();
  _gQuads = new OGeometryGeneratorQuads();
  _gQuadStrip = new OGeometryGeneratorQuadStrip();
  _gLines = new OGeometryGeneratorLines();
  _gLineStrip= new OGeometryGeneratorLineStrip();

}

OptiXManager::~OptiXManager()
{
}

void OptiXManager::updateLights()
{

}

Renderable* OptiXManager::createRenderable(GeometryGenerator* gen)
{
  OGeometryGenerator* mg = dynamic_cast<OGeometryGenerator*>(gen);
  assert(mg);
  return new ORenderable(mg);
}

void  OptiXManager::updateMaterial()
{
  if (!initialized)
    return;
  GLMaterial m = gl_material;
  //TODO: DEBUG: hardcoding mat for debugging
  // m.diffuse = Color(RGB(1.0, 0.713726, .21569));
  //m.diffuse = Color(RGB(0.8, 0.8, 0.8));
  // m.specular = Manta::Color(RGB(.1, .1, .1));
  // m.ambient = Manta::Color(RGB(0, 0, 0));
  // m.shiny = 100;

}

void OptiXManager::useShadows(bool st)
{
}

void OptiXManager::setSize(int w, int h)
{

  printf("setSize %d %d\n", w,h);
  if (initialized && (w != _width || h != _height))
  {
    _width = w; _height = h;
    updateCamera();
  }
}


void OptiXManager::init()
{
  if (initialized)
    return;
  initialized=true;
  printf("%s::%s\n",typeid(*this).name(),__FUNCTION__);

  updateBackground();
  updateCamera();
  updateMaterial();
  if (!current_scene)
    current_scene = new OScene();
  if (!next_scene)
    next_scene = new OScene();

}

//TODO: updating pixelsampler mid flight crashes manta
void OptiXManager::setNumSamples(int,int,int samples)
{
}

void OptiXManager::setNumThreads(int t)
{
}

size_t OptiXManager::generateNID()
{
  return 0;
  // return ++_nid_counter;
}

Renderable* OptiXManager::getRenderable(size_t nid)
{
  return _map_renderables[nid];
}

void* OptiXManager::renderLoop(void* t)
{
}

void OptiXManager::internalRender()
{
}


void OptiXManager::render()
{
  printf("optix render\n");
  if (!initialized)
    return;
  if (next_scene->instances.size() == 0)
    return;
  for(vector<GRInstance>::iterator itr = next_scene->instances.begin(); itr != next_scene->instances.end(); itr++)
  {
    Manta::AffineTransform mt = itr->transform;
    Renderable* ren = itr->renderable;
    ORenderable* er = dynamic_cast<ORenderable*>(ren);
    if (er->isBuilt())
    {
        //JOAO: add instances to optix scene here
    }
  }
  next_scene->instances.resize(0);

  //JOAO: put render call here

  displayFrame();

}


void OptiXManager::displayFrame()
{
  char* data = NULL;

  //JOAO: map data to buffer

  if (!data)
    return;
  if (_format == "RGBA8")
    glDrawPixels(_width, _height, GL_RGBA, GL_UNSIGNED_BYTE, data);
  else
    return;

   if (params.write_to_file != "")
  {
    char* rgba_data = (char*)data;
    DEBUG("writing image\n");
    string filename = params.write_to_file;
      // if (params.write_to_file == "generated")
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
    _realFrameNumber++;
  }
}

void OptiXManager::syncInstances()
{}

void OptiXManager::updateCamera()
{
  //JOAO: put camera update here
}

void OptiXManager::updateBackground()
{
}

void OptiXManager::addInstance(Renderable* ren)
{
  if (!ren->isBuilt())
  {
    std::cerr << "addInstance: renderable not build by rendermanager\n";
    return;
  }
  next_scene->instances.push_back(GRInstance(ren, current_transform));
}

void OptiXManager::addRenderable(Renderable* ren)
{
  ORenderable* oren = dynamic_cast<ORenderable*>(ren);
  if (!oren)
  {
    printf("error: OptiXManager::addRenderable wrong renderable type\n");
    return;
  }
  // updateMaterial();
      // msgModel = new miniSG::Model;
      // msgModel->material.push_back(new miniSG::Material);
  // OSPMaterial ospMat = ospNewMaterial(renderer,"OBJMaterial");
  // float Kd[] = {1.f,1.f,1.f};
  // float Ks[] = {1,1,1};

  Manta::Mesh* mesh = oren->_data->mesh;
  assert(mesh);
  size_t numNormals = mesh->vertexNormals.size();
  size_t numTexCoords = mesh->texCoords.size();
  size_t numPositions = mesh->vertices.size();
  printf("addrenderable called mesh indices/3 vertices normals texcoords: %d %d %d %d \n", mesh->vertex_indices.size()/3, mesh->vertices.size(), mesh->vertexNormals.size(),
    mesh->texCoords.size());
  size_t numTriangles = mesh->vertex_indices.size()/3;
  // assert(mesh->vertices.size() == numTriangles*3);
  oren->setBuilt(true);

  //JOAO: put optix call here
}

void OptiXManager::deleteRenderable(Renderable* ren)
{
  //TODO: DELETE RENDERABLES
  ORenderable* r = dynamic_cast<ORenderable*>(ren);
  // printf("deleting renderable of size: %d\n", er->_data->mesh->vertex_indices.size()/3);
  /*if (er->isBuilt())*/
  /*g_device->rtClear(er->_data->d_mesh);*/
  r->setBuilt(false);
  /*er->_data->mesh->vertexNormals.resize(0);*/
  // delete er->_data->mesh;  //embree handles clearing the data... not sure how to get it to not do that with rtclear yet
}



void OptiXManager::addTexture(int handle, int target, int level, int internalFormat, int width, int height, int border, int format, int type, void* data)
{
}

void OptiXManager::deleteTexture(int handle)
{

}

GeometryGenerator* OptiXManager::getGeometryGenerator(int type)
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
    //case GL_LINES:
    //{
        ////			gen = rm->GLines;
        ////break;
    //}
    //case GL_LINE_STRIP:
    //{
        ////			gen = rm->GLineStrip;
        ////break;
    //}
    //case GL_POLYGON:
    //{
        ////this is temporary for visit, need to support other than quads
        ////break;
    //}
    default:
    {
      return _gVoid;
    }
  }
}

RenderManager* createOptiXManager(){ return OptiXManager::singleton(); }
