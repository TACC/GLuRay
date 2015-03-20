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
