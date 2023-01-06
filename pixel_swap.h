#ifndef SC3CHF_PIXSWP
#define SC3CHF_PIXSWP

//For MSVC
#ifdef _MSC_VER
#pragma warning(disable : 4996)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif //#ifndef _CRT_SECURE_NO_WARNINGS
#endif //#ifdef _MSC_VER

#include "definations.h"
extern png_data_t png;

#define 32BIT_UINT_SWAP(x,y) (\
{\
    ulong32_t __u32_int_swp_tmp_ = x;
    x = y;
    y = __u32_int_swp_tmp_;
}\
)

void ramdom_color_order(){

}



#endif //#ifndef SC3CHF_PIXSWP