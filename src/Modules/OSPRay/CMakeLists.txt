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

find_package(OSPRay)
INCLUDE_DIRECTORIES(
  ${OSPRAY_INCLUDE_DIRS}
  )

SET(OSPRAY_SOURCES "")

SET(OSPRAY_SOURCES 
 OSPRayRenderer.cc
 OSPRayRenderer.h
 ORenderable.cc
 ORenderable.h
 OScene.cc
 OScene.h
  )

ADD_LIBRARY (GLuRay_OSPRay STATIC ${OSPRAY_SOURCES})

TARGET_LINK_LIBRARIES(GLuRay_OSPRay ${OSPRAY_LIBRARIES})


