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

#include <Mesh_DSM.h>
#include <Core/Exceptions/InternalError.h>
#include <Core/Persistent/ArchiveElement.h>
#include <Core/Util/Preprocessor.h>
#include <Interface/Context.h>
#include <Interface/MantaInterface.h>
#include <Model/Primitives/MeshTriangle.h>

#include <Model/Primitives/KenslerShirleyTriangle.h>
#include <Model/Primitives/Sphere.h>
#include <Model/Materials/Lambertian.h>

using namespace Manta;

extern int cacheFraction;

#ifdef USE_SINGLE_MATERIAL_MESH
int Mesh_DSM::TriangleData::materialIndex = 0;
#endif

Mesh_DSM::Mesh_DSM() : size(0), readFromFile(false)
{
}

Mesh_DSM::~Mesh_DSM()
{
}

void Mesh_DSM::populateMesh(const TriangleData* triDatas, const Mesh* mesh)
{
  this->mesh = mesh;
  materials = mesh->materials;
  size = mesh->size();

  const int triPerBlock = 226;
  const int numCacheEntries = cacheFraction>0?
    1*(size/triPerBlock+1) / cacheFraction : -1;
  tris.setupCache(triPerBlock, numCacheEntries, size, triDatas);
  tris.originalData = triDatas;

  saveToFile("out.tri");
}

void Mesh_DSM::populateMesh(const Mesh* mesh)
{
  this->mesh = mesh;
  materials = mesh->materials;
  size = mesh->size();

  const int triPerBlock = 110;
  const int numCacheEntries = cacheFraction>0?
    1*(size/triPerBlock+1) / cacheFraction : -1;

  tris.setupCache(triPerBlock, numCacheEntries, size, *this);
  tris.originalData = NULL;

  saveToFile("output.tri");
}

void Mesh_DSM::getDatum(void* datum, size_t triID) const
{
  TriangleData *triData = static_cast<TriangleData*>(datum);

  if (readFromFile) {
    in.seekg(sizeof(size_t) + triID*sizeof(TriangleData));
    in.read((char*) triData, sizeof(TriangleData));
  }
  else { // read from mesh
    *triData = TriangleData(mesh, triID);
  }
}

void Mesh_DSM::getDatums(void* datums, size_t triID, size_t num) const
{
  TriangleData *triData = static_cast<TriangleData*>(datums);

  if (readFromFile) {
//     static streampos lastPos = -1; // I'm a lazy programmer and made this static, yuck. FIXME!
    const streampos newPos = sizeof(size_t) + triID*sizeof(TriangleData);
//     if (lastPos != newPos) {
      in.seekg(newPos);
//     }
//     lastPos = newPos + streampos(num*sizeof(TriangleData));
    in.read((char*) triData, num*sizeof(TriangleData));
  }
  else { // read from mesh
    for (size_t i=0; i < num; ++i)
      triData[i] = TriangleData(mesh, triID+num);
  }
}

void Mesh_DSM::intersect(size_t triID, const RenderContext& context, RayPacket& rays)
{
  // For now we'll just create a triangle, but it might be a tiny bit faster
  // not to do this and instead have the actual triangle intersection code in here.

  // TODO: See if there is some way to keep track of what we have so that we
  // don't need to keep acquiring and releasing every time.

  const int blockID = triID / tris.datumsPerBlock;
  const TriangleData* block = tris.get_data(blockID, context.proc);
  const TriangleData &triData = block[triID - blockID*tris.datumsPerBlock];
  Triangle_DSM triangle(triData.vertices[0], triData.vertices[1], triData.vertices[2],
                        materials[triData.materialIndex]);
  triangle.intersect(context, rays);
  tris.release_data(blockID);
}

