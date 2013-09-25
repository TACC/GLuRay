
#include <UseMPI.h>
#ifdef USE_MPI
#include <Engine/Display/NullDisplay.h>
#include <Engine/LoadBalancers/MPI_LoadBalancer.h>
#include <Engine/ImageTraversers/MPI_ImageTraverser.h>
#include <mpi.h>
#endif

#include "defines.h"
#include "RIVLManager.h"
#include "CDTimer.h"
#include "RScene.h"
#include "MRenderable.h"
#include "common.h"
#include <Modules/Manta/AccelWork.h>

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



//RIVL
#include "rivl.h"
#include "common/Camera.h"
#include "common/FrameBuffer.h"
#include "geometry/TriangleMesh.h"
#include "accel/TriangleMeshBVH2.h"
#include "accel/BowPass.h"
#include "renderer/DummyRenderer.h"
#include "renderer/RayCast.h"
#include "renderer/SimpleAO.h"
#include "parseOBJ.h"



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
//#include <X11/Xlib.h>
//#include <X11/Xutil.h>

#define USE_MEGAMESH 1

#if USE_MPI
int cacheFraction = -1;  //for dynbvh_d and mesh_dsm
#endif

rivl::FrameBuffer *fb;
rivl::Renderer    *renderer;
rivl::Camera      *camera;

//using namespace rivl;

ostream& operator<<(ostream& out, GLMaterial& m)
{
  out << "GLMaterial:\n";
  out << "ambient: " << m.ambient[0] << " " << m.ambient[1] << " " << m.ambient[2] << " ";
  out << "diffuse: " << m.diffuse[0] << " " << m.diffuse[1] << " " << m.diffuse[2] << " ";
  out << "specular: " << m.specular[0] << " " << m.specular[1] << " " << m.specular[2] << " ";
  out << "emissive: " << m.emissive[0] << " " << m.emissive[1] << " " << m.emissive[2] << " ";
  out << "shiny: " << m.shiny;
  return out;
}
ostream& operator<<(ostream& out, GLLight& m)
{
  out << "GLLight:\n";
  out << "ambient: " << m.ambient[0] << " " << m.ambient[1] << " " << m.ambient[2] << " ";
  out << "diffuse: " << m.diffuse[0] << " " << m.diffuse[1] << " " << m.diffuse[2] << " ";
  out << "specular: " << m.specular[0] << " " << m.specular[1] << " " << m.specular[2] << " ";
  out << "pos: " << m.pos[0] << " " << m.pos[1] << " " << m.pos[2] << " ";
  out << "is pointlight: " << m.w << " is enabled: " << m.enabled;

}

// generate N points on [0,1]^2
void getLightSamples( float *u_, float *v_, int n)
{
  //for (int i = 0; i < n; i++) {
  // u[i] = drand48();
  //   v[i] = drand48();
  //}
  // hammersley from 97 jgt article
  float p, u, v;
  int k, kk, pos;

  for (k=0, pos=0 ; k<n ; k++)
  {
    u = 0;
    for (p=0.5, kk=k ; kk ; p*=0.5, kk>>=1)
      if (kk & 1)                           // kk mod 2 == 1
        u += p;

    v = (k + 0.5) / n;

    u_[k] = u;
    v_[k] = v;
  }
}

void addLights( LightSet* lights, int num_lights, float width_scale, float intensity)
{
  float minx = -200; float scalex = 30*width_scale;
  float minz = 400; float scalez = 30*width_scale;
  float y = 400;
  Color c1 = Color(RGB(0.85, 0.9, 0.6));
  Color c2 = Color(RGB(0.3,0.3,1.0));
  Color c4 = Color(RGB(1.,1.0,1.0));

  float *u = new float[num_lights];
  float *v = new float[num_lights];
  getLightSamples( u, v, num_lights );
  srand(1);
  for (int i = 0; i < num_lights; i++) {
    Color c3 = Color(RGB(drand48(), drand48(), drand48()));
    float rand = drand48(), rand2 = drand48(), rand3 = drand48();
    Color col = (c3*rand*.2 + ((c1*rand2 + c2*(1.0-rand2))*rand3*.5 + c4*(1.0-rand3)*.5)*.8) * (intensity/num_lights);
    lights->add(new PointLight(Vector(minx + u[i] * scalex, y, minz + v[i]*scalez), col));
  }
  delete [] u;
  delete [] v;
}


RIVLManager* RIVLManager::_singleton = NULL;

RIVLManager* RIVLManager::singleton()
{
  if (!_singleton)
    _singleton = new RIVLManager();
  return _singleton;
}


RIVLManager::RIVLManager()
  :RenderManager(), current_scene(NULL), next_scene(NULL),
_nid_counter(0), _depth(false)
{
  _gVoid = new RGeometryGeneratorVoid();
  _gTriangle = new RGeometryGeneratorTriangles();
  _gTriangleStrip = new RGeometryGeneratorTriangleStrip();
  _gQuads = new RGeometryGeneratorQuads();
  _gQuadStrip = new RGeometryGeneratorQuadStrip();
  _gLines = new RGeometryGeneratorLines();
  _gLineStrip= new RGeometryGeneratorLineStrip();
}

RIVLManager::~RIVLManager()
{
}

void RIVLManager::updateLights()
{
#if 0
  if(!lights)
    return;
  //cerr << "setuplights\n";
  lights_dirty = false;
  while (lights->numLights() > 0)
  {
    lights->remove(lights->getLight(0));
  }
  double cintensity = params.skyDome_intensity;
  if (cintensity < 0.0)
    cintensity = 0.0;
  double compI = 1.0 - cintensity - params.ao_intensity;
  if (compI < 0.0)
    compI = 0.0;
  if (lights,params.num_skyDome_lights > 0)
    addLights(lights,params.num_skyDome_lights, params.skyDome_size, params.skyDome_intensity);
  //if ((cintensity < 0.9 || params.num_skyDome_lights <= 0) && !use_gl_lights)
  {
    //lights->add(new PointLight(Vector(-8,0,10), Color(RGBColor(.5,.5,.3))*.1*compI));
    //lights->add(new PointLight(Vector(8,5,6), Color(RGBColor(.6,.67,.9))*.4*compI));
  }

  Color ambient(RGB(0,0,0));
  bool addedLight = false;
  //TODO: modify light position by modelview!
  if (params.use_gl_lights && use_gl_lights)
  {
    for(int i = 0; i < 8; i++)
    {
      GLLight& l = gl_lights[i];
      if (l.enabled)
      {
        addedLight = true;
        if (l.w == 0)
        {
          //cout << "adding gl directional light " << i << ":\n" << l << "\n";
          lights->add(new DirectionalLight(l.pos, l.diffuse));
        }
        else
        {
          cout << "adding gl point light " << i << ":\n" << l << "\n";
          lights->add(new PointLight(l.pos, l.diffuse));
        }
        if (use_gl_material)
        {
          ambient += l.ambient*0.0f; //TODO: HACK!  ambient should be mix of material properties and ambt... this does this but the material properties are global and old
        }
        else
          ambient += l.ambient*0.5; //TODO: HACK!  ambient should be mix of material properties and amb
      }
    }
    if (!addedLight) //Manta crashes with no lights...
    {
      lights->add(new PointLight(Vector(10,10,-1), Color(RGBColor(1,1,1))*0.3));
    }
  }
  else
  {
    lights->add(new PointLight(Vector(8,5,6), Color(RGBColor(.6,.67,.9))*.5*compI));
  }
  if (!use_gl_lights)
    ambient = Color(RGB(.2,.2,.2));
  if (params.num_ao_samples > 0)
  {
    //  current_material = new AmbientOcclusionCombiner(current_material, 100.0,params.num_ao_samples);
    //lights->setAmbientLight(new AmbientOcclusionBackground(ambient*params.ao_intensity,params.ao_distance,params.num_ao_samples, false, background));
    ambient = Color(RGB(1,1,1));  //HACK!
    lights->setAmbientLight(new AmbientOcclusion(ambient*params.ao_intensity,params.ao_distance,params.num_ao_samples, false));
  }
  else {
    lights->setAmbientLight(new ConstantAmbient(ambient));
  }
  //cerr << "setuplights done\n";
#endif
}

