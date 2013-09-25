#include <Interface/LightSet.h>
#include <Interface/Context.h>

#include "AccelWork.h"
#include <Modules/Manta/MantaManager.h>
#include <Core/Util/Logger.h>

void AccelWork::run() {
  //LOGSTARTC("AccelWork", 0,1,0);
  LightSet* lights = MantaManager::singleton()->getLights();
  PreprocessContext context(MantaManager::singleton()->getEngine(), 0, 1, lights);
  assert(_object);
  _object->preprocess(context);
  //LOGSTOP("AccelWork");
}
