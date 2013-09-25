SET(IVL_DIR "" CACHE STRING "base IVL directory")
SET(RIVL_DIR "" CACHE STRING "base RIVL directory")
INCLUDE_DIRECTORIES(${RIVL_DIR}/rivl/host)
#INCLUDE_DIRECTORIES(${RIVL_DIR}/../host)

INCLUDE(${IVL_DIR}/runtime/cmake/ivl.cmake)

SET(RIVL_SOURCES)


SET(RIVL_SOURCES ${RIVL_SOURCES}
 RIVLManager.cc
 RIVLManager.h
 RRenderable.cc
 RRenderable.h
 RScene.cc
 RScene.h
 parseOBJ.h
 parseOBJ.cpp
  )

FIND_LIBRARY(LIB_RIVL_HOST rivl_host ${RIVL_DIR}/bin)
SET(RIVL_LIBS
   ${LIB_RIVL_HOST}
  )

ADD_LIBRARY (GLuRay_RIVL SHARED ${RIVL_SOURCES})

TARGET_LINK_LIBRARIES(GLuRay_RIVL ${RIVL_LIBS})
