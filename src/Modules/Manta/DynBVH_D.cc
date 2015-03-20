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

#include <Core/Exceptions/InternalError.h>
#include <Core/Math/MiscMath.h>
#include <Core/Thread/Time.h>
#include <Core/Util/Preprocessor.h>
#include <Core/Util/UpdateGraph.h>
#include <Core/Persistent/ArchiveElement.h>
#include <Core/Persistent/MantaRTTI.h>
#include <Core/Persistent/stdRTTI.h>
#include <DynBVH_Parameters.h>
#include <Interface/Context.h>
#include <Interface/Task.h>
#include <Interface/InterfaceRTTI.h>
#include <Interface/MantaInterface.h>
#include <DynBVH_D.h>
#include <algorithm>
#include <deque>
#include <float.h>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdio.h>
#include <stdlib.h>

using namespace Manta;
using std::cerr;

#define TEST_MASKS 1
// these constants control the SAH cost model
const float BVH_C_isec = 10.f;
const float BVH_C_trav = 10.f;
// NOTE(boulos): In Ingo's paper he says 16 works better than 8, but
// I'm not sure for which models yet. For bunny it makes no
// difference.
const int BVH_num_samples = 16;

extern int cacheFraction;

#define LONGEST_AXIS 0

#include <Model/Groups/Mesh.h>
void WriteMeshSorted(Group* group, std::vector<int> ids, const char* filename);

void
DynBVH_D::printNode(int nodeID, int depth) const {
  BVHNode& node = nodes[nodeID];

  std::string indent;
  for (int i = 0; i < depth; i++) {
    indent += "  ";
  }

  cerr << indent << "NodeID = " << nodeID;

  if (node.isLeaf()) {
    cerr << " LEAF w/ " << node.children << " children.\n";
  } else {
    cerr << " INTR w/ bounds " << node.bounds << endl;
    printNode(node.child+0, depth+1);
    printNode(node.child+1, depth+1);
  }
}

DynBVH_D::~DynBVH_D()
{
  if (mesh_DSM)
    delete mesh_DSM;
  //  cerr << MANTA_FUNC << " called.\n";
}

void DynBVH_D::intersect(const RenderContext& context, RayPacket& rays) const
{
  bool debugFlag = rays.getFlag(RayPacket::DebugPacket);
  if (debugFlag) {
    //cerr << __func__ << " called\n";
    cerr << MANTA_FUNC << " called\n";
    cerr << "Rays are : \n" << rays << endl;
  }

#ifdef COLLECT_STATS
  stats[context.proc].nTotalRays += rays.end() - rays.begin();
  stats[context.proc].nTotalRaysInPacket += rays.end() - rays.begin();
  stats[context.proc].nTotalPackets++;
#endif


  rays.computeInverseDirections();
#if USE_DYNBVH_PORTS
  templatedTraverse(context, rays);
#else
  rays.computeSigns();

  // compute IntervalArithmetic Data
  IAData ia_data;
  for (int axis = 0; axis < 3; axis++ ) {
      ia_data.min_rcp[axis]     =  std::numeric_limits<float>::max();
      ia_data.max_rcp[axis]     = -std::numeric_limits<float>::max();
      ia_data.min_org[axis]     =  std::numeric_limits<float>::max();
      ia_data.max_org[axis]     = -std::numeric_limits<float>::max();
      ia_data.min_org_rcp[axis] =  std::numeric_limits<float>::max();
      ia_data.max_org_rcp[axis] = -std::numeric_limits<float>::max();
  }

#ifdef MANTA_SSE
  int b = (rays.begin() + 3) & ~3;
  int e = (rays.end()) & ~3;
  if (b >= e) {
    for (int ray = rays.begin(); ray < rays.end(); ray++ ) {
#if TEST_MASKS
      if (rays.rayIsMasked(ray)) continue;
#endif
      for (int axis = 0; axis < 3; axis++) {
        const Real new_rcp     = rays.getInverseDirection(ray, axis);
        const Real new_org     = rays.getOrigin(ray,axis);
        const Real new_org_rcp = new_org * new_rcp;

        ia_data.min_rcp[axis] = (ia_data.min_rcp[axis] < new_rcp) ? ia_data.min_rcp[axis] : new_rcp;
        ia_data.max_rcp[axis] = (ia_data.max_rcp[axis] < new_rcp) ? new_rcp : ia_data.max_rcp[axis];

        ia_data.min_org[axis] = (ia_data.min_org[axis] < new_org) ? ia_data.min_org[axis] : new_org;
        ia_data.max_org[axis] = (ia_data.max_org[axis] < new_org) ? new_org : ia_data.max_org[axis];

        ia_data.min_org_rcp[axis] = (ia_data.min_org_rcp[axis] < new_org_rcp) ?
          ia_data.min_org_rcp[axis] : new_org_rcp;
        ia_data.max_org_rcp[axis] = (ia_data.max_org_rcp[axis] < new_org_rcp) ?
          new_org_rcp : ia_data.max_org_rcp[axis];
      }
    }
  } else {
    for (int ray = rays.begin(); ray < b; ray++) {
#if TEST_MASKS
      if (rays.rayIsMasked(ray)) continue;
#endif
      for (int axis = 0; axis < 3; axis++) {
        const Real new_rcp     = rays.getInverseDirection(ray, axis);
        const Real new_org     = rays.getOrigin(ray,axis);
        const Real new_org_rcp = new_org * new_rcp;

        ia_data.min_rcp[axis] = (ia_data.min_rcp[axis] < new_rcp) ? ia_data.min_rcp[axis] : new_rcp;
        ia_data.max_rcp[axis] = (ia_data.max_rcp[axis] < new_rcp) ? new_rcp : ia_data.max_rcp[axis];

        ia_data.min_org[axis] = (ia_data.min_org[axis] < new_org) ? ia_data.min_org[axis] : new_org;
        ia_data.max_org[axis] = (ia_data.max_org[axis] < new_org) ? new_org : ia_data.max_org[axis];

        ia_data.min_org_rcp[axis] = (ia_data.min_org_rcp[axis] < new_org_rcp) ?
          ia_data.min_org_rcp[axis] : new_org_rcp;
        ia_data.max_org_rcp[axis] = (ia_data.max_org_rcp[axis] < new_org_rcp) ?
          new_org_rcp : ia_data.max_org_rcp[axis];
      }
    }
    __m128 min_rcp[3];
    __m128 max_rcp[3];
    __m128 min_org[3];
    __m128 max_org[3];
    __m128 min_org_rcp[3];
    __m128 max_org_rcp[3];
    // Copy current values
    for (int axis = 0; axis < 3; axis++) {
      min_rcp[axis] = _mm_set1_ps(ia_data.min_rcp[axis]);
      max_rcp[axis] = _mm_set1_ps(ia_data.max_rcp[axis]);
      min_org[axis] = _mm_set1_ps(ia_data.min_org[axis]);
      max_org[axis] = _mm_set1_ps(ia_data.max_org[axis]);
      min_org_rcp[axis] = _mm_set1_ps(ia_data.min_org_rcp[axis]);
      max_org_rcp[axis] = _mm_set1_ps(ia_data.max_org_rcp[axis]);
    }
    // Loop over all rays over all 3 axes (note change in order for
    // cache friendly walk down the directions and origins)
    for (int axis = 0; axis < 3; axis++) {
      for (int ray = b; ray < e; ray += 4) {
        __m128 new_rcp = _mm_load_ps(&(rays.data->inverseDirection[axis][ray]));
        __m128 new_org = _mm_load_ps(&(rays.data->origin[axis][ray]));
        __m128 new_org_rcp = _mm_mul_ps(new_org, new_rcp);

        min_rcp[axis] = _mm_min_ps(min_rcp[axis], new_rcp);
        max_rcp[axis] = _mm_max_ps(max_rcp[axis], new_rcp);
        min_org[axis] = _mm_min_ps(min_org[axis], new_org);
        max_org[axis] = _mm_max_ps(max_org[axis], new_org);
        min_org_rcp[axis] = _mm_min_ps(min_org_rcp[axis], new_org_rcp);
        max_org_rcp[axis] = _mm_max_ps(max_org_rcp[axis], new_org_rcp);
      }
    }
    // Copy the results back out
    for (int axis = 0; axis < 3; axis++) {
      ia_data.min_rcp[axis] = min4f(min_rcp[axis]);
      ia_data.max_rcp[axis] = max4f(max_rcp[axis]);

      ia_data.min_org[axis] = min4f(min_org[axis]);
      ia_data.max_org[axis] = max4f(max_org[axis]);

      ia_data.min_org_rcp[axis] = min4f(min_org_rcp[axis]);
      ia_data.max_org_rcp[axis] = max4f(max_org_rcp[axis]);
    }
    for (int ray = e; ray < rays.end(); ray++) {
#if TEST_MASKS
      if (rays.rayIsMasked(ray)) continue;
#endif
      for (int axis = 0; axis < 3; axis++) {
        const Real new_rcp     = rays.getInverseDirection(ray, axis);
        const Real new_org     = rays.getOrigin(ray,axis);
        const Real new_org_rcp = new_org * new_rcp;

        ia_data.min_rcp[axis] = (ia_data.min_rcp[axis] < new_rcp) ? ia_data.min_rcp[axis] : new_rcp;
        ia_data.max_rcp[axis] = (ia_data.max_rcp[axis] < new_rcp) ? new_rcp : ia_data.max_rcp[axis];

        ia_data.min_org[axis] = (ia_data.min_org[axis] < new_org) ? ia_data.min_org[axis] : new_org;
        ia_data.max_org[axis] = (ia_data.max_org[axis] < new_org) ? new_org : ia_data.max_org[axis];

        ia_data.min_org_rcp[axis] = (ia_data.min_org_rcp[axis] < new_org_rcp) ?
          ia_data.min_org_rcp[axis] : new_org_rcp;
        ia_data.max_org_rcp[axis] = (ia_data.max_org_rcp[axis] < new_org_rcp) ?
          new_org_rcp : ia_data.max_org_rcp[axis];
      }
    }
  }
#else
  for (int ray = rays.begin(); ray < rays.end(); ray++ ) {
#if TEST_MASKS
    if (rays.rayIsMasked(ray)) continue;
#endif
    for (int axis = 0; axis < 3; axis++) {
      const Real new_rcp     = rays.getInverseDirection(ray, axis);
      const Real new_org     = rays.getOrigin(ray,axis);
      const Real new_org_rcp = new_org * new_rcp;

      ia_data.min_rcp[axis] = (ia_data.min_rcp[axis] < new_rcp) ? ia_data.min_rcp[axis] : new_rcp;
      ia_data.max_rcp[axis] = (ia_data.max_rcp[axis] < new_rcp) ? new_rcp : ia_data.max_rcp[axis];

      ia_data.min_org[axis] = (ia_data.min_org[axis] < new_org) ? ia_data.min_org[axis] : new_org;
      ia_data.max_org[axis] = (ia_data.max_org[axis] < new_org) ? new_org : ia_data.max_org[axis];

      ia_data.min_org_rcp[axis] = (ia_data.min_org_rcp[axis] < new_org_rcp) ?
        ia_data.min_org_rcp[axis] : new_org_rcp;
      ia_data.max_org_rcp[axis] = (ia_data.max_org_rcp[axis] < new_org_rcp) ?
        new_org_rcp : ia_data.max_org_rcp[axis];
    }
  }
#endif

  int blockID = 0;
  BVHNode const* block = nodesDData.get_data(blockID, context.proc);

#ifndef USE_ONLY_TRIANGLE_DSM
  if (rays.data->hitPrimMPI[0] == NULL)
    for (int i=0; i < RayPacket::MaxSize; ++i)
      rays.data->hitPrimMPI[i] = new Triangle_DSM;
#else
  if (rays.data->hitPrimMPI == NULL)
    rays.data->setNextHitPrimMPI(context.proc);
#endif

#if 0 //single ray packets
#ifdef COLLECT_STATS
  stats[context.proc].nTotalPackets += rays.end()-rays.begin()-1;
#endif

  const int rays_per_packet = 1; // If we want to trace smaller packets.
  for (int i=rays.begin(); i < rays.end(); i+=rays_per_packet) {
    RayPacket subpacket(rays, i, Min(i+rays_per_packet, rays.end()));
    intersectNode(0, blockID, block, context, subpacket, ia_data);
  }
#else
  intersectNode(0, blockID, block, context, rays, ia_data);
#endif

  nodesDData.release_data(blockID);

#endif // dynbvh port or not
}

