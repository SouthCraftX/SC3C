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

ccstring_t banner_text,help_text,WARN_OVERRIDE;

#endif // #ifdef SC3CHF_LANG
