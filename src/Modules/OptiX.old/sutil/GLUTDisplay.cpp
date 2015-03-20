
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


#if defined(__APPLE__)
#  include <GLUT/glut.h>
#  define GL_FRAMEBUFFER_SRGB_EXT           0x8DB9
#  define GL_FRAMEBUFFER_SRGB_CAPABLE_EXT   0x8DBA
#else
#  include <GL/glew.h>
#  if defined(_WIN32)
#    include <GL/wglew.h>
#  endif
#  include <GL/glut.h>
#endif

#include <GLUTDisplay.h>
#include <Mouse.h>
#include <DeviceMemoryLogger.h>

#include <optixu/optixu_math_stream_namespace.h>

#include <iostream>
#include <cstdlib>
#include <cstdio> //sprintf
#include <sstream>

// #define NVTX_ENABLE enables the nvToolsExt stuff from Nsight in NsightHelper.h
//#define NVTX_ENABLE

#include <NsightHelper.h>

using namespace optix;

//-----------------------------------------------------------------------------
// 
// GLUTDisplay class implementation 
//-----------------------------------------------------------------------------

Mouse*         GLUTDisplay::m_mouse                = 0;
PinholeCamera* GLUTDisplay::m_camera               = 0;
SampleScene*   GLUTDisplay::m_scene                = 0;

double         GLUTDisplay::m_last_frame_time      = 0.0;
unsigned int   GLUTDisplay::m_last_frame_count     = 0;
unsigned int   GLUTDisplay::m_frame_count          = 0;

bool           GLUTDisplay::m_display_fps          = true;
double         GLUTDisplay::m_fps_update_threshold = 0.5;
char           GLUTDisplay::m_fps_text[32];
float3         GLUTDisplay::m_text_color           = make_float3( 0.95f );
float3         GLUTDisplay::m_text_shadow_color    = make_float3( 0.10f );

bool           GLUTDisplay::m_print_mem_usage      = false;

GLUTDisplay::contDraw_E GLUTDisplay::m_app_continuous_mode = CDNone;
GLUTDisplay::contDraw_E GLUTDisplay::m_cur_continuous_mode = CDNone;

bool           GLUTDisplay::m_display_frames       = true;
bool           GLUTDisplay::m_save_frames_to_file  = false;
std::string    GLUTDisplay::m_save_frames_basename = "";

std::string    GLUTDisplay::m_camera_pose          = "";

int            GLUTDisplay::m_initial_window_width  = -1;
int            GLUTDisplay::m_initial_window_height = -1;

int            GLUTDisplay::m_old_window_height    = -1;
int            GLUTDisplay::m_old_window_width     = -1;
int            GLUTDisplay::m_old_window_x         = -1;
int            GLUTDisplay::m_old_window_y         = -1;
int            GLUTDisplay::m_old_window_x_offset  = -1;
int            GLUTDisplay::m_old_window_y_offset  = -1;

unsigned int   GLUTDisplay::m_texId                = 0;
bool           GLUTDisplay::m_sRGB_supported       = false;
bool           GLUTDisplay::m_use_sRGB             = false;

bool           GLUTDisplay::m_initialized          = false;
bool           GLUTDisplay::m_requires_display     = false;
bool           GLUTDisplay::m_benchmark_no_display = false;
unsigned int   GLUTDisplay::m_warmup_frames        = 50u;
unsigned int   GLUTDisplay::m_timed_frames         = 100u;
double         GLUTDisplay::m_warmup_start         = 0;
double         GLUTDisplay::m_warmup_time          = 10.0;
double         GLUTDisplay::m_benchmark_time       = 10.0;
unsigned int   GLUTDisplay::m_benchmark_frame_start= 0;
double         GLUTDisplay::m_benchmark_frame_time = 0;
std::string    GLUTDisplay::m_title                = "";

double         GLUTDisplay::m_progressive_timeout   = -1.;
double         GLUTDisplay::m_start_time           = 0.0;

int            GLUTDisplay::m_num_devices          = 0;

bool           GLUTDisplay::m_enable_cpu_rendering = false;



inline void removeArg( int& i, int& argc, char** argv ) 
{
  char* disappearing_arg = argv[i];
  for(int j = i; j < argc-1; ++j) {
    argv[j] = argv[j+1];
  }
  argv[argc-1] = disappearing_arg;
  --argc;
  --i;
}

