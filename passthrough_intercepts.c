// GL_VERSION_1_0

void glAccum(GLenum op, GLfloat value)
{
  next_glAccum(op, value);
  printGLError();

  debugPrint("glAccum(op= %s, value= %f)\n", getEnumString(op), value);
}

void glAlphaFunc(GLenum func, GLfloat ref)
{
  next_glAlphaFunc(func, ref);
  printGLError();

  debugPrint("glAlphaFunc(func= %s, ref= %f)\n", getEnumString(func), ref);
}

void glBitmap(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte* bitmap)
{
  next_glBitmap(width, height, xorig, yorig, xmove, ymove, bitmap);
  printGLError();

  debugPrint("glBitmap(width= %u, height= %u, xorig= %f, yorig= %f, xmove= %f, ymove= %f, bitmap= %x)\n", width, height, xorig, yorig, xmove, ymove, bitmap);
}

void glBlendFunc(GLenum sfactor, GLenum dfactor)
{
  next_glBlendFunc(sfactor, dfactor);
  printGLError();

  debugPrint("glBlendFunc(sfactor= %s, dfactor= %s)\n", getEnumString(sfactor), getEnumString(dfactor));
}

void glCallLists(GLsizei n, GLenum type, const void * lists)
{
  next_glCallLists(n, type, lists);
  printGLError();

  debugPrint("glCallLists(n= %u, type= %s, lists= %x)\n", n, getEnumString(type), lists);
}

void glClearAccum(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  next_glClearAccum(red, green, blue, alpha);
  printGLError();

  debugPrint("glClearAccum(red= %f, green= %f, blue= %f, alpha= %f)\n", red, green, blue, alpha);
}

void glClearDepth(GLdouble depth)
{
  next_glClearDepth(depth);
  printGLError();

  debugPrint("glClearDepth(depth= %f)\n", depth);
}

void glClearIndex(GLfloat c)
{
  next_glClearIndex(c);
  printGLError();

  debugPrint("glClearIndex(c= %f)\n", c);
}

void glClearStencil(GLint s)
{
  next_glClearStencil(s);
  printGLError();

  debugPrint("glClearStencil(s= %i)\n", s);
}

void glClipPlane(GLenum plane, const GLdouble* equation)
{
  next_glClipPlane(plane, equation);
  printGLError();

  debugPrint("glClipPlane(plane= %s, equation= %x)\n", getEnumString(plane), equation);
}

void glColor3b(GLbyte red, GLbyte green, GLbyte blue)
{
  next_glColor3b(red, green, blue);
  printGLError();

  debugPrint("glColor3b(red= %i, green= %i, blue= %i)\n", red, green, blue);
}

void glColor3bv(const GLbyte* v)
{
  next_glColor3bv(v);
  printGLError();

  debugPrint("glColor3bv(v= %x)\n", v);
}

void glColor3i(GLint red, GLint green, GLint blue)
{
  next_glColor3i(red, green, blue);
  printGLError();

  debugPrint("glColor3i(red= %i, green= %i, blue= %i)\n", red, green, blue);
}

void glColor3s(GLshort red, GLshort green, GLshort blue)
{
  next_glColor3s(red, green, blue);
  printGLError();

  debugPrint("glColor3s(red= %i, green= %i, blue= %i)\n", red, green, blue);
}

void glColor3sv(const GLshort* v)
{
  next_glColor3sv(v);
  printGLError();

  debugPrint("glColor3sv(v= %x)\n", v);
}

void glColor3ub(GLubyte red, GLubyte green, GLubyte blue)
{
  next_glColor3ub(red, green, blue);
  printGLError();

  debugPrint("glColor3ub(red= %x, green= %x, blue= %x)\n", red, green, blue);
}

void glColor3ui(GLuint red, GLuint green, GLuint blue)
{
  next_glColor3ui(red, green, blue);
  printGLError();

  debugPrint("glColor3ui(red= %u, green= %u, blue= %u)\n", red, green, blue);
}

void glColor3uiv(const GLuint* v)
{
  next_glColor3uiv(v);
  printGLError();

  debugPrint("glColor3uiv(v= %x)\n", v);
}

void glColor3us(GLushort red, GLushort green, GLushort blue)
{
  next_glColor3us(red, green, blue);
  printGLError();

  debugPrint("glColor3us(red= %u, green= %u, blue= %u)\n", red, green, blue);
}

void glColor3usv(const GLushort* v)
{
  next_glColor3usv(v);
  printGLError();

  debugPrint("glColor3usv(v= %x)\n", v);
}

void glColor4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha)
{
  next_glColor4b(red, green, blue, alpha);
  printGLError();

  debugPrint("glColor4b(red= %i, green= %i, blue= %i, alpha= %i)\n", red, green, blue, alpha);
}

void glColor4bv(const GLbyte* v)
{
  next_glColor4bv(v);
  printGLError();

  debugPrint("glColor4bv(v= %x)\n", v);
}

void glColor4i(GLint red, GLint green, GLint blue, GLint alpha)
{
  next_glColor4i(red, green, blue, alpha);
  printGLError();

  debugPrint("glColor4i(red= %i, green= %i, blue= %i, alpha= %i)\n", red, green, blue, alpha);
}

void glColor4iv(const GLint* v)
{
  next_glColor4iv(v);
  printGLError();

  debugPrint("glColor4iv(v= %x)\n", v);
}

void glColor4s(GLshort red, GLshort green, GLshort blue, GLshort alpha)
{
  next_glColor4s(red, green, blue, alpha);
  printGLError();

  debugPrint("glColor4s(red= %i, green= %i, blue= %i, alpha= %i)\n", red, green, blue, alpha);
}

void glColor4sv(const GLshort* v)
{
  next_glColor4sv(v);
  printGLError();

  debugPrint("glColor4sv(v= %x)\n", v);
}

void glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
{
  next_glColor4ub(red, green, blue, alpha);
  printGLError();

  debugPrint("glColor4ub(red= %x, green= %x, blue= %x, alpha= %x)\n", red, green, blue, alpha);
}

void glColor4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha)
{
  next_glColor4ui(red, green, blue, alpha);
  printGLError();

  debugPrint("glColor4ui(red= %u, green= %u, blue= %u, alpha= %u)\n", red, green, blue, alpha);
}

void glColor4uiv(const GLuint* v)
{
  next_glColor4uiv(v);
  printGLError();

  debugPrint("glColor4uiv(v= %x)\n", v);
}

void glColor4us(GLushort red, GLushort green, GLushort blue, GLushort alpha)
{
  next_glColor4us(red, green, blue, alpha);
  printGLError();

  debugPrint("glColor4us(red= %u, green= %u, blue= %u, alpha= %u)\n", red, green, blue, alpha);
}

void glColor4usv(const GLushort* v)
{
  next_glColor4usv(v);
  printGLError();

  debugPrint("glColor4usv(v= %x)\n", v);
}

void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
  next_glColorMask(red, green, blue, alpha);
  printGLError();

  debugPrint("glColorMask(red= %i, green= %i, blue= %i, alpha= %i)\n", red, green, blue, alpha);
}

void glColorMaterial(GLenum face, GLenum mode)
{
  next_glColorMaterial(face, mode);
  printGLError();

  debugPrint("glColorMaterial(face= %s, mode= %s)\n", getEnumString(face), getEnumString(mode));
}

void glCopyPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type)
{
  next_glCopyPixels(x, y, width, height, type);
  printGLError();

  debugPrint("glCopyPixels(x= %i, y= %i, width= %u, height= %u, type= %s)\n", x, y, width, height, getEnumString(type));
}

void glCullFace(GLenum mode)
{
  next_glCullFace(mode);
  printGLError();

  debugPrint("glCullFace(mode= %s)\n", getEnumString(mode));
}

void glDepthFunc(GLenum func)
{
  next_glDepthFunc(func);
  printGLError();

  debugPrint("glDepthFunc(func= %s)\n", getEnumString(func));
}

void glDepthMask(GLboolean flag)
{
  next_glDepthMask(flag);
  printGLError();

  debugPrint("glDepthMask(flag= %i)\n", flag);
}

void glDepthRange(GLdouble near, GLdouble far)
{
  next_glDepthRange(near, far);
  printGLError();

  debugPrint("glDepthRange(near= %f, far= %f)\n", near, far);
}

void glDrawBuffer(GLenum buf)
{
  next_glDrawBuffer(buf);
  printGLError();

  debugPrint("glDrawBuffer(buf= %s)\n", getEnumString(buf));
}

void glDrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels)
{
  next_glDrawPixels(width, height, format, type, pixels);
  printGLError();

  debugPrint("glDrawPixels(width= %u, height= %u, format= %s, type= %s, pixels= %x)\n", width, height, getEnumString(format), getEnumString(type), pixels);
}

void glEdgeFlag(GLboolean flag)
{
  next_glEdgeFlag(flag);
  printGLError();

  debugPrint("glEdgeFlag(flag= %i)\n", flag);
}

void glEdgeFlagv(const GLboolean* flag)
{
  next_glEdgeFlagv(flag);
  printGLError();

  debugPrint("glEdgeFlagv(flag= %x)\n", flag);
}

void glEvalCoord1d(GLdouble u)
{
  next_glEvalCoord1d(u);
  printGLError();

  debugPrint("glEvalCoord1d(u= %f)\n", u);
}

void glEvalCoord1dv(const GLdouble* u)
{
  next_glEvalCoord1dv(u);
  printGLError();

  debugPrint("glEvalCoord1dv(u= %x)\n", u);
}

void glEvalCoord1f(GLfloat u)
{
  next_glEvalCoord1f(u);
  printGLError();

  debugPrint("glEvalCoord1f(u= %f)\n", u);
}

void glEvalCoord1fv(const GLfloat* u)
{
  next_glEvalCoord1fv(u);
  printGLError();

  debugPrint("glEvalCoord1fv(u= %x)\n", u);
}

void glEvalCoord2d(GLdouble u, GLdouble v)
{
  next_glEvalCoord2d(u, v);
  printGLError();

  debugPrint("glEvalCoord2d(u= %f, v= %f)\n", u, v);
}

void glEvalCoord2dv(const GLdouble* u)
{
  next_glEvalCoord2dv(u);
  printGLError();

  debugPrint("glEvalCoord2dv(u= %x)\n", u);
}

void glEvalCoord2f(GLfloat u, GLfloat v)
{
  next_glEvalCoord2f(u, v);
  printGLError();

  debugPrint("glEvalCoord2f(u= %f, v= %f)\n", u, v);
}

void glEvalCoord2fv(const GLfloat* u)
{
  next_glEvalCoord2fv(u);
  printGLError();

  debugPrint("glEvalCoord2fv(u= %x)\n", u);
}

void glEvalMesh1(GLenum mode, GLint i1, GLint i2)
{
  next_glEvalMesh1(mode, i1, i2);
  printGLError();

  debugPrint("glEvalMesh1(mode= %s, i1= %i, i2= %i)\n", getEnumString(mode), i1, i2);
}

void glEvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2)
{
  next_glEvalMesh2(mode, i1, i2, j1, j2);
  printGLError();

  debugPrint("glEvalMesh2(mode= %s, i1= %i, i2= %i, j1= %i, j2= %i)\n", getEnumString(mode), i1, i2, j1, j2);
}

void glEvalPoint1(GLint i)
{
  next_glEvalPoint1(i);
  printGLError();

  debugPrint("glEvalPoint1(i= %i)\n", i);
}

void glEvalPoint2(GLint i, GLint j)
{
  next_glEvalPoint2(i, j);
  printGLError();

  debugPrint("glEvalPoint2(i= %i, j= %i)\n", i, j);
}

void glFeedbackBuffer(GLsizei size, GLenum type, GLfloat* buffer)
{
  next_glFeedbackBuffer(size, type, buffer);
  printGLError();

  debugPrint("glFeedbackBuffer(size= %u, type= %s, buffer= %x)\n", size, getEnumString(type), buffer);
}

void glFogf(GLenum pname, GLfloat param)
{
  next_glFogf(pname, param);
  printGLError();

  debugPrint("glFogf(pname= %s, param= %f)\n", getEnumString(pname), param);
}

void glFogfv(GLenum pname, const GLfloat* params)
{
  next_glFogfv(pname, params);
  printGLError();

  debugPrint("glFogfv(pname= %s, params= %x)\n", getEnumString(pname), params);
}

void glFogi(GLenum pname, GLint param)
{
  next_glFogi(pname, param);
  printGLError();

  debugPrint("glFogi(pname= %s, param= %i)\n", getEnumString(pname), param);
}

void glFogiv(GLenum pname, const GLint* params)
{
  next_glFogiv(pname, params);
  printGLError();

  debugPrint("glFogiv(pname= %s, params= %x)\n", getEnumString(pname), params);
}

void glFrontFace(GLenum mode)
{
  next_glFrontFace(mode);
  printGLError();

  debugPrint("glFrontFace(mode= %s)\n", getEnumString(mode));
}

GLuint glGenLists(GLsizei range)
{
  GLuint result= next_glGenLists(range);
  printGLError();

  debugPrint("glGenLists(range= %u)= %u\n", range, result);

  return result;
}

void glGetBooleanv(GLenum pname, GLboolean* data)
{
  next_glGetBooleanv(pname, data);
  printGLError();

  debugPrint("glGetBooleanv(pname= %s, data= %x)\n", getEnumString(pname), data);
}

void glGetClipPlane(GLenum plane, GLdouble* equation)
{
  next_glGetClipPlane(plane, equation);
  printGLError();

  debugPrint("glGetClipPlane(plane= %s, equation= %x)\n", getEnumString(plane), equation);
}

void glGetDoublev(GLenum pname, GLdouble* data)
{
  next_glGetDoublev(pname, data);
  printGLError();

  debugPrint("glGetDoublev(pname= %s, data= %x)\n", getEnumString(pname), data);
}

GLenum glGetError()
{
  GLenum result= next_glGetError();
  printGLError();

  debugPrint("glGetError()= %s\n", result== 0 ? "GL_NO_ERROR" : getEnumString(result));

  return result;
}

void glGetFloatv(GLenum pname, GLfloat* data)
{
  next_glGetFloatv(pname, data);
  printGLError();

  debugPrint("glGetFloatv(pname= %s, data= %x)\n", getEnumString(pname), data);
}

void glGetIntegerv(GLenum pname, GLint* data)
{
  next_glGetIntegerv(pname, data);
  printGLError();

  debugPrint("glGetIntegerv(pname= %s, data= %x)\n", getEnumString(pname), data);
}

void glGetLightfv(GLenum light, GLenum pname, GLfloat* params)
{
  next_glGetLightfv(light, pname, params);
  printGLError();

  debugPrint("glGetLightfv(light= %s, pname= %s, params= %x)\n", getEnumString(light), getEnumString(pname), params);
}

void glGetLightiv(GLenum light, GLenum pname, GLint* params)
{
  next_glGetLightiv(light, pname, params);
  printGLError();

  debugPrint("glGetLightiv(light= %s, pname= %s, params= %x)\n", getEnumString(light), getEnumString(pname), params);
}

void glGetMapdv(GLenum target, GLenum query, GLdouble* v)
{
  next_glGetMapdv(target, query, v);
  printGLError();

  debugPrint("glGetMapdv(target= %s, query= %s, v= %x)\n", getEnumString(target), getEnumString(query), v);
}

void glGetMapfv(GLenum target, GLenum query, GLfloat* v)
{
  next_glGetMapfv(target, query, v);
  printGLError();

  debugPrint("glGetMapfv(target= %s, query= %s, v= %x)\n", getEnumString(target), getEnumString(query), v);
}

void glGetMapiv(GLenum target, GLenum query, GLint* v)
{
  next_glGetMapiv(target, query, v);
  printGLError();

  debugPrint("glGetMapiv(target= %s, query= %s, v= %x)\n", getEnumString(target), getEnumString(query), v);
}

void glGetMaterialfv(GLenum face, GLenum pname, GLfloat* params)
{
  next_glGetMaterialfv(face, pname, params);
  printGLError();

  debugPrint("glGetMaterialfv(face= %s, pname= %s, params= %x)\n", getEnumString(face), getEnumString(pname), params);
}

void glGetMaterialiv(GLenum face, GLenum pname, GLint* params)
{
  next_glGetMaterialiv(face, pname, params);
  printGLError();

  debugPrint("glGetMaterialiv(face= %s, pname= %s, params= %x)\n", getEnumString(face), getEnumString(pname), params);
}

void glGetPixelMapfv(GLenum map, GLfloat* values)
{
  next_glGetPixelMapfv(map, values);
  printGLError();

  debugPrint("glGetPixelMapfv(map= %s, values= %x)\n", getEnumString(map), values);
}

void glGetPixelMapuiv(GLenum map, GLuint* values)
{
  next_glGetPixelMapuiv(map, values);
  printGLError();

  debugPrint("glGetPixelMapuiv(map= %s, values= %x)\n", getEnumString(map), values);
}

void glGetPixelMapusv(GLenum map, GLushort* values)
{
  next_glGetPixelMapusv(map, values);
  printGLError();

  debugPrint("glGetPixelMapusv(map= %s, values= %x)\n", getEnumString(map), values);
}

void glGetPolygonStipple(GLubyte* mask)
{
  next_glGetPolygonStipple(mask);
  printGLError();

  debugPrint("glGetPolygonStipple(mask= %x)\n", mask);
}

const GLubyte* glGetString(GLenum name)
{
  const GLubyte* result= next_glGetString(name);
  printGLError();

  debugPrint("glGetString(name= %s)= %s\n", getEnumString(name), result);

  return result;
}

void glGetTexEnvfv(GLenum target, GLenum pname, GLfloat* params)
{
  next_glGetTexEnvfv(target, pname, params);
  printGLError();

  debugPrint("glGetTexEnvfv(target= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(pname), params);
}

void glGetTexEnviv(GLenum target, GLenum pname, GLint* params)
{
  next_glGetTexEnviv(target, pname, params);
  printGLError();

  debugPrint("glGetTexEnviv(target= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(pname), params);
}

void glGetTexGendv(GLenum coord, GLenum pname, GLdouble* params)
{
  next_glGetTexGendv(coord, pname, params);
  printGLError();

  debugPrint("glGetTexGendv(coord= %s, pname= %s, params= %x)\n", getEnumString(coord), getEnumString(pname), params);
}

void glGetTexGenfv(GLenum coord, GLenum pname, GLfloat* params)
{
  next_glGetTexGenfv(coord, pname, params);
  printGLError();

  debugPrint("glGetTexGenfv(coord= %s, pname= %s, params= %x)\n", getEnumString(coord), getEnumString(pname), params);
}

void glGetTexGeniv(GLenum coord, GLenum pname, GLint* params)
{
  next_glGetTexGeniv(coord, pname, params);
  printGLError();

  debugPrint("glGetTexGeniv(coord= %s, pname= %s, params= %x)\n", getEnumString(coord), getEnumString(pname), params);
}

void glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void * pixels)
{
  next_glGetTexImage(target, level, format, type, pixels);
  printGLError();

  debugPrint("glGetTexImage(target= %s, level= %i, format= %s, type= %s, pixels= %x)\n", getEnumString(target), level, getEnumString(format), getEnumString(type), pixels);
}

void glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat* params)
{
  next_glGetTexLevelParameterfv(target, level, pname, params);
  printGLError();

  debugPrint("glGetTexLevelParameterfv(target= %s, level= %i, pname= %s, params= %x)\n", getEnumString(target), level, getEnumString(pname), params);
}

void glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint* params)
{
  next_glGetTexLevelParameteriv(target, level, pname, params);
  printGLError();

  debugPrint("glGetTexLevelParameteriv(target= %s, level= %i, pname= %s, params= %x)\n", getEnumString(target), level, getEnumString(pname), params);
}

void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params)
{
  next_glGetTexParameterfv(target, pname, params);
  printGLError();

  debugPrint("glGetTexParameterfv(target= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(pname), params);
}

void glGetTexParameteriv(GLenum target, GLenum pname, GLint* params)
{
  next_glGetTexParameteriv(target, pname, params);
  printGLError();

  debugPrint("glGetTexParameteriv(target= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(pname), params);
}

void glHint(GLenum target, GLenum mode)
{
  next_glHint(target, mode);
  printGLError();

  debugPrint("glHint(target= %s, mode= %s)\n", getEnumString(target), getEnumString(mode));
}

void glIndexMask(GLuint mask)
{
  next_glIndexMask(mask);
  printGLError();

  debugPrint("glIndexMask(mask= %u)\n", mask);
}

void glIndexd(GLdouble c)
{
  next_glIndexd(c);
  printGLError();

  debugPrint("glIndexd(c= %f)\n", c);
}

void glIndexdv(const GLdouble* c)
{
  next_glIndexdv(c);
  printGLError();

  debugPrint("glIndexdv(c= %x)\n", c);
}

void glIndexf(GLfloat c)
{
  next_glIndexf(c);
  printGLError();

  debugPrint("glIndexf(c= %f)\n", c);
}

void glIndexfv(const GLfloat* c)
{
  next_glIndexfv(c);
  printGLError();

  debugPrint("glIndexfv(c= %x)\n", c);
}

void glIndexi(GLint c)
{
  next_glIndexi(c);
  printGLError();

  debugPrint("glIndexi(c= %i)\n", c);
}

void glIndexiv(const GLint* c)
{
  next_glIndexiv(c);
  printGLError();

  debugPrint("glIndexiv(c= %x)\n", c);
}

void glIndexs(GLshort c)
{
  next_glIndexs(c);
  printGLError();

  debugPrint("glIndexs(c= %i)\n", c);
}

void glIndexsv(const GLshort* c)
{
  next_glIndexsv(c);
  printGLError();

  debugPrint("glIndexsv(c= %x)\n", c);
}

void glInitNames()
{
  next_glInitNames();
  printGLError();

  debugPrint("glInitNames()\n");
}

GLboolean glIsEnabled(GLenum cap)
{
  GLboolean result= next_glIsEnabled(cap);
  printGLError();

  debugPrint("glIsEnabled(cap= %s)= %i\n", getEnumString(cap), result);

  return result;
}

GLboolean glIsList(GLuint list)
{
  GLboolean result= next_glIsList(list);
  printGLError();

  debugPrint("glIsList(list= %u)= %i\n", list, result);

  return result;
}

void glLightModelf(GLenum pname, GLfloat param)
{
  next_glLightModelf(pname, param);
  printGLError();

  debugPrint("glLightModelf(pname= %s, param= %f)\n", getEnumString(pname), param);
}

void glLightModelfv(GLenum pname, const GLfloat* params)
{
  next_glLightModelfv(pname, params);
  printGLError();

  debugPrint("glLightModelfv(pname= %s, params= %x)\n", getEnumString(pname), params);
}

void glLightModeli(GLenum pname, GLint param)
{
  next_glLightModeli(pname, param);
  printGLError();

  debugPrint("glLightModeli(pname= %s, param= %i)\n", getEnumString(pname), param);
}

void glLightModeliv(GLenum pname, const GLint* params)
{
  next_glLightModeliv(pname, params);
  printGLError();

  debugPrint("glLightModeliv(pname= %s, params= %x)\n", getEnumString(pname), params);
}

void glLightf(GLenum light, GLenum pname, GLfloat param)
{
  next_glLightf(light, pname, param);
  printGLError();

  debugPrint("glLightf(light= %s, pname= %s, param= %f)\n", getEnumString(light), getEnumString(pname), param);
}

void glLighti(GLenum light, GLenum pname, GLint param)
{
  next_glLighti(light, pname, param);
  printGLError();

  debugPrint("glLighti(light= %s, pname= %s, param= %i)\n", getEnumString(light), getEnumString(pname), param);
}

void glLightiv(GLenum light, GLenum pname, const GLint* params)
{
  next_glLightiv(light, pname, params);
  printGLError();

  debugPrint("glLightiv(light= %s, pname= %s, params= %x)\n", getEnumString(light), getEnumString(pname), params);
}

void glLineStipple(GLint factor, GLushort pattern)
{
  next_glLineStipple(factor, pattern);
  printGLError();

  debugPrint("glLineStipple(factor= %i, pattern= %u)\n", factor, pattern);
}

void glLineWidth(GLfloat width)
{
  next_glLineWidth(width);
  printGLError();

  debugPrint("glLineWidth(width= %f)\n", width);
}

void glListBase(GLuint base)
{
  next_glListBase(base);
  printGLError();

  debugPrint("glListBase(base= %u)\n", base);
}

void glLoadName(GLuint name)
{
  next_glLoadName(name);
  printGLError();

  debugPrint("glLoadName(name= %u)\n", name);
}

void glLogicOp(GLenum opcode)
{
  next_glLogicOp(opcode);
  printGLError();

  debugPrint("glLogicOp(opcode= %s)\n", getEnumString(opcode));
}

void glMap1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble* points)
{
  next_glMap1d(target, u1, u2, stride, order, points);
  printGLError();

  debugPrint("glMap1d(target= %s, u1= %f, u2= %f, stride= %i, order= %i, points= %x)\n", getEnumString(target), u1, u2, stride, order, points);
}

void glMap1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat* points)
{
  next_glMap1f(target, u1, u2, stride, order, points);
  printGLError();

  debugPrint("glMap1f(target= %s, u1= %f, u2= %f, stride= %i, order= %i, points= %x)\n", getEnumString(target), u1, u2, stride, order, points);
}

void glMap2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble* points)
{
  next_glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
  printGLError();

  debugPrint("glMap2d(target= %s, u1= %f, u2= %f, ustride= %i, uorder= %i, v1= %f, v2= %f, vstride= %i, vorder= %i, points= %x)\n", getEnumString(target), u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

void glMap2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat* points)
{
  next_glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
  printGLError();

  debugPrint("glMap2f(target= %s, u1= %f, u2= %f, ustride= %i, uorder= %i, v1= %f, v2= %f, vstride= %i, vorder= %i, points= %x)\n", getEnumString(target), u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

void glMapGrid1d(GLint un, GLdouble u1, GLdouble u2)
{
  next_glMapGrid1d(un, u1, u2);
  printGLError();

  debugPrint("glMapGrid1d(un= %i, u1= %f, u2= %f)\n", un, u1, u2);
}

void glMapGrid1f(GLint un, GLfloat u1, GLfloat u2)
{
  next_glMapGrid1f(un, u1, u2);
  printGLError();

  debugPrint("glMapGrid1f(un= %i, u1= %f, u2= %f)\n", un, u1, u2);
}

void glMapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2)
{
  next_glMapGrid2d(un, u1, u2, vn, v1, v2);
  printGLError();

  debugPrint("glMapGrid2d(un= %i, u1= %f, u2= %f, vn= %i, v1= %f, v2= %f)\n", un, u1, u2, vn, v1, v2);
}

void glMapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2)
{
  next_glMapGrid2f(un, u1, u2, vn, v1, v2);
  printGLError();

  debugPrint("glMapGrid2f(un= %i, u1= %f, u2= %f, vn= %i, v1= %f, v2= %f)\n", un, u1, u2, vn, v1, v2);
}

void glNormal3b(GLbyte nx, GLbyte ny, GLbyte nz)
{
  next_glNormal3b(nx, ny, nz);
  printGLError();

  debugPrint("glNormal3b(nx= %i, ny= %i, nz= %i)\n", nx, ny, nz);
}

void glNormal3bv(const GLbyte* v)
{
  next_glNormal3bv(v);
  printGLError();

  debugPrint("glNormal3bv(v= %x)\n", v);
}

void glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
  next_glOrtho(left, right, bottom, top, zNear, zFar);
  printGLError();

  debugPrint("glOrtho(left= %f, right= %f, bottom= %f, top= %f, zNear= %f, zFar= %f)\n", left, right, bottom, top, zNear, zFar);
}

void glPassThrough(GLfloat token)
{
  next_glPassThrough(token);
  printGLError();

  debugPrint("glPassThrough(token= %f)\n", token);
}

void glPixelMapfv(GLenum map, GLsizei mapsize, const GLfloat* values)
{
  next_glPixelMapfv(map, mapsize, values);
  printGLError();

  debugPrint("glPixelMapfv(map= %s, mapsize= %u, values= %x)\n", getEnumString(map), mapsize, values);
}

void glPixelMapuiv(GLenum map, GLsizei mapsize, const GLuint* values)
{
  next_glPixelMapuiv(map, mapsize, values);
  printGLError();

  debugPrint("glPixelMapuiv(map= %s, mapsize= %u, values= %x)\n", getEnumString(map), mapsize, values);
}

void glPixelMapusv(GLenum map, GLsizei mapsize, const GLushort* values)
{
  next_glPixelMapusv(map, mapsize, values);
  printGLError();

  debugPrint("glPixelMapusv(map= %s, mapsize= %u, values= %x)\n", getEnumString(map), mapsize, values);
}

void glPixelStoref(GLenum pname, GLfloat param)
{
  next_glPixelStoref(pname, param);
  printGLError();

  debugPrint("glPixelStoref(pname= %s, param= %f)\n", getEnumString(pname), param);
}

void glPixelStorei(GLenum pname, GLint param)
{
  next_glPixelStorei(pname, param);
  printGLError();

  debugPrint("glPixelStorei(pname= %s, param= %i)\n", getEnumString(pname), param);
}

void glPixelTransferf(GLenum pname, GLfloat param)
{
  next_glPixelTransferf(pname, param);
  printGLError();

  debugPrint("glPixelTransferf(pname= %s, param= %f)\n", getEnumString(pname), param);
}

void glPixelTransferi(GLenum pname, GLint param)
{
  next_glPixelTransferi(pname, param);
  printGLError();

  debugPrint("glPixelTransferi(pname= %s, param= %i)\n", getEnumString(pname), param);
}

void glPixelZoom(GLfloat xfactor, GLfloat yfactor)
{
  next_glPixelZoom(xfactor, yfactor);
  printGLError();

  debugPrint("glPixelZoom(xfactor= %f, yfactor= %f)\n", xfactor, yfactor);
}

