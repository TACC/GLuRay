
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

#include <ObjLoader.h>
#include <optixu/optixu.h>
#include <optixu/optixu_math_namespace.h>
#include <ImageLoader.h>
#include <commonStructs.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include <string.h>

using namespace optix;

//------------------------------------------------------------------------------
// 
//  Helper functions
//
//------------------------------------------------------------------------------

namespace 
{
  std::string getExtension( const std::string& filename )
  {
    // Get the filename extension
    std::string::size_type extension_index = filename.find_last_of( "." );
    return extension_index != std::string::npos ?
           filename.substr( extension_index+1 ) :
           std::string();
  }
}

//------------------------------------------------------------------------------
// 
//  ObjLoader class definition 
//
//------------------------------------------------------------------------------

ObjLoader::ObjLoader( const char* filename,
                      Context context,
                      GeometryGroup geometrygroup,
                      Material material,
                      bool force_load_material_params,
                      const char* ASBuilder,
                      const char* ASTraverser,
                      const char* ASRefine,
                      bool large_geom )
: m_filename( filename ),
  m_context( context ),
  m_geometrygroup( geometrygroup ),
  m_vbuffer( 0 ),
  m_nbuffer( 0 ),
  m_tbuffer( 0 ),
  m_material( material ),
  m_intersect_program( 0 ),
  m_have_default_material( true ),
  m_force_load_material_params( force_load_material_params ),
  m_ASBuilder  (ASBuilder),
  m_ASTraverser(ASTraverser),
  m_ASRefine   (ASRefine),
  m_large_geom (large_geom),
  m_aabb()
{
  m_pathname = m_filename.substr(0,m_filename.find_last_of("/\\")+1);
}


ObjLoader::ObjLoader( const char* filename,
                      Context context,
                      GeometryGroup geometrygroup,
                      const char* ASBuilder,
                      const char* ASTraverser,
                      const char* ASRefine,
                      bool large_geom )
: m_filename( filename ),
  m_context( context ),
  m_geometrygroup( geometrygroup ),
  m_vbuffer( 0 ),
  m_nbuffer( 0 ),
  m_tbuffer( 0 ),
  m_material( 0 ),
  m_intersect_program( 0 ),
  m_bbox_program( 0 ),
  m_have_default_material( false ),
  m_force_load_material_params( false ),
  m_ASBuilder  (ASBuilder),
  m_ASTraverser(ASTraverser),
  m_ASRefine   (ASRefine),
  m_large_geom( large_geom),
  m_aabb()
{
  m_pathname = m_filename.substr(0,m_filename.find_last_of("/\\")+1);
}

void ObjLoader::load()
{
  load( optix::Matrix4x4::identity() );
}

void ObjLoader::setIntersectProgram( Program intersect_program )
{
  m_intersect_program = intersect_program;
}

void ObjLoader::setBboxProgram( Program bbox_program )
{
  m_bbox_program = bbox_program;
}

void ObjLoader::load( const optix::Matrix4x4& transform )
{
  // parse the OBJ file
  GLMmodel* model = glmReadOBJ( m_filename.c_str() );
  if ( !model ) {
    std::stringstream ss;
    ss << "ObjLoader::loadImpl - glmReadOBJ( '" << m_filename << "' ) failed" << std::endl;
    throw Exception( ss.str() );
  }

  // Create a single material to be shared by all GeometryInstances
  createMaterial(); 
  
  // Create vertex data buffers to be shared by all Geometries
  loadVertexData( model, transform );

  // Create a GeometryInstance and Geometry for each obj group
  createMaterialParams( model );
  createGeometryInstances( model );
  
  // Create a data for sampling light sources
  createLightBuffer( model );

  glmDelete( model );
}

void ObjLoader::createMaterial() 
{
  if ( m_have_default_material ) return;

  std::string path = std::string(sutilSamplesPtxDir()) + "/cuda_compile_ptx_generated_obj_material.cu.ptx";

  Program closest_hit = m_context->createProgramFromPTXFile( path, "closest_hit_radiance" );
  Program any_hit     = m_context->createProgramFromPTXFile( path, "any_hit_shadow" );
  m_material           = m_context->createMaterial();
  m_material->setClosestHitProgram( 0u, closest_hit );
  m_material->setAnyHitProgram( 1u, any_hit );
}


