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

// Original author: Thiago Ize

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

#ifndef _MANTA_CORE_DISTRIBUTEDDATA_H
#define _MANTA_CORE_DISTRIBUTEDDATA_H

#include <ice_semaphore.h>
#include <DSM_Data.h>

#include <mpi.h>
#include <iostream>
#include <stdio.h>
using namespace std;

#include <Core/Thread/Mutex.h>
#include <Core/Thread/Barrier.h>
#define llog(x) cout x

//#define ALL_RESIDENT

namespace Manta
{
  template<typename T>
  class DistributedData {
  public:

    class DatumBlock {
    public:
      DatumBlock() {};
      DatumBlock(T* blockData, int key) :
        key(key),
        blockData(blockData)
//         lastaccess(-MAXFLOAT)
      {

//         invcount = 0;
//         writing_node = -1;
//         sem2 = new Semaphore("RW", 0);
      }
      //~DatumBlock();
      int key;
      T* blockData;
//       double lastaccess;

      ice_semaphore semaphore; //for general access

//       int writing_node; //-1 if noone, else node number that is writing to it
//       Semaphore *sem2; //used to sleep threads until they have write access
//       int invcount; //countdown until all other nodes have invalidated
    };

    DatumBlock *cache;
    int blksize; // size (in bytes) of a block (a block is an entry/datum in a cache)
    int rs_size; // number of blocks in my fixed/permanent data part of the cache
    int lc_size; // number of blocks in my shared cache

    // Have a shared cache for the stuff we know ahead of time will be super
    // well used.  For instance, the root of the BVH tree will always be
    // traversed by every single ray.  For simplicity, we will say that the
    // first sharedRS_size blocks in the localData will be the shared data.
    // For the BVH, we can reorder it so that the first sharedRS_size blocks is
    // really just a single big block (in the reordering, we just change the
    // block size for the first block).
    int sharedRS_size; // number of blocks at start of RS

    int numNodes;
    int myRank;

    int totalNumDatums;
    int datumsPerBlock; // number of datums in a block

    T* localData; // My fixed local data.
    T* cacheData; // My cache for remote data.

    Barrier barrier; // For stats

    //#define USE_VICTIM_CACHE
#ifdef USE_VICTIM_CACHE
    T* victimData;

    static const int victimCacheSize = 8;

    DatumBlock *victimCache;

    mutable Mutex victimMutex;
    mutable int nextVictim;
#endif
#define NUM_WIN 8
    Mutex* getMutex[NUM_WIN];
    MPI::Win win[NUM_WIN];

#define DSM_STATS
#ifdef DSM_STATS
    struct Stats {
      Stats () : numAccumulations(0) { reset(); }

      void reset() {
        nGetData = nRes = nLocal = nRemote = nEvictions = 0;
        timeRemote = timeRemote_max = timeRDMA = 0;
        timeRemote_min = 1e15;// arbitrary big number

        timeRDMA_min = 1e15;
        timeRDMA_max = 0;
      }

      unsigned long nGetData;
      unsigned long nRes;
      unsigned long nLocal;
      unsigned long nRemote;
      unsigned long nEvictions;
      double timeRemote;
      double timeRemote_min;
      double timeRemote_max;
      double timeRDMA;

      double timeRDMA_min;
      double timeRDMA_max;

      size_t totalMemoryUsed; // not automatically reset.

      int numAccumulations;  // not automatically reset!

      // hopefully big enough to keep any false sharing among different
      // processors from occuring.
      char emptySpace[128];

