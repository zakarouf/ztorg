#ifndef ZAKAROUF__ZTYPES_H
#define ZAKAROUF__ZTYPES_H

#include "../config_types.h"
#include "base.h"
#include "typeof.h"
#include "mem.h"


/* CGLM */
#ifdef Z___TYPE_INCLUED_CGLM
    #include "cglm.h"
#endif

/* Vectors And Matrices For Graphical Maths */
#ifdef Z___TYPE_CONFIG__USE_GMATHTYPE
    #include "gmath.h"
#endif //#ifdef Z___TYPE_CONFIG__USE_GMATHTYPE

#ifdef Z___TYPE_CONFIG__USE_ARR_ARRAYTYPE
	#include "arr.h"
#endif

/* Irregular Type */
#ifdef Z___TYPE_CONFIG__USE_IRREGULAR_ARRAYTYPE
    #include "irrg.h"
#endif

/* Array Type */
#ifdef Z___TYPE_CONFIG__USE_DYNT_ARRAYTYPE
    #include "dynt.h"
#endif

/* Linked Lists */
#ifdef Z___TYPE_CONFIG__USE_TYPE_LINKEDLIST
    #include "llist.h"
#endif

#ifdef Z___TYPE_CONFIG__USE_STRING
	#include "string.h"
#endif

#ifdef Z___TYPE_CONFIG__USE_EXTENDED_FEATURES
    #include "base_ext.h"
#endif

#endif