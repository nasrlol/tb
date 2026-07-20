internal linux_wm_state
x11_create_window(MemArena *arena,
		  u32 window_height,
		  u32 window_width,
		  u32 display_x,
		  u32 display_y)
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
	root,                    // parent
	display_x,               // x
	display_y,               // y
	window_width,            // width
	window_height,           // height
	0,                       // border_width
	CopyFromParent,          // depth
	CopyFromParent,          // class
	v,                       // depth
	CWBackPixel,             // visual
	&wa);

    XSetWindowBorder(main_display, window, 60);
    XSelectInput(main_display, window, ExposureMask | StructureNotifyMask | KeyReleaseMask | KeyPressMask);
    XMapWindow(main_display, window);
    linux_wm_state out = { main_display, window, screen };

    return out;
    
}

internal void
x11_draw(linux_wm_state *s, s32 start_x, s32 end_x, s32 start_y, s32 end_y)
{

    u32 color = 0x55ffaaff;
    GC gc = XCreateGC(s->display, s->window, 0, Nil);
    XSetForeground(s->display, gc, color);

    XFreeGC(s->display, gc);
}


internal s32
x11_cleanup(linux_wm_state *s)
{
    XCloseDisplay(s->display);
    return 0;

}


internal s32
x11_read_input()
{

    return 0;
}


//-

internal Library
unix_library_load(MemArena *arena, String8 path)
{

    const char *cstring_path = null_terminate(arena, &path);
    void *lib = dlopen((const char *)path.data, RTLD_LAZY|RTLD_LOCAL);
    return { (u64)lib } ;

}

internal void *
unix_library_get_proc(Library *library, String8 proc_name)
{

    return NULL;
}


internal int
unix_library_close(Library *library)
{
    int result = dlclose(library);

    if(result)
    {

    }

    return result;
}


//-

internal u64
x11_load_bitmap_from_file()
{

    return 0;
}
