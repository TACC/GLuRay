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
#ifndef COMMON_H
#define COMMON_H

inline string GetVarString(string var)
{
  string v = "";
  char* str = getenv(var.c_str());
  if (!str)
    cerr << "WARNING: \"" << var << "\" ENV not found\n";
  else
    v = string(str);
  return v;
}

template<typename T>
bool GetVar(string var, T& val)
{
  T v;
  stringstream str(GetVarString(var));
  if (str.str() == "")
  {
    cout << "unable to find " << var << endl;
    return false;
  }
  cout << "found string: \"" << str.str() << "\"" << endl;
  str >> v;
  cout << "foudn value: " << v << endl;
  val = v;
  return true;
}

#endif
