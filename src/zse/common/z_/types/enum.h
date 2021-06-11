#ifndef ZAKAROUF__ZTYPES_TYPES__ENUM_H
#define ZAKAROUF__ZTYPES_TYPES__ENUM_H

#include "tuple.h"
#include "../prep/map.h"

/* More Powerful Enum Type Using Tuples
 * Usage:
 * z__Enum(
    WebEvent,
        // An unit-like
        (PageLoad),
        (PageUnload),

        // Like Tuple Struct
        (KeyPressed, char),
        (Paste, char *, int),

        // Or Records (Structures)
        (Click, (int, x, y))
    );
 * Pitfall: Dont have the last member have a comma
 * Example
 * The below Code is Valid
 * z__Enum(
        Result,
            (Ok),
            (Err, char *) // <== No Comma
        );
    
  Whilst This Code below is not.
 * z__Enum(
        Result,
            (Ok),
            (Err, char *), // <== Comma, Will result in Error
        );


 */
#define z__Enum(Name, ...)\
    z__EnumType(Name, __VA_ARGS__);\
    /* Assign Funtions */\
    z__Enum__PRIV__Apply_Functions(Name, __VA_ARGS__)


/* Without the Function Generation, Rest are same */
#define z__EnumType(Name, ...)\
    typedef z__Enum__PRIV__mapTupleArg_to_C_Enum(Name ,__VA_ARGS__) Name##Tags;  \
    typedef struct Name Name;                               \
    struct Name {                                           \
        union {                                             \
           z__Enum__PRIV__Apply__memberMap_map(__VA_ARGS__) \
        } data;                                             \
        Name##Tags tag;                                     \
    }

#define z__Enum_mtag(M) zpp__CAT(ENUM_TAG__, M)

#define z__Enum__PRIV__chip_Apply_if_0(...) z__Tuple_assign(zpp__PRIV__Args_get_1(__VA_ARGS__) ,zpp__Args_skip_1(__VA_ARGS__))
#define z__Enum__PRIV__chip_Apply_if_1(...) z__Record_assign(zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__Args_skip_1(__VA_ARGS__))

#define z__Enum__PRIV__chip_Apply_if(...) zpp__CAT(z__Enum__PRIV__chip_Apply_if_, zpp__IS_PAREN(zpp__PRIV__Args_get_2(__VA_ARGS__)))(__VA_ARGS__)

#define z__Enum__PRIV__chip__if_0(...) z__Enum__PRIV__chip_Apply_if(__VA_ARGS__) 
#define z__Enum__PRIV__chip__if_1(...)
#define z__Enum__PRIV__chip__if(...)\
    zpp__CAT(z__Enum__PRIV__chip__if_, zpp__Args_IS_EMPTY(zpp__Args_skip_1(__VA_ARGS__)))(__VA_ARGS__)

#define z__Enum_chip(En, sl, ...)                           \
    {                                                       \
        (En)->tag = zpp__CAT(ENUM_TAG__, sl);               \
        z__Enum__PRIV__chip__if(&(En)->data.sl, __VA_ARGS__); \
    }

#define z__Enum_grave(En, sl, ...)\
    zpp__From(                                                  \
        z__typeof(En) z__Enum_grave__var__tmp;                  \
        z__Enum_chip(&z__Enum_grave__var__tmp, sl, __VA_ARGS__);\
        z__Enum_grave__var__tmp;                                \
    )

#define z__Enum_match(en)                                       \
        for(int keep = 1; keep; keep = 0)                       \
        for(z__typeof(en) *z__tmp__enum = &en; keep; keep ^= 1) \
            switch((z__tmp__enum)->tag)                         \


#define z__Enum__PRIV__slot__Apply_if_0(M, ...) break; case zpp__CAT(ENUM_TAG__, M): { z__Tuple_toReference((z__tmp__enum)->data.M, __VA_ARGS__);

#define z__Enum__PRIV__slot__Apply_if_1(M, ...) break; case zpp__CAT(ENUM_TAG__, M): { z__Record_toReffrence(&(z__tmp__enum)->data.M, __VA_ARGS__);

#define z__Enum__PRIV__slot__Apply_if(M, ...)\
        zpp__CAT(z__Enum__PRIV__slot__Apply_if_, zpp__IS_PAREN(zpp__PRIV__Args_get_1(__VA_ARGS__)))(M, __VA_ARGS__)

