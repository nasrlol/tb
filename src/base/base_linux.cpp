internal linux_x11_win
linux_x11_create_window(MemArena *arena, u32 window_height, u32 window_width, u32 disp_x, u32 disp_y)
{

    Display *MainDisplay = XOpenDisplay(0);
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

    Window window = XCreateWindow(
	MainDisplay,            // display
	root,                   // parent
	disp_x,                 // x
	disp_y,                 // y
	window_width,           // width
	window_height,          // height
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

    return {


    };
}

internal void
draw_to_window(linux_x11_win *s)
{

    u32 color = 0x55ffaaff;
    GC gc = XCreateGC(s->display, s->window, 0, Nil);
    XSetForeground(s->display, gc, color);

    XFreeGC(s->display, gc);
}


internal s32
linux_x11_cleanup(linux_x11_win *s)
{
    
    XCloseDisplay(s->display);

    // TODO: ...

    return 0;

}
