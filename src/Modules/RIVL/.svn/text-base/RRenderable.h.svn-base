#ifndef RRENDERABLE_H
#define RRENDERABLE_H

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
#if USE_MPI
  #include "Mesh_DSM.h"
  #include "DynBVH_D.h"
#endif

#include "defines.h"
#include "Renderable.h"

#include <cassert>

using namespace Manta;

struct RData
{
public:
  size_t num_prims;
};


class RGeometryGenerator : public GeometryGenerator
{
public:
  RGeometryGenerator() {}
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z) = 0;
  virtual void addNormal(Manta::Real x, Manta::Real y, Manta::Real z) {}
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z) = 0;
  void setData(RData* data) { _data = data; }
protected:
  RData* _data;
};

//instead of sotring the entire display list, keep track of each
//begin end segment as a seperate item
//IMPORTANT:: Need to add as to work queue when mrenderable is finished, but only if it's MESH isn't empty!!!!!!
class RRenderable : public Renderable
{
public:
  RRenderable(RGeometryGenerator* gen);
  virtual ~RRenderable();
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z)
  {
    _generator->addVertex(x,y,z);
  }
  virtual void addNormal(Manta::Real x, Manta::Real y, Manta::Real z)
  {
    _generator->addNormal(x,y,z);
  }
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z)
  {
    _generator->addTextureCoord(u,v,w,z);
  }
  virtual void setGenerator(GeometryGenerator* gen)
  {
    _generator = gen;
    RGeometryGenerator* mgg = dynamic_cast<RGeometryGenerator*>(gen);
    assert(mgg);
    mgg->setData(_data);
  }

  virtual bool isEmpty() { return _data->num_prims < 1; }  //NOTE: MESH could still be empty...
  virtual size_t getNumPrims() { return _data->num_prims; }  // NOTE: num prims of groups, MESH could still be empty
  RData* _data;
};

class RGeometryGeneratorVoid: public RGeometryGenerator
{
public:
  RGeometryGeneratorVoid();
  virtual ~RGeometryGeneratorVoid();
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z) {}
  virtual void addNormal(Manta::Real x, Manta::Real y, Manta::Real z) {}
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z) {}
};


class RGeometryGeneratorTriangles : public RGeometryGenerator
{
public:
  RGeometryGeneratorTriangles()
  {}
  virtual ~RGeometryGeneratorTriangles();
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addNormal(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z);
};

class RGeometryGeneratorTriangleStrip : public RGeometryGenerator
{
public:
  RGeometryGeneratorTriangleStrip()
  {}
  virtual ~RGeometryGeneratorTriangleStrip();
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z);
};


class RGeometryGeneratorQuads : public RGeometryGenerator
{
public:
  RGeometryGeneratorQuads()
  {}
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z);
};

class RGeometryGeneratorQuadStrip : public RGeometryGenerator
{
public:
  RGeometryGeneratorQuadStrip()
  {}
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z);
};

class RGeometryGeneratorLines : public RGeometryGenerator
{
public:
  RGeometryGeneratorLines();
  virtual  ~RGeometryGeneratorLines();
  virtual void addVertex(Manta::Real x,Manta::Real y,Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z) {}
  Manta::Real radius;
  Vector last_vertex;
};

class RGeometryGeneratorLineStrip : public RGeometryGeneratorLines
{
public:
  RGeometryGeneratorLineStrip()
    :RGeometryGeneratorLines()
  {}
  virtual ~RGeometryGeneratorLineStrip() {}
  virtual void addVertex(Manta::Real x,Manta::Real y,Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z) {}
};

#endif
