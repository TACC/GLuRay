#include "gluray.h"


// GL_VERSION_1_0

void glBegin(GLenum mode)
{
  gr_beginPrimitive(mode);

  next_glBegin(mode);
  printGLError();

  debugPrint("glBegin(mode= %s)\n", getEnumString(mode));
}

void glCallList(GLuint list)
{
  gr_callList(list);
}

void glClear(GLbitfield mask)
{
  gr_clear(mask);
}

void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  gr_setBackgroundColor(red, green, blue, alpha);

  next_glClearColor(red, green, blue, alpha);
  printGLError();

  debugPrint("glClearColor(red= %f, green= %f, blue= %f, alpha= %f)\n", red, green, blue, alpha);
}

void glColor3d(GLdouble red, GLdouble green, GLdouble blue)
{
  gr_setColor(red,green,blue, 1.0f);

  next_glColor3d(red, green, blue);
  printGLError();

  debugPrint("glColor3d(red= %f, green= %f, blue= %f)\n", red, green, blue);
}

void glColor3dv(const GLdouble* v)
{
  gr_setColor(v[0],v[1],v[2], 1.0f);

  next_glColor3dv(v);
  printGLError();

  debugPrint("glColor3dv(v= %x)\n", v);
}

void glColor3f(GLfloat red, GLfloat green, GLfloat blue)
{
  gr_setColor(red,green,blue, 1.0f);

  next_glColor3f(red, green, blue);
  printGLError();

  debugPrint("glColor3f(red= %f, green= %f, blue= %f)\n", red, green, blue);
}

void glColor3fv(const GLfloat* v)
{
  gr_setColor(v[0],v[1],v[2], 1.0f);

  next_glColor3fv(v);
  printGLError();

  debugPrint("glColor3fv(v= %x)\n", v);
}

void glColor3iv(const GLint* v)
{
  gr_setColor(v[0],v[1],v[2], 1.0f);

  next_glColor3iv(v);
  printGLError();

  debugPrint("glColor3iv(v= %x)\n", v);
}

void glColor3ubv(const GLubyte* v)
{
  gr_setColorub(v[0], v[1], v[2], 255);

  next_glColor3ubv(v);
  printGLError();

  debugPrint("glColor3ubv(v= %x)\n", v);
}

void glColor4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha)
{
  gr_setColor(red,green,blue, alpha);

  next_glColor4d(red, green, blue, alpha);
  printGLError();

  debugPrint("glColor4d(red= %f, green= %f, blue= %f, alpha= %f)\n", red, green, blue, alpha);
}

void glColor4dv(const GLdouble* v)
{
  gr_setColor(v[0],v[1],v[2],v[3]);

  next_glColor4dv(v);
  printGLError();

  debugPrint("glColor4dv(v= %x)\n", v);
}

void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  gr_setColor(red,green,blue, alpha);

  next_glColor4f(red, green, blue, alpha);
  printGLError();

  debugPrint("glColor4f(red= %f, green= %f, blue= %f, alpha= %f)\n", red, green, blue, alpha);
}

void glColor4fv(const GLfloat* v)
{
  gr_setColor(v[0],v[1],v[2],v[3]);

  next_glColor4fv(v);
  printGLError();

  debugPrint("glColor4fv(v= %x)\n", v);
}

void glColor4ubv(const GLubyte* v)
{
  gr_setColorub(v[0],v[1],v[2],v[3]);

  next_glColor4ubv(v);
  printGLError();

  debugPrint("glColor4ubv(v= %x)\n", v);
}

void glDeleteLists(GLuint list, GLsizei range)
{
  gr_deleteLists(list, range);

  next_glDeleteLists(list, range);
  printGLError();

  debugPrint("glDeleteLists(list= %u, range= %u)\n", list, range);
}

void glDisable(GLenum cap)
{
  gr_disable(cap);

  next_glDisable(cap);
  printGLError();

  debugPrint("glDisable(cap= %s)\n", getEnumString(cap));
}

