/*
 * Copyright (c) 2008 - 2011 NVIDIA Corporation.  All rights reserved.
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

#include "PlyLoader.h"
#include "rply-1.01/rply.h"
#include <optixu/optixu.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_math_stream_namespace.h>
#include <iostream>
#include <cstring> //memcpy
#include <algorithm>


//------------------------------------------------------------------------------
// 
//  Helper functions
//
//------------------------------------------------------------------------------

namespace
{
  struct ModelData
  {
    ModelData() : nverts(0), nnormals(0), ntris(0), verts(0), normals(0), tris(0) {}
    optix::Aabb    aabb;
    unsigned       nverts;
    unsigned       nnormals;
    unsigned       ntris;
    optix::float3* verts;
    optix::float3* normals;
    optix::int3*   tris; 
  };


  std::string getExtension( const std::string& filename )
  {
    std::string::size_type extension_index = filename.find_last_of( "." );
    return extension_index != std::string::npos ?
           filename.substr( extension_index+1 ) :
           std::string();
  }


  int vertexCB( p_ply_argument argument )
  {
    int coord_index;
    ModelData* data;
    ModelData** data_pp = &data;
    ply_get_argument_user_data( argument, reinterpret_cast<void**>( data_pp ), &coord_index );
    switch( coord_index ) {
      case 0: 
        data->verts[ data->nverts ].x = static_cast<float>( ply_get_argument_value( argument ) );
        break;
      case 1: 
        data->verts[ data->nverts ].y = static_cast<float>( ply_get_argument_value( argument ) );
        break;
      case 2: 
        data->verts[ data->nverts ].z = static_cast<float>( ply_get_argument_value( argument ) );
        data->aabb.include( data->verts[ data->nverts ] );
        data->nverts += 1;
        break;
      case 3: 
        data->normals[ data->nnormals ].x = static_cast<float>( ply_get_argument_value( argument ) );
        break;
      case 4: 
        data->normals[ data->nnormals ].y = static_cast<float>( ply_get_argument_value( argument ) );
        break;
      case 5: 
        data->normals[ data->nnormals ].z = static_cast<float>( ply_get_argument_value( argument ) );
        data->nnormals += 1;
        break;
    }
    return 1;
  }


  int faceCB(p_ply_argument argument)
  {
    ModelData* data;
    ModelData** data_pp = &data;
    ply_get_argument_user_data( argument, reinterpret_cast<void**>( data_pp ), NULL );

    int num_verts, which_vertex;
    ply_get_argument_property( argument, NULL, &num_verts, &which_vertex );
    
    switch( which_vertex ) {
      case 0: 
        data->tris[ data->ntris ].x = static_cast<int>( ply_get_argument_value( argument ) );
        break;
      case 1: 
        data->tris[ data->ntris ].y = static_cast<int>( ply_get_argument_value( argument ) );
        break;
      case 2: 
        data->tris[ data->ntris ].z = static_cast<int>( ply_get_argument_value( argument ) );
        data->ntris += 1;
        break;
    }

    return 1;
  }

}

//------------------------------------------------------------------------------
// 
//  PlyLoader implementation
//
//------------------------------------------------------------------------------


PlyLoader::PlyLoader( const std::string&   filename,
                      optix::Context       context,
                      optix::GeometryGroup geometrygroup,
                      optix::Material      material,
                      const char* ASBuilder,
                      const char* ASTraverser,
                      const char* ASRefine,
                      bool large_geom )
: m_filename( filename ),
  m_context( context ),
  m_geometrygroup( geometrygroup ),
  m_material( material ),
  m_large_geom( large_geom),
  m_ASBuilder  (ASBuilder),
  m_ASTraverser(ASTraverser),
  m_ASRefine   (ASRefine)
{
  // Error checking on context and geometrygroup done in ModelLoader

  if( material.get() == 0 ) {
    const std::string ptx_path = std::string( sutilSamplesPtxDir() ) + "/cuda_compile_ptx_generated_phong.cu.ptx";
    m_material = context->createMaterial();
    m_material->setClosestHitProgram( 0, m_context->createProgramFromPTXFile( ptx_path, "closest_hit_radiance" ) );
    m_material->setAnyHitProgram    ( 1, m_context->createProgramFromPTXFile( ptx_path, "any_hit_shadow" ) );
    m_material[ "Kd"           ]->setFloat( 0.50f, 0.50f, 0.50f );
    m_material[ "Ks"           ]->setFloat( 0.00f, 0.00f, 0.00f );
    m_material[ "Ka"           ]->setFloat( 0.05f, 0.05f, 0.05f );
    m_material[ "reflectivity" ]->setFloat( 0.00f, 0.00f, 0.00f );
    m_material[ "phong_exp"    ]->setFloat( 1.00f );
  }
}


void PlyLoader::load()
{
  load( optix::Matrix4x4::identity() );
}


void PlyLoader::load( const optix::Matrix4x4& transform )
{
  p_ply ply = ply_open( m_filename.c_str(), 0);
  if( !ply ) {
    throw optix::Exception( "Error opening ply file (" + m_filename + ")" );
  }

  if( !ply_read_header( ply ) ) {
    throw optix::Exception( "Error parsing ply header (" + m_filename + ")" );
  }

  ModelData data;
  const int nverts = 
    ply_set_read_cb( ply, "vertex", "x", vertexCB, &data, 0);
  ply_set_read_cb( ply, "vertex", "y", vertexCB, &data, 1);
  ply_set_read_cb( ply, "vertex", "z", vertexCB, &data, 2);

  const int nnormals =
    ply_set_read_cb( ply, "vertex", "nx", vertexCB, &data, 3);
  ply_set_read_cb( ply, "vertex", "ny", vertexCB, &data, 4);
  ply_set_read_cb( ply, "vertex", "nz", vertexCB, &data, 5);

  int ntris = ply_set_read_cb(ply, "face", "vertex_indices", faceCB, &data, 0);

  data.verts = new optix::float3[ nverts ];
  if( nnormals > 0 )  data.normals = new optix::float3[ nnormals ];
  data.tris  = new optix::int3[ ntris ];

  if( !ply_read( ply ) ) {
    throw optix::Exception( "Error parsing ply file (" + m_filename + ")" );
  }
  ply_close(ply);

  m_aabb = data.aabb;

  /*
  std::cerr << " done.  got " << nverts << " verts and " << ntris << " tris." << std::endl;

  for( int i = 0; i < 10; ++i ) {
    std::cerr << " v: " << data.verts[i] << std::endl;
  }

  for( int i = 0; i < 10; ++i ) {
    std::cerr << " f: " << data.tris[i] << std::endl;
  }
  */

  createGeometryInstance( data.nverts, data.verts, 
    data.nnormals == data.nverts ? data.normals : 0, 
    data.ntris, data.tris );

  delete [] data.verts; data.verts = 0;
  delete [] data.normals; data.normals = 0;
  delete [] data.tris; data.tris = 0;

}

