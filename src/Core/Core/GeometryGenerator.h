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

#ifndef GEOMETRYGENERATOR_H
#define GEOMETRYGENERATOR_H

#include <cstdlib>
#include "defines.h"

class GeometryGenerator
{
public:
  GeometryGenerator() :_vertCounter(0) {}
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z) = 0;
  virtual void addNormal(Manta::Real x, Manta::Real y, Manta::Real z) {
    _normal = Manta::Vector(x,y,z);
  }
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z)
  {
    _texCoord = Manta::Vector(u,v,w);
  }
  //
  // reset - resets vertex counter for primitives
  //
  virtual void reset() { _vertCounter = 0; }
protected:
  size_t _vertCounter;
  Manta::Vector _normal, _texCoord;
};

#endif
