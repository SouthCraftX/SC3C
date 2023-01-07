/*
    main.c Main Program

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

    main.c 主程序
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

//For MSVC
#ifdef _MSC_VER
#pragma warning(disable : 4996)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif //#ifndef _CRT_SECURE_NO_WARNINGS
#endif //#ifdef _MSC_VER

#include <stdio.h>
#include <stdlib.h>
#include <zip.h>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

#include <time.h>
#include <stdbool.h>

#include "console_color.h"
#include "definations.h"

#include "argvpro.h"
#include "png_unzipper.h"
#include "png_decoder.h"
#include "ramdom_color_order.h"
#include "init.h"

convert_option_t opt;
png_data_t png;

int main( int argn , char* argc[]  ){

    init();
    do_banner();

    //懒得单独写一个构造函数了，就直接在main()里写吧
    {
	    png.row_ptr = NULL;
	    png.width   = 0;
    	png.height  = 0;
    }

    arg_processor(argn,argc);
    unzipper();
    png_decoder();

    if(opt.ramdom_color)
        ramdom_color_order();

    export_to_json();

    destroy_pixel_memory();
}

