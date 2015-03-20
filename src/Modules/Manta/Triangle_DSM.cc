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

// Modified code from original author: Thiago Ize

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

#include <Model/Primitives/Triangle_DSM.h>
#include <Interface/Context.h>
#include <Interface/RayPacket.h>
#include <Core/Geometry/BBox.h>
#include <Core/Util/Preprocessor.h>
#include <Core/Util/Assert.h>
#include <iostream>

using namespace Manta;
using namespace std;

RayPacketData::HitPrimMPI_storage RayPacketData::hitPrimMPI_storage[16]; // hardcoded to max 16 threads!!!!

Triangle_DSM::Triangle_DSM(const Vector &p1, const Vector &p2, const Vector &p3,
                           Material *mtl) : material(mtl)
{
  vertices[0] = p1;
  vertices[1] = p2;
  vertices[2] = p3;
}

Triangle_DSM* Triangle_DSM::clone(CloneDepth depth, Clonable* incoming)
{
  //TODO: Implement this!
  throw InternalError(string("Not yet implemented!") + MANTA_FUNC);

  Triangle_DSM *copy;

//   if (incoming)
//     copy = dynamic_cast<Triangle_DSM*>(incoming);
//   else
//     return new Triangle_DSM(mesh, myID);

//   copy->myID = myID;
//   copy->mesh = mesh;

  return copy;
}

Interpolable::InterpErr Triangle_DSM::serialInterpolate(const std::vector<keyframe_t> &keyframes)
{
  //We assume that the mesh has already been interpolated.
  return success;
}

void Triangle_DSM::preprocess(const PreprocessContext& context)
{
  if (context.proc != 0) { context.done(); return; }
  //TODO: this materials->preprocess might end up getting called lots
  //of times (imagine all the triangles share the same
  //material). Would be nice to have the preprocess for this in the
  //mesh class and just iterate over the materials. Not sure how to do
  //that, so we will do extra work for now.
  material->preprocess(context);
  context.done();
}

void Triangle_DSM::computeSurfaceDerivatives(const RenderContext& context,
                                             RayPacket& rays) const
{
  throw InternalError(string("Not yet implemented!") + MANTA_FUNC);
//   const int which = myID*3;
//   const unsigned int binormal0_idx = mesh->binormal_indices.size() ?
//     mesh->binormal_indices[which] : Mesh::kNoBinormalIndex;

//   // No binormals means use the default implementation
//   if (binormal0_idx == Mesh::kNoBinormalIndex) {
//     MeshTriangle::computeSurfaceDerivatives(context, rays);
//     return;
//   }

//   const unsigned int binormal1_idx = mesh->binormal_indices[which+1];
//   const unsigned int binormal2_idx = mesh->binormal_indices[which+2];

//   const unsigned int tangent0_idx = mesh->tangent_indices[which+0];
//   const unsigned int tangent1_idx = mesh->tangent_indices[which+1];
//   const unsigned int tangent2_idx = mesh->tangent_indices[which+2];

//   const Vector binormal0 = mesh->vertexBinormals[binormal0_idx];
//   const Vector binormal1 = mesh->vertexBinormals[binormal1_idx];
//   const Vector binormal2 = mesh->vertexBinormals[binormal2_idx];

//   const Vector tangent0 = mesh->vertexTangents[tangent0_idx];
//   const Vector tangent1 = mesh->vertexTangents[tangent1_idx];
//   const Vector tangent2 = mesh->vertexTangents[tangent2_idx];

//   for(int i = rays.begin(); i != rays.end(); ++i) {

//     float a = rays.getScratchpad<float>(SCRATCH_U)[i];
//     float b = rays.getScratchpad<float>(SCRATCH_V)[i];
//     float c = (1 - a - b);

//     Vector dPdu = a * tangent1 + b * tangent2 + c * tangent0;
//     Vector dPdv = a * binormal1 + b * binormal2 + c * binormal0;

//     rays.setSurfaceDerivativeU(i, dPdu);
//     rays.setSurfaceDerivativeV(i, dPdv);
//   }

//   rays.setFlag(RayPacket::HaveSurfaceDerivatives);
}

void Triangle_DSM::computeTexCoords2(const RenderContext&, RayPacket& rays) const
{
  for(int ray=rays.begin(); ray<rays.end(); ray++) {
    float a = rays.getScratchpad<float>(SCRATCH_U)[ray];
    float b = rays.getScratchpad<float>(SCRATCH_V)[ray];
    float c = (1.0 - a - b);

    rays.setTexCoords(ray, Vector(a, b, c));
  }
  rays.setFlag( RayPacket::HaveTexture2|RayPacket::HaveTexture3 );
}