      void print(int numProcs, int n=1) {
        //printf("Node: %d\t datumSize: %ld\n", myRank, sizeof(T));
#if 0
        printf("resident gets: %ld \t %.3lf\n", long(nRes/n+.9),
                                              100*(double)nRes/nGetData);
        printf("in cache gets: %ld \t %.3lf\n", long(nLocal/n+.9),
                                              100*(double)nLocal/nGetData);
        printf("remote gets:   %ld \t %.3lf\n", long(nRemote/n+.9),
                                              100*(double)nRemote/nGetData);
        printf("evictions:     %ld \t %.3lf\n", long(nEvictions/n+.9),
                                              100*(double)nEvictions/nGetData);
        printf("total gets:    %ld \n", long(nGetData/n+.9));
        if (nRemote > 0) {
          //printf("avg remote get time:%.2lfms \n", timeRemote/numProcs*1000/n);
        printf("avg remote get time/element: %.3lfus \n", timeRemote/nRemote*1e6);
        printf("min remote get time:%.4lfms \n", timeRemote_min*1000);
        printf("max remote get time:%.2lfms \n", timeRemote_max*1000);
        //printf("avg per thread total RDMA get time:  %.2lfms \n", timeRDMA/numProcs*1000/n);
        printf("min RDMA get time:  %.3lfus \n", timeRDMA_min*1e6);
        printf("max RDMA get time:  %.3lfus \n", timeRDMA_max*1e6);
        }

        printf("total Memory Used: %ld\n", totalMemoryUsed);
#else
        printf("dsm_stats: ");
        printf("%ld\t", long(nRes/n+.9));
        printf("%ld\t", long(nLocal/n+.9));
        printf("%ld\t", long(nRemote/n+.9));
        if (nRemote > 0) {
        printf("%.3lf\t", timeRemote/nRemote*1e6);
        printf("%.3lf\t", timeRDMA_min*1e6);
        printf("%.3lf\t", timeRDMA_max*1e6);
        }
        else {
          printf("- \t - \t - \t");
        }
        printf("%ld\t", totalMemoryUsed);
#endif
        printf("\n");
      }

      void merge(const Stats& otherStat) {
        nGetData += otherStat.nGetData;
        nRes += otherStat.nRes;
        nLocal += otherStat.nLocal;
        nRemote += otherStat.nRemote;
        nEvictions += otherStat.nEvictions;
        timeRemote += otherStat.timeRemote;
        if (otherStat.timeRemote > 0) {
          timeRemote_min = Min(timeRemote_min, otherStat.timeRemote);
          timeRemote_max = Max(timeRemote_max, otherStat.timeRemote);
          timeRDMA += otherStat.timeRDMA;
          timeRDMA_min = Min(timeRDMA_min, otherStat.timeRDMA_min);
          timeRDMA_max = Max(timeRDMA_max, otherStat.timeRDMA_max);
        }



        //printf("%d/%d took avg %lfus per RDMA\n", myRank, i, stats[i].timeRemote/stats[i].nRemote*1e6);
      }
    };

    mutable vector<Stats> stats; // one per thread

    Stats runningTotalStat;
    static const int StatsToCollect=20;

    void accumulateStats(Stats &finalStats) const {
      for (size_t i=0; i < stats.size(); ++i) {
        finalStats.merge(stats[i]);
      }
      finalStats.numAccumulations++;
    }


    void merge(Stats& myStats) {
      if (myRank==0) {
        for (int i=1; i < numNodes; ++i) {
          Stats otherStats;
          MPI::COMM_WORLD.Recv(&otherStats, sizeof(Stats), MPI_BYTE, MPI_ANY_SOURCE, 100+sizeof(T));
          myStats.merge(otherStats);
        }
        myStats.totalMemoryUsed = size_t(blksize)*(rs_size+lc_size);
      }
      else {
        MPI::COMM_WORLD.Send(&myStats, sizeof(Stats), MPI_BYTE, 2, 100+sizeof(T));
      }
    }