DynBVH_D::BVHNode const& DynBVH_D::getNode(int nodeID, int &blockID, BVHNode const* &block,
                                           const RenderContext& context) const
{
#ifdef ALL_RESIDENT
  return nodesDData.localData[nodeID];
#endif
  nodesDData.makeProgress(context.proc);

//   if (nodeID < nodesDData.sharedRS_size*nodesDData.datumsPerBlock) {
//     if (blockID != 0) {
//       nodesDData.release_data(blockID);
//       blockID=0;
//       block = nodesDData.get_data(0, context.proc);
//     }
//     return block[nodeID];
//   }

  int blockStartingNodeID = blockID*nodesDData.datumsPerBlock;
  if (nodeID < blockStartingNodeID ||
      nodeID >= blockStartingNodeID + nodesDData.datumsPerBlock) { // We are in a new block.

    nodesDData.release_data(blockID);
    // if numNodesInBlock is power of 2, do a bit shift.
    blockID = nodeID / nodesDData.datumsPerBlock;
    block = nodesDData.get_data(blockID, context.proc);
    blockStartingNodeID = blockID*nodesDData.datumsPerBlock;
   }

  return block[nodeID-blockStartingNodeID];
}

void DynBVH_D::intersectNode(int nodeID, int& blockID, BVHNode const* &block,
                             const RenderContext& context, RayPacket& rays,
                             const IAData& ia_data) const
{

  // watch out, we don't actually copy the node data.  node is only guaranteed
  // to point to valid data until another getNode() call is made!
  const BVHNode &node = getNode(nodeID, blockID, block, context);
  int firstActive = firstIntersects(node.bounds, rays, ia_data);

#ifdef COLLECT_STATS
  stats[context.proc].nTraversals++;
#endif

  if (firstActive != rays.end()) {
    if (node.isLeaf()) {
#ifdef COLLECT_STATS
      stats[context.proc].nIntersects += node.children;
      stats[context.proc].nLeavesVisited++;
#endif

      // we already know that one of the rays from begin to end hits the
      // object, so lastActive is going to find something we need not create a
      // subpacket to help it stop early

      // actually if we're just one ray it'll look more than it needs to since
      // it will reintersect the firstActive ray...
      int lastActive = lastIntersects(node.bounds, rays);

      // build a subpacket from firstActive to lastActive (inclusive, hence +1)
      RayPacket subpacket(rays, firstActive, lastActive+1);
#if 0
      for (int i = 0; i < node.children; i++ ) {
        const int object_id = object_ids[node.child+i];
        currGroup->get(object_id)->intersect(context,subpacket);
      }
#else
      mesh_DSM->intersect(node.child, node.children, context, subpacket);
#endif
    }
    else {
      // make a subpacket from the (possibly) new firstActive to the current end
      RayPacket subpacket(rays, firstActive, rays.end());

      // recurse
      int front_son = subpacket.getDirection(subpacket.begin(),
                                             static_cast<int>(node.axis)) > 0 ? 0 : 1;
      const int backNodeID = node.child+1-front_son;
      intersectNode(node.child+front_son, blockID, block, context, subpacket, ia_data);
      intersectNode(backNodeID, blockID, block, context, subpacket, ia_data);
    }
  }
}

// return the first index (between [rays.begin(),rays.end()]) which hits the box
int DynBVH_D::firstIntersects(const BBox& box, const RayPacket& rays, const IAData& ia_data)
{

  const bool anyHit = rays.getFlag(RayPacket::AnyHit);

  int rayBegin = rays.begin();
  int rayEnd = rays.end();

  for (; rayBegin < rayEnd; rayBegin++) {
#if TEST_MASKS
    if (rays.rayIsMasked(rayBegin)) continue;
#endif
    if (anyHit && rays.wasHit(rayBegin)) continue;
    break;
  }

#ifdef MANTA_SSE
  int b = (rayBegin + 3) & (~3);
  int e = rayEnd & (~3);
  if (b >=e) {
    for (int i = rayBegin; i < rayEnd; i++) {
#if TEST_MASKS
      if (rays.rayIsMasked(i)) continue;
#endif
      if (anyHit && rays.wasHit(i)) continue;

      __m128 t00 = _mm_mul_ss(_mm_sub_ss(_mm_set_ss(box[0][0]), _mm_set_ss(rays.getOrigin(i, 0))),
                              _mm_set_ss(rays.getInverseDirection(i, 0)));
      __m128 t01 = _mm_mul_ss(_mm_sub_ss(_mm_set_ss(box[1][0]), _mm_set_ss(rays.getOrigin(i, 0))),
                              _mm_set_ss(rays.getInverseDirection(i, 0)));
      __m128 tmin0 = _mm_max_ss(_mm_min_ss(t00, t01), _mm_set_ss(T_EPSILON));
      __m128 tmax0 = _mm_min_ss(_mm_max_ss(t00, t01), _mm_set_ss(rays.getMinT(i)));

      __m128 t10 = _mm_mul_ss(_mm_sub_ss(_mm_set_ss(box[0][1]), _mm_set_ss(rays.getOrigin(i, 1))),
                              _mm_set_ss(rays.getInverseDirection(i, 1)));
      __m128 t11 = _mm_mul_ss(_mm_sub_ss(_mm_set_ss(box[1][1]), _mm_set_ss(rays.getOrigin(i, 1))),
                              _mm_set_ss(rays.getInverseDirection(i, 1)));
      __m128 tmin1 = _mm_max_ss(_mm_min_ss(t10, t11), tmin0);
      __m128 tmax1 = _mm_min_ss(_mm_max_ss(t10, t11), tmax0);

      __m128 t20 = _mm_mul_ss(_mm_sub_ss(_mm_set_ss(box[0][2]), _mm_set_ss(rays.getOrigin(i, 2))),
                              _mm_set_ss(rays.getInverseDirection(i, 2)));
      __m128 t21 = _mm_mul_ss(_mm_sub_ss(_mm_set_ss(box[1][2]), _mm_set_ss(rays.getOrigin(i, 2))),
                              _mm_set_ss(rays.getInverseDirection(i, 2)));
      __m128 tmin2 = _mm_max_ss(_mm_min_ss(t20, t21), tmin1);
      __m128 tmax2 = _mm_min_ss(_mm_max_ss(t20, t21), tmax1);

      float tmin, tmax;
      _mm_store_ss(&tmin, tmin2);
      _mm_store_ss(&tmax, tmax2);
      if(tmin <= tmax){
        return i;
      }
    }
  } else {
    int i = rayBegin;
    {
      __m128 t00 = _mm_mul_ss(_mm_sub_ss(_mm_set_ss(box[0][0]), _mm_set_ss(rays.getOrigin(i, 0))),
                              _mm_set_ss(rays.getInverseDirection(i, 0)));
      __m128 t01 = _mm_mul_ss(_mm_sub_ss(_mm_set_ss(box[1][0]), _mm_set_ss(rays.getOrigin(i, 0))),
                              _mm_set_ss(rays.getInverseDirection(i, 0)));
      __m128 tmin0 = _mm_max_ss(_mm_min_ss(t00, t01), _mm_set_ss(T_EPSILON));
      __m128 tmax0 = _mm_min_ss(_mm_max_ss(t00, t01), _mm_set_ss(rays.getMinT(i)));

      __m128 t10 = _mm_mul_ss(_mm_sub_ss(_mm_set_ss(box[0][1]), _mm_set_ss(rays.getOrigin(i, 1))),
                              _mm_set_ss(rays.getInverseDirection(i, 1)));
      __m128 t11 = _mm_mul_ss(_mm_sub_ss(_mm_set_ss(box[1][1]), _mm_set_ss(rays.getOrigin(i, 1))),
                              _mm_set_ss(rays.getInverseDirection(i, 1)));
      __m128 tmin1 = _mm_max_ss(_mm_min_ss(t10, t11), tmin0);
      __m128 tmax1 = _mm_min_ss(_mm_max_ss(t10, t11), tmax0);

      __m128 t20 = _mm_mul_ss(_mm_sub_ss(_mm_set_ss(box[0][2]), _mm_set_ss(rays.getOrigin(i, 2))),
                              _mm_set_ss(rays.getInverseDirection(i, 2)));
      __m128 t21 = _mm_mul_ss(_mm_sub_ss(_mm_set_ss(box[1][2]), _mm_set_ss(rays.getOrigin(i, 2))),
                              _mm_set_ss(rays.getInverseDirection(i, 2)));
      __m128 tmin2 = _mm_max_ss(_mm_min_ss(t20, t21), tmin1);
      __m128 tmax2 = _mm_min_ss(_mm_max_ss(t20, t21), tmax1);

      float tmin, tmax;
      _mm_store_ss(&tmin, tmin2);
      _mm_store_ss(&tmax, tmax2);
      if(tmin <= tmax){
        return i;
      }
    }

    // try a frustum miss
    {
      float tmin_frustum = T_EPSILON;
      float tmax_frustum = FLT_MAX;

      for (int axis = 0; axis < 3; axis++) {
        // the subtraction is really (boxIA + -orgIA)
        // or boxIA + [-max_org, -min_org]
        // [box_min, box_max] + [-max_org, -min_org]
        float a = box[0][axis]-ia_data.max_org[axis];
        float b = box[1][axis]-ia_data.min_org[axis];

        // now for multiplication
        float ar0 = a * ia_data.min_rcp[axis];
        float ar1 = a * ia_data.max_rcp[axis];
        float br0 = b * ia_data.min_rcp[axis];
        float br1 = b * ia_data.max_rcp[axis];

        // [a,b] is valid intersection interval so a is min
        // and b is max t-value

        //a = std::min(ar0, std::min(ar1, std::min(br0, br1)));
        a = (br0 < br1) ? br0 : br1;
        a = (a   < ar1) ?   a : ar1;
        a = (a   < ar0) ?   a : ar0;

        //b = std::max(ar0, std::max(ar1, std::max(br0, br1)));
        b = (br0 < br1) ? br1 : br0;
        b = (b   < ar1) ? ar1 : b;
        b = (b   < ar0) ? ar0 : b;

        tmin_frustum = (tmin_frustum < a) ? a : tmin_frustum;
        tmax_frustum = (tmax_frustum > b) ? b : tmax_frustum;
      }

      // frustum exit
      if (tmin_frustum > tmax_frustum) {
        return rayEnd;
      }
    }

    if (i < b) i++; // Avoid redoing first ray, but only if we won't do it in SIMD

    // Scalar pickup loop
    for (; i < b; i++) {
#if TEST_MASKS
      if (rays.rayIsMasked(i)) continue;
#endif
      if (anyHit && rays.wasHit(i)) continue;
      float tmin = T_EPSILON;
      float tmax = rays.getMinT(i);

      for (int c = 0; c < 3; c++) {
        float t0 = (box[0][c] - rays.getOrigin(i,c)) * rays.getInverseDirection(i,c);
        float t1 = (box[1][c] - rays.getOrigin(i,c)) * rays.getInverseDirection(i,c);

        float near = (t0 < t1) ? t0 : t1;
        float far  = (t0 < t1) ? t1 : t0;
        tmin = (tmin < near) ? near : tmin; // max of tmin, near
        tmax = (far <  tmax) ? far : tmax;  // min of tmax, far
      }
      if (tmin <= tmax) {  // valid intersection
        return i;
      }
    }

    RayPacketData* data = rays.data;
    __m128 box_x0 = _mm_set1_ps(box[0][0]);
    __m128 box_x1 = _mm_set1_ps(box[1][0]);

    __m128 box_y0 = _mm_set1_ps(box[0][1]);
    __m128 box_y1 = _mm_set1_ps(box[1][1]);

    __m128 box_z0 = _mm_set1_ps(box[0][2]);
    __m128 box_z1 = _mm_set1_ps(box[1][2]);

    for(;i<e;i+=4) {
#if TEST_MASKS
      if (rays.groupIsMasked(i)) continue;
#endif
      // TODO; check if adding to valid_intersect whether groupIsMasked is faster.
      __m128 valid_intersect;
      if (anyHit) {
          valid_intersect = rays.wereNotHitSSE(i);
          if (getmask4(valid_intersect)==0) continue;
      }
      else
        valid_intersect = _mm_true;

      __m128 x0 = _mm_mul_ps(_mm_sub_ps(box_x0, _mm_load_ps(&data->origin[0][i])),
                             _mm_load_ps(&data->inverseDirection[0][i]));
      __m128 x1 = _mm_mul_ps(_mm_sub_ps(box_x1, _mm_load_ps(&data->origin[0][i])),
                             _mm_load_ps(&data->inverseDirection[0][i]));

      __m128 xmin = _mm_min_ps(x0,x1);
      __m128 xmax = _mm_max_ps(x0,x1);

      __m128 y0 = _mm_mul_ps(_mm_sub_ps(box_y0, _mm_load_ps(&data->origin[1][i])),
                             _mm_load_ps(&data->inverseDirection[1][i]));
      __m128 y1 = _mm_mul_ps(_mm_sub_ps(box_y1, _mm_load_ps(&data->origin[1][i])),
                             _mm_load_ps(&data->inverseDirection[1][i]));

      __m128 ymin = _mm_min_ps(y0,y1);
      __m128 ymax = _mm_max_ps(y0,y1);

      __m128 z0 = _mm_mul_ps(_mm_sub_ps(box_z0, _mm_load_ps(&data->origin[2][i])),
                             _mm_load_ps(&data->inverseDirection[2][i]));
      __m128 z1 = _mm_mul_ps(_mm_sub_ps(box_z1, _mm_load_ps(&data->origin[2][i])),
                             _mm_load_ps(&data->inverseDirection[2][i]));

      __m128 zmin = _mm_min_ps(z0,z1);
      __m128 zmax = _mm_max_ps(z0,z1);

      __m128 maximum_minimum = _mm_max_ps(xmin,_mm_max_ps(ymin,_mm_max_ps(zmin, _mm_set1_ps(T_EPSILON))));
      __m128 minimum_maximum = _mm_min_ps(xmax,_mm_min_ps(ymax,_mm_min_ps(zmax,_mm_load_ps(&data->minT[i]))));
      valid_intersect = and4(valid_intersect, _mm_cmple_ps(maximum_minimum,minimum_maximum));
      const int mask = _mm_movemask_ps(valid_intersect);

      if (mask) {
        // Breaking simd alignment in order to return the most exact packet
        // interval gives a performance benefit when ray packets are not
        // coherent wrt the current bvh bounds.  This clearly gives a benefit
        // for path tracing/ambient occlusion like packets, but also for ray
        // casting/hard shadows with high res meshes (small triangles compared
        // to packet size).  The penalty when this is not the case is small and
        // in those cases the frame rate is already really high, so we optimize
        // for the more useful case.
        if ( (mask&0x1) && !rays.rayIsMasked(i+0))
          return i;
        else if ( (mask&0x2) && !rays.rayIsMasked(i+1))
          return i+1;
        else if ( (mask&0x4) && !rays.rayIsMasked(i+2))
          return i+2;
        else if ( (mask&0x8) && !rays.rayIsMasked(i+3))
          return i+3;
      }
    }

    for(;i<rayEnd;i++) {
#if TEST_MASKS
      if (rays.rayIsMasked(i)) continue;
#endif
      if (anyHit && rays.wasHit(i)) continue;

      float tmin = T_EPSILON;
      float tmax = rays.getMinT(i);

      for (int c = 0; c < 3; c++) {
        float t0 = (box[0][c] - rays.getOrigin(i,c)) * rays.getInverseDirection(i,c);
        float t1 = (box[1][c] - rays.getOrigin(i,c)) * rays.getInverseDirection(i,c);

        float near = (t0 < t1) ? t0 : t1;
        float far  = (t0 < t1) ? t1 : t0;
        tmin = (tmin < near) ? near : tmin; // max of tmin, near
        tmax = (far <  tmax) ? far : tmax;  // min of tmax, far
      }
      if (tmin <= tmax) {  // valid intersection
        return i;
      }
    }
  }
  return rayEnd;
#else // NOT MANTA_SSE (scalar case)

  for (int i = rayBegin; i < rayEnd; i++) {

    // Note, the frustum test will always occur since the rayBegin is never
    // masked or anyhit hit.
#if TEST_MASKS
    if (rays.rayIsMasked(i)) continue;
#endif
    if (anyHit && rays.wasHit(i)) continue;

    float tmin = T_EPSILON;
    float tmax = rays.getMinT(i);

    for (int c = 0; c < 3; c++) {
      float t0 = (box[0][c] - rays.getOrigin(i,c)) * rays.getInverseDirection(i,c);
      float t1 = (box[1][c] - rays.getOrigin(i,c)) * rays.getInverseDirection(i,c);

      float near = (t0 < t1) ? t0 : t1;
      float far  = (t0 < t1) ? t1 : t0;
      tmin = (tmin < near) ? near : tmin; // max of tmin, near
      tmax = (far <  tmax) ? far : tmax;  // min of tmax, far
    }
    if (tmin <= tmax) {  // valid intersection
      return i;
    }

    if (i == rayBegin) {
      // try a frustum miss
      float tmin_frustum = 1e-5;
      float tmax_frustum = FLT_MAX;

      for (int axis = 0; axis < 3; axis++) {
        // the subtraction is really (boxIA + -orgIA)
        // or boxIA + [-max_org, -min_org]
        // [box_min, box_max] + [-max_org, -min_org]
        float a = box[0][axis]-ia_data.max_org[axis];
        float b = box[1][axis]-ia_data.min_org[axis];

        // now for multiplication
        float ar0 = a * ia_data.min_rcp[axis];
        float ar1 = a * ia_data.max_rcp[axis];
        float br0 = b * ia_data.min_rcp[axis];
        float br1 = b * ia_data.max_rcp[axis];

        // [a,b] is valid intersection interval so a is min
        // and b is max t-value

        //a = std::min(ar0, std::min(ar1, std::min(br0, br1)));
        a = (br0 < br1) ? br0 : br1;
        a = (a   < ar1) ?   a : ar1;
        a = (a   < ar0) ?   a : ar0;

        //b = std::max(ar0, std::max(ar1, std::max(br0, br1)));
        b = (br0 < br1) ? br1 : br0;
        b = (b   < ar1) ? ar1 : b;
        b = (b   < ar0) ? ar0 : b;

        tmin_frustum = (tmin_frustum < a) ? a : tmin_frustum;
        tmax_frustum = (tmax_frustum > b) ? b : tmax_frustum;
      }

      // frustum exit
      if (tmin_frustum > tmax_frustum) {
        return rayEnd;
      }
    }
  }
  return rayEnd;
#endif
}