#ifdef MANTA_SSE

#define cross4(xout, yout, zout, x1, y1, z1, x2, y2, z2) \
  {                                                      \
    xout = sub4(mul4(y1, z2), mul4(z1, y2));             \
    yout = sub4(mul4(z1, x2), mul4(x1, z2));             \
    zout = sub4(mul4(x1, y2), mul4(y1, x2));             \
  }

void Triangle_DSM::intersect( const RenderContext& context, RayPacket& rays ) const {

  RayPacketData *data = rays.data;
  const int ray_begin = rays.begin();
  const int ray_end   = rays.end();
  const int sse_begin = ( ray_begin + 3 ) & ( ~3 );
  const int sse_end   = ( ray_end ) & ( ~3 );

  if (sse_begin >= sse_end) { //no sse section exists.
    const Vector p0 = vertices[0];
    const Vector p1 = vertices[1];
    const Vector p2 = vertices[2];

    const Vector edge0 = p1 - p0;
    const Vector edge1 = p0 - p2;
    const Vector normal = Cross( edge0, edge1 );
    for ( int ray = ray_begin; ray < ray_end; ++ray ) {
      const Vector o = Vector( data->origin[ 0 ][ ray ],
                               data->origin[ 1 ][ ray ],
                               data->origin[ 2 ][ ray ] );
      const float oldt = data->minT[ ray ];
      const Vector d = Vector( data->direction[ 0 ][ ray ],
                               data->direction[ 1 ][ ray ],
                               data->direction[ 2 ][ ray ] );
      const float rcp = 1.0f / Dot( normal, d );
      const Vector edge2 = p0 - o;
      const float toverd = Dot( normal, edge2 ) * rcp;
      if ( toverd > oldt - T_EPSILON ||
           toverd < T_EPSILON )
        continue;
      const Vector interm = Cross( edge2, d );
      const float uoverd = Dot( interm, edge1 ) * rcp;
      if ( uoverd < 0.0f )
        continue;
      const float voverd = Dot( interm, edge0 ) * rcp;
      if ( uoverd + voverd > 1.0f || voverd < 0.0f )
        continue;
      if ( rays.hit( ray, toverd, material, &rays.data->hitPrimMPI[ray], this ) ) {
        rays.getScratchpad< float >( SCRATCH_U )[ ray ] = uoverd;
        rays.getScratchpad< float >( SCRATCH_V )[ ray ] = voverd;
        *(static_cast<Triangle_DSM*>(&rays.data->hitPrimMPI[ray])) = *this;
      }
    }
    return;
  }

  const sse_t eps4 = set4( T_EPSILON );

  const Vector p0 = vertices[0];
  const Vector p1 = vertices[1];
  const Vector p2 = vertices[2];

  const sse_t p1x = set4( p1[ 0 ] );
  const sse_t p1y = set4( p1[ 1 ] );
  const sse_t p1z = set4( p1[ 2 ] );

  const sse_t p0x = set4( p0[ 0 ] );
  const sse_t p0y = set4( p0[ 1 ] );
  const sse_t p0z = set4( p0[ 2 ] );

  const sse_t edge0x = sub4( p1x, p0x );
  const sse_t edge0y = sub4( p1y, p0y );
  const sse_t edge0z = sub4( p1z, p0z );

  const sse_t p2x = set4( p2[ 0 ] );
  const sse_t p2y = set4( p2[ 1 ] );
  const sse_t p2z = set4( p2[ 2 ] );

  const sse_t edge1x = sub4( p0x, p2x );
  const sse_t edge1y = sub4( p0y, p2y );
  const sse_t edge1z = sub4( p0z, p2z );

  sse_t normalx, normaly, normalz;
  cross4( normalx, normaly, normalz, edge0x, edge0y, edge0z, edge1x, edge1y, edge1z );

  for ( int ray = sse_begin; ray < sse_end; ray += 4 ) {

    const sse_t ox = load44( &data->origin[ 0 ][ ray ] );
    const sse_t oy = load44( &data->origin[ 1 ][ ray ] );
    const sse_t oz = load44( &data->origin[ 2 ][ ray ] );

    const sse_t oldt = load44( &data->minT[ ray ] );

    const sse_t dx = load44( &data->direction[ 0 ][ ray ] );
    const sse_t dy = load44( &data->direction[ 1 ][ ray ] );
    const sse_t dz = load44( &data->direction[ 2 ][ ray ] );

    const sse_t det = dot4( normalx, normaly, normalz, dx, dy, dz );
    const sse_t rcp = oneOver( det );

    const sse_t edge2x = sub4( p0x, ox );
    const sse_t edge2y = sub4( p0y, oy );
    const sse_t edge2z = sub4( p0z, oz );

    const sse_t t = dot4( normalx, normaly, normalz, edge2x, edge2y, edge2z );
    const sse_t toverd = mul4( rcp, t );
    const sse_t tmaskb = cmp4_lt( toverd, sub4( oldt, eps4 ) );
    const sse_t tmaska = cmp4_gt( toverd, eps4 );
    sse_t mask = and4( tmaska, tmaskb );
    if ( getmask4( mask ) == 0x0 )
      continue;

    sse_t intermx, intermy, intermz;
    cross4( intermx, intermy, intermz, edge2x, edge2y, edge2z, dx, dy, dz );

    const sse_t u = dot4( intermx, intermy, intermz, edge1x, edge1y, edge1z );
    const sse_t uoverd = mul4( rcp, u );
    const sse_t umask = cmp4_ge( uoverd, _mm_zero );
    mask = and4( mask, umask );
    if ( getmask4( mask ) == 0x0 )
      continue;

    const sse_t v = dot4( intermx, intermy, intermz, edge0x, edge0y, edge0z );
    const sse_t uplusv = add4( u, v );
    const sse_t uvmask = cmp4_le( mul4( uplusv, det ), mul4( det, det ) );
    const sse_t voverd = mul4( rcp, v );
    const sse_t vmask = cmp4_ge( voverd, _mm_zero );

    mask = and4( mask, uvmask );
    mask = and4( mask, vmask );
    if ( getmask4( mask ) == 0x0 )
      continue;

    rays.hitWithoutTminCheck( ray, mask, toverd, material,
                              &rays.data->hitPrimMPI[ray], this );
    float *udata = &rays.getScratchpad< float >( SCRATCH_U )[ ray ];
    float *vdata = &rays.getScratchpad< float >( SCRATCH_V )[ ray ];
    store44( udata, mask4( mask, uoverd, load44( udata ) ) );
    store44( vdata, mask4( mask, voverd, load44( vdata ) ) );

    const int mask4 = getmask4(mask);
    if (mask4 & 0x1) {
      *(static_cast<Triangle_DSM*>(&rays.data->hitPrimMPI[ray+0])) = *this;
      // hitPrim[ray] is already pointing to hitPrimMPI[ray].
    }
    if (mask4 & 0x2) {
      *(static_cast<Triangle_DSM*>(&rays.data->hitPrimMPI[ray+1])) = *this;
      rays.data->hitPrim[ray+1] = &rays.data->hitPrimMPI[ray+1];
    }
    if (mask4 & 0x4) {
      *(static_cast<Triangle_DSM*>(&rays.data->hitPrimMPI[ray+2])) = *this;
      rays.data->hitPrim[ray+2] = &rays.data->hitPrimMPI[ray+2];
    }
    if (mask4 & 0x8) {
      *(static_cast<Triangle_DSM*>(&rays.data->hitPrimMPI[ray+3])) = *this;
      rays.data->hitPrim[ray+3] = &rays.data->hitPrimMPI[ray+3];
    }
 }

  if ( ray_begin < sse_begin || ray_end > sse_end )
  {
    const Vector edge0 = p1 - p0;
    const Vector edge1 = p0 - p2;
    const Vector normal = Cross( edge0, edge1 );
    for ( int ray = ray_begin; ray < sse_begin; ++ray ) {
      const Vector o = Vector( data->origin[ 0 ][ ray ],
                               data->origin[ 1 ][ ray ],
                               data->origin[ 2 ][ ray ] );
      const float oldt = data->minT[ ray ];
      const Vector d = Vector( data->direction[ 0 ][ ray ],
                               data->direction[ 1 ][ ray ],
                               data->direction[ 2 ][ ray ] );
      const float rcp = 1.0f / Dot( normal, d );
      const Vector edge2 = p0 - o;
      const float toverd = Dot( normal, edge2 ) * rcp;
      if ( toverd > oldt - T_EPSILON ||
           toverd < T_EPSILON )
        continue;
      const Vector interm = Cross( edge2, d );
      const float uoverd = Dot( interm, edge1 ) * rcp;
      if ( uoverd < 0.0f )
        continue;
      const float voverd = Dot( interm, edge0 ) * rcp;
      if ( uoverd + voverd > 1.0f || voverd < 0.0f )
        continue;
      if ( rays.hit( ray, toverd, material, &rays.data->hitPrimMPI[ray], this ) ) {
        rays.getScratchpad< float >( SCRATCH_U )[ ray ] = uoverd;
        rays.getScratchpad< float >( SCRATCH_V )[ ray ] = voverd;
        *(static_cast<Triangle_DSM*>(&rays.data->hitPrimMPI[ray])) = *this;
      }
    }
    for ( int ray = sse_end; ray < ray_end; ++ray ) {
      const Vector o = Vector( data->origin[ 0 ][ ray ],
                               data->origin[ 1 ][ ray ],
                               data->origin[ 2 ][ ray ] );
      const float oldt = data->minT[ ray ];
      const Vector d = Vector( data->direction[ 0 ][ ray ],
                               data->direction[ 1 ][ ray ],
                               data->direction[ 2 ][ ray ] );
      const float rcp = 1.0f / Dot( normal, d );
      const Vector edge2 = p0 - o;
      const float toverd = Dot( normal, edge2 ) * rcp;
      if ( toverd > oldt - T_EPSILON ||
           toverd < T_EPSILON )
        continue;
      const Vector interm = Cross( edge2, d );
      const float uoverd = Dot( interm, edge1 ) * rcp;
      if ( uoverd < 0.0f )
        continue;
      const float voverd = Dot( interm, edge0 ) * rcp;
      if ( uoverd + voverd > 1.0f || voverd < 0.0f )
        continue;
      if ( rays.hit( ray, toverd, material, &rays.data->hitPrimMPI[ray], this ) ) {
        rays.getScratchpad< float >( SCRATCH_U )[ ray ] = uoverd;
        rays.getScratchpad< float >( SCRATCH_V )[ ray ] = voverd;
        *(static_cast<Triangle_DSM*>(&rays.data->hitPrimMPI[ray])) = *this;
      }
    }
  }

}

