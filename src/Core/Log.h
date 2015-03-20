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

#ifndef CD_LOG_H
#define CD_LOG_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "CD_Exception.h"

namespace CD
{

enum Logs { CD_LOG_APP = 1, CD_LOG_CLIENT = 2, CD_LOG_SERVER = 4, CD_LOG_USER = 8, CD_LOG_KERNEL = 16 };
class Log  //based off of gamedev.net engenuity article
{
public:
	static Log& GetSingleton();
	void Init();  //loads log strings
	void Write(int target, const char* msg, ...);
	void Write(int target, unsigned long msgID, ...);
protected:
	Log();
	std::ofstream _app;
	std::ofstream _client;
	std::ofstream _server;
	std::ofstream _kernel;
	
	vector<string> _strings;
	bool LoadStrings();
	//static Log* __logSingleton;
};

};

#endif