#include <string.h>
#if 0//#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include "definations.h"
#include "others.h"
#include "lang.h"

void test_arg( struct ConvertOption* opt){
/*
    access(path,F_OK)
    Detect the existence of a file.
    0  = File exists
    !0 = File doesn't exist

*/

    if(!opt->input_path)                            //检查源文件路径是否为空
        put_err_msg_abort( error_msg.arg.input_path_undef );
    if(!opt->output_path)                           //检查目标文件路径是否为空
        put_err_msg_abort( error_msg.arg.output_path_undef );  
    if(access(opt->input_path,F_OK))                //检查源文件路径是否存在
        put_err_msg_abort( error_msg.arg.bad_path , opt->input_path );
    if(access(opt->input_path,R_OK))                //检查源文件是否可读
        put_err_msg_abort( error_msg.arg.permission_denied , opt->input_path );
    if((!access(opt->output_path,F_OK))&&(!opt->force_overriding)){  //检查目标文件是否存在
        if(!file_exist_warning(opt->output_path))
            exit(0);
    }
    if(!opt->temp_path){                            //检查临时文件是否被指定
        remove(DEFAULT_CACHE_PATH);
        opt->temp_path = DEFAULT_CACHE_PATH;
        return;                                     //跳过剩余的临时文件路径检查
    }
    if((!access(opt->temp_path,F_OK))&&(!opt->force_overriding)){
        if(!file_exist_warning(opt->temp_path))
            exit(0);
    }

     //if(opt->show_opt) print_opt(opt);
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

void  arg_processor( struct ConvertOption* opt , const int argc ,  cstring_t* argv ){

    int now_argc                = 1     ;
    opt->temp_path              = NULL  ;
    opt->input_path             = NULL  ;
    opt->output_path            = NULL  ;
    opt->print_info_msg         = true  ;
    opt->ramdom_color           = false ;
    opt->force_overriding       = false ;
    opt->show_opt               = false ;

    if(argc==1){
        puts(info_msg.arg_do_help);
        exit(0);
    }

    while (now_argc<argc){

        if((argv[now_argc][0]=='-')&&(strlen(argv[now_argc])==2)){
            switch( argv[now_argc][1] ){
                case 'i':
                    arg_set_path(&argv[now_argc+1],&opt->input_path,"-i",&now_argc,&argc);
                    break;
                case 'o':
                    arg_set_path(&argv[now_argc+1],&opt->output_path,"-o",&now_argc,&argc);
                    break;
                case 'y':
                    opt->force_overriding = true ;
                    ++now_argc;
                    break;
                case 't':
                    arg_set_path(&argv[now_argc+1],&opt->temp_path,"-t",&now_argc,&argc);
                    break;
                case 'r':
                    opt->ramdom_color = true;
                    ++now_argc;
                    break;
                case 'e':
                    opt->print_info_msg = false;
                    ++now_argc;
                    break;
                case 'h':
                    do_help();
                    ++now_argc;
                    break;
                case 'p':
                    opt->show_opt = true;
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
            opt->input_path = argv[now_argc+1];
            now_argc+=2;
            continue;
        }
        if(!strcmp( argv[now_argc] , "-o" )){
            opt->output_path = argv[now_argc+1];
            now_argc+=2;
            continue;
        }
        if(!strcmp( argv[now_argc] , "-t" )){
            opt->output_path = argv[now_argc+1];
            now_argc+=2;
            continue;
        }
        if(!strcmp( argv[now_argc] , "-y" )){
            opt->force_overwriting = true ;
            ++now_argc;
            continue;
        }
        if(!strcmp( argv[now_argc] , "-r" )){
            opt->ramdom_color = true;
            ++now_argc;
            continue;
        }
        if(!strcmp( argv[now_argc] , "-e" )){
            opt->print_error_msg_only = true;
            continue;
        }

        put_err_msg( error_msg.ARG_INVAILD ,argv[now_argc] );
    }
*/
    test_arg( opt );
}
