
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

#include <Mouse.h>
#include <optixu/optixu_matrix_namespace.h>
#include <iostream>

# ifdef _WIN32
#   include <cfloat>
#   define ISFINITE _finite
# else
#   include <cmath>
#   define ISFINITE std::isfinite
# endif

#ifdef GLUT_FOUND
#  if defined(__APPLE__)
#    include <GLUT/glut.h>
#  else
#    include <GL/glut.h>
#  endif
#else
#  error "You in big trouble without the GLUT."
#endif

#define GLUT_MOTION 2


//-----------------------------------------------------------------------------
// 
// Helpers
//
//-----------------------------------------------------------------------------

using namespace optix;

namespace {

  /*
    Assigns src to dst if 
    src is not inf and nan!
    
    dst = isReal(src) ? src : dst;
  */

  float assignWithCheck( float& dst, const float &src )
  {
    if( ISFINITE( src ) ) {
      dst = src;
    }

    return dst;
  }

  /*
    Assigns src to dst if all src 
    components are neither inf nor nan!
    
    dst = isReal(src) ? src : dst;
  */

  float3 assignWithCheck( float3& dst, const float3 &src )
  {
    if( ISFINITE( src.x ) && ISFINITE( src.y ) && ISFINITE( src.z ) ) {
      dst = src;
    }

    return dst;
  }

  inline float DtoR(float d)
  {
    return d*(static_cast<float>(M_PI)/180.f);
  }


  inline float RtoD(float r)
  {
    return r*(180.f/static_cast<float>(M_PI));
  }


  inline float Clamp(float val, float min, float max)
  {
    return val > min ? (val < max ? val : max) : min;
  }


  float3 projectToSphere( float x, float y, float radius )
  {
    x /= radius;
    y /= radius;
    float rad2 = x*x+y*y;
    if(rad2 > 1.0f) {
      float rad = sqrt(rad2);
      x /= rad;
      y /= rad;
      return make_float3( x, y, 0.0f );
    } else {
      float z = sqrt(1-rad2);
      return make_float3( x, y, z );
    }
  }


  Matrix4x4 rotationMatrix( const float3& _to, const float3& _from ) 
  {
    float3 from = normalize( _from );
    float3 to   = normalize( _to );

    float3 v = cross(from, to);
    float  e = dot(from, to);
    if ( e > 1.0f-1.e-9f ) {
      return Matrix4x4::identity();
    } else {
      float h = 1.0f/(1.0f + e);
      float mtx[16];
      mtx[0] = e + h * v.x * v.x;
      mtx[1] = h * v.x * v.y + v.z;
      mtx[2] = h * v.x * v.z - v.y;
      mtx[3] = 0.0f;

      mtx[4] = h * v.x * v.y - v.z;
      mtx[5] = e + h * v.y * v.y;
      mtx[6] = h * v.y * v.z + v.x;
      mtx[7] = 0.0f; 

      mtx[8] = h * v.x * v.z + v.y;
      mtx[9] = h * v.y * v.z - v.x;
      mtx[10] = e + h * v.z * v.z;
      mtx[11] = 0.0f; 
      
      mtx[12] = 0.0f; 
      mtx[13] = 0.0f; 
      mtx[14] = 0.0f; 
      mtx[15] = 1.0f; 

      return Matrix4x4( mtx );
    }
  }

  Matrix4x4 initWithBasis( const float3& u,
                                 const float3& v,
                                 const float3& w,
                                 const float3& t )
  {
    float m[16];
    m[0] = u.x;
    m[1] = v.x;
    m[2] = w.x;
    m[3] = t.x;
    
    m[4] = u.y;
    m[5] = v.y;
    m[6] = w.y;
    m[7] = t.y;

    m[8] = u.z;
    m[9] = v.z;
    m[10] = w.z;
    m[11] = t.z;

    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;

    return Matrix4x4( m );
  }


  inline float det3 (float a, float b, float c,
                     float d, float e, float f,
                     float g, float h, float i)
  { return a*e*i + d*h*c + g*b*f - g*e*c - d*b*i - a*h*f; }


#define mm(i,j) m[i*4+j]
  float det4( const Matrix4x4& m )
  {
    float det;
    det  = mm(0,0) * det3(mm(1,1), mm(1,2), mm(1,3),
                          mm(2,1), mm(2,2), mm(2,3),
                          mm(3,1), mm(3,2), mm(3,3));
    det -= mm(0,1) * det3(mm(1,0), mm(1,2), mm(1,3),
                          mm(2,0), mm(2,2), mm(2,3),
                          mm(3,0), mm(3,2), mm(3,3));
    det += mm(0,2) * det3(mm(1,0), mm(1,1), mm(1,3),
                          mm(2,0), mm(2,1), mm(2,3),
                          mm(3,0), mm(3,1), mm(3,3));
    det -= mm(0,3) * det3(mm(1,0), mm(1,1), mm(1,2),
                          mm(2,0), mm(2,1), mm(2,2),
                          mm(3,0), mm(3,1), mm(3,2));
    return det;
  }

