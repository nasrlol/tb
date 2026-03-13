#define TB_IMPLEMENTATION
#include "core.h"
#include "../base/base_include.h"
#include "../platform/platform_include.h"

int main()
{
    b32 running = 1;

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
        .event_mask = 0,
        .do_not_propagate_mask = 0,
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

	// NOTE(nasr): type of input we want to handle
    XSelectInput(MainDisplay, window, ExposureMask | StructureNotifyMask | KeyReleaseMask);

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

    XEvent event;
    XNextEvent(MainDisplay, &event);

    for (;running;)
    {
        KeySym keysym = XLookupKeysym(event, 0);

        switch (event.type)
		{
            case (KeyPress):
		        {
                    if (keysym == XK_p || keysym == XK_P) 
                    {
                        XDrawRectangle(MainDisplay, screen, gc, 50, 50, 50, 50);
                    }

			        break;
		        }
            case (KeyRelease):
		        {
                    if (keysym == XK_p || keysym == XK_P) 
                    {
                        XDrawRectangle(MainDisplay, screen, gc, 50, 50, 50, 50);
                    }

			        break;
		        }
            default:
                {

                }

		}
	}
    arena_clear(arena);
    return 0;
}
