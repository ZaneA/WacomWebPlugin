#include <X11/Xlib.h>
#include <X11/extensions/XInput.h>
#include <X11/Xutil.h>

#include <string>
#include <stdio.h>
#include <stdlib.h>

// This corresponds to the mouse on my system
#define DEVICE_NUM 10

typedef class XInputWrapper {
  public:
    static XDeviceInfo* findDeviceById(Display *display, int id);
    static int registerDeviceEvents(Display *display, XDeviceInfo *deviceInfo);
    static void printDeviceEvents(Display *display);
    static void run();

    static int running;

    static char isWacom;
    static char isEraser;
    static float pressure;
    static long posX;
    static long posY;
    static float sysX;
    static float sysY;
    static long tabX;
    static long tabY;
    static float rotationDeg;
    static float rotationRad;
    static float tiltX;
    static float tiltY;
    static float tangentialPressure;
    static long version;
    static long pointerType;
    static std::string tabletModel;


  private:
    static int motionType;
    static int buttonPressType;
    static int buttonReleaseType;
    static int proximityInType;
    static int proximityOutType;

} XInputWrapper;
