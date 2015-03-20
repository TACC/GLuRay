
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

#include "materials.h"

rtDeclareVariable(float3,   Ka, , );
rtDeclareVariable(float3,   Kd, , );
rtDeclareVariable(float3,   Ks, , );
rtDeclareVariable(float,    phong_exp, , );
rtDeclareVariable(float3,   ambient_light_color, , );
rtDeclareVariable(int,      max_depth, , );
rtDeclareVariable(float,    scene_epsilon, , );
rtDeclareVariable(rtObject, top_object, , );
rtBuffer<BasicLight> lights;

rtDeclareVariable(float3, shading_normal, attribute shading_normal, );
rtDeclareVariable(float3, geometric_normal, attribute geometric_normal, );

// Semantic variables are maintained by the Optix engine
rtDeclareVariable(optix::Ray, ray, rtCurrentRay, );
rtDeclareVariable(float, t_hit, rtIntersectionDistance, );

rtDeclareVariable(PerRayData_radiance, prd_radiance, rtPayload, );

//
// Phong shading with reflections 
// 

RT_PROGRAM void closest_hit_radiance()
{
  float3 world_geo_normal   = normalize( rtTransformNormal( RT_OBJECT_TO_WORLD, geometric_normal ) );
  float3 world_shade_normal = normalize( rtTransformNormal( RT_OBJECT_TO_WORLD, shading_normal ) );
  float3 ffnormal           = faceforward( world_shade_normal, -ray.direction, world_geo_normal );

  // Ambient component
  float3 ambient = Ka * ambient_light_color;

  // Phong lighting
  float3 hit_point = ray.origin + t_hit * ray.direction;

  float3 direct = make_float3( 0.0f );
  for(int i = 0; i < lights.size(); ++i) {
    BasicLight light = lights[i];
    float3 L  = normalize(light.pos - hit_point);
    float nDl = dot( ffnormal, L);
    if( nDl > 0.0f ) {
      // Lambertian
      float3 diffuse = Kd * nDl * light.color;

      // Phong highlight
      float3 H = normalize(L - ray.direction);
      float nDh = dot( ffnormal, H );
      float3 specular = make_float3( 0.0f );
      if( nDh > 0.0f )
        specular = Ks * light.color * powf( nDh, phong_exp );

      direct += diffuse + specular;
    }
  }

  // reflection ray
  float3 reflected = make_float3( 0.1f );
  if( prd_radiance.depth < max_depth) {
    PerRayData_radiance refl_prd;
    refl_prd.depth = prd_radiance.depth+1;
    float3 R = reflect( ray.direction, ffnormal );
    optix::Ray refl_ray( hit_point, R, 0, scene_epsilon, RT_DEFAULT_MAX );
    rtTrace(top_object, refl_ray, refl_prd);
    reflected = Ks * refl_prd.result;
  }

  prd_radiance.result = ambient + direct + reflected;
}


