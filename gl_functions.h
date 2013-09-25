
#ifndef GL_FUNCTIONS_H
#define GL_FUNCTIONS_H

//#include "spyglass.h"
//#include "gl_functions.h"

#include <GL/gl.h>
#include <GL/glx.h>

static void (*next_glAccum)(GLenum op, GLfloat value) = NULL;

static void (*next_glActiveTexture)(GLenum texture) = NULL;

static void (*next_glActiveTextureARB)(GLenum texture) = NULL;

static void (*next_glAlphaFragmentOp1ATI)(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod) = NULL;

static void (*next_glAlphaFragmentOp2ATI)(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod) = NULL;

static void (*next_glAlphaFragmentOp3ATI)(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod) = NULL;

static void (*next_glAlphaFunc)(GLenum func, GLclampf ref) = NULL;

static void (*next_glApplyTextureEXT)(GLenum mode) = NULL;

static GLboolean (*next_glAreProgramsResidentNV)(GLsizei n, const GLuint * ids, GLboolean * residences) = NULL;

static GLboolean (*next_glAreTexturesResident)(GLsizei n, const GLuint * textures, GLboolean * residences) = NULL;

static GLboolean (*next_glAreTexturesResidentEXT)(GLsizei n, const GLuint * textures, GLboolean * residences) = NULL;

static void (*next_glArrayElement)(GLint i) = NULL;

static void (*next_glArrayElementEXT)(GLint i) = NULL;

static void (*next_glArrayObjectATI)(GLenum array, GLint size, GLenum type, GLsizei stride, GLuint buffer, GLuint offset) = NULL;

static void (*next_glAsyncMarkerSGIX)(GLuint marker) = NULL;

static void (*next_glBegin)(GLenum mode) = NULL;

static void (*next_glBeginFragmentShaderATI)() = NULL;

static void (*next_glBeginVertexShaderEXT)() = NULL;

static void (*next_glBindFragmentShaderATI)(GLuint id) = NULL;

static GLuint (*next_glBindLightParameterEXT)(GLenum light, GLenum value) = NULL;

static GLuint (*next_glBindMaterialParameterEXT)(GLenum face, GLenum value) = NULL;

static GLuint (*next_glBindParameterEXT)(GLenum value) = NULL;

static void (*next_glBindProgramNV)(GLenum target, GLuint id) = NULL;

static GLuint (*next_glBindTexGenParameterEXT)(GLenum unit, GLenum coord, GLenum value) = NULL;

static void (*next_glBindTexture)(GLenum target, GLuint texture) = NULL;

static void (*next_glBindTextureEXT)(GLenum target, GLuint texture) = NULL;

static GLuint (*next_glBindTextureUnitParameterEXT)(GLenum unit, GLenum value) = NULL;

static void (*next_glBindVertexShaderEXT)(GLuint id) = NULL;

static void (*next_glBinormal3bEXT)(GLbyte bx, GLbyte by, GLbyte bz) = NULL;

static void (*next_glBinormal3bvEXT)(const GLbyte * v) = NULL;

static void (*next_glBinormal3dEXT)(GLdouble bx, GLdouble by, GLdouble bz) = NULL;

static void (*next_glBinormal3dvEXT)(const GLdouble * v) = NULL;

static void (*next_glBinormal3fEXT)(GLfloat bx, GLfloat by, GLfloat bz) = NULL;

static void (*next_glBinormal3fvEXT)(const GLfloat * v) = NULL;

static void (*next_glBinormal3iEXT)(GLint bx, GLint by, GLint bz) = NULL;

static void (*next_glBinormal3ivEXT)(const GLint * v) = NULL;

static void (*next_glBinormal3sEXT)(GLshort bx, GLshort by, GLshort bz) = NULL;

static void (*next_glBinormal3svEXT)(const GLshort * v) = NULL;

static void (*next_glBinormalPointerEXT)(GLenum type, GLsizei stride, const GLvoid * pointer) = NULL;

static void (*next_glBitmap)(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap) = NULL;

static void (*next_glBlendColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) = NULL;

static void (*next_glBlendColorEXT)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) = NULL;

static void (*next_glBlendEquation)(GLenum mode) = NULL;

static void (*next_glBlendEquationEXT)(GLenum mode) = NULL;

static void (*next_glBlendFunc)(GLenum sfactor, GLenum dfactor) = NULL;

static void (*next_glBlendFuncSeparateEXT)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) = NULL;

static void (*next_glBlendFuncSeparateINGR)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) = NULL;

static void (*next_glCallList)(GLuint list) = NULL;

static void (*next_glCallLists)(GLsizei n, GLenum type, const GLvoid * lists) = NULL;

static void (*next_glClear)(GLbitfield mask) = NULL;

static void (*next_glClearAccum)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) = NULL;

static void (*next_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) = NULL;

static void (*next_glClearDepth)(GLclampd depth) = NULL;

static void (*next_glClearIndex)(GLfloat c) = NULL;

static void (*next_glClearStencil)(GLint s) = NULL;

static void (*next_glClientActiveTexture)(GLenum texture) = NULL;

static void (*next_glClientActiveTextureARB)(GLenum texture) = NULL;

static void (*next_glClientActiveVertexStreamATI)(GLenum stream) = NULL;

static void (*next_glClipPlane)(GLenum plane, const GLdouble * equation) = NULL;

static void (*next_glColor3b)(GLbyte red, GLbyte green, GLbyte blue) = NULL;

static void (*next_glColor3bv)(const GLbyte * v) = NULL;

static void (*next_glColor3d)(GLdouble red, GLdouble green, GLdouble blue) = NULL;

static void (*next_glColor3dv)(const GLdouble * v) = NULL;

static void (*next_glColor3f)(GLfloat red, GLfloat green, GLfloat blue) = NULL;

static void (*next_glColor3fVertex3fSUN)(GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glColor3fVertex3fvSUN)(const GLfloat * c, const GLfloat * v) = NULL;

static void (*next_glColor3fv)(const GLfloat * v) = NULL;

static void (*next_glColor3i)(GLint red, GLint green, GLint blue) = NULL;

static void (*next_glColor3iv)(const GLint * v) = NULL;

static void (*next_glColor3s)(GLshort red, GLshort green, GLshort blue) = NULL;

static void (*next_glColor3sv)(const GLshort * v) = NULL;

static void (*next_glColor3ub)(GLubyte red, GLubyte green, GLubyte blue) = NULL;

static void (*next_glColor3ubv)(const GLubyte * v) = NULL;

static void (*next_glColor3ui)(GLuint red, GLuint green, GLuint blue) = NULL;

static void (*next_glColor3uiv)(const GLuint * v) = NULL;

static void (*next_glColor3us)(GLushort red, GLushort green, GLushort blue) = NULL;

static void (*next_glColor3usv)(const GLushort * v) = NULL;

static void (*next_glColor4b)(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha) = NULL;

static void (*next_glColor4bv)(const GLbyte * v) = NULL;

static void (*next_glColor4d)(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha) = NULL;

static void (*next_glColor4dv)(const GLdouble * v) = NULL;

static void (*next_glColor4f)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) = NULL;

static void (*next_glColor4fNormal3fVertex3fSUN)(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glColor4fNormal3fVertex3fvSUN)(const GLfloat * c, const GLfloat * n, const GLfloat * v) = NULL;

static void (*next_glColor4fv)(const GLfloat * v) = NULL;

static void (*next_glColor4i)(GLint red, GLint green, GLint blue, GLint alpha) = NULL;

static void (*next_glColor4iv)(const GLint * v) = NULL;

static void (*next_glColor4s)(GLshort red, GLshort green, GLshort blue, GLshort alpha) = NULL;

static void (*next_glColor4sv)(const GLshort * v) = NULL;

static void (*next_glColor4ub)(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) = NULL;

static void (*next_glColor4ubVertex2fSUN)(GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y) = NULL;

static void (*next_glColor4ubVertex2fvSUN)(const GLubyte * c, const GLfloat * v) = NULL;

static void (*next_glColor4ubVertex3fSUN)(GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glColor4ubVertex3fvSUN)(const GLubyte * c, const GLfloat * v) = NULL;

static void (*next_glColor4ubv)(const GLubyte * v) = NULL;

static void (*next_glColor4ui)(GLuint red, GLuint green, GLuint blue, GLuint alpha) = NULL;

static void (*next_glColor4uiv)(const GLuint * v) = NULL;

static void (*next_glColor4us)(GLushort red, GLushort green, GLushort blue, GLushort alpha) = NULL;

static void (*next_glColor4usv)(const GLushort * v) = NULL;

static void (*next_glColorFragmentOp1ATI)(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod) = NULL;

static void (*next_glColorFragmentOp2ATI)(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod) = NULL;

static void (*next_glColorFragmentOp3ATI)(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod) = NULL;

static void (*next_glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) = NULL;

static void (*next_glColorMaterial)(GLenum face, GLenum mode) = NULL;

static void (*next_glColorPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) = NULL;

static void (*next_glColorPointerEXT)(GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid * pointer) = NULL;

static void (*next_glColorPointerListIBM)(GLint size, GLenum type, GLint stride, const GLvoid* * pointer, GLint ptrstride) = NULL;

static void (*next_glColorPointervINTEL)(GLint size, GLenum type, const GLvoid* * pointer) = NULL;

static void (*next_glColorSubTable)(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid * data) = NULL;

static void (*next_glColorSubTableEXT)(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid * data) = NULL;

static void (*next_glColorTable)(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * table) = NULL;

static void (*next_glColorTableEXT)(GLenum target, GLenum internalFormat, GLsizei width, GLenum format, GLenum type, const GLvoid * table) = NULL;

static void (*next_glColorTableParameterfv)(GLenum target, GLenum pname, const GLfloat * params) = NULL;

static void (*next_glColorTableParameterfvSGI)(GLenum target, GLenum pname, const GLfloat * params) = NULL;

static void (*next_glColorTableParameteriv)(GLenum target, GLenum pname, const GLint * params) = NULL;

static void (*next_glColorTableParameterivSGI)(GLenum target, GLenum pname, const GLint * params) = NULL;

static void (*next_glColorTableSGI)(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * table) = NULL;

static void (*next_glCombinerInputNV)(GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage) = NULL;

static void (*next_glCombinerOutputNV)(GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum) = NULL;

static void (*next_glCombinerParameterfNV)(GLenum pname, GLfloat param) = NULL;

static void (*next_glCombinerParameterfvNV)(GLenum pname, const GLfloat * params) = NULL;

static void (*next_glCombinerParameteriNV)(GLenum pname, GLint param) = NULL;

static void (*next_glCombinerParameterivNV)(GLenum pname, const GLint * params) = NULL;

static void (*next_glCombinerStageParameterfvNV)(GLenum stage, GLenum pname, const GLfloat * params) = NULL;

static void (*next_glCompressedTexImage1D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid * data) = NULL;

static void (*next_glCompressedTexImage1DARB)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid * data) = NULL;

static void (*next_glCompressedTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid * data) = NULL;

static void (*next_glCompressedTexImage2DARB)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid * data) = NULL;

static void (*next_glCompressedTexImage3D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid * data) = NULL;

static void (*next_glCompressedTexImage3DARB)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid * data) = NULL;

static void (*next_glCompressedTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid * data) = NULL;

static void (*next_glCompressedTexSubImage1DARB)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid * data) = NULL;

static void (*next_glCompressedTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid * data) = NULL;

static void (*next_glCompressedTexSubImage2DARB)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid * data) = NULL;

static void (*next_glCompressedTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid * data) = NULL;

static void (*next_glCompressedTexSubImage3DARB)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid * data) = NULL;

static void (*next_glConvolutionFilter1D)(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * image) = NULL;

static void (*next_glConvolutionFilter1DEXT)(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * image) = NULL;

static void (*next_glConvolutionFilter2D)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * image) = NULL;

static void (*next_glConvolutionFilter2DEXT)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * image) = NULL;

static void (*next_glConvolutionParameterf)(GLenum target, GLenum pname, GLfloat params) = NULL;

static void (*next_glConvolutionParameterfEXT)(GLenum target, GLenum pname, GLfloat params) = NULL;

static void (*next_glConvolutionParameterfv)(GLenum target, GLenum pname, const GLfloat * params) = NULL;

static void (*next_glConvolutionParameterfvEXT)(GLenum target, GLenum pname, const GLfloat * params) = NULL;

static void (*next_glConvolutionParameteri)(GLenum target, GLenum pname, GLint params) = NULL;

