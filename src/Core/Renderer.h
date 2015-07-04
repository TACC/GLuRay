/**********************************************************************************
*                     Copyright (c) 2013-2015 Carson Brownlee
*         Texas Advanced Computing Center, University of Texas at Austin
*                       All rights reserved
* 
*       This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
* 
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
* 
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************************/
#ifndef RENDERER_H
#define RENDERER_H
#include "defines.h"
#include "Work.h"
#include "GLuRayRenderParameters.h"
#include "GeometryGenerator.h"
#include "Renderable.h"
#include "GLTypes.h"

#include <GL/gl.h>

#include <Model/Lights/DirectionalLight.h>
#include <Interface/LightSet.h>
#include <Interface/MantaInterface.h>
#include <Interface/Object.h>
#include <Interface/Camera.h>
#include <Engine/Factory/Factory.h>
#include <Engine/Factory/Create.h>
#include <Engine/Display/SyncDisplay.h>
#include <Model/Materials/Volume.h>
#include <Core/Thread/Barrier.h>
#include <Core/Thread/CrowdMonitor.h>
#include <Core/Thread/Mutex.h>
#include <Core/Thread/Semaphore.h>


#include <queue>
#include <stack>
// using namespace Manta;

namespace glr
{

class Framebuffer 
{
public:
	Framebuffer() :  width(0), height(0), byteAlign(1), data(NULL), depth(NULL)
	{
		SetFormat(GL_RGBA, GL_UNSIGNED_BYTE);
	}

	void SetFormat(GLenum f, GLenum t)
	{
		glFormat = f;
		glType = t;

	  if (glFormat == GL_RGBA && glType == GL_UNSIGNED_BYTE)
			csize = 4;
	  else if (glFormat == GL_BGRA && glType == GL_UNSIGNED_BYTE)
			csize = 4;
		else if (glFormat == GL_FLOAT && glType == GL_LUMINANCE)
			csize = 4;
		else if (glFormat == GL_FLOAT && glType == GL_RGB)
			csize = 12;
		else if (glFormat == GL_FLOAT && glType == GL_RGBA)
			csize = 16;
		else
		{
			std::cerr << "GLR_ERROR: Framebuffer: unrecognized format/type\n";
			return;
		}

		if (data) 
		{
			width = 0;
			height = 0;
			free(data);
			if (depth) free(depth);
		}
	}

	GLenum GetFormat() { return glFormat; }
	GLenum GetType() { return glType; }
	GLenum GetAlignment() { return byteAlign; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	void *GetData() { return data; }
	void *GetDepth() { return depth; }

	~Framebuffer()
	{
		if (data) free(data);
		if (depth) free(depth);
	}

	void Load(int w, int h, void *c, void *d)
	{
		if (w != width || h != height)
		{
			if (data) free(data);
			data = (void *)malloc(w*h*csize);
			if (depth) free(depth);
			if (d) depth = (void *)malloc(w*h*sizeof(float));
			width = w;
			height = h;
		}

		memcpy(data, c, w*h*sizeof(int32_t));
		if (d)
			memcpy(depth, d, w*h*sizeof(float));
	}

	void Store()
	{
		std::cerr << "S";
		if (width && height && data)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, byteAlign);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_SCISSOR_TEST);
			glDisable(GL_ALPHA_TEST);
			glDisable(GL_BLEND);
			glDepthFunc(GL_ALWAYS);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			if (depth) glDrawPixels(width, height, GL_DEPTH_COMPONENT, GL_FLOAT, depth);
			glDrawPixels(width, height, glFormat, glType, data);
		}
	}

private:
	int csize;
	void *data;
	void *depth;
	GLenum glType, glFormat, byteAlign;
	size_t width, height;
};

class Renderer
{
public:
  Renderer() ;
  ~Renderer() {}
  virtual void setBGColor(float r, float g, float b, float a)
  {
    printf("setBGColor\n");
    Manta::Color color = Manta::Color(Manta::RGBColor(r,g,b));
    if ((params.env_map == "" || params.env_map == "none") && (current_bgcolor.color[0] != color[0] || current_bgcolor.color[1] != color[1] || current_bgcolor.color[2] != color[2] || current_bgcolor.a != a))
    {
    current_bgcolor.color = color;
    current_bgcolor.a = a;
    params.bgcolor = current_bgcolor;
    updateBackground();
    }
  }
  virtual void setColor(float r, float g, float b, float a) {current_color = Manta::RGBAColor(r,g,b,a);}
  virtual GLMaterial& getCurrentMaterial() { return gl_material; }
  virtual void enableGLMaterial(bool st) { use_gl_material = st; }
  virtual void updateMaterial() = 0;
  virtual void updateLights() = 0;
  //virtual void addScene(Scene* scene)=0;
  virtual void addWork(Work* work) {  accel_work_queue.push(work); }

