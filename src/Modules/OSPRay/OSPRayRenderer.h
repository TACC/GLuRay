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

#ifndef OSPRayRenderer_H
#define OSPRayRenderer_H
 //
//ospray
//
#include "ospray/ospray.h"

#include <queue>
#include <stack>
#include "defines.h"
#include "Renderer.h"
#include "Work.h"
#include "GLuRayRenderParameters.h"
//#include "ERenderable.h"



/*
 *Embreee
 */
// #include "sys/platform.h"
// #include "sys/ref.h"
// #include "lexers/streamfilters.h"
// #include "lexers/parsestream.h"
// //#include "../tutorials/glutdisplay.h"
// #include "../tutorial_host/tutorials_host.h"

// #include "sys/filename.h"
// #include "image/image.h"
// #include "device/loaders/loaders.h"
// //#include "glutdisplay.h"
// #include "regression.h"
// #include "math/affinespace.h"
// #include "math/color.h"
// #include "math/vec2.h"
// #include "math/vec3.h"
// #include "math/vec4.h"
// #include "device/handle.h"

// #include "sys/platform.h"
// #include "sys/ref.h"
// #include "camera.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>




/*
 *
 */

using namespace Manta;

class OScene;
class ORenderable;
class OGeometryGenerator;
// class OBJScene;
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

namespace glr
{

class OSPRayRenderer : public Renderer
{
  public:

    OSPRayRenderer() ;
    ~OSPRayRenderer();

/*
 *Inherited functions
 */

    GLMaterial& getCurrentMaterial() { return gl_material; }
    virtual void updateMaterial();
    void updateMaterial(OSPMaterial *matp, const GLMaterial &glmat);
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
    void updateRenderer();
    void reloadRenderer();

    /*
     *new functions
     */

    void displayCallback(int proc, int numProcs, bool& changed);

    void syncInstances();
    void displayFrame();
    static void* renderLoop(void* t);
    void internalRender();

    // void exportOBJ(EScene* scene);

    //
    //  Variables
    //

    OGeometryGenerator* _gVoid, *_gTriangle, *_gTriangleStrip, *_gQuads, *_gQuadStrip, *_gLines, *_gLineStrip;
    // //  static void* clientLoop(void* t);
    OScene *current_scene;
    OScene *next_scene;
    // queue<EScene*> scene_queue;
    map<int, Renderable*> _map_renderables;
    // vector<Renderable*> _newRenderables; //new renderables added to be synced over mpi

    // SyncDisplay* sync_display;
    // Mutex accel_mutex, general_mutex, params_mutex;
    // vector<float> depth_data;
    // vector<float> rgba_data;
    // vector<char> rgb_data;
    // bool frame_lag;
    // int _rank;
    // int _numProcs;
    // void relaunchCallback(int,int);
    size_t _nid_counter;
    bool _depth;
    int _width, _height;
    std::string _format;
    // bool _resetAccumulation;
    bool rendered;
    int _frameNumber;
    int _realFrameNumber;  //corrected by env param
    OSPMaterial o_current_material;

    // embree::Handle<embree::Device::RTCamera> _camera;
    // embree::Handle<embree::Device::RTMaterial> g_current_material;
    // embree::Handle<embree::Device::RTRenderer> _renderer;
    // embree::Handle<embree::Device::RTToneMapper> _tonemapper;
    // embree::Handle<embree::Device::RTFrameBuffer> _frameBuffer;
    // embree::Handle<embree::Device::RTImage> _backplate;
    // embree::Handle<embree::Device::RTScene> _render_scene;

    // std::string _scene;
    // std::string _accel;
    // std::string _builder;
    // std::string _traverser;

    // //rivl::vec2ui*       windowSize;
    // //rivl::FrameBuffer *fb;
    // //rivl::Renderer    *renderer;
    // //rivl::Camera      *camera;
    // Mutex embreeMutex;

    // embree::Vector3f _camPos;
    // std::vector<embree::Handle<embree::Device::RTPrimitive> > _lights;
    // std::map<int, embree::Handle<embree::Device::RTTexture>* > _textures;

    // Display* _xDisplay;
    // Window* _xWin;

    // OBJScene* _objScene;

    std::string _currentRenderer;
    std::vector<ORenderable*> renList;


    static OSPRayRenderer* singleton();
    static OSPRayRenderer* _singleton;
};
}
glr::Renderer* createOSPRayRenderer();

#endif
