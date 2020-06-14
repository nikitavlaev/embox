/**
 * @file
 *
 * @date 14.10.09
 * @author Nikolay Korotky
 */

#include <ctype.h>
#include <defines/null.h>

/**< ASCII table */
const unsigned char _ctype[] = {
_CTYPE_C,_CTYPE_C,_CTYPE_C,_CTYPE_C,_CTYPE_C,_CTYPE_C,_CTYPE_C,_CTYPE_C,                        /* 0-7 */
_CTYPE_C,_CTYPE_C|_CTYPE_S,_CTYPE_C|_CTYPE_S,_CTYPE_C|_CTYPE_S,_CTYPE_C|_CTYPE_S,_CTYPE_C|_CTYPE_S,_CTYPE_C,_CTYPE_C,         /* 8-15 */
_CTYPE_C,_CTYPE_C,_CTYPE_C,_CTYPE_C,_CTYPE_C,_CTYPE_C,_CTYPE_C,_CTYPE_C,                        /* 16-23 */
_CTYPE_C,_CTYPE_C,_CTYPE_C,_CTYPE_C,_CTYPE_C,_CTYPE_C,_CTYPE_C,_CTYPE_C,                        /* 24-31 */
_CTYPE_S|_CTYPE_SP,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,                    /* 32-39 */
_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,                        /* 40-47 */
_CTYPE_D,_CTYPE_D,_CTYPE_D,_CTYPE_D,_CTYPE_D,_CTYPE_D,_CTYPE_D,_CTYPE_D,                        /* 48-55 */
_CTYPE_D,_CTYPE_D,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,                        /* 56-63 */
_CTYPE_P,_CTYPE_U|_CTYPE_X,_CTYPE_U|_CTYPE_X,_CTYPE_U|_CTYPE_X,_CTYPE_U|_CTYPE_X,_CTYPE_U|_CTYPE_X,_CTYPE_U|_CTYPE_X,_CTYPE_U,      /* 64-71 */
_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,                        /* 72-79 */
_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,                        /* 80-87 */
_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,                        /* 88-95 */
_CTYPE_P,_CTYPE_L|_CTYPE_X,_CTYPE_L|_CTYPE_X,_CTYPE_L|_CTYPE_X,_CTYPE_L|_CTYPE_X,_CTYPE_L|_CTYPE_X,_CTYPE_L|_CTYPE_X,_CTYPE_L,      /* 96-103 */
_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,                        /* 104-111 */
_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,                        /* 112-119 */
_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_C,                        /* 120-127 */
/* Extended ASCII Codes */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,                /* 128-143 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,                /* 144-159 */
_CTYPE_S|_CTYPE_SP,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,   /* 160-175 */
_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,_CTYPE_P,       /* 176-191 */
_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,       /* 192-207 */
_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_P,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_U,_CTYPE_L,       /* 208-223 */
_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,       /* 224-239 */
_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_P,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L,_CTYPE_L};      /* 240-255 */

const unsigned short **__ctype_b_loc(void) {
	return NULL;
}

int32_t **__ctype_tolower_loc(void) {
	return NULL;
}

int32_t **__ctype_toupper_loc(void) {
	return NULL;
}