void ObjLoader::loadVertexData( GLMmodel* model, const optix::Matrix4x4& transform )
{
  unsigned int num_vertices  = model->numvertices;
  unsigned int num_texcoords = model->numtexcoords;
  unsigned int num_normals   = model->numnormals;

  // Create vertex buffer
  m_vbuffer = m_context->createBuffer( RT_BUFFER_INPUT, RT_FORMAT_FLOAT3, num_vertices );
  float3* vbuffer_data = static_cast<float3*>( m_vbuffer->map() );

  // Create normal buffer
  m_nbuffer = m_context->createBuffer( RT_BUFFER_INPUT, RT_FORMAT_FLOAT3, num_normals );
  float3* nbuffer_data = static_cast<float3*>( m_nbuffer->map() );

  // Create texcoord buffer
  m_tbuffer = m_context->createBuffer( RT_BUFFER_INPUT, RT_FORMAT_FLOAT2, num_texcoords );
  float2* tbuffer_data = static_cast<float2*>( m_tbuffer->map() );

  // Transform and copy vertices.  
  for ( unsigned int i = 0; i < num_vertices; ++i )
  {
    const float3 v3 = *((float3*)&model->vertices[(i+1)*3]);
    float4 v4 = make_float4( v3, 1.0f );
    vbuffer_data[i] = make_float3( transform*v4 );
  }

  // Transform and copy normals.
  const optix::Matrix4x4 norm_transform = transform.inverse().transpose();
  for( unsigned int i = 0; i < num_normals; ++i )
  {
    const float3 v3 = *((float3*)&model->normals[(i+1)*3]);
    float4 v4 = make_float4( v3, 0.0f );
    nbuffer_data[i] = make_float3( norm_transform*v4 );
  }

  // Copy texture coordinates.
  memcpy( static_cast<void*>( tbuffer_data ),
          static_cast<void*>( &(model->texcoords[2]) ),
          sizeof( float )*num_texcoords*2 );   

  // Calculate bbox of model
  for( unsigned int i = 0; i < num_vertices; ++i )
    m_aabb.include( vbuffer_data[i] );

  // Unmap buffers.
  m_vbuffer->unmap();
  m_nbuffer->unmap();
  m_tbuffer->unmap();
}


