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
