#ifndef SC3CHF_AUTOLANG
#define SC3CHF_AUTOLANG

#include "definations.h"
#include "init\set_lang.h"
#if 1
#include <windows.h>
#endif

extern convert_option_t opt;

lang_id_t get_sys_lang(){
    return (GetUserDefaultUILanguage() == 0x0804)?LANG_ZH:LANG_EN;
}

void lang_init(){
    if(get_sys_lang()==LANG_ZH){
        set_lang_zh();
    }
    else{
        set_lang_en();
    }
}

#endif // #ifndef SC3CHF_AUTOLANG