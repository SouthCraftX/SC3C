#ifndef SC3CHF_UNZ
#define SC3CHF_UNZ
#define __STDC_WANT_LIB_EXT1__ 1

#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "zconf.h"
#include "ioapi.h"
#include "unzip.h"
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
            fprintf( stderr , ERRMSG_UNZ_CLRCACHE , cache_path);
            abort();
        }
    }
}

bool unzipper( const struct ConvertOption* opt ){
    //char* zip_path;

    assert(opt!=NULL);

    byte                io_buffer       [BUFFER_SIZE] ;
    unzFile             zipfile         =  NULL       ;
    unz_global_info64   global_info                   ;
    unz_file_info64     file_info                     ;
    char                fname_in_zip    [FILENAME_MAX];
    memset( fname_in_zip , 0 , sizeof(fname_in_zip));

    zipfile =  unzOpen64( opt->input_path );

    if( zipfile == NULL ) {
        set_console_color(CSC_LIGHTRED);
        fprintf( stderr , ERRMSG_UNZ_OPENZIP,opt->input_path);
        abort();
    }

    if(unzGetGlobalInfo64( zipfile , &global_info ) != UNZ_OK ){
        set_console_color(CSC_LIGHTRED);
        unzClose( zipfile );
        fprintf( stderr , ERRMSG_UNZ_GBINFO);
        abort();
    }

    int gonext_ret = unzGoToFirstFile( zipfile );

    while( gonext_ret == UNZ_OK ){
        if(unzGetCurrentFileInfo64( zipfile , &file_info , fname_in_zip , 
                                    sizeof(fname_in_zip) , NULL , 0 , NULL , 0)
           != UNZ_OK)
        {
            nzClose( zipfile );
            set_console_color(CSC_LIGHTRED);
            fprintf( stderr , ERRMSG_UNZ_CTFINFO);
            abort();
        }

        if(strcmp_ignore_case(fname_in_zip , "noteColors.png"))
            goto GOTOLAB_NEXTFILE;

        if(unzOpenCurrentFile( zipfile ) != UNZ_OK){
            unzClose( zipfile );
            set_console_color(CSC_LIGHTRED);
            fprintf( stderr , "Failed to open noteColors.png." );
            abort();
        }
            
        if( file_info.uncompressed_size > 1024*1024 ){
            unzCloseCurrentFile( zipfile );
            unzClose( zipfile );
            set_console_color(CSC_LIGHTRED);
            fprintf( stderr , ERRMSG_UNZ_PNGTL);
            abort();
        }

        break;
        GOTOLAB_NEXTFILE:
            gonext_ret = unzGoToNextFile( zipfile );
    }
    memset( io_buffer , 0 , BUFFER_SIZE );

    FILE* write_png_fptr;
#ifdef  __STDC_LIB_EXT1__
    if( fopen_s(&write_png_fptr, PATH_TO_UNZIP , "wb" ) ){
#else
    write_png_fptr =  fopen(PATH_TO_UNZIP,"wb");
    if(!write_png_fptr){
#endif
        set_console_color(CSC_LIGHTRED);
        fprintf( stderr , ERRMSG_UNZ_TMPCR , opt->temp_path);
        abort();
    }

    int read_n = 0;
    for(int remain_size = file_info.uncompressed_size ; remain_size>0 ; remain_size-= BUFFER_SIZE )
    {
        read_n =  unzReadCurrentFile( zipfile , io_buffer , BUFFER_SIZE );
        fwriter( io_buffer , read_n , 1 , write_png_fptr );
    }
    unzCloseCurrentFile( zipfile );
    unzClose( zipfile );

            //for( int l = 0; l< file_info.uncompressed_size ; ++l){
        //    printf("%c ",*(io_buffer+l));
        //}

        //if( !writepng( io_buffer , file_info.uncompressed_size ,1, write_png_fptr ))
           // QUITMSG( "Failed to write temporary file." );

        //size_t write_ret = writepng( io_buffer , file_info.uncompressed_size , 1, write_png_fptr );
        return true;
    }

#endif
