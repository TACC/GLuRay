
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
#include "path_tracer.h"
#include "random.h"

using namespace optix;

struct PerRayData_pathtrace
{
  float3 result;
  float3 radiance;
  float3 attenuation;
  float3 origin;
  float3 direction;
  unsigned int seed;
  int depth;
  int countEmitted;
  int done;
  int inside;
};

struct PerRayData_pathtrace_shadow
{
  bool inShadow;
};

// Scene wide
rtDeclareVariable(float,         scene_epsilon, , );
rtDeclareVariable(rtObject,      top_object, , );

// For camera
rtDeclareVariable(float3,        eye, , );
rtDeclareVariable(float3,        U, , );
rtDeclareVariable(float3,        V, , );
rtDeclareVariable(float3,        W, , );
rtDeclareVariable(float3,        bad_color, , );
rtDeclareVariable(unsigned int,  frame_number, , );
rtDeclareVariable(unsigned int,  sqrt_num_samples, , );
rtBuffer<float4, 2>              output_buffer;
rtBuffer<ParallelogramLight>     lights;

rtDeclareVariable(unsigned int,  pathtrace_ray_type, , );
rtDeclareVariable(unsigned int,  pathtrace_shadow_ray_type, , );
rtDeclareVariable(unsigned int,  rr_begin_depth, , );

rtDeclareVariable(float3, geometric_normal, attribute geometric_normal, ); 
rtDeclareVariable(float3, shading_normal,   attribute shading_normal, ); 

rtDeclareVariable(PerRayData_pathtrace, current_prd, rtPayload, );

rtDeclareVariable(optix::Ray, ray,          rtCurrentRay, );
rtDeclareVariable(float,      t_hit,        rtIntersectionDistance, );
rtDeclareVariable(uint2,      launch_index, rtLaunchIndex, );

static __device__ inline float3 powf(float3 a, float exp)
{
  return make_float3(powf(a.x, exp), powf(a.y, exp), powf(a.z, exp));
}

// For miss program
rtDeclareVariable(float3,       bg_color, , );

//-----------------------------------------------------------------------------
//
//  Camera program -- main ray tracing loop
//
//-----------------------------------------------------------------------------

RT_PROGRAM void pathtrace_camera()
{
  size_t2 screen = output_buffer.size();

  float2 inv_screen = 1.0f/make_float2(screen) * 2.f;
  float2 pixel = (make_float2(launch_index)) * inv_screen - 1.f;

  float2 jitter_scale = inv_screen / sqrt_num_samples;
  unsigned int samples_per_pixel = sqrt_num_samples*sqrt_num_samples;
  float3 result = make_float3(0.0f);

  unsigned int seed = tea<16>(screen.x*launch_index.y+launch_index.x, frame_number);
  do {
    unsigned int x = samples_per_pixel%sqrt_num_samples;
    unsigned int y = samples_per_pixel/sqrt_num_samples;
    float2 jitter = make_float2(x-rnd(seed), y-rnd(seed));
    float2 d = pixel + jitter*jitter_scale;
    float3 ray_origin = eye;
    float3 ray_direction = normalize(d.x*U + d.y*V + W);

    PerRayData_pathtrace prd;
    prd.result = make_float3(0.f);
    prd.attenuation = make_float3(1.f);
    prd.countEmitted = true;
    prd.done = false;
    prd.inside = false;
    prd.seed = seed;
    prd.depth = 0;

    for(;;) {
      Ray ray = make_Ray(ray_origin, ray_direction, pathtrace_ray_type, scene_epsilon, RT_DEFAULT_MAX);
      rtTrace(top_object, ray, prd);
      if(prd.done) {
        prd.result += prd.radiance * prd.attenuation;
        break;
      }

      // RR
      if(prd.depth >= rr_begin_depth){
        float pcont = fmaxf(prd.attenuation);
        if(rnd(prd.seed) >= pcont)
          break;
        prd.attenuation /= pcont;
      }
      prd.depth++;
      prd.result += prd.radiance * prd.attenuation;
      ray_origin = prd.origin;
      ray_direction = prd.direction;
    } // eye ray

    result += prd.result;
    seed = prd.seed;
  } while (--samples_per_pixel);

  float3 pixel_color = result/(sqrt_num_samples*sqrt_num_samples);

  if (frame_number > 1)
  {
    float a = 1.0f / (float)frame_number;
    float b = ((float)frame_number - 1.0f) * a;
    float3 old_color = make_float3(output_buffer[launch_index]);
    output_buffer[launch_index] = make_float4(a * pixel_color + b * old_color, 0.0f);
  }
  else
  {
    output_buffer[launch_index] = make_float4(pixel_color, 0.0f);
  }
}