// return the last index which hits the box
int DynBVH_D::lastIntersects(const BBox& box, const RayPacket& rays)
{
  const bool anyHit = rays.getFlag(RayPacket::AnyHit);

  int rayBegin = rays.begin();
  int rayEnd = rays.end();

  for (; rayBegin < rayEnd; rayEnd--) {
#if TEST_MASKS
    if (rays.rayIsMasked(rayEnd-1)) continue;
#endif
    if (anyHit && rays.wasHit(rayEnd-1)) continue;
    break;
  }

#ifdef MANTA_SSE
  int last_simd = rayEnd & (~3);
  int first_simd = (rayBegin + 3) & (~3);
  if (first_simd >= last_simd) {
    for (int i = rayEnd - 1; i > rayBegin; i--) {
#if TEST_MASKS
      if (rays.rayIsMasked(i)) continue;
#endif
      if (anyHit && rays.wasHit(i)) continue;

      float tmin = T_EPSILON;
      float tmax = rays.getMinT(i);

      for (int c = 0; c < 3; c++) {
        float t0 = (box[0][c] - rays.getOrigin(i,c)) * rays.getInverseDirection(i,c);
        float t1 = (box[1][c] - rays.getOrigin(i,c)) * rays.getInverseDirection(i,c);

        float near = (t0 < t1) ? t0 : t1;
        float far  = (t0 < t1) ? t1 : t0;
        tmin = (tmin < near) ? near : tmin; // max of tmin, near
        tmax = (far <  tmax) ? far : tmax;  // min of tmax, far
      }
      if (tmin <= tmax) {  // valid intersection
        return i;
      }
    }
  } else {
    int i = rayEnd;
    for (; i > last_simd;) {
      i--;
#if TEST_MASKS
      if (rays.rayIsMasked(i)) continue;
#endif
      if (anyHit && rays.wasHit(i)) continue;

      float tmin = T_EPSILON;
      float tmax = rays.getMinT(i);

      for (int c = 0; c < 3; c++) {
        float t0 = (box[0][c] - rays.getOrigin(i,c)) * rays.getInverseDirection(i,c);
        float t1 = (box[1][c] - rays.getOrigin(i,c)) * rays.getInverseDirection(i,c);

        float near = (t0 < t1) ? t0 : t1;
        float far  = (t0 < t1) ? t1 : t0;
        tmin = (tmin < near) ? near : tmin; // max of tmin, near
        tmax = (far <  tmax) ? far : tmax;  // min of tmax, far
      }
      if (tmin <= tmax) {  // valid intersection
        return i;
      }
    }

    RayPacketData* data = rays.data;
    __m128 box_x0 = _mm_set1_ps(box[0][0]);
    __m128 box_x1 = _mm_set1_ps(box[1][0]);

    __m128 box_y0 = _mm_set1_ps(box[0][1]);
    __m128 box_y1 = _mm_set1_ps(box[1][1]);

    __m128 box_z0 = _mm_set1_ps(box[0][2]);
    __m128 box_z1 = _mm_set1_ps(box[1][2]);

    for(;i>first_simd;) {
      i -= 4;
#if TEST_MASKS
      if (rays.groupIsMasked(i)) continue;
#endif
      __m128 valid_intersect;
      if (anyHit) {
          valid_intersect = rays.wereNotHitSSE(i);
          if (getmask4(valid_intersect)==0) continue;
      }
      else
        valid_intersect = _mm_true;

      __m128 x0 = _mm_mul_ps(_mm_sub_ps(box_x0, _mm_load_ps(&data->origin[0][i])),
                             _mm_load_ps(&data->inverseDirection[0][i]));
      __m128 x1 = _mm_mul_ps(_mm_sub_ps(box_x1, _mm_load_ps(&data->origin[0][i])),
                             _mm_load_ps(&data->inverseDirection[0][i]));

      __m128 xmin = _mm_min_ps(x0,x1);
      __m128 xmax = _mm_max_ps(x0,x1);

      __m128 y0 = _mm_mul_ps(_mm_sub_ps(box_y0, _mm_load_ps(&data->origin[1][i])),
                             _mm_load_ps(&data->inverseDirection[1][i]));
      __m128 y1 = _mm_mul_ps(_mm_sub_ps(box_y1, _mm_load_ps(&data->origin[1][i])),
                             _mm_load_ps(&data->inverseDirection[1][i]));

      __m128 ymin = _mm_min_ps(y0,y1);
      __m128 ymax = _mm_max_ps(y0,y1);

      __m128 z0 = _mm_mul_ps(_mm_sub_ps(box_z0, _mm_load_ps(&data->origin[2][i])),
                             _mm_load_ps(&data->inverseDirection[2][i]));
      __m128 z1 = _mm_mul_ps(_mm_sub_ps(box_z1, _mm_load_ps(&data->origin[2][i])),
                             _mm_load_ps(&data->inverseDirection[2][i]));

      __m128 zmin = _mm_min_ps(z0,z1);
      __m128 zmax = _mm_max_ps(z0,z1);

      __m128 maximum_minimum = _mm_max_ps(xmin,_mm_max_ps(ymin,_mm_max_ps(zmin, _mm_set1_ps(T_EPSILON))));
      __m128 minimum_maximum = _mm_min_ps(xmax,_mm_min_ps(ymax,_mm_min_ps(zmax,_mm_load_ps(&data->minT[i]))));
      valid_intersect = and4(valid_intersect, _mm_cmple_ps(maximum_minimum,minimum_maximum));

      const int mask = _mm_movemask_ps(valid_intersect);

      if (mask) {
        if ((mask&0x8) && !rays.rayIsMasked(i+3))
          return i+3;
        else if ( (mask&0x4) && !rays.rayIsMasked(i+2))
          return i+2;
        else if ( (mask&0x2) && !rays.rayIsMasked(i+1))
          return i+1;
        else if ( (mask&0x1) && !rays.rayIsMasked(i))
          return i;
      }
    }

    for (; i > rayBegin;) {
      i--;
      //if (rays.rayIsMasked(i)) continue;
      if (anyHit && rays.wasHit(i)) continue;

      float tmin = T_EPSILON;
      float tmax = rays.getMinT(i);

      for (int c = 0; c < 3; c++) {
        float t0 = (box[0][c] - rays.getOrigin(i,c)) * rays.getInverseDirection(i,c);
        float t1 = (box[1][c] - rays.getOrigin(i,c)) * rays.getInverseDirection(i,c);

        float near = (t0 < t1) ? t0 : t1;
        float far  = (t0 < t1) ? t1 : t0;
        tmin = (tmin < near) ? near : tmin; // max of tmin, near
        tmax = (far <  tmax) ? far : tmax;  // min of tmax, far
      }
      if (tmin <= tmax) {  // valid intersection
        return i;
      }
    }
  }
#else
  for (int i = rayEnd - 1; i > rayBegin; i--) {
    //if (rays.rayIsMasked(i)) continue;
      if (anyHit && rays.wasHit(i)) continue;

    float tmin = T_EPSILON;
    float tmax = rays.getMinT(i);

    for (int c = 0; c < 3; c++) {
      float t0 = (box[0][c] - rays.getOrigin(i,c)) * rays.getInverseDirection(i,c);
      float t1 = (box[1][c] - rays.getOrigin(i,c)) * rays.getInverseDirection(i,c);

      float near = (t0 < t1) ? t0 : t1;
      float far  = (t0 < t1) ? t1 : t0;
      tmin = (tmin < near) ? near : tmin; // max of tmin, near
      tmax = (far <  tmax) ? far : tmax;  // min of tmax, far
    }
    if (tmin <= tmax) {  // valid intersection
      return i;
    }
  }
#endif
  return rayBegin;
}