void GLUTDisplay::printUsage()
{
  std::cerr
    << "Standard options:\n"
    << "  -d  | --dim=<width>x<height>               Set image dimensions, e.g. --dim=300x300 or -d=300x300\n"
    << "  -D  | --num-devices=<num_devices>          Set desired number of GPUs\n"
    << " -CPU | --enable-cpu                         Enable CPU execution of OptiX programs.  The number of threads can be set with --num-devices.\n"
    << "  -p  | --pose=\"[<eye>][<lookat>][<up>]vfov\" Camera pose, e.g. --pose=\"[0,0,-1][0,0,0][0,1,0]45.0\" or -p=\"[0,0,-1][0,0,0][0,1,0]45.0\"\n"
    << "  -s  | --save-frames[=<file_basename>]      Save each frame to frame_XXXX.ppm or file_basename_XXXX.ppm\n"
    << "  -N  | --no-display                         Don't display the image to the GLUT window\n"
    << "  -M  | --mem-usage                          Print memory usage after every frame\n"
    << "  -b  | --benchmark[=<w>x<t>]                Render and display 'w' warmup and 't' timing frames, then exit\n"
    << "  -bb | --timed-benchmark=<w>x<t>            Render and display 'w' warmup and 't' timing seconds, then exit\n";
  if ( !GLUTDisplay::m_requires_display )
  {
    std::cerr
      << "  -B  | --benchmark-no-display=<w>x<t>       Render 'w' warmup and 't' timing frames, then exit\n"
      << "  -BB | --timed-benchmark-no-display=<w>x<t> Render 'w' warmup and 't' timing seconds, then exit\n";
  }
  std::cerr << std::endl;

  std::cerr
    << "Standard mouse interaction:\n"
    << "  left mouse           Camera Rotate/Orbit (when interactive)\n"
    << "  middle mouse         Camera Pan/Truck (when interactive)\n"
    << "  right mouse          Camera Dolly (when interactive)\n"
    << "  right mouse + shift  Camera FOV (when interactive)\n"
    << std::endl;

  std::cerr
    << "Standard keystrokes:\n"
    << "  q Quit\n"
    << "  f Toggle full screen\n"
    << "  r Toggle continuous mode (progressive refinement, animation, or benchmark)\n"
    << "  R Set progressive refinement to never timeout and toggle continuous mode\n"
    << "  b Start/stop a benchmark\n"
    << "  d Toggle frame rate display\n"
    << "  s Save a frame to 'out.ppm'\n"
    << "  m Toggle memory usage printing\n"
    << "  c Print camera pose\n"
    << std::endl;
}

