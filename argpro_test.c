#include <stdio.h>
#include "argvpro.h"

int main( int argn , char** argv ){
    printf("Number of arguments:%i\n" , argn );
    for(int now = 0 ; now < argn ; ++ now ){
        printf("1: %s\n",argv[now]);
    }
    struct CovertOption opt;
    arg_processor(&opt,argn,argv);
    return 0;
}
