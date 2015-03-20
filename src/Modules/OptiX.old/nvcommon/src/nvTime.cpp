//
// nvTime.cpp - Timer and perf counter classes
//
//
// Author: Samuel Gateau
// Email: sdkfeedback@nvidia.com
//
// Copyright (c) NVIDIA Corporation. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#include "nvTime.h"

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

using namespace nv;

/**
 * The inverse frequency of the CPU on which the thread is running and used
 * to measure the elapsed time.
 */
double Timer::msInvFrequency = 0.0;
	
/**
 * initialize the inv frequency (done once on the first timer created.
 */
void Timer::initializeClass()
{
	if (!msInvFrequency )
	{
#ifdef WIN32
		LARGE_INTEGER lFreq;
		QueryPerformanceFrequency(&lFreq);
		msInvFrequency = 1.0 / double(lFreq.QuadPart);
#else
                msInvFrequency = 1.0;
#endif
	}
}

/**
 * Default constructor.
 */
Timer::Timer() :
	mStartTime(-1),
	mLastQueryTime(-1)
{
	initializeClass();
}

/**
 * Destructor.
 */
Timer::~Timer()
{
}

/**
 * Start the timer (Reset total elapsed time).
 * Stop the timer.
 */
void Timer::start()
{
	mStartTime = mLastQueryTime = queryAppTime();
}

void Timer::stop()
{
	mStartTime = mLastQueryTime = 0.0;
}

/** 
 * Get the total timer elapsed time since start [s].
 */
double Timer::getTotalElapsedTime() const
{
	return queryAppTime() - mStartTime;
}

/** 
 * Get the timer elapsed time since last 
 * call to the same method or start [s].
 */
double Timer::getElapsedTime() const
{
	if (isStarted())
	{
		double lTime = mLastQueryTime;
		mLastQueryTime = queryAppTime();
		return mLastQueryTime - lTime;
	}
	return 0.0;
}

/**
 * Query the current Application time.
 * It's a date expressed in s.
 */
double Timer::queryAppTime()
{
#ifdef WIN32
		LARGE_INTEGER lCount;
		QueryPerformanceCounter(&lCount);
		return (lCount.QuadPart * msInvFrequency);
#else
                double seconds;
                timeval time;
                gettimeofday(&time,0);
                seconds = time.tv_sec + (time.tv_usec/1e6f);
                return seconds;
#endif
}

