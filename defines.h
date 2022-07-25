#ifndef SC3CHF_DEFS
#define SC3CHF_DEFS

#include <stdio.h>

#define BUFFER_SIZE (8192)
#define MAX_PATH_LEN (260) 
#define PATH_TO_UNZIP ("noteColors.png")
#define DEFAULT_ALPHA (255)
//#define true (1)
//#define false (0)

//typedef int bool;
typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned long long ullong;
typedef long long llong;
typedef char* cstring;
typedef const char* ccstring;


enum StatusCode{
    OK = 0,
    InvaildArg,
    NoDirFile,
    OpenPNGFailed,
    OpenZipFailed,
    CreateFile,
    WrongNumChannel,
    WriteJson
};

enum StatusCode _scode;

struct CovertOption {
    char* input_path;
    char* output_path;
    char* temp_path;
    bool  print_error_msg_only : 1;
    bool  force_overwriting : 1;
    bool  ramdom_color : 1;
}


struct _PNGData {
    byte** row_ptr ;
    int bit_depth  ;
    int m_width    ;  
    int m_height   ;
    int color_type ;
    int num_channel;
    int num_pixel  ;
};

#endif