void glEnable(GLenum cap)
{
  gr_enable(cap);

  next_glEnable(cap);
  printGLError();

  debugPrint("glEnable(cap= %s)\n", getEnumString(cap));
}

void glEnd()
{
  gr_endPrimitive();

  next_glEnd();
  printGLError();

  debugPrint("glEnd()\n");
}

void glEndList()
{
  gr_endList();
}

void glFinish()
{
  if (GLURAY_RENDER_MODE & GLURAY_RENDER_GLFINISH)
    gr_render();

  next_glFinish();
  printGLError();

  debugPrint("glFinish()\n");
}

void glFlush()
{
  if (GLURAY_RENDER_MODE & GLURAY_RENDER_GLFLUSH)
    gr_render();

  next_glFlush();
  printGLError();

  debugPrint("glFlush()\n");
}

void glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
  gr_frustum(left,right,bottom,top,zNear,zFar);

  next_glFrustum(left, right, bottom, top, zNear, zFar);
  printGLError();

  debugPrint("glFrustum(left= %f, right= %f, bottom= %f, top= %f, zNear= %f, zFar= %f)\n", left, right, bottom, top, zNear, zFar);
}

void glLightfv(GLenum light, GLenum pname, const GLfloat* params)
{
  gr_light(light, pname, params);

  next_glLightfv(light, pname, params);
  printGLError();

  debugPrint("glLightfv(light= %s, pname= %s, params= %x)\n", getEnumString(light), getEnumString(pname), params);
}

void glLoadIdentity()
{
  gr_loadIdentity();

  next_glLoadIdentity();
  printGLError();

  debugPrint("glLoadIdentity()\n");
}

void glLoadMatrixd(const GLdouble* m)
{
  gr_loadMatrixd(m);

  next_glLoadMatrixd(m);
  printGLError();

  debugPrint("glLoadMatrixd(m= %x)\n", m);
}

void glLoadMatrixf(const GLfloat* m)
{
  gr_loadMatrixf(m);

  next_glLoadMatrixf(m);
  printGLError();

  debugPrint("glLoadMatrixf(m= %x)\n", m);
}

void glMaterialf(GLenum face, GLenum pname, GLfloat param)
{
  gr_materialf(face, pname, param);

  next_glMaterialf(face, pname, param);
  printGLError();

  debugPrint("glMaterialf(face= %s, pname= %s, param= %f)\n", getEnumString(face), getEnumString(pname), param);
}

void glMaterialfv(GLenum face, GLenum pname, const GLfloat* params)
{
  gr_materialfv(face, pname, params);

  next_glMaterialfv(face, pname, params);
  printGLError();

  debugPrint("glMaterialfv(face= %s, pname= %s, params= %x)\n", getEnumString(face), getEnumString(pname), params);
}

void glMateriali(GLenum face, GLenum pname, GLint param)
{
  gr_materiali(face, pname, param);

  next_glMateriali(face, pname, param);
  printGLError();

  debugPrint("glMateriali(face= %s, pname= %s, param= %i)\n", getEnumString(face), getEnumString(pname), param);
}

void glMaterialiv(GLenum face, GLenum pname, const GLint* params)
{
  gr_materialiv(face, pname, params);

  next_glMaterialiv(face, pname, params);
  printGLError();

  debugPrint("glMaterialiv(face= %s, pname= %s, params= %x)\n", getEnumString(face), getEnumString(pname), params);
}

void glMatrixMode(GLenum mode)
{
  gr_matrixMode(mode);

  next_glMatrixMode(mode);
  printGLError();

  debugPrint("glMatrixMode(mode= %s)\n", getEnumString(mode));
}

void glMultMatrixd(const GLdouble* m)
{
  gr_multMatrixd(m);

  next_glMultMatrixd(m);
  printGLError();

  debugPrint("glMultMatrixd(m= %x)\n", m);
}