void DynBVH_D::setGroup(Group* new_group) {
  if (new_group != currGroup)
    group_changed = true;
  currGroup = new_group;
}

Group* DynBVH_D::getGroup() const {
  return currGroup;
}

void DynBVH_D::groupDirty()
{
  group_changed = true;
}

void DynBVH_D::addToUpdateGraph(ObjectUpdateGraph* graph,
                              ObjectUpdateGraphNode* parent) {
  cerr << MANTA_FUNC << endl;
  ObjectUpdateGraphNode* node = graph->insert(this, parent);
  getGroup()->addToUpdateGraph(graph, node);
}

void DynBVH_D::preprocess(const PreprocessContext& context)
{
  //cerr << MANTA_FUNC << endl;
  // First preprocess the underlying group (so for example the
  // positions of underlying WaldTriangles are correct)

  if (currGroup) {
//     currGroup->preprocess(context);

    if (context.isInitialized()) {
      // Call rebuild (may call update underneath)
      rebuild(context.proc, context.numProcs);

      if (context.proc == 0)
        setupDSM();//allocate();
      //printNode(0, 0);
      barrier.wait(context.numProcs);
    }

    // NOTE(boulos): We allow rebuild to set the group_changed flag so
    // that you're not required to call preprocess in order to do an
    // update/rebuild.
  }

  if (context.isInitialized())
    mesh_DSM->preprocess(context);

#ifdef COLLECT_STATS
  context.manta_interface->registerParallelPreRenderCallback(
                                Callback::create(this, &DynBVH_D::updateStats));
#endif

#ifdef DSM_STATS
  context.manta_interface->registerParallelPreRenderCallback(
                   Callback::create(&nodesDData, &DistributedData<BVHNode>::updateStats));
#endif
}

int DynBVH_D::partitionObjects(int objBegin, int objEnd, int axis, float position) const {
  //cerr << MANTA_FUNC << " begin = " << objBegin << ", end = " << objEnd << endl;
  int first = objBegin;
  int last  = objEnd;
  --first;
  while (1) {
    for (++first; first < last; first++) {
      if (obj_centroids[object_ids[first]][axis] >= position)
        break;
    }

    for(--last; first < last; --last) {
      if (obj_centroids[object_ids[last]][axis] < position)
        break;
    }

    if (first < last) {
      // Swap first and last
      int temp = object_ids[first];
      object_ids[first] = object_ids[last];
      object_ids[last]  = temp;
    } else {
      return first;
    }
  }
  // To quiet warnings
  return -1;
}

void DynBVH_D::update(int proc, int numProcs) {
  PreprocessContext context;
//   parallelUpdateBounds(context, proc, numProcs);
  // TODO(boulos): Wait until everyone has gone through update to
  // disable group_changed (requires another barrier)
  if (proc == 0)
    group_changed = false;
}

void DynBVH_D::allocate() const {
printf("allocate - currgroupsize: %d nodes: %d\n", currGroup->size(), nodes.size());
 if(2*currGroup->size() > nodes.size()) {
   // Note: This code is not run if we load the bvh from file.
    nodes.resize(2*currGroup->size());
    printf("allocate resized nodes: %d\n", nodes.size());
    subtree_size.resize(2*currGroup->size());
    object_ids.resize(currGroup->size());
    // TODO(boulos): Free these after construction? or keep around
    // for rebuild?
    obj_bounds.resize(currGroup->size());
    obj_centroids.resize(currGroup->size());
  }
}

void DynBVH_D::setupDSM()
{
   // Setup distributed mesh if we don't already have one.
   if (dynamic_cast<Mesh_DSM*>(currGroup)) {
     mesh_DSM = static_cast<Mesh_DSM*>(currGroup);
   }
   else {
     Mesh* mesh = dynamic_cast<Mesh*>(currGroup);
     if (!mesh) {
       cout << "Error! DynBVH_D does not have a Mesh as the currGroup.\n";
       exit(1);
     }

     mesh_DSM = new Mesh_DSM;
     printf("creating new mesh_dsm for data\n");
#if 1
     Mesh_DSM::TriangleData* tris = reorderMesh();
     mesh_DSM->populateMesh(tris, mesh);
     delete[] tris;
     object_ids.clear();
#else
     mesh_DSM->populateMesh(mesh);
#endif
   }

   if (nodesDData.cache) // Did we already fill in the cache?
     return;



   //Infiniband packets are up to 4kB (2048 on our system I believe), so we
   //would probably have best performance at multiples of this (testing shows
   //2KB*4 is ideal).  Note though that the 4kB might include some packet
   //overhead, so something slightly smaller than 4kB might be optimal...  We
   //subtract 2 instead of 1 because we need to have even number of nodes per
   //block.
   const int nodesPerBlock = 2048*4/sizeof(BVHNode) - 2;

   size_t numCacheEntries = //2000;
     ((nodes.size()/nodesPerBlock) + 1) / cacheFraction;
   //numCacheEntries = Max(1, numCacheEntries - blocksInTopLevel);
   printf("numCacheEntries: %d nodes: %d nodesPerBlock: %d cacheFraction: %d\n", numCacheEntries, nodes.size(), nodesPerBlock, cacheFraction);



   const int blocksInTopLevel = 1;
   //1+1*(nodesPerBlock+2) + 0*(nodesPerBlock*nodesPerBlock+4);
   if (numCacheEntries > 0)
     numCacheEntries=Max(1,numCacheEntries-blocksInTopLevel);
   else
     numCacheEntries = -1;
   const int nodesPerBlockTopLevel = nodesPerBlock*blocksInTopLevel;

   printf("Using %d blocks in top level and %ld cache entries for BVH nodes\n", blocksInTopLevel, numCacheEntries);

   reorderNodes(nodesPerBlock, nodesPerBlockTopLevel);

//    nodesDData.setupCache(nodesPerBlock, numCacheEntries, nodes.size(), *this);

   nodesDData.setupCache(nodesPerBlock, numCacheEntries, nodes.size(), &nodes[0],
                         blocksInTopLevel);

   nodesDData.originalData = &nodes[0];

   // Write out a BVH that contains the reordered nodes.
   saveToFile("out_dsm.dynBVH");
   nodes.clear();
}

void DynBVH_D::reorderNodes(const int nodesPerBlock, const int nodesPerBlockTopLevel)
{
  ASSERT(nodesPerBlock%2 == 0);

  vector<BVHNode> reorderedNodes;
  reorderedNodes.reserve(nodes.size());
  reorderedNodes.push_back(nodes[0]);
  reorderNodes(nodesPerBlock, nodesPerBlockTopLevel-1, 0,
               reorderedNodes);

  if (reorderedNodes.size() != nodes.size()) {
    printf("something went wrong and we didn't fully copy all the nodes.  %ld!=%ld\n",
           reorderedNodes.size(), nodes.size());
    exit(1);
  }
  nodes = reorderedNodes; // optimize by doing a swap.
}

int DynBVH_D::reorderNodes(const int nodesPerBlock, int count, int parent,
                           vector<BVHNode>& reorderedNodes)
{
  if (reorderedNodes.size() > nodes.size()) {
    cerr << "something went wrong trying to reorder the nodes!\n";
    exit(1);
  }

  if (count == 0)
    count = nodesPerBlock;

  ASSERT(reorderedNodes[parent].isLeaf());

  deque<pair<BVHNode, size_t> > queue;
  const int childID = reorderedNodes[parent].child;
  queue.push_back( make_pair(nodes[childID+0], parent));
  queue.push_back( make_pair(nodes[childID+1], parent));

  while (!queue.empty()) {
    if (count == 1) {
      if (!queue.empty()) {
        count += nodesPerBlock; // reset count

        while (!queue.empty()) {
          int parent = queue.front().second;
          // pop the two children off
          queue.pop_front();
          queue.pop_front();

          count = reorderNodes(nodesPerBlock, count, parent, reorderedNodes);
        }
      }
      return count;
    }
    else if (count < 1) { cerr << "Something went wrong!\n"; exit(1); }
    else {

      // update reordered parent to point to the newly reordered children.
      parent = queue.front().second;
      reorderedNodes[parent].child = reorderedNodes.size();

      // update left child of parent and then again the right child.
      for (int i=0; i < 2; ++i) {
        reorderedNodes.push_back(queue.front().first);
        queue.pop_front();
        --count;
        if (!reorderedNodes.back().isLeaf()) {
          const int childID = reorderedNodes.back().child;
          queue.push_back( make_pair(nodes[childID+0], reorderedNodes.size()-1) );
          queue.push_back( make_pair(nodes[childID+1], reorderedNodes.size()-1) );
        }
      }
    }
  }
  return count;
}