static void (*next_glConvolutionParameteriEXT)(GLenum target, GLenum pname, GLint params) = NULL;

static void (*next_glConvolutionParameteriv)(GLenum target, GLenum pname, const GLint * params) = NULL;

static void (*next_glConvolutionParameterivEXT)(GLenum target, GLenum pname, const GLint * params) = NULL;

static void (*next_glCopyColorSubTable)(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width) = NULL;

static void (*next_glCopyColorSubTableEXT)(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width) = NULL;

static void (*next_glCopyColorTable)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width) = NULL;

static void (*next_glCopyColorTableSGI)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width) = NULL;

static void (*next_glCopyConvolutionFilter1D)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width) = NULL;

static void (*next_glCopyConvolutionFilter1DEXT)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width) = NULL;

static void (*next_glCopyConvolutionFilter2D)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height) = NULL;

static void (*next_glCopyConvolutionFilter2DEXT)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height) = NULL;

static void (*next_glCopyPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type) = NULL;

static void (*next_glCopyTexImage1D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) = NULL;

static void (*next_glCopyTexImage1DEXT)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) = NULL;

static void (*next_glCopyTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) = NULL;

static void (*next_glCopyTexImage2DEXT)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) = NULL;

static void (*next_glCopyTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) = NULL;

static void (*next_glCopyTexSubImage1DEXT)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) = NULL;

static void (*next_glCopyTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) = NULL;

static void (*next_glCopyTexSubImage2DEXT)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) = NULL;

static void (*next_glCopyTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) = NULL;

static void (*next_glCopyTexSubImage3DEXT)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) = NULL;

static void (*next_glCullFace)(GLenum mode) = NULL;

static void (*next_glCullParameterdvEXT)(GLenum pname, GLdouble * params) = NULL;

static void (*next_glCullParameterfvEXT)(GLenum pname, GLfloat * params) = NULL;

static void (*next_glCurrentPaletteMatrixARB)(GLint index) = NULL;

static void (*next_glDeformSGIX)(GLbitfield mask) = NULL;

static void (*next_glDeformationMap3dSGIX)(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, GLdouble w1, GLdouble w2, GLint wstride, GLint worder, const GLdouble * points) = NULL;

static void (*next_glDeformationMap3fSGIX)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, GLfloat w1, GLfloat w2, GLint wstride, GLint worder, const GLfloat * points) = NULL;

static void (*next_glDeleteAsyncMarkersSGIX)(GLuint marker, GLsizei range) = NULL;

static void (*next_glDeleteFencesNV)(GLsizei n, const GLuint * fences) = NULL;

static void (*next_glDeleteFragmentShaderATI)(GLuint id) = NULL;

static void (*next_glDeleteLists)(GLuint list, GLsizei range) = NULL;

static void (*next_glDeleteObjectBufferATI)(GLuint buffer) = NULL;

static void (*next_glDeleteProgramsNV)(GLsizei n, const GLuint * ids) = NULL;

static void (*next_glDeleteTextures)(GLsizei n, const GLuint * textures) = NULL;

static void (*next_glDeleteTexturesEXT)(GLsizei n, const GLuint * textures) = NULL;

static void (*next_glDeleteVertexShaderEXT)(GLuint id) = NULL;

static void (*next_glDepthFunc)(GLenum func) = NULL;

static void (*next_glDepthMask)(GLboolean flag) = NULL;

static void (*next_glDepthRange)(GLclampd near, GLclampd far) = NULL;

static void (*next_glDetailTexFuncSGIS)(GLenum target, GLsizei n, const GLfloat * points) = NULL;

static void (*next_glDisable)(GLenum cap) = NULL;

static void (*next_glDisableClientState)(GLenum array) = NULL;

static void (*next_glDisableVariantClientStateEXT)(GLuint id) = NULL;

static void (*next_glDrawArrays)(GLenum mode, GLint first, GLsizei count) = NULL;

static void (*next_glDrawArraysEXT)(GLenum mode, GLint first, GLsizei count) = NULL;
static void (*next_glDeleteBuffers)(GLsizei n, const GLuint* buffersa) = NULL;
static void (*next_glGenBuffers)(GLsizei n, GLuint* buffers) = NULL;

static void (*next_glDrawBuffer)(GLenum mode) = NULL;

static void (*next_glDrawElementArrayATI)(GLenum mode, GLsizei count) = NULL;

static void (*next_glDrawElements)(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices) = NULL;

static void (*next_glDrawMeshArraysSUN)(GLenum mode, GLint first, GLsizei count, GLsizei width) = NULL;

static void (*next_glDrawPixels)(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels) = NULL;

static void (*next_glDrawRangeElementArrayATI)(GLenum mode, GLuint start, GLuint end, GLsizei count) = NULL;

static void (*next_glDrawRangeElements)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices) = NULL;

static void (*next_glDrawRangeElementsEXT)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices) = NULL;

static void (*next_glEdgeFlag)(GLboolean flag) = NULL;

static void (*next_glEdgeFlagPointer)(GLsizei stride, const GLvoid * pointer) = NULL;

static void (*next_glEdgeFlagPointerEXT)(GLsizei stride, GLsizei count, const GLvoid * pointer) = NULL;

static void (*next_glEdgeFlagPointerListIBM)(GLint stride, const GLboolean* * pointer, GLint ptrstride) = NULL;

static void (*next_glEdgeFlagv)(const GLboolean * flag) = NULL;

static void (*next_glElementPointerATI)(GLenum type, const GLvoid * pointer) = NULL;

static void (*next_glEnable)(GLenum cap) = NULL;

static void (*next_glEnableClientState)(GLenum array) = NULL;

static void (*next_glEnableVariantClientStateEXT)(GLuint id) = NULL;

static void (*next_glEnd)() = NULL;

static void (*next_glEndFragmentShaderATI)() = NULL;

static void (*next_glEndList)() = NULL;

static void (*next_glEndVertexShaderEXT)() = NULL;

static void (*next_glEvalCoord1d)(GLdouble u) = NULL;

static void (*next_glEvalCoord1dv)(const GLdouble * u) = NULL;

static void (*next_glEvalCoord1f)(GLfloat u) = NULL;

static void (*next_glEvalCoord1fv)(const GLfloat * u) = NULL;

static void (*next_glEvalCoord2d)(GLdouble u, GLdouble v) = NULL;

static void (*next_glEvalCoord2dv)(const GLdouble * u) = NULL;

static void (*next_glEvalCoord2f)(GLfloat u, GLfloat v) = NULL;

static void (*next_glEvalCoord2fv)(const GLfloat * u) = NULL;

static void (*next_glEvalMapsNV)(GLenum target, GLenum mode) = NULL;

static void (*next_glEvalMesh1)(GLenum mode, GLint i1, GLint i2) = NULL;

static void (*next_glEvalMesh2)(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2) = NULL;

static void (*next_glEvalPoint1)(GLint i) = NULL;

static void (*next_glEvalPoint2)(GLint i, GLint j) = NULL;

static void (*next_glExecuteProgramNV)(GLenum target, GLuint id, const GLfloat * params) = NULL;

static void (*next_glExtractComponentEXT)(GLuint res, GLuint src, GLuint num) = NULL;

static void (*next_glFeedbackBuffer)(GLsizei size, GLenum type, GLfloat * buffer) = NULL;

static void (*next_glFinalCombinerInputNV)(GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage) = NULL;

static void (*next_glFinish)() = NULL;

static GLint (*next_glFinishAsyncSGIX)(GLuint * markerp) = NULL;

static void (*next_glFinishFenceNV)(GLuint fence) = NULL;

static void (*next_glFinishTextureSUNX)() = NULL;

static void (*next_gluLookAt)(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat)= NULL;

static void (*next_glFlush)() = NULL;

static void (*next_glFlushRasterSGIX)() = NULL;

static void (*next_glFlushVertexArrayRangeNV)() = NULL;

static void (*next_glFogCoordPointerEXT)(GLenum type, GLsizei stride, const GLvoid * pointer) = NULL;

static void (*next_glFogCoordPointerListIBM)(GLenum type, GLint stride, const GLvoid* * pointer, GLint ptrstride) = NULL;

static void (*next_glFogCoorddEXT)(GLdouble coord) = NULL;

static void (*next_glFogCoorddvEXT)(const GLdouble * coord) = NULL;

static void (*next_glFogCoordfEXT)(GLfloat coord) = NULL;

static void (*next_glFogCoordfvEXT)(const GLfloat * coord) = NULL;

static void (*next_glFogFuncSGIS)(GLsizei n, const GLfloat * points) = NULL;

static void (*next_glFogf)(GLenum pname, GLfloat param) = NULL;

static void (*next_glFogfv)(GLenum pname, const GLfloat * params) = NULL;

static void (*next_glFogi)(GLenum pname, GLint param) = NULL;

static void (*next_glFogiv)(GLenum pname, const GLint * params) = NULL;

static void (*next_glFragmentColorMaterialSGIX)(GLenum face, GLenum mode) = NULL;

static void (*next_glFragmentLightModelfSGIX)(GLenum pname, GLfloat param) = NULL;

static void (*next_glFragmentLightModelfvSGIX)(GLenum pname, const GLfloat * params) = NULL;

static void (*next_glFragmentLightModeliSGIX)(GLenum pname, GLint param) = NULL;

static void (*next_glFragmentLightModelivSGIX)(GLenum pname, const GLint * params) = NULL;

static void (*next_glFragmentLightfSGIX)(GLenum light, GLenum pname, GLfloat param) = NULL;

static void (*next_glFragmentLightfvSGIX)(GLenum light, GLenum pname, const GLfloat * params) = NULL;

static void (*next_glFragmentLightiSGIX)(GLenum light, GLenum pname, GLint param) = NULL;

static void (*next_glFragmentLightivSGIX)(GLenum light, GLenum pname, const GLint * params) = NULL;

static void (*next_glFragmentMaterialfSGIX)(GLenum face, GLenum pname, GLfloat param) = NULL;

static void (*next_glFragmentMaterialfvSGIX)(GLenum face, GLenum pname, const GLfloat * params) = NULL;

static void (*next_glFragmentMaterialiSGIX)(GLenum face, GLenum pname, GLint param) = NULL;

static void (*next_glFragmentMaterialivSGIX)(GLenum face, GLenum pname, const GLint * params) = NULL;

static void (*next_glFrameZoomSGIX)(GLint factor) = NULL;

static void (*next_glFrontFace)(GLenum mode) = NULL;

static void (*next_glFrustum)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) = NULL;

static GLuint (*next_glGenAsyncMarkersSGIX)(GLsizei range) = NULL;

static void (*next_glGenFencesNV)(GLsizei n, GLuint * fences) = NULL;

static GLuint (*next_glGenFragmentShadersATI)(GLuint range) = NULL;

static GLuint (*next_glGenLists)(GLsizei range) = NULL;

static void (*next_glGenProgramsNV)(GLsizei n, GLuint * ids) = NULL;

static GLuint (*next_glGenSymbolsEXT)(GLenum datatype, GLenum storagetype, GLenum range, GLuint components) = NULL;

static void (*next_glGenTextures)(GLsizei n, GLuint * textures) = NULL;

static void (*next_glGenTexturesEXT)(GLsizei n, GLuint * textures) = NULL;

static GLuint (*next_glGenVertexShadersEXT)(GLuint range) = NULL;

static void (*next_glGetArrayObjectfvATI)(GLenum array, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetArrayObjectivATI)(GLenum array, GLenum pname, GLint * params) = NULL;

static void (*next_glGetBooleanv)(GLenum pname, GLboolean * params) = NULL;

static void (*next_glGetClipPlane)(GLenum plane, GLdouble * equation) = NULL;

static void (*next_glGetColorTable)(GLenum target, GLenum format, GLenum type, GLvoid * table) = NULL;

static void (*next_glGetColorTableEXT)(GLenum target, GLenum format, GLenum type, GLvoid * data) = NULL;

static void (*next_glGetColorTableParameterfv)(GLenum target, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetColorTableParameterfvEXT)(GLenum target, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetColorTableParameterfvSGI)(GLenum target, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetColorTableParameteriv)(GLenum target, GLenum pname, GLint * params) = NULL;

static void (*next_glGetColorTableParameterivEXT)(GLenum target, GLenum pname, GLint * params) = NULL;

static void (*next_glGetColorTableParameterivSGI)(GLenum target, GLenum pname, GLint * params) = NULL;

static void (*next_glGetColorTableSGI)(GLenum target, GLenum format, GLenum type, GLvoid * table) = NULL;