void PlyLoader::createGeometryInstance( 
  unsigned nverts, optix::float3 const* verts, optix::float3 const* normals, 
  unsigned ntris, optix::int3 const* tris )
{
  if (m_large_geom) {
    if( m_ASBuilder == std::string("Sbvh") || m_ASBuilder == std::string("KdTree")) {
      m_ASBuilder = "MedianBvh";
      m_ASTraverser = "Bvh";
    }


    RTgeometry geometry;
    unsigned int usePTX32InHost64 = 0;
    rtuCreateClusteredMesh( m_context->get(), usePTX32InHost64, &geometry, nverts, 
                           (const float*)verts, ntris, (const unsigned int*)tris, 0 );
    optix::Geometry mesh = optix::Geometry::take(geometry);
   
    optix::GeometryInstance instance = m_context->createGeometryInstance( mesh, &m_material, &m_material+1 );

    optix::Acceleration acceleration = m_context->createAcceleration(m_ASBuilder, m_ASTraverser);
    acceleration->setProperty( "refine", m_ASRefine );
    acceleration->setProperty( "leaf_size", "1" );
    acceleration->markDirty();

    m_geometrygroup->setAcceleration( acceleration );
    m_geometrygroup->setChildCount( 1u );
    m_geometrygroup->setChild( 0, instance );
  } else {
    optix::Buffer vertex_buffer = m_context->createBuffer( RT_BUFFER_INPUT, RT_FORMAT_FLOAT3, nverts );
    memcpy( vertex_buffer->map(), verts, sizeof( optix::float3 )*nverts );
    vertex_buffer->unmap();

    optix::Buffer vindex_buffer = m_context->createBuffer( RT_BUFFER_INPUT, RT_FORMAT_INT3, ntris );
    memcpy( vindex_buffer->map(), tris, sizeof( optix::int3 )*ntris );
    vindex_buffer->unmap();

    optix::Buffer normal_buffer;
    optix::Buffer nindex_buffer;
    if( normals ) {
      normal_buffer = m_context->createBuffer( RT_BUFFER_INPUT, RT_FORMAT_FLOAT3, nverts );
      memcpy( normal_buffer->map(), normals, sizeof( optix::float3 )*nverts );
      normal_buffer->unmap();
      nindex_buffer = m_context->createBuffer( RT_BUFFER_INPUT, RT_FORMAT_INT3, ntris );
      memcpy( nindex_buffer->map(), tris, sizeof( optix::int3 )*ntris );
      nindex_buffer->unmap();
    }
    std::string ptx_path = std::string( sutilSamplesPtxDir() ) + (normals ? 
      "/cuda_compile_ptx_generated_triangle_mesh.cu.ptx" :
      "/cuda_compile_ptx_generated_triangle_mesh_small.cu.ptx");

    optix::Geometry mesh = m_context->createGeometry();
    mesh->setPrimitiveCount( ntris );
    mesh->setIntersectionProgram( m_context->createProgramFromPTXFile( ptx_path, "mesh_intersect" ) );
    mesh->setBoundingBoxProgram(  m_context->createProgramFromPTXFile( ptx_path, "mesh_bounds" ) );
    mesh[ "vertex_buffer" ]->set( vertex_buffer );
    mesh[ "vindex_buffer" ]->set( vindex_buffer );
    if( normals ) {
      mesh[ "normal_buffer" ]->set( normal_buffer );
      mesh[ "nindex_buffer" ]->set( nindex_buffer );
      
      // dummy buffers for unused attributes
      mesh[ "texcoord_buffer" ]->set( m_context->createBuffer( RT_BUFFER_INPUT, RT_FORMAT_FLOAT2, 1) );
      optix::Buffer dummy_indices = m_context->createBuffer( RT_BUFFER_INPUT, RT_FORMAT_INT3, ntris );
      memset( dummy_indices->map(), ~0, ntris * sizeof( optix::int3 ));
      dummy_indices->unmap();
      mesh[ "tindex_buffer" ]->set( dummy_indices );

      optix::Buffer material_buffer = m_context->createBuffer( RT_BUFFER_INPUT, RT_FORMAT_UNSIGNED_INT, ntris );
      memset( material_buffer->map(), 0, ntris * sizeof( int ));
      material_buffer->unmap();
      mesh[ "material_buffer" ]->set( material_buffer );
    }

    optix::GeometryInstance instance = m_context->createGeometryInstance( mesh, &m_material, &m_material+1 );

    optix::Acceleration acceleration = m_context->createAcceleration(m_ASBuilder, m_ASTraverser);
    acceleration->setProperty( "refine", m_ASRefine );
    if ( m_ASBuilder   == std::string("Sbvh")           ||
         m_ASBuilder   == std::string("Trbvh")          ||
         m_ASBuilder   == std::string("TriangleKdTree") ||
         m_ASTraverser == std::string( "KdTree")        )
    {
      acceleration->setProperty( "vertex_buffer_name", "vertex_buffer" );
      acceleration->setProperty( "index_buffer_name", "vindex_buffer" );
    }
    acceleration->markDirty();

    m_geometrygroup->setAcceleration( acceleration );
    m_geometrygroup->setChildCount( 1u );
    m_geometrygroup->setChild( 0, instance );
  }
}


bool PlyLoader::isMyFile( const std::string& filename )
{
  return getExtension( filename ) == "ply";
}

