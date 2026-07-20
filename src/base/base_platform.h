#ifndef BASE_PLATFORM_H
#define BASE_PLATFORM_H

#if PLATFORM_UNIX


#define PlatformCreateWindow(arena, height, width, x, y)              LinuxCreateWindow(arena, height, width, x, y) 
#define PlatformGetDisplayWidth(display, screen_num )          LinuxDisplayWdith(display, screen_num)      
#define PlatformGetDisplayHeight(display, screen_num)          LinuxDisplayHeight(display, screen_num)    
#define PlatformLoadBitmapFromFile(display, window, path, width, height, out, hotspot_x, hotspot_y)        LinuxLoadBitMapFromFile(display, window, path, width, height, out, hotspot_x, hotspot_y)    


#elif PLATFORM_WINDOWS

// TODO: ...

#else

// TODO: ...

#endif

#endif // BASE_PLATFORM_H