void GLUTDisplay::init( int& argc, char** argv )
{
  m_initialized = true;

  for (int i = 1; i < argc; ++i ) {
    std::string arg( argv[i] );
    if ( arg == "-s" || arg == "--save-frames" ) {
      m_save_frames_to_file = true;
      removeArg( i, argc, argv );
    } else if ( arg.substr( 0, 3 ) == "-s=" || arg.substr( 0, 14 )  == "--save-frames=" ) {
      m_save_frames_to_file = true;
      m_save_frames_basename = arg.substr( arg.find_first_of( '=' ) + 1 );
      removeArg( i, argc, argv );
    } else if ( arg == "-N" || arg == "--no-display" ) {
      m_display_frames = false;
      removeArg( i, argc, argv );
    } else if ( arg == "-M" || arg == "--mem-usage" ) {
      m_print_mem_usage = true;
      removeArg( i, argc, argv );
    } else if ( arg.substr( 0, 3 ) == "-p=" || arg.substr( 0, 7 ) == "--pose=" ) {
      m_camera_pose = arg.substr( arg.find_first_of( '=' ) + 1 );
      std::cerr << " got <<" << m_camera_pose << ">>" << std::endl;
      removeArg( i, argc, argv );
    } else if( arg.substr( 0, 3) == "-D=" || arg.substr( 0, 14 ) == "--num-devices=" ) {
      std::string arg_value = arg.substr( arg.find_first_of( '=' ) + 1 );
      m_num_devices = atoi(arg_value.c_str());
      if ( m_num_devices < 1 ) {
        std::cerr << "Invalid num devices: '" << arg_value << "'" << std::endl;
        printUsage();
        quit(1);
      }
      removeArg( i, argc, argv );
    } else if ( arg == "-CPU" || arg == "--enable-cpu" ) {
      m_enable_cpu_rendering = true;
      removeArg( i, argc, argv );
    } else if( arg.substr( 0, 3) == "-d=" || arg.substr( 0, 6 ) == "--dim=" ) {
      std::string arg_value = arg.substr( arg.find_first_of( '=' ) + 1 );
      unsigned int width, height;
      if ( sutilParseImageDimensions( arg_value.c_str(), &width, &height ) != RT_SUCCESS ) {
        std::cerr << "Invalid window dimensions: '" << arg_value << "'" << std::endl;
        printUsage();
        quit(1);
      }
      m_initial_window_width = width;
      m_initial_window_height = height;
      removeArg( i, argc, argv );
    } else if ( arg == "-b" || arg == "--benchmark" ) {
      m_app_continuous_mode = CDBenchmark;
      removeArg( i, argc, argv );
    } else if ( (arg == "-B" || arg == "--benchmark-no-display") && !GLUTDisplay::m_requires_display ) {
      m_cur_continuous_mode = CDBenchmark;
      m_benchmark_no_display = true;
      removeArg( i, argc, argv );
    } else if ( arg == "-bb" || arg == "--timed-benchmark" ) {
      m_app_continuous_mode = CDBenchmarkTimed;
      removeArg( i, argc, argv );
    } else if ( (arg == "-BB" || arg == "--timed-benchmark-no-display") && !GLUTDisplay::m_requires_display ) {
      m_cur_continuous_mode = CDBenchmarkTimed;
      m_benchmark_no_display = true;
      removeArg( i, argc, argv );
    } else if ( arg.substr( 0, 3 ) == "-b=" || arg.substr( 0, 12 ) == "--benchmark=" ) {
      m_app_continuous_mode = CDBenchmark;
      std::string bnd_args = arg.substr( arg.find_first_of( '=' ) + 1 );
      if ( sutilParseImageDimensions( bnd_args.c_str(), &m_warmup_frames, &m_timed_frames ) != RT_SUCCESS ) {
        std::cerr << "Invalid --benchmark arguments: '" << bnd_args << "'" << std::endl;
        printUsage();
        quit(1);
      }
      removeArg( i, argc, argv );
    } else if ( arg.substr( 0, 3) == "-B=" || arg.substr( 0, 23 ) == "--benchmark-no-display=" ) {
      m_cur_continuous_mode = CDBenchmark;
      m_benchmark_no_display = true;
      std::string bnd_args = arg.substr( arg.find_first_of( '=' ) + 1 );
      if ( sutilParseImageDimensions( bnd_args.c_str(), &m_warmup_frames, &m_timed_frames ) != RT_SUCCESS ) {
        std::cerr << "Invalid --benchmark-no-display arguments: '" << bnd_args << "'" << std::endl;
        printUsage();
        quit(1);
      }
      removeArg( i, argc, argv );
    } else if ( arg.substr( 0, 4) == "-bb=" || arg.substr( 0, 18 ) == "--timed-benchmark=" ) {
      m_app_continuous_mode = CDBenchmarkTimed;
      std::string bnd_args = arg.substr( arg.find_first_of( '=' ) + 1 );
      if ( sutilParseFloatDimensions( bnd_args.c_str(), &m_warmup_time, &m_benchmark_time ) != RT_SUCCESS) {
        std::cerr << "Invalid --timed-benchmark (-bb) arguments: '" << bnd_args << "'" << std::endl;
        printUsage();
        quit(1);
      }
      removeArg( i, argc, argv );
    } else if ( arg.substr( 0, 4) == "-BB=" || arg.substr( 0, 29 ) == "--timed-benchmark-no-display=" ) {
      m_cur_continuous_mode = CDBenchmarkTimed;
      m_benchmark_no_display = true;
      std::string bnd_args = arg.substr( arg.find_first_of( '=' ) + 1 );
      if ( sutilParseFloatDimensions( bnd_args.c_str(), &m_warmup_time, &m_benchmark_time ) != RT_SUCCESS ) {
        std::cerr << "Invalid --timed-benchmark-no-display (-BB) arguments: '" << bnd_args << "'" << std::endl;
        printUsage();
        quit(1);
      }
      removeArg( i, argc, argv );
    }
  }

  if (!m_benchmark_no_display)
  {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  }
}

