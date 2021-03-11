#include "common_string.h"


#include <stdlib.h>
#include <string.h>

// Strings

String_t z__String_create(int size)
{
    return (String_t){

        .data = malloc(sizeof(z__char_t) * size),
        .size = size,
        .used = 0
    };
}

inline void z__String_delete(String_t * s)
{
    free(s->data);
    s->size = 0;
    s->used = 0;
}

inline void z__String_resize(String_t *str, int newsize)
{
    str->size = newsize;
    z__char_t *tmpdata = realloc(str->data, newsize);

    if (tmpdata != NULL)
    {
        if (tmpdata != str->data)
        {
            str->data = tmpdata;
        }
    }
}

void z__String_Copy(String_t *dest, const String_t val)
{
    if (dest->size < val.size )
    {
        z__String_resize(dest, val.size);
    }
    memcpy(dest->data, val.data, val.size);
}

String_t z__String_MakeCopy(const String_t str)
{

    String_t str2 = {
        .data = malloc(sizeof(z__char_t) * str.size),
        .size = str.size,
        .used = str.used
    };

    memcpy(str2.data, str.data, str.size);

    return str2;
}

String_t z__String_Link(const String_t str)
{
    return (String_t) {
        .data = str.data,
        .size = str.size,
        .used = str.used
    };
}

inline void z__Strint_append(String_t *str, const z__char_t* src, int length)
{
    if (length > 0)
    {
        if ((str->size-str->used) > length){
            memcpy(&str[str->used], src, length);

        } else {
            z__String_resize(str, length+str->size);
        }
        str->used += length;
    }
}

inline void z__String_write(String_t *s, const z__char_t *st)
{
    memcpy(s->data, st, s->size);
}

inline void z__String_join(String_t *dest, String_t *src, unsigned int extraSpace)
{
    dest->size = dest->size + src->used + extraSpace;
    dest->data = reallocf(dest->data, dest->size);

    memcpy(&dest[dest->used], src->data, src->used);
}

/* See if `Char` exist in a string */
int z_findCharInStr(String_t str, z__char_t c, int fromIndex)
{
    for (int i = fromIndex; i < str.size; ++i)
    {
        if(str.data[i] == c)
            return i;
    }
    return -1;
}


// Malloc And Free 2d Char, Taken from Ztorg (https://github.com/zakarouf/ztorg)
static z__char_t **zse_malloc_2D_array_char (unsigned int x, unsigned int y) {

    z__char_t **arr = malloc(y * sizeof(z__char_t*));
    for (int i = 0; i < y; ++i)
    {
        arr[i] = malloc(x * sizeof(z__char_t));
    }

    return arr;

}
static void zse_free2dchar(z__char_t **mem, int size)
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
        .data = zse_malloc_2D_array_char(x, y),
        .x = x,
        .y = y,
        .linesUsed = 0
    };
}
void z__StringLines_delete(StringLines_t *strLines)
{
    zse_free2dchar(strLines->data, strLines->y);
    strLines->x = 0;
    strLines->y = 0;
}

StringLines_t z__StringLines_MakeCopy(StringLines_t strLines)
{
    StringLines_t tmp = z__StringLines_createEmpty(strLines.x, strLines.y);
    for (int i = 0; i < tmp.y; ++i)
    {
        memcpy(tmp.data[i], strLines.data[i], tmp.x);
    }
    return tmp;
}

void z__StringLines_Resize_Y (StringLines_t *ln , unsigned int newsize)
{
    if (ln->y > newsize)
    {
        for (int i = newsize; i < ln->y; ++i)
        {
            free(ln->data[i]);
        }
        ln->data = realloc(ln->data, sizeof(z__char_t*)*newsize);
        
    }
    else if (ln->y < newsize)
    {
        ln->data = realloc(ln->data, newsize);
        for (int i = ln->y; i < newsize; ++i)
        {
            ln->data[i] = malloc(sizeof(z__char_t) * ln->x);
        }
    }

    ln->y = newsize;
}
void z__StringLines_Resize_X (StringLines_t *ln, unsigned int newsize)
{
    for (int i = 0; i < ln->y; ++i)
    {
        ln->data[i] = realloc(ln->data[i], sizeof(z__char_t) * newsize);
    }

    ln->x = newsize;   
}

StringLines_t z__String_spiltChar (String_t buffer, const char *restrict breaker)
{
    String_t tmp = z__String_MakeCopy(buffer);
    char *lastbuff = tmp.data;
    char *token = strtok_r(lastbuff, breaker, &lastbuff);

    int ycount = 0;
    while(token != NULL)
    {
        ycount += 1;
        token = strtok_r(lastbuff, breaker, &lastbuff);
    }

    lastbuff = tmp.data;

    StringLines_t returnVal = z__StringLines_createEmpty(128, ycount);

    for (int i = 0; i < returnVal.y && token != NULL; ++i)
    {
        strcpy(returnVal.data[i], token);
        token = strtok_r(lastbuff, breaker, &lastbuff);
    }

    z__String_delete(&tmp);

    return returnVal;

}


StringLineArr_t z__StringLinesArr_createEmpty(int size, int x, int y)
{
    StringLineArr_t lns = {
        .Sldata = malloc(sizeof(StringLines_t) * size),
        .size = size,
        .used = 0
    };

    for (int i = 0; i < lns.size; ++i)
    {
        lns.Sldata[i] = z__StringLines_createEmpty(x, y);
    }

    return lns;
}

void z__StringLinesArr_delete(StringLineArr_t *lns)
{
    for (int i = 0; i < lns->size; ++i)
    {
        z__StringLines_delete(&lns->Sldata[i]);
    }
    lns->size = 0;
}

void z__StringLinesArr_resize(StringLineArr_t *lns, int newsize)
{
    if (newsize < lns->size)
    {
        for (int i = newsize; i < lns->size; ++i)
        {
            z__StringLines_delete(&lns->Sldata[i]);
        }
        lns->Sldata = realloc(lns->Sldata, sizeof(StringLines_t) * newsize);
        lns->size = newsize;
    }
    else if (newsize > lns->size)
    {
        lns->Sldata = realloc(lns->Sldata, sizeof(StringLines_t) * newsize);
        lns->size = newsize;
        for (int i = lns->size; i < newsize; ++i)
        {
            lns->Sldata[i] = z__StringLines_createEmpty(lns->Sldata[0].x, lns->Sldata[0].y);
        }
    }
}

// String END
