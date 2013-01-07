//
// PenAPIObject
//

//
// Headers.
//

#include "PenAPIObject.h"


//
// PenAPI functions.
//

// Allocate copy of object.
NPObject* PenAPIAllocate(NPP instance, NPClass *aClass)
{
  PenAPIObject *obj = (PenAPIObject*)g_netscapeFuncs->memalloc(sizeof(PenAPIObject));

  if (!obj)
    return NULL;

  memset(obj, 0, sizeof(PenAPIObject));

  obj->instance = instance;

  return (NPObject*)obj;
}

// Deallocate object.
void PenAPIDeallocate(NPObject *obj)
{
  g_netscapeFuncs->memfree(obj);
}

// Check if our PenAPI API handles a property.
// This is where the majority of the Wacom API is defined.
bool PenAPIHasProperty(NPObject *obj, NPIdentifier name)
{
  if (IS_IDENTIFIER("isEraser")           || 
      IS_IDENTIFIER("isWacom")            || 
      IS_IDENTIFIER("pointerType")        || 
      IS_IDENTIFIER("posX")               || 
      IS_IDENTIFIER("posY")               || 
      IS_IDENTIFIER("pressure")           || 
      IS_IDENTIFIER("rotationDeg")        || 
      IS_IDENTIFIER("rotationRad")        || 
      IS_IDENTIFIER("sysX")               || 
      IS_IDENTIFIER("sysY")               || 
      IS_IDENTIFIER("tabX")               || 
      IS_IDENTIFIER("tabY")               || 
      IS_IDENTIFIER("TabletModel")        || 
      IS_IDENTIFIER("TabletModelID")      || 
      IS_IDENTIFIER("tangentialPressure") || 
      IS_IDENTIFIER("tiltX")              || 
      IS_IDENTIFIER("tiltY")              || 
      IS_IDENTIFIER("version"))
    return true;

  return false;
}

// Provide the appropriate value to JS.
// Most of this will be passed through to an XInput object.
bool PenAPIGetProperty(NPObject *obj, NPIdentifier name, NPVariant *result)
{
  if (IS_IDENTIFIER("isWacom")) {
    // Is the device a Wacom tablet?
    INT32_TO_NPVARIANT(1, *result);
    return true;
  }
  
  if (IS_IDENTIFIER("version")) {
    // The PLUGIN_VERSION (eg. 2.0.0.*).
    STRINGN_TO_NPVARIANT(strdup(PLUGIN_VERSION), sizeof(PLUGIN_VERSION), *result);
    return true;
  }
 
  {
    // On all unhandled cases we just return the string "test".
    STRINGZ_TO_NPVARIANT(strdup("test"), *result);
    return true;
  }

  return false;
}

// No methods in this API for now so we just return false.
bool PenAPIHasMethod(NPObject *obj, NPIdentifier name) {
  return false;
}


//
// Initialize PenAPIClass.
// Try to only define what is strictly required.
//

NPClass PenAPIClass = {
  .structVersion = NP_CLASS_STRUCT_VERSION,
  .allocate = PenAPIAllocate,
  .deallocate = PenAPIDeallocate,
  .hasProperty = PenAPIHasProperty,
  .getProperty = PenAPIGetProperty,
  .invalidate = 0,
  .hasMethod = PenAPIHasMethod, // Needed on Firefox
  .invoke = 0,
  .invokeDefault = 0,
  .setProperty = 0,
  .removeProperty = 0,
  .enumerate = 0,
  .construct = 0,
};
