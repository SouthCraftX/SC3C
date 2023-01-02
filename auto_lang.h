#ifndef SC3CHF_AUTOLANG
#define SC3CHF_AUTOLANG

#include "definations.h"

#ifdef _WIN32
#include <winnls.h>
#endif

lang_id_t get_sys_lang(){
    LANGID lang = GetUserDefaultUILanguage();
    if(lang == 0x0804){
        
    }
}

#endif // #ifndef SC3CHF_AUTOLANG