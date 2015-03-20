
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

#include <sutil.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_matrix_namespace.h>

class PinholeCamera;


//-----------------------------------------------------------------------------
// 
// Mouse class -- handles user mouse events. This class defines the mouse
//                interaction that is modeled off of Maya.
//
//-----------------------------------------------------------------------------

class Mouse {
public:
  SUTILAPI Mouse(PinholeCamera* camera, int xres, int yres);
  SUTILAPI void handleMouseFunc(int button, int state, int x, int y, int modifier);
  SUTILAPI void handleMoveFunc(int x, int y);
  SUTILAPI void handlePassiveMotionFunc(int x, int y);
  SUTILAPI void handleResize(int new_xres, int new_yres);

private:
  struct InteractionState {
    InteractionState() {}
    InteractionState(int modifier, int button, int state)
      : modifier(modifier), button(button), state(state)
    {}
    int modifier; // Shift,Ctrl,Alt
    int button;   // Left,Middle,Right
    int state;    // Down,Up
    int last_x, last_y;
    optix::float3 rotate_from;
  };

  void call_func(int x, int y);

  void fov(int x, int y);
  void translate(int x, int y);
  void dolly(int x, int y);
  void rotate(int x, int y);
  void track_and_pan(int x, int y);
  void track(int x, int y);
  void pan(int x, int y);

  // Data
  PinholeCamera* camera;
  InteractionState current_interaction;
  int xres, yres;
  float fov_speed;
  float dolly_speed;
  float translate_speed;
};


//-----------------------------------------------------------------------------
// 
// PinholeCamera -- performs view transformations 
//
//-----------------------------------------------------------------------------

class PinholeCamera {
  typedef optix::float3 float3;
  typedef optix::float2 float2;
public:
  enum AspectRatioMode {
    KeepVertical,
    KeepHorizontal,
    KeepNone
  };

  SUTILAPI PinholeCamera(float3 eye, float3 lookat, float3 up, float hfov=60, float vfov=60,
                         AspectRatioMode arm = KeepVertical);

  SUTILAPI void setup();
  
  SUTILAPI void getEyeUVW(float3& eye, float3& U, float3& V, float3& W);

  SUTILAPI void getEyeLookUpFOV(float3& eye, float3& lookat, float3& up, float& HFOV, float& VFOV);

  SUTILAPI void scaleFOV(float);
  SUTILAPI void translate(float2);
  SUTILAPI void dolly(float);
  SUTILAPI void transform( const optix::Matrix4x4& trans );
  SUTILAPI void setAspectRatio(float ratio);
  
  SUTILAPI void setParameters(float3 eye_in, float3 lookat_in, float3 up_in, float hfov_in, float vfov_in, PinholeCamera::AspectRatioMode aspectRatioMode_in);

  enum TransformCenter {
    LookAt,
    Eye,
    Origin
  };

  float3 eye, lookat, up;
  float hfov, vfov;
private:
  float3 lookdir, camera_u, camera_v;
  AspectRatioMode aspectRatioMode;
};