    void updateStats(int proc, int numProcs)
    {
      if (myRank >= 0 && proc == 0) {
//         Stats finalStats;
//         accumulateStats(finalStats);
//         finalStats.print(numProcs);

        accumulateStats(runningTotalStat);
        const int warmup = 40;
        if (runningTotalStat.numAccumulations == warmup) // The warmup (hardcoded)
          runningTotalStat.reset();
        if (runningTotalStat.numAccumulations > warmup) {
          //printf("Node: %d\t datumSize: %ld\n", myRank, sizeof(T));
          //runningTotalStat.print(numProcs, runningTotalStat.numAccumulations-warmup);
          if (runningTotalStat.numAccumulations == warmup+StatsToCollect) {
            merge(runningTotalStat);
            if (myRank==0) {
              //printf("Node: %d\t datumSize: %ld\n", myRank, sizeof(T));
              printf("\n");
              runningTotalStat.print(numProcs, runningTotalStat.numAccumulations-warmup);
            }
          }
        }

        stats.resize(numProcs);
      }

      barrier.wait(numProcs);

      stats[proc].reset();
    }

#endif

    DistributedData() : cache(NULL), sharedRS_size(0), totalNumDatums(0),
                        localData(NULL), cacheData(NULL), barrier("")
#ifdef USE_VICTIM_CACHE
                      , victimData(NULL), victimCache(NULL),
                        victimMutex("victim mutex"), nextVictim(0)
#endif
    {
      numNodes = MPI::COMM_WORLD.Get_size()-2;
      myRank = MPI::COMM_WORLD.Get_rank()-2;

#ifdef DSM_STATS
      stats.resize(16);
#endif

      for (int i=0; i < NUM_WIN; i++) getMutex[i] = new Mutex("get mutex");
    }

    ~DistributedData() {
      if (cache)
        delete[] cache;

      if (localData)
        MPI::Free_mem(localData);
      if (cacheData)
        MPI::Free_mem(cacheData);

      for (int i=0; i < NUM_WIN; ++i)
        win[i].Free();

#ifdef USE_VICTIM_CACHE
      delete[] victimData;
      delete[] victimCache;
#endif
    }

#ifdef ALL_RESIDENT
    //determines which node owns the block identified by key
    inline int owner(const int key) const {
      return myRank;
    }
    //determines the offset into the res_set from the key
    inline int rs_position(const int key) const {
      return key;
    }
#else
    //determines which node owns the block identified by key
    inline int owner(const int key) const {
      return key < sharedRS_size ? myRank : (key-sharedRS_size)%numNodes;
//       return key%numNodes;
    }
    //determines the offset into the res_set from the key
    inline int rs_position(const int key) const {
      return key < sharedRS_size ? key : sharedRS_size + ((key-sharedRS_size) / numNodes);
//       return key/numNodes;
    }
#endif

    inline int cachePosition(const int key) const {
      const int newKey = key - sharedRS_size;
      return (newKey - (newKey + (numNodes-myRank))/numNodes) % lc_size;
      //return newKey % lc_size;
    }

    /* how many non local blocks can I cache?*/
    inline int LC_size() const {return lc_size;};
    /* how many local blocks do I have?*/
    inline int RS_size() const {return rs_size;};
  /* how many blocks are in the entire shared memory?*/
    inline int Blocks() const { return rs_size * numNodes; };


    void makeProgress(const int proc) const {
      if (proc == 0)
      {
        static int count=0;
        count = (count+1)%64;
        if (count == 0) {
          int flag;
          MPI_Status status;
          MPI_Iprobe(myRank, -1, MPI_COMM_WORLD, &flag, &status);
        }
      }
    }

