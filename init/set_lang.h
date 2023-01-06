/*
    png_decoder.h 
    Provide a PNG decoder using libpng and zlib.

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

    png_decoder.h 提供了一个使用libpng和zlib的PNG解码器
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


#ifndef SC3CHF_INIT_LANG
#define SC3CHF_INIT_LANG
#include "lang.h"
//#include "init\auto_lang.h"

void set_lang_zh(){

    info_msg.unz.clean_cache    =  "清理缓存...";
    info_msg.unz.open_zip       =  "打开源文件...";
    info_msg.unz.global_info    =  "获取源文件的全局信息...";
    info_msg.unz.cur_file_info  =  "获取UMP颜色配置文件信息...";
    info_msg.unz.cur_file_open  =  "打开UMP颜色配置文件...";

    info_msg.arg_do_help        =  "运行'SC3C -h'以获得帮助页面\n";
    info_msg.ok                 =  "成功\n";
    info_msg.no_override        =  "已取消文件覆盖，SC3C正在退出...\n";

    info_msg.png.initdec        =  "初始化PNG解码器...\n";
    info_msg.png.alloc          =  "为解码后数据分配内存...\n";

    error_msg.write_json.coltm   =   "颜色配置太多！颜色数量最多为655,35种！\n";
    error_msg.write_json.create  =   "%s:无法创建JSON文件！";
    error_msg.write_json.write   =   "%s:无法写入JSON文件！\n";

    error_msg.unz.clean_cache        =   "%s:清理缓存失败！\n";
    error_msg.unz.open_zip           =   "%s:无法打开源文件\n";
    error_msg.unz.global_info        =   "%s:无法获取源文件的全局信息！\n";
    error_msg.unz.cur_file_info      =   "无法获得PNG文件的全局信息！\n";
    error_msg.unz.cur_file_open      =   "无法打开源文件中的颜色配置文件！\n";
    error_msg.unz.png_too_large      =   "PNG文件过大！\n";
    error_msg.unz.create_temp_file   =   "%s:创建临时文件失败！\n";
    error_msg.unz.write_temp_file    =   "%s:写入临时文件失败！\n";
    error_msg.unz.read_png           =   "读取PNG信息失败！\n";

    error_msg.png.initdec    =   "初始化PNG解码器失败！\n";
    error_msg.png.decode     =   "解码PNG时发生错误！\n";
    error_msg.png.read       =   "创建临时文件失败！";

    error_msg.arg.invaild                 =   "%s:无此参数！\n";
    error_msg.arg.bad_path                =   "%s:没有那个文件或目录！\n";
    error_msg.arg.permission_denied       =   "%s:拒绝访问！\n";
    error_msg.arg.loss                    =   "%i:参数缺失！\n";
    error_msg.arg.input_path_undef        =   "未指定源文件路径！\n";
    error_msg.arg.output_path_undef       =   "未指定输出文件路径！\n";

    banner_text =   "South Craft颜色配置转换器\n"
                    "软件作者: South Craft\n"
                    "版本: SC3C Alpha 3.2\n"
                    "Github: https://github.com/SouthCraftX/SC3C\n"
                    "这是在GNU通用公共许可证第三版下的自由软件。在此许可证下，允许您在下自由地分发、修改、使用这款软件。\n"
                    "欲了解更多，请访问：https://www.gnu.org/licenses/gpl-3.0.en.html";

    help_text = "使用方法: sc3c.exe -i <源文件路径> -o <输出文件路径> [可选参数]\n\n"
                "必填参数：\n"
                "  -i\t指定UMP资源包路径\n"
                "  -o\t指定输出JSON路径\n"
                "可选参数：\n"
                "  -h\t显示帮助页面（即本界面）\n"
                "  -t\t指定临时文件路径\n"
                "  -y\t若JSON已存在则直接覆盖\n"
                "  -r\t随机颜色顺序（当前版本不可用）\n"
                "  -e\t转换时仅显示错误信息\n";

    WARN_OVERRIDE  = "警告：%s已存在，要覆盖它吗？(y/n)：";
}

void set_lang_en(){

    info_msg.unz.clean_cache    =  "Cleaning cache ...";
    info_msg.unz.open_zip       =  "Opening the source file ...";
    info_msg.unz.global_info    =  "Getting the global info of the source file ...";
    info_msg.unz.cur_file_info  =  "Getting the info of noteColors.png ...";
    info_msg.unz.cur_file_open  =  "Opening noteColors.png ...";

    info_msg.arg_do_help        =  "Run 'SC3C -h' to get help.\n";
    info_msg.ok                 =  "OK\n";
    info_msg.no_override        =  "No override.Exiting ...\n";

    info_msg.png.initdec        =  "Succeed to initialise PNG decoder.\n";
    info_msg.png.alloc          =  "Succeed to allocate memory for pixel data.\n";



    error_msg.write_json.coltm   =   "颜色配置太多！颜色数量最多为655,35种！\n";
    error_msg.write_json.create  =   "%s:Failed to create JSON file.";
    error_msg.write_json.write   =   "%s:Failed to write the JSON file.\n";

    error_msg.unz.clean_cache        =   "Failed to clean cache,please delete %s.\n";
    error_msg.unz.open_zip           =   "%s:Failed to open the zip file.\n";
    error_msg.unz.global_info        =   "Failed to get global info of %s\n";
    error_msg.unz.cur_file_info      =   "Failed to get PNG file info.\n";
    error_msg.unz.cur_file_open      =   "Failed to open noteColors.png in the zip file.\n";
    error_msg.unz.png_too_large      =   "PNG file is too large.\n";
    error_msg.unz.create_temp_file   =   "%s:Failed to create temporary file.\n";
    error_msg.unz.write_temp_file    =   "%s:Failed to write temporary file.\n";
    error_msg.unz.read_png           =   "Failed to read the colour configure from the resource pack!\n";

    error_msg.png.initdec    =   "Failed to initialise PNG decoder.\n";
    error_msg.png.decode     =   "An error occurred while decoding the PNG.\n";
    error_msg.png.read       =   "Failed to read temperory file.";

    error_msg.arg.invaild                 =  "%s:No such a argument!\n";
    error_msg.arg.bad_path                =   "%s:No such a file or directory.\n";
    error_msg.arg.permission_denied       =   "%s:Permission denied.\n";
    error_msg.arg.loss                    =   "%i:Argument loss.\n";
    error_msg.arg.input_path_undef        =   "Source file is not specifiesed!\n";
    error_msg.arg.output_path_undef       =   "Output file is not specifiesed!\n";

    banner_text =   "SC3C\n"
                    "Author: South Craft\n"
                    "Version: SC3C Alpha 3.2\n"
                    "Github: https://github.com/SouthCraftX/SC3C"
                    "This is free software under the GNU General Public License v3."
                    "You are allowed to freely distribute, modify, and use the software under this license."
                    "Visit the following website to learn more:"
                    "https://www.gnu.org/licenses/gpl-3.0.en.html";

    help_text   =   "\n\nUsage: sc3c.exe -i <path/to/zip> -o <path/to/json> [Optional Parameters]\n\n"
                    " Required Parameters:\n"
                    "  -i\tSpecifies the path to resourcepack.\n"
                    "  -o\tSpecifies the path to JSON file.\n"
                    " Optional Parameters:\n"
                    "  -t\tSpecifies the path to temporary file.\n"
                    "  -y\tOverwrite the JSON file without asking.\n"
                    "  -r\tRandomise the colour order.(Not available now)\n"
                    "  -e\tDon't show non-error messages while converting.\n";

    WARN_OVERRIDE  = "Warning: %s is already exist.Override?(y/n):";
}       


//#endif //#ifdef SC3CHF_INIT_LANG


#endif //#ifndef SC3CHF_INIT_LANG