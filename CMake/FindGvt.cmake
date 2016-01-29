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
# Find Gvt
# defines:
# GVT_FOUND
# GVT_INCLUDE_DIRS
# GVT_LIBRARIES

# guess that OSPRay is installed in a peer directory (if in dev) or in a peer to the ParaView source
FIND_PATH(Gvt_DIR ospray
  HINTS ${PROJECT_SOURCE_DIR}/../Gvt  ${PROJECT_SOURCE_DIR}/../../../Gvt
  DOC "Gvt base directory"
  )
IF(NOT Gvt_DIR)
  MESSAGE("Could not find OSPRay base directory. Please set OSPRAY_DIR to the root of your local OSPRay git repository.")
ENDIF(NOT Gvt_DIR)

FIND_PATH(Gvt_BUILD_DIR ospModelViewer
  HINTS ${PROJECT_SOURCE_DIR}/../OSPRay/build ${PROJECT_SOURCE_DIR}/../OSPRay ${PROJECT_SOURCE_DIR}/../../../OSPRay/build ${PROJECT_SOURCE_DIR}/../../../OSPRay
  DOC "Gvt build directory"
  )
IF(NOT Gvt_BUILD_DIR)
  MESSAGE("Could not find OSPRay build directory. Please set OSPRAY_BUILD_DIR to the directory where OSPRay was built.")
ENDIF(NOT Gvt_BUILD_DIR)

if (Gvt_BUILD_DIR)
  SET(Gvt_INCLUDE_DIRS
    ${Gvt_DIR}
    )
endif(Gvt_BUILD_DIR)

SET(LIB_Gvt_Core LIB_Gvt_Core-NOTFOUND)
SET(LIB_Gvt_Render LIB_Gvt_Render-NOTFOUND)
FIND_LIBRARY(LIB_Gvt_Core gvtCore ${Gvt_BUILD_DIR}/lib)
FIND_LIBRARY(LIB_Gvt_Render gvtRender ${Gvt_BUILD_DIR}/lib)

SET(Gvt_LIBRARIES
  ${LIB_Gvt_Core}
  ${LIB_Gvt_Render}
  )