void GLUTDisplay::run( const std::string& title, SampleScene* scene, contDraw_E continuous_mode )
{
  if ( !m_initialized ) {
    std::cerr << "ERROR - GLUTDisplay::run() called before GLUTDisplay::init()" << std::endl;
    exit(2);
  }
  m_scene = scene;
  m_title = title;
  m_scene->enableCPURendering(m_enable_cpu_rendering);
  m_scene->setNumDevices( m_num_devices );

  if( m_benchmark_no_display ) {
    runBenchmarkNoDisplay();
    quit(0);
  }

  if( m_print_mem_usage ) {
    DeviceMemoryLogger::logDeviceDescription(m_scene->getContext(), std::cerr);
    DeviceMemoryLogger::logCurrentMemoryUsage(m_scene->getContext(), std::cerr, "Initial memory available: " );
    std::cerr << std::endl;
  }

  // Initialize GLUT and GLEW first. Now initScene can use OpenGL and GLEW.
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  if( m_initial_window_width > 0 && m_initial_window_height > 0)
    glutInitWindowSize( m_initial_window_width, m_initial_window_height );
  else
    glutInitWindowSize( 128, 128 );
  glutInitWindowPosition(100,100);
  glutCreateWindow( m_title.c_str() );
  glutHideWindow();
#if !defined(__APPLE__)
  glewInit();
  if (glewIsSupported( "GL_EXT_texture_sRGB GL_EXT_framebuffer_sRGB")) {
    m_sRGB_supported = true;
  }
#else
  m_sRGB_supported = true;
#endif
#if defined(_WIN32)
  // Turn off vertical sync
  wglSwapIntervalEXT(0);
#endif

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  // If m_app_continuous_mode was already set to CDBenchmark* on the command line then preserve it.
  setContinuousMode( m_app_continuous_mode == CDNone ? continuous_mode : m_app_continuous_mode );

  int buffer_width;
  int buffer_height;
  try {
    // Set up scene
    SampleScene::InitialCameraData camera_data;
    m_scene->initScene( camera_data );

    if( m_initial_window_width > 0 && m_initial_window_height > 0)
      m_scene->resize( m_initial_window_width, m_initial_window_height );

    if ( !m_camera_pose.empty() )
      camera_data = SampleScene::InitialCameraData( m_camera_pose );

    // Initialize camera according to scene params
    m_camera = new PinholeCamera( camera_data.eye,
                                 camera_data.lookat,
                                 camera_data.up,
                                 -1.0f, // hfov is ignored when using keep vertical
                                 camera_data.vfov,
                                 PinholeCamera::KeepVertical );

    Buffer buffer = m_scene->getOutputBuffer();
    RTsize buffer_width_rts, buffer_height_rts;
    buffer->getSize( buffer_width_rts, buffer_height_rts );
    buffer_width  = static_cast<int>(buffer_width_rts);
    buffer_height = static_cast<int>(buffer_height_rts);
    m_mouse = new Mouse( m_camera, buffer_width, buffer_height );
  } catch( Exception& e ){
    sutilReportError( e.getErrorString().c_str() );
    exit(2);
  }

  // Initialize state
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 1, 0, 1, -1, 1 );
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport(0, 0, buffer_width, buffer_height);

  glutShowWindow();

  // reshape window to the correct window resize
  glutReshapeWindow( buffer_width, buffer_height);

  // Set callbacks
  glutKeyboardFunc(keyPressed);
  glutDisplayFunc(display);
  glutMouseFunc(mouseButton);
  glutMotionFunc(mouseMotion);
  glutReshapeFunc(resize);

  // Initialize timer
  sutilCurrentTime( &m_last_frame_time );
  m_frame_count = 0;
  m_last_frame_count = 0;
  m_start_time = m_last_frame_time;
  if( m_cur_continuous_mode == CDBenchmarkTimed ) {
    m_warmup_start = m_last_frame_time;
    m_warmup_frames = 0;
    m_timed_frames = 0;
  }
  m_benchmark_frame_start = 0;

  //Calculate window position offset
  m_old_window_x_offset = glutGet(GLUT_INIT_WINDOW_X) - glutGet(GLUT_WINDOW_X);
  m_old_window_y_offset = glutGet(GLUT_INIT_WINDOW_Y) - glutGet(GLUT_WINDOW_Y);
  
  // Enter main loop
  glutMainLoop();
}

void GLUTDisplay::setCamera(SampleScene::InitialCameraData& camera_data)
{
  m_camera->setParameters(camera_data.eye,
                         camera_data.lookat,
                         camera_data.up,
                         camera_data.vfov, 
                         camera_data.vfov,
                         PinholeCamera::KeepVertical );
  glutPostRedisplay();  
}

// This is an internal function that does the actual work.
void GLUTDisplay::setCurContinuousMode(contDraw_E continuous_mode)
{
  m_cur_continuous_mode = continuous_mode;

  sutilCurrentTime( &m_start_time );
  glutIdleFunc( m_cur_continuous_mode!=CDNone ? idle : 0 );
  glutPostRedisplay();
}

// This is an API function for restaring the progressive timeout timer. 
void GLUTDisplay::restartProgressiveTimer()
{
  // Unless the user has overridden it, progressive implies a finite continuous drawing timeout.
  if(m_app_continuous_mode == CDProgressive && m_progressive_timeout < 0.0) {
    m_progressive_timeout = 10.0;
  }
}

// This is an API function for the app to specify its desired mode.
void GLUTDisplay::setContinuousMode(contDraw_E continuous_mode)
{
  m_app_continuous_mode = continuous_mode;

  // Unless the user has overridden it, progressive implies a finite continuous drawing timeout.
  restartProgressiveTimer();

  setCurContinuousMode(m_app_continuous_mode);
}

void GLUTDisplay::postRedisplay()
{
  glutPostRedisplay();
}

void GLUTDisplay::drawText( const std::string& text, float x, float y, void* font )
{
  // Save state
  glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT );

  glDisable( GL_TEXTURE_2D );
  glDisable( GL_LIGHTING );
  glDisable( GL_DEPTH_TEST);

  glColor3fv( &( m_text_shadow_color.x) ); // drop shadow
  // Shift shadow one pixel to the lower right.
  glWindowPos2f(x + 1.0f, y - 1.0f);
  for( std::string::const_iterator it = text.begin(); it != text.end(); ++it )
    glutBitmapCharacter( font, *it );

  glColor3fv( &( m_text_color.x) );        // main text
  glWindowPos2f(x, y);
  for( std::string::const_iterator it = text.begin(); it != text.end(); ++it )
    glutBitmapCharacter( font, *it );

  // Restore state
  glPopAttrib();
}

