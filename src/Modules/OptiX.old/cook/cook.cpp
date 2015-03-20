
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
//  cook.cpp -- Cook style distributed ray tracing example, showing the '1984'
//              billiard balls scene as well as an alternate scene to demonstrate
//              depth of field
//
//  options:  -t   | --texture-path  <path_to_textures>  Specify path to textures
//            -mb  | --motion-blur                       Choose 1984 Cook scene
//            -dof | --depth-of-field                    DoF test (default)
//
//-----------------------------------------------------------------------------


#include <iostream>
#include <fstream>
#include <sstream>

#include <optix_world.h>
#include <GLUTDisplay.h>
#include <ImageLoader.h>
#include "commonStructs.h"
#include <cstdlib>
#include <cstring>

using namespace optix;

//-----------------------------------------------------------------------------

const unsigned WIDTH  = 1024u;
const unsigned HEIGHT = 1024u;

//-----------------------------------------------------------------------------

inline float deg_to_rad( float degrees )
{
  return degrees * M_PIf / 180.0f;
}

inline float rad_to_deg( float radians )
{
  return radians * 180.0f / M_PIf;
}

inline float random1()
{
  return (float)rand()/(float)RAND_MAX;
}

inline float2 random2()
{
  return make_float2( random1(), random1() );
}

inline float3 random3()
{
  return make_float3( random1(), random1(), random1() );
}

inline float4 random4()
{
  return make_float4( random1(), random1(), random1(), random1() );
}

optix::Matrix3x3 Rotation(float3 rotation)
{
  float alpha = -deg_to_rad( rotation.x );
  float beta  = -deg_to_rad( rotation.y );
  float gamma = -deg_to_rad( rotation.z );

  float s_a = sinf(alpha);
  float c_a = cosf(alpha);

  float s_b = sinf(beta);
  float c_b = cosf(beta);

  float s_g = sinf(gamma);
  float c_g = cosf(gamma);

  float rotate_x[3*3] = {   1,    0,    0,
                            0,   c_a, -s_a,
                            0,   s_a,  c_a };

  float rotate_y[3*3] = {  c_b,   0,   s_b,
                            0,    1,    0,
                          -s_b,   0,   c_b };

  float rotate_z[3*3] = {  c_g, -s_g,   0,
                           s_g,  c_g,   0, 
                            0,    0,    1 };

  optix::Matrix3x3 mat_x(rotate_x);
  optix::Matrix3x3 mat_y(rotate_y);
  optix::Matrix3x3 mat_z(rotate_z);

  optix::Matrix3x3 mat = mat_z * mat_y * mat_x;

  return mat;
}

//-----------------------------------------------------------------------------
// 
// Pool Ball
//
//-----------------------------------------------------------------------------

class PoolBall
{
public:

  PoolBall() {};
  PoolBall( Context context,
            const std::string& texture,
            float3             center,
            float              radius,
            float3             rotation,
            float3             color);
  PoolBall( Context context,
            const std::string& texture    = "",
            float              center_x   = 0.0f,
            float              center_y   = 0.0f,
            float              center_z   = 0.0f,
            float              radius     = 1.0f,
            float              rotation_x = 0.0f,
            float              rotation_y = 0.0f,
            float              rotation_z = 0.0f,
            float              color_r    = 1.0f,
            float              color_g    = 1.0f,
            float              color_b    = 1.0f );

  Material& getMaterial() { return material; }
  Geometry& getGeometry() { return geometry; }

private:

  Context  m_context;
  Material material;
  Geometry geometry;

public:

  float3 center;
  float  radius;
  float3 rotation;
  float3 color;

  void createGeometry();
  void createMaterial();
  void createTexture(const std::string& filename);
};

//-----------------------------------------------------------------------------

PoolBall::PoolBall(Context context,
                   const std::string& texture,
                   float3 center,
                   float radius,
                   float3 rotation,
                   float3 color)
 : m_context(context),
   center(center),
   radius(radius),
   rotation(rotation),
   color(color)
{
  createGeometry();
  createMaterial();
  createTexture(texture);
}

//-----------------------------------------------------------------------------

