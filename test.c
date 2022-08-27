#include <stdio.h>
#include <stdarg.h>

void put_err_msg( const char* formated_msg  , ...){
    va_list arg;
    va_start( arg , formated_msg );
    vfprintf( stderr , formated_msg , arg);
    va_end(arg);
}

int main(){

    put_err_msg( "Ptr=%p,Str=%s" , 0X8000 , "hi");

}