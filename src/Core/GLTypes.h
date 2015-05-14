
#ifndef GLTYPES
#define GLTYPES

#include "defines.h"
#include "Work.h"
#include "GLuRayRenderParameters.h"
#include "GeometryGenerator.h"
//#include "Renderable.h"

#include <Interface/MantaInterface.h>
#include <Interface/Object.h>
#include <Model/Materials/Volume.h>


#include <queue>
#include <stack>
// using namespace Manta;



struct GLLight
{
	GLLight() : pos(0,0,1), ambient(Manta::RGBColor(0.0,0.0,0.0)), diffuse(Manta::RGBColor(0,0,0)), specular(Manta::RGBColor(0,0,0)), enabled(false), w(0.0)
	{}
  Manta::Vector pos;
  Manta::Color ambient, diffuse, specular;
  bool enabled;
  Manta::Real w;  // 0 is directional, 1 is point...
};
ostream& operator<<(ostream& out, GLLight& m);

class GLMaterial
{
public:
  GLMaterial() : ambient(Manta::RGBColor(0.2,0.2,0.2)), diffuse(Manta::RGBColor(0.8,0.8,0.8)), specular(Manta::RGBColor(0,0,0)), emissive(Manta::RGBColor(0,0,0)), shiny(0.0)
  {}
  Manta::Color ambient, diffuse, specular, emissive;
  float shiny;
};
ostream& operator<<(ostream& out, GLMaterial& m);


#endif
