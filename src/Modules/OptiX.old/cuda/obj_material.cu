
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
#include "phong.h"

using namespace optix;

rtTextureSampler<float4, 2>   ambient_map;         // 
rtTextureSampler<float4, 2>   diffuse_map;         // Correspond to OBJ mtl params
rtTextureSampler<float4, 2>   specular_map;        // 
rtDeclareVariable(float,      phong_exp, , );          //
rtDeclareVariable(int,        illum, , );              //

rtDeclareVariable(float3, texcoord, attribute texcoord, ); 
rtDeclareVariable(float3, geometric_normal, attribute geometric_normal, ); 
rtDeclareVariable(float3, shading_normal, attribute shading_normal, ); 

RT_PROGRAM void any_hit_shadow()
{
  phongShadowed();
}

RT_PROGRAM void closest_hit_radiance()
{
  float3 direction              = ray.direction;
  float3 world_shading_normal   = normalize( rtTransformNormal( RT_OBJECT_TO_WORLD, shading_normal ) );
  float3 world_geometric_normal = normalize( rtTransformNormal( RT_OBJECT_TO_WORLD, geometric_normal ) );
  float3 ffnormal               = faceforward( world_shading_normal, -direction, world_geometric_normal );
  float3 uv                     = texcoord;

  float3 black = make_float3(0.0f, 0.0f, 0.0f);

  // grab values from textures
  // support only MTL illumination modes 0-3 (Ks is for now used as reflectivity)
  // ( see http://local.wasp.uwa.edu.au/~pbourke/dataformats/mtl/ )
  float3 Kd =                       make_float3( tex2D( diffuse_map,  uv.x, uv.y ) );
  float3 Ka = (illum < 1) ? black : make_float3( tex2D( ambient_map,  uv.x, uv.y ) );
  float3 Ks = (illum < 2) ? black : make_float3( tex2D( specular_map, uv.x, uv.y ) );
  float3 Kr = (illum < 3) ? black : Ks;

  phongShade( Kd, Ka, Ks, ffnormal, phong_exp, Kr );
}
