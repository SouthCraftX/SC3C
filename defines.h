#ifndef SC3CHF_DEFS
#define SC3CHF_DEFS

#define BUFFER_SIZE (8192)
#define MAX_PATH_LEN (260) 
#define PATH_TO_UNZIP ("noteColors.png")
#define DEFAULT_ALPHA (255)
#define true (1)
#define false (0)

typedef int bool;
typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned long long ullong;
typedef long long llong;

enum StatusCode{
    OK = 0,
    NoDirFile,
    OpenPNGFailed,
    OpenZipFailed,
    CreateFile,
    WrongNumChannel,
    WriteJson
};

enum StatusCode _scode;

struct _ResPackArchive {
    zip_t* archive;
    char* zip_path ;
    char* zip_png_path ; 
    int error_code;
    FILE* png_fileptr;
};


struct _PNGData {
    char* temp_png_path;
    byte** row_pointers;
    int bit_depth;
    int m_width    ;  
    int m_height   ;
    int color_type ;
    int num_channel;
    int num_pixel  ;
};

#endif