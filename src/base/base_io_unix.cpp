//- implementations
internal b32
unix_file_exists(String8 path)
{
    return access((const char *)path.data, F_OK) == 0;
}

//- file stuff
internal String8
unix_file_load(MemArena *arena, String8 path)
{
    String8     result = {0};
    struct stat sbuf   = {0};

    s32 file = open((const char *)path.data, O_RDONLY);
    if(file == -1)
    {
        Log("An error occurred. File was not loaded. error code: %s", file);
        return (String8){0};
    }

    if(fstat(file, &sbuf) == -1)
    {
        close(file);
        return str8_zero();
    }

    result      = PushString8(arena, (u64)sbuf.st_size);
    result.size = (u64)sbuf.st_size;
    if(result.size != 0)
        result.data = (u8 *)mmap(0, result.size, PROT_READ, MAP_PRIVATE, file, 0);

    close(file);
    return result;
}

internal String8
unix_file_write(String8 data, String8 path)
{
    String8 result = {0};
    s32     file   = open((const char *)path.data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(file == -1)
    {
        return (String8){0};
    }

    u64 written = 0;
    while(written < data.size)
    {
        s64 err = write(file, data.data + written, data.size - written);
        if(err == -1)
        {
            close(file);
            return str8_zero();
        }
        written += err;
    }

    close(file);
    result = data;
    return result;
}

internal void
unix_log_with_args(const char *format, ...) 
{
    va_list arguments;
    va_start(arguments, format);
    vprintf(format, arguments);
    va_end(arguments);
}


internal b32
unix_os_exit()
{
    _exit(0);
    return true;
}
