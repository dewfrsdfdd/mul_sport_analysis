#include <stdio.h>
#include <sys/stat.h>
#include "stdbool.h"
#include "stdint.h"
uint32_t file_size = 0;
uint32_t zh_flash_get_file_size(char* filename)
{
    struct stat fstat;
    stat(filename, &fstat);
    printf("%s size is %ld\n", filename, fstat.st_size);
    file_size = fstat.st_size;
    return fstat.st_size;
}
// #pragma warning(disable:4996)

FILE *zh_flash_open(const char *filename, const char *_Mode)
{
    printf("-------------%s\n",__func__);
    FILE *file_ft = NULL;
   // errno_t errno = fopen_s(&file_ft, filename, _Mode);

    // if (errno != 0)
    // {
    //     perror("Error opening file errno = %d\n", errno);
    // }
    return file_ft;
}

int zh_flash_read(FILE *fp, uint32_t addr, uint8_t *read_buff, uint32_t read_size)
{
  //printf("!!!!!!!!!!!!!!!!!!!! zh_flash_read ft_file:0x%x\n", fp);
    uint32_t filesize = file_size;
    if (fp == NULL) // 检查文件指针是否有效
    {
        return -1; // 返回错误代码，表示文件指针无效
    }
    //fseek(fp, 0, SEEK_END);
     //filesize = ftell(fp);
    //fseek(fp, 0, SEEK_SET);
    if (read_size + addr <= filesize) // 修改了这里的条件，使用 <= 以确保不会越界
    {
        fseek(fp, addr, SEEK_SET);
        size_t result = fread((void*)read_buff, 1, read_size, fp);
        //printf("result:%d\n", result);
        if (result != read_size) // 检查读取的字节数是否与请求的字节数相同
        {
            // 处理读取错误的情况
            printf("read erroor\n");
            return -1; // 返回错误代码
        }
        return 0; // 成功读取
    }
    return -1; // 返回错误代码，表示读取超出文件大小
}

int zh_flash_close(FILE *fp)
{
    if (fp)
    {
        fclose(fp);
    }
    return 0;
}
