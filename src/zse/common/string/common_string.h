#ifndef ZAKAROUF__ZTORG_COMMON_STRING_H
#define ZAKAROUF__ZTORG_COMMON_STRING_H

typedef char z__char_t;

typedef struct ZINT_STRING
{
    z__char_t * data;
    int size;
    int used;

}String_t;

typedef struct
{
    z__char_t **data;
    unsigned int x;
    unsigned int y;
    unsigned linesUsed;
}StringLines_t;

typedef struct
{
    StringLines_t *Sldata;
    int size;
    int used;
}StringLineArr_t;


#define z__fillString_MF(String, val)\
    memset(String.str, (val), String.size)

#define z__StringGetLen_MF(String)\
    (String_t)String.size;    

#define z__StringGetUsed_MF(String)\
    (String_t)String.used;    

int z_findCharInStr(String_t str, z__char_t c, int fromIndex);

String_t z__String_create(int size);
void z__String_delete(String_t * s);
void z__String_resize(String_t *str, int newsize);
void z__String_Copy(String_t *str, const String_t val);
String_t z__String_MakeCopy(const String_t str);
String_t z__String_Link(const String_t str);
void z__Strint_append(String_t *str, const z__char_t* src, int length);
void z__String_join(String_t *dest, String_t *src, unsigned int extraSpace);


StringLines_t z__StringLines_createEmpty(int x, int y);
void z__StringLines_delete(StringLines_t *strLines);
void z__StringLines_Resize_Y (StringLines_t *ln , unsigned int newsize);
void z__StringLines_Resize_X (StringLines_t *ln, unsigned int newsize);
StringLines_t z__StringLines_MakeCopy(StringLines_t strLines);
StringLines_t z__String_spiltChar(String_t buffer, const char * restrict breaker);


StringLineArr_t z__StringLinesArr_createEmpty(int size, int x, int y);
void z__StringLinesArr_delete(StringLineArr_t *lns);
void z__StringLinesArr_resize(StringLineArr_t *lns, int newsize);



#endif

