/*
 *  CD_Log.cpp
 *  CD_Base
 *
 *  Created by Scerenon on 5/16/05.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include "CD_Log.h"
using namespace std;

namespace CD
{

Log::Log()
{
}

Log& Log::GetSingleton()
{
	//if (!__logSingleton)
	//	__logSingleton = new Log;
	//return __logSingleton;
	static Log single;
	return single;
}

void Log::Init()
{
	_app.open("applog.txt");
	_client.open("clntlog.txt");
	_server.open("srvrlog.txt");
	_kernel.open("kernellog.txt");
	
	if (!LoadStrings()) CDThrowError("String codes could not be loaded");
}

void Log::Write(int target, const char* msg, ...)
{
	va_list args; va_start(args, msg);
	char szBuf[1024];
	vsprintf(szBuf, msg, args);
	
	if (target&CD_LOG_APP)
	{
		_app << szBuf << "\n";
		#ifndef DEBUG
			_app.flush();
		#endif
	}
	if (target&CD_LOG_CLIENT)
	{
		_client << szBuf << "\n";
		#ifndef DEBUG
			_client.flush();
		#endif
	}
	if (target&CD_LOG_SERVER)
	{
		_server << szBuf << "\n";
		#ifndef DEBUG
			_server.flush();
		#endif
	}
	else if (target&CD_LOG_KERNEL)
	{
		_kernel << szBuf << "\n";
		#ifndef DEBUG
			_kernel.flush();
		#endif
	}
	if (target&CD_LOG_USER)
	{
		#ifdef WIN32
			MEssageBox(NULL, szBuf, "Message",MB_OK);
		#else
			cout << szBuf << "\n";
			#ifndef DEBUG
				cout.flush();
			#endif
		#endif
	}
}

void Log::Write(int target, unsigned long msgID, ...)
{
	va_list args; va_start(args, msgID);
	char szBuf[1024];
	vsprintf(szBuf, _strings.at(msgID).c_str(), args);
	Write(target, szBuf);
}

bool Log::LoadStrings()
{
	ifstream in("strings.txt");
	if (!in.is_open()) return false;
	
	int index = 0;
	
	while(!in.eof())
	{
		char szBuf[1024];
		in.getline(szBuf, 1024);
		_strings.push_back( szBuf);
	}
	return true;
}

};