  Matrix4x4 inverse( const Matrix4x4& m )
  {
    Matrix4x4 inverse;
    float det = det4( m );

    inverse[0]  =  det3(mm(1,1), mm(1,2), mm(1,3),
                        mm(2,1), mm(2,2), mm(2,3),
                        mm(3,1), mm(3,2), mm(3,3)) / det;
    inverse[1]  = -det3(mm(0,1), mm(0,2), mm(0,3),
                        mm(2,1), mm(2,2), mm(2,3),
                        mm(3,1), mm(3,2), mm(3,3)) / det;
    inverse[2]  =  det3(mm(0,1), mm(0,2), mm(0,3),
                        mm(1,1), mm(1,2), mm(1,3),
                        mm(3,1), mm(3,2), mm(3,3)) / det;
    inverse[3]  = -det3(mm(0,1), mm(0,2), mm(0,3),
                        mm(1,1), mm(1,2), mm(1,3),
                        mm(2,1), mm(2,2), mm(2,3)) / det;

    inverse[4]  = -det3(mm(1,0), mm(1,2), mm(1,3),
                        mm(2,0), mm(2,2), mm(2,3),
                        mm(3,0), mm(3,2), mm(3,3)) / det;
    inverse[5]  =  det3(mm(0,0), mm(0,2), mm(0,3),
                        mm(2,0), mm(2,2), mm(2,3),
                        mm(3,0), mm(3,2), mm(3,3)) / det;
    inverse[6]  = -det3(mm(0,0), mm(0,2), mm(0,3),
                        mm(1,0), mm(1,2), mm(1,3),
                        mm(3,0), mm(3,2), mm(3,3)) / det;
    inverse[7]  =  det3(mm(0,0), mm(0,2), mm(0,3),
                        mm(1,0), mm(1,2), mm(1,3),
                        mm(2,0), mm(2,2), mm(2,3)) / det;

    inverse[8]  =  det3(mm(1,0), mm(1,1), mm(1,3),
                        mm(2,0), mm(2,1), mm(2,3),
                        mm(3,0), mm(3,1), mm(3,3)) / det;
    inverse[9]  = -det3(mm(0,0), mm(0,1), mm(0,3),
                        mm(2,0), mm(2,1), mm(2,3),
                        mm(3,0), mm(3,1), mm(3,3)) / det;
    inverse[10] =  det3(mm(0,0), mm(0,1), mm(0,3),
                        mm(1,0), mm(1,1), mm(1,3),
                        mm(3,0), mm(3,1), mm(3,3)) / det;
    inverse[11] = -det3(mm(0,0), mm(0,1), mm(0,3),
                        mm(1,0), mm(1,1), mm(1,3),
                        mm(2,0), mm(2,1), mm(2,3)) / det;

    inverse[12] = -det3(mm(1,0), mm(1,1), mm(1,2),
                        mm(2,0), mm(2,1), mm(2,2),
                        mm(3,0), mm(3,1), mm(3,2)) / det;
    inverse[13] =  det3(mm(0,0), mm(0,1), mm(0,2),
                        mm(2,0), mm(2,1), mm(2,2),
                        mm(3,0), mm(3,1), mm(3,2)) / det;
    inverse[14] = -det3(mm(0,0), mm(0,1), mm(0,2),
                        mm(1,0), mm(1,1), mm(1,2),
                        mm(3,0), mm(3,1), mm(3,2)) / det;
    inverse[15] =  det3(mm(0,0), mm(0,1), mm(0,2),
                        mm(1,0), mm(1,1), mm(1,2),
                        mm(2,0), mm(2,1), mm(2,2)) / det;

    return inverse;
}

#undef mm
}
  
  
//-----------------------------------------------------------------------------
// 
// Mouse definition 
//
//-----------------------------------------------------------------------------

Mouse::Mouse(PinholeCamera* camera, int xres, int yres)
  : camera(camera)
  , xres(xres)
  , yres(yres)
  , fov_speed(2)
  , dolly_speed(5)
  , translate_speed(33)
{
}

