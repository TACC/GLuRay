
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

#include <string>
#include <optixu/optixpp_namespace.h>
#include <sutil.h>
#include <SampleScene.h>

class Mouse;
class PinholeCamera;


//-----------------------------------------------------------------------------
// 
// GLUTDisplay 
//
//-----------------------------------------------------------------------------

class SUTILCLASSAPI GLUTDisplay
{
public:
  enum contDraw_E { CDNone=0, CDProgressive=1, CDAnimated=2, CDBenchmark=3, CDBenchmarkTimed=4 };

  SUTILAPI static void init( int& argc, char** argv );
  SUTILAPI static void run( const std::string& title, SampleScene* scene, contDraw_E continuous_mode = CDNone );
  SUTILAPI static void printUsage();

  SUTILAPI static void setTextColor( const optix::float3& c )
  { m_text_color = c; }

  SUTILAPI static void setTextShadowColor( const optix::float3& c )
  { m_text_shadow_color = c; }

  SUTILAPI static void setProgressiveDrawingTimeout( double t )
  { m_progressive_timeout = t; }

  SUTILAPI static contDraw_E getContinuousMode() { return m_app_continuous_mode; }
  SUTILAPI static void setContinuousMode(contDraw_E continuous_mode);
  SUTILAPI static void setRequiresDisplay( const bool requires_display )
  { m_requires_display = requires_display; }
  SUTILAPI static void restartProgressiveTimer();
  SUTILAPI static void setCamera(SampleScene::InitialCameraData& camera_data);

  SUTILAPI static bool isBenchmark() { return m_cur_continuous_mode == CDBenchmark || m_cur_continuous_mode == CDBenchmarkTimed ||
    m_app_continuous_mode == CDBenchmark || m_app_continuous_mode == CDBenchmarkTimed; }

  // Make sure you only call this from the callback functions found in SampleScene:
  // initScene, trace, getOutputBuffer, cleanUp, resize, doResize, and keyPressed.
  SUTILAPI static void postRedisplay();

  SUTILAPI static void setUseSRGB(bool enabled) { m_use_sRGB = enabled; }

private:

  // Draw text to screen at window pos x,y.  To make this public we will need to have
  // a public helper that caches the text for use in the display func
  static void drawText( const std::string& text, float x, float y, void* font );

  // Do the actual rendering to the display
  static void displayFrame();

  // Executed if m_benchmark_no_display is true:
  //   - Renders 'm_warmup_frames' frames without timing
  //   - Renders 'm_timed_frames' frames for benchmarking
  //   OR
  //   - Renders 'm_warmup_time' seconds without timing
  //   - Renders 'm_timed_time' seconds for benchmarking
  //   - Prints results to screen using sutilPrintBenchmark.
  //   - If m_save_frames_to_file is set, prints one copy of frame to file:
  //     ${m_title}.ppm. m_title is set to m_save_frames_basename if non-empty.
  static void runBenchmarkNoDisplay();
  
  // Set the current continuous drawing mode, while preserving the app's choice.
  static void setCurContinuousMode(contDraw_E continuous_mode);

  // Cleans up the rendering context and quits.  If there wasn't error cleaning up, the 
  // return code is passed out, otherwise 2 is used as the return code.
  static void quit(int return_code=0);

  // Glut callbacks
  static void idle();
  static void display();
  static void keyPressed(unsigned char key, int x, int y);
  static void mouseButton(int button, int state, int x, int y);
  static void mouseMotion(int x, int y);
  static void resize(int width, int height);

  static Mouse*         m_mouse;
  static PinholeCamera* m_camera;
  static SampleScene*   m_scene;

  static double         m_last_frame_time;
  static unsigned int   m_last_frame_count;
  static unsigned int   m_frame_count;

  static bool           m_display_fps;
  static double         m_fps_update_threshold;
  static char           m_fps_text[32];
  static optix::float3  m_text_color;
  static optix::float3  m_text_shadow_color;

  static bool           m_print_mem_usage;

  static contDraw_E     m_app_continuous_mode;
  static contDraw_E     m_cur_continuous_mode;
  static bool           m_display_frames;
  static bool           m_save_frames_to_file;
  static std::string    m_save_frames_basename;

  static std::string    m_camera_pose;

  static int            m_initial_window_width;
  static int            m_initial_window_height;

  static int            m_old_window_height;
  static int            m_old_window_width;
  static int            m_old_window_x;
  static int            m_old_window_y;
  static int            m_old_window_x_offset;
  static int            m_old_window_y_offset;

  static unsigned int   m_texId;
  static bool           m_sRGB_supported;
  static bool           m_use_sRGB;
  static bool           m_initialized;

  static bool           m_requires_display;
  static bool           m_benchmark_no_display;
  static unsigned int   m_warmup_frames;
  static unsigned int   m_timed_frames;
  static double         m_warmup_start; // time when the warmup started
  static double         m_warmup_time; // used instead of m_warmup_frames to specify a time to run instead of number of frames to run
  static double         m_benchmark_time; // like m_warmup_time, but for the time to benchmark
  static unsigned int   m_benchmark_frame_start;
  static double         m_benchmark_frame_time;
  static std::string    m_title;

  static double         m_progressive_timeout; // how long to do continuous rendering for progressive refinement (ignored when benchmarking or animating)
  static double         m_start_time; // time since continuous rendering last started

  static int            m_num_devices;

  static bool           m_enable_cpu_rendering; // enables CPU execution of OptiX programs
};
