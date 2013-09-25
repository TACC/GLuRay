#include "RRenderable.h"
#include "RIVLManager.h"
#include "RScene.h"


 RRenderable::RRenderable(RGeometryGenerator* gen)
  : Renderable(gen)
{
  _generator = gen;
  _data = new RData();
  gen->setData(_data);
}

RRenderable::~RRenderable()
{
}

RGeometryGeneratorVoid::RGeometryGeneratorVoid()
{
}

RGeometryGeneratorVoid::~RGeometryGeneratorVoid()
{
}


RGeometryGeneratorTriangles::~RGeometryGeneratorTriangles()
{
}


void RGeometryGeneratorTriangles::addVertex(Manta::Real x, Manta::Real y, Manta::Real z)
{
#if 0
  Mesh* _mesh = _data->mesh;

  bool use_computed_normal = false; //TODO: make config option
  _mesh->vertices.push_back(Vector(x,y,z));
  // cout << "pushing normal: " << MantaManager::singleton()->current_normal << endl;
  //if (!use_computed_normal)
  //  _mesh->vertexNormals.push_back(MantaManager::singleton()->current_normal);
  size_t num_verts = _mesh->vertices.size();
  if (_mesh->materials.size() == 0 || _mesh->materials.back() != MantaManager::singleton()->current_material)
    _mesh->materials.push_back(MantaManager::singleton()->current_material);
  if (++_vertCounter > 2 && _vertCounter%3 == 0) {
    _data->num_prims++;
    /*static size_t prim_counter = 10000;
      static TTYPE* prims = NULL;
      if (++prim_counter >= 10000)
      {
      prims = new TTYPE[10000];
      prim_counter = 0;
      }
      TTYPE* prim = &prims[prim_counter];*/
    TTYPE* prim = new TTYPE();
    size_t base = num_verts-3;
    _mesh->vertex_indices.push_back(base);
    _mesh->vertex_indices.push_back(base+1);
    _mesh->vertex_indices.push_back(base+2);

    if (use_computed_normal){
      Vector n = Cross((_mesh->vertices[base+1]-_mesh->vertices[base]),(_mesh->vertices[base+2]-_mesh->vertices[base]));
      n.normalize();
      _mesh->vertexNormals.push_back(n);
      _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-1);
      _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-1);
      _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-1);
    }
    else {
      if (_mesh->vertexNormals.size() >= 3)
      {
        //   _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-3);
        //   _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-2);
        //   _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-1);
      }
      else
      {
        //      _mesh->vertexNormals.push_back(Cross((_mesh->vertices[base+1]-_mesh->vertices[base]),(_mesh->vertices[base+2]-_mesh->vertices[base])));
        //  _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-1);
        //  _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-1);
        //  _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-1);

      }
    }


    if (!_mesh->texCoords.empty() && _mesh->texCoords.size() >= 3)
    {
      base = _mesh->texCoords.size()-3;
      _mesh->texture_indices.push_back(base);
      _mesh->texture_indices.push_back(base+1);
      _mesh->texture_indices.push_back(base+2);
      /*} else if (!_mesh->texCoords.empty()) {
        base = _mesh->texCoords.size()-1;
        _mesh->texture_indices.push_back(base);
        _mesh->texture_indices.push_back(base);
        _mesh->texture_indices.push_back(base);
        } else*/
  }else{
    _mesh->texture_indices.push_back(Mesh::kNoTextureIndex);
    _mesh->texture_indices.push_back(Mesh::kNoTextureIndex);
    _mesh->texture_indices.push_back(Mesh::kNoTextureIndex);
  }
  _mesh->face_material.push_back(_mesh->materials.size()-1);

  _mesh->addTriangle(prim);
}
#endif
}

void RGeometryGeneratorTriangles::addNormal(Manta::Real x, Manta::Real y, Manta::Real z)
{
#if 0
  Mesh* _mesh = _data->mesh;
  //_mesh->vertexNormals.push_back(Vector(x,y,z));
#endif
}

void RGeometryGeneratorTriangles::addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z)
{
#if 0
  Mesh* _mesh = _data->mesh;
  _mesh->texCoords.push_back(Manta::Vector(u,v,w));
#endif
}


RGeometryGeneratorTriangleStrip::~RGeometryGeneratorTriangleStrip()
{
}

void RGeometryGeneratorTriangleStrip::addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z) {
#if 0
    Mesh* _mesh = _data->mesh;
    _mesh->texCoords.push_back(Manta::Vector(u,v,w));
  // cout << "adding texture coordinate: " << u << v<< w << endl;
#endif
}

