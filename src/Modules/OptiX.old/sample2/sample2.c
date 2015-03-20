
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
 *  sample2.cpp -- Renders a group of boxes with a Phong material and a constant
 *                 background.
 */


#include <optix.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sutil.h>
#include "commonStructs.h"


char path_to_ptx[512];


#define NUM_BOXES 6
unsigned int width  = 512u;
unsigned int height = 384u;


typedef struct struct_BoxExtent{
    float min[3];
    float max[3];
} BoxExtent;


void createContext( RTcontext* context, RTbuffer* buffer );
void createMaterial( RTcontext context, RTmaterial* material );
void createGeometry( RTcontext context, RTgeometry* box );
void createInstances( RTcontext context, RTgeometry box, RTmaterial material );
void printUsageAndExit( const char* argv0 );


int main(int argc, char* argv[])
{
    /* Primary RTAPI objects */
    RTcontext           context;
    RTbuffer            output_buffer_obj;
    RTgeometry          box;
    RTmaterial          material;

    /* Parameters */
    char outfile[512];
    int i;
    int use_glut = 1;

    outfile[0] = '\0';

    /* If "--file" is specified, don't do any GL stuff */
    for( i = 1; i < argc; ++i ) {
      if( strcmp( argv[i], "--file" ) == 0 || strcmp( argv[i], "-f" ) == 0 )
        use_glut = 0;
    }

    /* Process command line args */
    if( use_glut )
      RT_CHECK_ERROR_NO_CONTEXT( sutilInitGlut( &argc, argv ) );
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

    /* Setup state */
    createContext( &context, &output_buffer_obj );
    createGeometry( context, &box );
    createMaterial( context, &material);
    createInstances( context, box, material );

    /* Run */
    RT_CHECK_ERROR( rtContextValidate( context ) );
    RT_CHECK_ERROR( rtContextCompile( context ) );
    RT_CHECK_ERROR( rtContextLaunch2D( context, 0, width, height ) );

    /* Display image */
    if( strlen( outfile ) == 0 ) {
      RT_CHECK_ERROR( sutilDisplayBufferInGlutWindow( argv[0], output_buffer_obj ) );
    } else {
      RT_CHECK_ERROR( sutilDisplayFilePPM( outfile, output_buffer_obj ) );
    }

    /* Clean up */
    RT_CHECK_ERROR( rtContextDestroy( context ) );
    return( 0 );
}