    T const* get_data(const int key, const int proc) const {
//       if (key < 0 || key > rs_size*numNodes) {
//         printf("Error: key is invalid: %d\n.  Rank=%d", key, myRank);
//         exit(1);
//       }
#ifdef DSM_STATS
      stats[proc].nGetData++;
#endif

#ifdef ALL_RESIDENT
      return &localData[key*datumsPerBlock];
      //return cache[0].blockData; // TODO: USE THIS
#endif
      // Special case this to make it fast.
      if (key < sharedRS_size) {
#ifdef DSM_STATS
      stats[proc].nRes++;
#endif
        return cache[0].blockData;
      }

      const int own = owner(key);
      T const* blockData = 0;

      if (own == myRank) {
        //llog(<< "DM("<<myRank<<"): answering request for " << key << " which is mine " << endl);
        const int pos = rs_position(key);
        blockData = cache[pos].blockData;
#ifdef DSM_STATS
      stats[proc].nRes++;
#endif
      }
      else {
#ifdef DSM_STATS
        double startTime = MPI::Wtime();
#endif
        const int pos = cachePosition(key) + rs_size;

        cache[pos].semaphore.get_access();

        if (cache[pos].key == key) {
//           if (myRank == 1)
//           llog(<< "DM("<<myRank<<"): answering request for " << key << " which is not mine but is in my cache. " << endl);

          blockData = cache[pos].blockData;
#ifdef DSM_STATS
          stats[proc].nLocal++;
#endif
        } else {
#ifdef DSM_STATS
          stats[proc].nRemote++;

          // replace current block in cache with new block.
          if (cache[pos].key != -1) {
            stats[proc].nEvictions++;
            //printf("%d Cache wasn't big enough! (%d)=%d -> %d .   ",myRank, pos, cache[pos].key, key);
          }
#endif
//           cout<< "DM("<<myRank<<"): answering request for " << key
//               << " which is not mine and I'll need to RDMA it from. " << own
//               <<"which will replace key: " << cache[pos].key<<endl;

          // We don't have the data and it's not in the cache.  We'll need to
          // bring it in, but before we do, we need to make sure that if we evict
          // something, it's not data that's being used by another thread.



          // So someone (maybe me?) can get sole access
          cache[pos].semaphore.release_access();
//           cache[pos].semaphore.get_sole_access();

#ifdef USE_VICTIM_CACHE
          victimMutex.lock();
          for (int i=0; i < victimCacheSize; ++i) {
            if (victimCache[i].key == key) {
              victimCache[i].semaphore.get_access();
              victimMutex.unlock();
//               printf("Found block in  victimCache\n");


              if ( ((int*)victimCache[i].blockData)[6] != ((int*)&originalData[key*datumsPerBlock])[6]) {

                int pos = cachePosition(key) + rs_size;
                int rs_pos = rs_position(key);
                printf("%d own%d myRank%d rs_size:%d key:%d pos%d rs_pos%d\n", whatwedid, own, myRank, rs_size, key, pos, rs_pos);
                cout << ((float*)victimCache[i].blockData)[0]<< "!= " <<((float*)&originalData[key*datumsPerBlock])[0]<<endl;
                cout << ((float*)victimCache[i].blockData)[1]<< "!= " <<((float*)&originalData[key*datumsPerBlock])[1]<<endl;
                cout << ((int*)victimCache[i].blockData)[6]<< "!= " <<((int*)&originalData[key*datumsPerBlock])[6]<<endl;
//         exit(1);
                printf("victimCache[i].key==%d,  key==%d\n", victimCache[i].key, key);
      }


              return victimCache[i].blockData;
            }
          }
          victimMutex.unlock();
#endif
          //static Mutex getMutex[8] = {Mutex("MPI_get mutex")};

            //Nope, no one updated the cache, so it's up to me.
#if 1
//               cout << "entering win_lock for key/pos/own "<<key<<" " <<pos<<" "<<own<<endl;

              T blockStorage[datumsPerBlock];

#ifdef DSM_STATS
              double startTimeRDMA = MPI::Wtime();
#endif
              //getMutex[proc]->lock();
              const int winID = proc;
              const int nodeOwnerID = own+2;

//In MVAPICH2 1.6, calling win_lock() should have very little overhead. No communication is performed
              int err = MPI_Win_lock(MPI_LOCK_SHARED, nodeOwnerID, MPI_MODE_NOCHECK*0, win[winID]);
//               if (err != MPI_SUCCESS)
//                 cout << "ERROR lock: " <<err<<endl;
//            err = MPI_Get(cache[pos].blockData, blksize, MPI_BYTE,

              // Also, here more setup occurs in MPI, but no actual communication takes place.
              err = MPI_Get(blockStorage, blksize, MPI_BYTE,
                            nodeOwnerID, size_t(rs_position(key))*blksize, blksize, MPI_BYTE, win[winID]);
//               if (err != MPI_SUCCESS)
//                 cout << "ERROR get: " <<err<<endl;

              err = MPI_Win_unlock(nodeOwnerID, win[winID]);
//               if (err != MPI_SUCCESS)
//                 cout << "ERROR unlock: " <<err<<endl;
              //getMutex[proc]->unlock();


#ifdef DSM_STATS
          double endTimeRDMA = MPI::Wtime();
          double time = endTimeRDMA-startTimeRDMA;
          stats[proc].timeRDMA+=time;
          stats[proc].timeRDMA_min = Min(stats[proc].timeRDMA_min, time);
          stats[proc].timeRDMA_max = Max(stats[proc].timeRDMA_max, time);
//           if (time*1e6 > 300)
//             printf("%d(%d) read from %d %d/%d-> %.3fus\n", myRank, datumsPerBlock, nodeOwnerID-2,  key, pos, time*1e6);
#endif

              // Maybe another thread already updated the cache for us?  If so,
              // this saves us from having to wait for all other threads to
              // stop using this data so we can get sole access.
              cache[pos].semaphore.get_access();
              if (cache[pos].key == key) {
//             if (cache[pos].key == key) {
//               static int count = 0;
//               ++count;
//               //if (count%10==0)
//               printf("%d %d\n",myRank, count);
//             }

                blockData = cache[pos].blockData;
                return blockData;
              }
              else {
                cache[pos].semaphore.release_access();
                cache[pos].semaphore.get_sole_access();

#ifdef USE_VICTIM_CACHE
                victimMutex.lock();
                for (int i=0; i < victimCacheSize; ++i) {
                  if (victimCache[nextVictim].semaphore.count == 0) {
//                     printf("%d/%d Found where to place victim %d\n", myRank, proc, nextVictim);
                    //victimCache[nextVictim].semaphore.get_access();
                    memcpy(victimCache[nextVictim].blockData, cache[pos].blockData, blksize);
                    victimCache[nextVictim].key = cache[pos].key;
                    nextVictim = (nextVictim+1)%victimCacheSize;
                    break;
                  }
                  nextVictim = (nextVictim+1)%victimCacheSize;
                }
                victimMutex.unlock();
#endif
                memcpy(cache[pos].blockData, blockStorage, blksize);
              }
//               cout << "leaving win_lock for key/pos/own "<<key<<" " <<pos<<" "<<own<<endl;
#else
            memcpy(cache[pos].blockData, &originalData[key*datumsPerBlock], blksize);
#endif
            blockData = cache[pos].blockData;
            cache[pos].key = key;

          cache[pos].semaphore.release_sole_access_but_retain();
#ifdef DSM_STATS
          double endTime = MPI::Wtime();
          stats[proc].timeRemote+=endTime-startTime;
#endif

        }
      }

#if 0
      if ( ((int*)blockData)[6] != ((int*)&originalData[key*datumsPerBlock])[6]) {

        int pos = cachePosition(key) + rs_size;
        int rs_pos = rs_position(key);
        printf("%d own%d myRank%d rs_size:%d key:%d pos%d rs_pos%d\n", whatwedid, own, myRank, rs_size, key, pos, rs_pos);
        cout << ((float*)blockData)[0]<< "!= " <<((float*)&originalData[key*datumsPerBlock])[0]<<endl;
        cout << ((float*)blockData)[1]<< "!= " <<((float*)&originalData[key*datumsPerBlock])[1]<<endl;
        cout << ((int*)blockData)[6]<< "!= " <<((int*)&originalData[key*datumsPerBlock])[6]<<endl;
//         exit(1);
      }
#endif

      return blockData;
    }


