
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

/*
 *  A simple selector sample.
 */

#include <optix.h>
#include <optixu/optixu_math_namespace.h>
#include <sutil.h>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace optix;;

unsigned width  = 1024;
unsigned height = 768;

const unsigned NUM_RAY_TYPES = 2;
const unsigned STACK_SIZE    = 1024;

// Scene setup functions
void create_context( RTcontext* context, RTbuffer* output_buffer );
void create_materials( RTcontext context, RTmaterial material[] );
void create_geometry( RTcontext context, RTmaterial material[] );

// Helper functions
void               makeMaterialPrograms  ( RTcontext context, RTmaterial material, const char *filename, const char *ch_program_name, const char *ah_program_name );
RTvariable         makeMaterialVariable1i( RTcontext context, RTmaterial material, const char *name, int i1 );
RTvariable         makeMaterialVariable1f( RTcontext context, RTmaterial material, const char *name, float f1 );
RTvariable         makeMaterialVariable3f( RTcontext context, RTmaterial material, const char *name, float f1, float f2, float f3 );
RTgeometry         makeGeometry          ( RTcontext context, unsigned int primitives);
void               makeGeometryPrograms  ( RTcontext context, RTgeometry geometry, const char *filename, const char *is_program_name, const char *bb_program_name );
RTvariable         makeGeometryVariable4f( RTcontext context, RTgeometry geometry, const char *name, float f1, float f2, float f3, float f4 );
RTgeometryinstance makeGeometryInstance  ( RTcontext context, RTgeometry geometry, RTmaterial material );
RTgeometrygroup    makeGeometryGroup     ( RTcontext context, RTgeometryinstance instance, RTacceleration acceleration );
RTacceleration     makeAcceleration      ( RTcontext context, const char *builder, const char *traverser );

std::string        ptxpath( const std::string& base );
void               printUsageAndExit( const std::string& argv0 );

// -----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
  RTcontext  context;
  RTbuffer   output_buffer;
  RTmaterial material[2];

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
 
  create_context( &context, &output_buffer );
  create_materials( context, material );
  create_geometry( context, material );

  RT_CHECK_ERROR( rtContextValidate(context) );
  RT_CHECK_ERROR( rtContextCompile(context) );
  RT_CHECK_ERROR( rtContextLaunch2D(context,0,width,height) );
  if( outfile.empty() ) {
    RT_CHECK_ERROR( sutilDisplayBufferInGlutWindow( argv[0], output_buffer ) );
  } else {
    RT_CHECK_ERROR( sutilDisplayFilePPM( outfile.c_str(), output_buffer ) );
  }

  RT_CHECK_ERROR( rtContextDestroy(context) );
  return 0;
}

// -----------------------------------------------------------------------------

