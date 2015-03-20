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

#ifndef MDSMRENDERABLE_H
#define MDSMRENDERABLE_H

#include <Interface/MantaInterface.h>
#include <Interface/Scene.h>
#include <Interface/Object.h>
#include <Interface/Context.h>
#include <Core/Geometry/BBox.h>
#include <Core/Exceptions/Exception.h>
#include <Core/Exceptions/InternalError.h>
#include <Model/Instances/Instance.h>
#include <Model/TexCoordMappers/UniformMapper.h>
#include <Model/Groups/Group.h>
#include <Model/Primitives/MeshTriangle.h>
#include <Model/Primitives/PrimitiveCommon.h>
#include <UseMPI.h>
#ifndef USE_MPI
horrible error, file needs mpi support
#endif
#include "Mesh_DSM.h"

#include "defines.h"
#include "Renderable.h"

#include <cassert>

using namespace Manta;

struct MDSMData
{
public:
  Mesh_DSM* mesh;
  Group* group;
  size_t num_prims;   //NOTE: this should be the number of prims overall in group, the mesh could actually be empty!!!
  bool perVertexColors;
};


class MDSMGeometryGenerator : public GeometryGenerator
{
public:
  MDSMGeometryGenerator() {}
  virtual void addVertex(Real x, Real y, Real z) = 0;
  virtual void addNormal(Real x, Real y, Real z) {}
  virtual void addTextureCoord(Real u, Real v, Real w, Real z) = 0;
  void setData(MDSMData* data) { _data = data; }
protected:
  MDSMData* _data;
};

//instead of sotring the entire display list, keep track of each
//begin end segment as a seperate item
//IMPORTANT:: Need to add as to work queue when mrenderable is finished, but only if it's MESH isn't empty!!!!!!
class MDSMRenderable : public Renderable
{
public:
  MDSMRenderable(MDSMGeometryGenerator* gen);
  virtual ~MDSMRenderable();
  virtual void addVertex(Real x, Real y, Real z)
  {
    _generator->addVertex(x,y,z);
  }
  virtual void addNormal(Real x, Real y, Real z)
  {
    _generator->addNormal(x,y,z);
  }
  virtual void addTextureCoord(Real u, Real v, Real w, Real z)
  {
    _generator->addTextureCoord(u,v,w,z);
  }
  virtual void setGenerator(GeometryGenerator* gen)
  {
    _generator = gen;
    MDSMGeometryGenerator* mgg = dynamic_cast<MDSMGeometryGenerator*>(gen);
    assert(mgg);
    mgg->setData(_data);
  }

  virtual bool isEmpty() { return _data->num_prims < 1; }  //NOTE: MESH could still be empty...
  virtual size_t getNumPrims() { return _data->num_prims; }  // NOTE: num prims of groups, MESH could still be empty
  Primitive* instance;
  AccelerationStructure* as;
//  Material* material;
  //texture
  MDSMData* _data;
};

class MDSMGeometryGeneratorVoid: public MDSMGeometryGenerator
{
public:
  MDSMGeometryGeneratorVoid();
  virtual ~MDSMGeometryGeneratorVoid();
  virtual void addVertex(Real x, Real y, Real z) {}
  virtual void addNormal(Real x, Real y, Real z) {}
  virtual void addTextureCoord(Real u, Real v, Real w, Real z) {}
};


class MDSMGeometryGeneratorTriangles : public MDSMGeometryGenerator
{
public:
  MDSMGeometryGeneratorTriangles()
  {}
  virtual ~MDSMGeometryGeneratorTriangles();
  virtual void addVertex(Real x, Real y, Real z);
  virtual void addNormal(Real x, Real y, Real z);
  virtual void addTextureCoord(Real u, Real v, Real w, Real z);
};

class MDSMGeometryGeneratorTriangleStrip : public MDSMGeometryGenerator
{
public:
  MDSMGeometryGeneratorTriangleStrip()
  {}
  virtual ~MDSMGeometryGeneratorTriangleStrip();
  virtual void addVertex(Real x, Real y, Real z);
  virtual void addTextureCoord(Real u, Real v, Real w, Real z);
};


class MDSMGeometryGeneratorQuads : public MDSMGeometryGenerator
{
public:
  MDSMGeometryGeneratorQuads()
  {}
  virtual void addVertex(Real x, Real y, Real z);
  virtual void addTextureCoord(Real u, Real v, Real w, Real z);
};

class MDSMGeometryGeneratorQuadStrip : public MDSMGeometryGenerator
{
public:
  MDSMGeometryGeneratorQuadStrip()
  {}
  virtual void addVertex(Real x, Real y, Real z);
  virtual void addTextureCoord(Real u, Real v, Real w, Real z);
};

class MDSMGeometryGeneratorLines : public MDSMGeometryGenerator
{
public:
  MDSMGeometryGeneratorLines();
  virtual  ~MDSMGeometryGeneratorLines();
  virtual void addVertex(Real x,Real y,Real z);
  virtual void addTextureCoord(Real u, Real v, Real w, Real z) {}
  Real radius;
  Vector last_vertex;
};

class MDSMGeometryGeneratorLineStrip : public MDSMGeometryGeneratorLines
{
public:
  MDSMGeometryGeneratorLineStrip()
    :MDSMGeometryGeneratorLines()
  {}
  virtual ~MDSMGeometryGeneratorLineStrip() {}
  virtual void addVertex(Real x,Real y,Real z);
  virtual void addTextureCoord(Real u, Real v, Real w, Real z) {}
};

#endif
