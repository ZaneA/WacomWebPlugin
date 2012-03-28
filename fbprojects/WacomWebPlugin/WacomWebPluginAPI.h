#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "WacomWebPlugin.h"

#ifndef H_WacomWebPluginAPI
#define H_WacomWebPluginAPI

//
// Pen API
//
class PenAPI : public FB::JSAPIAuto
{
  public:
    PenAPI(const FB::BrowserHostPtr& host) : m_host(host) {
      registerProperty("isWacom",
          make_property(this,
            &PenAPI::get_isWacom));

      registerProperty("isEraser",
          make_property(this,
            &PenAPI::get_isEraser));

      registerProperty("pressure",
          make_property(this,
            &PenAPI::get_pressure));

      registerProperty("posX",
          make_property(this,
            &PenAPI::get_posX));

      registerProperty("posY",
          make_property(this,
            &PenAPI::get_posY));

      registerProperty("sysX",
          make_property(this,
            &PenAPI::get_sysX));

      registerProperty("sysY",
          make_property(this,
            &PenAPI::get_sysY));

      registerProperty("tabX",
          make_property(this,
            &PenAPI::get_tabX));

      registerProperty("tabY",
          make_property(this,
            &PenAPI::get_tabY));

      registerProperty("rotationDeg",
          make_property(this,
            &PenAPI::get_rotationDeg));

      registerProperty("rotationRad",
          make_property(this,
            &PenAPI::get_rotationRad));

      registerProperty("tiltX",
          make_property(this,
            &PenAPI::get_tiltX));

      registerProperty("tiltY",
          make_property(this,
            &PenAPI::get_tiltY));

      registerProperty("tangentialPressure",
          make_property(this,
            &PenAPI::get_tangentialPressure));

      registerProperty("version",
          make_property(this,
            &PenAPI::get_version));

      registerProperty("pointerType",
          make_property(this,
            &PenAPI::get_pointerType));

      registerProperty("tabletModel",
          make_property(this,
            &PenAPI::get_tabletModel));
    }

    virtual ~PenAPI() {};

    char get_isWacom();
    char get_isEraser();
    float get_pressure();
    long get_posX();
    long get_posY();
    float get_sysX();
    float get_sysY();
    long get_tabX();
    long get_tabY();
    float get_rotationDeg();
    float get_rotationRad();
    float get_tiltX();
    float get_tiltY();
    float get_tangentialPressure();
    long get_version();
    long get_pointerType();
    std::string get_tabletModel();

  private:
    FB::BrowserHostPtr m_host;
};

//
// Touch API
//
class TouchAPI : public FB::JSAPIAuto
{
  public:
    TouchAPI(const FB::BrowserHostPtr& host) : m_host(host) {
    }

    virtual ~TouchAPI() {};

  private:
    FB::BrowserHostPtr m_host;
};

FB_FORWARD_PTR(PenAPI);

//
// WacomWebPluginAPI
// Main entry point
//
class WacomWebPluginAPI : public FB::JSAPIAuto
{
  public:
    WacomWebPluginAPI(const WacomWebPluginPtr& plugin, const FB::BrowserHostPtr& host) : m_plugin(plugin), m_host(host) {
      registerProperty("penAPI",
          make_property(this,
            &WacomWebPluginAPI::get_penAPI));

      registerProperty("version",
          make_property(this,
            &WacomWebPluginAPI::get_version));

      // Pen API
      m_penAPI = boost::make_shared<PenAPI>(m_host);
    }

    virtual ~WacomWebPluginAPI() {};

    WacomWebPluginPtr getPlugin();

    // Read/Write property ${PROPERTY.ident}
    //std::string get_testString();
    //void set_testString(const std::string& val);

    // Read-only property ${PROPERTY.ident}
    boost::weak_ptr<PenAPI> get_penAPI();

    std::string get_version();

  private:
    WacomWebPluginWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    PenAPIPtr m_penAPI;
};

#endif // H_WacomWebPluginAPI

