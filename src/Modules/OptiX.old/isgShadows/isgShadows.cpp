
/*
 * Copyright (c) 2010 NVIDIA Corporation.  All rights reserved.
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

#include <cstdlib>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glew.h>
#  if defined(_WIN32)
#    include <GL/wglew.h>
#  endif
#  include <GL/glut.h>
#endif

#include <optixu/optixpp_namespace.h>

#include <cstdio>
#include <limits>

#include <nvModel.h>
#include <nvTime.h>

#include <framebufferObject.h>
#include <nvGlutManipulators.h>

#include <Cg/cg.h>
#include <Cg/cgGL.h>

#include <string.h>
#include <limits>

#include "sutil.h"
#include "PPMLoader.h"

using namespace optix;

#define CHECK_ERRORS()         \
  do {                         \
    GLenum err = glGetError(); \
    if (err) {                                                       \
      printf( "GL Error %d at line %d\n", (int)err, __LINE__);       \
      exit(-1);                                                      \
    }                                                                \
  } while(0)


nv::GlutExamine manipulator;

nv::Model* model;
GLuint modelVB;
GLuint modelIB;
nv::vec3f modelBBMin, modelBBMax, modelBBCenter;
nv::vec3f lightPos;
float lightRadius = 0.05f;
GLuint shadowMapTex;
GLuint groundTex;

GLuint worldSpaceTex;
FramebufferObject* worldSpaceFBO;

unsigned int warmup_frames = 10u, timed_frames = 10u;
unsigned int initialWindowWidth  = 1024;
unsigned int initialWindowHeight = 768;
unsigned int rasterWidth, rasterHeight;
int logShadowSamplingRate = 0;

GLuint shadowMapPBO;

// CG
CGcontext cgContext;
CGeffect  cgEffect;
CGtechnique cgTechniqueWorldPos;
CGtechnique cgTechniqueHardShadows;

// OptiX
unsigned int traceWidth, traceHeight;

CGparameter cgWorldViewProjParam;
CGparameter cgWorldViewInvParam;
CGparameter cgWorldViewParam;
CGparameter cgLightPosParam;
CGparameter cgShadowMapParam;
CGparameter cgWorldPosMapParam;
CGparameter cgIsGroundParam;
CGparameter cgDoPCFParam;
CGparameter cgDoISGParam;
CGparameter cgGroundTexParam;
CGparameter cgInvSceneScaleParam;
CGparameter cgLightRadiusParam;

optix::Context        rtContext;
optix::TextureSampler rtWorldSpaceTexture;
optix::Buffer         rtShadowBuffer;

std::string CGFX_PATH;
std::string GROUNDTEX_PATH;

bool animate = false;
bool moveLight = false;
bool doBlur = true;
bool doISG  = true;
bool zUp = false;
bool stripNormals = false;

bool fixedCamera = false;
nv::matrix4f fixedCameraMatrix;

bool drawFps = true;

float scene_epsilon = 1e-3f;

void cgErrorCallback()
{
  CGerror lastError = cgGetError();
  if(lastError)
    {
      printf("%s\n", cgGetErrorString(lastError));
      printf("%s\n", cgGetLastListing(cgContext));
      exit(1);
    }
}

void getEffectParam( CGeffect effect,
                     const char* semantic,
                     CGparameter* param )
{
  (*param) = cgGetEffectParameterBySemantic(effect, semantic);
  if (!(*param))
    {
      std::cerr << "getCGParam: Couldn't find parameter with " << semantic << " semantic\n";
      exit(1);
    }
}

void init_gl()
{
#ifndef __APPLE__
  glewInit();

  if (!glewIsSupported( "GL_VERSION_2_0 "
                        "GL_EXT_framebuffer_object "))
    {
      printf("Unable to load the necessary extensions\n");
      printf("This sample requires:\n"
             "OpenGL 2.0\n"
             "GL_EXT_framebuffer_object\n"
             "Exiting...\n");
      exit(-1);
    }
  #if defined(_WIN32)
  // Turn off vertical sync
  wglSwapIntervalEXT(0);
  #endif
#endif

  glClearColor(.2f,.2f,.2f,1.f);
  glEnable(GL_DEPTH_TEST);

  cgContext = cgCreateContext();
  cgSetErrorCallback(cgErrorCallback);
  cgGLSetDebugMode( CG_FALSE );
  cgSetParameterSettingMode(cgContext, CG_DEFERRED_PARAMETER_SETTING);
  cgGLRegisterStates(cgContext);


#ifdef __APPLE__
  const char* cgc_args[] = { "-DCG_FRAGMENT_PROFILE=fp40", "-DCG_VERTEX_PROFILE=vp40", NULL };
#else
  const char* cgc_args[] = { "-DCG_FRAGMENT_PROFILE=gp4fp", "-DCG_VERTEX_PROFILE=gp4vp", NULL };
#endif

  cgEffect = cgCreateEffectFromFile(cgContext, CGFX_PATH.c_str(), cgc_args);
  if(!cgEffect) {
    printf("CGFX error:\n %s\n", cgGetLastListing(cgContext));
    exit(-1);
  }

  cgTechniqueWorldPos = cgGetNamedTechnique(cgEffect, "WorldPos");
  if(!cgTechniqueWorldPos) {
    printf("CGFX error:\n %s\n", cgGetLastListing(cgContext));
    exit(-1);
  }

  cgTechniqueHardShadows = cgGetNamedTechnique(cgEffect, "HardShadows");
  if(!cgTechniqueHardShadows) {
    printf("CGFX error:\n %s\n", cgGetLastListing(cgContext));
    exit(-1);
  }

  getEffectParam(cgEffect, "WorldViewProj", &cgWorldViewProjParam);
  getEffectParam(cgEffect, "WorldViewInv", &cgWorldViewInvParam);
  getEffectParam(cgEffect, "WorldView", &cgWorldViewParam);
  getEffectParam(cgEffect, "LightPos", &cgLightPosParam);
  getEffectParam(cgEffect, "ShadowMap", &cgShadowMapParam);
  getEffectParam(cgEffect, "WorldPosMap", &cgWorldPosMapParam);
  getEffectParam(cgEffect, "IsGround", &cgIsGroundParam);
  getEffectParam(cgEffect, "GroundTex", &cgGroundTexParam);
  getEffectParam(cgEffect, "InvSceneScale", &cgInvSceneScaleParam);
  getEffectParam(cgEffect, "LightRadius", &cgLightRadiusParam);
  
  getEffectParam(cgEffect, "DoPCF", &cgDoPCFParam); 
  cgSetParameter1i(cgDoPCFParam, 1);

  getEffectParam(cgEffect, "DoISG", &cgDoISGParam);
  cgSetParameter1i(cgDoISGParam, 1);

  // create PBO's
  glGenBuffers(1, &shadowMapPBO);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, shadowMapPBO);
  glBufferData(GL_PIXEL_UNPACK_BUFFER, 32*32*sizeof(float), 0, GL_STREAM_READ);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

  // setup FBO's
  worldSpaceFBO = new FramebufferObject();

  GLuint worldSpaceDepthTex;
  glGenTextures(1, &worldSpaceTex);
  glGenTextures(1, &worldSpaceDepthTex);

  glBindTexture(GL_TEXTURE_2D, worldSpaceTex);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, 32, 32, 0, GL_RGBA, GL_FLOAT, NULL);
  glBindTexture(GL_TEXTURE_2D, 0);
  cgGLSetTextureParameter(cgWorldPosMapParam, worldSpaceTex);

  glBindTexture(GL_TEXTURE_2D, worldSpaceDepthTex);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  float BorderColor[4] = { std::numeric_limits<float>::max() };
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, BorderColor);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8_EXT, 32, 32, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
  glBindTexture(GL_TEXTURE_2D, 0);

  worldSpaceFBO->AttachTexture( GL_TEXTURE_2D, worldSpaceTex, GL_COLOR_ATTACHMENT0_EXT );
  worldSpaceFBO->AttachTexture( GL_TEXTURE_2D, worldSpaceDepthTex, GL_DEPTH_ATTACHMENT_EXT );
  if(!worldSpaceFBO->IsValid()) {
    printf("FBO is incomplete\n");
    exit(-1);
  }

  // and shadow map texture
  glGenTextures(1, &shadowMapTex);
  glBindTexture(GL_TEXTURE_2D, shadowMapTex);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE32F_ARB, 32, 32, 0, GL_LUMINANCE, GL_FLOAT, NULL);
  glBindTexture(GL_TEXTURE_2D, 0);
  cgGLSetTextureParameter(cgShadowMapParam, shadowMapTex);

  // load ground texture
  PPMLoader ppm(GROUNDTEX_PATH);
  if(ppm.failed()) {
    std::cerr << "Could not load PPM file " << GROUNDTEX_PATH << '\n';
    exit(1);
  }
  glGenTextures(1, &groundTex);
  glBindTexture(GL_TEXTURE_2D, groundTex);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, ppm.width(), ppm.height(), GL_RGB, GL_UNSIGNED_BYTE, ppm.raster());
  glBindTexture(GL_TEXTURE_2D, 0);
  cgGLSetTextureParameter(cgGroundTexParam, groundTex);
  

  CHECK_ERRORS();
}

void init_scene(const char* model_filename)
{
  model = new nv::Model();
  if(!model->loadModelFromFile(model_filename)) {
    std::cerr << "Unable to load model '" << model_filename << "'" << std::endl;
    exit(-1);
  }

  model->removeDegeneratePrims();

  if(stripNormals) {
    model->clearNormals();
  }

  model->computeNormals();

  model->clearTexCoords();
  model->clearColors();
  model->clearTangents();

  if(zUp) {
    nv::vec3f* vertices = (nv::vec3f*)model->getPositions();
    nv::vec3f* normals  = (nv::vec3f*)model->getNormals();
    for(int i = 0; i < model->getPositionCount(); ++i) {
      std::swap(vertices[i].y, vertices[i].z);
      vertices[i].z *= -1;

      std::swap(normals[i].y, normals[i].z);
      normals[i].z *= -1;
    }
  }

  model->compileModel();

  glGenBuffers(1, &modelVB);
  glBindBuffer(GL_ARRAY_BUFFER, modelVB);
  glBufferData(GL_ARRAY_BUFFER,
               model->getCompiledVertexCount()*model->getCompiledVertexSize()*sizeof(float),
               model->getCompiledVertices(), GL_STATIC_READ);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenBuffers(1, &modelIB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelIB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
               model->getCompiledIndexCount()*sizeof(int),
               model->getCompiledIndices(), GL_STATIC_READ);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  float diag;
  model->computeBoundingBox(modelBBMin, modelBBMax);
  modelBBCenter = (modelBBMin + modelBBMax) * 0.5;
  diag = nv::length(modelBBMax - modelBBMin);
  cgSetParameter1f(cgInvSceneScaleParam, 1.f/diag);
  lightPos = modelBBMax + nv::vec3<float>(diag*.5f);
  lightPos.z *= -1;

  manipulator.setTrackballActivate(GLUT_LEFT_BUTTON, 0);
  manipulator.setDollyActivate( GLUT_RIGHT_BUTTON, 0);
  manipulator.setPanActivate( GLUT_MIDDLE_BUTTON, 0);

  manipulator.setDollyScale( diag*0.02f );
  manipulator.setPanScale( diag*0.02f );
  manipulator.setDollyPosition( -diag);

  CHECK_ERRORS();
}

std::string ptxpath( const std::string& base )
{
  return std::string(sutilSamplesPtxDir()) + "/isgShadows_generated_" + base + ".ptx";
}

void init_optix()
{
  try {
    rtContext = optix::Context::create();
    rtContext->setRayTypeCount(1);
    rtContext->setEntryPointCount(1);

    rtContext["shadow_ray_type"]->setUint(0u);
    rtContext["scene_epsilon"]->setFloat(scene_epsilon);

    // Limit number of devices to 1 as this is faster for this particular sample.
    std::vector<int> enabled_devices = rtContext->getEnabledDevices();
    rtContext->setDevices(enabled_devices.begin(), enabled_devices.begin()+1);

    rtWorldSpaceTexture = rtContext->createTextureSamplerFromGLImage(worldSpaceTex, RT_TARGET_GL_TEXTURE_2D);
    rtWorldSpaceTexture->setWrapMode(0, RT_WRAP_CLAMP_TO_EDGE);
    rtWorldSpaceTexture->setWrapMode(1, RT_WRAP_CLAMP_TO_EDGE);
    rtWorldSpaceTexture->setWrapMode(2, RT_WRAP_CLAMP_TO_EDGE);
    rtWorldSpaceTexture->setIndexingMode(RT_TEXTURE_INDEX_ARRAY_INDEX);
    rtWorldSpaceTexture->setReadMode(RT_TEXTURE_READ_ELEMENT_TYPE);
    rtWorldSpaceTexture->setMaxAnisotropy(1.0f);
    rtWorldSpaceTexture->setFilteringModes(RT_FILTER_NEAREST, RT_FILTER_NEAREST, RT_FILTER_NONE);
    rtContext["request_texture"]->setTextureSampler(rtWorldSpaceTexture);

    rtShadowBuffer = rtContext->createBufferFromGLBO(RT_BUFFER_OUTPUT, shadowMapPBO);
    rtShadowBuffer->setSize(32,32);
    rtShadowBuffer->setFormat(RT_FORMAT_FLOAT);
    rtContext["shadow_buffer"]->setBuffer(rtShadowBuffer);

    rtContext->setRayGenerationProgram( 0, rtContext->createProgramFromPTXFile( ptxpath("shadow_request_isg.cu"), "shadow_request" ) );
    rtContext->setExceptionProgram( 0, rtContext->createProgramFromPTXFile( ptxpath("shadow_request_isg.cu"), "exception" ) );

    optix::Material opaque = rtContext->createMaterial();
    opaque->setAnyHitProgram(0, rtContext->createProgramFromPTXFile( ptxpath("opaque_isg.cu"), "any_hit_shadow") );

    optix::Geometry rtModel = rtContext->createGeometry();
    rtModel->setPrimitiveCount( model->getCompiledIndexCount()/3 );
    rtModel->setIntersectionProgram( rtContext->createProgramFromPTXFile( ptxpath("triangle_mesh_fat.cu"), "mesh_intersect" ) );
    rtModel->setBoundingBoxProgram( rtContext->createProgramFromPTXFile( ptxpath("triangle_mesh_fat.cu"), "mesh_bounds" ) );

    int num_vertices = model->getCompiledVertexCount();
    optix::Buffer vertex_buffer = rtContext->createBufferFromGLBO(RT_BUFFER_INPUT, modelVB);
    vertex_buffer->setFormat(RT_FORMAT_USER);
    vertex_buffer->setElementSize(3*2*sizeof(float));
    vertex_buffer->setSize(num_vertices);
    rtModel["vertex_buffer"]->setBuffer(vertex_buffer);


    optix::Buffer index_buffer = rtContext->createBufferFromGLBO(RT_BUFFER_INPUT, modelIB);
    index_buffer->setFormat(RT_FORMAT_INT3);
    index_buffer->setSize(model->getCompiledIndexCount()/3);
    rtModel["index_buffer"]->setBuffer(index_buffer);

    optix::Buffer material_buffer = rtContext->createBuffer(RT_BUFFER_INPUT);
    material_buffer->setFormat(RT_FORMAT_UNSIGNED_INT);
    material_buffer->setSize(model->getCompiledIndexCount()/3);
    void* material_data = material_buffer->map();
    memset(material_data, 0, model->getCompiledIndexCount()/3*sizeof(unsigned int));
    material_buffer->unmap();
    rtModel["material_buffer"]->setBuffer(material_buffer);

    optix::GeometryInstance instance = rtContext->createGeometryInstance();
    instance->setMaterialCount(1);
    instance->setMaterial(0, opaque);
    instance->setGeometry(rtModel);

    optix::GeometryGroup geometrygroup = rtContext->createGeometryGroup();
    geometrygroup->setChildCount(1);
    geometrygroup->setChild(0, instance);
    geometrygroup->setAcceleration( rtContext->createAcceleration("Bvh","Bvh") );

    rtContext["shadow_casters"]->set(geometrygroup);

    rtContext->setStackSize(2048);
    rtContext->validate();
  } catch ( optix::Exception& e ) {
    sutilReportError( e.getErrorString().c_str() );
    exit(-1);
  }
}

void draw_ground(CGtechnique& tech)
{
  float diag = nv::length(modelBBMax - modelBBMin);
  float dim = diag*3;

  CGpass pass = cgGetFirstPass(tech);
  while(pass) {
    cgSetPassState(pass);
  
    glBegin(GL_TRIANGLES);
    glNormal3f(0,1,0);
    glTexCoord2f(0,0); glVertex3f(-dim, modelBBMin.y, -dim);
    glTexCoord2f(0,1); glVertex3f(-dim, modelBBMin.y, dim);
    glTexCoord2f(1,0); glVertex3f(dim, modelBBMin.y, -dim);

    glTexCoord2f(0,1); glVertex3f(-dim, modelBBMin.y, dim);
    glTexCoord2f(1,0); glVertex3f(dim, modelBBMin.y, -dim);
    glTexCoord2f(1,1); glVertex3f(dim, modelBBMin.y, dim);

    glEnd();

    cgResetPassState(pass);
    pass = cgGetNextPass(pass);
  }
}

void draw_model(CGtechnique& tech)
{
  glBindBuffer(GL_ARRAY_BUFFER, modelVB);
  glEnableClientState(GL_VERTEX_ARRAY);

  glVertexPointer(  model->getPositionSize(),
                    GL_FLOAT,
                    model->getCompiledVertexSize()*sizeof(float),
                    (void*) (model->getCompiledPositionOffset()*sizeof(float)));

  if ( model->hasNormals() ) {
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(    GL_FLOAT,
                        model->getCompiledVertexSize()*sizeof(float),
                        (void*) (model->getCompiledNormalOffset()*sizeof(float)));
  }

  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, modelIB);

  CGpass pass = cgGetFirstPass(tech);
  while(pass) {
    cgSetPassState(pass);
    glDrawElements( GL_TRIANGLES, model->getCompiledIndexCount(), GL_UNSIGNED_INT, 0 );
    cgResetPassState(pass);
    pass = cgGetNextPass(pass);
  }
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDisableClientState( GL_VERTEX_ARRAY );
  glDisableClientState( GL_NORMAL_ARRAY );
  

  CHECK_ERRORS();
}

void draw_scene(CGtechnique& current_technique)
{
  glLoadIdentity();
  if(fixedCamera) {
    glMultMatrixf(fixedCameraMatrix.get_value());
  } else {
    manipulator.applyTransform();
    glTranslatef( -modelBBCenter.x,
                  -modelBBCenter.y,
                  -modelBBCenter.z );
  }

  cgGLSetStateMatrixParameter(
                              cgWorldViewProjParam,
                              CG_GL_MODELVIEW_PROJECTION_MATRIX,
                              CG_GL_MATRIX_IDENTITY );
  cgGLSetStateMatrixParameter(
                              cgWorldViewInvParam,
                              CG_GL_MODELVIEW_MATRIX,
                              CG_GL_MATRIX_INVERSE_TRANSPOSE );
  cgGLSetStateMatrixParameter(
                              cgWorldViewParam,
                              CG_GL_MODELVIEW_MATRIX,
                              CG_GL_MATRIX_IDENTITY );

  cgSetParameter3f(   cgLightPosParam,
                      lightPos.x,
                      lightPos.y,
                      lightPos.z );

  cgSetParameter1f( cgLightRadiusParam, lightRadius );

  rtContext["light_pos"]->setFloat(lightPos.x, lightPos.y, lightPos.z);

  cgSetParameter1i( cgIsGroundParam, 0 );
  draw_model(current_technique);
  cgSetParameter1i( cgIsGroundParam, 1 );
  draw_ground(current_technique);

  CHECK_ERRORS();
}

void drawText( const std::string& text, float x, float y, void* font )
{
  // Save state
  glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT );

  glDisable( GL_TEXTURE_2D );
  glDisable( GL_LIGHTING );
  glDisable( GL_DEPTH_TEST);

  glColor3f( .1f, .1f, .1f ); // drop shadow
  // Shift shadow one pixel to the lower right.
  glWindowPos2f(x + 1.0f, y - 1.0f);
  for( std::string::const_iterator it = text.begin(); it != text.end(); ++it )
    glutBitmapCharacter( font, *it );

  glColor3f( .95f, .95f, .95f );        // main text
  glWindowPos2f(x, y);
  for( std::string::const_iterator it = text.begin(); it != text.end(); ++it )
    glutBitmapCharacter( font, *it );

  // Restore state
  glPopAttrib();
}

void display()
{
  sutilFrameBenchmark("isgShadows", warmup_frames, timed_frames);

  // render world space position buffer
  glViewport(0,0, traceWidth, traceHeight);
  worldSpaceFBO->Bind();
  float NaN = std::numeric_limits<float>::quiet_NaN();
  glClearColor( NaN, NaN, NaN, NaN );
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  draw_scene(cgTechniqueWorldPos);

  // ray trace shadows from world space buffer
  try {
    rtContext->launch(0, traceWidth, traceHeight);
  } catch (optix::Exception& e) {
    sutilReportError( e.getErrorString().c_str() );
    exit(1);
  }

  // copy shadow map data to from rt buffer to texture
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, shadowMapPBO);
  glBindTexture(GL_TEXTURE_2D, shadowMapTex);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, traceWidth, traceHeight,
                  GL_LUMINANCE, GL_FLOAT, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

  // draw final colors
  glViewport(0,0, rasterWidth, rasterHeight);

  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
  glDrawBuffer(GL_BACK);
  glClearColor(1.f, 1.f, 1.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  draw_scene(cgTechniqueHardShadows);

  // draw fps
  if(drawFps && animate) {
    static double last_frame_time = 0;
    static int frame_count = 0;
    static char fps_text[32];
    double current_time;
    sutilCurrentTime(&current_time);
    double dt = current_time - last_frame_time;
    ++frame_count;
    if(dt > 0.5) {
      sprintf( fps_text, "fps: %6.1f", frame_count / ( current_time - last_frame_time ) );
   
      last_frame_time = current_time;
      frame_count = 0;
    }

    drawText( fps_text, 10.0f, 10.0f, GLUT_BITMAP_8_BY_13 );
  }

  glutSwapBuffers();

  CHECK_ERRORS();
  glutReportErrors();
}

void resize(int w, int h)
{
  // We don't want to allocate 0 memory for the PBOs
  w = w == 0 ? 1 : w; 
  h = h == 0 ? 1 : h; 

  rasterWidth = w;
  rasterHeight = h;

  traceWidth = rasterWidth >> logShadowSamplingRate;
  traceHeight = rasterHeight >> logShadowSamplingRate;

  manipulator.reshape(w,h);

  float aspect = (float)w/(float)h;
  float diag = nv::length(modelBBMax - modelBBMin);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, aspect, diag*.01, diag*100);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  try {
    // resize PBOs
    rtShadowBuffer->unregisterGLBuffer();
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, shadowMapPBO);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, traceWidth*traceHeight*sizeof(float), 0, GL_STREAM_READ);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    rtShadowBuffer->registerGLBuffer();

    // resize FBOs
    rtWorldSpaceTexture->unregisterGLTexture();
    glBindTexture(GL_TEXTURE_2D, worldSpaceFBO->GetAttachedId( GL_COLOR_ATTACHMENT0_EXT ) );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, traceWidth, traceHeight, 0, GL_RGBA, GL_FLOAT, NULL);
    rtWorldSpaceTexture->registerGLTexture();
  } catch ( optix::Exception& e ) {
    sutilReportError( e.getErrorString().c_str() );
    exit(-1);
  }

  glBindTexture(GL_TEXTURE_2D, worldSpaceFBO->GetAttachedId( GL_DEPTH_ATTACHMENT_EXT ) );
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8_EXT, traceWidth, traceHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);

  // resize shadow map texture
  glBindTexture(GL_TEXTURE_2D, shadowMapTex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE32F_ARB, traceWidth, traceHeight, 0, GL_LUMINANCE, GL_FLOAT, 0);

  glBindTexture(GL_TEXTURE_2D, 0);

  // resize rt buffers
  rtShadowBuffer->setSize(traceWidth,traceHeight);

  glutPostRedisplay();

  CHECK_ERRORS();
}

void idle()
{
  manipulator.idle();
  glutPostRedisplay();
}

void special_key(int k, int x, int y)
{
  glutPostRedisplay();
}


void keyboard(unsigned char k, int x, int y)
{
  bool reshape = false;

  switch(k) {

  case 27: // esc
  case 'q':
    exit(0);
    break;

  case 'r':
    animate = !animate;
    if(animate) {
      glutIdleFunc(idle);
    } else {
      glutIdleFunc(0);
    }
    break;

  case 'l':
    moveLight = !moveLight;
    break;

  case 's':
    logShadowSamplingRate += 1;
    if(rasterWidth  >> logShadowSamplingRate < 2 ||
       rasterHeight >> logShadowSamplingRate < 2 ||
       logShadowSamplingRate >= 7)
      logShadowSamplingRate -= 1;
    reshape = true;
    break;

  case 'S':
    logShadowSamplingRate -= 1;
    if(logShadowSamplingRate < 0)
      logShadowSamplingRate = 0;
    reshape = true;
    break;

  case 'b':
    doBlur = !doBlur;
    cgSetParameter1i(cgDoPCFParam, (int)doBlur);
    break;

  case 'g':
    if(doBlur) {
      doISG = !doISG;
      cgSetParameter1i(cgDoISGParam, (int)doISG);
    }
    break;

  case 'k':
    lightRadius -= 0.0025f;
    if(lightRadius < 0)
      lightRadius = 0;
    break;

  case 'K':
    lightRadius += 0.0025f;
    if(lightRadius > .1f)
      lightRadius = .1f;
    break;

  case 'c': {
    nv::matrix4f xform = manipulator.getTransform();
    for(int i = 0; i < 16; ++i) 
      std::cerr << xform(i%4, i/4) << ' ';
    std::cerr << std::endl;
  } break;

  case 'e':
    scene_epsilon /= 10;
    rtContext["scene_epsilon"]->setFloat(scene_epsilon);
    break;

  case 'E':
    scene_epsilon *= 10;
    rtContext["scene_epsilon"]->setFloat(scene_epsilon);
    break;

  case 'f':
    static int old_width = -1;
    static int old_height = -1;
    static int old_x = -1;
    static int old_y = -1;
    if(old_width == -1) {
      old_width = glutGet(GLUT_WINDOW_WIDTH);
      old_height = glutGet(GLUT_WINDOW_HEIGHT);
      old_x = glutGet(GLUT_WINDOW_X);
      old_y = glutGet(GLUT_WINDOW_Y);
      glutFullScreen();
    } else {
      glutPositionWindow(old_x, old_y);
      glutReshapeWindow(old_width, old_height);
      old_width = -1;
    }
    break;

  }


  if(reshape) {
    resize(rasterWidth, rasterHeight);
  }

  glutPostRedisplay();
}

nv::vec3f startLightPos;
int startX, startY;
bool lightMoving = false;
void mouse(int button, int state, int x, int y)
{
  if(moveLight) {
    if(button == GLUT_LEFT_BUTTON) {
      if(state == GLUT_DOWN) {
        startLightPos = lightPos;
        startX = x;
        startY = y;
        lightMoving = true;
      } else {
        lightMoving = false;
      }
    }
  } else {
    manipulator.mouse(button, state, x, y);
  }

  glutPostRedisplay();
}

void motion(int x, int y)
{
  if(moveLight && lightMoving) {
    float diag = nv::length(modelBBMax - modelBBMin)*1.8f;
    float deltaX = static_cast<float>(x - startX)/static_cast<float>(rasterWidth)*diag;
    float deltaY = static_cast<float>(y - startY)/static_cast<float>(rasterHeight)*diag;
    lightPos = startLightPos + nv::vec3f(deltaX, 0, deltaY);
  } else {
    manipulator.motion(x,y);
  }

  glutPostRedisplay();
}

void printUsageAndExit( const std::string& argv0, bool doExit = true )
{
  std::cerr
    << "Usage  : " << argv0 << " [options]\n"
    << "App options:\n"
    << "  -h  | --help                               Print this usage message\n"
    << "  -o  | --obj <obj_file>                     Specify .OBJ model to be rendered\n"
    << "  -s  | --shader <cgfx_file>                 Specify cgfx effect to load\n"
    << "  -z  | --zup                                Load model as positive Z as the up direction\n"
    << "  -c  | --camera                             Use the following 16 values to specify the modelview matrix\n"
    << "  -nf | --nofps                              Do not display the FPS counter\n"
    << "  -cn | --compute-normals                    Compute normals instead of reading them from the file\n" 
    << "  -b  | --benchmark[=<w>x<t>]                Render and display 'w' warmup and 't' timing frames, then exit\n"
    << "        --dim=<width>x<height>               Set image dimensions\n"
    << std::endl;

  std::cerr
    << "App keystrokes:\n"
    << "  q Quit\n"
    << "  f Toggle full screen\n"
    << "  e Decrease scene epsilon size (used for shadow ray offset)\n"
    << "  E Increase scene epsilon size (used for shadow ray offset)\n"
    << "  s Decrease the shadow sampling rate\n"
    << "  S Increase the shadow sampling rate\n"
    << "  l Toggle mouse control of the light position\n"
    << "  r Toggle camera hold/continuous rendering\n"
    << "  b Toggle shadow blurring\n"
    << "  k Decrease the light radius\n"
    << "  K Increase the light radius\n"
    << "  g Toggle between PCF and ISG blurring\n"
    << "  c Print modelview matrix\n"
    << std::endl;


  if ( doExit ) exit(1);
}

int main(int argc, char** argv)
{
  
  // Allow glut to consume its args first
  glutInit(&argc, argv);

  bool dobenchmark = false;
  std::string filename;
  std::string cgfx_path;
  std::string ground_tex;
  for(int i = 1; i < argc; ++i) {
    std::string arg(argv[i]);
    if( arg == "--obj" || arg == "-o" ) {
      if( i + 1 >= argc ) {
        printUsageAndExit(argv[0]);
      }
      filename = argv[++i];
    } else if( arg == "--help" || arg == "-h" ) {
      printUsageAndExit(argv[0]);
    } else if (arg.substr(0, 3) == "-B=" || arg.substr(0, 23) == "--benchmark-no-display=" ||
      arg.substr(0, 3) == "-b=" || arg.substr(0, 23) == "--benchmark=") {
      dobenchmark = true;
      std::string bnd_args = arg.substr(arg.find_first_of('=') + 1);
      if (sutilParseImageDimensions(bnd_args.c_str(), &warmup_frames, &timed_frames) != RT_SUCCESS) {
        std::cerr << "Invalid --benchmark-no-display arguments: '" << bnd_args << "'" << std::endl;
        printUsageAndExit(argv[0]);
      }
    } else if (arg == "-B" || arg == "--benchmark-no-display" || arg == "-b" || arg == "--benchmark") {
      dobenchmark = true;
    } else if( arg == "--shader" || arg == "-s" ) {
      if( i + 1 >= argc ) {
        printUsageAndExit(argv[0]);
      }
      cgfx_path = argv[++i];
    } else if( arg == "--zup" || arg == "-z" ) {
      zUp = true;
    } else if (arg == "--camera" || arg == "-c" ) {
      if( i + 16 >= argc ) {
        printUsageAndExit(argv[0]);
      }
      for(int j = 0; j < 16; ++j) {
        fixedCameraMatrix(j%4,j/4) = static_cast<float>(atof(argv[++i]));
      }
      fixedCamera = true;
    } else if (arg == "--nofps" || arg == "-nf") {
      drawFps = false;
    } else if (arg == "--compute-normals" || arg == "-cn") {
      stripNormals = true;
    } else if ( arg.substr( 0, 6 ) == "--dim=" ) {
      std::string dims_arg = arg.substr(6);
      if ( sutilParseImageDimensions( dims_arg.c_str(),
                                      &initialWindowWidth,
                                      &initialWindowHeight )
          != RT_SUCCESS ) {
        std::cerr << "Invalid window dimensions: '" << dims_arg << "'" << std::endl;
        printUsageAndExit( argv[0] );
      }
    } else {
      fprintf( stderr, "Unknown option '%s'\n", argv[i] );
      printUsageAndExit( argv[0] );
    }
  }

  if( !dobenchmark ) printUsageAndExit( argv[0], false );

  if(filename.empty()) {
    filename = std::string( sutilSamplesDir() ) + "/simpleAnimation/cow.obj";
  }
  if(cgfx_path.empty()) {
    cgfx_path = std::string( sutilSamplesDir() ) + "/isgShadows/isgShadows.cgfx";
  }

  CGFX_PATH = cgfx_path;
  GROUNDTEX_PATH = std::string( sutilSamplesDir() ) + "/isgShadows/ground.ppm";

  glutInitWindowSize(initialWindowWidth, initialWindowHeight);
  glutInitWindowPosition(100, 100);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("isgShadows");

  init_gl();
  init_scene(filename.c_str());
  init_optix();
  
  CHECK_ERRORS();
  glutReportErrors();

  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutSpecialFunc(special_key);

  if(dobenchmark) {
    glutIdleFunc(idle);
    animate = true;
  } else {
    warmup_frames = timed_frames = 0;
  }

  glutMainLoop();
}
