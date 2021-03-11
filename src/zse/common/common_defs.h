#ifndef Z_COMMON_DEFINATAION_H
#define Z_COMMON_DEFINATAION_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t  zse_u8;
typedef uint16_t zse_u16;
typedef uint32_t zse_u32;
typedef uint64_t zse_u64;

typedef int8_t  zse_i8;
typedef int16_t zse_i16;
typedef int32_t zse_i32;
typedef int64_t zse_i64;

typedef int zse_int;

typedef float zse_float32;
typedef double zse_float64;

typedef struct _ZSE_Vint2
{
	zse_int x, y;
}zse_Vint2;

typedef struct _ZSE_Vint3
{
	zse_int x, y, z;
}zse_Vint3;

typedef struct _ZSE_Vint4
{
	zse_int x, y, z, w;
}zse_Vint4;


typedef struct _ZSE_Vector2
{
	zse_float32 x, y;
}zse_Vector2;

typedef struct _ZSE_Vector3
{
	zse_float32 x, y, z;
}zse_Vector3;

typedef struct _ZSE_Vector4
{
	zse_float32 x, y, z, w;
}zse_Vector4;

#define zse_xyz3Dto1D(x, y, z, X, Y) x + ((y)*X) + ((z)*X*Y)

typedef struct _Standart_brush_t
{

	zse_Vint3 pos;
	int ink;
	unsigned char size;
	bool toggle;

}BRUSH_t;

#define frinl __attribute__((always_inline)) inline

#endif