void RGeometryGeneratorTriangleStrip::addVertex(Manta::Real x, Manta::Real y, Manta::Real z)
{
#if 0
  Mesh* _mesh = _data->mesh;
  _mesh->vertices.push_back(Vector(x,y,z));
  size_t num_verts = _mesh->vertices.size();
  //   _mesh->materials.push_back(MantaManager::singleton()->current_material);
  if (_mesh->materials.size() == 0 || _mesh->materials.back() != MantaManager::singleton()->current_material)
    _mesh->materials.push_back(MantaManager::singleton()->current_material);
  if (++_vertCounter > 2) {
    _data->num_prims++;
    TTYPE* prim = new TTYPE();
    size_t base = num_verts-3;
    _mesh->vertex_indices.push_back(base);
    _mesh->vertex_indices.push_back(base+1);
    _mesh->vertex_indices.push_back(base+2);

    if (!_mesh->texCoords.empty()) //TODO: support for non vertex colors
    {
      if (_mesh->texCoords.size() >= 3)
      {
        base = _mesh->texCoords.size()-3;
        _mesh->texture_indices.push_back(base);
        _mesh->texture_indices.push_back(base+1);
        _mesh->texture_indices.push_back(base+2);
        //  _mesh->normal_indices.push_back(0);
        //  _mesh->normal_indices.push_back(0);
        //  _mesh->normal_indices.push_back(0);
      }
      // cout << "tex coord: " << _mesh->texCoords[base] << _mesh->texCoords[base+1] << " " <<  _mesh->texCoords[base]  << endl;
    }
    /*  if (_mesh->vertexNormals.size() >= 3)
        {
        _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-3);
        _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-2);
        _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-1);
        }*/
    _mesh->face_material.push_back(_mesh->materials.size()-1);

    _mesh->addTriangle(prim);
  }
#endif
}


void RGeometryGeneratorQuads::addVertex(Manta::Real x, Manta::Real y, Manta::Real z)
{
#if 0
  Mesh* _mesh = _data->mesh;
  _mesh->vertices.push_back(Vector(x,y,z));
  size_t num_verts = _mesh->vertices.size();
  _vertCounter++;
  // _mesh->materials.push_back(MantaManager::singleton()->current_material);
  if (_mesh->materials.size() == 0 || _mesh->materials.back() != MantaManager::singleton()->current_material)
    _mesh->materials.push_back(MantaManager::singleton()->current_material);
  if (_vertCounter > 3 && _vertCounter%4 == 0) {
    _data->num_prims++;
    TTYPE* prim = new TTYPE();
    TTYPE* prim2 = new TTYPE();
    size_t base = num_verts-4;
    _mesh->vertex_indices.push_back(base);
    _mesh->vertex_indices.push_back(base+1);
    _mesh->vertex_indices.push_back(base+2);
    _mesh->vertex_indices.push_back(base);
    _mesh->vertex_indices.push_back(base+2);
    _mesh->vertex_indices.push_back(base+3);

    if (!_mesh->texCoords.empty() )
    {
      if (_mesh->texCoords.size() >= 4)
      {
        base = _mesh->texCoords.size()-4;
        _mesh->texture_indices.push_back(base);
        _mesh->texture_indices.push_back(base+1);
        _mesh->texture_indices.push_back(base+2);
        _mesh->texture_indices.push_back(base);
        _mesh->texture_indices.push_back(base+2);
        _mesh->texture_indices.push_back(base+3);
      }
    }
    _mesh->face_material.push_back(_mesh->materials.size()-1);
    _mesh->face_material.push_back(_mesh->materials.size()-1);
    if (_mesh->vertexNormals.size() >= 4)
    {
      _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-4);
      _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-3);
      _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-2);
      _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-4);
      _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-2);
      _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-1);
    } else{
      //TODO: this is wrong...
      /*         _mesh->vertexNormals.push_back(Cross((_mesh->vertices[base+1]-_mesh->vertices[base]),(_mesh->vertices[base+2]-_mesh->vertices[base])));
                 _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-1);
                 _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-1);
                 _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-1);
                 _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-1);
                 _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-1);
                 _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-1);
                 */
    }


    _mesh->addTriangle(prim);
    _mesh->addTriangle(prim2);
  }
#endif
}

void RGeometryGeneratorQuads::addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z)
{
#if 0
  Mesh* mesh = _data->mesh;
  mesh->texCoords.push_back(Manta::Vector(u,v,w));
#endif
}


