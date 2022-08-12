#ifndef SC3CHF_LANG
#define SC3CHF_LANG

#define LANG_ZH_CN

#ifdef LANG_ZH_CN



#define INFO_ARG_DOHELP ("未指定任何参数，请用'-h'参数以查看命令用法")

#define INFO_UNZ_OPENZIP    ("[ZipArchive I/O]打开UMP资源包文件成功\n")
#define INFO_UNZ_GBINFO     ("[ZipArchive I/O]获取资源包全局信息成功\n")
#define INFO_UNZ_CTFINFO    ("[ZipArchive I/O]获取资源包内当前文件信息成功\n")
#define INFO_UNZ_CTFOPEN    ("[ZipArchive I/O]成功打开资源包内包含颜色配置信息的PNG文件\n")
#define INFO_UNZ_CLEAN      ("[ZipArchive I/O]已清除清理缓存\n")

#define INFO_PNG_ALLOC      ("[PNG Decoder]成功为像素数据分配内存\n")

#define ERRMSG_OWW_INPUT    ("输入错误！已取消文件文件覆盖！\n")
#define ERRMSG_ARG_INVAILD  ("[ArgProcessor]%s:无此参数！\n")
#define ERRMSG_ARG_IPATH    ("[ArgProcessor]%s:文件不存在！\n")
#define ERRMSG_ARG_PMDEN    ("[ArgProcessor]%s:拒绝访问！\n")
#define ERRMSG_ARG_LOSS     ("[Arg Processor]%i:指令不完整!\n")
#define ERRMSG_ARG_IUNDEF   ("[Arg Processor]未指定源文件!\n")
#define ERRMSG_ARG_OUNDEF   ("[Arg Processor]未指定输出文件!\n")

#define ERRMSG_UNZ_CLRCACHE ("[ZipArchive I/O]无法清理缓存，请手动删除%s.\n")
#define ERRMSG_UNZ_OPENZIP  ("[ZipArchive I/O]%s:打开UMP资源包文件失败！\n")
#define ERRMSG_UNZ_GBINFO   ("[ZipArchive I/O]获取资源包全局信息失败！\n")
#define ERRMSG_UNZ_CTFINFO  ("[ZipArchive I/O]获取资源包内当前文件信息失败！\n")
#define ERRMSG_UNZ_CTFOPEN  ("[ZipArchive I/O]无法打开资源包内包含颜色配置信息的PNG文件！\n")
#define ERRMSG_UNZ_PNGTL    ("[ZipArchive I/O]包含颜色配置信息的PNG文件过大！其必须小于1MB！\n")
#define ERRMSG_UNZ_TMPCR    ("[File I/O]%s:无法创建临时文件！请重新指定临时文件路径！\n")
#define ERRMSG_UNZ_TMPFW    ("[File I/O]%s:无法写入临时文件！\n")

#define ERRMSG_OUT_COLTM    ("[JSONExporter]颜色配置太多！颜色数量最多为655,35种！\n")
#define ERRMSG_OUT_WRITR    ("[JSONExporter]写入JSON文件失败！\n")

#define ERRMSG_PNG_INITDEC ("[PNG Decoder]初始化ONG解码器失败！\n")


const char* banner_text ="South Craft颜色配置转换器\n"
                         "软件作者: South Craft\n"
                         "版本: SC3C Alpha 1.0\n"
                         "Github: https://github.com/SouthCraftX/SC3C\n";

const char* help_text =  "使用方法: sc3c.exe -i <源文件路径> -o <J输出文件路径> [可选参数]\n\n"
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

#define INFO_ARG_DOHELP ("Run 'SC3C -h' to get help.\n")

#define INFO_PNG_INITDEC    ("[PNG Decoder]Succeed to initialise PNG decoder.\n")

#define IBFO_UNZ_CLRCACHE   ("[Zip Archive I/O]Succeed to clean cache.\n")
#define INFO_UNZ_OPENZIP    ("[Zip Archive I/O]Succeed to open %s.\n")
#define INFO_UNZ_GBINFO     ("[Zip Archive I/O]Succeed to get global info of &s.\n")

#define INFO_PNG_ALLOC      ("[PNG Decoder]Succeed to allocate memory for pixel data.")


#define ERRMSG_ARG_INVAILD  ("[ArgProcessor]%s:No such a argument!\n")
#define ERRMSG_ARG_IPATH    ("[ArgProcessor]%s:No such a file or directory.\n")
#define ERRMSG_ARG_PMDEN    ("[ArgProcessor]%s:Permission denied.\n")
#define ERRMSG_ARG_LOSS     ("[Arg Processor]%i:Argument loss.\n")

#define ERRMSG_OWW_INPUT    ("Invalid input!File overwrite cancelled.\n")

#define ERRMSG_PNG_INITDEC  ("[PNG Decoder]Failed to initialise PNG decoder.\n")

#define ERRMSG_UNZ_CLRCACHE ("[ZipArchive I/O]Failed to clean cache,please delete %s.\n")
#define ERRMSG_UNZ_OPENZIP  ("[ZipArchive I/O]%s:Failed to open the zip file.\n")
#define ERRMSG_UNZ_GBINFO   ("[ZipArchive I/O]Failed to get global info of %s\n")
#define ERRMSG_UNZ_CTFINFO  ("[ZipArchive I/O]Failed to get PNG file info.\n")
#define ERRMSG_UNZ_CTFOPEN  ("[ZipArchive I/O]Failed to open noteColors.png in the zip file.\n")
#define ERRMSG_UNZ_PNGTL    ("[ZipArchive I/O]PNG file is too large.\n")
#define ERRMSG_UNZ_TMPCR    ("[File I/O]%s:Failed to create temporary file.\n")
#define ERRMSG_UNZ_TMPFW    ("[File I/O]%s:Failed to write temporary file.Please secifies anothor path. \n")

#define ERRMSG_OUT_COLTM    ("[JSONExporter]颜色配置太多！颜色数量最多为655,35种！\n")
#define ERRMSG_OUT_WRITR    ("[JSONExporter]%s:Failed to write the JSON file.\n")

const char* banner_text ="SC3C\n"
                         "Author: South Craft\n"
                         "Version: SC3C Alpha 1.0\n"
                         "Github: https://github.com/SouthCraftX/SC3C";

const char* help_text =  "\n\nUsage: sc3c.exe -i <path/to/zip> -o <path/to/json> [OPTION]\n\n"
                         " -i\tSpecifies the path to resourcepack.\n"
                         " -o\tSpecifies the path to JSON file.\n"
                         " -t\tSpecifies the path to temporary file.\n"
                         " -y\tOverwrite the JSON file without asking.\n"
                         " -r\tRandomise the colour order.\n"
                         " -e\tDon't show non-error messages while converting.\n";

#endif

#endif
