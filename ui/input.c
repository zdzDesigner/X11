#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  Display *display = XOpenDisplay(NULL);
  if (display == NULL) {
    fprintf(stderr, "Cannot open display\n");
    return 1;
  }

  int screen = DefaultScreen(display);
  Window root = RootWindow(display, screen);

  Window window = XCreateSimpleWindow(display, root, 0, 0, 300, 200, 1, BlackPixel(display, screen),
                                      WhitePixel(display, screen));
  XSelectInput(display, window, KeyPressMask | ExposureMask);
  XMapWindow(display, window);
  XFlush(display);

  XIM xim = XOpenIM(display, NULL, NULL, NULL);
  XIC xic = XCreateIC(xim, XNInputStyle, XIMPreeditNothing | XIMStatusNothing, XNClientWindow,
                      window, NULL);

  XEvent event;
  char input_text[256] = {0};
  int input_text_length = 0;

  while (1) {
    XNextEvent(display, &event);

    if (event.type == Expose) {
      XDrawString(display, window, DefaultGC(display, screen), 10, 50, input_text,
                  input_text_length);
    } else if (event.type == KeyPress) {
      printf("--------\n");
      KeySym key;
      XLookupString(&event.xkey, NULL, 0, &key, NULL);
      if (key == XK_Return) {
        printf("Input: %s\n", input_text);
        XClearWindow(display, window);
        input_text_length = 0;
      } else {
        Status status;
        Xutf8LookupString(xic, &event.xkey, input_text + input_text_length,
                          sizeof(input_text) - input_text_length, NULL, &status);
        input_text_length = strlen(input_text);
      }
    }
  }

  XDestroyIC(xic);
  XCloseIM(xim);
  XCloseDisplay(display);
  return 0;
}
