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

/*
  For more information, please see: http://software.sci.utah.edu

  The MIT License

  Copyright (c) 2005
  Scientific Computing and Imaging Institute, University of Utah

  License for the specific language governing rights and limitations under
  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*/

//#include <Model/Instances/Instance.h>
#include "DirtyInstance.h"
#include <Model/Instances/MPT.h>
#include <Interface/Context.h>
#include <Interface/RayPacket.h>
#include <Core/Exceptions/BadPrimitive.h>
#include <Core/Exceptions/InternalError.h>
#include <Core/Geometry/BBox.h>
#include <Core/Math/MiscMath.h>
#include <Core/Util/Preprocessor.h>
#include <Core/Util/UpdateGraph.h>

#include <iostream>
#include <sstream>
#include <cassert>
using namespace Manta;
using namespace std;

// TODO:
// 1. Only transform hit position instead of ray origin/direction (computeNormal and texCoords)
// 2. Avoid redundant transformation in texCooords

DirtyInstance::DirtyInstance(Object* instance, const AffineTransform& transform)
  : instance(instance), transform(transform),_dirty(true)
{
  // By default, use the texture coordinates of the child object
  tex = this;

  // Compute the inverse transform
  transform_inv = transform.inverse();
}

DirtyInstance::DirtyInstance() : instance(NULL),_dirty(true)
{
  // By default, use the texture coordinates of the child object
  tex = this;
}

DirtyInstance::~DirtyInstance()
{
}


Primitive* DirtyInstance::clone(CloneDepth depth, Clonable* incoming)
{
  DirtyInstance *copy;
  if (incoming)
    copy = dynamic_cast<DirtyInstance*>(incoming);
  else
    copy = new DirtyInstance();

  copy->tex = tex;   //TODO: is this what we want to do with tex when cloning?

  copy->instance = reinterpret_cast<Object*>(instance->clone(depth, copy->instance));
  copy->setTransform(transform);
  return copy;
}

Interpolable::InterpErr DirtyInstance::serialInterpolate(const std::vector<keyframe_t> &keyframes)
{
  for (int r=0; r<3; ++r)
    for (int c=0; c<4; ++c)
      transform.mat[r][c] = 0;

  vector<keyframe_t> instance_keyframes(keyframes);

  for (size_t i=0; i < keyframes.size(); ++i) {
    Interpolable::keyframe_t kt = keyframes[i];
    DirtyInstance *instance = dynamic_cast<DirtyInstance*>(keyframes[i].keyframe);
    if (instance == NULL)
      return notInterpolable;

    //TODO: This is most likely not the right way to interpolate
    //between two affine transform matrices.  Furthermore, this should
    //be implemented in the AffineTransform class.
    for (int r=0; r<3; ++r)
      for (int c=0; c<4; ++c)
        transform.mat[r][c] += instance->transform.mat[r][c]*keyframes[i].t;

    instance_keyframes[i].keyframe = instance->instance;
  }

  transform_inv = transform.inverse();

  instance->serialInterpolate(instance_keyframes);

  return success;
}



void DirtyInstance::setTransform(AffineTransform new_transform) {
  transform = new_transform;
  transform_inv = transform.inverse();
}

Object* DirtyInstance::getInstance() {
  return instance;
}

const Object* DirtyInstance::getInstance() const {
  return instance;
}

void DirtyInstance::preprocess(const PreprocessContext& context)
{
  //cerr << MANTA_FUNC << endl;
  //cerr << " Before instance->preprocess (thread " << context.proc << " of " << context.numProcs << ")\n";
  if (_dirty)
  {
    _dirty=false;
    instance->preprocess(context);
  }
  // TODO(bigler: change this to 0 when fixed)
  if (material != this) material->preprocess(context);
  //cerr << " After instance->preprocess (thread " << context.proc << " of " << context.numProcs << ")\n";
}

void DirtyInstance::addToUpdateGraph(ObjectUpdateGraph* graph,
                                ObjectUpdateGraphNode* parent) {
  ObjectUpdateGraphNode* node = graph->insert(this, parent);
  instance->addToUpdateGraph(graph, node);
}

void DirtyInstance::computeBounds(const PreprocessContext& context, BBox& bbox) const
{
  BBox ibox;
  instance->computeBounds(context, ibox);

  // Transform the eight corners of the child bounding box
  for(int i=0;i<8;i++)
    bbox.extendByPoint(transform.multiply_point(ibox.getCorner(i)));
}

