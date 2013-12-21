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
// Entrypoint for plugin.
//

#include "common.h"
#include "BaseObject.h"
#include "PenAPIObject.h"
#include "XInput.h"

// Hold a pointer to browser functions.
NPNetscapeFuncs *g_netscapeFuncs = NULL;

// Hold global instances of BaseObject and PenAPIObject in here.
// This can work because the plugin has no instance state.
api_t g_api;


//
// Plugin functions.
//

// Plugin version.
const char* NP_GetPluginVersion(void)
{
  return PLUGIN_VERSION;
}

// Plugin MIME + description.
const char* NP_GetMIMEDescription(void)
{
  return PLUGIN_MIME_DESCRIPTION;
}

// Called when plugin is loaded.
NPError NP_Initialize(NPNetscapeFuncs *netscapeFuncs, NPPluginFuncs *pluginFuncs)
{
  pluginFuncs->version = PLUGIN_VERSIONL;
  pluginFuncs->size = sizeof(*pluginFuncs);

  // Link up function pointers for instances.
  pluginFuncs->newp = NPP_New;
  pluginFuncs->destroy = NPP_Destroy;
  pluginFuncs->getvalue = NPP_GetValue;

  // FIXME This should probably be copied in case it goes away.
  g_netscapeFuncs = netscapeFuncs;

  return NPERR_NO_ERROR;
}

// Called when plugin is unloaded.
void NP_Shutdown(void)
{
}

// Called to fetch a value from the plugin.
NPError NP_GetValue(NPP instance, NPNVariable variable, void *value)
{
  NPError err = NPERR_NO_ERROR;

  switch (variable) {
    // If browser is asking for name or description,
    // then return PLUGIN_NAME.
    case NPPVpluginNameString:
    case NPPVpluginDescriptionString:
      *((char**)value) = PLUGIN_NAME;
      break;

    // Tell the browser that we don't want a window.
    // Chrome seems to ignore this and give us one anyway.
    case NPPVpluginWindowBool:
      *((bool*)value) = false;
      break;

    default:
      return NPERR_INVALID_PARAM;
  }

  return err;
}


//
// Plugin *instance* functions.
//

// Called when a plugin *instance* is created.
NPError NPP_New(NPMIMEType pluginType, NPP instance, uint16_t mode, int16_t argc, char *argn[], char *argv[], NPSavedData *saved)
{
  // Create Base object if needed.
  if (g_api.base == NULL) {
    g_api.base = g_netscapeFuncs->createobject(instance, &BaseClass);
  }

  // Create PenAPI object if needed.
  if (g_api.penAPI == NULL) {
    g_api.penAPI = g_netscapeFuncs->createobject(instance, &PenAPIClass);
  }

  // Retain both.
  g_netscapeFuncs->retainobject(g_api.base);
  g_netscapeFuncs->retainobject(g_api.penAPI);

  // Start XInput thread.
  xinput_start();

  return NPERR_NO_ERROR;
}

// Called when a plugin *instance* is destroyed.
NPError NPP_Destroy(NPP instance, NPSavedData **save)
{
  // Stop XInput thread.
  xinput_stop();

  // Release objects.
  g_netscapeFuncs->releaseobject(g_api.penAPI);
  g_netscapeFuncs->releaseobject(g_api.base);

  return NPERR_NO_ERROR;
}

NPError NPP_GetValue(NPP instance, NPPVariable variable, void *value)
{
  NPError err = NPERR_NO_ERROR;

  switch (variable) {
    // Return our scriptable "Base" object here.
    // This is the root of our plugins scriptable interface.
    case NPPVpluginScriptableNPObject:
      {
        void **v = value;
        NPObject *obj = g_api.base;
        g_netscapeFuncs->retainobject(obj);
        *v = obj;
      }
      break;

    // Work around Chrome bug.
    case NPPVpluginNeedsXEmbed:
      *((NPBool*)value) = true;
      break;

    default:
      return NPERR_INVALID_PARAM;
  }

  return err;
}
