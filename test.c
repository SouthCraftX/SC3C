
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

    //arg_processor(argn,argc);

    opt.force_overriding = false;
    opt.ramdom_color     = false;
    opt.input_path       = "domino piano v1.6.zip";
    opt.temp_path        = "noteColors.png";
    opt.output_path      = "t2.json";

    unzipper();
    png_decoder();

    if(opt.ramdom_color)
        ramdom_color_order();

    export_to_json();

    destroy_pixel_memory();
}

