
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
 *  A small ambient occlusion sample.
 */


#include <optix.h>
#include <sutil.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


unsigned int width  = 256;
unsigned int height = 192;
char ptx_path[1024];

void create_context( RTcontext* context, RTbuffer* output_buffer );
void create_material( RTcontext context, RTmaterial* material );
void create_geometry( RTcontext context, RTmaterial material );

void ptxPath( const char* base, char* path );
void cross( const float a[3], const float b[3], float result[3] );
void normalize( float a[3] );
float dot( const float a[3], const float b[3] );
void printUsageAndExit( const char* argv0 );


int main(int argc, char* argv[])
{
  RTcontext  context;
  RTbuffer   output_buffer;
  RTmaterial material;

  char outfile[512];
  int i;

  outfile[0] = '\0';

  RT_CHECK_ERROR_NO_CONTEXT( sutilInitGlut( &argc, argv ) );

  /* Process command line args */
  for( i = 1; i < argc; ++i ) {
    if( strcmp( argv[i], "--help" ) == 0 || strcmp( argv[i], "-h" ) == 0 ) {
      printUsageAndExit( argv[0] );
    } else if( strcmp( argv[i], "--file" ) == 0 || strcmp( argv[i], "-f" ) == 0 ) {
      if( i < argc-1 ) {
        strcpy( outfile, argv[++i] );
      } else {
        printUsageAndExit( argv[0] );
      }
    } else if ( strncmp( argv[i], "--dim=", 6 ) == 0 ) {
      const char *dims_arg = &argv[i][6];
      if ( sutilParseImageDimensions( dims_arg, &width, &height ) != RT_SUCCESS ) {
        fprintf( stderr, "Invalid window dimensions: '%s'\n", dims_arg );
        printUsageAndExit( argv[0] );
      }
    } else {
      fprintf( stderr, "Unknown option '%s'\n", argv[i] );
      printUsageAndExit( argv[0] );
    }
  }

  create_context( &context, &output_buffer );
  create_material( context, &material );
  create_geometry( context, material );

  RT_CHECK_ERROR( rtContextValidate(context) );
  RT_CHECK_ERROR( rtContextCompile(context) );
  RT_CHECK_ERROR( rtContextLaunch2D(context,0,width,height) );

  /* Display image */
  if( strlen( outfile ) == 0 ) {
    RT_CHECK_ERROR( sutilDisplayBufferInGlutWindow( argv[0], output_buffer ) );
  } else {
    RT_CHECK_ERROR( sutilDisplayFilePPM( outfile, output_buffer ) );
  }

  RT_CHECK_ERROR( rtContextDestroy(context) );
  return 0;
}


