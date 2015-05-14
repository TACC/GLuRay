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


#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H
#include "defines.h"
#include "Work.h"
#include "GLuRayRenderParameters.h"
#include "GeometryGenerator.h"
#include "Renderable.h"
#include "GLTypes.h"
#include "Renderer.h"

#include <Model/Lights/DirectionalLight.h>
#include <Interface/LightSet.h>
#include <Interface/MantaInterface.h>
#include <Interface/Object.h>
#include <Interface/Camera.h>
#include <Engine/Factory/Factory.h>
#include <Engine/Factory/Create.h>
#include <Engine/Display/SyncDisplay.h>
#include <Model/Materials/Volume.h>
#include <Core/Thread/Barrier.h>
#include <Core/Thread/CrowdMonitor.h>
#include <Core/Thread/Mutex.h>
#include <Core/Thread/Semaphore.h>


#include <queue>
#include <stack>
// using namespace Manta;

namespace glr
{

//class Scene;
class RenderManager
{
public:
  RenderManager() ;
  ~RenderManager() {}
  virtual void setBGColor(float r, float g, float b, float a)
  {
    _renderer->setBGColor(r,g,b,a);
  }
  virtual void setColor(float r, float g, float b, float a) 
    {_renderer->setColor(r,g,b,a);}
  virtual GLMaterial& getCurrentMaterial() { return _renderer->getCurrentMaterial(); }
  virtual void enableGLMaterial(bool st) { _renderer->enableGLMaterial(st); }
  virtual void updateMaterial() {_renderer->updateMaterial();}
  virtual void updateLights() {_renderer->updateLights();}
  //virtual void addScene(Scene* scene)=0;
  virtual void addWork(Work* work) {  _renderer->addWork(work); }

  virtual void render() {_renderer->render();}
  virtual void init() {_renderer->init();}

  virtual void setNumSamples(int samples) {_renderer->setNumSamples(0,1,samples);}
  virtual void setNumThreads(int t) {_renderer->setNumThreads(t);}

  virtual void setSize(int w, int h) {_renderer->setSize(w,h);}
  void setNearFar(double near, double far) { _renderer->setNearFar(near,far);}
  virtual void setRenderParametersString(string in, bool need_relaunch = true)
  {_renderer->setRenderParametersString(in,need_relaunch);}
  virtual void setRenderParameters(GLuRayRenderParameters& rp, bool need_relaunch = true)
  {_renderer->setRenderParameters(rp,need_relaunch);}
  GLuRayRenderParameters& getRenderParameters() { return _renderer->params; }
  virtual void pushRenderParameters() { _renderer->pushRenderParameters();}
  virtual void popRenderParameters() { _renderer->popRenderParameters();}

  virtual void useShadows(bool st) { _renderer->useShadows(st);}
  virtual void updateBackground() {_renderer->updateBackground();}
  virtual void updateCamera() {_renderer->updateCamera();}
  virtual void enableLighting(bool st) {_renderer->enableLighting(st);}
  virtual void enableLight(int light, bool st) {_renderer->enableLight(light,st);}
  virtual GLLight getLight(int num) { return _renderer->getLight(num); }
  virtual void setLight(int num, const GLLight& l ) { _renderer->setLight(num,l); }
  virtual bool getUsePerVertexColors() {return _renderer->getUsePerVertexColors(); }
  virtual void setUsePerVertexColors(bool st) {_renderer->setUsePerVertexColors(st);}
  virtual Manta::RGBAColor getCurrentColor() { return _renderer->getCurrentColor(); }
  virtual GeometryGenerator* getGeometryGenerator(int type) {return _renderer->getGeometryGenerator(type);}
  virtual Renderable* createRenderable(GeometryGenerator* gen) {return _renderer->createRenderable(gen);}
  virtual void addRenderable(Renderable* ren) {_renderer->addRenderable(ren);}
  virtual void deleteRenderable(Renderable* ren) {_renderer->deleteRenderable(ren);}
  virtual void addTexture(int handle, int target, int level, int internalFormat, int width, int height, int border, int format, int type, void* data) 
  {_renderer->addTexture(handle,target,level,internalFormat,width,height,border,format,type,data);}
  virtual void deleteTexture(int handle) {_renderer->deleteTexture(handle);}
  virtual void addInstance(Renderable* ren) {_renderer->addInstance(ren);}
  Renderable* getCurrentRenderable() { return _renderer->getCurrentRenderable(); }
  void setCurrentRenderable(Renderable* r) { _renderer->setCurrentRenderable(r); }
  Manta::AffineTransform& getCurrentTransform() { return _renderer->getCurrentTransform(); }
  void setWindowID(unsigned long id) { window_id = id;}

  /*inline*/ void lock(const int mutex)
  {
    _renderer->lock(mutex);
  }
  /*inline*/ void unlock(const int mutex)
  {
    _renderer->unlock(mutex);
  }

  protected:

  std::queue<Work*> accel_work_queue;
  bool kill_accel_threads;

  void initClient();
  static void* clientLoop(void* t);

  Manta::RGBAColor current_color;
  Manta::Material* current_material;
  Manta::AffineTransform current_transform;
  stack<Manta::AffineTransform> transform_stack;
  Manta::RGBAColor current_bgcolor;
  Renderable* current_renderable;
  Manta::Vector current_normal;
  bool auto_camera;
  int num_threads;
  int window_id;
  int channel_id;
  bool rendering;
  GLuRayRenderParameters params;
  stack<GLuRayRenderParameters> render_parameters_stack;
  bool print_build_time;
  bool relaunch;
  bool client_running;
  bool render_once;
  bool usePerVertexColors;
  std::vector<GLLight> gl_lights;
  GLMaterial gl_material;
  bool use_gl_lights;
  bool use_gl_material; //use material or color?
  bool lights_dirty;
  bool dirty_renderParams;
  string new_renderParamsString;
  bool frame_lag;
  int rank;
  bool dirty_sampleGenerator;
  bool initialized;
  double _zFar, _zNear;
  vector<Manta::Mutex*> _mutexes;
  Renderer* _renderer;
};

}

#endif

