#ifndef ACCELWORK_H
#define ACCELWORK_H

#include <Core/Work.h>

class AccelWork : public Work
{
public:
 AccelWork(Manta::Object* o, std::string nname = "untitled") : _object(o) { name = nname; }
  virtual void run();

  private:
  Manta::Object* _object;
};

#endif