PoolBall::PoolBall(Context context,
                   const std::string& texture,
                   float center_x, float center_y, float center_z,
                   float radius,
                   float rotation_x, float rotation_y, float rotation_z,
                   float color_r, float color_g, float color_b)
 : m_context(context),
   center(make_float3(center_x, center_y, center_z)),
   radius(radius),
   rotation(make_float3(rotation_x, rotation_y, rotation_z)),
   color(make_float3(color_r, color_g, color_b))
{
  createGeometry();
  createMaterial();
  createTexture(texture);
}

//-----------------------------------------------------------------------------

void PoolBall::createGeometry()
{
  geometry = m_context->createGeometry();

  geometry->setPrimitiveCount( 1 );
  std::string ptx_path( SampleScene::ptxpath( "cook", "sphere_texcoord.cu" ) );
  geometry->setBoundingBoxProgram(  m_context->createProgramFromPTXFile( ptx_path, "bounds" ) );
  geometry->setIntersectionProgram( m_context->createProgramFromPTXFile( ptx_path, "intersect" ) );
  geometry["sphere"]->setFloat( center.x, center.y, center.z, radius );

  optix::Matrix3x3 matrix = Rotation(rotation);

  geometry["matrix_row_0"]->setFloat(matrix[0*3+0], matrix[0*3+1], matrix[0*3+2]);
  geometry["matrix_row_1"]->setFloat(matrix[1*3+0], matrix[1*3+1], matrix[1*3+2]);
  geometry["matrix_row_2"]->setFloat(matrix[2*3+0], matrix[2*3+1], matrix[2*3+2]);
}

//-----------------------------------------------------------------------------

void PoolBall::createMaterial()
{
  std::string ptx_path( SampleScene::ptxpath( "cook", "clearcoat.cu" ) );
  Program clearcoat_ch = m_context->createProgramFromPTXFile( ptx_path, "closest_hit_radiance" );
  Program clearcoat_ah = m_context->createProgramFromPTXFile( ptx_path, "any_hit_shadow" );

  material = m_context->createMaterial();

  material->setClosestHitProgram( 0, clearcoat_ch );
  material->setAnyHitProgram( 1, clearcoat_ah );

  material["importance_cutoff"]->setFloat( 1e-2f );
  material["cutoff_color"]->setFloat( 0.34f, 0.55f, 0.85f );
  material["fresnel_exponent"]->setFloat( 4.0f );
  material["fresnel_minimum"]->setFloat( 0.1f );
  material["fresnel_maximum"]->setFloat( 1.0f );
  material["reflection_color"]->setFloat( 1.0f, 1.0f, 1.0f );
  material["reflection_maxdepth"]->setInt( 5 );

  material["Ka"]->setFloat(0.2f, 0.2f, 0.2f);
  material["Ks"]->setFloat(1.0f, 1.0f, 1.0f);
  material["exponent"]->setFloat(128.0f);

  material["Kd"]->setFloat(color.x, color.y, color.z);
}

//-----------------------------------------------------------------------------

void PoolBall::createTexture(const std::string& filename)
{
  const float3 default_color = make_float3(1.0f, 1.0f, 1.0f);
  material["kd_map"]->setTextureSampler( loadTexture( m_context, filename, default_color) );
}

//-----------------------------------------------------------------------------
// 
// Cook Scene
//
//-----------------------------------------------------------------------------

class CookScene : public SampleScene
{
public:

  // SETUP_1984     -- Classic cook pool ball scene
  // SETUP_TRIANGLE -- Pool ball triangle (better suited for DoF)
  enum Setup { SETUP_1984, SETUP_TRIANGLE };

  struct Parameters
  {
    Setup setup;

    float lookfrom[3];
    float lookat[3];
    float distance_offset; // How much to offset the focal distance.  It can be
                           // negative, but the value will be clamped to the
                           // eye point minus the scene epsilon.
    float aperture;
  };

  CookScene( Setup setup_, const std::string& texture_path_, bool use_float3_output_buffer )
    : poolball(), setup( setup_ ), texture_path( texture_path_ ),
      output_buffer_format( use_float3_output_buffer ? RT_FORMAT_FLOAT3 : RT_FORMAT_FLOAT4 )
  {}

  virtual void   initScene( InitialCameraData& camera_data );
  virtual void   trace( const RayGenCameraData& camera_data );
  virtual Buffer getOutputBuffer();


private:
  std::string texpath( const std::string& base );
  void createGeometry();
  void setupTriangle();
  void setup1984();

  static Parameters     parameters[];

  std::vector<PoolBall> poolball;
  Setup                 setup;
  std::string           texture_path;
  RTformat              output_buffer_format;
};