void create_context( RTcontext* context, RTbuffer* output_buffer )
{
  /* Variable declarations */
  RTprogram raygen_program;
  RTprogram exception_program;
  RTprogram miss_program;

  RTvariable var_output_buffer;
  RTvariable var_scene_epsilon;
  RTvariable var_radiance_ray_type;

  RTvariable var_badcolor;
  RTvariable var_bgcolor;
  RTvariable var_eye;
  RTvariable var_U;
  RTvariable var_V;
  RTvariable var_W;
  RTvariable var_frame;

  float eye[3], lookat[3], up[3];
  float hfov, aspect_ratio; 
  float camera_u[3], camera_v[3], camera_w[3];

  RTbuffer   seed_buffer;
  RTvariable seed_buffer_var;
  unsigned int* seeds;
  void *temp = 0;
  unsigned int i;

  /* Context. */
  RT_CHECK_ERROR2( rtContextCreate( context ) );
  RT_CHECK_ERROR2( rtContextSetEntryPointCount( *context, 1 ) );
  RT_CHECK_ERROR2( rtContextSetRayTypeCount( *context, 2 ) );
  RT_CHECK_ERROR2( rtContextSetStackSize( *context, 320 ) );
  
  /* Output buffer. */
  RT_CHECK_ERROR2( rtBufferCreate( *context, RT_BUFFER_OUTPUT, output_buffer ) );
  RT_CHECK_ERROR2( rtBufferSetFormat( *output_buffer, RT_FORMAT_UNSIGNED_BYTE4 ) );
  RT_CHECK_ERROR2( rtBufferSetSize2D( *output_buffer, width, height ) );

  /* Ray generation program. */
  ptxPath( "pinhole_camera.cu", ptx_path );
  RT_CHECK_ERROR2( rtProgramCreateFromPTXFile( *context, ptx_path, "pinhole_camera", &raygen_program ) );
  RT_CHECK_ERROR2( rtContextSetRayGenerationProgram( *context, 0, raygen_program ) );

  /* Exception program. */
  RT_CHECK_ERROR2( rtProgramCreateFromPTXFile( *context, ptx_path, "exception", &exception_program ) );
  RT_CHECK_ERROR2( rtContextSetExceptionProgram( *context, 0, exception_program ) );

  /* Miss program. */
  ptxPath( "constantbg.cu", ptx_path );
  RT_CHECK_ERROR2( rtProgramCreateFromPTXFile( *context, ptx_path, "miss", &miss_program ) );
  RT_CHECK_ERROR2( rtContextSetMissProgram( *context, 0, miss_program ) );

  /* Variables. */
  RT_CHECK_ERROR2( rtContextDeclareVariable( *context, "output_buffer", &var_output_buffer ) );
  RT_CHECK_ERROR2( rtContextDeclareVariable( *context, "scene_epsilon", &var_scene_epsilon ) );
  RT_CHECK_ERROR2( rtContextDeclareVariable( *context, "radiance_ray_type", &var_radiance_ray_type ) );
  RT_CHECK_ERROR2( rtContextDeclareVariable( *context, "bad_color", &var_badcolor ) );
  RT_CHECK_ERROR2( rtContextDeclareVariable( *context, "bg_color", &var_bgcolor ) );
  RT_CHECK_ERROR2( rtContextDeclareVariable( *context, "frame", &var_frame ) );
  RT_CHECK_ERROR2( rtVariableSetObject( var_output_buffer, *output_buffer ) );
  RT_CHECK_ERROR2( rtVariableSet1f( var_scene_epsilon, 1e-3f ) );
  RT_CHECK_ERROR2( rtVariableSet1ui( var_radiance_ray_type, 0u ) );
  RT_CHECK_ERROR2( rtVariableSet1i( var_frame, 0u ) );
  RT_CHECK_ERROR2( rtVariableSet3f( var_badcolor, 1.0f, 1.0f, 0.0f ) );
  RT_CHECK_ERROR2( rtVariableSet3f( var_bgcolor, 0.462f, 0.725f, 0.0f ) );

  /* Camera variables. */
  RT_CHECK_ERROR2( rtContextDeclareVariable( *context, "eye",&var_eye ) );
  RT_CHECK_ERROR2( rtContextDeclareVariable( *context, "U",&var_U ) );
  RT_CHECK_ERROR2( rtContextDeclareVariable( *context, "V",&var_V ) );
  RT_CHECK_ERROR2( rtContextDeclareVariable( *context, "W",&var_W ) );

  eye[0]    = 3.0f;  eye[1]    = 2.0f;  eye[2]    = -3.0f;
  lookat[0] = 0.0f;  lookat[1] = 0.3f;  lookat[2] =  0.0f;
  up[0]     = 0.0f;  up[1]     = 1.0f;  up[2]     =  0.0f;
  hfov      = 75.0f;
  
  aspect_ratio = (float)width/(float)height;
  sutilCalculateCameraVariables( eye, lookat, up, hfov, aspect_ratio,
                                 camera_u, camera_v, camera_w );

  RT_CHECK_ERROR2( rtVariableSet3fv( var_eye, eye ) );
  RT_CHECK_ERROR2( rtVariableSet3fv( var_U, camera_u ) );
  RT_CHECK_ERROR2( rtVariableSet3fv( var_V, camera_v ) );
  RT_CHECK_ERROR2( rtVariableSet3fv( var_W, camera_w ) );

  /* Random seed buffer */
  RT_CHECK_ERROR2( rtBufferCreate( *context, RT_BUFFER_INPUT, &seed_buffer ) );
  RT_CHECK_ERROR2( rtBufferSetFormat( seed_buffer, RT_FORMAT_UNSIGNED_INT ) );
  RT_CHECK_ERROR2( rtBufferSetSize2D( seed_buffer, width, height ) );
  RT_CHECK_ERROR2( rtBufferMap( seed_buffer, &temp ) );
  seeds = (unsigned int*)temp;
  for( i = 0; i < width*height; ++i ) 
    seeds[i] = rand();
  RT_CHECK_ERROR2( rtBufferUnmap( seed_buffer ) );
  RT_CHECK_ERROR2( rtContextDeclareVariable( *context, "rnd_seeds",
                                             &seed_buffer_var) );
  RT_CHECK_ERROR2( rtVariableSetObject( seed_buffer_var, seed_buffer ) );

}


