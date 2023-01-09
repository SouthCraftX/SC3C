gcc -g main.c -I/usr/include/libpng16 -lpng16 -lz -lminizip -O3 -ffunction-sections -fdata-sections  -Wl,-gc-sections -s -Wall -o main