static void (*next_glGetCombinerInputParameterfvNV)(GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetCombinerInputParameterivNV)(GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint * params) = NULL;

static void (*next_glGetCombinerOutputParameterfvNV)(GLenum stage, GLenum portion, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetCombinerOutputParameterivNV)(GLenum stage, GLenum portion, GLenum pname, GLint * params) = NULL;

static void (*next_glGetCombinerStageParameterfvNV)(GLenum stage, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetCompressedTexImage)(GLenum target, GLint level, void * img) = NULL;

static void (*next_glGetCompressedTexImageARB)(GLenum target, GLint level, void * img) = NULL;

static void (*next_glGetConvolutionFilter)(GLenum target, GLenum format, GLenum type, GLvoid * image) = NULL;

static void (*next_glGetConvolutionFilterEXT)(GLenum target, GLenum format, GLenum type, GLvoid * image) = NULL;

static void (*next_glGetConvolutionParameterfv)(GLenum target, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetConvolutionParameterfvEXT)(GLenum target, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetConvolutionParameteriv)(GLenum target, GLenum pname, GLint * params) = NULL;

static void (*next_glGetConvolutionParameterivEXT)(GLenum target, GLenum pname, GLint * params) = NULL;

static void (*next_glGetDetailTexFuncSGIS)(GLenum target, GLfloat * points) = NULL;

static void (*next_glGetDoublev)(GLenum pname, GLdouble * params) = NULL;

static GLenum (*next_glGetError)() = NULL;

static void (*next_glGetFenceivNV)(GLuint fence, GLenum pname, GLint * params) = NULL;

static void (*next_glGetFinalCombinerInputParameterfvNV)(GLenum variable, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetFinalCombinerInputParameterivNV)(GLenum variable, GLenum pname, GLint * params) = NULL;

static void (*next_glGetFloatv)(GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetFogFuncSGIS)(GLfloat * points) = NULL;

static void (*next_glGetFragmentLightfvSGIX)(GLenum light, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetFragmentLightivSGIX)(GLenum light, GLenum pname, GLint * params) = NULL;

static void (*next_glGetFragmentMaterialfvSGIX)(GLenum face, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetFragmentMaterialivSGIX)(GLenum face, GLenum pname, GLint * params) = NULL;

static void (*next_glGetHistogram)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid * values) = NULL;

static void (*next_glGetHistogramEXT)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid * values) = NULL;

static void (*next_glGetHistogramParameterfv)(GLenum target, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetHistogramParameterfvEXT)(GLenum target, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetHistogramParameteriv)(GLenum target, GLenum pname, GLint * params) = NULL;

static void (*next_glGetHistogramParameterivEXT)(GLenum target, GLenum pname, GLint * params) = NULL;

static void (*next_glGetImageTransformParameterfvHP)(GLenum target, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetImageTransformParameterivHP)(GLenum target, GLenum pname, GLint * params) = NULL;

static GLint (*next_glGetInstrumentsSGIX)() = NULL;

static void (*next_glGetIntegerv)(GLenum pname, GLint * params) = NULL;

static void (*next_glGetInvariantBooleanvEXT)(GLuint id, GLenum value, GLboolean * data) = NULL;

static void (*next_glGetInvariantFloatvEXT)(GLuint id, GLenum value, GLfloat * data) = NULL;

static void (*next_glGetInvariantIntegervEXT)(GLuint id, GLenum value, GLint * data) = NULL;

static void (*next_glGetLightfv)(GLenum light, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetLightiv)(GLenum light, GLenum pname, GLint * params) = NULL;

static void (*next_glGetListParameterfvSGIX)(GLuint list, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetListParameterivSGIX)(GLuint list, GLenum pname, GLint * params) = NULL;

static void (*next_glGetLocalConstantBooleanvEXT)(GLuint id, GLenum value, GLboolean * data) = NULL;

static void (*next_glGetLocalConstantFloatvEXT)(GLuint id, GLenum value, GLfloat * data) = NULL;

static void (*next_glGetLocalConstantIntegervEXT)(GLuint id, GLenum value, GLint * data) = NULL;

static void (*next_glGetMapAttribParameterfvNV)(GLenum target, GLuint index, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetMapAttribParameterivNV)(GLenum target, GLuint index, GLenum pname, GLint * params) = NULL;

static void (*next_glGetMapControlPointsNV)(GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLboolean packed, GLvoid * points) = NULL;

static void (*next_glGetMapParameterfvNV)(GLenum target, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetMapParameterivNV)(GLenum target, GLenum pname, GLint * params) = NULL;

static void (*next_glGetMapdv)(GLenum target, GLenum query, GLdouble * v) = NULL;

static void (*next_glGetMapfv)(GLenum target, GLenum query, GLfloat * v) = NULL;

static void (*next_glGetMapiv)(GLenum target, GLenum query, GLint * v) = NULL;

static void (*next_glGetMaterialfv)(GLenum face, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetMaterialiv)(GLenum face, GLenum pname, GLint * params) = NULL;

static void (*next_glGetMinmax)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid * values) = NULL;

static void (*next_glGetMinmaxEXT)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid * values) = NULL;

static void (*next_glGetMinmaxParameterfv)(GLenum target, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetMinmaxParameterfvEXT)(GLenum target, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetMinmaxParameteriv)(GLenum target, GLenum pname, GLint * params) = NULL;

static void (*next_glGetMinmaxParameterivEXT)(GLenum target, GLenum pname, GLint * params) = NULL;

static void (*next_glGetObjectBufferfvATI)(GLuint buffer, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetObjectBufferivATI)(GLuint buffer, GLenum pname, GLint * params) = NULL;

static void (*next_glGetPixelMapfv)(GLenum map, GLfloat * values) = NULL;

static void (*next_glGetPixelMapuiv)(GLenum map, GLuint * values) = NULL;

static void (*next_glGetPixelMapusv)(GLenum map, GLushort * values) = NULL;

static void (*next_glGetPixelTexGenParameterfvSGIS)(GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetPixelTexGenParameterivSGIS)(GLenum pname, GLint * params) = NULL;

static void (*next_glGetPointerv)(GLenum pname, GLvoid* * params) = NULL;

static void (*next_glGetPointervEXT)(GLenum pname, GLvoid* * params) = NULL;

static void (*next_glGetPolygonStipple)(GLubyte * mask) = NULL;

static void (*next_glGetProgramParameterdvNV)(GLenum target, GLuint index, GLenum pname, GLdouble * params) = NULL;

static void (*next_glGetProgramParameterfvNV)(GLenum target, GLuint index, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetProgramStringNV)(GLuint id, GLenum pname, GLubyte * program) = NULL;

static void (*next_glGetProgramivNV)(GLuint id, GLenum pname, GLint * params) = NULL;

static void (*next_glGetSeparableFilter)(GLenum target, GLenum format, GLenum type, GLvoid * row, GLvoid * column, GLvoid * span) = NULL;

static void (*next_glGetSeparableFilterEXT)(GLenum target, GLenum format, GLenum type, GLvoid * row, GLvoid * column, GLvoid * span) = NULL;

static void (*next_glGetSharpenTexFuncSGIS)(GLenum target, GLfloat * points) = NULL;

static const GLubyte * (*next_glGetString)(GLenum name) = NULL;

static void (*next_glGetTexBumpParameterfvATI)(GLenum pname, GLfloat * param) = NULL;

static void (*next_glGetTexBumpParameterivATI)(GLenum pname, GLint * param) = NULL;

static void (*next_glGetTexEnvfv)(GLenum target, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetTexEnviv)(GLenum target, GLenum pname, GLint * params) = NULL;

static void (*next_glGetTexFilterFuncSGIS)(GLenum target, GLenum filter, GLfloat * weights) = NULL;

static void (*next_glGetTexGendv)(GLenum coord, GLenum pname, GLdouble * params) = NULL;

static void (*next_glGetTexGenfv)(GLenum coord, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetTexGeniv)(GLenum coord, GLenum pname, GLint * params) = NULL;

static void (*next_glGetTexImage)(GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels) = NULL;

static void (*next_glGetTexLevelParameterfv)(GLenum target, GLint level, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetTexLevelParameteriv)(GLenum target, GLint level, GLenum pname, GLint * params) = NULL;

static void (*next_glGetTexParameterfv)(GLenum target, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetTexParameteriv)(GLenum target, GLenum pname, GLint * params) = NULL;

static void (*next_glGetTrackMatrixivNV)(GLenum target, GLuint address, GLenum pname, GLint * params) = NULL;

static void (*next_glGetVariantArrayObjectfvATI)(GLuint id, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetVariantArrayObjectivATI)(GLuint id, GLenum pname, GLint * params) = NULL;

static void (*next_glGetVariantBooleanvEXT)(GLuint id, GLenum value, GLboolean * data) = NULL;

static void (*next_glGetVariantFloatvEXT)(GLuint id, GLenum value, GLfloat * data) = NULL;

static void (*next_glGetVariantIntegervEXT)(GLuint id, GLenum value, GLint * data) = NULL;

static void (*next_glGetVariantPointervEXT)(GLuint id, GLenum value, GLvoid* * data) = NULL;

static void (*next_glGetVertexAttribPointervNV)(GLuint index, GLenum pname, GLvoid* * pointer) = NULL;

static void (*next_glGetVertexAttribdvNV)(GLuint index, GLenum pname, GLdouble * params) = NULL;

static void (*next_glGetVertexAttribfvNV)(GLuint index, GLenum pname, GLfloat * params) = NULL;

static void (*next_glGetVertexAttribivNV)(GLuint index, GLenum pname, GLint * params) = NULL;

static void (*next_glGlobalAlphaFactorbSUN)(GLbyte factor) = NULL;

static void (*next_glGlobalAlphaFactordSUN)(GLdouble factor) = NULL;

static void (*next_glGlobalAlphaFactorfSUN)(GLfloat factor) = NULL;

static void (*next_glGlobalAlphaFactoriSUN)(GLint factor) = NULL;

static void (*next_glGlobalAlphaFactorsSUN)(GLshort factor) = NULL;

static void (*next_glGlobalAlphaFactorubSUN)(GLubyte factor) = NULL;

static void (*next_glGlobalAlphaFactoruiSUN)(GLuint factor) = NULL;

static void (*next_glGlobalAlphaFactorusSUN)(GLushort factor) = NULL;

static void (*next_glHint)(GLenum target, GLenum mode) = NULL;

static void (*next_glHintPGI)(GLenum target, GLint mode) = NULL;

static void (*next_glHistogram)(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink) = NULL;

static void (*next_glHistogramEXT)(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink) = NULL;

static void (*next_glIglooInterfaceSGIX)(GLenum pname, const GLvoid * params) = NULL;

static void (*next_glImageTransformParameterfHP)(GLenum target, GLenum pname, GLfloat param) = NULL;

static void (*next_glImageTransformParameterfvHP)(GLenum target, GLenum pname, const GLfloat * params) = NULL;

static void (*next_glImageTransformParameteriHP)(GLenum target, GLenum pname, GLint param) = NULL;

static void (*next_glImageTransformParameterivHP)(GLenum target, GLenum pname, const GLint * params) = NULL;

static void (*next_glIndexFuncEXT)(GLenum func, GLclampf ref) = NULL;

static void (*next_glIndexMask)(GLuint mask) = NULL;

static void (*next_glIndexMaterialEXT)(GLenum face, GLenum mode) = NULL;

static void (*next_glIndexPointer)(GLenum type, GLsizei stride, const GLvoid * pointer) = NULL;

static void (*next_glIndexPointerEXT)(GLenum type, GLsizei stride, GLsizei count, const GLvoid * pointer) = NULL;

static void (*next_glIndexPointerListIBM)(GLenum type, GLint stride, const GLvoid* * pointer, GLint ptrstride) = NULL;

static void (*next_glIndexd)(GLdouble c) = NULL;

static void (*next_glIndexdv)(const GLdouble * c) = NULL;

static void (*next_glIndexf)(GLfloat c) = NULL;

static void (*next_glIndexfv)(const GLfloat * c) = NULL;

static void (*next_glIndexi)(GLint c) = NULL;

static void (*next_glIndexiv)(const GLint * c) = NULL;

static void (*next_glIndexs)(GLshort c) = NULL;

static void (*next_glIndexsv)(const GLshort * c) = NULL;

static void (*next_glIndexub)(GLubyte c) = NULL;

static void (*next_glIndexubv)(const GLubyte * c) = NULL;

static void (*next_glInitNames)() = NULL;

static void (*next_glInsertComponentEXT)(GLuint res, GLuint src, GLuint num) = NULL;

