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
#include <string>

//-----------------------------------------------------------------------------
// 
//  PlyLoader class declaration
//
//-----------------------------------------------------------------------------
class PlyLoader
{
public:
  SUTILAPI PlyLoader( const std::string&   filename,
                      optix::Context       context,
                      optix::GeometryGroup geometrygroup,
                      optix::Material      material,
                      const char* ASBuilder   = "Sbvh",
                      const char* ASTraverser = "Bvh",
                      const char* ASRefine    = "0",
                      bool large_geom = false);

  SUTILAPI ~PlyLoader() {} // makes sure CRT objects are destroyed on the correct heap

  SUTILAPI void setIntersectProgram( optix::Program program );
  SUTILAPI void load();
  SUTILAPI void load( const optix::Matrix4x4& transform );

  SUTILAPI optix::Aabb getSceneBBox()const { return m_aabb; }

  SUTILAPI static bool isMyFile( const std::string& filename );

private:
  void createGeometryInstance( unsigned nverts, optix::float3 const* verts, optix::float3 const* normals,
    unsigned ntris, optix::int3 const* tris );

  std::string            m_filename;

  optix::Context         m_context;
  optix::GeometryGroup   m_geometrygroup;
  //optix::Buffer          m_vbuffer;
  //optix::Buffer          m_ibuffer;
  optix::Material        m_material;
  bool                   m_large_geom;
  const char*            m_ASBuilder;
  const char*            m_ASTraverser;
  const char*            m_ASRefine;

  //optix::Program         m_intersect_program;

  optix::Aabb            m_aabb;
};
