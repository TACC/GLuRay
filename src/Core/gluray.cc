
#if 0
#include <Engine/Display/GLXImageDisplay.h>

#include "gluray.h"
#include <iostream>
#include <GL/gl.h>
#include <pthread.h>
#include <cassert>
#include <stack>
#include <queue>
#include <fstream>
int GLURAY_RENDER_MODE=0;   //extern in defines

void gr_init(){}
void gr_addVertex(float x, float y, float z){}
void gr_beginPrimitive(int type){}
void gr_endPrimitive(){}
void gr_render(){}
void gr_setColor(float r, float g, float b, float a){}
void gr_setColorub(unsigned char r, unsigned char g, unsigned char b, unsigned char a){}
void gr_setBackgroundColor(float r, float g, float b, float a){}
void gr_normal(float x,float y,float z){}
void gr_materialfv(int face, int pname, float* params){}
void gr_materialf(int face, int pname, float param){}
void gr_materialiv(int face, int pname, int* params){}
void gr_materiali(int face, int pname, int param){}
void gr_translate(float x, float y, float z){}
void gr_rotate(float angle, float x, float y, float z){}
void gr_scale(float x, float y, float z){}
void gr_newList(size_t list, int mode){}
void gr_endList(){}
void gr_callList(int list){}
void gr_deleteLists(GLuint list, GLsizei range){}
void gr_enableClientState(GLenum st){}
void gr_vertexPointer(GLint dim, GLenum type, GLsizei stride, const GLvoid* pointer){}
void gr_colorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer){}
void gr_drawArrays(GLenum type, GLint first, GLsizei count){}
void gr_drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices){}
void gr_drawElements_internal(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, GLint first){}
void gr_disableClientState(GLenum st){}
void gr_pushMatrix(){}
void gr_popMatrix(){}
void gr_loadIdentity(){}
void gr_viewport(int x, int y, int width, int height){}
void gr_lookAt(float ex,float ey, float ez, float lx,
		     float ly, float lz, float ux, float uy, float uz){}
void gr_makeCurrent(unsigned long winID){}
void gr_chooseVisual(XVisualInfo* info){}
void gr_matrixMode(int mode){}
void gr_multMatrixf(const float* m){}
void gr_multMatrixd(const double* m){}
void gr_loadMatrixf(const float* m){}
void gr_loadMatrixd(const double* m){}
void gr_clear(GLbitfield mask){}

void gr_light(int light, int pname, float* params){}
void gr_enable(int what){}
void gr_disable(int what){}

void gr_material(int pname, float* params){}
void gr_frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble ar){}
void gr_glTexImage1D(GLenum target, GLint level, GLint internalFormat, GLsizei width,
    GLint border, GLenum format, GLenum type, const GLvoid* data){}
void gr_glTexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height,
    GLint border, GLenum format, GLenum type, const GLvoid* data){}
void gr_finalize(){}
void gr_lock(const int num){}
void gr_unlock(const int num){}
#endif

#if 1
#include "defines.h"

#define LOGGING_ON
#include <Core/Util/Logger.h>

#include <UseMPI.h>
#ifdef USE_MPI
# include <Engine/Display/NullDisplay.h>
# include <Engine/LoadBalancers/MPI_LoadBalancer.h>
# include <Engine/ImageTraversers/MPI_ImageTraverser.h>
#include <mpi.h>
#endif


#include <unistd.h>
#include <Engine/Display/GLXImageDisplay.h>

#include "gluray.h"
#include "main.h"
#include "CDTimer.h"
#include "DirtyInstance.h"
#include "MScene.h"
//#include "GLTypes.h"
#ifdef USE_RIVL
//#include "RIVLManager.h"
#endif
#ifdef USE_EMBREE
//#include "EmbreeManager.h"
#endif
#ifdef USE_OSPRAY
//#include "OSPRayManager.h"
#endif
#include "MantaManager.h"

#include <iostream>
#include <vector>
#include <Interface/MantaInterface.h>
#include <Interface/Scene.h>
#include <Interface/Object.h>
#include <Interface/Camera.h>
#include <Model/Instances/Instance.h>
#include "common.h"


#include <GL/gl.h>


#include "MRenderable.h"


#include <pthread.h>
#include <cassert>
#include <stack>
#include <queue>
#include <fstream>


using namespace std;
using namespace Manta;


int GLURAY_RENDER_MODE;   //extern in defines

size_t numadds = 0;

#if (USE_GLURAY == 0)
#define GRCHECK() { return; }
#else
#define GRCHECK() { gr_init(); }
#endif

float poly_vert[4][3];
int num_poly_verts = 0;
size_t dl_size = 400000000;

bool autocamera = false;
bool reset_camera = true;
GLenum PRIM_TYPE = GL_POINT;
bool IN_DL = false;  //in a display list?
bool IN_IMMEDIATE = false;  //building a display list over immediate mode calls
bool support_immediate = false;  //immediate mode not supported currently, need to modify beginPrim and endPrim for that
int DL_NUM = 0;
unsigned long window_id = 0;
int num_elements = 0;
stack<AffineTransform> transform_stack;
bool needFOVCalc = true;


int matrix_mode = GL_MODELVIEW;
int resolution[2];
//vector<float> rgb_data, depth_data;
//string port = "3490";
int max_packet_size = 100;
bool rendered = true;