void  RIVLManager::updateMaterial()
{
  //TODO: transparency taken from glcolor always for now...
  GLMaterial m = gl_material;
  //TODO: DEBUG: hardcoding mat for debugging
  //m.diffuse = Color(RGB(1.0, 0.713726, .21569));
  //m.diffuse = Color(RGB(0.8, 0.8, 0.8));
  m.specular = Color(RGB(.1, .1, .1));
  m.ambient = Color(RGB(0, 0, 0));
  m.shiny = 100;

  if (!use_gl_material)
  {
    m.diffuse = current_color.color;
    m.specular = Color(RGB(0,0,0));
    m.ambient = Color(RGB(1.0,1.0,1.0));
    m.shiny = 10;
  }
  else
  {
    //cout << "using gl material: " << m << endl;
    //params.material = "lambertian";
    //if (m.specular[0] > 0.001 || m.specular[1] > 0.001 || m.specular[2] > 0.001)
    if (params.material == "phong")
    {
      if (current_color.a < 0.99)
        params.material = "transparent";
    }
    //printf("using glmaterial with ambient: %f\n", m.ambient);
  }
#if 0
  //usePerVertexColors = false;  //TODO: DEBUG
  if (usePerVertexColors)
  {
    Manta::Texture<Manta::Color> *texture = new Manta::TexCoordTexture();
    //    texture = new Constant<Manta::Color>(m.diffuse);
    if (params.material == "phong")
    {
      Texture<Color> *specular =
        new Constant<Manta::Color>
        (m.specular);
      Texture<float> *refl = new Constant<float>(params.reflectivity);

      current_material= new Phong(texture,
          specular, m.shiny,refl);
    }
    else if (params.material == "lambertian")
    {

      //current_material = new Lambertian(Color(RGBColor(0,1,0)));
      current_material = new Lambertian(texture);
    }
    else if (params.material == "metal")
      current_material = new MetalMaterial(texture, m.shiny);
    else if (params.material == "glass")
    {
      //current_material = new Dielectric(params.ri, params.ri2, texture);
    }
    else if (params.material == "thinDielectric")
    {
      //current_material = new ThinDielectric(params.eta, texture, params.thickness, 1);
    }
    else if (params.material == "orenNayar")
      current_material = new OrenNayar(texture);
    else if (params.material == "transparent")
    {
      if (current_color.a < 0.95)
        current_material = new Transparent(texture, current_color.a);
      else
      {

        Texture<Color> *specular =
          new Constant<Manta::Color>
          (m.specular);
        Texture<float> *refl = new Constant<float>(params.reflectivity);

        current_material= new Phong(texture,
            specular, m.shiny,refl);
      }
    }
    else
      assert(0);
  }
  else
  {
    if (params.material == "phong")
      current_material= new Phong(m.diffuse,
          m.specular, m.shiny, (ColorComponent)params.reflectivity);
    else if (params.material == "lambertian")
      current_material = new Lambertian(m.diffuse);
    else if (params.material == "metal")
      current_material = new MetalMaterial(m.diffuse, 10);
    else if (params.material == "glass")
    {
      current_material = new Dielectric(params.ri, params.ri2, current_color.color);
    }
    else if (params.material == "thinDielectric")
      current_material = new ThinDielectric(params.eta, m.diffuse, params.thickness, 1);
    else if (params.material == "orenNayar")
      current_material = new OrenNayar(m.diffuse, 1);
    else if (params.material == "transparent")
      current_material = new Transparent(m.diffuse, current_color.a);
    else
      assert(0);
  }
#endif
}

void RIVLManager::useShadows(bool st)
{
}

void RIVLManager::setSize(int w, int h)
{
  if (w != params.width || h != params.height)
  {
    params.width = w;
    params.height = h;
    rivl::vec2ui windowSize = rivl::vec2ui(w,h);
    rivl::vec2ui offset(0U,0U);
    fb = new rivl::FrameBuffer(windowSize, windowSize, offset);
  }
}

rivl::TriangleMesh *parseOBJ(const std::string &fileName,
                             vector<OBJ::Material> &material,
                             rivl::box3fa &worldBounds)
{
  worldBounds.clear();
  rivl::vec3fa INVALID_NORMAL(0.f,0.f,0.f);
  rivl::vec2f  INVALID_TEXCOORD(rivl::pos_inf,rivl::pos_inf);

  OBJ::OBJFile *objFile = OBJ::OBJFile::read(fileName);
  if (!objFile) {
    cerr << "could not read OBJ file '" << fileName << "' ... exiting" << endl;
    exit(1);
  }
  cout << "done parsing OBJ file : " << endl; objFile->print();

  for (int i=0;i<objFile->material.size();i++) {
    if (objFile->material[i])
      material.push_back(*objFile->material[i]);
    else
      material.push_back(OBJ::Material(""));
  };

  // now, merge all individual groups into a single rivl trianglemesh
  // (tesssellating larger faces as we go)
  rivl::TriangleMesh *mesh = new rivl::TriangleMesh;
  std::map<rivl::vec3i,int> vtxMap;
  for (int gID=0;gID<objFile->group.size();gID++) {
    OBJ::OBJFile::Group *g = objFile->group[gID];
    assert(g);
    // first, convert 3-index vertices to single-index vertices.
    for (int fID=0;fID<g->face.size();fID++) {
      OBJ::OBJFile::Face *f = g->face[fID];
      assert(f);
      vector<int> newVtxID;
      for (int vID=0;vID<f->vertex.size();vID++) {
        OBJ::OBJFile::Vertex vtxID = f->vertex[vID];
        if (vtxMap.find((const rivl::vec3i&)vtxID) == vtxMap.end()) {
          // not found
          int newID = mesh->vertex.size();
          if (vtxID.vn >= 0) {
            while (mesh->normal.size() < mesh->vertex.size())
              mesh->normal.push_back(INVALID_NORMAL);
            mesh->normal.push_back(objFile->vn[vtxID.vn]);
          }
          if (vtxID.vt >= 0) {
            while (mesh->texcoord.size() < mesh->vertex.size())
              mesh->texcoord.push_back(INVALID_TEXCOORD);
            mesh->texcoord.push_back(objFile->vt[vtxID.vt]);
          }
          mesh->vertex.push_back(objFile->v[vtxID.v]);
          worldBounds.extend(objFile->v[vtxID.v]);

          vtxMap[(const rivl::vec3i&)vtxID] = newID;
          newVtxID.push_back(newID);
        } else {
          // already exists
          newVtxID.push_back(vtxMap[(const rivl::vec3i&)vtxID]);
        }
      }
      // now, tessellate
      for (int i=2;i<newVtxID.size();i++) {
        rivl::TriangleMesh::Triangle t;
        t.vtxID.x = newVtxID[0];
        t.vtxID.y = newVtxID[i-1];
        t.vtxID.z = newVtxID[i];
        t.shaderID = g->materialID;
        if (t.shaderID > 200)
          PRINT(g->materialID);
        // t.has_normals = (t.vtxID.x < mesh->normal.size() &&
        //                  mesh->normal[t.vtxID.x] != INVALID_NORMAL &&
        //                  t.vtxID.y < mesh->normal.size() &&
        //                  mesh->normal[t.vtxID.y] != INVALID_NORMAL &&
        //                  t.vtxID.z < mesh->normal.size() &&
        //                  mesh->normal[t.vtxID.z] != INVALID_NORMAL);
        // t.has_texcoords = (t.vtxID.x < mesh->texcoord.size() &&
        //                    mesh->texcoord[t.vtxID.x] != INVALID_TEXCOORD &&
        //                    t.vtxID.y < mesh->texcoord.size() &&
        //                    mesh->texcoord[t.vtxID.y] != INVALID_TEXCOORD &&
        //                    t.vtxID.z < mesh->texcoord.size() &&
        //                    mesh->texcoord[t.vtxID.z] != INVALID_TEXCOORD);
        mesh->triangle.push_back(t);
      }
    }
  }
  delete objFile;
  return mesh;
}



