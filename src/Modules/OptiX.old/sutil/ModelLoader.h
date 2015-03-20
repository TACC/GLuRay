
/*
 * Copyright (c) 2008 - 2009 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property and proprietary
 * rights in and to this software, related documentation and any modifications thereto.
 * Any use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from NVIDIA Corporation is strictly
 * prohibited.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THIS SOFTWARE IS PROVIDED *AS IS*
 * AND NVIDIA AND ITS SUPPLIERS DISCLAIM ALL WARRANTIES, EITHER EXPRESS OR IMPLIED,
 * INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE.  IN NO EVENT SHALL NVIDIA OR ITS SUPPLIERS BE LIABLE FOR ANY
 * SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER (INCLUDING, WITHOUT
 * LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, LOSS OF
 * BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS) ARISING OUT OF THE USE OF OR
 * INABILITY TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS BEEN ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGES
 */

#pragma once

#include <optix.h>
#include <sutil.h> /* For SUTILAPI */

#ifdef __cplusplus
extern "C" 
{ 
#endif /* __cplusplus */

/* Load model with given filename into the provided geometrygroup.  The
 * geometry group should be NULL, in which case a new group is created, or
 * empty.  If material is NULL, the materials specified by the model are
 * used, or a default if no mats exist in model, else given material is used.
 * Currently only OBJ and PLY models are supported.
 */
RTresult loadModel( const char* filename,
                    RTcontext context,
                    RTmaterial mat,
                    RTgeometrygroup* geometrygroup );

/*
 * Load vertex list and triangle indices from the given file.  Also generates 
 * the BBox of the loaded model.
 *
 * returns 1 for success, zero for failure
 */
SUTILAPI int loadModelRaw( const char* filename,
                           int*    num_triangles,
                           int**   triangle_indices,
                           int*    num_vertices,
                           float** vertices,
                           float   bbox_min[3],
                           float   bbox_max[3] );

/*
 * Delete vertex list and triangle indices which were created with loadModelRaw
 *
 * returns 1 for success, zero for failure
 */
SUTILAPI int deleteModelRaw( int**   triangle_indices,
                             float** vertices );
#ifdef __cplusplus
}
#endif /* __cplusplus */

