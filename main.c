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
    export_to_json();

    destroy_pixel_memory();
}

