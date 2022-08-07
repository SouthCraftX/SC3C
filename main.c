#include <stdio.h>
#include <stdlib.h>
#include <zip.h>
#include <io.h>
#include <png.h>
#include <time.h>
#include <stdbool.h>

#include "defines.h"
#include "construct_func.h"
#include "png_unzipper.h"

void png_decoder(struct PNGData* png , const struct CovertOption* opt) {

    png_structp     png_ptr             = NULL;
    png_infop       info_ptr            = NULL;
    FILE*           temp_png_file_ptr   = fopen(opt->temp_path, "rb");

    png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL , NULL , NULL );
    if( png_ptr == NULL ){
        put_err_msg( "Failed to initialise PNG decoder");
        abort();
    }

    info_ptr = png_create_info_struct( png_ptr );
    if (!info_ptr){
        png_destroy_read_struct(&png_ptr,NULL,NULL);
        put_err_msg( "Failed to initialise PNG decoder");
        abort();
    }
    int png_error_code = setjmp( png_jmpbuf( png_ptr ) );
    if( png_error_code ){
        put_err_msg( "[PNG I/O]Have problems decoding PNG. Error Code = %i", png_error_code);
    }

    png_init_io( png_ptr, temp_png_file_ptr );
    //png_read_png( png_ptr, info_ptr , PNG_TRANSFORM_EXPAND , NULL );

    ulong width,height;
    long bit_depth,color_type;
    png_get_IHDR( png_ptr , info_ptr , &png->width , &png->height,
                  &bit_depth , &color_type , NULL , NULL, NULL );

    //png->num_channel = png_get_channels( png_ptr , info_ptr );
    
    //将像素格式转换为RGBA
    if (bit_depth==16)
        png_set_strip_16(png_ptr); //要求位深度强制8bit
    if (color_type==PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);            //要求转换索引颜色到RGB
    if (color_type==PNG_COLOR_TYPE_GRAY && bit_depth<8)
        png_set_expand_gray_1_2_4_to_8(png_ptr);    //要求位深度强制8bit
    if (png_get_valid(png_ptr,info_ptr,PNG_INFO_tRNS))
       png_set_tRNS_to_alpha(png_ptr);
    if(color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, DEFAULT_ALPHA, PNG_FILLER_AFTER);  // These color_type don't have an alpha channel then fill it with DEFAULT_ALPHA.
    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png_ptr);               //灰度必须转换成RGB
    
    png_read_update_info(png_ptr, info_ptr);
    
    png->row_ptr = (png_bytep *)malloc(sizeof(png_bytep) * height);

    for (int y = 0; y < height; y++) {
        png->row_ptr[y] = (png_byte *)malloc(png_get_rowbytes(png_ptr, png_info));
    }
    png_read_image(png, png->row_ptr);

    
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(temp_png_file_ptr);

    return OK;

}



bool ExportJSON( struct PNGData* png , const struct CovertOption* opt ){

   FILE* json_ptr = fopen( opt->output_path , "r" );
   if( json_ptr == NULL ){
       put_err_msg(  "Failed to create JSON file:%s" , opt->output_path);
       abort();
   }
   fputs("[",json_ptr);
   for( int loop=0 ; loop <= (png->num_pixel*3) ; loop +=3 ) {
        fputs(   ("{\"R\":%i,\"G\":%i,\"B\":%i,\"A\":%i},",
                            png->row_ptr[loop][0],
                            png->row_ptr[loop][1],
                            png->row_ptr[loop][2],
                            png->row_ptr[loop][3],) , json_ptr);
        //if( is_successful ==  EOF ){
            //fprintf( stderr , "Failed to write JSON file!");
            //fclose( json_ptr );
            //exit(WriteJson);
        //}
   }
   fputs( "\b]" , json_ptr ); 
   fclose( json_ptr );
   
}
/*
bool RandomColourOrder( struct _PNGData* png ){

    for( int step = 0 ; step < png->num_pixel ; ++step ){
        byte temp_red , temp_blue , temp_green , temp_alpha ;
        
        int swap_x = rand()%(png->num_pixel) , swap_y = rand()%(png->num_pixel);
        temp_red   = png->pixel_red  [ swap_y ];
        temp_blue  = png->pixel_blue [ swap_y ];
        temp_green = png->pixel_green[ swap_y ];
        temp_alpha = png->pixel_alpha[ swap_y ];

        png->pixel_red  [ swap_y ] =   png->pixel_red  [ swap_x ] ;
        png->pixel_blue [ swap_y ] =   png->pixel_blue [ swap_x ] ;
        png->pixel_green[ swap_y ] =   png->pixel_green[ swap_x ] ;
        png->pixel_alpha[ swap_y ] =   png->pixel_alpha[ swap_x ] ;

        png->pixel_red  [ swap_x ] = temp_red  ;
        png->pixel_blue [ swap_x ] = temp_blue ;
        png->pixel_green[ swap_x ] = temp_green;
        png->pixel_alpha[ swap_x ] = temp_alpha;

    }
}
*/
void PutHelpInfo(){

}




int main( int argn , char* argc[]  ){

}