Mesh_DSM::TriangleData* DynBVH_D::reorderMesh()
{
  Mesh_DSM::TriangleData* tris = new Mesh_DSM::TriangleData[currGroup->size()];
  size_t trisSize = 0;
  reorderMesh(0, tris, trisSize);
  if (trisSize != currGroup->size()) {
    printf("Something went wrong and we do not have the right number of tri! %ld != %ld\n",
           trisSize, currGroup->size());
  }
  return tris;
}

void DynBVH_D::reorderMesh(unsigned int nodeID, Mesh_DSM::TriangleData* tris,
                           size_t &trisSize)
{
  BVHNode& node = nodes[nodeID];
  if (node.isLeaf()) {
    const int childID = trisSize;
    for (int i = 0; i < node.children; ++i) {
      tris[trisSize] = Mesh_DSM::TriangleData(static_cast<Mesh*>(currGroup),
                                              object_ids[node.child+i]);
      //object_ids[node.child+i] = trisSize; // TODO: get rid of object_ids. They are not needed.
      ++trisSize;
    }
    node.child = childID;
  }
  else {
    reorderMesh(node.child+0, tris, trisSize);
    reorderMesh(node.child+1, tris, trisSize);
  }
}

void DynBVH_D::rebuild(int proc, int numProcs)
{
  Mesh_DSM* meshdsm = dynamic_cast<Mesh_DSM*>(currGroup);
  if (meshdsm)
    cout << __FUNCTION__ << " " << nodesDData.myRank << " currgroup was MeshDSM\n";
  else
    cout << __FUNCTION__ << " " << nodesDData.myRank <<  " currgroup was NOT MeshDSM\n";

  if (!group_changed) {
    update(proc, numProcs);
    return;
  }
  PreprocessContext context;

  if (proc > 0) return;

  if (print_info)
    cerr << "\nDynBVH_D::preprocess START (" << currGroup->size() << " objects)\n";
  double start = Time::currentSeconds();

  allocate();

  for ( size_t i = 0; i < currGroup->size(); i++ ) {
    object_ids[i] = i;
    obj_bounds[i].reset();
    currGroup->get(i)->computeBounds(context, obj_bounds[i]);
    obj_centroids[i] = obj_bounds[i].center();
  }

  num_nodes.set(0);
  nextFree.set(1);

  double build_start = Time::currentSeconds();


  build(context, 0, 0, currGroup->size());

  nodes.resize(num_nodes);

  double updateBound_start = Time::currentSeconds();
  updateBounds(context, 0);
  bounds = nodes[0].bounds;
  double end = Time::currentSeconds();
  if (print_info) {
    cerr << "\nDynBVH_D build time: Total ("<<end-start<<")\n"
         << "object_ids initialization ("<<build_start-start<<")\n"
         << "build ("<<updateBound_start-build_start<<")\n"
         << "updateBounds ("<<end-updateBound_start<<")\n"
         << "num_nodes = " << num_nodes << "\n"
         << "BBox = ("<<nodes[0].bounds.getMin()<<", "<<nodes[0].bounds.getMax()<<")\n\n";

  }

  // NOTE(boulos): As of 17-Aug-2007 we don't have a parallel build so
  // this is implicity proc0 anyway and requires no barrier.
  group_changed = false;
}

void DynBVH_D::build(const PreprocessContext& context,
                   int nodeID, int objectBegin, int objectEnd)
{
  //cerr << MANTA_FUNC << " begin = " << objectBegin << " , end = " << objectEnd << endl;
  if (objectEnd <= objectBegin) {
    throw InternalError("Tried building BVH over invalid range");
  }

  BVHNode& node = nodes[nodeID];

  PartitionData partition;
#if USE_APPROXIMATE_BUILD
  partition = partitionApproxSAH(context, nodeID, objectBegin, objectEnd);
#else
  partition = partitionSAH(context, nodeID, objectBegin, objectEnd);
#endif

  if (partition.axis == -1) {
    // make leaf
    node.makeLeaf(objectBegin, objectEnd-objectBegin);

    std::sort(object_ids.begin()+objectBegin,object_ids.begin()+objectEnd);

    subtree_size[nodeID] = 1;
    num_nodes++;
  } else {
    // make internal node
    // allocate two spots
    int my_spot = (nextFree += 2);
    node.makeInternal(my_spot, partition.axis);
    num_nodes++;

    nodes[node.child+0].bounds = partition.bounds_l;
    nodes[node.child+1].bounds = partition.bounds_r;

    build(context, node.child+0, objectBegin, partition.split);
    build(context, node.child+1, partition.split, objectEnd);
    subtree_size[nodeID] = 1 + subtree_size[node.child+0] + subtree_size[node.child+1];
  }
}

void DynBVH_D::updateBounds(const PreprocessContext& context, int ID)
{
  BVHNode& node = nodes[ID];
  if (node.isLeaf()) {
    node.bounds.reset();
    for (int i = 0; i < node.children; i++ ) {
      BBox temp;
      int obj_id = object_ids[node.child + i];
      currGroup->get(obj_id)->computeBounds(context,temp);

      node.bounds.extendByBox(temp);
    }
    node.axis = 0;
    node.axis_sign = 0;
  } else {
    int left_son = node.child;
    int right_son = left_son + 1;
    updateBounds(context, left_son);
    updateBounds(context, right_son);

    node.bounds.reset();
    const BVHNode& left_node = nodes[left_son];
    const BVHNode& right_node = nodes[right_son];

    node.bounds.extendByBox(left_node.bounds);
    node.bounds.extendByBox(right_node.bounds);
  }
}

