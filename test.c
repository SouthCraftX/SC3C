#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>


int main()
{
        char buffer[1024];
        char *path = "./1.zip";
        int err = 0;
        zip_t *archive = NULL;
        zip_file_t *file = NULL;
        zip_int64_t n = 0;

        //打开zip压缩文件
        archive = zip_open(path, ZIP_RDONLY, &err);
        if(archive == NULL)
        {
                printf("open 1.zip failed, err=%d,message=%s\n", err , zip_error_strerror(&err));
                return -1;
        }

        //打开zip文件里的其中一个文件
        file = zip_fopen(archive, "1.txt", ZIP_FL_COMPRESSED);
        if(file == NULL)
        {
                printf("open 1.txt failed\n");
                zip_close(archive);
                return -1;
        }

        //读其中一个文件的内容
        memset(buffer, 0x00, sizeof(buffer));
        n = zip_fread(file, buffer, 100);

        printf("%s", buffer);

        //关闭其中一个文件
        zip_fclose(file);

        //关闭压缩文件
        zip_close(archive);

        return 0;
}