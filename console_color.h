/*
    console_color.h
    Change the font color in the console.

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

    console_color.h 改变控制台中字体颜色
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


#ifndef SC3CHF_CSC
#define SC3CHF_CSC

//For MSVC
#ifdef _MSC_VER
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
#endif //#ifdef _MSC_VER

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