#ifndef TILIN_H_
#define TILIN_H_

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


Display *display; // The Display
Window win_foc;   // The Focused Window
XWindowAttributes attr;
XButtonEvent start;
XEvent event;
int revert;

int max(int a, int b){
  return ((a) > (b) ? (a) : (b));
}

void grabkey(Display *display, const char k[]) {
  XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym(k)), Mod4Mask,
           XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
}

void grabbutton(Display *display, int nbutton) {
  XGrabButton(display, nbutton, Mod4Mask, XDefaultRootWindow(display), True,
              ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
              GrabModeAsync, GrabModeAsync, None, None);
}

void spawn(Display *display, const char **com) {
  if (fork())
    return;

  if (display) {
    close(ConnectionNumber(display));
  }
  setsid();
  execvp((char *)com[0], (char **)com);
}

static const char *term[] = {"st", NULL};            // TERMINAL
static const char *emacs[] = {"emacs", "-mm", NULL}; // TEXTEDITOR
static const char *launcher[] = {"rofi", "-show", "drun",
                                 NULL}; // APPLAUNCHEAPPR
static const char *surf[] = {"surf", "google.com", NULL};

#endif // TILIN_H_
