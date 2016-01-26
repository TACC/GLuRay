## ======================================================================================= ##
## Copyright 2014-2015 Texas Advanced Computing Center, The University of Texas at Austin  ##
## All rights reserved.                                                                    ##
##                                                                                         ##
## Licensed under the BSD 3-Clause License, (the "License"); you may not use this file     ##
## except in compliance with the License.                                                  ##
## A copy of the License is included with this software in the file LICENSE.               ##
## If your copy does not contain the License, you may obtain a copy of the License at:     ##
##                                                                                         ##
##     http://opensource.org/licenses/BSD-3-Clause                                         ##
##                                                                                         ##
## Unless required by applicable law or agreed to in writing, software distributed under   ##
## the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY ##
## KIND, either express or implied.                                                        ##
## See the License for the specific language governing permissions and limitations under   ##
## limitations under the License.                                                          ##
## ======================================================================================= ##

###############################################################################
# Find OSPRay
# defines:
# OSPRAY_FOUND
# OSPRAY_INCLUDE_DIRS
# OSPRAY_LIBRARIES

SET(OSPRAY_FOUND, FALSE)
SET(OSPRAY_SOURCE "" CACHE FILEPATH "path to OSPRay source")
SET(OSPRAY_BUILD  "" CACHE FILEPATH "path to OSPRay build")

IF(NOT OSPRAY_SOURCE OR NOT OSPRAY_BUILD)
	MESSAGE(SEND_ERROR "OSPRAY_SOURCE and OSPRAY_BUILD are required")
	RETURN()
ENDIF(NOT OSPRAY_SOURCE OR NOT OSPRAY_BUILD)

FIND_PATH(OSPRAY_SOURCE_DIR ospray HINTS ${OSPRAY_SOURCE} DOC "OSPRay base directory")
FILE(GLOB EMBREE_DIR ${OSPRAY_SOURCE_DIR}/ospray/embree*)

IF(NOT OSPRAY_SOURCE_DIR OR NOT EMBREE_DIR)
	MESSAGE(SEND_ERROR "Invalid OSPRAY_SOURCE")
	RETURN()
ENDIF(NOT OSPRAY_SOURCE_DIR OR NOT EMBREE_DIR)

FIND_LIBRARY(LIB_OSPRAY_EMBREE ospray_embree ${OSPRAY_BUILD})
FIND_LIBRARY(LIB_OSPRAY ospray ${OSPRAY_BUILD})
FIND_LIBRARY(LIB_OSPRAY_MODULE_OPENGL_UTIL ospray_module_opengl_util ${OSPRAY_BUILD})

IF(NOT LIB_OSPRAY OR NOT LIB_OSPRAY_EMBREE OR NOT LIB_OSPRAY_MODULE_OPENGL_UTIL)
	MESSAGE(SEND_ERROR "Invalid OSPRAY_BUILD")
	RETURN()
ENDIF(NOT LIB_OSPRAY OR NOT LIB_OSPRAY_EMBREE OR NOT LIB_OSPRAY_MODULE_OPENGL_UTIL)

SET(OSPRAY_LIBRARIES ${LIB_OSPRAY} ${LIB_OSPRAY_EMBREE} ${LIB_OSPRAY_MODULE_OPENGL_UTIL})

SET(OSPRAY_INCLUDE_DIRS
	${OSPRAY_SOURCE_DIR}
	${OSPRAY_SOURCE_DIR}/ospray/include
        ${OSPRAY_SOURCE_DIR}/ospray/embree-v2.7.1
        ${OSPRAY_BUILD}/
	)

IF(WIN32)
  SET(LIB_DIR /Release)
ELSE()
  SET(LIB_DIR "")
ENDIF(WIN32)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${OSPRAY_CMAKE_DIR} ${OSPRAY_DIR})
SET(OSPRAY_CC ${OSP_OSPRAY_COMPILER} CACHE STRING "OSPRay Compiler (ICC, GCC, CLANG)")
SET(OSPRAY_MIC ${OSP_OSPRAY_BUILD_MIC_SUPPORT} CACHE BOOL "Was OSPRay buit with Xeon Phi Support?")
SET(OSPRAY_MPI ${OSP_OSPRAY_BUILD_MPI_DEVICE} CACHE BOOL "Was OSPRay built with MPI Remote/Distributed rendering support?")
SET(OSPRAY_XEON_TARGET ${OSP_OSPRAY_XEON_TARGET} CACHE STRING "OSPRay target ISA on host (SSE,AVX,AVX2)")

MARK_AS_ADVANCED(LIB_OSPRAY LIB_OSPRAY_EMBREE LIB_OSPRAY_MODULE_OPENGL_UTIL OSPRAY_CC OSPRAY_MIC OSPRAY_MPI OSPRAY_SOURCE_DIR OSPRAY_XEON_TARGET)

ADD_DEFINITIONS(${OSPRAY_EMBREE_CXX_FLAGS})

SET(OSPRAY_FOUND, TRUE)
