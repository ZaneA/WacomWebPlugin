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


xinput_values_t g_xinput_values = {
  .isWacom = true,
  .tabletModel = "Intuos 5",
  .tabletModelID = "Intuos 5",
};

xinput_wrapper_t g_xinput_wrapper = {
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

static XDeviceInfo* xinput_findDeviceById(Display *display, int id)
{
  XDeviceInfo *tablet = NULL;
  XDeviceInfo *devices = NULL;
  int num;

  devices = XListInputDevices(display, &num);

  for (int i = 0; i < num; i++) {
    if (id == devices[i].id) {
      printf("Got %s\n", devices[i].name);
      tablet = &devices[i];

      XAnyClassPtr any = (XAnyClassPtr)tablet->inputclassinfo;

      for (int j = 0; j < tablet->num_classes; j++) {
        if (any->class == ValuatorClass) {
          XValuatorInfoPtr v = (XValuatorInfoPtr)any;
          g_xinput_wrapper.pressure_min = v->axes[2].min_value;
          g_xinput_wrapper.pressure_max = v->axes[2].max_value;
          printf("PRESSURE DEBUG: min=%d, max=%d\n", v->axes[2].min_value, v->axes[2].max_value);
          break;
        }

        any = (XAnyClassPtr)((char *)any + any->length);
      }
    }
  }

  return tablet;
}

static int xinput_registerDeviceEvents(Display *display, XDeviceInfo *deviceInfo)
{
  int num = 0;
  XEventClass eventList[7];

  Window rootWin = RootWindow(display, DefaultScreen(display));

  XDevice *device = XOpenDevice(display, deviceInfo->id);

  if (device == NULL) {
    fprintf(stderr, "Unable to open device.\n");
    return 0;
  }

  if (device->num_classes > 0) {
    XInputClassInfo *ip;
    int i;

    for (ip = device->classes, i = 0; i < deviceInfo->num_classes; ip++, i++) {
      switch (ip->input_class) {
        case ButtonClass:
          DeviceButtonPress(device, g_xinput_wrapper.buttonPressType, eventList[num]); num++;
          DeviceButtonRelease(device, g_xinput_wrapper.buttonReleaseType, eventList[num]); num++;
          break;

        case ValuatorClass:
          DeviceMotionNotify(device, g_xinput_wrapper.motionType, eventList[num]); num++;
          //ProximityIn(device, g_xinput_wrapper.proximityInType, eventList[num]); num++;
          //ProximityOut(device, g_xinput_wrapper.proximityOutType, eventList[num]); num++;
          break;

        default:
          fprintf(stderr, "Unknown class %d.\n", ip->input_class);
          break;
      }
    }

    if (XSelectExtensionEvent(display, rootWin, eventList, num)) {
      fprintf(stderr, "Error selecting extended events.\n");
      return 0;
    }
  }

  return num;
}

static void xinput_printDeviceEvents(Display *display)
{
  XEvent ev;

  if (XPending(display) <= 0) {
    usleep(1000);
    return;
  }

  XNextEvent(display, &ev);

  if (ev.type == g_xinput_wrapper.motionType) {
    printf("Motion event\n");

    XDeviceMotionEvent *motion = (XDeviceMotionEvent*)&ev;

    for (int i = 0; i < motion->axes_count; i++) {

      if (motion->first_axis + i == 0) // X
        g_xinput_values.tabX = g_xinput_values.sysX = g_xinput_values.posX = motion->axis_data[i];

      if (motion->first_axis + i == 1) // Y
        g_xinput_values.tabY = g_xinput_values.sysY = g_xinput_values.posY = motion->axis_data[i];

      if (motion->first_axis + i == 2) // Pressure
        g_xinput_values.pressure = motion->axis_data[i] / ((float)g_xinput_wrapper.pressure_max - (float)g_xinput_wrapper.pressure_min);

      printf("%d axis = %d, ", motion->first_axis + i, motion->axis_data[i]);
    }

    printf("\n");
  } else if (ev.type == g_xinput_wrapper.buttonPressType || ev.type == g_xinput_wrapper.buttonReleaseType) {
    XDeviceButtonEvent *button = (XDeviceButtonEvent*)&ev;

    if (ev.type == g_xinput_wrapper.buttonPressType) {
      g_xinput_values.pointerType = 1; // Pen
    } else {
      g_xinput_values.pointerType = 0; // Out of proximity
    }

    printf("Button %s event on button %d\n", (ev.type == g_xinput_wrapper.buttonPressType) ? "press" : "release", button->button);

    for (int i = 0; i < button->axes_count; i++) {
      printf("%d axis = %d, ", button->first_axis + i, button->axis_data[i]);
    }

    printf("\n");
  } else if (ev.type == g_xinput_wrapper.proximityInType || ev.type == g_xinput_wrapper.proximityOutType) {
    XProximityNotifyEvent *prox = (XProximityNotifyEvent*)&ev;

    printf("%s proximity\n", (ev.type == g_xinput_wrapper.proximityInType) ? "In" : "Out");

    for (int i = 0; i < prox->axes_count; i++) {
      printf("%d axis = %d, ", prox->first_axis + i, prox->axis_data[i]);
    }

    printf("\n");
  }
}

static void *xinput_run(void *args)
{
  Display *display = XOpenDisplay(NULL);

  if (display == NULL) {
    fprintf(stderr, "Couldn't open display.\n");
    return NULL;
  }

  XDeviceInfo *info = xinput_findDeviceById(display, 8);

  if (info == NULL) {
    fprintf(stderr, "Couldn't find device.\n");
    XCloseDisplay(display);
    return NULL;
  }

  if (xinput_registerDeviceEvents(display, info)) {
    while (g_xinput_wrapper.running) {
      xinput_printDeviceEvents(display);
    }
  }

  XCloseDisplay(display);
  return NULL;
}

// Start the XInput wrapper, in a thread.
void xinput_start()
{
  printf("xinput_start()\n");
  g_xinput_wrapper.running = true;

  // Create a thread running xinput_run().
  int ret = pthread_create(&g_xinput_wrapper.thread, NULL, xinput_run, NULL);
  assert(ret == 0);
}

void xinput_stop()
{
  printf("xinput_stop()\n");
  g_xinput_wrapper.running = false;

  int ret = pthread_join(g_xinput_wrapper.thread, NULL);
  assert(ret == 0);
}

xinput_values_t *xinput_getValues()
{
  return &g_xinput_values;
}
