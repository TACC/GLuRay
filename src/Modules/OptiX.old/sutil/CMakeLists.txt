
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

set(sources
  ${SAMPLES_CUDA_DIR}/commonStructs.h
  ${SAMPLES_CUDA_DIR}/helpers.h
  ${SAMPLES_CUDA_DIR}/obj_material.cu
  ${SAMPLES_CUDA_DIR}/phong.h
  ${SAMPLES_CUDA_DIR}/phong.cu
  ${SAMPLES_CUDA_DIR}/random.h
  ${SAMPLES_CUDA_DIR}/triangle_mesh.cu
  ${SAMPLES_CUDA_DIR}/triangle_mesh_small.cu
  rply-1.01/rply.c
  rply-1.01/rply.h
  DeviceMemoryLogger.h
  DeviceMemoryLogger.cpp
  GLUTDisplay.cpp
  GLUTDisplay.h
  glm.h
  glm.cpp
  HDRLoader.cpp
  HDRLoader.h
  ImageDisplay.cpp
  ImageDisplay.h
  ImageLoader.cpp
  ImageLoader.h
  MeshScene.cpp
  MeshScene.h
  ModelLoader.cpp
  ModelLoader.h
  Mouse.cpp
  Mouse.h
  ObjLoader.cpp
  ObjLoader.h
  PlyLoader.cpp
  PlyLoader.h
  PPMLoader.cpp
  PPMLoader.h
  ${CMAKE_CURRENT_BINARY_DIR}/../sampleConfig.h
  SampleScene.h
  SampleScene.cpp
  SunSky.cpp
  SunSky.h
  sutil.c
  sutil.h
  )

if(OPENGL_FOUND AND NOT APPLE)
  list(APPEND sources "glew.c" "GL/glew.h")
  if( WIN32 )
    list(APPEND sources "GL/wglew.h")
  else()
    list(APPEND sources "GL/glxew.h")
  endif()

  if( WIN32 )
    add_definitions(-DGLEW_BUILD)
  endif()

  if(USING_GNU_CXX OR USING_CLANG_CXX)
    # glew.c #includes glew.h which contains "lax" function prototypes
    # glew.c #includes glxew.h which uses "uint", which isn't compatible with ansi
    #set_source_files_properties("glew.c" PROPERTIES COMPILE_FLAGS "-Duint=\"unsigned int\" -Wno-strict-prototypes -Wno-missing-prototypes")
    set_source_files_properties("glew.c" PROPERTIES COMPILE_FLAGS  "-Wno-strict-prototypes -Wno-missing-prototypes")

    # glm dangerously ignores return values for fscanf/fgets 
    set_source_files_properties("glm.cpp" PROPERTIES COMPILE_FLAGS "-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0")
  endif()
  
endif()

if(GLUT_FOUND AND OPENGL_FOUND)
  include_directories(${GLUT_INCLUDE_DIR})
  add_definitions(-DGLUT_FOUND -DGLUT_NO_LIB_PRAGMA)

endif()


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# For commonStructs.h
include_directories(${SAMPLES_CUDA_DIR})

# Compile the cuda files to ptx.  Note that this will ignore all of the non CUDA
# files.
CUDA_COMPILE_PTX(ptx_files ${sources})

# Make the library.
add_library(sutil ${sources} ${ptx_files})

# Use gcc rather than g++ to link if we are linking statically against libgcc_s and libstdc++
if(USING_GNU_C OR USING_GNU_CXX)
  if(GCC_LIBSTDCPP_HACK)
    set_target_properties(sutil PROPERTIES LINKER_LANGUAGE "C")
    target_link_libraries(sutil LINK_PRIVATE ${STATIC_LIBSTDCPP})
  endif()
endif()

# Note that if the GLUT_LIBRARIES and OPENGL_LIBRARIES haven't been looked for,
# these variable will be empty.
target_link_libraries(sutil
  optix
  optixu
  ${GLUT_LIBRARIES}
  ${OPENGL_LIBRARIES}
  )
if(WIN32)
  target_link_libraries(sutil winmm.lib)
endif()
add_perforce_to_target( sutil )

# Copy the free glut dlls as part of the sutil build process
if(WIN32)
  if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set( build_configuration "$(ConfigurationName)" )
  else()
    set( build_configuration "${CMAKE_BUILD_TYPE}")
  endif()

  add_custom_command(TARGET sutil
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -D build_configuration:STRING=${build_configuration}
    -D "output_directory:PATH=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}"
    -D "source_dll:FILE=${GLUT_glut_DLL}"
    -P "${CMAKE_SOURCE_DIR}/CMake/CopyDLL.cmake"
    )
endif()

if(RELEASE_INSTALL_BINARY_SAMPLES AND NOT RELEASE_STATIC_BUILD)
  # If performing a release install, we want to use rpath for our install name.
  # The executables' rpaths will then be set to @executable_path so we can invoke
  # the samples from an arbitrary location and it will still find this library.
  set_target_properties(sutil PROPERTIES
    INSTALL_NAME_DIR "@rpath"
    BUILD_WITH_INSTALL_RPATH ON
    )
  install(TARGETS sutil
    RUNTIME DESTINATION ${SDK_BINARY_INSTALL_DIR}
    LIBRARY DESTINATION ${SDK_BINARY_INSTALL_DIR}
    )
endif()

# Make the list of sources available to the parent directory for installation needs.
set(sutil_sources "${sources}" PARENT_SCOPE)