void RIVLManager::init()
{
  int ac = 1;
  const char* av = "wakka";
  rivl::rivl_init(&ac, &av);

  camera      = new rivl::Camera;
 /* camera->fovy = atof(av[++i]);*/
      //camera->lookFrom.x = atof(av[++i]);
      //camera->lookFrom.y = atof(av[++i]);
      //camera->lookFrom.z = atof(av[++i]);
      //camera->lookAt.x = atof(av[++i]);
      //camera->lookAt.y = atof(av[++i]);
      //camera->lookAt.z = atof(av[++i]);
      //camera->lookUp.x = atof(av[++i]);
      //camera->lookUp.y = atof(av[++i]);
      //camera->lookUp.z = atof(av[++i]);
  rivl::box3fa worldBounds;
  string objFileName("/work/01336/carson/data/bunny.obj");
  vector<OBJ::Material> material;
  rivl::TriangleMesh *mesh = parseOBJ(objFileName,material,worldBounds);

  rivl::Accel* accel = new rivl::TriangleMeshBVH2(mesh);
  accel->build();
  //renderer = new rivl::SimpleAORenderer(accel);
  renderer = new rivl::RayCastRenderer(accel,rivl::RayCastRenderer::SHADE_Ng);
  cout << "objView: done parsing input file : #triangles = " << mesh->triangle.size() << endl;
  camera->lookAt   = worldBounds.center();
  rivl::vec3f dir  = 0.7f * rivl::vec3f(-.4f,-.5f,-1.f);
  // rivl::vec3f dir  = 0.8f * rivl::vec3f(-1.f,-.5f,.4f);
  camera->lookFrom = camera->lookAt - rivl::length(worldBounds.diagonal()) * dir;
  int res[2];
  res[0] = params.width;
  res[1] = params.height;
  camera->aspect = res[0]/float(res[1]);
  camera->upload();
  setSize(params.width, params.height);

  return;
#if 0

  _rank = -1;
#ifdef USE_MPI
  _rank = MPI::COMM_WORLD.Get_rank();
  MPI_Comm_size(MPI_COMM_WORLD, &_numProcs);
  GetVar<int>("GLURAY_CACHEFRAC", cacheFraction);
  GetVar<bool>("GLURAY_DEPTH", _depth);

#endif
  cerr << "initializing GLuRay\n";
  lights = new LightSet();
  gl_lights[0].diffuse = Color(RGB(1,1,1));
  gl_lights[0].specular = Color(RGB(1,1,1));
  gl_lights[0].pos = Vector(0,0,1);
  gl_lights[0].w = 0;
  updateLights();
  setColor(current_color.color[0], current_color.color[2], current_color.color[3], current_color.a);
  updateMaterial();
  //  current_material= new Phong(Color(RGBColor(1,1,1)),
  //			      Color(RGBColor(.6,.6,.6)), 32, (ColorComponent)params.reflectivity);
  //current_material = new AmbientOcclusion(current_material, 100.0,20);
  current_normal = Vector(0,1,0);
  current_transform.initWithIdentity();
  current_bgcolor = params.bgcolor;
  //  background = new ConstantBackground(current_bgcolor.color);
  //camera = new PinholeCamera(params.camera_eye, params.camera_dir, params.camera_up, params.camera_hfov, params.camera_vfov);
  updateBackground();
  if (!current_scene)
    current_scene = new MScene();
  if (!next_scene)
    next_scene = new MScene();
  //DEBUG: insert dummy object to avoid DynBVH from crashing!
  //   if (scene->world->getVectorOfObjects().empty())
  current_scene->world->add(new Sphere(new Lambertian(Color(RGBColor(current_bgcolor.color[0],current_bgcolor.color[1],current_bgcolor.color[2]))), Vector(0,0,0), Manta::Real(0e-6)));

#if RUN_CLIENT
  if (!client_running)
  {
    client_running = true;
    pthread_t thread;
    cout << "run client\n";
    int err = pthread_create(&thread, 0, clientLoop, this);
    if (err){
      printf("ERROR; return code from pthread_create() is %d\n", err);
      exit(-1);
    }
  }
#endif


  //GetVariables();
  //  cout << "setting up manta\n";
  int argc = 0;
  char **argv = NULL;
#if HAVE_IEEEFP_H
  fpsetmask(FP_X_OFL|FP_X_DZ|FP_X_INV);
#endif

  // Copy args into a vector<string>
  vector<string> args;
  for(int i=1;i<argc;i++)
    args.push_back(argv[i]);

  try {
    cout << "creating manta\n";
    ///////////////////////////////////////////////////////////////////////////
    // Create Manta.
    rtrt = createManta();
    updateCamera();

    rtrt->setDisplayBeforeRender(false);

    cout << "creating factory\n";
    // Create a Manta Factory.
    factory = new Factory( rtrt );


    // Use one worker by default.
    /*#ifdef USE_MPI*/
    //if (rank == 1)
    //rtrt->changeNumWorkers(1);
    //else if (rank == 0)
    //rtrt->changeNumWorkers(Max(2, Min(4, num_threads-1)));
    //else
    //rtrt->changeNumWorkers(num_threads);
    //#else
    //rtrt->changeNumWorkers(num_threads);
    //#endif

    setNumThreadsCallback(0,1);  //DEBUG: breaking in SCIRun

    // Default options.
    if (_depth)
    {
      if(!factory->selectImageType("rgba8zfloat"))
        throw InternalError("default image not found");
    }
    else
    {
      if(!factory->selectImageType("rgb8"))
        throw InternalError("default image not found");
    }
    if (params.shadows)
      factory->selectShadowAlgorithm("hard");
    else
      factory->selectShadowAlgorithm("noshadows");

    // if(!factory->selectShadowAlgorithm("noshadows"))
    //           if(!factory->selectShadowAlgorithm("hard"))
    // throw InternalError("default shadow algorithm not found" );

    // Defaults for command line args.
    string stack_file = "";
    bool haveUI = false;
    bool channelCreated=false;
    bool stereo = false;
    bool timeView = false;
    vector<string> timeViewArgs;
    Color bgcolor;
    bool override_scene_bgcolor = false;
    int maxDepth = -1;          // -1 is invalid and represent unset state.

    // ImageDisplay *display;
    //      // if (!window_id)
    //      //   { display = new Gl2MantaDisplay(0,0);

    //      //         UserInterface* ui = factory->createUserInterface("X");
    //      //         if (!ui) throw UnknownComponent( "Null user interface not found", "");
    //      //         ui->startup();
    //      //      haveUI = true;

    //      // } else {
    //      //   display = new Gl2MantaDisplay(0,window_id);
    //      // }
    cout << "creating sync_display\n";
    //   if(!sync_display)
    {
      vector<string> vs;
      sync_display = new Manta::SyncDisplay( vs );
      // TODO: memory leak, NullDisplay is not deleted
      sync_display->setChild(  new Manta::NullDisplay(vs)  );
      //    sync_display->setChild(new Manta::FileDisplay(vs) );
    }
    //copy_display = new Manta::CopyDisplay(vs);
    //copy_display->setChild(  new Manta::NullDisplay(vs)  );

#if USE_MPI
    //  if (rank <= 0)
    {
      channel_id = rtrt->createChannel( sync_display,
          camera, stereo, params.width, params.height);
    }
    /*else
      {
      vector<string> args;
      channel_id = rtrt->createChannel( new NullDisplay(args),
      camera, stereo, params.width, params.height);
      }*/
#else
    channel_id = rtrt->createChannel( sync_display,
        camera, stereo, params.width, params.height);
#endif

    ///////////////////////////////////////////////////////////////////////////
    // Use defaults if necessary.

    // Check to see if a channel  was created.
    if(!channelCreated){
      //      ImageDisplay *display = factory->createImageDisplay( "opengl" );
      //XVisualInfo* visual_info;
      //GLXDrawable drawable;
      //ImageDisplay* display = GLXImageDisplay(visual_info, drawable);
      //rtrt->createChannel(display,currentCamera,stereo,xres,yres);
      //      rtrt->createChannel(display, currentCamera, stereo, xres, yres);
    }

    // Check to see if a UI was specified
    if(!haveUI){
      UserInterface* ui = factory->createUserInterface("null");

      ui->startup();
    }

    // Check if default scene should be used.
    //  if(rtrt->getScene()==0){
    // current_scene = new MScene();

    //NOTE: this is added because dynbvh bombs on empty scenes
    current_scene->world->add(new Sphere(current_material, Vector(0,0,0), Manta::Real(0e-6)));

    //rtrt->setScene(scenet);
    rtrt->setScene(current_scene->scene);
    // }


    // rtrt->registerSerialAnimationCallback(Callback::create(this,
    // 		    	  &RIVLManager::buildAccelerationCallback));
    //  }

    //    ready.down();
    // done.down();




    /*   if (!rendering) {
         rendering = true;
    //     cout << "gl2manta rendering\n";
    // rtrt->addTransaction( "setScene",
    //		Callback::create(this, &RIVLManager::updateScene));

    cout << "starting rendering\n";
    if (frame_lag)
    rtrt->beginRendering(false);
    else
    {
    rtrt->beginRendering(false);
    }
    cout << "rendering started\n";
    }
     */


#ifdef USE_MPI
    if(!factory->selectLoadBalancer("MPI_LoadBalancer(-granularity 100 -masterGranularity 4)"))
      throw InternalError("MPI load balancer not found");

    //if(!factory->selectImageTraverser("tiled(-square)"))
    //  throw InternalError("default image traverser not found");
    if(!factory->selectImageTraverser("MPI_ImageTraverser(-square)"))
      throw InternalError("MPI image traverser not found");

    //if(!factory->selectLoadBalancer("workqueue(-granularity 60)"))
    //   throw InternalError("default load balancer not found");

    //   if(!factory->selectImageTraverser("tiled(-square)"))
    //    throw InternalError("default image traverser not found");
#else
    if(!factory->selectLoadBalancer("workqueue(-granularity 60)"))
      throw InternalError("default load balancer not found");

    if(!factory->selectImageTraverser("tiled(-square)"))
      throw InternalError("default image traverser not found");
#endif

    //    if(!factory->selectPixelSampler("singlesample"))
    stringstream s;
    if (params.num_samples > 1)
      s << "regularsample (-numberOfSamples " << params.num_samples << ")";
    else
      s << "singlesample";
    if(!factory->selectPixelSampler(s.str()))
      throw InternalError("default pixel sampler not found");

    if(!factory->selectRenderer("raytracer"))
      //	    if(!factory->selectRenderer("pathtracer"))
      throw InternalError("default renderer not found");

} catch (Exception& e) {
  cerr << "manta.cc (top level): Caught exception: " << e.message() << '\n';
  Thread::exitAll( 1 );
  assert(0);
} catch (std::exception e){
  cerr << "manta.cc (top level): Caught std exception: "
                                 << e.what()
                                            << '\n';
  Thread::exitAll(1);
  assert(0);
} catch(...){
  cerr << "manta.cc (top level): Caught unknown exception\n";
  Thread::exitAll(1);
  assert(0);
}

#if USE_MPI
MPI_LoadBalancer::setNumRenderThreadsPerNode(rtrt->numWorkers());
#endif //USE_MPI


//  if (!frame_lag)
//    sync_display->waitOnFrameReady();
#endif
cout << "initialization done\n";
initialized = true;
}



