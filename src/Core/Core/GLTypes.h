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
using namespace Manta;



struct GLLight
{
	GLLight() : pos(0,0,1), ambient(RGBColor(0.0,0.0,0.0)), diffuse(RGBColor(0,0,0)), specular(RGBColor(0,0,0)), enabled(false), w(0.0)
	{}
  Vector pos;
  Color ambient, diffuse, specular;
  bool enabled;
  Manta::Real w;  // 0 is directional, 1 is point...
};
ostream& operator<<(ostream& out, GLLight& m);

class GLMaterial
{
public:
  GLMaterial() : ambient(RGBColor(0.2,0.2,0.2)), diffuse(RGBColor(0.8,0.8,0.8)), specular(RGBColor(0,0,0)), emissive(RGBColor(0,0,0)), shiny(0.0)
  {}
  Color ambient, diffuse, specular, emissive;
  float shiny;
};
ostream& operator<<(ostream& out, GLMaterial& m);


#endif
