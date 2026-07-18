internal void
platform_create_window_linux(mem_arena *arena, u32 height, u32 width, u32 xpos, u32 ypos)
{
    if(library_open("X11/X.h"))
    {


	// Then we are fine
    }
    else if(library_open("wayland stuff"))
    {
	// Then we are fine
       
    }
    else
    {

	// We are not fine
    }

    linux_x11_create_window(arena, height, width, xpos, ypos)



}