DynBVH_D::PartitionData DynBVH_D::partitionApproxSAH(const PreprocessContext& context,
                                                 int nodeID,
                                                 int objBegin,
                                                 int objEnd) const {
  // TODO(thiago): check whether returning a structure instead of through an
  // argument is expensive.
  PartitionData partition;

  int num_objects = objEnd - objBegin;
  if ( num_objects == 1 ) {
    partition.axis = -1;
    partition.split = -1;
    return partition;
  }

  BBox centroid_bounds;
  for (int i = objBegin; i < objEnd; i++) {
    centroid_bounds.extendByPoint(obj_centroids[object_ids[i]]);
  }

  const float inv_parent_area = 1.0f / nodes[nodeID].bounds.computeArea();
  BVHCostEval best_cost;
  best_cost.cost = num_objects * BVH_C_isec;
  best_cost.axis = -1;
  best_cost.position = FLT_MAX;
  best_cost.event = -1;

  struct SampleBin {
    SampleBin() { count = 0;}
    BBox bounds;
    int count;
  };


  const int num_samples = BVH_num_samples;
  SampleBin bins[3][num_samples];

  Vector min_point = centroid_bounds.getMin();
  Vector max_point = centroid_bounds.getMax();
  Vector width = max_point - min_point;
  Vector scale((num_samples/width[0]) * .999f,
               (num_samples/width[1]) * .999f,
               (num_samples/width[2]) * .999f);
#ifdef LONGEST_AXIS
  int longest_axis = centroid_bounds.longestAxis();
#endif

  for (int i = objBegin; i < objEnd; i++) {
    BBox& obj_box = obj_bounds[object_ids[i]];
    Vector& obj_centroid = obj_centroids[object_ids[i]];
#ifdef LONGEST_AXIS
    for (int axis = longest_axis; axis == longest_axis; axis++) {
#else
    for (int axis = 0; axis < 3; axis++) {
#endif
      // Sample bin is where this position would fall to the left
      int which_bin = int((obj_centroid[axis] - min_point[axis]) * scale[axis]);
      which_bin = Clamp(which_bin, 0, num_samples - 1);
      bins[axis][which_bin].count++;
      bins[axis][which_bin].bounds.extendByBox(obj_box);
    }
  }

  // Now that we have all the sample points binned, we can just sweep over
  // them to search for the best cost
#ifdef LONGEST_AXIS
  for (int axis = longest_axis; axis == longest_axis; axis++) {
#else
  for (int axis = 0; axis < 3; axis++) {
#endif
    float left_areas[num_samples];
    float right_areas[num_samples];
    int left_counts[num_samples];
    int right_counts[num_samples];
    BBox left_box, right_box;
    int num_left = 0;
    int num_right = num_objects;

    // Sweep from left to right, aggregating area and counts
    for (int i = 0; i < num_samples; i++) {
      num_left += bins[axis][i].count;
      num_right -= bins[axis][i].count;
      left_box.extendByBox(bins[axis][i].bounds);
      left_counts[i] = num_left;
      right_counts[i] = num_right;
      left_areas[i]  = left_box.computeArea();
    }

    // Sweep from right to left, aggregating areas
    for (int i = num_samples - 1; i >= 0; i--) {
      if (i == num_samples - 1)
        right_areas[i] = FLT_MAX;
      else
        right_areas[i] = right_box.computeArea();

      right_box.extendByBox(bins[axis][i].bounds);
    }

    // NOTE(boulos): The last bin is pointless (since it indicates leaf)
    for (int i = 0; i < num_samples - 1; i++) {
      float cost = (left_areas[i] * left_counts[i] +
                    right_areas[i] * right_counts[i])*inv_parent_area * BVH_C_isec +
                    BVH_C_trav;
      if (cost < best_cost.cost) {
        // Found new best cost
        best_cost.cost = cost;
        best_cost.axis = axis;
        // NOTE(boulos): The position we want is the end of the bin, not the start
        float sample_position =
          (min_point[axis] + width[axis]*(static_cast<float>(i+1)/num_samples));
        best_cost.position = sample_position;
        best_cost.num_left = left_counts[i];
        best_cost.num_right = right_counts[i];
        best_cost.event = -1; // Unused
      }
    }
  }

  partition.axis = best_cost.axis;
  if ( partition.axis != -1 ) {
    // write out object ids [objBegin,objEnd) in appropriate order
    int middle = partitionObjects(objBegin, objEnd, partition.axis, best_cost.position);
    if (middle == objBegin || middle == objEnd) {
      // Splitting didn't find a valid split, split in the middle unless
      // we have too few
      const int kMinObjects = 3;
      if (num_objects < kMinObjects) {
        partition.axis = -1;
        partition.split = 0;
        return partition;
      }
      middle = objBegin + num_objects / 2;
    }

    for (int i = objBegin; i < middle; ++i) {
      partition.bounds_l.extendByBox(obj_bounds[object_ids[i]]);
    }
    for (int i = middle; i < objEnd; ++i) {
      partition.bounds_r.extendByBox(obj_bounds[object_ids[i]]);
    }

    partition.split = middle;
    return partition;
  }

  // making a leaf
  partition.split = 0;
  return partition;
}

  DynBVH_D::PartitionData DynBVH_D::partitionSAH(const PreprocessContext& context,
                                                 int nodeID,
                                                 int objBegin, int objEnd) const
{
  PartitionData partition;

  int num_objects = objEnd - objBegin;
  if ( num_objects == 1 ) {
      partition.axis = -1;
      return partition;
  }

  BVHCostEval best_cost;
  best_cost.cost = BVH_C_isec * num_objects;
  best_cost.axis = -1;
  best_cost.position = FLT_MAX;
  best_cost.event = -1;

  for ( int axis = 0; axis < 3; axis++ ) {
    BVHCostEval new_cost;
    if ( buildEvents(context, nodeID, objBegin,objEnd,axis,new_cost) ) {
      if ( new_cost.cost < best_cost.cost ) {
        best_cost = new_cost;
      }
    }
  }

  partition.bounds_r = best_cost.bounds_r;
  partition.axis = best_cost.axis;
  if ( partition.axis != -1 ) {
    // write out object ids [objBegin,objEnd) in appropriate order
    // NOTE(boulos): Because the way the sweep works, we can't just
    // use the position and partitionObjects
    std::vector<BVHSAHEvent> events;
    events.reserve(objEnd-objBegin);
    for ( int i = objBegin; i < objEnd; i++ ) {
      BVHSAHEvent new_event;
      new_event.position = obj_centroids[object_ids[i]][partition.axis];
      new_event.obj_id   = object_ids[i];
      events.push_back(new_event);
    }

    partition.split = objBegin + best_cost.event;

    std::sort(events.begin(),events.end(),CompareBVHSAHEvent());
    for (int i = objBegin; i < objEnd; i++) {
      object_ids[i] = events[i-objBegin].obj_id;

      if (i < partition.split)
        partition.bounds_l.extendByBox(obj_bounds[object_ids[i]]);
    }

    return partition;
  }

  return partition; // making a leaf anyway
}

bool DynBVH_D::buildEvents(const PreprocessContext& context,
                         const int parentID,
                         int first,
                         int last,
                         int axis,
                         BVHCostEval& best_eval) const
{
  std::vector<BVHSAHEvent> events;
  events.reserve(last-first);
  for ( int i = first; i < last; i++ ) {
    BVHSAHEvent new_event;
    new_event.position = obj_centroids[object_ids[i]][axis];
    new_event.obj_id   = object_ids[i];
    events.push_back(new_event);
  }

  std::sort(events.begin(),events.end(),CompareBVHSAHEvent());

  int num_events = int(events.size());
  BBox left_box;

  int num_left = 0;
  int num_right = num_events;

  for ( size_t i = 0; i < events.size(); i++ ) {
    events[i].num_left = num_left;
    events[i].num_right = num_right;
    events[i].left_area = left_box.computeArea();

    BBox& tri_box = obj_bounds[events[i].obj_id];
    left_box.extendByBox(tri_box);

    num_left++;
    num_right--;
  }

  BBox right_box;

  best_eval.cost = FLT_MAX;
  best_eval.event = -1;

  const float inv_parent_area = 1.0f / nodes[parentID].bounds.computeArea();

  for ( int i = num_events - 1; i >= 0; i-- ) {
    BBox& tri_box = obj_bounds[events[i].obj_id];
    right_box.extendByBox(tri_box);

    if ( events[i].num_left > 0 && events[i].num_right > 0 ) {
      events[i].right_area = right_box.computeArea();

      float this_cost = (events[i].num_left * events[i].left_area +
                         events[i].num_right * events[i].right_area);
      this_cost *= inv_parent_area;
      this_cost *= BVH_C_isec;
      this_cost += BVH_C_trav;

      events[i].cost = this_cost;
      if ( this_cost < best_eval.cost ) {
        best_eval.bounds_r   = right_box;
        best_eval.cost       = this_cost;
        best_eval.position   = events[i].position;
        best_eval.axis       = axis;
        best_eval.event      = i;
        best_eval.num_left   = events[i].num_left;
        best_eval.num_right  = events[i].num_right;
      }
    }
  }
  return best_eval.event != -1;
}

bool DynBVH_D::buildFromFile(const string &file)
{
  nodes.clear();

  //Something's wrong, let's bail.
  if (!currGroup)
    return false;

  in.open(file.c_str(), ios::binary | ios::in);
  if (!in) {
    printf("Node %d could not load BVH from file!\n", nodesDData.myRank);
   return false;
  }
  group_changed = false;

  unsigned int object_ids_size;
  in.read((char*)&object_ids_size, sizeof(object_ids_size));

#if 0
  object_ids.resize(object_ids_size);
  in.read((char*) &object_ids[0], sizeof(object_ids[0])*object_ids.size());

  unsigned int nodes_size;
  in.read((char*)&nodes_size, sizeof(nodes_size));
  nodes.resize(nodes_size);

  in.read((char*) &nodes[0], sizeof(nodes[0])*nodes.size());
  num_nodes.set(nodes.size());
  bounds = nodes[0].bounds;
#else
  // skip object_ids.
  dataStart = in.tellg();
  dataStart +=sizeof(int)*object_ids_size;
  in.seekg(dataStart);

  unsigned int nodes_size;
  in.read((char*)&nodes_size, sizeof(nodes_size));
  num_nodes.set(nodes_size);

  dataStart = in.tellg();

  // TODO: nodesPerBlock and blocksInTopLevel should be saved to file and
  // then loaded from file!

  const int nodesPerBlock = 2048*4/sizeof(BVHNode) - 2;

  const int blocksInTopLevel = 1;//nodesPerBlock+2; // This gives two levels of blocks

  size_t numCacheEntries = //2000;
    ((nodes_size/nodesPerBlock) + 1) / cacheFraction;
   //numCacheEntries = Max(1, numCacheEntries - blocksInTopLevel);

  if (cacheFraction < 0)
    numCacheEntries = -1;

  nodesDData.setupCache(nodesPerBlock, numCacheEntries, nodes_size, *this, blocksInTopLevel);

  int blockID = 0;
  BVHNode const* block = nodesDData.get_data(blockID, 0);
  bounds = block[0].bounds;
  nodesDData.release_data(blockID);

  printf("Done building tree from file %d\n", nodesDData.myRank);

#endif


  in.close();

  return true;
}

void DynBVH_D::getDatum(void* datum, size_t nodeID) const
{
  in.seekg(dataStart + static_cast<streampos>(nodeID*sizeof(BVHNode)));
  in.read((char*)datum, sizeof(BVHNode));
}

void DynBVH_D::getDatums(void* datums, size_t nodeID, size_t num) const
{
//   static streampos lastPos = -1;
  const streampos newPos = dataStart + static_cast<streampos>(nodeID*sizeof(BVHNode));
//   if (lastPos != newPos) {
    in.seekg(newPos);
//   }
//   lastPos = newPos + streampos(num*sizeof(BVHNode));
  in.read((char*)datums, num*sizeof(BVHNode));
}


bool DynBVH_D::saveToFile(const string &file)
{
  ofstream out(file.c_str(), ios::out | ios::binary);
  if (!out) return false;

  if (nodes.empty()) {
    printf("\nERROR!\n      The nods vector is empty!\n");
  }

  const unsigned int object_ids_size = object_ids.size();
  const unsigned int nodes_size = nodes.size();
  out.write((char*) &object_ids_size, sizeof(object_ids_size));
  out.write((char*) &object_ids[0], sizeof(object_ids[0])*object_ids_size);
  out.write((char*) &nodes_size, sizeof(nodes_size));
  out.write((char*) &nodes[0], sizeof(nodes[0])*nodes_size);

  out.close();
  return true;
}


// begin port from actual DynBVH_D
#ifdef MANTA_SSE
void DynBVH_D::templatedTraverse(const RenderContext& context, RayPacket& packet) const {
  struct StackNode {
    int nodeID;
    int firstActive;
  };

  StackNode nodeStack[64];// ={}; // NOTE(boulos): no need to 0 out
  int stackPtr = 0;

  int ID = 0;
  int firstActive = 0;

  const int frontSon[3] = {
    packet.getDirection(0, 0) > 0 ? 0 : 1,
    packet.getDirection(0, 1) > 0 ? 0 : 1,
    packet.getDirection(0, 2) > 0 ? 0 : 1
  };

  const BVHNode* const nodes = &this->nodes[0];
  __m128 min_rcp[3];
  __m128 max_rcp[3];

  RayPacketData* data = packet.data;
  MANTA_UNROLL(3);
  for (int d = 0; d < 3; d++) {
    min_rcp[d] = _mm_load_ps(&data->inverseDirection[d][0]);
    max_rcp[d] = _mm_load_ps(&data->inverseDirection[d][0]);

    MANTA_UNROLL(8);
    for (int pack = 1; pack < RayPacket::SSE_MaxSize; pack++) {
      min_rcp[d] = _mm_min_ps(min_rcp[d],
                              _mm_load_ps(&data->inverseDirection[d][pack * 4]));
      max_rcp[d] = _mm_max_ps(max_rcp[d],
                              _mm_load_ps(&data->inverseDirection[d][pack * 4]));
    }
  }

  // do sign check

  int signChecked =
    ((_mm_movemask_ps(_mm_cmpgt_ps(min_rcp[0], _mm_setzero_ps())) == 0xf) ||
     (_mm_movemask_ps(_mm_cmplt_ps(max_rcp[0], _mm_setzero_ps())) == 0xf)) &&
    ((_mm_movemask_ps(_mm_cmpgt_ps(min_rcp[1], _mm_setzero_ps())) == 0xf) ||
     (_mm_movemask_ps(_mm_cmplt_ps(max_rcp[1], _mm_setzero_ps())) == 0xf)) &&
    ((_mm_movemask_ps(_mm_cmpgt_ps(min_rcp[2], _mm_setzero_ps())) == 0xf) ||
     (_mm_movemask_ps(_mm_cmplt_ps(max_rcp[2], _mm_setzero_ps())) == 0xf));

  if (!signChecked) {
    // variant for non-equal signs
    for (;;) {
      const BVHNode& thisNode = nodes[ID];
      firstActive = firstActivePort(packet, firstActive, thisNode.bounds);
      if (firstActive < RayPacket::MaxSize) {
        if (!thisNode.isLeaf()) {
          // inner node
          int front = frontSon[thisNode.axis];
          nodeStack[stackPtr].nodeID = thisNode.child + 1 - front;
          nodeStack[stackPtr].firstActive = firstActive;
          stackPtr++;
          ID = thisNode.child + front;
          continue;
        } else {
          // leaf
          int lastActive = lastActivePort(packet, firstActive, thisNode.bounds);
          // this part has to differ from DynBVH_D due to requirements
          // on primitive intersection.  Shouldn't hurt though.
          RayPacket subpacket(packet, firstActive, lastActive+1);

          for (int i = 0; i < thisNode.children; i++ ) {
            const int object_id = object_ids[thisNode.child+i];
            currGroup->get(object_id)->intersect(context,subpacket);
          }
        }
      }
      if (stackPtr <= 0) {
        return;
      }
      --stackPtr;
      ID = nodeStack[stackPtr].nodeID;
      firstActive = nodeStack[stackPtr].firstActive;
    }
  }

  // sign matches case
  __m128 min_org[3];
  __m128 max_org[3];

  if (!packet.getFlag(RayPacket::ConstantOrigin)) {
    for (int d = 0; d < 3; d++) {
      min_org[d] = max_org[d] = _mm_load_ps(&data->origin[d][0]);
      for (int i = 1; i < RayPacket::SSE_MaxSize; i++) {
        min_org[d] = _mm_min_ps(min_org[d], _mm_load_ps(&data->origin[d][i * 4]));
        max_org[d] = _mm_max_ps(max_org[d], _mm_load_ps(&data->origin[d][i * 4]));
      }
    }
  }

  __m128 max_t = _mm_load_ps(&data->minT[0]);
  for (int pack=1; pack < RayPacket::SSE_MaxSize; pack++) {
    max_t = _mm_max_ps(max_t, _mm_load_ps(&data->minT[pack * 4]));
  }

  const __m128 signCorrected_max_rcp[3] = {
    frontSon[0]?max_rcp[0]:min_rcp[0],
    frontSon[1]?max_rcp[1]:min_rcp[1],
    frontSon[2]?max_rcp[2]:min_rcp[2]
  };

  const __m128 signCorrected_min_rcp[3] = {
    !frontSon[0]?max_rcp[0]:min_rcp[0],
    !frontSon[1]?max_rcp[1]:min_rcp[1],
    !frontSon[2]?max_rcp[2]:min_rcp[2]
  };

  const __m128 signCorrected_max_org[3] = {
    !frontSon[0]?max_org[0]:min_org[0],
    !frontSon[1]?max_org[1]:min_org[1],
    !frontSon[2]?max_org[2]:min_org[2]
  };

  const __m128 signCorrected_min_org[3] = {
    frontSon[0]?max_org[0]:min_org[0],
    frontSon[1]?max_org[1]:min_org[1],
    frontSon[2]?max_org[2]:min_org[2]
  };

  for (;;) {
    const BVHNode& thisNode = nodes[ID];
    firstActive = firstActiveSameSignFrustumPort(packet, firstActive, thisNode.bounds, frontSon,
                                                 signCorrected_min_org,
                                                 signCorrected_max_org,
                                                 signCorrected_min_rcp,
                                                 signCorrected_max_rcp,
                                                 max_t);
    if (firstActive < RayPacket::MaxSize) {
      if (!thisNode.isLeaf()) {
        // inner node
        int front = frontSon[thisNode.axis];
        nodeStack[stackPtr].nodeID = thisNode.child + int(1-front); // NOTE(boulos): check this...
        nodeStack[stackPtr].firstActive = firstActive;
        stackPtr++;
        ID = thisNode.child + front;
        continue;
      } else {
        int lastActive = lastThatIntersectsSameSignPort(packet,
                                                        firstActive,
                                                        thisNode.bounds,
                                                        frontSon);
        // Same deal as above.
        RayPacket subpacket(packet, firstActive, lastActive+1);

        for (int i = 0; i < thisNode.children; i++ ) {
          const int object_id = object_ids[thisNode.child+i];
          currGroup->get(object_id)->intersect(context,subpacket);
        }
      }
    }
    if (stackPtr <= 0) {
      return;
    }
    --stackPtr;
    ID = nodeStack[stackPtr].nodeID;
    firstActive = nodeStack[stackPtr].firstActive;
  }
}

int DynBVH_D::firstActivePort(RayPacket& packet, int firstActive, const BBox& box) const {
  __m128 box_min_x = _mm_set1_ps(box[0][0]);
  __m128 box_min_y = _mm_set1_ps(box[0][1]);
  __m128 box_min_z = _mm_set1_ps(box[0][2]);

  __m128 box_max_x = _mm_set1_ps(box[1][0]);
  __m128 box_max_y = _mm_set1_ps(box[1][1]);
  __m128 box_max_z = _mm_set1_ps(box[1][2]);

  const RayPacketData* data = packet.data;
  const bool constant_origin = packet.getFlag(RayPacket::ConstantOrigin);

  // NOTE(boulos): To get rid of a warning, we'll just do this one
  // always. TODO(boulos): Make this code correctly handle variable
  // sized ray packets.
  __m128 diff_x_min = _mm_sub_ps(box_min_x, _mm_load_ps(&data->origin[0][0]));;
  __m128 diff_y_min = _mm_sub_ps(box_min_y, _mm_load_ps(&data->origin[1][0]));;
  __m128 diff_z_min = _mm_sub_ps(box_min_z, _mm_load_ps(&data->origin[2][0]));;

  __m128 diff_x_max = _mm_sub_ps(box_max_x, _mm_load_ps(&data->origin[0][0]));;
  __m128 diff_y_max = _mm_sub_ps(box_max_y, _mm_load_ps(&data->origin[1][0]));;
  __m128 diff_z_max = _mm_sub_ps(box_max_z, _mm_load_ps(&data->origin[2][0]));;

  for (int i=firstActive;i < RayPacket::MaxSize; i+=4) {
    __m128 t0 = _mm_set1_ps(T_EPSILON);
    __m128 t1 = _mm_load_ps(&data->minT[i]);

    if (!constant_origin) {
      diff_x_min = _mm_sub_ps(box_min_x, _mm_load_ps(&data->origin[0][i]));
      diff_y_min = _mm_sub_ps(box_min_y, _mm_load_ps(&data->origin[1][i]));
      diff_z_min = _mm_sub_ps(box_min_z, _mm_load_ps(&data->origin[2][i]));

      diff_x_max = _mm_sub_ps(box_max_x, _mm_load_ps(&data->origin[0][i]));
      diff_y_max = _mm_sub_ps(box_max_y, _mm_load_ps(&data->origin[1][i]));
      diff_z_max = _mm_sub_ps(box_max_z, _mm_load_ps(&data->origin[2][i]));
    }

    {
      const __m128 tBoxMin = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[0][i]),
                                        diff_x_min);
      const __m128 tBoxMax = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[0][i]),
                                        diff_x_max);
      t0 = _mm_max_ps(t0, _mm_min_ps(tBoxMin, tBoxMax));
      t1 = _mm_min_ps(t1, _mm_max_ps(tBoxMin, tBoxMax));
    }

    {
      const __m128 tBoxMin = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[1][i]),
                                        diff_y_min);
      const __m128 tBoxMax = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[1][i]),
                                        diff_y_max);
      t0 = _mm_max_ps(t0, _mm_min_ps(tBoxMin, tBoxMax));
      t1 = _mm_min_ps(t1, _mm_max_ps(tBoxMin, tBoxMax));
    }

    {
      const __m128 tBoxMin = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[2][i]),
                                        diff_z_min);
      const __m128 tBoxMax = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[2][i]),
                                        diff_z_max);
      t0 = _mm_max_ps(t0, _mm_min_ps(tBoxMin, tBoxMax));
      t1 = _mm_min_ps(t1, _mm_max_ps(tBoxMin, tBoxMax));
    }

    if (_mm_movemask_ps(_mm_cmple_ps(t0, t1)) != 0x0)
      return i;
  }
  return RayPacket::MaxSize;
}

