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

  // X 客户端连接到 X 服务器
  // 客户端可以发送请求来要求 X 服务器执行某些操作。一个简单的请求示例是 CreateWindow，它告诉 X 服务器“创建一个窗口”。
  Window window = XCreateSimpleWindow(display, root, 0, 0, 300, 200, 1, BlackPixel(display, screen),
                                      BlackPixel(display, screen));
  XSelectInput(display, window, ExposureMask); // 侦听特定事件
  // 在 X11 协议中显示窗口称为映射窗口，隐藏窗口称为取消映射(最小化窗口)
  XMapWindow(display, window);
  XFlush(display);

  XEvent event;
  while (1) {
    XNextEvent(display, &event);
    if (event.type == Expose) {
      printf("Expose\n");
      GC gc = XCreateGC(display, window, 0, NULL);
      XDrawString(display, window, gc, 10, 50, "Hello, X11!", -1);
      XFreeGC(display, gc);
    }
  }

  XCloseDisplay(display);
  return 0;
}
