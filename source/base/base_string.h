#ifndef BASE_STRING_H
#define BASE_STRING_H

// let's use this for strings
// to better differentiate between stuff
typedef u8  s8;
typedef struct string string ;

struct string
{
    s8 *data;
    umm size;
};

// TODO(nasr): helper functions for string

#endif /* BASE_STRING_H */
