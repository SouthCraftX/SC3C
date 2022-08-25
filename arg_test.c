#include <stdio.h>
#include "argvpro.h"
#include <stdlib.h>
int main(long argn ,cstring* argv  ){

    for(long now = 0 ; now < argn , ++now ){
        printf("Arg %i:%s\n",now+1,argv[now]);
    }

    struct ConvertOption opt;
    arg_processor( argn , argv , opt );

    return 0;
}