//-----------------------------------------------------------------------------

CookScene::Parameters CookScene::parameters[] =
{
  { CookScene::SETUP_1984,     {5.0f,  5.0f, 13.7f}, {5.0f, 5.01f,  0.0f},  0.0f, 0.100f },
  { CookScene::SETUP_TRIANGLE, {5.0f, -3.0f,  5.0f}, {5.0f, 5.10f,  0.0f}, -1.5f, 0.150f }
};

//-----------------------------------------------------------------------------

void CookScene::initScene( InitialCameraData& camera_data )
{
  // Setup state
  m_context->setRayTypeCount( 2 );
  m_context->setEntryPointCount( 1 );
  m_context->setStackSize( 1440 );

  // Limit number of devices to 1 as this is faster for this particular sample.
  std::vector<int> enabled_devices = m_context->getEnabledDevices();
  m_context->setDevices(enabled_devices.begin(), enabled_devices.begin()+1);

  // Setup output buffer
  // Use float3 for testing zero-copy vs. LinearPartitioned.
  m_context["output_format"]->setInt( output_buffer_format );

  if (output_buffer_format == RT_FORMAT_FLOAT4 ) {
    m_context["output_buffer_f4"]->setBuffer( createOutputBuffer(RT_FORMAT_FLOAT4, WIDTH, HEIGHT));
    m_context["output_buffer_f3"]->setBuffer( m_context->createBuffer(RT_BUFFER_OUTPUT, RT_FORMAT_FLOAT3, 1, 1));
  }
  else {
    m_context["output_buffer_f3"]->setBuffer( createOutputBuffer(RT_FORMAT_FLOAT3, WIDTH, HEIGHT));
    m_context["output_buffer_f4"]->setBuffer( m_context->createBuffer(RT_BUFFER_OUTPUT, RT_FORMAT_FLOAT4, 1, 1));
  }


  // Setup camera
  camera_data = InitialCameraData( make_float3( parameters[setup].lookfrom[0],   // eye
                                                parameters[setup].lookfrom[1],
                                                parameters[setup].lookfrom[2] ),
                                   make_float3( parameters[setup].lookat[0],     // target
                                                parameters[setup].lookat[1],
                                                parameters[setup].lookat[2] ),
                                   make_float3( 0.0f, 1.0f,  0.0f ),             // up
                                   40.0f );                                      // vfov

  // Declare camera variables.  The values do not matter, they will be overwritten in trace.
  m_context["eye"]->setFloat( make_float3( 0.0f, 0.0f, 0.0f ) );
  m_context["U"]->setFloat( make_float3( 0.0f, 0.0f, 0.0f ) );
  m_context["V"]->setFloat( make_float3( 0.0f, 0.0f, 0.0f ) );
  m_context["W"]->setFloat( make_float3( 0.0f, 0.0f, 0.0f ) );

  // Context variables
  m_context["radiance_ray_type"]->setUint(0);
  m_context["shadow_ray_type"]->setUint(1);
  m_context["bad_color"]->setFloat( 0.0f, 1.0f, 0.0f );
  m_context["bg_color"]->setFloat( make_float3( 0.34f, 0.55f, 0.85f ) );
  m_context["scene_epsilon"]->setFloat( 1.e-2f );
  m_context["max_depth"]->setInt(5);

  // Camera parameters
  m_context["focal_scale"]->setFloat( 0.0f ); // Value is set in trace()
  m_context["aperture_radius"]->setFloat(parameters[setup].aperture);

  // Setup programs
  std::string ptx_path = ptxpath( "cook", "dof_camera.cu" );
  Program ray_gen_program = m_context->createProgramFromPTXFile( ptx_path, "dof_camera" );
  m_context->setRayGenerationProgram( 0, ray_gen_program );
  Program exception_program = m_context->createProgramFromPTXFile( ptx_path, "exception" );
  m_context->setExceptionProgram( 0, exception_program );
  m_context->setMissProgram( 0, m_context->createProgramFromPTXFile( ptxpath( "cook", "constantbg.cu" ), "miss" ) );

  // Setup lighting
  BasicLight lights[] = { 
    { make_float3( -30.0f, -10.0f, 80.0f ), make_float3( 1.0f, 1.0f, 1.0f ), 1 },
    { make_float3(  10.0f,  30.0f, 20.0f ), make_float3( 1.0f, 1.0f, 1.0f ), 1 }
  };

  Buffer light_buffer = m_context->createBuffer(RT_BUFFER_INPUT);
  light_buffer->setFormat(RT_FORMAT_USER);
  light_buffer->setElementSize(sizeof(BasicLight));
  light_buffer->setSize( sizeof(lights)/sizeof(lights[0]) );
  memcpy(light_buffer->map(), lights, sizeof(lights));
  light_buffer->unmap();

  m_context["lights"]->set(light_buffer);
  m_context["ambient_light_color"]->setFloat( 0.4f, 0.4f, 0.4f );

  // Rendering variables
  m_context["frame_number"]->setUint(1);
  m_context["jitter"]->setFloat(0.0f, 0.0f, 0.0f, 0.0f);

   // Setup secene
  createGeometry();
  m_context->validate();
  m_context->compile();
}

