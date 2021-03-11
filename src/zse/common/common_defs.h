#ifndef Z_COMMON_DEFINATAION_H
#define Z_COMMON_DEFINATAION_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t  z__u8;
typedef uint16_t z__u16;
typedef uint32_t z__u32;
typedef uint64_t z__u64;

typedef int8_t  z__i8;
typedef int16_t z__i16;
typedef int32_t z__i32;
typedef int64_t z__i64;

typedef int z__int;

typedef float z__float32;
typedef double z__float64;

typedef struct _ZSE_Vint2
{
	z__int x, y;
}z__Vint2;

typedef struct _ZSE_Vint3
{
	z__int x, y, z;
}z__Vint3;

typedef struct _ZSE_Vint4
{
	z__int x, y, z, w;
}z__Vint4;


typedef struct _ZSE_Vector2
{
	z__float32 x, y;
}z__Vector2;

typedef struct _ZSE_Vector3
{
	z__float32 x, y, z;
}z__Vector3;

typedef struct _ZSE_Vector4
{
	z__float32 x, y, z, w;
}z__Vector4;


#define frinl __attribute__((always_inline)) inline

#endif
