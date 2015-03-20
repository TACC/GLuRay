
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

//-----------------------------------------------------------------------------
//
//  Sample demonstrating various instancing cases:
//    - multiple geometry instances referencing the same geometry object
//    - multiple geometry instances referencing the same material
//    - multiple transforms referencing the same geometry group
//    - sharing of acceleration structures between different geometry groups and
//      between higher level groups
//
//-----------------------------------------------------------------------------
 


#include <optixu/optixpp_namespace.h>
#include <optixu/optixu_math_namespace.h>
#include <sutil.h>
#include "commonStructs.h"

#include <iostream>
#include <string>
#include <vector>
#include <cstring> // memcpy
#include <cstdlib> // exit

using namespace optix;
using namespace std;

unsigned int width  = 1024;
unsigned int height = 720;
bool test_scale;


Context createContext();
void createMaterials( Context context, vector<Material>& materials );
void createGeometries( Context context, vector<Geometry>& geometries );
void createTopGroups( Context context, const std::vector<Geometry>& geometries,
                      const std::vector<Material>& materials,
                      bool no_accel );
std::string ptxPath( const std::string& base );
void printUsageAndExit( const std::string& argv0 );

 

int main(int argc, char* argv[])
{
  int use_glut = 1;

  /* If "--file" is specified, don't do any GL stuff */
  for( int i = 1; i < argc; ++i ) {
    if( strcmp( argv[i], "--file" ) == 0 || strcmp( argv[i], "-f" ) == 0 )
      use_glut = 0;
  }

  /* Process command line args */
  if( use_glut )
    RT_CHECK_ERROR_NO_CONTEXT( sutilInitGlut( &argc, argv ) );

  // Process command line options
  std::string outfile;
  bool no_accel = false;
  test_scale = true;
  for ( int i = 1; i < argc; i++ ) {
    std::string arg( argv[i] );
    if ( arg == "--no-scale" || arg == "-n" ) {
      test_scale = false;
    } else if ( arg == "--no-accel" || arg == "-na") {
      no_accel = true;
    } else if( arg == "--file" || arg == "-f" ) {
      if( i < argc-1 ) {
        outfile = argv[++i];
      } else {
        printUsageAndExit( argv[0] );
      }
    } else if ( arg == "--help" || arg == "-h" ) {
      printUsageAndExit( argv[0] );
    } else if ( arg.substr( 0, 6 ) == "--dim=" ) {
      std::string dims_arg = arg.substr(6);
      if ( sutilParseImageDimensions( dims_arg.c_str(), &width, &height ) != RT_SUCCESS ) {
        std::cerr << "Invalid window dimensions: '" << dims_arg << "'" << std::endl;
        printUsageAndExit( argv[0] );
      }
    } else {
      std::cerr << "Unknown option: '" << arg << "'\n";
      printUsageAndExit( argv[0] );
    }
  }

  try {
    vector<Material> materials;
    vector<Geometry> geometries;
    Context context = createContext();
    createMaterials( context, materials );
    createGeometries( context, geometries );
    createTopGroups( context, geometries, materials, no_accel );

    context->validate();
    context->compile();
    context->launch( 0, width, height );
    if( outfile.empty() ) {
      context->checkError( sutilDisplayBufferInGlutWindow( argv[0], context["output_buffer"]->getBuffer()->get() ) );
    } else {
      context->checkError( sutilDisplayFilePPM( outfile.c_str(), context["output_buffer"]->getBuffer()->get() ) );
    }
    context->destroy();
  } catch( Exception& e ) {
    sutilReportError( e.getErrorString().c_str() );
    exit( 1 );
  }
  return 0;
}


