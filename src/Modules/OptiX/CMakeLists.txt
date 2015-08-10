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

# cmake_policy(VERSION 2.6)
# cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)
# if(USING_CLANG_C)
#   set(CUDA_HOST_COMPILER "gcc" CACHE FILEPATH "Host side compiler used by NVCC")
# endif()


find_package(CUDA QUIET REQUIRED)
include_directories(
    ${CUDA_INCLUDE_DIRS}
    )

find_package(OptiX)
INCLUDE_DIRECTORIES( ${OptiX_INCLUDE}
${OptiX_INCLUDE}/../SDK
${OptiX_INCLUDE}/../SDK/sutil
 ${OptiX_INCLUDE}/../optixu
 )


MESSAGE("optix include: " ${OptiX_INCLUDE})
MESSAGE("optix_LIBRARY:" ${optix_LIBRARY})

SET(glrOptix_SRC "")

SET(glrOptix_SRC
 OptiXRenderer.cc
 OptiXRenderer.h
 ORenderable.cc
 ORenderable.h
 OScene.cc
 OScene.h
  )

ADD_LIBRARY (GLuRay_Optix STATIC ${glrOptix_SRC} ${CUDA_LIBRARIES})

TARGET_LINK_LIBRARIES(GLuRay_Optix ${optix_LIBRARY} optixu
  ${OptiX_INCLUDE}/../build/lib/libsutil.so)


