/**********************************************************************************
*                     Copyright (c) 2013-2015 Carson Brownlee
*         Texas Advanced Computing Center, University of Texas at Austin
*                       All rights reserved
* 
*       This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
* 
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
* 
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************************/
#ifndef DEFINES_H
#define DEFINES_H

#include <CMakeDefines.h>

enum RenderModes {GLURAY_RENDER_GLFINISH=1, GLURAY_RENDER_GLFLUSH=2, GLURAY_RENDER_GLREADPIXELS=4,
  GLURAY_RENDER_GLXSWAPBUFFERS=8};

extern int GLURAY_RENDER_MODE;
//( 0
    //| GLURAY_RENDER_GLXSWAPBUFFERS
    //| GLURAY_RENDER_GLFINISH
    //| GLURAY_RENDER_GLFLUSH
    //| GLURAY_RENDER_GLREADPIXELS
    //)


#if DEBUG_MSGS
#if USE_MPI
  #define DEBUG(x) { printf("rank: %d %s", MantaManager::singleton()->_rank, x); fflush(stdout); }
#else
  #define DEBUG(x) { printf(x); }
#endif
#else
  #define DEBUG(x) { ; }
#endif


typedef float Real;

#endif
