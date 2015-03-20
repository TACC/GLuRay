
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

#include "helpers.h"
#include "commonStructs.h"

using namespace optix;

// global parameters
rtDeclareVariable(rtObject,     top_object, , );
rtDeclareVariable(rtObject,     top_shadower, , );
rtDeclareVariable(float,        scene_epsilon, , );
rtDeclareVariable(int,          max_depth, , );
rtDeclareVariable(unsigned int, radiance_ray_type, , );
rtDeclareVariable(unsigned int, shadow_ray_type, , );
rtDeclareVariable(float3,       ambient_light_color, , );
rtDeclareVariable(float3,       jitter, , );

// surface parameters
rtDeclareVariable(float,        importance_cutoff, , );
rtDeclareVariable(float3,       cutoff_color, , );
rtDeclareVariable(float,        fresnel_exponent, , );
rtDeclareVariable(float,        fresnel_minimum, , );
rtDeclareVariable(float,        fresnel_maximum, , );
rtDeclareVariable(float3,       reflection_color, , );
rtDeclareVariable(int,          reflection_maxdepth, , );
rtDeclareVariable(float3,       Kd, , );
rtDeclareVariable(float3,       Ka, , );
rtDeclareVariable(float3,       Ks, , );
rtDeclareVariable(float,        exponent, , );

// surface textures
rtTextureSampler<float4, 2>     kd_map;

// hitpoint parameters
rtDeclareVariable(float3, texcoord, attribute texcoord, ); 
rtDeclareVariable(float3, shading_normal, attribute shading_normal, ); 

// ray parameters
rtDeclareVariable(optix::Ray, ray, rtCurrentRay, );
rtDeclareVariable(float, isect_dist, rtIntersectionDistance, );

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

rtBuffer<BasicLight> lights;

rtDeclareVariable(PerRayData_radiance, prd_radiance, rtPayload, );
rtDeclareVariable(PerRayData_shadow,   prd_shadow,   rtPayload, );

// -----------------------------------------------------------------------------

static __device__ __inline__ float3 TraceRay(float3 origin, float3 direction, int depth, float importance )
{
  optix::Ray ray = optix::make_Ray( origin, direction, radiance_ray_type, scene_epsilon, RT_DEFAULT_MAX );
  PerRayData_radiance prd;
  prd.depth = depth;
  prd.importance = importance;

  rtTrace( top_object, ray, prd );
  return prd.result;
}

// -----------------------------------------------------------------------------

RT_PROGRAM void closest_hit_radiance()
{
  // intersection vectors
  const float3 hit = ray.origin + isect_dist * ray.direction;            // hitpoint
  const float3 N   = normalize(rtTransformNormal(RT_OBJECT_TO_WORLD, shading_normal)); // normal
  const float3 I   = ray.direction;                                            // incident direction
        float3 R   = reflect(I, N);                                            // reflection direction

  float depth = prd_radiance.depth;  

  float reflection = fresnel_schlick(-dot(N, I), fresnel_exponent, fresnel_minimum, fresnel_maximum);

  // we need not clamp this subtraction because after fresnel_schlick,
  // reflection is guaranteed to be <= fresnel_maximum
  float oneMinusFresnel = fresnel_maximum - reflection;

  // ambient
  float3 kd = Kd * make_float3( tex2D( kd_map, texcoord.x, texcoord.y ) );
  float3 result = oneMinusFresnel * Ka * ambient_light_color * kd;

  // direct lighting
  for (unsigned i=0; i<lights.size(); ++i)
  {
    float3 L = normalize(lights[i].pos - hit);

    // diffuse
    float3 diffuse = 1.0f/lights.size() * ( max(dot(N, L), 0.0f) * lights[i].color );
    result += oneMinusFresnel * diffuse * kd;

    // specular
    result += powf(max(dot(R, L), 0.0f) , exponent) * Ks;
  }

  // reflection
  if (depth < min(reflection_maxdepth, max_depth))
  {
    // phong lobe jittering
    float3 U, V, W;
    create_onb(R, U, V, W);
    R = sample_phong_lobe(make_float2(jitter.x, jitter.y), 4096.0f, U, V, W);

    // avoid directions below surface
    if (dot(R, N) < 0.01f)
      R = W;

    // shoot reflection ray
    float3 ntsc_luminance = {0.30f, 0.59f, 0.11f}; 
    float importance = prd_radiance.importance * reflection * dot( reflection_color, ntsc_luminance );
    float3 color = cutoff_color;
    if ( importance > importance_cutoff ) {
      color = TraceRay( hit, R, depth+1, importance );
    }
    result += reflection * reflection_color * color;
  }

  prd_radiance.result = result;
}

// -----------------------------------------------------------------------------

RT_PROGRAM void any_hit_shadow()
{
  prd_shadow.attenuation = make_float3(0.0f);
  rtTerminateRay();
}
