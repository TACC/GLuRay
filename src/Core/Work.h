#ifndef WORK_H
#define WORK_H

#include <Interface/Object.h>
#include <string>

class Work
{
 public:
  virtual void run() = 0;
  std::string name;
};
#endif
