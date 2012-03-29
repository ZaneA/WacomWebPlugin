/**********************************************************\

  Auto-generated WacomWebPluginAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "XInputWrapper.h"
#include "WacomWebPluginAPI.h"

char PenAPI::get_isWacom()
{
  return XInputWrapper::isWacom;
}

char PenAPI::get_isEraser()
{
  return XInputWrapper::isEraser;
}

float PenAPI::get_pressure()
{
  return XInputWrapper::pressure;
}

long PenAPI::get_posX()
{
  return XInputWrapper::posX;
}

long PenAPI::get_posY()
{
  return XInputWrapper::posY;
}

float PenAPI::get_sysX()
{
  return XInputWrapper::sysX;
}

float PenAPI::get_sysY()
{
  return XInputWrapper::sysY;
}

long PenAPI::get_tabX()
{
  return XInputWrapper::tabX;
}

long PenAPI::get_tabY()
{
  return XInputWrapper::tabY;
}

float PenAPI::get_rotationDeg()
{
  return XInputWrapper::rotationDeg;
}

float PenAPI::get_rotationRad()
{
  return XInputWrapper::rotationRad;
}

float PenAPI::get_tiltX()
{
  return XInputWrapper::tiltX;
}

float PenAPI::get_tiltY()
{
  return XInputWrapper::tiltY;
}

float PenAPI::get_tangentialPressure()
{
  return XInputWrapper::tangentialPressure;
}

long PenAPI::get_version()
{
  return XInputWrapper::version;
}

long PenAPI::get_pointerType()
{
  return XInputWrapper::pointerType;
}

std::string PenAPI::get_tabletModel()
{
  return XInputWrapper::tabletModel;
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
