// Copyright (c) NVIDIA Corporation. All rights reserved.

#ifndef NV_VERTEXBUFFER_H
#define NV_VERTEXBUFFER_H

#include <vector>

// class representing a buffer object
class nvBufferObject {
public:
	nvBufferObject(GLenum target, GLsizeiptrARB size, GLenum usage=GL_STATIC_DRAW_ARB)
		: m_target(target),
		  m_size(size),
		  m_usage(usage)
	{
		glGenBuffersARB(1, &m_id);
		Bind();
        glBufferDataARB(m_target, m_size, 0, m_usage);
	}

	~nvBufferObject() {
		glDeleteBuffersARB(1, &m_id);
	}

	void Bind() {
		glBindBufferARB(m_target, m_id);
	}

	void Unbind() {
		glBindBufferARB(m_target, 0);
	}

	void SetData(void *data) {
		Bind();
        glBufferDataARB(m_target, m_size, data, m_usage);
	}

	void *Map(GLenum access) {
		Bind();
        return glMapBufferARB(m_target, access);
	}

	bool Unmap() {
		Bind();
        return glUnmapBufferARB(m_target) == GL_TRUE;
	}

private:
	GLenum m_target;
	GLsizeiptrARB m_size;
	GLenum m_usage;
	GLuint m_id;
};


// extends nvBufferObject to represent a vertex array stored in a buffer object
class nvVertexAttribBuffer : public nvBufferObject {
public:
	nvVertexAttribBuffer(GLuint index, GLuint nverts, GLint size, GLenum type, GLboolean normalized=GL_FALSE, GLsizei stride=0, GLenum usage=GL_STATIC_DRAW_ARB)
		: m_index(index),
		  m_size(size),
		  m_type(type),
		  m_normalized(normalized),
		  m_stride(stride),
		  nvBufferObject(GL_ARRAY_BUFFER_ARB, nverts*size*GetTypeSize(type), usage)
	{
	}

	~nvVertexAttribBuffer()
	{
	}

	enum Attribute { POSITION=0, WEIGHT, NORMAL, COLOR0, COLOR1, FOGCOORD, TEXCOORD0=8 };

	int GetTypeSize(GLenum type) {
		switch(type) {
			case GL_FLOAT:
				return sizeof(float);
				break;
			case GL_INT:
				return sizeof(int);
				break;
			case GL_SHORT:
				return sizeof(short);
				break;
			default:
				fprintf(stderr, "Error: unsupported vertex type\n");
				return 0;
		}
	}

	void SetPointer() {
		Bind();
        glVertexAttribPointerARB(m_index, m_size, m_type, m_normalized, m_stride, 0);
    }

	void Enable() {
        glEnableVertexAttribArrayARB(m_index);   
	}

	void Disable() {
        glDisableVertexAttribArrayARB(m_index);   
	}

private:
	GLuint m_index;
	GLint m_size;
	GLenum m_type;
	GLboolean m_normalized;
	GLsizei m_stride;
};

// geometry buffer is a collection of vertex attributes plus an index buffer
class nvGeometryBuffer
{
public:
	nvGeometryBuffer(int nindices)
		: m_nindices(nindices)
	{
		m_index_buffer = new nvBufferObject(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(short)*nindices);
	}

	~nvGeometryBuffer()
	{
		delete m_index_buffer;
		for(unsigned int i=0; i<m_attrib.size(); i++) {
			delete m_attrib[i];
		}
	}

	void AddAttribute(nvVertexAttribBuffer *attrib) {
		m_attrib.push_back(attrib);
	}

    void SetPointers() {
		for(unsigned int i=0; i<m_attrib.size(); i++) {
			m_attrib[i]->SetPointer();
		}
    }

    void EnableArrays() {
		for(unsigned int i=0; i<m_attrib.size(); i++) {
			m_attrib[i]->Enable();
		}
    }

    void DisableArrays() {
		for(unsigned int i=0; i<m_attrib.size(); i++) {
			m_attrib[i]->Disable();
		}
    }

	void DrawElementsInstanced(GLenum mode, GLsizei instances)
    {
		m_index_buffer->Bind();
        glDrawElementsInstancedEXT(mode, m_nindices, GL_UNSIGNED_SHORT, 0, instances);
		m_index_buffer->Unbind();
	}

	void DrawElements(GLenum mode)
    {
		m_index_buffer->Bind();
        glDrawElements(mode, m_nindices, GL_UNSIGNED_SHORT, 0);
		m_index_buffer->Unbind();
	}

	nvBufferObject *GetIndexBuffer() { return m_index_buffer; }

private:
	int m_nverts, m_nindices;
	nvBufferObject *m_index_buffer;
	std::vector<nvVertexAttribBuffer *> m_attrib;
};

#endif
