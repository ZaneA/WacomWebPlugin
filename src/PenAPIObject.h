//
// WacomWebPlugin - An implementation of the Wacom Web API on Linux.
// Copyright (C) 2013  Zane Ashby <zane.a@demonastery.org>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

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
