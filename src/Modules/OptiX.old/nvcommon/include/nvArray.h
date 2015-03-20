// array classes
//
// Copyright (c) NVIDIA Corporation. All rights reserved.
////////////////////////////////////////////////////////////////////////////////

#ifndef NV_ARRAY_H
#define NV_ARRAY_H

namespace nv {

// 2d array
template <class T>
class array2
{
public:
    typedef T value_type;

	array2(int width, int height, int channels=1)
	{
		w = width;
		h = height;
		c = channels;
		data = new T [w*h*c];
	}

	~array2()
	{
		delete [] data;
	}

	T & operator () (int x, int y, int channel=0)
	{
		if (x < 0) x += w;
		if (y < 0) y += h;
		if (x > w-1) x -= w;
		if (y > h-1) y -= h;
		return data[((y*w+x)*c)+channel];
	}
	
	T * get_data()
	{
		return data;
	}

private:
	int w, h, c;
	T *data;
};

};

#endif