/*
ice_semaphore.cc
 copyright 2004, David E. DeMarle
 Terms of use:
   1) This header must remain unmodified.
   2) Use of this software for non-academic purposes requires permission of the author.
   3) The author assumes no liability for any damages resulting from its use.
*/


#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <ice_semaphore.h>

#include <iostream>
using namespace std;
// #define elog(s) cout s
// #define ilog(s) //cout s

using namespace Manta;

ice_semaphore::ice_semaphore() {

  mutex = new Mutex("ice_semaphore");
//   sem = new sem_t();

//   if (sem_init(sem, 0, 0) != 0){
//     elog( << "SEM: Error creating semaphore" << errno << endl);
//   }
  count = 0;
}

ice_semaphore::~ice_semaphore() {
  delete mutex;
//   int mysemstat = sem_post(sem);

//   if (mysemstat == -1) {
//     elog( << "SEM: Semaphore Release Error " << errno << endl);
//   }
//   if(sem_destroy(sem) != 0){
//     elog( << "SEM: Error destroying semaphore " << errno << endl);
//   }
//   delete sem;
}

/*
//when a thread uses a dm, it uses this to prevent others from deleting it
bool ice_semaphore::try_get_access() {
  ilog( << "SEM: Trying to get access to semaphore " << endl);

  bool rc = false;

  int mysemstat = sem_trywait(sem);

  if (mysemstat == 0) {
    count = count + 1;
    mysemstat = sem_post(sem);
    if (mysemstat == -1) {
      elog( << "SEM: Semaphore Release Error " << errno << endl);
      exit(-1);
    }
    rc = true;
  } else {
    ilog( << "SEM: could not, it's being accessed " << endl);
  }

  if (rc) {
    ilog( << "SEM: Got access to semaphore " << endl);
  } else {
    ilog( << "SEM: Failed to get access to semaphore " << endl);
  }

  return rc;
}


bool ice_semaphore::try_get_sole_access() {
  ilog( << "SEM: Trying to get sole access to semaphore " << endl);

  bool rc = false;
  int mysemstat = sem_trywait(sem);
  if (mysemstat == 0) {
    if (count == 0) {
      rc = true;
    } else {
      ilog( << "SEM: could not, count is " << count << endl);
      mysemstat = sem_post(sem);
      if (mysemstat == -1) {
    elog( << "SEM: Semaphore Release Error " << errno << endl);
    exit(-1);
      }
    }
  } else {
    ilog( << "SEM: could not, it's being accessed " << endl);
  }

  if (rc) {
    ilog( << "SEM: Got sole access to semaphore " << endl);
  } else {
    ilog( << "SEM: Failed to get sole access to semaphore " << endl);
  }
  return rc;
}
*/
