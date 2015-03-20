
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
#include <optix_math.h>

#include "commonStructs.h"
#include "helpers.h"


struct PerRayData_radiance
{
  float3 result;
  float importance;
  int depth;
};

struct PerRayData_shadow
{
  float3 attenuation;
};

// global parameters
rtDeclareVariable(rtObject,     top_object, , );
rtDeclareVariable(rtObject,     top_shadower, , );
rtDeclareVariable(int,          max_depth, , );
rtDeclareVariable(float,        scene_epsilon, , );
rtDeclareVariable(float3,       ambient_light_color, , );
rtDeclareVariable(unsigned int, radiance_ray_type, , );
rtDeclareVariable(unsigned int, shadow_ray_type, , );
rtDeclareVariable(float3,       jitter, , );

// ray parameters
rtDeclareVariable(optix::Ray, ray, rtCurrentRay, );
rtDeclareVariable(float, t_hit, rtIntersectionDistance, );

rtDeclareVariable(PerRayData_radiance, prd_radiance, rtPayload, );
rtDeclareVariable(PerRayData_shadow,   prd_shadow,   rtPayload, );


rtBuffer<BasicLight> lights;


static __device__ void phongShadowed()
{
  // this material is opaque, so it fully attenuates all shadow rays
  prd_shadow.attenuation = make_float3(0);
  
  rtTerminateRay();
}

static
__device__ void phongShade( float3 p_Kd,
                            float3 p_Ka,
                            float3 p_Ks,
                            float3 p_normal,
                            float  p_phong_exp,
                            float3 p_reflectivity )
{
  float3 hit_point = ray.origin + t_hit * ray.direction;
  
  // ambient contribution
  float3 result = p_Ka * ambient_light_color;

  // compute direct lighting
  unsigned int num_lights = lights.size();

  for(int i = 0; i < num_lights; ++i) {
    // set jittered light direction
    BasicLight light = lights[i];
    float3 L = light.pos - hit_point;

    float2 sample = optix::square_to_disk(make_float2(jitter.x, jitter.y));
    float3 U, V, W;
    create_onb(L, U, V, W);
    L += 5.0f * (sample.x * U + sample.y * V);

    float Ldist = length(L);
    L = (1.0f / Ldist) * L;

    float nDl = dot( p_normal, L);

    // cast shadow ray
    PerRayData_shadow shadow_prd;
    shadow_prd.attenuation = make_float3(1);
    if(nDl > 0) {
      optix::Ray shadow_ray = optix::make_Ray( hit_point, L, shadow_ray_type, scene_epsilon, Ldist );
      rtTrace(top_shadower, shadow_ray, shadow_prd);
    }

    // If not completely shadowed, light the hit point
    if(fmaxf(shadow_prd.attenuation) > 0) {
      float3 Lc = light.color * shadow_prd.attenuation;

      result += p_Kd * nDl * Lc;

      float3 H = normalize(L - ray.direction);
      float nDh = dot( p_normal, H );
      if(nDh > 0) {
        float power = pow(nDh, p_phong_exp);
        result += p_Ks * power * Lc;
      }
    }
  }

  if( fmaxf( p_reflectivity ) > 0 ) {

    // ray tree attenuation
    PerRayData_radiance new_prd;             
    float3 ntsc_luminance = {0.30, 0.59, 0.11}; 
    new_prd.importance = prd_radiance.importance * dot( p_reflectivity, ntsc_luminance );
    new_prd.depth = prd_radiance.depth + 1;

    // reflection ray
    if( new_prd.importance >= 0.01f && new_prd.depth <= max_depth) {
      float3 R = reflect( ray.direction, p_normal );

      optix::Ray refl_ray = optix::make_Ray( hit_point, R, radiance_ray_type, scene_epsilon, RT_DEFAULT_MAX );
      rtTrace(top_object, refl_ray, new_prd);
      result += p_reflectivity * new_prd.result;
    }
  }

  // pass the color back up the tree
  prd_radiance.result = result;
}
