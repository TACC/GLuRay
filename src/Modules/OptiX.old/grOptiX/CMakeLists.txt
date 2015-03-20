#find_package(OSPRay)
#INCLUDE_DIRECTORIES(
  #${OSPRAY_INCLUDE_DIRS}
  #)

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
 OptiXManager.cc
 OptiXManager.h
 ORenderable.cc
 ORenderable.h
 OScene.cc
 OScene.h
  )

ADD_LIBRARY (GLuRay_Optix STATIC ${glrOptix_SRC} ${CUDA_LIBRARIES})

TARGET_LINK_LIBRARIES(GLuRay_Optix ${optix_LIBRARY} optixu ${OptiX_INCLUDE}/../SDK-precompiled-samples/libsutil.so)


