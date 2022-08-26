#include "defines.h"

#ifdef _WIN32

#include <windows.h>

enum {
    CSC_BLACK =0,
    CSC_BLUE,
    CSC_GREEN,
    CSC_ACIDBLUE,
    CSC_RED,
    CSC_PURPLE,
    CSC_YELLOW,
    CSC_WHITE,
    CSC_GREY,
    CSC_BABYBLUE,
    CSC_ACIDGREEN,
    CSC_LIGHTGREEEN,
    CSC_LIGHTRED,
    CSC_LIGHTPURPLE,
    CSC_LIGHTYELLOW,
    CSC_LIGHTWHITE
} console_color;

void set_console_color( flag8 color ){
    SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE) , color);
}
#else

#define CSC_NONE                 "\e[0m"
#define CSC_BLACK                "\e[0;30m"
#define CSC_LIGHTBLACK           "\e[1;30m"
#define CSC_RED                  "\e[0;31m"
#define CSC_LIGHTRED             "\e[1;31m"
#define CSC_GREEN                "\e[0;32m"
#define CSC_ACIDGREEN            "\e[1;32m"
#define CSC_BROWN                "\e[0;33m"
#define CSC_YELLOW               "\e[1;33m"
#define CSC_BLUE                 "\e[0;34m"
#define CSC_ACIDBLUE             "\e[1;34m"
#define CSC_PURPLE               "\e[0;35m"
#define CSC_LIGHTPURPLE          "\e[1;35m"
#define CSC_CYAN                 "\e[0;36m"
#define CSC_LIGHTCYAN            "\e[1;36m"
#define CSC_GRAY                 "\e[0;37m"
#define CSC_WHITE                "\e[1;37m"

void set_console_color( ccstring color ){
    puts(color);
}
#endif