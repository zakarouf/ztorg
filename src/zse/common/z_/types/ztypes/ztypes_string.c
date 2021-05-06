#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "mem.h"
#include "string.h"


#ifdef Z___TYPE_CONFIG__USE_STRING

    z__String z__String_new(int size)
    {
        return (z__String){

            .data = calloc(sizeof(z__char) , size),
            .size = size,
            .used = 0
        };
    }

    inline void z__String_delete(z__String * s)
    {
        free(s->data);
        s->size = 0;
        s->used = 0;
    }

    inline void z__String_resize(z__String *str, int newsize)
    {
        str->size = newsize;
        str->data = z__mem_safe_realloc(str->data, newsize);
    }

    void z__String_Copy(z__String *dest, const z__String val)
    {
        if (dest->size < val.size )
        {
            z__String_resize(dest, val.size);
        }
        memcpy(dest->data, val.data, val.size);
    }

    z__String z__String_MakeCopy(const z__String str)
    {

        z__String str2 = {
            .data = calloc(sizeof(z__char) , str.size),
            .size = str.size,
            .used = str.used
        };

        memcpy(str2.data, str.data, str.size);

        return str2;
    }

    inline void z__Strint_append(z__String *str, const z__char *src, int length)
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

    inline void z__String_write(z__String *s, const z__char *st, int len)
    {
        if (len == -1) {
            len = strlen(st);
        }
        if (len > s->size) {
            z__String_resize(s, len+1);
        }

        memcpy(s->data, st, s->size);
        s->used = len;
    }

    inline void z__String_join(z__String *dest, z__String *src, unsigned int extraSpace)
    {
        dest->size = dest->size + src->used + extraSpace;
        dest->data = reallocf(dest->data, dest->size);

        memcpy(&dest[dest->used], src->data, src->used);
    }

    void z__String_pushChar(z__String *dest, z__char ch)
    {
        if(dest->size <= dest->used) {
            z__String_resize(dest, dest->size + 8);
        }

        dest->data[dest->used] = ch;
        dest->used += 1;
    }

    void z__String_insertChar(z__String *dest, z__char ch, z__i32 pos)
    {
        if(pos >= dest->used && pos < 0) {
            return;
        }
        
        if (dest->size <= dest->used) {
            z__String_resize(dest, dest->size +8);
        }

        z__char
            tmpchar = dest->data[pos],
            *buff = &dest->data[dest->used];
        dest->data[pos] = ch;
        dest->data[dest->used + 1] = 0;

        int splen = dest->used - pos;

        for (int i = 0; i < splen; i++) {
            *buff = *(buff-1);
            buff--;
        }
        dest->data[pos +1] = tmpchar;

        dest->used += 1;
    }

    void z__String_delChar(z__String *dest, z__i32 pos)
    {
        if(pos >= dest->used && pos < 0) {
            return;
        }

        int splen = dest->used - pos;
        z__char *buff = &dest->data[pos];

        for (int i = 0; i < splen; ++i)
        {
            *buff = *(buff+1);
            buff++;
        }
        dest->used -= 1;
    }

    void z__String_replaceChar(z__String *dest, z__char ch, z__i32 pos)
    {
        if(pos >= dest->used && pos < 0) {
            return;
        }
        dest->data[pos] = ch;
    }

    
    z__String z__String_newFromFile(char filename[])
    {
        FILE *f;

        if ((f = fopen(filename, "rb")) == NULL)
        {
            return (z__String) {
                NULL, 0, 0
            };
        }

        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

        z__char *string = malloc(fsize + 1);
        fread(string, 1, fsize, f);
        fclose(f);

        string[fsize] = 0;
        return (z__String){
             .data = string
            ,.size = fsize +1
            ,.used = fsize +1
        };
    }
       

    z__StringLines z__StringLines_new(unsigned int base_lines_count)
    {
        z__StringLines ln = {
            .data = calloc(base_lines_count, sizeof(*ln.data)),
            .lines = base_lines_count,
            .linesUsed = 0
        };
        ln.sizeofString = calloc(base_lines_count, sizeof(*ln.sizeofString));

        return ln;
    }

    void z__StringLines_delete(z__StringLines *ln)
    {
        for (int i = 0; i < ln->linesUsed; ++i)
        {
            free(ln->data[i]);
        }
        free(ln->data);
        free(ln->sizeofString);

        ln->lines = 0;
        ln->linesUsed = 0;
    }

    void z__StringLines_pushString(z__StringLines *ln ,z__String str)
    {
        if(ln->linesUsed >= ln->lines) {
            ln->lines += Z___TYPE_STRINGLINES_REALLOC_RESIZE_BY_DEFAULT;
            ln->data = z__mem_safe_realloc(ln->data, sizeof(*ln->data) *ln->lines);
        }

        ln->data[ln->linesUsed] = calloc(str.used+1, sizeof(**ln->data));
        memcpy(ln->data[ln->linesUsed], str.data, str.used * sizeof(*str.data));
        ln->sizeofString[ln->linesUsed] = str.used;
        ln->linesUsed += 1;
    }

    void z__StringLines_push(z__StringLines *ln , char const * st, int len)
    {
        if(ln->linesUsed >= ln->lines) {
            ln->lines += Z___TYPE_STRINGLINES_REALLOC_RESIZE_BY_DEFAULT;
            ln->data = z__mem_safe_realloc(ln->data, sizeof(*ln->data) *ln->lines);
            ln->sizeofString = z__mem_safe_realloc(ln->sizeofString, sizeof(*ln->sizeofString) *ln->lines);
        }

        if (len == -1) {
            len = strlen(st);
        }

        ln->data[ln->linesUsed] = calloc(len, sizeof(**ln->data));
        memcpy(ln->data[ln->linesUsed], st, len * sizeof(*st));
        ln->sizeofString[ln->linesUsed] = len;
        ln->linesUsed += 1;
    }

    void z__StringLines_pop(z__StringLines *ln)
    {
        free(ln->data[ln->linesUsed-1]);
        ln->linesUsed -= 1;
        /*
        if (ln->lines - ln->linesUsed >= Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)
        {
            ln->lines -= Z___TYPE_STRINGLINES_REALLOC_RESIZE_BY_DEFAULT;
            ln->data = z__mem_safe_realloc(ln->data, sizeof(*ln->data) *ln->lines);
            ln->sizeofString = z__mem_safe_realloc(ln->sizeofString, sizeof(*ln->sizeofString) *ln->lines);
        }
        */
    }

    z__StringLines z__StringLines_newFrom(z__StringLines const *ln)
    {
        z__StringLines newln = {
            .lines = ln->lines,
            .linesUsed = ln->linesUsed
        };

        newln.sizeofString = malloc(sizeof(*newln.sizeofString) * newln.lines);
        memcpy(newln.sizeofString, ln->sizeofString, sizeof(*newln.sizeofString)*newln.lines);

        newln.data = malloc(sizeof(*newln.data) * newln.lines);

        for (int i = 0; i < newln.linesUsed; ++i) {
            newln.data[i] = malloc(sizeof(**newln.data) * newln.sizeofString[i]);
            memcpy(newln.data[i], ln->data[i], newln.sizeofString[i]);
        }

        return newln;
    }

    z__StringLines z__String_splitTok(z__String str, char const *restrict seperator)
    {
        z__String tmp = z__String_MakeCopy(str);
        char *lastbuff = tmp.data;
        char *token = strtok_r(lastbuff, seperator, &lastbuff);

        /*Count*/
        int linesCount = 0;
        while(token) {

            linesCount += 1;
            token = strtok_r(lastbuff, seperator, &lastbuff);
        }

        z__String_delete(&tmp);
        tmp = z__String_MakeCopy(str);

        lastbuff = tmp.data;
        token = strtok_r(lastbuff, seperator, &lastbuff);

        z__StringLines ln = z__StringLines_new(linesCount);

        while(token) {
            z__StringLines_push(&ln, token, -1);
            token = strtok_r(lastbuff, seperator, &lastbuff);
        }

        return ln;
    }

    z__StringLines z__String_splitTok_raw(char const *restrict stri, int len, char const *restrict seperator)
    {
        if (len == -1)
        {
            len = strlen(stri);
        }
        
        char *tmp_stri = malloc(len * sizeof(*tmp_stri));
        memcpy(tmp_stri, stri, len);

        char *lastbuff = tmp_stri;
        char *token = strtok_r(lastbuff, seperator, &lastbuff);

        /*Count*/
        int linesCount = 0;
        while(token) {

            linesCount += 1;
            token = strtok_r(lastbuff, seperator, &lastbuff);
        }

        free(tmp_stri);
        tmp_stri = malloc(len * sizeof(*tmp_stri));
        memcpy(tmp_stri, stri, len);

        lastbuff = tmp_stri;

        token = strtok_r(lastbuff, seperator, &lastbuff);

        z__StringLines ln = z__StringLines_new(linesCount);

        while(token) {
            z__StringLines_push(&ln, token, -1);
            token = strtok_r(lastbuff, seperator, &lastbuff);
        }

        return ln;
    }

    z__StringLines z__String_split_raw(char const *mainStr, int mainStrLen, char const *str, int str_len)
    {
        if (str_len == -1)
        {
            str_len = strlen(str);
        }
        if (mainStrLen == -1)
        {
            mainStrLen = strlen(mainStr);
        }

        char *tmp_mainStr = malloc(sizeof(*tmp_mainStr) * mainStrLen);
        memcpy(tmp_mainStr, mainStr, mainStrLen);

        char *strst = strnstr(tmp_mainStr, str, mainStrLen);

        while(strst) {
            memset(strst, 0, str_len);
            strst += str_len;
            strst = strstr(strst, str);
        }

        strst = tmp_mainStr;
        z__StringLines ln = z__StringLines_new(8);

        int i = 0, len = 0;
        if (*strst)
        {
            i = strlen(strst);
            z__StringLines_push(&ln, strst, i);
            strst += i + str_len;
        }

        while(i <= mainStrLen) {

            len = strnlen(strst, mainStrLen-i);
            z__StringLines_push(&ln, strst, len);

            i += len+str_len;
            strst += len + str_len;
        }

        return ln;
    }

    z__StringLinesArr z__StringLinesArr_new(int size, int x, int y)
    {
        z__StringLinesArr lns = {
            .Sldata = calloc(sizeof(z__StringLines), size),
            .size = size,
            .used = 0
        };

        for (int i = 0; i < lns.size; ++i)
        {
            lns.Sldata[i] = z__StringLines_new(x);
        }

        return lns;
    }

    void z__StringLinesArr_delete(z__StringLinesArr *lns)
    {
        for (int i = 0; i < lns->size; ++i)
        {
            z__StringLines_delete(&lns->Sldata[i]);
        }
        free(lns->Sldata);
        lns->Sldata = NULL;
        lns->size = 0;
    }

    void z__StringLinesArr_resize(z__StringLinesArr *lns, int newsize)
    {
        if (newsize < lns->size)
        {
            for (int i = newsize; i < lns->size; ++i)
            {
                z__StringLines_delete(&lns->Sldata[i]);
            }
            lns->Sldata = z__mem_safe_realloc(lns->Sldata, sizeof(z__StringLines) * newsize);
            lns->size = newsize;
        }
        else if (newsize > lns->size)
        {
            lns->Sldata = z__mem_safe_realloc(lns->Sldata, sizeof(z__StringLines) * newsize);
            lns->size = newsize;
            for (int i = lns->size; i < newsize; ++i)
            {
                lns->Sldata[i] = z__StringLines_new(lns->Sldata[0].lines);
            }
        }
    }

    // String END

#endif //Z___TYPE_CONFIG__USE_STRING
