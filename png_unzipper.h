#include <zlib.h>
#include <stdio.h>
#include <minizip\zip.h>
#include <minizip\unzip.h>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

void clean_cache(){
    if(access( PATH_TO_UNZIP , 0 )==F_OK){
        if(remove( PATH_TO_UNZIP ))
            QUITMSG("Failed to clean cache.");
    }
}

int unzipper(
    const char* zip_path,
    const char* temp_path,
    int no_cleaning
){
    //char* zip_path;
    byte io_buffer[BUFFER_SIZE] ;
    unzFile zipfile =  NULL;
    unz_global_info64 global_info;
    unz_file_info64 file_info;
    char fname_in_zip[MAX_PATH_LEN];
    memset( fname_in_zip , 0 , sizeof(fname_in_zip));

    zipfile =  unzOpen64( zip_path );

    clean_cache();
    if( zipfile == NULL ) 
        QUITMSG("Failed to open the zip.");

    if(unzGetGlobalInfo64( zipfile , &global_info ) != UNZ_OK )
        QUITMSG("Failed to get golbal info.");

    int gonext_ret = unzGoToFirstFile( zipfile );

    while( gonext_ret == UNZ_OK ){
        if(unzGetCurrentFileInfo64( zipfile , &file_info , fname_in_zip , sizeof(fname_in_zip) , NULL , 0 , NULL , 0 )!= UNZ_OK)
            QUITMSG( "Failed to get current file info.");

        if(strcmp_ignore_case(fname_in_zip , "noteColors.png")) 
            goto GOTOLAB_NEXTFILE;

        if(unzOpenCurrentFile( zipfile ) != UNZ_OK)
            QUITMSG( "Failed to open noteColors.png." );

        if( file_info.uncompressed_size > 1024*1024 )
            QUITMSG(" PNG file is too large.");

        break;
        GOTOLAB_NEXTFILE:
            gonext_ret = unzGoToNextFile( zipfile );
    }
    memset( io_buffer , 0 , BUFFER_SIZE );
           
    FILE* write_png_fptr;
    if( fopen_s(&write_png_fptr , PATH_TO_UNZIP , "wb" ))
        QUITMSG( "Failed to create temporary file.");

    int read_n = 0;
    for(int remain_size = file_info.uncompressed_size ; remain_size>0 ; remain_size-= BUFFER_SIZE ){
        read_n =  unzReadCurrentFile( zipfile , io_buffer , BUFFER_SIZE );
        fwriter( io_buffer , read_n , 1 , write_png_fptr );
    }
    unzCloseCurrentFile( zipfile );
    unzClose( zipfile );

    if(!no_cleaning) 
        clean_cache();
            //for( int l = 0; l< file_info.uncompressed_size ; ++l){
        //    printf("%c ",*(io_buffer+l));
        //}

        //if( !writepng( io_buffer , file_info.uncompressed_size ,1, write_png_fptr ))
           // QUITMSG( "Failed to write temporary file." );
    
        //size_t write_ret = writepng( io_buffer , file_info.uncompressed_size , 1, write_png_fptr );
        return 0;
    }
    



