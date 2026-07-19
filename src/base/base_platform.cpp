internal void
platform_create_window_linux(mem_arena *arena, u32 height, u32 width, u32 xpos, u32 ypos)
{
    if(LibraryOpen("X11/X.h"))
    {
	// Then we are fine
    }
    else if(LibraryOpen("wayland-client.h"))
    {
	// Then we are fine
    }
    else
    {
    }


    linux_x11_create_window(arena, height, width, xpos, ypos)

}


}
