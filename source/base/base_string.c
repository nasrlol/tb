internal umm
skip_whitespaces(string *buffer)
{
    s32 index = 0;
    while (buffer->size > index)
    {
        ++index;
    }
}

internal b8
compare_string_struct(string c1, string c2)
{
    if (c1.size != c2.size)
    {
        return -1;
    }

    for (s32 index = 0;
    index < c1.size;
    ++index)
    {
        if (c1.Data[index] != c2.Data[index])
        {
            return -1;
        }
    }

    return 0;
}

internal b8
compare_string(char *c1, char *c2)
{
    if (sizeof(*c1) != sizeof(*c2))
    {
        return -1;
    }

    for (
    u64 word_idx = 0;
    word_idx <= sizeof(*c1);
    ++word_idx)
    {
        if (*c1 != *c2)
        {
            return -1;
        }
        ++c1;
        ++c2;
    }

    return 0;
}

/** NOTE(nasr): Helper function to parse strings to int using ascii codes **/
internal u64
parse_u64(char *buf, umm len)
{
    u64 value = 0;

    for (umm buffer_idx = 0; buffer_idx < len; ++buffer_idx)
    {
        char c = buf[buffer_idx];
        if (c < '0' || c > '9')
        {
            break;
        }
        value = value * 10 + (c - '0');
    }

    return value;
}
