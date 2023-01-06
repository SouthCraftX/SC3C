/*
    lang.h


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

    lang.h
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

#ifndef SC3CHF_LANG
#define SC3CHF_LANG
#define LANG_ZH_CN
#include "definations.h"


struct
{

    struct
    {
        ccstring_t invaild;
        ccstring_t bad_path;
        ccstring_t permission_denied;
        ccstring_t loss;
        ccstring_t input_path_undef;
        ccstring_t output_path_undef;
    } arg;

    struct
    {
        ccstring_t initdec;
        ccstring_t decode;
        ccstring_t read;
    } png;

    struct
    {
        ccstring_t clean_cache;
        ccstring_t open_zip;
        ccstring_t global_info;
        ccstring_t cur_file_info;
        ccstring_t cur_file_open;
        ccstring_t png_too_large;
        ccstring_t create_temp_file;
        ccstring_t write_temp_file;
        ccstring_t read_png;
    } unz;

    struct
    {
        ccstring_t coltm;
        ccstring_t create;
        ccstring_t write;
    } write_json;

} error_msg;

struct
{

    ccstring_t arg_do_help;
    ccstring_t ok;
    ccstring_t no_override;

    struct
    {
        ccstring_t initdec;
        ccstring_t alloc;
    } png;

    struct
    {
        ccstring_t clean_cache;
        ccstring_t open_zip;
        ccstring_t global_info;
        ccstring_t cur_file_info;
        ccstring_t cur_file_open;
    } unz;

} info_msg;

cstring_t banner_text,help_text,WARN_OVERRIDE;

#endif // #ifdef SC3CHF_LANG