//TODO: updating pixelsampler mid flight crashes manta
void RIVLManager::setNumSamples(int,int,int samples)
{
  cout << "setting samples\n";
  params.num_samples = samples;
  stringstream s;
  if (params.num_samples > 1)
    s << "regularsample (-numberOfSamples " << params.num_samples << ")";
  else
    s << "singlesample";
  //if(!factory->selectPixelSampler(s.str()))
  //{}
  vector<string> args;
  args.push_back("-numberOfSamples");
  args.push_back("8");
  //PixelSampler* ps = new RegularSampler(args);
  //rtrt->setPixelSampler(ps);
  //  assert(0);
  cout << "set num samples to: " << samples << endl;
}

void RIVLManager::setNumThreads(int t)
{
}



size_t RIVLManager::generateNID()
{
  return ++_nid_counter;
}

Renderable* RIVLManager::getRenderable(size_t nid)
{
  return _map_renderables[nid];
}


void RIVLManager::render()
{
  renderer->render(camera, fb);
  fb->download();

  glPixelStorei(GL_UNPACK_ROW_LENGTH, fb->size.x);
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glPixelStorei(GL_PACK_ALIGNMENT, 1);
      glDisable(GL_DEPTH_TEST);
      glDisable(GL_SCISSOR_TEST);
      glDisable(GL_ALPHA_TEST);

  glDrawPixels(fb->size.x, fb->size.y, GL_RGBA, GL_UNSIGNED_BYTE, fb->h_mem);

#if 0
  //MPI_Barrier(MPI_COMM_WORLD);
  //DEBUG("RIVLManager::render\n");
  //LOGSTARTC("RIVLManager::render", 0.4,0.4,0.0);
  static int mpiCounter = 0;
  mpiCounter++;
  //printf("rank: %d RIVLManager::render %d\n", _rank, mpiCounter);
  /*MPI_Status stat;
    static vector<int> renderProcNums;
    static int renderProcNum = -1;
    renderProcNums.resize(0);
    if (mpiCounter < 10)
    {
    MPI_Request req[_numProcs];
    MPI_Status stats[_numProcs];
    if (_rank > 0)
    {
    unsigned char num=1;
    MPI_Isend(&num, 1, MPI_BYTE, 0, 843, MPI_COMM_WORLD, &req[_rank]);
    printf("isend rank %d run %d\n", _rank, mpiCounter);
  //sleep(12);
  MPI_Wait(&req[_rank], stats);
  }
  else //rank == 0
  {
  for (int i = 1; i < _numProcs; i++)
  {
  unsigned char num=0;
  MPI_Irecv(&num, 1, MPI_BYTE, i, 843, MPI_COMM_WORLD, &req[i]);
  }
  sleep(2);
  for (int i = 1; i < _numProcs; i++)
  {
  int tag=0;
  MPI_Test(&req[i], &tag, &stat);
  if (tag)
  {
  printf("found pvrendererproc\n");
  renderProcNums.push_back(i);
  //  MPI_Waitall(1, &req[i], &stat);
  }
  else
  {
  printf("did not find pvrendererproc %d of %d %d\n", i, _numProcs, mpiCounter);
  MPI_Cancel(&req[i]);
  }
  }
  //MPI_Waitall(_numProcs, req, stats);

  }
  }
  if (_rank == 0)
  renderProcNum = renderProcNums.size();
   */
  /*if (mpiCounter == 2)
    {
  //vector<int>::iterator itr = std::find(renderProcNums.begin(), renderProcNums.end(), _rank);
  //bool found=(itr != renderProcNums.end());
  if (_rank == 0)
  {
  for (int i = 0; i < renderProcNum; i++)
  {
  MPI_Send(&renderProcNum, 1, MPI_INT, renderProcNums[i], 876, MPI_COMM_WORLD);
  MPI_Send(&renderProcNums[0], renderProcNum, MPI_INT, renderProcNums[i], 877, MPI_COMM_WORLD);
  }

  }
  else //if (found)
  {
  MPI_Recv(&renderProcNum, 1, MPI_INT, 0, 876, MPI_COMM_WORLD, &stat);
  renderProcNums.resize(renderProcNum);
  MPI_Recv(&renderProcNums[0], renderProcNum, MPI_INT, 0, 877, MPI_COMM_WORLD, &stat);
  }
  //else
  //  printf("renderproc %d called but was not called first frame\n", _rank);
  renderProcNums.push_back(0);
  renderProcNum++;
  }
  if (mpiCounter < 2)
  return;
   */
  /*if (_rank == 0)
    {
    stringstream sstr;
    for (int i =0; i < renderProcNum; i++)
    sstr << renderProcNums[i] << " ";
    printf("rank: %d renderProcNum: %d %s\n", _rank, renderProcNum, sstr.str().c_str());
    }
   */

  /*MPI_Comm pv_comm, world_comm;
    MPI_Group pv_group;

    MPI_Comm_group(MPI_COMM_WORLD, &world_comm);
    MPI_Group_incl(world_comm, renderProcNum, &renderProcNums[0], &pv_group);
    MPI_Comm_create(MPI_COMM_WORLD, pv_group, &pv_comm);
   */

  //MPI_Barrier(pv_comm);
  //MPI_Barrier(MPI_COMM_WORLD);
  //MPI_Barrier(MPI_COMM_WORLD);
  //DEBUG("RIVLManager::render2\n");
  //return;
  static CDTimer timer;
  timer.start();

#if USE_MPI
  MPI_Barrier(MPI_COMM_WORLD);
  int res[2];
  res[0] = params.width;
  res[1] = params.height;
  MPI_Bcast(&res, 2, MPI_INT, 0, MPI_COMM_WORLD);
  setSize(res[0],res[1]);

  DEBUG("RIVLManager::render done syncing resolution rank:\n");

#endif


#ifndef USE_MPI
  if (mpiCounter > 8)
#endif
  {
    if (!rendering) {
      rendering = true;
      //     cout << "gl2manta rendering\n";
      // rtrt->addTransaction( "setScene",
      //		Callback::create(this, &RIVLManager::updateScene));

      printf("rank: %d starting rendering\n", _rank);
      if (frame_lag)
        rtrt->beginRendering(false);
      else
      {
        rtrt->beginRendering(false);
      }
      //MPI_Barrier(MPI_COMM_WORLD);
      printf("rank: %d rendering started\n", _rank);
      if (!frame_lag)
        sync_display->waitOnFrameReady();
#if USE_MPI
      MPI_Barrier(MPI_COMM_WORLD);
#endif
      printf("rank: %d wait on frameready\n", _rank);
    }
  }

  if (dirty_renderParams)
  {
    printf("\n\nUPDATING RENDER PARAMS\n\n");
    GLuRayRenderParameters p = params;
    setRenderParametersString(new_renderParamsString, false);
    GLuRayRenderParameters p2 = params;
    cout << "\n\nCOMPARISON: " << p.num_samples << " " << p2.num_samples << endl << endl;
    if(p.num_samples != p2.num_samples || p.shadows != p2.shadows)
    {
      cout << "\n\nNEEDS RELAUNCH\n\n";
      relaunch = true;
    }
    dirty_renderParams = false;
  }

  if (auto_camera) {
    BBox bbox;
    PreprocessContext context2(rtrt, 0, 1, lights);

    current_scene->world->preprocess(context2);
    current_scene->world->computeBounds(context2, bbox);
    rtrt->getCamera(0)->autoview(bbox);
  }

  // static int frameNumber = 0;
  // frameNumber++;
  /*if (frameNumber == 1)
    LogManager::GetSingleton()->SetEnabled(false);
    if (frameNumber == 30)
    LogManager::GetSingleton()->SetEnabled(true);
    if (frameNumber == 40)
    {
    LOGSCLOSE();
    LogManager::GetSingleton()->SetEnabled(false);
    }*/

  static CDTimer timer3;
  timer3.start();
#if USE_MPI
  LOGSTART("syncInstances");
  syncInstances();
  LOGSTOP("syncInstances");
#endif  //USE_MPI
  timer3.stop();
  //printf("rank: %d sync time: %f\n", _rank, timer3.getDelta());

  DEBUG("wait on frame ready\n");
  static CDTimer timer2;
  timer2.start();
  //Manta::LogManager::GetSingleton()->SetEnabled(true);
  LOGSTARTC("RIVLManager::render internal", 0.7,0.5,0.0);
#ifndef USE_MPI
  if (mpiCounter > 8)  //TODO: DEBUG: HACK: this is a blatant hack to fix a bug that was unreproducable on my desktop. according to gdb it was crashing in dynbvh updatebounds but the line was over a seemingly valid call to the objs.
#endif
  {
    if (!frame_lag)
    {
      sync_display->doneRendering();
      sync_display->waitOnFrameReady();
    }
    if (frame_lag)
      sync_display->waitOnFrameReady();
  }

  DEBUG("wait on frame ready done\n");
  LOGSTOP("RIVLManager::render internal");
  //MPI_Barrier(MPI_COMM_WORLD);
  timer2.stop();
  //printf("rank: %d internal render time: %f\n", _rank, timer2.getDelta());
  //static CDTimer timer4;
  //timer4.start();
#if !USE_MPI
  displayFrame();
#endif
  //timer4.stop();
  //printf("rank: %d display time: %f\n", _rank, timer4.getDelta());


  //LOGSTOP("copy_image");
  //LOGSTARTC("render_post", 0.4,0.0,0.0);

  // glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

  current_scene->world->shrinkTo(0,false);
  current_scene->scene->setBackground(background);
  current_scene->scene->setLights(lights);
  // current_scene->clearInstances();
  current_scene->instances.resize(0);



  /* if (auto_camera) {
     BBox bbox;
     PreprocessContext context2(rtrt, 0, 1, lights);

     rtrt->getScene()->getObject()->computeBounds(context2,bbox);
     cout << "bbox: " << bbox << endl;
     rtrt->getCamera()->autoview(bbox);

     }*/


  //  rtrt->getCamera(0)->output(cout);

  //add transactions to preprocess all renderables
  // for(int i =0; i < next_scene->numInstances(); i++)

  //TODO: this is a bad way to do autocamera!  rewrite
  //BBox bbox;
  //PreprocessContext context2(rtrt, 0, 1, lights);
  /*if (auto_camera)
    {
    current_scene->world->preprocess(context2);
    current_scene->world->computeBounds(context2, bbox);
    }*/

  //  PreprocessContext context3(rtrt, 0, 1, lights);



  /*
   *ADD INSTANCES TO WORLD OBJECT
   */
  DEBUG("ADDING INSTANCES TO WORLD\n");
  size_t totalMeshSize = 0;
  for( std::vector<GRInstance>::iterator itr = next_scene->instances.begin(); itr !=
      next_scene->instances.end(); itr++)
  {
    MRenderable* mr = dynamic_cast<MRenderable*>(itr->renderable);
    stringstream str;
    //str << "adding instance into world with " << mr->_data->mesh->size() <<
    //" tris and transform: \n" << itr->transform << endl;
    //cerr << str.str();
    //if (mr->isBuilt())
    {
      DirtyInstance* di = new DirtyInstance(mr->instance, itr->transform);
      current_scene->instances.push_back(*itr);
      if (mpiCounter > 10)
        current_scene->world->add(di);
    }


    size_t meshsize = (sizeof(Vector)*mr->_data->mesh->vertices.size()+sizeof(unsigned int)*mr->_data->mesh->vertex_indices.size())/(1024*1024);
    totalMeshSize  += meshsize;
    //printf("rank: %d id: %d meshsize: %dMB\n", _rank, mr->getNID(), meshsize);
  }
  current_scene->world->add(new Sphere(current_material, Vector(0,0,0), Manta::Real(0e-6)));
  //printf("rank: %d total mesh size: %d\MB\n", _rank, totalMeshSize);


  //DEBUG: insert dummy object to avoid DynBVH from crashing!
  if (current_scene->world->getVectorOfObjects().empty())
  {
    current_scene->world->add(new Sphere(new Lambertian(Color(RGBColor(current_bgcolor.color[0],current_bgcolor.color[1],current_bgcolor.color[2]))), Vector(0,0,0), Manta::Real(0e-6)));
    cout << "scene empty\n";
  }
  /*
     BBox bbox;
     PreprocessContext context2(rtrt, 0, 1, lights);
     bool rotate = (params.rotate_speed != 0.0 || params.rotate_offset != 0.0);
     if(rotate || params.add_plane)
     {
     bbox = BBox(Vector(-.569, -.562,-1.532), Vector(.655, .638, -.269));
     current_scene->world->preprocess(context2);
  //current_scene->world->computeBounds(context2, bbox);
  //cout << "bounds: " << bbox <<endl;
  }

  DirtyInstance* rot;
  Group* world;
  GRInstance* last_instance = 0;
  if (rotate && !current_scene->instances.empty() && last_instance != &(current_scene->instances[0]))
  {
  last_instance = &(current_scene->instances[0]);
  static size_t frameNum = params.rotate_offset;

  Vector wmin(-.555, -.559, -1.5078), wmax(.622,.603, -.289);
  wmin = bbox.getMin();
  wmax = bbox.getMax();
  Vector wsize = wmax-wmin;
  Vector center = wmin + wsize/2.0;
  float offset = 0.1;
  double angle = double(frameNum)*params.rotate_speed;
  BasicCameraData data = camera->getBasicCameraData();
  data.lookat = center - Vector(0,0.13,0);
  float dist = -data.lookat[2];
  data.eye[0]  = sin(angle)*dist;
  data.eye[1] = center[1] + offset;
  data.eye[2]  = data.lookat[2]+cos(angle)*dist;
  data.up = Vector(0,1,0);
  camera->setBasicCameraData(data);

  frameNum++;
  }*/

  rtrt->setCamera(0,camera);



  /*if (params.add_plane)
    {
    Material* mat = new Phong(Color(RGB(1,1,1)), Color(RGB(0,0,0)), 32, 0.2);
    Vector wmin(-.555, -.559, -1.5078), wmax(.622,.603, -.289);
    wmin = bbox.getMin();
    wmax = bbox.getMax();
    Vector wsize = wmax-wmin;
    Vector center = wmin + wsize/2.0;
    Vector csize(-.1,100,-.1); // x and z are extensions from data
    float offset = 0.01;
    float radius = FLT_MAX;
    Primitive* prim = new Cylinder(mat, Vector(center[0], wmin[1] - offset-csize[1], center[2]), Vector(center[0], wmin[1] - offset, center[2]), radius);
    Primitive* top = new Disk(mat, Vector(center[0], wmin[1] - offset, center[2]), Vector(0,1,0), radius, Vector(0,1,0));
    current_scene->world->add(top);
    }*/

  /*
   *add transaction to preprocess global scene
   */
  current_scene->as->groupDirty();
  AccelWork* work = new AccelWork(current_scene->as, "global build\n");
  addWork(work);
  work->run();
  next_scene->instances.resize(0);
  //  PreprocessContext context2(rtrt, 0, 1, lights);
  //current_scene->world->preprocess(context2);



  if (render_once)
  {
    cout << "rendering once\n";
    sync_display->doneRendering();
    sync_display->waitOnFrameReady();
    sync_display->doneRendering();
    sync_display->waitOnFrameReady();
    render_once = false;
    popRenderParameters();
    relaunch = true;
  }

  if (lights_dirty)
    updateLights();

  //glFinish();
  if (frame_lag)
    sync_display->doneRendering();
  timer.stop();

  if (relaunch)
  {
    relaunch = false;

    cout << "killing manta\n";

    sync_display->abort();
    int t = rtrt->numWorkers();
    rtrt->changeNumWorkers(0);
    cout << "found t: " << t << endl;
    while (t != 0)
    {
      sync_display->doneRendering();
      t = rtrt->numWorkers();
      if (t!=0)
        sync_display->waitOnFrameReady();
      t = rtrt->numWorkers();
    }
    cout << "rtrt finish\n";
    rtrt->finish();
    cout << "block until finished\n";
    rtrt->blockUntilFinished();
    cout << "deleting rtrt\n";
    //delete rtrt;
    cout << "manta killed\n";
    rendering = false;
    init();
    rtrt->changeNumWorkers(params.num_threads);
    cout << "init after killed\n";
    cout.flush();
  }
  DEBUG("done rendering\n");
  //printf("rank: %d render time: %f\n", _rank, timer.getDelta());
  LOGSTOP("RIVLManager::render");
#if USE_MPI
//  MPI_Barrier(MPI_COMM_WORLD);
#endif
#endif
}