void RGeometryGeneratorQuadStrip::addVertex(Manta::Real x, Manta::Real y, Manta::Real z)
{
#if 0
  Mesh* _mesh = _data->mesh;
  _mesh->vertices.push_back(Vector(x,y,z));
  size_t num_verts = _mesh->vertices.size();
  _vertCounter++;
  // _mesh->materials.push_back(MantaManager::singleton()->current_material);
  if (_mesh->materials.size() == 0 || _mesh->materials.back() != MantaManager::singleton()->current_material)
    _mesh->materials.push_back(MantaManager::singleton()->current_material);
  if (_vertCounter > 3 && _vertCounter%2 == 0) {
    _data->num_prims++;
    TTYPE* prim = new TTYPE();
    TTYPE* prim2 = new TTYPE();
    size_t base = num_verts-4;

    _mesh->vertex_indices.push_back(base);
    _mesh->vertex_indices.push_back(base+1);
    _mesh->vertex_indices.push_back(base+2);
    _mesh->vertex_indices.push_back(base+1);
    _mesh->vertex_indices.push_back(base+2);
    _mesh->vertex_indices.push_back(base+3);
    /*  _mesh->texCoords.push_back(Manta::Vector(.5,0.5,1.0));  //CD DEBUG...
        _mesh->texture_indices.push_back(_mesh->texCoords.size()-1);
        _mesh->texture_indices.push_back(_mesh->texCoords.size()-1);
        _mesh->texture_indices.push_back(_mesh->texCoords.size()-1);
        _mesh->texture_indices.push_back(_mesh->texCoords.size()-1);
        _mesh->texture_indices.push_back(_mesh->texCoords.size()-1);
        _mesh->texture_indices.push_back(_mesh->texCoords.size()-1);
        */

    if (_mesh->texCoords.size() >= 4)
    {
      base = _mesh->texCoords.size()-4;
      _mesh->texture_indices.push_back(base);
      _mesh->texture_indices.push_back(base+1);
      _mesh->texture_indices.push_back(base+2);
      _mesh->texture_indices.push_back(base+1);
      _mesh->texture_indices.push_back(base+2);
      _mesh->texture_indices.push_back(base+3);
    }
    else
    {
      //_mesh->texture_indices.push_back(Mesh::kNoTextureIndex);
      //_mesh->texture_indices.push_back(Mesh::kNoTextureIndex);
      //_mesh->texture_indices.push_back(Mesh::kNoTextureIndex);
      //_mesh->texture_indices.push_back(Mesh::kNoTextureIndex);
      //_mesh->texture_indices.push_back(Mesh::kNoTextureIndex);
      //_mesh->texture_indices.push_back(Mesh::kNoTextureIndex);
    }


    /*    Manta::Texture<Manta::Color>* tex = new Manta::TexCoordTexture();
          Manta::Texture<Manta::Color>* spec = new Manta::Constant<Manta::Color>(Manta::Color(Manta::RGB(0.5,.5,.5)));
          Manta::Texture<Manta::Real>* refl = new Manta::Constant<Manta::Real>(0.0);
          Manta::Material* mat = new Manta::Phong(tex, spec, 10, refl);

          _mesh->materials.push_back(mat);*/
    _mesh->face_material.push_back(_mesh->materials.size()-1);
    _mesh->face_material.push_back(_mesh->materials.size()-1);
    /*  _mesh->vertexNormals.push_back(Vector(0,1,0));

        _mesh->normal_indices.push_back(0);
        _mesh->normal_indices.push_back(0);
        _mesh->normal_indices.push_back(0);
        _mesh->normal_indices.push_back(0);
        _mesh->normal_indices.push_back(0);
        _mesh->normal_indices.push_back(0);
        */

    if (_mesh->vertexNormals.size() >= 4)
      {
      _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-4);
      _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-3);
      _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-2);
      _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-4);
      _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-2);
      _mesh->normal_indices.push_back(_mesh->vertexNormals.size()-1);
      }

    _mesh->addTriangle(prim);
    _mesh->addTriangle(prim2);
  }
#endif
}


void RGeometryGeneratorQuadStrip::addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z)
{
#if 0
  Mesh* _mesh = _data->mesh;
  _mesh->texCoords.push_back(Manta::Vector(u,v,w));
#endif
}

RGeometryGeneratorLines::RGeometryGeneratorLines()
{
  radius = 0.03;
}

RGeometryGeneratorLines::~RGeometryGeneratorLines()
{
}

void RGeometryGeneratorLines::addVertex(Manta::Real x,Manta::Real y,Manta::Real z)
{
#if 0
  Group* group = _data->group;
  _vertCounter++;
  Vector vertex(x,y,z);
  if (_vertCounter > 1 && _vertCounter%2 == 0) {
    _data->num_prims++;
    group->add(new Cylinder(MantaManager::singleton()->current_material, last_vertex, vertex, radius));
  }
  last_vertex = vertex;
#endif
}


void RGeometryGeneratorLineStrip::addVertex(Manta::Real x,Manta::Real y,Manta::Real z)
{
#if 0
  Group* group = _data->group;
  _vertCounter++;
  Vector vertex(x,y,z);
  if (_vertCounter > 1) {
    _data->num_prims++;
    group->add(new Cylinder(MantaManager::singleton()->current_material, last_vertex, vertex, radius));
  }
  last_vertex = vertex;
#endif
}
