#ifndef SC3CHF_INIT_CMDCT
#define SC3CHF_INIT_CMDCT

#include "console_color.h"
#include "others.h"

#ifdef _WIN32
void cmd_text_col_init(){
    //将结构体视为数组
    flag8_t* ptr = (flag8_t*)&cmd_text_color;
    for( ushort8_t n = 0 ; n < sizeof(cmd_text_color) ; ++n ){
        ptr[n] = n;
    }
}
#else

void cmd_text_col_init(){
    cmd_text_color.none         =       "\e[0m"   ;
    cmd_text_color.black        =       "\e[0;30m";
    cmd_text_color.lightblack   =       "\e[1;30m";
    cmd_text_color.red          =       "\e[0;31m";
    cmd_text_color.lightred     =       "\e[1;31m";
    cmd_text_color.green        =       "\e[0;32m";
    cmd_text_color.acidgreen    =       "\e[1;32m";
    cmd_text_color.brown        =       "\e[0;33m";
    cmd_text_color.yellow       =       "\e[1;33m";
    cmd_text_color.blue         =       "\e[0;34m";
    cmd_text_color.acidblue     =       "\e[1;34m";
    cmd_text_color.purple       =       "\e[0;35m";
    cmd_text_color.lightpurple  =       "\e[1;35m";
    cmd_text_color.cyan         =       "\e[0;36m";
    cmd_text_color.lightcyan    =       "\e[1;36m";
    cmd_text_color.gray         =       "\e[0;37m";
    cmd_text_color.white        =       "\e[1;37m";
}

#endif //#ifdef _WIN32
#endif //#ifndef SC3CHF_CMDTC_INIT
