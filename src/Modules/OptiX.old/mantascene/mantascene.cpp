
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
//  mantascene.cpp - Manta's builtin scene, for testing/benchmark purposes
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
// Manta Scene
//
//-----------------------------------------------------------------------------

class MantaScene : public SampleScene
{
public:
  // From SampleScene
  virtual void   initScene( InitialCameraData& camera_data );
  virtual void   trace( const RayGenCameraData& camera_data );
  virtual Buffer getOutputBuffer();
  virtual bool   keyPressed(unsigned char key, int x, int y);

  void createGeometry();

  static bool m_useGLBuffer;
private:
  unsigned int num_devices;
  unsigned int max_num_devices;

  static unsigned int WIDTH;
  static unsigned int HEIGHT;
};

unsigned int MantaScene::WIDTH  = 512u;
unsigned int MantaScene::HEIGHT = 512u;

// make PBOs default since it's a lot of faster
bool MantaScene::m_useGLBuffer = true;


bool MantaScene::keyPressed(unsigned char key, int x, int y)
{
  switch(key) {
    case 'P':{
      num_devices = min(num_devices+1, max_num_devices);
      std::vector<int> dev;
	  std::cerr << "Using devices: ";
      for(unsigned int i = 0; i < num_devices; ++i) {
		  std::cerr << i << " ";
		  dev.push_back(i);
	  }
	  std::cerr << std::endl;
      m_context->setDevices(dev.begin(), dev.end());
      return true;
    } break;

    case 'p':{
      num_devices = max(num_devices-1, 1);
      std::vector<int> dev;
	  std::cerr << "Using devices: ";
      for(unsigned int i = 0; i < num_devices; ++i) {
		  std::cerr << i << " ";
		  dev.push_back(i);
	  }
	  std::cerr << std::endl;
      m_context->setDevices(dev.begin(), dev.end());
      return true;
    } break;
  }

  return false;
}