Context createContext()
{
  // Context.
  Context context = Context::create();
  context->setEntryPointCount( 1 );
  context->setRayTypeCount( 2 );
  context->setStackSize( 1760 );

  context["scene_epsilon"]->setFloat( 1.e-3f );
  context["radiance_ray_type"]->setUint( 0u );
  context["shadow_ray_type"]->setUint( 1u );
  context["max_depth"]->setInt( 2 );
  context["ambient_light_color"]->setFloat( 1.0f, 1.0f, 1.0f );
  
  // Output buffer.
  Variable output_buffer = context["output_buffer"];
  Buffer buffer = context->createBuffer( RT_BUFFER_OUTPUT, RT_FORMAT_UNSIGNED_BYTE4, width, height );
  output_buffer->set(buffer);

  // Ray generation program.
  std::string ptx_path( ptxPath( "pinhole_camera.cu" ) );
  Program ray_gen_program = context->createProgramFromPTXFile( ptx_path, "pinhole_camera" );
  context->setRayGenerationProgram( 0, ray_gen_program );

  // Exception program.
  Program exception_program = context->createProgramFromPTXFile( ptx_path, "exception" );
  context->setExceptionProgram( 0, exception_program );
  context["bad_color"]->setFloat( 1.0f, 1.0f, 0.0f );

  // Miss program.
  ptx_path = ptxPath( "constantbg.cu" );
  context->setMissProgram( 0, context->createProgramFromPTXFile( ptx_path, "miss" ) );
  context["bg_color"]->setFloat( 0.462f, 0.4f, 0.925f );

  // Light variables.
  BasicLight light = { make_float3(12.0f, 10.0f, 4.0f), make_float3(0.8f, 0.8f, 0.8f), 1 };

  Buffer light_buffer = context->createBuffer(RT_BUFFER_INPUT);
  light_buffer->setFormat(RT_FORMAT_USER);
  light_buffer->setElementSize(sizeof(BasicLight));
  light_buffer->setSize( 1 );
  memcpy(light_buffer->map(), &light, sizeof(light));
  light_buffer->unmap();
  context[ "lights" ]->set( light_buffer );

  // Camera variables.
  float3 eye = make_float3(15, 10, 15);
  float3 lookat = make_float3(0.0f, 0.3f, 0.0f);
  float3 up = make_float3(0, 1, 0);
  float hfov = 60;
  float3 lookdir = normalize(lookat-eye);
  float3 camera_u = cross(lookdir, up);
  float3 camera_v = cross(camera_u, lookdir);
  float ulen = tanf(hfov/2.0f*M_PIf/180.0f);
  camera_u = normalize(camera_u);
  camera_u *= ulen;
  float aspect_ratio = (float)width/(float)height;
  float vlen = ulen/aspect_ratio;
  camera_v = normalize(camera_v);
  camera_v *= vlen;
  context["eye"]->setFloat( eye.x, eye.y, eye.z );
  context["U"]->setFloat( camera_u.x, camera_u.y, camera_u.z );
  context["V"]->setFloat( camera_v.x, camera_v.y, camera_v.z );
  context["W"]->setFloat( lookdir.x, lookdir.y, lookdir.z );

  return context;
}


void createMaterials( Context context, vector<Material>& materials )
{
  for( int i=0; i<4; ++i ) {

    // Material.
    Material material = context->createMaterial();
    Program  radiance_program = context->createProgramFromPTXFile( ptxPath( "phong.cu" ), "closest_hit_radiance" );
    Program  shadow_program   = context->createProgramFromPTXFile( ptxPath( "phong.cu" ), "any_hit_shadow" );
    material->setClosestHitProgram( 0, radiance_program );
    material->setAnyHitProgram( 1, shadow_program );

    // Variables.
    material["Ks"]->setFloat( 0.4f, 0.4f, 0.4f );
    material["phong_exp"]->setFloat( 200.0f );

    switch( i )
    {
    case 0:
      material["Ka"]->setFloat( 0.7f, 0.7f, 0.8f );
      material["Kd"]->setFloat( 0.7f, 0.7f, 0.7f );
      material["reflectivity"]->setFloat( 0.0f, 0.0f, 0.0f );
      break;
    case 1:
      material["Kd"]->setFloat( 0.5f, 0.1f, 0.1f );
      material["Ka"]->setFloat( 0.6f, 0.1f, 0.1f );
      material["reflectivity"]->setFloat( 0.1f, 0.1f, 0.1f );
      break;
    case 2:
      material["Kd"]->setFloat( 0.1f, 0.5f, 0.1f );
      material["Ka"]->setFloat( 0.1f, 0.6f, 0.1f );
      material["reflectivity"]->setFloat( 0.1f, 0.1f, 0.1f );
      break;
    case 3:
      material["Kd"]->setFloat( 0.5f, 0.5f, 0.1f );
      material["Ka"]->setFloat( 0.6f, 0.6f, 0.1f );
      material["reflectivity"]->setFloat( 0.1f, 0.1f, 0.1f );
      break;
    default: break;
    }

    materials.push_back( material );
  }
}


void createGeometries( Context context, std::vector<Geometry>& geometries )
{
  // Sphere geometry.
  Geometry sphere_geom = context->createGeometry();
  sphere_geom->setPrimitiveCount( 1u );
  sphere_geom->setBoundingBoxProgram( context->createProgramFromPTXFile( ptxPath( "sphere.cu" ), "bounds" ) );
  sphere_geom->setIntersectionProgram( context->createProgramFromPTXFile( ptxPath( "sphere.cu" ), "intersect" ) );
  sphere_geom["sphere"]->setFloat( 0.0f, 1.0f, 0.0f, 1.0f );

  // Ground geometry.
  Geometry ground_geom = context->createGeometry();
  ground_geom->setPrimitiveCount( 1u );
  ground_geom->setBoundingBoxProgram( context->createProgramFromPTXFile( ptxPath( "parallelogram.cu" ), "bounds" ) );
  ground_geom->setIntersectionProgram( context->createProgramFromPTXFile( ptxPath( "parallelogram.cu" ),"intersect" ) );

  float3 anchor = make_float3( -1, 0, 1);
  float3 v1 = make_float3( 2, 0, 0);
  float3 v2 = make_float3( 0, 0, -2);
  float3 normal = cross( v1, v2 );
  normal = normalize( normal );
  float d = dot( normal, anchor );
  v1 *= 1.0f/dot( v1, v1 );
  v2 *= 1.0f/dot( v2, v2 );
  float4 plane = make_float4( normal, d );
  ground_geom["plane"]->setFloat( plane.x, plane.y, plane.z, plane.w );
  ground_geom["v1"]->setFloat( v1.x, v1.y, v1.z );
  ground_geom["v2"]->setFloat( v2.x, v2.y, v2.z );
  ground_geom["anchor"]->setFloat( anchor.x, anchor.y, anchor.z );

  geometries.push_back( sphere_geom );
  geometries.push_back( ground_geom );
}


