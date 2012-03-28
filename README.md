Wacom Web Plugin for Linux
===

This project aims to build a functional plugin for modern browsers that follows Wacom's official web plugin implementation at http://www.wacomeng.com/web/WebPluginReleaseNotes.htm and allows websites such as DeviantART's Muro to gain access to tablet properties through a Javascript API.

Getting Started
---

1. Grab a copy of FireBreath from `http://www.firebreath.org` and untar it into a directory somewhere.
2. `git clone` this repo somewhere.
3. From inside this repo, run `/path/to/firebreath/prepmake.sh fbprojects fbbuild`
4. Inside `fbbuild/` run `make` to build WacomWebPlugin.
5. Link or copy the plugin into your local plugins directory, ie. `ln -s /path/to/fbbuild/bin/WacomWebPlugin/npWacomWebPlugin.so ~/.mozilla/plugins/`
6. Open your browser and navigate to `http://muro.deviantart.com` to see the plugin in action!