void create_material( RTcontext context, RTmaterial* material )
{
  RTvariable var_occlusion_distance;
  RTvariable var_sqrt_occlusion_samples;
  RTprogram  ch_radiance_program;
  RTprogram  ah_occlusion_program;

  /* Material. */
  RT_CHECK_ERROR( rtMaterialCreate(context,material) );
  ptxPath( "ambocc.cu", ptx_path );
  RT_CHECK_ERROR( rtProgramCreateFromPTXFile( context, ptx_path, "closest_hit_radiance", &ch_radiance_program ) );
  RT_CHECK_ERROR( rtProgramCreateFromPTXFile( context, ptx_path, "any_hit_occlusion", &ah_occlusion_program ) );
  RT_CHECK_ERROR( rtMaterialSetClosestHitProgram( *material, 0, ch_radiance_program ) );
  RT_CHECK_ERROR( rtMaterialSetAnyHitProgram( *material, 1, ah_occlusion_program ) );

  /* Variables. */
  RT_CHECK_ERROR( rtMaterialDeclareVariable( *material, "occlusion_distance", &var_occlusion_distance ) );
  RT_CHECK_ERROR( rtVariableSet1f( var_occlusion_distance, 100.0f ) );
  RT_CHECK_ERROR( rtMaterialDeclareVariable( *material, "sqrt_occlusion_samples", &var_sqrt_occlusion_samples ) );
  RT_CHECK_ERROR( rtVariableSet1i( var_sqrt_occlusion_samples, 10 ) );
}


