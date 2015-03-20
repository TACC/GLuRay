
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
 * sample1.cpp -- Renders a solid green image.
 *
 * A filename can be given on the command line to write the results to file. 
 */

#include <optix.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sutil.h>


void printUsageAndExit( const char* argv0 );


int main(int argc, char* argv[])
{
    /* Primary RTAPI objects */
    RTcontext context;
    RTprogram ray_gen_program;
    RTbuffer  buffer;

    /* Parameters */
    RTvariable result_buffer;
    RTvariable draw_color;

    char path_to_ptx[512];
    char outfile[512];

    unsigned int width  = 512u;
    unsigned int height = 384u;
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

    /* Create our objects and set state */
    RT_CHECK_ERROR( rtContextCreate( &context ) );
    RT_CHECK_ERROR( rtContextSetRayTypeCount( context, 1 ) );
    RT_CHECK_ERROR( rtContextSetEntryPointCount( context, 1 ) );

    RT_CHECK_ERROR( rtBufferCreate( context, RT_BUFFER_OUTPUT, &buffer ) );
    RT_CHECK_ERROR( rtBufferSetFormat( buffer, RT_FORMAT_FLOAT4 ) );
    RT_CHECK_ERROR( rtBufferSetSize2D( buffer, width, height ) );
    RT_CHECK_ERROR( rtContextDeclareVariable( context, "result_buffer", &result_buffer ) );
    RT_CHECK_ERROR( rtVariableSetObject( result_buffer, buffer ) );

    sprintf( path_to_ptx, "%s/%s", sutilSamplesPtxDir(), "sample1_generated_draw_color.cu.ptx" );
    RT_CHECK_ERROR( rtProgramCreateFromPTXFile( context, path_to_ptx, "draw_solid_color", &ray_gen_program ) );
    RT_CHECK_ERROR( rtProgramDeclareVariable( ray_gen_program, "draw_color", &draw_color ) );
    RT_CHECK_ERROR( rtVariableSet3f( draw_color, 0.462f, 0.725f, 0.0f ) );
    RT_CHECK_ERROR( rtContextSetRayGenerationProgram( context, 0, ray_gen_program ) );

    /* Run */
    RT_CHECK_ERROR( rtContextValidate( context ) );
    RT_CHECK_ERROR( rtContextCompile( context ) );
    RT_CHECK_ERROR( rtContextLaunch2D( context, 0 /* entry point */, width, height ) );

    /* Display image */
    if( strlen( outfile ) == 0 ) {
      RT_CHECK_ERROR( sutilDisplayBufferInGlutWindow( argv[0], buffer ) );
    } else {
      RT_CHECK_ERROR( sutilDisplayFilePPM( outfile, buffer ) );
    }

    /* Clean up */
    RT_CHECK_ERROR( rtBufferDestroy( buffer ) );
    RT_CHECK_ERROR( rtProgramDestroy( ray_gen_program ) );
    RT_CHECK_ERROR( rtContextDestroy( context ) );

    return( 0 );
}


void printUsageAndExit( const char* argv0 )
{
  fprintf( stderr, "Usage  : %s [options]\n", argv0 );
  fprintf( stderr, "Options: --file | -f <filename>      Specify file for image output\n" );
  fprintf( stderr, "         --help | -h                 Print this usage message\n" );
  fprintf( stderr, "         --dim=<width>x<height>      Set image dimensions; defaults to 512x384\n" );
  exit(1);
}


