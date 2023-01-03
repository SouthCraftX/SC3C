#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char get_sys_lang(){
    char* env = getenv("LANG");
    if(!env) return 0;
    return (!strncmp(env,"zh",(unsigned long)2))?1:0;
}

int main(){
    printf("%i\n",get_sys_lang());
}