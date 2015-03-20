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

#ifndef _MANTA_DYNBVH_D_H_
#define _MANTA_DYNBVH_D_H_

#include <Model/Groups/Group.h>
#include <Core/Geometry/BBox.h>
#include <Interface/RayPacket.h>
#include <Interface/AccelerationStructure.h>
#include <Core/Thread/AtomicCounter.h>
#include <Core/Thread/Barrier.h>
#include <DistributedData.h>
#include <Mesh_DSM.h>
namespace Manta
{
  class Task;
  class TaskList;

  class DynBVH_D : public AccelerationStructure, public DSM_Data
  {
  public:
    struct IAData
    {
      Real min_rcp[3];
      Real max_rcp[3];
      Real min_org[3];
      Real max_org[3];
      Real min_org_rcp[3];
      Real max_org_rcp[3];
    };

    struct BVHNode
    {
    public:
      BBox bounds;
      int child; // my child
      unsigned char axis; // 0 = x, 1 = y, 2 = z,
      unsigned char axis_sign; // 0 means left-right, 1 means right-left
      short children; // num children

      // 24 bytes + 4 bytes + 1 + 1 + 2 = 32 bytes

      inline void makeLeaf(int first_child, short num_children)
      {
        child = first_child;
        children = num_children;
        axis = 0;
        axis_sign = 0;
      }

      inline void makeInternal(int first_child, unsigned char _axis)
      {
        child = first_child;
        children = 0;
        axis = _axis;
        axis_sign = 0; // for now
      }

      inline bool isLeaf() const
      {
        return children != 0;
      }

      void readwrite(ArchiveElement* archive);
    };

    struct BVHBuildRecord {
      int objectBegin;
      int objectEnd;
    };

  protected:
    DistributedData<BVHNode> nodesDData;
    mutable Mesh_DSM* mesh_DSM;

    // For reading in from a file
    mutable ifstream in;
    streampos dataStart;
    virtual void getDatum(void* datum, size_t triID) const;
    virtual void getDatums(void *datums, size_t index, size_t num) const;
    BBox bounds;


    // NOTE(boulos): Because intersect is const, lazy build requires
    // that almost everything in here become mutable and that almost
    // all functions become const. How sad.
    mutable vector<BVHNode> nodes;
    mutable vector<int> object_ids;
    mutable vector<BVHBuildRecord> build_records;

    mutable vector<unsigned int> subtree_size; // number of nodes making up this subtree
    vector<unsigned int> subtreeList; // for load balancing parallel update
    unsigned int largeSubtreeSize;
    Mutex subtreeListMutex;
    bool subtreeListFilled;

    mutable AtomicCounter num_nodes;
    Group* currGroup;
    bool group_changed;
    Barrier barrier;

    mutable AtomicCounter nextFree;

    mutable vector<BBox> obj_bounds;
    mutable vector<Vector> obj_centroids;

    char* TaskListMemory;
    size_t CurTaskList;

    char* TaskMemory;
    size_t CurTask;

    char* TwoArgCallbackMemory;
    size_t CurTwoArgCallback;

    char* FourArgCallbackMemory;
    size_t CurFourArgCallback;

    char* FiveArgCallbackMemory;
    size_t CurFiveArgCallback;

    bool print_info;
  public:
    DynBVH_D(bool print = true) : mesh_DSM(NULL), num_nodes("DynBVH_D Num Nodes", 0), currGroup(NULL), group_changed(false), barrier("DynBVH_D barrier"), nextFree("DynBVH_D Next Free", 0), TaskListMemory(0), CurTaskList(0), TaskMemory(0), CurTask(0), TwoArgCallbackMemory(0), CurTwoArgCallback(0), FourArgCallbackMemory(0), CurFourArgCallback(0), FiveArgCallbackMemory(0), CurFiveArgCallback(0), print_info(print)
    {}
    virtual ~DynBVH_D();

    void setGroup(Group* new_group);
    Group* getGroup() const;
    void groupDirty(); // tells the acceleration structure that the group has changed

    virtual void addToUpdateGraph(ObjectUpdateGraph* graph,
                                  ObjectUpdateGraphNode* parent);

    void allocate() const;

    void printNode(int nodeID, int depth) const;

    int partitionObjects(int first, int last, int axis, float position) const;

    void preprocess(const PreprocessContext&);
    void intersect(const RenderContext& context, RayPacket& rays) const;

    // return the first index (between [rays.begin(),rays.end()]) which hits the box
    static int firstIntersects(const BBox& box, const RayPacket& rays, const IAData& ia_data);
    // return the last index which hits the box
    static int lastIntersects(const BBox& box, const RayPacket& rays);

  protected:
    BVHNode const& getNode(int nodeID, int &blockID, BVHNode const* &block,
                           const RenderContext& context) const;
    void intersectNode(int nodeID, int& blockID, BVHNode const* &block,
                       const RenderContext& context, RayPacket& rays,
                       const IAData& ia_data) const;

  public:
    void computeBounds(const PreprocessContext& context,
                       BBox& bbox) const
    {
      bbox.extendByBox(bounds);
      return;
    }