void glMultMatrixf(const GLfloat* m)
{
  gr_multMatrixf(m);

  next_glMultMatrixf(m);
  printGLError();

  debugPrint("glMultMatrixf(m= %x)\n", m);
}

void glNewList(GLuint list, GLenum mode)
{
  gr_newList(list,mode);
}

void glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz)
{
  gr_normal(nx,ny,nz);
}

void glNormal3dv(const GLdouble* v)
{
  gr_normal(v[0],v[1],v[2]);
}

void glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz)
{
  gr_normal(nx,ny,nz);
}

void glNormal3fv(const GLfloat* v)
{
  gr_normal(v[0],v[1],v[2]);
}

void glNormal3i(GLint nx, GLint ny, GLint nz)
{
  gr_normal(nx,ny,nz);

  next_glNormal3i(nx, ny, nz);
  printGLError();

  debugPrint("glNormal3i(nx= %i, ny= %i, nz= %i)\n", nx, ny, nz);
}

void glNormal3iv(const GLint* v)
{
  gr_normal(v[0],v[1],v[2]);

  next_glNormal3iv(v);
  printGLError();

  debugPrint("glNormal3iv(v= %x)\n", v);
}

void glNormal3s(GLshort nx, GLshort ny, GLshort nz)
{
  gr_normal(nx,ny,nz);

  next_glNormal3s(nx, ny, nz);
  printGLError();

  debugPrint("glNormal3s(nx= %i, ny= %i, nz= %i)\n", nx, ny, nz);
}

void glNormal3sv(const GLshort* v)
{
  gr_normal(v[0],v[1],v[2]);

  next_glNormal3sv(v);
  printGLError();

  debugPrint("glNormal3sv(v= %x)\n", v);
}

void glPopMatrix()
{
  gr_popMatrix();

  next_glPopMatrix();
  printGLError();

  debugPrint("glPopMatrix()\n");
}

void glPushMatrix()
{
  gr_pushMatrix();

  next_glPushMatrix();
  printGLError();

  debugPrint("glPushMatrix()\n");
}

void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels)
{
  if (format == GL_RGBA //TODO: this assumes compositors will read in rgba first...
    && (GLURAY_RENDER_MODE & GLURAY_RENDER_GLREADPIXELS) )
    gr_render();

  next_glReadPixels(x, y, width, height, format, type, pixels);
  printGLError();

  debugPrint("glReadPixels(x= %i, y= %i, width= %u, height= %u, format= %s, type= %s, pixels= %x)\n", x, y, width, height, getEnumString(format), getEnumString(type), pixels);
}

void glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z)
{
  gr_rotate(angle,x,y,z);

  next_glRotated(angle, x, y, z);
  printGLError();

  debugPrint("glRotated(angle= %f, x= %f, y= %f, z= %f)\n", angle, x, y, z);
}

void glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
  gr_rotate(angle,x,y,z);

  next_glRotatef(angle, x, y, z);
  printGLError();

  debugPrint("glRotatef(angle= %f, x= %f, y= %f, z= %f)\n", angle, x, y, z);
}

void glScaled(GLdouble x, GLdouble y, GLdouble z)
{
  gr_scale(x,y,z);

  next_glScaled(x, y, z);
  printGLError();

  debugPrint("glScaled(x= %f, y= %f, z= %f)\n", x, y, z);
}

void glScalef(GLfloat x, GLfloat y, GLfloat z)
{
  gr_scale(x,y,z);

  next_glScalef(x, y, z);
  printGLError();

  debugPrint("glScalef(x= %f, y= %f, z= %f)\n", x, y, z);
}

void glTexCoord2fv(const GLfloat* v)
{
  gr_texCoord(v[0], v[1], 0.0);

  next_glTexCoord2fv(v);
  printGLError();

  debugPrint("glTexCoord2fv(v= %x)\n", v);
}

void glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels)
{
  gr_texImage1D(target, level, internalformat, width, border, format, type, pixels);

  next_glTexImage1D(target, level, internalformat, width, border, format, type, pixels);
  printGLError();

  debugPrint("glTexImage1D(target= %s, level= %i, internalformat= %i, width= %u, border= %i, format= %s, type= %s, pixels= %x)\n", getEnumString(target), level, internalformat, width, border, getEnumString(format), getEnumString(type), pixels);
}

void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels)
{
  gr_texImage2D(target, level, internalformat, width, height, border, format, type, pixels);

  next_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
  printGLError();

  debugPrint("glTexImage2D(target= %s, level= %i, internalformat= %i, width= %u, height= %u, border= %i, format= %s, type= %s, pixels= %x)\n", getEnumString(target), level, internalformat, width, height, border, getEnumString(format), getEnumString(type), pixels);
}

void glTranslated(GLdouble x, GLdouble y, GLdouble z)
{
  gr_translate(x,y,z);

  next_glTranslated(x, y, z);
  printGLError();

  debugPrint("glTranslated(x= %f, y= %f, z= %f)\n", x, y, z);
}

void glTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
  gr_translate(x,y,z);

  next_glTranslatef(x, y, z);
  printGLError();

  debugPrint("glTranslatef(x= %f, y= %f, z= %f)\n", x, y, z);
}

void glVertex2d(GLdouble x, GLdouble y)
{
  gr_addVertex(x,y,0);

  next_glVertex2d(x, y);
  printGLError();

  debugPrint("glVertex2d(x= %f, y= %f)\n", x, y);
}

void glVertex3d(GLdouble x, GLdouble y, GLdouble z)
{
  gr_addVertex(x,y,z);
}

void glVertex3dv(const GLdouble* v)
{
  gr_addVertex(v[0],v[1],v[2]);
}

void glVertex3f(GLfloat x, GLfloat y, GLfloat z)
{
  gr_addVertex(x,y,z);
}

void glVertex3fv(const GLfloat* v)
{
  gr_addVertex(v[0],v[1],v[2]);
}

void glVertex3iv(const GLint* v)
{
  gr_addVertex(v[0],v[1],v[2]);

  next_glVertex3iv(v);
  printGLError();

  debugPrint("glVertex3iv(v= %x)\n", v);
}

void glVertex3sv(const GLshort* v)
{
  gr_addVertex(v[0],v[1],v[2]);

  next_glVertex3sv(v);
  printGLError();

  debugPrint("glVertex3sv(v= %x)\n", v);
}

void glVertex4dv(const GLdouble* v)
{
  gr_addVertex(v[0],v[1],v[2]);

  next_glVertex4dv(v);
  printGLError();

  debugPrint("glVertex4dv(v= %x)\n", v);
}

void glVertex4fv(const GLfloat* v)
{
  gr_addVertex(v[0],v[1],v[2]);

  next_glVertex4fv(v);
  printGLError();

  debugPrint("glVertex4fv(v= %x)\n", v);
}

void glVertex4iv(const GLint* v)
{
  gr_addVertex(v[0],v[1],v[2]);

  next_glVertex4iv(v);
  printGLError();

  debugPrint("glVertex4iv(v= %x)\n", v);
}

void glVertex4sv(const GLshort* v)
{
  gr_addVertex(v[0],v[1],v[2]);

  next_glVertex4sv(v);
  printGLError();

  debugPrint("glVertex4sv(v= %x)\n", v);
}

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
  gr_viewport(x,y,width,height);

  next_glViewport(x, y, width, height);
  printGLError();

  debugPrint("glViewport(x= %i, y= %i, width= %u, height= %u)\n", x, y, width, height);
}


// GL_VERSION_1_1

void glColorPointer(GLint size, GLenum type, GLsizei stride, const void * pointer)
{
  gr_colorPointer(size,type,stride, pointer);

  next_glColorPointer(size, type, stride, pointer);
  printGLError();

  debugPrint("glColorPointer(size= %i, type= %s, stride= %u, pointer= %x)\n", size, getEnumString(type), stride, pointer);
}

