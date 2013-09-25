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
