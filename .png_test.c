#include <stdio.h>
#include <png.h>
#include <stdlib.h>
#include "others.h"
#include "defines.h"
#include "lang.h"

//#pragma comment(lib,"C:\\cygwin64\\usr\\x86_64-w64-mingw32\\sys-root\\mingw\\bin\\libpng16-16.dll")
void png_decoder( const struct ConvertOption* opt ,
                  struct PNGData* png ) {

    png_structp     png_ptr             = NULL;
    png_infop       info_ptr            = NULL;
    FILE*           png_fptr; 

    png_fptr = fopen(opt->temp_path, "rb");
    if (!png_fptr) {
        perror("无法读取PNG");
        abort();
    }

    png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL , NULL , NULL );
    if( png_ptr == NULL )
        put_err_msg_abort( ERRMSG_PNG_INITDEC);

    info_ptr = png_create_info_struct( png_ptr );
    if (!info_ptr){
        png_destroy_read_struct( &png_ptr ,NULL,NULL);
        put_err_msg_abort(  ERRMSG_PNG_INITDEC );
    }
    int png_error_code = setjmp( png_jmpbuf( png_ptr ) );
    if( png_error_code )
        put_err_msg_abort( ERRMSG_PNG_DECODE , png_error_code);


    png_init_io( png_ptr, png_fptr );
    png_read_info( png_ptr, info_ptr );

    long32 bit_depth,color_type;
    png_get_IHDR( png_ptr , info_ptr , &png->width , &png->height,
                  &bit_depth , &color_type , NULL , NULL, NULL );

    //png->num_channel = png_get_channels( png_ptr , info_ptr );
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

    png->row_ptr = (png_bytep *)malloc( sizeof(png_bytep) * png->height);

    for (ulong32 y = 0; y < png->height; y++) {
        png->row_ptr[y] = (png_byte *)malloc(png_get_rowbytes(png_ptr, info_ptr));
    }//这样写有个弊端：1-没有检查是否分配成功（但如果在for循环里检查会大幅度降低性能）2-容易加剧内存碎片化 。上述问题将在后续版本用内存池解决。
    png_read_image( png_ptr, png->row_ptr);

    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose( png_fptr );

}



void export_to_json(  const struct ConvertOption* opt,
                      struct PNGData* png){

    putchar('[');
   //ugly
    for( ulong32 hei = 0 ; hei < png->height ; ++hei ) {
        for( ulong32 wid = 0 ; wid < png->width ; ++wid ){
            printf("{\"R\":%i,\"G\":%i,\"B\":%i,\"A\":%i},",
                    png->row_ptr[hei][wid*4],png->row_ptr[hei][wid*4+1],
                    png->row_ptr[hei][wid*4+2],png->row_ptr[hei][wid*4+3]);
        }
    }
   puts( "\b]" );
}

int main(){

    struct PNGData png;
    struct ConvertOption opt;

    opt.temp_path = "C:\\Program Files (x86)\\i4Tools8\\cache\\hometmp\\02.png";
    png_decoder( &opt , &png );

    for (int y = 0; y < png.height; y ++) {
        for (int x = 0; x < png.width; x ++)
            //printf("[%02hhx%02hhx%02hhx]", png->row_pointers[y][3 * x], png->row_pointers[y][3 * x + 1], png->row_pointers[y][3 * x + 2]);
            printf("[R%i G%i B%i A%i]", png.row_ptr[y][3 * x], png.row_ptr[y][3 * x + 1], png.row_ptr[y][3 * x + 2], png.row_ptr[y][3*x+3]);
        printf("\n");
    }

    export_to_json( &opt , &png );
}