static void (*next_glInstrumentsBufferSGIX)(GLsizei size, GLint * buffer) = NULL;

static void (*next_glInterleavedArrays)(GLenum format, GLsizei stride, const GLvoid * pointer) = NULL;

static GLboolean (*next_glIsAsyncMarkerSGIX)(GLuint marker) = NULL;

static GLboolean (*next_glIsEnabled)(GLenum cap) = NULL;

static GLboolean (*next_glIsFenceNV)(GLuint fence) = NULL;

static GLboolean (*next_glIsList)(GLuint list) = NULL;

static GLboolean (*next_glIsObjectBufferATI)(GLuint buffer) = NULL;

static GLboolean (*next_glIsProgramNV)(GLuint id) = NULL;

static GLboolean (*next_glIsTexture)(GLuint texture) = NULL;

static GLboolean (*next_glIsTextureEXT)(GLuint texture) = NULL;

static GLboolean (*next_glIsVariantEnabledEXT)(GLuint id, GLenum cap) = NULL;

static void (*next_glLightEnviSGIX)(GLenum pname, GLint param) = NULL;

static void (*next_glLightModelf)(GLenum pname, GLfloat param) = NULL;

static void (*next_glLightModelfv)(GLenum pname, const GLfloat * params) = NULL;

static void (*next_glLightModeli)(GLenum pname, GLint param) = NULL;

static void (*next_glLightModeliv)(GLenum pname, const GLint * params) = NULL;

static void (*next_glLightf)(GLenum light, GLenum pname, GLfloat param) = NULL;

static void (*next_glLightfv)(GLenum light, GLenum pname, const GLfloat * params) = NULL;

static void (*next_glLighti)(GLenum light, GLenum pname, GLint param) = NULL;

static void (*next_glLightiv)(GLenum light, GLenum pname, const GLint * params) = NULL;

static void (*next_glLineStipple)(GLint factor, GLushort pattern) = NULL;

static void (*next_glLineWidth)(GLfloat width) = NULL;

static void (*next_glListBase)(GLuint base) = NULL;

static void (*next_glListParameterfSGIX)(GLuint list, GLenum pname, GLfloat param) = NULL;

static void (*next_glListParameterfvSGIX)(GLuint list, GLenum pname, const GLfloat * params) = NULL;

static void (*next_glListParameteriSGIX)(GLuint list, GLenum pname, GLint param) = NULL;

static void (*next_glListParameterivSGIX)(GLuint list, GLenum pname, const GLint * params) = NULL;

static void (*next_glLoadIdentity)() = NULL;

static void (*next_glLoadIdentityDeformationMapSGIX)(GLbitfield mask) = NULL;

static void (*next_glLoadMatrixd)(const GLdouble * m) = NULL;

static void (*next_glLoadMatrixf)(const GLfloat * m) = NULL;

static void (*next_glLoadName)(GLuint name) = NULL;

static void (*next_glLoadProgramNV)(GLenum target, GLuint id, GLsizei len, const GLubyte * program) = NULL;

static void (*next_glLoadTransposeMatrixd)(const GLdouble * m) = NULL;

static void (*next_glLoadTransposeMatrixdARB)(const GLdouble * m) = NULL;

static void (*next_glLoadTransposeMatrixf)(const GLfloat * m) = NULL;

static void (*next_glLoadTransposeMatrixfARB)(const GLfloat * m) = NULL;

static void (*next_glLockArraysEXT)(GLint first, GLsizei count) = NULL;

static void (*next_glLogicOp)(GLenum opcode) = NULL;

static void (*next_glMap1d)(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points) = NULL;

static void (*next_glMap1f)(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points) = NULL;

static void (*next_glMap2d)(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points) = NULL;

static void (*next_glMap2f)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points) = NULL;

static void (*next_glMapControlPointsNV)(GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLint uorder, GLint vorder, GLboolean packed, const GLvoid * points) = NULL;

static void (*next_glMapGrid1d)(GLint un, GLdouble u1, GLdouble u2) = NULL;

static void (*next_glMapGrid1f)(GLint un, GLfloat u1, GLfloat u2) = NULL;

static void (*next_glMapGrid2d)(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2) = NULL;

static void (*next_glMapGrid2f)(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2) = NULL;

static void (*next_glMapParameterfvNV)(GLenum target, GLenum pname, const GLfloat * params) = NULL;

static void (*next_glMapParameterivNV)(GLenum target, GLenum pname, const GLint * params) = NULL;

static void (*next_glMaterialf)(GLenum face, GLenum pname, GLfloat param) = NULL;

static void (*next_glMaterialfv)(GLenum face, GLenum pname, const GLfloat * params) = NULL;

static void (*next_glMateriali)(GLenum face, GLenum pname, GLint param) = NULL;

static void (*next_glMaterialiv)(GLenum face, GLenum pname, const GLint * params) = NULL;

static void (*next_glMatrixIndexPointerARB)(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) = NULL;

static void (*next_glMatrixIndexubvARB)(GLint size, const GLubyte * indices) = NULL;

static void (*next_glMatrixIndexuivARB)(GLint size, const GLuint * indices) = NULL;

static void (*next_glMatrixIndexusvARB)(GLint size, const GLushort * indices) = NULL;

static void (*next_glMatrixMode)(GLenum mode) = NULL;

static void (*next_glMinmax)(GLenum target, GLenum internalformat, GLboolean sink) = NULL;

static void (*next_glMinmaxEXT)(GLenum target, GLenum internalformat, GLboolean sink) = NULL;

static void (*next_glMultMatrixd)(const GLdouble * m) = NULL;

static void (*next_glMultMatrixf)(const GLfloat * m) = NULL;

static void (*next_glMultTransposeMatrixd)(const GLdouble * m) = NULL;

static void (*next_glMultTransposeMatrixdARB)(const GLdouble * m) = NULL;

static void (*next_glMultTransposeMatrixf)(const GLfloat * m) = NULL;

static void (*next_glMultTransposeMatrixfARB)(const GLfloat * m) = NULL;

static void (*next_glMultiDrawArraysEXT)(GLenum mode, GLint * first, GLsizei * count, GLsizei primcount) = NULL;

static void (*next_glMultiDrawElementsEXT)(GLenum mode, const GLsizei * count, GLenum type, const GLvoid* * indices, GLsizei primcount) = NULL;

static void (*next_glMultiModeDrawArraysIBM)(GLenum mode, const GLint * first, const GLsizei * count, GLsizei primcount, GLint modestride) = NULL;

static void (*next_glMultiModeDrawElementsIBM)(const GLenum * mode, const GLsizei * count, GLenum type, const GLvoid* * indices, GLsizei primcount, GLint modestride) = NULL;

static void (*next_glMultiTexCoord1d)(GLenum target, GLdouble s) = NULL;

static void (*next_glMultiTexCoord1dARB)(GLenum target, GLdouble s) = NULL;

static void (*next_glMultiTexCoord1dv)(GLenum target, const GLdouble * v) = NULL;

static void (*next_glMultiTexCoord1dvARB)(GLenum target, const GLdouble * v) = NULL;

static void (*next_glMultiTexCoord1f)(GLenum target, GLfloat s) = NULL;

static void (*next_glMultiTexCoord1fARB)(GLenum target, GLfloat s) = NULL;

static void (*next_glMultiTexCoord1fv)(GLenum target, const GLfloat * v) = NULL;

static void (*next_glMultiTexCoord1fvARB)(GLenum target, const GLfloat * v) = NULL;

static void (*next_glMultiTexCoord1i)(GLenum target, GLint s) = NULL;

static void (*next_glMultiTexCoord1iARB)(GLenum target, GLint s) = NULL;

static void (*next_glMultiTexCoord1iv)(GLenum target, const GLint * v) = NULL;

static void (*next_glMultiTexCoord1ivARB)(GLenum target, const GLint * v) = NULL;

static void (*next_glMultiTexCoord1s)(GLenum target, GLshort s) = NULL;

static void (*next_glMultiTexCoord1sARB)(GLenum target, GLshort s) = NULL;

static void (*next_glMultiTexCoord1sv)(GLenum target, const GLshort * v) = NULL;

static void (*next_glMultiTexCoord1svARB)(GLenum target, const GLshort * v) = NULL;

static void (*next_glMultiTexCoord2d)(GLenum target, GLdouble s, GLdouble t) = NULL;

static void (*next_glMultiTexCoord2dARB)(GLenum target, GLdouble s, GLdouble t) = NULL;

static void (*next_glMultiTexCoord2dv)(GLenum target, const GLdouble * v) = NULL;

static void (*next_glMultiTexCoord2dvARB)(GLenum target, const GLdouble * v) = NULL;

static void (*next_glMultiTexCoord2f)(GLenum target, GLfloat s, GLfloat t) = NULL;

static void (*next_glMultiTexCoord2fARB)(GLenum target, GLfloat s, GLfloat t) = NULL;

static void (*next_glMultiTexCoord2fv)(GLenum target, const GLfloat * v) = NULL;

static void (*next_glMultiTexCoord2fvARB)(GLenum target, const GLfloat * v) = NULL;

static void (*next_glMultiTexCoord2i)(GLenum target, GLint s, GLint t) = NULL;

static void (*next_glMultiTexCoord2iARB)(GLenum target, GLint s, GLint t) = NULL;

static void (*next_glMultiTexCoord2iv)(GLenum target, const GLint * v) = NULL;

static void (*next_glMultiTexCoord2ivARB)(GLenum target, const GLint * v) = NULL;

static void (*next_glMultiTexCoord2s)(GLenum target, GLshort s, GLshort t) = NULL;

static void (*next_glMultiTexCoord2sARB)(GLenum target, GLshort s, GLshort t) = NULL;

static void (*next_glMultiTexCoord2sv)(GLenum target, const GLshort * v) = NULL;

static void (*next_glMultiTexCoord2svARB)(GLenum target, const GLshort * v) = NULL;

static void (*next_glMultiTexCoord3d)(GLenum target, GLdouble s, GLdouble t, GLdouble r) = NULL;

static void (*next_glMultiTexCoord3dARB)(GLenum target, GLdouble s, GLdouble t, GLdouble r) = NULL;

static void (*next_glMultiTexCoord3dv)(GLenum target, const GLdouble * v) = NULL;

static void (*next_glMultiTexCoord3dvARB)(GLenum target, const GLdouble * v) = NULL;

static void (*next_glMultiTexCoord3f)(GLenum target, GLfloat s, GLfloat t, GLfloat r) = NULL;

static void (*next_glMultiTexCoord3fARB)(GLenum target, GLfloat s, GLfloat t, GLfloat r) = NULL;

static void (*next_glMultiTexCoord3fv)(GLenum target, const GLfloat * v) = NULL;

static void (*next_glMultiTexCoord3fvARB)(GLenum target, const GLfloat * v) = NULL;

static void (*next_glMultiTexCoord3i)(GLenum target, GLint s, GLint t, GLint r) = NULL;

static void (*next_glMultiTexCoord3iARB)(GLenum target, GLint s, GLint t, GLint r) = NULL;

static void (*next_glMultiTexCoord3iv)(GLenum target, const GLint * v) = NULL;

static void (*next_glMultiTexCoord3ivARB)(GLenum target, const GLint * v) = NULL;

static void (*next_glMultiTexCoord3s)(GLenum target, GLshort s, GLshort t, GLshort r) = NULL;

static void (*next_glMultiTexCoord3sARB)(GLenum target, GLshort s, GLshort t, GLshort r) = NULL;

static void (*next_glMultiTexCoord3sv)(GLenum target, const GLshort * v) = NULL;

static void (*next_glMultiTexCoord3svARB)(GLenum target, const GLshort * v) = NULL;

static void (*next_glMultiTexCoord4d)(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q) = NULL;

static void (*next_glMultiTexCoord4dARB)(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q) = NULL;

static void (*next_glMultiTexCoord4dv)(GLenum target, const GLdouble * v) = NULL;

static void (*next_glMultiTexCoord4dvARB)(GLenum target, const GLdouble * v) = NULL;

static void (*next_glMultiTexCoord4f)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q) = NULL;

static void (*next_glMultiTexCoord4fARB)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q) = NULL;

static void (*next_glMultiTexCoord4fv)(GLenum target, const GLfloat * v) = NULL;

static void (*next_glMultiTexCoord4fvARB)(GLenum target, const GLfloat * v) = NULL;

static void (*next_glMultiTexCoord4i)(GLenum target, GLint s, GLint t, GLint r, GLint q) = NULL;

