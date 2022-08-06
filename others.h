#ifndef SC3CHF_OTHERS
#define SC3CHF_OTHERS
#include "defines.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <io.h>
//Print a error message.
void put_err_msg( ccstring formated_msg  , ...){
    va_list arg;
    fprintf( stderr , formated_msg , arg);
}


void put_info_msg( const struct CovertOption* opt , 
                   ccstring formated_msg , ... ){
    va_list arg;
    if(!opt->print_error_msg_only)
        printf( formated_msg , arg );
    return;
}

bool file_exist_warning( ccstring path){
    printf("Warning: %s is already exist.Override?(y/n):");
    char input;
    fflush ( stdin );
    scanf("%c",input);
    fflush ( stdin );

    switch( input ){
        case 'y':
        case 'Y': return true;
        case 'n':
        case 'N': return false;
        default: 
            puts("Invalid input.File overwrite cancelled.");
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