void createContext( RTcontext* context, RTbuffer* output_buffer_obj )
{
    RTprogram  ray_gen_program;
    RTprogram  miss_program;
    RTbuffer   light_buffer_obj;
    RTvariable output_buffer;
    RTvariable light_buffer;
    RTvariable radiance_ray_type;
    RTvariable shadow_ray_type;
    RTvariable epsilon;
    RTvariable max_depth;

    BasicLight light;
    void* light_buffer_data;

    /* variables for ray gen program */
    RTvariable eye;
    RTvariable U;
    RTvariable V;
    RTvariable W;

    /* variables for the miss program */
    RTvariable color;

    /* Setup context */
    RT_CHECK_ERROR2( rtContextCreate( context ) );
    RT_CHECK_ERROR2( rtContextSetRayTypeCount( *context, 2 ) ); /* shadow and radiance */
    RT_CHECK_ERROR2( rtContextSetEntryPointCount( *context, 1 ) );

    RT_CHECK_ERROR2( rtContextDeclareVariable( *context, "output_buffer", &output_buffer ) );
    RT_CHECK_ERROR2( rtContextDeclareVariable( *context, "lights", &light_buffer ) );
    RT_CHECK_ERROR2( rtContextDeclareVariable( *context, "max_depth", &max_depth ) );
    RT_CHECK_ERROR2( rtContextDeclareVariable( *context, "radiance_ray_type", &radiance_ray_type ) );
    RT_CHECK_ERROR2( rtContextDeclareVariable( *context, "shadow_ray_type", &shadow_ray_type ) );
    RT_CHECK_ERROR2( rtContextDeclareVariable( *context, "scene_epsilon", &epsilon ) );

    RT_CHECK_ERROR2( rtVariableSet1i( max_depth, 10u ) );
    RT_CHECK_ERROR2( rtVariableSet1ui( radiance_ray_type, 0u ) );
    RT_CHECK_ERROR2( rtVariableSet1ui( shadow_ray_type, 1u ) );
    RT_CHECK_ERROR2( rtVariableSet1f( epsilon, 1.e-4f ) );

    /* Render result buffer */
    RT_CHECK_ERROR2( rtBufferCreate( *context, RT_BUFFER_OUTPUT, output_buffer_obj ) );
    RT_CHECK_ERROR2( rtBufferSetFormat( *output_buffer_obj, RT_FORMAT_UNSIGNED_BYTE4 ) );
    RT_CHECK_ERROR2( rtBufferSetSize2D( *output_buffer_obj, width, height ) );
    RT_CHECK_ERROR2( rtVariableSetObject( output_buffer, *output_buffer_obj ) );

    /* Lights buffer */
    light.color.x = 0.9f;
    light.color.y = 0.9f;
    light.color.z = 0.9f;
    light.pos.x   = 0.0f;
    light.pos.y   = 20.0f;
    light.pos.z   = 20.0f;
    light.casts_shadow = 1;
    light.padding      = 0u;

    RT_CHECK_ERROR2( rtBufferCreate( *context, RT_BUFFER_INPUT, &light_buffer_obj ) );
    RT_CHECK_ERROR2( rtBufferSetFormat( light_buffer_obj, RT_FORMAT_USER ) );
    RT_CHECK_ERROR2( rtBufferSetElementSize( light_buffer_obj, sizeof(BasicLight) ) );
    RT_CHECK_ERROR2( rtBufferSetSize1D( light_buffer_obj, 1 ) );
    RT_CHECK_ERROR2( rtBufferMap( light_buffer_obj, &light_buffer_data ) );
    ((BasicLight*)light_buffer_data)[0] = light;
    RT_CHECK_ERROR2( rtBufferUnmap( light_buffer_obj ) );
    RT_CHECK_ERROR2( rtVariableSetObject( light_buffer, light_buffer_obj ) );

    /* Ray generation program */
    sprintf( path_to_ptx, "%s/%s", sutilSamplesPtxDir(), "sample2_generated_pinhole_camera.cu.ptx" );
    RT_CHECK_ERROR2( rtProgramCreateFromPTXFile( *context, path_to_ptx, "pinhole_camera", &ray_gen_program ) );
    RT_CHECK_ERROR2( rtProgramDeclareVariable( ray_gen_program, "eye", &eye ) );
    RT_CHECK_ERROR2( rtProgramDeclareVariable( ray_gen_program, "U", &U ) );
    RT_CHECK_ERROR2( rtProgramDeclareVariable( ray_gen_program, "V", &V ) );
    RT_CHECK_ERROR2( rtProgramDeclareVariable( ray_gen_program, "W", &W ) );
    RT_CHECK_ERROR2( rtVariableSet3f( eye, 0.0f, 0.0f, 5.0f ) );
    RT_CHECK_ERROR2( rtVariableSet3f( U, 1.0f, 0.0f, 0.0f ) );
    RT_CHECK_ERROR2( rtVariableSet3f( V, 0.0f, 1.0f, 0.0f ) );
    RT_CHECK_ERROR2( rtVariableSet3f( W, 0.0f, 0.0f, -1.0f ) );
    RT_CHECK_ERROR2( rtContextSetRayGenerationProgram( *context, 0, ray_gen_program ) );

    /* Miss program */
    sprintf( path_to_ptx, "%s/%s", sutilSamplesPtxDir(), "sample2_generated_constantbg.cu.ptx" );
    RT_CHECK_ERROR2( rtProgramCreateFromPTXFile( *context, path_to_ptx, "miss", &miss_program ) );
    RT_CHECK_ERROR2( rtProgramDeclareVariable( miss_program, "bg_color" , &color) );
    RT_CHECK_ERROR2( rtVariableSet3f( color, .3f, 0.1f, 0.2f ) );
    RT_CHECK_ERROR2( rtContextSetMissProgram( *context, 0, miss_program ) );
}

