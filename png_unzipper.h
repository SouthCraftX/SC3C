/*
    png_unzipper.h 
    Provide a simply unzipper

[English]
    Copyright (C) <2023> <South Craft>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 3 as 
    published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License, version 3 for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Send an email to the following email address if you want to contact
    me: southcraft2007@gmail.com

[Chinese]
    注：如果中文版本与英文版本有出入，以英文版本为准

    png_unzipper.h  提供了一个简易的解压缩器
    版权所有（C）<2023> <South Craft>

　　本程序为自由软件，在自由软件联盟发布的GNU通用公共许可协议的约束下，你可以对其进行
    再发布及修改。协议版本为第三版。

    我们希望发布的这款程序有用，但不保证，甚至不保证它有经济价值和适合特定用途。详情
    参见GNU通用公共许可协议。

    你理当已收到一份GNU通用公共许可协议的副本，如果没有，请访问
    <http://www.gnu.org/licenses/>

    联系方式：[Gmail] southcraft2007@gmail.com

Completed in GMT+8 Jan 4th, 2023, 11:52 AM
*/


#ifndef SC3CHF_UNZ
#define SC3CHF_UNZ

//For MSVC
#ifdef _MSC_VER
#pragma warning(disable : 4996)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif //#ifndef _CRT_SECURE_NO_WARNINGS
#endif //#ifdef _MSC_VER

#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>

//minizip
#include <zip.h>
#include <unzip.h>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

#include "console_color.h"
#include "lang.h"
#include "definations.h"
#include "others.h"


/*
    remove()
    To remove a file.
    return :
        0   = succeed
        !0  = failed
*/

extern convert_option_t opt;
extern png_data_t       png;

/*
void clean_cache( ccstring_t cache_path ){
    if(access( cache_path  , 0 )==F_OK){
        if(remove( cache_path )){
            put_err_msg_abort( error_msg.unz.clean_cache , cache_path);
            abort();
        }
    }
}
*/

void delete_cache(){
    remove( opt.temp_path );
}

void unzipper(){

    byte_t              io_buffer       [BUFFER_SIZE] ;
    unzFile             zipfile         =  NULL       ;
    unz_global_info64   global_info                   ;
    unz_file_info64     file_info                     ;
    char                fname_in_zip    [FILENAME_MAX];
    //memset( fname_in_zip , 0 , sizeof(fname_in_zip));

    put_info_msg( info_msg.unz.open_zip );
    zipfile =  unzOpen64( opt.input_path );

    if( zipfile == NULL ) {
        put_err_msg_abort( error_msg.unz.open_zip , opt.input_path );
    }
    put_info_msg( info_msg.ok );

    put_info_msg( info_msg.unz.global_info );
    if(unzGetGlobalInfo64( zipfile , &global_info ) != UNZ_OK ){
        unzClose( zipfile );
        put_err_msg_abort( error_msg.unz.global_info );
    }
    put_info_msg( info_msg.ok );

    put_info_msg( info_msg.unz.search );
    int gonext_ret = unzGoToFirstFile( zipfile );
    bool found_png = false;
    while( gonext_ret == UNZ_OK ){
        if(unzGetCurrentFileInfo64( zipfile , &file_info , fname_in_zip ,
                                    sizeof(fname_in_zip) , NULL , 0 , NULL , 0)
           != UNZ_OK)
        {
            unzClose( zipfile );
            put_err_msg_abort( error_msg.unz.cur_file_info );
        }

        if(strcmp_ignore_case(fname_in_zip , PNG_NAME ))
            goto GOTOLAB_NEXTFILE;

        found_png = true;
        put_info_msg( info_msg.unz.found );

        put_info_msg( info_msg.unz.cur_file_open );
        if(unzOpenCurrentFile( zipfile ) != UNZ_OK){
            unzClose( zipfile );
            put_err_msg_abort( error_msg.unz.read_png );
        }
        put_info_msg( info_msg.ok );

        if( file_info.uncompressed_size > 128*1024 ){
            unzCloseCurrentFile( zipfile );
            unzClose( zipfile );
            put_err_msg_abort( error_msg.unz.png_too_large );
        }
        break;

        GOTOLAB_NEXTFILE:
            gonext_ret = unzGoToNextFile( zipfile );
    }

        if(!found_png){
            put_err_msg_abort( error_msg.unz.no_png );
        }
        
        put_info_msg( info_msg.unz.create_tmp_file );
        FILE* write_png_fptr = fopen( opt.temp_path , "wb" );
        if( !write_png_fptr ){
            put_err_msg_abort( error_msg.unz.create_temp_file , opt.temp_path );
        }
        put_info_msg( info_msg.ok );

        //memset( io_buffer , 0 , BUFFER_SIZE );
        put_info_msg( info_msg.unz.write_tmp_file );
        int read_n = 0;
        for(int remain_size = file_info.uncompressed_size ; remain_size > 0 ; remain_size -= BUFFER_SIZE )
        {
            read_n =  unzReadCurrentFile( zipfile , io_buffer , BUFFER_SIZE );
            fwrite( io_buffer , 1 , read_n , write_png_fptr );
        }
        put_info_msg( info_msg.ok );
        fclose( write_png_fptr );
        unzCloseCurrentFile( zipfile );
        unzClose( zipfile );
    }

#endif  
