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


#ifndef CD_EXCEPTION_H
#define CD_EXCEPTION_H


#include <string>
#include <iostream>

namespace CD
{

class Exception
{
public:
	Exception();
	Exception(string msg);
	Exception(string msg, string file, int line);
	
	std::string GetMsg();
	std::string GetFile();
	int GetLine();
	
	void OutputAll(ostream& out);
	
private:
	string _msg;
	string _file;
	int _line;
};

#ifdef __WIN32
#define glrThrowError(msg) throw CD::Exception( msg, __FILE__ ,__LINE__)
#else
#define glrThrowError(msg) throw CD::Exception( std::stringstream() << __PRETTY_FUNCTION__ << ": " << msg)
#endif


};

#endif
