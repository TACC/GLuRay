
/*
 * Copyright (c) 2008 - 2009 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property and proprietary
 * rights in and to this software, related documentation and any modifications thereto.
 * Any use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from NVIDIA Corporation is strictly
 * prohibited.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THIS SOFTWARE IS PROVIDED *AS IS*
 * AND NVIDIA AND ITS SUPPLIERS DISCLAIM ALL WARRANTIES, EITHER EXPRESS OR IMPLIED,
 * INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE.  IN NO EVENT SHALL NVIDIA OR ITS SUPPLIERS BE LIABLE FOR ANY
 * SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER (INCLUDING, WITHOUT
 * LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, LOSS OF
 * BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS) ARISING OUT OF THE USE OF OR
 * INABILITY TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS BEEN ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGES
 */

#include <optix.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_matrix_namespace.h>
#include <optixu/optixu_aabb_namespace.h>

using namespace optix;

// This is to be plugged into an RTgeometry object to represent a triangle mesh
// with a shared vertex buffer, triangle index buffer, and single material

rtBuffer<float3> vertex_buffer;     
rtBuffer<int3>   vindex_buffer;    // position indices 

rtDeclareVariable(float3, texcoord, attribute texcoord, ); 
rtDeclareVariable(float3, geometric_normal, attribute geometric_normal, ); 
rtDeclareVariable(float3, shading_normal, attribute shading_normal, ); 

rtDeclareVariable(optix::Ray, ray, rtCurrentRay, );

RT_PROGRAM void mesh_intersect( int primIdx )
{
  int3 v_idx = vindex_buffer[primIdx];

  float3 p0 = vertex_buffer[ v_idx.x ];
  float3 p1 = vertex_buffer[ v_idx.y ];
  float3 p2 = vertex_buffer[ v_idx.z ];

  // Intersect ray with triangle
  float3 n;
  float  t, beta, gamma;
  if( intersect_triangle( ray, p0, p1, p2, n, t, beta, gamma ) ) {

    if(  rtPotentialIntersection( t ) ) {

      geometric_normal = normalize( n );
      shading_normal   = geometric_normal;
      texcoord = make_float3( 0.0f, 0.0f, 0.0f );

      rtReportIntersection( 0 );
    }
  }
}


RT_PROGRAM void mesh_bounds (int primIdx, float result[6])
{
  int3 v_idx = vindex_buffer[primIdx];

  float3 v0   = vertex_buffer[ v_idx.x ];
  float3 v1   = vertex_buffer[ v_idx.y ];
  float3 v2   = vertex_buffer[ v_idx.z ];
  const float  area = length(cross(v1-v0, v2-v0));

  optix::Aabb* aabb = (optix::Aabb*)result;

  if(area > 0.0f && !isinf(area)) {
    aabb->m_min = fminf( fminf( v0, v1), v2 );
    aabb->m_max = fmaxf( fmaxf( v0, v1), v2 );
  } else {
    aabb->invalidate();
  }
}

