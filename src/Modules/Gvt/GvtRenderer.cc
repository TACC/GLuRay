


#include "defines.h"
#include "GvtRenderer.h"
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

#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>



#include <arpa/inet.h>
#include <GL/gl.h>

//gvt
//
// Simple gravit application.
// Load some geometry and render it.
//
#include <gvt/render/RenderContext.h>
#include <gvt/render/Types.h>
#include <vector>
#include <algorithm>
#include <set>
#include <gvt/core/mpi/Wrapper.h>
#include <gvt/core/Math.h>
#include <gvt/render/data/Dataset.h>
#include <gvt/render/data/Domains.h>
#include <gvt/render/Schedulers.h>
#include <gvt/render/adapter/manta/Wrapper.h>
//#include <gvt/render/adapter/optix/Wrapper.h>
#include <gvt/render/algorithm/Tracers.h>
#include <gvt/render/data/scene/gvtCamera.h>
#include <gvt/render/data/scene/Image.h>
#include <gvt/render/data/Primitives.h>

#include <iostream>

using namespace std;
using namespace gvt::render;
using namespace gvt::core::math;
using namespace gvt::core::mpi;
using namespace gvt::render::data::scene;
using namespace gvt::render::schedule;
using namespace gvt::render::data::primitives;
using namespace gvt::render::adapter::manta::data::domain;
//using namespace gvt::render::adapter::optix::data::domain;

//gvt

using namespace glr;

   GvtRenderer* GvtRenderer::_singleton = NULL;

   GvtRenderer* GvtRenderer::singleton()
   {
    if (!_singleton)
      _singleton = new GvtRenderer();
    return _singleton;
  }


  GvtRenderer::GvtRenderer()
  :Renderer()
  {
    DEBUG("");
    initialized=false;
    printf("%s::%s\n",typeid(*this).name(),__FUNCTION__);
    _framebuffer.format = "RGBA8";

    _gVoid = new GeometryGeneratorVoid();
    _gTriangle = new GeometryGeneratorVoid();
    _gTriangleStrip = new GeometryGeneratorVoid();
    _gQuads = new GeometryGeneratorVoid();
    _gQuadStrip = new GeometryGeneratorVoid();
    _gLines = new GeometryGeneratorVoid();
    _gLineStrip= new GeometryGeneratorVoid();
    _gPoints = new GeometryGeneratorVoid();

    _currentRenderer = "obj";
//    renList.clear();
    
    
    MPI_Init(NULL,NULL);

  }

  GvtRenderer::~GvtRenderer()
  {
  }

  void GvtRenderer::updateLights()
  {
}

Renderable* GvtRenderer::createRenderable(GeometryGenerator* gen)
{
//  GeometryGeneratorVoid* mg = dynamic_cast<GeometryGeneratorVoid*>(gen);
//  assert(mg);
  return new GvtRenderable(gen);
}

void GvtRenderer::updateMaterial()
{
//  updateMaterial(&o_current_material, gl_material);
}

//void GvtRenderer::updateMaterial(OSPMaterial *matp, const GLMaterial &glmat)
//{
//  if (!initialized)
//    return;
//
//  GLMaterial m = glmat;
//  //m.diffuse = Color(RGB(1.0, 0.713726, .21569)); // hardcode mat for debugging
//  m.specular = Manta::Color(RGB(.1, .1, .1));
//  m.ambient = Manta::Color(RGB(0, 0, 0));
//  m.shiny = 100;
//
//}

void GvtRenderer::useShadows(bool st)
{
  if(!initialized)
    return;
}

void GvtRenderer::setSize(int w, int h)
{
  if (!initialized)
    return;
  if (initialized && (w != _width || h != _height))
  {
    _width = w; _height = h;
    updateCamera();
  }
}

// struct networkSetupInfo
// {
//   std::string hostname;
//   unsigned int port;
// };


void GvtRenderer::init()
{
  if (initialized)
    return;
  initialized=true;

  _width = _height = 0;
  setSize(params.width,params.height);
  
  updateBackground();
  updateCamera();

  rendering = true;

  _rank = -1;
  //lights = new LightSet();
  gl_lights[0].diffuse = Manta::Color(RGB(1,1,1));
  gl_lights[0].specular = Manta::Color(RGB(1,1,1));
  gl_lights[0].pos = Manta::Vector(0,0,1);
  gl_lights[0].w = 0;
  updateLights();
  setColor(current_color.color[0], current_color.color[2], current_color.color[3], current_color.a);
  updateMaterial();
  //  current_material= new Phong(Color(RGBColor(1,1,1)),
  //			      Color(RGBColor(.6,.6,.6)), 32, (ColorComponent)params.reflectivity);
  //current_material = new AmbientOcclusion(current_material, 100.0,20);
  current_normal = Manta::Vector(0,1,0);
  current_transform.initWithIdentity();
  current_bgcolor = params.bgcolor;
  //  background = new ConstantBackground(current_bgcolor.color);
  //camera = new PinholeCamera(params.camera_eye, params.camera_dir, params.camera_up, params.camera_hfov, params.camera_vfov);
  updateBackground();
  updateCamera();
  if (!current_scene)
    current_scene = new Scene();
  if (!next_scene)
    next_scene = new Scene();

  cout << "initialization done\n";
  initialized = true;
}

