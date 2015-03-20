
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

#include <ObjLoader.h>
#include <PlyLoader.h>
#include <ModelLoader.h>
#include <iostream>


////////////////////////////////////////////
// 
//  Entry point from sutil api 
//
////////////////////////////////////////////


extern "C"
RTresult loadModel( const char* fname, RTcontext context, RTmaterial mat, RTgeometrygroup* geometrygroup )
{

  // Ensure we have a valid geometry group 
  if ( !(*geometrygroup) ) {
    RTresult result = rtGeometryGroupCreate( context, geometrygroup );
    if ( result != RT_SUCCESS ) {
      std::cerr << "loadModel(): rtGeometryGroupCreate failed. " << std::endl;
      return result;
    }
  } else {
    unsigned int num_children;
    RTresult result = rtGeometryGroupGetChildCount( *geometrygroup, &num_children );
    if ( result != RT_SUCCESS ) {
      std::cerr << "loadModel(): rtGeometryGroupGetChildCount failed. " << std::endl;
      return result;
    }
    if ( num_children != 0 ) {
      std::cerr << "loadModel() - geometry group has preexisting children" << std::endl; 
      return RT_ERROR_INVALID_VALUE;
    }
  }

  // Load the file
  if ( ObjLoader::isMyFile( fname ) ) {
    try {
      if ( mat )  {
        ObjLoader loader( fname,
                          optix::Context::take( context ),
                          optix::GeometryGroup::take( *geometrygroup ),
                          optix::Material::take( mat ) );
        loader.load();
      } else {
        ObjLoader loader( fname,
                          optix::Context::take( context ),
                          optix::GeometryGroup::take( *geometrygroup ) );
        loader.load();
      }
    } catch( optix::Exception& e ) {
      std::cerr << " loadModel() failed: '" << e.getErrorString() << "'" 
                << std::endl;
      return RT_ERROR_UNKNOWN;
    } catch( ... ) {
      std::cerr << " loadModel() failed: error unknown" << std::endl; 
      return RT_ERROR_UNKNOWN;
    }
    return RT_SUCCESS;

  } else if( PlyLoader::isMyFile( fname ) ) { 
    try {
      PlyLoader loader( fname,
                        optix::Context::take( context ),
                        optix::GeometryGroup::take( *geometrygroup ),
                        optix::Material::take( mat ) );
      loader.load();
    } catch( optix::Exception& e ) {
      std::cerr << " loadModel() failed: '" << e.getErrorString() << "'" 
                << std::endl;
      return RT_ERROR_UNKNOWN;
    } catch( ... ) {
      std::cerr << " loadModel() failed: error unknown" << std::endl; 
      return RT_ERROR_UNKNOWN;
    }
    return RT_SUCCESS;

  } else {
    std::cerr << "loadModel: '" << fname << "' extension not recognized." 
              << std::endl;
    return RT_ERROR_INVALID_VALUE;
  }
}


#define SET_ZERO_IF_NOT_NULL( ptr )                                            \
  do { if( ptr ) *ptr = 0; } while( false )


#define REQUIRE_NOT_NULL( ptr )                                                \
  do {                                                                         \
    if( !ptr ) {                                                               \
      std::cerr << "loadModelRaw: Invalid input. '#ptr' is NULL.";             \
      return false;                                                            \
    }                                                                          \
  } while( false )


extern "C"
int loadModelRaw( const char* filename,
                   int*    num_triangles,
                   int**   triangle_indices,
                   int*    num_vertices,
                   float** vertices,
                   float   bbox_min[3],
                   float   bbox_max[3] )
{
  // Init all output variables to zero as failure state
  SET_ZERO_IF_NOT_NULL( num_triangles    );
  SET_ZERO_IF_NOT_NULL( triangle_indices );
  SET_ZERO_IF_NOT_NULL( num_vertices     );
  SET_ZERO_IF_NOT_NULL( vertices         );

  // Now report error if any are NULL 
  REQUIRE_NOT_NULL( num_triangles    );
  REQUIRE_NOT_NULL( triangle_indices );
  REQUIRE_NOT_NULL( num_vertices     );
  REQUIRE_NOT_NULL( vertices         );

  if( ObjLoader::isMyFile( filename ) )
  {
    GLMmodel* model = glmReadOBJ( filename );
    if( !model )
    {
      std::cerr << "loadModelRaw: glmReadOBJ( " << filename << ") failed."
                << std::endl;
      return 0;
    }

    //
    // Vertices
    //
    *num_vertices = model->numvertices;
    *vertices = new (std::nothrow) float[ *num_vertices*3 ];
    if( !(*vertices) )
    {
      std::cerr << "loadModelRaw: failed to allocate memory.";
      return 0;
    }
    std::copy( model->vertices + 3, // Skip dummy vert
               model->vertices + 3 + model->numvertices*3,
               *vertices );

    //
    // Triangle indices
    //
    *num_triangles = model->numtriangles;
    *triangle_indices = new (std::nothrow) int[ *num_triangles*3 ];
    if( !(*triangle_indices) )
    {
      std::cerr << "loadModelRaw: failed to allocate memory.";
      return 0;
    }

    for( int i=0; i < *num_triangles; ++i )
    {
      (*triangle_indices)[ 3*i+0 ] = model->triangles[i].vindices[0]-1; // 
      (*triangle_indices)[ 3*i+1 ] = model->triangles[i].vindices[1]-1; // Account for dummy vert
      (*triangle_indices)[ 3*i+2 ] = model->triangles[i].vindices[2]-1; //
    }

    glmBoundingBox( model, bbox_min, bbox_max );
    glmDelete( model );

    return 1;

  } else {
    std::cerr << "loadModelRaw: '" << filename << "' extension not recognized." 
              << std::endl;
    return 0;
  }
}


#undef SET_ZERO_IF_NOT_NULL
#undef REQUIRE_NOT_NULL


extern "C"
int deleteModelRaw( int**   triangle_indices,
                    float** vertices )
{
   if( !triangle_indices || !vertices )
   {
     std::cerr << "deleteModelRaw: invalid NULL input pointer" << std::endl;
     return 0;
   }

   delete [] *triangle_indices; 
   *triangle_indices = 0;

   delete [] *vertices;
   *vertices = 0;

   return 1;
}

