#define BASE_PLATFORM
#include "base/base_include.h"

int main() {

    MemArena *arena = ArenaCreate(MiB(100));


    

    LinuxCreateWindow(arena, 100, 100, 100, 100) ;

    ArenaDestroy(arena);
    return (0);
}

