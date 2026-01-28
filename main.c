#include <X11/X.h>
#include <X11/Xlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

#include "base/base.h"
#include "base/base_arena.h"

#include "base/base.c"
#include "base/base_arena.c"


#define NIL 0

typedef struct
{
i32 x;
i32 y;
u32 height;
u32 width;
u32 border_width;
i32 window_depth;
u32 window_class;
u64 value_mask;

} WindowProperties;

typedef struct
{
i32 x;
i32 y;
i32 z;

} vertex;

void
sleep_ms(long ms)
{
struct timespec ts;
ts.tv_sec = ms / 1000;
ts.tv_nsec = (ms % 1000) * 1000000L;

while (nanosleep(&ts, &ts))
{
NULL;
}
}

void
move_down(double *y)
{
++*y;
}

void
move_up(double *y)
{
--*y;
}

void
move_left(double *x)
{
--*x;
}

void
move_right(double *x)
{
++*x;
}



typedef struct
{
void (*move)(double *a);
} movement;

void
handle_destroy(Display *display, GC *gc)
{
XFreeGC(display, *gc);
XCloseDisplay(display);
}

typedef struct
{
i32 x;
i32 y;

} display_pos;

typedef struct
{
i32 x;
i32 y;
i32 z;

} pos;


int
main()
{
Display *MainDisplay = XOpenDisplay(0);
mem_arena *arena = arena_create(MiB(8));

Window root = XDefaultRootWindow(MainDisplay);
int screen = DefaultScreen(MainDisplay);

Visual *v = DefaultVisual(MainDisplay, screen);

XSetWindowAttributes wa = {
.background_pixmap = None,
.background_pixel = BlackPixel(MainDisplay, DefaultScreen(MainDisplay)),
.border_pixmap = CopyFromParent,
.border_pixel = 0,
.bit_gravity = ForgetGravity,
.win_gravity = NorthWestGravity,
.backing_store = NotUseful,
.backing_planes = 1,
.backing_pixel = 0,
.save_under = False,
.event_mask = {},
.do_not_propagate_mask = {},
.override_redirect = False,
.colormap = CopyFromParent,
.cursor = None
};

i32 dp_heigth = DisplayHeight(MainDisplay, screen);
i32 dp_width = DisplayWidth(MainDisplay, screen);

WindowProperties p = {

.x = dp_width / 2,
.y = dp_heigth / 2,
.height = (u32)800,
.width = (u32)1200,
.border_width = 0,
.window_depth = CopyFromParent,
.window_class = CopyFromParent,
.value_mask = CWBackPixel,

};


Window window =
XCreateWindow(
MainDisplay,
root,
p.x,
p.y,
p.width,
p.height,
p.border_width,
p.window_depth,
p.window_class,
v,
p.value_mask,
&wa);

Pixmap pixmap = XCreatePixmap(MainDisplay, window, dp_width, dp_heigth, 1);

XSetWindowBorder(MainDisplay, window, 60);
XSelectInput(MainDisplay, window, ExposureMask | StructureNotifyMask);
XMapWindow(MainDisplay, window);


double x = p.width / 2;
double y = p.height / 2;

u32 rect_width = 50;
u32 rect_height = 50;

u64 color = 0x0000ff00;

GC gc = XCreateGC(MainDisplay, window, 0, NIL);
XSetForeground(MainDisplay, gc, color);


double *pX = &x;
double *pY = &y;

movement m = {
.move = move_down
};

XEvent event;
XNextEvent(MainDisplay, &event);

for (;;)
{
switch (event.type)
case KeyPress:
case KeyRelease:
{


}
default:
{
if (*pX + rect_width >= p.width)
{
m.move = move_left;
}
else if (*pX <= 0)
{
m.move = move_right;
}

char words[] = "working";

XTextItem ti = {
.chars = words,
.nchars = (int)strlen(words),
.delta = 0,
.font = None
};

XClearWindow(MainDisplay, window);

pos *p = arena_push(arena, sizeof(*p),  0);

p->z = 10;
p->x = ((i32)*pX * 10) / p->z;
p->y = ((i32)*pY * 10) / p->z;

XFillRectangle(
MainDisplay,
window,
gc,
(i32)p->x,
(i32)p->y,
rect_height,
rect_width);

m.move(&x);

sleep_ms(1);

XFlush(MainDisplay);
}

case DestroyNotify:
{
// handle_destroy(MainDisplay, &gc);
}
}

arena_clear(arena);
return 0;
}
