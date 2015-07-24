SET(GVT_SOURCES "")

SET(GVT_SOURCES ${GVT_SOURCES}
 GvtRenderer.cc
 GvtRenderer.h
 GvtRenderable.cc
 GvtRenderable.h
 GvtScene.h
  )



ADD_LIBRARY (GLuRay_GVT STATIC ${GVT_SOURCES})

TARGET_LINK_LIBRARIES(GLuRay_GVT ${GVT_LIBS})