enum gr_MATERIALS {
  gr_PHONG,
  gr_LAMBERTIAN,
  gr_AO,
  gr_METAL
};

ThreadGroup* accelThreads;
Mutex* accelThreadsMutex;

int material = gr_PHONG;
map<std::size_t, vector<Renderable*>* > display_lists;
Renderable* __dl_renderable;
const GLvoid* __color_pointer = 0;
int __color_stride = 0;


int vertex_counter = 0, prim_counter = 0;

vector<float> vert_x;
vector<float> vert_y;
vector<float> vert_z;

static void make_stack( ReadContext &context, const vector<string> &args );
bool initialized = false;
bool rendering = false;

static int attributeListDbl[] = { GLX_RGBA, GLX_DOUBLEBUFFER, /*In case single buffering is not supported*/ GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, None };

RenderManager* rm = 0;

void gr_init()
{
#if (USE_GLURAY == 0)
  return;
#endif
  if (initialized)
    return;

  Manta::LogManager::GetSingleton()->SetEnabled(true);

  GLURAY_RENDER_MODE = ( 0
    //| GLURAY_RENDER_GLXSWAPBUFFERS
    //| GLURAY_RENDER_GLFINISH
    //| GLURAY_RENDER_GLFLUSH
    //| GLURAY_RENDER_GLREADPIXELS
    );

  string renderMode = GetVarString("GLURAY_RENDERMODE");
  if (renderMode == "")
    renderMode = "GLXSWAPBUFFERS";
  if (renderMode.find("GLXSWAPBUFFERS") != string::npos)
    GLURAY_RENDER_MODE |= GLURAY_RENDER_GLXSWAPBUFFERS;
  if (renderMode.find("GLFINISH") != string::npos)
    GLURAY_RENDER_MODE |= GLURAY_RENDER_GLFINISH;
  if (renderMode.find("GLFLUSH") != string::npos)
    GLURAY_RENDER_MODE |= GLURAY_RENDER_GLFLUSH;
  if (renderMode.find("GLREADPIXELS") != string::npos)
    GLURAY_RENDER_MODE |= GLURAY_RENDER_GLREADPIXELS;
  if (!GLURAY_RENDER_MODE)
    GLURAY_RENDER_MODE |= GLURAY_RENDER_GLXSWAPBUFFERS;

#ifdef USE_RIVL
  //rm = RIVLManager::singleton();
#elif USE_EMBREE
  //rm = EmbreeManager::singleton();
#else
  //rm = MantaManager::singleton();
#endif
  rm = createRenderManager();

#if DEBUG_GDB
  /*static bool once = false;
  if (!once)
  {
    pid_t pid;
    once = true;
    char msg[256];
    pid = fork();
    int ppid = getppid();
    printf("ppid: %d pid: %d\n", ppid, pid);
    sprintf(msg, "gdb -pid %d", ppid);
    if (pid == 0)
    {
      system(msg);
      wait();
      exit(0);
    }
    sleep(30);
    //while(true) {}
  }*/
  int x = 0;
  while (!x)
  {
  }
#endif


  initialized = true;
  cout << "initializing\n";

#if USE_MPI
  int provided=-1;
  int requested=MPI_THREAD_MULTIPLE;

  int argc = 1;
  char*** argv = NULL;
  printf("initializing mpi\n");
  int initialized;
  MPI_Initialized(&initialized);
  if (!initialized)
  {
    MPI_Init_thread(&argc, argv, requested, &provided);
  int rank = MPI::COMM_WORLD.Get_rank();
  if (rank == 0 && (provided != requested))
    cerr << "Error:  MPI provided does not support MPI_THREAD_MULTIPLE\n do not run with more than one thread\n";
  }

#endif


  gr_setColor(1,1,1,1);

  string configFile;
  GetVar<string>("GLURAY_CONFIG", configFile);
  std::ifstream fin(configFile.c_str());
  if (fin)
  {
    std::string str((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    cout << "found config file: " << str << endl;
    rm->setRenderParametersString(str, false);
  }

  int num_threads = 8;
  if (GetVar<int>("GLURAY_NUM_THREADS", num_threads))
    rm->setNumThreads(num_threads);
  if(GetVar<size_t>("GLURAY_DL_SIZE", dl_size))
    cout << "setting dl_size: " << dl_size << endl;

  rm->init();
  //MantaManager::singleton()->init();
  // MantaManager::singleton()->current_bgcolor = Color(RGBColor(1,1,1));
  //  resolution[0] = 512;
  //  resolution[1] = 512;
  //  accelThreads = new ThreadGroup("accel threads");
  //  accelThreadsMutex = new Mutex("accel thread mutex");

  /* for(int i = 0; i < 2; i++)
     {
     Thread* thread = new Thread(new AccelRunnable(), "accel thread", accelThreads,Thread::NotActivated);
     thread->migrate(4+i);
     thread->activate(false);
  //    thread->join();
  //delete thread;
  }*/
  //killAccelThreads();

  //MantaManager::singleton()->current_normal = Vector(0,1,0);
  //MantaManager::singleton()->current_transform.initWithIdentity();
  //next_scene = new MScene();
  //  current_material = new  Phong(Color(RGBColor(.6,0,0)),
  //                          Color(RGBColor(.6,.6,.6)), 32, (ColorComponent)0.4);

  // cout << "running init routine\n";
  // manta_main();


  // cout << "done\n";
  Thread::setDefaultAbortMode("exit");
  cout << "done initializing\n";
}


void gr_addVertex(float x, float y, float z)
{
  GRCHECK();
  numadds++;
  if (!support_immediate && !IN_DL)
    return;

  //      cout << "addvertex:" << x << " " << y << " " << z << endl;

  if (PRIM_TYPE == GL_POLYGON)
  {
    if (num_poly_verts < 3)
    {
      poly_vert[num_poly_verts][0] = x;
      poly_vert[num_poly_verts][1] = y;
      poly_vert[num_poly_verts][2] = z;
      num_poly_verts++;
    }
    return;
  }
  Renderable* mr = rm->current_renderable;
  assert(mr);

  //split up large structures for parallel builds
  if (mr->getNumPrims() > dl_size)
  {
    //TODO: vapor hack 5
    if (IN_DL)  {
      rm->addRenderable(__dl_renderable);
      __dl_renderable = rm->createRenderable(rm->getGeometryGenerator(0));
      mr = __dl_renderable;
      rm->setCurrentRenderable(mr);
      display_lists[DL_NUM]->push_back(__dl_renderable);

      gr_endPrimitive();
      //TODO: this will break strips
      gr_beginPrimitive(PRIM_TYPE);
    }
  }

  if (rm->getUsePerVertexColors())
  {
    RGBAColor c = rm->getCurrentColor();
    mr->addTextureCoord(c.color[0], c.color[1], c.color[2], c.a);
  }
  mr->addVertex(x,y,z);
}

void gr_texCoord(float x, float y, float z)
{
  GRCHECK();
  Renderable* mr = rm->current_renderable;
  assert(mr);
  mr->addTextureCoord(x,y,z,1);
}

void gr_setColor(float r, float g, float b, float a)
{
  GRCHECK();
  static float oldr, oldg, oldb, olda;
  if (r != oldr || g != oldg || b != oldb || a != olda)
  {
    rm->setColor(r,g,b,a);
    if (!rm->getUsePerVertexColors())
      rm->updateMaterial();
    oldr = r; oldg=g; oldb=b; olda=a;
  }
}

void gr_setColorub(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
  static float s = 1.0f/255.0f;
  gr_setColor(float(r)*s, float(g)*s, float(b)*s, float(a)*s);
}

void gr_setBackgroundColor(float r, float g, float b, float a)
{
  GRCHECK();
  static float oldr, oldg, oldb, olda;
  if (r != oldr || g != oldg || b != oldb || a != olda)
  {
    rm->setBGColor(r,g,b,a);
    oldr = r; oldg=g; oldb=b; olda=a;
  }
}


void gr_normal(float x, float y, float z)
{
  GRCHECK();
  if (IN_DL)
    if (rm->getCurrentRenderable())
      rm->getCurrentRenderable()->addNormal(x,y,z);
}

//
////  TODO:  currently does not support immediate mode!
//
void gr_beginPrimitive(int type)
{
  GRCHECK();
  LOGSTARTC("beginPrim", 0,0.3,0.5);
  numadds = 0;

  if (!support_immediate && !IN_DL)
    return;
  bool ok = true;
  PRIM_TYPE = type;
  gr_init();
  vertex_counter = 0;
  prim_counter = 0;
  Renderable* renderable = NULL;
  GeometryGenerator* gen = rm->getGeometryGenerator(PRIM_TYPE);
  gen->reset();
  if (!IN_DL)
  {
    GLint dl = glGenLists(1);
    gr_newList(dl, GL_COMPILE);
    IN_IMMEDIATE = true;
    //assert("error" == "immediate mode not supported");  //TODO: support immediate
  }
  renderable = __dl_renderable;
  renderable->setGenerator(gen);
  rm->setCurrentRenderable(renderable);
  if (IN_DL)
  {
    if (!display_lists[DL_NUM])
    {
      display_lists[DL_NUM] = new vector<Renderable*>();
      display_lists[DL_NUM]->push_back(renderable);
    }
  }

  return;
}


void gr_endPrimitive()
{
  GRCHECK();
#if (DEBUG_MSGS == 1)
  cout << "num addvert called: " << numadds << endl;
  if (rm->getCurrentRenderable())
    cout << "num prims in current renderable: " << rm->getCurrentRenderable()->getNumPrims() << endl;
#endif
  if (PRIM_TYPE == GL_POLYGON && IN_DL)
  {
    if (num_poly_verts == 4)
    {
      PRIM_TYPE = GL_QUADS;
      __dl_renderable->setGenerator(rm->getGeometryGenerator(GL_QUADS));
      gr_addVertex(poly_vert[0][0], poly_vert[0][1],poly_vert[0][2]);
      gr_addVertex(poly_vert[1][0], poly_vert[1][1],poly_vert[1][2]);
      gr_addVertex(poly_vert[2][0], poly_vert[2][1],poly_vert[2][2]);
      gr_addVertex(poly_vert[3][0], poly_vert[3][1],poly_vert[3][2]);
    }
    else
    {
      //TODO
    }
  }


  if (IN_IMMEDIATE)
  {
    gr_endList();
    IN_IMMEDIATE = false;
    //gr_callList(DL_NUM);
  }
  LOGSTOP("beginPrim");
  //TODO: vapor hack3, no support for immediate
  return;

#if 0


  //  cout << "endprim\n";
  if (!support_immediate && !IN_DL)
    return;
  assert(MantaManager::singleton()->current_renderable);
  //assert(next_scene->world);
  if (!rm->current_renderable->isEmpty() && (support_immediate || (!support_immediate && IN_DL)))  {
    /*   MRenderable* mcr = dynamic_cast<MRenderable*>(MantaManager::singleton()->current_renderable);
         AccelerationStructure* ma = mcr->as;
         static int counter = 0;
         stringstream name;
         name << "renderable as build " << counter++;
         AccelWork* work = new AccelWork(ma,name.str());
         MantaManager::singleton()->addWork(work);*/
    rm->addRenderable(rm->current_renderable);
    //        MantaManager::singleton()->addWork(new AccelWork(MantaManager::singleton()->current_renderable->instance, "endPrim instance build"));
    //MantaManager::singleton()->rtrt->addTransaction( "addWork",
    //		      Callback::create(MantaManager::singleton(), &MantaManager::addWork, work));
    //work->run();
    //ma->rebuild(0,1);
    //if (!IN_DL) {
    //MantaManager::singleton()->next_scene->world->add(mcr->instance);
    //rm->addInstance(rm->current_renderable);
    //num_elements++;
    //}
  }  else
    MantaManager::singleton()->next_scene->renderables.pop_back();
  //  cout << "doneendprim\n";
#endif
}

int frame = 0;
bool newCamFrame = true; // boolean added for taking maximum viewport size each frame
void gr_render()
{
  GRCHECK();
  DEBUG("gr_render called\n");
  //if (rm->next_scene->instances.size() < 1)
  {
    //DEBUG("gr_render nothing, returning\n");  //TODO: removed for mpi tests
    //return;
  }
  //TODO: DEBUG: paraview is stalling here... ranks 1-2 aren't getting cleared first
  if (rendered)
    return;
  newCamFrame = true; // boolean added for taking maximum viewport size each frame
  frame++;
  /*
    static int frame = 0;
    if (frame == 0)
    LogManager::GetSingleton()->SetEnabled(true);
    if (frame++ == 50)
    {
    cout << "writing\n";
    LOGSCLOSE();
    LogManager::GetSingleton()->SetEnabled(false);
    }
    */
  LOGSTARTC("GLuRay_Render", .5, .5, 0.5);
  static CDTimer timer;
  timer.stop();
  //cout << "time since last render: " << timer.getDelta() << endl;
  timer.start();
  // needFOVCalc = true;
  //if (needFOVCalc)
  {
    GLfloat m[16];
    glGetFloatv(GL_PROJECTION_MATRIX, m);
    double fov = 2.0*atan(1.0/m[0])*180.0/M_PI;
    GLuRayRenderParameters& p = rm->params;
    p.camera_vfov = p.camera_hfov = fov;
    p.camera_vfov = fov*float(p.height)/float(p.width);
    p.camera_hfov = fov;
    //  needFOVCalc = false;
    //TODO:
    rm->updateCamera();
  }
  //timer.start();
  static CDTimer sceneTimer, renderTimer, displayTimer;

  //renderTimer.start();
  rm->render();
  //renderTimer.stop();
  //displayTimer.start();
  //m->displayFrame();
  //displayTimer.stop();
  rendered = true;
  LOGSTOP("GLuRay_Render");
}



void gr_materialfv(int face, int pname, float* params)
{
  GRCHECK();
  GLMaterial& mat = rm->getCurrentMaterial();
  if (pname == GL_SHININESS)
    mat.shiny = params[0];
  else
  {
    Color c(RGBColor(params[0], params[1], params[2]));
    switch(pname)
    {
      case GL_SPECULAR:
        {
          mat.specular = c;
          break;
        }
      case GL_AMBIENT:
        {
          mat.ambient = c;
          break;
        }
      case GL_DIFFUSE:
        {
          mat.diffuse = c;
          break;
        }
      case GL_AMBIENT_AND_DIFFUSE:
        {
          mat.diffuse = c;
          mat.ambient = c;
          break;
        }
      default:
        ;
    }
  }
  rm->enableGLMaterial(true);
  rm->setColor(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2], 1.0);
  rm->updateMaterial();
}

void gr_materialf(int face, int pname, float param)
{
  GRCHECK();

}

void gr_materialiv(int face, int pname, int* params)
{
  GRCHECK();

}

void gr_materiali(int face, int pname, int param)
{
  GRCHECK();

}



void gr_translate(float x, float y, float z)
{
  GRCHECK();
  if (matrix_mode != GL_MODELVIEW)
    return;
  /*  float modelview[16];
      glGetFloatv(GL_MODELVIEW_MATRIX , modelview);
      for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
      current_transform.mat[i][j] = modelview[i*3+j];
      }
      }*/
  //   current_transform.translate(Vector(x,y,z));
  AffineTransform t;
  t.initWithTranslation(Vector(x,y,z));
  rm->current_transform = rm->current_transform*t;
}

#define DEG_TO_RADIONS 3.14f/180.0f

void gr_rotate(float angle, float x, float y, float z)
{
  GRCHECK();
  if (matrix_mode != GL_MODELVIEW)
    return;
  //current_transform.rotate(Vector(x,y,z), angle*DEG_TO_RADIONS);
  AffineTransform t;
  t.initWithRotation(Vector(x,y,z), angle*DEG_TO_RADIONS);
  rm->current_transform =   rm->current_transform*t;
}


void gr_scale(float x, float y, float z)
{
  GRCHECK();
  if (matrix_mode != GL_MODELVIEW)
    return;
  AffineTransform t;
  t.initWithScale(Vector(x,y,z));
  rm->current_transform = rm->current_transform*t;
}

void gr_loadIdentity()
{
  GRCHECK();
  if (matrix_mode != GL_MODELVIEW)
    return;
  rm->current_transform.initWithIdentity();
}

void gr_newList(size_t list, int mode)
{
  printf("newlist\n");
  fflush(stdout);
  GRCHECK();
  gr_pushMatrix();
  //
  //  setting color before and after display list so we can safely delete all materials...
  //
  RGBAColor c = rm->current_color;
  rm->setColor(c.color[0],c.color[1],c.color[2],c.a);
  rm->updateMaterial();


  rm->current_transform.initWithIdentity();
  IN_DL = true;
  DL_NUM = list;
  //TODO: check if exists
  if (display_lists[DL_NUM])
    gr_deleteLists(DL_NUM, 1);
  display_lists[DL_NUM] = new vector<Renderable*>();
  assert(display_lists[DL_NUM]);

  //TODO: vapor hack
  __dl_renderable = rm->createRenderable(rm->getGeometryGenerator(0));
  //MantaManager::singleton()->next_scene->renderables.push_back(__dl_renderable);
  display_lists[DL_NUM]->push_back(__dl_renderable);

  if (mode == GL_COMPILE_AND_EXECUTE)
  {
    //assert(GL_COMPILE_AND_EXECUTE==55);
    gr_callList(DL_NUM);
  }
}

void gr_endList()
{
  printf("endlist\n");
  fflush(stdout);
  GRCHECK();
  //
  //  setting color to safely delete materials
  //
  RGBAColor c = rm->current_color;
  // MantaManager::singleton()->setColor(c.color[0],c.color[1],c.color[2],c.a);
  rm->updateMaterial();

  //TODO: vapor hack4
  if (IN_DL && !__dl_renderable->isEmpty())  {
    /*    if (DL_NUM == 1)
          {
          MantaManager::singleton()->next_scene->renderables.push_back(__dl_renderable);
          AccelerationStructure* ma = __dl_renderable->as;
          static int counter = 0;
          stringstream name;
          name << "renderable as build " << counter++;
          AccelWork* work = new AccelWork(ma,name.str());
          ma->setGroup(__dl_renderable->_data->group);
          MantaManager::singleton()->addWork(work);
          __dl_renderable->instance = new DirtyInstance(ma, MantaManager::singleton()->current_transform);
    //__dl_renderable->_data->group->add(ma);
    }*/
    //TODO: generalize
    rm->addRenderable(__dl_renderable);
    /*
       MRenderable* dlr = dynamic_cast<MRenderable*>(__dl_renderable);
       rm->next_scene->renderables.push_back(dlr);
    //TODO: generalize this
    AccelerationStructure* ma = dlr->as;
    static int counter = 0;
    stringstream name;
    name << "renderable as build " << counter++;
    AccelWork* work = new AccelWork(ma,name.str());
    MantaManager::singleton()->addWork(work);
    dlr->_data->group->add(ma);
    */
  }

  //  cout << "end list\n";
  //   bool empty = true;
  //   for( vector<MRenderable*>::iterator itr = display_lists[DL_NUM]->begin(); itr != display_lists[DL_NUM]->end(); itr++)
  //     {
  //   if (!(*itr)->isEmpty())
  //     empty = false;
  //   else {
  //     //  display_lists[DL_NUM]->erase(itr);
  //   }
  // }
  //   if (empty)
  //     {
  //       delete display_lists[DL_NUM];
  //       display_lists[DL_NUM] = NULL;
  //     }
  gr_popMatrix();
  IN_DL = false;
  gr_callList(DL_NUM);
  DL_NUM = 0;
}

void gr_callList(int list)
{
  GRCHECK();
  DEBUG("callList\n");
  //LOGSTARTC("gluray_callList", 0.2, 0.2, 0.2);
  //if (needFOVCalc)
  //{
  //GLfloat m[16];
  //glGetFloatv(GL_PROJECTION_MATRIX, m);
  //double fov = 2.0*atan(1.0/m[0])*180.0/M_PI;
  //GLuRayRenderParameters& p = rm->params;
  //p.camera_vfov = p.camera_hfov = fov;
  //needFOVCalc = false;
  ////TODO:
  //rm->updateCamera();
  //}

  if (IN_DL)
  {
    //TODO: check for cycles...
    if (!display_lists[list]->at(0)->isEmpty())
    {
      //TODO: this is a hack since groups weren't using the bvh...!
      /*MRenderable* mr = display_lists[list]->at(0);
        if (mr->_data->num_prims > 0)
        {
      //   DynBVH* hack = new DynBVH(DEBUG_MSGS);
      //   hack->setGroup(mr->_data->mesh);
      //   AccelWork* work = new AccelWork(hack, "hackbuildgluray.cc");
      //   MantaManager::singleton()->addWork(work);
      //       mr->_data->group->add(hack);


      //__dl_renderable->_data->group->add(mr->as);
      __dl_renderable->_data->num_prims += mr->_data->num_prims;
      //cout << "added"
      MRenderable* dr = __dl_renderable;
      MData* dr_d = dr->_data;
      MData* mr_d = mr->_data;
      Mesh* dr_m = dr_d->mesh;
      Mesh* mr_m = mr_d->mesh;
      //TODO: this breaks things (waste of memory and ignores transforms), should add instances
       *dr_m += *mr_m;
       delete mr_d;
       delete mr_m;
       delete mr;


       printf("adding list x to y: %d %d\n", list, DL_NUM);
       printf("size of x: %d\n", mr->_data->mesh->vertices.size());
       }
       */
    }
    else
      cout << "internal call list was empty\n";
    return;
  }
  else
  {
    //TODO: this is a hack since groups weren't using the bvh...!
    /*
       if (!display_lists[list]->at(0)->isEmpty())
       {
       cout << "internal call list was empty\n";

       MRenderable* mr = display_lists[list]->at(0);
       if (mr->_data->group->size() == 0)
       {
       if (mr->_data->num_prims > 0)
       {
       DynBVH* hack = new DynBVH(DEBUG_MSGS);
       hack->setGroup(mr->_data->mesh);
       AccelWork* work = new AccelWork(hack, "hackbuildgluray.cc");
       MantaManager::singleton()->addWork(work);
       mr->_data->group->add(hack);
       }
       }
       }
       */
  }

  num_elements++;
  //TODO: garbage collect new instances!
  assert(display_lists[list]);
  for(int i = 0; i < display_lists[list]->size(); i++) {
    if (display_lists[list]->at(i)->isEmpty()) {
      //cout << "gl2manta error: display list instance was empty\n";
      continue;
    }
    //	   DirtyInstance* instance = new DirtyInstance(display_lists[list]->at(i)->instance, MantaManager::singleton()->current_transform);
    //  MRenderable* tr = new
    //MantaManager::singleton()->next_scene->world->add(instance);
    //MantaManager::singleton()->addAccelWork(work);
    //	   next_scene->renderables.push_back(display_lists[list]->at(i));
    // DirtyInstance& di = MantaManager::singleton()->next_scene->addInstance();
    // 	   di.setInstance(display_lists[list]->at(i)->instance);
    // 	   di.setTransform(MantaManager::singleton()->current_transform);
    rm->addInstance(display_lists[list]->at(i));
    //MRenderable* mr = dynamic_cast<MRenderable*>(display_lists[list]->at(i));
    //DirtyInstance* inst = new DirtyInstance(mr->instance,MantaManager::singleton()->current_transform);
    //MantaManager::singleton()->next_scene->instances.push_back(inst);
    //AccelWork* work = new AccelWork(inst, "call list instance build\n");
#if DEBUG_MSGS
    //cout << "adding to scene: " << display_lists[list]->at(i)->_data->num_prims << endl;
#endif
    //PreprocessContext context(MantaManager::singleton()->rtrt, 0, 1, MantaManager::singleton()->lights);
    //mr->_data->group->preprocess(context);
    //MantaManager::singleton()->addWork(work);
  }
  //	   cout << "adding list: " << list << endl;
  //	   cout << "num elements in world: " << next_scene.world->size() << endl;
  //LOGSTOP("gluray_callList");
}

void gr_deleteLists(GLuint list, GLsizei range)
{
  GRCHECK();
  for(int i = 0; i < range; i++)
  {
    int index = list+i;
#if DEBUG_MSGS
    cout << "deleting list: " << index << endl;
#endif
    assert(display_lists[index]);
    for(int j = 0; j < display_lists[index]->size(); j++)
    {
      //TODO: generalize
      //MRenderable* mr = dynamic_cast<MRenderable*>(display_lists[index]->at(j));
      rm->deleteRenderable(display_lists[index]->at(j));
    }
    delete display_lists[index];
    display_lists[index] = 0;
  }
}

void gr_enableClientState(GLenum st)
{
  GRCHECK();

}

const GLvoid* __vertex_pointer = 0;
int __vertex_stride = 0;
bool __vertex_fill =  false;

void gr_vertexPointer(GLint dim, GLenum type, GLsizei stride, const GLvoid* pointer)
{
  GRCHECK();
  __vertex_pointer = pointer;
  //if (pointer == 0)
  //	cout << "null vertex pointer given\n";
  //else
  //	cout << "valid vertex pointer given\n";
  assert(pointer); //TODO: support VBOs

  __vertex_fill = false;
  switch(type)
  {
    case  GL_FLOAT:
      {
        if (dim == 3)
        {
          if (stride < 3*sizeof(float))
            stride = 3*sizeof(float);
          __vertex_stride = stride;
        }
        break;
      }
    default:
      break;
  }
}



void gr_colorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)
{
  GRCHECK();
  cout << "gr_colorPointer\n";
  __color_pointer = pointer;
  //if (pointer == 0)
  //	cout << "null color pointer give\n";
  //else
  //	cout << "valid color pointer given\n";

  assert(pointer); //TODO: support VBOs
  switch(type)
  {
    case  GL_FLOAT:
      {
        if (stride < 4*sizeof(float))
          stride = 4*sizeof(float);
        __color_stride = stride;
        break;
      }
    default:
      {
        assert ("error" == "unsupported color format");
      }
      break;
  }

}