void RIVLManager::displayFrame()
{
#if 0
  if (!rendering)
    return;
  if (_rank > 0)
    return;
  LOGSTARTC("RIVLManager::displayFrame", 0.1,0.5,0.0);
  //sync_display->doneRendering();
#if USE_MPI
  //DEBUG("render barrier wait\n");
  //MPI_Barrier(MPI_COMM_WORLD);
  //DEBUG("render barrier passed\n");
#endif //USE_MPI

  DEBUG("copying image\n");
  static CDTimer displayTimer;
  displayTimer.start();

  const SimpleImageBase* image = dynamic_cast< const Manta::SimpleImageBase * >
    ( sync_display->getCurrentImage() );
  if (!image)
    return;
  char* data = static_cast< char * >( image->getRawData(0) );
  if (!data)
    return;

  DEBUG("copy image done\n");

  bool stereo;
  int xres, yres;
  sync_display->getCurrentImage()->
    getResolution( stereo, xres, yres );

  //glDisable(GL_TEXTURE_2D);
  //glDisable(GL_BLEND);

  int rowLength = image->getRowLength();
  DEBUG("draw pixels\n");
  static GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  int rwidth = viewport[2];
  int rheight = viewport[3];

  int mwidth, mheight;
  mwidth = min(xres, rwidth);
  mheight = min(yres, rheight);
  if (rwidth != xres || rheight != yres)
    setSize(rwidth, rheight);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, rowLength);
  //printf("mwidth mheight: %d %d\n", mwidth, mheight);
  // printf("mwh: %d %d, rwh: %d %d, xyres: %d %d, rowLength: %d\n", mwidth, mheight,
  //    rwidth, rheight, xres, yres, rowLength);
  // DEBUG("xresyres: " << xres << " " << yres << end;
  //cout << "viewport: " << rwidth << " " << rheight << endl;
  //cout << "minwin: " << mwidth << " " << mheight << endl;
  //static int once = 0;
  //if (once++ > 18)  //VAPOR hack... why is drawpixels suddenly crashing now?  context or viewport must be out of whack

  if (_depth)
  {
    glPushClientAttrib(GL_UNPACK_ROW_LENGTH | GL_UNPACK_ALIGNMENT | GL_PACK_ALIGNMENT );
    glPixelStorei(GL_UNPACK_ROW_LENGTH, rowLength);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    float* fdata = static_cast< float * >( image->getRawData(0) );
    if (mwidth*mheight > depth_data.size()) {
      //rgba_data.resize(xres*yres*3);
      depth_data.resize(mwidth*mheight);
      rgba_data.resize(mwidth*mheight);
    }

    //printf("mwidth %d mheight %d\n", mwidth, mheight);
    //static float* rgba_data = new float[1024*1024*4];
    int mhdiff = yres - mheight;
    int rhdiff = rheight - mheight;
    if (mhdiff != 0 || rhdiff != 0)
    {
      printf("manta sizes out of sync\n");
      //if (frame_lag)
      //  sync_display->doneRendering();
      //else
      //  sync_display->waitOnFrameReady();
      return; // CD DEBUG!!!! BADDDDD
    }
    /*GLdouble modelViewM[16];*/
    //GLdouble projectionM[16];
    //GLint viewportM[4];
    //glGetDoublev(GL_MODELVIEW, modelViewM);
    //glGetDoublev(GL_PROJECTION, projectionM);
    //glGetIntegerv(GL_VIEWPORT, viewportM);

    /*Vector fustrum[2];*/
    //gluUnProject(viewport[0], viewport[1],0.0,modelViewM,projectionM,viewportM,fustrum[0].x, fustrum[0].y, fustrum[0].z);
    //gluUnProject(viewport[0]+viewport[2], viewport[1]+viewport[3],0.0,modelViewM,projectionM,viewportM,fustrum[1].x, fustrum[1].y, fustrum[1].z);
    //float near fustrum[0].magnitude();
    //float far = (fustrum[1] - fustrum[0]).magnitude();
    _zNear = 444.24;
    _zFar = 909.98;  //TODO CARSONDEBUG: dont hardcode these!
    float zRangeInv = 1.0f/fabs(_zFar-_zNear);
    for(int j = 0; j < mheight; j++)
    {
      size_t mi = (( j + mhdiff)*rowLength )*2;
      size_t ti = (( j + rhdiff)*rwidth);
      for (int i= 0; i < mwidth; i++)
      {
        if ((mi+i*2)>= (xres*yres*2))
          printf("mindex out of range:%d\n", mi+i*2);
        else if ((ti+i)>= (xres*yres*4))
          printf("tindex out of range:%d\n", ti+i);
        else
        {
#if 0 //USE_MPI
          depth_data[ti+1] = (_rank==0) ? 0.1 : 0.9;
#else
          float depth = 0;
          size_t index = mi+i*2+1;
          //if (index < xres*yres*2)
          depth = fdata[index];
          //if (ti + i < depth_data.size())
          depth_data[ti+i] = std::min(1.0f, std::max(0.0f, float((depth-_zNear)*zRangeInv)));
          //depth_data[ti+i] = 10000.0f;
#endif


          rgba_data[ti+i] = fdata[mi + i*2];
          //
          //DEBUG: display depth
          //
#if 1
          {
            float nDepth = 0.5;
            //if (ti + i < depth_data.size())
            nDepth = depth_data[ti+i];

            //reinterpret_cast<char*>(&rgba_data[ti+i])[0] = nDepth*255.0;
            //reinterpret_cast<char*>(&rgba_data[ti+i])[1] = nDepth*255.0;
            //reinterpret_cast<char*>(&rgba_data[ti+i])[2] = nDepth*255.0;
            //reinterpret_cast<char*>(&rgba_data[ti+i])[0] = (_rank==0)?255:0;
            //reinterpret_cast<char*>(&rgba_data[ti+i])[1] = (_rank==1)?255:0;
            //reinterpret_cast<char*>(&rgba_data[ti+i])[2] = (_rank==2)?255:0;

            //reinterpret_cast<char*>(&rgba_data[ti+i])[0] = nDepth*255.0f;
            //reinterpret_cast<char*>(&rgba_data[ti+i])[1] = nDepth*255.0f;
            //reinterpret_cast<char*>(&rgba_data[ti+i])[2] = nDepth*255.0f;
            //reinterpret_cast<char*>(&rgba_data[ti+i])[3] = 255;

            //TODO:  hardcoding transparent background for now
            unsigned char* rgba = reinterpret_cast<unsigned char*>(&rgba_data[0]+ti+i);
            if (rgba[1] > 253 && rgba[2] > 253 )
              reinterpret_cast<unsigned char*>(&rgba_data[ti+i])[3] = 0;
          }
#endif
        }
      }

    }

    //glDisable(GL_DEPTH_TEST);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, mwidth);
    GLint rmode, dmode;
    glGetIntegerv(GL_READ_BUFFER, &rmode);
    glGetIntegerv(GL_DRAW_BUFFER, &dmode);
    glDrawBuffer(rmode);
    //glDrawBuffer(GL_BACK);
    //glEnable(GL_DEPTH_TEST);
    glDrawPixels(mwidth,mheight, GL_DEPTH_COMPONENT, GL_FLOAT, &depth_data[0]);
    glDisable(GL_DEPTH_TEST);
    glDrawPixels(mwidth,mheight,GL_RGBA,GL_UNSIGNED_BYTE, &rgba_data[0]);
    glEnable(GL_DEPTH_TEST);

    //glDrawBuffer(GL_FRONT);
    // glDrawPixels(mwidth,mheight,GL_RGBA,GL_UNSIGNED_BYTE, &rgba_data[0]);
    //glDrawPixels(mwidth,mheight, GL_DEPTH_COMPONENT, GL_FLOAT, &depth_data[0]);
    glDrawBuffer(dmode);
    glFinish();
    glPopClientAttrib();
  }
  else  //no depth buffer
  {
    if (_rank <= 0)
    {
      //glPushClientAttrib(GL_UNPACK_ROW_LENGTH | GL_UNPACK_ALIGNMENT | GL_PACK_ALIGNMENT );
      glPixelStorei(GL_UNPACK_ROW_LENGTH, rowLength);
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glPixelStorei(GL_PACK_ALIGNMENT, 1);
      glDisable(GL_DEPTH_TEST);
      glDisable(GL_SCISSOR_TEST);
      glDisable(GL_ALPHA_TEST);

      static CDTimer timer5;
      timer5.start();
      glDrawPixels(mwidth,mheight,GL_RGB,GL_UNSIGNED_BYTE, data);
      timer5.stop();
      //printf("rank: 0 drawpixels time: %f\n", timer5.getDelta());
      //glPopClientAttrib();
    }
  }

  if (params.write_to_file != "")
  {
    DEBUG("writing image\n");
    string filename = params.write_to_file;
    if (params.write_to_file == "generated")
    {
      char cfilename[256];
      static int frame_number = 0;
#if USE_MPI
      sprintf(cfilename, "render_%04d_%dx%d_%d.rgb", frame_number++, xres, yres, _rank);
#else
      sprintf(cfilename, "render_%04d_%dx%d.rgb", frame_number++, xres, yres);
#endif
      filename = string(cfilename);
    }
    //unsigned char* test = new unsigned char[xres*yres*3];
    //glReadPixels(0,0,xres,yres,GL_RGB, GL_UNSIGNED_BYTE, test);
    FILE* pFile = fopen(filename.c_str(), "w");
    assert(pFile);
    if (_depth)
    {
      fwrite((void*)&rgba_data[0], 1, mwidth*mheight*4, pFile);
      fclose(pFile);
      stringstream s("");
      //TODO: this fudge factor on teh sizes makes no sense... I'm assuming it's because they have row padding in the data but it doesn't show up in drawpixels... perplexing.  It can also crash just a hack for now
      s  << "convert -flip -size " << mwidth << "x" << mheight << " -depth 8 rgba:" << filename << " " << filename << ".png";
      system(s.str().c_str());
      //delete []test;

    }
    else
    {
      fwrite(data, 1, xres*yres*3, pFile);
      fclose(pFile);
      stringstream s("");
      //TODO: this fudge factor on teh sizes makes no sense... I'm assuming it's because they have row padding in the data but it doesn't show up in drawpixels... perplexing.  It can also crash just a hack for now
      s  << "convert -flip -size " << mwidth << "x" << mheight << " -depth 8 rgb:" << filename << " " << filename << ".png";
      system(s.str().c_str());
    }
    //delete []test;
  }

  DEBUG("draw pixels done \n");
  displayTimer.stop();
  //printf("rank: %d display time: %f\n", _rank, displayTimer.getDelta());
  LOGSTOP("RIVLManager::displayFrame");