void glPointSize(GLfloat size)
{
  next_glPointSize(size);
  printGLError();

  debugPrint("glPointSize(size= %f)\n", size);
}

void glPolygonMode(GLenum face, GLenum mode)
{
  next_glPolygonMode(face, mode);
  printGLError();

  debugPrint("glPolygonMode(face= %s, mode= %s)\n", getEnumString(face), getEnumString(mode));
}

void glPolygonStipple(const GLubyte* mask)
{
  next_glPolygonStipple(mask);
  printGLError();

  debugPrint("glPolygonStipple(mask= %x)\n", mask);
}

void glPopAttrib()
{
  next_glPopAttrib();
  printGLError();

  debugPrint("glPopAttrib()\n");
}

void glPopName()
{
  next_glPopName();
  printGLError();

  debugPrint("glPopName()\n");
}

void glPushAttrib(GLbitfield mask)
{
  next_glPushAttrib(mask);
  printGLError();

  debugPrint("glPushAttrib(mask= %x)\n", mask);
}

void glPushName(GLuint name)
{
  next_glPushName(name);
  printGLError();

  debugPrint("glPushName(name= %u)\n", name);
}

void glRasterPos2d(GLdouble x, GLdouble y)
{
  next_glRasterPos2d(x, y);
  printGLError();

  debugPrint("glRasterPos2d(x= %f, y= %f)\n", x, y);
}

void glRasterPos2dv(const GLdouble* v)
{
  next_glRasterPos2dv(v);
  printGLError();

  debugPrint("glRasterPos2dv(v= %x)\n", v);
}

void glRasterPos2f(GLfloat x, GLfloat y)
{
  next_glRasterPos2f(x, y);
  printGLError();

  debugPrint("glRasterPos2f(x= %f, y= %f)\n", x, y);
}

void glRasterPos2fv(const GLfloat* v)
{
  next_glRasterPos2fv(v);
  printGLError();

  debugPrint("glRasterPos2fv(v= %x)\n", v);
}

void glRasterPos2i(GLint x, GLint y)
{
  next_glRasterPos2i(x, y);
  printGLError();

  debugPrint("glRasterPos2i(x= %i, y= %i)\n", x, y);
}

void glRasterPos2iv(const GLint* v)
{
  next_glRasterPos2iv(v);
  printGLError();

  debugPrint("glRasterPos2iv(v= %x)\n", v);
}

void glRasterPos2s(GLshort x, GLshort y)
{
  next_glRasterPos2s(x, y);
  printGLError();

  debugPrint("glRasterPos2s(x= %i, y= %i)\n", x, y);
}

void glRasterPos2sv(const GLshort* v)
{
  next_glRasterPos2sv(v);
  printGLError();

  debugPrint("glRasterPos2sv(v= %x)\n", v);
}

void glRasterPos3d(GLdouble x, GLdouble y, GLdouble z)
{
  next_glRasterPos3d(x, y, z);
  printGLError();

  debugPrint("glRasterPos3d(x= %f, y= %f, z= %f)\n", x, y, z);
}

void glRasterPos3dv(const GLdouble* v)
{
  next_glRasterPos3dv(v);
  printGLError();

  debugPrint("glRasterPos3dv(v= %x)\n", v);
}

void glRasterPos3f(GLfloat x, GLfloat y, GLfloat z)
{
  next_glRasterPos3f(x, y, z);
  printGLError();

  debugPrint("glRasterPos3f(x= %f, y= %f, z= %f)\n", x, y, z);
}

void glRasterPos3fv(const GLfloat* v)
{
  next_glRasterPos3fv(v);
  printGLError();

  debugPrint("glRasterPos3fv(v= %x)\n", v);
}

void glRasterPos3i(GLint x, GLint y, GLint z)
{
  next_glRasterPos3i(x, y, z);
  printGLError();

  debugPrint("glRasterPos3i(x= %i, y= %i, z= %i)\n", x, y, z);
}

void glRasterPos3iv(const GLint* v)
{
  next_glRasterPos3iv(v);
  printGLError();

  debugPrint("glRasterPos3iv(v= %x)\n", v);
}

void glRasterPos3s(GLshort x, GLshort y, GLshort z)
{
  next_glRasterPos3s(x, y, z);
  printGLError();

  debugPrint("glRasterPos3s(x= %i, y= %i, z= %i)\n", x, y, z);
}

void glRasterPos3sv(const GLshort* v)
{
  next_glRasterPos3sv(v);
  printGLError();

  debugPrint("glRasterPos3sv(v= %x)\n", v);
}

void glRasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
  next_glRasterPos4d(x, y, z, w);
  printGLError();

  debugPrint("glRasterPos4d(x= %f, y= %f, z= %f, w= %f)\n", x, y, z, w);
}

void glRasterPos4dv(const GLdouble* v)
{
  next_glRasterPos4dv(v);
  printGLError();

  debugPrint("glRasterPos4dv(v= %x)\n", v);
}

void glRasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
  next_glRasterPos4f(x, y, z, w);
  printGLError();

  debugPrint("glRasterPos4f(x= %f, y= %f, z= %f, w= %f)\n", x, y, z, w);
}

void glRasterPos4fv(const GLfloat* v)
{
  next_glRasterPos4fv(v);
  printGLError();

  debugPrint("glRasterPos4fv(v= %x)\n", v);
}

void glRasterPos4i(GLint x, GLint y, GLint z, GLint w)
{
  next_glRasterPos4i(x, y, z, w);
  printGLError();

  debugPrint("glRasterPos4i(x= %i, y= %i, z= %i, w= %i)\n", x, y, z, w);
}

void glRasterPos4iv(const GLint* v)
{
  next_glRasterPos4iv(v);
  printGLError();

  debugPrint("glRasterPos4iv(v= %x)\n", v);
}

void glRasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w)
{
  next_glRasterPos4s(x, y, z, w);
  printGLError();

  debugPrint("glRasterPos4s(x= %i, y= %i, z= %i, w= %i)\n", x, y, z, w);
}

void glRasterPos4sv(const GLshort* v)
{
  next_glRasterPos4sv(v);
  printGLError();

  debugPrint("glRasterPos4sv(v= %x)\n", v);
}

void glReadBuffer(GLenum src)
{
  next_glReadBuffer(src);
  printGLError();

  debugPrint("glReadBuffer(src= %s)\n", getEnumString(src));
}

void glRectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
{
  next_glRectd(x1, y1, x2, y2);
  printGLError();

  debugPrint("glRectd(x1= %f, y1= %f, x2= %f, y2= %f)\n", x1, y1, x2, y2);
}

void glRectdv(const GLdouble* v1, const GLdouble* v2)
{
  next_glRectdv(v1, v2);
  printGLError();

  debugPrint("glRectdv(v1= %x, v2= %x)\n", v1, v2);
}

void glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
  next_glRectf(x1, y1, x2, y2);
  printGLError();

  debugPrint("glRectf(x1= %f, y1= %f, x2= %f, y2= %f)\n", x1, y1, x2, y2);
}

void glRectfv(const GLfloat* v1, const GLfloat* v2)
{
  next_glRectfv(v1, v2);
  printGLError();

  debugPrint("glRectfv(v1= %x, v2= %x)\n", v1, v2);
}

void glRecti(GLint x1, GLint y1, GLint x2, GLint y2)
{
  next_glRecti(x1, y1, x2, y2);
  printGLError();

  debugPrint("glRecti(x1= %i, y1= %i, x2= %i, y2= %i)\n", x1, y1, x2, y2);
}

void glRectiv(const GLint* v1, const GLint* v2)
{
  next_glRectiv(v1, v2);
  printGLError();

  debugPrint("glRectiv(v1= %x, v2= %x)\n", v1, v2);
}

void glRects(GLshort x1, GLshort y1, GLshort x2, GLshort y2)
{
  next_glRects(x1, y1, x2, y2);
  printGLError();

  debugPrint("glRects(x1= %i, y1= %i, x2= %i, y2= %i)\n", x1, y1, x2, y2);
}

void glRectsv(const GLshort* v1, const GLshort* v2)
{
  next_glRectsv(v1, v2);
  printGLError();

  debugPrint("glRectsv(v1= %x, v2= %x)\n", v1, v2);
}

GLint glRenderMode(GLenum mode)
{
  GLint result= next_glRenderMode(mode);
  printGLError();

  debugPrint("glRenderMode(mode= %s)= %i\n", getEnumString(mode), result);

  return result;
}

void glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
  next_glScissor(x, y, width, height);
  printGLError();

  debugPrint("glScissor(x= %i, y= %i, width= %u, height= %u)\n", x, y, width, height);
}

void glSelectBuffer(GLsizei size, GLuint* buffer)
{
  next_glSelectBuffer(size, buffer);
  printGLError();

  debugPrint("glSelectBuffer(size= %u, buffer= %x)\n", size, buffer);
}

void glShadeModel(GLenum mode)
{
  next_glShadeModel(mode);
  printGLError();

  debugPrint("glShadeModel(mode= %s)\n", getEnumString(mode));
}

void glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
  next_glStencilFunc(func, ref, mask);
  printGLError();

  debugPrint("glStencilFunc(func= %s, ref= %i, mask= %u)\n", getEnumString(func), ref, mask);
}

void glStencilMask(GLuint mask)
{
  next_glStencilMask(mask);
  printGLError();

  debugPrint("glStencilMask(mask= %u)\n", mask);
}

void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
  next_glStencilOp(fail, zfail, zpass);
  printGLError();

  debugPrint("glStencilOp(fail= %s, zfail= %s, zpass= %s)\n", getEnumString(fail), getEnumString(zfail), getEnumString(zpass));
}

void glTexCoord1d(GLdouble s)
{
  next_glTexCoord1d(s);
  printGLError();

  debugPrint("glTexCoord1d(s= %f)\n", s);
}

void glTexCoord1dv(const GLdouble* v)
{
  next_glTexCoord1dv(v);
  printGLError();

  debugPrint("glTexCoord1dv(v= %x)\n", v);
}

void glTexCoord1f(GLfloat s)
{
  next_glTexCoord1f(s);
  printGLError();

  debugPrint("glTexCoord1f(s= %f)\n", s);
}

void glTexCoord1fv(const GLfloat* v)
{
  next_glTexCoord1fv(v);
  printGLError();

  debugPrint("glTexCoord1fv(v= %x)\n", v);
}

void glTexCoord1i(GLint s)
{
  next_glTexCoord1i(s);
  printGLError();

  debugPrint("glTexCoord1i(s= %i)\n", s);
}

void glTexCoord1iv(const GLint* v)
{
  next_glTexCoord1iv(v);
  printGLError();

  debugPrint("glTexCoord1iv(v= %x)\n", v);
}

void glTexCoord1s(GLshort s)
{
  next_glTexCoord1s(s);
  printGLError();

  debugPrint("glTexCoord1s(s= %i)\n", s);
}

void glTexCoord1sv(const GLshort* v)
{
  next_glTexCoord1sv(v);
  printGLError();

  debugPrint("glTexCoord1sv(v= %x)\n", v);
}

void glTexCoord2d(GLdouble s, GLdouble t)
{
  next_glTexCoord2d(s, t);
  printGLError();

  debugPrint("glTexCoord2d(s= %f, t= %f)\n", s, t);
}

void glTexCoord2dv(const GLdouble* v)
{
  next_glTexCoord2dv(v);
  printGLError();

  debugPrint("glTexCoord2dv(v= %x)\n", v);
}

void glTexCoord2f(GLfloat s, GLfloat t)
{
  next_glTexCoord2f(s, t);
  printGLError();

  debugPrint("glTexCoord2f(s= %f, t= %f)\n", s, t);
}

void glTexCoord2i(GLint s, GLint t)
{
  next_glTexCoord2i(s, t);
  printGLError();

  debugPrint("glTexCoord2i(s= %i, t= %i)\n", s, t);
}

void glTexCoord2iv(const GLint* v)
{
  next_glTexCoord2iv(v);
  printGLError();

  debugPrint("glTexCoord2iv(v= %x)\n", v);
}

void glTexCoord2s(GLshort s, GLshort t)
{
  next_glTexCoord2s(s, t);
  printGLError();

  debugPrint("glTexCoord2s(s= %i, t= %i)\n", s, t);
}

void glTexCoord2sv(const GLshort* v)
{
  next_glTexCoord2sv(v);
  printGLError();

  debugPrint("glTexCoord2sv(v= %x)\n", v);
}

void glTexCoord3d(GLdouble s, GLdouble t, GLdouble r)
{
  next_glTexCoord3d(s, t, r);
  printGLError();

  debugPrint("glTexCoord3d(s= %f, t= %f, r= %f)\n", s, t, r);
}

void glTexCoord3dv(const GLdouble* v)
{
  next_glTexCoord3dv(v);
  printGLError();

  debugPrint("glTexCoord3dv(v= %x)\n", v);
}

void glTexCoord3f(GLfloat s, GLfloat t, GLfloat r)
{
  next_glTexCoord3f(s, t, r);
  printGLError();

  debugPrint("glTexCoord3f(s= %f, t= %f, r= %f)\n", s, t, r);
}

void glTexCoord3fv(const GLfloat* v)
{
  next_glTexCoord3fv(v);
  printGLError();

  debugPrint("glTexCoord3fv(v= %x)\n", v);
}

void glTexCoord3i(GLint s, GLint t, GLint r)
{
  next_glTexCoord3i(s, t, r);
  printGLError();

  debugPrint("glTexCoord3i(s= %i, t= %i, r= %i)\n", s, t, r);
}

void glTexCoord3iv(const GLint* v)
{
  next_glTexCoord3iv(v);
  printGLError();

  debugPrint("glTexCoord3iv(v= %x)\n", v);
}

void glTexCoord3s(GLshort s, GLshort t, GLshort r)
{
  next_glTexCoord3s(s, t, r);
  printGLError();

  debugPrint("glTexCoord3s(s= %i, t= %i, r= %i)\n", s, t, r);
}

void glTexCoord3sv(const GLshort* v)
{
  next_glTexCoord3sv(v);
  printGLError();

  debugPrint("glTexCoord3sv(v= %x)\n", v);
}

void glTexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q)
{
  next_glTexCoord4d(s, t, r, q);
  printGLError();

  debugPrint("glTexCoord4d(s= %f, t= %f, r= %f, q= %f)\n", s, t, r, q);
}

void glTexCoord4dv(const GLdouble* v)
{
  next_glTexCoord4dv(v);
  printGLError();

  debugPrint("glTexCoord4dv(v= %x)\n", v);
}

void glTexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
  next_glTexCoord4f(s, t, r, q);
  printGLError();

  debugPrint("glTexCoord4f(s= %f, t= %f, r= %f, q= %f)\n", s, t, r, q);
}

void glTexCoord4fv(const GLfloat* v)
{
  next_glTexCoord4fv(v);
  printGLError();

  debugPrint("glTexCoord4fv(v= %x)\n", v);
}

void glTexCoord4i(GLint s, GLint t, GLint r, GLint q)
{
  next_glTexCoord4i(s, t, r, q);
  printGLError();

  debugPrint("glTexCoord4i(s= %i, t= %i, r= %i, q= %i)\n", s, t, r, q);
}

void glTexCoord4iv(const GLint* v)
{
  next_glTexCoord4iv(v);
  printGLError();

  debugPrint("glTexCoord4iv(v= %x)\n", v);
}

void glTexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q)
{
  next_glTexCoord4s(s, t, r, q);
  printGLError();

  debugPrint("glTexCoord4s(s= %i, t= %i, r= %i, q= %i)\n", s, t, r, q);
}

void glTexCoord4sv(const GLshort* v)
{
  next_glTexCoord4sv(v);
  printGLError();

  debugPrint("glTexCoord4sv(v= %x)\n", v);
}

void glTexEnvf(GLenum target, GLenum pname, GLfloat param)
{
  next_glTexEnvf(target, pname, param);
  printGLError();

  debugPrint("glTexEnvf(target= %s, pname= %s, param= %f)\n", getEnumString(target), getEnumString(pname), param);
}

void glTexEnvfv(GLenum target, GLenum pname, const GLfloat* params)
{
  next_glTexEnvfv(target, pname, params);
  printGLError();

  debugPrint("glTexEnvfv(target= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(pname), params);
}

void glTexEnvi(GLenum target, GLenum pname, GLint param)
{
  next_glTexEnvi(target, pname, param);
  printGLError();

  debugPrint("glTexEnvi(target= %s, pname= %s, param= %i)\n", getEnumString(target), getEnumString(pname), param);
}

void glTexEnviv(GLenum target, GLenum pname, const GLint* params)
{
  next_glTexEnviv(target, pname, params);
  printGLError();

  debugPrint("glTexEnviv(target= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(pname), params);
}

void glTexGend(GLenum coord, GLenum pname, GLdouble param)
{
  next_glTexGend(coord, pname, param);
  printGLError();

  debugPrint("glTexGend(coord= %s, pname= %s, param= %f)\n", getEnumString(coord), getEnumString(pname), param);
}

void glTexGendv(GLenum coord, GLenum pname, const GLdouble* params)
{
  next_glTexGendv(coord, pname, params);
  printGLError();

  debugPrint("glTexGendv(coord= %s, pname= %s, params= %x)\n", getEnumString(coord), getEnumString(pname), params);
}

void glTexGenf(GLenum coord, GLenum pname, GLfloat param)
{
  next_glTexGenf(coord, pname, param);
  printGLError();

  debugPrint("glTexGenf(coord= %s, pname= %s, param= %f)\n", getEnumString(coord), getEnumString(pname), param);
}

void glTexGenfv(GLenum coord, GLenum pname, const GLfloat* params)
{
  next_glTexGenfv(coord, pname, params);
  printGLError();

  debugPrint("glTexGenfv(coord= %s, pname= %s, params= %x)\n", getEnumString(coord), getEnumString(pname), params);
}

void glTexGeni(GLenum coord, GLenum pname, GLint param)
{
  next_glTexGeni(coord, pname, param);
  printGLError();

  debugPrint("glTexGeni(coord= %s, pname= %s, param= %i)\n", getEnumString(coord), getEnumString(pname), param);
}

void glTexGeniv(GLenum coord, GLenum pname, const GLint* params)
{
  next_glTexGeniv(coord, pname, params);
  printGLError();

  debugPrint("glTexGeniv(coord= %s, pname= %s, params= %x)\n", getEnumString(coord), getEnumString(pname), params);
}

void glTexParameterf(GLenum target, GLenum pname, GLfloat param)
{
  next_glTexParameterf(target, pname, param);
  printGLError();

  debugPrint("glTexParameterf(target= %s, pname= %s, param= %f)\n", getEnumString(target), getEnumString(pname), param);
}

void glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params)
{
  next_glTexParameterfv(target, pname, params);
  printGLError();

  debugPrint("glTexParameterfv(target= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(pname), params);
}

void glTexParameteri(GLenum target, GLenum pname, GLint param)
{
  next_glTexParameteri(target, pname, param);
  printGLError();

  debugPrint("glTexParameteri(target= %s, pname= %s, param= %i)\n", getEnumString(target), getEnumString(pname), param);
}

void glTexParameteriv(GLenum target, GLenum pname, const GLint* params)
{
  next_glTexParameteriv(target, pname, params);
  printGLError();

  debugPrint("glTexParameteriv(target= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(pname), params);
}

void glVertex2dv(const GLdouble* v)
{
  next_glVertex2dv(v);
  printGLError();

  debugPrint("glVertex2dv(v= %x)\n", v);
}

void glVertex2f(GLfloat x, GLfloat y)
{
  next_glVertex2f(x, y);
  printGLError();

  debugPrint("glVertex2f(x= %f, y= %f)\n", x, y);
}

void glVertex2fv(const GLfloat* v)
{
  next_glVertex2fv(v);
  printGLError();

  debugPrint("glVertex2fv(v= %x)\n", v);
}

void glVertex2i(GLint x, GLint y)
{
  next_glVertex2i(x, y);
  printGLError();

  debugPrint("glVertex2i(x= %i, y= %i)\n", x, y);
}

void glVertex2iv(const GLint* v)
{
  next_glVertex2iv(v);
  printGLError();

  debugPrint("glVertex2iv(v= %x)\n", v);
}

void glVertex2s(GLshort x, GLshort y)
{
  next_glVertex2s(x, y);
  printGLError();

  debugPrint("glVertex2s(x= %i, y= %i)\n", x, y);
}

void glVertex2sv(const GLshort* v)
{
  next_glVertex2sv(v);
  printGLError();

  debugPrint("glVertex2sv(v= %x)\n", v);
}

void glVertex3i(GLint x, GLint y, GLint z)
{
  next_glVertex3i(x, y, z);
  printGLError();

  debugPrint("glVertex3i(x= %i, y= %i, z= %i)\n", x, y, z);
}

void glVertex3s(GLshort x, GLshort y, GLshort z)
{
  next_glVertex3s(x, y, z);
  printGLError();

  debugPrint("glVertex3s(x= %i, y= %i, z= %i)\n", x, y, z);
}

void glVertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
  next_glVertex4d(x, y, z, w);
  printGLError();

  debugPrint("glVertex4d(x= %f, y= %f, z= %f, w= %f)\n", x, y, z, w);
}

void glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
  next_glVertex4f(x, y, z, w);
  printGLError();

  debugPrint("glVertex4f(x= %f, y= %f, z= %f, w= %f)\n", x, y, z, w);
}

void glVertex4i(GLint x, GLint y, GLint z, GLint w)
{
  next_glVertex4i(x, y, z, w);
  printGLError();

  debugPrint("glVertex4i(x= %i, y= %i, z= %i, w= %i)\n", x, y, z, w);
}

void glVertex4s(GLshort x, GLshort y, GLshort z, GLshort w)
{
  next_glVertex4s(x, y, z, w);
  printGLError();

  debugPrint("glVertex4s(x= %i, y= %i, z= %i, w= %i)\n", x, y, z, w);
}


// GL_VERSION_1_1

GLboolean glAreTexturesResident(GLsizei n, const GLuint* textures, GLboolean* residences)
{
  GLboolean result= next_glAreTexturesResident(n, textures, residences);
  printGLError();

  debugPrint("glAreTexturesResident(n= %u, textures= %x, residences= %x)= %i\n", n, textures, residences, result);

  return result;
}

void glArrayElement(GLint i)
{
  next_glArrayElement(i);
  printGLError();

  debugPrint("glArrayElement(i= %i)\n", i);
}

void glBindTexture(GLenum target, GLuint texture)
{
  next_glBindTexture(target, texture);
  printGLError();

  debugPrint("glBindTexture(target= %s, texture= %u)\n", getEnumString(target), texture);
}

void glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
{
  next_glCopyTexImage1D(target, level, internalformat, x, y, width, border);
  printGLError();

  debugPrint("glCopyTexImage1D(target= %s, level= %i, internalformat= %s, x= %i, y= %i, width= %u, border= %i)\n", getEnumString(target), level, getEnumString(internalformat), x, y, width, border);
}

void glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
  next_glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
  printGLError();

  debugPrint("glCopyTexImage2D(target= %s, level= %i, internalformat= %s, x= %i, y= %i, width= %u, height= %u, border= %i)\n", getEnumString(target), level, getEnumString(internalformat), x, y, width, height, border);
}

void glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
  next_glCopyTexSubImage1D(target, level, xoffset, x, y, width);
  printGLError();

  debugPrint("glCopyTexSubImage1D(target= %s, level= %i, xoffset= %i, x= %i, y= %i, width= %u)\n", getEnumString(target), level, xoffset, x, y, width);
}

void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
  next_glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
  printGLError();

  debugPrint("glCopyTexSubImage2D(target= %s, level= %i, xoffset= %i, yoffset= %i, x= %i, y= %i, width= %u, height= %u)\n", getEnumString(target), level, xoffset, yoffset, x, y, width, height);
}

void glDeleteTextures(GLsizei n, const GLuint* textures)
{
  next_glDeleteTextures(n, textures);
  printGLError();

  debugPrint("glDeleteTextures(n= %u, textures= %x)\n", n, textures);
}

void glEdgeFlagPointer(GLsizei stride, const void * pointer)
{
  next_glEdgeFlagPointer(stride, pointer);
  printGLError();

  debugPrint("glEdgeFlagPointer(stride= %u, pointer= %x)\n", stride, pointer);
}

void glGenTextures(GLsizei n, GLuint* textures)
{
  next_glGenTextures(n, textures);
  printGLError();

  debugPrint("glGenTextures(n= %u, textures= %x)\n", n, textures);
}

void glGetPointerv(GLenum pname, void ** params)
{
  next_glGetPointerv(pname, params);
  printGLError();

  debugPrint("glGetPointerv(pname= %s, params= %x)\n", getEnumString(pname), params);
}

void glIndexPointer(GLenum type, GLsizei stride, const void * pointer)
{
  next_glIndexPointer(type, stride, pointer);
  printGLError();

  debugPrint("glIndexPointer(type= %s, stride= %u, pointer= %x)\n", getEnumString(type), stride, pointer);
}

void glIndexub(GLubyte c)
{
  next_glIndexub(c);
  printGLError();

  debugPrint("glIndexub(c= %x)\n", c);
}

void glIndexubv(const GLubyte* c)
{
  next_glIndexubv(c);
  printGLError();

  debugPrint("glIndexubv(c= %x)\n", c);
}

void glInterleavedArrays(GLenum format, GLsizei stride, const void * pointer)
{
  next_glInterleavedArrays(format, stride, pointer);
  printGLError();

  debugPrint("glInterleavedArrays(format= %s, stride= %u, pointer= %x)\n", getEnumString(format), stride, pointer);
}

GLboolean glIsTexture(GLuint texture)
{
  GLboolean result= next_glIsTexture(texture);
  printGLError();

  debugPrint("glIsTexture(texture= %u)= %i\n", texture, result);

  return result;
}

void glNormalPointer(GLenum type, GLsizei stride, const void * pointer)
{
  next_glNormalPointer(type, stride, pointer);
  printGLError();

  debugPrint("glNormalPointer(type= %s, stride= %u, pointer= %x)\n", getEnumString(type), stride, pointer);
}

void glPolygonOffset(GLfloat factor, GLfloat units)
{
  next_glPolygonOffset(factor, units);
  printGLError();

  debugPrint("glPolygonOffset(factor= %f, units= %f)\n", factor, units);
}

void glPopClientAttrib()
{
  next_glPopClientAttrib();
  printGLError();

  debugPrint("glPopClientAttrib()\n");
}

void glPrioritizeTextures(GLsizei n, const GLuint* textures, const GLfloat* priorities)
{
  next_glPrioritizeTextures(n, textures, priorities);
  printGLError();

  debugPrint("glPrioritizeTextures(n= %u, textures= %x, priorities= %x)\n", n, textures, priorities);
}

void glPushClientAttrib(GLbitfield mask)
{
  next_glPushClientAttrib(mask);
  printGLError();

  debugPrint("glPushClientAttrib(mask= %x)\n", mask);
}

void glTexCoordPointer(GLint size, GLenum type, GLsizei stride, const void * pointer)
{
  next_glTexCoordPointer(size, type, stride, pointer);
  printGLError();

  debugPrint("glTexCoordPointer(size= %i, type= %s, stride= %u, pointer= %x)\n", size, getEnumString(type), stride, pointer);
}

void glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels)
{
  next_glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
  printGLError();

  debugPrint("glTexSubImage1D(target= %s, level= %i, xoffset= %i, width= %u, format= %s, type= %s, pixels= %x)\n", getEnumString(target), level, xoffset, width, getEnumString(format), getEnumString(type), pixels);
}

void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels)
{
  next_glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
  printGLError();

  debugPrint("glTexSubImage2D(target= %s, level= %i, xoffset= %i, yoffset= %i, width= %u, height= %u, format= %s, type= %s, pixels= %x)\n", getEnumString(target), level, xoffset, yoffset, width, height, getEnumString(format), getEnumString(type), pixels);
}


// GL_VERSION_1_2

void glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
  next_glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
  printGLError();

  debugPrint("glCopyTexSubImage3D(target= %s, level= %i, xoffset= %i, yoffset= %i, zoffset= %i, x= %i, y= %i, width= %u, height= %u)\n", getEnumString(target), level, xoffset, yoffset, zoffset, x, y, width, height);
}

void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices)
{
  next_glDrawRangeElements(mode, start, end, count, type, indices);
  printGLError();

  debugPrint("glDrawRangeElements(mode= %s, start= %u, end= %u, count= %u, type= %s, indices= %x)\n", getEnumString(mode), start, end, count, getEnumString(type), indices);
}

void glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels)
{
  next_glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
  printGLError();

  debugPrint("glTexImage3D(target= %s, level= %i, internalformat= %i, width= %u, height= %u, depth= %u, border= %i, format= %s, type= %s, pixels= %x)\n", getEnumString(target), level, internalformat, width, height, depth, border, getEnumString(format), getEnumString(type), pixels);
}

void glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels)
{
  next_glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
  printGLError();

  debugPrint("glTexSubImage3D(target= %s, level= %i, xoffset= %i, yoffset= %i, zoffset= %i, width= %u, height= %u, depth= %u, format= %s, type= %s, pixels= %x)\n", getEnumString(target), level, xoffset, yoffset, zoffset, width, height, depth, getEnumString(format), getEnumString(type), pixels);
}


// GL_VERSION_1_3

void glActiveTexture(GLenum texture)
{
  next_glActiveTexture(texture);
  printGLError();

  debugPrint("glActiveTexture(texture= %s)\n", getEnumString(texture));
}

void glClientActiveTexture(GLenum texture)
{
  next_glClientActiveTexture(texture);
  printGLError();

  debugPrint("glClientActiveTexture(texture= %s)\n", getEnumString(texture));
}

void glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data)
{
  next_glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
  printGLError();

  debugPrint("glCompressedTexImage1D(target= %s, level= %i, internalformat= %s, width= %u, border= %i, imageSize= %u, data= %x)\n", getEnumString(target), level, getEnumString(internalformat), width, border, imageSize, data);
}

void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data)
{
  next_glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
  printGLError();

  debugPrint("glCompressedTexImage2D(target= %s, level= %i, internalformat= %s, width= %u, height= %u, border= %i, imageSize= %u, data= %x)\n", getEnumString(target), level, getEnumString(internalformat), width, height, border, imageSize, data);
}

void glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data)
{
  next_glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
  printGLError();

  debugPrint("glCompressedTexImage3D(target= %s, level= %i, internalformat= %s, width= %u, height= %u, depth= %u, border= %i, imageSize= %u, data= %x)\n", getEnumString(target), level, getEnumString(internalformat), width, height, depth, border, imageSize, data);
}

void glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data)
{
  next_glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
  printGLError();

  debugPrint("glCompressedTexSubImage1D(target= %s, level= %i, xoffset= %i, width= %u, format= %s, imageSize= %u, data= %x)\n", getEnumString(target), level, xoffset, width, getEnumString(format), imageSize, data);
}

void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data)
{
  next_glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
  printGLError();

  debugPrint("glCompressedTexSubImage2D(target= %s, level= %i, xoffset= %i, yoffset= %i, width= %u, height= %u, format= %s, imageSize= %u, data= %x)\n", getEnumString(target), level, xoffset, yoffset, width, height, getEnumString(format), imageSize, data);
}

void glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data)
{
  next_glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
  printGLError();

  debugPrint("glCompressedTexSubImage3D(target= %s, level= %i, xoffset= %i, yoffset= %i, zoffset= %i, width= %u, height= %u, depth= %u, format= %s, imageSize= %u, data= %x)\n", getEnumString(target), level, xoffset, yoffset, zoffset, width, height, depth, getEnumString(format), imageSize, data);
}

void glGetCompressedTexImage(GLenum target, GLint level, void * img)
{
  next_glGetCompressedTexImage(target, level, img);
  printGLError();

  debugPrint("glGetCompressedTexImage(target= %s, level= %i, img= %x)\n", getEnumString(target), level, img);
}

void glLoadTransposeMatrixd(const GLdouble* m)
{
  next_glLoadTransposeMatrixd(m);
  printGLError();

  debugPrint("glLoadTransposeMatrixd(m= %x)\n", m);
}

void glLoadTransposeMatrixf(const GLfloat* m)
{
  next_glLoadTransposeMatrixf(m);
  printGLError();

  debugPrint("glLoadTransposeMatrixf(m= %x)\n", m);
}

void glMultTransposeMatrixd(const GLdouble* m)
{
  next_glMultTransposeMatrixd(m);
  printGLError();

  debugPrint("glMultTransposeMatrixd(m= %x)\n", m);
}

void glMultTransposeMatrixf(const GLfloat* m)
{
  next_glMultTransposeMatrixf(m);
  printGLError();

  debugPrint("glMultTransposeMatrixf(m= %x)\n", m);
}

void glMultiTexCoord1d(GLenum target, GLdouble s)
{
  next_glMultiTexCoord1d(target, s);
  printGLError();

  debugPrint("glMultiTexCoord1d(target= %s, s= %f)\n", getEnumString(target), s);
}

void glMultiTexCoord1dv(GLenum target, const GLdouble* v)
{
  next_glMultiTexCoord1dv(target, v);
  printGLError();

  debugPrint("glMultiTexCoord1dv(target= %s, v= %x)\n", getEnumString(target), v);
}

void glMultiTexCoord1f(GLenum target, GLfloat s)
{
  next_glMultiTexCoord1f(target, s);
  printGLError();

  debugPrint("glMultiTexCoord1f(target= %s, s= %f)\n", getEnumString(target), s);
}

void glMultiTexCoord1fv(GLenum target, const GLfloat* v)
{
  next_glMultiTexCoord1fv(target, v);
  printGLError();

  debugPrint("glMultiTexCoord1fv(target= %s, v= %x)\n", getEnumString(target), v);
}

void glMultiTexCoord1i(GLenum target, GLint s)
{
  next_glMultiTexCoord1i(target, s);
  printGLError();

  debugPrint("glMultiTexCoord1i(target= %s, s= %i)\n", getEnumString(target), s);
}

void glMultiTexCoord1iv(GLenum target, const GLint* v)
{
  next_glMultiTexCoord1iv(target, v);
  printGLError();

  debugPrint("glMultiTexCoord1iv(target= %s, v= %x)\n", getEnumString(target), v);
}

void glMultiTexCoord1s(GLenum target, GLshort s)
{
  next_glMultiTexCoord1s(target, s);
  printGLError();

  debugPrint("glMultiTexCoord1s(target= %s, s= %i)\n", getEnumString(target), s);
}

void glMultiTexCoord1sv(GLenum target, const GLshort* v)
{
  next_glMultiTexCoord1sv(target, v);
  printGLError();

  debugPrint("glMultiTexCoord1sv(target= %s, v= %x)\n", getEnumString(target), v);
}

void glMultiTexCoord2d(GLenum target, GLdouble s, GLdouble t)
{
  next_glMultiTexCoord2d(target, s, t);
  printGLError();

  debugPrint("glMultiTexCoord2d(target= %s, s= %f, t= %f)\n", getEnumString(target), s, t);
}

void glMultiTexCoord2dv(GLenum target, const GLdouble* v)
{
  next_glMultiTexCoord2dv(target, v);
  printGLError();

  debugPrint("glMultiTexCoord2dv(target= %s, v= %x)\n", getEnumString(target), v);
}

void glMultiTexCoord2f(GLenum target, GLfloat s, GLfloat t)
{
  next_glMultiTexCoord2f(target, s, t);
  printGLError();

  debugPrint("glMultiTexCoord2f(target= %s, s= %f, t= %f)\n", getEnumString(target), s, t);
}

void glMultiTexCoord2fv(GLenum target, const GLfloat* v)
{
  next_glMultiTexCoord2fv(target, v);
  printGLError();

  debugPrint("glMultiTexCoord2fv(target= %s, v= %x)\n", getEnumString(target), v);
}

void glMultiTexCoord2i(GLenum target, GLint s, GLint t)
{
  next_glMultiTexCoord2i(target, s, t);
  printGLError();

  debugPrint("glMultiTexCoord2i(target= %s, s= %i, t= %i)\n", getEnumString(target), s, t);
}

void glMultiTexCoord2iv(GLenum target, const GLint* v)
{
  next_glMultiTexCoord2iv(target, v);
  printGLError();

  debugPrint("glMultiTexCoord2iv(target= %s, v= %x)\n", getEnumString(target), v);
}

void glMultiTexCoord2s(GLenum target, GLshort s, GLshort t)
{
  next_glMultiTexCoord2s(target, s, t);
  printGLError();

  debugPrint("glMultiTexCoord2s(target= %s, s= %i, t= %i)\n", getEnumString(target), s, t);
}

void glMultiTexCoord2sv(GLenum target, const GLshort* v)
{
  next_glMultiTexCoord2sv(target, v);
  printGLError();

  debugPrint("glMultiTexCoord2sv(target= %s, v= %x)\n", getEnumString(target), v);
}

void glMultiTexCoord3d(GLenum target, GLdouble s, GLdouble t, GLdouble r)
{
  next_glMultiTexCoord3d(target, s, t, r);
  printGLError();

  debugPrint("glMultiTexCoord3d(target= %s, s= %f, t= %f, r= %f)\n", getEnumString(target), s, t, r);
}

void glMultiTexCoord3dv(GLenum target, const GLdouble* v)
{
  next_glMultiTexCoord3dv(target, v);
  printGLError();

  debugPrint("glMultiTexCoord3dv(target= %s, v= %x)\n", getEnumString(target), v);
}

void glMultiTexCoord3f(GLenum target, GLfloat s, GLfloat t, GLfloat r)
{
  next_glMultiTexCoord3f(target, s, t, r);
  printGLError();

  debugPrint("glMultiTexCoord3f(target= %s, s= %f, t= %f, r= %f)\n", getEnumString(target), s, t, r);
}

void glMultiTexCoord3fv(GLenum target, const GLfloat* v)
{
  next_glMultiTexCoord3fv(target, v);
  printGLError();

  debugPrint("glMultiTexCoord3fv(target= %s, v= %x)\n", getEnumString(target), v);
}

void glMultiTexCoord3i(GLenum target, GLint s, GLint t, GLint r)
{
  next_glMultiTexCoord3i(target, s, t, r);
  printGLError();

  debugPrint("glMultiTexCoord3i(target= %s, s= %i, t= %i, r= %i)\n", getEnumString(target), s, t, r);
}

void glMultiTexCoord3iv(GLenum target, const GLint* v)
{
  next_glMultiTexCoord3iv(target, v);
  printGLError();

  debugPrint("glMultiTexCoord3iv(target= %s, v= %x)\n", getEnumString(target), v);
}

void glMultiTexCoord3s(GLenum target, GLshort s, GLshort t, GLshort r)
{
  next_glMultiTexCoord3s(target, s, t, r);
  printGLError();

  debugPrint("glMultiTexCoord3s(target= %s, s= %i, t= %i, r= %i)\n", getEnumString(target), s, t, r);
}

void glMultiTexCoord3sv(GLenum target, const GLshort* v)
{
  next_glMultiTexCoord3sv(target, v);
  printGLError();

  debugPrint("glMultiTexCoord3sv(target= %s, v= %x)\n", getEnumString(target), v);
}

void glMultiTexCoord4d(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q)
{
  next_glMultiTexCoord4d(target, s, t, r, q);
  printGLError();

  debugPrint("glMultiTexCoord4d(target= %s, s= %f, t= %f, r= %f, q= %f)\n", getEnumString(target), s, t, r, q);
}

void glMultiTexCoord4dv(GLenum target, const GLdouble* v)
{
  next_glMultiTexCoord4dv(target, v);
  printGLError();

  debugPrint("glMultiTexCoord4dv(target= %s, v= %x)\n", getEnumString(target), v);
}

void glMultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
  next_glMultiTexCoord4f(target, s, t, r, q);
  printGLError();

  debugPrint("glMultiTexCoord4f(target= %s, s= %f, t= %f, r= %f, q= %f)\n", getEnumString(target), s, t, r, q);
}

void glMultiTexCoord4fv(GLenum target, const GLfloat* v)
{
  next_glMultiTexCoord4fv(target, v);
  printGLError();

  debugPrint("glMultiTexCoord4fv(target= %s, v= %x)\n", getEnumString(target), v);
}

void glMultiTexCoord4i(GLenum target, GLint s, GLint t, GLint r, GLint q)
{
  next_glMultiTexCoord4i(target, s, t, r, q);
  printGLError();

  debugPrint("glMultiTexCoord4i(target= %s, s= %i, t= %i, r= %i, q= %i)\n", getEnumString(target), s, t, r, q);
}

void glMultiTexCoord4iv(GLenum target, const GLint* v)
{
  next_glMultiTexCoord4iv(target, v);
  printGLError();

  debugPrint("glMultiTexCoord4iv(target= %s, v= %x)\n", getEnumString(target), v);
}

void glMultiTexCoord4s(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q)
{
  next_glMultiTexCoord4s(target, s, t, r, q);
  printGLError();

  debugPrint("glMultiTexCoord4s(target= %s, s= %i, t= %i, r= %i, q= %i)\n", getEnumString(target), s, t, r, q);
}

void glMultiTexCoord4sv(GLenum target, const GLshort* v)
{
  next_glMultiTexCoord4sv(target, v);
  printGLError();

  debugPrint("glMultiTexCoord4sv(target= %s, v= %x)\n", getEnumString(target), v);
}

void glSampleCoverage(GLfloat value, GLboolean invert)
{
  next_glSampleCoverage(value, invert);
  printGLError();

  debugPrint("glSampleCoverage(value= %f, invert= %i)\n", value, invert);
}


// GL_VERSION_1_4

void glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  next_glBlendColor(red, green, blue, alpha);
  printGLError();

  debugPrint("glBlendColor(red= %f, green= %f, blue= %f, alpha= %f)\n", red, green, blue, alpha);
}

void glBlendEquation(GLenum mode)
{
  next_glBlendEquation(mode);
  printGLError();

  debugPrint("glBlendEquation(mode= %s)\n", getEnumString(mode));
}

void glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
  next_glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
  printGLError();

  debugPrint("glBlendFuncSeparate(sfactorRGB= %s, dfactorRGB= %s, sfactorAlpha= %s, dfactorAlpha= %s)\n", getEnumString(sfactorRGB), getEnumString(dfactorRGB), getEnumString(sfactorAlpha), getEnumString(dfactorAlpha));
}

void glFogCoordPointer(GLenum type, GLsizei stride, const void * pointer)
{
  next_glFogCoordPointer(type, stride, pointer);
  printGLError();

  debugPrint("glFogCoordPointer(type= %s, stride= %u, pointer= %x)\n", getEnumString(type), stride, pointer);
}

void glFogCoordd(GLdouble coord)
{
  next_glFogCoordd(coord);
  printGLError();

  debugPrint("glFogCoordd(coord= %f)\n", coord);
}

void glFogCoorddv(const GLdouble* coord)
{
  next_glFogCoorddv(coord);
  printGLError();

  debugPrint("glFogCoorddv(coord= %x)\n", coord);
}

void glFogCoordf(GLfloat coord)
{
  next_glFogCoordf(coord);
  printGLError();

  debugPrint("glFogCoordf(coord= %f)\n", coord);
}

void glFogCoordfv(const GLfloat* coord)
{
  next_glFogCoordfv(coord);
  printGLError();

  debugPrint("glFogCoordfv(coord= %x)\n", coord);
}

void glMultiDrawArrays(GLenum mode, const GLint* first, const GLsizei* count, GLsizei drawcount)
{
  next_glMultiDrawArrays(mode, first, count, drawcount);
  printGLError();

  debugPrint("glMultiDrawArrays(mode= %s, first= %x, count= %x, drawcount= %u)\n", getEnumString(mode), first, count, drawcount);
}

void glMultiDrawElements(GLenum mode, const GLsizei* count, GLenum type, const void *const* indices, GLsizei drawcount)
{
  next_glMultiDrawElements(mode, count, type, indices, drawcount);
  printGLError();

  debugPrint("glMultiDrawElements(mode= %s, count= %x, type= %s, indices= %x, drawcount= %u)\n", getEnumString(mode), count, getEnumString(type), indices, drawcount);
}

void glPointParameterf(GLenum pname, GLfloat param)
{
  next_glPointParameterf(pname, param);
  printGLError();

  debugPrint("glPointParameterf(pname= %s, param= %f)\n", getEnumString(pname), param);
}

void glPointParameterfv(GLenum pname, const GLfloat* params)
{
  next_glPointParameterfv(pname, params);
  printGLError();

  debugPrint("glPointParameterfv(pname= %s, params= %x)\n", getEnumString(pname), params);
}

void glPointParameteri(GLenum pname, GLint param)
{
  next_glPointParameteri(pname, param);
  printGLError();

  debugPrint("glPointParameteri(pname= %s, param= %i)\n", getEnumString(pname), param);
}

void glPointParameteriv(GLenum pname, const GLint* params)
{
  next_glPointParameteriv(pname, params);
  printGLError();

  debugPrint("glPointParameteriv(pname= %s, params= %x)\n", getEnumString(pname), params);
}

void glSecondaryColor3b(GLbyte red, GLbyte green, GLbyte blue)
{
  next_glSecondaryColor3b(red, green, blue);
  printGLError();

  debugPrint("glSecondaryColor3b(red= %i, green= %i, blue= %i)\n", red, green, blue);
}

void glSecondaryColor3bv(const GLbyte* v)
{
  next_glSecondaryColor3bv(v);
  printGLError();

  debugPrint("glSecondaryColor3bv(v= %x)\n", v);
}

void glSecondaryColor3d(GLdouble red, GLdouble green, GLdouble blue)
{
  next_glSecondaryColor3d(red, green, blue);
  printGLError();

  debugPrint("glSecondaryColor3d(red= %f, green= %f, blue= %f)\n", red, green, blue);
}

void glSecondaryColor3dv(const GLdouble* v)
{
  next_glSecondaryColor3dv(v);
  printGLError();

  debugPrint("glSecondaryColor3dv(v= %x)\n", v);
}

void glSecondaryColor3f(GLfloat red, GLfloat green, GLfloat blue)
{
  next_glSecondaryColor3f(red, green, blue);
  printGLError();

  debugPrint("glSecondaryColor3f(red= %f, green= %f, blue= %f)\n", red, green, blue);
}

void glSecondaryColor3fv(const GLfloat* v)
{
  next_glSecondaryColor3fv(v);
  printGLError();

  debugPrint("glSecondaryColor3fv(v= %x)\n", v);
}

void glSecondaryColor3i(GLint red, GLint green, GLint blue)
{
  next_glSecondaryColor3i(red, green, blue);
  printGLError();

  debugPrint("glSecondaryColor3i(red= %i, green= %i, blue= %i)\n", red, green, blue);
}

void glSecondaryColor3iv(const GLint* v)
{
  next_glSecondaryColor3iv(v);
  printGLError();

  debugPrint("glSecondaryColor3iv(v= %x)\n", v);
}

void glSecondaryColor3s(GLshort red, GLshort green, GLshort blue)
{
  next_glSecondaryColor3s(red, green, blue);
  printGLError();

  debugPrint("glSecondaryColor3s(red= %i, green= %i, blue= %i)\n", red, green, blue);
}

void glSecondaryColor3sv(const GLshort* v)
{
  next_glSecondaryColor3sv(v);
  printGLError();

  debugPrint("glSecondaryColor3sv(v= %x)\n", v);
}

void glSecondaryColor3ub(GLubyte red, GLubyte green, GLubyte blue)
{
  next_glSecondaryColor3ub(red, green, blue);
  printGLError();

  debugPrint("glSecondaryColor3ub(red= %x, green= %x, blue= %x)\n", red, green, blue);
}

void glSecondaryColor3ubv(const GLubyte* v)
{
  next_glSecondaryColor3ubv(v);
  printGLError();

  debugPrint("glSecondaryColor3ubv(v= %x)\n", v);
}

void glSecondaryColor3ui(GLuint red, GLuint green, GLuint blue)
{
  next_glSecondaryColor3ui(red, green, blue);
  printGLError();

  debugPrint("glSecondaryColor3ui(red= %u, green= %u, blue= %u)\n", red, green, blue);
}

void glSecondaryColor3uiv(const GLuint* v)
{
  next_glSecondaryColor3uiv(v);
  printGLError();

  debugPrint("glSecondaryColor3uiv(v= %x)\n", v);
}

void glSecondaryColor3us(GLushort red, GLushort green, GLushort blue)
{
  next_glSecondaryColor3us(red, green, blue);
  printGLError();

  debugPrint("glSecondaryColor3us(red= %u, green= %u, blue= %u)\n", red, green, blue);
}

void glSecondaryColor3usv(const GLushort* v)
{
  next_glSecondaryColor3usv(v);
  printGLError();

  debugPrint("glSecondaryColor3usv(v= %x)\n", v);
}

void glSecondaryColorPointer(GLint size, GLenum type, GLsizei stride, const void * pointer)
{
  next_glSecondaryColorPointer(size, type, stride, pointer);
  printGLError();

  debugPrint("glSecondaryColorPointer(size= %i, type= %s, stride= %u, pointer= %x)\n", size, getEnumString(type), stride, pointer);
}

void glWindowPos2d(GLdouble x, GLdouble y)
{
  next_glWindowPos2d(x, y);
  printGLError();

  debugPrint("glWindowPos2d(x= %f, y= %f)\n", x, y);
}

void glWindowPos2dv(const GLdouble* v)
{
  next_glWindowPos2dv(v);
  printGLError();

  debugPrint("glWindowPos2dv(v= %x)\n", v);
}

void glWindowPos2f(GLfloat x, GLfloat y)
{
  next_glWindowPos2f(x, y);
  printGLError();

  debugPrint("glWindowPos2f(x= %f, y= %f)\n", x, y);
}

void glWindowPos2fv(const GLfloat* v)
{
  next_glWindowPos2fv(v);
  printGLError();

  debugPrint("glWindowPos2fv(v= %x)\n", v);
}

void glWindowPos2i(GLint x, GLint y)
{
  next_glWindowPos2i(x, y);
  printGLError();

  debugPrint("glWindowPos2i(x= %i, y= %i)\n", x, y);
}

void glWindowPos2iv(const GLint* v)
{
  next_glWindowPos2iv(v);
  printGLError();

  debugPrint("glWindowPos2iv(v= %x)\n", v);
}

void glWindowPos2s(GLshort x, GLshort y)
{
  next_glWindowPos2s(x, y);
  printGLError();

  debugPrint("glWindowPos2s(x= %i, y= %i)\n", x, y);
}

void glWindowPos2sv(const GLshort* v)
{
  next_glWindowPos2sv(v);
  printGLError();

  debugPrint("glWindowPos2sv(v= %x)\n", v);
}

void glWindowPos3d(GLdouble x, GLdouble y, GLdouble z)
{
  next_glWindowPos3d(x, y, z);
  printGLError();

  debugPrint("glWindowPos3d(x= %f, y= %f, z= %f)\n", x, y, z);
}

void glWindowPos3dv(const GLdouble* v)
{
  next_glWindowPos3dv(v);
  printGLError();

  debugPrint("glWindowPos3dv(v= %x)\n", v);
}

void glWindowPos3f(GLfloat x, GLfloat y, GLfloat z)
{
  next_glWindowPos3f(x, y, z);
  printGLError();

  debugPrint("glWindowPos3f(x= %f, y= %f, z= %f)\n", x, y, z);
}

void glWindowPos3fv(const GLfloat* v)
{
  next_glWindowPos3fv(v);
  printGLError();

  debugPrint("glWindowPos3fv(v= %x)\n", v);
}

void glWindowPos3i(GLint x, GLint y, GLint z)
{
  next_glWindowPos3i(x, y, z);
  printGLError();

  debugPrint("glWindowPos3i(x= %i, y= %i, z= %i)\n", x, y, z);
}

void glWindowPos3iv(const GLint* v)
{
  next_glWindowPos3iv(v);
  printGLError();

  debugPrint("glWindowPos3iv(v= %x)\n", v);
}

void glWindowPos3s(GLshort x, GLshort y, GLshort z)
{
  next_glWindowPos3s(x, y, z);
  printGLError();

  debugPrint("glWindowPos3s(x= %i, y= %i, z= %i)\n", x, y, z);
}

void glWindowPos3sv(const GLshort* v)
{
  next_glWindowPos3sv(v);
  printGLError();

  debugPrint("glWindowPos3sv(v= %x)\n", v);
}


// GL_VERSION_1_5

void glBeginQuery(GLenum target, GLuint id)
{
  next_glBeginQuery(target, id);
  printGLError();

  debugPrint("glBeginQuery(target= %s, id= %u)\n", getEnumString(target), id);
}

void glBindBuffer(GLenum target, GLuint buffer)
{
  next_glBindBuffer(target, buffer);
  printGLError();

  debugPrint("glBindBuffer(target= %s, buffer= %u)\n", getEnumString(target), buffer);
}

void glBufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage)
{
  next_glBufferData(target, size, data, usage);
  printGLError();

  debugPrint("glBufferData(target= %s, size= %u, data= %x, usage= %s)\n", getEnumString(target), size, data, getEnumString(usage));
}

void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data)
{
  next_glBufferSubData(target, offset, size, data);
  printGLError();

  debugPrint("glBufferSubData(target= %s, offset= %i, size= %u, data= %x)\n", getEnumString(target), offset, size, data);
}

void glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
  next_glDeleteBuffers(n, buffers);
  printGLError();

  debugPrint("glDeleteBuffers(n= %u, buffers= %x)\n", n, buffers);
}

void glDeleteQueries(GLsizei n, const GLuint* ids)
{
  next_glDeleteQueries(n, ids);
  printGLError();

  debugPrint("glDeleteQueries(n= %u, ids= %x)\n", n, ids);
}

void glEndQuery(GLenum target)
{
  next_glEndQuery(target);
  printGLError();

  debugPrint("glEndQuery(target= %s)\n", getEnumString(target));
}

void glGenBuffers(GLsizei n, GLuint* buffers)
{
  next_glGenBuffers(n, buffers);
  printGLError();

  debugPrint("glGenBuffers(n= %u, buffers= %x)\n", n, buffers);
}

void glGenQueries(GLsizei n, GLuint* ids)
{
  next_glGenQueries(n, ids);
  printGLError();

  debugPrint("glGenQueries(n= %u, ids= %x)\n", n, ids);
}

void glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
  next_glGetBufferParameteriv(target, pname, params);
  printGLError();

  debugPrint("glGetBufferParameteriv(target= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(pname), params);
}

void glGetBufferPointerv(GLenum target, GLenum pname, void ** params)
{
  next_glGetBufferPointerv(target, pname, params);
  printGLError();

  debugPrint("glGetBufferPointerv(target= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(pname), params);
}

void glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void * data)
{
  next_glGetBufferSubData(target, offset, size, data);
  printGLError();

  debugPrint("glGetBufferSubData(target= %s, offset= %i, size= %u, data= %x)\n", getEnumString(target), offset, size, data);
}

void glGetQueryObjectiv(GLuint id, GLenum pname, GLint* params)
{
  next_glGetQueryObjectiv(id, pname, params);
  printGLError();

  debugPrint("glGetQueryObjectiv(id= %u, pname= %s, params= %x)\n", id, getEnumString(pname), params);
}

void glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint* params)
{
  next_glGetQueryObjectuiv(id, pname, params);
  printGLError();

  debugPrint("glGetQueryObjectuiv(id= %u, pname= %s, params= %x)\n", id, getEnumString(pname), params);
}

void glGetQueryiv(GLenum target, GLenum pname, GLint* params)
{
  next_glGetQueryiv(target, pname, params);
  printGLError();

  debugPrint("glGetQueryiv(target= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(pname), params);
}

GLboolean glIsBuffer(GLuint buffer)
{
  GLboolean result= next_glIsBuffer(buffer);
  printGLError();

  debugPrint("glIsBuffer(buffer= %u)= %i\n", buffer, result);

  return result;
}

GLboolean glIsQuery(GLuint id)
{
  GLboolean result= next_glIsQuery(id);
  printGLError();

  debugPrint("glIsQuery(id= %u)= %i\n", id, result);

  return result;
}

void * glMapBuffer(GLenum target, GLenum access)
{
  void * result= next_glMapBuffer(target, access);
  printGLError();

  debugPrint("glMapBuffer(target= %s, access= %s)= %x\n", getEnumString(target), getEnumString(access), result);

  return result;
}

GLboolean glUnmapBuffer(GLenum target)
{
  GLboolean result= next_glUnmapBuffer(target);
  printGLError();

  debugPrint("glUnmapBuffer(target= %s)= %i\n", getEnumString(target), result);

  return result;
}


// GL_VERSION_2_0

void glAttachShader(GLuint program, GLuint shader)
{
  next_glAttachShader(program, shader);
  printGLError();

  debugPrint("glAttachShader(program= %u, shader= %u)\n", program, shader);
}

void glBindAttribLocation(GLuint program, GLuint index, const GLchar* name)
{
  next_glBindAttribLocation(program, index, name);
  printGLError();

  debugPrint("glBindAttribLocation(program= %u, index= %u, name= %x)\n", program, index, name);
}

void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
  next_glBlendEquationSeparate(modeRGB, modeAlpha);
  printGLError();

  debugPrint("glBlendEquationSeparate(modeRGB= %s, modeAlpha= %s)\n", getEnumString(modeRGB), getEnumString(modeAlpha));
}

void glCompileShader(GLuint shader)
{
  next_glCompileShader(shader);
  printGLError();

  debugPrint("glCompileShader(shader= %u)\n", shader);
}

GLuint glCreateProgram()
{
  GLuint result= next_glCreateProgram();
  printGLError();

  debugPrint("glCreateProgram()= %u\n", result);

  return result;
}

GLuint glCreateShader(GLenum type)
{
  GLuint result= next_glCreateShader(type);
  printGLError();

  debugPrint("glCreateShader(type= %s)= %u\n", getEnumString(type), result);

  return result;
}

void glDeleteProgram(GLuint program)
{
  next_glDeleteProgram(program);
  printGLError();

  debugPrint("glDeleteProgram(program= %u)\n", program);
}

void glDeleteShader(GLuint shader)
{
  next_glDeleteShader(shader);
  printGLError();

  debugPrint("glDeleteShader(shader= %u)\n", shader);
}

void glDetachShader(GLuint program, GLuint shader)
{
  next_glDetachShader(program, shader);
  printGLError();

  debugPrint("glDetachShader(program= %u, shader= %u)\n", program, shader);
}

void glDisableVertexAttribArray(GLuint index)
{
  next_glDisableVertexAttribArray(index);
  printGLError();

  debugPrint("glDisableVertexAttribArray(index= %u)\n", index);
}

void glDrawBuffers(GLsizei n, const GLenum* bufs)
{
  next_glDrawBuffers(n, bufs);
  printGLError();

  debugPrint("glDrawBuffers(n= %u, bufs= %x)\n", n, bufs);
}

void glEnableVertexAttribArray(GLuint index)
{
  next_glEnableVertexAttribArray(index);
  printGLError();

  debugPrint("glEnableVertexAttribArray(index= %u)\n", index);
}

void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
  next_glGetActiveAttrib(program, index, bufSize, length, size, type, name);
  printGLError();

  debugPrint("glGetActiveAttrib(program= %u, index= %u, bufSize= %u, length= %x, size= %x, type= %x, name= %s)\n", program, index, bufSize, length, size, type, name);
}

