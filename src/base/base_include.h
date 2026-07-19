#ifndef BASE_INCLUDE_H
#define BASE_INCLUDE_H

#if defined(__linux__) ||  defined(__APPLE__) 
#define PLATFORM_UNIX 1
#elif defined(__linux__) && !defined(__APPLE__)
#define PLATFORM_LINUX 1
#elif defined(_WIN32) || defined(_WIN64)
#define PLATFORM_WINDOWS 1
#elif defined(__APPLE__)
#define PLATFORM_APPLE 1
#else
#define PLATFORM_UNKNOWN 1
#endif // platform definitions

#if defined(PLATFORM_UNIX)

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif  // _GNU_SOURCE

#include <unistd.h>
#include <dirent.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dlfcn.h>

#elif defined(PLATFORM_WINDOWS)

#include <windows.h>
#include <memoryapi.h>

#endif

#include <time.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>

#include "base_core.h"
#include "base_arena.h"
#include "base_string.h"
#include "base_io.h"
#include "base_stack.h"


#include "base_arena.cpp"
#include "base_string.cpp"
#include "base_stack.cpp"

#if defined(PLATFORM_UNIX)
#include "base_io_unix.cpp"
#elif defined(PLATFORM_WINDOWS)
#include "base_io_win32.cpp"
#endif // PLATFORM_IO

#include "base_rand.cpp"
#include "base_simd.cpp"


#ifdef BASE_PLATFORM

#if PLATFORM_WINDOWS
#include "base_windows.h"
#include "base_windows.cpp"
#endif

#if PLATFORM_UNIX

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "base_linux.h"
#include "base_linux.cpp"

#endif

#include "base_platform.h"

#endif

#endif // BASE_INCLUDE_H
