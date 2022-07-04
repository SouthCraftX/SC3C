#include <zlib.h>
#include <stdio.h>
#include <minizip\zip.h>
#include <minizip\unzip.h>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

#define  MAX_PATH_LEN (260)
#define PATH_TO_UNZIP (".\\SC3C_TEMP\\noteColor.png")
typedef unsigned char byte;

size_t writepng( void* buffer , size_t nwrite ,FILE* stream  ){
#ifdef USE_UNLOCKED_FWRITE
    return _fwrite_nolock( buffer , nwrite , 1 ,stream );
#else
    return fwrite( buffer , nwrite , 1 ,stream );
#endif
}

int strcmp_ignore_case( const char* str_x , const char* str_y ){
#ifdef _WIN32
    return stricmp( str_x , str_y );
#else
    return strcasecmp( str_x , str_y );
#endif
}

void clean_cache(){
    if(access( PATH_TO_UNZIP , 0 )==F_OK){
        if(remove( PATH_TO_UNZIP ))
            QUITMSG("Failed to clean cache.");
    }
}

//Print a error message and exit.
inline void QUITMSG( const char* msg ){
    fprintf( stderr , msg );
    exit();
}

int main(){

    //char* zip_path;
    int error_code = ZIP_ERRNO;
    unzFile zipfile =  NULL;
    unz_global_info64 global_info;
    unz_file_info64 file_info;
    char fname_in_zip[MAX_PATH_LEN];
    memset( fname_in_zip , 0 , sizeof(fname_in_zip));

    unzFile zipfile =  unzOpen64( "MidiVoyager.zip");

    clean_cache();
    if( zipfile == NULL ) 
        QUITMSG("Failed to open the zip.");

    if(unzGetGlobalInfo64( zipfile , &global_info ) != UNZ_OK )
        QUITMSG("Failed to get golbal info.");

    int gonext_ret = unzGoToFirstFile( zipfile );

    while( gonext_ret == UNZ_OK ){
        if(unzGetCurrentFileInfo64( zipfile , &file_info , fname_in_zip , sizeof(fname_in_zip) , NULL , 0 , NULL , 0 )!= UNZ_OK)
            QUITMSG( "Failed to get current file info.");

        if(strcmp_ignore_case(fname_in_zip , "noteColor.png")) 
            goto GOTOLAB_NEXTFILE;

        if(unzOpenCurrentFile( zipfile ) != UNZ_OK)
            QUITMSG( "Failed to open noteColor.png." );

        if( file_info.uncompressed_size > 1024*1024 )
            QUITMSG(" PNG file is too large.");

        byte* io_buffer = NULL;
        io_buffer = (byte*)malloc( file_info.uncompressed_size );
        if( io_buffer == NULL )
            QUITMSG( "Failed to allocate memory for unziping.");
        
        size_t read_n = 0;
        read_n =  unzReadCurrentFile( zipfile , io_buffer , file_info.uncompressed_size );
        if( read_n < file_info.uncompressed_size)
            QUITMSG(" Error size.");

        FILE* write_png_fptr = fopen( PATH_TO_UNZIP , "wb" );
        if( write_png_fptr == NULL)
            QUITMSG( "Failed to create temporary file." );

        if( !writepng( io_buffer , file_info.uncompressed_size , write_png_fptr ))
            QUITMSG( "Failed to write temporary file." );
    

        break;
        GOTOLAB_NEXTFILE:
            gonext_ret = unzGoToNextFile( zipfile );
        }


    }
    