    void update(int proc=0, int numProcs=1);
    void rebuild(int proc=0, int numProcs=1);

    void build(const PreprocessContext& context,
               int nodeID, int objectBegin, int objectEnd);

    void setupDSM();

    int reorderNodes(const int nodesPerBlock, int count, int parent,
                     vector<BVHNode>& reorderedNodes);
    void reorderNodes(const int nodesPerBlock, const int nodesPerBlockTopLevel);

    Mesh_DSM::TriangleData* reorderMesh();
    void reorderMesh(unsigned int nodeID, Mesh_DSM::TriangleData* tris,
                     size_t &trisSize);

    void updateBounds(const PreprocessContext& context, int ID = 0);

    void readwrite(ArchiveElement* archive);

    virtual bool buildFromFile(const string &file);
    virtual bool saveToFile(const string &file);

  protected:

    void computeTraversalCost();
    VectorT<float, 2> computeSubTreeTraversalCost(unsigned int nodeID);

    struct PartitionData {
      BBox bounds_l, bounds_r;
      int axis;
      int split;
    };

    PartitionData partitionSAH(const PreprocessContext& context,
                               int nodeID,
                               int objBegin,
                               int objEnd) const;

    PartitionData partitionApproxSAH(const PreprocessContext& context,
                                    int nodeID,
                                    int objBegin,
                                    int objEnd) const;

    void seedSubtrees(const int nodeID, const unsigned int maxNodes);

    struct BVHCostEval
    {
      BBox bounds_r;
      float position;
      float cost;
      int num_left;
      int num_right;
      int event;
      int axis;
    };

    struct BVHSAHEvent
    {
      float position;
      int obj_id;
      float left_area;
      float right_area;
      int num_left;
      int num_right;
      float cost;
    };

    struct CompareBVHSAHEvent
    {
      bool operator()(const BVHSAHEvent& x, const BVHSAHEvent& y)
      {
        // add obj_id sorting in here automatically?
        return x.position < y.position;
      }
    };

    bool buildEvents(const PreprocessContext& context,
                     int parentID,
                     int first,
                     int last,
                     int axis,
                     BVHCostEval& eval) const;

#ifdef MANTA_SSE
    // DynBVH_D ports
    void templatedTraverse(const RenderContext& context, RayPacket& packet) const;

    int firstActivePort(RayPacket& packet, int firstActive, const BBox& box) const;
    int lastActivePort(RayPacket& packet, int firstActive, const BBox& box) const;

    int firstActiveSameSignFrustumPort(RayPacket& packet,
                                       const int firstActive,
                                       const BBox& bounds,
                                       const int signs[3],
                                       const __m128 sc_min_org[3],
                                       const __m128 sc_max_org[3],
                                       const __m128 sc_min_rcp[3],
                                       const __m128 sc_max_rcp[3],
                                       const __m128& max_t) const;

    int lastThatIntersectsSameSignPort(RayPacket& packet,
                                       const int firstActive,
                                       const BBox& box,
                                       const int signs[3]) const;
#endif

// #define COLLECT_STATS
#ifdef COLLECT_STATS
    struct Stats {
      Stats () { reset(); }

      void reset() {
        nIntersects = 0;
        nTraversals = 0;
        nTotalRays = 0;
        nTotalRaysInPacket = 0;
        nTotalPackets = 0;
        nLeavesVisited = 0;
      }

      long nIntersects;
      long nTraversals;
      long nTotalRays;
      long nTotalRaysInPacket;
      long nTotalPackets;
      long nLeavesVisited;

      // hopefully big enough to keep any false sharing among different
      // processors from occuring.
      char emptySpace[128];
    };

    mutable vector<Stats> stats; // one per thread

    Stats accumulateStats() const {
      Stats finalStats;
      for (size_t i=0; i < stats.size(); ++i) {
        finalStats.nIntersects += stats[i].nIntersects;
        finalStats.nTraversals += stats[i].nTraversals;
        finalStats.nTotalRays += stats[i].nTotalRays;
        finalStats.nTotalRaysInPacket += stats[i].nTotalRaysInPacket;
        finalStats.nTotalPackets += stats[i].nTotalPackets;
        finalStats.nLeavesVisited +=stats[i].nLeavesVisited;
      }
      return finalStats;
    }

    void updateStats(int proc, int numProcs)
    {
      if (proc == 0) {
        Stats finalStats = accumulateStats();

        printf("intersections per packet:        %f\n", (float)finalStats.nIntersects/finalStats.nTotalPackets);
        printf("node traversals per packet:      %f\n", (float)finalStats.nTraversals/finalStats.nTotalPackets);
        printf("leaves visited per packet:       %f\n", (float)finalStats.nLeavesVisited/finalStats.nTotalPackets);
        printf("average ray packet size:         %f\n", (float)finalStats.nTotalRaysInPacket/finalStats.nTotalPackets);
        printf("number of packets:               %ld\n", finalStats.nTotalPackets);
        printf("number of rays:                  %ld\n", finalStats.nTotalRays);
        printf("\n");

        stats.resize(numProcs);
      }

      barrier.wait(numProcs);

      stats[proc].reset();
    }
#endif

  };
};

#endif
