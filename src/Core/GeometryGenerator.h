#ifndef GEOMETRYGENERATOR_H
#define GEOMETRYGENERATOR_H

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
#include <Model/Groups/Mesh.h>
#include <Model/Primitives/MeshTriangle.h>
#include <Model/Primitives/PrimitiveCommon.h>

#include <cstdlib>
#include "defines.h"
#include "GLTypes.h"

struct GeometryData
{
  GeometryData() {
    mesh = new Manta::Mesh(); num_prims = 0;
  }
  // OData();
  Manta::Mesh* mesh;
  size_t num_prims;
//  OSPGeometry ospMesh;
//  OSPModel ospModel;
//  OSPMaterial mat;
  GLMaterial glMaterial;
  // embree::Handle<embree::Device::RTMaterial> d_material;
  // embree::Handle<embree::Device::RTShape> d_mesh;
//  OGeometryType geomType; //geometry type: triangles, cylinders, spheres
};

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
  virtual void setData(GeometryData* data) { _data = data; }
  //
  // reset - resets vertex counter for primitives
  //
  virtual void reset() { _vertCounter = 0; }
protected:
  size_t _vertCounter;
  Manta::Vector _normal, _texCoord;
  GeometryData* _data;
};

class GeometryGeneratorVoid: public GeometryGenerator
{
public:
  GeometryGeneratorVoid();
  virtual ~GeometryGeneratorVoid();
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z) {}
  virtual void addNormal(Manta::Real x, Manta::Real y, Manta::Real z) {}
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z) {}
};

class GeometryGeneratorTriangles : public GeometryGenerator
{
public:
  GeometryGeneratorTriangles()
  {}
  virtual ~GeometryGeneratorTriangles();
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addNormal(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z);
};

class GeometryGeneratorTriangleStrip : public GeometryGenerator
{
public:
  GeometryGeneratorTriangleStrip()
  {}
  virtual ~GeometryGeneratorTriangleStrip();
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addNormal(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z);
};


class GeometryGeneratorQuads : public GeometryGenerator
{
public:
  GeometryGeneratorQuads()
  {}
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z);
};

class GeometryGeneratorQuadStrip : public GeometryGenerator
{
public:
  GeometryGeneratorQuadStrip()
  {}
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z);
};

class GeometryGeneratorLines : public GeometryGenerator
{
public:
  GeometryGeneratorLines();
  virtual  ~GeometryGeneratorLines();
  virtual void addVertex(Manta::Real x,Manta::Real y,Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z) {}
  Manta::Real radius;
  Manta::Vector last_vertex;
};

class GeometryGeneratorPoints : public GeometryGenerator
{
public:
  GeometryGeneratorPoints();
  virtual  ~GeometryGeneratorPoints();
  virtual void addVertex(Manta::Real x,Manta::Real y,Manta::Real z);
};

class GeometryGeneratorLineStrip : public GeometryGeneratorLines
{
public:
  GeometryGeneratorLineStrip()
  :GeometryGeneratorLines()
  {}
  virtual ~GeometryGeneratorLineStrip() {}
  virtual void addVertex(Manta::Real x,Manta::Real y,Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z) {}
};

#endif
