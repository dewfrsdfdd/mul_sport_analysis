#include "mul_sport_common.h"
#define MS_ANALYSIS 1


#include "ms_sport_analysis.h"
#include "string.h"
#include "daily_activity_data_struct.h"
#include "zh_flash_opter.h"
#include "mul_sport_ops.h"
#include "mul_sport_factory.h"
#include "multi_motion_sport_handle.h"
#if GPS_DATA_MANAGER_SWITCH
#include "multi_motion_gps_handle.h"
#endif
#include "multi_motion_public_part.h"
#include "ms_gps_sport.h"

#pragma warning(disable:4996)
#pragma pack(push, 1)
typedef union _ms_points_item_t
{
    struct
    {
        struct
        {
            float initialize_altitude;
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union
            {
                uint8_t st_d;
                struct
                {
                    uint8_t training_type : 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
            uint32_t segment_distance;
        } data_head;
    } out_run_c; // 户外跑步类

    struct
    {
        struct
        {
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union
            {
                uint8_t st_d;
                struct
                {
                    uint8_t training_type : 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
            uint32_t segment_distance;
        } data_head;
    } indoor_run; // 室内跑步

    struct
    {
        struct
        {
            float initialize_altitude;
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union
            {
                uint8_t st_d;
                struct
                {
                    uint8_t training_type : 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
        } data_head;
    } out_non_run_c; // 户外非跑步类

    struct
    {
        struct
        {
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union
            {
                uint8_t st_d;
                struct
                {
                    uint8_t training_type : 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
        } data_head;
    } free_sport; // 自由训练类

    struct
    {
        struct
        {
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union
            {
                uint8_t st_d;
                struct
                {
                    uint8_t training_type : 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
            uint32_t segment_count;
        } data_head;
    } rope_skip; // 跳绳类

    struct
    {
        struct
        {
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union
            {
                uint8_t st_d;
                struct
                {
                    uint8_t training_type : 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
        } data_head;
    } elliptical_m; // 椭圆机

    struct
    {
        struct
        {
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union
            {
                uint8_t st_d;
                struct
                {
                    uint8_t training_type : 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
            uint32_t segment_times; // 本段总划次
        } data_head;
    } rowing_m; // 划船机类

    struct
    {
        struct {
            uint32_t count_sport_hold;
            uint32_t restore_time;
        } data_head;
    } swimming;            // 游泳类
} ms_points_item_t;

typedef struct _ms_gps_v1_t
{
         uint32_t gps_timestamp;
        float    gps_longitude;
        float    gps_latitude;   
} ms_gps_v1_t;
typedef struct _ms_gps_v2_t
{
    uint32_t gps_timestamp;
    float gps_longitude;
    float gps_latitude;
    float location_accuracy;
    union
    {
        uint16_t fv_d;
        struct
        {
            uint16_t gps_source : 4;
            uint16_t location_speed : 12;
        } speed_gps_s;
    } speed_gps_u;
} ms_gps_v2_t;
#pragma pack(pop)
#if MS_ANALYSIS
static bool interval_switch = 1;//间歇训练开关 
static uint16_t sport_analysis_type = SPORTING_Skipping_rope_H_TYPE;//解析的运动类型
static uint32_t total_point_count = 180;//总的打点数
static uint8_t gps_version = 2;//gps版本
#define USE_BIN 1
static uint8_t point_buff[] = {
0x36,0xb4,0xa0,0x66,0x20,0x02,0xa8,0x00,0xff,0xff,0x05,0x00,0x00,0x00,0x36,0xb4,0xa0,0x66,0x00,0x24,0xb5,0xa0,0x66,0x02,0x51,0x03,0xfd,0x00,0x1c,0x00,0x07,0x00,0x0f,0x00,0x01,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x35,0xb5,0xa0,0x66,0x02,0x43,0x00,0x1f,0x00,0x35,0x00,0x09,0x00,0x1d,0x00,0x02,0x00,0x31,0x00,0x00,0x00,0x00,0x00,0x0a,0x00,0x00,0x5e,0xb5,0xa0,0x66,0x03,0x9b,0x00,0x38,0x00,0x4f,0x00,0x0c,0x00,0x2c,0x00,0x03,0x00,0x15,0x00,0x00,0x00,0x00,0x00,0x0e,0x00,0x00,0x72,0xb5,0xa0,0x66,0x03,0x4a,0x00,0x21,0x00,0x6a,0x00,0x0f,0x00,0x3c,0x00,0x04,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x11,0x00,0x01,0x72,0xb5,0xa0,0x66,0x03,0x4a,0x00,0x21,0x00,
};

static uint8_t gps_point_buff[] = {
0x2e,0x38,0x3d,0x67,0x20,0x02,0x16,0x20,0xfc,0x3a,0x38,0x3d,0x67,0xba,0xca,0xe3,0x42,0xce,0xb6,0xb5,0x41,0xd7,0x55,0x26,0x42,0xf2,0x01,0x3b,0x38,0x3d,0x67,0xbd,0xca,0xe3,0x42,0x83,0xb6,0xb5,0x41,0x74,0x58,0xb2,0x41,0x82,0x20,0x3c,0x38,0x3d,0x67,0xb5,0xca,0xe3,0x42,0xe7,0xb6,0xb5,0x41,0xb6,0x28,0xe1,0x41,0x02,0x02,0x3d,0x38,0x3d,0x67,0x9b,0xca,0xe3,0x42,0x5e,0xb7,0xb5,0x41,0xaa,0x87,0xed,0x41,0xf2,0x01,0x3f,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xf1,0xb6,0xb5,0x41,0x0f,0x5b,0x8b,0x41,0x32,0x20,0x40,0x38,0x3d,0x67,0xbf,0xca,0xe3,0x42,0xec,0xb6,0xb5,0x41,0x7f,0x87,0x39,0x41,0x62,0x20,0x41,0x38,0x3d,0x67,0xbe,0xca,0xe3,0x42,0x07,0xb7,0xb5,0x41,0xe1,0xea,0x44,0x41,0x42,0x20,0x42,0x38,0x3d,0x67,0xbe,0xca,0xe3,0x42,0x04,0xb7,0xb5,0x41,0x6f,0x02,0x25,0x41,0x72,0x20,0x43,0x38,0x3d,0x67,0xc5,0xca,0xe3,0x42,0xea,0xb6,0xb5,0x41,0xd5,0xd0,0x23,0x41,0x22,0x20,0x44,0x38,0x3d,0x67,0xc1,0xca,0xe3,0x42,0xdc,0xb6,0xb5,0x41,0xef,0x91,0x38,0x41,0xb2,0x20,0x45,0x38,0x3d,0x67,0xc5,0xca,0xe3,0x42,0xc5,0xb6,0xb5,0x41,0xe3,0x63,0x3e,0x41,0x02,0x01,0x46,0x38,0x3d,0x67,0xbf,0xca,0xe3,0x42,0xb5,0xb6,0xb5,0x41,0x46,0x90,0x37,0x41,0x32,0x20,0x47,0x38,0x3d,0x67,0xb2,0xca,0xe3,0x42,0xd1,0xb6,0xb5,0x41,0x8e,0x79,0x39,0x41,0x32,0x20,0x48,0x38,0x3d,0x67,0xb2,0xca,0xe3,0x42,0xbc,0xb6,0xb5,0x41,0x39,0xea,0x50,0x41,0x32,0x20,0x49,0x38,0x3d,0x67,0xb7,0xca,0xe3,0x42,0xc4,0xb6,0xb5,0x41,0xd0,0x4c,0x3d,0x41,0x52,0x20,0x4a,0x38,0x3d,0x67,0xb8,0xca,0xe3,0x42,0xc5,0xb6,0xb5,0x41,0xf4,0x75,0x30,0x41,0x02,0x20,0x4b,0x38,0x3d,0x67,0xb4,0xca,0xe3,0x42,0xef,0xb6,0xb5,0x41,0x61,0x49,0x46,0x41,0x02,0x20,0x4c,0x38,0x3d,0x67,0xb6,0xca,0xe3,0x42,0xda,0xb6,0xb5,0x41,0xca,0x77,0x21,0x41,0x32,0x20,0x4d,0x38,0x3d,0x67,0xb8,0xca,0xe3,0x42,0xe1,0xb6,0xb5,0x41,0xc8,0xcc,0x2c,0x41,0x72,0x20,0x4e,0x38,0x3d,0x67,0xc7,0xca,0xe3,0x42,0xcf,0xb6,0xb5,0x41,0x05,0xcb,0x1f,0x41,0x32,0x20,0x4f,0x38,0x3d,0x67,0xc1,0xca,0xe3,0x42,0xdf,0xb6,0xb5,0x41,0x5d,0x54,0x2d,0x41,0x12,0x20,0x50,0x38,0x3d,0x67,0xbd,0xca,0xe3,0x42,0xd9,0xb6,0xb5,0x41,0x98,0xa0,0x06,0x41,0x42,0x20,0x51,0x38,0x3d,0x67,0xbf,0xca,0xe3,0x42,0xd1,0xb6,0xb5,0x41,0xc7,0xd6,0x09,0x41,0x42,0x20,0x52,0x38,0x3d,0x67,0xbf,0xca,0xe3,0x42,0xd0,0xb6,0xb5,0x41,0xb5,0xc6,0xfe,0x40,0x32,0x20,0x53,0x38,0x3d,0x67,0xbf,0xca,0xe3,0x42,0xd3,0xb6,0xb5,0x41,0xee,0xd9,0xf6,0x40,0x32,0x20,0x54,0x38,0x3d,0x67,0xbd,0xca,0xe3,0x42,0xd5,0xb6,0xb5,0x41,0xd9,0xaa,0xeb,0x40,0x32,0x20,0x55,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xda,0xb6,0xb5,0x41,0x13,0x1f,0xfd,0x40,0x22,0x20,0x56,0x38,0x3d,0x67,0xb6,0xca,0xe3,0x42,0xe3,0xb6,0xb5,0x41,0x6b,0x6a,0xf6,0x40,0x52,0x20,0x57,0x38,0x3d,0x67,0xb6,0xca,0xe3,0x42,0xe3,0xb6,0xb5,0x41,0x7c,0x6b,0xe9,0x40,0x42,0x20,0x58,0x38,0x3d,0x67,0xb5,0xca,0xe3,0x42,0xe6,0xb6,0xb5,0x41,0x3a,0xc6,0xf1,0x40,0x52,0x20,0x59,0x38,0x3d,0x67,0xb5,0xca,0xe3,0x42,0xea,0xb6,0xb5,0x41,0xd6,0x48,0x06,0x41,0x72,0x20,0x5a,0x38,0x3d,0x67,0xb6,0xca,0xe3,0x42,0xea,0xb6,0xb5,0x41,0x12,0x35,0xfd,0x40,0x42,0x20,0x5b,0x38,0x3d,0x67,0xb6,0xca,0xe3,0x42,0xeb,0xb6,0xb5,0x41,0x69,0xba,0xdb,0x40,0x12,0x20,0x5c,0x38,0x3d,0x67,0xb6,0xca,0xe3,0x42,0xe8,0xb6,0xb5,0x41,0x5d,0x0c,0xae,0x40,0x22,0x20,0x5d,0x38,0x3d,0x67,0xb8,0xca,0xe3,0x42,0xe4,0xb6,0xb5,0x41,0xc4,0x59,0xc1,0x40,0x02,0x20,0x5e,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe2,0xb6,0xb5,0x41,0xdb,0x6f,0xb2,0x40,0x02,0x20,0x5f,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe1,0xb6,0xb5,0x41,0x73,0xdc,0xb6,0x40,0x02,0x20,0x60,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe2,0xb6,0xb5,0x41,0x36,0xea,0xb5,0x40,0x02,0x20,0x61,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe3,0xb6,0xb5,0x41,0xc4,0xc6,0xae,0x40,0x02,0x20,0x62,0x38,0x3d,0x67,0xb8,0xca,0xe3,0x42,0xe5,0xb6,0xb5,0x41,0x30,0xfa,0xb1,0x40,0x02,0x20,0x63,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe4,0xb6,0xb5,0x41,0xb7,0x5d,0xaf,0x40,0x02,0x20,0x64,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe4,0xb6,0xb5,0x41,0x03,0x49,0xa7,0x40,0x02,0x20,0x65,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe4,0xb6,0xb5,0x41,0x8d,0x16,0xa1,0x40,0x02,0x20,0x66,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe4,0xb6,0xb5,0x41,0x97,0xa7,0xa5,0x40,0x02,0x20,0x67,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe5,0xb6,0xb5,0x41,0xcb,0x34,0x9c,0x40,0x02,0x20,0x68,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe5,0xb6,0xb5,0x41,0x64,0x65,0x97,0x40,0x02,0x20,0x69,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe5,0xb6,0xb5,0x41,0xa3,0xb1,0x9d,0x40,0x02,0x20,0x6a,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe5,0xb6,0xb5,0x41,0x43,0xe3,0xa6,0x40,0x02,0x20,0x6b,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe5,0xb6,0xb5,0x41,0x63,0x58,0xa7,0x40,0x02,0x20,0x6c,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe5,0xb6,0xb5,0x41,0x20,0x5c,0xa8,0x40,0x02,0x20,0x6d,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe5,0xb6,0xb5,0x41,0xa7,0x1e,0xa3,0x40,0x02,0x20,0x6e,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe5,0xb6,0xb5,0x41,0x5e,0x49,0xa1,0x40,0x02,0x20,0x6f,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe5,0xb6,0xb5,0x41,0x59,0x23,0x9f,0x40,0x02,0x20,0x70,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe5,0xb6,0xb5,0x41,0x5d,0xf1,0x99,0x40,0x02,0x20,0x71,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe4,0xb6,0xb5,0x41,0xc6,0x79,0x97,0x40,0x02,0x20,0x72,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe4,0xb6,0xb5,0x41,0x93,0x04,0x93,0x40,0x02,0x20,0x73,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe4,0xb6,0xb5,0x41,0x54,0x82,0x8e,0x40,0x02,0x20,0x74,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe4,0xb6,0xb5,0x41,0x6d,0x14,0x8b,0x40,0x02,0x20,0x75,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe4,0xb6,0xb5,0x41,0x30,0x50,0x87,0x40,0x02,0x20,0x76,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe4,0xb6,0xb5,0x41,0xb7,0x1a,0x80,0x40,0x02,0x20,0x77,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe4,0xb6,0xb5,0x41,0xe8,0x1f,0x77,0x40,0x02,0x20,0x78,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe4,0xb6,0xb5,0x41,0x29,0x90,0x74,0x40,0x02,0x20,0x79,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe3,0xb6,0xb5,0x41,0xb3,0x92,0x75,0x40,0x02,0x20,0x7a,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe3,0xb6,0xb5,0x41,0x9e,0x26,0x7b,0x40,0x02,0x20,0x7b,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe3,0xb6,0xb5,0x41,0x16,0x64,0x7b,0x40,0x02,0x20,0x7c,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe3,0xb6,0xb5,0x41,0x2d,0x5a,0x7c,0x40,0x02,0x20,0x7d,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe3,0xb6,0xb5,0x41,0x0a,0x2e,0x7b,0x40,0x02,0x20,0x7e,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe3,0xb6,0xb5,0x41,0x9c,0x29,0x7c,0x40,0x02,0x20,0x7f,0x38,0x3d,0x67,0xb9,0xca,0xe3,0x42,0xe3,0xb6,0xb5,0x41,0xf6,0x3a,0x77,0x40,0x02,0x20,
};

static uint8_t record_buff[] = {
0x36,0xb4,0xa0,0x66,0x20,0x06,0xa9,0x00,0xfe,0x7f,0xbe,0x04,0x36,0xb4,0xa0,0x66,0xb1,0xb5,0xa0,0x66,0x3d,0x01,0x00,0x00,0x6a,0x00,0x00,0x00,0x0f,0x00,0x43,0x00,0x00,0x00,0x51,0x03,0x00,0x00,0x00,0x00,0x00,0x3c,0x00,0x02,0x31,0x04,0x00,0x5d,0x00,0x1f,0x00,0x19,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfa,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,
};

//日常打点数据放这里
static uint8_t daily_data_point[] =
{
0x00,0xb6,0x3c,0x67,0x20,0x03,0x00,0xbe,0xec,0xc0,0x0c,0xc0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x38,
0x00,0x01,0x00,0x13,0x00,0x00,0x00,0xff,

};
static uint8_t daily_data_record[] =
{
0xfe,0xcb,0x2e,0x67,0x20,0x05,0x01,0x00,0xff,0xfd,0xf8,0xfc,0x0e,0x0a,0x00,0x00,0x72,0x00,0x5a,0x4f,0x91,0x51,0xec,0x2e,0x67,0x4f,0xcc,0xd9,0x2e,0x67,0x5f,0x00,0x00,0x00,0x00,0x7c,0x00,0x72,0x00,0x00,0x00,0x61,0x61,0xc8,0xec,0x2e,0x67,0x5f,0x9c,0xcd,0x2e,0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x01,0x02,0x06,0x00,0x01,0x16,
};
#define IsLeapYear(yr) (!((yr) % 400) || (((yr) % 100) && !((yr) % 4)))
#define YearLength(yr) (IsLeapYear(yr) ? 366 : 365)
typedef unsigned int UTCTime; /* used to store the second counts for RTC */
#define BEGYEAR         1970     // UTC started at 00:00:00 January 1, 2000
#define DAY             86400UL  // 24 hours * 60 minutes * 60 seconds
#define SLEEP_BASE_YEAR 2000
typedef enum {
    MOn = 0,
    Tues = 1,
    Wed = 2,
    Thur = 3,
    Fri = 4,
    Sat = 5,
    Sun = 6
}DAY_OF_WEEK;
typedef struct
{
    uint16_t year;    // 2000+年
    uint8_t month;    // 0-11月
    uint8_t day;      // 0-30日
    uint8_t seconds;  // 0-59秒
    uint8_t minutes;  // 0-59分
    uint8_t hour;     // 0-23时
    int8_t offset;    // 本地时区
}UTCTimeStruct;
/*********************************************************************
 * Get month length
 *********************************************************************/
uint8_t monthLength(uint8_t lpyr, uint8_t mon)
{
    uint8_t days = 31;

    if (mon == 1) //
    {
        days = (28 + lpyr);
    }
    else {
        if (mon > 6) //
        {
            mon--;
        }

        if (mon & 1) {
            days = 30;
        }
    }

    return (days);
}
void ConvertToUTCTime(UTCTimeStruct* tm, UTCTime secTime)
{
    //	struct tm now;
    //	gmtime_r(&secTime, &now);
    //	rt_kprintf("ConvertToUTCTime=%d,%d,%d,%d\n",now.tm_year,now.tm_mon,now.tm_mday,secTime);
    //	tm_out->year=now.tm_year;
    //	tm_out->month=now.tm_mon;
    //	tm_out->day=now.tm_mday;
    //	tm_out->hour=now.tm_hour;
    //	tm_out->minutes=now.tm_min;
    //	tm_out->seconds=now.tm_sec;

#if 1
    {
        uint32_t day = secTime % DAY;
        tm->seconds = day % 60UL;
        tm->minutes = (day % 3600UL) / 60UL;
        tm->hour = day / 3600UL;
    }

    {
        uint32_t numDays = secTime / DAY;
        tm->year = BEGYEAR;
        while (numDays >= YearLength(tm->year))
        {
            numDays -= YearLength(tm->year);
            tm->year++;
        }

        tm->month = 0;
        while (numDays >= monthLength(IsLeapYear(tm->year), tm->month))
        {
            numDays -= monthLength(IsLeapYear(tm->year), tm->month);
            tm->month++;
        }
        tm->day = numDays;
    }
    // rt_kprintf("ConvertToUTCTime=%d,%d,%d,%d\n", tm->year, tm->month, tm->minutes, secTime);
#endif
}
int32_t get_time_zone_offset(int8_t time_zone)
{
    return time_zone * 15 * 60;
}
uint16_t mul_sport_analysis_sport_type(data_id_t* p_id)
{
    uint16_t sport_type = 0;


    switch (p_id->type_desc.specific_type)
    {
        /* t2 - 室内跑 */
    case ST_INDOOR_RUN:
        sport_type = SPORTING_Indoor_running_TYPE;
        break;

        /* t4 - 自由训练 */
    case ST_INDOOR_CYCLE:
    case ST_FREE_SPORT:
        sport_type = SPORTING_free_activity_TYPE;
        break;

        /* t5 - 游泳 */
    case ST_SWIM_INDOOR:
        sport_type = SPORTING_swim_indoor_TYPE; // 泳池游泳
        break;
    case ST_SWIM_OUTDOOR:
        sport_type = SPORTING_swim_outdoor_TYPE;// 开放水域游泳
        break;

        /* t6 - 划船机 */
    case ST_ROWING_MACHINE:
        sport_type = SPORTING_Rowing_machine_TYPE;
        break;

        /* t7 - 跳绳 */
    case ST_ROPE_SKIPPING:
        sport_type = SPORTING_Skipping_rope_H_TYPE;
        break;

        /* t8 - 椭圆机 */
    case ST_ELLIPTICAL_MACHINE:
        sport_type = SPORTING_Elliptical_machine_TYPE;
        break;

        /* t9 - 户外跑步类 */
    case ST_OUTSIDE_RUN_CATEGORY:
        {
        uint8_t head_size = 0;
            switch (p_id->version)
            {
                case 1:
                break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                {
                    head_size = 8;
                }
                    break;
                case 5:
                {
                    head_size = 10;
                }
                    break;
                default:
                    break;
            }
            uint16_t stype = 0;
            memcpy(&stype, &record_buff[head_size + 7], sizeof(uint16_t));
            switch (stype)
            {
            case 1:
                sport_type = SPORTING_Outdoor_running_TYPE;
                break;
            case 2:
                sport_type = SPORTING_Outdoor_walking_TYPE;
                break;
            case 4:
                sport_type = SPORTING_Mountaineering_TYPE;
                break;
            case 5:
                sport_type = SPORTING_Off_road_TYPE;
                break;
            case 15:
                sport_type = SPORTING_Outdoor_hiking_TYPE;
                break;
            case 207:
                sport_type = SPORTING_Outdoor_running_TYPE;
                break;
            default:
                sport_type = SPORTING_Outdoor_running_TYPE;
                break;
            }
        
        }
        break;

        /* t10 - 户外非跑走类*/
    case ST_OUTSIDE_NOT_RUN_CATEGORY:
        sport_type = SPORTING_Outdoor_cycling_TYPE;
        break;

    default:
        sport_type = SPORTING_Outdoor_cycling_TYPE;
        break;
    }

    return sport_type;
}
void mul_sport_analysis_points(void)
{
    //printf("%s,%d\n", __func__, __LINE__);
    uint32_t offset_start = 7;
    // 读取固定头部
    p_ms_abstract_config_t p_ms_sport_config = NULL;
    Set_current_sproting_type(sport_analysis_type);
    if (!mul_sport_get_cur_sport_config((void **)&p_ms_sport_config))
    {
        return;
    }
   // printf("%s,%d\n", __func__, __LINE__);
    bool ret_flag;
    p_ms_abstract_sport_handle_t p_ms_sport_handle = NULL; // 指针
    ret_flag = mul_sport_factory_get_sport(p_ms_sport_config, &p_ms_sport_handle);
    printf("%s,%d,0x%x,0x%x\n", __func__, __LINE__, p_ms_sport_config, p_ms_sport_handle);
    if (p_ms_sport_handle && p_ms_sport_config)
    {
       // printf("%s,%d\n", __func__, __LINE__);
        static ms_common_sport_list_v1_t s_ms_sport_list;

        s_ms_sport_list.ms_sport_list.magic_number = MUL_SPORT_MAGIC_NUMBER;
        s_ms_sport_list.ms_sport_list.version = MUL_SPORT_VER_1;
        s_ms_sport_list.ms_sport_list.ms_config = p_ms_sport_config;
        s_ms_sport_list.ms_sport_list.ms_handle = p_ms_sport_handle;
        p_ms_abstract_sport_list_t g_p_sport_list_item_obj_t = (p_ms_abstract_sport_list_t)&s_ms_sport_list;
        // p_ms_sport_handle->pf_get_sport_fixed_data()
        uint16_t idx_pos;
        data_id_t mul_id;
       // printf("%s,%d\n", __func__, __LINE__);
        mul_id.timestamp = 0;//sport_start_timestamp();
        mul_id.timezone = mul_sport_get_time_zone();
        mul_id.version = g_p_sport_list_item_obj_t->ms_handle->data_ver;

        mul_id.type_desc.type = ENUM_SPORT_DATA_T;
        mul_id.type_desc.specific_type = g_p_sport_list_item_obj_t->ms_config->sport_type;
        mul_id.type_desc.data_type = ENUM_POINT_DATA_T;
       // printf("%s,%d\n", __func__, __LINE__);
        // 读取头部
        uint8_t *file_header_ptr = NULL;
        size_t file_header_len = 0;
        mul_sport_platform_get_data_header_ptr(&mul_id, &file_header_ptr, &file_header_len);
        printf("total_point_file:%d\n",sizeof(point_buff)/sizeof(uint8_t));
        char file_header_p[1024] = {0};
        char file_str[256 * 2] = {0};
        FILE* p_file = fopen("analysis.txt", "w");
        if (p_file == NULL)
        {
            printf("open fail\n");
        }
        memset(file_header_p, 0, sizeof(file_header_p));
        if (file_header_len)
        {
            //file_header_p = (uint8_t *)malloc(file_header_len);
            if (file_header_p && (sizeof(point_buff) > (offset_start + file_header_len)))
            {
                memcpy(file_header_p, &point_buff[offset_start], file_header_len);
                offset_start += file_header_len;
                if (strcmp(file_header_p, (char*)file_header_ptr) == 0) // 头部比对成功
                {
                    uint32_t curren_hold = 0;
                    uint32_t total_hold = 0;
                    while(/*total_hold<total_point_count && */(offset_start<sizeof(point_buff)))
                    {
                        // 读取暂停时长-条数等头部
                        uint32_t head_len = p_ms_sport_handle->sport_fixed_data_len;
                        ms_points_item_t points_item_head;
                        memset(&points_item_head, 0, sizeof(points_item_head));
                        memcpy(&points_item_head, &point_buff[offset_start], head_len);
                        offset_start += head_len;
                        switch (Get_current_sporting_type())
                        {
                        case SPORTING_Outdoor_running_TYPE:
                        case SPORTING_Outdoor_walking_TYPE:
                        case SPORTING_Outdoor_hiking_TYPE:
                        case SPORTING_Mountaineering_TYPE:
                        case SPORTING_Off_road_TYPE:
                        {
                            curren_hold = points_item_head.out_run_c.data_head.count_sport_hold;
                            if (interval_switch)
                            {
                                memset(file_str, 0, sizeof(file_str));
                                int len = snprintf(file_str,sizeof(file_str),"total_point_count:%d,restore_time:%d,segment_distance:%d,seg_type:%d,train_type:%d\n",
                                           points_item_head.out_run_c.data_head.count_sport_hold,
                                           points_item_head.out_run_c.data_head.restore_time,
                                           points_item_head.out_run_c.data_head.segment_distance,
                                           points_item_head.out_run_c.data_head.segment_type.st_s.segment_type,
                                           points_item_head.out_run_c.data_head.segment_type.st_s.training_type);
                                fwrite(file_str, len, sizeof(char), p_file);
                            }
                        }
                        break;
                        case SPORTING_Outdoor_cycling_TYPE:
                        {
                            curren_hold = points_item_head.out_non_run_c.data_head.count_sport_hold;
                            if (interval_switch)
                            {
                                memset(file_str, 0, sizeof(file_str));
                                int len = snprintf(file_str, sizeof(file_str), "total_point_count:%d,restore_time:%d,seg_type:%d,train_type:%d\n",
                                           points_item_head.out_non_run_c.data_head.count_sport_hold,
                                           points_item_head.out_non_run_c.data_head.restore_time,
                                           points_item_head.out_run_c.data_head.segment_type.st_s.segment_type,
                                           points_item_head.out_non_run_c.data_head.segment_type.st_s.training_type);
                                fwrite(file_str, len, sizeof(char), p_file);
                            }
                        }
                        break;
                        case SPORTING_Indoor_running_TYPE:
                        {
                            curren_hold = points_item_head.indoor_run.data_head.count_sport_hold;
                            if (interval_switch)
                            {
                                printf("total_point_count:%d,restore_time:%d,segment_distance:%d,seg_type:%d,train_type:%d\n",
                                           points_item_head.indoor_run.data_head.count_sport_hold,
                                           points_item_head.indoor_run.data_head.restore_time,
                                           points_item_head.indoor_run.data_head.segment_distance,
                                           points_item_head.indoor_run.data_head.segment_type.st_s.segment_type,
                                           points_item_head.indoor_run.data_head.segment_type.st_s.training_type);
                            }
                        }

                        break;
                        case SPORTING_Skipping_rope_H_TYPE:
                        {
                            curren_hold = points_item_head.rope_skip.data_head.count_sport_hold;
                            if (interval_switch)
                            {
                                printf("total_point_count:%d,restore_time:%d,segment_count:%d,seg_type:%d,train_type:%d\n",
                                           points_item_head.rope_skip.data_head.count_sport_hold,
                                           points_item_head.rope_skip.data_head.restore_time,
                                           points_item_head.rope_skip.data_head.segment_count,
                                           points_item_head.rope_skip.data_head.segment_type.st_s.segment_type,
                                           points_item_head.rope_skip.data_head.segment_type.st_s.training_type);
                            }
                        }
                        break;
                        case SPORTING_Elliptical_machine_TYPE:
                        {
                            curren_hold = points_item_head.elliptical_m.data_head.count_sport_hold;
                            if (interval_switch)
                            {
                                printf("total_point_count:%d,restore_time:%d,seg_type:%d,train_type:%d\n",
                                           points_item_head.elliptical_m.data_head.count_sport_hold,
                                           points_item_head.elliptical_m.data_head.restore_time,
                                           points_item_head.rope_skip.data_head.segment_type.st_s.segment_type,
                                           points_item_head.rope_skip.data_head.segment_type.st_s.training_type);
                            }
                        }
                        break;
                        case SPORTING_Rowing_machine_TYPE:
                            curren_hold = points_item_head.rowing_m.data_head.count_sport_hold;
                            if (interval_switch)
                            {
                                printf("total_point_count:%d,restore_time:%d,segment_times:%d,seg_type:%d,train_type:%d\n",
                                           points_item_head.rowing_m.data_head.count_sport_hold,
                                           points_item_head.rowing_m.data_head.restore_time,
                                           points_item_head.rowing_m.data_head.segment_times,
                                           points_item_head.rowing_m.data_head.segment_type.st_s.segment_type,
                                           points_item_head.rowing_m.data_head.segment_type.st_s.training_type);
                            }
                            break;
                        case SPORTING_swim_indoor_TYPE:  // 泳池游泳
                        case SPORTING_swim_outdoor_TYPE: // 开放水域游泳
                            curren_hold = points_item_head.swimming.data_head.count_sport_hold;
                            break;
                        default:
                            curren_hold = points_item_head.free_sport.data_head.count_sport_hold;
                            break;
                        }
                        uint32_t data_body_len = 0;
                        uint8_t sport_buf[50] = { 0 };// mul_spomalloc(512);
                        memset(sport_buf, 0, sizeof(sport_buf));
                        p_ms_sport_handle->pf_get_sport_data(sport_buf,&data_body_len);
                        printf("data_body_len:%d,hold:%d\n",data_body_len,curren_hold);
                       // free(sport_buf);
                         ms_record_info_t record_info;
                        if(Get_current_sporting_type() == SPORTING_swim_indoor_TYPE||
                        Get_current_sporting_type() == SPORTING_swim_outdoor_TYPE)                               
                        {
                            mul_sport_platform_get_record_info(&mul_id, &record_info);
                        }
                        while(curren_hold)
                        {
                            bool segment_flag = true;
                            switch (Get_current_sporting_type())
                            {
                            case SPORTING_Outdoor_running_TYPE:
                            case SPORTING_Outdoor_walking_TYPE:
                            case SPORTING_Outdoor_hiking_TYPE:
                            case SPORTING_Mountaineering_TYPE:
                            case SPORTING_Off_road_TYPE:
                               {
                                Outside_Run_Category_Data_Type_V5 outside_run_category_data;
                                memset(&outside_run_category_data, 0, sizeof(outside_run_category_data));
                                memcpy(&outside_run_category_data.data_s.data_body, &point_buff[offset_start], data_body_len);
                                offset_start+=data_body_len;
                                if (Get_current_sporting_type() == SPORTING_Outdoor_hiking_TYPE ||
                                    Get_current_sporting_type() == SPORTING_Mountaineering_TYPE ||
                                    Get_current_sporting_type() == SPORTING_Off_road_TYPE)
                                {
                                    memset(file_str, 0, sizeof(file_str));
                                    float speed = 0;//
                                    if (outside_run_category_data.data_s.data_body.pace)
                                        speed = 3600.f / (float)outside_run_category_data.data_s.data_body.pace;
                                    else
                                        speed = 0;
                                    int len = snprintf(file_str, sizeof(file_str), "i:%d,ext_kca:%d,extra_step:%d,hr:%d,h_chang:%d,is_km:%d,is_up:%d,ex_dis:%d,cadence:%d,stride:%d,pace:%d,speed:%0.2f\n",
                                        total_hold,
                                        outside_run_category_data.data_s.data_body.extra_calorie.ec_s.extra_calorie,
                                        outside_run_category_data.data_s.data_body.extra_calorie.ec_s.extra_step,
                                        outside_run_category_data.data_s.data_body.hr,
                                        outside_run_category_data.data_s.data_body.heigth_change.hc_s.height_change,
                                        outside_run_category_data.data_s.data_body.heigth_change.hc_s.is_km,
                                        outside_run_category_data.data_s.data_body.heigth_change.hc_s.is_up,
                                        outside_run_category_data.data_s.data_body.extra_distance,
                                        outside_run_category_data.data_s.data_body.cadence,
                                        outside_run_category_data.data_s.data_body.extra_stride,
                                        outside_run_category_data.data_s.data_body.pace,
                                        speed);
                                    fwrite(file_str, len, sizeof(char), p_file);
                                }
                                else
                                {
                                    memset(file_str, 0, sizeof(file_str));
                                    int len = snprintf(file_str,sizeof(file_str), "i:%d,ext_kca:%d,extra_step:%d,hr:%d,h_chang:%d,is_km:%d,is_up:%d,ex_dis:%d,cadence:%d,stride:%d,pace:%d\n",
                                        total_hold,
                                        outside_run_category_data.data_s.data_body.extra_calorie.ec_s.extra_calorie,
                                        outside_run_category_data.data_s.data_body.extra_calorie.ec_s.extra_step,
                                        outside_run_category_data.data_s.data_body.hr,
                                        outside_run_category_data.data_s.data_body.heigth_change.hc_s.height_change,
                                        outside_run_category_data.data_s.data_body.heigth_change.hc_s.is_km,
                                        outside_run_category_data.data_s.data_body.heigth_change.hc_s.is_up,
                                        outside_run_category_data.data_s.data_body.extra_distance,
                                        outside_run_category_data.data_s.data_body.cadence,
                                        outside_run_category_data.data_s.data_body.extra_stride,
                                        outside_run_category_data.data_s.data_body.pace);
                                    fwrite(file_str, len, sizeof(char), p_file);
                                }
                               }
                                break;
                            case SPORTING_Outdoor_cycling_TYPE:
                               {
                                switch(p_ms_sport_handle->data_ver)
                                {
                                case 3:
                                {
                                    Outside_Non_Running_Data_Type_V3 outside_non_running_data;

                                    memset(&outside_non_running_data, 0, sizeof(outside_non_running_data));
                                    memcpy(&outside_non_running_data.data_s.data_body, &point_buff[offset_start], data_body_len);
                                    offset_start += data_body_len;
                                    memset(file_str, 0, sizeof(file_str));
                                    int len = snprintf(file_str, sizeof(file_str), "i:%d,extra_calorie:%d,extra_count:%d,hr:%d,extra_distance:%d,speed:%d\n",
                                               total_hold,
                                               outside_non_running_data.data_s.data_body.extra_calorie.ec_s.extra_calorie,
                                               outside_non_running_data.data_s.data_body.extra_calorie.ec_s.extra_count,
                                               outside_non_running_data.data_s.data_body.hr,
                                               outside_non_running_data.data_s.data_body.extra_distance,
                                               outside_non_running_data.data_s.data_body.speed);
                                    fwrite(file_str, len, sizeof(char), p_file);
                                }
                                break;
                                default:
                                    break;
                                }
                               }                              
                                break;
                            case SPORTING_Indoor_running_TYPE://V6
                            {

                                Indoor_Run_Data_Type_V6 indoor_run_data;

                                memset(&indoor_run_data, 0, sizeof(indoor_run_data));
                                memcpy(&indoor_run_data.data_s.data_body, &point_buff[offset_start], data_body_len);
                                offset_start += data_body_len;
                                printf("i:%d,extra_calorie =%d,extra_step =%d,hr =%d,distance =%d,stride =%d,cadence =%d,pace =%d\n",
                                           total_hold,
                                           indoor_run_data.data_s.data_body.extra_calorie.ec_s.extra_calorie,
                                           indoor_run_data.data_s.data_body.extra_calorie.ec_s.extra_step,
                                           indoor_run_data.data_s.data_body.hr,
                                           indoor_run_data.data_s.data_body.extra_distance,
                                           indoor_run_data.data_s.data_body.extra_stride,
                                           indoor_run_data.data_s.data_body.cadence,
                                           indoor_run_data.data_s.data_body.pace);
                            }
                                break;
                            case SPORTING_Skipping_rope_H_TYPE://V5
                            {

                                Rope_Skipping_Data_Type_V5 rope_skipping_data;

                                memset(&rope_skipping_data, 0, sizeof(rope_skipping_data));
                                memcpy(&rope_skipping_data.data_s.data_body, &point_buff[offset_start], data_body_len);
                                offset_start += data_body_len;
                                printf("i:%d,hr =%d,extra_calorie =%d,cadence =%d\n",
                                           total_hold,
                                           rope_skipping_data.data_s.data_body.hr,
                                           rope_skipping_data.data_s.data_body.extra_calorie,
                                           rope_skipping_data.data_s.data_body.cadence);
                            }
                                break;
                            case SPORTING_Elliptical_machine_TYPE://椭圆机V3
                            {
                                Elliptical_Machine_Data_Type_V3 elliptical_machine_data;

                                memset(&elliptical_machine_data, 0, sizeof(elliptical_machine_data));
                                memcpy(&elliptical_machine_data.data_s.data_body, &point_buff[offset_start], data_body_len);
                                offset_start += data_body_len;
                                printf("i:%d,extra_calorie:%d,extra_step:%d,hr:%d,cadence:%d\n",
                                           total_hold,
                                           elliptical_machine_data.data_s.data_body.extra_calorie.ec_s.extra_calorie,
                                           elliptical_machine_data.data_s.data_body.extra_calorie.ec_s.extra_step,
                                           elliptical_machine_data.data_s.data_body.hr,
                                           elliptical_machine_data.data_s.data_body.cadence);
                            }
                                break;
                            case SPORTING_Rowing_machine_TYPE:
                            {
                                Rowing_Machine_Data_Type_V4 rowing_machine_data;

                                memset(&rowing_machine_data, 0, sizeof(rowing_machine_data));
                                memcpy(&rowing_machine_data.data_s.data_body, &point_buff[offset_start], data_body_len);
                                offset_start += data_body_len;
                                printf("i:%d,hr:%d,extra_calorie:%d,sliding_frequency:%d\n",
                                           total_hold,
                                           rowing_machine_data.data_s.data_body.hr,
                                           rowing_machine_data.data_s.data_body.extra_calorie,
                                           rowing_machine_data.data_s.data_body.sliding_frequency);
                            }
                                break;
                            case SPORTING_swim_indoor_TYPE:  // 泳池游泳
                            case SPORTING_swim_outdoor_TYPE: // 开放水域游泳
                            {
                                //进来先读头是小节还是段落
                                Swimming_Data_Type_V2  Swimming_Data;
                                memset(&Swimming_Data,0,sizeof(Swimming_Data));
                                memcpy(&Swimming_Data.data_s.data_body.section_data, &point_buff[offset_start], record_info.data_section_len);

                                bool is_detail_body = mul_sport_platform_get_record_is_detail_body(&mul_id, (uint8_t*)&Swimming_Data.data_s.data_body.section_data);
                                if(is_detail_body)
                                {
                                    memset(&Swimming_Data, 0, sizeof(Swimming_Data));
                                    memcpy(&Swimming_Data.data_s.data_body, &point_buff[offset_start], record_info.data_body_len);
                                    offset_start += record_info.data_body_len;
                                    printf("i:%d,total_distance:%d,total_calorie:%d,sport_calorie:%d\n", total_hold, Swimming_Data.data_s.data_body.total_distance, Swimming_Data.data_s.data_body.total_calorie, Swimming_Data.data_s.data_body.sport_calorie);
                                    printf("i:%d,data_type:%d,pace:%d,posture:%d\n", total_hold, Swimming_Data.data_s.data_body.section_data.data_type, Swimming_Data.data_s.data_body.section_data.pace, Swimming_Data.data_s.data_body.section_data.posture);
                                    printf("i:%d,swolf:%d,timestamp:%d,total_pull_count:%d\n", total_hold, Swimming_Data.data_s.data_body.section_data.swolf, Swimming_Data.data_s.data_body.section_data.timestamp, Swimming_Data.data_s.data_body.total_pull_count);
                                    printf("i:%d,total_turn_count:%d,pull_rate:%d,unknown_pull_count:%d\n", total_hold, Swimming_Data.data_s.data_body.total_turn_count, Swimming_Data.data_s.data_body.pull_rate, Swimming_Data.data_s.data_body.unknown_pull_count);
                                    printf("i:%d,breaststroke_pull_count:%d,freestyle_pull_count:%d,backstroke_pull_count:%d,butterfly_pull_count:%d\n", total_hold, Swimming_Data.data_s.data_body.breaststroke_pull_count, Swimming_Data.data_s.data_body.freestyle_pull_count, Swimming_Data.data_s.data_body.backstroke_pull_count, Swimming_Data.data_s.data_body.butterfly_pull_count);
                                }
                                else
                                {
                                    segment_flag = false;
                                    offset_start += record_info.data_section_len;
                                }
                            }
                                break;
                            default:
                            {
                                switch(p_ms_sport_handle->data_ver)
                                {
                                case 2:
                                {
                                    Free_Sport_Data_Type_V2 free_sport_data;

                                    memset(&free_sport_data, 0, sizeof(free_sport_data));
                                    memcpy(&free_sport_data.data_s.data_body, &point_buff[offset_start], data_body_len);
                                    offset_start += data_body_len;
                                    printf("i:%d,extra_calorie:%d,hr:%d\n",
                                               total_hold,
                                               free_sport_data.data_s.data_body.extra_calorie,
                                               free_sport_data.data_s.data_body.hr);
                                }
                                break;
                                default:
                                    break;
                                }
                            }
                                break;
                            }
                            curren_hold--;
                            if (Get_current_sporting_type() == SPORTING_swim_indoor_TYPE ||
                                Get_current_sporting_type() == SPORTING_swim_outdoor_TYPE)
                            {
                                if (segment_flag)
                                    total_hold++;
                            }
                            else
                            {
                                total_hold++;
                            }
                        }
                    }

                }
            }
            //free(file_header_p);
        }
        fclose(p_file);
        // offset_start+=p_ms_sport_handle->sport_fixed_data_len;
    }

}

void mul_sport_analysis_record(void)
{
    data_id_t data_id;
    memcpy(&data_id, &record_buff[0], sizeof(data_id_t));
    printf("tm:%d,zone:%d,ver:%d,data_type:%d,stype:%d,type:%d\n", data_id.timestamp, data_id.timezone, data_id.version, data_id.type_desc.data_type, data_id.type_desc.specific_type, data_id.type_desc.type);
    sport_analysis_type = mul_sport_analysis_sport_type(&data_id);
    uint32_t offset_start = 7;
    // 读取固定头部
    p_ms_abstract_config_t p_ms_sport_config = NULL;
    printf("sport_analysis_type:%d\n", sport_analysis_type);
    Set_current_sproting_type(sport_analysis_type);
   if (!mul_sport_get_cur_sport_config((void **)&p_ms_sport_config))
    {
        return;
    }
    bool ret_flag;
    p_ms_abstract_sport_handle_t p_ms_sport_handle = NULL; // 指针
    ret_flag = mul_sport_factory_get_sport(p_ms_sport_config, &p_ms_sport_handle);
    if (p_ms_sport_handle && p_ms_sport_config)
    {
        static ms_common_sport_list_v1_t s_ms_sport_list;

        s_ms_sport_list.ms_sport_list.magic_number = MUL_SPORT_MAGIC_NUMBER;
        s_ms_sport_list.ms_sport_list.version = MUL_SPORT_VER_1;
        s_ms_sport_list.ms_sport_list.ms_config = p_ms_sport_config;
        s_ms_sport_list.ms_sport_list.ms_handle = p_ms_sport_handle;
        p_ms_abstract_sport_list_t g_p_sport_list_item_obj_t = (p_ms_abstract_sport_list_t)&s_ms_sport_list;
        // p_ms_sport_handle->pf_get_sport_fixed_data()
        data_id_t repo_id;

        uint8_t repo_ver = s_ms_sport_list.ms_sport_list.ms_handle->repo_ver;
        repo_id.type_desc.specific_type = g_p_sport_list_item_obj_t->ms_config->sport_type;
        mul_sport_report_ver_special_handler((Sport_Type_Type)repo_id.type_desc.specific_type, &repo_ver);
        repo_id.type_desc.data_type = ENUM_REPORT_DATA_T;
        repo_id.version = repo_ver;

        // 读取头部
        uint8_t *file_header_ptr = NULL;
        size_t file_header_len = 0;

        mul_sport_platform_get_data_header_ptr(&repo_id, &file_header_ptr, &file_header_len);
        printf("%s,%d,%d\n", __func__, __LINE__, file_header_len);
        uint8_t file_header_p[100] = {0};// NULL;
        if (file_header_len)
        {
            //file_header_p = (uint8_t *)malloc(file_header_len);
            printf("%s,%d,offset_start:%d\n", __func__, __LINE__,offset_start);
            if (file_header_p && (sizeof(record_buff) > (offset_start + file_header_len)))
            {
                printf("%s,%d\n", __func__, __LINE__);
                memcpy((char*) & file_header_p[0], &record_buff[offset_start], file_header_len);
                offset_start += file_header_len;
                if (strcmp((char *)file_header_p, (char *)file_header_ptr) == 0) // 头部比对成功
                {
                    uint32_t data_body_len = 0;
                    uint8_t sport_buf[512] = {0};//mul_spomalloc(1024);
                    p_ms_sport_handle->pf_get_sport_repo(sport_buf, &data_body_len);
                    printf("type:%d,data_body_len:%d,off:%d\n", Get_current_sporting_type(),data_body_len,offset_start);
                    //free(sport_buf);
                    switch (Get_current_sporting_type())
                    {
                    case SPORTING_Outdoor_running_TYPE:
                    case SPORTING_Outdoor_walking_TYPE:
                    case SPORTING_Outdoor_hiking_TYPE:
                    case SPORTING_Mountaineering_TYPE:
                    case SPORTING_Off_road_TYPE:
                    {
                        if (data_id.version == 4)
                        {
                            Report_Outside_Run_Category_Data_Type_V4 outside_run_category_repo_data;

                            memset(&outside_run_category_repo_data, 0, sizeof(outside_run_category_repo_data));
                            memcpy(&outside_run_category_repo_data.data_s, &record_buff[offset_start], data_body_len);
                            offset_start += data_body_len;
                            printf("sub_sport_type=%d,sport_start_time=%d,sport_stop_time=%d\n",
                                outside_run_category_repo_data.data_s.sub_sport_type,
                                outside_run_category_repo_data.data_s.sport_start_time,
                                outside_run_category_repo_data.data_s.sport_stop_time);
                            printf("sport_total_time=%d,valid_exercise_time=%d,sport_total_distance=%d\n",
                                outside_run_category_repo_data.data_s.sport_total_time,
                                outside_run_category_repo_data.data_s.valid_exercise_time,
                                outside_run_category_repo_data.data_s.sport_total_distance);
                            printf("total_calorie=%d,sport_calorie=%d,high_speed=%d\n",
                                outside_run_category_repo_data.data_s.total_calorie,
                                outside_run_category_repo_data.data_s.sport_calorie,
                                outside_run_category_repo_data.data_s.high_speed);
                            printf("low_speed=%d,fast_speed=%lf,total_step=%d\n",
                                outside_run_category_repo_data.data_s.low_speed,
                                outside_run_category_repo_data.data_s.fast_speed,
                                outside_run_category_repo_data.data_s.total_step);
                            printf("max_step_rate=%d,avg_hr=%d,max_hr=%d\n",
                                outside_run_category_repo_data.data_s.max_step_rate,
                                outside_run_category_repo_data.data_s.avg_hr,
                                outside_run_category_repo_data.data_s.max_hr);
                            printf("min_hr=%d,total_up=%d,total_down=%d\n",
                                outside_run_category_repo_data.data_s.min_hr,
                                outside_run_category_repo_data.data_s.total_up,
                                outside_run_category_repo_data.data_s.total_down);
                            printf("avg_height=%d,max_height=%d,min_height=%d\n",
                                outside_run_category_repo_data.data_s.avg_height,
                                outside_run_category_repo_data.data_s.max_height,
                                outside_run_category_repo_data.data_s.min_height);
                            printf("hr_limit_time=%d,hr_without_oxygen=%d,hr_with_oxygen=%d\n",
                                outside_run_category_repo_data.data_s.hr_limit_time,
                                outside_run_category_repo_data.data_s.hr_without_oxygen,
                                outside_run_category_repo_data.data_s.hr_with_oxygen);
                            printf("hr_expend_fat=%d,hr_warmup=%d,target_duration=%d\n",
                                outside_run_category_repo_data.data_s.hr_expend_fat,
                                outside_run_category_repo_data.data_s.hr_warmup,
                                outside_run_category_repo_data.data_s.target_duration);
                            printf("target_calorie=%d,target_distance=%d,target_pace=%d\n",
                                outside_run_category_repo_data.data_s.target_calorie,
                                outside_run_category_repo_data.data_s.target_distance,
                                outside_run_category_repo_data.data_s.target_pace);
                            printf("target_cadence=%d,designated_courses=%d,genki_value=%d\n",
                                outside_run_category_repo_data.data_s.target_cadence,
                                outside_run_category_repo_data.data_s.designated_courses,
                                outside_run_category_repo_data.data_s.genki_value);
                        }
                        else if (data_id.version == 5)
                        {
                            Report_Outside_Run_Category_Data_Type_V5 outside_run_category_repo_data;

                            memset(&outside_run_category_repo_data, 0, sizeof(outside_run_category_repo_data));
                            memcpy(&outside_run_category_repo_data.data_s, &record_buff[offset_start], data_body_len);
                            offset_start += data_body_len;
                            printf("sub_sport_type:%d\n", outside_run_category_repo_data.data_s.sub_sport_type);
                            printf("sport_start_time:%d\n", outside_run_category_repo_data.data_s.sport_start_time);
                            printf("sport_stop_time:%d\n", outside_run_category_repo_data.data_s.sport_stop_time);
                            printf("sport_total_time:%d\n", outside_run_category_repo_data.data_s.sport_total_time);
                            printf("valid_exercise_time:%d\n", outside_run_category_repo_data.data_s.valid_exercise_time);
                            printf("sport_total_distance:%d\n", outside_run_category_repo_data.data_s.sport_total_distance);
                            printf("total_calorie:%d\n", outside_run_category_repo_data.data_s.total_calorie);
                            printf("sport_calorie:%d\n", outside_run_category_repo_data.data_s.sport_calorie);
                            printf("avg_pace:%d\n", outside_run_category_repo_data.data_s.avg_pace);
                            printf("high_pace:%d\n", outside_run_category_repo_data.data_s.high_pace);
                            printf("low_pace:%d\n", outside_run_category_repo_data.data_s.low_pace);
                            printf("avg_speed:%f\n", outside_run_category_repo_data.data_s.avg_speed);
                            printf("max_speed:%f\n", outside_run_category_repo_data.data_s.max_speed);
                            printf("total_step:%d\n", outside_run_category_repo_data.data_s.total_step);
                            printf("avg_stride:%d\n", outside_run_category_repo_data.data_s.avg_stride);
                            printf("avg_cadence:%d\n", outside_run_category_repo_data.data_s.avg_cadence);
                            printf("max_step_rate:%d\n", outside_run_category_repo_data.data_s.max_step_rate);
                            printf("avg_hr: %d\n",outside_run_category_repo_data.data_s.avg_hr);
                            printf("max_hr: %d\n",outside_run_category_repo_data.data_s.max_hr);
                            printf("min_hr: %d\n",outside_run_category_repo_data.data_s.min_hr);
                            printf("total_up:%f\n", outside_run_category_repo_data.data_s.total_up);
                            printf("total_down:%f\n", outside_run_category_repo_data.data_s.total_down);
                            printf("avg_height:%f\n", outside_run_category_repo_data.data_s.avg_height);
                            printf("max_height:%f\n", outside_run_category_repo_data.data_s.max_height);
                            printf("min_height:%f\n", outside_run_category_repo_data.data_s.min_height);
                            printf("training_effect:%f\n", outside_run_category_repo_data.data_s.training_effect);
                            printf("training_effect_rating: %d\n",outside_run_category_repo_data.data_s.training_effect_rating);
                                printf("anaerobic_training_effect:%f\n", outside_run_category_repo_data.data_s.anaerobic_training_effect);
                            printf("anaerobic_training_effect_rating: %d\n",outside_run_category_repo_data.data_s.anaerobic_training_effect_rating);
                                printf("max_oxygen_uptake: %d\n",outside_run_category_repo_data.data_s.max_oxygen_uptake);
                                    printf("max_oxygen_uptake_rating: %d\n",outside_run_category_repo_data.data_s.max_oxygen_uptake_rating);
                                        printf("body_power_use: %d\n",outside_run_category_repo_data.data_s.body_power_use);
                                            printf("recover_time:%d\n", outside_run_category_repo_data.data_s.recover_time);
                            printf("hr_zone_selection: %d\n",outside_run_category_repo_data.data_s.hr_zone_selection);
                                printf("hr_limit_time:%d\n", outside_run_category_repo_data.data_s.hr_limit_time);
                            printf("hr_without_oxygen:%d\n", outside_run_category_repo_data.data_s.hr_without_oxygen);
                            printf("hr_with_oxygen:%d\n", outside_run_category_repo_data.data_s.hr_with_oxygen);
                            printf("hr_expend_fat:%d\n", outside_run_category_repo_data.data_s.hr_expend_fat);
                            printf("hr_warmup:%d\n", outside_run_category_repo_data.data_s.hr_warmup);
                            printf("target_duration:%d\n", outside_run_category_repo_data.data_s.target_duration);
                            printf("target_calorie:%d\n", outside_run_category_repo_data.data_s.target_calorie);
                            printf("target_distance:%d\n", outside_run_category_repo_data.data_s.target_distance);
                            printf("target_pace:%d\n", outside_run_category_repo_data.data_s.target_pace);
                            printf("target_speed:%f\n", outside_run_category_repo_data.data_s.target_speed);
                            printf("target_cadence:%d\n", outside_run_category_repo_data.data_s.target_cadence);
                            printf("designated_courses: %d\n",outside_run_category_repo_data.data_s. designated_courses);
                            printf("training_load:%d\n", outside_run_category_repo_data.data_s.training_load);
                            printf("training_load_rating:%d\n", outside_run_category_repo_data.data_s.training_load_rating);
                            printf("running_power_index:%d\n", outside_run_category_repo_data.data_s.running_power_index);
                            printf("running_power_level:%d\n", outside_run_category_repo_data.data_s.running_power_level);
                            printf("training_status:%d\n", outside_run_category_repo_data.data_s.training_status);
                            printf("genki_value:%d\n", outside_run_category_repo_data.data_s.genki_value);
                            printf("full_palm_landing_time:%d\n", outside_run_category_repo_data.data_s.full_palm_landing_time);
                            printf("forehand_landing_time:%d\n", outside_run_category_repo_data.data_s.forehand_landing_time);
                            printf("hell_landing_time:%d\n", outside_run_category_repo_data.data_s.hell_landing_time);
                            printf("inversion_amplitude:%d\n", outside_run_category_repo_data.data_s.inversion_amplitude);
                            printf("main_landing_method:%d\n", outside_run_category_repo_data.data_s.main_landing_method);
                            printf("running_posture1:%d\n", outside_run_category_repo_data.data_s.running_posture1);
                            printf("running_posture2:%d\n", outside_run_category_repo_data.data_s.running_posture2);
                        }
                    }
                    break;
                    case SPORTING_Outdoor_cycling_TYPE:
                    {
                        switch (p_ms_sport_handle->repo_ver)
                        {
                        case 4:
                        {
                            Report_Outside_Non_Running_Data_Type_V4 outside_non_running_repo_data;
                            memset(&outside_non_running_repo_data, 0, sizeof(outside_non_running_repo_data));
                            memcpy(&outside_non_running_repo_data.data_s, &record_buff[offset_start], data_body_len);
                            offset_start += data_body_len;
                            printf("non_running_style_sub_sport_type:%d\n", outside_non_running_repo_data.data_s.non_running_style_sub_sport_type);
                            printf("sport_start_time:%d\n", outside_non_running_repo_data.data_s.sport_start_time);
                            printf("sport_stop_time:%d\n", outside_non_running_repo_data.data_s.sport_stop_time);
                            printf("sport_total_time:%d\n", outside_non_running_repo_data.data_s.sport_total_time);
                            printf("valid_exercise_time:%d\n", outside_non_running_repo_data.data_s.valid_exercise_time);
                            printf("sport_total_distance:%d\n", outside_non_running_repo_data.data_s.sport_total_distance);
                            printf("total_calorie:%d\n", outside_non_running_repo_data.data_s.total_calorie);
                            printf("sport_calorie:%d\n", outside_non_running_repo_data.data_s.sport_calorie);
                            printf("high_speed:%d\n", outside_non_running_repo_data.data_s.high_speed);
                            printf("low_speed:%d\n", outside_non_running_repo_data.data_s.low_speed);
                            printf("fast_speed:%lf\n", outside_non_running_repo_data.data_s.fast_speed);
                            printf("avg_hr:%d\n", outside_non_running_repo_data.data_s.avg_hr);
                            printf("max_hr:%d\n", outside_non_running_repo_data.data_s.max_hr);
                            printf("min_hr:%d\n", outside_non_running_repo_data.data_s.min_hr);
                            printf("total_up:%lf\n", outside_non_running_repo_data.data_s.total_up);
                            printf("total_down:%lf\n", outside_non_running_repo_data.data_s.total_down);
                            printf("avg_height:%lf\n", outside_non_running_repo_data.data_s.avg_height);
                            printf("max_height:%lf\n", outside_non_running_repo_data.data_s.max_height);
                            printf("min_height:%lf\n", outside_non_running_repo_data.data_s.min_height);
                            printf("hr_limit_time:%d\n", outside_non_running_repo_data.data_s.hr_limit_time);
                            printf("hr_without_oxygen:%d\n", outside_non_running_repo_data.data_s.hr_without_oxygen);
                            printf("hr_with_oxygen:%d\n", outside_non_running_repo_data.data_s.hr_with_oxygen);
                            printf("hr_expend_fat:%d\n", outside_non_running_repo_data.data_s.hr_expend_fat);
                            printf("hr_warmup:%d\n", outside_non_running_repo_data.data_s.hr_warmup);
                            printf("target_duration:%d\n", outside_non_running_repo_data.data_s.target_duration);
                            printf("target_calorie:%d\n", outside_non_running_repo_data.data_s.target_calorie);
                            printf("target_distance:%d\n", outside_non_running_repo_data.data_s.target_distance);
                            printf("target_speed:%d\n", outside_non_running_repo_data.data_s.target_speed);
                            printf("genki_value:%d\n", outside_non_running_repo_data.data_s.genki_value);
                        }
                        break;
                        default:
                            break;
                        }
                    }
                        break;
                    case SPORTING_Indoor_running_TYPE: // V9
                        switch (p_ms_sport_handle->repo_ver)
                        {
                        case 9:
                        {

                            Report_Indoor_Run_Data_Type_V9 indoor_run_repo_data;

                            memset(&indoor_run_repo_data, 0, sizeof(indoor_run_repo_data));

                            memset(&indoor_run_repo_data, 0, sizeof(indoor_run_repo_data));
                            memcpy(&indoor_run_repo_data.data_s, &record_buff[offset_start], data_body_len);
                            offset_start += data_body_len;
                            printf("sport_start_time =%d,sport_stop_time =%d,sport_total_time =%d\n",
                                indoor_run_repo_data.data_s.sport_start_time,
                                indoor_run_repo_data.data_s.sport_stop_time,
                                indoor_run_repo_data.data_s.sport_total_time);
                            printf("sport_total_distance =%d,sport_calorie =%d,high_speed =%d\n",
                                indoor_run_repo_data.data_s.sport_total_distance,
                                indoor_run_repo_data.data_s.sport_calorie,
                                indoor_run_repo_data.data_s.high_speed);
                            printf("low_speed =%d,total_step =%d,max_step_rate =%d\n",
                                indoor_run_repo_data.data_s.low_speed,
                                indoor_run_repo_data.data_s.total_step,
                                indoor_run_repo_data.data_s.max_step_rate);
                            printf("avg_hr =%d,max_hr =%d,min_hr =%d\n",
                                indoor_run_repo_data.data_s.avg_hr,
                                indoor_run_repo_data.data_s.max_hr,
                                indoor_run_repo_data.data_s.min_hr);
                            printf("training_effect =%lf,aerobic_training_effect =%lf,max_oxygen_uptake =%d\n",
                                indoor_run_repo_data.data_s.training_effect,
                                indoor_run_repo_data.data_s.aerobic_training_effect,
                                indoor_run_repo_data.data_s.max_oxygen_uptake);
                            printf("max_oxygen_uptake_rate =%d,body_power_use =%d,recover_time =%d\n",
                                indoor_run_repo_data.data_s.max_oxygen_uptake_rate,
                                indoor_run_repo_data.data_s.body_power_use,
                                indoor_run_repo_data.data_s.recover_time);
                            printf("hr_limit_time =%d,hr_without_oxygen =%d,hr_with_oxygen =%d\n",
                                indoor_run_repo_data.data_s.hr_limit_time,
                                indoor_run_repo_data.data_s.hr_without_oxygen,
                                indoor_run_repo_data.data_s.hr_with_oxygen);
                            printf("hr_expend_fat =%d,hr_warmup =%d,total_calorie =%d\n",
                                indoor_run_repo_data.data_s.hr_expend_fat,
                                indoor_run_repo_data.data_s.hr_warmup,
                                indoor_run_repo_data.data_s.total_calorie);
                            printf("valid_exercise_time =%d,anaerobic_training_effect =%d,anaerobic_training_effect_rate =%d\n",
                                indoor_run_repo_data.data_s.valid_exercise_time,
                                indoor_run_repo_data.data_s.anaerobic_training_effect,
                                indoor_run_repo_data.data_s.anaerobic_training_effect_rate);
                            printf("subtype =%d,designated_courses =%d,hr_zone_selection =%d\n",
                                indoor_run_repo_data.data_s.subtype,
                                indoor_run_repo_data.data_s.designated_courses,
                                indoor_run_repo_data.data_s.hr_zone_selection);
                            printf("target_duration =%d,target_calorie =%d,target_distance =%d\n",
                                indoor_run_repo_data.data_s.target_duration,
                                indoor_run_repo_data.data_s.target_calorie,
                                indoor_run_repo_data.data_s.target_distance);
                            printf("target_pace =%d,target_speed =%lf,target_cadence =%d\n",
                                indoor_run_repo_data.data_s.target_pace,
                                indoor_run_repo_data.data_s.target_speed,
                                indoor_run_repo_data.data_s.target_cadence);
                            printf("fixed_distance =%d,training_load =%d,training_load_rate =%d\n",
                                indoor_run_repo_data.data_s.fixed_distance,
                                indoor_run_repo_data.data_s.training_load,
                                indoor_run_repo_data.data_s.training_load_rate);
                            printf("running_power_index =%lf,running_power_level =%d,training_state =%d\n",
                                indoor_run_repo_data.data_s.running_power_index,
                                indoor_run_repo_data.data_s.running_power_level,
                                indoor_run_repo_data.data_s.training_state);
                            printf("genki_value =%d,full_palm_landing_time =%d,forehand_landing_time =%d\n",
                                indoor_run_repo_data.data_s.genki_value,
                                indoor_run_repo_data.data_s.full_palm_landing_time,
                                indoor_run_repo_data.data_s.forehand_landing_time);
                            printf("hell_landing_time =%d,inversion_amplitude =%d\n",
                                indoor_run_repo_data.data_s.hell_landing_time,
                                indoor_run_repo_data.data_s.inversion_amplitude);
                        }
                            break;
                        case 11:
                        {

                            Report_Indoor_Run_Data_Type_V11 indoor_run_repo_data;

                            memset(&indoor_run_repo_data, 0, sizeof(indoor_run_repo_data));

                            memset(&indoor_run_repo_data, 0, sizeof(indoor_run_repo_data));
                            memcpy(&indoor_run_repo_data.data_s, &record_buff[offset_start], data_body_len);
                            offset_start += data_body_len;
                            printf("sport_start_time:%d\n", indoor_run_repo_data.data_s.sport_start_time);
                            printf("sport_stop_time:%d\n", indoor_run_repo_data.data_s.sport_stop_time);
                            printf("sport_total_time:%d\n", indoor_run_repo_data.data_s.sport_total_time);
                            printf("sport_total_distance:%d\n", indoor_run_repo_data.data_s.sport_total_distance);
                            printf("sport_calorie:%d\n", indoor_run_repo_data.data_s.sport_calorie);
                            printf("avg_pace:%d\n", indoor_run_repo_data.data_s.avg_pace);
                            printf("fast_pace:%d\n", indoor_run_repo_data.data_s.fast_pace);
                            printf("low_pace:%d\n", indoor_run_repo_data.data_s.low_pace);
                            printf("total_step:%d\n", indoor_run_repo_data.data_s.total_step);
                            printf("avg_stride:%d\n", indoor_run_repo_data.data_s.avg_stride);
                            printf("avg_cadence:%d\n", indoor_run_repo_data.data_s.avg_cadence);
                            printf("max_step_rate:%d\n", indoor_run_repo_data.data_s.max_step_rate);
                            printf("avg_hr:%d\n", indoor_run_repo_data.data_s.avg_hr);
                            printf("max_hr:%d\n", indoor_run_repo_data.data_s.max_hr);
                            printf("min_hr:%d\n", indoor_run_repo_data.data_s.min_hr);
                                printf("aerobic_training_effect:%d\n", indoor_run_repo_data.data_s.aerobic_training_effect);
                            printf("max_oxygen_uptake:%d\n", indoor_run_repo_data.data_s.max_oxygen_uptake);
                            printf("max_oxygen_uptake_rate:%d\n", indoor_run_repo_data.data_s.max_oxygen_uptake_rate);
                            printf("body_power_use:%d\n", indoor_run_repo_data.data_s.body_power_use);
                            printf("recover_time:%d\n", indoor_run_repo_data.data_s.recover_time);
                            printf("hr_limit_time:%d\n", indoor_run_repo_data.data_s.hr_limit_time);
                            printf("hr_without_oxygen:%d\n", indoor_run_repo_data.data_s.hr_without_oxygen);
                            printf("hr_with_oxygen:%d\n", indoor_run_repo_data.data_s.hr_with_oxygen);
                            printf("hr_expend_fat:%d\n", indoor_run_repo_data.data_s.hr_expend_fat);
                            printf("hr_warmup:%d\n", indoor_run_repo_data.data_s.hr_warmup);
                            printf("total_calorie:%d\n", indoor_run_repo_data.data_s.total_calorie);
                            printf("valid_exercise_time:%d\n", indoor_run_repo_data.data_s.valid_exercise_time);
                                printf("anaerobic_training_effect_rate:%d\n", indoor_run_repo_data.data_s.anaerobic_training_effect_rate);
                            printf("subtype:%d\n", indoor_run_repo_data.data_s.subtype);
                            printf("designated_courses:%d\n", indoor_run_repo_data.data_s.designated_courses);
                            printf("hr_zone_selection:%d\n", indoor_run_repo_data.data_s.hr_zone_selection);
                            printf("target_duration:%d\n", indoor_run_repo_data.data_s.target_duration);
                            printf("target_calorie:%d\n", indoor_run_repo_data.data_s.target_calorie);
                            printf("target_distance:%d\n", indoor_run_repo_data.data_s.target_distance);
                            printf("target_pace:%d\n", indoor_run_repo_data.data_s.target_pace);
                                printf("target_cadence:%d\n", indoor_run_repo_data.data_s.target_cadence);
                            printf("fixed_distance:%d\n", indoor_run_repo_data.data_s.fixed_distance);
                            printf("training_load:%d\n", indoor_run_repo_data.data_s.training_load);
                            printf("training_load_rate:%d\n", indoor_run_repo_data.data_s.training_load_rate);
                                printf("running_power_level:%d\n", indoor_run_repo_data.data_s.running_power_level);
                            printf("training_state:%d\n", indoor_run_repo_data.data_s.training_state);
                            printf("s5_score:%d\n", indoor_run_repo_data.data_s.s5_score);
                            printf("s10_score:%d\n", indoor_run_repo_data.data_s.s10_score);
                            printf("s21_score:%d\n", indoor_run_repo_data.data_s.s21_score);
                            printf("s42_score:%d\n", indoor_run_repo_data.data_s.s42_score);
                            printf("genki_value:%d\n", indoor_run_repo_data.data_s.genki_value);
                            printf("full_palm_landing_time:%d\n", indoor_run_repo_data.data_s.full_palm_landing_time);
                            printf("forehand_landing_time:%d\n", indoor_run_repo_data.data_s.forehand_landing_time);
                            printf("hell_landing_time:%d\n", indoor_run_repo_data.data_s.hell_landing_time);
                            printf("inversion_amplitude:%d\n", indoor_run_repo_data.data_s.inversion_amplitude);
                            printf("main_landing_methods:%d\n", indoor_run_repo_data.data_s.main_landing_methods);
                            printf("running_posture_lead:%d\n", indoor_run_repo_data.data_s.running_posture_lead);
                            printf("running_posture_back:%d\n", indoor_run_repo_data.data_s.running_posture_back);
                            printf("avg_landing_impact_force:%d\n", indoor_run_repo_data.data_s.avg_landing_impact_force);
                            printf("max_landing_impact_force:%d\n", indoor_run_repo_data.data_s.max_landing_impact_force);
                            printf("avg_touchdown_time:%d\n", indoor_run_repo_data.data_s.avg_touchdown_time);
                                printf("avg_air_time:%d\n", indoor_run_repo_data.data_s.avg_air_time);
                            printf("max_air_time:%d\n", indoor_run_repo_data.data_s.max_air_time);
                            printf("avg_ground_to_air_ratio:%d\n", indoor_run_repo_data.data_s.avg_ground_to_air_ratio);
                            printf("min_ground_to_air_ratio:%d\n", indoor_run_repo_data.data_s.min_ground_to_air_ratio);
                            printf("train_k:%d\n", indoor_run_repo_data.data_s.train_k);
                        }
                            break;
                        }

                
                    break;
                    case SPORTING_Skipping_rope_H_TYPE:
                    {

                        Report_Rope_Skipping_Data_Type_V5 rope_skipping_repo_data;

                        memset(&rope_skipping_repo_data, 0, sizeof(rope_skipping_repo_data));
                        memcpy(&rope_skipping_repo_data.data_s, &record_buff[offset_start], data_body_len);
                        offset_start += data_body_len;
                        printf("sport_start_time%d\n",rope_skipping_repo_data.data_s.sport_start_time);
                        printf("sport_stop_time%d\n",rope_skipping_repo_data.data_s.sport_stop_time);
                        printf("sport_total_time%d\n",rope_skipping_repo_data.data_s.sport_total_time);
                        printf("sport_calorie%d\n",rope_skipping_repo_data.data_s.sport_calorie);
                        printf("avg_hr%d\n",rope_skipping_repo_data.data_s.avg_hr);
                        printf("max_hr%d\n",rope_skipping_repo_data.data_s.max_hr);
                        printf("min_hr%d\n",rope_skipping_repo_data.data_s.min_hr);
                        printf("training_effect%f\n",rope_skipping_repo_data.data_s.training_effect);
                        printf("training_effect_rate%d\n",rope_skipping_repo_data.data_s.training_effect_rate);
                        printf("body_power_use%d\n",rope_skipping_repo_data.data_s.body_power_use);
                        printf("recover_time%d\n",rope_skipping_repo_data.data_s.recover_time);
                        printf("hr_limit_time%d\n",rope_skipping_repo_data.data_s.hr_limit_time);
                        printf("hr_without_oxygen%d\n",rope_skipping_repo_data.data_s.hr_without_oxygen);
                        printf("hr_with_oxygen%d\n",rope_skipping_repo_data.data_s.hr_with_oxygen);
                        printf("hr_expend_fat%d\n",rope_skipping_repo_data.data_s.hr_expend_fat);
                        printf("hr_warmup%d\n",rope_skipping_repo_data.data_s.hr_warmup);
                        printf("total_calorie%d\n",rope_skipping_repo_data.data_s.total_calorie);
                        printf("total_jumps%d\n",rope_skipping_repo_data.data_s.total_jumps);
                        printf("avg_jump_freq%d\n",rope_skipping_repo_data.data_s.avg_jump_freq);
                        printf("best_jump_freq%d\n",rope_skipping_repo_data.data_s.best_jump_freq);
                        printf("total_rest_time%d\n",rope_skipping_repo_data.data_s.total_rest_time);
                        printf("avg_takeoff_height%d\n",rope_skipping_repo_data.data_s.avg_takeoff_height);
                        printf("max_takeoff_height%d\n",rope_skipping_repo_data.data_s.max_takeoff_height);
                        printf("min_takeoff_height%d\n",rope_skipping_repo_data.data_s.min_takeoff_height);
                        printf("airborne_time%d\n",rope_skipping_repo_data.data_s.airborne_time);
                        printf("acting%d\n",rope_skipping_repo_data.data_s.acting);
                        printf("group_cnts%d\n",rope_skipping_repo_data.data_s.group_cnts);
                        printf("valid_exercise_time%d\n",rope_skipping_repo_data.data_s.valid_exercise_time);
                        printf("anaerobic_training_effect%d\n",rope_skipping_repo_data.data_s.anaerobic_training_effect);
                        printf("anaerobic_training_effect_rate%d\n",rope_skipping_repo_data.data_s.anaerobic_training_effect_rate);
                        printf("designated_courses%d\n",rope_skipping_repo_data.data_s.designated_courses);
                        printf("hr_zone_selection%d\n",rope_skipping_repo_data.data_s.hr_zone_selection);
                        printf("target_duration%d\n",rope_skipping_repo_data.data_s.target_duration);
                        printf("target_calorie%d\n",rope_skipping_repo_data.data_s.target_calorie);
                        printf("target_times%d\n",rope_skipping_repo_data.data_s.target_times);
                        printf("total_stumbles%d\n",rope_skipping_repo_data.data_s.total_stumbles);
                        printf("training_load%d\n",rope_skipping_repo_data.data_s.training_load);
                        printf("training_load_rate%d\n",rope_skipping_repo_data.data_s.training_load_rate);
                        printf("genki_value%d\n",rope_skipping_repo_data.data_s.genki_value);
                    }
                    break;
                    case SPORTING_Elliptical_machine_TYPE:
                    {

                        Report_Elliptical_Machine_Data_Type_V5 elliptical_machine_repo_data;

                        memset(&elliptical_machine_repo_data, 0, sizeof(elliptical_machine_repo_data));

                        memcpy(&elliptical_machine_repo_data.data_s, &record_buff[offset_start], data_body_len);
                        offset_start += data_body_len;
                        printf("sport_start_time:%d\n", elliptical_machine_repo_data.data_s.sport_start_time);
                        printf("sport_stop_time:%d\n", elliptical_machine_repo_data.data_s.sport_stop_time);
                        printf("sport_total_time:%d\n", elliptical_machine_repo_data.data_s.sport_total_time);
                        printf("sport_calorie:%d\n", elliptical_machine_repo_data.data_s.sport_calorie);
                        printf("total_step:%d\n", elliptical_machine_repo_data.data_s.total_step);
                        printf("max_step_rate:%d\n", elliptical_machine_repo_data.data_s.max_step_rate);
                        printf("avg_hr:%d\n", elliptical_machine_repo_data.data_s.avg_hr);
                        printf("max_hr:%d\n", elliptical_machine_repo_data.data_s.max_hr);
                        printf("min_hr:%d\n", elliptical_machine_repo_data.data_s.min_hr);
                        printf("hr_limit_time:%d\n", elliptical_machine_repo_data.data_s.hr_limit_time);
                        printf("hr_without_oxygen:%d\n", elliptical_machine_repo_data.data_s.hr_without_oxygen);
                        printf("hr_with_oxygen:%d\n", elliptical_machine_repo_data.data_s.hr_with_oxygen);
                        printf("hr_expend_fat:%d\n", elliptical_machine_repo_data.data_s.hr_expend_fat);
                        printf("hr_warmup:%d\n", elliptical_machine_repo_data.data_s.hr_warmup);
                        printf("total_calorie:%d\n", elliptical_machine_repo_data.data_s.total_calorie);
                        printf("target_duration:%d\n", elliptical_machine_repo_data.data_s.target_duration);
                        printf("target_calorie:%d\n", elliptical_machine_repo_data.data_s.target_calorie);
                        printf("target_cadence:%d\n", elliptical_machine_repo_data.data_s.target_cadence);
                        printf("genki_value:%d\n", elliptical_machine_repo_data.data_s.genki_value);
                    }
                        break;
                    case SPORTING_Rowing_machine_TYPE:
                    {

                        Report_Rowing_Machine_Data_Type_V6 rowing_machine_repo_data;

                        memset(&rowing_machine_repo_data, 0, sizeof(rowing_machine_repo_data));
                        memcpy(&rowing_machine_repo_data.data_s, &record_buff[offset_start], data_body_len);
                        offset_start += data_body_len;
                        printf("sport_start_time:%d\n", rowing_machine_repo_data.data_s.sport_start_time);
                        printf("sport_stop_time:%d\n", rowing_machine_repo_data.data_s.sport_stop_time);
                        printf("sport_total_time:%d\n", rowing_machine_repo_data.data_s.sport_total_time);
                        printf("sport_calorie:%d\n", rowing_machine_repo_data.data_s.sport_calorie);
                        printf("avg_hr:%d\n", rowing_machine_repo_data.data_s.avg_hr);
                        printf("max_hr:%d\n", rowing_machine_repo_data.data_s.max_hr);
                        printf("min_hr:%d\n", rowing_machine_repo_data.data_s.min_hr);
                        printf("hr_limit_time:%d\n", rowing_machine_repo_data.data_s.hr_limit_time);
                        printf("hr_without_oxygen:%d\n", rowing_machine_repo_data.data_s.hr_without_oxygen);
                        printf("hr_with_oxygen:%d\n", rowing_machine_repo_data.data_s.hr_with_oxygen);
                        printf("hr_expend_fat:%d\n", rowing_machine_repo_data.data_s.hr_expend_fat);
                        printf("hr_warmup:%d\n", rowing_machine_repo_data.data_s.hr_warmup);
                        printf("total_calorie:%d\n", rowing_machine_repo_data.data_s.total_calorie);
                        printf("total_strokes:%d\n", rowing_machine_repo_data.data_s.total_strokes);
                        printf("avg_stroke_freq:%d\n", rowing_machine_repo_data.data_s.avg_stroke_freq);
                        printf("best_stroke_freq:%d\n", rowing_machine_repo_data.data_s.best_stroke_freq);
                        printf("target_duration:%d\n", rowing_machine_repo_data.data_s.target_duration);
                        printf("target_calorie:%d\n", rowing_machine_repo_data.data_s.target_calorie);
                        printf("target_times:%d\n", rowing_machine_repo_data.data_s.target_times);
                        printf("genki_value:%d\n", rowing_machine_repo_data.data_s.genki_value);
                    }
                        break;
                    case SPORTING_swim_indoor_TYPE:  // 泳池游泳
                    case SPORTING_swim_outdoor_TYPE: // 开放水域游泳
                    {
                        Report_Swimming_Data_Type_V6   report_swimming_data ;
                        memset(&report_swimming_data, 0, sizeof(report_swimming_data));
                        memcpy(&report_swimming_data.data_s, &record_buff[offset_start], data_body_len);
                        offset_start += data_body_len;
                        printf("sport_start_time:%d\n", report_swimming_data.data_s.sport_start_time);
                        printf("sport_stop_time:%d\n", report_swimming_data.data_s.sport_stop_time);
                        printf("sport_total_time:%d\n", report_swimming_data.data_s.sport_total_time);
                        printf("sport_total_distance:%d\n", report_swimming_data.data_s.sport_total_distance);
                        printf("sport_calorie:%d\n", report_swimming_data.data_s.sport_calorie);
                        printf("high_speed:%d\n", report_swimming_data.data_s.high_speed);
                        printf("low_speed:%d\n", report_swimming_data.data_s.low_speed);
                        printf("body_power_use:%d\n", report_swimming_data.data_s.body_power_use);
                        printf("recover_time:%d\n", report_swimming_data.data_s.recover_time);
                        printf("arm_pull_count:%d\n", report_swimming_data.data_s.arm_pull_count);
                        printf("posture:%d\n", report_swimming_data.data_s.posture);
                        printf("pull_rate:%d\n", report_swimming_data.data_s.pull_rate);
                        printf("turn_count:%d\n", report_swimming_data.data_s.turn_count);
                        printf("avg_swolf:%d\n", report_swimming_data.data_s.avg_swolf);
                        printf("best_swolf:%d\n", report_swimming_data.data_s.best_swolf);
                        printf("pool_width:%d\n", report_swimming_data.data_s.pool_width);
                        printf("total_calorie:%d\n", report_swimming_data.data_s.total_calorie);
                        printf("valid_exercise_time:%d\n", report_swimming_data.data_s.valid_exercise_time);
                        printf("target_time:%d\n", report_swimming_data.data_s.target_time);
                        printf("target_calorie:%d\n", report_swimming_data.data_s.target_calorie);
                        printf("target_distance:%d\n", report_swimming_data.data_s.target_distance);
                        printf("target_pace:%d\n", report_swimming_data.data_s.target_pace);
                        printf("target_times:%d\n", report_swimming_data.data_s.target_times);
                        printf("training_effect:%d\n", report_swimming_data.data_s.training_effect);
                        printf("training_effect_rate:%d\n", report_swimming_data.data_s.training_effect_rate);
                        printf("anaerobic_training_effect_rate:%d\n", report_swimming_data.data_s.anaerobic_training_effect_rate);
                        printf("training_load:%d\n", report_swimming_data.data_s.training_load);
                        printf("training_load_rate:%d\n", report_swimming_data.data_s.training_load_rate);
                        printf("genki_value:%d\n", report_swimming_data.data_s.genki_value);
                    }
                    break;
                    default:
                    {
                        switch (p_ms_sport_handle->repo_ver)
                        {
                        case 8:
                        {
                            Repofree_Sport_Data_Type_V8 free_sport_repo_data;
                            memset(&free_sport_repo_data, 0, sizeof(free_sport_repo_data));
                            memcpy(&free_sport_repo_data.data_s, &record_buff[offset_start], data_body_len);
                            offset_start += data_body_len;
                            printf("sport_start_time:%d\n", free_sport_repo_data.data_s.sport_start_time);
                            printf("sport_stop_time:%d\n", free_sport_repo_data.data_s.sport_stop_time);
                            printf("sport_total_time:%d\n", free_sport_repo_data.data_s.sport_total_time);
                            printf("sport_calorie:%d\n", free_sport_repo_data.data_s.sport_calorie);
                            printf("avg_hr:%d\n", free_sport_repo_data.data_s.avg_hr);
                            printf("max_hr:%d\n", free_sport_repo_data.data_s.max_hr);
                            printf("min_hr:%d\n", free_sport_repo_data.data_s.min_hr);
                            printf("hr_limit_time:%d\n", free_sport_repo_data.data_s.hr_limit_time);
                            printf("hr_without_oxygen:%d\n", free_sport_repo_data.data_s.hr_without_oxygen);
                            printf("hr_with_oxygen:%d\n", free_sport_repo_data.data_s.hr_with_oxygen);
                            printf("hr_expend_fat:%d\n", free_sport_repo_data.data_s.hr_expend_fat);
                            printf("hr_warmup:%d\n", free_sport_repo_data.data_s.hr_warmup);
                            printf("total_calorie:%d\n", free_sport_repo_data.data_s.total_calorie);
                            printf("valid_exercise_time:%d\n", free_sport_repo_data.data_s.valid_exercise_time);
                            printf("free_style_sub_sport_type:%d\n", free_sport_repo_data.data_s.free_style_sub_sport_type);
                            printf("target_duration:%d\n", free_sport_repo_data.data_s.target_duration);
                            printf("target_calorie:%d\n", free_sport_repo_data.data_s.target_calorie);
                            printf("genki_value:%d\n", free_sport_repo_data.data_s.genki_value);
                        }
                        break;
                        default:
                            break;
                        }
                    }
                        break;
                    }
                }
                // offset_start+=p_ms_sport_handle->sport_fixed_data_len;
            }
        }
    }
}

void mul_sport_analysis_gps_points(void)
{
    uint32_t offset_start = 7;
    // 读取固定头部
    //data_id_t* p_data_id = (data_id_t*)malloc(sizeof(data_id_t));
    data_id_t data_id;
#if USE_BINARY_FILES
    FILE* ft_file = fopen("gps_points.bin", "rb + ");
    //FILE* ft_file = zh_flash_open("./gps_points.bin", "rb+");
    
 printf("!!!!!!!!!!!!!!!!!!!!ft_file:0x%x\n", ft_file);
    if (ft_file == NULL)
    {
        printf("ft_file:0x%x\n", ft_file);
        return;
    }
    size_t file_size = zh_flash_get_file_size("gps_points.bin");
    fread(&data_id, 1, sizeof(data_id_t), ft_file);
    //memcpy(&data_id, p_data_id, sizeof(data_id_t));
    //free(p_data_id);
    printf("%s,end:%d\n", __func__,data_id.version);
#else
    memcpy(&data_id, &gps_point_buff[0], sizeof(data_id_t));
#endif
    data_id.type_desc.data_type = ENUM_SPORT_GPS_DATA_T;
    //data_id.version = gps_version;
    
    uint32_t len = 0;
    uint8_t buff[50] = {0};
    uint32_t data_body_len = 0;
    p_ms_abstract_gps_handle_t g_p_ms_gps_handle_obj = NULL;
    g_p_ms_gps_handle_obj = mul_sport_get_gps_handle_obj(data_id.version);

    if (!g_p_ms_gps_handle_obj)
    {
        return;
    }
    ms_gps_item_t gps_item;
    gps_item.gps_v1.ts = 0;
    uint32_t index = 1;
    g_p_ms_gps_handle_obj->pf_get_gps_data(buff, &data_body_len, gps_item);
      uint8_t *file_header_ptr = NULL;
      char file_str[256 * 4] = { 0 };
      FILE* pgps_file = fopen("gps.txt", "w");
      if (pgps_file == NULL)
      {
          printf("open fail\n");
          return;
     }
      printf("data_body_len:%d\n", data_body_len);
    if (mul_sport_platform_get_data_header_ptr(&data_id, &file_header_ptr, &len))
    {
        offset_start += len;
#if USE_BINARY_FILES
        while ((file_size >= (offset_start + data_body_len)))
#else
        while ((sizeof(gps_point_buff) >= (offset_start + data_body_len)))
#endif
        {
            switch (data_id.version)
            {
            case 0x01:
            {
                ms_gps_v1_t gps_data;
                memset(&gps_data, 0, sizeof(gps_data));
#if USE_BINARY_FILES
                zh_flash_read(ft_file, offset_start, (uint8_t *)&gps_data, sizeof(ms_gps_v1_t));
#else
                memcpy(&gps_data, &gps_point_buff[offset_start], data_body_len);
#endif
                offset_start += data_body_len;
                char tmp_buff[1024] ;
                memset(tmp_buff,0,sizeof(tmp_buff));
                snprintf(tmp_buff,sizeof(tmp_buff),"index:%d,gps_timestamp:%d,gps_longitude:%f,gps_latitude:%f",index,gps_data.gps_timestamp, gps_data.gps_longitude, gps_data.gps_latitude);
                index++;
            }
            break;
            case 0x02:
            {
                ms_gps_v2_t gps_data;
                memset(&gps_data, 0, sizeof(gps_data));
#if USE_BINARY_FILES
                zh_flash_read(ft_file, offset_start, (uint8_t *)&gps_data, sizeof(ms_gps_v2_t));
#else
                memcpy(&gps_data, &gps_point_buff[offset_start], data_body_len);
#endif
                offset_start += data_body_len;
                //char tmp_buff[1024];
                memset(file_str, 0, sizeof(file_str));
                UTCTimeStruct start_time;
                ConvertToUTCTime(&start_time, (gps_data.gps_timestamp + get_time_zone_offset(data_id.timezone)));
                uint16_t year;
                uint8_t month, day, hour, minute;
                year = start_time.year;
                month = start_time.month + 1;
                day = start_time.day + 1;
                hour = start_time.hour;
                minute = start_time.minutes;
                uint32_t len = snprintf(file_str, sizeof(file_str), "%d/%02d/%02d %02d:%02d:%02d,gps_longitude:%f,gps_latitude:%f,location_speed:%f,location_accuracy:%f\n", year,month,day,hour,minute, start_time.seconds, gps_data.gps_longitude, gps_data.gps_latitude, (float)gps_data.speed_gps_u.speed_gps_s.location_speed / (float)10.f, gps_data.location_accuracy);
                index++;
               // printf("len:%d\n", len);
               fwrite(file_str, len, sizeof(char), pgps_file);
            }
                break;
            default:
                break;
            }
        }
    }
    printf("offset_start:%d,%d\n", offset_start, sizeof(gps_point_buff));
    fclose(pgps_file);
#if USE_BINARY_FILES
    zh_flash_close(ft_file);
#endif
}
const uint8_t  g_daily_point_header_v3_buf[] = { 0x00, 0xBE, 0xEC, 0xC0, 0x0C, 0xC0 };
const uint8_t  g_daily_report_header_v3_buf[] = { 0x00, 0xFF, 0xF9, 0xF8 };
const uint8_t  g_daily_report_header_v5_buf[] = { 0x00, 0xFF, 0xFD, 0xF8, 0xFC };
void mul_sport_analysis_daily_data_points(void)
{
    uint32_t offset_start = 7;
    // 读取固定头部
    data_id_t data_id;
#if USE_BINARY_FILES
    //FILE * ft_file = zh_flash_open("daily_points.bin", "rb");
    FILE* ft_file = fopen("daily_points.bin", "rb + ");

    printf("%s,ft_file:0x % x\n", __func__,ft_file);
    if (ft_file == NULL)
    {
        printf("ft_file:0x%x\n", ft_file);
        return;
    }
    printf("!!!!!!!!!!!!!!!!!!!!ft_file:0x%x\n", ft_file);
    size_t file_size = zh_flash_get_file_size("daily_points.bin");
    zh_flash_read(ft_file,0,(uint8_t*)&data_id,sizeof(data_id));
#else
    memcpy(&data_id, &daily_data_point[0], sizeof(data_id_t));
#endif
    data_id.type_desc.data_type = ENUM_POINT_DATA_T;
    //data_id.version = gps_version;
    uint8_t data_body_len = 9;//default
    uint8_t head_len = sizeof(g_daily_point_header_v3_buf);
    bool flag = false;
    printf("daily_start:%d,%d,version:%d\n", data_id.timestamp, data_id.timezone, data_id.version);
    switch (data_id.version)
    {
    case 0x2:
        break;
    case 0x3:
    {
        uint8_t buff[sizeof(g_daily_point_header_v3_buf)+1] = {0};
        memset(buff, 0, sizeof(buff));
#if USE_BINARY_FILES
        zh_flash_read(ft_file, 7, (uint8_t *)buff, sizeof(g_daily_point_header_v3_buf));
#else
        memcpy(buff, &daily_data_point[7], sizeof(g_daily_point_header_v3_buf));
#endif

        if (strcmp(buff, g_daily_point_header_v3_buf) == 0)
        {
            flag = true;
            head_len = sizeof(g_daily_point_header_v3_buf);
        }
        else if(strcmp(buff, &g_daily_point_header_v3_buf[1]) == 0)//安卓这么走
        {
            flag = true;
            head_len = sizeof(g_daily_point_header_v3_buf)-sizeof(uint8_t);//减去压缩
        }
        data_body_len = 9;
        printf("flag:%d,%d\n", flag, head_len);
    }
    break;
    default:
    {

    }
    break;
    }
    if (flag)
    {
        uint8_t* file_header_ptr = NULL;
        char file_str[256 * 4] = { 0 };
        FILE* pgps_file = fopen("daily_point.txt", "w");
        if (pgps_file == NULL)
        {
            printf("open fail\n");
            return;
        }
        printf("data_body_len:%d\n", data_body_len);
            offset_start += head_len;
            uint32_t index = 0;
#if USE_BINARY_FILES
            while ((file_size >= (offset_start + data_body_len)))
#else
            while ((sizeof(daily_data_point) >= (offset_start + data_body_len)))
#endif
            {
                switch (data_id.version)
                {
                case 0x03:
                {
                    Point_Activity_Day_Type point_data;
                    memset(&point_data, 0, sizeof(point_data));
#if USE_BINARY_FILES
                    zh_flash_read(ft_file, offset_start, (uint8_t *)&point_data, sizeof(Point_Activity_Day_Type));
#else
                    memcpy(&point_data, &daily_data_point[offset_start], data_body_len);
#endif
                    offset_start += data_body_len;
                    char tmp_buff[1024];
                    memset(tmp_buff, 0, sizeof(tmp_buff));
                    UTCTimeStruct start_time;
                    ConvertToUTCTime(&start_time, (data_id.timestamp + 60 * index+ get_time_zone_offset(data_id.timezone)));
                    uint16_t year;
                    uint8_t month, day, hour, minute;
                    year = start_time.year;
                    month = start_time.month + 1;
                    day = start_time.day + 1;
                    hour = start_time.hour;
                    minute = start_time.minutes;
                    uint16_t len = snprintf(tmp_buff, sizeof(tmp_buff), "%d/%02d/%02d %02d:%02d,extra_step:%d,extra_cal:%d\n", year, month, day, hour, minute, point_data.data_s.step.step_s.extra_step, point_data.data_s.sports_type.sports_type_s.extra_cal);
                    index++;
                    fwrite(tmp_buff, len, sizeof(char), pgps_file);
                }
                break;
                default:
                    break;
                }
            }
        printf("offset_start:%d,%d\n", offset_start, sizeof(daily_data_point));
        fclose(pgps_file);
    }
#if USE_BINARY_FILES
    zh_flash_close(ft_file);
#endif
}

void mul_sport_analysis_daily_data_record(void)
{
    uint32_t offset_start = 7;
    // 读取固定头部
    data_id_t data_id;
#if USE_BINARY_FILES
    FILE* ft_file = fopen("daily_record.bin", "rb + ");

    printf("%s,ft_file:0x % x\n", __func__, ft_file);
    if (ft_file == NULL)
    {
        printf("ft_file:0x%x\n", ft_file);
        return;
    }
    size_t file_size = zh_flash_get_file_size("daily_record.bin");
    zh_flash_read(ft_file,0,(uint8_t*)&data_id,sizeof(data_id));
#else
    memcpy(&data_id, &daily_data_record[0], sizeof(data_id_t));
#endif
    //data_id.version = gps_version;
    uint8_t data_body_len = 9;//default
    uint8_t head_len = sizeof(g_daily_report_header_v5_buf);
    bool flag = false;
    printf("daily_start:%d,%d,version:%d\n", data_id.timestamp, data_id.timezone, data_id.version);
    switch (data_id.version)
    {
    case 0x2:
        break;
    case 0x3:
    {
    }
    break;
    case 0x5:
    {
        uint8_t buff[sizeof(g_daily_report_header_v5_buf) + 1] = { 0 };
        memset(buff, 0, sizeof(buff));
#if USE_BINARY_FILES
        zh_flash_read(ft_file, 7, buff, sizeof(buff));
#else
        memcpy(buff, &daily_data_record[7], sizeof(g_daily_report_header_v5_buf));
#endif
        if (strcmp(buff, g_daily_report_header_v5_buf) == 0)
        {
            flag = true;
        }
        else if (strcmp(buff, &g_daily_report_header_v5_buf[1]) == 0)//安卓这么走
        {
            flag = true;
            head_len = sizeof(g_daily_report_header_v5_buf) - sizeof(uint8_t);//减去压缩
        }
        Report_Activity_Day_Type record;
        data_body_len = sizeof(record.data_s);
        head_len = sizeof(g_daily_report_header_v5_buf);
        printf("flag:%d\n", flag);
    }
    break;
    default:
    {
    }
    break;
    }
    if (flag)
    {
        uint8_t* file_header_ptr = NULL;
        char file_str[256 * 4] = { 0 };
        FILE* pgps_file = fopen("daily_record.txt", "w");
        if (pgps_file == NULL)
        {
            printf("open fail\n");
            return;
        }
        printf("data_body_len:%d\n", data_body_len);
        offset_start += head_len;
        uint32_t index = 0;
#if USE_BINARY_FILES
        while ((file_size >= (offset_start + data_body_len)))
#else
        while ((sizeof(daily_data_record) >= (offset_start + data_body_len)))
#endif
        {
            switch (data_id.version)
            {
            case 0x05:
            {
                Report_Activity_Day_Type record_data;
                memset(&record_data, 0, sizeof(record_data));
               
#if USE_BINARY_FILES
                zh_flash_read(ft_file, offset_start, (uint8_t *)&record_data, data_body_len);
#else
                memcpy(&record_data, &daily_data_record[offset_start], data_body_len);
#endif
                offset_start += data_body_len;
                char tmp_buff[1024];
                memset(tmp_buff, 0, sizeof(tmp_buff));
                UTCTimeStruct start_time;
                ConvertToUTCTime(&start_time, (data_id.timestamp + 60 * index + get_time_zone_offset(data_id.timezone)));
                uint16_t year;
                uint8_t month, day, hour, minute;
                year = start_time.year;
                month = start_time.month + 1;
                day = start_time.day + 1;
                hour = start_time.hour;
                minute = start_time.minutes;
               uint16_t len = snprintf(tmp_buff, sizeof(tmp_buff), "total_step_now:%d\n", record_data.data_s.total_step_now);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "total_calorie_now:%d\n", record_data.data_s.total_calorie_now);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "hr_now:%d\n", record_data.data_s.hr_now);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "calm_hr_day:%d\n", record_data.data_s.calm_hr_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "max_hr_day:%d\n", record_data.data_s.max_hr_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "max_hr_time_day:%d\n", record_data.data_s.max_hr_time_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "min_hr_day:%d\n", record_data.data_s.min_hr_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "min_hr_time_day:%d\n", record_data.data_s.min_hr_time_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "avg_hr_day:%d\n", record_data.data_s.avg_hr_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "avg_pressure_day:%d\n", record_data.data_s.avg_pressure_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "max_pressure_day:%d\n", record_data.data_s.max_pressure_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "min_pressure_day:%d\n", record_data.data_s.min_pressure_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "valid_stand[3]:%d\n", record_data.data_s.valid_stand[3]);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "total_calorie:%d\n", record_data.data_s.total_calorie);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "recover_time:%d\n", record_data.data_s.recover_time);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "spo2_now:%d\n", record_data.data_s.spo2_now);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "max_spo2_day:%d\n", record_data.data_s.max_spo2_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "max_spo2_time_day:%d\n", record_data.data_s.max_spo2_time_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "min_spo2_day:%d\n", record_data.data_s.min_spo2_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "min_spo2_time_day:%d\n", record_data.data_s.min_spo2_time_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "avg_spo2_day:%d\n", record_data.data_s.avg_spo2_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "workload_day:%d\n", record_data.data_s.workload_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "total_workload_7_day:%d\n", record_data.data_s.total_workload_7_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "workload_level:%d\n", record_data.data_s.workload_level);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "low_genki_day:%d\n", record_data.data_s.low_genki_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "medium_genki_day:%d\n", record_data.data_s.medium_genki_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "high_genki_day:%d\n", record_data.data_s.high_genki_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "total_genki_7_day:%d\n", record_data.data_s.total_genki_7_day);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "next_genki_suggest_type:%d\n", record_data.data_s.next_genki_suggest_type);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                len = snprintf(tmp_buff, sizeof(tmp_buff), "next_genki_suggest_dur:%d\n", record_data.data_s.next_genki_suggest_dur);
                fwrite(tmp_buff, len, sizeof(char), pgps_file);
                memset(tmp_buff, 0, sizeof(tmp_buff));
                index++;

                fwrite(tmp_buff, len, sizeof(char), pgps_file);
            }
            break;
            default:
                break;
            }
        }
        printf("offset_start:%d,%d\n", offset_start, sizeof(daily_data_record));
        fclose(pgps_file);
    }
#if USE_BINARY_FILES
    zh_flash_close(ft_file);
#endif
}

void hex_to_bin(const char* txt_file,uint8_t type) {
    FILE* file = fopen(txt_file, "r");
    if (!file) {
        printf("无法打开文本文件\n");
        return;
    }

    FILE* bin = NULL;//
    if(type == 1)
        bin = fopen("daily_points.bin", "wb+");
    else
        bin = fopen("daily_record.bin", "wb+");
    if (!bin) {
        printf("无法创建二进制文件\n");
        fclose(file);
        return;
    }

    char hex_str[3] = { 0 }; // 用于存储每两个字符
    while (fscanf(file, "%2s", hex_str) == 1) { // 每次读取两个字符
        unsigned int byte;
        sscanf(hex_str, "%2x", &byte); // 将十六进制字符串转换为字节
        fputc(byte, bin); // 写入字节到二进制文件
    }

    fclose(file);
    fclose(bin);
}

#endif /* MS_ANALYSIS */