#define z__Enum__PRIV__slot__if_0(M, ...)\
   z__Enum__PRIV__slot__Apply_if(M, __VA_ARGS__)

#define z__Enum__PRIV__slot__if_1(M, ...)\
    break; default: {

#define z__Enum__PRIV__slot__if(...)\
    zpp__CAT(z__Enum__PRIV__slot__if_, zpp__Args_IS_EMPTY(__VA_ARGS__))(__VA_ARGS__)

// FIXME: z__Enum_slot(en, (), x, y) <= Gets Evaluated as Record instead of tuple. Due
//      The first Argument being Parenthesis, Add a second evalution after IS_PAREN, to check if
//      its emply too. If yes, It's a tuple, Else its a record.
#define z__Enum_slot(...) z__Enum__PRIV__slot__if(__VA_ARGS__)

#define z__Enum_emptyslot break; default:
#define z__Enum_unslot }

#define z__Enum_ifSlot(En, M, ...)\
        if(z__Enum_mtag(M) == (En).tag )\
            for(int keep = 1; keep; keep = 0)\
                for(({ z__Enum__PRIV__slot__if(__VA_ARGS__) });keep; keep ^= 1)\
        

#define z__Enum_matches(En, M) (z__Enum_mtag(M) == (En).tag)

#ifdef Z___TYPE_CONFIG__USE_ENUM_ALIAS_MATCH_STATEMENT

    #define match(En) z__Enum_match(En)
    #define slot(...) z__Enum_slot(__VA_ARGS__)
    #define unslot z__Enum_unslot

    #define emptyslot z__Enum_emptyslot
    #define ifSlot(En, Tup, ...) z__Enum_ifSlot(En, Tup, __VA_ARGS__)



#endif


/* Enum Generation */

#define z__Enum__PRIV__Args_get_1() zpp__PRIV__Args_get_1
#define z__Enum__PRIV__Args_skip_1() zpp__Args_skip_1
#define z__Enum__PRIV__Args_HAS_COMMA() zpp__Args_HAS_COMMA

#define z__Enum__PRIV__Arg_ToTuple_1(x)\
    z__TupleX(z__Enum__PRIV__Args_skip_1()x) z__Enum__PRIV__Args_get_1()x;
#define z__Enum__PRIV__Arg_ToTuple_0(x) char x;

#define z__Enum__PRIV__Arg_ToTuple(x)\
    zpp__CAT(z__Enum__PRIV__Arg_ToTuple_, z__Enum__PRIV__Args_HAS_COMMA()x)(x)\

#define z__Enum__PRIV__TupleArgmap(...) zpp__Args_map(z__Enum__PRIV__Arg_ToTuple, __VA_ARGS__)


#define z__Enum__PRIV__Arg_ToRecord_1__expand(...)\
    z__Record__PRIV__forEnum(__VA_ARGS__)

#define z__Enum__PRIV__Arg_ToRecord_1(x)\
    z__Enum__PRIV__Arg_ToRecord_1__expand(zpp__EXPAND x)

#define z__Enum__PRIV__Arg_ToRecord_0(x) char x;

#define z__Enum__PRIV__Arg_ToRecord(x)\
    zpp__CAT(z__Enum__PRIV__Arg_ToRecord_, z__Enum__PRIV__Args_HAS_COMMA()x)(x)\



#define z__Enum__PRIV__memberMap_of_if(x) zpp__CAT(z__Enum__PRIV__memberMap_of_if_ ,zpp__IS_PAREN(zpp__PRIV__Args_get_2 x))(x)

#define z__Enum__PRIV__memberMap_of_if_0(x) z__Enum__PRIV__Arg_ToTuple(x);
#define z__Enum__PRIV__memberMap_of_if_1(x) z__Enum__PRIV__Arg_ToRecord(x)


#define z__Enum__PRIV__Apply__memberMap_of_if(x) zpp__CAT(z__Enum__PRIV__Apply__memberMap_of_if_, zpp__Args_HAS_COMMA x)(x)

#define z__Enum__PRIV__Apply__memberMap_of_if_0(x) char x;
#define z__Enum__PRIV__Apply__memberMap_of_if_1(x) z__Enum__PRIV__memberMap_of_if(x)

#define z__Enum__PRIV__Apply__memberMap_map(...) zpp__Args_map(z__Enum__PRIV__Apply__memberMap_of_if, __VA_ARGS__)


#define z__Enum__PRIV__FirstArgof_Param(x)\
    z__Enum__PRIV__Args_get_1()x

#define z__Enum__PRIV__mapTupleArg_to_C_Enum(...)\
    enum{ zpp__Args_maplist_fn_Pattern(z__Enum__PRIV__FirstArgof_Param, ENUM_TAG__, , zpp__Args_skip_1(__VA_ARGS__))}
    //zpp__Args_maplist(z__Enum__PRIV__FirstArgof_Param, ) }




/* Apply Function for each type of enum */

#define z__Enum__PRIV__GEN__fn__Record__createArgList(x) zpp__Args_skip_1 x
#define z__Enum__PRIV__GEN__fn__Record__createArgList_map(...) zpp__Args_maplist(z__Enum__PRIV__GEN__fn__Record__createArgList, __VA_ARGS__)

#define z__Enum__PRIV__GEN__fn__Record(x)\
    Z__INLINE __attribute__((const)) zpp__PRIV__Args_get_1 x (z__Enum__PRIV__GEN__fn__Record__createArgList_map(zpp__Args_skip_1 x))\
    z__Record__PRIV__forEnum_createMembers(zpp__Args_skip_1 x)  \
    {                                                           \
        z__typeof(zpp__PRIV__Args_get_1 x (                     \
                    z__Enum__PRIV__GEN__fn__Record__createArgList_map(zpp__Args_skip_1 x)) ) result;\
                                                                                                    \
        z__Enum_chip(&result, zpp__PRIV__Args_get_1 x,                                              \
                zpp__Args_toDuplicateParenList(                                                     \
                    z__Enum__PRIV__GEN__fn__Record__createArgList_map(zpp__Args_skip_1 x) ));       \
        return result;                                                                              \
    }

#define z__Enum__PRIV__GEN__fn__Tuple(x)\
    Z__INLINE __attribute__((const)) zpp__PRIV__Args_get_1 x (z__Tuple___createMemberList(zpp__Args_skip_1 x))\
    {                                                           \
        z__typeof( zpp__PRIV__Args_get_1 x (                    \
                    zpp__Args_getupto(                          \
                        zpp__PRIV__DEC(zpp__Args_Count x),      \
                        zpp__num_underscore158_asc()) )) result;\
                                                                \
        z__Enum_chip(&result, zpp__PRIV__Args_get_1 x,          \
                zpp__Args_getupto(                              \
                    zpp__PRIV__DEC(zpp__Args_Count x),          \
                    zpp__num_underscore158_asc()));             \
        return result;                                          \
    }

#define z__Enum__PRIV__GEN__fn__Unit(x)\
    Z__INLINE __attribute__((const)) zpp__PRIV__Args_get_1 x () \
    {                                                           \
        z__typeof(zpp__PRIV__Args_get_1 x () ) result;          \
        z__Enum_chip(&result, zpp__PRIV__Args_get_1 x);         \
        return result;                                          \
    }

#define z__Enum__PRIV__GEN__fn__either_record_or_tuple_if_0(x) z__Enum__PRIV__GEN__fn__Tuple(x)
#define z__Enum__PRIV__GEN__fn__either_record_or_tuple_if_1(x) z__Enum__PRIV__GEN__fn__Record(x)

#define z__Enum__PRIV__GEN__fn__either_record_or_tuple_if(x)\
    zpp__CAT(z__Enum__PRIV__GEN__fn__either_record_or_tuple_if_, zpp__IS_PAREN(zpp__PRIV__Args_get_2 x))(x)


#define z__Enum__PRIV__Apply_Functions_check_if_0(x) z__Enum__PRIV__GEN__fn__Unit(x)
#define z__Enum__PRIV__Apply_Functions_check_if_1(x) z__Enum__PRIV__GEN__fn__either_record_or_tuple_if(x)

#define z__Enum__PRIV__Apply_Functions_check_if(x)\
    zpp__CAT(z__Enum__PRIV__Apply_Functions_check_if_, zpp__Args_HAS_COMMA x)(x)
 
#define z__Enum__PRIV__Apply_Functions(EnumType, ...)\
    zpp__PRIV__Args_map__fn_Pattern(z__Enum__PRIV__Apply_Functions_check_if, EnumType, , __VA_ARGS__);



#endif
