// analysis_sport.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "mul_sport_common.h"
#include "ms_sport_analysis.h"
#include "string.h"
#include "mul_sport_ops.h"
#include "mul_sport_factory.h"
#include "multi_motion_sport_handle.h"
#include "multi_motion_gps_handle.h"
#include "multi_motion_public_part.h"
#include "ms_gps_sport.h"

int main()
{
    std::cout << "Hello World!\n";
   mul_sport_platform_init();//初始化函数指针数组
   mul_sport_analysis_record();
   mul_sport_analysis_points();
    //mul_sport_analysis_gps_points();
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