void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
  next_glGetActiveUniform(program, index, bufSize, length, size, type, name);
  printGLError();

  debugPrint("glGetActiveUniform(program= %u, index= %u, bufSize= %u, length= %x, size= %x, type= %x, name= %s)\n", program, index, bufSize, length, size, type, name);
}

void glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders)
{
  next_glGetAttachedShaders(program, maxCount, count, shaders);
  printGLError();

  debugPrint("glGetAttachedShaders(program= %u, maxCount= %u, count= %x, shaders= %x)\n", program, maxCount, count, shaders);
}

GLint glGetAttribLocation(GLuint program, const GLchar* name)
{
  GLint result= next_glGetAttribLocation(program, name);
  printGLError();

  debugPrint("glGetAttribLocation(program= %u, name= %x)= %i\n", program, name, result);

  return result;
}

void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
  next_glGetProgramInfoLog(program, bufSize, length, infoLog);
  printGLError();

  debugPrint("glGetProgramInfoLog(program= %u, bufSize= %u, length= %x, infoLog= %s)\n", program, bufSize, length, infoLog);
}

void glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
  next_glGetProgramiv(program, pname, params);
  printGLError();

  debugPrint("glGetProgramiv(program= %u, pname= %s, params= %x)\n", program, getEnumString(pname), params);
}

void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
  next_glGetShaderInfoLog(shader, bufSize, length, infoLog);
  printGLError();

  debugPrint("glGetShaderInfoLog(shader= %u, bufSize= %u, length= %x, infoLog= %s)\n", shader, bufSize, length, infoLog);
}

void glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source)
{
  next_glGetShaderSource(shader, bufSize, length, source);
  printGLError();

  debugPrint("glGetShaderSource(shader= %u, bufSize= %u, length= %x, source= %s)\n", shader, bufSize, length, source);
}

void glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{
  next_glGetShaderiv(shader, pname, params);
  printGLError();

  debugPrint("glGetShaderiv(shader= %u, pname= %s, params= %x)\n", shader, getEnumString(pname), params);
}

GLint glGetUniformLocation(GLuint program, const GLchar* name)
{
  GLint result= next_glGetUniformLocation(program, name);
  printGLError();

  debugPrint("glGetUniformLocation(program= %u, name= %x)= %i\n", program, name, result);

  return result;
}

void glGetUniformfv(GLuint program, GLint location, GLfloat* params)
{
  next_glGetUniformfv(program, location, params);
  printGLError();

  debugPrint("glGetUniformfv(program= %u, location= %i, params= %x)\n", program, location, params);
}

void glGetUniformiv(GLuint program, GLint location, GLint* params)
{
  next_glGetUniformiv(program, location, params);
  printGLError();

  debugPrint("glGetUniformiv(program= %u, location= %i, params= %x)\n", program, location, params);
}

void glGetVertexAttribPointerv(GLuint index, GLenum pname, void ** pointer)
{
  next_glGetVertexAttribPointerv(index, pname, pointer);
  printGLError();

  debugPrint("glGetVertexAttribPointerv(index= %u, pname= %s, pointer= %x)\n", index, getEnumString(pname), pointer);
}

void glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble* params)
{
  next_glGetVertexAttribdv(index, pname, params);
  printGLError();

  debugPrint("glGetVertexAttribdv(index= %u, pname= %s, params= %x)\n", index, getEnumString(pname), params);
}

void glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)
{
  next_glGetVertexAttribfv(index, pname, params);
  printGLError();

  debugPrint("glGetVertexAttribfv(index= %u, pname= %s, params= %x)\n", index, getEnumString(pname), params);
}

void glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params)
{
  next_glGetVertexAttribiv(index, pname, params);
  printGLError();

  debugPrint("glGetVertexAttribiv(index= %u, pname= %s, params= %x)\n", index, getEnumString(pname), params);
}

GLboolean glIsProgram(GLuint program)
{
  GLboolean result= next_glIsProgram(program);
  printGLError();

  debugPrint("glIsProgram(program= %u)= %i\n", program, result);

  return result;
}

GLboolean glIsShader(GLuint shader)
{
  GLboolean result= next_glIsShader(shader);
  printGLError();

  debugPrint("glIsShader(shader= %u)= %i\n", shader, result);

  return result;
}

void glLinkProgram(GLuint program)
{
  next_glLinkProgram(program);
  printGLError();

  debugPrint("glLinkProgram(program= %u)\n", program);
}

void glShaderSource(GLuint shader, GLsizei count, const GLchar*const* string, const GLint* length)
{
  next_glShaderSource(shader, count, string, length);
  printGLError();

  debugPrint("glShaderSource(shader= %u, count= %u, string= %x, length= %x)\n", shader, count, string, length);
}

void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
  next_glStencilFuncSeparate(face, func, ref, mask);
  printGLError();

  debugPrint("glStencilFuncSeparate(face= %s, func= %s, ref= %i, mask= %u)\n", getEnumString(face), getEnumString(func), ref, mask);
}

void glStencilMaskSeparate(GLenum face, GLuint mask)
{
  next_glStencilMaskSeparate(face, mask);
  printGLError();

  debugPrint("glStencilMaskSeparate(face= %s, mask= %u)\n", getEnumString(face), mask);
}

void glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
{
  next_glStencilOpSeparate(face, sfail, dpfail, dppass);
  printGLError();

  debugPrint("glStencilOpSeparate(face= %s, sfail= %s, dpfail= %s, dppass= %s)\n", getEnumString(face), getEnumString(sfail), getEnumString(dpfail), getEnumString(dppass));
}

void glUniform1f(GLint location, GLfloat v0)
{
  next_glUniform1f(location, v0);
  printGLError();

  debugPrint("glUniform1f(location= %i, v0= %f)\n", location, v0);
}

