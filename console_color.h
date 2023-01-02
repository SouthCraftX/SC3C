#ifndef SC3CHF_CSC
#define SC3CHF_CSC


#include "definations.h"
//CSC (aka Console Color)
#ifdef _WIN32

#include <windows.h>

struct {
    flag8_t black;
    flag8_t blue;
    flag8_t green;
    flag8_t acidblue; 
    flag8_t red;
    flag8_t purple; 
    flag8_t yellow;
    flag8_t white;
    flag8_t grey;
    flag8_t babyblue; 
    flag8_t acidgreen; 
    flag8_t lightgreeen; 
    flag8_t lightred;
    flag8_t lightpurple; 
    flag8_t lightyellow;
    flag8_t lightwhit;
} cmd_text_color;

#define set_console_color( color )(\
    SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE) , color)\
)
#else

struct {
    ccstring_t none        ;
    ccstring_t black       ;
    ccstring_t lightblack  ;
    ccstring_t red         ;
    ccstring_t lightred    ;
    ccstring_t green       ;
    ccstring_t acidgreen   ;
    ccstring_t brown       ;
    ccstring_t yellow      ;
    ccstring_t blue        ;
    ccstring_t acidblue    ;
    ccstring_t purple      ;
    ccstring_t lightpurple ;
    ccstring_t cyan        ;
    ccstring_t lightcyan   ;
    ccstring_t gray        ;
    ccstring_t white       ;
} cmd_text_color;

#define set_console_color( color )(\
    puts(color)\
)
#endif

#endif