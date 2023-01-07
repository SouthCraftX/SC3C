#ifndef SC3CHF_PIXSWP
#define SC3CHF_PIXSWP

//For MSVC
#ifdef _MSC_VER
#pragma warning(disable : 4996)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif //#ifndef _CRT_SECURE_NO_WARNINGS
#endif //#ifdef _MSC_VER

#include <stdlib.h>
#include <time.h>

#include "definations.h"
extern png_data_t png;

#define ULONG32_SWAP(x,y,tmp)             \
(                                       \
    tmp = x,                            \
    x = y,                              \
    y = tmp                             \
)                           


void ramdom_color_order(){

    ulong32_t** rgba_row = (ulong32_t**)png.row_ptr;
    srand(time(0));
    ulong32_t tmp;

    for(ulong32_t n ; n < MAX_RAMDOM_NUM ; ++n ){
        ulong32_t dst_x = rand() %  png.width  ,  //必须这么写，因为多次malloc导致内存不连续
                  dst_y = rand() %  png.height ,
                  src_x = rand() %  png.width  ,
                  src_y = rand() %  png.height ;
        ULONG32_SWAP( rgba_row[dst_y][dst_x] , rgba_row[src_y][src_x] , tmp );    
    }

}



#endif //#ifndef SC3CHF_PIXSWP