static void (*next_glMultiTexCoord4iARB)(GLenum target, GLint s, GLint t, GLint r, GLint q) = NULL;

static void (*next_glMultiTexCoord4iv)(GLenum target, const GLint * v) = NULL;

static void (*next_glMultiTexCoord4ivARB)(GLenum target, const GLint * v) = NULL;

static void (*next_glMultiTexCoord4s)(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q) = NULL;

static void (*next_glMultiTexCoord4sARB)(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q) = NULL;

static void (*next_glMultiTexCoord4sv)(GLenum target, const GLshort * v) = NULL;

static void (*next_glMultiTexCoord4svARB)(GLenum target, const GLshort * v) = NULL;

static void (*next_glNewList)(GLuint list, GLenum mode) = NULL;

static GLuint (*next_glNewObjectBufferATI)(GLsizei size, const GLvoid * pointer, GLenum usage) = NULL;

static void (*next_glNormal3b)(GLbyte nx, GLbyte ny, GLbyte nz) = NULL;

static void (*next_glNormal3bv)(const GLbyte * v) = NULL;

static void (*next_glNormal3d)(GLdouble nx, GLdouble ny, GLdouble nz) = NULL;

static void (*next_glNormal3dv)(const GLdouble * v) = NULL;

static void (*next_glNormal3f)(GLfloat nx, GLfloat ny, GLfloat nz) = NULL;

static void (*next_glNormal3fVertex3fSUN)(GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glNormal3fVertex3fvSUN)(const GLfloat * n, const GLfloat * v) = NULL;

static void (*next_glNormal3fv)(const GLfloat * v) = NULL;

static void (*next_glNormal3i)(GLint nx, GLint ny, GLint nz) = NULL;

static void (*next_glNormal3iv)(const GLint * v) = NULL;

static void (*next_glNormal3s)(GLshort nx, GLshort ny, GLshort nz) = NULL;

static void (*next_glNormal3sv)(const GLshort * v) = NULL;

static void (*next_glNormalPointer)(GLenum type, GLsizei stride, const GLvoid * pointer) = NULL;

static void (*next_glNormalPointerEXT)(GLenum type, GLsizei stride, GLsizei count, const GLvoid * pointer) = NULL;

static void (*next_glNormalPointerListIBM)(GLenum type, GLint stride, const GLvoid* * pointer, GLint ptrstride) = NULL;

static void (*next_glNormalPointervINTEL)(GLenum type, const GLvoid* * pointer) = NULL;

static void (*next_glNormalStream3bATI)(GLenum stream, GLbyte nx, GLbyte ny, GLbyte nz) = NULL;

static void (*next_glNormalStream3bvATI)(GLenum stream, const GLbyte * coords) = NULL;

static void (*next_glNormalStream3dATI)(GLenum stream, GLdouble nx, GLdouble ny, GLdouble nz) = NULL;

static void (*next_glNormalStream3dvATI)(GLenum stream, const GLdouble * coords) = NULL;

static void (*next_glNormalStream3fATI)(GLenum stream, GLfloat nx, GLfloat ny, GLfloat nz) = NULL;

static void (*next_glNormalStream3fvATI)(GLenum stream, const GLfloat * coords) = NULL;

static void (*next_glNormalStream3iATI)(GLenum stream, GLint nx, GLint ny, GLint nz) = NULL;

static void (*next_glNormalStream3ivATI)(GLenum stream, const GLint * coords) = NULL;

static void (*next_glNormalStream3sATI)(GLenum stream, GLshort nx, GLshort ny, GLshort nz) = NULL;

static void (*next_glNormalStream3svATI)(GLenum stream, const GLshort * coords) = NULL;

static void (*next_glOrtho)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) = NULL;

static void (*next_glPNTrianglesfATI)(GLenum pname, GLfloat param) = NULL;

static void (*next_glPNTrianglesiATI)(GLenum pname, GLint param) = NULL;

static void (*next_glPassTexCoordATI)(GLuint dst, GLuint coord, GLenum swizzle) = NULL;

static void (*next_glPassThrough)(GLfloat token) = NULL;

static void (*next_glPixelMapfv)(GLenum map, GLint mapsize, const GLfloat * values) = NULL;

static void (*next_glPixelMapuiv)(GLenum map, GLint mapsize, const GLuint * values) = NULL;

static void (*next_glPixelMapusv)(GLenum map, GLint mapsize, const GLushort * values) = NULL;

static void (*next_glPixelStoref)(GLenum pname, GLfloat param) = NULL;

static void (*next_glPixelStorei)(GLenum pname, GLint param) = NULL;

static void (*next_glPixelTexGenParameterfSGIS)(GLenum pname, GLfloat param) = NULL;

static void (*next_glPixelTexGenParameterfvSGIS)(GLenum pname, const GLfloat * params) = NULL;

static void (*next_glPixelTexGenParameteriSGIS)(GLenum pname, GLint param) = NULL;

static void (*next_glPixelTexGenParameterivSGIS)(GLenum pname, const GLint * params) = NULL;

static void (*next_glPixelTexGenSGIX)(GLenum mode) = NULL;

static void (*next_glPixelTransferf)(GLenum pname, GLfloat param) = NULL;

static void (*next_glPixelTransferi)(GLenum pname, GLint param) = NULL;

static void (*next_glPixelTransformParameterfEXT)(GLenum target, GLenum pname, GLfloat param) = NULL;

static void (*next_glPixelTransformParameterfvEXT)(GLenum target, GLenum pname, const GLfloat * params) = NULL;

static void (*next_glPixelTransformParameteriEXT)(GLenum target, GLenum pname, GLint param) = NULL;

static void (*next_glPixelTransformParameterivEXT)(GLenum target, GLenum pname, const GLint * params) = NULL;

static void (*next_glPixelZoom)(GLfloat xfactor, GLfloat yfactor) = NULL;

static void (*next_glPointParameterfARB)(GLenum pname, GLfloat param) = NULL;

static void (*next_glPointParameterfEXT)(GLenum pname, GLfloat param) = NULL;

static void (*next_glPointParameterfSGIS)(GLenum pname, GLfloat param) = NULL;

static void (*next_glPointParameterfvARB)(GLenum pname, const GLfloat * params) = NULL;

static void (*next_glPointParameterfvEXT)(GLenum pname, const GLfloat * params) = NULL;

static void (*next_glPointParameterfvSGIS)(GLenum pname, const GLfloat * params) = NULL;

static void (*next_glPointSize)(GLfloat size) = NULL;

static GLint (*next_glPollAsyncSGIX)(GLuint * markerp) = NULL;

static GLint (*next_glPollInstrumentsSGIX)(GLint * marker_p) = NULL;

static void (*next_glPolygonMode)(GLenum face, GLenum mode) = NULL;

static void (*next_glPolygonOffset)(GLfloat factor, GLfloat units) = NULL;

static void (*next_glPolygonOffsetEXT)(GLfloat factor, GLfloat bias) = NULL;

static void (*next_glPolygonStipple)(const GLubyte * mask) = NULL;

static void (*next_glPopAttrib)() = NULL;

static void (*next_glPopClientAttrib)() = NULL;

static void (*next_glPopMatrix)() = NULL;

static void (*next_glPopName)() = NULL;

static void (*next_glPrioritizeTextures)(GLsizei n, const GLuint * textures, const GLclampf * priorities) = NULL;

static void (*next_glPrioritizeTexturesEXT)(GLsizei n, const GLuint * textures, const GLclampf * priorities) = NULL;

static void (*next_glProgramParameter4dNV)(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = NULL;

static void (*next_glProgramParameter4dvNV)(GLenum target, GLuint index, const GLdouble * params) = NULL;

static void (*next_glProgramParameter4fNV)(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = NULL;

static void (*next_glProgramParameter4fvNV)(GLenum target, GLuint index, const GLfloat * params) = NULL;

static void (*next_glProgramParameters4dvNV)(GLenum target, GLuint index, GLuint num, const GLdouble * params) = NULL;

static void (*next_glProgramParameters4fvNV)(GLenum target, GLuint index, GLuint num, const GLfloat * params) = NULL;

static void (*next_glPushAttrib)(GLbitfield mask) = NULL;

static void (*next_glPushClientAttrib)(GLbitfield mask) = NULL;

static void (*next_glPushMatrix)() = NULL;

static void (*next_glPushName)(GLuint name) = NULL;

static void (*next_glRasterPos2d)(GLdouble x, GLdouble y) = NULL;

static void (*next_glRasterPos2dv)(const GLdouble * v) = NULL;

static void (*next_glRasterPos2f)(GLfloat x, GLfloat y) = NULL;

static void (*next_glRasterPos2fv)(const GLfloat * v) = NULL;

static void (*next_glRasterPos2i)(GLint x, GLint y) = NULL;

static void (*next_glRasterPos2iv)(const GLint * v) = NULL;

static void (*next_glRasterPos2s)(GLshort x, GLshort y) = NULL;

static void (*next_glRasterPos2sv)(const GLshort * v) = NULL;

static void (*next_glRasterPos3d)(GLdouble x, GLdouble y, GLdouble z) = NULL;

static void (*next_glRasterPos3dv)(const GLdouble * v) = NULL;

static void (*next_glRasterPos3f)(GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glRasterPos3fv)(const GLfloat * v) = NULL;

static void (*next_glRasterPos3i)(GLint x, GLint y, GLint z) = NULL;

static void (*next_glRasterPos3iv)(const GLint * v) = NULL;

static void (*next_glRasterPos3s)(GLshort x, GLshort y, GLshort z) = NULL;

static void (*next_glRasterPos3sv)(const GLshort * v) = NULL;

static void (*next_glRasterPos4d)(GLdouble x, GLdouble y, GLdouble z, GLdouble w) = NULL;

static void (*next_glRasterPos4dv)(const GLdouble * v) = NULL;

static void (*next_glRasterPos4f)(GLfloat x, GLfloat y, GLfloat z, GLfloat w) = NULL;

static void (*next_glRasterPos4fv)(const GLfloat * v) = NULL;

static void (*next_glRasterPos4i)(GLint x, GLint y, GLint z, GLint w) = NULL;

static void (*next_glRasterPos4iv)(const GLint * v) = NULL;

static void (*next_glRasterPos4s)(GLshort x, GLshort y, GLshort z, GLshort w) = NULL;

static void (*next_glRasterPos4sv)(const GLshort * v) = NULL;

static void (*next_glReadBuffer)(GLenum mode) = NULL;

static void (*next_glReadInstrumentsSGIX)(GLint marker) = NULL;

static void (*next_glReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * pixels) = NULL;

static void (*next_glRectd)(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) = NULL;

static void (*next_glRectdv)(const GLdouble * v1, const GLdouble * v2) = NULL;

static void (*next_glRectf)(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) = NULL;

static void (*next_glRectfv)(const GLfloat * v1, const GLfloat * v2) = NULL;

static void (*next_glRecti)(GLint x1, GLint y1, GLint x2, GLint y2) = NULL;

static void (*next_glRectiv)(const GLint * v1, const GLint * v2) = NULL;

static void (*next_glRects)(GLshort x1, GLshort y1, GLshort x2, GLshort y2) = NULL;

static void (*next_glRectsv)(const GLshort * v1, const GLshort * v2) = NULL;

static void (*next_glReferencePlaneSGIX)(const GLdouble * equation) = NULL;

static GLint (*next_glRenderMode)(GLenum mode) = NULL;

static void (*next_glReplacementCodePointerSUN)(GLenum type, GLsizei stride, const GLvoid* * pointer) = NULL;

static void (*next_glReplacementCodeubSUN)(GLubyte code) = NULL;

static void (*next_glReplacementCodeubvSUN)(const GLubyte * code) = NULL;

static void (*next_glReplacementCodeuiColor3fVertex3fSUN)(GLenum rc, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glReplacementCodeuiColor3fVertex3fvSUN)(const GLenum * rc, const GLfloat * c, const GLfloat * v) = NULL;

static void (*next_glReplacementCodeuiColor4fNormal3fVertex3fSUN)(GLenum rc, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glReplacementCodeuiColor4fNormal3fVertex3fvSUN)(const GLenum * rc, const GLfloat * c, const GLfloat * n, const GLfloat * v) = NULL;

static void (*next_glReplacementCodeuiColor4ubVertex3fSUN)(GLenum rc, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glReplacementCodeuiColor4ubVertex3fvSUN)(const GLenum * rc, const GLubyte * c, const GLfloat * v) = NULL;

static void (*next_glReplacementCodeuiNormal3fVertex3fSUN)(GLenum rc, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glReplacementCodeuiNormal3fVertex3fvSUN)(const GLenum * rc, const GLfloat * n, const GLfloat * v) = NULL;

static void (*next_glReplacementCodeuiSUN)(GLuint code) = NULL;

static void (*next_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN)(GLenum rc, GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN)(const GLenum * rc, const GLfloat * tc, const GLfloat * c, const GLfloat * n, const GLfloat * v) = NULL;

static void (*next_glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN)(GLenum rc, GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN)(const GLenum * rc, const GLfloat * tc, const GLfloat * n, const GLfloat * v) = NULL;

static void (*next_glReplacementCodeuiTexCoord2fVertex3fSUN)(GLenum rc, GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glReplacementCodeuiTexCoord2fVertex3fvSUN)(const GLenum * rc, const GLfloat * tc, const GLfloat * v) = NULL;

static void (*next_glReplacementCodeuiVertex3fSUN)(GLenum rc, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glReplacementCodeuiVertex3fvSUN)(const GLenum * rc, const GLfloat * v) = NULL;

static void (*next_glReplacementCodeuivSUN)(const GLuint * code) = NULL;

static void (*next_glReplacementCodeusSUN)(GLushort code) = NULL;

static void (*next_glReplacementCodeusvSUN)(const GLushort * code) = NULL;

static void (*next_glRequestResidentProgramsNV)(GLsizei n, const GLuint * ids) = NULL;

static void (*next_glResetHistogram)(GLenum target) = NULL;

static void (*next_glResetHistogramEXT)(GLenum target) = NULL;

static void (*next_glResetMinmax)(GLenum target) = NULL;

static void (*next_glResetMinmaxEXT)(GLenum target) = NULL;

static void (*next_glResizeBuffersMESA)() = NULL;

static void (*next_glRotated)(GLdouble angle, GLdouble x, GLdouble y, GLdouble z) = NULL;

static void (*next_glRotatef)(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glSampleCoverage)(GLclampf value, GLboolean invert) = NULL;

static void (*next_glSampleCoverageARB)(GLclampf value, GLboolean invert) = NULL;

static void (*next_glSampleMapATI)(GLuint dst, GLuint interp, GLenum swizzle) = NULL;

static void (*next_glSampleMaskEXT)(GLclampf value, GLboolean invert) = NULL;

static void (*next_glSampleMaskSGIS)(GLclampf value, GLboolean invert) = NULL;

static void (*next_glSamplePatternEXT)(GLenum pattern) = NULL;

static void (*next_glSamplePatternSGIS)(GLenum pattern) = NULL;

static void (*next_glScaled)(GLdouble x, GLdouble y, GLdouble z) = NULL;

static void (*next_glScalef)(GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glScissor)(GLint x, GLint y, GLsizei width, GLsizei height) = NULL;

static void (*next_glSecondaryColor3bEXT)(GLbyte red, GLbyte green, GLbyte blue) = NULL;

static void (*next_glSecondaryColor3bvEXT)(const GLbyte * v) = NULL;

static void (*next_glSecondaryColor3dEXT)(GLdouble red, GLdouble green, GLdouble blue) = NULL;

static void (*next_glSecondaryColor3dvEXT)(const GLdouble * v) = NULL;

static void (*next_glSecondaryColor3fEXT)(GLfloat red, GLfloat green, GLfloat blue) = NULL;

static void (*next_glSecondaryColor3fvEXT)(const GLfloat * v) = NULL;

static void (*next_glSecondaryColor3iEXT)(GLint red, GLint green, GLint blue) = NULL;

static void (*next_glSecondaryColor3ivEXT)(const GLint * v) = NULL;

static void (*next_glSecondaryColor3sEXT)(GLshort red, GLshort green, GLshort blue) = NULL;

static void (*next_glSecondaryColor3svEXT)(const GLshort * v) = NULL;

static void (*next_glSecondaryColor3ubEXT)(GLubyte red, GLubyte green, GLubyte blue) = NULL;

static void (*next_glSecondaryColor3ubvEXT)(const GLubyte * v) = NULL;

static void (*next_glSecondaryColor3uiEXT)(GLuint red, GLuint green, GLuint blue) = NULL;

static void (*next_glSecondaryColor3uivEXT)(const GLuint * v) = NULL;

static void (*next_glSecondaryColor3usEXT)(GLushort red, GLushort green, GLushort blue) = NULL;

static void (*next_glSecondaryColor3usvEXT)(const GLushort * v) = NULL;

static void (*next_glSecondaryColorPointerEXT)(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) = NULL;

static void (*next_glSecondaryColorPointerListIBM)(GLint size, GLenum type, GLint stride, const GLvoid* * pointer, GLint ptrstride) = NULL;

static void (*next_glSelectBuffer)(GLsizei size, GLuint * buffer) = NULL;

static void (*next_glSeparableFilter2D)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * row, const GLvoid * column) = NULL;

static void (*next_glSeparableFilter2DEXT)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * row, const GLvoid * column) = NULL;