void ObjLoader::createGeometryInstances( GLMmodel* model )
{
  // Load triangle_mesh programs
  if( !m_intersect_program.get() ) {
    std::string path = std::string(sutilSamplesPtxDir()) + "/cuda_compile_ptx_generated_triangle_mesh.cu.ptx";
    m_intersect_program = m_context->createProgramFromPTXFile( path, "mesh_intersect" );
  }

  if( !m_bbox_program.get() ) {
    std::string path = std::string(sutilSamplesPtxDir()) + "/cuda_compile_ptx_generated_triangle_mesh.cu.ptx";
    m_bbox_program = m_context->createProgramFromPTXFile( path, "mesh_bounds" );
  }

  std::vector<GeometryInstance> instances;

  // Loop over all groups -- grab the triangles and material props from each group
  unsigned int triangle_count = 0u;
  unsigned int group_count = 0u;
  for ( GLMgroup* obj_group = model->groups;
        obj_group != 0;
        obj_group = obj_group->next, group_count++ ) {

    unsigned int num_triangles = obj_group->numtriangles;
    if ( num_triangles == 0 ) continue; 

    // Create vertex index buffers
    Buffer vindex_buffer = m_context->createBuffer( RT_BUFFER_INPUT, RT_FORMAT_INT3, num_triangles );
    int3* vindex_buffer_data = static_cast<int3*>( vindex_buffer->map() );

    Buffer tindex_buffer = m_context->createBuffer( RT_BUFFER_INPUT, RT_FORMAT_INT3, num_triangles );
    int3* tindex_buffer_data = static_cast<int3*>( tindex_buffer->map() );

    Buffer nindex_buffer = m_context->createBuffer( RT_BUFFER_INPUT, RT_FORMAT_INT3, num_triangles );
    int3* nindex_buffer_data = static_cast<int3*>( nindex_buffer->map() );

    Buffer mbuffer = m_context->createBuffer( RT_BUFFER_INPUT, RT_FORMAT_UNSIGNED_INT, num_triangles );
    unsigned int* mbuffer_data = static_cast<unsigned int*>( mbuffer->map() );

    optix::Geometry mesh;

    for ( unsigned int i = 0; i < obj_group->numtriangles; ++i, ++triangle_count ) {

      unsigned int tindex = obj_group->triangles[i];
      int3 vindices;
      vindices.x = model->triangles[ tindex ].vindices[0] - 1; 
      vindices.y = model->triangles[ tindex ].vindices[1] - 1; 
      vindices.z = model->triangles[ tindex ].vindices[2] - 1; 
      assert( vindices.x <= static_cast<int>(model->numvertices) );
      assert( vindices.y <= static_cast<int>(model->numvertices) );
      assert( vindices.z <= static_cast<int>(model->numvertices) );
      
      vindex_buffer_data[ i ] = vindices;

      int3 nindices;
      nindices.x = model->triangles[ tindex ].nindices[0] - 1; 
      nindices.y = model->triangles[ tindex ].nindices[1] - 1; 
      nindices.z = model->triangles[ tindex ].nindices[2] - 1; 
      assert( nindices.x <= static_cast<int>(model->numnormals) );
      assert( nindices.y <= static_cast<int>(model->numnormals) );
      assert( nindices.z <= static_cast<int>(model->numnormals) );

      int3 tindices;
      tindices.x = model->triangles[ tindex ].tindices[0] - 1; 
      tindices.y = model->triangles[ tindex ].tindices[1] - 1; 
      tindices.z = model->triangles[ tindex ].tindices[2] - 1; 
      assert( tindices.x <= static_cast<int>(model->numtexcoords) );
      assert( tindices.y <= static_cast<int>(model->numtexcoords) );
      assert( tindices.z <= static_cast<int>(model->numtexcoords) );

      nindex_buffer_data[ i ] = nindices;
      tindex_buffer_data[ i ] = tindices;
      mbuffer_data[ i ] = 0; // See above TODO

    }
    vindex_buffer->unmap();
    tindex_buffer->unmap();
    nindex_buffer->unmap();
    mbuffer->unmap();

    std::vector<int> tri_reindex;

    if (m_large_geom) {
      if( m_ASBuilder == std::string("Sbvh") || m_ASBuilder == std::string("KdTree")) {
        m_ASBuilder = "MedianBvh";
        m_ASTraverser = "Bvh";
      }

      float* vertex_buffer_data = static_cast<float*>( m_vbuffer->map() );
      RTsize nverts;
      m_vbuffer->getSize(nverts);

      tri_reindex.resize(num_triangles);
      RTgeometry geometry;

      unsigned int usePTX32InHost64 = 0;
      rtuCreateClusteredMeshExt( m_context->get(), usePTX32InHost64, &geometry, 
                                (unsigned int)nverts, vertex_buffer_data, 
                                 num_triangles, (const unsigned int*)vindex_buffer_data,
                                 mbuffer_data,
                                 m_nbuffer->get(), 
                                (const unsigned int*)nindex_buffer_data,
                                m_tbuffer->get(), 
                                (const unsigned int*)tindex_buffer_data);
      mesh = optix::Geometry::take(geometry);

      m_vbuffer->unmap();
      rtBufferDestroy( vindex_buffer->get() );
    } else {
      // Create the mesh object
      mesh = m_context->createGeometry();
      mesh->setPrimitiveCount( num_triangles );
      mesh->setIntersectionProgram( m_intersect_program);
      mesh->setBoundingBoxProgram( m_bbox_program );
      mesh[ "vertex_buffer" ]->setBuffer( m_vbuffer );
      mesh[ "vindex_buffer" ]->setBuffer( vindex_buffer );
      mesh[ "normal_buffer" ]->setBuffer( m_nbuffer );
      mesh[ "texcoord_buffer" ]->setBuffer( m_tbuffer );
      mesh[ "tindex_buffer" ]->setBuffer( tindex_buffer );
      mesh[ "nindex_buffer" ]->setBuffer( nindex_buffer );
      mesh[ "material_buffer" ]->setBuffer( mbuffer );
    }

    // Create the geom instance to hold mesh and material params
    GeometryInstance instance = m_context->createGeometryInstance( mesh, &m_material, &m_material+1 );
    loadMaterialParams( instance, obj_group->material );
    instances.push_back( instance );
  }

  assert( triangle_count == model->numtriangles );
  
  // Set up group 
  const unsigned current_child_count = m_geometrygroup->getChildCount();
  m_geometrygroup->setChildCount( current_child_count + static_cast<unsigned int>(instances.size()) );
  optix::Acceleration acceleration = m_context->createAcceleration(m_ASBuilder, m_ASTraverser);
  acceleration->setProperty( "refine", m_ASRefine );
  if (m_large_geom) {
    acceleration->setProperty( "leaf_size", "1" );
  } else {
    if ( m_ASBuilder   == std::string("Sbvh") ||
         m_ASBuilder   == std::string("Trbvh") ||
         m_ASBuilder   == std::string("TriangleKdTree") ||
         m_ASTraverser == std::string( "KdTree" )) {
      acceleration->setProperty( "vertex_buffer_name", "vertex_buffer" );
      acceleration->setProperty( "index_buffer_name", "vindex_buffer" );
    }
  }
  m_geometrygroup->setAcceleration( acceleration );
  acceleration->markDirty();

  for ( unsigned int i = 0; i < instances.size(); ++i )
    m_geometrygroup->setChild( current_child_count + i, instances[i] );

  if (m_large_geom) {
    rtBufferDestroy( m_vbuffer->get() );
  }
}


