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

    XSetWindowBorder(MainDisplay, window, 60);
    XSelectInput(MainDisplay, window, ExposureMask | StructureNotifyMask | KeyReleaseMask | KeyPressMask);
    XMapWindow(MainDisplay, window);
    XEvent event;

    f32 DELTA = 2.5;

    u32 rect_width = 50;
    u32 rect_height = 50;

    i32 rect_x_position = p.width / 2;
    i32 rect_y_position = p.height / 2;

    i32 rect_enemy_x_position = (p.width / 2)  + 300;   
    i32 rect_enemy_y_position = (p.height / 2) + 300; 

    u64 color = 0x0FF0FF00;

    GC gc = XCreateGC(MainDisplay, window, 0, NIL);
    XSetForeground(MainDisplay, gc, color);

    for (;running;)
    {
        //- handle enemy movement
        {
            if(rect_enemy_x_position < rect_x_position) rect_enemy_x_position += DELTA*0.5;
            if(rect_enemy_y_position < rect_y_position) rect_enemy_y_position += DELTA*0.5;

            if(rect_enemy_x_position > rect_x_position) rect_enemy_x_position -= DELTA*0.5;
            if(rect_enemy_y_position > rect_y_position) rect_enemy_y_position -= DELTA*0.5;
        }

        XNextEvent(MainDisplay, &event);

        switch (event.type)
		{
            case(KeyPress):
		        {

                    KeySym keysym = XLookupKeysym(&event.xkey, 0);
                    //- handle user movement
                    {
                        if(keysym == XK_h)      rect_x_position -= DELTA*1.2;
                        else if(keysym == XK_l) rect_x_position += DELTA*1.2;
                        else if(keysym == XK_k) rect_y_position -= DELTA*1.2;
                        else if(keysym == XK_j) rect_y_position += DELTA*1.2;
                        else if(keysym == XK_s);
                        else if(keysym == XK_Escape || keysym == XK_q) goto exit;
                    }

                    //- draw entities
                    {
                        XClearWindow(MainDisplay, window);

                        //--
                        XDrawRectangle(MainDisplay, window, gc, rect_x_position, rect_y_position, 50, 50);
                        XFillRectangle(MainDisplay, window, gc, rect_x_position, rect_y_position, 50, 50);

                        //--
                        XDrawRectangle(MainDisplay, window, gc, rect_enemy_x_position, rect_y_position, 50, 50);
                        XFillRectangle(MainDisplay, window, gc, rect_enemy_x_position, rect_y_position, 50, 50);
                    } break;
		        }
            default:
		}
	}
exit:
    arena_clear(arena);
    return 0;
}
