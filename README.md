Wacom Web Plugin for Linux
===

This project aims to build a functional plugin for modern browsers on Linux that follows Wacom's official web plugin implementation at http://www.wacomeng.com/web/WebPluginReleaseNotes.htm and allows websites such as DeviantART's Muro to gain access to tablet properties through a Javascript API (for now only the PenAPI is supported).

This project is in no way affiliated with Wacom. But until they provide an official plugin, this will have to do.

Getting Started
---

The previous version of this plugin used FireBreath which made things fairly easy, but it is a bulky dependency for a plugin that only requires Linux support.

Therefore, getting started with this plugin should be a lot easier. First of all you will need to make sure that you have appropriate NPAPI headers:

- On Ubuntu you can get these by installing the `firefox-dev` package (`sudo apt-get install firefox-dev`).
- On ArchLinux you can get these by installing the `npapi-sdk` package (`sudo pacman -Sy npapi-sdk`).

You will also need X11 and XInput headers:

- On ArchLinux you can get these by installing `libx11` and `xorg-xinput`.

1. Clone the repo and run `make` from the root.
2. Link or copy the resulting plugin to your local plugins directory, i.e. `ln -s /path/to/WacomWebPlugin/npWacomWebPlugin.so ~/.mozilla/plugins/`
3. Open your browser and navigate to [deviantART's Muro](http://sta.sh/muro) to see the plugin in action!

Screenshot
---

![Screenshot](https://github.com/ZaneA/WacomWebPlugin/raw/master/screenshot.png "Screenshot")
