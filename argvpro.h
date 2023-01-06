/*
    argvpro.h 
    Process arguments from user.

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

    argvpro.h   处理来自用户的参数。
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


#include <string.h>
#if 0//#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include "definations.h"
#include "others.h"
#include "lang.h"

//For MSVC
#ifdef _MSC_VER
#pragma warning(disable : 4996)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif //#ifndef _CRT_SECURE_NO_WARNINGS
#endif //#ifdef _MSC_VER

extern convert_option_t opt;

void test_arg(){
/*
    access(path,F_OK)
    Detect the existence of a file.
    0  = File exists
    !0 = File doesn't exist

*/

    if(!opt.input_path)                            //检查源文件路径是否为空
        put_err_msg_abort( error_msg.arg.input_path_undef );
    if(!opt.output_path)                           //检查目标文件路径是否为空
        put_err_msg_abort( error_msg.arg.output_path_undef );  
    if(access(opt.input_path,F_OK))                //检查源文件路径是否存在
        put_err_msg_abort( error_msg.arg.bad_path , opt.input_path );
    if(access(opt.input_path,R_OK))                //检查源文件是否可读
        put_err_msg_abort( error_msg.arg.permission_denied , opt.input_path );
    if((!access(opt.output_path,F_OK))&&(!opt.force_overriding)){  //检查目标文件是否存在
        if(!file_exist_warning(opt.output_path))
            exit(0);
    }
    if(!opt.temp_path){                            //检查临时文件是否被指定
        remove(DEFAULT_CACHE_PATH);
        opt.temp_path = DEFAULT_CACHE_PATH;
        return;                                     //跳过剩余的临时文件路径检查
    }
    if((!access(opt.temp_path,F_OK))&&(!opt.force_overriding)){
        if(!file_exist_warning(opt.temp_path))
            exit(0);
    }

     //if(opt.show_opt) print_opt(opt);
}

/*
    src (aka source)
    dst (aka destination)
*/
void arg_set_path( cstring_t* src , cstring_t* dst , ccstring_t arg,
                    int* now_argc_ptr , const int* argc_ptr)
{
    if((*now_argc_ptr)+1 == *(argc_ptr))
        put_err_msg_abort( error_msg.arg.loss , arg );
    *dst = *src;
    (*now_argc_ptr)+=2;
}

void  arg_processor( const int argc ,  cstring_t* argv ){

    int now_argc                = 1     ;
    opt.temp_path              = NULL  ;
    opt.input_path             = NULL  ;
    opt.output_path            = NULL  ;
    opt.print_info_msg         = true  ;
    opt.ramdom_color           = false ;
    opt.force_overriding       = false ;
    opt.show_opt               = false ;

    if(argc==1){
        puts(info_msg.arg_do_help);
        exit(0);
    }

    while (now_argc<argc){

        if((argv[now_argc][0]=='-')&&(strlen(argv[now_argc])==2)){
            switch( argv[now_argc][1] ){
                case 'i':
                    arg_set_path(&argv[now_argc+1],&opt.input_path,"-i",&now_argc,&argc);
                    break;
                case 'o':
                    arg_set_path(&argv[now_argc+1],&opt.output_path,"-o",&now_argc,&argc);
                    break;
                case 'y':
                    opt.force_overriding = true ;
                    ++now_argc;
                    break;
                case 't':
                    arg_set_path(&argv[now_argc+1],&opt.temp_path,"-t",&now_argc,&argc);
                    break;
                case 'r':
                    opt.ramdom_color = true;
                    ++now_argc;
                    break;
                case 'e':
                    opt.print_info_msg = false;
                    ++now_argc;
                    break;
                case 'h':
                    do_help();
                    ++now_argc;
                    break;
                case 'p':
                    opt.show_opt = true;
                    ++now_argc;
                    break;
                default:
                    goto GOTOLAB_INVAILD_ARG;
            }
            continue;
        }
        else{
            goto GOTOLAB_INVAILD_ARG;
        }
        GOTOLAB_INVAILD_ARG:
            put_err_msg_abort(error_msg.arg.invaild,argv[now_argc]);
    }
/*
        if( !strcmp( argv[now_argc] , "-i" )){
            opt.input_path = argv[now_argc+1];
            now_argc+=2;
            continue;
        }
        if(!strcmp( argv[now_argc] , "-o" )){
            opt.output_path = argv[now_argc+1];
            now_argc+=2;
            continue;
        }
        if(!strcmp( argv[now_argc] , "-t" )){
            opt.output_path = argv[now_argc+1];
            now_argc+=2;
            continue;
        }
        if(!strcmp( argv[now_argc] , "-y" )){
            opt.force_overwriting = true ;
            ++now_argc;
            continue;
        }
        if(!strcmp( argv[now_argc] , "-r" )){
            opt.ramdom_color = true;
            ++now_argc;
            continue;
        }
        if(!strcmp( argv[now_argc] , "-e" )){
            opt.print_error_msg_only = true;
            continue;
        }

        put_err_msg( error_msg.ARG_INVAILD ,argv[now_argc] );
    }
*/
    test_arg( opt );
}
