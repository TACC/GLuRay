#ifndef RIVLMANAGER_H
#define RIVLMANAGER_H
#include <queue>
#include <stack>
#include "defines.h"
#include "RenderManager.h"
#include "Work.h"
#include "GLuRayRenderParameters.h"
#include "RRenderable.h"

using namespace Manta;

class RScene;
class RRenderable;
/*namespace rivl
{
//class vec2ui;
class FrameBuffer;
class Renderer;
class Camera;
}*/

class RIVLManager : public RenderManager
{
  public:

  struct NRenderable
  {
    size_t nid;
    size_t numPrims;
    size_t numVerts;
    //TODO; material properties, nonmeshes etc
  };

  struct NInstance
  {
    size_t nid;
    AffineTransform transform;
  };

    RIVLManager() ;
    ~RIVLManager();
    GLMaterial& getCurrentMaterial() { return gl_material; }
    virtual void updateMaterial();
    //virtual void updateScene();
    virtual void render();
    virtual void init();
    virtual void updateLights();

    virtual Renderable* createRenderable(GeometryGenerator* gen)
    {
      RGeometryGenerator* mg = dynamic_cast<RGeometryGenerator*>(gen);
      assert(mg);
      return new RRenderable(mg);
    }
 //   virtual void addScene(Scene* scene) {scene_queue.push(scene);}

    //adds renderable to next scene with current transform
    virtual void addInstance(Renderable* ren);
    virtual void addRenderable(Renderable* ren);
    virtual GeometryGenerator* getGeometryGenerator(int type);
    void setNumSamples(int,int,int samples);
    void setNumThreads(int t);
    void setNumThreadsCallback(int,int);
    size_t generateNID();
    Renderable* getRenderable(size_t nid);

    void setSize(int w, int h);

    void useShadows(bool st);
    void updateBackground();
    void updateCamera();
    void setCameraCallback(int,int);


    bool kill_accel_threads;
    void buildAccelerationCallback(int,int,bool&);
    void displayCallback(int proc, int numProcs, bool& changed);

    RGeometryGenerator* _gVoid, *_gTriangle, *_gTriangleStrip, *_gQuads, *_gQuadStrip, *_gLines, *_gLineStrip;

    void syncInstances();
    void displayFrame();

  //  static void* clientLoop(void* t);
  RScene *current_scene;
  RScene *next_scene;
  queue<RScene*> scene_queue;
  map<int, Renderable*> _map_renderables;
  vector<Renderable*> _newRenderables; //new renderables added to be synced over mpi

    SyncDisplay* sync_display;
    Mutex accel_mutex, general_mutex, params_mutex;
    vector<float> depth_data;
    vector<float> rgba_data;
    vector<char> rgb_data;
    bool frame_lag;
    int _rank;
    int _numProcs;
    void relaunchCallback(int,int);
    size_t _nid_counter;
    bool _depth;

//rivl::vec2ui*       windowSize;
//rivl::FrameBuffer *fb;
//rivl::Renderer    *renderer;
//rivl::Camera      *camera;

    static RIVLManager* singleton();
    static RIVLManager* _singleton;
};

RenderManager* createRIVLManager();

#endif
