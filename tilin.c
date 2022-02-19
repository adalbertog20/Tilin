#include "tilin.h"
#include <X11/Xlib.h>

int main(void) {

  if (!(display = (XOpenDisplay(0x0)))) {
    return 1;
  }

  // Declaring keybinds

  grabkey(display, "q");

  grabkey(display, "Return");

  grabkey(display, "p");

  grabkey(display, "e");

  grabkey(display, "BackSpace");

  grabbutton(display, 1);

  grabbutton(display, 3);

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
      } else if (event.xkey.keycode ==
                 XKeysymToKeycode(display, XStringToKeysym("s"))) {
        XRaiseWindow(display, event.xkey.subwindow);
      } else if (event.xkey.keycode ==
                 XKeysymToKeycode(display, XStringToKeysym("l"))) {
        XLowerWindow(display, event.xkey.subwindow);
      }

    } else if (event.type == ButtonPress && event.xbutton.subwindow != None) {
      XGrabPointer(display, event.xbutton.subwindow, True,
                   PointerMotionMask | ButtonReleaseMask, GrabModeAsync,
                   GrabModeAsync, None, None, CurrentTime);
      XGetWindowAttributes(display, event.xbutton.subwindow, &attr);
      start = event.xbutton;
    } else if (event.type == MotionNotify) {
      int xdiff, ydiff;
      while (XCheckTypedEvent(display, MotionNotify, &event))
        ;
      xdiff = event.xbutton.x_root - start.x_root;
      ydiff = event.xbutton.y_root - start.y_root;
      XMoveResizeWindow(display, event.xbutton.window,
                        attr.x + (start.button == 1 ? xdiff : 0),
                        attr.y + (start.button == 1 ? ydiff : 0),
                        max(1, attr.width + (start.button == 3 ? xdiff : 0)),
                        max(1, attr.height + (start.button == 3 ? ydiff : 0)));
    } else if (event.type == ButtonRelease)
      XUngrabPointer(display, CurrentTime);

    if (event.type == KeyPress) {
      if (event.xkey.keycode ==
          XKeysymToKeycode(display, XStringToKeysym("w"))) {
        spawn(display, surf);
      }
      if (event.xkey.keycode ==
          XKeysymToKeycode(display, XStringToKeysym("Return"))) {
        spawn(display, term);
      }
      if (event.xkey.keycode ==
          XKeysymToKeycode(display, XStringToKeysym("e"))) {
        spawn(display, emacs);
      }
      if (event.xkey.keycode ==
          XKeysymToKeycode(display, XStringToKeysym("p"))) {
        system("rofi -show drun");
      } else if (event.xkey.keycode ==
                 XKeysymToKeycode(display, XStringToKeysym("BackSpace"))) {
        XCloseDisplay(display);
      }
    }
  }
}
