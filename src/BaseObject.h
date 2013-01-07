//
// BaseObject
//

#ifndef __BASEOBJECT_H
#define __BASEOBJECT_H

#include "common.h"

extern NPClass BaseClass;

typedef struct BaseObject {
  // Due to C memory layout we can access NPObject properties as if they were
  // directly defined inside this struct, just by doing a cast first.
  // i.e. BaseObject.structVersion
  NPObject _obj;

  NPP instance;
} BaseObject;

#endif
