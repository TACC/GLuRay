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

#ifndef MANTAMANAGER_H
#define MANTAMANAGER_H
#include <queue>
#include <stack>
#include "defines.h"
#include "RenderManager.h"
#include "GLTypes.h"

#include <Model/Lights/DirectionalLight.h>
#include <Interface/LightSet.h>
#include <Interface/MantaInterface.h>
#include <Interface/Scene.h>
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


#include "Work.h"
#include "GLuRayRenderParameters.h"
#include "MRenderable.h"
using namespace Manta;

class MScene;
class MRenderable;

class MantaManager : public RenderManager
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

    MantaManager() ;
    ~MantaManager();
    GLMaterial& getCurrentMaterial() { return gl_material; }
    virtual void updateMaterial();
    //virtual void updateScene();
    virtual void render();
    virtual void init();
    virtual void updateLights();

    Manta::LightSet* getLights();
    MantaInterface* getEngine();
    Manta::Camera* getCamera() { return camera; }

    virtual Renderable* createRenderable(GeometryGenerator* gen)
    {
      MGeometryGenerator* mg = dynamic_cast<MGeometryGenerator*>(gen);
      assert(mg);
      return new MRenderable(mg);
    }
    void addScene(MScene* scene) {scene_queue.push(scene);}

    //adds renderable to next scene with current transform
    virtual void addInstance(Renderable* ren);
    virtual void addRenderable(Renderable* ren);
    virtual void deleteRenderable(Renderable* ren);
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
    void updateRenderer();


    bool kill_accel_threads;
    void buildAccelerationCallback(int,int,bool&);
    void displayCallback(int proc, int numProcs, bool& changed);

    MGeometryGenerator* _gVoid, *_gTriangle, *_gTriangleStrip, *_gQuads, *_gQuadStrip, *_gLines, *_gLineStrip;

    template<class T> void kill(T* o)
    {
      rtrt->addOneShotCallback(MantaInterface::Relative, 1, Callback::create(this,&MantaManager::kill_callback<T>, o));
    }
    template<class T> void kill_callback(int, int, T* o)
    {
      delete o;
    }

    void syncInstances();
    void displayFrame();

  //  static void* clientLoop(void* t);
  MScene *current_scene;
  MScene *next_scene;
  queue<MScene*> scene_queue;
  map<int, Renderable*> _map_renderables;
  vector<Renderable*> _newRenderables; //new renderables added to be synced over mpi

    Material* current_material;
    MantaInterface* rtrt;
    Factory *factory;
    SyncDisplay* sync_display;
    LightSet* lights;
    Background* background;
    Camera* camera;
    Mutex accel_mutex, general_mutex, params_mutex;
    Semaphore ready, done;
    Barrier accel_barrier;
    vector<CallbackHandle*> callback_handles;
    vector<float> depth_data;
    vector<float> rgba_data;
    vector<char> rgb_data;
    bool frame_lag;
    int _rank;
    int _numProcs;
    void relaunchCallback(int,int);
    size_t _nid_counter;
    bool _depth;

    static MantaManager* singleton();
    static MantaManager* _singleton;
};


#endif
