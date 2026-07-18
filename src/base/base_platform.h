#ifndef BASE_PLATFORM_H
#define BASE_PLATFORM_H

#if PLATFORM_UNIX

#define PlatformCreateWindow(arena, height, width, xpos, ypos)  linux_x11_create_window(arena, height, width, xpos, ypos)
							    
#define PlatformDrawLine() ...
#define PlatformDrawRect() ...

#define PlatformLoadLibrary

#elif PLATFORM_WINDOWS

#define PlatformCreateWindow() ...
#define PlatformDrawLine() ...
#define PlatformDrawRect() ...

#define PlatformLoadLibrary

#else
#error unsupported platform
#endif 

#endif // BASE_PLATFORM_H
