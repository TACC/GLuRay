
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
//  materials.cpp - Demonstrates a progression of materials shaders from simple
//                  to complex
//
//-----------------------------------------------------------------------------

#include <optixu/optixpp_namespace.h>
#include <optixu/optixu_math_namespace.h>
#include <GLUTDisplay.h>
#include "commonStructs.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace optix;


//-----------------------------------------------------------------------------
// 
// Material Scene
//
//-----------------------------------------------------------------------------

class MaterialScene : public SampleScene
{
public:
  // From SampleScene
  virtual void   initScene( InitialCameraData& camera_data );
  virtual void   trace( const RayGenCameraData& camera_data );
  virtual Buffer getOutputBuffer();

  void createGeometry();

  static bool m_useGLBuffer;
private:
  static unsigned int WIDTH;
  static unsigned int HEIGHT;
};

unsigned int MaterialScene::WIDTH  = 640u;
unsigned int MaterialScene::HEIGHT = 480u;

// make PBOs default since it's a lot of faster
bool MaterialScene::m_useGLBuffer = true;


void MaterialScene::initScene( InitialCameraData& camera_data )
{
  try {
    // Setup state
    m_context->setRayTypeCount( 2 );
    m_context->setEntryPointCount( 1 );
    m_context->setStackSize(1040);

    m_context["max_depth"]->setInt( 5 );
    m_context["radiance_ray_type"]->setUint( 0u );
    m_context["shadow_ray_type"]->setUint( 1u );
    m_context["scene_epsilon"]->setFloat( 1.e-4f );

    Variable output_buffer = m_context["output_buffer"];

    output_buffer->set(createOutputBuffer(RT_FORMAT_UNSIGNED_BYTE4, WIDTH, HEIGHT ) );

    // Set up camera
    camera_data = InitialCameraData( make_float3( 0.0f, 2.0f, 9.0f ), // eye
                                     make_float3( 0.0f, 0.3f, 0.0f ), // lookat
                                     make_float3( 0.0f, 1.0f, 0.0f ), // up
                                     60.0f );                          // vfov

    // Declare camera variables.  The values do not matter, they will be overwritten in trace.
    m_context["eye"]->setFloat( make_float3( 0.0f, 0.0f, 0.0f ) );
    m_context["U"]->setFloat( make_float3( 0.0f, 0.0f, 0.0f ) );
    m_context["V"]->setFloat( make_float3( 0.0f, 0.0f, 0.0f ) );
    m_context["W"]->setFloat( make_float3( 0.0f, 0.0f, 0.0f ) );

    // Ray gen program
    std::string ptx_path( ptxpath( "materials", "pinhole_camera.cu" ) );
    Program ray_gen_program = m_context->createProgramFromPTXFile( ptx_path, "pinhole_camera" );
    m_context["lens_angle"]->setFloat( 90.0f );
    m_context->setRayGenerationProgram( 0, ray_gen_program );

    // Exception
    Program exception_program = m_context->createProgramFromPTXFile( ptx_path, "exception" );
    m_context->setExceptionProgram( 0, exception_program );
    m_context["bad_color"]->setFloat( 1.0f, 1.0f, 0.0f );

    // Miss program
    ptx_path = ptxpath( "materials", "gradientbg.cu" );
    m_context->setMissProgram( 0, m_context->createProgramFromPTXFile( ptx_path, "miss" ) );
    m_context["background_light"]->setFloat( 0.2f, 0.2f, 0.7f );
    m_context["background_dark"]->setFloat( 0.7f, 0.7f, 0.2f );
    m_context["up"]->setFloat( normalize( make_float3( 0.0f, 1.0f, -0.5f ) ) );

    // Setup lights
    m_context["ambient_light_color"]->setFloat( 0.05f, 0.05f, 0.05f );
    BasicLight lights[] = { 
      { { -5.0f, 8.0f, 5.0f }, { 0.5f, 0.5f, 0.3f }, 1 },
      { { 15.0f, 8.0f, 0.0f }, { 0.1f, 0.1f, 0.3f }, 1 }
    };

    Buffer light_buffer = m_context->createBuffer(RT_BUFFER_INPUT);
    light_buffer->setFormat(RT_FORMAT_USER);
    light_buffer->setElementSize(sizeof(BasicLight));
    light_buffer->setSize( sizeof(lights)/sizeof(lights[0]) );
    memcpy(light_buffer->map(), lights, sizeof(lights));
    light_buffer->unmap();

    m_context["lights"]->set(light_buffer);

    // Create scene geom
    createGeometry();

    // Finalize
    m_context->validate();
    m_context->compile();

  } catch( Exception& e ){
    sutilReportError( e.getErrorString().c_str() );
    exit(1);
  }
}


