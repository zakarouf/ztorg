#include "common_string.h"


#include <stdlib.h>
#include <string.h>


// Malloc And Free 2d Char, Orginally were Part of Ztorg (https://github.com/zakarouf/ztorg)
// Now Moved to Common String
static z__char_t **zse_calloc_2D_array_char (unsigned int x, unsigned int y) {

    z__char_t **arr = calloc(sizeof(z__char_t*), y);
    for (int i = 0; i < y; ++i)
    {
        arr[i] = calloc(sizeof(z__char_t), x);
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


static void *safe_realloc(void * data, size_t size)
{
    void *tmpdata = realloc(data, size);
    if (tmpdata != NULL)
    {
        if (tmpdata != data)
        {
            return tmpdata;
        }
    }
    return data;
}

// Strings

String_t z__String_create(int size)
{
    return (String_t){

        .data = calloc(sizeof(z__char_t) , size),
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
    str->data = safe_realloc(str->data, newsize);
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
        .data = calloc(sizeof(z__char_t) , str.size),
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

StringLines_t z__StringLines_createEmpty(int x, int y)
{
    return (StringLines_t){
        .data = zse_calloc_2D_array_char(x, y),
        .sizeofString = x,
        .length = y,
        .linesUsed = 0
    };
}
void z__StringLines_delete(StringLines_t *strLines)
{
    zse_free2dchar(strLines->data, strLines->length);
    strLines->sizeofString = 0;
    strLines->length = 0;
}

StringLines_t z__StringLines_MakeCopy(StringLines_t strLines)
{
    StringLines_t tmp = z__StringLines_createEmpty(strLines.sizeofString, strLines.length);
    for (int i = 0; i < tmp.length; ++i)
    {
        memcpy(tmp.data[i], strLines.data[i], tmp.sizeofString);
    }
    return tmp;
}

void z__StringLines_Resize_Y (StringLines_t *ln , unsigned int newsize)
{
    if (ln->length > newsize)
    {
        for (int i = newsize; i < ln->length; ++i)
        {
            free(ln->data[i]);
        }
        ln->data = safe_realloc(ln->data, sizeof(z__char_t*)*newsize);
        
    }
    else if (ln->length < newsize)
    {
        ln->data = safe_realloc(ln->data, newsize);
        for (int i = ln->length; i < newsize; ++i)
        {
            ln->data[i] = calloc(sizeof(z__char_t), ln->sizeofString);
        }
    }

    ln->length = newsize;
}
void z__StringLines_Resize_X (StringLines_t *ln, unsigned int newsize)
{
    for (int i = 0; i < ln->length; ++i)
    {
        ln->data[i] = reallocf(ln->data[i], sizeof(z__char_t) * newsize);
    }

    ln->sizeofString = newsize;   
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

    for (int i = 0; i < returnVal.length && token != NULL; ++i)
    {
        strcpy(returnVal.data[i], token);
        token = strtok_r(lastbuff, breaker, &lastbuff);
    }

    z__String_delete(&tmp);

    return returnVal;

}

void z__StringLines_pushString(StringLines_t *strLines, int len, const z__char_t *string)
{
    if (strLines->length <= strLines->linesUsed )
    {
        z__StringLines_Resize_Y(strLines, strLines->linesUsed+8);
    }
    int linesUsed = strLines->linesUsed;

    if (len >= strLines->sizeofString)
    {
        z__StringLines_Resize_X(strLines, len+8);
    }    
    memcpy(strLines->data[linesUsed], string, len);
    strLines->linesUsed++;
}

StringLinesArr_t z__StringLinesArr_createEmpty(int size, int x, int y)
{
    StringLinesArr_t lns = {
        .Sldata = calloc(sizeof(StringLines_t), size),
        .size = size,
        .used = 0
    };

    for (int i = 0; i < lns.size; ++i)
    {
        lns.Sldata[i] = z__StringLines_createEmpty(x, y);
    }

    return lns;
}

void z__StringLinesArr_delete(StringLinesArr_t *lns)
{
    for (int i = 0; i < lns->size; ++i)
    {
        z__StringLines_delete(&lns->Sldata[i]);
    }
    lns->size = 0;
}

void z__StringLinesArr_resize(StringLinesArr_t *lns, int newsize)
{
    if (newsize < lns->size)
    {
        for (int i = newsize; i < lns->size; ++i)
        {
            z__StringLines_delete(&lns->Sldata[i]);
        }
        lns->Sldata = safe_realloc(lns->Sldata, sizeof(StringLines_t) * newsize);
        lns->size = newsize;
    }
    else if (newsize > lns->size)
    {
        lns->Sldata = safe_realloc(lns->Sldata, sizeof(StringLines_t) * newsize);
        lns->size = newsize;
        for (int i = lns->size; i < newsize; ++i)
        {
            lns->Sldata[i] = z__StringLines_createEmpty(lns->Sldata[0].sizeofString, lns->Sldata[0].length);
        }
    }
}

// String END
