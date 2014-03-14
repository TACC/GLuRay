SET(GVT_SOURCES "")

SET(GVT_SOURCES ${GVT_SOURCES}
 GvtManager.cc
 GvtManager.h
 GvtRenderable.cc
 GvtRenderable.h
 GvtScene.cc
 GvtScene.h
  )



ADD_LIBRARY (GLuRay_GVT STATIC ${GVT_SOURCES})

TARGET_LINK_LIBRARIES(GLuRay_GVT ${GVT_LIBS})