static void (*next_glSetFenceNV)(GLuint fence, GLenum condition) = NULL;

static void (*next_glSetFragmentShaderConstantATI)(GLuint dst, const GLfloat * value) = NULL;

static void (*next_glSetInvariantEXT)(GLuint id, GLenum type, const void * addr) = NULL;

static void (*next_glSetLocalConstantEXT)(GLuint id, GLenum type, const void * addr) = NULL;

static void (*next_glShadeModel)(GLenum mode) = NULL;

static void (*next_glShaderOp1EXT)(GLenum op, GLuint res, GLuint arg1) = NULL;

static void (*next_glShaderOp2EXT)(GLenum op, GLuint res, GLuint arg1, GLuint arg2) = NULL;

static void (*next_glShaderOp3EXT)(GLenum op, GLuint res, GLuint arg1, GLuint arg2, GLuint arg3) = NULL;

static void (*next_glSharpenTexFuncSGIS)(GLenum target, GLsizei n, const GLfloat * points) = NULL;

static void (*next_glSpriteParameterfSGIX)(GLenum pname, GLfloat param) = NULL;

static void (*next_glSpriteParameterfvSGIX)(GLenum pname, const GLfloat * params) = NULL;

static void (*next_glSpriteParameteriSGIX)(GLenum pname, GLint param) = NULL;

static void (*next_glSpriteParameterivSGIX)(GLenum pname, const GLint * params) = NULL;

static void (*next_glStartInstrumentsSGIX)() = NULL;

static void (*next_glStencilFunc)(GLenum func, GLint ref, GLuint mask) = NULL;

static void (*next_glStencilMask)(GLuint mask) = NULL;

static void (*next_glStencilOp)(GLenum fail, GLenum zfail, GLenum zpass) = NULL;

static void (*next_glStopInstrumentsSGIX)(GLint marker) = NULL;

static void (*next_glSwizzleEXT)(GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW) = NULL;

static void (*next_glTagSampleBufferSGIX)() = NULL;

static void (*next_glTangent3bEXT)(GLbyte tx, GLbyte ty, GLbyte tz) = NULL;

static void (*next_glTangent3bvEXT)(const GLbyte * v) = NULL;

static void (*next_glTangent3dEXT)(GLdouble tx, GLdouble ty, GLdouble tz) = NULL;

static void (*next_glTangent3dvEXT)(const GLdouble * v) = NULL;

static void (*next_glTangent3fEXT)(GLfloat tx, GLfloat ty, GLfloat tz) = NULL;

static void (*next_glTangent3fvEXT)(const GLfloat * v) = NULL;

static void (*next_glTangent3iEXT)(GLint tx, GLint ty, GLint tz) = NULL;

static void (*next_glTangent3ivEXT)(const GLint * v) = NULL;

static void (*next_glTangent3sEXT)(GLshort tx, GLshort ty, GLshort tz) = NULL;

static void (*next_glTangent3svEXT)(const GLshort * v) = NULL;

static void (*next_glTangentPointerEXT)(GLenum type, GLsizei stride, const GLvoid * pointer) = NULL;

static void (*next_glTbufferMask3DFX)(GLuint mask) = NULL;

static GLboolean (*next_glTestFenceNV)(GLuint fence) = NULL;

static void (*next_glTexBumpParameterfvATI)(GLenum pname, const GLfloat * param) = NULL;

static void (*next_glTexBumpParameterivATI)(GLenum pname, const GLint * param) = NULL;

static void (*next_glTexCoord1d)(GLdouble s) = NULL;

static void (*next_glTexCoord1dv)(const GLdouble * v) = NULL;

static void (*next_glTexCoord1f)(GLfloat s) = NULL;

static void (*next_glTexCoord1fv)(const GLfloat * v) = NULL;

static void (*next_glTexCoord1i)(GLint s) = NULL;

static void (*next_glTexCoord1iv)(const GLint * v) = NULL;

static void (*next_glTexCoord1s)(GLshort s) = NULL;

static void (*next_glTexCoord1sv)(const GLshort * v) = NULL;

static void (*next_glTexCoord2d)(GLdouble s, GLdouble t) = NULL;

static void (*next_glTexCoord2dv)(const GLdouble * v) = NULL;

static void (*next_glTexCoord2f)(GLfloat s, GLfloat t) = NULL;

static void (*next_glTexCoord2fColor3fVertex3fSUN)(GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glTexCoord2fColor3fVertex3fvSUN)(const GLfloat * tc, const GLfloat * c, const GLfloat * v) = NULL;

static void (*next_glTexCoord2fColor4fNormal3fVertex3fSUN)(GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glTexCoord2fColor4fNormal3fVertex3fvSUN)(const GLfloat * tc, const GLfloat * c, const GLfloat * n, const GLfloat * v) = NULL;

static void (*next_glTexCoord2fColor4ubVertex3fSUN)(GLfloat s, GLfloat t, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glTexCoord2fColor4ubVertex3fvSUN)(const GLfloat * tc, const GLubyte * c, const GLfloat * v) = NULL;

static void (*next_glTexCoord2fNormal3fVertex3fSUN)(GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glTexCoord2fNormal3fVertex3fvSUN)(const GLfloat * tc, const GLfloat * n, const GLfloat * v) = NULL;

static void (*next_glTexCoord2fVertex3fSUN)(GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glTexCoord2fVertex3fvSUN)(const GLfloat * tc, const GLfloat * v) = NULL;

static void (*next_glTexCoord2fv)(const GLfloat * v) = NULL;

static void (*next_glTexCoord2i)(GLint s, GLint t) = NULL;

static void (*next_glTexCoord2iv)(const GLint * v) = NULL;

static void (*next_glTexCoord2s)(GLshort s, GLshort t) = NULL;

static void (*next_glTexCoord2sv)(const GLshort * v) = NULL;

static void (*next_glTexCoord3d)(GLdouble s, GLdouble t, GLdouble r) = NULL;

static void (*next_glTexCoord3dv)(const GLdouble * v) = NULL;

static void (*next_glTexCoord3f)(GLfloat s, GLfloat t, GLfloat r) = NULL;

static void (*next_glTexCoord3fv)(const GLfloat * v) = NULL;

static void (*next_glTexCoord3i)(GLint s, GLint t, GLint r) = NULL;

static void (*next_glTexCoord3iv)(const GLint * v) = NULL;

static void (*next_glTexCoord3s)(GLshort s, GLshort t, GLshort r) = NULL;

static void (*next_glTexCoord3sv)(const GLshort * v) = NULL;

static void (*next_glTexCoord4d)(GLdouble s, GLdouble t, GLdouble r, GLdouble q) = NULL;

static void (*next_glTexCoord4dv)(const GLdouble * v) = NULL;

static void (*next_glTexCoord4f)(GLfloat s, GLfloat t, GLfloat r, GLfloat q) = NULL;

