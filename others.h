#ifndef SC3CHF_OTHERS
#define SC3CHF_OTHERS

//For MSVC
#ifdef _MSC_VER
#pragma warning(disable : 4996)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif //#ifndef _CRT_SECURE_NO_WARNINGS
#endif //#ifdef _MSC_VER


#include "definations.h"
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

void do_banner(){

    puts(banner_text);
}

extern convert_option_t opt;
extern png_data_t       png;

void destroy_pixel_memory( ){
    for(ulong32_t hei = 0 ; hei < png.height ; hei++ ){
        free(png.row_ptr[hei]);
    }
    free(png.row_ptr);
}

//#define put_err_msg( format , ...) ( 
 //           fprintf(stderr, format , __VA_ARGS__) 
 //       )


//Print a error message end abort.
void put_err_msg_abort( ccstring_t format , ...){
    va_list arg;
    va_start( arg , format );
    set_console_color(cmd_text_color.lightred);
    vfprintf( stderr , format  , arg);
    set_console_color(cmd_text_color.white);
    va_end(arg);
    exit(-1);
}

void put_info_msg( const bool if_put  ,
                   ccstring_t format , ... ){
    va_list arg;
    va_start( arg , format );
    if(if_put)
        vprintf( format , arg );
    va_end(arg);
}

void put_debug_msg (const bool if_put  ,
                   ccstring_t format , ... )
{
    set_console_color( cmd_text_color.green );
    va_list arg;
    va_start( arg , format );
    if(if_put)
        vprintf( format , arg );
    va_end(arg);
    set_console_color( cmd_text_color.white );   
}
/*
void print_opt(const struct ConvertOption* opt){
    set_console_color( CSC_GREEN );
    puts("=====DEBUG=====\nConvert Option:\n");
    printf("\tInput Path = %s\n\tOutput Path = %s\n\tTemp File Path = %s\n\tForce Overriding = %i\n\t"\
            "Print Info Message = %i\n\t",
            opt->input_path , opt->output_path , opt->temp_path, 
            opt->force_overriding  , opt->print_info_msg );
}
*/
bool file_exist_warning( ccstring_t path){

    set_console_color( cmd_text_color.yellow );
    printf(WARN_OVERRIDE,path);
    set_console_color( cmd_text_color.white );

    char input_char;
    fflush ( stdin );
    scanf("%c",&input_char);
    fflush ( stdin );

    switch( input_char ){
        case 'y':
        case 'Y': return true;
        case 'n':
        case 'N': return false;
        default:
            set_console_color(cmd_text_color.lightred);
            puts( info_msg.no_override );
            set_console_color(cmd_text_color.white);
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
int strcmp_ignore_case( ccstring_t x , ccstring_t y ){
#ifdef _WIN32
    return _stricmp( x , y );
#else
    return strcasecmp( x , y );
#endif
}


#endif
