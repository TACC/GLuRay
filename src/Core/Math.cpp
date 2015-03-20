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


#include "CD_Math.h"

namespace CD
{

//
// Vector3D
//

float Vector3D::Magnitude()
{
	return (float)sqrt(x*x + y*y + z*z);
}

Vector3D Vector3D::Normalize()
{
	(*this) /= Magnitude();
	return *this;
}

float Vector3D::Dot(Vector3D &v)
{
	return (x * v.x + y * v.y + z * v.z);
}

Vector3D Vector3D::Cross(const Vector3D &v)
{
    Vector3D n;  

    n.x = ((v.y * z) - (v.z * y));
                                                        
    n.y = ((v.z * x) - (v.x * z));
                                                        
    n.z = ((v.x * y) - (v.y * x));

    return n;
}
	

Matrix::Matrix()
{
	Identity();
}


Matrix::Matrix(const Matrix &m)
{
	for (int i = 0; i < 16; i++)
		_data[i] = m._data[i];
}

Matrix::Matrix(float* m)
{
	for (int i = 0; i < 16; i++)
		_data[i] = m[i];
}

void Matrix::Zero()
{
	for (int i = 0; i < 16; i++)
		_data[i] = 0.0f;
}



void Matrix::Identity()
{
	Zero();
	_data[0] = _data[5] = _data[10] = _data[15] = 1.0f;
}



void Matrix::Rotate(float rot, float x, float y, float z)
{
	x*= rot;
	y*=rot;
	z*=rot;
			Identity();

			float sinx=(float)sin((double)x);
			float cosx=(float)cos((double)x);
			float siny=(float)sin((double)y);
			float cosy=(float)cos((double)y);
			float sinz=(float)sin((double)z);
			float cosz=(float)cos((double)z);

			_data[0]=cosy*cosz;
			_data[1]=sinx*siny*cosz-cosx*sinz;
			_data[2]=cosx*siny*cosz+sinx*sinz;

			_data[4]=cosy*sinz;
			_data[5]=sinx*siny*sinz+cosx*cosz;
			_data[6]=cosx*siny*sinz-sinx*cosz;

			_data[8]=-siny;
			_data[9]=sinx*cosy;
			_data[10]=cosx*cosy;
}


void Matrix::Translate(float x, float y, float z)
{
	Identity();
	_data[12] = x;
	_data[13] = y;
	_data[14] = z;
}

};