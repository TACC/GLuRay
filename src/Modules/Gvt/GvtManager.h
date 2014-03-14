#ifndef GvtManager_H
#define GvtManager_H
#include <queue>
#include <stack>
#include "defines.h"
#include "RenderManager.h"
#include "Work.h"
#include "GLuRayRenderParameters.h"
//#include "ERenderable.h"


using namespace Manta;

class GvtScene;
class GvtRenderable;
class GvtGeometryGenerator;
class OBJScene;
class Scene;
//class Display;
//class Window;
/*namespace rivl
  {
//class vec2ui;
class FrameBuffer;
class Renderer;
class Camera;
}*/

class GvtManager : public RenderManager
{
  public:

    GvtManager() ;
    ~GvtManager();

/*
 *Inherited functions
 */

    GLMaterial& getCurrentMaterial() { return gl_material; }
    virtual void updateMaterial();
    //virtual void updateScene();
    virtual void render();
    virtual void init();
    virtual void updateLights();

    virtual Renderable* createRenderable(GeometryGenerator* gen);
    //adds renderable to next scene with current transform
    virtual void addInstance(Renderable* ren);
    virtual void addRenderable(Renderable* ren);
    virtual void deleteRenderable(Renderable* ren);
    virtual void addTexture(int handle, int target, int level, int internalFormat, int width, int height, int border, int format, int type, void* data);
    virtual void deleteTexture(int handle);
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

    /*
     *new functions
     */

    void displayCallback(int proc, int numProcs, bool& changed);

    void syncInstances();
    void displayFrame();
    static void* renderLoop(void* t);
    void internalRender();

    void exportOBJ(EScene* scene);

    //
    //  Variables
    //

    GvtGeometryGenerator* _gVoid, *_gTriangle, *_gTriangleStrip, *_gQuads, *_gQuadStrip, *_gLines, *_gLineStrip;
    //  static void* clientLoop(void* t);
    GvtScene *current_scene;
    GvtScene *next_scene;
    queue<GvtScene*> scene_queue;
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
    int _width, _height;
    std::string _format;
    bool _resetAccumulation;
    bool rendered;
    int _frameNumber;
    int _realFrameNumber;  //corrected by env param


    std::string _scene;
    std::string _accel;
    std::string _builder;
    std::string _traverser;

    //rivl::vec2ui*       windowSize;
    //rivl::FrameBuffer *fb;
    //rivl::Renderer    *renderer;


    Display* _xDisplay;
    Window* _xWin;

    OBJScene* _objScene;


    static GvtManager* singleton();
    static GvtManager* _singleton;
};
RenderManager* createGvtManager();

#endif
