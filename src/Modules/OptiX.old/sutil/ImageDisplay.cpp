
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

#include <ImageDisplay.h>
#include <fstream>
#include <vector>

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <sutil.h>

#ifdef GLUT_FOUND

#if defined(__APPLE__)
#  include <GLUT/glut.h>
#else
#  include <GL/glew.h>
#  if defined(_WIN32)
#    include <GL/wglew.h>
#  endif
#  include <GL/glut.h>
#endif

#endif // GLUT_FOUND

namespace {
  RTcontext g_context = NULL;
  bool g_glut_initialized = false;
}

static RTresult
checkBuffer(RTbuffer buffer)
{
  // Check to see if the buffer is two dimensional
  unsigned int dimensionality;
  RTresult result;
  result = rtBufferGetDimensionality(buffer, &dimensionality);
  if (result != RT_SUCCESS) return result;
  if (2 != dimensionality) {
    fprintf(stderr, "Dimensionality of the buffer is %u instead of 2\n", dimensionality);
    return RT_ERROR_INVALID_VALUE;
  }
  // Check to see if the buffer is of type float{1,3,4} or uchar4
  RTformat format;
  result = rtBufferGetFormat(buffer, &format);
  if (result != RT_SUCCESS) return result;
  if (RT_FORMAT_FLOAT != format && RT_FORMAT_FLOAT4 != format && RT_FORMAT_FLOAT3 != format && RT_FORMAT_UNSIGNED_BYTE4 != format) {
    fprintf(stderr, "Buffer's format isn't float, float3, float4, or uchar4\n");
    return RT_ERROR_INVALID_VALUE;
  }

  return RT_SUCCESS;
}

static RTresult SavePPM(const unsigned char *Pix, const char *fname, int wid, int hgt, int chan)
{
  if(Pix==NULL || chan < 1 || wid < 1 || hgt < 1) {
    fprintf(stderr, "Image is not defined. Not saving.\n");
    return RT_ERROR_UNKNOWN;
  }

  if(chan < 1 || chan > 4) {
    fprintf(stderr, "Can't save a X channel image as a PPM.\n");
    return RT_ERROR_UNKNOWN;
  }

  ofstream OutFile(fname, ios::out | ios::binary);
  if(!OutFile.is_open()) {
    fprintf(stderr, "Could not open file for SavePPM\n");
    return RT_ERROR_UNKNOWN;
  }

  bool is_float = false;
  OutFile << 'P';
  OutFile << ((chan==1 ? (is_float?'Z':'5') : (chan==3 ? (is_float?'7':'6') : '8'))) << endl;
  OutFile << wid << " " << hgt << endl << 255 << endl;

  OutFile.write(reinterpret_cast<char*>(const_cast<unsigned char*>( Pix )), wid * hgt * chan * (is_float ? 4 : 1));

  OutFile.close();

  return RT_SUCCESS;
}