void GLUTDisplay::runBenchmarkNoDisplay( )
{
  // Set up scene
  SampleScene::InitialCameraData initial_camera_data;
  m_scene->setUseVBOBuffer( false );
  m_scene->initScene( initial_camera_data );


  if( m_initial_window_width > 0 && m_initial_window_height > 0)
    m_scene->resize( m_initial_window_width, m_initial_window_height );

  if ( !m_camera_pose.empty() )
    initial_camera_data = SampleScene::InitialCameraData( m_camera_pose );

  // Initialize camera according to scene params
  m_camera = new PinholeCamera( initial_camera_data.eye,
                               initial_camera_data.lookat,
                               initial_camera_data.up,
                               -1.0f, // hfov is ignored when using keep vertical
                               initial_camera_data.vfov,
                               PinholeCamera::KeepVertical );
  m_mouse = new Mouse( m_camera, m_initial_window_width, m_initial_window_height );
  m_mouse->handleResize( m_initial_window_width, m_initial_window_height );

  float3 eye, U, V, W;
  m_camera->getEyeUVW( eye, U, V, W );
  SampleScene::RayGenCameraData camera_data( eye, U, V, W );


  // Initial compilation
  double compilation_time = 0.0f;
  {
    double start_time, finish_time;
    sutilCurrentTime( &start_time );
    m_scene->getContext()->compile();
    sutilCurrentTime( &finish_time );
    compilation_time = finish_time - start_time;
  }

  // Accel build
  double accel_build_time = 0.0f;
  {
    double start_time, finish_time;
    sutilCurrentTime( &start_time );
    m_scene->getContext()->launch( 0, 0 );
    sutilCurrentTime( &finish_time );
    accel_build_time = finish_time - start_time;
  }
  printf( "PREPROCESS: %s | compile %g sec | accelbuild %g sec\n",
          m_title.c_str(),
          compilation_time,
          accel_build_time );
  fflush(stdout);

  
  // Warmup frames
  if ( m_cur_continuous_mode == CDBenchmarkTimed ) {
    // Count elapsed time
    double start_time, finish_time;
    sutilCurrentTime( &start_time );
    m_warmup_frames = 0;
    do
    {
      m_scene->trace( camera_data );
      sutilCurrentTime( &finish_time );
      m_warmup_frames++;
    } while( finish_time-start_time < m_warmup_time);
  } else {
    // Count frames
    for( unsigned int i = 0; i < m_warmup_frames; ++i ) {
      m_scene->trace( camera_data );
    }
  }

  // Timed frames
  double start_time, finish_time;
  sutilCurrentTime( &start_time );
  if ( m_cur_continuous_mode == CDBenchmarkTimed ) {
    // Count elapsed time
    m_timed_frames = 0;
    do
    {
      m_scene->trace( camera_data );
      sutilCurrentTime( &finish_time );
      m_timed_frames++;
    } while( finish_time-start_time < m_benchmark_time );
  } else
  {
    // Count frames
    for( unsigned int i = 0; i < m_timed_frames; ++i ) {
      m_scene->trace( camera_data );
    }
    sutilCurrentTime( &finish_time );
  }

  // Save image if necessary
  if( m_save_frames_to_file ) {
    std::string filename = m_save_frames_basename.empty() ?  m_title + ".ppm" : m_save_frames_basename+ ".ppm"; 
    Buffer buffer = m_scene->getOutputBuffer();
    sutilDisplayFilePPM( filename.c_str(), buffer->get() );
  }

  double total_time = finish_time-start_time;
  sutilPrintBenchmark( m_title.c_str(), total_time, m_warmup_frames, m_timed_frames);
}

