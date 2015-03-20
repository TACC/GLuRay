//
// nvTime.h - Timer and perf counter classes
//
//
// Author: Samuel Gateau
// Email: sdkfeedback@nvidia.com
//
// Copyright (c) NVIDIA Corporation. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#ifndef NV_TIME_H
#define NV_TIME_H

namespace nv
{
    //*************************************************************************
    // Timer
    class Timer 
    {
    public:
        /******************************** METHODS *********************************/

	    /**
	     * Default constructor.
	     */
	    Timer();

        /**
	     * Destructor.
	     */
	    ~Timer();

	    /**
	     * Start the timer (Reset total elapsed time).
	     * Stop the timer.
	     * Check if the timer is started.
	     */
	    void start();
	    void stop();
	    bool isStarted() const { return mStartTime != -1.0; }

	    /** 
	     * Get the total timer elapsed time since start [s].
	     */
	    double getTotalElapsedTime() const;

	    /** 
	     * Get the timer elapsed time since last 
	     * call to the same method or start [s].
	     */
	    double getElapsedTime() const;

	    /**
	     * Query the current Application time.
	     * It's a date expressed in s.
	     */
	    static double queryAppTime();

    private:
        /******************************* ATTRIBUTES *******************************/

	    /**
	     * The start time
	     * -1 if not started;
	     */
	    double mStartTime;
    	
	    /**
	     * The last time queried.
	     */
	    mutable double mLastQueryTime;

	    /**
	     * The inverse frequency of the CPU on which the thread is running and used
	     * to measure the elapsed time.
	     */
	    static double msInvFrequency;

	    /******************************** METHODS *********************************/

	    /**
	     * initialize the inv frequency (done once on the first timer created.
	     */
	    static void initializeClass();
    };


    //*************************************************************************
    // FrameTimer
    class  FrameTimer : public Timer
    {
    public:
        /******************************** METHODS *********************************/

	    /**
	     * Default constructor.
	     */
        FrameTimer() : 
            Timer(),
            mCurrentFrameNb(0),
            mAverageFrameNb(0),
            mCurrentFrameDuration(0.0)
        {}

        /**
	     * Destructor.
	     */
        ~FrameTimer() {}
 
        /** 
         * Notify a new frame
         * Evaluate the current frame duration
         */
        void newFrame()
        {
            mCurrentFrameNb++;
            mAverageFrameNb++;
            if (mAverageFrameNb > 10)
            {
                mCurrentFrameDuration =  getElapsedTime() / ((double) mAverageFrameNb);
                mAverageFrameNb = 0;
            }
        }

        double getFrameDuration() const { return mCurrentFrameDuration; }
        double getFramerate() const { return (1.0/mCurrentFrameDuration); }
        int getFrameNb() const { return mCurrentFrameNb; }
 
    private:
        /******************************* ATTRIBUTES *******************************/

        /**
         * The current frame nb
         */
        int mCurrentFrameNb;
        int mAverageFrameNb;

        /**
         * The current frame duration
         */
        double mCurrentFrameDuration;
    };
};

#endif  // NV_TIME_H