void MantaScene::initScene( InitialCameraData& camera_data )
{
  try {
    // Setup state
    m_context->setRayTypeCount( 2 );
    m_context->setEntryPointCount( 1 );
    m_context->setStackSize(1200);

    num_devices = Context::getDeviceCount();
    max_num_devices = num_devices;

    m_context["max_depth"]->setInt( 5 );
    m_context["radiance_ray_type"]->setUint( 0u );
    m_context["shadow_ray_type"]->setUint( 1u );
    m_context["scene_epsilon"]->setFloat( 1.e-4f );

    Variable output_buffer = m_context["output_buffer"];

    output_buffer->set(createOutputBuffer(RT_FORMAT_UNSIGNED_BYTE4, WIDTH, HEIGHT ) );

    // Set up camera
    camera_data = InitialCameraData( make_float3( 3.0f, 2.0f, -3.0f ), // eye
                                     make_float3( 0.0f, 0.3f,  0.0f ), // lookat
                                     make_float3( 0.0f, 1.0f,  0.0f ), // up
                                     60.0f );                          // vfov

    // Declare camera variables.  The values do not matter, they will be overwritten in trace.
    m_context["eye"]->setFloat( make_float3( 0.0f, 0.0f, 0.0f ) );
    m_context["U"]->setFloat( make_float3( 0.0f, 0.0f, 0.0f ) );
    m_context["V"]->setFloat( make_float3( 0.0f, 0.0f, 0.0f ) );
    m_context["W"]->setFloat( make_float3( 0.0f, 0.0f, 0.0f ) );

    // Ray gen program
    std::string ptx_path( ptxpath( "mantascene", "pinhole_camera.cu" ) );
    Program ray_gen_program = m_context->createProgramFromPTXFile( ptx_path, "pinhole_camera" );
    m_context->setRayGenerationProgram( 0, ray_gen_program );

    // Exception
    Program exception_program = m_context->createProgramFromPTXFile( ptx_path, "exception" );
    m_context->setExceptionProgram( 0, exception_program );
    m_context["bad_color"]->setFloat( 1.0f, 1.0f, 0.0f );

    // Miss program
    m_context->setMissProgram( 0, m_context->createProgramFromPTXFile( ptxpath( "mantascene", "constantbg.cu" ), "miss" ) );
    m_context["bg_color"]->setFloat( make_float3(108.0f/255.0f, 166.0f/255.0f, 205.0f/255.0f) * 0.5f );

    // Setup lights
    m_context["ambient_light_color"]->setFloat(0,0,0);
    BasicLight lights[] = { 
      { { 0.0f, 8.0f, -5.0f }, { .6f, .1f, .1f }, 1 },
      { { 5.0f, 8.0f,  0.0f }, { .1f, .6f, .1f }, 1 },
      { { 5.0f, 2.0f, -5.0f }, { .2f, .2f, .2f }, 1 }
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


Buffer MantaScene::getOutputBuffer()
{
  return m_context["output_buffer"]->getBuffer();
}


void MantaScene::trace( const RayGenCameraData& camera_data )
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

void MantaScene::createGeometry()
{
  // Sphere
  Geometry sphere = m_context->createGeometry();
  sphere->setPrimitiveCount( 1u );
  sphere->setBoundingBoxProgram( m_context->createProgramFromPTXFile( ptxpath( "mantascene", "sphere.cu" ), "bounds" ) );
  sphere->setIntersectionProgram( m_context->createProgramFromPTXFile( ptxpath( "mantascene", "sphere.cu" ), "robust_intersect" ) );
  sphere["sphere"]->setFloat( 0.0f, 1.2f, 0.0f, 1.0f );

  // Floor
  Geometry parallelogram = m_context->createGeometry();
  parallelogram->setPrimitiveCount( 1u );

  std::string ptx_path( ptxpath( "mantascene", "parallelogram.cu" ) );
  parallelogram->setBoundingBoxProgram( m_context->createProgramFromPTXFile( ptx_path, "bounds" ) );
  parallelogram->setIntersectionProgram( m_context->createProgramFromPTXFile( ptx_path, "intersect" ) );
  float3 anchor = make_float3( -20.0f, 0.01f, 20.0f);
  float3 v1 = make_float3( 40, 0, 0);
  float3 v2 = make_float3( 0, 0, -40);
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

  // Phong programs
  Program phong_ch = m_context->createProgramFromPTXFile( ptxpath( "mantascene", "phong.cu" ), "closest_hit_radiance" );
  Program phong_ah = m_context->createProgramFromPTXFile( ptxpath( "mantascene", "phong.cu" ), "any_hit_shadow" );

  // Sphere material
  Material sphere_matl = m_context->createMaterial();
  sphere_matl->setClosestHitProgram( 0, phong_ch );
  sphere_matl->setAnyHitProgram( 1, phong_ah );

  sphere_matl["Ka"]->setFloat(0,0,0);
  sphere_matl["Kd"]->setFloat(.6f, 0, 0);
  sphere_matl["Ks"]->setFloat(.6f, .6f, .6f);
  sphere_matl["phong_exp"]->setFloat(32);
  sphere_matl["reflectivity"]->setFloat(.4f, .4f, .4f);

  // Floor material
  Program check_ch    = m_context->createProgramFromPTXFile( ptxpath( "mantascene", "checker.cu" ), "closest_hit_radiance" );
  Program check_ah    = m_context->createProgramFromPTXFile( ptxpath( "mantascene", "checker.cu" ), "any_hit_shadow" );
  Material floor_matl = m_context->createMaterial();
  floor_matl->setClosestHitProgram( 0, check_ch );
  floor_matl->setAnyHitProgram( 1, check_ah );

  floor_matl["Kd1"]->setFloat( 0.0f, 0.0f, 0.0f);
  floor_matl["Ka1"]->setFloat( 0.0f, 0.0f, 0.0f);
  floor_matl["Ks1"]->setFloat( 0.5f, 0.5f, 0.5f);
  floor_matl["reflectivity1"]->setFloat( 0.5f, 0.5f, 0.5f);
  floor_matl["phong_exp1"]->setFloat( 32.0f );
  
  floor_matl["Kd2"]->setFloat( 0.6f, 0.6f, 0.6f);
  floor_matl["Ka2"]->setFloat( 0.0f, 0.0f, 0.0f);
  floor_matl["Ks2"]->setFloat( 0.5f, 0.5f, 0.5f);
  floor_matl["reflectivity2"]->setFloat( 0.2f, 0.2f, 0.2f);
  floor_matl["phong_exp2"]->setFloat( 32.0f );

  floor_matl["inv_checker_size"]->setFloat( 40.0f, 40.0f, 1.0f );

  // Place geometry into hierarchy
  std::vector<GeometryInstance> gis;
  gis.push_back( m_context->createGeometryInstance( sphere,        &sphere_matl, &sphere_matl+1 ) );
  gis.push_back( m_context->createGeometryInstance( parallelogram, &floor_matl, &floor_matl+1 ) );

  GeometryGroup geometrygroup = m_context->createGeometryGroup();
  geometrygroup->setChildCount( static_cast<unsigned int>(gis.size()) );
  geometrygroup->setChild( 0, gis[0] );
  geometrygroup->setChild( 1, gis[1] );
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
      printUsageAndExit( argv[0] );
    } else {
      std::cerr << "Unknown option '" << arg << "'\n";
      printUsageAndExit( argv[0] );
    }
  }

  if( !GLUTDisplay::isBenchmark() ) printUsageAndExit( argv[0], false );

  try {
    MantaScene scene;
    scene.setUseVBOBuffer( use_vbo_buffer );
    GLUTDisplay::run( "MantaScene", &scene );
  } catch( Exception& e ){
    sutilReportError( e.getErrorString().c_str() );
    exit(1);
  }
  
  return 0;
}