Buffer MaterialScene::getOutputBuffer()
{
  return m_context["output_buffer"]->getBuffer();
}


void MaterialScene::trace( const RayGenCameraData& camera_data )
{
  m_context["eye"]->setFloat( camera_data.eye );
  m_context["U"]->setFloat( camera_data.U );
  m_context["V"]->setFloat( camera_data.V );
  m_context["W"]->setFloat( camera_data.W );

  Buffer buffer = m_context["output_buffer"]->getBuffer();
  RTsize buffer_width, buffer_height;
  buffer->getSize( buffer_width, buffer_height );

  m_context->launch( 0, 
                    static_cast<unsigned int>(buffer_width),
                    static_cast<unsigned int>(buffer_height)
                    );
}

void MaterialScene::createGeometry()
{
  // Create materials
  Program phong_ch = m_context->createProgramFromPTXFile( ptxpath( "materials", "phong.cu" ), "closest_hit_radiance" );
  Program phong_ah = m_context->createProgramFromPTXFile( ptxpath( "materials", "phong.cu" ), "any_hit_shadow" );

  std::vector<Material> materials;
  materials.push_back( m_context->createMaterial() );
  materials.back()["Kd"]->setFloat( 0.7f, 0.7f, 0.7f);
  materials.back()->setClosestHitProgram( 0, m_context->createProgramFromPTXFile( ptxpath( "materials", "material0.cu" ),
                                          "closest_hit_radiance" ) );

  materials.push_back( m_context->createMaterial() );
  materials.back()->setClosestHitProgram( 0, m_context->createProgramFromPTXFile( ptxpath( "materials", "material1.cu" ),
                                          "closest_hit_radiance" ) );

  materials.push_back( m_context->createMaterial() );
  materials.back()["Ka"]->setFloat( 0.1f ,0.1f ,0.1f );
  materials.back()["Kd"]->setFloat( 0.7f, 0.7f, 0.7f);
  materials.back()->setClosestHitProgram( 0, m_context->createProgramFromPTXFile( ptxpath( "materials", "material2.cu" ),
                                          "closest_hit_radiance" ) );

  materials.push_back( m_context->createMaterial() );
  materials.back()["Ka"]->setFloat( 0.1f, 0.1f, 0.1f );
  materials.back()["Kd"]->setFloat( 0.7f, 0.7f, 0.7f);
  materials.back()["Ks"]->setFloat( 0.3f, 0.3f, 0.3f);
  materials.back()["phong_exp"]->setFloat( 32.0f );
  materials.back()->setClosestHitProgram( 0, m_context->createProgramFromPTXFile( ptxpath( "materials", "material3.cu" ),
                                          "closest_hit_radiance" ) );
  materials.back()["phong_exp"]->setFloat(32);

  materials.push_back( m_context->createMaterial() );
  materials.back()["Ka"]->setFloat( 0.1f ,0.1f ,0.1f );
  materials.back()["Kd"]->setFloat( 0.7f, 0.7f, 0.7f);
  materials.back()["Ks"]->setFloat( 0.3f, 0.3f, 0.3f);
  materials.back()["phong_exp"]->setFloat( 32.0f );
  materials.back()->setClosestHitProgram( 0, m_context->createProgramFromPTXFile( ptxpath( "materials", "material4.cu" ),
                                          "closest_hit_radiance" ) );
  materials.back()->setAnyHitProgram( 1, m_context->createProgramFromPTXFile( ptxpath( "materials", "material4.cu" ),
                                      "any_hit_shadow" ) );

  // Create primitives
  std::vector<GeometryInstance> gis;
  Program sphere_intersect = m_context->createProgramFromPTXFile( ptxpath( "materials", "sphere.cu" ), "robust_intersect" );
  Program sphere_bounds    = m_context->createProgramFromPTXFile( ptxpath( "materials", "sphere.cu" ), "bounds" );
  Program pgram_intersect  = m_context->createProgramFromPTXFile( ptxpath( "materials", "parallelogram.cu" ), "intersect" );
  Program pgram_bounds     = m_context->createProgramFromPTXFile( ptxpath( "materials", "parallelogram.cu" ), "bounds" );
  for( unsigned int i = 0u; i < 5u; ++i ) {
    Geometry sphere = m_context->createGeometry();  
    sphere->setPrimitiveCount( 1u );
    sphere->setBoundingBoxProgram( sphere_bounds );
    sphere->setIntersectionProgram( sphere_intersect );
    sphere["sphere"]->setFloat( -5.0f + 2.5f*static_cast<float>( i ), 1.0f, 0.0f, 1.0f );
    
    Geometry parallelogram = m_context->createGeometry();
    parallelogram->setPrimitiveCount( 1u );
    parallelogram->setBoundingBoxProgram( pgram_bounds );
    parallelogram->setIntersectionProgram( pgram_intersect ); 
    float3 anchor = make_float3( -6.0f + 2.5f*static_cast<float>( i ), 0.01f, 1.0f);
    float3 v1 = make_float3( 2.0f, 0.0f, 0.0f);
    float3 v2 = make_float3( 0.0f, 0.0f, -2.0f);
    float3 normal = cross( v1, v2 );
    normal = normalize( normal );
    float d = dot( normal, anchor );
    v1 *= 1.0f/dot( v1, v1 );
    v2 *= 1.0f/dot( v2, v2 );
    float4 plane = make_float4( normal, d );
    parallelogram["plane"]->setFloat( plane );
    parallelogram["v1"]->setFloat( v1 );
    parallelogram["v2"]->setFloat( v2 );
    parallelogram["anchor"]->setFloat( anchor );

    gis.push_back( m_context->createGeometryInstance( sphere, materials.begin() + i, materials.begin() + i + 1 ) );
    gis.push_back( m_context->createGeometryInstance( parallelogram, materials.begin() + i, materials.begin() + i + 1 ) );
  }


  GeometryGroup geometrygroup = m_context->createGeometryGroup();
  geometrygroup->setChildCount( static_cast<unsigned int>(gis.size()) );
  for( unsigned int i = 0u; i < gis.size(); ++i ) {
    geometrygroup->setChild( i, gis[i] );
  }
  geometrygroup->setAcceleration( m_context->createAcceleration("NoAccel","NoAccel") );

  m_context["top_object"]->set( geometrygroup );
  m_context["top_shadower"]->set( geometrygroup );
}