    void release_data(const int key) const {

#ifdef ALL_RESIDENT
      return;
#endif

      const int own = owner(key);

      if (own != myRank) {
        int pos = cachePosition(key) + rs_size;

#ifdef USE_VICTIM_CACHE
        if (cache[pos].key == key)
          cache[pos].semaphore.release_access();
        else {
//           printf("Releasing victim key=%d\n", key);
          victimMutex.lock();
          for (int i=0; i < victimCacheSize; ++i) {
            if (victimCache[i].key == key) {
              victimCache[i].semaphore.release_access();
              break;
            }
          }
          victimMutex.unlock();
        }
#else
          cache[pos].semaphore.release_access();
#endif
      }
    }

    const T* originalData; // for debugging

    void loadAllResident(DSM_Data* DSM_data) {

      if (myRank >= 0) {
#if 1
      const int numPasses = 16;
      for (int pass=0; pass < numPasses; ++pass) {
        if (myRank==0)
          printf("pass %d of %d\n",pass, numPasses);
        size_t myStart = size_t(myRank)*datumsPerBlock*rs_size/numNodes;
        size_t myEnd = size_t(myRank+1)*datumsPerBlock*rs_size/numNodes;

        size_t length = (myEnd-myStart)/numPasses;
        myStart = myStart + length*pass;
        myEnd = myStart + length;

        if (pass+1 == numPasses)
          myEnd = size_t(myRank+1)*datumsPerBlock*rs_size/numNodes;

        if (myEnd > size_t(rs_size)*datumsPerBlock)
          myEnd = rs_size*datumsPerBlock;
        DSM_data->getDatums(&localData[myStart], myStart, myEnd-myStart);
        // Now that everyone has their own data, let's exchange with each other.

        MPI_Request s_reqs[numNodes];
        for (int i=0; i < numNodes; ++i) {
          if (i != myRank) {
            MPI_Isend(&localData[myStart], sizeof(T)*(myEnd-myStart),
                      MPI_BYTE, i+2, 200, MPI_COMM_WORLD, &s_reqs[i]);
          }
          else
            s_reqs[i] = MPI_REQUEST_NULL;
        }

      MPI_Request r_reqs[numNodes];
      for (int i=0; i < numNodes; ++i) {
        if (i != myRank) {
          size_t start = size_t(i)*datumsPerBlock*rs_size/numNodes;
          size_t end = size_t(i+1)*datumsPerBlock*rs_size/numNodes;

          size_t length = (end-start)/numPasses;
          start = start + length*pass;
          end = start + length;

          if (pass+1 == numPasses)
            end = size_t(i+1)*datumsPerBlock*rs_size/numNodes;

          if (end > size_t(rs_size)*datumsPerBlock)
            end = rs_size*datumsPerBlock;

          MPI_Irecv(&localData[start], sizeof(T)*(end-start),
                    MPI_BYTE, i+2, 200, MPI_COMM_WORLD, &r_reqs[i]);
        }
        else
          r_reqs[i] = MPI_REQUEST_NULL;
      }

      MPI_Waitall(numNodes, s_reqs, MPI_STATUSES_IGNORE);
      MPI_Waitall(numNodes, r_reqs, MPI_STATUSES_IGNORE);
      }
      cache[0] = DatumBlock(&localData[0], 0); // In case anyone tries to read the first node
#else
      DSM_data->getDatums(&localData[0], 0, datumsPerBlock*rs_size);
#endif
      }
      MPI_Barrier(MPI_COMM_WORLD);
    }

