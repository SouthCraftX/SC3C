/*
    auto_lang.h
    Try to get OS language, then select Chinese or English as the 
    language of the software.

[English]
    Copyright (C) <2023> <South Craft>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 3 as 
    published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License, version 3 for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Send an email to the following email address if you want to contact
    me: southcraft2007@gmail.com

[Chinese]
    注：如果中文版本与英文版本有出入，以英文版本为准

    auto_lang.h 尝试从系统获取语言消息，并选择中文或英文作文软件的语言
    版权所有（C）<2023> <South Craft>

　　本程序为自由软件，在自由软件联盟发布的GNU通用公共许可协议的约束下，你可以对其进行
    再发布及修改。协议版本为第三版。

    我们希望发布的这款程序有用，但不保证，甚至不保证它有经济价值和适合特定用途。详情
    参见GNU通用公共许可协议。

    你理当已收到一份GNU通用公共许可协议的副本，如果没有，请访问
    <http://www.gnu.org/licenses/>

    联系方式：[Gmail] southcraft2007@gmail.com

Completed in GMT+8 Jan 4th, 2023, 11:52 AM
*/


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

/*  
    @get_sys_lang() :   当语言是中文时返回LANG_ZH
                        不是中文或无法检测返回LANG_EN
*/
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
    cstring_t lang_token = getenv("LANG");
    if(!lang_token) return LANG_EN;
    return (!strncmp(lang_token,"zh",(ulong32_t)2))?LANG_ZH:LANG_EN;
}
#endif

void lang_init(){
    if(get_sys_lang()==LANG_ZH){
        set_lang_zh();
    }
    else{ set_lang_en(); }
}

#endif // #ifndef SC3CHF_AUTOLANG