#ifndef SC3CHF_UNZ
#define SC3CHF_UNZ
#define __STDC_WANT_LIB_EXT1__ 1

#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
//#include "zconf.h"
#include <zip.h>
#include <unzip.h>
#include <assert.h>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

#include "console_color.h"
#include "lang.h"
#include "defines.h"
#include "others.h"

/*
    remove()
    To remove a file.
    return :
        0   = succeed
        !0  = failed
*/
void clean_cache( ccstring cache_path ){
    if(access( cache_path  , 0 )==F_OK){
        if(remove( cache_path )){
            put_err_msg_abort( ERRMSG_UNZ_CLRCACHE , cache_path);
            abort();
        }
    }
}

void unzipper( const struct ConvertOption* opt ){
    //char* zip_path;

    assert(opt);
    put_debug_msg( opt->print_info_msg , "Debug:[+]",__func__ ,"\n");

    byte                io_buffer       [BUFFER_SIZE] ;
    unzFile             zipfile         =  NULL       ;
    unz_global_info64   global_info                   ;
    unz_file_info64     file_info                     ;
    char                fname_in_zip    [FILENAME_MAX];
    memset( fname_in_zip , 0 , sizeof(fname_in_zip));

    zipfile =  unzOpen64( opt->input_path );

    if( zipfile == NULL ) {
        put_err_msg_abort( ERRMSG_UNZ_OPENZIP , opt->input_path);
    }

    if(unzGetGlobalInfo64( zipfile , &global_info ) != UNZ_OK ){
        unzClose( zipfile );
        put_err_msg_abort( ERRMSG_UNZ_GBINFO );
    }

    int gonext_ret = unzGoToFirstFile( zipfile );

    while( gonext_ret == UNZ_OK ){
        if(unzGetCurrentFileInfo64( zipfile , &file_info , fname_in_zip ,
                                    sizeof(fname_in_zip) , NULL , 0 , NULL , 0)
           != UNZ_OK)
        {
            unzClose( zipfile );
            put_err_msg_abort( ERRMSG_UNZ_CTFINFO );
        }
        put_info_msg( opt->print_info_msg , INFO_UNZ_CTFINFO );

        put_debug_msg( opt->print_info_msg , "Now file:%s", fname_in_zip );

        if(strcmp_ignore_case(fname_in_zip , PNG_NAME ))
            goto GOTOLAB_NEXTFILE;

        if(unzOpenCurrentFile( zipfile ) != UNZ_OK){
            unzClose( zipfile );
            put_err_msg_abort( ERRMSG_UNZ_OPENPNG );
        }
        put_info_msg(opt->print_info_msg , INFO_UNZ_CTFOPEN );

        if( file_info.uncompressed_size > 1024*1024 ){
            unzCloseCurrentFile( zipfile );
            unzClose( zipfile );
            put_err_msg_abort( ERRMSG_UNZ_PNGTL);
        }
        break;

        GOTOLAB_NEXTFILE:
            gonext_ret = unzGoToNextFile( zipfile );
    }

        FILE* write_png_fptr = fopen( PATH_TO_UNZIP , "wb" );
        if( !write_png_fptr ){
            put_err_msg_abort( ERRMSG_UNZ_TMPCR , opt->temp_path);
        }
        memset( io_buffer , 0 , BUFFER_SIZE );
        int read_n = 0 , write_n;
        for(int remain_size = file_info.uncompressed_size ; remain_size>0 ; remain_size-= BUFFER_SIZE )
        {
            read_n =  unzReadCurrentFile( zipfile , io_buffer , BUFFER_SIZE );
            write_n = fwrite( io_buffer , 1 , read_n , write_png_fptr );
        }
        fclose(write_png_fptr);
        unzCloseCurrentFile( zipfile );
        unzClose( zipfile );
    }

#endif  
