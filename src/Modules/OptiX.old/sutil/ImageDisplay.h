
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

#pragma once

/* This file contains helper code to display an image stored in a CUDA buffer. */

#include <optix.h>

#ifdef __cplusplus
extern "C" 
{ 
#endif /* __cplusplus */

/* initializes the glut window and creates a context.  May only be called once
 * per application invocation.  This function must be called prior to calling
 * displayGlutWindow[VBO].
 */ 
RTresult initGlut(int* argc, char** argv);

/* Uses a glut window to display the image.  This function can only be called
 * once per application invocation.  Depending on the implementation of GLUT,
 * control may not be given back to the application after startup.  In addition
 * most GLUT implementations cannot be started up again (the library uses a set
 * of global variables that cannot be reinitialized).
 * */
RTresult displayGlutWindow(const char* window_title, RTbuffer buffer);

/* Uses a glut window to display the image.  This function may only be called
 * once per application invocation.  Depending on the implementation of GLUT,
 * control may not be given back to the application after displaying the image.
 * In addition most GLUT implementations cannot be started up again (the library
 * uses a set of global variables that cannot be reinitialized). Context is
 * passed in so RTAPI can be exited cleanly
 */
RTresult displayGlutWindowVBO(const char* window_title,
                              unsigned int vboId,
                              unsigned int width,
                              unsigned int height,
                              RTcontext context);

/* Whatever filename you give here will have .ppm appended to it. */
RTresult displayFilePPM(const char* filename, RTbuffer buffer);

/* Clean up command line args.  Currently only cleans up the -psn_0_####### arg
 * added by the OS when invoking samples via OSX app.
 */
RTresult cleanCommandLineArgs( int* argc, char** argv );

#ifdef __cplusplus
}
#endif /* __cplusplus */