#endif
}

void RIVLManager::syncInstances()
{}

void RIVLManager::updateCamera()
{
#if 0
  //  cout << "updateCamera\n";
  GLuRayRenderParameters& p = params;
#if DEBUG_MSGS
  printf("update camera hfov:%f vfov%f\n", p.camera_hfov, p.camera_vfov);
#endif
  //p.camera_hfov=p.camera_vfov=22.6;

  if (!camera)
  {
    if (p.camera == "pinhole")
      camera = new PinholeCamera(p.camera_eye, p.camera_dir, p.camera_up, p.camera_hfov, p.camera_vfov);
    else
      camera = new ThinLensCamera(p.camera_eye, p.camera_dir, p.camera_up, p.camera_hfov, p.camera_vfov, p.focalDistance, p.aperture);
  }
  else  //would be better to just use the new camera... but it seems these arent updated correctly anyway in manta so instead set cameradata.  You have to choose pinhole or thinlens at startup then
  {
    BasicCameraData data = camera->getBasicCameraData();
    data.lookat = p.camera_dir;
    data.eye = p.camera_eye;
    data.up = p.camera_up;
    data.hfov = p.camera_hfov;
    data.vfov = p.camera_vfov;
    camera->setBasicCameraData(data);
  }

  //TODO: memory leak!
  //   rtrt->addOneShotCallback(MantaInterface::Absolute, 0,
  //      Callback::create(this, &RIVLManager::setCameraCallback));
#endif
}

