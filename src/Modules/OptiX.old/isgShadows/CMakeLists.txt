
#
#  Copyright (c) 2008 - 2009 NVIDIA Corporation.  All rights reserved.
#
#  NVIDIA Corporation and its licensors retain all intellectual property and proprietary
#  rights in and to this software, related documentation and any modifications thereto.
#  Any use, reproduction, disclosure or distribution of this software and related
#  documentation without an express license agreement from NVIDIA Corporation is strictly
#  prohibited.
#
#  TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THIS SOFTWARE IS PROVIDED *AS IS*
#  AND NVIDIA AND ITS SUPPLIERS DISCLAIM ALL WARRANTIES, EITHER EXPRESS OR IMPLIED,
#  INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
#  PARTICULAR PURPOSE.  IN NO EVENT SHALL NVIDIA OR ITS SUPPLIERS BE LIABLE FOR ANY
#  SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER (INCLUDING, WITHOUT
#  LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, LOSS OF
#  BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS) ARISING OUT OF THE USE OF OR
#  INABILITY TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS BEEN ADVISED OF THE POSSIBILITY OF
#  SUCH DAMAGES
#

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(cg_64_bit 64)
endif()

set(enable_hybrid ON)

find_library(CG_LIBRARY NAMES cg Cg PATHS ENV CG_LIB${cg_64_bit}_PATH)
if(NOT CG_LIBRARY)
  first_time_message("Cannot find Cg, isgShadows will not be built")
  set(enable_hybrid OFF)
endif()

find_path(CG_INCLUDE_DIR Cg/cg.h PATH ENV CG_INC_PATH)
if(NOT CG_INCLUDE_DIR)
  first_time_message("Cannot find Cg.h, isgShadows will not be built")
  set(enable_hybrid OFF)
endif()

if(NOT APPLE)
  find_library(CGGL_LIBRARY NAMES cgGL CgGL PATHS ENV CG_LIB${cg_64_bit}_PATH)
  if(NOT CGGL_LIBRARY)
    first_time_message("Cannot find CgGL, isgShadows will not be built")
    set(enable_hybrid OFF)
  endif()
endif()


if(GLUT_FOUND AND OPENGL_FOUND AND enable_hybrid)

  mark_as_advanced(CG_LIBRARY CG_INCLUDE_DIR CGGL_LIBRARY)

  include_directories(${GLUT_INCLUDE_DIR} ${CG_INCLUDE_DIR})
  add_definitions(-DGLUT_FOUND -DGLUT_NO_LIB_PRAGMA)

  include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../nvcommon/include")
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../nvcommon/nvModel/include")

  set(SRCS
    isgShadows.cgfx
    isgShadows.cpp
    opaque_isg.cu
    shadow_request_isg.cu

    # These files are common among multiple samples
    triangle_mesh_fat.cu
    )

  # See top level CMakeLists.txt file for documentation of OPTIX_add_sample_executable.
  OPTIX_add_sample_executable( isgShadows ${SRCS} )

  target_link_libraries( isgShadows
    ${CG_LIBRARY}
    ${CGGL_LIBRARY}
    nvModel
    nvCommon
    )

else()
  first_time_message("Disabling isgShadows, which requires glut and opengl and Cg.")
endif()
