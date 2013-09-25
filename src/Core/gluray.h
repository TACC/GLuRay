
#ifdef __cplusplus
extern "C" {
#endif

void gl2manta_init();
void gl2manta_addVertex(float x, float y, float z);
void gl2manta_texCoord(float x, float y, float z);
void gl2manta_beginPrimitive(int type);
void gl2manta_endPrimitive();
void gl2manta_render();
void gl2manta_setColor(float r, float g, float b, float a);
void gl2manta_setColorub(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void gl2manta_setBackgroundColor(float r, float g, float b, float a);
void gl2manta_normal(float x,float y,float z);
void gl2manta_materialfv(int face, int pname, float* params);
void gl2manta_materialf(int face, int pname, float param);
void gl2manta_materialiv(int face, int pname, int* params);
void gl2manta_materiali(int face, int pname, int param);
void gl2manta_translate(float x, float y, float z);
void gl2manta_rotate(float angle, float x, float y, float z);
void gl2manta_scale(float x, float y, float z);
void gl2manta_newList(size_t list, int mode);
void gl2manta_endList();
void gl2manta_callList(int list);
void gl2manta_deleteLists(GLuint list, GLsizei range);
void gl2manta_enableClientState(GLenum st);
void gl2manta_vertexPointer(GLint dim, GLenum type, GLsizei stride, const GLvoid* pointer);
void gl2manta_colorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);
void gl2manta_drawArrays(GLenum type, GLint first, GLsizei count);
void gl2manta_drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
void gl2manta_drawElements_internal(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, GLint first);
void gl2manta_disableClientState(GLenum st);
void gl2manta_pushMatrix();
void gl2manta_popMatrix();
void gl2manta_loadIdentity();
void gl2manta_viewport(int x, int y, int width, int height);
void gl2manta_lookAt(float ex,float ey, float ez, float lx,
		     float ly, float lz, float ux, float uy, float uz);
void gl2manta_makeCurrent(unsigned long winID);
void gl2manta_chooseVisual(XVisualInfo* info);
void gl2manta_matrixMode(int mode);
void gl2manta_multMatrixf(const float* m);
void gl2manta_multMatrixd(const double* m);
void gl2manta_loadMatrixf(const float* m);
void gl2manta_loadMatrixd(const double* m);
void gl2manta_clear(GLbitfield mask);

void gl2manta_light(int light, int pname, float* params);
void gl2manta_enable(int what);
void gl2manta_disable(int what);

void gl2manta_material(int pname, float* params);
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

