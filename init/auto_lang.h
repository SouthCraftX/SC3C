#ifndef SC3CHF_AUTOLANG
#define SC3CHF_AUTOLANG

#include "definations.h"
#include "init\set_lang.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <stdlib.h>
#include <string.h>
#endif

extern convert_option_t opt;

#ifdef _WIN32
lang_id_t get_sys_lang(){
    LANGID lang = GetUserDefaultUILanguage();
    return ((lang == 0x0804)||(lang == 0x1004))?LANG_ZH:LANG_EN;
    // 0x0804 ZH_CN 中文（中国）
    // 0x1004 ZH_SG 中文（新加坡）
}
#else
lang_id_t get_sys_lang(){
    //简体中文系统上：zh_CN.UTF-8
    return (!strncmp(getenv("LANG"),"zh",(ulong32_t)2))?LANG_ZH:LANG_EN;
}
#endif

void lang_init(){
    if(get_sys_lang()==LANG_ZH){
        set_lang_zh();
    }
    else{ set_lang_en(); }
}

#endif // #ifndef SC3CHF_AUTOLANG