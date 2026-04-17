#ifndef BASE_OS_H
#define BASE_OS_H

#define STDIN_FD  0
#define STDOUT_FD 1
#define STDERR_FD 2

#endif /* BASE_OS_H */

#ifdef BASE_IMPLEMENTATION

internal string8
load_file(mem_arena *arena, const char *path)
{
    string8 result = {0};
    struct stat sbuf = {0};

    // TODO(nasr): abstract this to a platform layer
    s32 file = open(path, O_RDONLY);
    if(file == -1)
    {
        return (string8){0};
    }

    if(fstat(file, &sbuf) == -1)
    {
        close(file);
        return (string8){0};
    }


    result = PushString8(arena, sbuf.st_size);

    result.size = (u64)sbuf.st_size;
    if(result.size != 0)
    {
        result.data = (u8 *)mmap(0, result.size, PROT_READ, MAP_PRIVATE, file, 0);
    }

    close(file);
    return result;
}

internal string8
write_file(const char *path, string8 data)
{
    string8 result = {0};
    s32 file = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(file == -1)
    {
        return (string8){0};
    }

    u64 written = 0;
    while(written < data.size)
    {
        s64 err = write(file, data.data + written, data.size - written);
        if(err == -1)
        {
            close(file);
            return (string8){0};
        }
        written += err;
    }

    close(file);
    result = data;
    return result;
}

#define os_write(buf, count) _os_write(STDIN_FD, buf, count)
#define os_read(buf,  count)  _os_read(STDIN_FD, buf, count)

internal s64
_os_write(s32 fd, void const *buf, u64 count)
{
    return syscall(SYS_write, fd, buf, count);
}

internal s64
_os_read(s32 fd, void *buf, u64 count)
{
    return syscall(SYS_read, fd, buf, count);
}

internal void
log_s8(string8 s)
{
    os_write(s.data, s.size);
}

#if 1
internal void
_log(const char *str)
{
#ifdef BASE_LOGGING
    s32 len = 0;
    while (str[len]) len++;
    os_write(str, len);
#else
    unused(str);
#endif

}
#endif

internal void
write_string(const char *str)
{
    s32 len = 0;
    while (str[len]) len++;
    os_write(str, len);
}

internal void
write_int(s32 num)
{

    if (num < 0)
    {
        write(STDERR_FILENO, "-", 1);
        num = -num;
    }
    if (num >= 10) write_int(num / 10);

    char digit = '0' + (num % 10);

    write(STDERR_FILENO, &digit, 1);
}

internal inline void
sleep_ms(long ms)
{
  struct timespec ts;
  ts.tv_sec = ms / 1000;
  ts.tv_nsec = (ms % 1000) * 1000000L;

  while (nanosleep(&ts, &ts))
  {
    NULL;
  }
}


#endif
