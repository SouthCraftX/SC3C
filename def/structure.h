/*
    structure.h
    Define some structures.

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

    structure.h 定义了一些结构体
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

#ifndef SC3CHF_DEF_STRUCT
#define SC3CHF_DEF_STRUCT

#include "def\basic_types.h"

struct ConvertOption {
    bool  print_info_msg : 1;
    bool  force_overriding : 1;
    bool  ramdom_color : 1;
    bool  save_tmp_file : 1;
    bool  hide_banner : 1;
    char* input_path;
    char* output_path;
    char* temp_path;
    //bool  show_opt : 1 ;   
};


struct PNGData {
    byte_t**  row_ptr ;
    ulong32_t height;
    ulong32_t width;
};

typedef struct ConvertOption    convert_option_t;
typedef struct PNGData          png_data_t;       

#endif //#ifndef SC3CHF_DEF_STRUCT