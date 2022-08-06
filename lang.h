#ifndef SC3CHF_LANG
#define SC3CHF_LANG

#define LANG_ZH_CN

#ifdef LANG_ZH_CN



#define INFO_UNZ_OPENZIP    ("[ZipArchive I/O]打开UMP资源包文件成功\n")
#define INFO_UNZ_GBINFO     ("[ZipArchive I/O]获取资源包全局信息成功\n")
#define INFO_UNZ_CTFINFO    ("[ZipArchive I/O]获取资源包内当前文件信息成功\n")
#define INFO_UNZ_CTFOPEN    ("[ZipArchive I/O]成功打开资源包内包含颜色配置信息的PNG文件\n")

#define ERRMSG_OWW_INPUT    ("输入错误！已取消文件文件覆盖！")
#define ERRMSG_ARG_INVAILD  ("[ArgProcessor]%s:无此参数！")
#define ERRMSG_ARG_IPATH    ("[ArgProcessor]%s:文件不存在！")
#define ERRMSG_ARG_PMDEN    ("[ArgProcessor]%s:拒绝访问！")

#define ERRMSG_UNZ_CLRCACHE ("[ZipArchive I/O]无法清理缓存，请手动删除%s")
#define ERRMSG_UNZ_OPENZIP  ("[ZipArchive I/O]%s:打开UMP资源包文件失败！\n")
#define ERRMSG_UNZ_GBINFO   ("[ZipArchive I/O]获取资源包全局信息失败！\n")
#define ERRMSG_UNZ_CTFINFO  ("[ZipArchive I/O]获取资源包内当前文件信息失败！\n")
#define ERRMSG_UNZ_CTFOPEN  ("[ZipArchive I/O]无法打开资源包内包含颜色配置信息的PNG文件！\n")
#define ERRMSG_UNZ_PNGTL    ("[ZipArchive I/O]包含颜色配置信息的PNG文件过大！其必须小于1MB！\n")
#define ERRMSG_UNZ_TMPCR    ("[File I/O]%s:无法创建临时文件！请重新指定临时文件路径！\n")
#define ERRMSG_UNZ_TMPFW    ("[File I/O]无法写入临时文件！\n")

#define ERRMSG_PNG_INITDEC ("[PNG Decoder]初始化ONG解码器失败！\n")

const char* banner_text ="SC3C的帮助页面\n"
                         "软件作者: South Craft\n"
                         "版本: SC3C Alpha 1.0\n"
                         "Built with GCC 11.2.0\n"
                         "Github: https://github.com/SouthCraftX/SC3C";

const char* help_text =  "使用方法: sc3c.exe -i <ZIP_PATH> -o <JSON_PATH> [OPTION]\n\n"
                         " -i\t指定UMP资源包路径\n"
                         " -o\t指定输出JSON路径\n"
                         " -t\t指定临时文件路径\n"
                         " -y\t若JSON已存在则直接覆盖\n"
                         " -r\t随机颜色顺序\n"
                         " -e\t转换时仅显示错误信息\n";
#else

#define ERRMSG_ARG_INVAILD  ("[ArgProcessor]%s:No such a argument!")
#define ERRMSG_ARG_IPATH    ("[ArgProcessor]%s:No such a file or directory.")
#define ERRMSG_ARG_PMDEN    ("[ArgProcessor]%s:Permission denied.")

#define ERRMSG_OWW_INPUT    ("Invalid input!File overwrite cancelled.")

#define ERRMSG_PNG_INITDEC  ("[PNG Decoder]Failed to initialise PNG decoder.\n")

#define ERRMSG_UNZ_CLRCACHE ("[ZipArchive I/O]Failed to clean cache,please delete %s.")
#define ERRMSG_UNZ_OPENZIP  ("[ZipArchive I/O]%s:Failed to open the zip file.")
#define ERRMSG_UNZ_GBINFO   ("[ZipArchive I/O]Failed to get golbal info of the zip file.")
#define ERRMSG_UNZ_CTFINFO  ("[ZipArchive I/O]Failed to get PNG file info.")
#define ERRMSG_UNZ_CTFOPEN  ("[ZipArchive I/O]Failed to open noteColors.png in the zip file.")
#define ERRMSG_UNZ_PNGTL    ("[ZipArchive I/O]PNG file is too large.")
#define ERRMSG_UNZ_TMPCR    ("[File I/O]%s:Failed to create temporary file.")
#define ERRMSG_UNZ_TMPFW    ("[File I/O]%s:Failed to write temporary file.Please secifies anothor ")

const char* banner_text ="Help Page of SC3C\n"
                         "Author: South Craft\n"
                         "Version: SC3C Alpha 1.0\n"
                         "Built with GCC 11.2.0\n"
                         "Github: https://github.com/SouthCraftX/SC3C";

const char* help_text =  "\n\nUsage: sc3c.exe -i <ZIP_PATH> -o <JSON_PATH> [OPTION]\n\n"
                         " -i\tSpecifies the path to resourcepack.\n"
                         " -o\tSpecifies the path to JSON file.\n"
                         " -t\tSpecifies the path to temporary file.\n"
                         " -y\tOverwrite the JSON file without asking.\n"
                         " -r\tRandomise the colour order.\n"
                         " -e\tDon't show non-error messages while converting.\n";

#endif

#endif