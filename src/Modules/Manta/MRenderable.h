#ifndef MRENDERABLE_H
#define MRENDERABLE_H

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

struct MData
{
public:
  Mesh* mesh;
  Group* group;
  size_t num_prims;   //NOTE: this should be the number of prims overall in group, the mesh could actually be empty!!!
  bool perVertexColors;
};


class MGeometryGenerator : public GeometryGenerator
{
public:
  MGeometryGenerator() {}
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z) = 0;
  virtual void addNormal(Manta::Real x, Manta::Real y, Manta::Real z) {}
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z) = 0;
  void setData(MData* data) { _data = data; }
protected:
  MData* _data;
};

//instead of sotring the entire display list, keep track of each
//begin end segment as a seperate item
//IMPORTANT:: Need to add as to work queue when mrenderable is finished, but only if it's MESH isn't empty!!!!!!
class MRenderable : public Renderable
{
public:
  MRenderable(MGeometryGenerator* gen);
  virtual ~MRenderable();
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
    MGeometryGenerator* mgg = dynamic_cast<MGeometryGenerator*>(gen);
    assert(mgg);
    mgg->setData(_data);
  }

  virtual bool isEmpty() { return _data->num_prims < 1; }  //NOTE: MESH could still be empty...
  virtual size_t getNumPrims() { return _data->num_prims; }  // NOTE: num prims of groups, MESH could still be empty
  Primitive* instance;
  AccelerationStructure* as;
//  Material* material;
  //texture
  MData* _data;
#if USE_MPI
  Mesh_DSM* meshDSM;
  DynBVH_D* asDSM;
#endif
};

class MGeometryGeneratorVoid: public MGeometryGenerator
{
public:
  MGeometryGeneratorVoid();
  virtual ~MGeometryGeneratorVoid();
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z) {}
  virtual void addNormal(Manta::Real x, Manta::Real y, Manta::Real z) {}
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z) {}
};


class MGeometryGeneratorTriangles : public MGeometryGenerator
{
public:
  MGeometryGeneratorTriangles()
  {}
  virtual ~MGeometryGeneratorTriangles();
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addNormal(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z);
};

class MGeometryGeneratorTriangleStrip : public MGeometryGenerator
{
public:
  MGeometryGeneratorTriangleStrip()
  {}
  virtual ~MGeometryGeneratorTriangleStrip();
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z);
};


class MGeometryGeneratorQuads : public MGeometryGenerator
{
public:
  MGeometryGeneratorQuads()
  {}
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z);
};

class MGeometryGeneratorQuadStrip : public MGeometryGenerator
{
public:
  MGeometryGeneratorQuadStrip()
  {}
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z);
};

class MGeometryGeneratorLines : public MGeometryGenerator
{
public:
  MGeometryGeneratorLines();
  virtual  ~MGeometryGeneratorLines();
  virtual void addVertex(Manta::Real x,Manta::Real y,Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z) {}
  Manta::Real radius;
  Vector last_vertex;
};

class MGeometryGeneratorLineStrip : public MGeometryGeneratorLines
{
public:
  MGeometryGeneratorLineStrip()
    :MGeometryGeneratorLines()
  {}
  virtual ~MGeometryGeneratorLineStrip() {}
  virtual void addVertex(Manta::Real x,Manta::Real y,Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z) {}
};

class NullRenderable : public PrimitiveCommon
{
public:
  NullRenderable() {}
  virtual void intersect(const RenderContext& context,
			 RayPacket& rays) {}
  virtual void computeNormal(const RenderContext& context,
			     RayPacket& rays) {}
  virtual void setTexCoordMapper(const TexCoordMapper* new_tex) {}
  virtual void computeBounds(const PreprocessContext& context, BBox& bbox) {}
};


#endif
