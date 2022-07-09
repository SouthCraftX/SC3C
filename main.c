#include <stdio.h>
#include <stdlib.h>
#include <zip.h>
#include <io.h>
#include <png.h>
#include <time.h>

#include "defines.h"
#include "construct_func.h"
#include "png_unzipper.h"
//#define TEMP_PNG_FILE "TEMP\\ColorConfigurationConversion\\_____color_____.png"

//#define NUM_RAMDOM_CHANGES 233

/*
bool UnzipPNGFile( struct _ResPackArchive* _archive ){

    if( access( _archive->zip_path , F_OK) != -1){
        goto ContinueRun;
    }
    else{
        printf("%s is not exist." , _archive->zip_path );
        exit( NoDirFile );
    }

    ContinueRun:

    _archive->archive = zip_open(  _archive->zip_path , ZIP_RDONLY , &(_archive->error_code));
    if( _archive->archive == NULL ){
        //char error_message[2048];
        //sprintf( error_message , "Failed to open %s . Error = %d.\n" , _archive->zip_path , _archive->error_code  );
        fprintf( stderr , "Failed to open %s . Error = %d.\n" , _archive->zip_path , _archive->error_code );
        exit( OpenZipFailed );
    }
    printf( "%s is successfully opened.\n" , _archive->zip_path );

    zip_file_t* png_fileptr;
    png_fileptr = zip_fopen(_archive->archive ,  _archive->zip_png_path , ZIP_FL_COMPRESSED);

    if( png_fileptr == NULL){
        fprintf( stderr , "Failed to open %s in %s.The resource pack may not include color configurations.\n", _archive->zip_png_path , _archive->zip_path );
        zip_close( _archive->archive );
        exit( OpenPNGFailed );
    }
    printf("%s\\%s is successfully opened.\n",_archive->zip_path,_archive->zip_png_path);

    FILE* local_png = fopen( TEMP_PNG_FILE , "w+" );
    if( local_png == NULL ){
        fprintf( stderr , "Failed to create temporary file:%s" , TEMP_PNG_FILE );
        zip_fclose( png_fileptr );
        zip_close( _archive->archive );
        exit( CreateFile );
    }

    int index = zip_name_locate( _archive->archive , _archive->zip_png_path , ZIP_FL_ENC_GUESS );
    zip_stat_t png_stat;
    zip_stat_index(_archive->archive,index, ZIP_FL_UNCHANGED, &png_stat);
    
    byte buffer[png_stat.size];
    memset( buffer , 0 , sizeof(buffer) );
    size_t read_size = zip_fread( png_fileptr  , buffer , png_stat.size );
    fwrite( buffer , 1 , read_size , local_png );
    fclose( local_png );
    zip_fclose( png_fileptr );
    zip_close( _archive->archive );
    printf("Successfully create tempoary file.\n");
    return OK;

}


    if( access( _archive->zip_path , F_OK) != -1){
        goto ContinueRun;
    }
    else{
        fprintf("%s is not exist." , _archive->zip_path );
        exit( NoDirFile );
    }

    ContinueRun:

    _archive->archive = zip_open(  _archive->zip_path , ZIP_RDONLY , &(_archive->error_code));
    if( _archive->archive == NULL ){
        fprintf( stderr , ("Failed to open %s . Error = %d.\n" , _archive->zip_path , _archive->error_code ));
        exit( OpenZipFailed );
    }
    printf( "%s is successfully opened.\n" , _archive->zip_path );

    zip_file_t* png_fileptr;
    png_fileptr = zip_fopen(_archive->archive ,  _archive->zip_png_path , ZIP_FL_COMPRESSED);

    if( png_fileptr == NULL){
        fprintf( stderr , "Failed to open %s in %s.\n", _archive->zip_png_path , _archive->zip_path );
        zip_close( _archive->archive );
        exit( OpenPNGFailed );
    }
    printf("%s\\%s is successfully opened.\n",_archive->zip_path,_archive->zip_png_path);

    FILE* LocalPNG = fopen( TEMP_PNG_FILE , "w+" );
    if( LocalPNG == NULL ){
        fprintf( stderr , "Failed to create temporary file:%s" , TEMP_PNG_FILE );
        zip_fclose( png_fileptr );
        zip_close( _archive->archive );
        exit( CreateFile );
    }

    int index = zip_name_locate( _archive->archive , _archive->zip_png_path , ZIP_FL_ENC_GUESS );
    zip_stat_t PNG_stat;
    zip_stat_index(_archive->archive,index, ZIP_FL_UNCHANGED, &PNG_stat);
    
    byte buffer[PNG_stat.size];
    memset( buffer , 0 , sizeof(buffer) );
    size_t read_size = zip_fread( _archive->archive , buffer , PNG_stat.size );
    fwrite( buffer , 1 , read_size , LocalPNG );
    fclose( LocalPNG );
    zip_fclose( png_fileptr );
    zip_close( _archive->archive );
    printf("Successfully create tempoary file.\n");
    return OK;

}
*/
void ReadPNG(struct _PNGData* png) {

    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    FILE* temp_png_file_ptr = fopen(PATH_TO_UNZIP, "rb");

    png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL , NULL , NULL );
    if( png_ptr == NULL )
        QUITMSG( "Failed to prepare png_ptr.");

    info_ptr = png_create_info_struct( png_ptr );
    if (!info_ptr){
        png_destroy_read_struct(&png_ptr,NULL,NULL);
        QUITMSG( "Failed to prepare info_ptr.");
    }

    int png_error_code = setjmp( png_jmpbuf( png_ptr ) );
    if( png_error_code ){
        char errmsg[64] ;
        sprintf( errmsg , "[PNG I/O]Have problems decoding PNG.[libpng]Error Code = %i", png_error_code );
        QUITMSG(errmsg);
    }

    png_init_io( png_ptr, temp_png_file_ptr );
    png_read_png( png_ptr, info_ptr , PNG_TRANSFORM_EXPAND , NULL );

    png_get_IHDR( png_ptr , info_ptr , &png->m_width , &png->m_height,
                  &png->bit_depth , &png->color_type , NULL , NULL, NULL );

    png->num_channel = png_get_channels( png_ptr , info_ptr );
    png->num_pixel   = png->m_height * png->m_width ;

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
        
    png->row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * png->m_height);

    for (int y = 0; y < png->m_height; y++) {
        png->row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png_ptr, png_info));
    }
    png_read_image(png, png->row_pointers);

    /*
    png->pixel_red       = (byte*)malloc(png->num_pixel);
	png->pixel_green     = (byte*)malloc(png->num_pixel);
	png->pixel_blue      = (byte*)malloc(png->num_pixel);
    png->pixel_alpha     = (byte*)malloc(png->num_pixel);

    if( png->num_channel == 4 ){
        for(int height = 0; height < png->m_height; height++){
            for(int width = 0; width < (4 * png->m_width); width += 4){
                png->pixel_blue [width*height] = row_pointers[height][width + 2]; // blue
                png->pixel_green[width*height] = row_pointers[height][width + 1]; // green
                png->pixel_red  [width*height] = row_pointers[height][width];   // red
                png->pixel_alpha[width*height] = row_pointers[height][width + 3]; // alpha
            }
        }
    }
    else if( png->num_channel == 3 ){
        for(int height = 0; height < png->m_height; height++){
            for(int width = 0; width < (4 * png->m_width); width += 4){
                png->pixel_blue   = row_pointers[height][width + 2]; // blue
                png->pixel_green  = row_pointers[height][width + 1]; // green
                png->pixel_red    = row_pointers[height][width];   // red
                png->pixel_alpha[width*height] = DEFAULT_ALPHA ;
            }
        }
    }
    else{
        fprintf( stderr , "Wrong number of colour channels:%i",png->num_channel);
    }
    */
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(temp_png_file_ptr);

    return OK;

}

bool FileExistWarning( const char* path){
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

bool ExportJSON( struct _PNGData* png , const char* json_path ){

   FILE* json_ptr = fopen( json_path , "r" );
   if( json_ptr == NULL ){
       fprintf( stderr , "Failed to create JSON file:%s" , json_path);
       exit(CreateFile);
   }
   fputs("[",json_ptr);
   for( int loop=0 ; loop <= (png->num_pixel*3) ; loop +=3 ) {
        byte is_successful = fputs(   ("{\"R\":%i,\"G\":%i,\"B\":%i,\"A\":%i},",
                            **(png->row_pointers+loop),
                            **(png->row_pointers+loop+1),
                            **(png->row_pointers+loop+2),
                            DEFAULT_ALPHA) , json_ptr);
        if( is_successful ==  EOF ){
            fprintf( stderr , "Failed to write JSON file!");
            fclose( json_ptr );
            exit(WriteJson);
        }
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