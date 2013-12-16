
#ifdef __cplusplus
extern "C" {
#endif

void gr_init();
void gr_addVertex(float x, float y, float z);
void gr_texCoord(float x, float y, float z);
void gr_beginPrimitive(int type);
void gr_endPrimitive();
void gr_render();
void gr_setColor(float r, float g, float b, float a);
void gr_setColorub(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void gr_setBackgroundColor(float r, float g, float b, float a);
void gr_normal(float x,float y,float z);
void gr_materialfv(int face, int pname, float* params);
void gr_materialf(int face, int pname, float param);
void gr_materialiv(int face, int pname, int* params);
void gr_materiali(int face, int pname, int param);
void gr_translate(float x, float y, float z);
void gr_rotate(float angle, float x, float y, float z);
void gr_scale(float x, float y, float z);
void gr_newList(size_t list, int mode);
void gr_endList();
void gr_callList(int list);
void gr_deleteLists(GLuint list, GLsizei range);
void gr_enableClientState(GLenum st);
void gr_vertexPointer(GLint dim, GLenum type, GLsizei stride, const GLvoid* pointer);
void gr_colorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);
void gr_drawArrays(GLenum type, GLint first, GLsizei count);
void gr_drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
void gr_drawElements_internal(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, GLint first);
void gr_disableClientState(GLenum st);
void gr_pushMatrix();
void gr_popMatrix();
void gr_loadIdentity();
void gr_viewport(int x, int y, int width, int height);
void gr_lookAt(float ex,float ey, float ez, float lx,
		     float ly, float lz, float ux, float uy, float uz);
void gr_makeCurrent(unsigned long winID);
void gr_chooseVisual(XVisualInfo* info);
void gr_matrixMode(int mode);
void gr_multMatrixf(const float* m);
void gr_multMatrixd(const double* m);
void gr_loadMatrixf(const float* m);
void gr_loadMatrixd(const double* m);
void gr_clear(GLbitfield mask);

void gr_light(int light, int pname, float* params);
void gr_enable(int what);
void gr_disable(int what);

void gr_material(int pname, float* params);
void gr_frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble ar);
void gr_texImage1D(GLenum target, GLint level, GLint internalFormat, GLsizei width,
    GLint border, GLenum format, GLenum type, const GLvoid* data);
void gr_texImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height,
    GLint border, GLenum format, GLenum type, const GLvoid* data);
void gr_finalize();
void gr_lock(const int num);
void gr_unlock(const int num);

#ifdef __cplusplus
}
#endif

