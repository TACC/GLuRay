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
