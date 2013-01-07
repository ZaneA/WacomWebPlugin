//
// BaseObject
//

//
// Headers.
//

#include "BaseObject.h"
#include "PenAPIObject.h"


//
// Base functions.
//

// Allocate copy of object.
NPObject* BaseAllocate(NPP instance, NPClass *aClass)
{
  BaseObject *obj = (BaseObject*)g_netscapeFuncs->memalloc(sizeof(BaseObject));

  if (!obj)
    return NULL;

  memset(obj, 0, sizeof(BaseObject));

  obj->instance = instance;

  return (NPObject*)obj;
}

// Deallocate object.
void BaseDeallocate(NPObject *obj)
{
  g_netscapeFuncs->memfree(obj);
}

// Check if our Base API handles a property.
// In this case we handle "penAPI" and "version".
// Version shouldn't even be required here according to the Wacom docs,
// but it seems that the demos do expect it.
bool BaseHasProperty(NPObject *obj, NPIdentifier name)
{
  if (IS_IDENTIFIER("penAPI") ||
      IS_IDENTIFIER("version"))
    return true;

  return false;
}

// Provide the appropriate value to JS.
bool BaseGetProperty(NPObject *obj, NPIdentifier name, NPVariant *result)
{
  if (IS_IDENTIFIER("penAPI")) {
    // The main part of the API is defined in the PenAPIObject.
    // Retain and return this object.
    NPObject *penObj = g_api.penAPI;
    g_netscapeFuncs->retainobject(penObj);
    OBJECT_TO_NPVARIANT(penObj, *result);
    return true;
  }

  if (IS_IDENTIFIER("version")) {
    // Return the PLUGIN_VERSION.
    STRINGN_TO_NPVARIANT(strdup(PLUGIN_VERSION), sizeof(PLUGIN_VERSION), *result);
    return true;
  }

  return false;
}

// No methods in here so we just return false.
bool BaseHasMethod(NPObject *obj, NPIdentifier name) {
  return false;
}


//
// Initialize BaseClass.
// Try to only define what is strictly required.
//

NPClass BaseClass = {
  .structVersion = NP_CLASS_STRUCT_VERSION,
  .allocate = BaseAllocate,
  .deallocate = BaseDeallocate,
  .hasProperty = BaseHasProperty,
  .getProperty = BaseGetProperty,
  .invalidate = 0,
  .hasMethod = BaseHasMethod, // Needed on Firefox
  .invoke = 0,
  .invokeDefault = 0,
  .setProperty = 0,
  .removeProperty = 0,
  .enumerate = 0,
  .construct = 0,
};
