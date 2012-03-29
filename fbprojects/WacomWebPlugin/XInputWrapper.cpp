#include "XInputWrapper.h"

int XInputWrapper::running = 0;

int XInputWrapper::motionType = -1;
int XInputWrapper::buttonPressType = -1;
int XInputWrapper::buttonReleaseType = -1;
int XInputWrapper::proximityInType = -1;
int XInputWrapper::proximityOutType = -1;

// Tablet state (Bleeegghh)
char XInputWrapper::isWacom = 1;
char XInputWrapper::isEraser = 0;
float XInputWrapper::pressure = 0.0f;
long XInputWrapper::posX = 0;
long XInputWrapper::posY = 0;
float XInputWrapper::sysX = 0.0f;
float XInputWrapper::sysY = 0.0f;
long XInputWrapper::tabX = 0;
long XInputWrapper::tabY = 0;
float XInputWrapper::rotationDeg = 0.0f;
float XInputWrapper::rotationRad = 0.0f;
float XInputWrapper::tiltX = 0.0f;
float XInputWrapper::tiltY = 0.0f;
float XInputWrapper::tangentialPressure = 0.0f;
long XInputWrapper::version = 1101;
long XInputWrapper::pointerType = 0;
std::string XInputWrapper::tabletModel = "Intuos 5";

XDeviceInfo* XInputWrapper::findDeviceById(Display *display, int id)
{
  XDeviceInfo *devices;
  int num;

  devices = XListInputDevices(display, &num);

  for (int i = 0; i < num; i++) {
    if (id == devices[i].id) {
      printf("Got %s\n", devices[i].name);
      return &devices[i];
    }
  }

  return NULL;
}

int XInputWrapper::registerDeviceEvents(Display *display, XDeviceInfo *deviceInfo)
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
          DeviceButtonPress(device, XInputWrapper::buttonPressType, eventList[num]); num++;
          DeviceButtonRelease(device, XInputWrapper::buttonReleaseType, eventList[num]); num++;
          break;

        case ValuatorClass:
          DeviceMotionNotify(device, XInputWrapper::motionType, eventList[num]); num++;
          //ProximityIn(device, XInputWrapper::proximityInType, eventList[num]); num++;
          //ProximityOut(device, XInputWrapper::proximityOutType, eventList[num]); num++;
          break;

        default:
          fprintf(stderr, "Unknown class.\n");
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

void XInputWrapper::printDeviceEvents(Display *display)
{
  XEvent ev;

  while(1) {
    XNextEvent(display, &ev);

    if (ev.type == XInputWrapper::motionType) {
      printf("Motion event\n");

      XDeviceMotionEvent *motion = (XDeviceMotionEvent*)&ev;

      for (int i = 0; i < motion->axes_count; i++) {

        if (motion->first_axis + i == 0)
          XInputWrapper::tabX = XInputWrapper::sysX = XInputWrapper::posX = motion->axis_data[i];

        if (motion->first_axis + i == 1)
          XInputWrapper::tabY = XInputWrapper::sysY = XInputWrapper::posY = motion->axis_data[i];

        printf("%d axis = %d, ", motion->first_axis + i, motion->axis_data[i]);
      }

      printf("\n");
    } else if (ev.type == XInputWrapper::buttonPressType || ev.type == XInputWrapper::buttonReleaseType) {
      XDeviceButtonEvent *button = (XDeviceButtonEvent*)&ev;

      if (ev.type == XInputWrapper::buttonPressType) {
        XInputWrapper::pointerType = 1; // Pen
        XInputWrapper::pressure = (float)((double)rand() / (double)RAND_MAX);
      } else {
        XInputWrapper::pointerType = 0; // Out of proximity
        XInputWrapper::pressure = 0.0f;
      }

      printf("Button %s event on button %d\n", (ev.type == XInputWrapper::buttonPressType) ? "press" : "release", button->button);

      for (int i = 0;  i < button->axes_count; i++) {
        printf("%d axis = %d, ", button->first_axis + i, button->axis_data[i]);
      }

      printf("\n");
    } else if (ev.type == XInputWrapper::proximityInType || ev.type == XInputWrapper::proximityOutType) {
      XProximityNotifyEvent *prox = (XProximityNotifyEvent*)&ev;

      printf("%s proximity\n", (ev.type == XInputWrapper::proximityInType) ? "In" : "Out");

      for (int i = 0;  i < prox->axes_count; i++) {
        printf("%d axis = %d, ", prox->first_axis + i, prox->axis_data[i]);
      }

      printf("\n");
    }
  }
}

void XInputWrapper::run()
{
  Display *display = XOpenDisplay(NULL);

  if (display == NULL) {
    fprintf(stderr, "Couldn't open display.\n");
    return;
  }

  XDeviceInfo *info = XInputWrapper::findDeviceById(display, DEVICE_NUM);

  if (info == NULL) {
    fprintf(stderr, "Couldn't find device.\n");
    XCloseDisplay(display);
    return;
  }

  if (XInputWrapper::registerDeviceEvents(display, info)) {
    while (XInputWrapper::running) {
      XInputWrapper::printDeviceEvents(display);
    }
  }

  XCloseDisplay(display);
}
