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


#ifdef LANG_ZH_CN

#define WARN_OVERRIDE ("警告：%s已存在，要覆盖它吗？(y/n)")
const char *banner_text = "South Craft颜色配置转换器\n"
                          "软件作者: South Craft\n"
                          "版本: SC3C Alpha 2.0\n"
                          "Github: https://github.com/SouthCraftX/SC3C\n";

const char *help_text = "使用方法: sc3c.exe -i <源文件路径> -o <J输出文件路径> [可选参数]\n\n"
                        "必填参数：\n"
                        "  -i\t指定UMP资源包路径\n"
                        "  -o\t指定输出JSON路径\n"
                        "可选参数：\n"
                        "  -h\t显示帮助页面（即本界面）\n"
                        "  -t\t指定临时文件路径\n"
                        "  -y\t若JSON已存在则直接覆盖\n"
                        "  -r\t随机颜色顺序（当前版本不可用）\n"
                        "  -e\t转换时仅显示错误信息\n";
#else

#define WARN_OVERRIDE ("Warning: %s is already exist.Override?(y/n):")

const char *banner_text = "SC3C\n"
                          "Author: South Craft\n"
                          "Version: SC3C Alpha 2.0\n"
                          "Github: https://github.com/SouthCraftX/SC3C";

const char *help_text = "\n\nUsage: sc3c.exe -i <path/to/zip> -o <path/to/json> [Optional Parameters]\n\n"
                        " Required Parameters:\n"
                        "  -i\tSpecifies the path to resourcepack.\n"
                        "  -o\tSpecifies the path to JSON file.\n"
                        " Optional Parameters:\n"
                        "  -t\tSpecifies the path to temporary file.\n"
                        "  -y\tOverwrite the JSON file without asking.\n"
                        "  -r\tRandomise the colour order.(Not available now)\n"
                        "  -e\tDon't show non-error messages while converting.\n";

#endif // #ifdef LANG_ZH_CN

#endif // #ifdef SC3CHF_LANG
