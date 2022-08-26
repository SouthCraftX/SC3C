#ifndef SC3CHF_OTHERS
#define SC3CHF_OTHERS

#include "defines.h"
#include "lang.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

void do_help(){
    puts(help_text);
}

void destroy_pixel_memory( struct PNGData* png ){
    for(int hei = 0 ; hei < png->height ; ++hei ){
        free(png->row_ptr);
    }
    free(png->row_ptr);
}

#define put_err_msg( format , ...) ( \
            fprintf(stderr, format , __VA_ARGS__) \
        )


/*
//Print a error message.
void put_err_msg( ccstring formated_msg  , ...){
    va_list arg;
    fprintf( stderr , formated_msg , arg);
}
*/

void put_info_msg( const bool if_put  ,
                   ccstring formated_msg , ... ){
    va_list arg;
    if(if_put)
        printf( formated_msg , arg );
    return;
}

bool file_exist_warning( ccstring path){
    set_console_color(CSC_LIGHTYELLOW);
    printf("Warning: %s is already exist.Override?(y/n):",path);
    set_console_color(CSC_WHITE);
    char input;
    fflush ( stdin );
    scanf("%c",&input);
    fflush ( stdin );

    switch( input ){
        case 'y':
        case 'Y': return true;
        case 'n':
        case 'N': return false;
        default:
            set_console_color(CSC_LIGHTRED);
            puts("Invalid input.File overwrite cancelled.");
            set_console_color(CSC_WHITE);
            return false;
    }
}

size_t fwriter( void* buffer , size_t nwrite ,size_t ncount ,FILE* stream  ){
#ifdef USE_UNLOCKED_FWRITE
    /* _fwrite_nolock() only works with MSVCCRT */
    return _fwrite_nolock( buffer , nwrite , ncount ,stream );
#else
    return fwrite( buffer , nwrite , ncount ,stream );
#endif
}

/*
    strcmp_ignore_case()
    Compare strings in case-insensitive mode.
    return:
        0   =   same
        !0  =   different
*/
int strcmp_ignore_case( ccstring str_x , ccstring str_y ){
#ifdef _WIN32
    return stricmp( str_x , str_y );
#else
    return strcasecmp( str_x , str_y );
#endif
}


#endif
