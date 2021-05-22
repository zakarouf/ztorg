#ifndef ZAKAROUF__ZPREP_BASE_H
#define ZAKAROUF__ZPREP_BASE_H

#define zpp__PRIMITIVE_CAT(a, b)        a##b
#define zpp__PRIMITIVE_CAT3(a, b, c)    a##b##c
#define zpp__PRIMITIVE_CAT4(a, b, c, d) a##b##c##d
#define zpp__PRIMITIVE_CAT5(a, b, c, d, e) a##b##c##d##e

#define zpp__CAT(_1, _2) zpp__PRIMITIVE_CAT(_1, _2)
#define zpp__CAT3(_1,  _2, _3)                                \
  zpp__CAT(zpp__CAT(_1, _2), _3)
#define zpp__CAT4(_1,  _2, _3, _4)                            \
  zpp__CAT(zpp__CAT3(_1, _2, _3), _4)
#define zpp__CAT5(_1,  _2, _3, _4, _5)                        \
  zpp__CAT(zpp__CAT4(_1, _2, _3, _4), _5)
#define zpp__CAT6(_1,  _2, _3, _4, _5, _6)                    \
  zpp__CAT(zpp__CAT5(_1, _2, _3, _4, _5), _6)

#define zpp__PRIV_TO_STRING(...) #__VA_ARGS__

#define zpp__PRIV_COMMA(...) ,
#define zpp__IGNORE(...)
#define zpp__EXPAND(...) __VA_ARGS__
#define zpp__EMPTY
#define zpp__ARG_FLUSH(v) v

#define zpp__if_then(cond, x, y) zpp__CAT(zpp__if_then_, cond)(x, y)
#define zpp__if_then_0(x, y) y
#define zpp__if_then_1(x, y) x

#define zpp__AND(exp) zpp__PRIMITIVE_CAT(zpp__AND_, exp)
#define zpp__AND_0(exp) 0
#define zpp__AND_1(exp) exp

#define zpp__NOT(exp) zpp__CAT(zpp__NOT_, exp)
#define zpp__NOT_0 1 
#define zpp__NOT_1 0

#define zpp__V(...) (0zpp__V, __VA_ARGS__)

#define zpp__From(...) ({ __VA_ARGS__  })

#endif
