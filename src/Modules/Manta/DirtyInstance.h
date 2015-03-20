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

#ifndef Manta_Model_DirtyInstance_h
#define Manta_Model_DirtyInstance_h

#include <Interface/Primitive.h>
#include <Interface/TexCoordMapper.h>
#include <Core/Geometry/AffineTransform.h>
#include <Model/Instances/InstanceMaterial.h>

namespace Manta {


  // Convenience struct to hold normal, texcoord, etc to avoid
  // stomping useful data in the scratchpad.
  struct InstanceShadingData2 {
    Vector normal;
    Vector geometricNormal;
    VectorT<Real, 2> texcoord2;
    // NOTE(boulos): When we update texture coordinates to be
    // separated add this one too.
    //
    Vector texcoord3;
    Vector surfDerivU;
    Vector surfDerivV;

    InstanceShadingData2(const Vector& normal,
                        const Vector& geometricNormal,
                        const VectorT<Real, 2>& tex2,
                        const Vector& tex3,
                        const Vector& dpdu,
                        const Vector& dpdv
                        )
      : normal(normal), geometricNormal(geometricNormal),
        texcoord2(tex2), texcoord3(tex3),
        surfDerivU(dpdu), surfDerivV(dpdv)
    {
    }
  };


  class DirtyInstance : public Primitive,
                   public InstanceMaterial,
                   public TexCoordMapper
  {
  public:
    DirtyInstance(Object* instance, const AffineTransform& transform);
    virtual ~DirtyInstance();

    virtual Primitive* clone(CloneDepth depth, Clonable* incoming);
    virtual InterpErr serialInterpolate(const std::vector<keyframe_t> &keyframes);

    // Functions for callbacks (must be pass by value)
    void setTransform(AffineTransform new_transform);

    Object* getInstance();
    const Object *getInstance() const;

    // Generic
    virtual void preprocess(const PreprocessContext&);
    virtual void computeBounds(const PreprocessContext& context,
                               BBox& bbox) const;

    // From Primitive
    virtual void intersect(const RenderContext& context, RayPacket& rays) const;
    virtual void computeNormal(const RenderContext& context, RayPacket& rays) const;
    virtual void computeGeometricNormal(const RenderContext& context, RayPacket& rays) const;
    virtual void setTexCoordMapper(const TexCoordMapper* new_tex);

    // From TexCoordMapper
    virtual void computeTexCoords2(const RenderContext& context,
                                   RayPacket& rays) const;
    virtual void computeTexCoords3(const RenderContext& context,
                                   RayPacket& rays) const;
    virtual void computeSurfaceDerivatives(const RenderContext& context,
                                           RayPacket& rays) const;

    virtual void addToUpdateGraph(ObjectUpdateGraph* graph,
                                  ObjectUpdateGraphNode* parent);

  private:
    Object* instance;
    const TexCoordMapper* tex;

    // Transformation and its inverse.
    AffineTransform transform;
    AffineTransform transform_inv;
    bool _dirty;

    DirtyInstance();
  };
}

#endif