static void (*next_glTexCoord4fColor4fNormal3fVertex4fSUN)(GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = NULL;

static void (*next_glTexCoord4fColor4fNormal3fVertex4fvSUN)(const GLfloat * tc, const GLfloat * c, const GLfloat * n, const GLfloat * v) = NULL;

static void (*next_glTexCoord4fVertex4fSUN)(GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = NULL;

static void (*next_glTexCoord4fVertex4fvSUN)(const GLfloat * tc, const GLfloat * v) = NULL;

static void (*next_glTexCoord4fv)(const GLfloat * v) = NULL;

static void (*next_glTexCoord4i)(GLint s, GLint t, GLint r, GLint q) = NULL;

static void (*next_glTexCoord4iv)(const GLint * v) = NULL;

static void (*next_glTexCoord4s)(GLshort s, GLshort t, GLshort r, GLshort q) = NULL;

static void (*next_glTexCoord4sv)(const GLshort * v) = NULL;

static void (*next_glTexCoordPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) = NULL;

static void (*next_glTexCoordPointerEXT)(GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid * pointer) = NULL;

static void (*next_glTexCoordPointerListIBM)(GLint size, GLenum type, GLint stride, const GLvoid* * pointer, GLint ptrstride) = NULL;

static void (*next_glTexCoordPointervINTEL)(GLint size, GLenum type, const GLvoid* * pointer) = NULL;

static void (*next_glTexEnvf)(GLenum target, GLenum pname, GLfloat param) = NULL;

static void (*next_glTexEnvfv)(GLenum target, GLenum pname, const GLfloat * params) = NULL;

static void (*next_glTexEnvi)(GLenum target, GLenum pname, GLint param) = NULL;

static void (*next_glTexEnviv)(GLenum target, GLenum pname, const GLint * params) = NULL;

static void (*next_glTexFilterFuncSGIS)(GLenum target, GLenum filter, GLsizei n, const GLfloat * weights) = NULL;

static void (*next_glTexGend)(GLenum coord, GLenum pname, GLdouble param) = NULL;

static void (*next_glTexGendv)(GLenum coord, GLenum pname, const GLdouble * params) = NULL;

static void (*next_glTexGenf)(GLenum coord, GLenum pname, GLfloat param) = NULL;

static void (*next_glTexGenfv)(GLenum coord, GLenum pname, const GLfloat * params) = NULL;

static void (*next_glTexGeni)(GLenum coord, GLenum pname, GLint param) = NULL;

static void (*next_glTexGeniv)(GLenum coord, GLenum pname, const GLint * params) = NULL;

static void (*next_glTexImage1D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid * pixels) = NULL;

static void (*next_glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * pixels) = NULL;

static void (*next_glTexImage3D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid * pixels) = NULL;

static void (*next_glTexImage3DEXT)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid * pixels) = NULL;

static void (*next_glTexImage4DSGIS)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLint border, GLenum format, GLenum type, const GLvoid * pixels) = NULL;

static void (*next_glTexParameterf)(GLenum target, GLenum pname, GLfloat param) = NULL;

static void (*next_glTexParameterfv)(GLenum target, GLenum pname, const GLfloat * params) = NULL;

static void (*next_glTexParameteri)(GLenum target, GLenum pname, GLint param) = NULL;

static void (*next_glTexParameteriv)(GLenum target, GLenum pname, const GLint * params) = NULL;

static void (*next_glTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels) = NULL;

static void (*next_glTexSubImage1DEXT)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels) = NULL;

static void (*next_glTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels) = NULL;

static void (*next_glTexSubImage2DEXT)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels) = NULL;

static void (*next_glTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels) = NULL;

static void (*next_glTexSubImage3DEXT)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels) = NULL;

static void (*next_glTexSubImage4DSGIS)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint woffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLenum format, GLenum type, const GLvoid * pixels) = NULL;

static void (*next_glTextureColorMaskSGIS)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) = NULL;

static void (*next_glTextureLightEXT)(GLenum pname) = NULL;

static void (*next_glTextureMaterialEXT)(GLenum face, GLenum mode) = NULL;

static void (*next_glTextureNormalEXT)(GLenum mode) = NULL;

static void (*next_glTrackMatrixNV)(GLenum target, GLuint address, GLenum matrix, GLenum transform) = NULL;

static void (*next_glTranslated)(GLdouble x, GLdouble y, GLdouble z) = NULL;

static void (*next_glTranslatef)(GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glUnlockArraysEXT)() = NULL;

static void (*next_glUpdateObjectBufferATI)(GLuint buffer, GLuint offset, GLsizei size, const GLvoid * pointer, GLenum preserve) = NULL;

static void (*next_glVariantArrayObjectATI)(GLuint id, GLenum type, GLsizei stride, GLuint buffer, GLuint offset) = NULL;

static void (*next_glVariantPointerEXT)(GLuint id, GLenum type, GLuint stride, const void * addr) = NULL;

static void (*next_glVariantbvEXT)(GLuint id, const GLbyte * addr) = NULL;

static void (*next_glVariantdvEXT)(GLuint id, const GLdouble * addr) = NULL;

static void (*next_glVariantfvEXT)(GLuint id, const GLfloat * addr) = NULL;

static void (*next_glVariantivEXT)(GLuint id, const GLint * addr) = NULL;

static void (*next_glVariantsvEXT)(GLuint id, const GLshort * addr) = NULL;

static void (*next_glVariantubvEXT)(GLuint id, const GLubyte * addr) = NULL;

static void (*next_glVariantuivEXT)(GLuint id, const GLuint * addr) = NULL;

static void (*next_glVariantusvEXT)(GLuint id, const GLushort * addr) = NULL;

static void (*next_glVertex2d)(GLdouble x, GLdouble y) = NULL;

static void (*next_glVertex2dv)(const GLdouble * v) = NULL;

static void (*next_glVertex2f)(GLfloat x, GLfloat y) = NULL;

static void (*next_glVertex2fv)(const GLfloat * v) = NULL;

static void (*next_glVertex2i)(GLint x, GLint y) = NULL;

static void (*next_glVertex2iv)(const GLint * v) = NULL;

static void (*next_glVertex2s)(GLshort x, GLshort y) = NULL;

static void (*next_glVertex2sv)(const GLshort * v) = NULL;

static void (*next_glVertex3d)(GLdouble x, GLdouble y, GLdouble z) = NULL;

static void (*next_glVertex3dv)(const GLdouble * v) = NULL;

static void (*next_glVertex3f)(GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glVertex3fv)(const GLfloat * v) = NULL;

static void (*next_glVertex3i)(GLint x, GLint y, GLint z) = NULL;

static void (*next_glVertex3iv)(const GLint * v) = NULL;

static void (*next_glVertex3s)(GLshort x, GLshort y, GLshort z) = NULL;

static void (*next_glVertex3sv)(const GLshort * v) = NULL;

static void (*next_glVertex4d)(GLdouble x, GLdouble y, GLdouble z, GLdouble w) = NULL;

static void (*next_glVertex4dv)(const GLdouble * v) = NULL;

static void (*next_glVertex4f)(GLfloat x, GLfloat y, GLfloat z, GLfloat w) = NULL;

static void (*next_glVertex4fv)(const GLfloat * v) = NULL;

static void (*next_glVertex4i)(GLint x, GLint y, GLint z, GLint w) = NULL;

static void (*next_glVertex4iv)(const GLint * v) = NULL;

static void (*next_glVertex4s)(GLshort x, GLshort y, GLshort z, GLshort w) = NULL;

static void (*next_glVertex4sv)(const GLshort * v) = NULL;

static void (*next_glVertexArrayRangeNV)(GLsizei length, const GLvoid * pointer) = NULL;

static void (*next_glVertexAttrib1dNV)(GLuint index, GLdouble x) = NULL;

static void (*next_glVertexAttrib1dvNV)(GLuint index, const GLdouble * v) = NULL;

static void (*next_glVertexAttrib1fNV)(GLuint index, GLfloat x) = NULL;

static void (*next_glVertexAttrib1fvNV)(GLuint index, const GLfloat * v) = NULL;

static void (*next_glVertexAttrib1sNV)(GLuint index, GLshort x) = NULL;

static void (*next_glVertexAttrib1svNV)(GLuint index, const GLshort * v) = NULL;

static void (*next_glVertexAttrib2dNV)(GLuint index, GLdouble x, GLdouble y) = NULL;

static void (*next_glVertexAttrib2dvNV)(GLuint index, const GLdouble * v) = NULL;

static void (*next_glVertexAttrib2fNV)(GLuint index, GLfloat x, GLfloat y) = NULL;

static void (*next_glVertexAttrib2fvNV)(GLuint index, const GLfloat * v) = NULL;

static void (*next_glVertexAttrib2sNV)(GLuint index, GLshort x, GLshort y) = NULL;

static void (*next_glVertexAttrib2svNV)(GLuint index, const GLshort * v) = NULL;

static void (*next_glVertexAttrib3dNV)(GLuint index, GLdouble x, GLdouble y, GLdouble z) = NULL;

static void (*next_glVertexAttrib3dvNV)(GLuint index, const GLdouble * v) = NULL;

static void (*next_glVertexAttrib3fNV)(GLuint index, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glVertexAttrib3fvNV)(GLuint index, const GLfloat * v) = NULL;

static void (*next_glVertexAttrib3sNV)(GLuint index, GLshort x, GLshort y, GLshort z) = NULL;

static void (*next_glVertexAttrib3svNV)(GLuint index, const GLshort * v) = NULL;

static void (*next_glVertexAttrib4dNV)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = NULL;

static void (*next_glVertexAttrib4dvNV)(GLuint index, const GLdouble * v) = NULL;

static void (*next_glVertexAttrib4fNV)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = NULL;

static void (*next_glVertexAttrib4fvNV)(GLuint index, const GLfloat * v) = NULL;

static void (*next_glVertexAttrib4sNV)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) = NULL;

static void (*next_glVertexAttrib4svNV)(GLuint index, const GLshort * v) = NULL;

static void (*next_glVertexAttrib4ubNV)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) = NULL;

static void (*next_glVertexAttrib4ubvNV)(GLuint index, const GLubyte * v) = NULL;

static void (*next_glVertexAttribPointerNV)(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) = NULL;

static void (*next_glVertexAttribs1dvNV)(GLuint index, GLsizei n, const GLdouble * v) = NULL;

static void (*next_glVertexAttribs1fvNV)(GLuint index, GLsizei n, const GLfloat * v) = NULL;

static void (*next_glVertexAttribs1svNV)(GLuint index, GLsizei n, const GLshort * v) = NULL;

static void (*next_glVertexAttribs2dvNV)(GLuint index, GLsizei n, const GLdouble * v) = NULL;

static void (*next_glVertexAttribs2fvNV)(GLuint index, GLsizei n, const GLfloat * v) = NULL;

static void (*next_glVertexAttribs2svNV)(GLuint index, GLsizei n, const GLshort * v) = NULL;

static void (*next_glVertexAttribs3dvNV)(GLuint index, GLsizei n, const GLdouble * v) = NULL;

static void (*next_glVertexAttribs3fvNV)(GLuint index, GLsizei n, const GLfloat * v) = NULL;

static void (*next_glVertexAttribs3svNV)(GLuint index, GLsizei n, const GLshort * v) = NULL;

static void (*next_glVertexAttribs4dvNV)(GLuint index, GLsizei n, const GLdouble * v) = NULL;

static void (*next_glVertexAttribs4fvNV)(GLuint index, GLsizei n, const GLfloat * v) = NULL;

static void (*next_glVertexAttribs4svNV)(GLuint index, GLsizei n, const GLshort * v) = NULL;

static void (*next_glVertexAttribs4ubvNV)(GLuint index, GLsizei n, const GLubyte * v) = NULL;

static void (*next_glVertexBlendARB)(GLint count) = NULL;

static void (*next_glVertexBlendEnvfATI)(GLenum pname, GLfloat param) = NULL;

static void (*next_glVertexBlendEnviATI)(GLenum pname, GLint param) = NULL;

static void (*next_glVertexPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) = NULL;

static void (*next_glVertexPointerEXT)(GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid * pointer) = NULL;

static void (*next_glVertexPointerListIBM)(GLint size, GLenum type, GLint stride, const GLvoid* * pointer, GLint ptrstride) = NULL;

static void (*next_glVertexPointervINTEL)(GLint size, GLenum type, const GLvoid* * pointer) = NULL;

static void (*next_glVertexStream1dATI)(GLenum stream, GLdouble x) = NULL;

static void (*next_glVertexStream1dvATI)(GLenum stream, const GLdouble * coords) = NULL;

static void (*next_glVertexStream1fATI)(GLenum stream, GLfloat x) = NULL;

static void (*next_glVertexStream1fvATI)(GLenum stream, const GLfloat * coords) = NULL;

static void (*next_glVertexStream1iATI)(GLenum stream, GLint x) = NULL;

static void (*next_glVertexStream1ivATI)(GLenum stream, const GLint * coords) = NULL;

static void (*next_glVertexStream1sATI)(GLenum stream, GLshort x) = NULL;

static void (*next_glVertexStream1svATI)(GLenum stream, const GLshort * coords) = NULL;

static void (*next_glVertexStream2dATI)(GLenum stream, GLdouble x, GLdouble y) = NULL;

static void (*next_glVertexStream2dvATI)(GLenum stream, const GLdouble * coords) = NULL;

