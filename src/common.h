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

// Threading
#include <pthread.h>

// Stdlib
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//
// Defines.
//

#define PLUGIN_NAME    "Wacom Web Plugin"
#define PLUGIN_VERSION "2.0.0.1" // Highest version of API that is supported.
#define PLUGIN_MIME    "application/x-wacomtabletplugin"

// Just a helper macro, makes for nicer looking code.
#define IS_IDENTIFIER(id) (name == g_netscapeFuncs->getstringidentifier(id))

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
