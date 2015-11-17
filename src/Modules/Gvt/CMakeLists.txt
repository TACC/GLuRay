find_package(Gvt REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread timer system)
find_package(MPI REQUIRED)

INCLUDE_DIRECTORIES(${Gvt_DIR}/src)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${MPI_INCLUDE_PATH})

SET(Gvt_SOURCES "")

SET(Gvt_SOURCES ${GVT_SOURCES}
 GvtRenderer.cc
 GvtRenderer.h
 GvtRenderable.cc
 GvtRenderable.h
 GvtScene.h
  )

set(CMAKE_CXX_FLAGS "-cxxlib=/opt/apps/gcc/4.9.1/ ${CMAKE_CXX_FLAGS}")

ADD_LIBRARY (GLuRay_Gvt STATIC ${Gvt_SOURCES})

MESSAGE("Gvt_LIBRARIES: " ${Gvt_LIBRARIES})

TARGET_LINK_LIBRARIES(GLuRay_Gvt ${Gvt_LIBRARIES} ${Boost_LIBRARIES} ${MPI_LIBRARIES})


