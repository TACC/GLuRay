
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

using namespace optix;

rtDeclareVariable(rtObject,     top_object, , );
rtDeclareVariable(float,        scene_epsilon, , );
rtDeclareVariable(int,          max_depth, , );
rtDeclareVariable(unsigned int, radiance_ray_type, , );
rtDeclareVariable(unsigned int, shadow_ray_type, , );
rtDeclareVariable(float3, shading_normal, attribute shading_normal, ); 

rtDeclareVariable(optix::Ray, ray, rtCurrentRay, );
rtDeclareVariable(float, isect_dist, rtIntersectionDistance, );

rtDeclareVariable(float3,       tile_size, , ); 
rtDeclareVariable(float3,       tile_color_dark, , );
rtDeclareVariable(float3,       tile_color_light, , );
rtDeclareVariable(float3,       light_direction, , );

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

rtDeclareVariable(PerRayData_radiance, prd_radiance, rtPayload, );
rtDeclareVariable(PerRayData_shadow, prd_shadow, rtPayload, );

// -----------------------------------------------------------------------------

RT_PROGRAM void closest_hit_radiance()
{
  const float3 h = ray.origin + isect_dist * ray.direction;
  const float3 l = normalize(light_direction);
  const float3 n = normalize(rtTransformNormal(RT_OBJECT_TO_WORLD, shading_normal));

  const float3 p = h / tile_size;
  float3 result = (static_cast<int>( floorf(p.x) + floorf(p.y) + floorf(p.z) ) & 1) ?
                  tile_color_light : tile_color_dark;

  const float cos_theta = dot(l, n);
  if (cos_theta > 0.01f)
  {
    optix::Ray shadow_ray = optix::make_Ray( h, l, shadow_ray_type, scene_epsilon, RT_DEFAULT_MAX );
    PerRayData_shadow shadow_prd;
    shadow_prd.attenuation = make_float3(1.0f);
  
    rtTrace( top_object, shadow_ray, shadow_prd );
  
    result *= 0.25f + (cos_theta * shadow_prd.attenuation * 0.75f);
  }
  else
    result *= 0.25f;

  prd_radiance.result = result;
}

// -----------------------------------------------------------------------------

RT_PROGRAM void any_hit_shadow()
{
  // this material is opaque, so it fully attenuates all shadow rays
  prd_shadow.attenuation = make_float3(0.0f);
  rtTerminateRay();
}
