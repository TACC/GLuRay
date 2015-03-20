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

#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "GeometryGenerator.h"
#include "defines.h"
#include "GLTypes.h"

class Renderable
{
public:
  Renderable(GeometryGenerator* gen) { _generator = gen; _nid=0; _built = false;}
  virtual ~Renderable() {}
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z) = 0;
  virtual void addNormal(Manta::Real x, Manta::Real y, Manta::Real z) = 0;
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z) =0;
  virtual void setGenerator(GeometryGenerator* gen)=0;
  virtual bool isEmpty() =0;  //NOTE: MESH could still be empty...
  virtual size_t getNumPrims() { return 0; }  // NOTE: num prims of groups, MESH could still be empty
  void setNID(size_t& nid_) { _nid = nid_;}
  size_t getNID() { return _nid;}
  bool isBuilt() {return _built; }
  void setBuilt(bool st) { _built = st; }
  GLMaterial glMaterial;
protected:
  bool _built;
  GeometryGenerator* _generator;
  size_t _nid; //network id
};

#endif
