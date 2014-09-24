#find_package(OSPRay)
#INCLUDE_DIRECTORIES(
  #${OSPRAY_INCLUDE_DIRS}
  #)

find_package(OptiX)
INCLUDE_DIRECTORIES( ${optix_INCLUDE} )

SET(glrOptix_SRC "")

SET(glrOptix_SRC 
 OptiXManager.cc
 OptiXManager.h
 ORenderable.cc
 ORenderable.h
 OScene.cc
 OScene.h
  )

ADD_LIBRARY (GLuRay_Optix STATIC ${glrOptix_SRC})

TARGET_LINK_LIBRARIES(GLuRay_Optix ${optix_LIBRARY})