rtDeclareVariable(float3,        emission_color, , );

RT_PROGRAM void diffuseEmitter()
{
  current_prd.radiance = current_prd.countEmitted? emission_color : make_float3(0.f);
  current_prd.done = true;
}

rtDeclareVariable(float3,        diffuse_color, , );

RT_PROGRAM void diffuse()
{
  float3 world_shading_normal   = normalize( rtTransformNormal( RT_OBJECT_TO_WORLD, shading_normal ) );
  float3 world_geometric_normal = normalize( rtTransformNormal( RT_OBJECT_TO_WORLD, geometric_normal ) );

  float3 ffnormal = faceforward( world_shading_normal, -ray.direction, world_geometric_normal );

  float3 hitpoint = ray.origin + t_hit * ray.direction;
  current_prd.origin = hitpoint;

  float z1=rnd(current_prd.seed);
  float z2=rnd(current_prd.seed);
  float3 p;
  cosine_sample_hemisphere(z1, z2, p);
  float3 v1, v2;
  createONB(ffnormal, v1, v2);
  current_prd.direction = v1 * p.x + v2 * p.y + ffnormal * p.z;
  float3 normal_color = (normalize(world_shading_normal)*0.5f + 0.5f)*0.9;
  current_prd.attenuation = current_prd.attenuation * diffuse_color; // use the diffuse_color as the diffuse response
  current_prd.countEmitted = false;

  // Compute direct light...
  // Or shoot one...
  unsigned int num_lights = lights.size();
  float3 result = make_float3(0.0f);

  for(int i = 0; i < num_lights; ++i) {
    ParallelogramLight light = lights[i];
    float z1 = rnd(current_prd.seed);
    float z2 = rnd(current_prd.seed);
    float3 light_pos = light.corner + light.v1 * z1 + light.v2 * z2;

    float Ldist = length(light_pos - hitpoint);
    float3 L = normalize(light_pos - hitpoint);
    float nDl = dot( ffnormal, L );
    float LnDl = dot( light.normal, L );
    float A = length(cross(light.v1, light.v2));

    // cast shadow ray
    if ( nDl > 0.0f && LnDl > 0.0f ) {
      PerRayData_pathtrace_shadow shadow_prd;
      shadow_prd.inShadow = false;
      Ray shadow_ray = make_Ray( hitpoint, L, pathtrace_shadow_ray_type, scene_epsilon, Ldist );
      rtTrace(top_object, shadow_ray, shadow_prd);

      if(!shadow_prd.inShadow){
        float weight=nDl * LnDl * A / (M_PIf*Ldist*Ldist);
        result += light.emission * weight;
      }
    }
  }

  current_prd.radiance = result;
}

rtDeclareVariable(float3,        glass_color, , );
rtDeclareVariable(float,         index_of_refraction, , );

RT_PROGRAM void glass_refract()
{
  float3 world_shading_normal   = normalize( rtTransformNormal( RT_OBJECT_TO_WORLD, shading_normal ) );
  float3 world_geometric_normal = normalize( rtTransformNormal( RT_OBJECT_TO_WORLD, geometric_normal ) );

  float3 ffnormal = faceforward( world_shading_normal, -ray.direction, world_geometric_normal );

  float3 hitpoint = ray.origin + t_hit * ray.direction;
  current_prd.origin = hitpoint;
  current_prd.countEmitted = true;
  float iof;
  if (current_prd.inside) {
    // Shoot outgoing ray
    iof = 1.0f/index_of_refraction;
  } else {
    iof = index_of_refraction;
  }
  refract(current_prd.direction, ray.direction, ffnormal, iof);
  //prd.direction = reflect(ray.direction, ffnormal);

  if (current_prd.inside) {
    // Compute Beer's law
    current_prd.attenuation = current_prd.attenuation * powf(glass_color, t_hit);
  }
  current_prd.inside = !current_prd.inside;

  current_prd.radiance = make_float3(0.0f);
}

//-----------------------------------------------------------------------------
//
//  Exception program
//
//-----------------------------------------------------------------------------

RT_PROGRAM void exception()
{
  output_buffer[launch_index] = make_float4(bad_color, 0.0f);
}


//-----------------------------------------------------------------------------
//
//  Miss program
//
//-----------------------------------------------------------------------------

RT_PROGRAM void miss()
{
  current_prd.radiance = bg_color;
  current_prd.done = true;
}


rtDeclareVariable(PerRayData_pathtrace_shadow, current_prd_shadow, rtPayload, );

RT_PROGRAM void shadow()
{
  current_prd_shadow.inShadow = true;
  rtTerminateRay();
}
