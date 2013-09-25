/*
ice_semaphore.h
 copyright 2004, David E. DeMarle
 Terms of use:
   1) This header must remain unmodified.
   2) Use of this software for non-academic purposes requires permission of the author.
   3) The author assumes no liability for any damages resulting from its use.
*/


#ifndef _ICE_SEMAPHORE_H_
#define _ICE_SEMAPHORE_H_

#include <Core/Thread/Mutex.h>

#define elog(s) //cout s
#define ilog(s) //cout s

namespace Manta
{

  class ice_semaphore {
    //sem_t *sem;
    Mutex *mutex;
  public:
    volatile int count;
  public:
    ice_semaphore();
    ~ice_semaphore();

    ice_semaphore(const ice_semaphore& copy) {
      count = copy.count;
      mutex = new Mutex("");
    }
    ice_semaphore& operator=(const ice_semaphore& rhs) {
      if (this == &rhs) return *this;
      count = rhs.count;
      // do not copy mutex.
      return *this;
    }

    void get_access() {
      //   ilog( << "SEM: Getting access to semaphore " << endl);

      mutex->lock();
      count = count + 1;
      //if (count > 16) printf("count already at %d!\n", count);
      mutex->unlock();

      //ilog( << "SEM: Got access to semaphore " << endl);
    }

    void release_access() {
      ilog( << "SEM: Releasing access to semaphore " << endl);

      mutex->lock();
      count = count - 1;
      mutex->unlock();

      ilog( << "SEM: Released access to semaphore " << endl);
    }

    void get_sole_access() {
      ilog( << "SEM: Getting sole access to semaphore " << endl);

      bool gotten = false;
      while (!gotten) {
        mutex->lock();
        if (count == 0)
          gotten = true;
        else {
          mutex->unlock();
        }
      }

      ilog( << "SEM: Got sole access to semaphore " << endl);
    }

    void release_sole_access() {
      ilog( << "SEM: Releasing sole access to semaphore " << endl);

      mutex->unlock();

      ilog( << "SEM: Released sole access to semaphore " << endl);
    }

    void release_sole_access_but_retain() {
      ilog( << "SEM: Releasing sole access, w/ retain to semaphore " << endl);

      count = 1;
      mutex->unlock();

      ilog( << "SEM: Released sole access, w/ retain to semaphore " << endl);
    }

//     bool try_get_access();
//     bool try_get_sole_access();
  };

};
#endif //_ICE_SEMAPHORE_H_