void Mouse::handleMouseFunc(int button, int state, int x, int y, int modifier)
{
  switch(state) {
  case GLUT_DOWN:
    current_interaction = InteractionState(modifier, button, state);
    call_func(x,y);
    break;
  case GLUT_UP:
    break;
  }
}

void Mouse::handleMoveFunc(int x, int y)
{
  current_interaction.state = GLUT_MOTION;
  call_func(x,y);
}

void Mouse::handlePassiveMotionFunc(int x, int y)
{
}

void Mouse::handleResize(int new_xres, int new_yres)
{
  xres = new_xres;
  yres = new_yres;
  camera->setAspectRatio(static_cast<float>(xres)/yres);
}

void Mouse::call_func(int x, int y)
{
  int modifier = current_interaction.modifier;
  int button   = current_interaction.button;
  if (modifier == 0                 && button == GLUT_LEFT_BUTTON)
    rotate(x, y);
  if (modifier == 0                 && button == GLUT_MIDDLE_BUTTON)
    translate(x, y);
  if (modifier == GLUT_ACTIVE_SHIFT && button == GLUT_RIGHT_BUTTON)
    fov(x, y);
  if (modifier == 0                 && button == GLUT_RIGHT_BUTTON)
    dolly(x, y);
}

void Mouse::fov(int x, int y)
{
  if(current_interaction.state == GLUT_MOTION) {
    float xmotion = (current_interaction.last_x - x)/static_cast<float>(xres);
    float ymotion = (current_interaction.last_y - y)/static_cast<float>(yres);
    float scale;
    if(fabsf(xmotion) > fabsf(ymotion))
      scale = xmotion;
    else
      scale = ymotion;
    scale *= fov_speed;

    if (scale < 0.0f)
      scale = 1.0f/(1.0f-scale);
    else
      scale += 1.0f;

    // Manipulate Camera
    camera->scaleFOV(scale);
  }
  current_interaction.last_x = x;
  current_interaction.last_y = y;
}


void Mouse::translate(int x, int y)
{
  if(current_interaction.state == GLUT_MOTION) {
    float xmotion =  float(current_interaction.last_x - x)/xres;
    float ymotion = -float(current_interaction.last_y - y)/yres;
    float2 translation = make_float2(xmotion, ymotion) * translate_speed;

    camera->translate(translation);
  }
  current_interaction.last_x = x;
  current_interaction.last_y = y;
}


void Mouse::dolly(int x, int y)
{
  if(current_interaction.state == GLUT_MOTION) {
    float xmotion = -float(current_interaction.last_x - x)/xres;
    float ymotion = -float(current_interaction.last_y - y)/yres;

    float scale;
    if(fabsf(xmotion) > fabsf(ymotion))
      scale = xmotion;
    else
      scale = ymotion;
    scale *= dolly_speed;

    camera->dolly(scale);
  }
  current_interaction.last_x = x;
  current_interaction.last_y = y;
}

void Mouse::rotate(int x, int y)
{

  float xpos = 2.0f*static_cast<float>(x)/static_cast<float>(xres) - 1.0f;
  float ypos = 1.0f - 2.0f*static_cast<float>(y)/static_cast<float>(yres);

  if ( current_interaction.state == GLUT_DOWN ) {
    
    current_interaction.rotate_from = projectToSphere( xpos, ypos, 0.8f );

  } else if(current_interaction.state == GLUT_MOTION) {

    float3 to( projectToSphere( xpos, ypos, 0.8f ) );
    float3 from( current_interaction.rotate_from );
  
    Matrix4x4 m = rotationMatrix( to, from);
    current_interaction.rotate_from = to;
    camera->transform( m ); 
  }
  current_interaction.last_x = x;
  current_interaction.last_y = y;

}

void Mouse::track_and_pan(int x, int y)
{
}

void Mouse::track(int x, int y)
{
}

void Mouse::pan(int x, int y)
{
}

//-----------------------------------------------------------------------------
// 
// PinholeCamera definition 
//
//-----------------------------------------------------------------------------

PinholeCamera::PinholeCamera(float3 eye, float3 lookat, float3 up, float hfov, float vfov, AspectRatioMode arm)
  : eye(eye)
  , lookat(lookat)
  , up(up)
  , hfov(hfov)
  , vfov(vfov)
  , aspectRatioMode(arm)
{
  setup();
}

