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


#include "CD_Exception.h"

namespace CD
{

Exception::Exception()
{
	_msg = _file = "N/A";
	_line = -1;
}

Exception::Exception(string msg)
{
	_file = "N/A";
	_msg = msg;
	_line = -1;
}

Exception::Exception(string msg, string file, int line)
{
	_msg = msg;
	_file = file;
	_line = line;
}

string Exception::GetMsg()
{
	return _msg;
}

string Exception::GetFile()
{
	return _file;
}

int Exception::GetLine()
{
	return _line;
}

void Exception::OutputAll(ostream& out)
{
	out << "Error: " << _msg << " in file: " << _file << " line: " << _line << endl;
}

};