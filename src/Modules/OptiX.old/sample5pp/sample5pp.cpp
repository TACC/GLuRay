
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
//  sample5pp.cpp -- Renders sphere with a normal shader using CPP optix wrapper. 
//
//-----------------------------------------------------------------------------


#include <iostream>
#include <cstdlib>
#include <optixu/optixpp_namespace.h>
#include <sutil.h>

using namespace optix;

typedef struct struct_BoxExtent{
    float min[3];
    float max[3];
} BoxExtent;

unsigned int width  = 1024;
unsigned int height = 768;

std::string ptxPath( const std::string& base )
{
  return std::string(sutilSamplesPtxDir()) + "/sample5pp_generated_" + base + ".ptx";
}

Context  createContext();
Material createMaterial( Context context );
Geometry createGeometry( Context context );
void     createInstance( Context context, Geometry sphere, Material material );
void     printUsageAndExit( const std::string& argv0 );


int main( int argc, char** argv )
{
  // Process command line options
  std::string outfile;
  RT_CHECK_ERROR_NO_CONTEXT( sutilInitGlut( &argc, argv ) );
  for ( int i = 1; i < argc; ++i ) {
    std::string arg( argv[i] );
    if ( arg == "--help" || arg == "-h" ) {
      printUsageAndExit( argv[0] );
    } else if( arg == "--file" || arg == "-f" ) {
      if( i < argc-1 ) {
        outfile = argv[++i];
      } else {
        printUsageAndExit( argv[0] );
      }
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

  try
  {
    // Setup state
    Context  context  = createContext();
    Geometry sphere   = createGeometry( context );
    Material material = createMaterial( context );
    createInstance( context, sphere, material );

    // Run
    context->validate();
    context->compile();
    context->launch( 0, width, height );

    // DisplayImage
    if( outfile.empty() ) {
      context->checkError( sutilDisplayBufferInGlutWindow( argv[0], context["output_buffer"]->getBuffer()->get() ) );
    } else {
      context->checkError( sutilDisplayFilePPM( outfile.c_str(), context["output_buffer"]->getBuffer()->get() ) );
    }

    // Clean up
    context->destroy();

  } catch( Exception& e ){
    sutilReportError( e.getErrorString().c_str() );
    exit(1);
  }
  return( 0 );
}


Context createContext() 
{
  // Set up context
  Context context = Context::create();
  context->setRayTypeCount( 1 );
  context->setEntryPointCount( 1 );

  context["radiance_ray_type"]->setUint( 0u );
  context["scene_epsilon"]->setFloat( 1.e-4f );

  Variable output_buffer = context["output_buffer"];
  Buffer buffer = context->createBuffer( RT_BUFFER_OUTPUT, RT_FORMAT_UNSIGNED_BYTE4, width, height );
  output_buffer->set(buffer);

  // Ray generation program
  std::string ptx_path( ptxPath( "pinhole_camera.cu" ) );
  Program ray_gen_program = context->createProgramFromPTXFile( ptx_path, "pinhole_camera" );
  context->setRayGenerationProgram( 0, ray_gen_program );

  float3 cam_eye = { 0.0f, 0.0f, 5.0f };
  float3 lookat  = { 0.0f, 0.0f, 0.0f };
  float3 up      = { 0.0f, 1.0f, 0.0f };
  float  hfov    = 60.0f;
  float  aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
  float3 camera_u, camera_v, camera_w;
  sutilCalculateCameraVariables( &cam_eye.x, &lookat.x, &up.x, hfov, aspect_ratio,
                                 &camera_u.x, &camera_v.x, &camera_w.x );

  context["eye"]->setFloat( cam_eye );
  context["U"]->setFloat( camera_u );
  context["V"]->setFloat( camera_v );
  context["W"]->setFloat( camera_w );

  // Exception program
  Program exception_program = context->createProgramFromPTXFile( ptx_path, "exception" );
  context->setExceptionProgram( 0, exception_program );
  context["bad_color"]->setFloat( 1.0f, 1.0f, 0.0f );

  // Miss program
  ptx_path = ptxPath( "constantbg.cu" );
  context->setMissProgram( 0, context->createProgramFromPTXFile( ptx_path, "miss" ) );
  context["bg_color"]->setFloat( 0.3f, 0.1f, 0.2f );

  return context;
}


Geometry createGeometry( Context context )
{
  Geometry sphere = context->createGeometry();
  sphere->setPrimitiveCount( 1u );
  sphere->setBoundingBoxProgram( context->createProgramFromPTXFile( ptxPath( "sphere.cu" ), "bounds" ) );
  sphere->setIntersectionProgram( context->createProgramFromPTXFile( ptxPath( "sphere.cu" ), "intersect" ) );
  sphere["sphere"]->setFloat( 0, 0, 0, 1.5 );
  return sphere;
}


Material createMaterial( Context context )
{
  Program chp = context->createProgramFromPTXFile( ptxPath( "normal_shader.cu" ), "closest_hit_radiance" );

  Material matl = context->createMaterial();
  matl->setClosestHitProgram( 0, chp );
  return matl;
}


void createInstance( Context context, Geometry sphere, Material material )
{
  // Create geometry instance
  GeometryInstance gi = context->createGeometryInstance();
  gi->setMaterialCount( 1 );
  gi->setGeometry( sphere );
  gi->setMaterial( 0, material );

  // Create geometry group
  GeometryGroup geometrygroup = context->createGeometryGroup();
  geometrygroup->setChildCount( 1 );
  geometrygroup->setChild( 0, gi );
  geometrygroup->setAcceleration( context->createAcceleration("NoAccel","NoAccel") );

  context["top_object"]->set( geometrygroup );
}


void printUsageAndExit( const std::string& argv0 )
{ 
  std::cerr << "Usage  : " << argv0 << " [options]\n"
            << "Options: --help | -h             Print this usage message\n"
            << "         --file | -f <filename>  Specify file for image output\n"
            << "         --dim=<width>x<height>  Set image dimensions; defaults to 1024x768\n";
  exit(1); 
} 