void GLUTDisplay::keyPressed(unsigned char key, int x, int y)
{
  try {
    if( m_scene->keyPressed(key, x, y) ) {
      glutPostRedisplay();
      return;
    }
  } catch( Exception& e ){
    sutilReportError( e.getErrorString().c_str() );
    exit(2);
  }

  switch (key) {
  case 27: // esc
  case 'q':
    quit();
  case 'f':
    if ( m_old_window_width == -1) { // We are in non-fullscreen mode
      m_old_window_width  = glutGet(GLUT_WINDOW_WIDTH);
      m_old_window_height = glutGet(GLUT_WINDOW_HEIGHT);
      m_old_window_x      = glutGet(GLUT_WINDOW_X) + m_old_window_x_offset;
      m_old_window_y      = glutGet(GLUT_WINDOW_Y) + m_old_window_y_offset;
      glutFullScreen();
    } else { // We are in fullscreen mode
      glutPositionWindow( m_old_window_x, m_old_window_y );
      glutReshapeWindow( m_old_window_width, m_old_window_height );
      m_old_window_width = m_old_window_height = -1;
    }
    glutPostRedisplay();
    break;

  case 'R':
    setProgressiveDrawingTimeout(0.0);
    // Fall through

  case 'r':
    if(m_app_continuous_mode == CDProgressive) {
      if(m_cur_continuous_mode == CDProgressive) {
        setCurContinuousMode(CDNone);
      } else if(m_cur_continuous_mode == CDNone) {
        setCurContinuousMode(CDProgressive);
      }
      break;
    }
    if(m_app_continuous_mode == CDAnimated) {
      if(m_cur_continuous_mode == CDAnimated) {
        setCurContinuousMode(CDNone);
      } else if(m_cur_continuous_mode == CDNone) {
        setCurContinuousMode(CDAnimated);
      }
      break;
    }
    // Fall through to benchmark mode if the app hasn't specified a kind of continuous to do

  case 'b':
    if(m_cur_continuous_mode == CDBenchmarkTimed) {
      // Turn off the benchmark and print the results
      double current_time;
      sutilCurrentTime(&current_time);
      double total_time = current_time-m_benchmark_frame_time;
      sutilPrintBenchmark(m_title.c_str(), total_time, m_warmup_frames, m_timed_frames);
      setCurContinuousMode(m_app_continuous_mode);
    } else {
      // Turn on the benchmark and set continuous rendering
      std::cerr << "Benchmark started. Press 'b' again to end.\n";
      setCurContinuousMode(CDBenchmarkTimed);
      m_benchmark_time = 1e37f; // Do a timed benchmark, but forever.
      m_benchmark_frame_start = m_frame_count;

      double current_time;
      sutilCurrentTime(&current_time);
      m_warmup_start = current_time;
      m_benchmark_frame_time = current_time;
      m_warmup_frames = 0;
      m_warmup_time = 0;
      m_timed_frames = 0;
    }
    break;

  case 'd':
    m_display_fps = !m_display_fps;
    break;

  case 's':
    sutilDisplayFilePPM( "out.ppm", m_scene->getOutputBuffer()->get() );
    break;

  case 'm':
    m_print_mem_usage =  !m_print_mem_usage;
    glutPostRedisplay();
    break;

  case 'c':
    float3 eye, lookat, up;
    float hfov, vfov;

    m_camera->getEyeLookUpFOV(eye, lookat, up, hfov, vfov);
    std::cerr << '"' << eye << lookat << up << vfov << '"' << std::endl;
    break;

    case '[':
      m_scene->incrementCPUThreads(-1);
      break;
      
    case ']':
      m_scene->incrementCPUThreads(1);
      break;



  default:
    return;
  }
}


void GLUTDisplay::mouseButton(int button, int state, int x, int y)
{
  sutilCurrentTime( &m_start_time );
  m_mouse->handleMouseFunc( button, state, x, y, glutGetModifiers() );
  if ( state != GLUT_UP )
    m_scene->signalCameraChanged();
  glutPostRedisplay();
}


void GLUTDisplay::mouseMotion(int x, int y)
{
  sutilCurrentTime( &m_start_time );
  m_mouse->handleMoveFunc( x, y );
  m_scene->signalCameraChanged();
  if (m_app_continuous_mode == CDProgressive) {
    setCurContinuousMode(CDProgressive);
  }
  glutPostRedisplay();
}


void GLUTDisplay::resize(int width, int height)
{
  // disallow size 0
  width  = max(1, width);
  height = max(1, height);

  sutilCurrentTime( &m_start_time );
  m_scene->signalCameraChanged();
  m_mouse->handleResize( width, height );

  try {
    m_scene->resize(width, height);
  } catch( Exception& e ){
    sutilReportError( e.getErrorString().c_str() );
    exit(2);
  }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 1, 0, 1, -1, 1);
  glViewport(0, 0, width, height);
  if (m_app_continuous_mode == CDProgressive) {
    setCurContinuousMode(CDProgressive);
  }
  glutPostRedisplay();
}


void GLUTDisplay::idle()
{
  glutPostRedisplay();
}


