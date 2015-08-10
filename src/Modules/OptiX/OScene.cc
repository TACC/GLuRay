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


#include "OScene.h"
// #include "RIVLManager.h"
#include "GLuRayRenderParameters.h"

using namespace std;
// using namespace Manta;



  OScene::OScene()
{
 // camera =  MantaManager::singleton()->getCamera();

  build();
}
void OScene::build()
{
#if 0
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

#endif
}

OScene::~OScene()
{

}
