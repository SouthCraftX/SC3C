#ifndef SC3CHF_DEF_BTYPE
#define SC3CHF_DEF_BTYPE

#include <stdbool.h>    //bool,true,false
#include <stdint.h>     //int32_t,...


typedef     uint8_t     byte_t    ;
typedef     byte_t      ushort8_t ;
typedef     uint16_t    ushort16_t;
typedef     uint32_t    ulong32_t ;
typedef     uint64_t    ulong64_t ;

typedef     int8_t      short8_t  ;
typedef     int16_t     short16_t ;
typedef     int32_t     long32_t  ;
typedef     int64_t     long64_t  ;

typedef     uint8_t       flag8_t   ;
typedef     uint16_t      flag16_t  ;
typedef     ulong32_t     flag32_t  ;
typedef     ulong64_t     flag64_t  ;

typedef     char*         cstring_t ;
typedef     const char*   ccstring_t;

typedef     flag8_t       lang_id_t;


#endif //#ifndef SC3CHF_DEF_BTYPE