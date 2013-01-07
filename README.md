Wacom Web Plugin for Linux
===

This project aims to build a functional plugin for modern browsers on Linux that follows Wacom's official web plugin implementation at http://www.wacomeng.com/web/WebPluginReleaseNotes.htm and allows websites such as DeviantART's Muro to gain access to tablet properties through a Javascript API.

This project is in no way affiliated with Wacom. But until they provide an official plugin, this will have to do.

Getting Started
---

The previous version of this plugin (on the `master` branch) used FireBreath which made things fairly easy, but it is a bulky dependency for a plugin that only requires Linux support.

Therefore, getting started with this plugin should be a lot easier:

1. Make sure you have the NPAPI headers located at `/usr/include/npapi-sdk/` (or modify the Makefile).
2. From the root of the repo, run `make`.
3. Link or copy the resulting plugin to your local plugins directory, i.e. `ln -s /path/to/WacomWebPlugin/npWacomWebPlugin.so ~/.mozilla/plugins/`
4. Open your browser and navigate to `http://muro.deviantart.com` to see the plugin in action!

Screenshot
---

![Screenshot](https://github.com/ZaneA/WacomWebPlugin/raw/master/screenshot.png "Screenshot")