void gr_drawArrays(GLenum mode, GLint first, GLsizei count)
{
  GRCHECK();
  gr_drawElements(mode, count, GL_UNSIGNED_INT, NULL);
}

void gr_drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
{
  GRCHECK();
  gr_drawElements_internal(mode, count, type, indices, 0);
}

void gr_drawElements_internal(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, GLint first)
{
  GRCHECK();
  //assert(__vertex_pointer);
  if (!__vertex_pointer)
    return;
  RGBAColor c = rm->getCurrentColor();
  //if (__color_pointer)   //  MantaManager::singleton()->usePerVertexColors = true;
  gr_setColor(c.color[0], c.color[1], c.color[2],  c.a);
  gr_beginPrimitive(mode);
  switch(mode)
  {
    case GL_TRIANGLE_STRIP:
      {
        /*size_t index = reinterpret_cast<std::size_t>(__vertex_pointer)+first+count;
          if (indices != NULL && count > 3)
          index += static_cast<const float*>(indices)[0]+static_cast<const float*>(indices)[3]; //TODO: this is an incorrect hack to force reusewithout checking through all indices however this could be bad...

          cout << "drawArrays index: " << index << endl;
        //TODO: bad carson!  should only be done for vbos this won't update
        if (!display_lists[index])
        {
        cout << "drawArrays new list\n";
        gr_newList(index, GL_COMPILE);*/
        const float* data = &(static_cast<const float*>(__vertex_pointer)[first*__vertex_stride]);
        const float* cdata = &(static_cast<const float*>(__color_pointer)[first*__color_stride]);
        if (indices == NULL)
        {
          for (size_t i = first; i < count; i++)
          {
            if (__color_pointer && rm->getUsePerVertexColors()) //TODO: set this according to glenableclientstate

            {
              rm->current_renderable->addTextureCoord(cdata[2],cdata[1],cdata[0],cdata[3]);
            }
            gr_addVertex(data[0],data[1],data[2]);
            data += 3*__vertex_stride;
            cdata += 4*__color_stride;
          }
        }
        else
        {
          for(size_t i =0; i < count; i++)
          {
            assert(type != GL_UNSIGNED_SHORT);
            assert(type != GL_UNSIGNED_BYTE);
            size_t vindex = static_cast<const unsigned int*>(indices)[i];
            const float* v = data + (__vertex_stride/sizeof(float))*vindex;
            const float* c = cdata + (__color_stride/sizeof(float))*vindex;
            if (__color_pointer)
            {
              cout << "add vert2\n";
              rm->getCurrentRenderable()->addTextureCoord(c[0],c[1],c[2],c[3]);
            }
            gr_addVertex(v[0],v[1],v[2]);
          }
        }
        /*    gr_endList();
              gr_callList(index);*/
        //}
        //else
        //{
        /*	gr_callList(index);*/
        //}

      }
      break;
    default:
      break;
  }
  gr_endPrimitive();
  gr_setColor(c.color[0], c.color[1], c.color[2], c.a);
}

