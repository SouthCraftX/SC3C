#ifndef SC3CHF_CSTRUCTFUC
#define SC3CHF_CSTRUCTFUC

void Construct_ResPackArchive( struct _ResPackArchive* _struct , char* zip_path ){
    _struct->archive        = NULL;
    _struct->zip_path        = zip_path;
    _struct->zip_png_path   = "noteColors.png";
    _struct->error_code     = 0;
    _struct->png_fileptr    = NULL;
};

void Construct_PNGData( struct _PNGData* _struct ){
    _struct->temp_png_path = TEMP_PNG_FILE ;
    _struct->pixel_red     = NULL ;
    _struct->pixel_green   = NULL ;
    _struct->pixel_blue    = NULL ;
    _struct->pixel_alpha   = NULL ;
    _struct->m_width       = 0 ;
    _struct->m_height      = 0 ;
    _struct->color_type    = 0 ;
    _struct->num_channel   = 0 ;
    _struct->num_pixel     = 0 ;
}

#endif