void createGeometry( RTcontext context, RTgeometry* box )
{
    RTprogram  box_intersection_program;
    RTprogram  box_bounding_box_program;
    RTvariable box_min_var;
    RTvariable box_max_var;

    float     box_min[3];
    float     box_max[3];

    RT_CHECK_ERROR( rtGeometryCreate( context, box ) );
    RT_CHECK_ERROR( rtGeometrySetPrimitiveCount( *box, 1u ) );

    sprintf( path_to_ptx, "%s/%s", sutilSamplesPtxDir(), "sample2_generated_box.cu.ptx" );
    RT_CHECK_ERROR( rtProgramCreateFromPTXFile( context, path_to_ptx, "box_bounds", &box_bounding_box_program ) );
    RT_CHECK_ERROR( rtGeometrySetBoundingBoxProgram( *box, box_bounding_box_program ) );
    RT_CHECK_ERROR( rtProgramCreateFromPTXFile( context, path_to_ptx, "box_intersect", &box_intersection_program ) );
    RT_CHECK_ERROR( rtGeometrySetIntersectionProgram( *box, box_intersection_program ) );


    box_min[0] = box_min[1] = box_min[2] = -0.5f;
    box_max[0] = box_max[1] = box_max[2] =  0.5f;

    RT_CHECK_ERROR( rtGeometryDeclareVariable( *box, "boxmin", &box_min_var ) );
    RT_CHECK_ERROR( rtGeometryDeclareVariable( *box, "boxmax", &box_max_var ) );
    RT_CHECK_ERROR( rtVariableSet3fv( box_min_var, box_min ) );
    RT_CHECK_ERROR( rtVariableSet3fv( box_max_var, box_max ) );
}

void createMaterial( RTcontext context, RTmaterial* material )
{
    RTprogram closest_hit_program;
    RTprogram any_hit_program;

    /* Create our hit programs to be shared among all materials */
    sprintf( path_to_ptx, "%s/%s", sutilSamplesPtxDir(), "sample2_generated_phong.cu.ptx" );
    RT_CHECK_ERROR( rtProgramCreateFromPTXFile( context, path_to_ptx, "closest_hit_radiance", &closest_hit_program ) );
    RT_CHECK_ERROR( rtProgramCreateFromPTXFile( context, path_to_ptx, "any_hit_shadow", &any_hit_program ) );

    RT_CHECK_ERROR( rtMaterialCreate( context, material ) );

    /* Note that we are leaving anyHitProgram[0] and closestHitProgram[1] as NULL.
     * This is because our radiance rays only need closest_hit and shadow rays only
     * need any_hit */
    RT_CHECK_ERROR( rtMaterialSetClosestHitProgram( *material, 0, closest_hit_program ) );
    RT_CHECK_ERROR( rtMaterialSetAnyHitProgram( *material, 1, any_hit_program ) );
}

