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
