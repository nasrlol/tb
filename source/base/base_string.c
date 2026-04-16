internal b32
is_alpha(u8 point)
{
    return ((point >= 'a' && point <= 'z') || (point >= 'A' && point <= 'Z') || (point == '_'));
}

internal b32
is_digit(u8 point)
{
    return (point >= '0' && point <= '9');
}

internal b32
is_alpha_num(u8 point)
{
    return (is_alpha(point) || is_digit(point));
}

internal b32 is_whitespace(u8 point)
{
    return (point == '\n' || point == '\r' || point == ' ' || point == '\t');
}

internal b32
is_slash(u8 point)
{
  return (point == '/' || point == '\\');
}