void createInstances( RTcontext context, RTgeometry box, RTmaterial material )
{
    RTtransform     transforms[NUM_BOXES];
    RTgroup         top_level_group;
    RTvariable      top_object;
    RTvariable      top_shadower;
    RTacceleration  top_level_acceleration;
    
    int i;

    float m[16];
    m[ 0] = 1.0f;  m[ 1] = 0.0f;  m[ 2] = 0.0f;  m[ 3] = 0.0f;
    m[ 4] = 0.0f;  m[ 5] = 1.0f;  m[ 6] = 0.0f;  m[ 7] = 0.0f;
    m[ 8] = 0.0f;  m[ 9] = 0.0f;  m[10] = 1.0f;  m[11] = 0.0f;
    m[12] = 0.0f;  m[13] = 0.0f;  m[14] = 0.0f;  m[15] = 1.0f;

    for ( i = 0; i < NUM_BOXES; ++i )
    {
        float kd_slider;
        RTgeometrygroup geometrygroup;
        RTgeometryinstance instance;
        RTacceleration acceleration;
        RTvariable kd;
        RTvariable ks;
        RTvariable ka;
        RTvariable reflectivity;
        RTvariable expv;
        RTvariable ambient;

        /* Create this geometry instance */
        RT_CHECK_ERROR( rtGeometryInstanceCreate( context, &instance ) );
        RT_CHECK_ERROR( rtGeometryInstanceSetGeometry( instance, box ) );
        RT_CHECK_ERROR( rtGeometryInstanceSetMaterialCount( instance, 1 ) );
        RT_CHECK_ERROR( rtGeometryInstanceSetMaterial( instance, 0, material ) );

        /* Set variables to be consumed by material for this geometry instance */
        kd_slider = (float)i / (float)(NUM_BOXES-1);
        RT_CHECK_ERROR( rtGeometryInstanceDeclareVariable( instance, "Kd", &kd ) );
        RT_CHECK_ERROR( rtGeometryInstanceDeclareVariable( instance, "Ks", &ks ) );
        RT_CHECK_ERROR( rtGeometryInstanceDeclareVariable( instance, "Ka", &ka ) );
        RT_CHECK_ERROR( rtGeometryInstanceDeclareVariable( instance, "phong_exp", &expv ) );
        RT_CHECK_ERROR( rtGeometryInstanceDeclareVariable( instance, "reflectivity", &reflectivity ) );
        RT_CHECK_ERROR( rtGeometryInstanceDeclareVariable( instance, "ambient_light_color", &ambient) );
        RT_CHECK_ERROR( rtVariableSet3f( kd, kd_slider, 0.0f, 1.0f-kd_slider ) );
        RT_CHECK_ERROR( rtVariableSet3f( ks, 0.5f, 0.5f, 0.5f ) );
        RT_CHECK_ERROR( rtVariableSet3f( ka, 0.8f, 0.8f, 0.8f ) );
        RT_CHECK_ERROR( rtVariableSet3f( reflectivity, 0.8f, 0.8f, 0.8f ) );
        RT_CHECK_ERROR( rtVariableSet1f( expv, 10.0f ) );
        RT_CHECK_ERROR( rtVariableSet3f( ambient, 0.2f, 0.2f, 0.2f ) );

        /* create group to hold instance transform */
        RT_CHECK_ERROR( rtGeometryGroupCreate( context, &geometrygroup ) );
        RT_CHECK_ERROR( rtGeometryGroupSetChildCount( geometrygroup, 1 ) );
        RT_CHECK_ERROR( rtGeometryGroupSetChild( geometrygroup, 0, instance ) );

        /* create acceleration object for group and specify some build hints*/
        RT_CHECK_ERROR( rtAccelerationCreate(context,&acceleration) );
        RT_CHECK_ERROR( rtAccelerationSetBuilder(acceleration,"NoAccel") );
        RT_CHECK_ERROR( rtAccelerationSetTraverser(acceleration,"NoAccel") );
        RT_CHECK_ERROR( rtGeometryGroupSetAcceleration( geometrygroup, acceleration) );

        /* mark acceleration as dirty */
        RT_CHECK_ERROR( rtAccelerationMarkDirty( acceleration ) );

        /* add a transform node */
        RT_CHECK_ERROR( rtTransformCreate( context, &transforms[i] ) );
        RT_CHECK_ERROR( rtTransformSetChild( transforms[i], geometrygroup ) );
        m[3] = i*1.5f - (NUM_BOXES-1)*0.75f;
        RT_CHECK_ERROR( rtTransformSetMatrix( transforms[i], 0, m, 0 ) );
    }

    /* Place these geometrygroups as children of the top level object */
    RT_CHECK_ERROR( rtGroupCreate( context, &top_level_group ) );
    RT_CHECK_ERROR( rtGroupSetChildCount( top_level_group, NUM_BOXES ) );
    for ( i = 0; i < NUM_BOXES; ++i ) {
      RT_CHECK_ERROR( rtGroupSetChild( top_level_group, i, transforms[i] ) );
    }
    RT_CHECK_ERROR( rtContextDeclareVariable( context, "top_object", &top_object ) );
    RT_CHECK_ERROR( rtVariableSetObject( top_object, top_level_group ) );
    RT_CHECK_ERROR( rtContextDeclareVariable( context, "top_shadower", &top_shadower ) );
    RT_CHECK_ERROR( rtVariableSetObject( top_shadower, top_level_group ) );

    RT_CHECK_ERROR( rtAccelerationCreate( context, &top_level_acceleration ) );
    RT_CHECK_ERROR( rtAccelerationSetBuilder(top_level_acceleration,"NoAccel") );
    RT_CHECK_ERROR( rtAccelerationSetTraverser(top_level_acceleration,"NoAccel") );
    RT_CHECK_ERROR( rtGroupSetAcceleration( top_level_group, top_level_acceleration) );

    /* mark acceleration as dirty */
    RT_CHECK_ERROR( rtAccelerationMarkDirty( top_level_acceleration ) );
}


void printUsageAndExit( const char* argv0 )
{
  fprintf( stderr, "Usage  : %s [options]\n", argv0 );
  fprintf( stderr, "Options: --file | -f <filename>      Specify file for image output\n" );
  fprintf( stderr, "Options: --help | -h                 Print this usage message\n" );
  fprintf( stderr, "         --dim=<width>x<height>      Set image dimensions; defaults to 512x384\n" );
  exit(1);
}
