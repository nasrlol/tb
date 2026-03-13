#ifndef PLATFORM_H
#define PLATFORM_H

#define NIL 0

#include <X11/X.h>
#include <X11/Xlib.h>
 #include <X11/keysym.h>
#include <time.h>
#include <unistd.h>

typedef struct WindowProperties WindowProperties;
struct WindowProperties
{
    i32 x;
    i32 y;
    u32 height;
    u32 width;
    u32 border_width;
    i32 window_depth;
    u32 window_class;
    u64 value_mask;

};

typedef struct vertex vertex;

struct vertex
{
    i32 x;
    i32 y;
    i32 z;
};

typedef struct display_pos display_pos;

struct display_pos
{
    i32 x;
    i32 y;

};

typedef struct pos pos;
struct pos
{
    i32 x;
    i32 y;
    i32 z;

} ;




#endif /* PLATFORM_H */
