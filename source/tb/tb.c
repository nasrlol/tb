#define BASE_IMPLEMENTATION
#define BASE_RAND_IMPLEMENTATION
#define BASE_MATH_IMPLEMENTATION
#include "../base/base_include.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "tb.h"


internal void
el_push(enemy_list *el, enemy *en)
{

    en->next = NULL;

    if (el->first == NULL) {
        el->first = en;
        el->last = en;
    } else {
        el->last->next = en;
        el->last = en;
    }
    el->count++;
}


internal void
pop_enemies(enemy_list *el)
{
    unused(el);
    //- TODO(nasr): implement a stack design
}

internal void
load_enemies(Display *MainDisplay, Window *window, GC *gc, enemy_list *el)
{
    s32 x = (s32)generate_random_u64(RAND_CONSTANT) / ( 10 << 8 );
    s32 y = (s32)generate_random_u64(RAND_CONSTANT) / ( 10 << 8 );

    if(el->first == NULL)
    {
        return;
    }
    enemy *current = el->first;

    for (s32 index = 0; index < el->count; ++index)
    {

        s32 delta = (s32)generate_random_u64(RAND_CONSTANT);

        //- draw
        {
            XDrawRectangle(MainDisplay, *window, *gc, x * (1/delta), y * (1/delta), 50, 50);
            XFillRectangle(MainDisplay, *window, *gc, x * (1/delta), y * (1/delta), 50, 50);
        }



        {
            s32 dx, dy;

            if(current->next)
            {
                 dx = current->x - current->next->x;
                 dy = current->y - current->next->y;
                 _log("shawakoemba");

            } else
            {
                 dx = 50;
                 dy = 50;
            }

            //- normalize the distance | why this is needed? no clue
            f32 distance = sqrtf(dx*dx + dy*dy);

            if(distance > 1.0f) {

                f32 speed = delta * 0.5f;

                current->x += (s32)((dx / distance) * speed);
                current->y += (s32)((dy / distance) * speed);
            }

            for (s32 index = 0; index < el->count; ++index) {
                if(current->x >= 500)   delta = -delta;
                if(current->y >= 500)  delta = -delta;

                if(current->x >= 500) delta = -delta;
                if(current->x >=  500) delta = -delta;
            }

        }

        if(current->next != NULL)
        {
            current = current->next;
        }
    }

    // handle enemys
}

int main()
{
    b32 running = 1;

    Display *MainDisplay = XOpenDisplay(0);
    mem_arena *global_arena = arena_create(MiB(8));
    mem_arena *enemy_arena  = arena_create(MiB(100));

    Window root = XDefaultRootWindow(MainDisplay);
    int screen = DefaultScreen(MainDisplay);

    Visual *v = DefaultVisual(MainDisplay, screen);


    XSetWindowAttributes wa = {
        .background_pixmap = None,
        .background_pixel = BlackPixel(MainDisplay, DefaultScreen(MainDisplay)),
        .border_pixmap = CopyFromParent,
        .border_pixel= 0,
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

    s32 WINDOW_WIDTH = 1600;
    s32 WINDOW_HEIGHT = 800;

    Window window = XCreateWindow(
            MainDisplay,            // display
            root,                   // parent
            (dp_width / 2),         // x
            (dp_heigth / 2),        // y
            (u32)WINDOW_WIDTH,      // width
            (u32)WINDOW_HEIGHT,     // height
            0,                      // border_width
            CopyFromParent,         // depth
            CopyFromParent,         // class
            v,                      // depth
            CWBackPixel,            // visual
            &wa);

    XSetWindowBorder(MainDisplay, window, 60);
    XSelectInput(MainDisplay, window, ExposureMask | StructureNotifyMask | KeyReleaseMask | KeyPressMask);
    XMapWindow(MainDisplay, window);
    XEvent event;


    GC gc = XCreateGC(MainDisplay, window, 0, NIL);
    XSetForeground(MainDisplay, gc, 0x53f830a2);

    s32 delta = 20;

    enemy_list *el = PushStruct(enemy_arena, enemy_list);

    el->first = NULL;
    el->last  = NULL;
    el->count = 0;

    user user =
    {

        .color = 0x4af333f4ff,
        .alive = False,
        .x     = 400,
        .y     = 400,
        .width = 50,
        .height = 50,

    };


    for (;running;)
    {
        //- handle collision detection
        //- handle enemy movement


        XNextEvent(MainDisplay, &event);

        switch (event.type)
        {
            case(KeyPress):
                {
                    KeySym keysym = XLookupKeysym(&event.xkey, 0); //- handle user movement
                    {

                        if(keysym == XK_h)      user.x -= (delta*1.5);
                        else if(keysym == XK_l) user.x += (delta*1.5);
                        else if(keysym == XK_k) user.y -= (delta*1.5);
                        else if(keysym == XK_j) user.y += (delta*1.5);
                        else if(keysym == XK_s);
                        else if(keysym == XK_Escape || keysym == XK_q) goto exit;
                        else if(keysym == XK_p) {

                            enemy *en = PushStruct(enemy_arena, enemy);
                            el_push(el, en);

                        }
                    }


                    //- draw entities
                } break;
            default: {
                         _log("exited");

                     }
        }

        // clear screen before drawing entities
        XClearWindow(MainDisplay, window);

        load_enemies(MainDisplay, &window, &gc, el);

        XDrawRectangle(MainDisplay, window, gc, user.x, user.y, user.width, user.height);
        XFillRectangle(MainDisplay, window, gc, user.x, user.y, user.width, user.height);

        user.color = user.color << 8;

    }

exit:
    arena_destroy(global_arena);
    return 0;
}
