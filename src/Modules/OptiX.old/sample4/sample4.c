
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
 *  sample4.cpp -- Draws a texture to the screen, where the texture is created
 *                 by the RTAPI.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <optix.h>
#include <sutil.h>


void printUsageAndExit( const char* argv0 );


int main(int argc, char** argv)
{
  RTcontext context;
  RTbuffer  tex_buffer;
  RTbuffer  result_buffer;
  RTprogram draw_tex;
  RTtexturesampler tex_sampler;
  RTvariable tex_sampler_var;
  RTvariable result_buffer_var;
  void* tex_data_ptr;
  unsigned char* tex_data;
  int k;
  unsigned int i,j;

  unsigned int tex_width  = 64;
  unsigned int tex_height = 64;

  unsigned int trace_width  = 512;
  unsigned int trace_height = 384;
  
  char path_to_ptx[512];
  char outfile[512];

  outfile[0] = '\0';

  /* Process command line args */
  RT_CHECK_ERROR_NO_CONTEXT( sutilInitGlut( &argc, argv ) );
  for( k = 1; k < argc; ++k ) {
    if( strcmp( argv[k], "--help" ) == 0 || strcmp( argv[k], "-h" ) == 0 ) {
      printUsageAndExit( argv[0] );
    } else if( strcmp( argv[k], "--file" ) == 0 || strcmp( argv[k], "-f" ) == 0 ) {
      if( k < argc-1 ) {
        strcpy( outfile, argv[++k] );
      } else {
        printUsageAndExit( argv[0] );
      }
    } else if ( strncmp( argv[k], "--dim=", 6 ) == 0 ) {
      const char *dims_arg = &argv[k][6];
      if ( sutilParseImageDimensions( dims_arg, &trace_width, &trace_height ) != RT_SUCCESS ) {
        fprintf( stderr, "Invalid window dimensions: '%s'\n", dims_arg );
        printUsageAndExit( argv[0] );
      }
    } else {
      fprintf( stderr, "Unknown option '%s'\n", argv[k] );
      printUsageAndExit( argv[0] );
    }
  }

  /* Create the context */
  RT_CHECK_ERROR( rtContextCreate( &context ) );

  /* Create the buffer that represents the texture data */
  RT_CHECK_ERROR( rtBufferCreate( context, RT_BUFFER_INPUT, &tex_buffer ) );
  RT_CHECK_ERROR( rtBufferSetFormat( tex_buffer, RT_FORMAT_UNSIGNED_BYTE4 ) );
  RT_CHECK_ERROR( rtBufferSetSize2D( tex_buffer, tex_width, tex_height ) );
  RT_CHECK_ERROR( rtBufferMap( tex_buffer, &tex_data_ptr ) );
  tex_data = (unsigned char*)tex_data_ptr;
  for(j = 0; j < tex_height; ++j) {
    for(i = 0; i < tex_width; ++i) {
      *tex_data++ = (unsigned char)((i+j)/((float)(tex_width+tex_height))*255); /* R */
      *tex_data++ = (unsigned char)(i/((float)tex_width)*255);                  /* G */
      *tex_data++ = (unsigned char)(j/((float)tex_height)*255);                 /* B */
      *tex_data++ = 255;                                                        /* A */
    }
  }
  RT_CHECK_ERROR( rtBufferUnmap( tex_buffer ) );

  /* Create the texture sampler */
  RT_CHECK_ERROR( rtTextureSamplerCreate( context, &tex_sampler ) );
  RT_CHECK_ERROR( rtTextureSamplerSetWrapMode( tex_sampler, 0, RT_WRAP_CLAMP_TO_EDGE ) );
  RT_CHECK_ERROR( rtTextureSamplerSetWrapMode( tex_sampler, 1, RT_WRAP_CLAMP_TO_EDGE ) );
  RT_CHECK_ERROR( rtTextureSamplerSetFilteringModes( tex_sampler, RT_FILTER_LINEAR, RT_FILTER_LINEAR, RT_FILTER_NONE ) );
  RT_CHECK_ERROR( rtTextureSamplerSetIndexingMode( tex_sampler, RT_TEXTURE_INDEX_NORMALIZED_COORDINATES ) );
  RT_CHECK_ERROR( rtTextureSamplerSetReadMode( tex_sampler, RT_TEXTURE_READ_NORMALIZED_FLOAT ) );
  RT_CHECK_ERROR( rtTextureSamplerSetMaxAnisotropy( tex_sampler, 1.f ) );
  RT_CHECK_ERROR( rtTextureSamplerSetMipLevelCount( tex_sampler, 1 ) );
  RT_CHECK_ERROR( rtTextureSamplerSetArraySize( tex_sampler, 1 ) );
  RT_CHECK_ERROR( rtTextureSamplerSetBuffer( tex_sampler, 0, 0, tex_buffer ) );
  RT_CHECK_ERROR( rtContextDeclareVariable( context, "input_texture" , &tex_sampler_var) );
  RT_CHECK_ERROR( rtVariableSetObject( tex_sampler_var, tex_sampler ) );

  /* Create the output buffer */
  RT_CHECK_ERROR( rtBufferCreate( context, RT_BUFFER_OUTPUT, &result_buffer ) );
  RT_CHECK_ERROR( rtBufferSetFormat( result_buffer, RT_FORMAT_FLOAT4 ) );
  RT_CHECK_ERROR( rtBufferSetSize2D( result_buffer, trace_width, trace_height ) );
  RT_CHECK_ERROR( rtContextDeclareVariable( context, "result_buffer" , &result_buffer_var) );
  RT_CHECK_ERROR( rtVariableSetObject( result_buffer_var, result_buffer ) );
  
  /* Create ray generation program */
  sprintf( path_to_ptx, "%s/%s", sutilSamplesPtxDir(), "sample4_generated_draw_texture.cu.ptx" );
  RT_CHECK_ERROR( rtProgramCreateFromPTXFile( context, path_to_ptx, "draw_texture", &draw_tex ) );

  /* Setup context programs */
  RT_CHECK_ERROR( rtContextSetEntryPointCount( context, 1 ) );
  RT_CHECK_ERROR( rtContextSetRayTypeCount( context, 1 ) );
  RT_CHECK_ERROR( rtContextSetRayGenerationProgram( context, 0, draw_tex ) );

  /* Trace */
  RT_CHECK_ERROR( rtContextValidate( context ) );
  RT_CHECK_ERROR( rtContextCompile( context ) );
  RT_CHECK_ERROR( rtContextLaunch2D( context, 0, trace_width, trace_height ) );

  /* Display image */
  if( strlen( outfile ) == 0 ) {
    RT_CHECK_ERROR( sutilDisplayBufferInGlutWindow( argv[0], result_buffer ) );
  } else {
    RT_CHECK_ERROR( sutilDisplayFilePPM( outfile, result_buffer ) );
  }

  /* Cleanup */
  RT_CHECK_ERROR( rtContextDestroy( context ) );

  return( 0 );
}


void printUsageAndExit( const char* argv0 )
{
  fprintf( stderr, "Usage  : %s [options]\n", argv0 );
  fprintf( stderr, "Options: --help | -h             Print this usage message\n" );
  fprintf( stderr, "Options: --file | -f <filename>      Specify file for image output\n" );
  fprintf( stderr, "         --dim=<width>x<height>  Set image dimensions; defaults to 512x384\n" );
  exit(1);
}