void GvtRenderer::setNumSamples(int,int,int samples)
{
    if (!initialized)
        return;
}

void GvtRenderer::setNumThreads(int t)
{
}

void GvtRenderer::reloadRenderer()
{
}

// Switch to the correct ospray renderer if num_ao_samples has changed
void GvtRenderer::updateRenderer()
{
}



size_t GvtRenderer::generateNID()
{
  return 0;
  // return ++_nid_counter;
}

Renderable* GvtRenderer::getRenderable(size_t nid)
{
  return _map_renderables[nid];
}

void* GvtRenderer::renderLoop(void* t)
{
}

void GvtRenderer::internalRender()
{
}


void GvtRenderer::render()
{
  if (!initialized)
    return;
  if (next_scene->instances.size() == 0)
    return;
  _frameNumber++;
  //if (rendered && params.accumulate)
  //displayFrame();
  rendered = true;
  next_scene->instances.resize(0);


}

void GvtRenderer::syncInstances()
{}

void GvtRenderer::updateCamera()
{
  if (!initialized)
    return;
  GLuRayRenderParameters& p = params;
  float angle = p.camera_vfov;
  float aspectRatio = float(_width)/float(_height);
  float camRadius = 0.0f;
  if (p.camera != "pinhole")
    camRadius = p.aperture;
  if (camRadius == 0.0f)
  {
  }
  else
  {
  }
}

void GvtRenderer::updateBackground()
{
  if (!initialized)
    return;
}

void GvtRenderer::addInstance(Renderable* ren)
{
  if (!initialized)
    return;
  if (!ren->isBuilt())
  {
    std::cerr << "addInstance: renderable not build by rendermanager\n";
    return;
  }
  next_scene->instances.push_back(GRInstance(ren, current_transform));
}

