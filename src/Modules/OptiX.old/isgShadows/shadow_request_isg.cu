
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

rtBuffer<float,  2>          shadow_buffer;
rtTextureSampler<float4, 2>  request_texture;

rtDeclareVariable(uint, shadow_ray_type, , );
rtDeclareVariable(float, scene_epsilon, , );
rtDeclareVariable(uint2, launch_index, rtLaunchIndex, );

rtDeclareVariable(float3, light_pos, , );
rtDeclareVariable(rtObject, shadow_casters, , );

struct PerRayData_shadow
{
  float3 attenuation;
};

RT_PROGRAM void shadow_request()
{
  float3 ray_origin = make_float3(tex2D(request_texture, launch_index.x, launch_index.y));

  PerRayData_shadow prd;
  prd.attenuation = make_float3(-1);

  if( !isnan(ray_origin.x) ) {
    float3 L = light_pos-ray_origin;
    float dist = sqrtf(dot(L,L));
    float3 ray_direction = L/dist;
    optix::Ray ray = optix::make_Ray(ray_origin, ray_direction, shadow_ray_type, scene_epsilon, dist);
    rtTrace(shadow_casters, ray, prd);
  }

  shadow_buffer[launch_index] = prd.attenuation.x;
}

RT_PROGRAM void exception()
{
}