#ifdef MANTA_SSE
// Compute 4 points at once
inline void MultiplyPointSSE(const AffineTransform& t,
                             __m128 x_in,
                             __m128 y_in,
                             __m128 z_in,
                             __m128& x_out,
                             __m128& y_out,
                             __m128& z_out) {
  x_out  = _mm_mul_ps(_mm_set1_ps(t.mat[0][0]), x_in);
  x_out  = _mm_add_ps(x_out, _mm_mul_ps(_mm_set1_ps(t.mat[0][1]), y_in));
  x_out  = _mm_add_ps(x_out, _mm_mul_ps(_mm_set1_ps(t.mat[0][2]), z_in));
  x_out  = _mm_add_ps(x_out, _mm_set1_ps(t.mat[0][3]));

  y_out  = _mm_mul_ps(_mm_set1_ps(t.mat[1][0]), x_in);
  y_out  = _mm_add_ps(y_out, _mm_mul_ps(_mm_set1_ps(t.mat[1][1]), y_in));
  y_out  = _mm_add_ps(y_out, _mm_mul_ps(_mm_set1_ps(t.mat[1][2]), z_in));
  y_out  = _mm_add_ps(y_out, _mm_set1_ps(t.mat[1][3]));

  z_out  = _mm_mul_ps(_mm_set1_ps(t.mat[2][0]), x_in);
  z_out  = _mm_add_ps(z_out, _mm_mul_ps(_mm_set1_ps(t.mat[2][1]), y_in));
  z_out  = _mm_add_ps(z_out, _mm_mul_ps(_mm_set1_ps(t.mat[2][2]), z_in));
  z_out  = _mm_add_ps(z_out, _mm_set1_ps(t.mat[2][3]));
}

inline void MultiplyVectorSSE(const AffineTransform& t,
                              __m128 x_in,
                              __m128 y_in,
                              __m128 z_in,
                              __m128& x_out,
                              __m128& y_out,
                              __m128& z_out) {
  x_out  = _mm_mul_ps(_mm_set1_ps(t.mat[0][0]), x_in);
  x_out  = _mm_add_ps(x_out, _mm_mul_ps(_mm_set1_ps(t.mat[0][1]), y_in));
  x_out  = _mm_add_ps(x_out, _mm_mul_ps(_mm_set1_ps(t.mat[0][2]), z_in));

  y_out  = _mm_mul_ps(_mm_set1_ps(t.mat[1][0]), x_in);
  y_out  = _mm_add_ps(y_out, _mm_mul_ps(_mm_set1_ps(t.mat[1][1]), y_in));
  y_out  = _mm_add_ps(y_out, _mm_mul_ps(_mm_set1_ps(t.mat[1][2]), z_in));

  z_out  = _mm_mul_ps(_mm_set1_ps(t.mat[2][0]), x_in);
  z_out  = _mm_add_ps(z_out, _mm_mul_ps(_mm_set1_ps(t.mat[2][1]), y_in));
  z_out  = _mm_add_ps(z_out, _mm_mul_ps(_mm_set1_ps(t.mat[2][2]), z_in));
}
#endif

