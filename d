[1mdiff --git a/octet/src/platform/windows_specific.h b/octet/src/platform/windows_specific.h[m
[1mindex 32530ca..d6e5d86 100644[m
[1m--- a/octet/src/platform/windows_specific.h[m
[1m+++ b/octet/src/platform/windows_specific.h[m
[36m@@ -11,6 +11,11 @@[m
 #define WIN32_LEAN_AND_MEAN 1[m
 #include <windows.h>[m
 #include <mmsystem.h>[m
[32m+[m[32m// added libraries[m[41m[m
[32m+[m[32m#include <cmath>[m[41m[m
[32m+[m[32m#include <time.h>[m[41m[m
[32m+[m[32m#include <fstream>[m[41m[m
[32m+[m[32m#include <conio.h>[m[41m[m
 [m
 #include <ShellAPI.h> // for DragAcceptFiles etc.[m
 [m
[36m@@ -137,6 +142,20 @@[m [mnamespace octet {[m
     app(int argc, char **argv) {[m
     }[m
 [m
[32m+[m	[32m// just to present a window with the same ratio[m[41m[m
[32m+[m	[32mvoid GetDesktopResolution(int &horizontal, int &vertical)[m[41m[m
[32m+[m	[32m{[m[41m[m
[32m+[m		[32mRECT desktop;[m[41m[m
[32m+[m		[32m// Get a handle to the desktop window[m[41m[m
[32m+[m		[32mconst HWND hDesktop = GetDesktopWindow();[m[41m[m
[32m+[m		[32m// Get the size of screen to the variable desktop[m[41m[m
[32m+[m		[32mGetWindowRect(hDesktop, &desktop);[m[41m[m
[32m+[m[41m[m
[32m+[m		[32mhorizontal = desktop.right;[m[41m[m
[32m+[m		[32mvertical = desktop.bottom;[m[41m[m
[32m+[m	[32m}[m[41m[m
[32m+[m[41m[m
[32m+[m[41m[m
     void init() {[m
       WSADATA wsa;[m
       WSAStartup(MAKEWORD(2,2), &wsa);[m
[36m@@ -154,10 +173,19 @@[m [mnamespace octet {[m
 [m
       gl_context = 0;[m
      [m
[31m-      window_handle = CreateWindowW(L"MyClass", L"octet",[m
[31m-        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 768, 768,[m
[31m-        NULL, NULL, wndclass.hInstance, (LPVOID)this[m
[31m-      );[m
[32m+[m	[32m  //to center the window with a ratio[m[41m[m
[32m+[m	[32m  int horizontal_screen = 0;[m[41m[m
[32m+[m	[32m  int vertical_screen = 0;[m[41m[m
[32m+[m	[32m  const double ratio_screen = 0.80;[m[41m[m
[32m+[m[41m[m
[32m+[m	[32m  GetDesktopResolution(horizontal_screen, vertical_screen);[m[41m[m
[32m+[m[41m[m
[32m+[m	[32m  window_handle = CreateWindowW(L"MyClass", L"octet",[m[41m[m
[32m+[m		[32m  WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,[m[41m[m
[32m+[m		[32m  ((int)horizontal_screen*ratio_screen),[m[41m[m
[32m+[m		[32m  ((int)vertical_screen*ratio_screen),[m[41m[m
[32m+[m		[32m  NULL, NULL, wndclass.hInstance, (LPVOID)this[m[41m[m
[32m+[m		[32m  );[m[41m[m
 [m
       map()[window_handle] = this;[m
 [m
