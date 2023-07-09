#include <X11/Xlib.h>
#include <stdio.h>

int main() {
  Display *display = XOpenDisplay(NULL);
  if (display == NULL) {
    fprintf(stderr, "Cannot open display\n");
    return 1;
  }

  int screen = DefaultScreen(display);
  Window root = RootWindow(display, screen);
  unsigned int width = 300, height = 200;
  unsigned int border_width = 1;
  unsigned int border_color = BlackPixel(display, screen);
  unsigned int background_color = WhitePixel(display, screen);

  Window window = XCreateSimpleWindow(display, root, 0, 0, width, height, border_width,
                                      border_color, background_color);
  XMapWindow(display, window);
  XFlush(display);

  XEvent event;
  while (1) {
    XNextEvent(display, &event);
    // 在此处处理窗口事件
  }

  XCloseDisplay(display);
  return 0;
}
