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
// XInput Wrapper.
//

//
// Headers.
//

#include "common.h"
#include "XInput.h"


//
// Globals.
//

// Holds the values for the Wacom API.
xinput_values_t g_xinput_values = {
  .isWacom = true,
};

// Holds XInput wrapper state.
xinput_state_t g_xinput_state = {
  .refcount = 0,
  .pressure_min = 0,
  .pressure_max = 1,
  .motionType = -1,
  .buttonPressType = -1,
  .buttonReleaseType = -1,
  .proximityInType = -1,
  .proximityOutType = -1,
};


//
// Functions.
//

static bool xinput_findDevices(Display *display, XDeviceInfo *stylus_info, XDeviceInfo *eraser_info)
{
  int found = 0;

  int num;
  XDeviceInfo *devices = XListInputDevices(display, &num);

  Atom stylus = XInternAtom(display, "STYLUS", false);
  Atom eraser = XInternAtom(display, "ERASER", false);

  for (int i = 0; i < num; i++) {
    debug("Got device \"%s\"\n", devices[i].name);

    if (devices[i].type == stylus) {
      found++;

      // Fill tablet model here.
      snprintf(g_xinput_values.tabletModel, sizeof(g_xinput_values.tabletModel), "%s", devices[i].name);
      snprintf(g_xinput_values.tabletModelID, sizeof(g_xinput_values.tabletModelID), "%s", devices[i].name);

      debug("Found stylus.\n");

      memcpy(stylus_info, &devices[i], sizeof(XDeviceInfo));

      XAnyClassPtr any = (XAnyClassPtr)devices[i].inputclassinfo;

      for (int j = 0; j < devices[i].num_classes; j++) {
        if (any->class == ValuatorClass) {
          XValuatorInfoPtr v = (XValuatorInfoPtr)any;
          g_xinput_state.pressure_min = v->axes[2].min_value;
          g_xinput_state.pressure_max = v->axes[2].max_value;
          debug("PRESSURE DEBUG: min=%d, max=%d\n", v->axes[2].min_value, v->axes[2].max_value);
          break;
        }

        any = (XAnyClassPtr)((char *)any + any->length);
      }
    } else if (devices[i].type == eraser) {
      found++;

      debug("Found eraser.\n");

      memcpy(eraser_info, &devices[i], sizeof(XDeviceInfo));
    }
  }

  XFreeDeviceList(devices);

  return (found == 2);
}

static XDevice *xinput_registerDeviceEvents(Display *display, XDeviceInfo *deviceInfo)
{
  int num = 0;
  XEventClass eventList[5];

  Window rootWin = RootWindow(display, DefaultScreen(display));

  XDevice *device = XOpenDevice(display, deviceInfo->id);

  assert(device != NULL);

  if (device->num_classes > 0) {
    XInputClassInfo *ip;
    int i;

    for (ip = device->classes, i = 0; i < deviceInfo->num_classes; ip++, i++) {
      switch (ip->input_class) {
        case KeyClass:
          break;

        case ButtonClass:
          DeviceButtonPress(device, g_xinput_state.buttonPressType, eventList[num]); num++;
          DeviceButtonRelease(device, g_xinput_state.buttonReleaseType, eventList[num]); num++;
          break;

        case ValuatorClass:
          DeviceMotionNotify(device, g_xinput_state.motionType, eventList[num]); num++;
          ProximityIn(device, g_xinput_state.proximityInType, eventList[num]); num++;
          ProximityOut(device, g_xinput_state.proximityOutType, eventList[num]); num++;
          break;

        default:
          fprintf(stderr, "Unknown class %d.\n", ip->input_class);
          break;
      }
    }

    if (XSelectExtensionEvent(display, rootWin, eventList, num)) {
      fprintf(stderr, "Error selecting extended events.\n");
      return NULL;
    }
  }

  return device;
}

