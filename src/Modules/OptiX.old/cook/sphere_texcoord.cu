
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

#include "helpers.h"

using namespace optix;

rtDeclareVariable(float4, sphere, , );
rtDeclareVariable(float3, rotation, , );

rtDeclareVariable(float3, matrix_row_0, , );
rtDeclareVariable(float3, matrix_row_1, , );
rtDeclareVariable(float3, matrix_row_2, , );

rtDeclareVariable(optix::Ray, ray, rtCurrentRay, );

rtDeclareVariable(float3, texcoord, attribute texcoord, ); 
rtDeclareVariable(float3, geometric_normal, attribute geometric_normal, ); 
rtDeclareVariable(float3, shading_normal, attribute shading_normal, ); 

RT_PROGRAM void intersect(int primIdx)
{
  float3 center = make_float3(sphere);
  float3 O = ray.origin - center;
  float3 D = ray.direction;
  float radius = sphere.w;

  float b = dot(O, D);
  float c = dot(O, O)-radius*radius;
  float disc = b*b-c;
  if(disc > 0.0f){
    float sdisc = sqrtf(disc);
    float root1 = (-b - sdisc);
    bool check_second = true;
    if( rtPotentialIntersection( root1 ) ) {
      shading_normal = geometric_normal = (O + root1*D)/radius;

      float3 polar;
      polar.x = dot(matrix_row_0, geometric_normal);
      polar.y = dot(matrix_row_1, geometric_normal);
      polar.z = dot(matrix_row_2, geometric_normal);
      polar = optix::cart_to_pol(polar);

      texcoord = make_float3( polar.x*0.5f*M_1_PIf, (polar.y+M_PI_2f)*M_1_PIf, polar.z/radius );

      if(rtReportIntersection(0))
        check_second = false;
    } 
    if(check_second) {
      float root2 = (-b + sdisc);
      if( rtPotentialIntersection( root2 ) ) {
        shading_normal = geometric_normal = (O + root2*D)/radius;

        float3 polar;
        polar.x = dot(matrix_row_0, geometric_normal);
        polar.y = dot(matrix_row_1, geometric_normal);
        polar.z = dot(matrix_row_2, geometric_normal);
        polar = optix::cart_to_pol(polar);

        texcoord = make_float3( polar.x*0.5f*M_1_PIf, (polar.y+M_PI_2f)*M_1_PIf, polar.z/radius );

        rtReportIntersection(0);
      }
    }
  }
}

RT_PROGRAM void bounds (int, optix::Aabb* aabb)
{
  const float3 cen = make_float3( sphere );
  const float3 rad = make_float3( sphere.w );
  
  if( rad.x > 0.0f && !isinf(rad.x) ) {
    aabb->m_min = cen - rad;
    aabb->m_max = cen + rad;
  } else {
    aabb->invalidate();
  }
}

