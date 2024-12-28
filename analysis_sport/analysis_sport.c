// analysis_sport.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <windows.h>
#define _countof(array) (sizeof(array) / sizeof((array)[0]))
extern void hex_to_bin(const char* txt_file,uint8_t type);
#define VERSION1 1
#define VERSION2 0
#define VERSION3 6
int main()
{

    // 设置控制台输出为 UTF-8 编码
	SetConsoleOutputCP(CP_UTF8);
    printf("****************************************************************************************************\n");
    printf("*********************************time:2024/12/5 17:22 version:%d.%d.%d*********************************\n",VERSION1,VERSION2,VERSION3);
    printf("****************************************************************************************************\n");
    mul_sport_platform_init();//初始化函数指针数组
    int is_need_to_bin = 0;
    printf("是否需要字符串转成2进制,0不需要,其他是需要:\n");
    scanf_s("%d", &is_need_to_bin);
    if (is_need_to_bin>0)
    {
        char buff[255] = {0};

    here: {};
        memset(buff, 0, sizeof(buff));
        printf("输入input参数,格式为txt,通常为IOS的打点格式:\n");
        scanf_s("%s", buff, (unsigned)_countof(buff)); // 使用 _countof 获取数组大小
        int type = 0;
        printf("输入转出类型:(1.日常打点,2.日常报告,3.运动打点,4.运动报告,5.gps打点(运动打点和报告都需要打点才能解析,必需先解析报告再解析打点))\n");
        scanf_s("%d", &type);
        hex_to_bin((const char*)buff,type);

        type = 0;
        printf("是否还需要解析:1需要,0不需要\n");
        scanf_s("%d", &type);
        if (type)
        {
            goto here;
        }
        else
        {
            goto an_start;
        }
    }
    else
    {
an_start:
{};
        printf("解析开始\n");
        extern void set_phone_type(void);
        set_phone_type();
        mul_sport_analysis_record();
        mul_sport_analysis_points();
        mul_sport_analysis_gps_points();
        mul_sport_analysis_daily_data_points();
        mul_sport_analysis_daily_data_record();
        printf("解析结束\n");
    }
    system("pause");
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
