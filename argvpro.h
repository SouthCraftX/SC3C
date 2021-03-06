#include <string.h>
#include <io.h>
#include "defines.h"
#include "others.h"
#include "lang.h"

void test_arg( struct CovertOption* opt){

    if(access(opt->input_path,F_OK)){
        put_err_msg(ERRMSG_ARG_IPATH,opt->input_path);
        abort();
    }
    if(access(opt->input_path,R_OK)){
        put_err_msg(ERRMSG_ARG_PMDEN,opt->input_path);
        abort();
    }
    if((!access(opt->output_path,F_OK))&&(!opt->force_overwriting)){
        if(!file_exist_warning(opt->output_path))
            exit();
    }
    if((!access(opt->temp_path,F_OK))&&(!opt->force_overwriting)){
        if(!file_exist_warning(opt->temp_path))
            exit();
    }
    if(opt->temp_path == NULL){
        opt->temp_path = tmpnam();
    }

}


int arg_processor( struct CovertOption* opt , const long argc ,  cstring* argv ){

    int now_argc                = 1     ;
    opt->temp_path              = NULL  ;
    opt->input_path             = NULL  ;
    opt->output_path            = NULL  ;
    opt->print_error_msg_only   = false ;
    opt->ramdom_color           = false ;
    opt->force_overwriting      = false ;

    while ( now_argc < argc ){
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
        put_err_msg( ERRMSG_ARG_INVAILD );
    }
    
}