static void (*next_glVertexStream2fATI)(GLenum stream, GLfloat x, GLfloat y) = NULL;

static void (*next_glVertexStream2fvATI)(GLenum stream, const GLfloat * coords) = NULL;

static void (*next_glVertexStream2iATI)(GLenum stream, GLint x, GLint y) = NULL;

static void (*next_glVertexStream2ivATI)(GLenum stream, const GLint * coords) = NULL;

static void (*next_glVertexStream2sATI)(GLenum stream, GLshort x, GLshort y) = NULL;

static void (*next_glVertexStream2svATI)(GLenum stream, const GLshort * coords) = NULL;

static void (*next_glVertexStream3dATI)(GLenum stream, GLdouble x, GLdouble y, GLdouble z) = NULL;

static void (*next_glVertexStream3dvATI)(GLenum stream, const GLdouble * coords) = NULL;

static void (*next_glVertexStream3fATI)(GLenum stream, GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glVertexStream3fvATI)(GLenum stream, const GLfloat * coords) = NULL;

static void (*next_glVertexStream3iATI)(GLenum stream, GLint x, GLint y, GLint z) = NULL;

static void (*next_glVertexStream3ivATI)(GLenum stream, const GLint * coords) = NULL;

static void (*next_glVertexStream3sATI)(GLenum stream, GLshort x, GLshort y, GLshort z) = NULL;

static void (*next_glVertexStream3svATI)(GLenum stream, const GLshort * coords) = NULL;

static void (*next_glVertexStream4dATI)(GLenum stream, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = NULL;

static void (*next_glVertexStream4dvATI)(GLenum stream, const GLdouble * coords) = NULL;

static void (*next_glVertexStream4fATI)(GLenum stream, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = NULL;

static void (*next_glVertexStream4fvATI)(GLenum stream, const GLfloat * coords) = NULL;

static void (*next_glVertexStream4iATI)(GLenum stream, GLint x, GLint y, GLint z, GLint w) = NULL;

static void (*next_glVertexStream4ivATI)(GLenum stream, const GLint * coords) = NULL;

static void (*next_glVertexStream4sATI)(GLenum stream, GLshort x, GLshort y, GLshort z, GLshort w) = NULL;

static void (*next_glVertexStream4svATI)(GLenum stream, const GLshort * coords) = NULL;

static void (*next_glVertexWeightPointerEXT)(GLsizei size, GLenum type, GLsizei stride, const GLvoid * pointer) = NULL;

static void (*next_glVertexWeightfEXT)(GLfloat weight) = NULL;

static void (*next_glVertexWeightfvEXT)(const GLfloat * weight) = NULL;

static void (*next_glViewport)(GLint x, GLint y, GLsizei width, GLsizei height) = NULL;

static void (*next_glWeightPointerARB)(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) = NULL;

static void (*next_glWeightbvARB)(GLint size, const GLbyte * weights) = NULL;

static void (*next_glWeightdvARB)(GLint size, const GLdouble * weights) = NULL;

static void (*next_glWeightfvARB)(GLint size, const GLfloat * weights) = NULL;

static void (*next_glWeightivARB)(GLint size, const GLint * weights) = NULL;

static void (*next_glWeightsvARB)(GLint size, const GLshort * weights) = NULL;

static void (*next_glWeightubvARB)(GLint size, const GLubyte * weights) = NULL;

static void (*next_glWeightuivARB)(GLint size, const GLuint * weights) = NULL;

static void (*next_glWeightusvARB)(GLint size, const GLushort * weights) = NULL;

static void (*next_glWindowPos2dARB)(GLdouble x, GLdouble y) = NULL;

static void (*next_glWindowPos2dMESA)(GLdouble x, GLdouble y) = NULL;

static void (*next_glWindowPos2dvARB)(const GLdouble * v) = NULL;

static void (*next_glWindowPos2dvMESA)(const GLdouble * v) = NULL;

static void (*next_glWindowPos2fARB)(GLfloat x, GLfloat y) = NULL;

static void (*next_glWindowPos2fMESA)(GLfloat x, GLfloat y) = NULL;

static void (*next_glWindowPos2fvARB)(const GLfloat * v) = NULL;

static void (*next_glWindowPos2fvMESA)(const GLfloat * v) = NULL;

static void (*next_glWindowPos2iARB)(GLint x, GLint y) = NULL;

static void (*next_glWindowPos2iMESA)(GLint x, GLint y) = NULL;

static void (*next_glWindowPos2ivARB)(const GLint * v) = NULL;

static void (*next_glWindowPos2ivMESA)(const GLint * v) = NULL;

static void (*next_glWindowPos2sARB)(GLshort x, GLshort y) = NULL;

static void (*next_glWindowPos2sMESA)(GLshort x, GLshort y) = NULL;

static void (*next_glWindowPos2svARB)(const GLshort * v) = NULL;

static void (*next_glWindowPos2svMESA)(const GLshort * v) = NULL;

static void (*next_glWindowPos3dARB)(GLdouble x, GLdouble y, GLdouble z) = NULL;

static void (*next_glWindowPos3dMESA)(GLdouble x, GLdouble y, GLdouble z) = NULL;

static void (*next_glWindowPos3dvARB)(const GLdouble * v) = NULL;

static void (*next_glWindowPos3dvMESA)(const GLdouble * v) = NULL;

static void (*next_glWindowPos3fARB)(GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glWindowPos3fMESA)(GLfloat x, GLfloat y, GLfloat z) = NULL;

static void (*next_glWindowPos3fvARB)(const GLfloat * v) = NULL;

static void (*next_glWindowPos3fvMESA)(const GLfloat * v) = NULL;

static void (*next_glWindowPos3iARB)(GLint x, GLint y, GLint z) = NULL;

static void (*next_glWindowPos3iMESA)(GLint x, GLint y, GLint z) = NULL;

static void (*next_glWindowPos3ivARB)(const GLint * v) = NULL;

static void (*next_glWindowPos3ivMESA)(const GLint * v) = NULL;

static void (*next_glWindowPos3sARB)(GLshort x, GLshort y, GLshort z) = NULL;

static void (*next_glWindowPos3sMESA)(GLshort x, GLshort y, GLshort z) = NULL;

static void (*next_glWindowPos3svARB)(const GLshort * v) = NULL;

static void (*next_glWindowPos3svMESA)(const GLshort * v) = NULL;

static void (*next_glWindowPos4dMESA)(GLdouble x, GLdouble y, GLdouble z, GLdouble w) = NULL;

static void (*next_glWindowPos4dvMESA)(const GLdouble * v) = NULL;

static void (*next_glWindowPos4fMESA)(GLfloat x, GLfloat y, GLfloat z, GLfloat w) = NULL;

static void (*next_glWindowPos4fvMESA)(const GLfloat * v) = NULL;

static void (*next_glWindowPos4iMESA)(GLint x, GLint y, GLint z, GLint w) = NULL;

static void (*next_glWindowPos4ivMESA)(const GLint * v) = NULL;

static void (*next_glWindowPos4sMESA)(GLshort x, GLshort y, GLshort z, GLshort w) = NULL;

static void (*next_glWindowPos4svMESA)(const GLshort * v) = NULL;

static void (*next_glWriteMaskEXT)(GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW) = NULL;

static void (*next_glXBindSwapBarrierSGIX)(Display * dpy, GLXDrawable drawable, GLint barrier) = NULL;

static void (*next_glXChangeDrawableAttributes)(GLint drawable) = NULL;

static void (*next_glXChangeDrawableAttributesSGIX)(GLint drawable) = NULL;

static XVisualInfo * (*next_glXChooseVisual)(Display * dpy, GLint screen, GLint * attriblist) = NULL;

static void (*next_glXClientInfo)() = NULL;

static void (*next_glXCopyContext)(Display * dpy, GLXContext source, GLXContext dest, unsigned long mask) = NULL;

static GLXContext (*next_glXCreateContext)(Display * dpy, XVisualInfo * visual, GLXContext share_list, Bool direct) = NULL;

static GLXPbuffer (*next_glXCreateGLXPbufferSGIX)(Display * dpy, GLXFBConfig config, GLuint width, GLuint height, const GLint * attriblist) = NULL;

static GLXPixmap (*next_glXCreateGLXPixmap)(Display * dpy, XVisualInfo * visual, Pixmap pixmap) = NULL;

static void (*next_glXCreateGLXVideoSourceSGIX)(GLint dpy, GLint screen, GLint server, GLint path, GLint classt, GLint node) = NULL;

static GLXContext (*next_glXCreateNewContext)(Display * dpy, GLXFBConfig config, GLint render_type, GLXContext share_list, Bool direct) = NULL;

static GLXPbuffer (*next_glXCreatePbuffer)(Display * dpy, GLXFBConfig config, const GLint * attrib_list) = NULL;

static GLXPixmap (*next_glXCreatePixmap)(Display * dpy, GLXFBConfig config, Pixmap pixmap, const GLint * attriblist) = NULL;

static GLXWindow (*next_glXCreateWindow)(Display * dpy, GLXFBConfig config, Window window, const GLint * attrib_list) = NULL;

static void (*next_glXDestroyContext)(Display * dpy, GLXContext ctx) = NULL;

static void (*next_glXDestroyGLXPbufferSGIX)(Display * dpy, GLXPbuffer pbuffer) = NULL;

static void (*next_glXDestroyGLXPixmap)(Display * dpy, GLXPixmap pixmap) = NULL;

static void (*next_glXDestroyGLXVideoSourceSGIX)(GLint dpy, GLint glxvideosource) = NULL;

static void (*next_glXDestroyHyperpipeConfigSGIX)() = NULL;

static void (*next_glXDestroyPbuffer)(Display * dpy, GLXPbuffer pbuffer) = NULL;

static void (*next_glXDestroyPixmap)(Display * dpy, Pixmap pixmap) = NULL;

static void (*next_glXDestroyWindow)(Display * dpy, Window window) = NULL;

static void (*next_glXGetDrawableAttributes)(GLint drawable) = NULL;

static void (*next_glXGetDrawableAttributesSGIX)(GLint drawable) = NULL;

static GLXFBConfig * (*next_glXGetFBConfigs)(Display * dpy, GLint screen, GLint * nelements) = NULL;

static void (*next_glXGetVisualConfigs)() = NULL;

static void (*next_glXHyperpipeConfigSGIX)() = NULL;

static Bool (*next_glXIsDirect)(Display * dpy, GLXContext ctx) = NULL;

static void (*next_glXJoinSwapGroupSGIX)(Display * dpy, GLXDrawable drawable, GLXDrawable member) = NULL;

static Bool (*next_glXMakeContextCurrent)(Display * dpy, GLXDrawable drawdrawable, GLXDrawable readdrawable, GLXContext context) = NULL;

static Bool (*next_glXMakeCurrent)(Display * dpy, GLXDrawable drawable, GLXContext ctx) = NULL;

static void (*next_glXMakeCurrentReadSGI)(GLint drawable, GLint readdrawable, GLint context) = NULL;

static GLint (*next_glXQueryContext)(Display * dpy, GLXContext context, GLint attribute, GLint * value) = NULL;

static GLint (*next_glXQueryContextInfoEXT)(Display * dpy, GLXContext context, GLint attribute, GLint * value) = NULL;

static const char * (*next_glXQueryExtensionsString)(Display * dpy, GLint screen) = NULL;

static void (*next_glXQueryHyperpipeConfigSGIX)() = NULL;

static void (*next_glXQueryHyperpipeNetworkSGIX)() = NULL;

static Bool (*next_glXQueryMaxSwapBarriersSGIX)(Display * dpy, GLint screen, GLint * max) = NULL;

static const char * (*next_glXQueryServerString)(Display * dpy, GLint screen, GLint name) = NULL;

static Bool (*next_glXQueryVersion)(Display * dpy, GLint * major, GLint * minor) = NULL;

static void (*next_glXRender)() = NULL;

static void (*next_glXRenderLarge)() = NULL;

static void (*next_glXSwapBuffers)(Display * dpy, GLXDrawable drawable) = NULL;

static void (*next_glXSwapIntervalSGI)() = NULL;

static void (*next_glXUseXFont)(Font font, GLint first, GLint count, GLint list_base) = NULL;

static void (*next_glXVendorPrivate)() = NULL;

static void (*next_glXVendorPrivateWithReply)() = NULL;

static void (*next_glXWaitGL)() = NULL;

static void (*next_glXWaitX)() = NULL;

static void (*next_MPI_Finalize)() = NULL;



//void next2_glDisable(GLenum cap);

#endif