//-----------------------------------------------------------------------------

void CookScene::trace( const RayGenCameraData& camera_data )
{
  m_context["eye"]->setFloat( camera_data.eye );
  m_context["U"]->setFloat( camera_data.U );
  m_context["V"]->setFloat( camera_data.V );
  m_context["W"]->setFloat( camera_data.W );
  float focal_distance = length(camera_data.W) + parameters[setup].distance_offset;
  focal_distance = fmaxf(focal_distance, m_context["scene_epsilon"]->getFloat());
  float focal_scale = focal_distance / length(camera_data.W);
  m_context["focal_scale"]->setFloat( focal_scale );

  Buffer buffer = getOutputBuffer();
  RTsize buffer_width, buffer_height;
  buffer->getSize( buffer_width, buffer_height );

  if (setup == SETUP_1984)
  {
    float3 offset = random1() * make_float3(0.1f, 0.6f, 0.0f);
    poolball[4].getGeometry()["sphere"]->setFloat( poolball[4].center.x + offset.x,
                                                   poolball[4].center.y + offset.y,
                                                   poolball[4].center.z + offset.z,
                                                   poolball[4].radius );
  }

  static unsigned frame = 1;

  if( m_camera_changed ) {
    srand(1984);
    frame = 1;
    m_camera_changed = false;
  }

  m_context["frame_number"]->setUint( frame++ );
  m_context["jitter"]->setFloat( random4() );

  m_context->launch( 0,
                    static_cast<unsigned int>(buffer_width),
                    static_cast<unsigned int>(buffer_height)
                    );

}

//-----------------------------------------------------------------------------

Buffer CookScene::getOutputBuffer()
{
  return m_context[ output_buffer_format == RT_FORMAT_FLOAT4 ? "output_buffer_f4" : "output_buffer_f3" ]->getBuffer();
}

//-----------------------------------------------------------------------------

std::string CookScene::texpath( const std::string& base )
{
  return texture_path + "/" + base;
}

//-----------------------------------------------------------------------------

