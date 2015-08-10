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

#include "MDSMRenderable.h"
#include "MantaRenderer.h"
#include "MScene.h"
//#include "Work.h"
#include <Model/Primitives/KenslerShirleyTriangle.h>
#include <Model/Instances/Instance.h>
#include <Model/Materials/ThinDielectric.h>
#include <Model/Materials/Lambertian.h>
#include <Model/Textures/TexCoordTexture.h>

//typedef WaldTriangle TTYPE;  //HAS some problems with texturing!!!
typedef KenslerShirleyTriangle TTYPE;

  MDSMRenderable::MDSMRenderable(MDSMGeometryGenerator* gen)
  : Renderable(gen)
{
  _generator = gen;
  as = new DynBVH(DEBUG_MSGS);
  //    material = new Phong(*current_material);
  //material = NULL;
  //instance = new InstanceRT(as, MantaManager::singleton()->current_transform);
  _data = new MDSMData();
  _data->mesh = new Mesh_DSM();
  _data->group = new Group();
  _data->perVertexColors = false;
  //    _data->group->add(_data->mesh);
  //
  //  THIS IS A BAD HACK, GROUPS ARE NOT BEHAVING WELL WITH AS!  - NEED TO ADD TO GLURAY.CC:
  //
  // DynBVH* hack = new DynBVH(true);
  //addVertex(0,0,0);
  //addVertex(0,0,0);
  //addVertex(0,0,0);
  // hack->setGroup(_data->mesh);
  // _data->group->add(hack);
  //  AccelWork* work = new AccelWork(hack, "wee");
  //  MantaManager::singleton()->addWork(work);
  //  as->setGroup(_data->group);
  // PreprocessContext context(MantaManager::singleton()->rtrt, 0, 1, MantaManager::singleton()->lights);
  //   as->preprocess(context);
  as->setGroup(_data->mesh);
  //   _data->group->add(as);
  instance = new DirtyInstance(as, MantaManager::singleton()->current_transform);
  //instance = new InstanceRT(as, MantaManager::singleton()->current_transform);
  _data->num_prims = 0;
  gen->setData(_data);
}

MDSMRenderable::~MDSMRenderable()
{
  delete as;
  delete instance;
}

MDSMGeometryGeneratorVoid::MDSMGeometryGeneratorVoid()
{
}

MDSMGeometryGeneratorVoid::~MDSMGeometryGeneratorVoid()
{
}


MDSMGeometryGeneratorTriangles::~MDSMGeometryGeneratorTriangles()
{
}


void MDSMGeometryGeneratorTriangles::addVertex(Real x, Real y, Real z)
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

void MDSMGeometryGeneratorTriangles::addNormal(Real x, Real y, Real z)
{
#if 0
  Mesh* _mesh = _data->mesh;
  //_mesh->vertexNormals.push_back(Vector(x,y,z));
#endif
}

void MDSMGeometryGeneratorTriangles::addTextureCoord(Real u, Real v, Real w, Real z)
{
#if 0
  Mesh* _mesh = _data->mesh;
  _mesh->texCoords.push_back(Manta::Vector(u,v,w));
#endif
}


MDSMGeometryGeneratorTriangleStrip::~MDSMGeometryGeneratorTriangleStrip()
{
  // _mesh->texCoords.push_back(Manta::Vector(0.0,0.0,0.9));
  //_mesh->texCoords.push_back(Manta::Vector(0.0,0.0,0.9));
  // _mesh->vertexNormals.push_back(Manta::Vector(0.0, 1.0, 0.0));
}

void MDSMGeometryGeneratorTriangleStrip::addTextureCoord(Real u, Real v, Real w, Real z)
{
#if 0
    Mesh* _mesh = _data->mesh;
    _mesh->texCoords.push_back(Manta::Vector(u,v,w));
  // cout << "adding texture coordinate: " << u << v<< w << endl;
#endif
}

void MDSMGeometryGeneratorTriangleStrip::addVertex(Real x, Real y, Real z)
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


void MDSMGeometryGeneratorQuads::addVertex(Real x, Real y, Real z)
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

void MDSMGeometryGeneratorQuads::addTextureCoord(Real u, Real v, Real w, Real z)
{
#if 0
  Mesh* mesh = _data->mesh;
  mesh->texCoords.push_back(Manta::Vector(u,v,w));
#endif
}


void MDSMGeometryGeneratorQuadStrip::addVertex(Real x, Real y, Real z)
{
#if 0
  Mesh_DSM* _mesh = _data->mesh;
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
          Manta::Texture<Real>* refl = new Manta::Constant<Real>(0.0);
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


void MDSMGeometryGeneratorQuadStrip::addTextureCoord(Real u, Real v, Real w, Real z)
{
#if 0
  Mesh* _mesh = _data->mesh;
  _mesh->texCoords.push_back(Manta::Vector(u,v,w));
#endif
}

MDSMGeometryGeneratorLines::MDSMGeometryGeneratorLines()
{
  radius = 0.03;
}

MDSMGeometryGeneratorLines::~MDSMGeometryGeneratorLines()
{
  //group->shrinkTo(0, true);
}

void MDSMGeometryGeneratorLines::addVertex(Real x,Real y,Real z)
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


void MDSMGeometryGeneratorLineStrip::addVertex(Real x,Real y,Real z)
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

