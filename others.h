#ifndef SC3CHF_OTHERS
#define SC3CHF_OTHERS
#include "defines.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <io.h>
//Print a error message and exit.
void put_err_msg( ccstring formated_msg  , ...){
    va_list arg;
    fprintf( stderr , formated_msg , arg);
}

void put_info_msg( const CovertOption* opt , ccstring formated_msg , ... ){
    va_list arg;
    if(!opt->print_error_msg_only)
        printf( formated_msg , arg );
    return;
}

bool file_exist_warning( ccstring path){
    printf("Warning: %s is already exist.Do you want to overwrite the file?(y/n):");
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
            printf("Invalid input.File overwrite cancelled.");
            return false;
    }
}

size_t fwriter( void* buffer , size_t nwrite ,size_t ncount ,FILE* stream  ){
#ifdef USE_UNLOCKED_FWRITE
    return _fwrite_nolock( buffer , nwrite , ncount ,stream );
#else
    return fwrite( buffer , nwrite , ncount ,stream );
#endif
}

int strcmp_ignore_case( ccstring str_x , ccstring str_y ){
#ifdef _WIN32
    return stricmp( str_x , str_y );
#else
    return strcasecmp( str_x , str_y );
#endif
}


#endif