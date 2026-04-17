#ifndef BASE_INCLUDE_H
#define BASE_INCLUDE_H

#include <dirent.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>

#include "base.h"
#include "base_mem.h"

#include "base_arena.h"
#include "base_stack.h"

#ifdef BASE_IMPLEMENTATION
#include "base_arena.c"
#endif


#include "base_string.h"
#include "base_string.c"

#include "base_os.h"
#include "base_error.h"

#include "base_rand.h"



#endif
