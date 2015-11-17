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
  #define glrDEBUG(x) { printf("rank: %d %s", MantaManager::singleton()->_rank, x); fflush(stdout); }
#else
  #define glrDEBUG(x) { std::cout << __PRETTY_FUNCTION__ << " (" << #x << ") " << x << std::endl; }
#endif
#else
  #define glrDEBUG(x) { ; }
#endif

typedef float Real;

#endif
