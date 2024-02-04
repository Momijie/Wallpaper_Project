#include <GL/gl.h>
#include <X11/X.h>
#include <stdbool.h>
#include <sys/types.h>
#define GLFW_EXPOSE_NATIVE_X11
#include "x11func.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <unistd.h>
#include <X11/Xatom.h>

static const int PROPERTY_FORMAT = 32;
static Atom NET_WM_STATE;
static Atom NET_WM_STATE_STICKY;
static Atom NET_WM_STATE_FULLSCREEN;
static Atom MOTIF_WM_HINTS;

void X11_Init_Atoms(Display* display)
{
 NET_WM_STATE = XInternAtom(display, "_NET_WM_STATE", false);
 NET_WM_STATE_FULLSCREEN = XInternAtom(display,"_NET_WM_STATE_FULLSCREEN",false);
 NET_WM_STATE_STICKY = XInternAtom(display, "_NET_WM_STATE_STICKY", false);
 MOTIF_WM_HINTS = XInternAtom(display, "_MOTIF_WM_HINTS", true);
}

void X11_Sticky(Display* display, Window window)
{
   XChangeProperty(display, window, NET_WM_STATE, XA_ATOM, PROPERTY_FORMAT, PropModeReplace, (unsigned char*)&NET_WM_STATE_STICKY, 1);
}

void X11_Below(Display* display, Window window)
{
   Atom netWmStateBelow = XInternAtom(display, "_NET_WM_STATE_BELOW", False);
   XChangeProperty(display, window, NET_WM_STATE, XA_ATOM, PROPERTY_FORMAT, PropModeAppend, (unsigned char *)&netWmStateBelow, 1);

   XFlush(display);
}
void X11_HIDE_BORDER(Display* display, Window window)
{
   
}

void GetProgramWindow(void)
{
  
   
  Display* display = XOpenDisplay(NULL);
  X11_Init_Atoms(display);

  GLFWwindow* context = glfwGetCurrentContext();
  Window window = glfwGetX11Window(context);
  Window root = DefaultRootWindow(display);
  
  XReparentWindow(display, window, root, 0, 0);
  X11_Sticky(display,window);
  X11_Below(display,window);

 
 XSync(display, False);

 XFlush(display);
}

