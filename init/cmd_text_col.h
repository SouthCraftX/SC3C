/*
    cmd_text_col.h
    Construct the structure named cmd_text_color.

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

    cmd_text_col.h 构造cmd_text_color结构体
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