void CookScene::createGeometry()
{
  /* Pool balls */

  if ( setup == SETUP_1984 )
    setup1984();
  else 
    setupTriangle();

  /* Floor (pooltable) */

  std::cerr << "Initializing scene ...";
  std::cerr.flush();

  // Geometry
  Geometry parallelogram = m_context->createGeometry();
  parallelogram->setPrimitiveCount( 1u );
  std::string ptx_path = SampleScene::ptxpath("cook", "parallelogram.cu");
  parallelogram->setBoundingBoxProgram( m_context->createProgramFromPTXFile( ptx_path, "bounds" ) );
  parallelogram->setIntersectionProgram( m_context->createProgramFromPTXFile( ptx_path, "intersect" ) );

  float3 anchor = make_float3( -4.00f, -4.0f, 0.01f );
  float3 v1 = make_float3( 18.0f,  0.0f, 0.01f );
  float3 v2 = make_float3(  0.0f, 18.0f, 0.01f );

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

  // Material
  Program check_ch = m_context->createProgramFromPTXFile( ptxpath( "cook", "distributed_phong.cu" ), "closest_hit_radiance" );
  Program check_ah = m_context->createProgramFromPTXFile( ptxpath( "cook", "distributed_phong.cu" ), "any_hit_shadow" );

  Material floor_matl = m_context->createMaterial();
  floor_matl->setClosestHitProgram( 0, check_ch );
  floor_matl->setAnyHitProgram( 1, check_ah );

  floor_matl["phong_exp"]->setFloat( 0.0f );
  floor_matl["reflectivity"]->setFloat( 0.0f, 0.0f, 0.0f);

  // Texture scaling
  floor_matl["Ka"]->setFloat( 0.35f, 0.35f, 0.35f );
  floor_matl["Kd"]->setFloat( 0.50f, 0.50f, 0.50f );
  floor_matl["Ks"]->setFloat( 1.00f, 1.00f, 1.00f );

  // Floor texture
  floor_matl["ka_map"]->setTextureSampler(loadTexture(m_context, texpath("cloth.ppm"), make_float3(1, 1, 1)));
  floor_matl["kd_map"]->setTextureSampler(loadTexture(m_context, texpath("cloth.ppm"), make_float3(1, 1, 1)));
  floor_matl["ks_map"]->setTextureSampler(loadTexture(m_context, "", make_float3(0, 0, 0)));

  // Geometry group
  std::vector<GeometryInstance> gis;
  for (unsigned i=0; i<poolball.size(); i++)
  {
    gis.push_back( m_context->createGeometryInstance(   poolball[i].getGeometry(),
                                                     &(poolball[i].getMaterial()),
                                                     &(poolball[i].getMaterial())+1 ) );
  }
  gis.push_back( m_context->createGeometryInstance( parallelogram, &floor_matl, &floor_matl+1 ) );

  GeometryGroup geometrygroup = m_context->createGeometryGroup();
  if (setup == SETUP_1984)
    geometrygroup->setAcceleration( m_context->createAcceleration("NoAccel","NoAccel") );
  else
    geometrygroup->setAcceleration( m_context->createAcceleration("Sbvh","Bvh") );

  geometrygroup->setChildCount( static_cast<unsigned int>(gis.size()) );
  
  for (unsigned int i=0; i<gis.size(); i++)
    geometrygroup->setChild( i, gis[i] );

  m_context["top_object"]->set( geometrygroup );
  m_context["top_shadower"]->set( geometrygroup );
  
  std::cerr << "finished." << std::endl;
}

//-----------------------------------------------------------------------------

void CookScene::setupTriangle()
{
  float3 center[15];
  float3 rotation[15];

  float  radius = 1.0f;
  float3  color = make_float3(1.00f, 0.96f, 0.94f);

  unsigned index = 0;
  for (unsigned i=0; i<5; i++)
    for (unsigned j=0; j<=i; j++)
    {
      // pool triangle
      center[index].x = 2.0f*(float)j-(float)i;
      center[index].y = 2.0f*(float)i;
      center[index].z = 1.0f;

       // scale and translate
      center[index] *= 1.0f;
      center[index] += make_float3(5.0f, 0.5f, 0.0f);

      // random rotation
      rotation[index] = 90.0f * ( 2.0f * random3() - make_float3(1.0f, 1.0f, 1.0f) );

      index++;
    }

  std::cerr << "Reading textures ... "; 
  std::cerr.flush();
  poolball.push_back( PoolBall(m_context, texpath("pool_1.ppm"),  center[ 0], radius, rotation[ 0], color) );
  poolball.push_back( PoolBall(m_context, texpath("pool_2.ppm"),  center[ 1], radius, rotation[ 1], color) );
  poolball.push_back( PoolBall(m_context, texpath("pool_14.ppm"), center[ 2], radius, rotation[ 2], color) );
  poolball.push_back( PoolBall(m_context, texpath("pool_11.ppm"), center[ 3], radius, rotation[ 3], color) );
  poolball.push_back( PoolBall(m_context, texpath("pool_8.ppm"),  center[ 4], radius, rotation[ 4], color) );
  poolball.push_back( PoolBall(m_context, texpath("pool_5.ppm"),  center[ 5], radius, rotation[ 5], color) );
  poolball.push_back( PoolBall(m_context, texpath("pool_3.ppm"),  center[ 6], radius, rotation[ 6], color) );
  poolball.push_back( PoolBall(m_context, texpath("pool_4.ppm"),  center[ 7], radius, rotation[ 7], color) );
  poolball.push_back( PoolBall(m_context, texpath("pool_9.ppm"),  center[ 8], radius, rotation[ 8], color) );
  poolball.push_back( PoolBall(m_context, texpath("pool_13.ppm"), center[ 9], radius, rotation[ 9], color) );
  poolball.push_back( PoolBall(m_context, texpath("pool_12.ppm"), center[10], radius, rotation[10], color) );
  poolball.push_back( PoolBall(m_context, texpath("pool_6.ppm"),  center[11], radius, rotation[11], color) );
  poolball.push_back( PoolBall(m_context, texpath("pool_15.ppm"), center[12], radius, rotation[12], color) );
  poolball.push_back( PoolBall(m_context, texpath("pool_10.ppm"), center[13], radius, rotation[13], color) );
  poolball.push_back( PoolBall(m_context, texpath("pool_7.ppm"),  center[14], radius, rotation[14], color) );
  std::cerr << "finished." << std::endl;
}

