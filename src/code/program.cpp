#define BASE_PLATFORM
#include "base/base_include.h"

int main() {

    MemArena *arena = ArenaCreate(MiB(100));


    String8 buffer  = str8("Hello World");
    String8 chopped = remove_null_terminator(arena, buffer);



    if (chopped.data[chopped.size - 1] == '\0');

    breakpoint();

    Log("String8 buffer: " Str8Fmt, Str8Arg(buffer));

    const char *cstring_buffer = null_terminate(arena, &buffer);
    breakpoint();
    Log("Regular buffer: %s\n", cstring_buffer);

    
    ArenaDestroy(arena);
    return (0);
}

