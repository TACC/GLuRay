#/**********************************************************************************
#*                     Copyright (c) 2013-2015 Carson Brownlee
#*         Texas Advanced Computing Center, University of Texas at Austin
#*                       All rights reserved
#* 
#*       This library is free software; you can redistribute it and/or
#* modify it under the terms of the GNU Lesser General Public
#* License as published by the Free Software Foundation; either
#* version 2.1 of the License, or (at your option) any later version.
#* 
#* This library is distributed in the hope that it will be useful,
#* but WITHOUT ANY WARRANTY; without even the implied warranty of
#* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#* Lesser General Public License for more details.
#* 
#* You should have received a copy of the GNU Lesser General Public
#* License along with this library; if not, write to the Free Software
#* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#**********************************************************************************/

CMAKE_MINIMUM_REQUIRED(VERSION 2.6.4)

PROJECT(GLuRay)

SET(CMAKE_CXX_FLAGS "-std=c++0x -fPIC")

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)
FIND_PACKAGE(Manta)
FIND_PACKAGE(OpenGL)
#FIND_PACKAGE(Boost)

SET(GLURAY_SRC
  src/Core/gluray.cc
  src/Modules/Manta/DirtyInstance.cc
  src/Modules/Manta/MRenderable.cc
  src/Modules/Manta/MantaRenderer.cc
 src/Modules/Manta/MScene.cc
  src/Core/Work.cc
  src/Modules/Manta/AccelWork.cc
  src/Core/RenderManager.cc
  src/Core/Renderer.cc
  src/Core/OBJScene.cc
  src/Core/Scene.cc
  src/Core/GeometryGenerator.cc
  )


SET(GLURAY_HDR
  src/Core/defines.h
  src/Core/gluray.h
  src/Core/GLuRayRenderParameters.h
  src/Modules/Manta/MantaRenderer.h
  src/Core/RenderManager.h
  src/Core/Renderer.h
  src/Core/Renderable.h
  src/Modules/Manta/MRenderable.h
  src/Core/GeometryGenerator.h
  src/Core/Work.h
  src/Modules/Manta/AccelWork.h
  src/Modules/Manta/MScene.h
  src/Modules/Manta/DirtyInstance.h
  src/Core/CDTimer.h
  src/Core/OBJScene.h
  src/Core/Scene.h
  )

###############################################################################
## Configure distributed version of manta for an MPI-based cluster

SET (ENABLE_MPI FALSE CACHE BOOL "Build MPI version of manta for running on clusters.")
IF (ENABLE_MPI)
  SET(USE_MPI_DEF "1" CACHE INTERNAL "Use MPI")
ELSE (ENABLE_MPI)
  SET(USE_MPI_DEF "0" CACHE INTERNAL "Use MPI")
ENDIF (ENABLE_MPI)

IF(ENABLE_MPI)
  SET(GLURAY_SRC ${GLURAY_SRC}
   src/Modules/Manta/ice_semaphore.cc
  src/Modules/Manta/CDComm.cc
  src/Modules/Manta/DynBVH_D.cc
  src/Modules/Manta/Mesh_DSM.cc
    )

  SET(GLURAY_HDR ${GLURAY_HDR}
src/Modules/Manta/DSM_Data.h
  src/Modules/Manta/ice_semaphore.h
  src/Modules/Manta/CDComm.h
  src/Modules/Manta/DynBVH_D.h
  src/Modules/Manta/Mesh_DSM.h
  
    )
ENDIF(ENABLE_MPI)



SET(USE_RIVL NO CACHE BOOL "using intels rivl")
SET(USE_EMBREE NO CACHE BOOL "using intels embree")
SET(USE_OSPRAY NO CACHE BOOL "using intels ospray")
SET(USE_OPTIX NO CACHE BOOL "using nvidia optix")
SET(USE_GVT NO CACHE BOOL "using gvt")
INCLUDE_DIRECTORIES(src/Core src/Modules/Manta src/Modules/RIVL
  ${CMAKE_BINARY_DIR}/include
  src/Modules/Embree src/Modules/Gvt src)