void gr_disableClientState(GLenum st)
{
  GRCHECK();
  if (st == GL_VERTEX_ARRAY)
  {
    __vertex_pointer = 0;
  }
}


void gr_pushMatrix()
{
  GRCHECK();
  transform_stack.push(rm->getCurrentTransform());
}

void gr_popMatrix()
{
  GRCHECK();
  rm->current_transform = transform_stack.top();
  transform_stack.pop();
}

void gr_makeCurrent(unsigned long winID)
{
  GRCHECK();
  rm->window_id = winID;
}


void gr_chooseVisual(XVisualInfo* info)
{
  GRCHECK();
  //  MantaManager::singleton()->visual = info->visual;  //crashes ensight...
}

void gr_viewport(int x, int y, int width, int height)
{
  GRCHECK();
  //TODO: this is a hack to keep paraview and other programs from messing up the viewport by drawing axis and other annoyances
  if(!newCamFrame)
  {
    //if (width < 300)  //TODO: this is a hack... paraview keeps changing it to 164 for some unknown reason
    //return;
    if (width < resolution[0] && height < resolution[0])
      return;
  }
  newCamFrame = false;
  gr_init();
  // rtrt->changeResolution(0,width,height,false);
  // rtrt->addOneShotCallback(MantaInterface::Absolute, 0,
  //
  if (resolution[0] != width || resolution[1] != height)
    reset_camera = true;
  else
    return;
  resolution[0] = width;
  resolution[1] = height;

  //Callback::create(&transaction_changeResolution));

  rm->setSize(width, height);


  //rgb_data.resize(width*height*3);
  //depth_data.resize(width*height);

  //cout << "changing viewport: " << width << " " << height << "\n";
  // syncDisplay->waitOnFrameReady();
  //rtrt->addTransaction( "setScene",
  //			Callback::create(&manager, &Gl2MantaManager::updateScene));
  //syncDisplay->doneRendering();
  //cout << "done chaning viewport\n";
}


