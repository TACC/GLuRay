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

#ifndef CDTIMER_H
#define CDTIMER_H

#include <time.h>
#include <iostream>
#include <sys/time.h>

// basic timer class
// usage:  timer.start, run app, timer.stop.
// time is averaged over num_samples
class CDTimer
{
public:
  CDTimer(int num_samples = 1)
    : _num_samples(num_samples), _current(0), _sum(0)
  {
    if (_num_samples <= 0)
      _num_samples = 1;
    _samples = new double[num_samples];
    reset();
  }
  void start()
  {
    _last = ((clock ()) );
        gettimeofday(&t1, NULL);

  }
  void stop()
  {
    unsigned long long current = ((clock ()) );
    double dt = static_cast<float>(current-_last)/ static_cast <float> (CLOCKS_PER_SEC);
    gettimeofday(&t2, NULL);
    dt = ((t2.tv_sec*1000000.0 + t2.tv_usec) - (t1.tv_sec*1000000.0 + t1.tv_usec))* 0.000001;
 //   std::cout << "dt: " << dt << std::endl;
    if (_current >= _num_samples)
      _sum -= _samples[(_current+1)%_num_samples];
    _samples[_current%_num_samples] = dt;
    _sum += dt;
    _current++;
    _last = current;
  }
  void reset()
  {
    _current = 0;
    _sum = 0;
  }
  float getFPS()
  {
    return 1.0f / (_sum / _num_samples);
  }
  float getDelta()
  {
    return (_sum/static_cast<float>(_num_samples));
  }
protected:
  timeval t1,t2;
  int _num_samples, _current;
  double* _samples;
  unsigned long long _last;
  double _sum;
};


#endif
