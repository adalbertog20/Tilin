#include <X11/X.h>
#include <stdio.h>
#include <stdbool.h>
#include <X11/Xlib.h>
#define MAX(a, b) ((a)> (b) ? (a) : (b))

int main(int argc, char *argv[])
{
    //Declaring some objects
    XEvent event;
    XWindowAttributes attributes;
    XButtonEvent start;
    Window focus;
    int revert;
    Display *display = NULL;

    if(!(display == XOpenDisplay(NULL)))
    {
        return 1;
    }

    //Mappings
    //Kill Window
    XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("q")), Mod1Mask, DefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
    //Open Terminal
    XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("Return")), Mod1Mask, DefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
    //Capture mouse buttons
    XGrabButton(display, 1, Mod1Mask, DefaultRootWindow(display), True,
        ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None);
    XGrabButton(display, 3, Mod1Mask, DefaultRootWindow(display), True,
        ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None);
    start.subwindow = None;
    while(true)
    {
        //Initialize stuff
        XNextEvent(display, &event);
        XGetInputFocus(display, &focus, &revert);
        XSync(display, false);
        XSetInputFocus(display, PointerRoot, RevertToPointerRoot, CurrentTime);

        //Close the window
        if(event.type == XKeysymToKeycode(display , XStringToKeysym("q")))
        {
            XDestroyWindow(display, focus);
        }
        if(event.type == KeyPress)
        {
            if(event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym("Return")))
            {
                system("st &");
            }
        }

    }
    return 0;
}