    void preloadCache() {

      MPI_Barrier(MPI_COMM_WORLD);
      if (myRank >= 0) {

        const int winID = 0; // only a single thread does this.
        const int totalBlocks = Ceil(float(totalNumDatums)/datumsPerBlock);

        double timeStart = MPI::Wtime();
        int nReads = 1;
        int lastKey = 0;
        for (int key=0; key < totalBlocks; ++key) {
          const int own = owner(key);
          //         if (own == (myRank+1)%numNodes) // Only get data from node next to you.
          if (own == myRank)
            continue;
          const int pos = cachePosition(key) + rs_size;
          if (cache[pos].key != -1) continue;

          // Figure out how fast we are reading in the data.
          const int incr = 10000;
          if (nReads%incr==0) {
            double timeEnd = MPI::Wtime();
            double time = (timeEnd-timeStart);//seconds
            if (time > 5) {
              double Bps = nReads*datumsPerBlock*sizeof(T)/time;
              double MBps = Bps/1024/1024;
              timeStart=timeEnd;
              printf("%d->%.3lfMB/s\t%f\n", myRank, MBps, float(key-lastKey)/nReads);
              lastKey=key;
              nReads = 0;
            }
          }
          nReads++;

          const int nodeOwnerID = own+2;
          int err = MPI_Win_lock(MPI_LOCK_SHARED, nodeOwnerID, 0, win[winID]);
          err = MPI_Get(cache[pos].blockData, blksize, MPI_BYTE,
                        nodeOwnerID, size_t(rs_position(key))*blksize, blksize, MPI_BYTE, win[winID]);
          err = MPI_Win_unlock(nodeOwnerID, win[winID]);
          cache[pos].key = key;
        }
      }
      MPI_Barrier(MPI_COMM_WORLD);//Barrier to ensure that progress is made in MPI_Get. Stupid MPI. Should be fixed by mvapich2-1.7!
    }