#else // MANTA_SSE

void Triangle_DSM::intersect( const RenderContext& context, RayPacket& rays ) const {
  //Finish porting this code over!

  RayPacketData *data = rays.data;
  const int ray_begin = rays.begin();
  const int ray_end   = rays.end();

  //const unsigned int index = myID*3;
  const Vector p0 = vertices[0];
  const Vector p1 = vertices[1];
  const Vector p2 = vertices[2];

  const Vector edge0 = p1 - p0;
  const Vector edge1 = p0 - p2;
  const Vector normal = Cross( edge0, edge1 );
  for ( int ray = ray_begin; ray < ray_end; ++ray ) {
    const Vector o = Vector( data->origin[ 0 ][ ray ],
                             data->origin[ 1 ][ ray ],
                             data->origin[ 2 ][ ray ] );
    const float oldt = data->minT[ ray ];
    const Vector d = Vector( data->direction[ 0 ][ ray ],
                             data->direction[ 1 ][ ray ],
                             data->direction[ 2 ][ ray ] );
    const float rcp = 1.0f / Dot( normal, d );
    const Vector edge2 = p0 - o;
    const float toverd = Dot( normal, edge2 ) * rcp;
    if ( toverd > oldt - T_EPSILON ||
         toverd < T_EPSILON )
      continue;
    const Vector interm = Cross( edge2, d );
    const float uoverd = Dot( interm, edge1 ) * rcp;
    if ( uoverd < 0.0f )
      continue;
    const float voverd = Dot( interm, edge0 ) * rcp;
    if ( uoverd + voverd > 1.0f || voverd < 0.0f )
      continue;
    if ( rays.hit( ray, toverd, material, &rays.data->hitPrimMPI[ray], this ) ) {
      rays.getScratchpad< float >( SCRATCH_U )[ ray ] = uoverd;
      rays.getScratchpad< float >( SCRATCH_V )[ ray ] = voverd;
      *(static_cast<Triangle_DSM*>(&rays.data->hitPrimMPI[ray])) = *this;
    }
  }
}

#endif // MANTA_SSE

void Triangle_DSM::computeNormal(const RenderContext& context, RayPacket &rays) const
{
  const Vector edge0 = vertices[1] - vertices[0];
  const Vector edge1 = vertices[2] - vertices[0];
  const Vector normal = Cross(edge0, edge1);
  for(int ray=rays.begin(); ray<rays.end(); ray++)
    rays.setNormal(ray, normal);
}

void Triangle_DSM::computeGeometricNormal(const RenderContext& context, RayPacket& rays) const
{
  computeNormal(context, rays);
  for(int ray=rays.begin(); ray<rays.end(); ray++)
    rays.setGeometricNormal(ray, rays.getNormal(ray));
}
