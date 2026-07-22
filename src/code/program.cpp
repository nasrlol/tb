#define BASE_PLATFORM
#include "base/base_include.h"
#include "render/render.h"

int ENTRYPOINT(
               HINSTANCE instance,
               HINSTANCE prev_instance,
               LPSTR cmdline,
               int cmdshow)
{

    MemArena *arena = ArenaCreate(MiB(100));
    PlatformCreateWindow(instance, 100, 100, 100, 100);

    ArenaDestroy(arena);
    return (0);
}