// Assume that the numTri are all adjacent in memory.  Doing the for loop in
// here gives about a 7% speedup since we don't have to get/release as many
// times.
void Mesh_DSM::intersect(size_t triID, size_t numTri, const RenderContext& context,
                         RayPacket& rays)
{
  // For now we'll just create a triangle, but it might be a tiny bit faster
  // not to do this and instead have the actual triangle intersection code in here.
#ifndef ALL_RESIDENT
  size_t blockID = triID / tris.datumsPerBlock;
  size_t blockStartingTriID = blockID*tris.datumsPerBlock;
  const TriangleData* block = tris.get_data(blockID, context.proc);

  for (size_t i=0; i < numTri; ++i) {
    size_t currTri = triID+i;
    if (currTri >= blockStartingTriID + tris.datumsPerBlock) {
      tris.release_data(blockID);
      ++blockID;
      blockStartingTriID+=tris.datumsPerBlock;
      block = tris.get_data(blockID, context.proc);

    }
#else
  const TriangleData* block = tris.localData;
  const size_t blockStartingTriID = 0;
  for (size_t i=0; i < numTri; ++i) {
    size_t currTri = triID+i;
#endif
    const TriangleData &triData = block[currTri - blockStartingTriID];
    Triangle_DSM triangle(triData.vertices[0], triData.vertices[1], triData.vertices[2],
                          materials[triData.materialIndex]);
    triangle.intersect(context, rays);
  }

#ifndef ALL_RESIDENT
  tris.release_data(blockID);
#endif
}

bool Mesh_DSM::saveToFile(const string& file)
{
  if (tris.myRank != 0)
    return true; // Only one node should write out this file.
  if (size_t(tris.rs_size*tris.datumsPerBlock) < size) {
    cout << "Cannot save to file the Mesh_DSM because we don't have all the data locally.\n";
    return false;
  }

  ofstream out(file.c_str(), ios::out | ios::binary);
  if (!out) return false;

  const size_t numTri = size;
  out.write((char*) &numTri, sizeof(numTri));
  out.write((char*) tris.localData, sizeof(TriangleData)*numTri);

  out.close();

  printf("Wrote mesh to file\n");

  return true;
}

bool Mesh_DSM::loadFromFile(const string& fileName)
{
  printf("Mesh_DSM loading from file\n");

  in.open(fileName.c_str(), ios::binary | ios::in);
  if (!in) {
    cerr << "Error loading Mesh from file: " << fileName << endl;
    return false;
  }
  in.read((char*) &size, sizeof(size));

  readFromFile = true;


  this->mesh = NULL;

  const int triPerBlock = 226;
  //8 threads rm_1iso, 1/32 cache for bvh and mesh.
  //56 -> upto 2.12fps 15-20k rgets, 340-400k total gets, 200ms
  //110 -> 2.26-2.34, 13-15k, 421-490-527k, 156-166-172ms
  //112 ->2.25-2.32-2.38 11k-16k, 141-207ms
  //113 -> 2.26-2.36, 11-13k, 374-389k, 147-157ms
  //114-> 2.23-2.34-2.60, 13k, 150-160ms
  //170 -> 2.52, 9.3-9.7-10.7k, 125-150ms
  //226 -> 2.53-2.64, 7.0k-7.7-8.1k, 93-100-128ms
  //227 -> 2.61-2.68, 7.3-7.5k, 482-531k, 100-115ms
  //284 -> 2.60-2.67, 5.9-7.5k, 346-371k, 106-120ms
  //341 -> 2.60-2.64-2.73, 6.7-7.7k 96-106-116ms
  const int numCacheEntries = cacheFraction>0 ?
    1*(size/triPerBlock+1) / cacheFraction : -1;
  //for (size_t i = 0; i < size; i++)
  //  objs.push_back(new Sphere(new Lambertian(Color(RGBColor(1,0,0))), Vector(0,0,i), 0.01));

  tris.setupCache(triPerBlock, numCacheEntries, size, *this);
  tris.originalData = NULL;

  in.close();

  printf("Mesh_DSM %d finished loading from file size: %d\n", tris.myRank, size);
  return true;
}

void Mesh_DSM::add(Object*)
{
  throw InternalError(string("Illegal call to ") + MANTA_FUNC);
}

void Mesh_DSM::set( int, Object *)
{
  throw InternalError(string("Illegal call to ") + MANTA_FUNC);
}

void Mesh_DSM::remove(Object*, bool)
{
  throw InternalError(string("Illegal call to ") + MANTA_FUNC);
}

void Mesh_DSM::computeBounds(const PreprocessContext& context,
                         int proc, int numProcs) const
{
//   if (proc == 0) {
//     this->bbox.reset();
//   }

//   BBox myBBox;

//   //Compute Bounding boxes in parallel
//   int size = vertices.size();
//   int start = proc*size/numProcs;
//   int end = (proc+1)*size/numProcs;
//   for (int i=start; i < end; ++i) {
//     myBBox.extendByPoint(vertices[i]);
//   }

//   //this barrier enforces that bbox has been initialized before
//   //threads start writing to it.
//   barrier.wait(numProcs);

//   mutex.lock();
//   this->bbox.extendByBox(myBBox);
//   mutex.unlock();

//   if (proc == 0) {
//     dirtybbox = false;
//   }

//   //Need to wait for other threads to finish computing bbox
//   barrier.wait(numProcs);
}

// BBox Mesh_DSM::getBBox(unsigned int which)
// {
//   const Vector &p1 = getVertex(which, 0);
//   const Vector &p2 = getVertex(which, 1);
//   const Vector &p3 = getVertex(which, 2);
//   BBox bbox(p1, p1);
//   bbox.extendByPoint(p2);
//   bbox.extendByPoint(p3);
//   return bbox;
// }

void Mesh_DSM::preprocess(const PreprocessContext& context)
{
  for (unsigned int i=0; i < materials.size(); ++i)
    materials[i]->preprocess(context);
   Group::preprocess(context);

#ifdef DSM_STATS
   if (context.proc == 0)
   context.manta_interface->registerParallelPreRenderCallback(
                        Callback::create(&tris, &DistributedData<TriangleData>::updateStats));
#endif

}