int DynBVH_D::lastActivePort(RayPacket& packet, int firstActive, const BBox& box) const {
  __m128 box_min_x = _mm_set1_ps(box[0][0]);
  __m128 box_min_y = _mm_set1_ps(box[0][1]);
  __m128 box_min_z = _mm_set1_ps(box[0][2]);

  __m128 box_max_x = _mm_set1_ps(box[1][0]);
  __m128 box_max_y = _mm_set1_ps(box[1][1]);
  __m128 box_max_z = _mm_set1_ps(box[1][2]);

  const RayPacketData* data = packet.data;

  __m128 diff_x_min = _mm_sub_ps(box_min_x, _mm_load_ps(&data->origin[0][0]));
  __m128 diff_y_min = _mm_sub_ps(box_min_y, _mm_load_ps(&data->origin[1][0]));
  __m128 diff_z_min = _mm_sub_ps(box_min_z, _mm_load_ps(&data->origin[2][0]));

  __m128 diff_x_max = _mm_sub_ps(box_max_x, _mm_load_ps(&data->origin[0][0]));
  __m128 diff_y_max = _mm_sub_ps(box_max_y, _mm_load_ps(&data->origin[1][0]));
  __m128 diff_z_max = _mm_sub_ps(box_max_z, _mm_load_ps(&data->origin[2][0]));

  const int last_ray = (RayPacket::SSE_MaxSize - 1) * 4;
  for (int i=last_ray; i > firstActive; i -= 4) {
    __m128 t0 = _mm_set1_ps(T_EPSILON);
    __m128 t1 = _mm_load_ps(&data->minT[i]);

    if (!packet.getFlag(RayPacket::ConstantOrigin)) {
      diff_x_min = _mm_sub_ps(box_min_x, _mm_load_ps(&data->origin[0][i]));
      diff_y_min = _mm_sub_ps(box_min_y, _mm_load_ps(&data->origin[1][i]));
      diff_z_min = _mm_sub_ps(box_min_z, _mm_load_ps(&data->origin[2][i]));

      diff_x_max = _mm_sub_ps(box_max_x, _mm_load_ps(&data->origin[0][i]));
      diff_y_max = _mm_sub_ps(box_max_y, _mm_load_ps(&data->origin[1][i]));
      diff_z_max = _mm_sub_ps(box_max_z, _mm_load_ps(&data->origin[2][i]));
    }

    {
      const __m128 tBoxMin = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[0][i]),
                                        diff_x_min);
      const __m128 tBoxMax = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[0][i]),
                                        diff_x_max);
      t0 = _mm_max_ps(t0, _mm_min_ps(tBoxMin, tBoxMax));
      t1 = _mm_min_ps(t1, _mm_max_ps(tBoxMin, tBoxMax));
    }

    {
      const __m128 tBoxMin = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[1][i]),
                                        diff_y_min);
      const __m128 tBoxMax = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[1][i]),
                                        diff_y_max);
      t0 = _mm_max_ps(t0, _mm_min_ps(tBoxMin, tBoxMax));
      t1 = _mm_min_ps(t1, _mm_max_ps(tBoxMin, tBoxMax));
    }

    {
      const __m128 tBoxMin = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[2][i]),
                                        diff_z_min);
      const __m128 tBoxMax = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[2][i]),
                                        diff_z_max);
      t0 = _mm_max_ps(t0, _mm_min_ps(tBoxMin, tBoxMax));
      t1 = _mm_min_ps(t1, _mm_max_ps(tBoxMin, tBoxMax));
    }

    // Unlike DynBVH_D we want to return last active "ray", so the last
    // entry in this simd is the answer.
    if (_mm_movemask_ps(_mm_cmple_ps(t0, t1)) != 0x0)
      return i + 3;
  }
  return firstActive + 3;
}