//-----------------------------------------------------------------------------

void CookScene::setup1984()
{
  poolball.push_back( PoolBall(m_context, texpath("pool_1.ppm"), 1.85f, 6.28f, 1.00f,  1.00f,  -00.872f-90.0f,  28.322f, -14.422f,  1.00f, 0.96f, 0.94f) );
  poolball.push_back( PoolBall(m_context, texpath("pool_9.ppm"), 4.37f, 5.19f, 1.00f,  1.00f,   11.339f-90.0f,  14.126f, -17.257f,  1.00f, 0.96f, 0.94f) );
  poolball.push_back( PoolBall(m_context, texpath("pool_8.ppm"), 6.23f, 6.07f, 1.00f,  1.00f,   15.492f-90.0f,  16.372f, -21.111f,  1.00f, 0.96f, 0.94f) );
  poolball.push_back( PoolBall(m_context, texpath("pool_4.ppm"), 8.31f, 6.83f, 1.00f,  1.00f,   27.679f-90.0f, -02.611f, -16.905f,  1.00f, 0.96f, 0.94f) );
  poolball.push_back( PoolBall(m_context, ""                   , 3.93f, 1.91f, 1.00f,  1.00f,   00.000f,        00.000f,  00.000f,  1.00f, 0.96f, 0.58f) );
}

//-----------------------------------------------------------------------------
// 
// Main 
//
//-----------------------------------------------------------------------------

void printUsageAndExit( const std::string& argv0, bool doExit = true )
{
  std::cerr
    << "Usage  : " << argv0 << " [options]\n"
    << "App options:\n"
    << "  -h  | --help                               Print this usage message\n"
    << "  -t  | --texture-path <path>                Specify path to textures\n"
    << "  -mb | --motion-blur                        1984 Cook motion blur scene\n"
    << " -dof | --depth-of-field                     Depth of field test (default)\n"
    << "  -f3                                        Use float3 output buffer (default is float4)\n"
    << std::endl;
  GLUTDisplay::printUsage();

  if ( doExit ) exit(1);
}

//-----------------------------------------------------------------------------

int main( int argc, char** argv )
{

  GLUTDisplay::init( argc, argv );

  srand(1984);

  // Process command line options
  std::string texture_path;
  CookScene::Setup setup = CookScene::SETUP_TRIANGLE;
  bool use_float3_output_buffer = false;
  for( int i = 1; i < argc; ++i ) {
    std::string arg( argv[i] );
    if        ( arg == "-mb" || arg == "--motion-blur" ) {
      setup = CookScene::SETUP_1984;
    } else if ( arg == "-dof" || arg == "--depth-of-field" ) {
      setup = CookScene::SETUP_TRIANGLE;
    } else if ( arg == "-h" || arg == "--help" ) {
      printUsageAndExit( argv[0] );
    } else if ( arg == "-t" || arg == "--texture-path" ) {
      if ( i == argc-1 ) {
        printUsageAndExit( argv[0] );
      }
      texture_path = argv[++i];
    } else if ( arg == "-f3" ) {
      use_float3_output_buffer = true;
    } else {
      std::cerr << "Unknown option '" << arg << "'\n";
      printUsageAndExit( argv[0] );
    }
  }

  if( !GLUTDisplay::isBenchmark() ) printUsageAndExit( argv[0], false );

  if( texture_path.empty() ) {
    texture_path = std::string( sutilSamplesDir() ) + "/cook/data";
  }

  try {
    CookScene scene( setup, texture_path, use_float3_output_buffer );
    GLUTDisplay::run( "CookScene ('1984')", &scene, GLUTDisplay::CDProgressive );
  } catch( Exception& e ) {
    sutilReportError( e.getErrorString().c_str() );    
    exit(2);
  }

  return 0;
}