void glUniform1fv(GLint location, GLsizei count, const GLfloat* value)
{
  next_glUniform1fv(location, count, value);
  printGLError();

  debugPrint("glUniform1fv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform1i(GLint location, GLint v0)
{
  next_glUniform1i(location, v0);
  printGLError();

  debugPrint("glUniform1i(location= %i, v0= %i)\n", location, v0);
}

void glUniform1iv(GLint location, GLsizei count, const GLint* value)
{
  next_glUniform1iv(location, count, value);
  printGLError();

  debugPrint("glUniform1iv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform2f(GLint location, GLfloat v0, GLfloat v1)
{
  next_glUniform2f(location, v0, v1);
  printGLError();

  debugPrint("glUniform2f(location= %i, v0= %f, v1= %f)\n", location, v0, v1);
}

void glUniform2fv(GLint location, GLsizei count, const GLfloat* value)
{
  next_glUniform2fv(location, count, value);
  printGLError();

  debugPrint("glUniform2fv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform2i(GLint location, GLint v0, GLint v1)
{
  next_glUniform2i(location, v0, v1);
  printGLError();

  debugPrint("glUniform2i(location= %i, v0= %i, v1= %i)\n", location, v0, v1);
}

void glUniform2iv(GLint location, GLsizei count, const GLint* value)
{
  next_glUniform2iv(location, count, value);
  printGLError();

  debugPrint("glUniform2iv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
  next_glUniform3f(location, v0, v1, v2);
  printGLError();

  debugPrint("glUniform3f(location= %i, v0= %f, v1= %f, v2= %f)\n", location, v0, v1, v2);
}

void glUniform3fv(GLint location, GLsizei count, const GLfloat* value)
{
  next_glUniform3fv(location, count, value);
  printGLError();

  debugPrint("glUniform3fv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2)
{
  next_glUniform3i(location, v0, v1, v2);
  printGLError();

  debugPrint("glUniform3i(location= %i, v0= %i, v1= %i, v2= %i)\n", location, v0, v1, v2);
}

void glUniform3iv(GLint location, GLsizei count, const GLint* value)
{
  next_glUniform3iv(location, count, value);
  printGLError();

  debugPrint("glUniform3iv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
  next_glUniform4f(location, v0, v1, v2, v3);
  printGLError();

  debugPrint("glUniform4f(location= %i, v0= %f, v1= %f, v2= %f, v3= %f)\n", location, v0, v1, v2, v3);
}

void glUniform4fv(GLint location, GLsizei count, const GLfloat* value)
{
  next_glUniform4fv(location, count, value);
  printGLError();

  debugPrint("glUniform4fv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
  next_glUniform4i(location, v0, v1, v2, v3);
  printGLError();

  debugPrint("glUniform4i(location= %i, v0= %i, v1= %i, v2= %i, v3= %i)\n", location, v0, v1, v2, v3);
}

void glUniform4iv(GLint location, GLsizei count, const GLint* value)
{
  next_glUniform4iv(location, count, value);
  printGLError();

  debugPrint("glUniform4iv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glUniformMatrix2fv(location, count, transpose, value);
  printGLError();

  debugPrint("glUniformMatrix2fv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glUniformMatrix3fv(location, count, transpose, value);
  printGLError();

  debugPrint("glUniformMatrix3fv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glUniformMatrix4fv(location, count, transpose, value);
  printGLError();

  debugPrint("glUniformMatrix4fv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUseProgram(GLuint program)
{
  next_glUseProgram(program);
  printGLError();

  debugPrint("glUseProgram(program= %u)\n", program);
}

void glValidateProgram(GLuint program)
{
  next_glValidateProgram(program);
  printGLError();

  debugPrint("glValidateProgram(program= %u)\n", program);
}

void glVertexAttrib1d(GLuint index, GLdouble x)
{
  next_glVertexAttrib1d(index, x);
  printGLError();

  debugPrint("glVertexAttrib1d(index= %u, x= %f)\n", index, x);
}

void glVertexAttrib1dv(GLuint index, const GLdouble* v)
{
  next_glVertexAttrib1dv(index, v);
  printGLError();

  debugPrint("glVertexAttrib1dv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib1f(GLuint index, GLfloat x)
{
  next_glVertexAttrib1f(index, x);
  printGLError();

  debugPrint("glVertexAttrib1f(index= %u, x= %f)\n", index, x);
}

void glVertexAttrib1fv(GLuint index, const GLfloat* v)
{
  next_glVertexAttrib1fv(index, v);
  printGLError();

  debugPrint("glVertexAttrib1fv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib1s(GLuint index, GLshort x)
{
  next_glVertexAttrib1s(index, x);
  printGLError();

  debugPrint("glVertexAttrib1s(index= %u, x= %i)\n", index, x);
}

void glVertexAttrib1sv(GLuint index, const GLshort* v)
{
  next_glVertexAttrib1sv(index, v);
  printGLError();

  debugPrint("glVertexAttrib1sv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y)
{
  next_glVertexAttrib2d(index, x, y);
  printGLError();

  debugPrint("glVertexAttrib2d(index= %u, x= %f, y= %f)\n", index, x, y);
}

void glVertexAttrib2dv(GLuint index, const GLdouble* v)
{
  next_glVertexAttrib2dv(index, v);
  printGLError();

  debugPrint("glVertexAttrib2dv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
{
  next_glVertexAttrib2f(index, x, y);
  printGLError();

  debugPrint("glVertexAttrib2f(index= %u, x= %f, y= %f)\n", index, x, y);
}

void glVertexAttrib2fv(GLuint index, const GLfloat* v)
{
  next_glVertexAttrib2fv(index, v);
  printGLError();

  debugPrint("glVertexAttrib2fv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib2s(GLuint index, GLshort x, GLshort y)
{
  next_glVertexAttrib2s(index, x, y);
  printGLError();

  debugPrint("glVertexAttrib2s(index= %u, x= %i, y= %i)\n", index, x, y);
}

void glVertexAttrib2sv(GLuint index, const GLshort* v)
{
  next_glVertexAttrib2sv(index, v);
  printGLError();

  debugPrint("glVertexAttrib2sv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
  next_glVertexAttrib3d(index, x, y, z);
  printGLError();

  debugPrint("glVertexAttrib3d(index= %u, x= %f, y= %f, z= %f)\n", index, x, y, z);
}

void glVertexAttrib3dv(GLuint index, const GLdouble* v)
{
  next_glVertexAttrib3dv(index, v);
  printGLError();

  debugPrint("glVertexAttrib3dv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
  next_glVertexAttrib3f(index, x, y, z);
  printGLError();

  debugPrint("glVertexAttrib3f(index= %u, x= %f, y= %f, z= %f)\n", index, x, y, z);
}

void glVertexAttrib3fv(GLuint index, const GLfloat* v)
{
  next_glVertexAttrib3fv(index, v);
  printGLError();

  debugPrint("glVertexAttrib3fv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z)
{
  next_glVertexAttrib3s(index, x, y, z);
  printGLError();

  debugPrint("glVertexAttrib3s(index= %u, x= %i, y= %i, z= %i)\n", index, x, y, z);
}

void glVertexAttrib3sv(GLuint index, const GLshort* v)
{
  next_glVertexAttrib3sv(index, v);
  printGLError();

  debugPrint("glVertexAttrib3sv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib4Nbv(GLuint index, const GLbyte* v)
{
  next_glVertexAttrib4Nbv(index, v);
  printGLError();

  debugPrint("glVertexAttrib4Nbv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib4Niv(GLuint index, const GLint* v)
{
  next_glVertexAttrib4Niv(index, v);
  printGLError();

  debugPrint("glVertexAttrib4Niv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib4Nsv(GLuint index, const GLshort* v)
{
  next_glVertexAttrib4Nsv(index, v);
  printGLError();

  debugPrint("glVertexAttrib4Nsv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
  next_glVertexAttrib4Nub(index, x, y, z, w);
  printGLError();

  debugPrint("glVertexAttrib4Nub(index= %u, x= %x, y= %x, z= %x, w= %x)\n", index, x, y, z, w);
}

void glVertexAttrib4Nubv(GLuint index, const GLubyte* v)
{
  next_glVertexAttrib4Nubv(index, v);
  printGLError();

  debugPrint("glVertexAttrib4Nubv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib4Nuiv(GLuint index, const GLuint* v)
{
  next_glVertexAttrib4Nuiv(index, v);
  printGLError();

  debugPrint("glVertexAttrib4Nuiv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib4Nusv(GLuint index, const GLushort* v)
{
  next_glVertexAttrib4Nusv(index, v);
  printGLError();

  debugPrint("glVertexAttrib4Nusv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib4bv(GLuint index, const GLbyte* v)
{
  next_glVertexAttrib4bv(index, v);
  printGLError();

  debugPrint("glVertexAttrib4bv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
  next_glVertexAttrib4d(index, x, y, z, w);
  printGLError();

  debugPrint("glVertexAttrib4d(index= %u, x= %f, y= %f, z= %f, w= %f)\n", index, x, y, z, w);
}

void glVertexAttrib4dv(GLuint index, const GLdouble* v)
{
  next_glVertexAttrib4dv(index, v);
  printGLError();

  debugPrint("glVertexAttrib4dv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
  next_glVertexAttrib4f(index, x, y, z, w);
  printGLError();

  debugPrint("glVertexAttrib4f(index= %u, x= %f, y= %f, z= %f, w= %f)\n", index, x, y, z, w);
}

void glVertexAttrib4fv(GLuint index, const GLfloat* v)
{
  next_glVertexAttrib4fv(index, v);
  printGLError();

  debugPrint("glVertexAttrib4fv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib4iv(GLuint index, const GLint* v)
{
  next_glVertexAttrib4iv(index, v);
  printGLError();

  debugPrint("glVertexAttrib4iv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
{
  next_glVertexAttrib4s(index, x, y, z, w);
  printGLError();

  debugPrint("glVertexAttrib4s(index= %u, x= %i, y= %i, z= %i, w= %i)\n", index, x, y, z, w);
}

void glVertexAttrib4sv(GLuint index, const GLshort* v)
{
  next_glVertexAttrib4sv(index, v);
  printGLError();

  debugPrint("glVertexAttrib4sv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib4ubv(GLuint index, const GLubyte* v)
{
  next_glVertexAttrib4ubv(index, v);
  printGLError();

  debugPrint("glVertexAttrib4ubv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib4uiv(GLuint index, const GLuint* v)
{
  next_glVertexAttrib4uiv(index, v);
  printGLError();

  debugPrint("glVertexAttrib4uiv(index= %u, v= %x)\n", index, v);
}

void glVertexAttrib4usv(GLuint index, const GLushort* v)
{
  next_glVertexAttrib4usv(index, v);
  printGLError();

  debugPrint("glVertexAttrib4usv(index= %u, v= %x)\n", index, v);
}

void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer)
{
  next_glVertexAttribPointer(index, size, type, normalized, stride, pointer);
  printGLError();

  debugPrint("glVertexAttribPointer(index= %u, size= %i, type= %s, normalized= %i, stride= %u, pointer= %x)\n", index, size, getEnumString(type), normalized, stride, pointer);
}


// GL_VERSION_2_1

void glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glUniformMatrix2x3fv(location, count, transpose, value);
  printGLError();

  debugPrint("glUniformMatrix2x3fv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glUniformMatrix2x4fv(location, count, transpose, value);
  printGLError();

  debugPrint("glUniformMatrix2x4fv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glUniformMatrix3x2fv(location, count, transpose, value);
  printGLError();

  debugPrint("glUniformMatrix3x2fv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glUniformMatrix3x4fv(location, count, transpose, value);
  printGLError();

  debugPrint("glUniformMatrix3x4fv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glUniformMatrix4x2fv(location, count, transpose, value);
  printGLError();

  debugPrint("glUniformMatrix4x2fv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glUniformMatrix4x3fv(location, count, transpose, value);
  printGLError();

  debugPrint("glUniformMatrix4x3fv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}


// GL_VERSION_3_0

void glBeginConditionalRender(GLuint id, GLenum mode)
{
  next_glBeginConditionalRender(id, mode);
  printGLError();

  debugPrint("glBeginConditionalRender(id= %u, mode= %s)\n", id, getEnumString(mode));
}

void glBeginTransformFeedback(GLenum primitiveMode)
{
  next_glBeginTransformFeedback(primitiveMode);
  printGLError();

  debugPrint("glBeginTransformFeedback(primitiveMode= %s)\n", getEnumString(primitiveMode));
}

void glBindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
  next_glBindBufferBase(target, index, buffer);
  printGLError();

  debugPrint("glBindBufferBase(target= %s, index= %u, buffer= %u)\n", getEnumString(target), index, buffer);
}

void glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
  next_glBindBufferRange(target, index, buffer, offset, size);
  printGLError();

  debugPrint("glBindBufferRange(target= %s, index= %u, buffer= %u, offset= %i, size= %u)\n", getEnumString(target), index, buffer, offset, size);
}

void glBindFragDataLocation(GLuint program, GLuint color, const GLchar* name)
{
  next_glBindFragDataLocation(program, color, name);
  printGLError();

  debugPrint("glBindFragDataLocation(program= %u, color= %u, name= %x)\n", program, color, name);
}

void glBindFramebuffer(GLenum target, GLuint framebuffer)
{
  next_glBindFramebuffer(target, framebuffer);
  printGLError();

  debugPrint("glBindFramebuffer(target= %s, framebuffer= %u)\n", getEnumString(target), framebuffer);
}

void glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
  next_glBindRenderbuffer(target, renderbuffer);
  printGLError();

  debugPrint("glBindRenderbuffer(target= %s, renderbuffer= %u)\n", getEnumString(target), renderbuffer);
}

void glBindVertexArray(GLuint array)
{
  next_glBindVertexArray(array);
  printGLError();

  debugPrint("glBindVertexArray(array= %u)\n", array);
}

void glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
  next_glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
  printGLError();

  debugPrint("glBlitFramebuffer(srcX0= %i, srcY0= %i, srcX1= %i, srcY1= %i, dstX0= %i, dstY0= %i, dstX1= %i, dstY1= %i, mask= %x, filter= %s)\n", srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, getEnumString(filter));
}

GLenum glCheckFramebufferStatus(GLenum target)
{
  GLenum result= next_glCheckFramebufferStatus(target);
  printGLError();

  debugPrint("glCheckFramebufferStatus(target= %s)= %s\n", getEnumString(target), getEnumString(result));

  return result;
}

void glClampColor(GLenum target, GLenum clamp)
{
  next_glClampColor(target, clamp);
  printGLError();

  debugPrint("glClampColor(target= %s, clamp= %s)\n", getEnumString(target), getEnumString(clamp));
}

void glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
{
  next_glClearBufferfi(buffer, drawbuffer, depth, stencil);
  printGLError();

  debugPrint("glClearBufferfi(buffer= %s, drawbuffer= %i, depth= %f, stencil= %i)\n", getEnumString(buffer), drawbuffer, depth, stencil);
}

void glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value)
{
  next_glClearBufferfv(buffer, drawbuffer, value);
  printGLError();

  debugPrint("glClearBufferfv(buffer= %s, drawbuffer= %i, value= %x)\n", getEnumString(buffer), drawbuffer, value);
}

void glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint* value)
{
  next_glClearBufferiv(buffer, drawbuffer, value);
  printGLError();

  debugPrint("glClearBufferiv(buffer= %s, drawbuffer= %i, value= %x)\n", getEnumString(buffer), drawbuffer, value);
}

void glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint* value)
{
  next_glClearBufferuiv(buffer, drawbuffer, value);
  printGLError();

  debugPrint("glClearBufferuiv(buffer= %s, drawbuffer= %i, value= %x)\n", getEnumString(buffer), drawbuffer, value);
}

void glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
{
  next_glColorMaski(index, r, g, b, a);
  printGLError();

  debugPrint("glColorMaski(index= %u, r= %i, g= %i, b= %i, a= %i)\n", index, r, g, b, a);
}

void glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{
  next_glDeleteFramebuffers(n, framebuffers);
  printGLError();

  debugPrint("glDeleteFramebuffers(n= %u, framebuffers= %x)\n", n, framebuffers);
}

void glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
{
  next_glDeleteRenderbuffers(n, renderbuffers);
  printGLError();

  debugPrint("glDeleteRenderbuffers(n= %u, renderbuffers= %x)\n", n, renderbuffers);
}

void glDeleteVertexArrays(GLsizei n, const GLuint* arrays)
{
  next_glDeleteVertexArrays(n, arrays);
  printGLError();

  debugPrint("glDeleteVertexArrays(n= %u, arrays= %x)\n", n, arrays);
}

void glDisablei(GLenum target, GLuint index)
{
  next_glDisablei(target, index);
  printGLError();

  debugPrint("glDisablei(target= %s, index= %u)\n", getEnumString(target), index);
}

void glEnablei(GLenum target, GLuint index)
{
  next_glEnablei(target, index);
  printGLError();

  debugPrint("glEnablei(target= %s, index= %u)\n", getEnumString(target), index);
}

void glEndConditionalRender()
{
  next_glEndConditionalRender();
  printGLError();

  debugPrint("glEndConditionalRender()\n");
}

void glEndTransformFeedback()
{
  next_glEndTransformFeedback();
  printGLError();

  debugPrint("glEndTransformFeedback()\n");
}

void glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length)
{
  next_glFlushMappedBufferRange(target, offset, length);
  printGLError();

  debugPrint("glFlushMappedBufferRange(target= %s, offset= %i, length= %u)\n", getEnumString(target), offset, length);
}

void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
  next_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
  printGLError();

  debugPrint("glFramebufferRenderbuffer(target= %s, attachment= %s, renderbuffertarget= %s, renderbuffer= %u)\n", getEnumString(target), getEnumString(attachment), getEnumString(renderbuffertarget), renderbuffer);
}

void glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
  next_glFramebufferTexture1D(target, attachment, textarget, texture, level);
  printGLError();

  debugPrint("glFramebufferTexture1D(target= %s, attachment= %s, textarget= %s, texture= %u, level= %i)\n", getEnumString(target), getEnumString(attachment), getEnumString(textarget), texture, level);
}

void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
  next_glFramebufferTexture2D(target, attachment, textarget, texture, level);
  printGLError();

  debugPrint("glFramebufferTexture2D(target= %s, attachment= %s, textarget= %s, texture= %u, level= %i)\n", getEnumString(target), getEnumString(attachment), getEnumString(textarget), texture, level);
}

void glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
{
  next_glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
  printGLError();

  debugPrint("glFramebufferTexture3D(target= %s, attachment= %s, textarget= %s, texture= %u, level= %i, zoffset= %i)\n", getEnumString(target), getEnumString(attachment), getEnumString(textarget), texture, level, zoffset);
}

void glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
  next_glFramebufferTextureLayer(target, attachment, texture, level, layer);
  printGLError();

  debugPrint("glFramebufferTextureLayer(target= %s, attachment= %s, texture= %u, level= %i, layer= %i)\n", getEnumString(target), getEnumString(attachment), texture, level, layer);
}

void glGenFramebuffers(GLsizei n, GLuint* framebuffers)
{
  next_glGenFramebuffers(n, framebuffers);
  printGLError();

  debugPrint("glGenFramebuffers(n= %u, framebuffers= %x)\n", n, framebuffers);
}

void glGenRenderbuffers(GLsizei n, GLuint* renderbuffers)
{
  next_glGenRenderbuffers(n, renderbuffers);
  printGLError();

  debugPrint("glGenRenderbuffers(n= %u, renderbuffers= %x)\n", n, renderbuffers);
}

void glGenVertexArrays(GLsizei n, GLuint* arrays)
{
  next_glGenVertexArrays(n, arrays);
  printGLError();

  debugPrint("glGenVertexArrays(n= %u, arrays= %x)\n", n, arrays);
}

void glGenerateMipmap(GLenum target)
{
  next_glGenerateMipmap(target);
  printGLError();

  debugPrint("glGenerateMipmap(target= %s)\n", getEnumString(target));
}

void glGetBooleani_v(GLenum target, GLuint index, GLboolean* data)
{
  next_glGetBooleani_v(target, index, data);
  printGLError();

  debugPrint("glGetBooleani_v(target= %s, index= %u, data= %x)\n", getEnumString(target), index, data);
}

GLint glGetFragDataLocation(GLuint program, const GLchar* name)
{
  GLint result= next_glGetFragDataLocation(program, name);
  printGLError();

  debugPrint("glGetFragDataLocation(program= %u, name= %x)= %i\n", program, name, result);

  return result;
}

void glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
{
  next_glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
  printGLError();

  debugPrint("glGetFramebufferAttachmentParameteriv(target= %s, attachment= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(attachment), getEnumString(pname), params);
}

void glGetIntegeri_v(GLenum target, GLuint index, GLint* data)
{
  next_glGetIntegeri_v(target, index, data);
  printGLError();

  debugPrint("glGetIntegeri_v(target= %s, index= %u, data= %x)\n", getEnumString(target), index, data);
}

void glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
  next_glGetRenderbufferParameteriv(target, pname, params);
  printGLError();

  debugPrint("glGetRenderbufferParameteriv(target= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(pname), params);
}

const GLubyte* glGetStringi(GLenum name, GLuint index)
{
  const GLubyte* result= next_glGetStringi(name, index);
  printGLError();

  debugPrint("glGetStringi(name= %s, index= %u)= %x\n", getEnumString(name), index, result);

  return result;
}

void glGetTexParameterIiv(GLenum target, GLenum pname, GLint* params)
{
  next_glGetTexParameterIiv(target, pname, params);
  printGLError();

  debugPrint("glGetTexParameterIiv(target= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(pname), params);
}

void glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint* params)
{
  next_glGetTexParameterIuiv(target, pname, params);
  printGLError();

  debugPrint("glGetTexParameterIuiv(target= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(pname), params);
}

void glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name)
{
  next_glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
  printGLError();

  debugPrint("glGetTransformFeedbackVarying(program= %u, index= %u, bufSize= %u, length= %x, size= %x, type= %x, name= %s)\n", program, index, bufSize, length, size, type, name);
}

void glGetUniformuiv(GLuint program, GLint location, GLuint* params)
{
  next_glGetUniformuiv(program, location, params);
  printGLError();

  debugPrint("glGetUniformuiv(program= %u, location= %i, params= %x)\n", program, location, params);
}

void glGetVertexAttribIiv(GLuint index, GLenum pname, GLint* params)
{
  next_glGetVertexAttribIiv(index, pname, params);
  printGLError();

  debugPrint("glGetVertexAttribIiv(index= %u, pname= %s, params= %x)\n", index, getEnumString(pname), params);
}

void glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint* params)
{
  next_glGetVertexAttribIuiv(index, pname, params);
  printGLError();

  debugPrint("glGetVertexAttribIuiv(index= %u, pname= %s, params= %x)\n", index, getEnumString(pname), params);
}

GLboolean glIsEnabledi(GLenum target, GLuint index)
{
  GLboolean result= next_glIsEnabledi(target, index);
  printGLError();

  debugPrint("glIsEnabledi(target= %s, index= %u)= %i\n", getEnumString(target), index, result);

  return result;
}

GLboolean glIsFramebuffer(GLuint framebuffer)
{
  GLboolean result= next_glIsFramebuffer(framebuffer);
  printGLError();

  debugPrint("glIsFramebuffer(framebuffer= %u)= %i\n", framebuffer, result);

  return result;
}

GLboolean glIsRenderbuffer(GLuint renderbuffer)
{
  GLboolean result= next_glIsRenderbuffer(renderbuffer);
  printGLError();

  debugPrint("glIsRenderbuffer(renderbuffer= %u)= %i\n", renderbuffer, result);

  return result;
}

GLboolean glIsVertexArray(GLuint array)
{
  GLboolean result= next_glIsVertexArray(array);
  printGLError();

  debugPrint("glIsVertexArray(array= %u)= %i\n", array, result);

  return result;
}

void * glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
  void * result= next_glMapBufferRange(target, offset, length, access);
  printGLError();

  debugPrint("glMapBufferRange(target= %s, offset= %i, length= %u, access= %x)= %x\n", getEnumString(target), offset, length, access, result);

  return result;
}

void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
  next_glRenderbufferStorage(target, internalformat, width, height);
  printGLError();

  debugPrint("glRenderbufferStorage(target= %s, internalformat= %s, width= %u, height= %u)\n", getEnumString(target), getEnumString(internalformat), width, height);
}

void glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
  next_glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
  printGLError();

  debugPrint("glRenderbufferStorageMultisample(target= %s, samples= %u, internalformat= %s, width= %u, height= %u)\n", getEnumString(target), samples, getEnumString(internalformat), width, height);
}

void glTexParameterIiv(GLenum target, GLenum pname, const GLint* params)
{
  next_glTexParameterIiv(target, pname, params);
  printGLError();

  debugPrint("glTexParameterIiv(target= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(pname), params);
}

void glTexParameterIuiv(GLenum target, GLenum pname, const GLuint* params)
{
  next_glTexParameterIuiv(target, pname, params);
  printGLError();

  debugPrint("glTexParameterIuiv(target= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(pname), params);
}

void glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar*const* varyings, GLenum bufferMode)
{
  next_glTransformFeedbackVaryings(program, count, varyings, bufferMode);
  printGLError();

  debugPrint("glTransformFeedbackVaryings(program= %u, count= %u, varyings= %x, bufferMode= %s)\n", program, count, varyings, getEnumString(bufferMode));
}

void glUniform1ui(GLint location, GLuint v0)
{
  next_glUniform1ui(location, v0);
  printGLError();

  debugPrint("glUniform1ui(location= %i, v0= %u)\n", location, v0);
}

void glUniform1uiv(GLint location, GLsizei count, const GLuint* value)
{
  next_glUniform1uiv(location, count, value);
  printGLError();

  debugPrint("glUniform1uiv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform2ui(GLint location, GLuint v0, GLuint v1)
{
  next_glUniform2ui(location, v0, v1);
  printGLError();

  debugPrint("glUniform2ui(location= %i, v0= %u, v1= %u)\n", location, v0, v1);
}

void glUniform2uiv(GLint location, GLsizei count, const GLuint* value)
{
  next_glUniform2uiv(location, count, value);
  printGLError();

  debugPrint("glUniform2uiv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
{
  next_glUniform3ui(location, v0, v1, v2);
  printGLError();

  debugPrint("glUniform3ui(location= %i, v0= %u, v1= %u, v2= %u)\n", location, v0, v1, v2);
}

void glUniform3uiv(GLint location, GLsizei count, const GLuint* value)
{
  next_glUniform3uiv(location, count, value);
  printGLError();

  debugPrint("glUniform3uiv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
  next_glUniform4ui(location, v0, v1, v2, v3);
  printGLError();

  debugPrint("glUniform4ui(location= %i, v0= %u, v1= %u, v2= %u, v3= %u)\n", location, v0, v1, v2, v3);
}

void glUniform4uiv(GLint location, GLsizei count, const GLuint* value)
{
  next_glUniform4uiv(location, count, value);
  printGLError();

  debugPrint("glUniform4uiv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glVertexAttribI1i(GLuint index, GLint x)
{
  next_glVertexAttribI1i(index, x);
  printGLError();

  debugPrint("glVertexAttribI1i(index= %u, x= %i)\n", index, x);
}

void glVertexAttribI1iv(GLuint index, const GLint* v)
{
  next_glVertexAttribI1iv(index, v);
  printGLError();

  debugPrint("glVertexAttribI1iv(index= %u, v= %x)\n", index, v);
}

void glVertexAttribI1ui(GLuint index, GLuint x)
{
  next_glVertexAttribI1ui(index, x);
  printGLError();

  debugPrint("glVertexAttribI1ui(index= %u, x= %u)\n", index, x);
}

void glVertexAttribI1uiv(GLuint index, const GLuint* v)
{
  next_glVertexAttribI1uiv(index, v);
  printGLError();

  debugPrint("glVertexAttribI1uiv(index= %u, v= %x)\n", index, v);
}

void glVertexAttribI2i(GLuint index, GLint x, GLint y)
{
  next_glVertexAttribI2i(index, x, y);
  printGLError();

  debugPrint("glVertexAttribI2i(index= %u, x= %i, y= %i)\n", index, x, y);
}

void glVertexAttribI2iv(GLuint index, const GLint* v)
{
  next_glVertexAttribI2iv(index, v);
  printGLError();

  debugPrint("glVertexAttribI2iv(index= %u, v= %x)\n", index, v);
}

void glVertexAttribI2ui(GLuint index, GLuint x, GLuint y)
{
  next_glVertexAttribI2ui(index, x, y);
  printGLError();

  debugPrint("glVertexAttribI2ui(index= %u, x= %u, y= %u)\n", index, x, y);
}

void glVertexAttribI2uiv(GLuint index, const GLuint* v)
{
  next_glVertexAttribI2uiv(index, v);
  printGLError();

  debugPrint("glVertexAttribI2uiv(index= %u, v= %x)\n", index, v);
}

void glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z)
{
  next_glVertexAttribI3i(index, x, y, z);
  printGLError();

  debugPrint("glVertexAttribI3i(index= %u, x= %i, y= %i, z= %i)\n", index, x, y, z);
}

void glVertexAttribI3iv(GLuint index, const GLint* v)
{
  next_glVertexAttribI3iv(index, v);
  printGLError();

  debugPrint("glVertexAttribI3iv(index= %u, v= %x)\n", index, v);
}

void glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z)
{
  next_glVertexAttribI3ui(index, x, y, z);
  printGLError();

  debugPrint("glVertexAttribI3ui(index= %u, x= %u, y= %u, z= %u)\n", index, x, y, z);
}

void glVertexAttribI3uiv(GLuint index, const GLuint* v)
{
  next_glVertexAttribI3uiv(index, v);
  printGLError();

  debugPrint("glVertexAttribI3uiv(index= %u, v= %x)\n", index, v);
}

void glVertexAttribI4bv(GLuint index, const GLbyte* v)
{
  next_glVertexAttribI4bv(index, v);
  printGLError();

  debugPrint("glVertexAttribI4bv(index= %u, v= %x)\n", index, v);
}

void glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
{
  next_glVertexAttribI4i(index, x, y, z, w);
  printGLError();

  debugPrint("glVertexAttribI4i(index= %u, x= %i, y= %i, z= %i, w= %i)\n", index, x, y, z, w);
}

void glVertexAttribI4iv(GLuint index, const GLint* v)
{
  next_glVertexAttribI4iv(index, v);
  printGLError();

  debugPrint("glVertexAttribI4iv(index= %u, v= %x)\n", index, v);
}

void glVertexAttribI4sv(GLuint index, const GLshort* v)
{
  next_glVertexAttribI4sv(index, v);
  printGLError();

  debugPrint("glVertexAttribI4sv(index= %u, v= %x)\n", index, v);
}

void glVertexAttribI4ubv(GLuint index, const GLubyte* v)
{
  next_glVertexAttribI4ubv(index, v);
  printGLError();

  debugPrint("glVertexAttribI4ubv(index= %u, v= %x)\n", index, v);
}

void glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
{
  next_glVertexAttribI4ui(index, x, y, z, w);
  printGLError();

  debugPrint("glVertexAttribI4ui(index= %u, x= %u, y= %u, z= %u, w= %u)\n", index, x, y, z, w);
}

void glVertexAttribI4uiv(GLuint index, const GLuint* v)
{
  next_glVertexAttribI4uiv(index, v);
  printGLError();

  debugPrint("glVertexAttribI4uiv(index= %u, v= %x)\n", index, v);
}

void glVertexAttribI4usv(GLuint index, const GLushort* v)
{
  next_glVertexAttribI4usv(index, v);
  printGLError();

  debugPrint("glVertexAttribI4usv(index= %u, v= %x)\n", index, v);
}

void glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer)
{
  next_glVertexAttribIPointer(index, size, type, stride, pointer);
  printGLError();

  debugPrint("glVertexAttribIPointer(index= %u, size= %i, type= %s, stride= %u, pointer= %x)\n", index, size, getEnumString(type), stride, pointer);
}


// GL_VERSION_3_1

void glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
  next_glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
  printGLError();

  debugPrint("glCopyBufferSubData(readTarget= %s, writeTarget= %s, readOffset= %i, writeOffset= %i, size= %u)\n", getEnumString(readTarget), getEnumString(writeTarget), readOffset, writeOffset, size);
}

void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)
{
  next_glDrawArraysInstanced(mode, first, count, instancecount);
  printGLError();

  debugPrint("glDrawArraysInstanced(mode= %s, first= %i, count= %u, instancecount= %u)\n", getEnumString(mode), first, count, instancecount);
}

void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount)
{
  next_glDrawElementsInstanced(mode, count, type, indices, instancecount);
  printGLError();

  debugPrint("glDrawElementsInstanced(mode= %s, count= %u, type= %s, indices= %x, instancecount= %u)\n", getEnumString(mode), count, getEnumString(type), indices, instancecount);
}

void glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName)
{
  next_glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
  printGLError();

  debugPrint("glGetActiveUniformBlockName(program= %u, uniformBlockIndex= %u, bufSize= %u, length= %x, uniformBlockName= %s)\n", program, uniformBlockIndex, bufSize, length, uniformBlockName);
}

void glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params)
{
  next_glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
  printGLError();

  debugPrint("glGetActiveUniformBlockiv(program= %u, uniformBlockIndex= %u, pname= %s, params= %x)\n", program, uniformBlockIndex, getEnumString(pname), params);
}

void glGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformName)
{
  next_glGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
  printGLError();

  debugPrint("glGetActiveUniformName(program= %u, uniformIndex= %u, bufSize= %u, length= %x, uniformName= %s)\n", program, uniformIndex, bufSize, length, uniformName);
}

void glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params)
{
  next_glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
  printGLError();

  debugPrint("glGetActiveUniformsiv(program= %u, uniformCount= %u, uniformIndices= %x, pname= %s, params= %x)\n", program, uniformCount, uniformIndices, getEnumString(pname), params);
}

GLuint glGetUniformBlockIndex(GLuint program, const GLchar* uniformBlockName)
{
  GLuint result= next_glGetUniformBlockIndex(program, uniformBlockName);
  printGLError();

  debugPrint("glGetUniformBlockIndex(program= %u, uniformBlockName= %x)= %u\n", program, uniformBlockName, result);

  return result;
}

void glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar*const* uniformNames, GLuint* uniformIndices)
{
  next_glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
  printGLError();

  debugPrint("glGetUniformIndices(program= %u, uniformCount= %u, uniformNames= %x, uniformIndices= %x)\n", program, uniformCount, uniformNames, uniformIndices);
}

void glPrimitiveRestartIndex(GLuint index)
{
  next_glPrimitiveRestartIndex(index);
  printGLError();

  debugPrint("glPrimitiveRestartIndex(index= %u)\n", index);
}

void glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer)
{
  next_glTexBuffer(target, internalformat, buffer);
  printGLError();

  debugPrint("glTexBuffer(target= %s, internalformat= %s, buffer= %u)\n", getEnumString(target), getEnumString(internalformat), buffer);
}

void glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
{
  next_glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
  printGLError();

  debugPrint("glUniformBlockBinding(program= %u, uniformBlockIndex= %u, uniformBlockBinding= %u)\n", program, uniformBlockIndex, uniformBlockBinding);
}


// GL_VERSION_3_2

GLenum glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
  GLenum result= next_glClientWaitSync(sync, flags, timeout);
  printGLError();

  debugPrint("glClientWaitSync(sync= %x, flags= %x, timeout= %u)= %s\n", sync, flags, timeout, getEnumString(result));

  return result;
}

void glDeleteSync(GLsync sync)
{
  next_glDeleteSync(sync);
  printGLError();

  debugPrint("glDeleteSync(sync= %x)\n", sync);
}

void glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLint basevertex)
{
  next_glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
  printGLError();

  debugPrint("glDrawElementsBaseVertex(mode= %s, count= %u, type= %s, indices= %x, basevertex= %i)\n", getEnumString(mode), count, getEnumString(type), indices, basevertex);
}

void glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex)
{
  next_glDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
  printGLError();

  debugPrint("glDrawElementsInstancedBaseVertex(mode= %s, count= %u, type= %s, indices= %x, instancecount= %u, basevertex= %i)\n", getEnumString(mode), count, getEnumString(type), indices, instancecount, basevertex);
}

void glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices, GLint basevertex)
{
  next_glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
  printGLError();

  debugPrint("glDrawRangeElementsBaseVertex(mode= %s, start= %u, end= %u, count= %u, type= %s, indices= %x, basevertex= %i)\n", getEnumString(mode), start, end, count, getEnumString(type), indices, basevertex);
}

GLsync glFenceSync(GLenum condition, GLbitfield flags)
{
  GLsync result= next_glFenceSync(condition, flags);
  printGLError();

  debugPrint("glFenceSync(condition= %s, flags= %x)= %x\n", getEnumString(condition), flags, result);

  return result;
}

void glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
{
  next_glFramebufferTexture(target, attachment, texture, level);
  printGLError();

  debugPrint("glFramebufferTexture(target= %s, attachment= %s, texture= %u, level= %i)\n", getEnumString(target), getEnumString(attachment), texture, level);
}

void glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64* params)
{
  next_glGetBufferParameteri64v(target, pname, params);
  printGLError();

  debugPrint("glGetBufferParameteri64v(target= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(pname), params);
}

void glGetInteger64i_v(GLenum target, GLuint index, GLint64* data)
{
  next_glGetInteger64i_v(target, index, data);
  printGLError();

  debugPrint("glGetInteger64i_v(target= %s, index= %u, data= %x)\n", getEnumString(target), index, data);
}

void glGetInteger64v(GLenum pname, GLint64* data)
{
  next_glGetInteger64v(pname, data);
  printGLError();

  debugPrint("glGetInteger64v(pname= %s, data= %x)\n", getEnumString(pname), data);
}

void glGetMultisamplefv(GLenum pname, GLuint index, GLfloat* val)
{
  next_glGetMultisamplefv(pname, index, val);
  printGLError();

  debugPrint("glGetMultisamplefv(pname= %s, index= %u, val= %x)\n", getEnumString(pname), index, val);
}

void glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values)
{
  next_glGetSynciv(sync, pname, bufSize, length, values);
  printGLError();

  debugPrint("glGetSynciv(sync= %x, pname= %s, bufSize= %u, length= %x, values= %x)\n", sync, getEnumString(pname), bufSize, length, values);
}

GLboolean glIsSync(GLsync sync)
{
  GLboolean result= next_glIsSync(sync);
  printGLError();

  debugPrint("glIsSync(sync= %x)= %i\n", sync, result);

  return result;
}

void glMultiDrawElementsBaseVertex(GLenum mode, const GLsizei* count, GLenum type, const void *const* indices, GLsizei drawcount, const GLint* basevertex)
{
  next_glMultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);
  printGLError();

  debugPrint("glMultiDrawElementsBaseVertex(mode= %s, count= %x, type= %s, indices= %x, drawcount= %u, basevertex= %x)\n", getEnumString(mode), count, getEnumString(type), indices, drawcount, basevertex);
}

void glProvokingVertex(GLenum mode)
{
  next_glProvokingVertex(mode);
  printGLError();

  debugPrint("glProvokingVertex(mode= %s)\n", getEnumString(mode));
}

void glSampleMaski(GLuint maskNumber, GLbitfield mask)
{
  next_glSampleMaski(maskNumber, mask);
  printGLError();

  debugPrint("glSampleMaski(maskNumber= %u, mask= %x)\n", maskNumber, mask);
}

void glTexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
  next_glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
  printGLError();

  debugPrint("glTexImage2DMultisample(target= %s, samples= %u, internalformat= %s, width= %u, height= %u, fixedsamplelocations= %i)\n", getEnumString(target), samples, getEnumString(internalformat), width, height, fixedsamplelocations);
}

void glTexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
  next_glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
  printGLError();

  debugPrint("glTexImage3DMultisample(target= %s, samples= %u, internalformat= %s, width= %u, height= %u, depth= %u, fixedsamplelocations= %i)\n", getEnumString(target), samples, getEnumString(internalformat), width, height, depth, fixedsamplelocations);
}

void glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
  next_glWaitSync(sync, flags, timeout);
  printGLError();

  debugPrint("glWaitSync(sync= %x, flags= %x, timeout= %u)\n", sync, flags, timeout);
}


// GL_VERSION_3_3

void glBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar* name)
{
  next_glBindFragDataLocationIndexed(program, colorNumber, index, name);
  printGLError();

  debugPrint("glBindFragDataLocationIndexed(program= %u, colorNumber= %u, index= %u, name= %x)\n", program, colorNumber, index, name);
}

void glBindSampler(GLuint unit, GLuint sampler)
{
  next_glBindSampler(unit, sampler);
  printGLError();

  debugPrint("glBindSampler(unit= %u, sampler= %u)\n", unit, sampler);
}

void glColorP3ui(GLenum type, GLuint color)
{
  next_glColorP3ui(type, color);
  printGLError();

  debugPrint("glColorP3ui(type= %s, color= %u)\n", getEnumString(type), color);
}

void glColorP3uiv(GLenum type, const GLuint* color)
{
  next_glColorP3uiv(type, color);
  printGLError();

  debugPrint("glColorP3uiv(type= %s, color= %x)\n", getEnumString(type), color);
}

void glColorP4ui(GLenum type, GLuint color)
{
  next_glColorP4ui(type, color);
  printGLError();

  debugPrint("glColorP4ui(type= %s, color= %u)\n", getEnumString(type), color);
}

void glColorP4uiv(GLenum type, const GLuint* color)
{
  next_glColorP4uiv(type, color);
  printGLError();

  debugPrint("glColorP4uiv(type= %s, color= %x)\n", getEnumString(type), color);
}

void glDeleteSamplers(GLsizei count, const GLuint* samplers)
{
  next_glDeleteSamplers(count, samplers);
  printGLError();

  debugPrint("glDeleteSamplers(count= %u, samplers= %x)\n", count, samplers);
}

void glGenSamplers(GLsizei count, GLuint* samplers)
{
  next_glGenSamplers(count, samplers);
  printGLError();

  debugPrint("glGenSamplers(count= %u, samplers= %x)\n", count, samplers);
}

GLint glGetFragDataIndex(GLuint program, const GLchar* name)
{
  GLint result= next_glGetFragDataIndex(program, name);
  printGLError();

  debugPrint("glGetFragDataIndex(program= %u, name= %x)= %i\n", program, name, result);

  return result;
}

void glGetQueryObjecti64v(GLuint id, GLenum pname, GLint64* params)
{
  next_glGetQueryObjecti64v(id, pname, params);
  printGLError();

  debugPrint("glGetQueryObjecti64v(id= %u, pname= %s, params= %x)\n", id, getEnumString(pname), params);
}

void glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64* params)
{
  next_glGetQueryObjectui64v(id, pname, params);
  printGLError();

  debugPrint("glGetQueryObjectui64v(id= %u, pname= %s, params= %x)\n", id, getEnumString(pname), params);
}

void glGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint* params)
{
  next_glGetSamplerParameterIiv(sampler, pname, params);
  printGLError();

  debugPrint("glGetSamplerParameterIiv(sampler= %u, pname= %s, params= %x)\n", sampler, getEnumString(pname), params);
}

void glGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint* params)
{
  next_glGetSamplerParameterIuiv(sampler, pname, params);
  printGLError();

  debugPrint("glGetSamplerParameterIuiv(sampler= %u, pname= %s, params= %x)\n", sampler, getEnumString(pname), params);
}

void glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat* params)
{
  next_glGetSamplerParameterfv(sampler, pname, params);
  printGLError();

  debugPrint("glGetSamplerParameterfv(sampler= %u, pname= %s, params= %x)\n", sampler, getEnumString(pname), params);
}

void glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint* params)
{
  next_glGetSamplerParameteriv(sampler, pname, params);
  printGLError();

  debugPrint("glGetSamplerParameteriv(sampler= %u, pname= %s, params= %x)\n", sampler, getEnumString(pname), params);
}

GLboolean glIsSampler(GLuint sampler)
{
  GLboolean result= next_glIsSampler(sampler);
  printGLError();

  debugPrint("glIsSampler(sampler= %u)= %i\n", sampler, result);

  return result;
}

void glMultiTexCoordP1ui(GLenum texture, GLenum type, GLuint coords)
{
  next_glMultiTexCoordP1ui(texture, type, coords);
  printGLError();

  debugPrint("glMultiTexCoordP1ui(texture= %s, type= %s, coords= %u)\n", getEnumString(texture), getEnumString(type), coords);
}

void glMultiTexCoordP1uiv(GLenum texture, GLenum type, const GLuint* coords)
{
  next_glMultiTexCoordP1uiv(texture, type, coords);
  printGLError();

  debugPrint("glMultiTexCoordP1uiv(texture= %s, type= %s, coords= %x)\n", getEnumString(texture), getEnumString(type), coords);
}

void glMultiTexCoordP2ui(GLenum texture, GLenum type, GLuint coords)
{
  next_glMultiTexCoordP2ui(texture, type, coords);
  printGLError();

  debugPrint("glMultiTexCoordP2ui(texture= %s, type= %s, coords= %u)\n", getEnumString(texture), getEnumString(type), coords);
}

void glMultiTexCoordP2uiv(GLenum texture, GLenum type, const GLuint* coords)
{
  next_glMultiTexCoordP2uiv(texture, type, coords);
  printGLError();

  debugPrint("glMultiTexCoordP2uiv(texture= %s, type= %s, coords= %x)\n", getEnumString(texture), getEnumString(type), coords);
}

void glMultiTexCoordP3ui(GLenum texture, GLenum type, GLuint coords)
{
  next_glMultiTexCoordP3ui(texture, type, coords);
  printGLError();

  debugPrint("glMultiTexCoordP3ui(texture= %s, type= %s, coords= %u)\n", getEnumString(texture), getEnumString(type), coords);
}

void glMultiTexCoordP3uiv(GLenum texture, GLenum type, const GLuint* coords)
{
  next_glMultiTexCoordP3uiv(texture, type, coords);
  printGLError();

  debugPrint("glMultiTexCoordP3uiv(texture= %s, type= %s, coords= %x)\n", getEnumString(texture), getEnumString(type), coords);
}

void glMultiTexCoordP4ui(GLenum texture, GLenum type, GLuint coords)
{
  next_glMultiTexCoordP4ui(texture, type, coords);
  printGLError();

  debugPrint("glMultiTexCoordP4ui(texture= %s, type= %s, coords= %u)\n", getEnumString(texture), getEnumString(type), coords);
}

void glMultiTexCoordP4uiv(GLenum texture, GLenum type, const GLuint* coords)
{
  next_glMultiTexCoordP4uiv(texture, type, coords);
  printGLError();

  debugPrint("glMultiTexCoordP4uiv(texture= %s, type= %s, coords= %x)\n", getEnumString(texture), getEnumString(type), coords);
}

void glNormalP3ui(GLenum type, GLuint coords)
{
  next_glNormalP3ui(type, coords);
  printGLError();

  debugPrint("glNormalP3ui(type= %s, coords= %u)\n", getEnumString(type), coords);
}

void glNormalP3uiv(GLenum type, const GLuint* coords)
{
  next_glNormalP3uiv(type, coords);
  printGLError();

  debugPrint("glNormalP3uiv(type= %s, coords= %x)\n", getEnumString(type), coords);
}

void glQueryCounter(GLuint id, GLenum target)
{
  next_glQueryCounter(id, target);
  printGLError();

  debugPrint("glQueryCounter(id= %u, target= %s)\n", id, getEnumString(target));
}

void glSamplerParameterIiv(GLuint sampler, GLenum pname, const GLint* param)
{
  next_glSamplerParameterIiv(sampler, pname, param);
  printGLError();

  debugPrint("glSamplerParameterIiv(sampler= %u, pname= %s, param= %x)\n", sampler, getEnumString(pname), param);
}

void glSamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint* param)
{
  next_glSamplerParameterIuiv(sampler, pname, param);
  printGLError();

  debugPrint("glSamplerParameterIuiv(sampler= %u, pname= %s, param= %x)\n", sampler, getEnumString(pname), param);
}

void glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param)
{
  next_glSamplerParameterf(sampler, pname, param);
  printGLError();

  debugPrint("glSamplerParameterf(sampler= %u, pname= %s, param= %f)\n", sampler, getEnumString(pname), param);
}

void glSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat* param)
{
  next_glSamplerParameterfv(sampler, pname, param);
  printGLError();

  debugPrint("glSamplerParameterfv(sampler= %u, pname= %s, param= %x)\n", sampler, getEnumString(pname), param);
}

void glSamplerParameteri(GLuint sampler, GLenum pname, GLint param)
{
  next_glSamplerParameteri(sampler, pname, param);
  printGLError();

  debugPrint("glSamplerParameteri(sampler= %u, pname= %s, param= %i)\n", sampler, getEnumString(pname), param);
}

void glSamplerParameteriv(GLuint sampler, GLenum pname, const GLint* param)
{
  next_glSamplerParameteriv(sampler, pname, param);
  printGLError();

  debugPrint("glSamplerParameteriv(sampler= %u, pname= %s, param= %x)\n", sampler, getEnumString(pname), param);
}

void glSecondaryColorP3ui(GLenum type, GLuint color)
{
  next_glSecondaryColorP3ui(type, color);
  printGLError();

  debugPrint("glSecondaryColorP3ui(type= %s, color= %u)\n", getEnumString(type), color);
}

void glSecondaryColorP3uiv(GLenum type, const GLuint* color)
{
  next_glSecondaryColorP3uiv(type, color);
  printGLError();

  debugPrint("glSecondaryColorP3uiv(type= %s, color= %x)\n", getEnumString(type), color);
}

void glTexCoordP1ui(GLenum type, GLuint coords)
{
  next_glTexCoordP1ui(type, coords);
  printGLError();

  debugPrint("glTexCoordP1ui(type= %s, coords= %u)\n", getEnumString(type), coords);
}

void glTexCoordP1uiv(GLenum type, const GLuint* coords)
{
  next_glTexCoordP1uiv(type, coords);
  printGLError();

  debugPrint("glTexCoordP1uiv(type= %s, coords= %x)\n", getEnumString(type), coords);
}

void glTexCoordP2ui(GLenum type, GLuint coords)
{
  next_glTexCoordP2ui(type, coords);
  printGLError();

  debugPrint("glTexCoordP2ui(type= %s, coords= %u)\n", getEnumString(type), coords);
}

void glTexCoordP2uiv(GLenum type, const GLuint* coords)
{
  next_glTexCoordP2uiv(type, coords);
  printGLError();

  debugPrint("glTexCoordP2uiv(type= %s, coords= %x)\n", getEnumString(type), coords);
}

void glTexCoordP3ui(GLenum type, GLuint coords)
{
  next_glTexCoordP3ui(type, coords);
  printGLError();

  debugPrint("glTexCoordP3ui(type= %s, coords= %u)\n", getEnumString(type), coords);
}

void glTexCoordP3uiv(GLenum type, const GLuint* coords)
{
  next_glTexCoordP3uiv(type, coords);
  printGLError();

  debugPrint("glTexCoordP3uiv(type= %s, coords= %x)\n", getEnumString(type), coords);
}

void glTexCoordP4ui(GLenum type, GLuint coords)
{
  next_glTexCoordP4ui(type, coords);
  printGLError();

  debugPrint("glTexCoordP4ui(type= %s, coords= %u)\n", getEnumString(type), coords);
}

void glTexCoordP4uiv(GLenum type, const GLuint* coords)
{
  next_glTexCoordP4uiv(type, coords);
  printGLError();

  debugPrint("glTexCoordP4uiv(type= %s, coords= %x)\n", getEnumString(type), coords);
}

void glVertexAttribDivisor(GLuint index, GLuint divisor)
{
  next_glVertexAttribDivisor(index, divisor);
  printGLError();

  debugPrint("glVertexAttribDivisor(index= %u, divisor= %u)\n", index, divisor);
}

void glVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
  next_glVertexAttribP1ui(index, type, normalized, value);
  printGLError();

  debugPrint("glVertexAttribP1ui(index= %u, type= %s, normalized= %i, value= %u)\n", index, getEnumString(type), normalized, value);
}

void glVertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value)
{
  next_glVertexAttribP1uiv(index, type, normalized, value);
  printGLError();

  debugPrint("glVertexAttribP1uiv(index= %u, type= %s, normalized= %i, value= %x)\n", index, getEnumString(type), normalized, value);
}

void glVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
  next_glVertexAttribP2ui(index, type, normalized, value);
  printGLError();

  debugPrint("glVertexAttribP2ui(index= %u, type= %s, normalized= %i, value= %u)\n", index, getEnumString(type), normalized, value);
}

void glVertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value)
{
  next_glVertexAttribP2uiv(index, type, normalized, value);
  printGLError();

  debugPrint("glVertexAttribP2uiv(index= %u, type= %s, normalized= %i, value= %x)\n", index, getEnumString(type), normalized, value);
}

void glVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
  next_glVertexAttribP3ui(index, type, normalized, value);
  printGLError();

  debugPrint("glVertexAttribP3ui(index= %u, type= %s, normalized= %i, value= %u)\n", index, getEnumString(type), normalized, value);
}

void glVertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value)
{
  next_glVertexAttribP3uiv(index, type, normalized, value);
  printGLError();

  debugPrint("glVertexAttribP3uiv(index= %u, type= %s, normalized= %i, value= %x)\n", index, getEnumString(type), normalized, value);
}

void glVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
  next_glVertexAttribP4ui(index, type, normalized, value);
  printGLError();

  debugPrint("glVertexAttribP4ui(index= %u, type= %s, normalized= %i, value= %u)\n", index, getEnumString(type), normalized, value);
}

void glVertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value)
{
  next_glVertexAttribP4uiv(index, type, normalized, value);
  printGLError();

  debugPrint("glVertexAttribP4uiv(index= %u, type= %s, normalized= %i, value= %x)\n", index, getEnumString(type), normalized, value);
}

void glVertexP2ui(GLenum type, GLuint value)
{
  next_glVertexP2ui(type, value);
  printGLError();

  debugPrint("glVertexP2ui(type= %s, value= %u)\n", getEnumString(type), value);
}

void glVertexP2uiv(GLenum type, const GLuint* value)
{
  next_glVertexP2uiv(type, value);
  printGLError();

  debugPrint("glVertexP2uiv(type= %s, value= %x)\n", getEnumString(type), value);
}

void glVertexP3ui(GLenum type, GLuint value)
{
  next_glVertexP3ui(type, value);
  printGLError();

  debugPrint("glVertexP3ui(type= %s, value= %u)\n", getEnumString(type), value);
}

void glVertexP3uiv(GLenum type, const GLuint* value)
{
  next_glVertexP3uiv(type, value);
  printGLError();

  debugPrint("glVertexP3uiv(type= %s, value= %x)\n", getEnumString(type), value);
}

void glVertexP4ui(GLenum type, GLuint value)
{
  next_glVertexP4ui(type, value);
  printGLError();

  debugPrint("glVertexP4ui(type= %s, value= %u)\n", getEnumString(type), value);
}

void glVertexP4uiv(GLenum type, const GLuint* value)
{
  next_glVertexP4uiv(type, value);
  printGLError();

  debugPrint("glVertexP4uiv(type= %s, value= %x)\n", getEnumString(type), value);
}


// GL_VERSION_4_0

void glBeginQueryIndexed(GLenum target, GLuint index, GLuint id)
{
  next_glBeginQueryIndexed(target, index, id);
  printGLError();

  debugPrint("glBeginQueryIndexed(target= %s, index= %u, id= %u)\n", getEnumString(target), index, id);
}

void glBindTransformFeedback(GLenum target, GLuint id)
{
  next_glBindTransformFeedback(target, id);
  printGLError();

  debugPrint("glBindTransformFeedback(target= %s, id= %u)\n", getEnumString(target), id);
}

void glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
{
  next_glBlendEquationSeparatei(buf, modeRGB, modeAlpha);
  printGLError();

  debugPrint("glBlendEquationSeparatei(buf= %u, modeRGB= %s, modeAlpha= %s)\n", buf, getEnumString(modeRGB), getEnumString(modeAlpha));
}

void glBlendEquationi(GLuint buf, GLenum mode)
{
  next_glBlendEquationi(buf, mode);
  printGLError();

  debugPrint("glBlendEquationi(buf= %u, mode= %s)\n", buf, getEnumString(mode));
}

void glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
  next_glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
  printGLError();

  debugPrint("glBlendFuncSeparatei(buf= %u, srcRGB= %s, dstRGB= %s, srcAlpha= %s, dstAlpha= %s)\n", buf, getEnumString(srcRGB), getEnumString(dstRGB), getEnumString(srcAlpha), getEnumString(dstAlpha));
}

void glBlendFunci(GLuint buf, GLenum src, GLenum dst)
{
  next_glBlendFunci(buf, src, dst);
  printGLError();

  debugPrint("glBlendFunci(buf= %u, src= %s, dst= %s)\n", buf, getEnumString(src), getEnumString(dst));
}

void glDeleteTransformFeedbacks(GLsizei n, const GLuint* ids)
{
  next_glDeleteTransformFeedbacks(n, ids);
  printGLError();

  debugPrint("glDeleteTransformFeedbacks(n= %u, ids= %x)\n", n, ids);
}

void glDrawArraysIndirect(GLenum mode, const void * indirect)
{
  next_glDrawArraysIndirect(mode, indirect);
  printGLError();

  debugPrint("glDrawArraysIndirect(mode= %s, indirect= %x)\n", getEnumString(mode), indirect);
}

void glDrawElementsIndirect(GLenum mode, GLenum type, const void * indirect)
{
  next_glDrawElementsIndirect(mode, type, indirect);
  printGLError();

  debugPrint("glDrawElementsIndirect(mode= %s, type= %s, indirect= %x)\n", getEnumString(mode), getEnumString(type), indirect);
}

void glDrawTransformFeedback(GLenum mode, GLuint id)
{
  next_glDrawTransformFeedback(mode, id);
  printGLError();

  debugPrint("glDrawTransformFeedback(mode= %s, id= %u)\n", getEnumString(mode), id);
}

void glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream)
{
  next_glDrawTransformFeedbackStream(mode, id, stream);
  printGLError();

  debugPrint("glDrawTransformFeedbackStream(mode= %s, id= %u, stream= %u)\n", getEnumString(mode), id, stream);
}

void glEndQueryIndexed(GLenum target, GLuint index)
{
  next_glEndQueryIndexed(target, index);
  printGLError();

  debugPrint("glEndQueryIndexed(target= %s, index= %u)\n", getEnumString(target), index);
}

void glGenTransformFeedbacks(GLsizei n, GLuint* ids)
{
  next_glGenTransformFeedbacks(n, ids);
  printGLError();

  debugPrint("glGenTransformFeedbacks(n= %u, ids= %x)\n", n, ids);
}

void glGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name)
{
  next_glGetActiveSubroutineName(program, shadertype, index, bufsize, length, name);
  printGLError();

  debugPrint("glGetActiveSubroutineName(program= %u, shadertype= %s, index= %u, bufsize= %u, length= %x, name= %s)\n", program, getEnumString(shadertype), index, bufsize, length, name);
}

void glGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name)
{
  next_glGetActiveSubroutineUniformName(program, shadertype, index, bufsize, length, name);
  printGLError();

  debugPrint("glGetActiveSubroutineUniformName(program= %u, shadertype= %s, index= %u, bufsize= %u, length= %x, name= %s)\n", program, getEnumString(shadertype), index, bufsize, length, name);
}

void glGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint* values)
{
  next_glGetActiveSubroutineUniformiv(program, shadertype, index, pname, values);
  printGLError();

  debugPrint("glGetActiveSubroutineUniformiv(program= %u, shadertype= %s, index= %u, pname= %s, values= %x)\n", program, getEnumString(shadertype), index, getEnumString(pname), values);
}

void glGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint* values)
{
  next_glGetProgramStageiv(program, shadertype, pname, values);
  printGLError();

  debugPrint("glGetProgramStageiv(program= %u, shadertype= %s, pname= %s, values= %x)\n", program, getEnumString(shadertype), getEnumString(pname), values);
}

void glGetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint* params)
{
  next_glGetQueryIndexediv(target, index, pname, params);
  printGLError();

  debugPrint("glGetQueryIndexediv(target= %s, index= %u, pname= %s, params= %x)\n", getEnumString(target), index, getEnumString(pname), params);
}

GLuint glGetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar* name)
{
  GLuint result= next_glGetSubroutineIndex(program, shadertype, name);
  printGLError();

  debugPrint("glGetSubroutineIndex(program= %u, shadertype= %s, name= %x)= %u\n", program, getEnumString(shadertype), name, result);

  return result;
}

GLint glGetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar* name)
{
  GLint result= next_glGetSubroutineUniformLocation(program, shadertype, name);
  printGLError();

  debugPrint("glGetSubroutineUniformLocation(program= %u, shadertype= %s, name= %x)= %i\n", program, getEnumString(shadertype), name, result);

  return result;
}

void glGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint* params)
{
  next_glGetUniformSubroutineuiv(shadertype, location, params);
  printGLError();

  debugPrint("glGetUniformSubroutineuiv(shadertype= %s, location= %i, params= %x)\n", getEnumString(shadertype), location, params);
}

void glGetUniformdv(GLuint program, GLint location, GLdouble* params)
{
  next_glGetUniformdv(program, location, params);
  printGLError();

  debugPrint("glGetUniformdv(program= %u, location= %i, params= %x)\n", program, location, params);
}

GLboolean glIsTransformFeedback(GLuint id)
{
  GLboolean result= next_glIsTransformFeedback(id);
  printGLError();

  debugPrint("glIsTransformFeedback(id= %u)= %i\n", id, result);

  return result;
}

void glMinSampleShading(GLfloat value)
{
  next_glMinSampleShading(value);
  printGLError();

  debugPrint("glMinSampleShading(value= %f)\n", value);
}

void glPatchParameterfv(GLenum pname, const GLfloat* values)
{
  next_glPatchParameterfv(pname, values);
  printGLError();

  debugPrint("glPatchParameterfv(pname= %s, values= %x)\n", getEnumString(pname), values);
}

void glPatchParameteri(GLenum pname, GLint value)
{
  next_glPatchParameteri(pname, value);
  printGLError();

  debugPrint("glPatchParameteri(pname= %s, value= %i)\n", getEnumString(pname), value);
}

void glPauseTransformFeedback()
{
  next_glPauseTransformFeedback();
  printGLError();

  debugPrint("glPauseTransformFeedback()\n");
}

void glResumeTransformFeedback()
{
  next_glResumeTransformFeedback();
  printGLError();

  debugPrint("glResumeTransformFeedback()\n");
}

void glUniform1d(GLint location, GLdouble x)
{
  next_glUniform1d(location, x);
  printGLError();

  debugPrint("glUniform1d(location= %i, x= %f)\n", location, x);
}

void glUniform1dv(GLint location, GLsizei count, const GLdouble* value)
{
  next_glUniform1dv(location, count, value);
  printGLError();

  debugPrint("glUniform1dv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform2d(GLint location, GLdouble x, GLdouble y)
{
  next_glUniform2d(location, x, y);
  printGLError();

  debugPrint("glUniform2d(location= %i, x= %f, y= %f)\n", location, x, y);
}

void glUniform2dv(GLint location, GLsizei count, const GLdouble* value)
{
  next_glUniform2dv(location, count, value);
  printGLError();

  debugPrint("glUniform2dv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z)
{
  next_glUniform3d(location, x, y, z);
  printGLError();

  debugPrint("glUniform3d(location= %i, x= %f, y= %f, z= %f)\n", location, x, y, z);
}

void glUniform3dv(GLint location, GLsizei count, const GLdouble* value)
{
  next_glUniform3dv(location, count, value);
  printGLError();

  debugPrint("glUniform3dv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
  next_glUniform4d(location, x, y, z, w);
  printGLError();

  debugPrint("glUniform4d(location= %i, x= %f, y= %f, z= %f, w= %f)\n", location, x, y, z, w);
}

void glUniform4dv(GLint location, GLsizei count, const GLdouble* value)
{
  next_glUniform4dv(location, count, value);
  printGLError();

  debugPrint("glUniform4dv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  next_glUniformMatrix2dv(location, count, transpose, value);
  printGLError();

  debugPrint("glUniformMatrix2dv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  next_glUniformMatrix2x3dv(location, count, transpose, value);
  printGLError();

  debugPrint("glUniformMatrix2x3dv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  next_glUniformMatrix2x4dv(location, count, transpose, value);
  printGLError();

  debugPrint("glUniformMatrix2x4dv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  next_glUniformMatrix3dv(location, count, transpose, value);
  printGLError();

  debugPrint("glUniformMatrix3dv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  next_glUniformMatrix3x2dv(location, count, transpose, value);
  printGLError();

  debugPrint("glUniformMatrix3x2dv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  next_glUniformMatrix3x4dv(location, count, transpose, value);
  printGLError();

  debugPrint("glUniformMatrix3x4dv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  next_glUniformMatrix4dv(location, count, transpose, value);
  printGLError();

  debugPrint("glUniformMatrix4dv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  next_glUniformMatrix4x2dv(location, count, transpose, value);
  printGLError();

  debugPrint("glUniformMatrix4x2dv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  next_glUniformMatrix4x3dv(location, count, transpose, value);
  printGLError();

  debugPrint("glUniformMatrix4x3dv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint* indices)
{
  next_glUniformSubroutinesuiv(shadertype, count, indices);
  printGLError();

  debugPrint("glUniformSubroutinesuiv(shadertype= %s, count= %u, indices= %x)\n", getEnumString(shadertype), count, indices);
}


// GL_VERSION_4_1

void glActiveShaderProgram(GLuint pipeline, GLuint program)
{
  next_glActiveShaderProgram(pipeline, program);
  printGLError();

  debugPrint("glActiveShaderProgram(pipeline= %u, program= %u)\n", pipeline, program);
}

void glBindProgramPipeline(GLuint pipeline)
{
  next_glBindProgramPipeline(pipeline);
  printGLError();

  debugPrint("glBindProgramPipeline(pipeline= %u)\n", pipeline);
}

void glClearDepthf(GLfloat d)
{
  next_glClearDepthf(d);
  printGLError();

  debugPrint("glClearDepthf(d= %f)\n", d);
}

GLuint glCreateShaderProgramv(GLenum type, GLsizei count, const GLchar*const* strings)
{
  GLuint result= next_glCreateShaderProgramv(type, count, strings);
  printGLError();

  debugPrint("glCreateShaderProgramv(type= %s, count= %u, strings= %x)= %u\n", getEnumString(type), count, strings, result);

  return result;
}

void glDeleteProgramPipelines(GLsizei n, const GLuint* pipelines)
{
  next_glDeleteProgramPipelines(n, pipelines);
  printGLError();

  debugPrint("glDeleteProgramPipelines(n= %u, pipelines= %x)\n", n, pipelines);
}

void glDepthRangeArrayv(GLuint first, GLsizei count, const GLdouble* v)
{
  next_glDepthRangeArrayv(first, count, v);
  printGLError();

  debugPrint("glDepthRangeArrayv(first= %u, count= %u, v= %x)\n", first, count, v);
}

void glDepthRangeIndexed(GLuint index, GLdouble n, GLdouble f)
{
  next_glDepthRangeIndexed(index, n, f);
  printGLError();

  debugPrint("glDepthRangeIndexed(index= %u, n= %f, f= %f)\n", index, n, f);
}

void glDepthRangef(GLfloat n, GLfloat f)
{
  next_glDepthRangef(n, f);
  printGLError();

  debugPrint("glDepthRangef(n= %f, f= %f)\n", n, f);
}

void glGenProgramPipelines(GLsizei n, GLuint* pipelines)
{
  next_glGenProgramPipelines(n, pipelines);
  printGLError();

  debugPrint("glGenProgramPipelines(n= %u, pipelines= %x)\n", n, pipelines);
}

void glGetDoublei_v(GLenum target, GLuint index, GLdouble* data)
{
  next_glGetDoublei_v(target, index, data);
  printGLError();

  debugPrint("glGetDoublei_v(target= %s, index= %u, data= %x)\n", getEnumString(target), index, data);
}

void glGetFloati_v(GLenum target, GLuint index, GLfloat* data)
{
  next_glGetFloati_v(target, index, data);
  printGLError();

  debugPrint("glGetFloati_v(target= %s, index= %u, data= %x)\n", getEnumString(target), index, data);
}

void glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void * binary)
{
  next_glGetProgramBinary(program, bufSize, length, binaryFormat, binary);
  printGLError();

  debugPrint("glGetProgramBinary(program= %u, bufSize= %u, length= %x, binaryFormat= %x, binary= %x)\n", program, bufSize, length, binaryFormat, binary);
}

void glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
  next_glGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
  printGLError();

  debugPrint("glGetProgramPipelineInfoLog(pipeline= %u, bufSize= %u, length= %x, infoLog= %s)\n", pipeline, bufSize, length, infoLog);
}

void glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint* params)
{
  next_glGetProgramPipelineiv(pipeline, pname, params);
  printGLError();

  debugPrint("glGetProgramPipelineiv(pipeline= %u, pname= %s, params= %x)\n", pipeline, getEnumString(pname), params);
}

void glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)
{
  next_glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
  printGLError();

  debugPrint("glGetShaderPrecisionFormat(shadertype= %s, precisiontype= %s, range= %x, precision= %x)\n", getEnumString(shadertype), getEnumString(precisiontype), range, precision);
}

void glGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble* params)
{
  next_glGetVertexAttribLdv(index, pname, params);
  printGLError();

  debugPrint("glGetVertexAttribLdv(index= %u, pname= %s, params= %x)\n", index, getEnumString(pname), params);
}

GLboolean glIsProgramPipeline(GLuint pipeline)
{
  GLboolean result= next_glIsProgramPipeline(pipeline);
  printGLError();

  debugPrint("glIsProgramPipeline(pipeline= %u)= %i\n", pipeline, result);

  return result;
}

void glProgramBinary(GLuint program, GLenum binaryFormat, const void * binary, GLsizei length)
{
  next_glProgramBinary(program, binaryFormat, binary, length);
  printGLError();

  debugPrint("glProgramBinary(program= %u, binaryFormat= %s, binary= %x, length= %u)\n", program, getEnumString(binaryFormat), binary, length);
}

void glProgramParameteri(GLuint program, GLenum pname, GLint value)
{
  next_glProgramParameteri(program, pname, value);
  printGLError();

  debugPrint("glProgramParameteri(program= %u, pname= %s, value= %i)\n", program, getEnumString(pname), value);
}

void glProgramUniform1d(GLuint program, GLint location, GLdouble v0)
{
  next_glProgramUniform1d(program, location, v0);
  printGLError();

  debugPrint("glProgramUniform1d(program= %u, location= %i, v0= %f)\n", program, location, v0);
}

void glProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble* value)
{
  next_glProgramUniform1dv(program, location, count, value);
  printGLError();

  debugPrint("glProgramUniform1dv(program= %u, location= %i, count= %u, value= %x)\n", program, location, count, value);
}

void glProgramUniform1f(GLuint program, GLint location, GLfloat v0)
{
  next_glProgramUniform1f(program, location, v0);
  printGLError();

  debugPrint("glProgramUniform1f(program= %u, location= %i, v0= %f)\n", program, location, v0);
}

void glProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat* value)
{
  next_glProgramUniform1fv(program, location, count, value);
  printGLError();

  debugPrint("glProgramUniform1fv(program= %u, location= %i, count= %u, value= %x)\n", program, location, count, value);
}

void glProgramUniform1i(GLuint program, GLint location, GLint v0)
{
  next_glProgramUniform1i(program, location, v0);
  printGLError();

  debugPrint("glProgramUniform1i(program= %u, location= %i, v0= %i)\n", program, location, v0);
}

void glProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint* value)
{
  next_glProgramUniform1iv(program, location, count, value);
  printGLError();

  debugPrint("glProgramUniform1iv(program= %u, location= %i, count= %u, value= %x)\n", program, location, count, value);
}

void glProgramUniform1ui(GLuint program, GLint location, GLuint v0)
{
  next_glProgramUniform1ui(program, location, v0);
  printGLError();

  debugPrint("glProgramUniform1ui(program= %u, location= %i, v0= %u)\n", program, location, v0);
}

void glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint* value)
{
  next_glProgramUniform1uiv(program, location, count, value);
  printGLError();

  debugPrint("glProgramUniform1uiv(program= %u, location= %i, count= %u, value= %x)\n", program, location, count, value);
}

void glProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1)
{
  next_glProgramUniform2d(program, location, v0, v1);
  printGLError();

  debugPrint("glProgramUniform2d(program= %u, location= %i, v0= %f, v1= %f)\n", program, location, v0, v1);
}

void glProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble* value)
{
  next_glProgramUniform2dv(program, location, count, value);
  printGLError();

  debugPrint("glProgramUniform2dv(program= %u, location= %i, count= %u, value= %x)\n", program, location, count, value);
}

void glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1)
{
  next_glProgramUniform2f(program, location, v0, v1);
  printGLError();

  debugPrint("glProgramUniform2f(program= %u, location= %i, v0= %f, v1= %f)\n", program, location, v0, v1);
}

void glProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat* value)
{
  next_glProgramUniform2fv(program, location, count, value);
  printGLError();

  debugPrint("glProgramUniform2fv(program= %u, location= %i, count= %u, value= %x)\n", program, location, count, value);
}

void glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1)
{
  next_glProgramUniform2i(program, location, v0, v1);
  printGLError();

  debugPrint("glProgramUniform2i(program= %u, location= %i, v0= %i, v1= %i)\n", program, location, v0, v1);
}

void glProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint* value)
{
  next_glProgramUniform2iv(program, location, count, value);
  printGLError();

  debugPrint("glProgramUniform2iv(program= %u, location= %i, count= %u, value= %x)\n", program, location, count, value);
}

void glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1)
{
  next_glProgramUniform2ui(program, location, v0, v1);
  printGLError();

  debugPrint("glProgramUniform2ui(program= %u, location= %i, v0= %u, v1= %u)\n", program, location, v0, v1);
}

void glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint* value)
{
  next_glProgramUniform2uiv(program, location, count, value);
  printGLError();

  debugPrint("glProgramUniform2uiv(program= %u, location= %i, count= %u, value= %x)\n", program, location, count, value);
}

void glProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2)
{
  next_glProgramUniform3d(program, location, v0, v1, v2);
  printGLError();

  debugPrint("glProgramUniform3d(program= %u, location= %i, v0= %f, v1= %f, v2= %f)\n", program, location, v0, v1, v2);
}

void glProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble* value)
{
  next_glProgramUniform3dv(program, location, count, value);
  printGLError();

  debugPrint("glProgramUniform3dv(program= %u, location= %i, count= %u, value= %x)\n", program, location, count, value);
}

void glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
  next_glProgramUniform3f(program, location, v0, v1, v2);
  printGLError();

  debugPrint("glProgramUniform3f(program= %u, location= %i, v0= %f, v1= %f, v2= %f)\n", program, location, v0, v1, v2);
}

void glProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat* value)
{
  next_glProgramUniform3fv(program, location, count, value);
  printGLError();

  debugPrint("glProgramUniform3fv(program= %u, location= %i, count= %u, value= %x)\n", program, location, count, value);
}

void glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2)
{
  next_glProgramUniform3i(program, location, v0, v1, v2);
  printGLError();

  debugPrint("glProgramUniform3i(program= %u, location= %i, v0= %i, v1= %i, v2= %i)\n", program, location, v0, v1, v2);
}

void glProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint* value)
{
  next_glProgramUniform3iv(program, location, count, value);
  printGLError();

  debugPrint("glProgramUniform3iv(program= %u, location= %i, count= %u, value= %x)\n", program, location, count, value);
}

void glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2)
{
  next_glProgramUniform3ui(program, location, v0, v1, v2);
  printGLError();

  debugPrint("glProgramUniform3ui(program= %u, location= %i, v0= %u, v1= %u, v2= %u)\n", program, location, v0, v1, v2);
}

void glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint* value)
{
  next_glProgramUniform3uiv(program, location, count, value);
  printGLError();

  debugPrint("glProgramUniform3uiv(program= %u, location= %i, count= %u, value= %x)\n", program, location, count, value);
}

void glProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3)
{
  next_glProgramUniform4d(program, location, v0, v1, v2, v3);
  printGLError();

  debugPrint("glProgramUniform4d(program= %u, location= %i, v0= %f, v1= %f, v2= %f, v3= %f)\n", program, location, v0, v1, v2, v3);
}

void glProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble* value)
{
  next_glProgramUniform4dv(program, location, count, value);
  printGLError();

  debugPrint("glProgramUniform4dv(program= %u, location= %i, count= %u, value= %x)\n", program, location, count, value);
}

void glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
  next_glProgramUniform4f(program, location, v0, v1, v2, v3);
  printGLError();

  debugPrint("glProgramUniform4f(program= %u, location= %i, v0= %f, v1= %f, v2= %f, v3= %f)\n", program, location, v0, v1, v2, v3);
}

void glProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat* value)
{
  next_glProgramUniform4fv(program, location, count, value);
  printGLError();

  debugPrint("glProgramUniform4fv(program= %u, location= %i, count= %u, value= %x)\n", program, location, count, value);
}

void glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
  next_glProgramUniform4i(program, location, v0, v1, v2, v3);
  printGLError();

  debugPrint("glProgramUniform4i(program= %u, location= %i, v0= %i, v1= %i, v2= %i, v3= %i)\n", program, location, v0, v1, v2, v3);
}

void glProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint* value)
{
  next_glProgramUniform4iv(program, location, count, value);
  printGLError();

  debugPrint("glProgramUniform4iv(program= %u, location= %i, count= %u, value= %x)\n", program, location, count, value);
}

void glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
  next_glProgramUniform4ui(program, location, v0, v1, v2, v3);
  printGLError();

  debugPrint("glProgramUniform4ui(program= %u, location= %i, v0= %u, v1= %u, v2= %u, v3= %u)\n", program, location, v0, v1, v2, v3);
}

void glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint* value)
{
  next_glProgramUniform4uiv(program, location, count, value);
  printGLError();

  debugPrint("glProgramUniform4uiv(program= %u, location= %i, count= %u, value= %x)\n", program, location, count, value);
}

void glProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  next_glProgramUniformMatrix2dv(program, location, count, transpose, value);
  printGLError();

  debugPrint("glProgramUniformMatrix2dv(program= %u, location= %i, count= %u, transpose= %i, value= %x)\n", program, location, count, transpose, value);
}

void glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glProgramUniformMatrix2fv(program, location, count, transpose, value);
  printGLError();

  debugPrint("glProgramUniformMatrix2fv(program= %u, location= %i, count= %u, transpose= %i, value= %x)\n", program, location, count, transpose, value);
}

void glProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  next_glProgramUniformMatrix2x3dv(program, location, count, transpose, value);
  printGLError();

  debugPrint("glProgramUniformMatrix2x3dv(program= %u, location= %i, count= %u, transpose= %i, value= %x)\n", program, location, count, transpose, value);
}

void glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glProgramUniformMatrix2x3fv(program, location, count, transpose, value);
  printGLError();

  debugPrint("glProgramUniformMatrix2x3fv(program= %u, location= %i, count= %u, transpose= %i, value= %x)\n", program, location, count, transpose, value);
}

void glProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  next_glProgramUniformMatrix2x4dv(program, location, count, transpose, value);
  printGLError();

  debugPrint("glProgramUniformMatrix2x4dv(program= %u, location= %i, count= %u, transpose= %i, value= %x)\n", program, location, count, transpose, value);
}

void glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glProgramUniformMatrix2x4fv(program, location, count, transpose, value);
  printGLError();

  debugPrint("glProgramUniformMatrix2x4fv(program= %u, location= %i, count= %u, transpose= %i, value= %x)\n", program, location, count, transpose, value);
}

void glProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  next_glProgramUniformMatrix3dv(program, location, count, transpose, value);
  printGLError();

  debugPrint("glProgramUniformMatrix3dv(program= %u, location= %i, count= %u, transpose= %i, value= %x)\n", program, location, count, transpose, value);
}

void glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glProgramUniformMatrix3fv(program, location, count, transpose, value);
  printGLError();

  debugPrint("glProgramUniformMatrix3fv(program= %u, location= %i, count= %u, transpose= %i, value= %x)\n", program, location, count, transpose, value);
}

void glProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  next_glProgramUniformMatrix3x2dv(program, location, count, transpose, value);
  printGLError();

  debugPrint("glProgramUniformMatrix3x2dv(program= %u, location= %i, count= %u, transpose= %i, value= %x)\n", program, location, count, transpose, value);
}

void glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glProgramUniformMatrix3x2fv(program, location, count, transpose, value);
  printGLError();

  debugPrint("glProgramUniformMatrix3x2fv(program= %u, location= %i, count= %u, transpose= %i, value= %x)\n", program, location, count, transpose, value);
}

void glProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  next_glProgramUniformMatrix3x4dv(program, location, count, transpose, value);
  printGLError();

  debugPrint("glProgramUniformMatrix3x4dv(program= %u, location= %i, count= %u, transpose= %i, value= %x)\n", program, location, count, transpose, value);
}

void glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glProgramUniformMatrix3x4fv(program, location, count, transpose, value);
  printGLError();

  debugPrint("glProgramUniformMatrix3x4fv(program= %u, location= %i, count= %u, transpose= %i, value= %x)\n", program, location, count, transpose, value);
}

void glProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  next_glProgramUniformMatrix4dv(program, location, count, transpose, value);
  printGLError();

  debugPrint("glProgramUniformMatrix4dv(program= %u, location= %i, count= %u, transpose= %i, value= %x)\n", program, location, count, transpose, value);
}

void glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glProgramUniformMatrix4fv(program, location, count, transpose, value);
  printGLError();

  debugPrint("glProgramUniformMatrix4fv(program= %u, location= %i, count= %u, transpose= %i, value= %x)\n", program, location, count, transpose, value);
}

void glProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  next_glProgramUniformMatrix4x2dv(program, location, count, transpose, value);
  printGLError();

  debugPrint("glProgramUniformMatrix4x2dv(program= %u, location= %i, count= %u, transpose= %i, value= %x)\n", program, location, count, transpose, value);
}

void glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glProgramUniformMatrix4x2fv(program, location, count, transpose, value);
  printGLError();

  debugPrint("glProgramUniformMatrix4x2fv(program= %u, location= %i, count= %u, transpose= %i, value= %x)\n", program, location, count, transpose, value);
}

void glProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  next_glProgramUniformMatrix4x3dv(program, location, count, transpose, value);
  printGLError();

  debugPrint("glProgramUniformMatrix4x3dv(program= %u, location= %i, count= %u, transpose= %i, value= %x)\n", program, location, count, transpose, value);
}

void glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glProgramUniformMatrix4x3fv(program, location, count, transpose, value);
  printGLError();

  debugPrint("glProgramUniformMatrix4x3fv(program= %u, location= %i, count= %u, transpose= %i, value= %x)\n", program, location, count, transpose, value);
}

void glReleaseShaderCompiler()
{
  next_glReleaseShaderCompiler();
  printGLError();

  debugPrint("glReleaseShaderCompiler()\n");
}

