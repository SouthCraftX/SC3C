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
            exit(0);
    }
    if((!access(opt->temp_path,F_OK))&&(!opt->force_overwriting)){
        if(!file_exist_warning(opt->temp_path))
            exit(0);
    }
    if(opt->temp_path == NULL){
        opt->temp_path = tmpnam(NULL);
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

        if( (argv[now_argc][0] == '-' )&&(strlen(argv[now_argc]==2))){
            switch( argv[now_argc][1] ){
                case 'i':
                    opt->input_path = argv[now_argc+1];
                    now_argc+=2;
                    break;
                case 'o':
                    opt->output_path = argv[now_argc+1];
                    now_argc+=2;
                    break;
                case 'y':
                    opt->force_overwriting = true ;
                    ++now_argc;
                    break;
                case 't':
                    opt->output_path = argv[now_argc+1];
                    now_argc+=2;
                    break;
                case 'r':
                     opt->ramdom_color = true;
                    ++now_argc;
                    break;
                case 'e':
                    opt->print_error_msg_only = true;
                    break;
                default:
                    goto GOTOLAB_INVAILD_ARG;
            }
        }
        else{
            GOTOLAB_INVAILD_ARG:
                 put_err_msg( ERRMSG_ARG_INVAILD ,argv[now_argc] );
                 abort();
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

        put_err_msg( ERRMSG_ARG_INVAILD ,argv[now_argc] );
    }
*/
    test_arg( opt );
}