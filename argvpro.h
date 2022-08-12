#include <string.h>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include "defines.h"
#include "others.h"
#include "lang.h"

void test_arg( struct CovertOption* opt){
/*
    access(path,F_OK)
    Detect the existence of a file.
    0  = File exists
    !0 = File doesn't exist

*/
    if(!opt->input_path){
        put_err_msg(ERRMSG_ARG_IUNDEF);
        abort();
    }
     if(!opt->output_path){
        put_err_msg(ERRMSG_ARG_OUNDEF);
        abort();
    }

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

/*
    src (aka source)
    dst (aka destination)
*/
void arg_set_path( cstring src , cstring dst , cstring arg,
                    int* now_argc_ptr , const int* argc_ptr)
{
    if((*now_argc_ptr)+1 == *(argc_ptr)){
        put_err_msg(ERRMSG_ARG_LOSS,arg);
        abort();
    }
    dst = src;
    (*now_argc_ptr)++;
}


void  arg_processor( struct CovertOption* opt , const int argc ,  cstring* argv ){

    int now_argc                = 1     ;
    opt->temp_path              = NULL  ;
    opt->input_path             = NULL  ;
    opt->output_path            = NULL  ;
    opt->print_error_msg_only   = false ;
    opt->ramdom_color           = false ;
    opt->force_overwriting      = false ;


    if(argc==1){
        puts(INFO_ARG_DOHELP);
        exit(0);
    }

    while ( now_argc < argc ){

        if( (argv[now_argc][0] == '-' )&&(strlen(argv[now_argc])==2) ){
            switch( argv[now_argc][1] ){
                case 'i':
                    arg_set_path(argv[now_argc+1],opt->input_path,"-i",&now_argc,&argc);
                    continue;
                case 'o':
                    arg_set_path(argv[now_argc+1],opt->output_path,"-o",&now_argc,&argc);
                    continue;
                case 'y':
                    opt->force_overwriting = true ;
                    ++now_argc;
                    continue;
                case 't':
                    arg_set_path(argv[now_argc+1],opt->temp_path,"-t",&now_argc,&argc);
                    continue;
                case 'r':
                    opt->ramdom_color = true;
                    ++now_argc;
                    continue;
                case 'e':
                    opt->print_error_msg_only = true;
                    ++now_argc;
                    continue;
                case 'h':
                    do_help();
                    continue;
                default:
                    goto GOTOLAB_INVAILD_ARG;
            }
        }
        else{
            GOTOLAB_INVAILD_ARG:
                 put_err_msg( ERRMSG_ARG_INVAILD ,argv[now_argc] );
                 abort();
        }
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
