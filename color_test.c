#include "console_color.h"
#include <stdio.h>

int main (){
    
    set_console_color(CSC_LIGHTRED);
    puts("ERROR\n");

    set_console_color(CSC_LIGHTYELLOW);
    puts("warning\n");

    set_console_color(CSC_WHITE);
    puts("INFO\n");
}