GeometryGroup createGeometryGroup( Context context,
                                   const vector<Material>& materials,
                                   const vector<Geometry>& geometries,
                                   int matidx )
{
  // Sphere instance.
  GeometryInstance sphere_inst = context->createGeometryInstance();
  sphere_inst->setGeometry( geometries[0] );
  sphere_inst->setMaterialCount( 1 );
  sphere_inst->setMaterial( 0, materials[matidx] );

  // Ground instance.
  GeometryInstance ground_inst = context->createGeometryInstance();
  ground_inst->setGeometry( geometries[1] );
  ground_inst->setMaterialCount( 1 );
  ground_inst->setMaterial( 0, materials[0] );

  // GeometryGroup.
  GeometryGroup geometry_group = context->createGeometryGroup();
  geometry_group->setChildCount( 2 );
  geometry_group->setChild( 0, sphere_inst );
  geometry_group->setChild( 1, ground_inst );

  return geometry_group;
}


Group createRow( Context context, GeometryGroup geometry_group )
{
  // Create a row of geometrygroups by placing a couple of transforms under a group
  // and referencing the geometrygroup multiple times.
  Group group = context->createGroup();
  group->setChildCount( 4u );

  for( int i=0; i<4; ++i )
  {
    Transform transform = context->createTransform();
    transform->setChild( geometry_group );
    group->setChild( i, transform );
    float m[16] = {1,0,0,0,
                   0,1,0,0,
                   0,0,1,0,
                   0,0,0,1 };
    m[11] = i*2.5f;
    if ( test_scale )
      m[5] =  1.0f - (float)i*0.25f;

    transform->setMatrix( false, m, NULL );
  }
  return group;
}


void createTopGroups( Context context, const vector<Geometry>& geometries, const vector<Material>& materials, bool no_accel )
{
  // Create one geometry group for each color (except the first one which is used for the ground),
  // and have them share their acceleration structure.
  Acceleration gg_accel = no_accel ?
    context->createAcceleration( "NoAccel", "NoAccel") :
    context->createAcceleration( "Bvh", "Bvh" );

  vector<GeometryGroup> geometry_groups;
  for( int i=0; i < (int)materials.size()-1; ++i ) {
    geometry_groups.push_back( createGeometryGroup( context, materials, geometries, i+1) );
    geometry_groups[i]->setAcceleration( gg_accel );
  }
  
  // Create one row group for each color, with all the groups sharing a single acceleration structure.
  Acceleration row_accel = no_accel ?
    context->createAcceleration( "NoAccel", "NoAccel") :
    context->createAcceleration( "MedianBvh", "Bvh" );
  vector<Group> row_groups;
  for( int i=0; i < (int)geometry_groups.size(); ++i ) {
    row_groups.push_back( createRow( context, geometry_groups[i] ) );
    row_groups[i]->setAcceleration( row_accel );
  }

  // Create a toplevel group holding all the row groups.
  Acceleration top_accel = no_accel ?
    context->createAcceleration( "NoAccel", "NoAccel") :
    context->createAcceleration( "Bvh", "Bvh" );
  Group top_group = context->createGroup();;
  top_group->setChildCount( static_cast<unsigned int>( row_groups.size() ) );
  for( unsigned int i=0; i < row_groups.size(); ++i ) {
    Transform transform = context->createTransform();
    transform->setChild( row_groups[i] );
    float m[16] = {1,0,0,0,
                   0,1,0,0,
                   0,0,1,0,
                   0,0,0,1 };
    m[3] = i * 3.0f;
    transform->setMatrix( false, m, 0);
    top_group->setChild( i, transform );
  }
  top_group->setAcceleration( top_accel );
  
  // Attach to context
  context["top_object"]->set( top_group );
  context["top_shadower"]->set( top_group );
}


std::string ptxPath( const std::string& base )
{
  return std::string(sutilSamplesPtxDir()) + "/sample7_generated_" + base + ".ptx";
}


void printUsageAndExit( const std::string& argv0 )
{
  std::cerr << "Usage  : " << argv0 << " [options]\n"
            << "Options: --help     | -h             Print this usage message\n"
            << "         --file     | -f <filename>  Specify file for image output\n"
            << "       : --no-scale | -n             Turn off testing of scale transformations\n" 
            << "         --dim=<width>x<height>      Set image dimensions; defaults to 1024x720\n";
  exit(1); 
}   