bool ObjLoader::isMyFile( const char* filename )
{
  return getExtension( filename ) == "obj";
}


void ObjLoader::loadMaterialParams( GeometryInstance gi, unsigned int index )
{
  // We dont need any material params if we have default material
  if ( m_have_default_material && !m_force_load_material_params) {
    return;
  }

  // If no materials were given in model use reasonable defaults
  if ( m_material_params.empty() ) {
    gi[ "emissive" ]->setFloat( 0.0f, 0.0f, 0.0f );
    gi[ "phong_exp" ]->setFloat( 32.0f );
    gi[ "reflectivity" ]->setFloat( 0.3f, 0.3f, 0.3f );
    gi[ "illum" ]->setInt( 2 );

    gi["ambient_map"]->setTextureSampler( loadTexture( m_context, "", make_float3( 0.2f, 0.2f, 0.2f ) ) );
    gi["diffuse_map"]->setTextureSampler( loadTexture( m_context, "", make_float3( 0.8f, 0.8f, 0.8f ) ) );
    gi["specular_map"]->setTextureSampler( loadTexture( m_context, "", make_float3( 0.0f, 0.0f, 0.0f ) ) );
    return;
  }

  // Load params from this material into the GI 
  if ( index < m_material_params.size() ) {
    MatParams& mp = m_material_params[index];
    gi[ "emissive"     ]->setFloat( mp.emissive );
    gi[ "reflectivity" ]->setFloat( mp.reflectivity );
    gi[ "phong_exp"    ]->setFloat( mp.phong_exp );
    gi[ "illum"        ]->setInt( mp.illum );
    gi[ "ambient_map"  ]->setTextureSampler( mp.ambient_map );
    gi[ "diffuse_map"  ]->setTextureSampler( mp.diffuse_map );
    gi[ "specular_map" ]->setTextureSampler( mp.specular_map );
    return;
  }

  // Should never reach this point
  std::cerr << "WARNING -- ObjLoader::loadMaterialParams given index out of range: "
            << index << std::endl;
}


