#include "common_string.h"
#include "../common.h"

#include <stdlib.h>
#include <string.h>

// Strings

String_t z__String_create(int size)
{
    return (String_t){

        .str = malloc(sizeof(char) * size),
        .size = size,
        .used = 0
    };
}

inline void z__String_delete(String_t * s)
{
    free(s->str);
    s->size = 0;
    s->used = 0;
}

String_t z__String_copy(const String_t str)
{

    String_t str2 = {
        .str = malloc(sizeof(char) * str.size),
        .size = str.size,
        .used = str.used
    };

    memcpy(str2.str, str.str, str.size);

    return str2;
}

inline void z__String_write(String_t *s, const char *st)
{
    memcpy(s->str, st, s->size);
}

inline void z__String_join(String_t *dest, String_t *src, zse_u32 extraSpace)
{
    dest->size = dest->size + src->used + extraSpace;
    dest->str = reallocf(dest->str, dest->size);

    memcpy(&dest[dest->used], src->str, src->used);
}

/* See if `Char` exist in a string */
int z_findCharInStr(String_t str, char c, int fromIndex)
{
    for (int i = fromIndex; i < str.size; ++i)
    {
        if(str.str[i] == c)
            return i;
    }
    return -1;
}


// Malloc And Free 2d Char, Taken from Ztorg (https://github.com/zakarouf/ztorg)
static char **zse_malloc_2D_array_char (unsigned int x, unsigned int y) {

    char **arr = malloc(y * sizeof(char*));
    for (int i = 0; i < y; ++i)
    {
        arr[i] = malloc(x * sizeof(char));
    }

    return arr;

}
static void zse_free2dchar(char **mem, int size)
{
    for (int i = 0; i < size; ++i)
    {
        free(mem[i]);
    }
    free(mem);

}


StringLines_t z__StringLines_createEmpty(int x, int y)
{
    return (StringLines_t){
        .lines = zse_malloc_2D_array_char(x, y),
        .x = x,
        .y = y
    };
}
void z__StringLines_destroy(StringLines_t *strLines)
{
    zse_free2dchar(strLines->lines, strLines->y);
    strLines->x = 0;
    strLines->y = 0;
}

StringLines_t z__StringLines_MakeCopy(StringLines_t strLines)
{
    StringLines_t tmp = z__StringLines_createEmpty(strLines.x, strLines.y);
    for (int i = 0; i < tmp.y; ++i)
    {
        memcpy(tmp.lines[i], strLines.lines[i], tmp.x);
    }
    return tmp;
}

void z__StringLines_Resize_Y (StringLines_t *ln , unsigned int newsize)
{
    if (ln->y > newsize)
    {
        for (int i = newsize; i < ln->y; ++i)
        {
            free(ln->lines[i]);
        }
        ln->lines = realloc(ln->lines, sizeof(char*)*newsize);
        
    }
    else if (ln->y < newsize)
    {
        ln->lines = realloc(ln->lines, newsize);
        for (int i = ln->y; i < newsize; ++i)
        {
            ln->lines[i] = malloc(sizeof(char) * ln->x);
        }
    }

    ln->y = newsize;
}
void z__StringLines_Resize_X (StringLines_t *ln, unsigned int newsize)
{
    for (int i = 0; i < ln->y; ++i)
    {
        ln->lines[i] = realloc(ln->lines[i], sizeof(char) * newsize);
    }

    ln->x = newsize;   
}



StringLineArr_t z__StringLinesArr_createEmpty(int size, int x, int y)
{
    StringLineArr_t lns = {
        .fn = malloc(sizeof(StringLines_t) * size),
        .size = size,
        .used = 0
    };

    for (int i = 0; i < lns.size; ++i)
    {
        lns.fn[i] = z__StringLines_createEmpty(x, y);
    }

    return lns;
}

void z__StringLinesArr_resize(StringLineArr_t *lns, int newsize)
{
    if (newsize < lns->size)
    {
        for (int i = newsize; i < lns->size; ++i)
        {
            z__StringLines_destroy(&lns->fn[i]);
        }
        lns->fn = realloc(lns->fn, sizeof(StringLines_t) * newsize);
        lns->size = newsize;
    }
    else if (newsize > lns->size)
    {
        lns->fn = realloc(lns->fn, sizeof(StringLines_t) * newsize);
        lns->size = newsize;
        for (int i = lns->size; i < newsize; ++i)
        {
            lns->fn[i] = z__StringLines_createEmpty(lns->fn[0].x, lns->fn[0].y);
        }
    }
}

void z__destroyStringLinesArr(StringLineArr_t *lns)
{
    for (int i = 0; i < lns->size; ++i)
    {
        z__StringLines_destroy(&lns->fn[i]);
    }
    lns->size = 0;
}

// String END
