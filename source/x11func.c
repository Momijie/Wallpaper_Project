#include "x11func.h"
#include <X11/Xlib.h>
#include <stdio.h>


void GetProgramWindow(int* handle) { 
  Window window = (Window) &handle;
  printf("%p\n", window);

}









void SetWindowAsRoot(void)
{
  Display* display = XOpenDisplay(NULL);
  const Window window = RootWindow(display, DefaultScreen(display));
  printf("%lx\n",window);



}
