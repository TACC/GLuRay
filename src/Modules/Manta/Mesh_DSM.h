#ifndef Mesh_DSM_h
#define Mesh_DSM_h

#include <Core/Geometry/Vector.h>
#include <Core/Geometry/BBox.h>
#include <Interface/Material.h>
#include <Interface/RayPacket.h>
#include <Interface/TexCoordMapper.h>
#include <Model/Groups/Group.h>
#include <Model/Groups/Mesh.h>

#include <DistributedData.h>
#include <DSM_Data.h>
#include <Model/Primitives/Triangle_DSM.h>

#include <vector>
#include <fstream>

namespace Manta
{
  using namespace std;

  class Mesh_DSM : public Group, public DSM_Data {
  public:

    // Might be nice to create two versions: this one and another for meshes
    // with just a single material and so doesn't need the material index.
    struct TriangleData {
      Vector vertices[3];

#define USE_SINGLE_MATERIAL_MESH
#ifdef USE_SINGLE_MATERIAL_MESH
      static int materialIndex;
#else
      int materialIndex;
#endif

      TriangleData() { }

      TriangleData(const Mesh* mesh, size_t triangleID) {
        vertices[0] = mesh->getVertex(triangleID, 0);
        vertices[1] = mesh->getVertex(triangleID, 1);
        vertices[2] = mesh->getVertex(triangleID, 2);
        materialIndex = mesh->face_material[triangleID];
      }
    };

    // TriangleData ideally should be spatially coherent.  Can easily
    // approximate this by creating a BVH over the triangles and then writing
    // out the TriangleData using an in order traversal.
    DistributedData<TriangleData> tris;

    // We assume that we don't have millions of materials and so we can just
    // replicate this list across all the nodes.
    vector<Material*> materials;

    const Mesh* mesh; // used only to populate the mesh
    size_t size;

    bool readFromFile;
    mutable ifstream in;

    Mesh_DSM();
    virtual ~Mesh_DSM();

    void populateMesh(const TriangleData* triDatas, const Mesh* mesh);
    void populateMesh(const Mesh* mesh);

    virtual void getDatum(void* datum, size_t triID) const;
    virtual void getDatums(void *datums, size_t index, size_t num) const;

    bool saveToFile(const string& filenName);
    bool loadFromFile(const string& filenName);

//     virtual Mesh_DSM* clone(CloneDepth depth, Clonable* incoming=NULL);

//     virtual InterpErr serialInterpolate(const std::vector<keyframe_t> &keyframes);
//     virtual InterpErr parallelInterpolate(const std::vector<keyframe_t> &keyframes,
//                                            int proc, int numProc);
//     virtual bool isParallel() const { return true; }

    // These methods should not be used, instead use addTriangle.
    virtual void add(Object*);
    virtual void set( int, Object *);
    virtual void remove(Object*, bool);

    virtual void intersect(size_t triID, const RenderContext& context, RayPacket& rays);
    void intersect(size_t triID, size_t numTri, const RenderContext& context,
                   RayPacket& rays);
//     inline Mesh_DSMTriangle* get( size_t i ) {
//       ASSERT( i < objs.size() );
//       //For some reason static_cast doesn't work when I inline this
//       return reinterpret_cast<Mesh_DSMTriangle*>(objs[i]);
//     }
//     inline const Mesh_DSMTriangle* get( size_t i ) const {
//       ASSERT( i < objs.size() );
//       //For some reason static_cast doesn't work when I inline this
//       return reinterpret_cast<Mesh_DSMTriangle* const>(objs[i]);
//     }

//     virtual inline Vector getVertex( size_t tri_id, size_t which_vert, Real t = 0 ) const {
//       return vertices[vertex_indices[3*tri_id + which_vert]];
//     }

    //this only adds the triangle to the group. You still need to add
    //the vertices, materials, etc. to the mesh.
//     void addTriangle(Mesh_DSMTriangle *tri);

    virtual void computeBounds(const PreprocessContext& context, int proc, int numProcs) const;

    // You can't get access to the actual primitive, because it may not
    // actually exist.  You can get the bounds of it, though.
//     virtual BBox getBBox(unsigned int which);

    virtual void preprocess(const PreprocessContext& context);
  };
}

#endif //Mesh_DSM_h
