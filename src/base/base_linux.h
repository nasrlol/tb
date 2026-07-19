#ifndef BASE_LINUX_H
#define BASE_LINUX_H

internal int LinuxEntrypoint(MemArena *arena, u32 window_height, u32 window_width, u32 disp_x, u64 disp_y);

typedef struct linux_x11_win linux_x11_win;
struct linux_x11_win
{
  Display *display;
  Window  window;
  s32 screen;
};

typedef struct Library Library;
struct Library
{
    u64 data;
};

#endif // BASE_LINUX_H