void create_context( RTcontext* context, RTbuffer* output_buffer )
{
  // Context
  RT_CHECK_ERROR2( rtContextCreate(context) );
  RT_CHECK_ERROR2( rtContextSetEntryPointCount(*context, 1) );
  RT_CHECK_ERROR2( rtContextSetRayTypeCount(*context, NUM_RAY_TYPES) );
  RT_CHECK_ERROR2( rtContextSetStackSize(*context, STACK_SIZE) );
  
  // Output buffer
  RT_CHECK_ERROR2( rtBufferCreate(*context,RT_BUFFER_OUTPUT,output_buffer) );
  RT_CHECK_ERROR2( rtBufferSetFormat(*output_buffer,RT_FORMAT_UNSIGNED_BYTE4) );
  RT_CHECK_ERROR2( rtBufferSetSize2D(*output_buffer,width,height) );

  // Ray generation program
  RTprogram raygen_program;
  RT_CHECK_ERROR2( rtProgramCreateFromPTXFile(*context,ptxpath("pinhole_camera.cu").c_str(),"pinhole_camera",&raygen_program) );
  RT_CHECK_ERROR2( rtContextSetRayGenerationProgram(*context,0,raygen_program) );

  // Exception program
  RTprogram exception_program;
  RT_CHECK_ERROR2( rtProgramCreateFromPTXFile(*context,ptxpath("pinhole_camera.cu").c_str(),"exception",&exception_program) );
  RT_CHECK_ERROR2( rtContextSetExceptionProgram(*context,0,exception_program) );

  // Miss program
  RTprogram miss_program;
  RT_CHECK_ERROR2( rtProgramCreateFromPTXFile(*context,ptxpath("constantbg.cu").c_str(),"miss",&miss_program) );
  RT_CHECK_ERROR2( rtContextSetMissProgram(*context,0,miss_program) );

  // System variables
  RTvariable var_output_buffer;
  RTvariable var_scene_epsilon;
  RTvariable var_max_depth;
  RTvariable var_radiance_ray_type;
  RTvariable var_shadow_ray_type;
  RTvariable var_badcolor;

  RT_CHECK_ERROR2( rtContextDeclareVariable(*context,"output_buffer",&var_output_buffer) );
  RT_CHECK_ERROR2( rtContextDeclareVariable(*context,"scene_epsilon",&var_scene_epsilon) );
  RT_CHECK_ERROR2( rtContextDeclareVariable(*context,"max_depth",&var_max_depth) );
  RT_CHECK_ERROR2( rtContextDeclareVariable(*context,"radiance_ray_type",&var_radiance_ray_type) );
  RT_CHECK_ERROR2( rtContextDeclareVariable(*context,"shadow_ray_type",&var_shadow_ray_type) );
  RT_CHECK_ERROR2( rtContextDeclareVariable(*context,"bad_color",&var_badcolor) );

  RT_CHECK_ERROR2( rtVariableSetObject(var_output_buffer,*output_buffer) );
  RT_CHECK_ERROR2( rtVariableSet1f(var_scene_epsilon,1e-3f) );
  RT_CHECK_ERROR2( rtVariableSet1i(var_max_depth,10) );
  RT_CHECK_ERROR2( rtVariableSet1ui(var_radiance_ray_type,0u) );
  RT_CHECK_ERROR2( rtVariableSet1ui(var_shadow_ray_type,1u) );
  RT_CHECK_ERROR2( rtVariableSet3f(var_badcolor,0.0f,1.0f,1.0f) );

  // Image background variables
  RTvariable var_bgcolor;
  RT_CHECK_ERROR2( rtContextDeclareVariable(*context,"bg_color",&var_bgcolor) );
  RT_CHECK_ERROR2( rtVariableSet3f(var_bgcolor,0.34f,0.55f,0.85f) );

  // Camera variables
  RTvariable var_eye;
  RTvariable var_U;
  RTvariable var_V;
  RTvariable var_W;

  RT_CHECK_ERROR2( rtContextDeclareVariable(*context,"eye",&var_eye) );
  RT_CHECK_ERROR2( rtContextDeclareVariable(*context,"U",&var_U) );
  RT_CHECK_ERROR2( rtContextDeclareVariable(*context,"V",&var_V) );
  RT_CHECK_ERROR2( rtContextDeclareVariable(*context,"W",&var_W) );

  float3 eye = make_float3(0.0f, 0.0f, 3.0f);
  float3 lookat = make_float3(0.0f, 0.0f, 0.0f);

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

  RT_CHECK_ERROR2( rtVariableSet3f(var_eye,eye.x,eye.y,eye.z) );
  RT_CHECK_ERROR2( rtVariableSet3f(var_U,camera_u.x,camera_u.y,camera_u.z) );
  RT_CHECK_ERROR2( rtVariableSet3f(var_V,camera_v.x,camera_v.y,camera_v.z) );
  RT_CHECK_ERROR2( rtVariableSet3f(var_W,lookdir.x,lookdir.y,lookdir.z) );
}

// -----------------------------------------------------------------------------

void create_materials( RTcontext context, RTmaterial material[] )
{
  RT_CHECK_ERROR( rtMaterialCreate(context, material+0) );
  RT_CHECK_ERROR( rtMaterialCreate(context, material+1) );

  makeMaterialPrograms(context, material[0], "checkerboard.cu", "closest_hit_radiance", "any_hit_shadow");
  makeMaterialVariable3f(context, material[0], "tile_size",        1.0f, 1.0f, 1.0f);
  makeMaterialVariable3f(context, material[0], "tile_color_dark",  0.0f, 0.0f, 1.0f);
  makeMaterialVariable3f(context, material[0], "tile_color_light", 0.0f, 1.0f, 1.0f);
  makeMaterialVariable3f(context, material[0], "light_direction",  0.0f, 1.0f, 1.0f);

  makeMaterialPrograms(context, material[1], "checkerboard.cu", "closest_hit_radiance", "any_hit_shadow");
  makeMaterialVariable3f(context, material[1], "tile_size",        1.0f, 1.0f, 1.0f);
  makeMaterialVariable3f(context, material[1], "tile_color_dark",  1.0f, 0.0f, 0.0f);
  makeMaterialVariable3f(context, material[1], "tile_color_light", 1.0f, 1.0f, 0.0f);
  makeMaterialVariable3f(context, material[1], "light_direction",  0.0f, 1.0f, 1.0f);
}