void glScissorArrayv(GLuint first, GLsizei count, const GLint* v)
{
  next_glScissorArrayv(first, count, v);
  printGLError();

  debugPrint("glScissorArrayv(first= %u, count= %u, v= %x)\n", first, count, v);
}

void glScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height)
{
  next_glScissorIndexed(index, left, bottom, width, height);
  printGLError();

  debugPrint("glScissorIndexed(index= %u, left= %i, bottom= %i, width= %u, height= %u)\n", index, left, bottom, width, height);
}

void glScissorIndexedv(GLuint index, const GLint* v)
{
  next_glScissorIndexedv(index, v);
  printGLError();

  debugPrint("glScissorIndexedv(index= %u, v= %x)\n", index, v);
}

void glShaderBinary(GLsizei count, const GLuint* shaders, GLenum binaryformat, const void * binary, GLsizei length)
{
  next_glShaderBinary(count, shaders, binaryformat, binary, length);
  printGLError();

  debugPrint("glShaderBinary(count= %u, shaders= %x, binaryformat= %s, binary= %x, length= %u)\n", count, shaders, getEnumString(binaryformat), binary, length);
}

void glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program)
{
  next_glUseProgramStages(pipeline, stages, program);
  printGLError();

  debugPrint("glUseProgramStages(pipeline= %u, stages= %x, program= %u)\n", pipeline, stages, program);
}

void glValidateProgramPipeline(GLuint pipeline)
{
  next_glValidateProgramPipeline(pipeline);
  printGLError();

  debugPrint("glValidateProgramPipeline(pipeline= %u)\n", pipeline);
}

void glVertexAttribL1d(GLuint index, GLdouble x)
{
  next_glVertexAttribL1d(index, x);
  printGLError();

  debugPrint("glVertexAttribL1d(index= %u, x= %f)\n", index, x);
}

void glVertexAttribL1dv(GLuint index, const GLdouble* v)
{
  next_glVertexAttribL1dv(index, v);
  printGLError();

  debugPrint("glVertexAttribL1dv(index= %u, v= %x)\n", index, v);
}

void glVertexAttribL2d(GLuint index, GLdouble x, GLdouble y)
{
  next_glVertexAttribL2d(index, x, y);
  printGLError();

  debugPrint("glVertexAttribL2d(index= %u, x= %f, y= %f)\n", index, x, y);
}

void glVertexAttribL2dv(GLuint index, const GLdouble* v)
{
  next_glVertexAttribL2dv(index, v);
  printGLError();

  debugPrint("glVertexAttribL2dv(index= %u, v= %x)\n", index, v);
}

void glVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
  next_glVertexAttribL3d(index, x, y, z);
  printGLError();

  debugPrint("glVertexAttribL3d(index= %u, x= %f, y= %f, z= %f)\n", index, x, y, z);
}

void glVertexAttribL3dv(GLuint index, const GLdouble* v)
{
  next_glVertexAttribL3dv(index, v);
  printGLError();

  debugPrint("glVertexAttribL3dv(index= %u, v= %x)\n", index, v);
}

void glVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
  next_glVertexAttribL4d(index, x, y, z, w);
  printGLError();

  debugPrint("glVertexAttribL4d(index= %u, x= %f, y= %f, z= %f, w= %f)\n", index, x, y, z, w);
}

void glVertexAttribL4dv(GLuint index, const GLdouble* v)
{
  next_glVertexAttribL4dv(index, v);
  printGLError();

  debugPrint("glVertexAttribL4dv(index= %u, v= %x)\n", index, v);
}

void glVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer)
{
  next_glVertexAttribLPointer(index, size, type, stride, pointer);
  printGLError();

  debugPrint("glVertexAttribLPointer(index= %u, size= %i, type= %s, stride= %u, pointer= %x)\n", index, size, getEnumString(type), stride, pointer);
}

void glViewportArrayv(GLuint first, GLsizei count, const GLfloat* v)
{
  next_glViewportArrayv(first, count, v);
  printGLError();

  debugPrint("glViewportArrayv(first= %u, count= %u, v= %x)\n", first, count, v);
}

void glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
  next_glViewportIndexedf(index, x, y, w, h);
  printGLError();

  debugPrint("glViewportIndexedf(index= %u, x= %f, y= %f, w= %f, h= %f)\n", index, x, y, w, h);
}

void glViewportIndexedfv(GLuint index, const GLfloat* v)
{
  next_glViewportIndexedfv(index, v);
  printGLError();

  debugPrint("glViewportIndexedfv(index= %u, v= %x)\n", index, v);
}


// GL_VERSION_4_2

void glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format)
{
  next_glBindImageTexture(unit, texture, level, layered, layer, access, format);
  printGLError();

  debugPrint("glBindImageTexture(unit= %u, texture= %u, level= %i, layered= %i, layer= %i, access= %s, format= %s)\n", unit, texture, level, layered, layer, getEnumString(access), getEnumString(format));
}

void glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance)
{
  next_glDrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance);
  printGLError();

  debugPrint("glDrawArraysInstancedBaseInstance(mode= %s, first= %i, count= %u, instancecount= %u, baseinstance= %u)\n", getEnumString(mode), first, count, instancecount, baseinstance);
}

void glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLuint baseinstance)
{
  next_glDrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance);
  printGLError();

  debugPrint("glDrawElementsInstancedBaseInstance(mode= %s, count= %u, type= %s, indices= %x, instancecount= %u, baseinstance= %u)\n", getEnumString(mode), count, getEnumString(type), indices, instancecount, baseinstance);
}

void glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance)
{
  next_glDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance);
  printGLError();

  debugPrint("glDrawElementsInstancedBaseVertexBaseInstance(mode= %s, count= %u, type= %s, indices= %x, instancecount= %u, basevertex= %i, baseinstance= %u)\n", getEnumString(mode), count, getEnumString(type), indices, instancecount, basevertex, baseinstance);
}

void glDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount)
{
  next_glDrawTransformFeedbackInstanced(mode, id, instancecount);
  printGLError();

  debugPrint("glDrawTransformFeedbackInstanced(mode= %s, id= %u, instancecount= %u)\n", getEnumString(mode), id, instancecount);
}

void glDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount)
{
  next_glDrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount);
  printGLError();

  debugPrint("glDrawTransformFeedbackStreamInstanced(mode= %s, id= %u, stream= %u, instancecount= %u)\n", getEnumString(mode), id, stream, instancecount);
}

void glGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint* params)
{
  next_glGetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);
  printGLError();

  debugPrint("glGetActiveAtomicCounterBufferiv(program= %u, bufferIndex= %u, pname= %s, params= %x)\n", program, bufferIndex, getEnumString(pname), params);
}

void glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint* params)
{
  next_glGetInternalformativ(target, internalformat, pname, bufSize, params);
  printGLError();

  debugPrint("glGetInternalformativ(target= %s, internalformat= %s, pname= %s, bufSize= %u, params= %x)\n", getEnumString(target), getEnumString(internalformat), getEnumString(pname), bufSize, params);
}

void glMemoryBarrier(GLbitfield barriers)
{
  next_glMemoryBarrier(barriers);
  printGLError();

  debugPrint("glMemoryBarrier(barriers= %x)\n", barriers);
}

void glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
{
  next_glTexStorage1D(target, levels, internalformat, width);
  printGLError();

  debugPrint("glTexStorage1D(target= %s, levels= %u, internalformat= %s, width= %u)\n", getEnumString(target), levels, getEnumString(internalformat), width);
}

void glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
  next_glTexStorage2D(target, levels, internalformat, width, height);
  printGLError();

  debugPrint("glTexStorage2D(target= %s, levels= %u, internalformat= %s, width= %u, height= %u)\n", getEnumString(target), levels, getEnumString(internalformat), width, height);
}

void glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
  next_glTexStorage3D(target, levels, internalformat, width, height, depth);
  printGLError();

  debugPrint("glTexStorage3D(target= %s, levels= %u, internalformat= %s, width= %u, height= %u, depth= %u)\n", getEnumString(target), levels, getEnumString(internalformat), width, height, depth);
}


// GL_VERSION_4_3

void glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
{
  next_glBindVertexBuffer(bindingindex, buffer, offset, stride);
  printGLError();

  debugPrint("glBindVertexBuffer(bindingindex= %u, buffer= %u, offset= %i, stride= %u)\n", bindingindex, buffer, offset, stride);
}

void glClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void * data)
{
  next_glClearBufferData(target, internalformat, format, type, data);
  printGLError();

  debugPrint("glClearBufferData(target= %s, internalformat= %s, format= %s, type= %s, data= %x)\n", getEnumString(target), getEnumString(internalformat), getEnumString(format), getEnumString(type), data);
}

void glClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data)
{
  next_glClearBufferSubData(target, internalformat, offset, size, format, type, data);
  printGLError();

  debugPrint("glClearBufferSubData(target= %s, internalformat= %s, offset= %i, size= %u, format= %s, type= %s, data= %x)\n", getEnumString(target), getEnumString(internalformat), offset, size, getEnumString(format), getEnumString(type), data);
}

void glCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth)
{
  next_glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
  printGLError();

  debugPrint("glCopyImageSubData(srcName= %u, srcTarget= %s, srcLevel= %i, srcX= %i, srcY= %i, srcZ= %i, dstName= %u, dstTarget= %s, dstLevel= %i, dstX= %i, dstY= %i, dstZ= %i, srcWidth= %u, srcHeight= %u, srcDepth= %u)\n", srcName, getEnumString(srcTarget), srcLevel, srcX, srcY, srcZ, dstName, getEnumString(dstTarget), dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
}

void glDebugMessageCallback(GLDEBUGPROC callback, const void * userParam)
{
  next_glDebugMessageCallback(callback, userParam);
  printGLError();

  debugPrint("glDebugMessageCallback(callback= %x, userParam= %x)\n", callback, userParam);
}

void glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled)
{
  next_glDebugMessageControl(source, type, severity, count, ids, enabled);
  printGLError();

  debugPrint("glDebugMessageControl(source= %s, type= %s, severity= %s, count= %u, ids= %x, enabled= %i)\n", getEnumString(source), getEnumString(type), getEnumString(severity), count, ids, enabled);
}

void glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* buf)
{
  next_glDebugMessageInsert(source, type, id, severity, length, buf);
  printGLError();

  debugPrint("glDebugMessageInsert(source= %s, type= %s, id= %u, severity= %s, length= %u, buf= %x)\n", getEnumString(source), getEnumString(type), id, getEnumString(severity), length, buf);
}

void glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z)
{
  next_glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
  printGLError();

  debugPrint("glDispatchCompute(num_groups_x= %u, num_groups_y= %u, num_groups_z= %u)\n", num_groups_x, num_groups_y, num_groups_z);
}

void glDispatchComputeIndirect(GLintptr indirect)
{
  next_glDispatchComputeIndirect(indirect);
  printGLError();

  debugPrint("glDispatchComputeIndirect(indirect= %i)\n", indirect);
}

void glFramebufferParameteri(GLenum target, GLenum pname, GLint param)
{
  next_glFramebufferParameteri(target, pname, param);
  printGLError();

  debugPrint("glFramebufferParameteri(target= %s, pname= %s, param= %i)\n", getEnumString(target), getEnumString(pname), param);
}

GLuint glGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum* sources, GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog)
{
  GLuint result= next_glGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
  printGLError();

  debugPrint("glGetDebugMessageLog(count= %u, bufSize= %u, sources= %x, types= %x, ids= %x, severities= %x, lengths= %x, messageLog= %s)= %u\n", count, bufSize, sources, types, ids, severities, lengths, messageLog, result);

  return result;
}

void glGetFramebufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
  next_glGetFramebufferParameteriv(target, pname, params);
  printGLError();

  debugPrint("glGetFramebufferParameteriv(target= %s, pname= %s, params= %x)\n", getEnumString(target), getEnumString(pname), params);
}

void glGetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64* params)
{
  next_glGetInternalformati64v(target, internalformat, pname, bufSize, params);
  printGLError();

  debugPrint("glGetInternalformati64v(target= %s, internalformat= %s, pname= %s, bufSize= %u, params= %x)\n", getEnumString(target), getEnumString(internalformat), getEnumString(pname), bufSize, params);
}

void glGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei* length, GLchar* label)
{
  next_glGetObjectLabel(identifier, name, bufSize, length, label);
  printGLError();

  debugPrint("glGetObjectLabel(identifier= %s, name= %u, bufSize= %u, length= %x, label= %s)\n", getEnumString(identifier), name, bufSize, length, label);
}

void glGetObjectPtrLabel(const void * ptr, GLsizei bufSize, GLsizei* length, GLchar* label)
{
  next_glGetObjectPtrLabel(ptr, bufSize, length, label);
  printGLError();

  debugPrint("glGetObjectPtrLabel(ptr= %x, bufSize= %u, length= %x, label= %s)\n", ptr, bufSize, length, label);
}

void glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint* params)
{
  next_glGetProgramInterfaceiv(program, programInterface, pname, params);
  printGLError();

  debugPrint("glGetProgramInterfaceiv(program= %u, programInterface= %s, pname= %s, params= %x)\n", program, getEnumString(programInterface), getEnumString(pname), params);
}

GLuint glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar* name)
{
  GLuint result= next_glGetProgramResourceIndex(program, programInterface, name);
  printGLError();

  debugPrint("glGetProgramResourceIndex(program= %u, programInterface= %s, name= %x)= %u\n", program, getEnumString(programInterface), name, result);

  return result;
}

GLint glGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar* name)
{
  GLint result= next_glGetProgramResourceLocation(program, programInterface, name);
  printGLError();

  debugPrint("glGetProgramResourceLocation(program= %u, programInterface= %s, name= %x)= %i\n", program, getEnumString(programInterface), name, result);

  return result;
}

GLint glGetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar* name)
{
  GLint result= next_glGetProgramResourceLocationIndex(program, programInterface, name);
  printGLError();

  debugPrint("glGetProgramResourceLocationIndex(program= %u, programInterface= %s, name= %x)= %i\n", program, getEnumString(programInterface), name, result);

  return result;
}

void glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar* name)
{
  next_glGetProgramResourceName(program, programInterface, index, bufSize, length, name);
  printGLError();

  debugPrint("glGetProgramResourceName(program= %u, programInterface= %s, index= %u, bufSize= %u, length= %x, name= %s)\n", program, getEnumString(programInterface), index, bufSize, length, name);
}

void glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei* length, GLint* params)
{
  next_glGetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params);
  printGLError();

  debugPrint("glGetProgramResourceiv(program= %u, programInterface= %s, index= %u, propCount= %u, props= %x, bufSize= %u, length= %x, params= %x)\n", program, getEnumString(programInterface), index, propCount, props, bufSize, length, params);
}

void glInvalidateBufferData(GLuint buffer)
{
  next_glInvalidateBufferData(buffer);
  printGLError();

  debugPrint("glInvalidateBufferData(buffer= %u)\n", buffer);
}

void glInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length)
{
  next_glInvalidateBufferSubData(buffer, offset, length);
  printGLError();

  debugPrint("glInvalidateBufferSubData(buffer= %u, offset= %i, length= %u)\n", buffer, offset, length);
}

void glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum* attachments)
{
  next_glInvalidateFramebuffer(target, numAttachments, attachments);
  printGLError();

  debugPrint("glInvalidateFramebuffer(target= %s, numAttachments= %u, attachments= %x)\n", getEnumString(target), numAttachments, attachments);
}

void glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height)
{
  next_glInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
  printGLError();

  debugPrint("glInvalidateSubFramebuffer(target= %s, numAttachments= %u, attachments= %x, x= %i, y= %i, width= %u, height= %u)\n", getEnumString(target), numAttachments, attachments, x, y, width, height);
}

void glInvalidateTexImage(GLuint texture, GLint level)
{
  next_glInvalidateTexImage(texture, level);
  printGLError();

  debugPrint("glInvalidateTexImage(texture= %u, level= %i)\n", texture, level);
}

void glInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth)
{
  next_glInvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth);
  printGLError();

  debugPrint("glInvalidateTexSubImage(texture= %u, level= %i, xoffset= %i, yoffset= %i, zoffset= %i, width= %u, height= %u, depth= %u)\n", texture, level, xoffset, yoffset, zoffset, width, height, depth);
}

void glMultiDrawArraysIndirect(GLenum mode, const void * indirect, GLsizei drawcount, GLsizei stride)
{
  next_glMultiDrawArraysIndirect(mode, indirect, drawcount, stride);
  printGLError();

  debugPrint("glMultiDrawArraysIndirect(mode= %s, indirect= %x, drawcount= %u, stride= %u)\n", getEnumString(mode), indirect, drawcount, stride);
}

void glMultiDrawElementsIndirect(GLenum mode, GLenum type, const void * indirect, GLsizei drawcount, GLsizei stride)
{
  next_glMultiDrawElementsIndirect(mode, type, indirect, drawcount, stride);
  printGLError();

  debugPrint("glMultiDrawElementsIndirect(mode= %s, type= %s, indirect= %x, drawcount= %u, stride= %u)\n", getEnumString(mode), getEnumString(type), indirect, drawcount, stride);
}

void glObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar* label)
{
  next_glObjectLabel(identifier, name, length, label);
  printGLError();

  debugPrint("glObjectLabel(identifier= %s, name= %u, length= %u, label= %x)\n", getEnumString(identifier), name, length, label);
}

void glObjectPtrLabel(const void * ptr, GLsizei length, const GLchar* label)
{
  next_glObjectPtrLabel(ptr, length, label);
  printGLError();

  debugPrint("glObjectPtrLabel(ptr= %x, length= %u, label= %x)\n", ptr, length, label);
}

void glPopDebugGroup()
{
  next_glPopDebugGroup();
  printGLError();

  debugPrint("glPopDebugGroup()\n");
}

void glPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar* message)
{
  next_glPushDebugGroup(source, id, length, message);
  printGLError();

  debugPrint("glPushDebugGroup(source= %s, id= %u, length= %u, message= %x)\n", getEnumString(source), id, length, message);
}

void glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding)
{
  next_glShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding);
  printGLError();

  debugPrint("glShaderStorageBlockBinding(program= %u, storageBlockIndex= %u, storageBlockBinding= %u)\n", program, storageBlockIndex, storageBlockBinding);
}

void glTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
  next_glTexBufferRange(target, internalformat, buffer, offset, size);
  printGLError();

  debugPrint("glTexBufferRange(target= %s, internalformat= %s, buffer= %u, offset= %i, size= %u)\n", getEnumString(target), getEnumString(internalformat), buffer, offset, size);
}

void glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
  next_glTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
  printGLError();

  debugPrint("glTexStorage2DMultisample(target= %s, samples= %u, internalformat= %s, width= %u, height= %u, fixedsamplelocations= %i)\n", getEnumString(target), samples, getEnumString(internalformat), width, height, fixedsamplelocations);
}

void glTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
  next_glTexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
  printGLError();

  debugPrint("glTexStorage3DMultisample(target= %s, samples= %u, internalformat= %s, width= %u, height= %u, depth= %u, fixedsamplelocations= %i)\n", getEnumString(target), samples, getEnumString(internalformat), width, height, depth, fixedsamplelocations);
}

void glTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers)
{
  next_glTextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
  printGLError();

  debugPrint("glTextureView(texture= %u, target= %s, origtexture= %u, internalformat= %s, minlevel= %u, numlevels= %u, minlayer= %u, numlayers= %u)\n", texture, getEnumString(target), origtexture, getEnumString(internalformat), minlevel, numlevels, minlayer, numlayers);
}

void glVertexAttribBinding(GLuint attribindex, GLuint bindingindex)
{
  next_glVertexAttribBinding(attribindex, bindingindex);
  printGLError();

  debugPrint("glVertexAttribBinding(attribindex= %u, bindingindex= %u)\n", attribindex, bindingindex);
}

void glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
{
  next_glVertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
  printGLError();

  debugPrint("glVertexAttribFormat(attribindex= %u, size= %i, type= %s, normalized= %i, relativeoffset= %u)\n", attribindex, size, getEnumString(type), normalized, relativeoffset);
}

void glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
  next_glVertexAttribIFormat(attribindex, size, type, relativeoffset);
  printGLError();

  debugPrint("glVertexAttribIFormat(attribindex= %u, size= %i, type= %s, relativeoffset= %u)\n", attribindex, size, getEnumString(type), relativeoffset);
}

void glVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
  next_glVertexAttribLFormat(attribindex, size, type, relativeoffset);
  printGLError();

  debugPrint("glVertexAttribLFormat(attribindex= %u, size= %i, type= %s, relativeoffset= %u)\n", attribindex, size, getEnumString(type), relativeoffset);
}

void glVertexBindingDivisor(GLuint bindingindex, GLuint divisor)
{
  next_glVertexBindingDivisor(bindingindex, divisor);
  printGLError();

  debugPrint("glVertexBindingDivisor(bindingindex= %u, divisor= %u)\n", bindingindex, divisor);
}


// GL_VERSION_4_4

void glBindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint* buffers)
{
  next_glBindBuffersBase(target, first, count, buffers);
  printGLError();

  debugPrint("glBindBuffersBase(target= %s, first= %u, count= %u, buffers= %x)\n", getEnumString(target), first, count, buffers);
}

void glBindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizeiptr* sizes)
{
  next_glBindBuffersRange(target, first, count, buffers, offsets, sizes);
  printGLError();

  debugPrint("glBindBuffersRange(target= %s, first= %u, count= %u, buffers= %x, offsets= %x, sizes= %x)\n", getEnumString(target), first, count, buffers, offsets, sizes);
}

void glBindImageTextures(GLuint first, GLsizei count, const GLuint* textures)
{
  next_glBindImageTextures(first, count, textures);
  printGLError();

  debugPrint("glBindImageTextures(first= %u, count= %u, textures= %x)\n", first, count, textures);
}

void glBindSamplers(GLuint first, GLsizei count, const GLuint* samplers)
{
  next_glBindSamplers(first, count, samplers);
  printGLError();

  debugPrint("glBindSamplers(first= %u, count= %u, samplers= %x)\n", first, count, samplers);
}

void glBindTextures(GLuint first, GLsizei count, const GLuint* textures)
{
  next_glBindTextures(first, count, textures);
  printGLError();

  debugPrint("glBindTextures(first= %u, count= %u, textures= %x)\n", first, count, textures);
}

void glBindVertexBuffers(GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides)
{
  next_glBindVertexBuffers(first, count, buffers, offsets, strides);
  printGLError();

  debugPrint("glBindVertexBuffers(first= %u, count= %u, buffers= %x, offsets= %x, strides= %x)\n", first, count, buffers, offsets, strides);
}

void glBufferStorage(GLenum target, GLsizeiptr size, const void * data, GLbitfield flags)
{
  next_glBufferStorage(target, size, data, flags);
  printGLError();

  debugPrint("glBufferStorage(target= %s, size= %u, data= %x, flags= %x)\n", getEnumString(target), size, data, flags);
}

void glClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void * data)
{
  next_glClearTexImage(texture, level, format, type, data);
  printGLError();

  debugPrint("glClearTexImage(texture= %u, level= %i, format= %s, type= %s, data= %x)\n", texture, level, getEnumString(format), getEnumString(type), data);
}

void glClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * data)
{
  next_glClearTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
  printGLError();

  debugPrint("glClearTexSubImage(texture= %u, level= %i, xoffset= %i, yoffset= %i, zoffset= %i, width= %u, height= %u, depth= %u, format= %s, type= %s, data= %x)\n", texture, level, xoffset, yoffset, zoffset, width, height, depth, getEnumString(format), getEnumString(type), data);
}


// GL_VERSION_4_5

void glBindTextureUnit(GLuint unit, GLuint texture)
{
  next_glBindTextureUnit(unit, texture);
  printGLError();

  debugPrint("glBindTextureUnit(unit= %u, texture= %u)\n", unit, texture);
}

void glBlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
  next_glBlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
  printGLError();

  debugPrint("glBlitNamedFramebuffer(readFramebuffer= %u, drawFramebuffer= %u, srcX0= %i, srcY0= %i, srcX1= %i, srcY1= %i, dstX0= %i, dstY0= %i, dstX1= %i, dstY1= %i, mask= %x, filter= %s)\n", readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, getEnumString(filter));
}

GLenum glCheckNamedFramebufferStatus(GLuint framebuffer, GLenum target)
{
  GLenum result= next_glCheckNamedFramebufferStatus(framebuffer, target);
  printGLError();

  debugPrint("glCheckNamedFramebufferStatus(framebuffer= %u, target= %s)= %s\n", framebuffer, getEnumString(target), getEnumString(result));

  return result;
}

void glClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void * data)
{
  next_glClearNamedBufferData(buffer, internalformat, format, type, data);
  printGLError();

  debugPrint("glClearNamedBufferData(buffer= %u, internalformat= %s, format= %s, type= %s, data= %x)\n", buffer, getEnumString(internalformat), getEnumString(format), getEnumString(type), data);
}

void glClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data)
{
  next_glClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data);
  printGLError();

  debugPrint("glClearNamedBufferSubData(buffer= %u, internalformat= %s, offset= %i, size= %u, format= %s, type= %s, data= %x)\n", buffer, getEnumString(internalformat), offset, size, getEnumString(format), getEnumString(type), data);
}

void glClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
{
  next_glClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil);
  printGLError();

  debugPrint("glClearNamedFramebufferfi(framebuffer= %u, buffer= %s, drawbuffer= %i, depth= %f, stencil= %i)\n", framebuffer, getEnumString(buffer), drawbuffer, depth, stencil);
}

void glClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat* value)
{
  next_glClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value);
  printGLError();

  debugPrint("glClearNamedFramebufferfv(framebuffer= %u, buffer= %s, drawbuffer= %i, value= %x)\n", framebuffer, getEnumString(buffer), drawbuffer, value);
}

void glClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint* value)
{
  next_glClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value);
  printGLError();

  debugPrint("glClearNamedFramebufferiv(framebuffer= %u, buffer= %s, drawbuffer= %i, value= %x)\n", framebuffer, getEnumString(buffer), drawbuffer, value);
}

void glClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint* value)
{
  next_glClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value);
  printGLError();

  debugPrint("glClearNamedFramebufferuiv(framebuffer= %u, buffer= %s, drawbuffer= %i, value= %x)\n", framebuffer, getEnumString(buffer), drawbuffer, value);
}

void glClipControl(GLenum origin, GLenum depth)
{
  next_glClipControl(origin, depth);
  printGLError();

  debugPrint("glClipControl(origin= %s, depth= %s)\n", getEnumString(origin), getEnumString(depth));
}

void glCompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data)
{
  next_glCompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data);
  printGLError();

  debugPrint("glCompressedTextureSubImage1D(texture= %u, level= %i, xoffset= %i, width= %u, format= %s, imageSize= %u, data= %x)\n", texture, level, xoffset, width, getEnumString(format), imageSize, data);
}

void glCompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data)
{
  next_glCompressedTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, imageSize, data);
  printGLError();

  debugPrint("glCompressedTextureSubImage2D(texture= %u, level= %i, xoffset= %i, yoffset= %i, width= %u, height= %u, format= %s, imageSize= %u, data= %x)\n", texture, level, xoffset, yoffset, width, height, getEnumString(format), imageSize, data);
}

void glCompressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data)
{
  next_glCompressedTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
  printGLError();

  debugPrint("glCompressedTextureSubImage3D(texture= %u, level= %i, xoffset= %i, yoffset= %i, zoffset= %i, width= %u, height= %u, depth= %u, format= %s, imageSize= %u, data= %x)\n", texture, level, xoffset, yoffset, zoffset, width, height, depth, getEnumString(format), imageSize, data);
}

void glCopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
  next_glCopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size);
  printGLError();

  debugPrint("glCopyNamedBufferSubData(readBuffer= %u, writeBuffer= %u, readOffset= %i, writeOffset= %i, size= %u)\n", readBuffer, writeBuffer, readOffset, writeOffset, size);
}

void glCopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
  next_glCopyTextureSubImage1D(texture, level, xoffset, x, y, width);
  printGLError();

  debugPrint("glCopyTextureSubImage1D(texture= %u, level= %i, xoffset= %i, x= %i, y= %i, width= %u)\n", texture, level, xoffset, x, y, width);
}

void glCopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
  next_glCopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height);
  printGLError();

  debugPrint("glCopyTextureSubImage2D(texture= %u, level= %i, xoffset= %i, yoffset= %i, x= %i, y= %i, width= %u, height= %u)\n", texture, level, xoffset, yoffset, x, y, width, height);
}

void glCopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
  next_glCopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height);
  printGLError();

  debugPrint("glCopyTextureSubImage3D(texture= %u, level= %i, xoffset= %i, yoffset= %i, zoffset= %i, x= %i, y= %i, width= %u, height= %u)\n", texture, level, xoffset, yoffset, zoffset, x, y, width, height);
}

void glCreateBuffers(GLsizei n, GLuint* buffers)
{
  next_glCreateBuffers(n, buffers);
  printGLError();

  debugPrint("glCreateBuffers(n= %u, buffers= %x)\n", n, buffers);
}

void glCreateFramebuffers(GLsizei n, GLuint* framebuffers)
{
  next_glCreateFramebuffers(n, framebuffers);
  printGLError();

  debugPrint("glCreateFramebuffers(n= %u, framebuffers= %x)\n", n, framebuffers);
}

void glCreateProgramPipelines(GLsizei n, GLuint* pipelines)
{
  next_glCreateProgramPipelines(n, pipelines);
  printGLError();

  debugPrint("glCreateProgramPipelines(n= %u, pipelines= %x)\n", n, pipelines);
}

