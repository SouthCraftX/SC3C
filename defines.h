#ifndef SC3CHF_DEFS
#define SC3CHF_DEFS

#include <stdbool.h> //bool,true,false


#include <stdint.h>  //int32_t,...

#define BUFFER_SIZE     (8192)
#define PATH_TO_UNZIP   ("noteColors.png")
#define PNG_NAME        ("noteColors.png")
#define DEFAULT_ALPHA   (255)
//#define true (1)
//#define false (0)

//typedef int bool;

typedef     uint8_t     byte    ;
typedef     byte        uint8   ;
typedef     uint16_t    uint16  ;
typedef     uint32_t    ulong32 ;
typedef     uint64_t    ulong64 ;

typedef     int8_t      int8    ;
typedef     int16_t     int16   ;
typedef     int32_t     long32  ;
typedef     int64_t     long64  ;

typedef     uint8       flag8   ;
typedef     uint16      flag16  ;
typedef     ulong32     flag32  ;
typedef     ulong64     flag64  ;

typedef     char*       cstring ;
typedef     const char* ccstring;


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

struct ConvertOption {
    char* input_path;
    char* output_path;
    char* temp_path;
    bool  print_info_msg : 1;
    bool  force_overriding : 1;
    bool  ramdom_color : 1;
    bool  no_cleaning : 1;
    bool  show_opt : 1 ;    // this
};


struct PNGData {
    byte**  row_ptr ;
    ulong32 height;
    ulong32 width;
};

#endif
