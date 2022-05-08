#include <stdio.h>
#include <stdlib.h>
#include <zip.h>
#include <stdlib.h>
#include <io.h>
#include <png.h>

typedef int bool;
typedef unsigned char byte;
#define true 1
#define false 0
#define TEMP_PNG_FILE "%TEMP%\_ColorConfigurationConversion_\_____color_____.png"
#define DEFAULT_ALPHA 255


enum StatusCode{
    OK = 0,
    NoDirFile,
    OpenPNGFailed,
    OpenZipFailed,
    CreateTempFile,
    WrongNumChannel
};

enum StatusCode _scode;

struct ResPackArchive {
    zip_t* archive;
    char* zip_path ;
    char* zip_png_path ; 
    int error_code;
    FILE* png_fileptr;
};

void Construct_ResPackArchive( ResPackArchive* _struct , char* zip_path ){
    _struct->archive        = NULL;
    _struct->zippath        = zip_path;
    _struct->zip_png_path   = "noteColors.png";
    _struct->error_code     = 0
    _struct->png_fileptr    = NULLL;
}

struct PNGData {
    char* temp_png_path ;
    byte* pixel_red     ;
    byte* pixel_green   ;
    byte* pixel_blue    ;
    byte* pixel_alpha   ;
    int m_width    ;  
    int m_height   ;
    int color_type ;
    int num_channel;
    int num_pixel  ;
};

void Construct_PNGData( PNGData* _struct ){
    _struct->temp_png_path = TEMP_PNG_FILE ;
    _struct->pixel_red     = NULL ;
    _struct->pixel_green   = NULL ;
    _struct->pixel_blue    = NULL ;
    _struct->pixel_alpha   = NULL ;
    _struct->m_width       = 0 ;
    _struct->m_height      = 0 ;
    _struct->color_type    = 0 ;
    _struct->num_channel   = 0 ;
    _struct->num_pixel     = 0 ;
}

bool UnzipPNGFile( ResPackArchive* _archive ){

    if( access( _archive->zip_path , F_OK) != -1){
        goto ContinueRun;
    }
    else{
        fprintf("%s is not exist." , _archive->zip_path );
        exit( NoDirFile );
    }

    ContinueRun:

    _archive->archive = zip_open(  _archive->path , ZIP_RDONLY , &(_archive->error_code));
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
        exit( CreateTempFile );
    }

    int index = zip_name_locate( _archive->archive , _archive->zip_png_path , ZIP_FL_ENC_GUESS );
    zip_stat_t PNG_stat;
    zip_stat_index(_archive->archive,index, s, &PNG_stat);
    
    byte buffer[PNG_stat.size];
    memset( buffer , 0 , sizeof(buffer) );
    size_t read_size = zip_fread( _arechive->archive , buffer , PNG_stat.size );
    fwrite( buffer , 1 , read_size , LocalPNG );
    fclose( LocalPNG );
    zip_fclose( png_fileptr );
    zip_close( _archive->archive );
    printf("Successfully create tempoary file.\n");
    return OK;

}

void ReadPNG(PNGData* png) {

    FILE* temp_png_file_ptr = fopen(png->fname, "rb");
    png_structp png_ptr     = png_create_read_struct( PNG_LIBPNG_VER_STRING , 0 , 0 , 0 );
    png_infop info_ptr      = png_create_info_struct( png->png_ptr );
    setjmp( png_jmpbuf( png->png_ptr ) );

    png_init_io( png->png_ptr, temp_png_file_ptr );
    png_read_png( png->png_ptr, png->info_ptr , PNG_TRANSFORM_EXPAND , 0 );

    png->m_width     = png_get_image_width( png->png_ptr , png->info_ptr);
    png->m_height    = png_get_image_height( png->png_ptr , png->info_ptr);
    png->color_type  = png_get_color_type( png->png_ptr , png->info_ptr);
    png->num_channel = png_get_channels( png->png_ptr , png->info_ptr );
    png->num_pixel   = png->m_height * png->m_width ;


    png_bytep* row_pointers = png_get_rows(png->png_ptr, png->info_ptr);

    png->pixel_red       = (byte*)malloc(png->num_pixel);
	png->pixel_green     = (byte*)malloc(png->num_pixel);
	png->pixel_blue      = (byte*)malloc(png->num_pixel);
    png->pixel_alpha     = (byte*)malloc(png->num_pixel);

    if( png->num_channel == 4 ){
        for(int height = 0; height < png->m_height; height++){
            for(int width = 0; width < (4 * png->m_width); width += 4){
                png->pixel_blue   = row_pointers[height][width + 2]; // blue
                png->pixel_green  = row_pointers[height][width + 1]; // green
                png->pixel_red    = row_pointers[height][width];   // red
                png->pixel_alpha  = row_pointers[height][width + 3]; // alpha
            }
        }
    }
    else if( png->num_channel == 3 ){
        for(int height = 0; height < png->m_height; height++){
            for(int width = 0; width < (4 * png->m_width); width += 4){
                png->pixel_blue   = row_pointers[height][width + 2]; // blue
                png->pixel_green  = row_pointers[height][width + 1]; // green
                png->pixel_red    = row_pointers[height][width];   // red
            }
        }
    }
    else{
        fprintf( stderr , "Wrong number of colour channels:%i",png->num_channel);
    }


    png_destroy_read_struct(&png_ptr, &info_ptr, 0);

    fclose(temp_png_file_ptr);

    return OK;

}