#ifndef SC3CHF_OTHERS
#define SC3CHF_OTHERS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Print a error message and exit.
 void QUITMSG( char* msg ){
    fprintf( stderr , msg );
    exit(-1);
}


size_t fwriter( void* buffer , size_t nwrite ,size_t ncount ,FILE* stream  ){
#ifdef USE_UNLOCKED_FWRITE
    return _fwrite_nolock( buffer , nwrite , ncount ,stream );
#else
    return fwrite( buffer , nwrite , ncount ,stream );
#endif
}

int strcmp_ignore_case( const char* str_x , const char* str_y ){
#ifdef _WIN32
    return stricmp( str_x , str_y );
#else
    return strcasecmp( str_x , str_y );
#endif
}


#endif