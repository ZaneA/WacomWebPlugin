#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for Wacom Web Plugin for Linux
#
#\**********************************************************/

set(PLUGIN_NAME "WacomWebPlugin")
set(PLUGIN_PREFIX "WWPFL")
set(COMPANY_NAME "ZaneAshby")

# ActiveX constants:
set(FBTYPELIB_NAME WacomWebPluginLib)
set(FBTYPELIB_DESC "WacomWebPlugin 1.0 Type Library")
set(IFBControl_DESC "WacomWebPlugin Control Interface")
set(FBControl_DESC "WacomWebPlugin Control Class")
set(IFBComJavascriptObject_DESC "WacomWebPlugin IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "WacomWebPlugin ComJavascriptObject Class")
set(IFBComEventSource_DESC "WacomWebPlugin IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID b60b9ad9-24ca-5fdf-9f5d-486d07d22fbf)
set(IFBControl_GUID 0839ef2b-4d53-5169-bb73-4928335f4129)
set(FBControl_GUID 73cd5ba5-5958-58cc-ba94-56ef9e845938)
set(IFBComJavascriptObject_GUID b60ef84b-968a-58b0-a2c1-e49fb94b52e3)
set(FBComJavascriptObject_GUID dacf5c8d-c8c6-50ed-93fc-6230fd5c0f1b)
set(IFBComEventSource_GUID 434b8eac-33c0-5455-8026-b2efd155e63b)

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "ZaneAshby.WacomWebPlugin")
set(MOZILLA_PLUGINID "zaneashby.com/WacomWebPlugin")

# strings
set(FBSTRING_CompanyName "Zane Ashby")
set(FBSTRING_FileDescription "Wacom Web Plugin for Linux")
set(FBSTRING_PLUGIN_VERSION "1.1.0.1")
set(FBSTRING_LegalCopyright "Copyright 2012 Zane Ashby")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}.dll")
set(FBSTRING_ProductName "Wacom Web Plugin for Linux")
set(FBSTRING_FileExtents "")
set(FBSTRING_PluginName "WacomTabletPlugin")
set(FBSTRING_MIMEType "application/x-wacomtabletplugin")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 0)
set(FBMAC_USE_COCOA 0)
set(FBMAC_USE_COREGRAPHICS 0)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