void glDisableClientState(GLenum array)
{
  gr_disableClientState(array);

  next_glDisableClientState(array);
  printGLError();

  debugPrint("glDisableClientState(array= %s)\n", getEnumString(array));
}

void glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
  gr_drawArrays(mode, first, count);
}

void glDrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices)
{
  gr_drawElements(mode, count, type, indices);
}

void glEnableClientState(GLenum array)
{
  gr_enableClientState(array);

  next_glEnableClientState(array);
  printGLError();

  debugPrint("glEnableClientState(array= %s)\n", getEnumString(array));
}

void glVertexPointer(GLint size, GLenum type, GLsizei stride, const void * pointer)
{
  gr_vertexPointer(size,type,stride,pointer);

  next_glVertexPointer(size, type, stride, pointer);
  printGLError();

  debugPrint("glVertexPointer(size= %i, type= %s, stride= %u, pointer= %x)\n", size, getEnumString(type), stride, pointer);
}


// GL_VERSION_1_2


// GL_VERSION_1_3


// GL_VERSION_1_4


// GL_VERSION_1_5


// GL_VERSION_2_0


// GL_VERSION_2_1


// GL_VERSION_3_0


// GL_VERSION_3_1


// GL_VERSION_3_2


// GL_VERSION_3_3


// GL_VERSION_4_0


// GL_VERSION_4_1


// GL_VERSION_4_2


// GL_VERSION_4_3


// GL_VERSION_4_4


// GL_VERSION_4_5


//GLX

XVisualInfo * glXChooseVisual(Display * dpy, GLint screen, GLint * attriblist) {
  XVisualInfo * result = NULL;
  result = next_glXChooseVisual(dpy, screen, attriblist);
  gr_chooseVisual(result);
  
  return result;
}

void glXDestroyContext(Display * dpy, GLXContext ctx) {
  return;
}

Bool glXMakeCurrent(Display * dpy, GLXDrawable drawable, GLXContext ctx) {
  gr_makeCurrent(drawable);
  
  Bool result;
  result = next_glXMakeCurrent(dpy, drawable, ctx);
  
  return result;
}

void glXSwapBuffers(Display * dpy, GLXDrawable drawable) {
  if (GLURAY_RENDER_MODE & GLURAY_RENDER_GLXSWAPBUFFERS)
    gr_render();
  
  next_glXSwapBuffers(dpy, drawable);
}

__GLXextFuncPtr glXGetProcAddressARB(const GLubyte* procName) {
  void* hdl;
  void* retval = NULL;
  const char* dlerr;
  dlerror();
  hdl = dlopen(NULL, RTLD_NOW | RTLD_LOCAL);
  if((dlerr = dlerror()) != NULL) {
    fprintf(stderr, "badness opening ourself: %s\n", dlerr);
  }
  dlerror();
  *(void**) (&retval) = dlsym(hdl, procName);
  if((dlerr = dlerror()) != NULL) {
    fprintf(stderr, "badness loading function %s: %s\n", procName, dlerr);
  }
  if(dlclose(hdl) != 0) {
    fprintf(stderr, "error closing self: %s\n", dlerror());
  }
  return retval;
}


// MPI

#include <UseMPI.h>
#if USE_MPI
#include <mpi.h>
#endif

#if USE_MPI
int MPI_Init(int *argc, char*** argv)
{
  printf("GLURAY Initializing MPI\n");
  int provided=-1;
  int requested=MPI_THREAD_MULTIPLE;

  //int argc = 1;
  //char*** argv = NULL;
  int initialized;
  MPI_Initialized(&initialized);
  if (!initialized)
  {
    MPI_Init_thread(argc, argv, requested, &provided);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0 && (provided != requested))
      printf("Error:  MPI provided does not support MPI_THREAD_MULTIPLE\n do not run with more than one thread\n");
}
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("MPI_Init rank: %d\n", rank);
}

int MPI_Finalize(void)
{
  GLLOCK();
  next_MPI_Finalize();
  GLUNLOCK();
}
#endif