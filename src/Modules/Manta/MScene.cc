#include <CMakeDefines.h>

#include "MScene.h"
#include "MantaManager.h"
#include "GLuRayRenderParameters.h"

using namespace std;
using namespace Manta;



  MScene::MScene(string cam_type, float focal_d, float ap, string env_file)
: num_elements(0), camera(NULL), created(false), camera_type(cam_type), focal_distance(focal_d), aperture(ap), env_filename(env_file), icounter(0)
{
  camera =  MantaManager::singleton()->getCamera();

  build();
}
void MScene::build()
{
  GLuRayRenderParameters& p = MantaManager::singleton()->params;
  as = new DynBVH(DEBUG_MSGS);
  scene = new Scene();



  Material* red=new Phong(Color(RGBColor(0,0,0)),
      Color(RGBColor(0,0,0)), 32, (ColorComponent)0.0);


  world = new Group();

  EnvMapBackground::MappingType mapping_type = EnvMapBackground::CylindricalEqualArea;
  mapping_type = EnvMapBackground::DebevecSphere;

  if (env_filename == "")
    scene->setBackground(new ConstantBackground(MantaManager::singleton()->current_bgcolor.color));
  else
  {
    ImageTexture<Color>* t = LoadColorImageTexture( env_filename, &std::cerr );
    t->setInterpolationMethod(ImageTexture<Color>::Bilinear);
    Vector up( 0.0f, 1.0f, 0.0f );
    Vector right( 1.0f, 0.0f, 0.0f );

    scene->setBackground( new EnvMapBackground( t,
          mapping_type, right, up ) );
  }

  //world->add(new NullRenderable());
  as->setGroup(world);
  // as->rebuild(0,1);
  scene->setObject(as);


  LightSet* lights = MantaManager::singleton()->lights;
  //lights->add(new PointLight(Vector(-8,-5,-10), Color(RGBColor(.7,.7,.7))));
  scene->setLights(lights);
  //    scene->getRenderParameters().maxDepth = 5;

  scene->addBookmark("default view", Vector(3, 3, 2), Vector(0, 0, 0.3), Vector(0, 0, 1), 60, 60);

}

MScene::~MScene()
{

}

void MScene::setBGColor(const Color& color)
{
  scene->setBackground(new ConstantBackground(color));
}


// DirtyInstance& MScene::addInstance()
// {
//   if (icounter >= instances.size())
//     instances.resize(instances.size()+10);
//   return instances.at(icounter++);
// }

// DirtyInstance& MScene::addInstance(DirtyInstance& i) {
//   //addInstance() = i;
// }