// -----------------------------------------------------------------------------

void create_geometry( RTcontext context, RTmaterial material[] )
{
  /* Setup two geometry groups */

  // Geometry nodes (two spheres at same position, but with different radii)
  RTgeometry geometry[2];

  geometry[0] = makeGeometry(context, 1);
  makeGeometryPrograms(context, geometry[0], "sphere.cu", "intersect", "bounds");
  makeGeometryVariable4f(context, geometry[0], "sphere", 0.0f, 0.0f, 0.0f, 0.5f);

  geometry[1] = makeGeometry(context, 1);
  makeGeometryPrograms(context, geometry[1], "sphere.cu", "intersect", "bounds");
  makeGeometryVariable4f(context, geometry[1], "sphere", 0.0f, 0.0f, 0.0f, 1.0f);

  // Geometry instance nodes
  RTgeometryinstance instance[2];
  instance[0] = makeGeometryInstance( context, geometry[0], material[0] );
  instance[1] = makeGeometryInstance( context, geometry[1], material[1] );

  // Accelerations nodes
  RTacceleration acceleration[2];
  acceleration[0] = makeAcceleration( context, "NoAccel", "NoAccel" );
  acceleration[1] = makeAcceleration( context, "NoAccel", "NoAccel" );

  // Geometry group nodes
  RTgeometrygroup group[2];
  group[0] = makeGeometryGroup( context, instance[0], acceleration[0] );
  group[1] = makeGeometryGroup( context, instance[1], acceleration[1] );

  /* Setup selector as top objects */

  // Init selector node
  RTselector selector;
  RTprogram  stor_visit_program;
  RT_CHECK_ERROR( rtSelectorCreate(context,&selector) );
  RT_CHECK_ERROR( rtProgramCreateFromPTXFile(context,ptxpath("selector_example.cu").c_str(),"visit",&stor_visit_program) );
  RT_CHECK_ERROR( rtSelectorSetVisitProgram(selector,stor_visit_program) );
  RT_CHECK_ERROR( rtSelectorSetChildCount(selector,2) );
  RT_CHECK_ERROR( rtSelectorSetChild(selector, 0, group[0]) );
  RT_CHECK_ERROR( rtSelectorSetChild(selector, 1, group[1]) );

  // Attach selector to context as top object
  RTvariable var_group;
  RT_CHECK_ERROR( rtContextDeclareVariable(context,"top_object",&var_group) );
  RT_CHECK_ERROR( rtVariableSetObject(var_group, selector) );
}

// -----------------------------------------------------------------------------

void makeMaterialPrograms( RTcontext context, RTmaterial material, const char *filename, 
                                                                   const char *ch_program_name,
                                                                   const char *ah_program_name )
{
  RTprogram ch_program;
  RTprogram ah_program;

  RT_CHECK_ERROR( rtProgramCreateFromPTXFile(context, ptxpath(filename).c_str(), ch_program_name, &ch_program) );
  RT_CHECK_ERROR( rtProgramCreateFromPTXFile(context, ptxpath(filename).c_str(), ah_program_name, &ah_program) );
  RT_CHECK_ERROR( rtMaterialSetClosestHitProgram(material, 0, ch_program) );
  RT_CHECK_ERROR( rtMaterialSetAnyHitProgram(material, 1, ah_program) );
}

// -----------------------------------------------------------------------------

RTvariable makeMaterialVariable1i( RTcontext context, RTmaterial material, const char *name, int i1 )
{
  RTvariable variable;

  RT_CHECK_ERROR( rtMaterialDeclareVariable(material, name, &variable) );
  RT_CHECK_ERROR( rtVariableSet1i(variable, i1) );

  return variable;
}

RTvariable makeMaterialVariable1f( RTcontext context, RTmaterial material, const char *name, float f1 )
{
  RTvariable variable;

  RT_CHECK_ERROR( rtMaterialDeclareVariable(material, name, &variable) );
  RT_CHECK_ERROR( rtVariableSet1f(variable, f1) );

  return variable;
}

