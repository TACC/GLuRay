
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

#pragma once
#include <sutil.h>
#include <optixu/optixpp_namespace.h>
#include <optixu/optixu_aabb_namespace.h>
#include <optixu/optixu_matrix_namespace.h>
#include <glm.h>
#include <string>

//-----------------------------------------------------------------------------
// 
//  ObjLoader class declaration 
//
//-----------------------------------------------------------------------------
class ObjLoader
{
public:
  SUTILAPI ObjLoader( const char* filename,                 // Model filename
                      optix::Context context,               // Context for RT object creation
                      optix::GeometryGroup geometrygroup,   // Empty geom group to hold model
                      const char* ASBuilder   = "Sbvh",
                      const char* ASTraverser = "Bvh",
                      const char* ASRefine = "0",
                      bool large_geom = false );            // Reorder geom data for page fault minimization
  SUTILAPI ObjLoader( const char* filename,
                      optix::Context context,
                      optix::GeometryGroup geometrygroup,
                      optix::Material material,                // Material override
                      bool force_load_material_params = false, // Set obj_material params even though material is overridden
                      const char* ASBuilder   = "Sbvh",
                      const char* ASTraverser = "Bvh",
                      const char* ASRefine = "0",
                      bool large_geom = false);                // Reorder geom data for page fault minimization

  SUTILAPI ~ObjLoader() {} // makes sure CRT objects are destroyed on the correct heap

  SUTILAPI void setIntersectProgram( optix::Program program );
  SUTILAPI void setBboxProgram( optix::Program program );
  SUTILAPI void load();
  SUTILAPI void load( const optix::Matrix4x4& transform );

  SUTILAPI optix::Aabb getSceneBBox()const { return m_aabb; }
  SUTILAPI optix::Buffer getLightBuffer()const { return m_light_buffer; }

  SUTILAPI static bool isMyFile( const char* filename );

private:

  struct MatParams
  {
    optix::float3 emissive;
    optix::float3 reflectivity;
    float  phong_exp;
    int    illum;
    optix::TextureSampler ambient_map;
    optix::TextureSampler diffuse_map;
    optix::TextureSampler specular_map;
  };

  void createMaterial();
  void createGeometryInstances( GLMmodel* model );
  void loadVertexData( GLMmodel* model, const optix::Matrix4x4& transform );
  void createMaterialParams( GLMmodel* model );
  void loadMaterialParams( optix::GeometryInstance gi, unsigned int index );
  void createLightBuffer( GLMmodel* model );

  std::string            m_pathname;
  std::string            m_filename;
  optix::Context         m_context;
  optix::GeometryGroup   m_geometrygroup;
  optix::Buffer          m_vbuffer;
  optix::Buffer          m_nbuffer;
  optix::Buffer          m_tbuffer;
  optix::Material        m_material;
  optix::Program         m_intersect_program;
  optix::Program         m_bbox_program;
  optix::Buffer          m_light_buffer;
  bool                   m_have_default_material;
  bool                   m_force_load_material_params;
  const char*            m_ASBuilder;
  const char*            m_ASTraverser;
  const char*            m_ASRefine;
  bool                   m_large_geom;
  optix::Aabb            m_aabb;
  std::vector<MatParams> m_material_params;
};



