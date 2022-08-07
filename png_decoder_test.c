#include <string.h>
#include <stdlib.h>
#include <png.h>
#include <stdio.h>
#define OK 0
#define TEMP_PNG_FILE "noteColors.png"
#define PATH_TO_UNZIP "noteColors.png"
typedef unsigned char byte;

void QUITMSG(const char* msg){
    fprintf(stderr , msg);
    exit(0);
}

struct _PNGData {
    char* temp_png_path;
    byte** row_pointers;
    int bit_depth;
    int m_width    ;  
    int m_height   ;
    int color_type ;
    int num_channel;
    int num_pixel  ;
};

void Construct_PNGData( struct _PNGData* _struct ){
    _struct->row_pointers = NULL;
    _struct->temp_png_path = TEMP_PNG_FILE ;
    _struct->bit_depth = 0;
    _struct->m_width       = 0 ;
    _struct->m_height      = 0 ;
    _struct->color_type    = 0 ;
    _struct->num_channel   = 0 ;
    _struct->num_pixel     = 0 ;
}

void ReadPNG(struct _PNGData* png) {

    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    FILE* temp_png_file_ptr ;

    if( fopen_s( &temp_png_file_ptr , PATH_TO_UNZIP , "rb" ) )
        QUITMSG("Failed to read temporary file.");

    png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL , NULL , NULL );
    if( png_ptr == NULL ){
        QUITMSG( "Failed to prepare png_ptr.");
        png_destroy_read_struct(&png_ptr, NULL, NULL);
    }

    info_ptr = png_create_info_struct( png_ptr );
    if (!info_ptr){
        png_destroy_read_struct(&png_ptr,NULL,NULL);
        QUITMSG( "Failed to prepare info_ptr.");
    }

    int png_error_code = setjmp( png_jmpbuf( png_ptr ) );
    if( png_error_code ){
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        char errmsg[64] ;
        sprintf( errmsg , "[PNG I/O]Have problems decoding PNG.[libpng]Error Code = %i", png_error_code );
        QUITMSG(errmsg);
    }

    png_init_io( png_ptr, temp_png_file_ptr );
    png_read_png( png_ptr, info_ptr , PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND , NULL );
    png_read_info(png_ptr, info_ptr);

    png_get_IHDR( png_ptr , info_ptr , &png->m_width , &png->m_height,
                  &png->bit_depth , &png->color_type , NULL , NULL, NULL );

    png->num_channel = png_get_channels( png_ptr , info_ptr );
    png->num_pixel   = png->m_height * png->m_width ;
/*
    if (png->color_type==PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);            //要求转换索引颜色到RGB
    if (png->color_type==PNG_COLOR_TYPE_GRAY && png->bit_depth<8)
        png_set_expand_gray_1_2_4_to_8(png_ptr);    //要求位深度强制8bit
    if (png_get_valid(png_ptr,info_ptr,PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);
    if (png->color_type == PNG_COLOR_TYPE_GRAY || png->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png_ptr);               //灰度必须转换成RGB
    if (png->bit_depth==16){

        png_set_strip_16(png_ptr); //要求位深度强制8bit
    }
 */       
    png->row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * png->m_height);

    for (int y = 0; y < png->m_height; y++) {
        png->row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png_ptr, info_ptr));
    }
    png_read_image(png_ptr, png->row_pointers);
    png_read_end( png_ptr , info_ptr );
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(temp_png_file_ptr);

}

void print_row(struct _PNGData* png){
    for( int i = 0 ; i< png->num_pixel ; i+=3){
        printf("R%iG%iB%i " , **(png->row_pointers+i),**(png->row_pointers+i+1) , **(png->row_pointers+i+2));
    }
}

int main(){
    struct _PNGData png;
    Construct_PNGData(&png);
    ReadPNG(&png);   
    print_row(&png);
    return 0;
}