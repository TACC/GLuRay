
/*
 * Copyright (c) 2008 - 2010 NVIDIA Corporation.  All rights reserved.
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

//------------------------------------------------------------------------------
//
// path_tracer.cpp: render cornell box using path tracing.
//
//------------------------------------------------------------------------------


#include <optixu/optixpp_namespace.h>
#include <sutil.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <GLUTDisplay.h>
#include <PPMLoader.h>
#include <sampleConfig.h>

#include "random.h"
#include "path_tracer.h"
#include "helpers.h"

using namespace optix;


//-----------------------------------------------------------------------------
//
// PathTracerScene
//
//-----------------------------------------------------------------------------

class PathTracerScene: public SampleScene
{
public:
  // Set the actual render parameters below in main().
  PathTracerScene()
  : m_rr_begin_depth(1u)
  , m_max_depth(100u)
  , m_sqrt_num_samples( 0u )
  , m_width(512u)
  , m_height(512u)
  {}

  virtual void   initScene( InitialCameraData& camera_data );
  virtual void   trace( const RayGenCameraData& camera_data );
  virtual Buffer getOutputBuffer();

  void   setNumSamples( unsigned int sns )                           { m_sqrt_num_samples= sns; }
  void   setDimensions( const unsigned int w, const unsigned int h ) { m_width = w; m_height = h; }

private:
  // Should return true if key was handled, false otherwise.
  virtual bool keyPressed(unsigned char key, int x, int y);
  void createGeometry();

  GeometryInstance createParallelogram( const float3& anchor,
                                        const float3& offset1,
                                        const float3& offset2);

  GeometryInstance createLightParallelogram( const float3& anchor,
                                             const float3& offset1,
                                             const float3& offset2,
                                             int lgt_instance = -1);
  void setMaterial( GeometryInstance& gi,
                    Material material,
                    const std::string& color_name,
                    const float3& color);

  Program        m_pgram_bounding_box;
  Program        m_pgram_intersection;

  unsigned int   m_rr_begin_depth;
  unsigned int   m_max_depth;
  unsigned int   m_sqrt_num_samples;
  unsigned int   m_width;
  unsigned int   m_height;
  unsigned int   m_frame;
  unsigned int   m_sampling_strategy;
};


void PathTracerScene::initScene( InitialCameraData& camera_data )
{
  m_context->setRayTypeCount( 3 );
  m_context->setEntryPointCount( 1 );
  m_context->setStackSize( 1800 );

  m_context["scene_epsilon"]->setFloat( 1.e-3f );
  m_context["max_depth"]->setUint(m_max_depth);
  m_context["pathtrace_ray_type"]->setUint(0u);
  m_context["pathtrace_shadow_ray_type"]->setUint(1u);
  m_context["pathtrace_bsdf_shadow_ray_type"]->setUint(2u);
  m_context["rr_begin_depth"]->setUint(m_rr_begin_depth);


  // Setup output buffer
  Variable output_buffer = m_context["output_buffer"];
  Buffer buffer = createOutputBuffer( RT_FORMAT_FLOAT4, m_width, m_height );
  output_buffer->set(buffer);


  // Set up camera
  camera_data = InitialCameraData( make_float3( 278.0f, 273.0f, -800.0f ), // eye
                                   make_float3( 278.0f, 273.0f, 0.0f ),    // lookat
                                   make_float3( 0.0f, 1.0f,  0.0f ),       // up
                                   35.0f );                                // vfov

  // Declare these so validation will pass
  m_context["eye"]->setFloat( make_float3( 0.0f, 0.0f, 0.0f ) );
  m_context["U"]->setFloat( make_float3( 0.0f, 0.0f, 0.0f ) );
  m_context["V"]->setFloat( make_float3( 0.0f, 0.0f, 0.0f ) );
  m_context["W"]->setFloat( make_float3( 0.0f, 0.0f, 0.0f ) );

  m_context["sqrt_num_samples"]->setUint( m_sqrt_num_samples );
  m_context["bad_color"]->setFloat( 0.0f, 1.0f, 0.0f );
  m_context["bg_color"]->setFloat( make_float3(0.0f) );

  // Setup programs
  std::string ptx_path = ptxpath( "path_tracer", "path_tracer.cu" );
  Program ray_gen_program = m_context->createProgramFromPTXFile( ptx_path, "pathtrace_camera" );
  m_context->setRayGenerationProgram( 0, ray_gen_program );
  Program exception_program = m_context->createProgramFromPTXFile( ptx_path, "exception" );
  m_context->setExceptionProgram( 0, exception_program );
  m_context->setMissProgram( 0, m_context->createProgramFromPTXFile( ptx_path, "miss" ) );

  m_context["frame_number"]->setUint(1);

   // Index of sampling_stategy (BSDF, light, MIS)
  m_sampling_strategy = 0;
  m_context["sampling_stategy"]->setInt(m_sampling_strategy);

  // Create scene geometry

  createGeometry();

  // Finalize
  m_context->validate();
  m_context->compile();
}

bool PathTracerScene::keyPressed( unsigned char key, int x, int y )
{
  return false;
}

void PathTracerScene::trace( const RayGenCameraData& camera_data )
{
  m_context["eye"]->setFloat( camera_data.eye );
  m_context["U"]->setFloat( camera_data.U );
  m_context["V"]->setFloat( camera_data.V );
  m_context["W"]->setFloat( camera_data.W );

  Buffer buffer = m_context["output_buffer"]->getBuffer();
  RTsize buffer_width, buffer_height;
  buffer->getSize( buffer_width, buffer_height );

  if( m_camera_changed ) {
    m_camera_changed = false;
    m_frame = 1;
  }

  m_context["frame_number"]->setUint( m_frame++ );

  m_context->launch( 0,
                    static_cast<unsigned int>(buffer_width),
                    static_cast<unsigned int>(buffer_height)
                    );
}

//-----------------------------------------------------------------------------

Buffer PathTracerScene::getOutputBuffer()
{
  return m_context["output_buffer"]->getBuffer();
}

GeometryInstance PathTracerScene::createParallelogram( const float3& anchor,
                                                       const float3& offset1,
                                                       const float3& offset2)
{
  Geometry parallelogram = m_context->createGeometry();
  parallelogram->setPrimitiveCount( 1u );
  parallelogram->setIntersectionProgram( m_pgram_intersection );
  parallelogram->setBoundingBoxProgram( m_pgram_bounding_box );

  float3 normal = normalize( cross( offset1, offset2 ) );
  float d = dot( normal, anchor );
  float4 plane = make_float4( normal, d );

  float3 v1 = offset1 / dot( offset1, offset1 );
  float3 v2 = offset2 / dot( offset2, offset2 );

  parallelogram["plane"]->setFloat( plane );
  parallelogram["anchor"]->setFloat( anchor );
  parallelogram["v1"]->setFloat( v1 );
  parallelogram["v2"]->setFloat( v2 );

  GeometryInstance gi = m_context->createGeometryInstance();
  gi->setGeometry(parallelogram);
  return gi;
}

GeometryInstance PathTracerScene::createLightParallelogram( const float3& anchor,
                                                            const float3& offset1,
                                                            const float3& offset2,
                                                            int lgt_instance)
{
  Geometry parallelogram = m_context->createGeometry();
  parallelogram->setPrimitiveCount( 1u );
  parallelogram->setIntersectionProgram( m_pgram_intersection );
  parallelogram->setBoundingBoxProgram( m_pgram_bounding_box );

  float3 normal = normalize( cross( offset1, offset2 ) );
  float d = dot( normal, anchor );
  float4 plane = make_float4( normal, d );

  float3 v1 = offset1 / dot( offset1, offset1 );
  float3 v2 = offset2 / dot( offset2, offset2 );

  parallelogram["plane"]->setFloat( plane );
  parallelogram["anchor"]->setFloat( anchor );
  parallelogram["v1"]->setFloat( v1 );
  parallelogram["v2"]->setFloat( v2 );
  parallelogram["lgt_instance"]->setInt( lgt_instance );

  GeometryInstance gi = m_context->createGeometryInstance();
  gi->setGeometry(parallelogram);
  return gi;
}

void PathTracerScene::setMaterial( GeometryInstance& gi,
                                   Material material,
                                   const std::string& color_name,
                                   const float3& color)
{
  gi->addMaterial(material);
  gi[color_name]->setFloat(color);
}

void PathTracerScene::createGeometry()
{
  // Light buffer
  ParallelogramLight light;
  light.corner   = make_float3( 343.0f, 548.6f, 227.0f);
  light.v1       = make_float3( -130.0f, 0.0f, 0.0f);
  light.v2       = make_float3( 0.0f, 0.0f, 105.0f);
  light.normal   = normalize( cross(light.v1, light.v2) );
  light.emission = make_float3( 15.0f, 15.0f, 5.0f );

  Buffer light_buffer = m_context->createBuffer( RT_BUFFER_INPUT );
  light_buffer->setFormat( RT_FORMAT_USER );
  light_buffer->setElementSize( sizeof( ParallelogramLight ) );
  light_buffer->setSize( 1u );
  memcpy( light_buffer->map(), &light, sizeof( light ) );
  light_buffer->unmap();
  m_context["lights"]->setBuffer( light_buffer );
  // Set up material
  Material diffuse = m_context->createMaterial();
  Program diffuse_ch = m_context->createProgramFromPTXFile( ptxpath( "path_tracer", "path_tracer.cu" ), "diffuse" );
  Program diffuse_ah = m_context->createProgramFromPTXFile( ptxpath( "path_tracer", "path_tracer.cu" ), "shadow" );
  diffuse->setClosestHitProgram( 0, diffuse_ch );
  diffuse->setAnyHitProgram( 1, diffuse_ah );

  Material diffuse_light = m_context->createMaterial();
  Program diffuse_em = m_context->createProgramFromPTXFile( ptxpath( "path_tracer", "path_tracer.cu" ), "diffuseEmitter" );
  diffuse_light->setClosestHitProgram( 0, diffuse_em );

  // Set up parallelogram programs
  std::string ptx_path = ptxpath( "path_tracer", "parallelogram.cu" );
  m_pgram_bounding_box = m_context->createProgramFromPTXFile( ptx_path, "bounds" );
  m_pgram_intersection = m_context->createProgramFromPTXFile( ptx_path, "intersect" );

  // create geometry instances
  std::vector<GeometryInstance> gis;

  const float3 white = make_float3( 0.8f, 0.8f, 0.8f );
  const float3 green = make_float3( 0.05f, 0.8f, 0.05f );
  const float3 red   = make_float3( 0.8f, 0.05f, 0.05f );
  const float3 light_em = make_float3( 15.0f, 15.0f, 5.0f );

  // Floor
  gis.push_back( createParallelogram( make_float3( 0.0f, 0.0f, 0.0f ),
                                      make_float3( 0.0f, 0.0f, 559.2f ),
                                      make_float3( 556.0f, 0.0f, 0.0f ) ) );
  setMaterial(gis.back(), diffuse, "diffuse_color", white);

  // Ceiling
  gis.push_back( createParallelogram( make_float3( 0.0f, 548.8f, 0.0f ),
                                      make_float3( 556.0f, 0.0f, 0.0f ),
                                      make_float3( 0.0f, 0.0f, 559.2f ) ) );
  setMaterial(gis.back(), diffuse, "diffuse_color", white);

  // Back wall
  gis.push_back( createParallelogram( make_float3( 0.0f, 0.0f, 559.2f),
                                      make_float3( 0.0f, 548.8f, 0.0f),
                                      make_float3( 556.0f, 0.0f, 0.0f) ) );
  setMaterial(gis.back(), diffuse, "diffuse_color", white);

  // Right wall
  gis.push_back( createParallelogram( make_float3( 0.0f, 0.0f, 0.0f ),
                                      make_float3( 0.0f, 548.8f, 0.0f ),
                                      make_float3( 0.0f, 0.0f, 559.2f ) ) );
  setMaterial(gis.back(), diffuse, "diffuse_color", green);

  // Left wall
  gis.push_back( createParallelogram( make_float3( 556.0f, 0.0f, 0.0f ),
                                      make_float3( 0.0f, 0.0f, 559.2f ),
                                      make_float3( 0.0f, 548.8f, 0.0f ) ) );
  setMaterial(gis.back(), diffuse, "diffuse_color", red);

  // Short block
  gis.push_back( createParallelogram( make_float3( 130.0f, 165.0f, 65.0f),
                                      make_float3( -48.0f, 0.0f, 160.0f),
                                      make_float3( 160.0f, 0.0f, 49.0f) ) );
  setMaterial(gis.back(), diffuse, "diffuse_color", white);
  gis.push_back( createParallelogram( make_float3( 290.0f, 0.0f, 114.0f),
                                      make_float3( 0.0f, 165.0f, 0.0f),
                                      make_float3( -50.0f, 0.0f, 158.0f) ) );
  setMaterial(gis.back(), diffuse, "diffuse_color", white);
  gis.push_back( createParallelogram( make_float3( 130.0f, 0.0f, 65.0f),
                                      make_float3( 0.0f, 165.0f, 0.0f),
                                      make_float3( 160.0f, 0.0f, 49.0f) ) );
  setMaterial(gis.back(), diffuse, "diffuse_color", white);
  gis.push_back( createParallelogram( make_float3( 82.0f, 0.0f, 225.0f),
                                      make_float3( 0.0f, 165.0f, 0.0f),
                                      make_float3( 48.0f, 0.0f, -160.0f) ) );
  setMaterial(gis.back(), diffuse, "diffuse_color", white);
  gis.push_back( createParallelogram( make_float3( 240.0f, 0.0f, 272.0f),
                                      make_float3( 0.0f, 165.0f, 0.0f),
                                      make_float3( -158.0f, 0.0f, -47.0f) ) );
  setMaterial(gis.back(), diffuse, "diffuse_color", white);

  // Tall block
  gis.push_back( createParallelogram( make_float3( 423.0f, 330.0f, 247.0f),
                                      make_float3( -158.0f, 0.0f, 49.0f),
                                      make_float3( 49.0f, 0.0f, 159.0f) ) );
  setMaterial(gis.back(), diffuse, "diffuse_color", white);
  gis.push_back( createParallelogram( make_float3( 423.0f, 0.0f, 247.0f),
                                      make_float3( 0.0f, 330.0f, 0.0f),
                                      make_float3( 49.0f, 0.0f, 159.0f) ) );
  setMaterial(gis.back(), diffuse, "diffuse_color", white);
  gis.push_back( createParallelogram( make_float3( 472.0f, 0.0f, 406.0f),
                                      make_float3( 0.0f, 330.0f, 0.0f),
                                      make_float3( -158.0f, 0.0f, 50.0f) ) );
  setMaterial(gis.back(), diffuse, "diffuse_color", white);
  gis.push_back( createParallelogram( make_float3( 314.0f, 0.0f, 456.0f),
                                      make_float3( 0.0f, 330.0f, 0.0f),
                                      make_float3( -49.0f, 0.0f, -160.0f) ) );
  setMaterial(gis.back(), diffuse, "diffuse_color", white);
  gis.push_back( createParallelogram( make_float3( 265.0f, 0.0f, 296.0f),
                                      make_float3( 0.0f, 330.0f, 0.0f),
                                      make_float3( 158.0f, 0.0f, -49.0f) ) );
  setMaterial(gis.back(), diffuse, "diffuse_color", white);

  // Create shadow group (no light)
  GeometryGroup shadow_group = m_context->createGeometryGroup(gis.begin(), gis.end());
  shadow_group->setAcceleration( m_context->createAcceleration("Bvh","Bvh") );
  m_context["top_shadower"]->set( shadow_group );

  // Light
  gis.push_back( createParallelogram( make_float3( 343.0f, 548.6f, 227.0f),
                                      make_float3( -130.0f, 0.0f, 0.0f),
                                      make_float3( 0.0f, 0.0f, 105.0f) ) );
  setMaterial(gis.back(), diffuse_light, "emission_color", light_em);

  // Create geometry group
  GeometryGroup geometry_group = m_context->createGeometryGroup(gis.begin(), gis.end());
  geometry_group->setAcceleration( m_context->createAcceleration("Bvh","Bvh") );
  m_context["top_object"]->set( geometry_group );
}

//-----------------------------------------------------------------------------
//
// main
//
//-----------------------------------------------------------------------------

void printUsageAndExit( const std::string& argv0, bool doExit = true )
{
  std::cerr
    << "Usage  : " << argv0 << " [options]\n"
    << "App options:\n"
    << "  -h  | --help                               Print this usage message\n"
    << " -rrd | --rr-begin-depth <d>                 Start Russian Roulette killing of rays at depth <d>\n"
    << "  -md | --max-depth <d>                      Maximum ray tree depth\n"
    << "  -n  | --sqrt_num_samples <ns>              Number of samples to perform for each frame\n"
    << "  -t  | --timeout <sec>                      Seconds before stopping rendering. Set to 0 for no stopping.\n"
    << std::endl;
  GLUTDisplay::printUsage();

  if ( doExit ) exit(1);
}


unsigned int getUnsignedArg(int& arg_index, int argc, char** argv)
{
  int result = -1;
  if (arg_index+1 < argc) {
    result = atoi(argv[arg_index+1]);
  } else {
    std::cerr << "Missing argument to "<<argv[arg_index]<<"\n";
    printUsageAndExit(argv[0]);
  }
  if (result < 0) {
    std::cerr << "Argument to "<<argv[arg_index]<<" must be positive.\n";
    printUsageAndExit(argv[0]);
  }
  ++arg_index;
  return static_cast<unsigned int>(result);
}

int main( int argc, char** argv )
{
  GLUTDisplay::init( argc, argv );

  // Process command line options
  unsigned int sqrt_num_samples = 2u;

  unsigned int width = 512u, height = 512u;
  float timeout = 10.0f;

  for ( int i = 1; i < argc; ++i ) {
    std::string arg( argv[i] );
    if ( arg == "--sqrt_num_samples" || arg == "-n" ) {
      if ( i == argc-1 ) printUsageAndExit( argv[0] );
      sqrt_num_samples = atoi( argv[++i] );
    } else if ( arg == "--timeout" || arg == "-t" ) {
      if(++i < argc) {
        timeout = static_cast<float>(atof(argv[i]));
      } else {
        std::cerr << "Missing argument to "<<arg<<"\n";
        printUsageAndExit(argv[0]);
      }
    } else if ( arg == "--help" || arg == "-h" ) {
      printUsageAndExit( argv[0] );
    } else {
      std::cerr << "Unknown option: '" << arg << "'\n";
      printUsageAndExit( argv[0] );
    }
  }

  if( !GLUTDisplay::isBenchmark() ) printUsageAndExit( argv[0], false );

  try {
    PathTracerScene scene;
    scene.setNumSamples( sqrt_num_samples );
    scene.setDimensions( width, height );
    GLUTDisplay::setProgressiveDrawingTimeout(timeout);
    GLUTDisplay::setUseSRGB(true);
    GLUTDisplay::run( "Cornell Box Scene", &scene, GLUTDisplay::CDProgressive );
  } catch( Exception& e ){
    sutilReportError( e.getErrorString().c_str() );
    exit(1);
  }

  return 0;
}