void gr_lookAt(float ex,float ey, float ez, float lx,float ly, float lz, float ux, float uy, float uz)
{
  GRCHECK();
  GLuRayRenderParameters& p = rm->params;
  p.camera_eye = Vector(ex,ey,ez);
  p.camera_dir = Vector(lx,ly,lz) - Vector(ex,ey,ez);
  p.camera_dir.normalize();
  p.camera_up = Vector(ux,uy,uz);
  rm->updateCamera();
}

void gr_matrixMode(int mode)
{
  GRCHECK();
  matrix_mode = mode;
}

void gr_multMatrixf(const float* m)
{
  GRCHECK();
  if (matrix_mode != GL_MODELVIEW)
    return;
  // cout << "mulitplying matrix\n";
  // cout << "current transform: \n" << current_transform;
  AffineTransform t;
  t.initWithIdentity();
  for(int row = 0; row < 3; row++) {
    for(int col = 0; col < 4; col++) {
      t(row,col) = m[col*4+row];
    }
  }
  // cout << "\n\n multiplying by: \n" << t;
  rm->current_transform = rm->current_transform*t;
  //cout << "\n\n result: \n" << current_transform << endl << endl;
}

void gr_multMatrixd(const double* m)
{
  GRCHECK();
  if (matrix_mode != GL_MODELVIEW)
    return;
  AffineTransform t;
  t.initWithIdentity();
  for(int row = 0; row < 3; row++) {
    for(int col = 0; col < 4; col++) {
      t(row,col) = m[col*4+row];
    }
  }
  rm->current_transform = rm->current_transform*t;
}