    void setupCache(int datumsPerBlock_, int lc_size_, int totalNumDatum, DSM_Data &DSM_data,
                    int firstNReplicated = 0) {
      setupCache(datumsPerBlock_, lc_size_, totalNumDatum, firstNReplicated);

#ifdef ALL_RESIDENT
      loadAllResident(&DSM_data);
      return;
#endif

      if (myRank < 0) return;

      int totalBlocks = Ceil(float(totalNumDatum)/datumsPerBlock);

      for (int i = 0; i < lc_size; i++) {
        const int key = -1; //flag remote blocks as unused
        cache[rs_size + i] = DatumBlock(&cacheData[i*datumsPerBlock], key);
      }

      double timeStart = MPI::Wtime();
      int nReads = 1;
      for (int key=0; key < totalBlocks; ++key) {

        // Figure out how fast we are reading in the data.
        const int incr = 10000;
        if (nReads%incr==0) {
          double timeEnd = MPI::Wtime();
          double time = (timeEnd-timeStart);//seconds
          if (time > 5) {
            double Bps = nReads*datumsPerBlock*sizeof(T)/time;
            double MBps = Bps/(1024*1024);
            timeStart=timeEnd;
            printf("%d->%lf\n", myRank, MBps);
            nReads = 1;
          }
        }

        if (owner(key) == myRank) { // resident memory
          nReads++;
          const int pos = rs_position(key);

          const int numDatums = datumsPerBlock*(key+1) > totalNumDatum ?
            totalNumDatum - key*datumsPerBlock : datumsPerBlock;

#if 0
          for (int i=0; i < numDatums; ++i) {
            DSM_data.getDatum(&localData[pos*datumsPerBlock+i], key*datumsPerBlock+i);
          }
#else
          DSM_data.getDatums(&localData[pos*datumsPerBlock], key*datumsPerBlock, numDatums);
#endif
          cache[pos] = DatumBlock(&localData[pos*datumsPerBlock], key);
        }
      }
#ifndef ALL_RESIDENT
      preloadCache();
#endif
    }