static void xinput_printDeviceEvents(Display *display, XDevice *stylus, XDevice *eraser)
{
  XEvent ev;

  // This allows the thread to finish instead of blocking on XNextEvent.
  if (XPending(display) <= 0) {
    usleep(1000);
    return;
  }

  XNextEvent(display, &ev);

  if (ev.type == g_xinput_state.motionType) {
    XDeviceMotionEvent *motion = (XDeviceMotionEvent*)&ev;

    for (int i = 0; i < motion->axes_count; i++) {

      if (motion->first_axis + i == 0) // X
        g_xinput_values.tabX = g_xinput_values.sysX = g_xinput_values.posX = motion->axis_data[i];

      if (motion->first_axis + i == 1) // Y
        g_xinput_values.tabY = g_xinput_values.sysY = g_xinput_values.posY = motion->axis_data[i];

      if (motion->first_axis + i == 2) // Pressure
        g_xinput_values.pressure = motion->axis_data[i] / ((float)g_xinput_state.pressure_max - (float)g_xinput_state.pressure_min);
    }
  } else if (ev.type == g_xinput_state.buttonPressType || ev.type == g_xinput_state.buttonReleaseType) {
    XDeviceButtonEvent *button = (XDeviceButtonEvent*)&ev;

    debug("Button %s event on button %d\n", (ev.type == g_xinput_state.buttonPressType) ? "press" : "release", button->button);

    for (int i = 0; i < button->axes_count; i++) {
      debug("%d axis = %d, ", button->first_axis + i, button->axis_data[i]);
    }

    debug("\n");
  } else if (ev.type == g_xinput_state.proximityInType || ev.type == g_xinput_state.proximityOutType) {
    XProximityNotifyEvent *prox = (XProximityNotifyEvent*)&ev;

    if (prox->type == g_xinput_state.proximityInType) {
      if (prox->deviceid == stylus->device_id) {
        g_xinput_values.isEraser = false;
        g_xinput_values.pointerType = 1; // Pen
      } else {
        g_xinput_values.isEraser = true;
        g_xinput_values.pointerType = 3; // Eraser
      } 
    } else if (prox->type == g_xinput_state.proximityOutType) {
      g_xinput_values.pointerType = 0; // Out of proximity
    }
  }
}

static void *xinput_run(void *args)
{
  Display *display = XOpenDisplay(NULL);

  assert(display != NULL);

  XDeviceInfo stylus_info, eraser_info;

  if (!xinput_findDevices(display, &stylus_info, &eraser_info)) {
    fprintf(stderr, "Couldn't find device.\n");
    goto cleanup;
  }

  XDevice *stylus = xinput_registerDeviceEvents(display, &stylus_info);
  XDevice *eraser = xinput_registerDeviceEvents(display, &eraser_info);

  assert(stylus != NULL);
  assert(eraser != NULL);

  while (g_xinput_state.refcount > 0) {
    xinput_printDeviceEvents(display, stylus, eraser);
  }

  XCloseDevice(display, eraser);
  XCloseDevice(display, stylus);

cleanup:
  XCloseDisplay(display);

  return NULL;
}

// Start the XInput wrapper, in a thread.
void xinput_start()
{
  debug("xinput_start()\n");

  // Create a thread running xinput_run().
  g_xinput_state.refcount++;

  if (g_xinput_state.refcount == 1) {
    debug("xinput_start(): Creating xinput thread.\n");
    int ret = pthread_create(&g_xinput_state.thread, NULL, xinput_run, NULL);
    assert(ret == 0);
  }
}

void xinput_stop()
{
  debug("xinput_stop()\n");

  // Stop the XInput event thread.
  g_xinput_state.refcount--;
  if (g_xinput_state.refcount == 0) {
    debug("xinput_stop(): Joining xinput thread.\n");
    int ret = pthread_join(g_xinput_state.thread, NULL);
    assert(ret == 0);
  }
}

// Return the values table, used in PenAPIObject.c.
xinput_values_t *xinput_getValues()
{
  return &g_xinput_values;
}
