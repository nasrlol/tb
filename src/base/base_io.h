#ifndef BASE_IO_H
#define BASE_IO_H

#define STDIN 0
#define STDOUT 1
#define STDERR 2

//-
#if PLATFORM_WINDOWS

#if COMPILER_GCC || COMPILER_CLANG
internal void win32_log_with_args(const char *mmessage, ...) PRINTF_FORMAT(1,2); 
#elif COMPILER_MSVC
internal void win32_log_with_args(_Printf_format_string_ const char *message, ...) ; 
#endif // COMPILER_GCC || COMPILER_CLANG

internal void win32_log(String8List messages);
internal b32  win32_os_exit();
internal b32  win32_file_exists(u8 *path);
internal b32  win32_file_write(String8 data, String8 path);
internal u64  safe_truncate_64(u64 value);
internal String8 win32_file_load(MemArena *arena, u8 *file);

#define FileLoad(arena, path) win32_file_load(arena, path)
#define FileWrite(data, path) win32_file_write(data, path)
#define FileExists(path) win32_file_exists(path)
#define OSExit() win32_os_exit();
#if COMPILER_GCC || COMPILER_CLANG

#define PRINTF_FORMAT(fmt, args) \
    __attribute__((format(printf, fmt, args)))

#define Log(...) win32_log_with_args(__VA_ARGS__) 

#elif COMPILER_MSVC
#define Log(message, ...)      win32_log_with_args(_Printf_format_string_ message, ...)
#endif // COMPILER_GCC || COMPILER_CLANG

#endif // PLATFORM_WINDOWS

#if PLATFORM_LINUX || PLATFORM_UNIX

internal String8   unix_file_write(String8 data, String8 path);
internal String8   unix_file_load(MemArena *arena, String8 path);
internal b32       unix_file_exists(String8 path);
internal b32       unix_os_exit();

internal s64       unix_read(int fd, const void *buf, u64 count);
internal s64       unix_log(int fd, const void *buf, u64 count);
internal void      unix_log_with_args(const char *format, ...);

//- File I/O
#define FileLoad(arena, path) unix_file_load(arena, path)
#define FileWrite(data, path) unix_file_write(data, path)
#define FileExists(path)      unix_file_exists(path)
#define OSExit() unix_os_exit();

#if COMPILER_GCC || COMPILER_CLANG
// TODO: I know that the __VA_ARGS are the correct ones for gcc but also check them out for clang
#define Log(...) unix_log_with_args(__VA_ARGS__)
#elif COMPILER_MSVC
#define Log(message, ...) unix_log_with_args(_Printf_format_string_ message, ...) // TODO: __VA_ARGS what is the implementation for msvc
// TODO: for this to wwork we need the /analyze argument
#endif // COMPILER_GCC || COMPILER_CLANG
#endif // PLATFORM_UNIX 

#endif /* BASE_IO_H */