void GvtRenderer::addRenderable(Renderable* ren)
{
  if (!initialized)
    return;
  GvtRenderable* oren = dynamic_cast<GvtRenderable*>(ren);
  if (!oren)
  {
    printf("error: GvtRenderer::addRenderable wrong renderable type\n");
    return;
  }

//  renList.push_back(oren);

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
  
  
  //
  //	our friend the cone.
  //
  Point4f points[7];
  points[0] = Point4f(0.5,0.0,0.0,1.0);
  points[1] = Point4f(-0.5,0.5,0.0,1.0);
  points[2] = Point4f(-0.5,0.25,0.433013,1.0);
  points[3] = Point4f(-0.5,-0.25,0.43013,1.0);
  points[4] = Point4f(-0.5,-0.5,0.0,1.0);
  points[5] = Point4f(-0.5,-0.25,-0.433013,1.0);
  points[6] = Point4f(-0.5,0.25,-0.433013,1.0);
  //
  //	build a mesh object from cone geometry.
  //
  gvt::render::data::primitives::Mesh* objMesh = new gvt::render::data::primitives::Mesh(new Lambert(Vector4f(0.5,0.5,0.5,1.0)));
  objMesh->addVertex(points[0]);
  objMesh->addVertex(points[1]);
  objMesh->addVertex(points[2]);
  objMesh->addVertex(points[3]);
  objMesh->addVertex(points[4]);
  objMesh->addVertex(points[5]);
  objMesh->addVertex(points[6]);
  
  objMesh->addFace(1,2,3);
  objMesh->addFace(1,3,4);
  objMesh->addFace(1,4,5);
  objMesh->addFace(1,5,6);
  objMesh->addFace(1,6,7);
  objMesh->addFace(1,7,2);
  
  gvt::render::data::Dataset scene;
  
  objMesh->generateNormals();
  int argc=1;
   char* argv[] = {"gluray\0","\0"};
  gvt::render::data::domain::GeometryDomain* domain = new gvt::render::data::domain::GeometryDomain(objMesh);
  scene.domainSet.push_back(domain);
  
  Vector4f   pos(1.0,1.0,1.0,0.0);
  Vector4f color(1.0,1.0,1.0,0.0);
  vector<gvt::render::data::scene::Light*> lightset;
  lightset.push_back(new gvt::render::data::scene::PointLight(pos,color));
  domain->setLights(lightset);
  //
  //	need a camera... using gvtCamera instead of default camera.... because I know how it works.
  //
  gvtPerspectiveCamera mycamera;
  Point4f cameraposition(1.0,1.0,1.0,1.0);
  Point4f focus(0.0,0.0,0.0,1.0);
  float fov = 45.0 * M_PI/180.0;
  Vector4f up(0.0,1.0,0.0,0.0);
  mycamera.lookAt(cameraposition,focus,up);
  mycamera.setFOV(fov);
  mycamera.setFilmsize(512,512);
  //
  //	Create an object to hold the image and a pointer to the raw image data.
  //
  gvt::render::data::scene::Image myimage(mycamera.getFilmSizeWidth(),mycamera.getFilmSizeHeight(),"cone");
  unsigned char *imagebuffer = myimage.GetBuffer();
  //
  //	Attributes class contains information used by tracer to generate image.
  //	This will be replaced by the Context in the future.
  //
  // RenderContext::CreateContext() ;
  gvt::render::RenderContext *cntxt = gvt::render::RenderContext::instance();
  
  if(cntxt == NULL) {
    std::cout << "Something went wrong" << std::endl;
    exit(0);
  }
  
  gvt::core::DBNodeH root = cntxt->getRootNode();
  gvt::core::Variant V;
  gvt::core::DBNodeH camnode,filmnode,datanode;
  
  // camera
  camnode = cntxt->createNodeFromType("Camera","conecam",root.UUID());
  V = mycamera.getEyePoint();
  camnode["eyePoint"] = V;
  V = mycamera.getFocalPoint();
  camnode["focus"] = V;
  V = mycamera.getUpVector();
  camnode["upVector"] = V;
  // film
  filmnode = cntxt->createNodeFromType("Film","conefilm",root.UUID());
  V = mycamera.getFilmSizeWidth();
  filmnode["width"] = V;
  V = mycamera.getFilmSizeHeight();
  filmnode["height"] = V;
  // dataset
  datanode = cntxt->createNodeFromType("Dataset","coneset",root.UUID());
  V = gvt::render::scheduler::Image;
  datanode["schedule"] = V;
  V = new gvt::render::data::Dataset();
  datanode["Dataset_Pointer"] = V;
  V = gvt::render::adapter::Manta;
  datanode["render_type"] = V;
  
		std::cout << "this should print the tree " << std::endl;
  cntxt->database()->printTree(root.UUID(),10,std::cout);
  
  if(gvt::core::variant_toInteger(V) == gvt::render::adapter::Manta) {
    gvt::core::variant_toDatasetPointer(root["Dataset"]["Dataset_Pointer"].value())->addDomain(new MantaDomain(domain));
  }
  V = Vector3f(1.,1.,1.);
  datanode["topology"] = V;
  V = gvt::render::accelerator::BVH;
  datanode["accel_type"] = V;
  V = domain->getMesh();
  datanode["Mesh_Pointer"] = V;
  
  int width = gvt::core::variant_toInteger(root["Film"]["width"].value());
  std::cout << "this should print the tree " << width << std::endl;
  cntxt->database()->printTree(root.UUID(),10,std::cout);
  //
  //	Render it....
  //
  mycamera.AllocateCameraRays();
  mycamera.generateRays();
  int stype = gvt::core::variant_toInteger(root["Dataset"]["schedule"].value());
  if(stype ==gvt::render::scheduler::Image) {
    gvt::render::algorithm::Tracer<ImageScheduler>(mycamera.rays,myimage)();
  } else if(stype == gvt::render::scheduler::Domain) {
    gvt::render::algorithm::Tracer<DomainScheduler>(mycamera.rays,myimage)();
  }
  
  _framebuffer.byteAlign = 1;
  _framebuffer.width = 512;
  _framebuffer.height = 512;
  _framebuffer.data = (void*)imagebuffer;
  _framebuffer.format = "RGBA8";

  // vertices.resize(numPositions);
  for(size_t i = 0; i < numPositions; i++)
  {
//    vertices[i] = ospray::vec3fa(mesh->vertices[i].x(), mesh->vertices[i].y(),  mesh->vertices[i].z());
  }

}

void GvtRenderer::deleteRenderable(Renderable* ren)
{
  if (!initialized)
    return;

  GvtRenderable* oren = dynamic_cast<GvtRenderable*>(ren);
  if (!oren)
  {
    cout << "error: GvtRenderer::deleteRenderable: wrong renderable type" << endl;
    return;
  }

  //ospRemoveGeometry(oren->_data->ospModel, oren->_data->ospMesh);
  //ospRelease(oren->_data->mat);

//  for(int i=0; i<renList.size(); i++) {
//    if(renList[i] == ren) {
//      renList.erase(renList.begin() + i);
//      break;
//    }
//  }
}

void GvtRenderer::addTexture(int handle, int target, int level, int internalFormat, int width, int height, int border, int format, int type, void* data)
{
  if (!initialized)
    return;
}

void GvtRenderer::deleteTexture(int handle)
{
  if (!initialized)
    return;
}

GeometryGenerator* GvtRenderer::getGeometryGenerator(int type)
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
    case GL_POINTS:
    {
      return _gPoints;
    }
    case GL_LINES:
    {
      return _gLines;
    }
    case GL_LINE_STRIP:
    {
      return _gLineStrip;
    }
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

glr::Renderer* createGvtRenderer(){ return GvtRenderer::singleton(); }
