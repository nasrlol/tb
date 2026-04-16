#define BASE_IMPLEMENTATION
#define BASE_RAND_IMPLEMENTATION
#define BASE_MATH_IMPLEMENTATION
#define BASE_PLATFORM
#define BASE_PLATFORM_IMPLEMENTATION
#include "../base/base_include.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 1200

internal void
load_entities(Display *MainDisplay, Window *window, GC *gc, s32 entity_count)
{
    s32 x = (s32)generate_random_u64(RAND_CONSTANT);
    s32 y = (s32)generate_random_u64(RAND_CONSTANT);

    for (s32 index = 0; index < entity_count; ++index)
    {
        s32 delta = (s32)generate_random_u64(RAND_CONSTANT);

        XDrawRectangle(MainDisplay,
        *window,
        *gc,
        x * (1/delta),
        y * (1/delta),
        50,
        50);

        XFillRectangle(MainDisplay,
        *window,
        *gc,
        x * (1/delta),
        y * (1/delta),
        50,
        50);
    }
}


internal void
load_user(Display *MainDisplay, Window *window, GC *gc, s32 x, s32 y, u32 width, u32 height)
{
        XDrawRectangle(MainDisplay, *window, *gc, x, y, width, height);
        XFillRectangle(MainDisplay, *window, *gc, x, y, width, height);
}


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

    s32 dp_heigth = DisplayHeight(MainDisplay, screen);
    s32 dp_width = DisplayWidth(MainDisplay, screen);


    WindowProperties p = {

        .x =
        .y =
        .height =
        .width =
        .border_width = 0,
        .window_depth = CopyFromParent,
        .window_class =
        .value_mask   =

    };

    Window window = XCreateWindow( MainDisplay, root, dp_width / 2, dp_heigth / 2,
                (u32)WINDOW_WIDTH, (u32)WINDOW_HEIGHT, 0, CopyFromParent, v, CWBackPixel, &wa);

    XSetWindowBorder(MainDisplay, window, 60);
    XSelectInput(MainDisplay, window, ExposureMask | StructureNotifyMask | KeyReleaseMask | KeyPressMask);
    XMapWindow(MainDisplay, window);
    XEvent event;

    f32 DELTA = 2.5;

    u32 rect_width = 50;
    u32 rect_height = 50;

    s32 rect_x_position = p.width / 2;
    s32 rect_y_position = p.height / 2;

    s32 rect_enemy_x_position = (p.width / 2)  + 300;
    s32 rect_enemy_y_position = (p.height / 2) + 300;

    u64 color = 0x0FF0FF00;

    GC gc = XCreateGC(MainDisplay, window, 0, NIL);
    XSetForeground(MainDisplay, gc, color);

    for (;running;)
    {
        //- handle collision detection
        {
            if(rect_y_position >= WINDOW_HEIGHT)    DELTA = -DELTA;
            if(rect_x_position >= WINDOW_WIDTH)     DELTA = -DELTA;

            if(rect_enemy_y_position >= WINDOW_HEIGHT)    DELTA = -DELTA;
            if(rect_enemy_x_position >= WINDOW_WIDTH)     DELTA = -DELTA;
        }

        //- handle enemy movement
        {
            s32 dy = rect_y_position - rect_enemy_y_position;
            s32 dx = rect_x_position - rect_enemy_x_position;

            //- normalize the distance | why this is needed? no clue
            f32 distance = sqrtf(dx*dx + dy*dy);

            if(distance > 1.0f) {
                f32 speed = DELTA * 0.5f;
                rect_enemy_x_position += (s32)((dx / distance) * speed);
                rect_enemy_y_position += (s32)((dy / distance) * speed);
            }
        }

        XNextEvent(MainDisplay, &event);

        switch (event.type)
        {
            case(KeyPress):
                {
                    KeySym keysym = XLookupKeysym(&event.xkey, 0);
                    //- handle user movement
                    {
                        if(keysym == XK_h)      rect_x_position -= DELTA*1.5;
                        else if(keysym == XK_l) rect_x_position += DELTA*1.5;
                        else if(keysym == XK_k) rect_y_position -= DELTA*1.5;
                        else if(keysym == XK_j) rect_y_position += DELTA*1.5;
                        else if(keysym == XK_s);
                        else if(keysym == XK_Escape || keysym == XK_q) goto exit;
                    }


                    // clear screen before drawing entities

                    XClearWindow(MainDisplay, window);

                    //- draw entities
                    {
                    } break;
                }
            default:
                {

                }
        }
    }


exit:
    arena_destroy(arena);
    return 0;
}