extern "C"
RTresult
displayFilePPM(const char* filename, RTbuffer buffer)
{
  RTresult result;
  GLsizei width, height;
  RTsize buffer_width, buffer_height;

  result = checkBuffer(buffer);
  if (result != RT_SUCCESS) {
    fprintf(stderr, "Buffer isn't the right format. Didn't pass.\n");
    return result;
  }

  GLvoid* imageData;
  result = rtBufferMap(buffer, &imageData);
  if (result != RT_SUCCESS) {
    // Get error from context
    RTcontext context;
    const char* error;
    rtBufferGetContext(buffer, &context);
    rtContextGetErrorString(context, result, &error);
    fprintf(stderr, "Error mapping image buffer: %s\n", error);
    exit(2);
  }
  if (0 == imageData) {
    fprintf(stderr, "data in buffer is null.\n");
    exit(2);
  }
  result = rtBufferGetSize2D(buffer, &buffer_width, &buffer_height);
  if (result != RT_SUCCESS) {
    // Get error from context
    RTcontext context;
    const char* error;
    rtBufferGetContext(buffer, &context);
    rtContextGetErrorString(context, result, &error);
    fprintf(stderr, "Error getting dimensions of buffer: %s\n", error);
    exit(2);
  }
  width  = static_cast<GLsizei>(buffer_width);
  height = static_cast<GLsizei>(buffer_height);

  std::vector<unsigned char> pix(width * height * 3);
  RTformat buffer_format;

  result = rtBufferGetFormat(buffer, &buffer_format);

  switch(buffer_format) {
    case RT_FORMAT_UNSIGNED_BYTE4:
      // Data is BGRA and upside down, so we need to swizzle to RGB
      for(int j = height-1; j >= 0; --j) {
        unsigned char *dst = &pix[0] + (3*width*(height-1-j));
        unsigned char *src = ((unsigned char*)imageData) + (4*width*j);
        for(int i = 0; i < width; i++) {
          *dst++ = *(src + 2);
          *dst++ = *(src + 1);
          *dst++ = *(src + 0);
          src += 4;
        }
      }
      break;

    case RT_FORMAT_FLOAT:
      // This buffer is upside down
      for(int j = height-1; j >= 0; --j) {
        unsigned char *dst = &pix[0] + width*(height-1-j);
        float* src = ((float*)imageData) + (3*width*j);
        for(int i = 0; i < width; i++) {
          int P = static_cast<int>((*src++) * 255.0f);
          unsigned int Clamped = P < 0 ? 0 : P > 0xff ? 0xff : P;

          // write the pixel to all 3 channels
          *dst++ = static_cast<unsigned char>(Clamped);
          *dst++ = static_cast<unsigned char>(Clamped);
          *dst++ = static_cast<unsigned char>(Clamped);
        }
      }
      break;

    case RT_FORMAT_FLOAT3:
      // This buffer is upside down
      for(int j = height-1; j >= 0; --j) {
        unsigned char *dst = &pix[0] + (3*width*(height-1-j));
        float* src = ((float*)imageData) + (3*width*j);
        for(int i = 0; i < width; i++) {
          for(int elem = 0; elem < 3; ++elem) {
            int P = static_cast<int>((*src++) * 255.0f);
            unsigned int Clamped = P < 0 ? 0 : P > 0xff ? 0xff : P;
            *dst++ = static_cast<unsigned char>(Clamped);
          }
        }
      }
      break;

    case RT_FORMAT_FLOAT4:
      // This buffer is upside down
      for(int j = height-1; j >= 0; --j) {
        unsigned char *dst = &pix[0] + (3*width*(height-1-j));
        float* src = ((float*)imageData) + (4*width*j);
        for(int i = 0; i < width; i++) {
          for(int elem = 0; elem < 3; ++elem) {
            int P = static_cast<int>((*src++) * 255.0f);
            unsigned int Clamped = P < 0 ? 0 : P > 0xff ? 0xff : P;
            *dst++ = static_cast<unsigned char>(Clamped);
          }

          // skip alpha
          src++;
        }
      }
      break;

    default:
      fprintf(stderr, "Unrecognized buffer data type or format.\n");
      exit(2);
      break;
  }

  SavePPM(&pix[0], filename, width, height, 3);

  // Now unmap the buffer
  result = rtBufferUnmap(buffer);
  if (result != RT_SUCCESS) {
    // Get error from context
    RTcontext context;
    const char* error;
    rtBufferGetContext(buffer, &context);
    rtContextGetErrorString(context, result, &error);
    fprintf(stderr, "Error unmapping image buffer: %s\n", error);
    exit(2);
  }

  return RT_SUCCESS;
}

#ifdef GLUT_FOUND

static void
keyPressed(unsigned char key, int x, int y)
{
  switch (key) {
  case 27: // esc
  case 'q':
    rtContextDestroy( g_context );
    exit(EXIT_SUCCESS);
  }
}

static RTbuffer imageBuffer = 0;

static void
display(void)
{
  RTresult result;
  GLvoid* imageData;
  GLsizei width, height;
  RTsize buffer_width, buffer_height;
  RTformat buffer_format;

  result = rtBufferMap(imageBuffer, &imageData);
  if (result != RT_SUCCESS) {
    // Get error from context
    RTcontext context;
    const char* error;
    rtBufferGetContext(imageBuffer, &context);
    rtContextGetErrorString(context, result, &error);
    fprintf(stderr, "Error mapping image buffer: %s\n", error);
    exit(2);
  }
  if (0 == imageData) {
    fprintf(stderr, "data in buffer is null.\n");
    exit(2);
  }

  result = rtBufferGetSize2D(imageBuffer, &buffer_width, &buffer_height);
  if (result != RT_SUCCESS) {
    // Get error from context
    RTcontext context;
    const char* error;
    rtBufferGetContext(imageBuffer, &context);
    rtContextGetErrorString(context, result, &error);
    fprintf(stderr, "Error getting dimensions of buffer: %s\n", error);
    exit(2);
  }
  width  = static_cast<GLsizei>(buffer_width);
  height = static_cast<GLsizei>(buffer_height);

  result = rtBufferGetFormat(imageBuffer, &buffer_format);
  GLenum gl_data_type = GL_FALSE;
  GLenum gl_format = GL_FALSE;
  switch (buffer_format) {
    case RT_FORMAT_UNSIGNED_BYTE4:
      gl_data_type = GL_UNSIGNED_BYTE;
      gl_format    = GL_BGRA;
      break;

    case RT_FORMAT_FLOAT:
      gl_data_type = GL_FLOAT;
      gl_format    = GL_LUMINANCE;
      break;

    case RT_FORMAT_FLOAT3:
      gl_data_type = GL_FLOAT;
      gl_format    = GL_RGB;
      break;

    case RT_FORMAT_FLOAT4:
      gl_data_type = GL_FLOAT;
      gl_format    = GL_RGBA;
      break;

    default:
      fprintf(stderr, "Unrecognized buffer data type or format.\n");
      exit(2);
      break;
  }

  glDrawPixels(width, height, gl_format, gl_data_type, imageData);
  glutSwapBuffers();

  // Now unmap the buffer
  result = rtBufferUnmap(imageBuffer);
  if (result != RT_SUCCESS) {
    // Get error from context
    RTcontext context;
    const char* error;
    rtBufferGetContext(imageBuffer, &context);
    rtContextGetErrorString(context, result, &error);
    fprintf(stderr, "Error unmapping image buffer: %s\n", error);
    exit(2);
  }
}