#INCLUDE_DIRECTORIES( ${MANTA_INCLUDE} )
#include_directories(${OPENGL_INCLUDE_DIR})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

ADD_LIBRARY(GLuRay SHARED ${GLURAY_SRC} ${GLURAY_HDR})
SET(GLURAY_LIBS ${MANTA_TARGET_LINK_LIBRARIES})
SET(CMAKE_DEFINES "")
IF(USE_RIVL)
  SET(GLURAY_LIBS ${GLURAY_LIBS} GLuRay_RIVL)
  SET(CMAKE_DEFINES "${CMAKE_DEFINES}#define USE_RIVL 1\n")
  SUBDIRS(src/Modules/RIVL)
ENDIF(USE_RIVL)
IF(USE_EMBREE)
  SET(MANTA_SSE NO)
  IF(USE_RIVL)
    MESSAGE( FATAL_ERROR "can't use multiple renderers for now, RIVL and
    EMBREE enabled")
  ENDIF(USE_RIVL)
  SET(CMAKE_DEFINES "${CMAKE_DEFINES}#define USE_EMBREE 1\n")
  #SET(GLURAY_LIBS ${GLURAY_LIBS} GLuRay_EMBREE)
  SUBDIRS(src/Modules/Embree)
  SET(GLURAY_LIBS ${GLURAY_LIBS} GLuRay_EMBREE)
ENDIF(USE_EMBREE)
IF(USE_OSPRAY)
  SET(MANTA_SSE NO)
  IF(USE_RIVL)
    MESSAGE( FATAL_ERROR "can't use multiple renderers for now, RIVL and
    EMBREE enabled")
  ENDIF(USE_RIVL)
  IF(USE_EMBREE)
    MESSAGE( FATAL_ERROR "can't use multiple renderers for now, RIVL and
    EMBREE enabled")
  ENDIF(USE_EMBREE)
  SET(CMAKE_DEFINES "${CMAKE_DEFINES}#define USE_OSPRAY 1\n")
  #SET(GLURAY_LIBS ${GLURAY_LIBS} GLuRay_EMBREE)
  SUBDIRS(src/Modules/OSPRay)
  SET(GLURAY_LIBS ${GLURAY_LIBS} GLuRay_OSPRay)
ENDIF(USE_OSPRAY)
IF (USE_OPTIX)
  SET(CMAKE_DEFINES "${CMAKE_DEFINES}#define USE_OPTIX 1\n")
  SUBDIRS(src/Modules/OptiX)
  SET(GLURAY_LIBS ${GLURAY_LIBS} GLuRay_Optix)
ENDIF()
IF(USE_GVT)
  SET(CMAKE_DEFINES "${CMAKE_DEFINES}#define USE_GVT 1\n")
  SUBDIRS(src/Modules/Gvt)
  SET(GLURAY_LIBS ${GLURAY_LIBS} GLuRay_Gvt)
ENDIF(USE_GVT)
#SET(GLURAY_LIBS "")
 MESSAGE(STATUS "GLURAY_LIBS: " ${GLURAY_LIBS})
TARGET_LINK_LIBRARIES(GLuRay ${GLURAY_LIBS} ${OPENGL_gl_LIBRARY})
CONFIGURE_FILE(
  ${MANTA_SOURCE_DIR}/include/UseMPI.h.CMakeTemplate
  ${MANTA_BUILD_PREFIX}/include/UseMPI.h
)

#
#set cmake defines accessable by source files
#
SET(DEBUG_MSGS NO CACHE BOOL "Debug messages")
SET(DEBUG_GL NO CACHE BOOL "output gl calls")
SET(INTERCEPT_GL_ERRORS NO CACHE BOOL "prevent OpenGL errors from reaching host code")
SET(USE_GLURAY YES CACHE BOOL "use gluray calls")
SET(RUN_CLIENT NO CACHE BOOL "run gui client")

IF(DEBUG_MSGS)
  SET(CMAKE_DEFINES "${CMAKE_DEFINES}#define DEBUG_MSGS 1\n")
ELSE(DEBUG_MSGS)
  SET(CMAKE_DEFINES "${CMAKE_DEFINES}#define DEBUG_MSGS 0\n")
ENDIF(DEBUG_MSGS)

IF(DEBUG_GL)
  SET(CMAKE_DEFINES "${CMAKE_DEFINES}#define DEBUG_GL 1\n")
ELSE(DEBUG_GL)
  SET(CMAKE_DEFINES "${CMAKE_DEFINES}#define DEBUG_GL 0\n")
ENDIF(DEBUG_GL)

IF(INTERCEPT_GL_ERRORS)
  SET(CMAKE_DEFINES "${CMAKE_DEFINES}#define INTERCEPT_GL_ERRORS 1\n")
ELSE(INTERCEPT_GL_ERRORS)
  SET(CMAKE_DEFINES "${CMAKE_DEFINES}#define INTERCEPT_GL_ERRORS 0\n")
ENDIF(INTERCEPT_GL_ERRORS)

IF(USE_GLURAY)
  SET(CMAKE_DEFINES "${CMAKE_DEFINES}#define USE_GLURAY 1\n")
ELSE(USE_GLURAY)
  SET(CMAKE_DEFINES "${CMAKE_DEFINES}#define USE_GLURAY 0\n")
ENDIF(USE_GLURAY)

IF(RUN_CLIENT)
  SET(CMAKE_DEFINES "${CMAKE_DEFINES}#define RUN_CLIENT 1\n")
ELSE(RUN_CLIENT)
  SET(CMAKE_DEFINES "${CMAKE_DEFINES}#define RUN_CLIENT 0\n")
ENDIF(RUN_CLIENT)

MESSAGE(STATUS ${OPENGL_gl_LIBRARY})
SET(CMAKE_DEFINES "${CMAKE_DEFINES}#define OPENGLLIB \"${OPENGL_gl_LIBRARY}\"\n")
FILE(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/include)
FILE(WRITE ${CMAKE_BINARY_DIR}/include/CMakeDefines.h ${CMAKE_DEFINES})
PROJECT(fakeGL)

FIND_PACKAGE(Manta)
FIND_PACKAGE(OpenGL REQUIRED)
ADD_LIBRARY(fakeGL SHARED gluray_interception.c)
include_directories(${OPENGL_INCLUDE_DIR})
message("opengl include directories: ${OPENGL_INCLUDE_DIR}")
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

#TARGET_LINK_LIBRARIES(fakeGL ${MANTA_TARGET_LINK_LIBRARIES} GLuRay)
TARGET_LINK_LIBRARIES(fakeGL ${GLURAY_LIBS} GLuRay ${OPENGL_gl_LIBRARY})

IF (ENABLE_MPI)
  FIND_PACKAGE(MPI REQUIRED)
  INCLUDE_DIRECTORIES(${MPI_INCLUDE_PATH})
  TARGET_LINK_LIBRARIES(fakeGL ${MPI_LIBRARIES})
  if(MPI_COMPILE_FLAGS)
    set_target_properties(fakeGL PROPERTIES
      COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
  endif()

  if(MPI_LINK_FLAGS)
    set_target_properties(fakeGL PROPERTIES
      LINK_FLAGS "${MPI_LINK_FLAGS}")
  endif()
ENDIF (ENABLE_MPI)

TARGET_LINK_LIBRARIES(fakeGL ${CMAKE_DL_LIBS})
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GNU_SOURCE")

FILE(REMOVE ${PROJECT_BINARY_DIR}/gluray)
FILE(WRITE ${PROJECT_BINARY_DIR}/gluray
  "#!/bin/sh\nLD_PRELOAD=\${LD_PRELOAD}:\"${PROJECT_BINARY_DIR}/libfakeGL.so\" \${1+\"\$@\"}\n"
  )
EXECUTE_PROCESS(COMMAND chmod +x ${PROJECT_BINARY_DIR}/gluray)
