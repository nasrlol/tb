#ifndef STACK_H
#define STACK_H

typedef struct mem_stack        mem_stack;
typedef struct mem_stack_header mem_stack_header;

struct mem_stack
{
    u8 *base_position;
    umm current_offset;
    umm capacity;
};

struct mem_stack_header
{
    u8 padding;
    u8 previous_offset;
};

#endif