void GLUTDisplay::displayFrame()
{
  GLboolean sRGB = GL_FALSE;
  if (m_use_sRGB && m_sRGB_supported) {
    glGetBooleanv( GL_FRAMEBUFFER_SRGB_CAPABLE_EXT, &sRGB );
    if (sRGB) {
      glEnable(GL_FRAMEBUFFER_SRGB_EXT);
    }
  }

  // Draw the resulting image
  Buffer buffer = m_scene->getOutputBuffer(); 
  RTsize buffer_width_rts, buffer_height_rts;
  buffer->getSize( buffer_width_rts, buffer_height_rts );
  int buffer_width  = static_cast<int>(buffer_width_rts);
  int buffer_height = static_cast<int>(buffer_height_rts);
  RTformat buffer_format = buffer->getFormat();

  if( m_save_frames_to_file ) {
    static char fname[128];
    std::string basename = m_save_frames_basename.empty() ? "frame" : m_save_frames_basename;
    sprintf(fname, "%s_%05d.ppm", basename.c_str(), m_frame_count);
    sutilDisplayFilePPM( fname, buffer->get() );
  }

  unsigned int vboId = 0;
  if( m_scene->usesVBOBuffer() )
    vboId = buffer->getGLBOId();

  if (vboId)
  {
    if (!m_texId)
    {
      glGenTextures( 1, &m_texId );
      glBindTexture( GL_TEXTURE_2D, m_texId);

      // Change these to GL_LINEAR for super- or sub-sampling
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

      // GL_CLAMP_TO_EDGE for linear filtering, not relevant for nearest.
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

      glBindTexture( GL_TEXTURE_2D, 0);
    }

    glBindTexture( GL_TEXTURE_2D, m_texId );

    // send pbo to texture
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, vboId);

    RTsize elementSize = buffer->getElementSize();
    if      ((elementSize % 8) == 0) glPixelStorei(GL_UNPACK_ALIGNMENT, 8);
    else if ((elementSize % 4) == 0) glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    else if ((elementSize % 2) == 0) glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
    else                             glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    {nvtx::ScopedRange r( "glTexImage" );
    if(buffer_format == RT_FORMAT_UNSIGNED_BYTE4) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, buffer_width, buffer_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);
    } else if(buffer_format == RT_FORMAT_FLOAT4) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, buffer_width, buffer_height, 0, GL_RGBA, GL_FLOAT, 0);
    } else if(buffer_format == RT_FORMAT_FLOAT3) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F_ARB, buffer_width, buffer_height, 0, GL_RGB, GL_FLOAT, 0);
    } else if(buffer_format == RT_FORMAT_FLOAT) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE32F_ARB, buffer_width, buffer_height, 0, GL_LUMINANCE, GL_FLOAT, 0);
    } else {
      assert(0 && "Unknown buffer format");
    }
    }
    glBindBuffer( GL_PIXEL_UNPACK_BUFFER, 0 );

    glEnable(GL_TEXTURE_2D);

    // Initialize offsets to pixel center sampling.

    float u = 0.5f/buffer_width;
    float v = 0.5f/buffer_height;

    glBegin(GL_QUADS);
    glTexCoord2f(u, v);
    glVertex2f(0.0f, 0.0f);
    glTexCoord2f(1.0f, v);
    glVertex2f(1.0f, 0.0f);
    glTexCoord2f(1.0f - u, 1.0f - v);
    glVertex2f(1.0f, 1.0f);
    glTexCoord2f(u, 1.0f - v);
    glVertex2f(0.0f, 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
  } else {
    GLvoid* imageData = buffer->map();
    assert( imageData );

    GLenum gl_data_type = GL_FALSE;
    GLenum gl_format = GL_FALSE;

    switch (buffer_format) {
          case RT_FORMAT_UNSIGNED_BYTE4:
            gl_data_type = GL_UNSIGNED_BYTE;
            gl_format    = GL_BGRA;
            break;

          case RT_FORMAT_FLOAT:
            gl_data_type = GL_FLOAT;
            gl_format    = GL_LUMINANCE;
            break;

          case RT_FORMAT_FLOAT3:
            gl_data_type = GL_FLOAT;
            gl_format    = GL_RGB;
            break;

          case RT_FORMAT_FLOAT4:
            gl_data_type = GL_FLOAT;
            gl_format    = GL_RGBA;
            break;

          default:
            fprintf(stderr, "Unrecognized buffer data type or format.\n");
            exit(2);
            break;
    }

    RTsize elementSize = buffer->getElementSize();
    int align = 1;
    if      ((elementSize % 8) == 0) align = 8; 
    else if ((elementSize % 4) == 0) align = 4;
    else if ((elementSize % 2) == 0) align = 2;
    glPixelStorei(GL_UNPACK_ALIGNMENT, align);

    NVTX_RangePushA("glDrawPixels");
    glDrawPixels( static_cast<GLsizei>( buffer_width ), static_cast<GLsizei>( buffer_height ),
      gl_format, gl_data_type, imageData);
    NVTX_RangePop();

    buffer->unmap();
  }
  if (m_use_sRGB && m_sRGB_supported && sRGB) {
    glDisable(GL_FRAMEBUFFER_SRGB_EXT);
  }
}