void printUsageAndExit( const std::string& argv0, bool doExit = true )
{
  std::cerr
    << "Usage  : " << argv0 << " [options]\n"
    << "App options:\n"
    << "  -h  | --help                               Print this usage message\n"
    << "  -P  | --pbo                                Use OpenGL PBO for output buffer\n"
    << "  -n  | --nopbo                              Use OptiX internal output buffer (Default)\n"
    << std::endl;
  GLUTDisplay::printUsage();

  std::cerr
    << "App keystrokes:\n"
    << "  p Decrease number of devices\n"
    << "  P Increase number of devices\n"
    << std::endl;

  if ( doExit ) exit(1);
}

int main( int argc, char** argv )
{
  GLUTDisplay::init( argc, argv );

  bool use_vbo_buffer = true;
  for(int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if(arg == "-P" || arg == "--pbo") {
      use_vbo_buffer = true;
    } else if( arg == "-n" || arg == "--nopbo" ) {
      use_vbo_buffer = false;
    } else if( arg == "-h" || arg == "--help" ) {
      printUsageAndExit(argv[0]);
    } else {
      std::cerr << "Unknown option '" << arg << "'\n";
      printUsageAndExit(argv[0]);
    }
  }

  if( !GLUTDisplay::isBenchmark() ) printUsageAndExit( argv[0], false );

  MaterialScene scene;
  scene.setUseVBOBuffer( use_vbo_buffer );
  GLUTDisplay::run( "MaterialScene", &scene );
  return 0;
}
