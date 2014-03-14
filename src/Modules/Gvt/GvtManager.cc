
#include <UseMPI.h>
#ifdef USE_MPI
#include <Engine/Display/NullDisplay.h>
#include <Engine/LoadBalancers/MPI_LoadBalancer.h>
#include <Engine/ImageTraversers/MPI_ImageTraverser.h>
#include <mpi.h>
#endif

#include "defines.h"
#include "GvtManager.h"
//#include <X11/Xlib.h>
//#include <X11/Xutil.h>

//#include "../gl_functions.h"
#include "CDTimer.h" 
#include "GvtScene.h"
#include "GvtRenderable.h"
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


GvtManager* GvtManager::_singleton = NULL;

GvtManager* GvtManager::singleton()
{
  if (!_singleton)
    _singleton = new GvtManager();
  return _singleton;
}

  GvtManager::GvtManager()
:RenderManager(), current_scene(NULL), next_scene(NULL),
  _nid_counter(0), _depth(false), _width(512), _height(512), _frameNumber(0), _realFrameNumber(0)
{

}

GvtManager::~GvtManager()
{

}

void GvtManager::updateLights()
{
  
}

Renderable* GvtManager::createRenderable(GeometryGenerator* gen)
{
  GvtGeometryGenerator* mg = dynamic_cast<GvtGeometryGenerator*>(gen);
  assert(mg);
  return new GvtRenderable(mg);
}

void  GvtManager::updateMaterial()
{
  
}

void GvtManager::useShadows(bool st)
{
}

void GvtManager::setSize(int w, int h)
{

}


void GvtManager::init()
{
  
}

//TODO: updating pixelsampler mid flight crashes manta
void GvtManager::setNumSamples(int,int,int samples)
{

}

void GvtManager::setNumThreads(int t)
{
}



size_t GvtManager::generateNID()
{
  return ++_nid_counter;
}

Renderable* GvtManager::getRenderable(size_t nid)
{
  return _map_renderables[nid];
}

void GvtManager::internalRender()
{

}


void GvtManager::render()
{
  


}


void GvtManager::displayFrame()
{
 
}

void GvtManager::syncInstances()
{}

void GvtManager::updateCamera()
{
  
}

void GvtManager::updateBackground()
{

}

void GvtManager::addInstance(Renderable* ren)
{
  if (!rendering)
    return;
  if (!ren->isBuilt())
    return;
  next_scene->instances.push_back(GRInstance(ren, current_transform));
}

void GvtManager::addRenderable(Renderable* ren)
{
  
}

void GvtManager::deleteRenderable(Renderable* ren)
{

}

void GvtManager::exportOBJ(EScene* scene)
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

void GvtManager::addTexture(int handle, int target, int level, int internalFormat, int width, int height, int border, int format, int type, void* data)
{
 
}

void GvtManager::deleteTexture(int handle)
{

}

GeometryGenerator* GvtManager::getGeometryGenerator(int type)
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

RenderManager* createGvtManager(){ return GvtManager::singleton(); }