void GLUTDisplay::display()
{
  if( m_cur_continuous_mode == CDProgressive && m_progressive_timeout > 0.0 ) {
    // If doing progressive refinement, see if we're done
    double current_time;
    sutilCurrentTime( &current_time );
    if( current_time - m_start_time > m_progressive_timeout ) {
      setCurContinuousMode( CDNone );
      return;
    }
  }

  try {
    // render the scene
    float3 eye, U, V, W;
    m_camera->getEyeUVW( eye, U, V, W );
    // Don't be tempted to just start filling in the values outside of a constructor, 
    // because if you add a parameter it's easy to forget to add it here.
    SampleScene::RayGenCameraData camera_data( eye, U, V, W );
    {nvtx::ScopedRange r( "trace" );
    m_scene->trace( camera_data );
    }

    // Always count rendered frames
    ++m_frame_count;

    // Not strictly necessary
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    if( m_display_frames ) {
      nvtx::ScopedRange r( "displayFrame" );
      displayFrame();
    }
  } catch( Exception& e ){
    sutilReportError( e.getErrorString().c_str() );
    exit(2);
  }

  // Do not draw text on 1st frame -- issue on linux causes problems with 
  // glDrawPixels call if drawText glutBitmapCharacter is called on first frame.
  if ( m_display_fps && m_cur_continuous_mode != CDNone && m_frame_count > 1 ) {
    // Output fps 
    double current_time;
    sutilCurrentTime( &current_time );
    double dt = current_time - m_last_frame_time;
    if( dt > m_fps_update_threshold ) {
      sprintf( m_fps_text, "fps: %7.2f", (m_frame_count - m_last_frame_count) / dt );

      m_last_frame_time = current_time;
      m_last_frame_count = m_frame_count;
    } else if( m_frame_count == 1 ) {
      sprintf( m_fps_text, "fps: %7.2f", 0.f );
    }

    drawText( m_fps_text, 10.0f, 10.0f, GLUT_BITMAP_8_BY_13 );
  }

  if( m_print_mem_usage ) {
    // Output memory
    std::ostringstream str;
    DeviceMemoryLogger::logCurrentMemoryUsage(m_scene->getContext(), str);
    drawText( str.str(), 10.0f, 26.0f, GLUT_BITMAP_8_BY_13 );
  }

  //printf("finished frame: %d\n", m_frame_count);
  if( m_cur_continuous_mode == CDBenchmark || m_cur_continuous_mode == CDBenchmarkTimed ) {
    double current_time;
    sutilCurrentTime(&current_time);

    // Do the timed frames first, since m_benchmark_frame_time may be set by the warmup
    // section below and we don't want to double count the frames.
    if ( m_cur_continuous_mode == CDBenchmarkTimed ) {
      // Count elapsed time, but only if we have moved out of the warmup phase.
      if (m_benchmark_frame_time > 0) {
        m_timed_frames++;
        //printf("_timed_frames = %d\n", m_timed_frames);
        double total_time = current_time-m_benchmark_frame_time;
        if ( total_time > m_benchmark_time ) {
          sutilPrintBenchmark(m_title.c_str(), total_time, m_warmup_frames, m_timed_frames);
          setCurContinuousMode( CDNone );
          quit(0); // We only get here for command line benchmarks, which always end.
        }
      }
    } else {
      // Count frames
      if(m_frame_count == m_benchmark_frame_start+m_warmup_frames+m_timed_frames) {
        double total_time = current_time-m_benchmark_frame_time;
        sutilPrintBenchmark(m_title.c_str(), total_time, m_warmup_frames, m_timed_frames);
        setCurContinuousMode( CDNone );
        quit(0); // We only get here for command line benchmarks, which always end.
      }
    }

    if ( m_cur_continuous_mode == CDBenchmarkTimed ) {
      if ( current_time-m_warmup_start < m_warmup_time) {
        // Under the alloted time, keep counting
        m_warmup_frames++;
        //printf("_warmup_frames = %d\n", m_warmup_frames);
      } else {
        // Over the alloted time, set the m_benchmark_frame_time if it hasn't been set yet.
        if (m_benchmark_frame_time == 0) {
          m_benchmark_frame_time = current_time;
          // Make sure we account for that last frame
          m_warmup_frames++;
          //printf("warmup done (m_warmup_frames = %d) after %g seconds.\n", m_warmup_frames, current_time-m_warmup_start);
        }
      }
    } else {
      // Count frames
      if(m_frame_count-1 == m_benchmark_frame_start+m_warmup_frames) {
        m_benchmark_frame_time = current_time; // Start timing.
      }
    }
  }

  {nvtx::ScopedRange r( "glutSwapBuffers" );
    // Swap buffers
    glutSwapBuffers();
  }
}

void GLUTDisplay::quit(int return_code)
{
  try {
    if(m_scene)
    {
      m_scene->cleanUp();
      if (m_scene->getContext().get() != 0)
      {
        sutilReportError( "Derived scene class failed to call SampleScene::cleanUp()" );
        exit(2);
      }
    }
    exit(return_code);
  } catch( Exception& e ) {
    sutilReportError( e.getErrorString().c_str() );
    exit(2);
  }
}
