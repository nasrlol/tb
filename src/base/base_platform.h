#ifndef BASE_PLATFORM_H
#define BASE_PLATFORM_H


typedef struct Library Library;
struct Library
{
    u64 data;
};

#if PLATFORM_UNIX

#define PlatformCreateWindow(arena, height, width, xpos, ypos)  
							    
#if 0 // TODO
#define PlatformDrawLine() 
#define PlatformDrawRect()
#define PlatformLoadLibrary
#endif


#elif PLATFORM_WINDOWS


#if 0 // TODO
#define PlatformCreateWindow() 
#define PlatformDrawLine() 
#define PlatformDrawRect() 
#define PlatformLoadLibrary
#endif


#else
#error unsupported platform
#endif 

#endif // BASE_PLATFORM_H