void gr_loadMatrixf(const float* m)
{
  GRCHECK();
  if (matrix_mode != GL_MODELVIEW)
    return;
  for(int row = 0; row < 3; row++) {
    for(int col = 0; col < 4; col++) {
      rm->current_transform(row,col) = m[col*4+row];
    }
  }
}

void gr_loadMatrixd(const double* m)
{
  GRCHECK();

  if (matrix_mode != GL_MODELVIEW)
    return;
  for(int row = 0; row < 3; row++) {
    for(int col = 0; col < 4; col++) {
      rm->current_transform(row,col) = m[col*4+row];
    }
  }
}

void gr_clear(GLbitfield mask)
{
  GRCHECK();
  //MantaManager* mm = MantaManager::singleton();
  /*if(rm->dirty_renderParams)
    {
    rm->setRenderParametersString(rm->new_renderParamsString, false);
    rm->dirty_renderParams = false;
    }*/
  rendered = false;
  //if (!rendered)
  //  gr_render(); //this is for single buffered rendering with no bufferswap
}



void gr_light(int light, int pname, float* params)
{
  GRCHECK();
  Vector p(params[0], params[1], params[2]);
  Color c(RGBColor(params[0], params[1], params[2]));
  int num = light - GL_LIGHT0;
  GLLight l = rm->getLight(num);
  l.w = params[3];
  switch (pname)
  {
    case GL_AMBIENT:
      {
        l.ambient = c;
        break;
      }
    case GL_SPECULAR:
      {
        l.specular = c;
        break;
      }
    case GL_DIFFUSE:
      {
        l.diffuse = c;
        break;
      }
    case GL_POSITION:
      {
        l.pos = p;
        break;
      }
  }
  rm->setLight(num, l);
}

