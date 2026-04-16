#ifndef TB_H
#define TB_H

typedef struct enemy enemy;
struct enemy
{
    enemy *next;
    enemy *prev;
    u64 color;
    s32 x, y;
};

typedef struct enemy_list enemy_list;
struct enemy_list
{
    enemy *first;
    enemy *last;

    s32 count;
};


typedef struct user user;
struct user
{
    u64 color;
    b32 alive;
    s32 x;
    s32 y;
    u64 width;
    s32 height;
};

#endif
