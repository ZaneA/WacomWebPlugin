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
// Common things.
//

#ifndef __COMMON_H
#define __COMMON_H

//
// Headers.
//

// NPAPI
#include <npapi.h>
#include <npfunctions.h>

// Stdlib
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <assert.h>


//
// Defines.
//

#define PLUGIN_NAME    "WacomTabletPlugin"
#define PLUGIN_VERSION "2.0.0.1" // Highest version of API that is supported.
#define PLUGIN_VERSIONL 2001     // Decimal version of above.
#define PLUGIN_MIME    "application/x-wacomtabletplugin"
#define PLUGIN_MIME2   "application/x-wacom-tablet"
#define PLUGIN_MIME_DESCRIPTION \
    PLUGIN_MIME "::" PLUGIN_NAME ";" PLUGIN_MIME2 "::" PLUGIN_NAME

// Just a helper macro, makes for nicer looking code.
#define IS_IDENTIFIER(id) (name == g_netscapeFuncs->getstringidentifier(id))

#ifdef DEBUG
#define debug printf
#else
#define debug(body, ...)
#endif

// Hold pointer to browser functions.
// Defined in main.c.
extern NPNetscapeFuncs *g_netscapeFuncs;

// Global structure to hold Base and PenAPI objects.
// Defined in main.c.
typedef struct api_t {
  NPObject *base;
  NPObject *penAPI;
} api_t;

extern api_t g_api;

#endif