extern "C"
RTresult
initGlut(int* argc, char** argv)
{
  // Initialize GLUT
  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(100, 100);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  g_glut_initialized = true;

  return RT_SUCCESS;
}

extern "C"
RTresult
displayGlutWindow(const char* window_title, RTbuffer buffer)
{
  RTresult result;
  RTsize buffer_width, buffer_height;
  int width, height;

  // Set the global RTcontext so we can destroy it at exit
  if ( g_context != NULL ) {
    fprintf(stderr, "displayGlutWindow called, while another displayGlut is active.  Not supported.");
    return RT_ERROR_UNKNOWN;
  }
  rtBufferGetContext( buffer, &g_context );
  
  if ( !g_glut_initialized ) {
    fprintf(stderr, "displayGlutWindow called before initGlut.");
    return RT_ERROR_UNKNOWN;
  }

  result = checkBuffer(buffer);
  if (result != RT_SUCCESS) {
    fprintf(stderr, "checkBuffer didn't pass\n");
    return result;
  }
  imageBuffer = buffer;

  result = rtBufferGetSize2D(buffer, &buffer_width, &buffer_height);
  if (result != RT_SUCCESS) {
    fprintf(stderr, "Error getting dimensions of buffer\n");
    return result;
  }
  width  = static_cast<int>(buffer_width);
  height = static_cast<int>(buffer_height);

  glutSetWindowTitle(window_title);
  glutReshapeWindow(width, height);

  // Init state
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, width, 0, height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.375, 0.375, 0.0);

  glutKeyboardFunc(keyPressed);
  glutDisplayFunc(display);

  glutMainLoop();

  return RT_SUCCESS;
}

/*******/
/* VBO */
/*******/

unsigned int vbo_id;
unsigned int buffer_width;
unsigned int buffer_height;

static void
displayVBO(void)
{
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, vbo_id);
  glDrawPixels(buffer_width, buffer_height, GL_RGB, GL_FLOAT, 0);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
  glutSwapBuffers();
}


extern "C"
RTresult
displayGlutWindowVBO(const char* window_title,
                     unsigned int vboId,
                     unsigned int width,
                     unsigned int height,
                     RTcontext context)
{
  
  // Set the global RTcontext so we can destroy it at exit
  if ( g_context != NULL ) {
    fprintf(stderr, "displayGlutWindowVBO called, while another displayGlut is active.  Not supported.");
    return RT_ERROR_UNKNOWN;
  }
  g_context = context;
  
  if ( !g_glut_initialized ) {
    fprintf(stderr, "displayGlutWindowVBO called before initGlut.");
    return RT_ERROR_UNKNOWN;
  }

  glutSetWindowTitle(window_title);
  glutReshapeWindow(width, height);

  buffer_width = width;
  buffer_height = height;
  vbo_id = vboId;

  // Init state
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, width, 0, height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.375, 0.375, 0.0);

  glutKeyboardFunc(keyPressed);
  glutDisplayFunc(displayVBO);

  glutMainLoop();

  return RT_SUCCESS;
}

extern "C"
RTresult
cleanCommandLineArgs(int* argc, char** argv)
{
  // TODO: implement removal of -psn_0_* flag
  return RT_SUCCESS;
}

#else // #ifdef GLUT_FOUND

extern "C"
RTresult
initGlut(int* argc, char** argv)
{
  cleanCommandLineArgs( argc, argv ) 
  fprintf(stderr, "Glut is not configured for this build. cleanCommandLinArgs needs to be implemented\n");
  return RT_SUCCESS;
}

extern "C"
RTresult
displayGlutWindow(const char* window_title, RTbuffer buffer)
{
  fprintf(stderr, "Glut is not configured for this build.\n");
  return RT_NOT_IMPLEMENTED;
}

extern "C"
RTresult
displayGlutWindowVBO(const char* window_title, unsigned int vboId, unsigned int width, unsigned int height)
{
  fprintf(stderr, "Glut is not configured for this build.\n");
  return RT_NOT_IMPLEMENTED;
}

extern "C"
RTresult
displayFilePPM(const char* filename, RTbuffer buffer);

#endif // #ifdef GLUT_FOUND