void glCreateQueries(GLenum target, GLsizei n, GLuint* ids)
{
  next_glCreateQueries(target, n, ids);
  printGLError();

  debugPrint("glCreateQueries(target= %s, n= %u, ids= %x)\n", getEnumString(target), n, ids);
}

void glCreateRenderbuffers(GLsizei n, GLuint* renderbuffers)
{
  next_glCreateRenderbuffers(n, renderbuffers);
  printGLError();

  debugPrint("glCreateRenderbuffers(n= %u, renderbuffers= %x)\n", n, renderbuffers);
}

void glCreateSamplers(GLsizei n, GLuint* samplers)
{
  next_glCreateSamplers(n, samplers);
  printGLError();

  debugPrint("glCreateSamplers(n= %u, samplers= %x)\n", n, samplers);
}

void glCreateTextures(GLenum target, GLsizei n, GLuint* textures)
{
  next_glCreateTextures(target, n, textures);
  printGLError();

  debugPrint("glCreateTextures(target= %s, n= %u, textures= %x)\n", getEnumString(target), n, textures);
}

void glCreateTransformFeedbacks(GLsizei n, GLuint* ids)
{
  next_glCreateTransformFeedbacks(n, ids);
  printGLError();

  debugPrint("glCreateTransformFeedbacks(n= %u, ids= %x)\n", n, ids);
}

void glCreateVertexArrays(GLsizei n, GLuint* arrays)
{
  next_glCreateVertexArrays(n, arrays);
  printGLError();

  debugPrint("glCreateVertexArrays(n= %u, arrays= %x)\n", n, arrays);
}

void glDisableVertexArrayAttrib(GLuint vaobj, GLuint index)
{
  next_glDisableVertexArrayAttrib(vaobj, index);
  printGLError();

  debugPrint("glDisableVertexArrayAttrib(vaobj= %u, index= %u)\n", vaobj, index);
}

void glEnableVertexArrayAttrib(GLuint vaobj, GLuint index)
{
  next_glEnableVertexArrayAttrib(vaobj, index);
  printGLError();

  debugPrint("glEnableVertexArrayAttrib(vaobj= %u, index= %u)\n", vaobj, index);
}

void glFlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length)
{
  next_glFlushMappedNamedBufferRange(buffer, offset, length);
  printGLError();

  debugPrint("glFlushMappedNamedBufferRange(buffer= %u, offset= %i, length= %u)\n", buffer, offset, length);
}

void glGenerateTextureMipmap(GLuint texture)
{
  next_glGenerateTextureMipmap(texture);
  printGLError();

  debugPrint("glGenerateTextureMipmap(texture= %u)\n", texture);
}

void glGetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void * pixels)
{
  next_glGetCompressedTextureImage(texture, level, bufSize, pixels);
  printGLError();

  debugPrint("glGetCompressedTextureImage(texture= %u, level= %i, bufSize= %u, pixels= %x)\n", texture, level, bufSize, pixels);
}

void glGetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void * pixels)
{
  next_glGetCompressedTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);
  printGLError();

  debugPrint("glGetCompressedTextureSubImage(texture= %u, level= %i, xoffset= %i, yoffset= %i, zoffset= %i, width= %u, height= %u, depth= %u, bufSize= %u, pixels= %x)\n", texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);
}

GLenum glGetGraphicsResetStatus()
{
  GLenum result= next_glGetGraphicsResetStatus();
  printGLError();

  debugPrint("glGetGraphicsResetStatus()= %s\n", getEnumString(result));

  return result;
}

void glGetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64* params)
{
  next_glGetNamedBufferParameteri64v(buffer, pname, params);
  printGLError();

  debugPrint("glGetNamedBufferParameteri64v(buffer= %u, pname= %s, params= %x)\n", buffer, getEnumString(pname), params);
}

void glGetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint* params)
{
  next_glGetNamedBufferParameteriv(buffer, pname, params);
  printGLError();

  debugPrint("glGetNamedBufferParameteriv(buffer= %u, pname= %s, params= %x)\n", buffer, getEnumString(pname), params);
}

void glGetNamedBufferPointerv(GLuint buffer, GLenum pname, void ** params)
{
  next_glGetNamedBufferPointerv(buffer, pname, params);
  printGLError();

  debugPrint("glGetNamedBufferPointerv(buffer= %u, pname= %s, params= %x)\n", buffer, getEnumString(pname), params);
}

void glGetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, void * data)
{
  next_glGetNamedBufferSubData(buffer, offset, size, data);
  printGLError();

  debugPrint("glGetNamedBufferSubData(buffer= %u, offset= %i, size= %u, data= %x)\n", buffer, offset, size, data);
}

void glGetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params)
{
  next_glGetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params);
  printGLError();

  debugPrint("glGetNamedFramebufferAttachmentParameteriv(framebuffer= %u, attachment= %s, pname= %s, params= %x)\n", framebuffer, getEnumString(attachment), getEnumString(pname), params);
}

void glGetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint* param)
{
  next_glGetNamedFramebufferParameteriv(framebuffer, pname, param);
  printGLError();

  debugPrint("glGetNamedFramebufferParameteriv(framebuffer= %u, pname= %s, param= %x)\n", framebuffer, getEnumString(pname), param);
}

void glGetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint* params)
{
  next_glGetNamedRenderbufferParameteriv(renderbuffer, pname, params);
  printGLError();

  debugPrint("glGetNamedRenderbufferParameteriv(renderbuffer= %u, pname= %s, params= %x)\n", renderbuffer, getEnumString(pname), params);
}

void glGetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
{
  next_glGetQueryBufferObjecti64v(id, buffer, pname, offset);
  printGLError();

  debugPrint("glGetQueryBufferObjecti64v(id= %u, buffer= %u, pname= %s, offset= %i)\n", id, buffer, getEnumString(pname), offset);
}

void glGetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
{
  next_glGetQueryBufferObjectiv(id, buffer, pname, offset);
  printGLError();

  debugPrint("glGetQueryBufferObjectiv(id= %u, buffer= %u, pname= %s, offset= %i)\n", id, buffer, getEnumString(pname), offset);
}

void glGetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
{
  next_glGetQueryBufferObjectui64v(id, buffer, pname, offset);
  printGLError();

  debugPrint("glGetQueryBufferObjectui64v(id= %u, buffer= %u, pname= %s, offset= %i)\n", id, buffer, getEnumString(pname), offset);
}

void glGetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
{
  next_glGetQueryBufferObjectuiv(id, buffer, pname, offset);
  printGLError();

  debugPrint("glGetQueryBufferObjectuiv(id= %u, buffer= %u, pname= %s, offset= %i)\n", id, buffer, getEnumString(pname), offset);
}

void glGetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels)
{
  next_glGetTextureImage(texture, level, format, type, bufSize, pixels);
  printGLError();

  debugPrint("glGetTextureImage(texture= %u, level= %i, format= %s, type= %s, bufSize= %u, pixels= %x)\n", texture, level, getEnumString(format), getEnumString(type), bufSize, pixels);
}

void glGetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat* params)
{
  next_glGetTextureLevelParameterfv(texture, level, pname, params);
  printGLError();

  debugPrint("glGetTextureLevelParameterfv(texture= %u, level= %i, pname= %s, params= %x)\n", texture, level, getEnumString(pname), params);
}

void glGetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint* params)
{
  next_glGetTextureLevelParameteriv(texture, level, pname, params);
  printGLError();

  debugPrint("glGetTextureLevelParameteriv(texture= %u, level= %i, pname= %s, params= %x)\n", texture, level, getEnumString(pname), params);
}

void glGetTextureParameterIiv(GLuint texture, GLenum pname, GLint* params)
{
  next_glGetTextureParameterIiv(texture, pname, params);
  printGLError();

  debugPrint("glGetTextureParameterIiv(texture= %u, pname= %s, params= %x)\n", texture, getEnumString(pname), params);
}

void glGetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint* params)
{
  next_glGetTextureParameterIuiv(texture, pname, params);
  printGLError();

  debugPrint("glGetTextureParameterIuiv(texture= %u, pname= %s, params= %x)\n", texture, getEnumString(pname), params);
}

void glGetTextureParameterfv(GLuint texture, GLenum pname, GLfloat* params)
{
  next_glGetTextureParameterfv(texture, pname, params);
  printGLError();

  debugPrint("glGetTextureParameterfv(texture= %u, pname= %s, params= %x)\n", texture, getEnumString(pname), params);
}

void glGetTextureParameteriv(GLuint texture, GLenum pname, GLint* params)
{
  next_glGetTextureParameteriv(texture, pname, params);
  printGLError();

  debugPrint("glGetTextureParameteriv(texture= %u, pname= %s, params= %x)\n", texture, getEnumString(pname), params);
}

void glGetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void * pixels)
{
  next_glGetTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels);
  printGLError();

  debugPrint("glGetTextureSubImage(texture= %u, level= %i, xoffset= %i, yoffset= %i, zoffset= %i, width= %u, height= %u, depth= %u, format= %s, type= %s, bufSize= %u, pixels= %x)\n", texture, level, xoffset, yoffset, zoffset, width, height, depth, getEnumString(format), getEnumString(type), bufSize, pixels);
}

void glGetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64* param)
{
  next_glGetTransformFeedbacki64_v(xfb, pname, index, param);
  printGLError();

  debugPrint("glGetTransformFeedbacki64_v(xfb= %u, pname= %s, index= %u, param= %x)\n", xfb, getEnumString(pname), index, param);
}

void glGetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint* param)
{
  next_glGetTransformFeedbacki_v(xfb, pname, index, param);
  printGLError();

  debugPrint("glGetTransformFeedbacki_v(xfb= %u, pname= %s, index= %u, param= %x)\n", xfb, getEnumString(pname), index, param);
}

void glGetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint* param)
{
  next_glGetTransformFeedbackiv(xfb, pname, param);
  printGLError();

  debugPrint("glGetTransformFeedbackiv(xfb= %u, pname= %s, param= %x)\n", xfb, getEnumString(pname), param);
}

void glGetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64* param)
{
  next_glGetVertexArrayIndexed64iv(vaobj, index, pname, param);
  printGLError();

  debugPrint("glGetVertexArrayIndexed64iv(vaobj= %u, index= %u, pname= %s, param= %x)\n", vaobj, index, getEnumString(pname), param);
}

void glGetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint* param)
{
  next_glGetVertexArrayIndexediv(vaobj, index, pname, param);
  printGLError();

  debugPrint("glGetVertexArrayIndexediv(vaobj= %u, index= %u, pname= %s, param= %x)\n", vaobj, index, getEnumString(pname), param);
}

void glGetVertexArrayiv(GLuint vaobj, GLenum pname, GLint* param)
{
  next_glGetVertexArrayiv(vaobj, pname, param);
  printGLError();

  debugPrint("glGetVertexArrayiv(vaobj= %u, pname= %s, param= %x)\n", vaobj, getEnumString(pname), param);
}

void glGetnColorTable(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void * table)
{
  next_glGetnColorTable(target, format, type, bufSize, table);
  printGLError();

  debugPrint("glGetnColorTable(target= %s, format= %s, type= %s, bufSize= %u, table= %x)\n", getEnumString(target), getEnumString(format), getEnumString(type), bufSize, table);
}

void glGetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, void * pixels)
{
  next_glGetnCompressedTexImage(target, lod, bufSize, pixels);
  printGLError();

  debugPrint("glGetnCompressedTexImage(target= %s, lod= %i, bufSize= %u, pixels= %x)\n", getEnumString(target), lod, bufSize, pixels);
}

void glGetnConvolutionFilter(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void * image)
{
  next_glGetnConvolutionFilter(target, format, type, bufSize, image);
  printGLError();

  debugPrint("glGetnConvolutionFilter(target= %s, format= %s, type= %s, bufSize= %u, image= %x)\n", getEnumString(target), getEnumString(format), getEnumString(type), bufSize, image);
}

void glGetnHistogram(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void * values)
{
  next_glGetnHistogram(target, reset, format, type, bufSize, values);
  printGLError();

  debugPrint("glGetnHistogram(target= %s, reset= %i, format= %s, type= %s, bufSize= %u, values= %x)\n", getEnumString(target), reset, getEnumString(format), getEnumString(type), bufSize, values);
}

void glGetnMapdv(GLenum target, GLenum query, GLsizei bufSize, GLdouble* v)
{
  next_glGetnMapdv(target, query, bufSize, v);
  printGLError();

  debugPrint("glGetnMapdv(target= %s, query= %s, bufSize= %u, v= %x)\n", getEnumString(target), getEnumString(query), bufSize, v);
}

void glGetnMapfv(GLenum target, GLenum query, GLsizei bufSize, GLfloat* v)
{
  next_glGetnMapfv(target, query, bufSize, v);
  printGLError();

  debugPrint("glGetnMapfv(target= %s, query= %s, bufSize= %u, v= %x)\n", getEnumString(target), getEnumString(query), bufSize, v);
}

void glGetnMapiv(GLenum target, GLenum query, GLsizei bufSize, GLint* v)
{
  next_glGetnMapiv(target, query, bufSize, v);
  printGLError();

  debugPrint("glGetnMapiv(target= %s, query= %s, bufSize= %u, v= %x)\n", getEnumString(target), getEnumString(query), bufSize, v);
}

void glGetnMinmax(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void * values)
{
  next_glGetnMinmax(target, reset, format, type, bufSize, values);
  printGLError();

  debugPrint("glGetnMinmax(target= %s, reset= %i, format= %s, type= %s, bufSize= %u, values= %x)\n", getEnumString(target), reset, getEnumString(format), getEnumString(type), bufSize, values);
}

void glGetnPixelMapfv(GLenum map, GLsizei bufSize, GLfloat* values)
{
  next_glGetnPixelMapfv(map, bufSize, values);
  printGLError();

  debugPrint("glGetnPixelMapfv(map= %s, bufSize= %u, values= %x)\n", getEnumString(map), bufSize, values);
}

void glGetnPixelMapuiv(GLenum map, GLsizei bufSize, GLuint* values)
{
  next_glGetnPixelMapuiv(map, bufSize, values);
  printGLError();

  debugPrint("glGetnPixelMapuiv(map= %s, bufSize= %u, values= %x)\n", getEnumString(map), bufSize, values);
}

void glGetnPixelMapusv(GLenum map, GLsizei bufSize, GLushort* values)
{
  next_glGetnPixelMapusv(map, bufSize, values);
  printGLError();

  debugPrint("glGetnPixelMapusv(map= %s, bufSize= %u, values= %x)\n", getEnumString(map), bufSize, values);
}

void glGetnPolygonStipple(GLsizei bufSize, GLubyte* pattern)
{
  next_glGetnPolygonStipple(bufSize, pattern);
  printGLError();

  debugPrint("glGetnPolygonStipple(bufSize= %u, pattern= %x)\n", bufSize, pattern);
}

void glGetnSeparableFilter(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void * row, GLsizei columnBufSize, void * column, void * span)
{
  next_glGetnSeparableFilter(target, format, type, rowBufSize, row, columnBufSize, column, span);
  printGLError();

  debugPrint("glGetnSeparableFilter(target= %s, format= %s, type= %s, rowBufSize= %u, row= %x, columnBufSize= %u, column= %x, span= %x)\n", getEnumString(target), getEnumString(format), getEnumString(type), rowBufSize, row, columnBufSize, column, span);
}

void glGetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels)
{
  next_glGetnTexImage(target, level, format, type, bufSize, pixels);
  printGLError();

  debugPrint("glGetnTexImage(target= %s, level= %i, format= %s, type= %s, bufSize= %u, pixels= %x)\n", getEnumString(target), level, getEnumString(format), getEnumString(type), bufSize, pixels);
}

void glGetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble* params)
{
  next_glGetnUniformdv(program, location, bufSize, params);
  printGLError();

  debugPrint("glGetnUniformdv(program= %u, location= %i, bufSize= %u, params= %x)\n", program, location, bufSize, params);
}

void glGetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat* params)
{
  next_glGetnUniformfv(program, location, bufSize, params);
  printGLError();

  debugPrint("glGetnUniformfv(program= %u, location= %i, bufSize= %u, params= %x)\n", program, location, bufSize, params);
}

void glGetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint* params)
{
  next_glGetnUniformiv(program, location, bufSize, params);
  printGLError();

  debugPrint("glGetnUniformiv(program= %u, location= %i, bufSize= %u, params= %x)\n", program, location, bufSize, params);
}

void glGetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint* params)
{
  next_glGetnUniformuiv(program, location, bufSize, params);
  printGLError();

  debugPrint("glGetnUniformuiv(program= %u, location= %i, bufSize= %u, params= %x)\n", program, location, bufSize, params);
}

void glInvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments)
{
  next_glInvalidateNamedFramebufferData(framebuffer, numAttachments, attachments);
  printGLError();

  debugPrint("glInvalidateNamedFramebufferData(framebuffer= %u, numAttachments= %u, attachments= %x)\n", framebuffer, numAttachments, attachments);
}

void glInvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height)
{
  next_glInvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height);
  printGLError();

  debugPrint("glInvalidateNamedFramebufferSubData(framebuffer= %u, numAttachments= %u, attachments= %x, x= %i, y= %i, width= %u, height= %u)\n", framebuffer, numAttachments, attachments, x, y, width, height);
}

void * glMapNamedBuffer(GLuint buffer, GLenum access)
{
  void * result= next_glMapNamedBuffer(buffer, access);
  printGLError();

  debugPrint("glMapNamedBuffer(buffer= %u, access= %s)= %x\n", buffer, getEnumString(access), result);

  return result;
}

void * glMapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
  void * result= next_glMapNamedBufferRange(buffer, offset, length, access);
  printGLError();

  debugPrint("glMapNamedBufferRange(buffer= %u, offset= %i, length= %u, access= %x)= %x\n", buffer, offset, length, access, result);

  return result;
}

void glMemoryBarrierByRegion(GLbitfield barriers)
{
  next_glMemoryBarrierByRegion(barriers);
  printGLError();

  debugPrint("glMemoryBarrierByRegion(barriers= %x)\n", barriers);
}

void glNamedBufferData(GLuint buffer, GLsizeiptr size, const void * data, GLenum usage)
{
  next_glNamedBufferData(buffer, size, data, usage);
  printGLError();

  debugPrint("glNamedBufferData(buffer= %u, size= %u, data= %x, usage= %s)\n", buffer, size, data, getEnumString(usage));
}

void glNamedBufferStorage(GLuint buffer, GLsizeiptr size, const void * data, GLbitfield flags)
{
  next_glNamedBufferStorage(buffer, size, data, flags);
  printGLError();

  debugPrint("glNamedBufferStorage(buffer= %u, size= %u, data= %x, flags= %x)\n", buffer, size, data, flags);
}

void glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void * data)
{
  next_glNamedBufferSubData(buffer, offset, size, data);
  printGLError();

  debugPrint("glNamedBufferSubData(buffer= %u, offset= %i, size= %u, data= %x)\n", buffer, offset, size, data);
}

void glNamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf)
{
  next_glNamedFramebufferDrawBuffer(framebuffer, buf);
  printGLError();

  debugPrint("glNamedFramebufferDrawBuffer(framebuffer= %u, buf= %s)\n", framebuffer, getEnumString(buf));
}

void glNamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum* bufs)
{
  next_glNamedFramebufferDrawBuffers(framebuffer, n, bufs);
  printGLError();

  debugPrint("glNamedFramebufferDrawBuffers(framebuffer= %u, n= %u, bufs= %x)\n", framebuffer, n, bufs);
}

void glNamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param)
{
  next_glNamedFramebufferParameteri(framebuffer, pname, param);
  printGLError();

  debugPrint("glNamedFramebufferParameteri(framebuffer= %u, pname= %s, param= %i)\n", framebuffer, getEnumString(pname), param);
}

void glNamedFramebufferReadBuffer(GLuint framebuffer, GLenum src)
{
  next_glNamedFramebufferReadBuffer(framebuffer, src);
  printGLError();

  debugPrint("glNamedFramebufferReadBuffer(framebuffer= %u, src= %s)\n", framebuffer, getEnumString(src));
}

void glNamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
  next_glNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer);
  printGLError();

  debugPrint("glNamedFramebufferRenderbuffer(framebuffer= %u, attachment= %s, renderbuffertarget= %s, renderbuffer= %u)\n", framebuffer, getEnumString(attachment), getEnumString(renderbuffertarget), renderbuffer);
}

void glNamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level)
{
  next_glNamedFramebufferTexture(framebuffer, attachment, texture, level);
  printGLError();

  debugPrint("glNamedFramebufferTexture(framebuffer= %u, attachment= %s, texture= %u, level= %i)\n", framebuffer, getEnumString(attachment), texture, level);
}

void glNamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
  next_glNamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer);
  printGLError();

  debugPrint("glNamedFramebufferTextureLayer(framebuffer= %u, attachment= %s, texture= %u, level= %i, layer= %i)\n", framebuffer, getEnumString(attachment), texture, level, layer);
}

void glNamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height)
{
  next_glNamedRenderbufferStorage(renderbuffer, internalformat, width, height);
  printGLError();

  debugPrint("glNamedRenderbufferStorage(renderbuffer= %u, internalformat= %s, width= %u, height= %u)\n", renderbuffer, getEnumString(internalformat), width, height);
}

void glNamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
  next_glNamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height);
  printGLError();

  debugPrint("glNamedRenderbufferStorageMultisample(renderbuffer= %u, samples= %u, internalformat= %s, width= %u, height= %u)\n", renderbuffer, samples, getEnumString(internalformat), width, height);
}

void glReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void * data)
{
  next_glReadnPixels(x, y, width, height, format, type, bufSize, data);
  printGLError();

  debugPrint("glReadnPixels(x= %i, y= %i, width= %u, height= %u, format= %s, type= %s, bufSize= %u, data= %x)\n", x, y, width, height, getEnumString(format), getEnumString(type), bufSize, data);
}

void glTextureBarrier()
{
  next_glTextureBarrier();
  printGLError();

  debugPrint("glTextureBarrier()\n");
}

void glTextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer)
{
  next_glTextureBuffer(texture, internalformat, buffer);
  printGLError();

  debugPrint("glTextureBuffer(texture= %u, internalformat= %s, buffer= %u)\n", texture, getEnumString(internalformat), buffer);
}

void glTextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
  next_glTextureBufferRange(texture, internalformat, buffer, offset, size);
  printGLError();

  debugPrint("glTextureBufferRange(texture= %u, internalformat= %s, buffer= %u, offset= %i, size= %u)\n", texture, getEnumString(internalformat), buffer, offset, size);
}

void glTextureParameterIiv(GLuint texture, GLenum pname, const GLint* params)
{
  next_glTextureParameterIiv(texture, pname, params);
  printGLError();

  debugPrint("glTextureParameterIiv(texture= %u, pname= %s, params= %x)\n", texture, getEnumString(pname), params);
}

void glTextureParameterIuiv(GLuint texture, GLenum pname, const GLuint* params)
{
  next_glTextureParameterIuiv(texture, pname, params);
  printGLError();

  debugPrint("glTextureParameterIuiv(texture= %u, pname= %s, params= %x)\n", texture, getEnumString(pname), params);
}

void glTextureParameterf(GLuint texture, GLenum pname, GLfloat param)
{
  next_glTextureParameterf(texture, pname, param);
  printGLError();

  debugPrint("glTextureParameterf(texture= %u, pname= %s, param= %f)\n", texture, getEnumString(pname), param);
}

void glTextureParameterfv(GLuint texture, GLenum pname, const GLfloat* param)
{
  next_glTextureParameterfv(texture, pname, param);
  printGLError();

  debugPrint("glTextureParameterfv(texture= %u, pname= %s, param= %x)\n", texture, getEnumString(pname), param);
}

void glTextureParameteri(GLuint texture, GLenum pname, GLint param)
{
  next_glTextureParameteri(texture, pname, param);
  printGLError();

  debugPrint("glTextureParameteri(texture= %u, pname= %s, param= %i)\n", texture, getEnumString(pname), param);
}

void glTextureParameteriv(GLuint texture, GLenum pname, const GLint* param)
{
  next_glTextureParameteriv(texture, pname, param);
  printGLError();

  debugPrint("glTextureParameteriv(texture= %u, pname= %s, param= %x)\n", texture, getEnumString(pname), param);
}

void glTextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width)
{
  next_glTextureStorage1D(texture, levels, internalformat, width);
  printGLError();

  debugPrint("glTextureStorage1D(texture= %u, levels= %u, internalformat= %s, width= %u)\n", texture, levels, getEnumString(internalformat), width);
}

void glTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
  next_glTextureStorage2D(texture, levels, internalformat, width, height);
  printGLError();

  debugPrint("glTextureStorage2D(texture= %u, levels= %u, internalformat= %s, width= %u, height= %u)\n", texture, levels, getEnumString(internalformat), width, height);
}

void glTextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
  next_glTextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations);
  printGLError();

  debugPrint("glTextureStorage2DMultisample(texture= %u, samples= %u, internalformat= %s, width= %u, height= %u, fixedsamplelocations= %i)\n", texture, samples, getEnumString(internalformat), width, height, fixedsamplelocations);
}

void glTextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
  next_glTextureStorage3D(texture, levels, internalformat, width, height, depth);
  printGLError();

  debugPrint("glTextureStorage3D(texture= %u, levels= %u, internalformat= %s, width= %u, height= %u, depth= %u)\n", texture, levels, getEnumString(internalformat), width, height, depth);
}

void glTextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
  next_glTextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations);
  printGLError();

  debugPrint("glTextureStorage3DMultisample(texture= %u, samples= %u, internalformat= %s, width= %u, height= %u, depth= %u, fixedsamplelocations= %i)\n", texture, samples, getEnumString(internalformat), width, height, depth, fixedsamplelocations);
}

void glTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels)
{
  next_glTextureSubImage1D(texture, level, xoffset, width, format, type, pixels);
  printGLError();

  debugPrint("glTextureSubImage1D(texture= %u, level= %i, xoffset= %i, width= %u, format= %s, type= %s, pixels= %x)\n", texture, level, xoffset, width, getEnumString(format), getEnumString(type), pixels);
}

void glTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels)
{
  next_glTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);
  printGLError();

  debugPrint("glTextureSubImage2D(texture= %u, level= %i, xoffset= %i, yoffset= %i, width= %u, height= %u, format= %s, type= %s, pixels= %x)\n", texture, level, xoffset, yoffset, width, height, getEnumString(format), getEnumString(type), pixels);
}

void glTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels)
{
  next_glTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
  printGLError();

  debugPrint("glTextureSubImage3D(texture= %u, level= %i, xoffset= %i, yoffset= %i, zoffset= %i, width= %u, height= %u, depth= %u, format= %s, type= %s, pixels= %x)\n", texture, level, xoffset, yoffset, zoffset, width, height, depth, getEnumString(format), getEnumString(type), pixels);
}

void glTransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer)
{
  next_glTransformFeedbackBufferBase(xfb, index, buffer);
  printGLError();

  debugPrint("glTransformFeedbackBufferBase(xfb= %u, index= %u, buffer= %u)\n", xfb, index, buffer);
}

void glTransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
  next_glTransformFeedbackBufferRange(xfb, index, buffer, offset, size);
  printGLError();

  debugPrint("glTransformFeedbackBufferRange(xfb= %u, index= %u, buffer= %u, offset= %i, size= %u)\n", xfb, index, buffer, offset, size);
}

GLboolean glUnmapNamedBuffer(GLuint buffer)
{
  GLboolean result= next_glUnmapNamedBuffer(buffer);
  printGLError();

  debugPrint("glUnmapNamedBuffer(buffer= %u)= %i\n", buffer, result);

  return result;
}

void glVertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex)
{
  next_glVertexArrayAttribBinding(vaobj, attribindex, bindingindex);
  printGLError();

  debugPrint("glVertexArrayAttribBinding(vaobj= %u, attribindex= %u, bindingindex= %u)\n", vaobj, attribindex, bindingindex);
}

void glVertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
{
  next_glVertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset);
  printGLError();

  debugPrint("glVertexArrayAttribFormat(vaobj= %u, attribindex= %u, size= %i, type= %s, normalized= %i, relativeoffset= %u)\n", vaobj, attribindex, size, getEnumString(type), normalized, relativeoffset);
}

void glVertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
  next_glVertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset);
  printGLError();

  debugPrint("glVertexArrayAttribIFormat(vaobj= %u, attribindex= %u, size= %i, type= %s, relativeoffset= %u)\n", vaobj, attribindex, size, getEnumString(type), relativeoffset);
}

void glVertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
  next_glVertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset);
  printGLError();

  debugPrint("glVertexArrayAttribLFormat(vaobj= %u, attribindex= %u, size= %i, type= %s, relativeoffset= %u)\n", vaobj, attribindex, size, getEnumString(type), relativeoffset);
}

void glVertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor)
{
  next_glVertexArrayBindingDivisor(vaobj, bindingindex, divisor);
  printGLError();

  debugPrint("glVertexArrayBindingDivisor(vaobj= %u, bindingindex= %u, divisor= %u)\n", vaobj, bindingindex, divisor);
}

void glVertexArrayElementBuffer(GLuint vaobj, GLuint buffer)
{
  next_glVertexArrayElementBuffer(vaobj, buffer);
  printGLError();

  debugPrint("glVertexArrayElementBuffer(vaobj= %u, buffer= %u)\n", vaobj, buffer);
}

void glVertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
{
  next_glVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride);
  printGLError();

  debugPrint("glVertexArrayVertexBuffer(vaobj= %u, bindingindex= %u, buffer= %u, offset= %i, stride= %u)\n", vaobj, bindingindex, buffer, offset, stride);
}

void glVertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides)
{
  next_glVertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides);
  printGLError();

  debugPrint("glVertexArrayVertexBuffers(vaobj= %u, first= %u, count= %u, buffers= %x, offsets= %x, strides= %x)\n", vaobj, first, count, buffers, offsets, strides);
}


