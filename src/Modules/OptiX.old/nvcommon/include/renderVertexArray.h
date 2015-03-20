/*
  Render to vertex array class
  sgreen 2/2004

  Copyright (c) NVIDIA Corporation. All rights reserved.
*/

#ifndef RENDERVERTEXARRAY_H
#define RENDERVERTEXARRAY_H

#ifdef WIN32
#include <windows.h>
#endif
#include <gl/glew.h>

class RenderVertexArray {
public:
  RenderVertexArray(int nverts, GLint size, GLenum type = GL_FLOAT);
  ~RenderVertexArray();

  void LoadData(void *data);                // load vertex data from memory
  void Read(GLenum buffer, int w, int h, int offset=0);   // read vertex data from frame buffer
  void SetPointer(GLuint index, GLsizei stride=0, GLuint offset=0);

  GLuint getHandle() { return m_buffer; }

private:
    GLenum m_usage;     // vbo usage flag
    GLuint m_buffer;
    GLuint m_index;
    GLuint m_nverts;
    GLint m_size;       // size of attribute       
    GLenum m_format;    // readpixels image format
    GLenum m_type;      // FLOAT or HALF_FLOAT
    int m_bytes_per_component;
};

#endif