void create_geometry( RTcontext context, RTmaterial material )
{
  RTgeometry sphere_geom;
  RTprogram  sphere_isect_program;
  RTprogram  sphere_bounds_program;
  RTvariable var_sphere;

  RTgeometry ground_geom;
  RTprogram  ground_isect_program;
  RTprogram  ground_bounds_program;
  RTvariable var_plane;
  RTvariable var_v1;
  RTvariable var_v2;
  RTvariable var_anchor;

  float v1[3], v2[3];
  float anchor[3];
  float normal[3];
  float inv_len2;
  float plane[4];

  RTgeometryinstance sphere_inst;
  RTgeometryinstance ground_inst;
  RTacceleration accel;
  RTgeometrygroup geometrygroup;
  RTvariable var_group;

  /* Sphere geometry. */
  RT_CHECK_ERROR( rtGeometryCreate( context,&sphere_geom ) );
  RT_CHECK_ERROR( rtGeometrySetPrimitiveCount( sphere_geom, 1 ) );
  ptxPath( "sphere.cu", ptx_path );
  RT_CHECK_ERROR( rtProgramCreateFromPTXFile( context, ptx_path, "intersect", &sphere_isect_program ) );
  RT_CHECK_ERROR( rtProgramCreateFromPTXFile( context, ptx_path, "bounds", &sphere_bounds_program) );
  RT_CHECK_ERROR( rtGeometrySetIntersectionProgram( sphere_geom, sphere_isect_program ) );
  RT_CHECK_ERROR( rtGeometrySetBoundingBoxProgram( sphere_geom, sphere_bounds_program ) );
  RT_CHECK_ERROR( rtGeometryDeclareVariable( sphere_geom, "sphere", &var_sphere ) );
  RT_CHECK_ERROR( rtVariableSet4f( var_sphere, 0.0f, 1.2f, 0.0f, 1.0f ) );

  /* Ground geometry. */
  RT_CHECK_ERROR( rtGeometryCreate( context, &ground_geom ) );
  RT_CHECK_ERROR( rtGeometrySetPrimitiveCount( ground_geom, 1 ) );
  ptxPath( "parallelogram.cu", ptx_path );
  RT_CHECK_ERROR( rtProgramCreateFromPTXFile( context, ptx_path, "intersect", &ground_isect_program ) );
  RT_CHECK_ERROR( rtProgramCreateFromPTXFile( context, ptx_path, "bounds", &ground_bounds_program ) );
  RT_CHECK_ERROR( rtGeometrySetIntersectionProgram( ground_geom,ground_isect_program ) );
  RT_CHECK_ERROR( rtGeometrySetBoundingBoxProgram( ground_geom,ground_bounds_program ) );
  RT_CHECK_ERROR( rtGeometryDeclareVariable( ground_geom, "plane", &var_plane ) );
  RT_CHECK_ERROR( rtGeometryDeclareVariable( ground_geom, "v1", &var_v1 ) );
  RT_CHECK_ERROR( rtGeometryDeclareVariable( ground_geom, "v2", &var_v2 ) );
  RT_CHECK_ERROR( rtGeometryDeclareVariable( ground_geom, "anchor", &var_anchor ) );

  anchor[0] = -30.0f;  anchor[1] =   0.0f;  anchor[2] =  20.0f;  
  v1[0]     =  40.0f;  v1[1]     =   0.0f;  v1[2]     =   0.0f;
  v2[0]     =   0.0f;  v2[1]     =   0.0f;  v2[2]     = -40.0f;
  cross( v1, v2, normal );
  normalize( normal );
  inv_len2 = 1.0f / dot( v1, v1 );
  v1[0] *= inv_len2; 
  v1[1] *= inv_len2; 
  v1[2] *= inv_len2; 

  inv_len2 = 1.0f / dot( v2, v2 );
  v2[0] *= inv_len2; 
  v2[1] *= inv_len2; 
  v2[2] *= inv_len2; 

  plane[0] = normal[0];
  plane[1] = normal[1];
  plane[2] = normal[2];
  plane[3] = dot( normal, anchor );
  
  RT_CHECK_ERROR( rtVariableSet4fv( var_plane, plane ) );
  RT_CHECK_ERROR( rtVariableSet3fv( var_v1, v1 ) );
  RT_CHECK_ERROR( rtVariableSet3fv( var_v2, v2 ) );
  RT_CHECK_ERROR( rtVariableSet3fv( var_anchor, anchor ) );
  
  /* Sphere instance. */
  RT_CHECK_ERROR( rtGeometryInstanceCreate( context, &sphere_inst ) );
  RT_CHECK_ERROR( rtGeometryInstanceSetGeometry( sphere_inst,sphere_geom ) );
  RT_CHECK_ERROR( rtGeometryInstanceSetMaterialCount( sphere_inst, 1 ) );
  RT_CHECK_ERROR( rtGeometryInstanceSetMaterial( sphere_inst, 0, material ) );

  /* Ground instance. */
  RT_CHECK_ERROR( rtGeometryInstanceCreate( context, &ground_inst ) );
  RT_CHECK_ERROR( rtGeometryInstanceSetGeometry( ground_inst, ground_geom ) );
  RT_CHECK_ERROR( rtGeometryInstanceSetMaterialCount( ground_inst, 1 ) );
  RT_CHECK_ERROR( rtGeometryInstanceSetMaterial( ground_inst, 0 ,material ) );

  /* Accelerations. */
  RT_CHECK_ERROR( rtAccelerationCreate( context, &accel ) );
  RT_CHECK_ERROR( rtAccelerationSetBuilder( accel, "NoAccel" ) );
  RT_CHECK_ERROR( rtAccelerationSetTraverser( accel, "NoAccel" ) );

  /* GeometryGroup. */
  RT_CHECK_ERROR( rtGeometryGroupCreate( context, &geometrygroup ) );
  RT_CHECK_ERROR( rtGeometryGroupSetChildCount( geometrygroup, 2 ) );
  RT_CHECK_ERROR( rtGeometryGroupSetChild( geometrygroup, 0, sphere_inst ) );
  RT_CHECK_ERROR( rtGeometryGroupSetChild( geometrygroup, 1, ground_inst ) );
  RT_CHECK_ERROR( rtGeometryGroupSetAcceleration( geometrygroup, accel ) );

  /* Attach to context */
  RT_CHECK_ERROR( rtContextDeclareVariable( context, "top_object", &var_group ) );
  RT_CHECK_ERROR( rtVariableSetObject( var_group, geometrygroup ) );
}


void ptxPath( const char* base, char* path )
{
  sprintf( path, "%s/ambocc_generated_%s.ptx", sutilSamplesPtxDir(), base );
}


void cross( const float a[3], const float b[3], float result[3] )
{
  result[0] = a[1]*b[2] - a[2]*b[1];
  result[1] = a[2]*b[0] - a[0]*b[2];
  result[2] = a[0]*b[1] - a[1]*b[0];
}


float dot( const float a[3], const float b[3] )
{
  return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}


void normalize( float a[3] )
{
  float inv_len = 1.0f / sqrtf( dot(a, a) );
  a[0] *= inv_len;
  a[1] *= inv_len;
  a[2] *= inv_len;
}


void printUsageAndExit( const char* argv0 )
{
  fprintf( stderr, "Usage  : %s [options]\n", argv0 );
  fprintf( stderr, " options:\n" );
  fprintf( stderr, "  -h  | --help                               Print this usage message\n" );
  fprintf( stderr, "  -f  | --file <filename>                    Specify file for image output\n" );
  fprintf( stderr, "      | --dim=<width>x<height>               Set image dimensions\n" );
  exit(1);
}