void PinholeCamera::setAspectRatio(float ratio)
{
  float realRatio = ratio;

  const float* inputAngle = 0;
  float* outputAngle = 0;
  switch(aspectRatioMode) {
  case PinholeCamera::KeepHorizontal:
    inputAngle = &hfov;
    outputAngle = &vfov;
    realRatio = 1.f/ratio;
    break;
  case PinholeCamera::KeepVertical:
    inputAngle = &vfov;
    outputAngle = &hfov;
    break;
  case PinholeCamera::KeepNone:
    return;
    break;
  }

  *outputAngle = RtoD(2.0f*atanf(realRatio*tanf(DtoR(0.5f*(*inputAngle)))));

  setup();
}

void PinholeCamera::setParameters(float3 eye_in, float3 lookat_in, float3 up_in, float hfov_in, float vfov_in, PinholeCamera::AspectRatioMode aspectRatioMode_in)
{
  eye = eye_in;
  lookat = lookat_in;
  up = up_in;
  hfov = hfov_in;
  vfov = vfov_in;
  aspectRatioMode = aspectRatioMode_in;
  
  setup();
}

void PinholeCamera::setup()
{
  lookdir = assignWithCheck( lookdir, lookat-eye );  // do not normalize lookdir -- implies focal length
  float lookdir_len = length( lookdir );
  up = assignWithCheck( up, normalize(up));
  camera_u = assignWithCheck( camera_u, normalize( cross(lookdir, up) ) );
  camera_v = assignWithCheck( camera_v, normalize( cross(camera_u, lookdir) ) );
  float ulen = lookdir_len * tanf(DtoR(hfov*0.5f));
  camera_u = assignWithCheck( camera_u, camera_u * ulen );
  float vlen = lookdir_len * tanf(DtoR(vfov*0.5f));
  camera_v = assignWithCheck( camera_v, camera_v * vlen );
}

void PinholeCamera::getEyeUVW(float3& eye_out, float3& U, float3& V, float3& W)
{
  eye_out = eye;
  U = camera_u;
  V = camera_v;
  W = lookdir;
}

void PinholeCamera::getEyeLookUpFOV(float3& eye_out, float3& lookat_out, float3& up_out, float& HFOV_out, float& VFOV_out)
{
  eye_out = eye;
  lookat_out = lookat;
  up_out = up;
  HFOV_out = hfov;
  VFOV_out = vfov;
}

void PinholeCamera::scaleFOV(float scale)
{
  const float fov_min = 0.0f;
  const float fov_max = 120.0f;
  float hfov_new = RtoD(2*atanf(scale*tanf(DtoR(hfov*0.5f))));
  hfov_new = Clamp(hfov_new, fov_min, fov_max);
  float vfov_new = RtoD(2*atanf(scale*tanf(DtoR(vfov*0.5f))));
  vfov_new = Clamp(vfov_new, fov_min, fov_max);

  hfov = assignWithCheck( hfov, hfov_new );
  vfov = assignWithCheck( vfov, vfov_new );

  setup();
}

void PinholeCamera::translate(float2 t)
{
  float3 trans = camera_u*t.x + camera_v*t.y;

  eye = assignWithCheck( eye, eye + trans );
  lookat = assignWithCheck( lookat, lookat + trans );

  setup();
}


// Here scale will move the eye point closer or farther away from the
// lookat point.  If you want an invertable value feed it
// (previous_scale/(previous_scale-1)
void PinholeCamera::dolly(float scale)
{
  // Better make sure the scale isn't exactly one.
  if (scale == 1.0f) return;
  float3 d = (lookat - eye) * scale;
  eye  = assignWithCheck( eye, eye + d );

  setup();
}

void PinholeCamera::transform( const Matrix4x4& trans )
{
  float3 cen = lookat;         // TODO: Add logic for various rotation types (eg, flythrough)

  Matrix4x4 frame = initWithBasis( normalize(camera_u),
                                         normalize(camera_v),
                                         normalize(-lookdir),
                                         cen );
  Matrix4x4 frame_inv = inverse( frame );

  Matrix4x4 final_trans = frame * trans * frame_inv;
  float4 up4     = make_float4( up );
  float4 eye4    = make_float4( eye );
  eye4.w         = 1.0f;
  float4 lookat4 = make_float4( lookat );
  lookat4.w      = 1.0f;


  up     = assignWithCheck( up, make_float3( final_trans*up4 ) );
  eye    = assignWithCheck( eye, make_float3( final_trans*eye4 ) );
  lookat = assignWithCheck( lookat, make_float3( final_trans*lookat4 ) );

  setup();
}
