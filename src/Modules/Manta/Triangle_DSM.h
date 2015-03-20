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

// Modified code from original author: Thiago Ize

/*
  For more information, please see: http://software.sci.utah.edu

  The MIT License

  Copyright (c) 2005
  Scientific Computing and Imaging Institute, University of Utah

  License for the specific language governing rights and limitations under
  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*/

#ifndef Triangle_DSM_h
#define Triangle_DSM_h

#include <Interface/Primitive.h>
//#include <Interface/RayPacket.h>
#include <Core/Geometry/Vector.h>
#include <Core/Geometry/Ray.h>
#include <Core/Geometry/BBox.h>
#include <Interface/Material.h>
#include <Interface/TexCoordMapper.h>

namespace Manta
{
  class Triangle_DSM : public Primitive, public TexCoordMapper
  {
  public:

    // Scratch pad structure for KenslerShirley Triangle.
    enum {
      SCRATCH_U = 0,
      SCRATCH_V,
      SCRATCH_LAST // Dependent classes may use this identifier to
                   // avoid conflicts.
    };

    Triangle_DSM() { }
    Triangle_DSM(const Vector &p1, const Vector &p2, const Vector &p3,
                 Material *mtl);
    Triangle_DSM(const Triangle_DSM &tri) {
      vertices[0] = tri.vertices[0];
      vertices[1] = tri.vertices[1];
      vertices[2] = tri.vertices[2];
      material = tri.material;
    }


    Triangle_DSM& operator=(const Triangle_DSM &tri) {
      vertices[0] = tri.vertices[0];
      vertices[1] = tri.vertices[1];
      vertices[2] = tri.vertices[2];
      material = tri.material;
      return *this;
    }

    virtual Triangle_DSM* clone(CloneDepth depth, Clonable* incoming=NULL);
    virtual InterpErr serialInterpolate(const std::vector<keyframe_t> &keyframes);

    virtual void preprocess(const PreprocessContext& context);

    virtual void setTexCoordMapper(const TexCoordMapper* new_tex) {
      //we always use ourselves as the TexCoordMapper
    }
    virtual void computeTexCoords2(const RenderContext&, RayPacket& rays) const;
    virtual void computeTexCoords3(const RenderContext& context, RayPacket& rays) const {
      computeTexCoords2(context, rays);
    }

    virtual void computeSurfaceDerivatives(const RenderContext&, RayPacket& rays) const;

    void intersect(const RenderContext& context, RayPacket& rays) const;

    void computeNormal(const RenderContext& context, RayPacket &rays) const;
    void computeGeometricNormal(const RenderContext& context, RayPacket& rays) const;

    virtual void computeBounds(const PreprocessContext& context,
                               BBox& bbox) const
    {
      bbox.extendByPoint(vertices[0]);
      bbox.extendByPoint(vertices[1]);
      bbox.extendByPoint(vertices[2]);
    }

  public:
    Vector vertices[3];
    Material *material;
  };
}

#endif
