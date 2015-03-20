
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

#include <optixu/optixpp_namespace.h>
#include <sutil.h>
#include <string>
#include <iosfwd>

//-----------------------------------------------------------------------------
//
// Utility functions
//
//-----------------------------------------------------------------------------

// Creates a TextureSampler object for the given PPM file.  If filename is 
// empty or PPMLoader fails, a 1x1 texture is created with the provided default
// texture color.
SUTILAPI optix::TextureSampler loadPPMTexture( optix::Context context,
                                             const std::string& ppm_filename,
                                             const optix::float3& default_color );


//-----------------------------------------------------------------------------
//
// PPMLoader class declaration 
//
//-----------------------------------------------------------------------------

class PPMLoader
{
public:
  SUTILAPI PPMLoader( const std::string& filename, const bool vflip = false );
  SUTILAPI ~PPMLoader();

  SUTILAPI optix::TextureSampler loadTexture( optix::Context context,
                                              const optix::float3& default_color,
                                              bool linearize_gamma = false);

  SUTILAPI bool           failed()const;
  SUTILAPI unsigned int   width()const;
  SUTILAPI unsigned int   height()const;
  SUTILAPI unsigned char* raster()const;

private:
  unsigned int   m_nx;
  unsigned int   m_ny;
  unsigned int   m_max_val;
  unsigned char* m_raster;
  bool           m_is_ascii;

  static void getLine( std::ifstream& file_in, std::string& s );

};