void gr_enable(int what)
{
  GRCHECK();

  switch(what)
  {
    case GL_LIGHT0:
    case GL_LIGHT1:
    case GL_LIGHT2:
    case GL_LIGHT3:
    case GL_LIGHT4:
    case GL_LIGHT5:
    case GL_LIGHT6:
    case GL_LIGHT7:
      {
        int lightnum = what - GL_LIGHT0;
        rm->enableLight(lightnum, true);
        break;
      }
    case GL_LIGHTING:
      {
        //       MantaManager::singleton()->enableLighting(true);
        break;
      }
  }
}

void gr_disable(int what)
{
  GRCHECK();

  switch(what)
  {
    case GL_LIGHT0:
    case GL_LIGHT1:
    case GL_LIGHT2:
    case GL_LIGHT3:
    case GL_LIGHT4:
    case GL_LIGHT5:
    case GL_LIGHT6:
    case GL_LIGHT7:
      {
        int lightnum = what - GL_LIGHT0;
        rm->enableLight(lightnum, false);
        break;
      }
    case GL_LIGHTING:
      {
        //TODO: ignore for now... it is often disabled AFTER gl draw calls unfortunately need to handle this better...
        //MantaManager::singleton()->enableLighting(false);
        break;
      }

  }

}

void gr_material(int pname, float* params)
{
  GRCHECK();
}

void gr_frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far)
{
  GRCHECK();
  rm->setNearFar(near,far);
}

void gr_texImage1D(GLenum target, GLint level, GLint internalFormat, GLsizei width,
    GLint border, GLenum format, GLenum type, const GLvoid* data)
{
  GRCHECK();

}

void gr_texImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data)
{
  GRCHECK();
  int texId;
  glGetIntegerv(GL_TEXTURE_BINDING_2D, &texId);
  if (texId <= 0)
    return;
  //if (data == 0)
  //return;
  rm->addTexture(texId, target, level, internalFormat, width, height, border, format, type, (void*)data);
#if USE_MPI
  static CDTimer displayTimer;
  displayTimer.start();
  rm->displayFrame();  //TODO: this breaks frame lag
  displayTimer.stop();
#endif
  //printf("display time: %f\n", displayTimer.getDelta());
}

void gr_finalize()
{
  GRCHECK();
  if (frame > 2)
  {
    LOGSCLOSE();
  }
}

void gr_lock(const int num)
{
  GRCHECK();
  rm->lock(num);
}


void gr_unlock(const int num)
{
  GRCHECK();
  rm->unlock(num);
}


#endif