int DynBVH_D::firstActiveSameSignFrustumPort(RayPacket& packet,
                                           const int firstActive,
                                           const BBox& box,
                                           const int signs[3],
                                           const __m128 sc_min_org[3],
                                           const __m128 sc_max_org[3],
                                           const __m128 sc_min_rcp[3],
                                           const __m128 sc_max_rcp[3],
                                           const __m128& max_t) const {

  const __m128 box_near_x = _mm_set1_ps(box[signs[0]][0]);
  const __m128 box_near_y = _mm_set1_ps(box[signs[1]][1]);
  const __m128 box_near_z = _mm_set1_ps(box[signs[2]][2]);

  const __m128 box_far_x = _mm_set1_ps(box[1-signs[0]][0]);
  const __m128 box_far_y = _mm_set1_ps(box[1-signs[1]][1]);
  const __m128 box_far_z = _mm_set1_ps(box[1-signs[2]][2]);

  const RayPacketData* data = packet.data;

  __m128 near_minus_org_x  = _mm_sub_ps(box_near_x, _mm_load_ps(&data->origin[0][0]));
  __m128 near_minus_org_y  = _mm_sub_ps(box_near_y, _mm_load_ps(&data->origin[1][0]));
  __m128 near_minus_org_z  = _mm_sub_ps(box_near_z, _mm_load_ps(&data->origin[2][0]));

  __m128 far_minus_org_x   = _mm_sub_ps(box_far_x, _mm_load_ps(&data->origin[0][0]));
  __m128 far_minus_org_y   = _mm_sub_ps(box_far_y, _mm_load_ps(&data->origin[1][0]));
  __m128 far_minus_org_z   = _mm_sub_ps(box_far_z, _mm_load_ps(&data->origin[2][0]));

  // test first (assumed) packet
  {
    const int i = firstActive;
    __m128 t0 = _mm_set1_ps(T_EPSILON);
    __m128 t1 = _mm_load_ps(&data->minT[i]);

    if (!packet.getFlag(RayPacket::ConstantOrigin)) {
      near_minus_org_x = _mm_sub_ps(box_near_x, _mm_load_ps(&data->origin[0][i]));
      near_minus_org_y = _mm_sub_ps(box_near_y, _mm_load_ps(&data->origin[1][i]));
      near_minus_org_z = _mm_sub_ps(box_near_z, _mm_load_ps(&data->origin[2][i]));
    }

    const __m128 tBoxNearX = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[0][i]), near_minus_org_x);
    const __m128 tBoxNearY = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[1][i]), near_minus_org_y);
    const __m128 tBoxNearZ = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[2][i]), near_minus_org_z);

    t0 = _mm_max_ps(t0, tBoxNearX);
    t0 = _mm_max_ps(t0, tBoxNearY);
    t0 = _mm_max_ps(t0, tBoxNearZ);

    if (!packet.getFlag(RayPacket::ConstantOrigin)) {
      far_minus_org_x = _mm_sub_ps(box_far_x, _mm_load_ps(&data->origin[0][i]));
      far_minus_org_y = _mm_sub_ps(box_far_y, _mm_load_ps(&data->origin[1][i]));
      far_minus_org_z = _mm_sub_ps(box_far_z, _mm_load_ps(&data->origin[2][i]));
    }

    const __m128 tBoxFarX = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[0][i]), far_minus_org_x);
    const __m128 tBoxFarY = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[1][i]), far_minus_org_y);
    const __m128 tBoxFarZ = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[2][i]), far_minus_org_z);

    t1 = _mm_min_ps(t1, tBoxFarX);
    t1 = _mm_min_ps(t1, tBoxFarY);
    t1 = _mm_min_ps(t1, tBoxFarZ);

    if (_mm_movemask_ps(_mm_cmple_ps(t0,t1)) != 0x0)
      return i;
  }

  // first greedy "maybe hit" test failed.

  if (packet.getFlag(RayPacket::ConstantOrigin)) {
    __m128 t0 = _mm_set1_ps(T_EPSILON);
    __m128 t1 = max_t;

    const __m128 tBoxNearX = _mm_mul_ps(sc_max_rcp[0], near_minus_org_x);
    const __m128 tBoxNearY = _mm_mul_ps(sc_max_rcp[1], near_minus_org_y);
    const __m128 tBoxNearZ = _mm_mul_ps(sc_max_rcp[2], near_minus_org_z);

    t0 = _mm_max_ps(t0, tBoxNearX);
    t0 = _mm_max_ps(t0, tBoxNearY);
    t0 = _mm_max_ps(t0, tBoxNearZ);

    const __m128 tBoxFarX = _mm_mul_ps(sc_min_rcp[0], far_minus_org_x);
    const __m128 tBoxFarY = _mm_mul_ps(sc_min_rcp[1], far_minus_org_y);
    const __m128 tBoxFarZ = _mm_mul_ps(sc_min_rcp[2], far_minus_org_z);

    t1 = _mm_min_ps(t1, tBoxFarX);
    t1 = _mm_min_ps(t1, tBoxFarY);
    t1 = _mm_min_ps(t1, tBoxFarZ);

    if (_mm_movemask_ps(_mm_cmple_ps(t0,t1)) == 0x0)
      return RayPacket::MaxSize;
  } else {
    // IA for non-constant origin
    __m128 t0 = _mm_set1_ps(T_EPSILON);
    __m128 t1 = max_t;

    near_minus_org_x = _mm_sub_ps(box_near_x, sc_max_org[0]);
    near_minus_org_y = _mm_sub_ps(box_near_y, sc_max_org[1]);
    near_minus_org_z = _mm_sub_ps(box_near_z, sc_max_org[2]);

    const __m128 tBoxNearX = _mm_mul_ps(sc_max_rcp[0], near_minus_org_x);
    const __m128 tBoxNearY = _mm_mul_ps(sc_max_rcp[1], near_minus_org_y);
    const __m128 tBoxNearZ = _mm_mul_ps(sc_max_rcp[2], near_minus_org_z);

    t0 = _mm_max_ps(t0, tBoxNearX);
    t0 = _mm_max_ps(t0, tBoxNearY);
    t0 = _mm_max_ps(t0, tBoxNearZ);

    far_minus_org_x = _mm_sub_ps(box_far_x, sc_min_org[0]);
    far_minus_org_y = _mm_sub_ps(box_far_y, sc_min_org[1]);
    far_minus_org_z = _mm_sub_ps(box_far_z, sc_min_org[2]);

    const __m128 tBoxFarX = _mm_mul_ps(sc_min_rcp[0], far_minus_org_x);
    const __m128 tBoxFarY = _mm_mul_ps(sc_min_rcp[1], far_minus_org_y);
    const __m128 tBoxFarZ = _mm_mul_ps(sc_min_rcp[2], far_minus_org_z);

    t1 = _mm_min_ps(t1, tBoxFarX);
    t1 = _mm_min_ps(t1, tBoxFarY);
    t1 = _mm_min_ps(t1, tBoxFarZ);

    if (_mm_movemask_ps(_mm_cmple_ps(t0,t1)) == 0x0)
      return RayPacket::MaxSize;
  }

  // frustum culling failed.  probably at least one ray hits...
  for (int i = firstActive + 4; i < RayPacket::MaxSize; i+= 4) {
    __m128 t0 = _mm_set1_ps(T_EPSILON);
    __m128 t1 = _mm_load_ps(&data->minT[i]);

    if (!packet.getFlag(RayPacket::ConstantOrigin)) {
      near_minus_org_x = _mm_sub_ps(box_near_x, _mm_load_ps(&data->origin[0][i]));
      near_minus_org_y = _mm_sub_ps(box_near_y, _mm_load_ps(&data->origin[1][i]));
      near_minus_org_z = _mm_sub_ps(box_near_z, _mm_load_ps(&data->origin[2][i]));
    }

    const __m128 tBoxNearX = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[0][i]),
                                        near_minus_org_x);
    const __m128 tBoxNearY = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[1][i]),
                                        near_minus_org_y);
    const __m128 tBoxNearZ = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[2][i]),
                                        near_minus_org_z);

    t0 = _mm_max_ps(t0, tBoxNearX);
    t0 = _mm_max_ps(t0, tBoxNearY);
    t0 = _mm_max_ps(t0, tBoxNearZ);

    if (!packet.getFlag(RayPacket::ConstantOrigin)) {
      far_minus_org_x = _mm_sub_ps(box_far_x, _mm_load_ps(&data->origin[0][i]));
      far_minus_org_y = _mm_sub_ps(box_far_y, _mm_load_ps(&data->origin[1][i]));
      far_minus_org_z = _mm_sub_ps(box_far_z, _mm_load_ps(&data->origin[2][i]));
    }

    const __m128 tBoxFarX = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[0][i]),
                                       far_minus_org_x);
    const __m128 tBoxFarY = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[1][i]),
                                       far_minus_org_y);
    const __m128 tBoxFarZ = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[2][i]),
                                       far_minus_org_z);

    t1 = _mm_min_ps(t1, tBoxFarX);
    t1 = _mm_min_ps(t1, tBoxFarY);
    t1 = _mm_min_ps(t1, tBoxFarZ);
    if (_mm_movemask_ps(_mm_cmple_ps(t0, t1)) != 0x0)
      return i;
  }

  return RayPacket::MaxSize;
}

int DynBVH_D::lastThatIntersectsSameSignPort(RayPacket& packet,
                                           const int firstActive,
                                           const BBox& box,
                                           const int signs[3]) const {
  const __m128 box_near_x = _mm_set1_ps(box[signs[0]][0]);
  const __m128 box_near_y = _mm_set1_ps(box[signs[1]][1]);
  const __m128 box_near_z = _mm_set1_ps(box[signs[2]][2]);

  const __m128 box_far_x = _mm_set1_ps(box[1-signs[0]][0]);
  const __m128 box_far_y = _mm_set1_ps(box[1-signs[1]][1]);
  const __m128 box_far_z = _mm_set1_ps(box[1-signs[2]][2]);

  const RayPacketData* data = packet.data;

  __m128 near_minus_org_x = _mm_sub_ps(box_near_x, _mm_load_ps(&data->origin[0][0]));
  __m128 near_minus_org_y = _mm_sub_ps(box_near_y, _mm_load_ps(&data->origin[1][0]));
  __m128 near_minus_org_z = _mm_sub_ps(box_near_z, _mm_load_ps(&data->origin[2][0]));

  __m128 far_minus_org_x  = _mm_sub_ps(box_far_x, _mm_load_ps(&data->origin[0][0]));
  __m128 far_minus_org_y  = _mm_sub_ps(box_far_y, _mm_load_ps(&data->origin[1][0]));
  __m128 far_minus_org_z  = _mm_sub_ps(box_far_z, _mm_load_ps(&data->origin[2][0]));

  // frustum culling failed.  probably at least one ray hits...
  const int last_ray = (RayPacket::SSE_MaxSize - 1) * 4;
  for (int i = last_ray; i > firstActive; i-= 4) {
    __m128 t0 = _mm_set1_ps(T_EPSILON);
    __m128 t1 = _mm_load_ps(&data->minT[i]);

    if (!packet.getFlag(RayPacket::ConstantOrigin)) {
      near_minus_org_x = _mm_sub_ps(box_near_x, _mm_load_ps(&data->origin[0][i]));
      near_minus_org_y = _mm_sub_ps(box_near_y, _mm_load_ps(&data->origin[1][i]));
      near_minus_org_z = _mm_sub_ps(box_near_z, _mm_load_ps(&data->origin[2][i]));
    }

    const __m128 tBoxNearX = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[0][i]),
                                        near_minus_org_x);
    const __m128 tBoxNearY = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[1][i]),
                                        near_minus_org_y);
    const __m128 tBoxNearZ = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[2][i]),
                                        near_minus_org_z);

    t0 = _mm_max_ps(t0, tBoxNearX);
    t0 = _mm_max_ps(t0, tBoxNearY);
    t0 = _mm_max_ps(t0, tBoxNearZ);

    if (!packet.getFlag(RayPacket::ConstantOrigin)) {
      far_minus_org_x = _mm_sub_ps(box_far_x, _mm_load_ps(&data->origin[0][i]));
      far_minus_org_y = _mm_sub_ps(box_far_y, _mm_load_ps(&data->origin[1][i]));
      far_minus_org_z = _mm_sub_ps(box_far_z, _mm_load_ps(&data->origin[2][i]));
    }

    const __m128 tBoxFarX = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[0][i]),
                                       far_minus_org_x);
    const __m128 tBoxFarY = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[1][i]),
                                       far_minus_org_y);
    const __m128 tBoxFarZ = _mm_mul_ps(_mm_load_ps(&data->inverseDirection[2][i]),
                                       far_minus_org_z);

    t1 = _mm_min_ps(t1, tBoxFarX);
    t1 = _mm_min_ps(t1, tBoxFarY);
    t1 = _mm_min_ps(t1, tBoxFarZ);
    if (_mm_movemask_ps(_mm_cmple_ps(t0, t1)) != 0x0)
      return i + 3;
  }

  return firstActive + 3;
}
#endif // MANTA_SSE for USE_DYNBVH_PORTS

namespace Manta {
  MANTA_DECLARE_RTTI_DERIVEDCLASS(DynBVH_D, AccelerationStructure, ConcreteClass, readwriteMethod);
  MANTA_REGISTER_CLASS(DynBVH_D);

#ifndef SWIG
  MANTA_DECLARE_RTTI_BASECLASS(DynBVH_D::BVHNode, ConcreteClass, readwriteMethod);
  MANTA_REGISTER_CLASS(DynBVH_D::BVHNode);
#endif
}

#ifndef SWIG
void DynBVH_D::BVHNode::readwrite(ArchiveElement* archive) {
  archive->readwrite("bounds", bounds);
  archive->readwrite("child", child);
  archive->readwrite("axis", axis);
  archive->readwrite("axis_sign", axis_sign);
  archive->readwrite("children", children);
}
#endif

void DynBVH_D::readwrite(ArchiveElement* archive) {
  MantaRTTI<AccelerationStructure>::readwrite(archive, *this);
  archive->readwrite("group", currGroup);
  archive->readwrite("object_ids", object_ids);
  archive->readwrite("nodes", nodes);
  if (archive->reading()) {
    int num_nodes_nonatomic;
    archive->readwrite("num_nodes", num_nodes_nonatomic);
    num_nodes.set(num_nodes_nonatomic);
  } else {
    int num_nodes_nonatomic = num_nodes;
    archive->readwrite("num_nodes", num_nodes_nonatomic);
  }
}

