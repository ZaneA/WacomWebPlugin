/**********************************************************\

  Auto-generated WacomWebPluginAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "WacomWebPluginAPI.h"

char PenAPI::get_isWacom()
{
  return 1;
}

char PenAPI::get_isEraser()
{
  return 0;
}

float PenAPI::get_pressure()
{
  return 0.0f;
}

long PenAPI::get_posX()
{
  return 0;
}

long PenAPI::get_posY()
{
  return 0;
}

float PenAPI::get_sysX()
{
  return 0.0f;
}

float PenAPI::get_sysY()
{
  return 0.0f;
}

long PenAPI::get_tabX()
{
  return 0;
}

long PenAPI::get_tabY()
{
  return 0;
}

float PenAPI::get_rotationDeg()
{
  return 0.0f;
}

float PenAPI::get_rotationRad()
{
  return 0.0f;
}

float PenAPI::get_tiltX()
{
  return 0.0f;
}

float PenAPI::get_tiltY()
{
  return 0.0f;
}

float PenAPI::get_tangentialPressure()
{
  return 0.0f;
}

long PenAPI::get_version()
{
  return 1101;
}

long PenAPI::get_pointerType()
{
  return 0;
}

std::string PenAPI::get_tabletModel()
{
  return "";
}

///////////////////////////////////////////////////////////////////////////////
/// @fn WacomWebPluginPtr WacomWebPluginAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
WacomWebPluginPtr WacomWebPluginAPI::getPlugin()
{
    WacomWebPluginPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

// Read/Write property testString
//std::string WacomWebPluginAPI::get_testString()
//{
//    return m_testString;
//}
//
//void WacomWebPluginAPI::set_testString(const std::string& val)
//{
//    m_testString = val;
//}

boost::weak_ptr<PenAPI> WacomWebPluginAPI::get_penAPI()
{
  return m_penAPI;
}

// Read-only property version
std::string WacomWebPluginAPI::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}