void DirtyInstance::intersect(const RenderContext& context, RayPacket& rays) const
{
  //if (_dirty)
    //return;
  assert(!_dirty);  //TODO: CARSON DEBUG
  bool debugFlag = rays.getFlag(RayPacket::DebugPacket);
  if (debugFlag) {
    cerr << MANTA_FUNC << " called\n";
  }
  RayPacketData raydata;
  RayPacket instance_rays(raydata, RayPacket::UnknownShape, rays.begin(), rays.end(),
                          rays.getDepth(), 0);
  // TODO(boulos): Make this a lot cleaner and try to easily maintain
  // ray packet properties (probably best to just do so in specialized
  // instance classes though)


  // We setup the instance_rays to be normalized (makes it so we don't
  // need to worry about someone calling normalize directions for us
  // underneath us and then requiring a scaling on the end).
  //
  // Since we're an affine transform, the constant origin property
  // should be transferred as well.
  //
  // Finally, if the parent is a debug packet, we should be too.
  instance_rays.setFlag(
    RayPacket::NormalizedDirections |
    (rays.getAllFlags() & (RayPacket::ConstantOrigin | RayPacket::DebugPacket)));

  // Clears things for us, so we don't have to reproduce this code everywhere
  instance_rays.resetHits();
  Packet<Real> scales;
  Packet<Real> inv_scales;

  if(rays.getFlag(RayPacket::ConstantOrigin)){
    Vector o = transform_inv.multiply_point(rays.getOrigin(rays.begin()));

#define SCALAR_KERNEL_CONSTANT_ORIGIN \
    Vector dir = transform_inv.multiply_vector(rays.getDirection(i)); \
    Real length = dir.length(); \
    inv_scales.set(i, length);  \
    Real ilength = 1/length; \
    scales.set(i, ilength);                  \
    instance_rays.setRay(i, o, dir*ilength); \
    instance_rays.overrideMinT(i, rays.getMinT(i)*length);

#define SCALAR_KERNEL_NONCONSTANT_ORIGIN \
    Vector o = transform_inv.multiply_point(rays.getOrigin(i)); \
    SCALAR_KERNEL_CONSTANT_ORIGIN;

#ifdef MANTA_SSE

#define SSE_KERNEL_CONSTANT_ORIGIN \
    __m128 dir_x, dir_y, dir_z;                                               \
    MultiplyVectorSSE(transform_inv,                                          \
                      _mm_load_ps(&(rays.data->direction[0][i])),             \
                      _mm_load_ps(&(rays.data->direction[1][i])),             \
                      _mm_load_ps(&(rays.data->direction[2][i])),             \
                      dir_x, dir_y, dir_z);                                   \
    __m128 length = _mm_add_ps(_mm_mul_ps(dir_x, dir_x),                      \
                               _mm_add_ps(_mm_mul_ps(dir_y, dir_y),           \
                                          _mm_mul_ps(dir_z, dir_z)));         \
    length = _mm_sqrt_ps(length);                                             \
    _mm_store_ps(&(inv_scales.data[i]), length);                              \
    __m128 inv_length = _mm_div_ps(_mm_set1_ps(1.f), length);                 \
    _mm_store_ps(&(scales.data[i]), inv_length);                              \
                                                                              \
    _mm_store_ps(&(instance_rays.data->origin[0][i]), org_x);                 \
    _mm_store_ps(&(instance_rays.data->origin[1][i]), org_y);                 \
    _mm_store_ps(&(instance_rays.data->origin[2][i]), org_z);                 \
                                                                              \
    dir_x = _mm_mul_ps(dir_x, inv_length);                                    \
    dir_y = _mm_mul_ps(dir_y, inv_length);                                    \
    dir_z = _mm_mul_ps(dir_z, inv_length);                                    \
    _mm_store_ps(&(instance_rays.data->direction[0][i]), dir_x);              \
    _mm_store_ps(&(instance_rays.data->direction[1][i]), dir_y);              \
    _mm_store_ps(&(instance_rays.data->direction[2][i]), dir_z);              \
                                                                              \
    __m128 new_t = _mm_mul_ps(length, _mm_load_ps(&(rays.data->minT[i])));    \
    _mm_store_ps(&(instance_rays.data->minT[i]), new_t);

#define SSE_KERNEL_NONCONSTANT_ORIGIN \
    __m128 org_x, org_y, org_z;                                               \
    MultiplyPointSSE(transform_inv,                                           \
                     _mm_load_ps(&(rays.data->origin[0][i])),                 \
                     _mm_load_ps(&(rays.data->origin[1][i])),                 \
                     _mm_load_ps(&(rays.data->origin[2][i])),                 \
                     org_x, org_y, org_z);                                    \
    SSE_KERNEL_CONSTANT_ORIGIN;
#endif // MANTA_SSE

#ifdef MANTA_SSE
    int b = (rays.rayBegin + 3) & (~3);
    int e = (rays.rayEnd) & (~3);
    if (b >= e) {
      for (int i = rays.begin(); i < rays.end(); i++) {
        SCALAR_KERNEL_CONSTANT_ORIGIN;
      }
    } else {
      for (int i = rays.begin(); i < b; i++) {
        SCALAR_KERNEL_CONSTANT_ORIGIN;
      }
      __m128 org_x = _mm_set1_ps(o[0]);
      __m128 org_y = _mm_set1_ps(o[1]);
      __m128 org_z = _mm_set1_ps(o[2]);
      for (int i = b; i < e; i+= 4) {
        SSE_KERNEL_CONSTANT_ORIGIN;
      }
      for (int i = e; i < rays.end(); i++) {
        SCALAR_KERNEL_CONSTANT_ORIGIN;
      }
    }
#else
    for(int i = rays.begin();i<rays.end();i++){
      SCALAR_KERNEL_CONSTANT_ORIGIN;
    }
#endif

  } else {
#ifdef MANTA_SSE
    int b = (rays.rayBegin + 3) & (~3);
    int e = (rays.rayEnd) & (~3);
    if (b >= e) {
      for (int i = rays.begin(); i < rays.end(); i++) {
        SCALAR_KERNEL_NONCONSTANT_ORIGIN;
      }
    } else {
      for (int i = rays.begin(); i < b; i++) {
        SCALAR_KERNEL_NONCONSTANT_ORIGIN;
      }
      for (int i = b; i < e; i+= 4) {
        SSE_KERNEL_NONCONSTANT_ORIGIN;
      }
      for (int i = e; i < rays.end(); i++) {
        SCALAR_KERNEL_NONCONSTANT_ORIGIN;
      }
    }
#else
    for(int i = rays.begin();i<rays.end();i++){
      SCALAR_KERNEL_NONCONSTANT_ORIGIN;
    }
#endif
  }

#undef SCALAR_KERNEL_CONSTANT_ORIGIN
#undef SCALAR_KERNEL_NONCONSTANT_ORIGIN
#undef SSE_KERNEL_CONSTANT_ORIGIN
#undef SSE_KERNEL_NONCONSTANT_ORIGIN

  if (debugFlag) {
    cerr << "After transforming the incoming rays:" << endl;
    cerr << rays << endl;
    cerr << "We get this: " << endl;
    cerr << instance_rays << endl << endl;
  }

  instance->intersect(context, instance_rays);
  for(int i=instance_rays.begin();i<instance_rays.end();i++){
    if(instance_rays.wasHit(i)){
      int end = i+1;
      // NOTE(boulos): We are almost guaranteed to hit the underlying
      // primitive if we hit the instance due to the way we setup the
      // instance minT value. (numerical errors might get us, but
      // that's a small chance)
      while (end < instance_rays.end() && instance_rays.wasHit(end))
        end++;
      // Compute a group of normals and texcoords
      RayPacket sub_packet(instance_rays, i, end);
      sub_packet.computeNormals<true>(context);
      sub_packet.computeGeometricNormals<true>(context);
      // NOTE(boulos): Once the texcoords are separated, there will be
      // another call to texcoords 3 here
      //
      //TODO: DEBUG: CARSON: TEXTURE SUPPORT BROKEN IN DYNBVH_D!!!
      //
      //sub_packet.computeTextureCoordinates2(context);
      //sub_packet.computeTextureCoordinates3(context);

      //sub_packet.computeSurfaceDerivatives(context);

      // TODO(bigler: change this to zero when we fix InstanceMaterial)
      bool override_material = material != this;

      for (int j = i; j < end; j++) {
        Real s = scales.get(j);
        const Material* hit_material = override_material ? material : instance_rays.getHitMaterial(j);
        if(rays.hit(j,
                    instance_rays.getMinT(j)*s,
                    hit_material,
                    this,
                    this)) {
          // NOTE(boulos): We're deferring the normal transform until
          // requested
          Vector tcoords3 = Vector(1,0,0);
          //sub_packet.setTexCoords(j, Vector(1,0,0));
          tcoords3 = sub_packet.getTexCoords(j);
          rays.scratchpad<InstanceShadingData2>(j) =
            InstanceShadingData2(sub_packet.getNormal(j),
                                sub_packet.getGeometricNormal(j),
                                sub_packet.getTexCoords2(j),
                                tcoords3,
                                sub_packet.getSurfaceDerivativeU(j),
                                sub_packet.getSurfaceDerivativeV(j));
        }
      }
      i = end;
    }
  }
}

