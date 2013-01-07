//
// PenAPIObject
//

#ifndef __PENAPIOBJECT_H
#define __PENAPIOBJECT_H

#include "common.h"

extern NPClass PenAPIClass;

typedef struct PenAPIObject {
  // Due to C memory layout we can access NPObject properties as if they were
  // directly defined inside this struct, just by doing a cast first.
  // i.e. PenAPIObject.structVersion
  NPObject _obj;

  NPP instance;
} PenAPIObject;

#endif