void RIVLManager::updateBackground()
{
#if 0
  //  cout << "updateBackground\n";
  current_bgcolor = params.bgcolor;
  if (params.env_map == "" || params.env_map == "none")
    background = new ConstantBackground(current_bgcolor.color);
  else
  {
    EnvMapBackground::MappingType mapping_type = EnvMapBackground::DebevecSphere;
    //CylindricalEqualArea;

    ImageTexture<Color>* t = LoadColorImageTexture( params.env_map, &std::cerr );
    t->setInterpolationMethod(ImageTexture<Color>::Bilinear);
    Vector up( 0.0f, 1.0f, 0.0f );
    Vector right( 1.0f, 0.0f, 0.0f );

    background =  new EnvMapBackground( t,
        mapping_type, right, up ) ;
  }
  //  cout << "done updateBackground\n";
#endif
}

void RIVLManager::addInstance(Renderable* ren)
{
  if (!rendering)
    return;
  if (!ren->isBuilt())
    return;
  next_scene->instances.push_back(GRInstance(ren, current_transform));
}

void RIVLManager::addRenderable(Renderable* ren)
{
#if 0
  MRenderable* mr = dynamic_cast<MRenderable*>(ren);
  if (!mr)
    return;
  printf("rank: %d %s: size: %d\n", _rank, __FUNCTION__, mr->getNumPrims());
  static int counter = 0;
    MPI_Comm_group(mworld, &world_group);

  //mr->setBuilt(false);
  next_scene->renderables.push_back(mr);
  _newRenderables.push_back(mr);
  printf("rank: %d %s: size: %d done\n", _rank, __FUNCTION__, mr->getNumPrims());
#endif
}

GeometryGenerator* RIVLManager::getGeometryGenerator(int type)
{
  return _gVoid;

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

RenderManager* createRIVLManager() { return RIVLManager::singleton(); }

