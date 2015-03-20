
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

//-----------------------------------------------------------------------------
//
//  MeshScene.cpp
//  
//-----------------------------------------------------------------------------

#include <optixu/optixpp_namespace.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_aabb_namespace.h>
#include <sutil.h>
#include <GLUTDisplay.h>
#include <PlyLoader.h>
#include <ObjLoader.h>
#include "commonStructs.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "random.h"
#include "MeshScene.h"

using namespace optix;

//------------------------------------------------------------------------------
//
// MeshScene implementation
//
//------------------------------------------------------------------------------


const int MeshScene::WIDTH  = 1024;
const int MeshScene::HEIGHT = 768;


MeshScene::MeshScene():
  m_accel_builder("Sbvh"),
  m_accel_traverser("Bvh"),
  m_accel_refine("0"),
  m_accel_cache_loaded( false ),
  m_accel_caching_on  ( false ),
  m_accel_large_mesh  ( false )
{
}


SUTILAPI MeshScene::MeshScene(bool accel_cache_loaded, bool accel_caching_on, bool accel_large_mesh):
  m_accel_builder("Sbvh"),
  m_accel_traverser("Bvh"),
  m_accel_refine("0"),
  m_accel_cache_loaded( accel_cache_loaded ),
  m_accel_caching_on  ( accel_caching_on ),
  m_accel_large_mesh  ( accel_large_mesh )
{
}


void MeshScene::loadAccelCache()
{
  // If acceleration caching is turned on and a cache file exists, load it.
  if( m_accel_caching_on ) {

    const std::string cachefile = getCacheFileName();

    std::ifstream in( cachefile.c_str(), std::ifstream::in | std::ifstream::binary );
    if ( in ) {
      unsigned long long int size = 0ull;

#ifdef WIN32
      // This is to work around a bug in Visual Studio where a pos_type is cast to an int before being cast to the requested type, thus wrapping file sizes at 2 GB. WTF? To be fixed in VS2011.
      FILE *fp = fopen(cachefile.c_str(), "rb");

      _fseeki64(fp, 0L, SEEK_END);
      size = _ftelli64(fp);
      fclose(fp);
#else
      // Read data from file
      in.seekg (0, std::ios::end);
      std::ifstream::pos_type szp = in.tellg();
      in.seekg (0, std::ios::beg);
      size = static_cast<unsigned long long int>(szp);
#endif

      std::cerr << "acceleration cache file found: '" << cachefile << "' (" << size << " bytes)\n";
      
      if(sizeof(size_t) <= 4 && size >= 0x80000000ULL) {
        std::cerr << "[WARNING] acceleration cache file too large for 32-bit application.\n";
        m_accel_cache_loaded = false;
        return;
      }

      char* data = new char[static_cast<size_t>(size)];
      in.read( data, static_cast<std::streamsize>(size) );
      
      // Load data into accel
      Acceleration accel = m_geometry_group->getAcceleration();
      try {
        accel->setData( data, static_cast<RTsize>(size) );
        m_accel_cache_loaded = true;

      } catch( optix::Exception& e ) {
        // Setting the acceleration cache failed, but that's not a problem. Since the acceleration
        // is marked dirty and builder and traverser are both set already, it will simply build as usual,
        // without using the cache. So we just warn the user here, but don't do anything else.
        std::cerr << "[WARNING] could not use acceleration cache, reason: " << e.getErrorString() << std::endl;
        m_accel_cache_loaded = false;
      }

      delete[] data;

    } else {
      m_accel_cache_loaded = false;
      std::cerr << "no acceleration cache file found\n";
    }
  }
}

void MeshScene::saveAccelCache()
{
  // If accel caching on, marshallize the accel 
  if( m_accel_caching_on && !m_accel_cache_loaded ) {

    const std::string cachefile = getCacheFileName();

    // Get data from accel
    Acceleration accel = m_geometry_group->getAcceleration();
    RTsize size = accel->getDataSize();
    char* data  = new char[size];
    accel->getData( data );

    // Write to file
    std::ofstream out( cachefile.c_str(), std::ofstream::out | std::ofstream::binary );
    if( !out ) {
      delete[] data;
      std::cerr << "could not open acceleration cache file '" << cachefile << "'" << std::endl;
      return;
    }
    out.write( data, size );
    delete[] data;
    std::cerr << "acceleration cache written: '" << cachefile << "'" << std::endl;
  }
}

std::string MeshScene::getCacheFileName()
{
  std::string cachefile = m_filename;
  size_t idx = cachefile.find_last_of( '.' );
  cachefile.erase( idx );
  cachefile.append( ".accelcache" );
  return cachefile;
}
