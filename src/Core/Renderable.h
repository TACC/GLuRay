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
