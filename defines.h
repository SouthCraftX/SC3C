#ifndef SC3CHF_DEFS
#define SC3CHF_DEFS

#include <stdbool.h> //bool,true,false

#ifdef USE_STDINT
#include <stdint.h>  //int32_t,...
#endif

#define BUFFER_SIZE (8192)
#define MAX_PATH_LEN (260)
#define PATH_TO_UNZIP ("noteColors.png")
#define DEFAULT_ALPHA (255)
//#define true (1)
//#define false (0)

//typedef int bool;
#ifdef USE_STDINT
typedef uint8_t       byte;
typedef uint32_t      uint;
typedef uint32_t      ulong;
typedef uint16_t      ushort;
typedef uint64_t      ullong;
typedef int64_t       llong;
#else
typedef unsigned char       byte;
typedef unsigned int        uint;
typedef unsigned long       ulong;
typedef unsigned short      ushort;
typedef unsigned long long  ullong;
typedef long long           llong;
#endif

typedef char*               cstring;
typedef const char*         ccstring;


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
    bool  no_cleaning : 1;
    bool  do_help : 1;
};


struct PNGData {
    byte** row_ptr ;
    int height;
    int width;
};

#endif
