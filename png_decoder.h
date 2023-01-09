/*
    png_decoder.h 
    Provide a PNG decoder using libpng and zlib.

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

    png_decoder.h 提供了一个使用libpng和zlib的PNG解码器
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



#ifndef SC3CHF_PNGDEC
#define SC3CHF_PNGDEC

//For MSVC
#ifdef _MSC_VER
#pragma warning(disable : 4996)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif //#ifndef _CRT_SECURE_NO_WARNINGS
#endif //#ifdef _MSC_VER

#include <png.h>
#include <stdio.h>
#include <limits.h>

#include "definations.h"
#include "others.h"

extern convert_option_t opt;
extern png_data_t       png;

void png_decoder( ) {

    png_structp     png_ptr     = NULL;
    png_infop       info_ptr    = NULL;
    FILE*           png_fptr    = fopen(opt.temp_path, "rb");

    if(!png_fptr)
        put_err_msg_abort(error_msg.png.read);

    put_info_msg( info_msg.png.initdec );
    png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL , NULL , NULL );
    if( png_ptr == NULL )
        put_err_msg_abort( error_msg.png.initdec);

    info_ptr = png_create_info_struct( png_ptr );
    if (!info_ptr){
        png_destroy_read_struct(&png_ptr,NULL,NULL);
        put_err_msg_abort(  error_msg.png.initdec );
    }
    put_info_msg( info_msg.ok );

    int png_error_code = setjmp( png_jmpbuf( png_ptr ) );
    if( png_error_code )
        put_err_msg_abort( error_msg.png.decode , png_error_code);


    png_init_io( png_ptr, png_fptr );
    png_read_info( png_ptr, info_ptr );
    //png_read_png( png_ptr, info_ptr , PNG_TRANSFORM_EXPAND , NULL );

    put_info_msg( info_msg.png.get_info );
    long32_t bit_depth,color_type;
    if(!png_get_IHDR( png_ptr , info_ptr , &png.width , &png.height,
                  &bit_depth , &color_type , NULL , NULL, NULL ))
    {
        put_err_msg_abort( error_msg.png.get_info );
    }
    put_info_msg( info_msg.ok );

    //png.num_channel = png_get_channels( png_ptr , info_ptr );
    //将像素格式转换为RGBA
    if ( bit_depth == 16 )
        png_set_strip_16( png_ptr ); //要求位深度强制8bit
    if ( color_type == PNG_COLOR_TYPE_PALETTE )
        png_set_palette_to_rgb( png_ptr );            //要求转换索引颜色到RGB
    if ( color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8( png_ptr );    //要求位深度强制8bit
    if ( png_get_valid( png_ptr , info_ptr , PNG_INFO_tRNS ) )
       png_set_tRNS_to_alpha( png_ptr);
    if( color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_PALETTE )
        png_set_filler( png_ptr , DEFAULT_ALPHA , PNG_FILLER_AFTER);  // These color_type don't have an alpha channel then fill it with DEFAULT_ALPHA.
    if( color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA )
        png_set_gray_to_rgb( png_ptr );               //灰度必须转换成RGB

    //更新图像信息
    png_read_update_info(png_ptr, info_ptr);


    long64_t test_is_nullptr = 1;
    png.row_ptr = (byte_t**)malloc( sizeof(png_bytep) * png.height );

    test_is_nullptr = (test_is_nullptr&&png.row_ptr);
    if(!test_is_nullptr) 
        goto GOTOLAB_PNG_NULPTR;
    
    for (ulong32_t y = 0; y < png.height; y++) {
        png.row_ptr[y] = (png_byte *)malloc(png_get_rowbytes(png_ptr, info_ptr));
        test_is_nullptr = (test_is_nullptr&&png.row_ptr[y]);
    }
    if(!test_is_nullptr){
        GOTOLAB_PNG_NULPTR:
            try_free_pixel_memory();
            put_err_msg_abort( error_msg.png.alloc );
    }
        

    png_read_image( png_ptr, png.row_ptr);

    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose( png_fptr );

}

void export_to_json(){

    put_info_msg( info_msg.write_json.create );
    FILE* json_fptr = fopen( opt.output_path , "w" );
    if( !json_fptr ){
        free_pixel_memory();
        put_err_msg_abort( error_msg.write_json.create , opt.output_path );
    }
    put_info_msg( info_msg.ok );

    if( fputc('[',json_fptr) == EOF )
        goto GOTOLAB_WRIFAL;
    
   //ugly
    byte_t test_write = 1;
    for( ulong32_t hei = 0 ; hei < png.height ; ++hei ) {
        for( ulong32_t wid = 0 ; wid < png.width ; ++wid ){
            test_write = fprintf(   json_fptr , "{\"R\":%i,\"G\":%i,\"B\":%i,\"A\":%i},",
                                    png.row_ptr[hei][wid*4],png.row_ptr[hei][wid*4+1],
                                    png.row_ptr[hei][wid*4+2],png.row_ptr[hei][wid*4+3])
            && test_write ;
        }
    }
    test_write = (!(fseek(json_fptr , -1 , SEEK_CUR ))&&test_write);
    if( ( fputs( "]" , json_fptr ) == EOF ) || !test_write )
        goto GOTOLAB_WRIFAL;
    
    fclose( json_fptr );

    return;

    GOTOLAB_WRIFAL:
        put_err_msg_abort( error_msg.write_json.write );
}

#endif //#ifndef SC3CHF_PNGDEC