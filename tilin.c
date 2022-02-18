#include <X11/X.h>
#include <X11/Xlib.h>
#include <stdlib.h>

int main(void) {
  Display *display;
  Window win_foc;
  XWindowAttributes attr;
  XButtonEvent start;
  XEvent event;
  int revert;

  if (!(display = (XOpenDisplay(0x0))))
    return 1;

  XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("q")), Mod4Mask,
           DefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);

  XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("Return")),
           Mod4Mask, DefaultRootWindow(display), True, GrabModeAsync,
           GrabModeAsync);

  XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("BackSpace")),
           Mod4Mask, DefaultRootWindow(display), True, GrabModeAsync,
           GrabModeAsync);

  XGrabButton(display, 1, Mod4Mask, DefaultRootWindow(display), True,
              ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
              GrabModeAsync, GrabModeAsync, None, None);
  XGrabButton(display, 3, Mod4Mask, DefaultRootWindow(display), True,
              ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
              GrabModeAsync, GrabModeAsync, None, None);

  start.subwindow = None;

  for (;;) {
    XNextEvent(display, &event);
    XGetInputFocus(display, &win_foc, &revert);
    XSync(display, False);
    XSetInputFocus(display, PointerRoot, RevertToPointerRoot, CurrentTime);

    if (event.type == KeyPress && event.xbutton.subwindow != None) {

      if (event.xkey.keycode ==
          XKeysymToKeycode(display, XStringToKeysym("q"))) {
        XDestroyWindow(display, win_foc);
      }
    }

    if (event.type == KeyPress) {
      if (event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym("Return"))) {
        system("st &");
      }
      if (event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym("p"))) {
        system("rofi -show drun");
      } 
      if (event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym("BackSpace"))) {
        XCloseDisplay(display);
      }
    }
  }
}