void ObjLoader::createMaterialParams( GLMmodel* model )
{
  m_material_params.resize( model->nummaterials );
  for ( unsigned int i = 0; i < model->nummaterials; ++i ) {

    GLMmaterial& mat = model->materials[i];
    MatParams& params = m_material_params[i];

    params.emissive     = make_float3( mat.emissive[0], mat.emissive[1], mat.emissive[2] );
    params.reflectivity = make_float3( mat.specular[0], mat.specular[1], mat.specular[2] );
    params.phong_exp    = mat.shininess; 
    params.illum        = ( (mat.shader > 3) ? 2 : mat.shader ); // use 2 as default if out-of-range

    float3 Kd = make_float3( mat.diffuse[0],
                             mat.diffuse[1],
                             mat.diffuse[2] );
    float3 Ka = make_float3( mat.ambient[0],
                             mat.ambient[1],
                             mat.ambient[2] );
    float3 Ks = make_float3( mat.specular[0],
                             mat.specular[1],
                             mat.specular[2] );

    // load textures relatively to OBJ main file
    std::string ambient_map  = strlen(mat.ambient_map)  ? m_pathname + mat.ambient_map  : "";
    std::string diffuse_map  = strlen(mat.diffuse_map)  ? m_pathname + mat.diffuse_map  : "";
    std::string specular_map = strlen(mat.specular_map) ? m_pathname + mat.specular_map : "";

    params.ambient_map = loadTexture( m_context, ambient_map, Ka );
    params.diffuse_map = loadTexture( m_context, diffuse_map, Kd );
    params.specular_map = loadTexture( m_context, specular_map, Ks );
  }
}


void ObjLoader::createLightBuffer( GLMmodel* model )
{
  // create a buffer for the next-event estimation
  m_light_buffer = m_context->createBuffer( RT_BUFFER_INPUT );
  m_light_buffer->setFormat( RT_FORMAT_USER );
  m_light_buffer->setElementSize( sizeof( TriangleLight ) );

  // light sources
  std::vector<TriangleLight> lights;

  unsigned int num_light = 0u;
  unsigned int group_count = 0u;

  if (model->nummaterials > 0)
  {
    for ( GLMgroup* obj_group = model->groups; obj_group != 0; obj_group = obj_group->next, group_count++ ) 
    {
      unsigned int num_triangles = obj_group->numtriangles;
      if ( num_triangles == 0 ) continue; 
      GLMmaterial& mat = model->materials[obj_group->material];

      if ( (mat.emissive[0] + mat.emissive[1] + mat.emissive[2]) > 0.0f ) 
      {
        // extract necessary data
        for ( unsigned int i = 0; i < obj_group->numtriangles; ++i ) 
        {
          // indices for vertex data
          unsigned int tindex = obj_group->triangles[i];
          int3 vindices;
          vindices.x = model->triangles[ tindex ].vindices[0]; 
          vindices.y = model->triangles[ tindex ].vindices[1]; 
          vindices.z = model->triangles[ tindex ].vindices[2]; 

          TriangleLight light;
          light.v1 = *((float3*)&model->vertices[vindices.x * 3]);
          light.v2 = *((float3*)&model->vertices[vindices.y * 3]);
          light.v3 = *((float3*)&model->vertices[vindices.z * 3]);

          // normal vector
          light.normal = normalize( cross( light.v2 - light.v3, light.v1 - light.v3 ) );

          light.emission = make_float3( mat.emissive[0], mat.emissive[1], mat.emissive[2] );

          lights.push_back(light);
          
          num_light++;
        }
      }
    }
  }

  // write to the buffer
  m_light_buffer->setSize( 0 );
  if (num_light != 0)
  {
    m_light_buffer->setSize( num_light );
    memcpy( m_light_buffer->map(), &lights[0], num_light * sizeof( TriangleLight ) );
    m_light_buffer->unmap();
  }
}
