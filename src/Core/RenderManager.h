#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H
#include "defines.h"
#include "Work.h"
#include "GLuRayRenderParameters.h"
#include "GeometryGenerator.h"
#include "Renderable.h"
#include "GLTypes.h"

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
using namespace Manta;


//class Scene;
class RenderManager
{
public:
  RenderManager() ;
  ~RenderManager() {}
  virtual void setBGColor(float r, float g, float b, float a)
  {
    printf("setBGColor\n");
    Color color = Color(RGBColor(r,g,b));
	  if ((params.env_map == "" || params.env_map == "none") && (current_bgcolor.color[0] != color[0] || current_bgcolor.color[1] != color[1] || current_bgcolor.color[2] != color[2] || current_bgcolor.a != a))
	  {
		current_bgcolor.color = color;
		current_bgcolor.a = a;
		params.bgcolor = current_bgcolor;
		updateBackground();
	  }
  }
  virtual void setColor(float r, float g, float b, float a) {current_color = RGBAColor(r,g,b,a);}
  virtual GLMaterial& getCurrentMaterial() { return gl_material; }
  virtual void enableGLMaterial(bool st) { use_gl_material = st; }
  virtual void updateMaterial() = 0;
  virtual void updateLights() = 0;
  //virtual void addScene(Scene* scene)=0;
  virtual void addWork(Work* work) {  accel_work_queue.push(work); }

  virtual void render() = 0;
  virtual void init() = 0;

  virtual void setNumSamples(int,int,int samples) = 0;
  virtual void setNumThreads(int t) = 0;

  virtual void setSize(int w, int h)=0;
  void setNearFar(double near, double far) { _zNear = near; _zFar = far; }
  virtual void setRenderParametersString(string in, bool need_relaunch = true);
  virtual void setRenderParameters(GLuRayRenderParameters& rp, bool need_relaunch = true);
  virtual void pushRenderParameters();
  virtual void popRenderParameters();

  virtual void useShadows(bool st) = 0;
  virtual void updateBackground() = 0;
  virtual void updateCamera()=0;
  virtual void enableLighting(bool st) { use_gl_lights = st; lights_dirty = true; }
  virtual void enableLight(int light, bool st) { gl_lights[light].enabled = st; lights_dirty = true; }
  virtual GLLight getLight(int num) { return gl_lights[num]; }
  virtual void setLight(int num, const GLLight& l ) { gl_lights.at(num) = l; lights_dirty = true; }
  virtual bool getUsePerVertexColors() {return usePerVertexColors; }
  virtual void setUsePerVertexColors(bool st) {usePerVertexColors = st;}
  virtual RGBAColor getCurrentColor() { return current_color; }
  virtual GeometryGenerator* getGeometryGenerator(int type) = 0;
  virtual Renderable* createRenderable(GeometryGenerator* gen) = 0;
  virtual void addRenderable(Renderable* ren) = 0;
  virtual void deleteRenderable(Renderable* ren) = 0;
  virtual void addTexture(int handle, int target, int level, int internalFormat, int width, int height, int border, int format, int type, void* data) {}
  virtual void deleteTexture(int handle) {}
  virtual void addInstance(Renderable* ren);
  Renderable* getCurrentRenderable() { return current_renderable; }
  void setCurrentRenderable(Renderable* r) { current_renderable = r; }
  AffineTransform& getCurrentTransform() { return current_transform; }

  /*inline*/ void lock(const int mutex)
  {
    _mutexes[mutex]->lock();
  }
  /*inline*/ void unlock(const int mutex)
  {
    _mutexes[mutex]->unlock();
  }

  //protected:

  std::queue<Work*> accel_work_queue;
  bool kill_accel_threads;

  static void* clientLoop(void* t);

  RGBAColor current_color;
  Material* current_material;
  AffineTransform current_transform;
  stack<AffineTransform> transform_stack;
  RGBAColor current_bgcolor;
  Renderable* current_renderable;
  Vector current_normal;
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
  vector<Mutex*> _mutexes;
};

RenderManager* createRenderManager();

#endif

