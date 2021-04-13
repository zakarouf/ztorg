#ifndef ZSE_COMMON_H
#define ZSE_COMMON_H

#include "config.h"
#include "common/common.h"

#if defined(_MSC_VER)
#  ifdef ZSE__STATIC
#    define ZSE__EXPORT
#  elif defined(ZSE__EXPORTS)
#    define ZSE__EXPORT __declspec(dllexport)
#  else
#    define ZSE__EXPORT __declspec(dllimport)
#  endif
#  define ZSE__INLINE __forceinline
#else
#  define ZSE__EXPORT __attribute__((visibility("default")))
#  define ZSE__INLINE static inline __attribute((always_inline))
#  define ZSE__INLINE_NST inline __attribute((always_inline))
#endif


#define zse_xyz3Dto1D(x, y, z, X, Y) ((x) + ((y)*(X)) + ((z)*(X)*(Y)))

typedef struct _Standart_brush_t
{

	z__Vint3 pos;
	int ink;
	unsigned char size;
	bool toggle;

}BRUSH_t;


#endif
