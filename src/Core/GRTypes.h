#ifndef GRTYPES
#define GRTYPES

#include "defines.h"
#include "Work.h"
#include "GLuRayRenderParameters.h"
#include "GeometryGenerator.h"
#include "Renderable.h"

#include <Interface/MantaInterface.h>
#include <Interface/Object.h>
#include <Model/Materials/Volume.h>


#include <queue>
#include <stack>
// using namespace Manta;

struct GRInstance
{
  GRInstance()
  {
    renderable = NULL;
  }
  GRInstance(Renderable* ren, const Manta::AffineTransform& tran)
  {
    renderable = ren; transform = tran;
  }
  Renderable* renderable;
  Manta::AffineTransform transform;
  //GLMaterial* material;
};

#endif
