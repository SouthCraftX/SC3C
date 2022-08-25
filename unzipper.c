#include "png_unzipper.h"

struct ConvertOption opt;

int main(){
    opt.input_path = "demo.zip";
    opt.temp_path  = "temp.png";
    opt.no_cleaning = true ;

    unzipper( &opt );

    return 0;
}