  virtual void render() = 0;
  virtual void init() = 0;

  virtual void setNumSamples(int,int,int samples) = 0;
  virtual void setNumThreads(int t) = 0;

  virtual void setSize(int w, int h)=0;
  void setNearFar(double near, double far) { _zNear = near; _zFar = far; }
  virtual void setRenderParametersString(string in, bool need_relaunch = true);
  virtual void setRenderParameters(GLuRayRenderParameters& rp, bool need_relaunch = true);
  virtual void pushRenderParameters();
  virtual void popRenderParameters();

  virtual void useShadows(bool st) = 0;
  virtual void updateBackground() = 0;
  virtual void updateCamera()=0;
  virtual void enableLighting(bool st) { use_gl_lights = st; lights_dirty = true; }
  virtual void enableLight(int light, bool st) { gl_lights[light].enabled = st; lights_dirty = true; }
  virtual GLLight getLight(int num) { return gl_lights[num]; }
  virtual void setLight(int num, const GLLight& l ) { gl_lights.at(num) = l; lights_dirty = true; }
  virtual bool getUsePerVertexColors() {return usePerVertexColors; }
  virtual void setUsePerVertexColors(bool st) {usePerVertexColors = st;}
  virtual Manta::RGBAColor getCurrentColor() { return current_color; }
  virtual GeometryGenerator* getGeometryGenerator(int type) = 0;
  virtual Renderable* createRenderable(GeometryGenerator* gen) = 0;
  virtual void addRenderable(Renderable* ren) = 0;
  virtual void deleteRenderable(Renderable* ren) = 0;
  virtual void addTexture(int handle, int target, int level, int internalFormat, int width, int height, int border, int format, int type, void* data) {}
  virtual void deleteTexture(int handle) {}
  virtual void addInstance(Renderable* ren);
  Renderable* getCurrentRenderable() { return current_renderable; }
  void setCurrentRenderable(Renderable* r) { current_renderable = r; }
  Manta::AffineTransform& getCurrentTransform() { return current_transform; }

  /*inline*/ void lock(const int mutex)
  {
    _mutexes[mutex]->lock();
  }
  /*inline*/ void unlock(const int mutex)
  {
    _mutexes[mutex]->unlock();
  }
  void displayFrame();

  //protected:

  std::queue<Work*> accel_work_queue;
  bool kill_accel_threads;

  // void initClient();
  // static void* clientLoop(void* t);

  Manta::RGBAColor current_color;
  Manta::Material* current_material;
  Manta::AffineTransform current_transform;
  stack<Manta::AffineTransform> transform_stack;
  Manta::RGBAColor current_bgcolor;
  Renderable* current_renderable;
  Manta::Vector current_normal;
  bool auto_camera;
  int num_threads;
  int window_id;
  int channel_id;
  bool rendering;
  GLuRayRenderParameters params;
  stack<GLuRayRenderParameters> render_parameters_stack;
  bool print_build_time;
  bool relaunch;
  bool client_running;
  bool render_once;
  bool usePerVertexColors;
  std::vector<GLLight> gl_lights;
  GLMaterial gl_material;
  bool use_gl_lights;
  bool use_gl_material; //use material or color?
  bool lights_dirty;
  bool dirty_renderParams;
  string new_renderParamsString;
  bool frame_lag;
  int rank;
  bool dirty_sampleGenerator;
  bool initialized;
  double _zFar, _zNear;
  vector<Manta::Mutex*> _mutexes;

  size_t _nid_counter;
  bool _depth;
  int _width, _height;
  Framebuffer _framebuffer;
  // bool _resetAccumulation;
  bool rendered;
  int _frameNumber;
  int _realFrameNumber;  //corrected by env param
};

}
#endif