void DirtyInstance::computeNormal(const RenderContext& context, RayPacket& rays) const
{
  for (int i = rays.begin(); i < rays.end(); i++) {
    rays.setNormal(i, transform_inv.transpose_mult_vector(
                     rays.scratchpad<InstanceShadingData2>(i).normal));
  }
  rays.setFlag(RayPacket::HaveNormals);
}

void DirtyInstance::computeGeometricNormal(const RenderContext& context, RayPacket& rays) const
{
  for (int i = rays.begin(); i < rays.end(); i++) {
    rays.setGeometricNormal(i, transform_inv.transpose_mult_vector(
                              rays.scratchpad<InstanceShadingData2>(i).geometricNormal));
  }
  rays.setFlag(RayPacket::HaveGeometricNormals);
}

void DirtyInstance::setTexCoordMapper(const TexCoordMapper* new_tex)
{
  string me(MANTA_FUNC);
  throw InternalError(me + " shouldn't be called");
}

void DirtyInstance::computeTexCoords2(const RenderContext& context,
                               RayPacket& rays) const
{
  for (int i = rays.begin(); i < rays.end(); i++) {
    rays.setTexCoords(i, rays.scratchpad<InstanceShadingData2>(i).texcoord2);
  }
  rays.setFlag(RayPacket::HaveTexture2);
}

void DirtyInstance::computeTexCoords3(const RenderContext& context,
                                 RayPacket& rays) const
{
  for (int i = rays.begin(); i < rays.end(); i++) {
    rays.setTexCoords(i, rays.scratchpad<InstanceShadingData2>(i).texcoord3);
  }
  rays.setFlag(RayPacket::HaveTexture3);
}

void DirtyInstance::computeSurfaceDerivatives(const RenderContext& context,
                                         RayPacket& rays) const
{
  for (int i = rays.begin(); i < rays.end(); i++) {
    rays.setSurfaceDerivativeU(i, transform.multiply_vector(
                                 rays.scratchpad<InstanceShadingData2>(i).surfDerivU));
    rays.setSurfaceDerivativeV(i, transform.multiply_vector(
                                 rays.scratchpad<InstanceShadingData2>(i).surfDerivV));
  }
  rays.setFlag(RayPacket::HaveSurfaceDerivatives);
}