RTvariable makeMaterialVariable3f( RTcontext context, RTmaterial material, const char *name, float f1, float f2, float f3 )
{
  RTvariable variable;

  RT_CHECK_ERROR( rtMaterialDeclareVariable(material, name, &variable) );
  RT_CHECK_ERROR( rtVariableSet3f(variable, f1, f2, f3) );

  return variable;
}

// -----------------------------------------------------------------------------

RTgeometry makeGeometry( RTcontext context, unsigned int primitives)
{
  RTgeometry geometry;

  RT_CHECK_ERROR( rtGeometryCreate(context, &geometry) );
  RT_CHECK_ERROR( rtGeometrySetPrimitiveCount(geometry, primitives) );

  return geometry;
}

// -----------------------------------------------------------------------------

void makeGeometryPrograms( RTcontext context, RTgeometry geometry, const char *filename, 
                                                                   const char *is_program_name,
                                                                   const char *bb_program_name )
{
  RTprogram is_program;
  RTprogram bb_program;

  RT_CHECK_ERROR( rtProgramCreateFromPTXFile(context, ptxpath(filename).c_str(), is_program_name, &is_program) );
  RT_CHECK_ERROR( rtProgramCreateFromPTXFile(context, ptxpath(filename).c_str(), bb_program_name, &bb_program) );
  RT_CHECK_ERROR( rtGeometrySetIntersectionProgram(geometry, is_program) );
  RT_CHECK_ERROR( rtGeometrySetBoundingBoxProgram(geometry, bb_program) );
}

// -----------------------------------------------------------------------------

RTvariable makeGeometryVariable4f( RTcontext context, RTgeometry geometry, const char *name, float f1, float f2, float f3, float f4 )
{
  RTvariable variable;

  RT_CHECK_ERROR( rtGeometryDeclareVariable(geometry, name, &variable) );
  RT_CHECK_ERROR( rtVariableSet4f(variable, f1, f2, f3, f4) );

  return variable;
}

// -----------------------------------------------------------------------------

RTgeometryinstance makeGeometryInstance( RTcontext context, RTgeometry geometry, RTmaterial material )
{
  RTgeometryinstance instance;

  RT_CHECK_ERROR( rtGeometryInstanceCreate(context, &instance) );
  RT_CHECK_ERROR( rtGeometryInstanceSetGeometry(instance, geometry) );
  RT_CHECK_ERROR( rtGeometryInstanceSetMaterialCount(instance, 1) );
  RT_CHECK_ERROR( rtGeometryInstanceSetMaterial(instance, 0, material) );

  return instance;
}

// -----------------------------------------------------------------------------

RTgeometrygroup makeGeometryGroup( RTcontext context, RTgeometryinstance instance, RTacceleration acceleration )
{
  RTgeometrygroup geometrygroup;

  RT_CHECK_ERROR( rtGeometryGroupCreate(context,& geometrygroup) );
  RT_CHECK_ERROR( rtGeometryGroupSetChildCount(geometrygroup, 1) );
  RT_CHECK_ERROR( rtGeometryGroupSetChild(geometrygroup, 0, instance) );
  RT_CHECK_ERROR( rtGeometryGroupSetAcceleration(geometrygroup, acceleration) );

  return geometrygroup;
}

// -----------------------------------------------------------------------------

RTacceleration makeAcceleration( RTcontext context, const char *builder, const char *traverser )
{
  RTacceleration acceleration;

  RT_CHECK_ERROR( rtAccelerationCreate(context, &acceleration) );
  RT_CHECK_ERROR( rtAccelerationSetBuilder(acceleration, builder) );
  RT_CHECK_ERROR( rtAccelerationSetTraverser(acceleration, traverser) );

  return acceleration;
}

// -----------------------------------------------------------------------------

std::string ptxpath( const std::string& base )
{
  return std::string(sutilSamplesPtxDir()) + "/sample8_generated_" + base + ".ptx";
}

// -----------------------------------------------------------------------------

void printUsageAndExit( const std::string& argv0 )
{
  std::cerr << "Usage  : " << argv0 << " <options>\n"
            << "Options: --help  | -h             Print this usage message\n"
            << "         --file  | -f <filename>  Specify file for image output\n"
            << "         --dim=<width>x<height>   Set image dimensions; defaults to 1024x768\n";
  exit(1); 
}
