#ifndef SC3CHF_OTHERS
#define SC3CHF_OTHERS

#include "defines.h"
#include "lang.h"
#include "console_color.h"
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
    for(ulong32 hei = 0 ; hei < png->height ; ++hei ){
        free(png->row_ptr);
    }
    free(png->row_ptr);
}

//#define put_err_msg( format , ...) ( 
 //           fprintf(stderr, format , __VA_ARGS__) 
 //       )


//Print a error message end abort.
void put_err_msg_abort( ccstring formated_msg  , ...){
    va_list arg;
    va_start( arg , formated_msg );
    set_console_color(CSC_LIGHTRED);
    vfprintf( stderr , formated_msg , arg);
    va_end(arg);
    abort();
}

void put_info_msg( const bool if_put  ,
                   ccstring formated_msg , ... ){
    va_list arg;
    va_start( arg , formated_msg );
    if(if_put)
        vprintf( formated_msg , arg );
    va_end(arg);
    return;
}

void put_debug_msg (const bool if_put  ,
                   ccstring formated_msg , ... )
{
    set_console_color( CSC_GREEN );
    va_list arg;
    va_start( arg , formated_msg );
    if(if_put)
        vprintf( formated_msg , arg );
    va_end(arg);
    set_console_color( CSC_WHITE );
    return;        
}

void print_opt(const struct ConvertOption* opt){
    set_console_color( CSC_GREEN );
    puts("=====DEBUG=====\nConvert Option:\n");
    printf("\tInput Path = %s\n\tOutput Path = %s\n\tTemp File Path = %s\n\tForce Overriding = %i\n\t"\
            "Print Info Message = %i\n\t",
            opt->input_path , opt->output_path , opt->temp_path, 
            opt->force_overriding  , opt->print_info_msg );
}

bool file_exist_warning( ccstring path){
    set_console_color( CSC_YELLOW );
    printf(WARN_OVERRIDE,path);
    set_console_color( CSC_WHITE );
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
            puts( ERRMSG_OWW_INPUT );
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