    void setupCache(int datumsPerBlock_, int lc_size_, int totalNumDatum, const T* data,
                    int firstNReplicated = 0) {
      setupCache(datumsPerBlock_, lc_size_, totalNumDatum, firstNReplicated);

      originalData = data;

      if (myRank < 0) {

#ifdef ALL_RESIDENT
        loadAllResident(NULL);
#else
        preloadCache();
#endif
        return;
      }

      int totalBlocks_rd = totalNumDatum/datumsPerBlock; // rd for rounded down

      for (int key=0; key < totalBlocks_rd; ++key) {
        if (owner(key) == myRank) {
          const int pos = rs_position(key);
          memcpy(&localData[pos*datumsPerBlock], &data[key*datumsPerBlock], blksize);
          cache[pos] = DatumBlock(&localData[pos*datumsPerBlock], key);
        }
      }
      if (totalBlocks_rd*datumsPerBlock < totalNumDatum) {
        const int key = totalBlocks_rd;
        if (owner(key) == myRank) {
          const int pos = rs_position(key);
          memcpy(&localData[pos*datumsPerBlock], &data[key*datumsPerBlock],
                 (totalNumDatum - key*datumsPerBlock)*sizeof(T));
          cache[pos] = DatumBlock(&localData[pos*datumsPerBlock], key);
        }
      }

      for (int i = 0; i < lc_size; i++) {
        const int key = -1; //flag remote blocks as unused
        cache[rs_size + i] = DatumBlock(&cacheData[i*datumsPerBlock], key);
      }
#ifndef ALL_RESIDENT
      preloadCache();
#endif
    }

  protected:
    void setupCache(int datumsPerBlock_, int lc_size_, int totalNumDatum_, int firstNReplicated)
    {

      if (myRank < 0)
        lc_size_ = 1;

      // Do we want to use all resident memory?
      printf("lc_size_: %d\n", lc_size_);

      totalNumDatums = totalNumDatum_;
      sharedRS_size = firstNReplicated;
      datumsPerBlock = datumsPerBlock_;

      blksize = datumsPerBlock*sizeof(T);
      rs_size = ((totalNumDatums/datumsPerBlock) / numNodes) + 1; // add 1 to round up
      const int redundantBlocks = static_cast<int>(sharedRS_size*(numNodes-1.0f)/numNodes+1);
      rs_size += redundantBlocks;

      if ((lc_size_+1)*datumsPerBlock >= totalNumDatums)
        lc_size = Max(1, (totalNumDatums/datumsPerBlock - rs_size) + 2 + redundantBlocks);
      else
        lc_size = totalNumDatums/datumsPerBlock;
      lc_size = Max(1, Min(lc_size_, lc_size));

#ifdef ALL_RESIDENT
      rs_size = (totalNumDatums/datumsPerBlock) + 1; // add 1 to round up
      lc_size = 1;
#endif

      int numblks = rs_size+lc_size;

      printf("setupCache(%d) called with %d datumsPerBlock, %d rs_size, %d lc_size, %d totalNumDatums\n",
             myRank, datumsPerBlock, rs_size, lc_size, totalNumDatums);

      //localData = new T[rs_size*datumsPerBlock];// data;
      //cacheData = new T[lc_size*datumsPerBlock];
      localData = (T*) MPI::Alloc_mem(size_t(rs_size)*datumsPerBlock*sizeof(T), MPI_INFO_NULL);
      cacheData = (T*) MPI::Alloc_mem(size_t(lc_size)*datumsPerBlock*sizeof(T), MPI_INFO_NULL);

      if (!localData || !cacheData) {
        printf("%d node had an Error allocating memeory in DistributedData\n", myRank+2);
        printf("localData=%p \tcacheData=%p\n", localData, cacheData);
        printf("amount requested: %ld and %ld\n", rs_size*datumsPerBlock*sizeof(T),
               lc_size*datumsPerBlock*sizeof(T));
      }

      cache = new DatumBlock[numblks];

#ifdef USE_VICTIM_CACHE
      victimCache = new DatumBlock[victimCacheSize];
      victimData = new T[victimCacheSize*datumsPerBlock];
      for (int i=0; i < victimCacheSize; ++i) {
        victimCache[i].key = -1;
        victimCache[i].blockData = &victimData[i*datumsPerBlock];
      }
#endif

      for (int i=0; i < NUM_WIN; ++i) {
        win[i] = MPI::Win::Create(localData,
                                  size_t(rs_size)*blksize, 1,
                                  MPI_INFO_NULL,
                                  MPI_COMM_WORLD);
      }
    }
  };

};
#endif
