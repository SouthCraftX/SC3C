/*
    basic_types.h
    Define some basic types, such as byte_t.

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

    png_decoder.h 提供了一个使用libpng和zlib的PNG解码器
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


#ifndef SC3CHF_DEF_BTYPE
#define SC3CHF_DEF_BTYPE

#include <stdbool.h>    //bool,true,false
#include <stdint.h>     //int32_t,...


typedef     uint8_t     byte_t    ;
typedef     byte_t      ushort8_t ;
typedef     uint16_t    ushort16_t;
typedef     uint32_t    ulong32_t ;
typedef     uint64_t    ulong64_t ;

typedef     int8_t      short8_t  ;
typedef     int16_t     short16_t ;
typedef     int32_t     long32_t  ;
typedef     int64_t     long64_t  ;

typedef     uint8_t       flag8_t   ;
typedef     uint16_t      flag16_t  ;
typedef     ulong32_t     flag32_t  ;
typedef     ulong64_t     flag64_t  ;

typedef     char*         cstring_t ;
typedef     const char*   ccstring_t;

typedef     flag8_t       lang_id_t;


#endif //#ifndef SC3CHF_DEF_BTYPE