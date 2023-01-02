#ifndef SC3CHF_DEF_STRUCT
#define SC3CHF_DEF_STRUCT

#include "basic_types.h"

struct ConvertOption {
    char* input_path;
    char* output_path;
    char* temp_path;
    bool  print_info_msg : 1;
    bool  force_overriding : 1;
    bool  ramdom_color : 1;
    bool  no_cleaning : 1;
    bool  show_opt : 1 ;   
};


struct PNGData {
    byte_t**  row_ptr ;
    ulong32_t height;
    ulong32_t width;
};

typedef struct ConvertOption    convert_option_t;
typedef struct PNGData          png_data_t;       

#endif //#ifndef SC3CHF_DEF_STRUCT