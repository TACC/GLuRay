// Copyright (c) NVIDIA Corporation. All rights reserved.

#ifndef NV_SHAPE_H
#define NV_SHAPE_H

#include "nvVertexBuffer.h"

class nvShape {
public:
	nvShape(GLenum prim, int nindices) : m_prim(prim) {
		m_geom = new nvGeometryBuffer(nindices);
	}

	~nvShape() {
		delete m_geom;
	}

	void Draw() {
		m_geom->SetPointers();
		m_geom->EnableArrays();
		m_geom->DrawElements(m_prim);
		m_geom->DisableArrays();
	};

	void DrawInstanced(int ninstances)
	{
		m_geom->SetPointers();
		m_geom->EnableArrays();
		m_geom->DrawElementsInstanced(m_prim, ninstances);
		m_geom->DisableArrays();
	}

	GLenum m_prim;
	nvGeometryBuffer *m_geom;
};

class nvTorusShape : public nvShape
{
public:
	nvTorusShape(float r, float R, int nsides, int rings)
		: nvShape(GL_QUADS, 4*rings*nsides)
	{
		int nverts = rings*(nsides+1)*2;
		nvVertexAttribBuffer *position_buffer = new nvVertexAttribBuffer(nvVertexAttribBuffer::POSITION, nverts, 3, GL_FLOAT);
		nvVertexAttribBuffer *normal_buffer = new nvVertexAttribBuffer(nvVertexAttribBuffer::NORMAL, nverts, 3, GL_FLOAT);
		m_geom->AddAttribute(position_buffer);
		m_geom->AddAttribute(normal_buffer);

		float *vptr= (float *) position_buffer->Map(GL_WRITE_ONLY_ARB);
        float *nptr= (float *) normal_buffer->Map(GL_WRITE_ONLY_ARB);

        // generate vertex and normal data
        int i, j;
        float theta, phi, theta1;
        float cosTheta, sinTheta;
        float cosTheta1, sinTheta1;
        float ringDelta, sideDelta;

        ringDelta = 2.0 * NV_PI / rings;
        sideDelta = 2.0 * NV_PI / nsides;

        theta = 0.0;
        cosTheta = 1.0;
        sinTheta = 0.0;
        for (i = rings - 1; i >= 0; i--) {
            theta1 = theta + ringDelta;
            cosTheta1 = cos(theta1);
            sinTheta1 = sin(theta1);
            phi = 0.0;
            for (j = nsides; j >= 0; j--) {
                float cosPhi, sinPhi, dist;

                phi += sideDelta;
                cosPhi = cos(phi);
                sinPhi = sin(phi);
                dist = R + r * cosPhi;

                *nptr++ = cosTheta1 * cosPhi;
                *nptr++ = -sinTheta1 * cosPhi;
                *nptr++ = sinPhi;

                *vptr++ = cosTheta1 * dist;
                *vptr++ = -sinTheta1 * dist;
                *vptr++ = r * sinPhi;

                *nptr++ = cosTheta * cosPhi;
                *nptr++ = -sinTheta * cosPhi;
                *nptr++ = sinPhi;

                *vptr++ = cosTheta * dist;
                *vptr++ = -sinTheta * dist;
                *vptr++ = r * sinPhi;
            }
            theta = theta1;
            cosTheta = cosTheta1;
            sinTheta = sinTheta1;
        }

        // unmap buffers
	    position_buffer->Unmap();
	    normal_buffer->Unmap();

        // create indices
        unsigned short *iptr= (unsigned short *) m_geom->GetIndexBuffer()->Map(GL_WRITE_ONLY_ARB);
        int v = 0;
        for (i = rings - 1; i >= 0; i--) {
            for (j = nsides; j >= 0; j--) {
                if (j > 0) {
                    *iptr++ = v;
                    *iptr++ = v+1;
                    *iptr++ = v+3;
                    *iptr++ = v+2;
                }
                v+=2;
            }
        }
        m_geom->GetIndexBuffer()->Unmap();
	}
};


class nvCubeShape : public nvShape
{
public:
	nvCubeShape(float s)
		: nvShape(GL_TRIANGLES, 6*2*3)
    {
        float v[][3] = {
            -s, -s, -s,  // 0
            s, -s, -s,   // 1
            s,  s, -s,   // 2
            -s,  s, -s,  // 3
            -s, -s, s,   // 4
            s, -s, s,    // 5
            s,  s, s,    // 6
            -s,  s, s,   // 7
        };

        float n[][3] = {
            -1, -1, -1,  // 0
            1, -1, -1,   // 1
            1,  1, -1,   // 2
            -1,  1, -1,  // 3
            -1, -1, 1,   // 4
            1, -1, 1,    // 5
            1,  1, 1,    // 6
            -1,  1, 1,   // 7
        };

        unsigned short indices[] = {
            0, 1, 2,
            2, 3, 0,
            1, 5, 6,
            6, 2, 1,
            5, 4, 7,
            7, 6, 5,
            4, 0, 3,
            3, 7, 4,
            1, 0, 4, 
            4, 5, 1,
            3, 2, 6,
            6, 7, 3,
        };

        int nverts = 8;
		nvVertexAttribBuffer *position_buffer = new nvVertexAttribBuffer(nvVertexAttribBuffer::POSITION, nverts, 3, GL_FLOAT);
		nvVertexAttribBuffer *normal_buffer = new nvVertexAttribBuffer(nvVertexAttribBuffer::NORMAL, nverts, 3, GL_FLOAT);
		m_geom->AddAttribute(position_buffer);
		m_geom->AddAttribute(normal_buffer);

		position_buffer->SetData(v);
		normal_buffer->SetData(n);
		m_geom->GetIndexBuffer()->SetData(indices);
    }
};

#endif
