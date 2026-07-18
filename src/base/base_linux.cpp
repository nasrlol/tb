internal linux_x11_win
linux_x11_create_window(MemArena *arena, u32 window_height, u32 window_width, u32 disp_x, u32 disp_y)
{

    Display *main_display = XOpenDisplay(0);
    if(!main_display)
    {
	Log("Error! Failed to open x11 display. Are you on X11?");
    }
    else
    {
	Log("Successfully opened x11 display?\n");
	Log("Display: %p\n", main_display); 
    }

    Window root = XDefaultRootWindow(main_display);
    int screen = DefaultScreen(main_display);

    Visual *v = DefaultVisual(main_display, screen);

    XSetWindowAttributes wa = {
	.background_pixmap = None,
	.background_pixel = BlackPixel(main_display, DefaultScreen(main_display)),
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
	main_display,            // display
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

    XSetWindowBorder(main_display, window, 60);
    XSelectInput(main_display, window, ExposureMask | StructureNotifyMask | KeyReleaseMask | KeyPressMask);
    XMapWindow(main_display, window);

    return {
	    main_display,
	    window,
	    screen,
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
    return 0;

}


internal int
linux_x11_read_input()
{

    return 0;
}



internal void
library_open(String8 path)
{

    int result = dlopen(path);
    if(result)
    {
	Log("Failed to open library not available");
	return;
    }

}


internal void
library_close(String8 path)
{

    dlclose(path);

}
