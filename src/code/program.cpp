#define BASE_PLATFORM
#include "base/base_include.h"

int main() {

    MemArena *arena = ArenaCreate(MiB(100));
    linux_x11_win s = PlatformCreateWindow(arena, 1600, 800, 100, 100);

    linux_x11_cleanup(&s);
    ArenaDestroy(arena);
    return (0);
}

