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


#ifndef CD_MATH
#define CD_MATH

#include <cmath>

namespace glr
{

const float PI = 3.14159265;
const float PI2 = PI/2.0f; //pi over 2
const float DtoR = PI/180.0f; // degrees to radians

class Vector3D
{
public:
	Vector3D() { x = y = z = 0.0f; };
	Vector3D(const Vector3D &v) { x = v.x; y = v.y; z = v.z; };
	Vector3D(float nx, float ny, float nz) { x = nx; y = ny; z = nz; };
	
	Vector3D operator + (const Vector3D &v)
	{
		Vector3D temp;
		temp.x = x + v.x;
		temp.y = y + v.y;
		temp.z = z + v.z;
		return temp;
	};
	Vector3D operator - (const Vector3D &v)
	{
		Vector3D temp;
		temp.x = x - v.x;
		temp.y = y - v.y;
		temp.z = z - v.z;
		return temp;
	};
	Vector3D operator * (const Vector3D &v)
	{
		Vector3D temp;
		temp.x = x * v.x;
		temp.y = y * v.y;
		temp.z = z * v.z;
		return temp;
	};
	Vector3D operator * (float scalar)
	{
		Vector3D temp;
		temp.x = x * scalar;
		temp.y = y * scalar;
		temp.z = z * scalar;
		return temp;
	};
	Vector3D operator / (float scalar)
	{
		Vector3D temp;
		temp.x = x / scalar;
		temp.y = y / scalar;
		temp.z = z / scalar;
		return temp;
	};
	Vector3D operator += (const Vector3D &v)
	{
		x+=v.x; y+=v.y; z+=v.z;
		return *this;
	};
	Vector3D operator -= (const Vector3D &v)
	{
		x-=v.x; y-=v.y; z-=v.z;
		return *this;
	};
	Vector3D operator *= (const Vector3D &v)
	{
		x*=v.x; y*=v.y; z*=v.z;
		return *this;
	};
	Vector3D operator *= (float scalar)
	{
		x*=scalar; y*=scalar; z*=scalar;
		return *this;
	};
	Vector3D operator /= (float scalar)
	{
		x/=scalar; y/=scalar; z/=scalar;
		return *this;
	};
	Vector3D operator= (const Vector3D& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	};
	
	float Magnitude();
	Vector3D Normalize();
	float Dot(Vector3D &v);
	Vector3D Cross(const Vector3D &v);
	
	float x;
	float y;
	float z;

};

#define Idx(x,y)	((x*4)+y)

class Matrix
{
public:
	Matrix();
	Matrix(const Matrix &m);
	Matrix(float* m);
	float _data[16];
	
	void Zero();
	void Identity();
	
	Matrix operator * (Matrix &m)
	{
		//based on NEHE's code
		
		Matrix temp;
		
		for (int i = 0; i < 4; i++)
		{
			float row1 = _data[Idx(0, i)], row2 = _data[Idx(1, i)], row3 = _data[Idx(2, i)], row4 = _data[Idx(3, i)];
			for (int j = 0; j < 4; j++)
			{
				temp._data[Idx(j, i)]=(row1*m._data[Idx(j,0)])+(row2*m._data[Idx(j,1)])+
												(row3*m._data[Idx(j,2)])+(row4*m._data[Idx(j,3)]);
			}
		}
		return temp;
	}
	
	void Rotate(float rot, float x, float y, float z);
	
	void Translate(float x, float y, float z);
	
};
	
};

#endif