#ifndef _ZH_APP_SPORTS_DATA_H_
#define _ZH_APP_SPORTS_DATA_H_
// #include "zh_middle_data_manager.h"
#include <stdint.h>
#include <stdbool.h>
///#include "rtthread.h"
//#include "rtconfig.h"
//#include "lv_area.h"
#ifndef BSP_USING_PC_SIMULATOR
//#include "mi_gps_opt_main.h"
//#include "wear_common.pb.h"
//#include "wear_fitness.pb.h"
#endif
#if defined(USING_GYRO_SENSOR) && defined(ENUM_PROJECT_NAME_N65B_GLOBAL) 
#include "mi_swimming_analyzer.h"
#endif 
/********************************************************运动相关 start********************************************************/
//运动报告GPS轨迹图使能
#define GPS_TRACK_DRAW   1
//gps缓存长度
#define GPS_TRACK_LEN               1024
typedef struct {
    uint16_t x;
    uint16_t y;
} gps_track_t;
#define CONVERT_Km_TO_Mile 100.f / 161
#define CONVERT_PerKm_TO_PerMile 161 / 100     // 配速
#define CONVERT_Mi_TO_Ft 328084 / 100000       // 米到英尺
#define CONVERT_BaiMi_TO_BaiFt 100000 / 328084 // 百米到百英尺
#define CONVRT_CM_TO_IN 39370 / 100000         // 厘米到英寸
typedef enum _SPORT_SEETING_TYPE
{
    SPORT_SEETING_NULL = 0,
	SPORT_SEETING_CONSUME = 1,	
    SPORT_SEETING_DISTANCE = 2,
    SPORT_SEETING_TIME = 3,
    SPORT_SEETING_COUNT = 4,//兼容趟数,用此字段兼容
    SPORT_SEETING_STEPFREQ = 5,
    SPORT_SEETING_HR = 6,
    SPORT_SEETING_PACE_REMIND = 7,       // 配速提醒
    SPORT_SEETING_DISTANCE_REMIND = 8,   // 距离提醒
    SPORT_ENERGY_SUPPLY_DISTANCE = 9,    // 能量补给按距离
    SPORT_ENERGY_SUPPLY_TIME = 10,       // 能量补给按时间
    SPORT_INTERVAL_TRAINING_SWITCH = 11, // 间歇训练开关
    SPORT_WARM_UP_SWITCH = 12,           // 热身开关
    SPORT_RELAX_SWITCH = 13,             // 放松开关
    SPORT_INTERVAL_TRAINING_DEST = 14,   // 距离
    SPORT_INTERVAL_TRAINING_TIME = 15,   // 时间
    SPORT_INTERVAL_TRAINING_TIMES = 16,  // 次数
    SPORT_INTERVAL_TRAINING_COUNT = 17,  // 个数
    SPORT_SEETING_AUTO_PAUSE = 18,
    SPORT_HR_SELECT = 19, // hr_select 此bit用于hr是否是出厂默认值,
    SPORT_INTELLIGENT_COMPANION_RUN=20,//智能陪跑
    SPORT_SCREEN_ALWAYS_ON = 21,//屏幕常亮开关
    // SPORT_ENERGY_SUPPLY_TIME=20,//能量补给按时间
    SPORT_SWING_POOL = 22,//泳池
    SPORT_SWIM_POOL_25 = 23,//25m
    SPORT_SWIM_POOL_50 = 24,//50m
    SPORT_SETTING_MAX,
} SPORT_SEETING_TYPE;
// 多运动
typedef enum SPORT_alg_state
{
    Sport_state_stop = 0,
    Sport_state_start = 1,
    Sport_state_pause = 2,
} Sport_state_t;

// 多运动
typedef enum SPORT_interval_training
{
    Sport_MODE_TIME = 0,
    Sport_MODE_DISTANCE = 1,
    Sport_MODE_COUNT = 2,
} SPORT_interval_training_mode;
typedef enum SPORT_interval_training_t
{
    INTERVAL_TRAINING_WARM_UP = 0,
    INTERVAL_TRAINING = 1,
    INTERVAL_TRAINING_REST = 2,
    INTERVAL_TRAINING_RELAX = 3,
    COURSE_BEAT_IT = 4,
    COURSE_CANTER = 5,
    COURSE_MODERATE_PACE = 6,
    COURSE_TANTIVY = 7,
    COURSE_ACTIVITY = 8,
    INTERVAL_MAX = 127,
} SPORT_interval_training_type;
typedef struct
{
    SPORT_interval_training_mode mode;
    SPORT_interval_training_type type;
    uint8_t completion_times;
    uint8_t total_times;
    uint32_t current_time_count;
    uint32_t total_time_count;
    uint32_t current_distance;
    uint32_t total_distance;
    uint16_t current_count;
    uint16_t total_count;
} Sport_interval_training_type;
typedef enum Running_course_type_t
{
    Sport_Course_Null = 0,
    Combining_Basic_Running_Walking = 1,      // 基础跑走结合
    Advanced_Running_Walking_Combination = 2, // 进阶跑走结合
    Basic_Jogging = 3,                        // 基础慢跑
    Basic_Fuel_Running = 4,                   // 基础燃脂跑
    Advanced_Fat_Burning_Run = 5,             // 进阶燃脂跑
    MIIT_Fuel_Run = 6,                        // MIIT 燃脂跑
    Basic_Aerobic_Endurance_Run = 7,          // 基础有氧耐力跑
    Advanced_Aerobic_Endurance_Run = 8,       // 基础有氧耐力跑
    Basic_Interval_Running = 9,               // 基础间歇跑
    Advanced_Interval_Running = 10,           // 基础间歇跑
    Sport_Cource_max,
} Running_course_type; // 课程主类型
typedef enum Running_course_sub_type_t
{
    Sport_Course_Sub_Null = 0,
    Beat_It_Type = 4,       // 快走
    Jogging_Type = 5,       // 慢跑
    Moderate_pace_Type = 6, // 中速跑
    Run_Fast_Type = 7,      // 快跑
    Sport_Course_Sub_Max,
} Running_course_sub_type;  // 课程子类型
typedef struct
{
    int u_swimmingType; // 姿态
    float u_swimmingPace_avg;
    uint16_t u_swimming_time;
} SWIMING_OUT_detail_t;
typedef enum _SPORT_point_max_t
{
    MAX_HR_POINT,
    MIN_HR_POINT,
    MAX_PACE_POINT,
    MIN_PACE_POINT,
    MAX_CADENCE_POINT,
    MIN_CADENCE_POINT,
    MAX_SPEED_POINT,
    MIN_SPEED_POINT,
    MAX_ACTION_FREQ_POINT,
    MIN_ACTION_FREQ_POINT,
    MAX_SWOLF_POINT,
    MIN_SWOLF_POINT,
    MAX_PULL_RATE_POINT,
    MIN_PULL_RATE_POINT,
} SPORT_point_max_t;
typedef union
{
    uint32_t ec_opt_d;
    struct
    {
        uint32_t valid : 8;
        uint32_t value : 24;
    } values;
} ec_opt_values;
typedef union _sport_record_max_t {
    struct {
        uint32_t  max_hr_point;//最大心率时间点
        uint32_t  min_hr_point;//最小心率时间点
        uint32_t max_pace_point;// 最大配速时间点
        ec_opt_values max_pace_value;//最快配速
        uint32_t min_pace_point;// 最小配速时间点
        ec_opt_values min_pace_value;//最小配速
        uint32_t  max_cadence_point;// 步数步频
        uint32_t  min_cadence_point;// 步数步频
    } run_c;    // 户外跑步类,健走,室内跑步，登山，越野

    // struct {
    //     uint32_t  max_hr_point;//最大心率时间点
    //     uint32_t  min_hr_point;//最小心率时间点
    //     uint32_t max_pace_point;// 最大配速时间点
    //     uint32_t min_pace_point;// 最小配速时间点
    //     uint32_t  max_cadence_point;// 步数步频
    //     uint32_t  min_cadence_point;// 步数步频
    // } indoor_run;    // 室内跑步

    struct {
        uint32_t  max_hr_point;//最大心率时间点
        uint32_t  min_hr_point;//最小心率时间点
        uint32_t max_speed_point;// 最大速度时间点
        ec_opt_values max_speed_value;//最大速度打点
        uint32_t min_speed_point;// 最小速度时间点
        ec_opt_values min_speed_value;//最小速度打点
    } out_non_run_c;    // 户外非跑步类

    struct {
        uint32_t  max_hr_point;//最大心率时间点
        uint32_t  min_hr_point;//最小心率时间点
    } free_sport;    // 自由训练类

    struct {
        uint32_t  max_hr_point;//最大心率时间点
        uint32_t  min_hr_point;//最小心率时间点
        uint32_t   max_action_freq_point; // 跳绳频率
        uint32_t   min_action_freq_point; // 跳绳频率
    } rope_skip;    // 跳绳类

    struct {
        uint32_t  max_hr_point;//最大心率时间点
        uint32_t  min_hr_point;//最小心率时间点
        uint32_t  max_cadence_point;// 椭圆机步频
        uint32_t  min_cadence_point;// 椭圆机步频
    } elliptical_m;

    struct {
        uint32_t  max_hr_point;//最大心率时间点
        uint32_t  min_hr_point;//最小心率时间点
        uint32_t   max_action_freq_point; // 划船划频
        uint32_t   min_action_freq_point; // 划船划频
    } rowing_m;    // 划船机类

    struct {//TODO游泳特殊处理
        uint32_t max_pace_point;
        uint32_t min_pace_point;
        uint32_t max_swolf_point;
        uint32_t min_swolf_point;
        uint32_t max_pull_rate_point;
        uint32_t min_pull_rate_point;
    } swimming;    // 游泳类
} sport_record_max_t;
typedef struct
{
    int16_t x;
    int16_t y;
} lv_point_t;
typedef union _sport_chart_t {
    lv_point_t point;
    struct {
        uint16_t offset;
        uint16_t  value;
    }v;
} sport_chart_t;
typedef struct
{
    uint32_t sport_distance;           // 距离
    uint16_t sport_Speed_distribution; // 配速
    uint32_t sport_Speed;              // 速度
    float    sport_Speed_m_per_s;      // 速度(unit: m/s)
} SPORT_get_some_data;
#define CHART_MAX 60
typedef struct
{

    uint32_t sport_time_start; // 开始时间（秒）   （已有数据）
    uint32_t sport_time_count; // 用时（秒）        （已有数据）
    int8_t sport_time_zone;    // 开始时间 (时区) (已有数据)
    uint8_t sport_strength;
    uint16_t sport_seeting_choose_target;
    uint32_t sport_distance; // 距离(米)                （已有数据）
    // 配速实际显示为xx分xx秒/公里   需要先将秒/米换算成 ==> 秒/公里（*1000） 输入显示函数中
    uint32_t sport_Speed_distribution;          // 当前配速（秒/千米）              （已有数据）
    uint32_t sport_avg_Speed_distribution;      // 平均配速（秒/千米）              （已有数据）
    uint32_t sport_Speed_distribution_last_1km; // 上公里配速（秒/千米）           （已有数据）
    uint32_t sport_Speed_distribution_last_1mi; // 上英里配速(秒/英里); 上英里速度用配速计算;
    uint32_t sport_Maximum_Speed_distribution;  // 上公里最大配速（秒/千米）     （已有数据）
    uint32_t sport_Miximum_Speed_distribution;  // 上公里最小配速（秒/千米）     （已有数据）
    uint32_t sport_Speed_distribution_max;      // 最大配速                                （已有数据）
    uint32_t sport_Speed_distribution_min;

    uint32_t sport_Step_number;                      // 步数
    uint16_t sport_Step_frequency;                   // 当前步频
    uint16_t sport_Maximum_Step_frequency;           // 最大步频
    uint16_t sport_Maximum_Step_frequency_timestamp; // 最大步频出现的时间戳（秒）
    uint16_t sport_ave_Step_frequency;               // 平均步频
    float sport_step_length;                         // 当前步幅 （厘米）
    float sport_avg_step_length;                     // 平均步幅 （厘米）
    uint32_t sport_Speed;                         // 速度(千米/小时(已放大100倍使用进行单位转换))（已有数据）
    uint32_t sport_average_velocity;              // 平均速度(千米/小时(已放大100倍使用进行单位转换))（已有数据）
    uint32_t sport_onekilometre_average_velocity; // 上公里速度(千米/小时(已放大100倍使用进行单位转换))（已有数据）

    uint32_t sport_Limit_speed;           // 最大速度(千米/小时(已放大100倍使用进行单位转换))（已有数据）
    uint32_t sport_Limit_speed_timestamp; // 最大速度出现的时间戳（秒）

    // 最大速度出现的时间戳（秒）

    // 运动强度
    float sport_consume;                   // 消耗（kcal）
    uint8_t sport_heart_rate;              // 心率/min
    uint8_t sport_Mean_heart_rate;         // 平均心率
    uint8_t sport_Maximum_heart_rate;      // 最大心率
    uint8_t sport_Miximum_heart_rate;      // 最小心率
    uint32_t sport_heart_rate_count;       // 心率-总时长（秒）
    uint32_t sport_heart_rate_count_1;     // 心率-极限时长（秒）
    uint32_t sport_heart_rate_count_2;     // 心率-无氧耐力时长（秒）
    uint32_t sport_heart_rate_count_3;     // 心率-有氧耐力时长（秒）
    uint32_t sport_heart_rate_count_4;     // 心率-燃脂时长（秒）
    uint32_t sport_heart_rate_count_5;     // 心率-热身时长（秒）
    int32_t sport_basic_altitude;          // 基准海拔
    uint32_t sport_relative_up_altitude;   // 累计爬升海拔（米）
    uint32_t sport_relative_down_altitude; // 累计下降海拔（米）
    int32_t sport_max_altitude;            // 最高海拔
    int32_t sport_min_altitude;            // 最低海拔
    int32_t sport_current_altitude;        // 当前海拔
    int32_t sport_avg_high;                // 平均高度
    int32_t sport_max_high;                // 最大高度
    int32_t sport_min_high;                // 最小高度
    uint32_t sport_rm_count;               // m69    跳绳划船机次数
    uint32_t sport_rm_last_count;          //跳绳划船机上一次次数用于计算本段总数
    uint32_t sport_rm_frequency;           // m69   跳绳划船机频率
    uint16_t sport_max_freq;
    uint16_t sport_avg_freq;
    uint32_t sport_setting_target;
    uint16_t sport_number_of_tips;                     // 泳池趟数
    uint8_t sport_main_swimming_posture;               // 主要泳姿
    uint16_t sport_avg_swolf;                          // 游泳平均swolf
    uint16_t sport_paddling_count;                     // 划水数
    uint16_t avg_sliding_frequency;                    // 平均频次/分
    //lv_point_t sport_gps_chart[CHART_MAX];             // gps轨迹图
    sport_chart_t sport_heart_chart[CHART_MAX];           // 心率图表
    uint16_t sport_heart_chart_count;
    sport_chart_t sport_steps_frequency_chart[CHART_MAX]; // 步频,划频
    uint16_t sport_steps_frequency_chart_count;
    sport_chart_t sport_pace_chart[CHART_MAX];              // pace or speed
    uint16_t sport_pace_chart_count;
    float sport_genki_value;//元气值 todo
    uint16_t sport_Minimum_Step_frequency;           // 最小步频大于0
    uint32_t sport_Min_speed;           // 最小速度(千米/小时(已放大100倍使用进行单位转换))（已有数据）大于0
    uint16_t sport_min_freq;            //划船机跳绳最小频率大于0
#if GPS_TRACK_DRAW == 1
    double *lon;
    double *lat;
    uint32_t len;
    uint32_t gps_draw_track_count;
    gps_track_t gps_track[GPS_TRACK_LEN];// gps轨迹图
#endif
    uint16_t sport_max_swolf;                          // 游泳最大swolf
    uint16_t sport_min_swolf;                          // 游泳最小swolf
} SPORT_data_save_data_t;
typedef struct Sport_Basic_Data
{
    uint32_t steps;
    uint32_t detail_steps;
    uint16_t calories;
    uint32_t distance;
    uint8_t heart_rate;
    uint16_t intensity;
    uint8_t valid_stand;
} sport_basic_data_t;

typedef struct
{
#ifndef BSP_USING_PC_SIMULATOR
    uint16_t sport_type;
#endif
    uint32_t duration;
    uint32_t distance;
} Sport_Best_Data_t;

enum Sport_Best_Data_index
{
    BEST_OUTDOOR_RUNNING,
    BEST_INDOOR_RUNNING,
    BEST_OUTDOOR_WALK,
    BEST_OUTDOOR_CYCLING,
    BEST_LOCAL_MAX,
};

enum
{
    LOCAL_INFO_EVT,
    ENERGY_EVT,
    HR_CHANGING_EVT,
    PACE_EVT,
    KM_EVT,
    DURA_BEST_EVT,
    DIST_BEST_EVT,
    DIST_TARGRT_EVT,
    CAL_TARGRT_EVT,
    DURA_TARGRT_EVT,
    COUNT_TARGRT_EVT,
    MAX_HR_EVT,
    HR_ZONES_EVT,
    AUTO_PACE_EVT,
};

enum
{
    PACE_SPEED_LOW,
    PACE_SPEED_HIGH,
    PACE_SPEED_HOLD,
};

typedef struct
{
    uint8_t sport_heart_rate_range;
    uint8_t sport_heart_rate_percent;
} SPORT_HEART_RATE_INFO_STRU;
typedef struct _sport_gps_data_t
{
    uint32_t timestamp;
    double longitude;
    double latitude;
    double altitude;
    float speed;
    float bearing;
    float horizontal_accuracy;
    float vertical_accuracy;
	uint8_t provider;
} sport_gps_data_t;
typedef struct
{
    uint8_t sport_state;
    uint8_t sport_type;
    uint16_t sport_disable;
    uint16_t time_cnt;
	uint16_t endtime_cnt;
} auto_sport_ctrl_t;

enum
{
    HR_ZONES_NULL,
    HR_ZONES_WARM_UP,//热身
    HR_ZONES_WEIGHT_REDUCTION,//燃脂
    HR_ZONES_ENDURANCE,//有氧
    HR_ZONES_ANAEROBIC,//无氧
    HR_ZONES_EXTREME,//极限
};


typedef struct 
{
        uint8_t timing_mode;//
        uint8_t start_time_hour;//抬婉开始时间的时
        uint8_t start_time_min;//抬婉开始时间的分
        uint8_t end_time_hour;//抬婉开始时间的时
        uint8_t end_time_min;//抬婉开始时间的分
        uint8_t sensitivity_mode;//灵敏度设置
        uint8_t remind_sport_end;
}sport_detect_dst_t;



typedef struct
{
    uint32_t sport_seeting_choose_target;     // 多运动选中目标
    uint16_t sport_seeting_count_data;        // 多运动设置个数,兼容泳池趟数
    uint16_t sport_seeting_consume_data;      // 多运动设置热量
    uint16_t sport_seeting_time_data;         // 多运动设置时间
    uint32_t sport_seeting_distance_data;     // 多运动设置距离
    uint32_t sport_seeting_pace_data;         // 多运动设置配速
    uint32_t sport_seeting_step_freq;         // 多运动设置频率
    uint8_t sport_heart_rate_warn_value;      // 多运动心率预警值
    uint16_t sport_interval_training_time;    // 训练时间
    uint32_t sport_interval_training_dis;     // 距离
    uint16_t sport_interval_training_times;   // 次数
    uint16_t sport_interval_training_count;   // 个数
    uint16_t sport_interval_training_xunlian; // 训练
    uint8_t sport_interval_training_loop;     // 循环
    uint16_t sport_interval_training_rest;    // 休息
    uint16_t sport_distance_remind;           // 距离提醒
    uint16_t sport_pace_or_speed_remind;      // 配速提醒，速度提醒
    uint16_t sport_energy_supply_remind_dis;  // 能量补给提醒，按距离
    uint16_t sport_energy_supply_remind_time; // 能量补给提醒，按时间
    uint16_t sport_accompanying_running_pace; // 陪跑配速
    uint8_t sport_pool_length;                //泳池长度最大200
    uint8_t sport_heart_rate_zones;//心率区间0->closs,1->热身.....5->极限
} SPORT_setting_target_data_t;

typedef struct
{
    uint32_t sport_seeting_choose_target; // 多运动选中目标
    uint32_t sport_seeting_count_data;    // 多运动设置个数
    uint32_t sport_seeting_consume_data;  // 多运动设置热量
    uint32_t sport_seeting_time_data;     // 多运动设置时间
    uint32_t sport_seeting_distance_data; // 多运动设置距离
    uint32_t sport_seeting_pace_data;     // 多运动设置配速
    uint32_t sport_seeting_step_freq;     // 多运动设置频率
    uint8_t sport_heart_rate_warn_value;  // 多运动心率预警值
    uint32_t sport_reminder_kilometre_duration;
    uint32_t sport_reminder_pace;
    uint32_t sport_reminder_kilometre_pace;
    //    uint16_t           sport_interval_training_time;//训练时间
    //    uint32_t           sport_interval_training_dis;//距离
    //    uint16_t          sport_interval_training_times;//次数
    //    uint16_t          sport_interval_training_count;//个数
    //    uint8_t          sport_interval_training_loop;//循环
    //    uint16_t           sport_interval_training_rest;//休息
    //    uint16_t          sport_distance_remind;//距离提醒
    //    uint16_t           sport_pace_or_speed_remind;//配速提醒，速度提醒
    //    uint16_t      sport_energy_supply_remind_dis;//能量补给提醒，按距离
    //    uint16_t      sport_energy_supply_remind_time;//能量补给提醒，按时间
} SPORT_app_target_data_t;

#pragma pack(push, 1)
typedef struct
{
    union
    {
        // 跳绳
        struct
        {
            uint8_t hr;
            uint8_t extra_calorie;
            uint16_t cadence;
            // uint8_t takeoff_height;
            // uint8_t extra_trips;
        } rope_skipping;

        // 椭圆机
        struct
        {
            union
            {
                uint8_t ec_d;
                struct
                {
                    uint8_t extra_step : 4;
                    uint8_t extra_calorie : 4;
                } ec_s;
            } extra_calorie;
            uint8_t hr;
            uint8_t cadence;
        } elliptical_machine;

        // 划船机
        struct
        {
            uint8_t hr;
            uint8_t extra_calorie;
            uint8_t sliding_frequency;
        } rowing_machine;

        // 骑行
        struct
        {
            union {
                uint8_t ec_d;
                struct {
                    uint8_t extra_count : 4;
                    uint8_t extra_calorie : 4;
                } ec_s;
            } extra_calorie;
            uint8_t hr;
            union {
                uint8_t hc_d;
                struct {
                    uint8_t height_change : 6;
                    uint8_t is_up: 1;
                    uint8_t is_km : 1;
                } hc_s;
            } heigth_change;
            uint8_t extra_distance;
            uint16_t speed;
        } outside_cycle;

        // 室内跑(转换使用)
        struct
        {
            union
            {
                uint8_t ec_d;
                struct
                {
                    uint8_t extra_step : 4;
                    uint8_t extra_calorie : 4;
                } ec_s;
            } extra_calorie;
            uint8_t hr;
            uint8_t extra_distance;
            uint8_t extra_stride;
            uint8_t cadence;
            uint16_t pace; 
        } indoor_run;

        // 跑走类(户外跑,室内跑,健走)
        struct
        {
            union
            {
                uint8_t ec_d;
                struct
                {
                    uint8_t extra_step : 4;
                    uint8_t extra_calorie : 4;
                } ec_s;
            } extra_calorie;
            uint8_t hr;
            union
            {
                uint8_t hc_d;
                struct
                {
                    uint8_t height_change : 6;
                    uint8_t is_up : 1;
                    uint8_t is_km : 1;
                } hc_s;
            } heigth_change;
            uint8_t extra_distance;
            uint8_t extra_stride;
            uint8_t cadence;
            uint16_t pace; 
        } run_category;
    };
} SPORT_app_auto_sport_data_t, *pSPORT_app_auto_sport_data_t;

typedef struct
{
    uint32_t gps_timestamp;
    float gps_longitude;
    float gps_latitude;
} SPORT_app_auto_sport_gpsv1_data_t, *pSPORT_app_auto_sport_gpsv1_data_t;
typedef struct
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
} SPORT_app_auto_sport_gpsv2_data_t, *pSPORT_app_auto_sport_gpsv2_data_t;
#pragma pack(pop)

typedef enum SPORT_type
{
    // 默认
    SPORTING_Outdoor_running_TYPE = 0, // 户外跑步       0
    SPORTING_Outdoor_walking_TYPE,     // 户外健走       1
    SPORTING_free_activity_TYPE,       // 自由活动 		2
    SPORTING_Outdoor_hiking_TYPE,      // 户外徒步      3
    SPORTING_Outdoor_cycling_TYPE,     // 户外骑行       4
    SPORTING_Indoor_running_TYPE,      // 室内跑步      5
    SPORTING_Skipping_rope_H_TYPE,     // 跳绳 6
                                   // 水上运动
    SPORTING_swim_indoor_TYPE,    // 泳池游泳
    SPORTING_swim_outdoor_TYPE,   // 开放水域游泳
    SPORTING_sailboat_TYPE,       // 帆船
    SPORTING_paddle_board_TYPE,   // 桨板
    SPORTING_water_polo_TYPE,     // 水球
    SPORTING_aquatic_sport_TYPE,  // 水上运动
    SPORTING_surfing_TYPE,        // 滑水
    SPORTING_canoeing_TYPE,       // 皮划艇
    SPORTING_kayak_rafting_TYPE,  // 皮艇漂流
    SPORTING_rowing_TYPE,         // 划船
    SPORTING_motorboat_TYPE,      // 摩托艇
    SPORTING_web_swimming_TYPE,   // 蹼泳
    SPORTING_driving_TYPE,        // 跳水
    SPORTING_fancy_swimming_TYPE, // 花样游泳
    SPORTING_snorkeling_TYPE,     // 浮潜
    SPORTING_kite_surfing_TYPE,   // 风筝冲浪
    SPORTING_indoor_surfing_TYPE, // 室内冲浪
    SPORTING_dragon_boat_TYPE,    // 龙舟
                               // 户外运动类
    SPORTING_Mountaineering_TYPE, // 登山
    SPORTING_Off_road_TYPE,       // 越野
                            // SPORT_triathlon_TYPE,		  // 铁人三项
    SPORTING_rock_climbing_TYPE,  // 攀岩
    SPORTING_skateboard_TYPE,     // 滑板
    SPORTING_Roller_skating_TYPE, // 轮滑
    SPORTING_Parkour_TYPE,        // 跑酷
    SPORTING_ATV_TYPE,            // 沙滩车
    SPORTING_Paraglider_TYPE,     // 滑翔伞
    SPORTING_bicycle_moto_TYPE,   // 小轮车
    SPORTING_heel_and_toe_TYPE,   // 竞走
                                // 训练类
    SPORTING_High_intensity_interval_training_TYPE, // 高强度间歇训练
    SPORTING_Yoga_TYPE,                             // 瑜伽
    SPORTING_Indoor_cycling_TYPE,                   // 室内单车
    SPORTING_Elliptical_machine_TYPE,               // 椭圆机
    SPORTING_Rowing_machine_TYPE,                   // 划船机
    SPORTING_Climbing_machine_TYPE,                 // 爬楼机
    SPORTING_Stepper_TYPE,                          // 踏步机
    SPORTING_spinning_TYPE,                         // 动感单车
    SPORTING_Core_training_TYPE,                    // 核心训练
    SPORTING_Flexibility_training_TYPE,             // 柔韧训练
    SPORTING_Pilates_TYPE,                          // 普拉提
    SPORTING_gymnastics_TYPE,                       // 体操
    SPORTING_Stretch_TYPE,                          // 拉伸
    SPORTING_Strength_Training_TYPE,                // 力量训练
    SPORTING_Cross_training_CrossFit_TYPE,          // 交叉训练CrossFit
    SPORTING_Climb_the_stairs_TYPE,                 // 爬楼梯
    SPORTING_Aerobics_TYPE,                         // 健身操
    SPORTING_Physical_Training_TYPE,                // 体能训练
    SPORTING_Wall_ball_TYPE,                        // 墙球
    SPORTING_Dumbbell_training_TYPE,                // 哑铃训练
    SPORTING_Barbell_training_TYPE,                 // 杠铃训练
    PORTING_weightlifting_TYPE,                     // 举重
    SPORTING_Deadlift_TYPE,                         // 硬拉
    SPORTING_Bobby_Jump_TYPE,                       // 波比跳
    SPORTING_Sit_ups_TYPE,                          // 仰卧起坐
    SPORTING_Functional_training_TYPE,              // 功能性训练
    SPORTING_Upper_limb_training_TYPE,              // 上肢训练
    SPORTING_Lower_limb_training_TYPE,              // 下肢训练
    SPORTING_Waist_and_abdomen_training_TYPE,       // 腰腹训练
    SPORTING_Back_training_TYPE,                    // 背部训练
    SPORTING_walking_machine_TYPE,                  // 漫步机
    SPORTING_single_bar_TYPE,                       // 单杠
    SPORTING_parallel_bars_TYPE,                    // 双杠
    SPORTING_step_training_TYPE,                    // 踏步训练
    SPORTING_group_callisthenics_TYPE,              // 团体操
    SPORTING_strike_TYPE,                           // 搏击操
    SPORTING_battle_rope_TYPE,                      // 战绳
    SPORTING_mixed_aerobic_TYPE,                    // 混合有氧
    SPORTING_walk_indoor_TYPE,                      // 室内步行
    SPORTING_gym_TYPE,                              // 室内健身
                       // 舞蹈类
    SPORTING_Square_dance_TYPE,   // 广场舞
    SPORTING_Belly_dance_TYPE,    // 肚皮舞
    SPORTING_ballet_TYPE,         // 芭蕾舞
    SPORTING_Street_dance_TYPE,   // 街舞
    SPORTING_Zumba_TYPE,          // 尊巴
    SPORTING_National_dance_TYPE, // 民族舞
    SPORTING_Jazz_TYPE,           // 爵士舞
    SPORTING_Latin_Dance_TYPE,    // 拉丁舞
    SPORTING_hip_hop_dance_TYPE,  // 嘻哈舞
    SPORTING_pole_dance_TYPE,     // 钢管舞
    SPORTING_breakdancing_TYPE,   // 霹雳舞
    SPORTING_social_dancing_TYPE, // 交际舞
    SPORTING_modern_dancing_TYPE, // 现代舞
    SPORTING_dance_TYPE,          // 舞蹈
                         // 搏击类
    SPORTING_boxing_TYPE,           // 拳击
    SPORTING_Wrestling_TYPE,        // 摔跤
    SPORTING_Martial_arts_TYPE,     // 武术
    SPORTING_Tai_Chi_TYPE,          // 太极
    SPORTING_Muay_Thai_TYPE,        // 泰拳
    SPORTING_judo_TYPE,             // 柔道
    SPORTING_Taekwondo_TYPE,        // 跆拳道
    SPORTING_karate_TYPE,           // 空手道
    SPORTING_free_sparring_TYPE,    // 自由搏击
    SPORTING_fencing_movement_TYPE, // 剑术
    SPORTING_fencing_TYPE,          // 击剑
    SPORTING_jujitsu_TYPE,          // 柔术
                           // 球类
    SPORTING_tennis_TYPE,           // 网球
    SPORTING_basketball_TYPE,       // 篮球
    SPORTING_golf_TYPE,             // 高尔夫
    SPORTING_Soccer_TYPE,           // 足球
    SPORTING_volleyball_TYPE,       // 排球
    SPORTING_baseball_TYPE,         // 棒球
    SPORTING_softball_TYPE,         // 垒球
    SPORTING_Rugby_TYPE,            // 橄榄球
    SPORTING_hockey_TYPE,           // 曲棍球
    SPORTING_pingpong_TYPE,         // 乒乓球
    SPORTING_badminton_TYPE,        // 羽毛球
    SPORTING_cricket_TYPE,          // 板球
    SPORTING_Handball_TYPE,         // 手球
    SPORTING_bowling_TYPE,          // 保龄球
    SPORTING_squash_TYPE,           // 壁球
    SPORTING_billiards_TYPE,        // 台球
    SPORTING_Shuttlecock_TYPE,      // 毽球
    SPORTING_beach_soccer_TYPE,     // 沙滩足球
    SPORTING_beach_volleyball_TYPE, // 沙滩排球
    SPORTING_Sepak_Takraw_TYPE,     // 藤球
    SPORTING_indoor_football_TYPE,  // 室内足球
    SPORTING_sandbags_ball_TYPE,    // 沙包球
    SPORTING_bocci_TYPE,            // 地掷球
    SPORTING_hihi_ball_TYPE,        // 回力球
    SPORTING_gateball_TYPE,         // 门球
    SPORTING_dodgeball_TYPE,        // 躲避球
                             // 冰雪运动
    SPORTING_Snowboarding_TYPE,         // 单板滑雪
    SPORTING_Double_board_skiing_TYPE,  // 双板滑雪
    SPORTING_cross_country_skiing_TYPE, // 越野滑雪
    SPORTING_Outdoor_skating_TYPE,      // 户外滑冰
    SPORTING_indoor__skating_TYPE,      // 室内滑冰
    SPORTING_Curling_TYPE,              // 冰壶
    SPORTING_Snow_sports_TYPE,          // 雪上运动
    SPORTING_Snowmobile_TYPE,           // 雪地摩托
    SPORTING_puck_TYPE,                 // 冰球
    SPORTING_Snow_car_TYPE,             // 雪车
    SPORTING_sled_TYPE,                 // 雪橇
                        // 休闲运动类
    SPORTING_Archery_TYPE,             // 射箭
    SPORTING_Darts_TYPE,               // 飞镖
    SPORTING_ride_horse_TYPE,          // 骑马
    SPORTING_Tug_of_war_TYPE,          // 拔河
    SPORTING_Hula_Hoop_TYPE,           // 呼啦圈
    SPORTING_fly_a_kite_TYPE,          // 放风筝
    SPORTING_fishing_TYPE,             // 钓鱼
    SPORTING_Frisbee_TYPE,             // 飞盘
    SPORTING_shuttlecock_kicking_TYPE, // 踢毽子
    SPORTING_swing_TYPE,               // 秋千
    SPORTING_motion_sensing_game_TYPE, // 体感游戏
    SPORTING_foosball_TYPE,            // 桌上足球
    SPORTING_shuffle_ball_TYPE,        // 沙壶球
    SPORTING_electronic_sports_TYPE,   // 电子竞技
                                     // 棋牌运动
    SPORTING_chess_TYPE,       // 国际象棋
    SPORTING_draughts_TYPE,    // 国际跳棋
    SPORTING_weiqi_TYPE,       // 围棋
    SPORTING_bridge_TYPE,      // 桥牌
    SPORTING_board_games_TYPE, // 桌游
                               // 其他运动
    SPORTING_equesttrian_TYPE,     // 马术
    SPORTING_track_and_field_TYPE, // 田径
    SPORTING_racing_car_TYPE,      // 赛车
    SPORTING_MORE,                 // 更多
    SPORTING_MAX_END_TYPE,         // 多运动-结束ID
} Sport_type;
#define WEAR_SENSOR_MAX 60
typedef struct 
{
    uint16_t accel_count;
    uint8_t operating_mode;//1->存,2->取,0->空闲
#if 0
#ifndef BSP_USING_PC_SIMULATOR
    struct _AxisSensor accel[WEAR_SENSOR_MAX];
#endif
    uint16_t gyro_count;
#ifndef BSP_USING_PC_SIMULATOR
    struct _AxisSensor gyro[WEAR_SENSOR_MAX]; 
#endif
#endif
} Wear_Sensor_data;

typedef struct _SPORT_app_auto_sport_obj_t
{
#define MAX_SPORT_APP_AUTO_SPORT_DATA (12 * 1024)
    uint32_t total_cnts;
    uint32_t data_len;
    Sport_type sport_type;
    union
    {
        uint8_t data_array[MAX_SPORT_APP_AUTO_SPORT_DATA];//12288
#if 1//defined(USING_GYRO_SENSOR) && defined(ENUM_PROJECT_NAME_N65B_GLOBAL) 
    struct 
    {
        uint16_t record_num;
#if defined(USING_GYRO_SENSOR) && defined(ENUM_PROJECT_NAME_N65B_GLOBAL) 
        sw_record_t swim_record[380];
#endif
    }Swim_record;
// #else
    struct 
    {
        Wear_Sensor_data sensor_data1;//2896
        Wear_Sensor_data sensor_data2;
        Wear_Sensor_data sensor_data3;
        Wear_Sensor_data sensor_data4;
    }Sensory_course;
#endif 
    }data;
    
} SPORT_app_auto_sport_obj_t;

//// 一级提醒界面的显示界面
typedef enum SPROT_First_Remind_type
{
    SPACE_WILL_FULL_STATE = 0,     // 空间将满
    PHONE_DISCONNECT_STATE = 1,    // 蓝牙连接断开将无法记录运动轨迹  （户外跑 户外骑行 健走）
    SPACE_WAS_FULL = 2,            // 空间已满，将要覆盖
    SPORT_Positioning = 3,         // 定位中
    SPORT_Positioning_success = 4, // 定位成功
    SPORT_Positioning_fail = 5,    // 定位失败
} Sport_First_Remind_type_t,
    Sport_First_Remind_type;

#define MAX_SPORT_RECORD_NUM 20
#define MAX_SPORT_SEETING_TARGET_NUM SPORTING_MAX_END_TYPE
typedef struct
{
    SPORT_data_save_data_t sport_save_data_record_t; // 数据
    uint8_t sport_save_data_record_types;            // 类型
    bool sport_save_uploat_flag;                     // true:运动上传成功  false ：还未上传运动
    uint8_t sport_save_data_sub_type;                // 运动子id,只适用于课程结构
} SPORT_save_data_t;
#define SPORT_RECORD_TIME_LINE 60
typedef struct
{
    uint8_t sport_index;
    uint8_t sport_type;
    uint8_t sport_use_count;
    uint8_t sport_gourp; // 1水上运动,2户外运动,3训练,4舞蹈类运动,5搏击类运动,6球类运动,7冰雪运动,8休闲运动,9棋牌运动,10其他运动
} sport_list_type_t;


typedef struct{
	float speed;
	uint8_t auto_pause_disable;
	uint8_t cur_act_state;
	uint8_t user_pause;
	uint8_t vilidspeed;
}auto_pause_dst_t;

typedef enum
{
    DISTANCE_KM = 0,
    DISTANCE_MILE
} ZH_UnitType;
typedef struct{
	uint32_t sub_section_time;
	uint16_t sub_section_swolf;
    uint16_t total_trip_count;//总转身次数用于判断是否是新的小节段落
    uint16_t sub_section_distance;//记录小节的距离
    uint8_t swim_is_write;//用于是否写入打点0->不写,bit1->小节，bit2->段落,bit3->报告
    uint16_t sub_section_count;//记录小节条数
}swim_data_t;
typedef struct // 杂项
{
    Sport_state_t sport_Function_state; // 运动的状态
    uint32_t sport_upload_steps;        // 副屏运动上传APP的步数
    float sport_upload_kcal;
    uint32_t heart_rate_sum;
    uint32_t heart_rate_count;
    uint32_t one_min_sport_max_step_freq;
    uint32_t one_min_sport_last_min_step;
    SPORT_get_some_data wear_get_data;
    //    SPORT_get_some_data         app_get_data;
    
    sport_gps_data_t phone_gps_data[2];
	sport_gps_data_t app_gps_data[2];
	sport_gps_data_t device_gps_data[2];
	
    sport_gps_data_t gps_data_to_be_written;
    uint32_t record_last_second_distance;
    uint32_t last_one_minute_distance;
    uint32_t last_one_minute_speed;
    uint32_t last_one_minute_pace;
    uint32_t sport_timestamp;
    uint32_t cal_distance; // 校准值
    float total_consume;
	uint32_t used_timestamp;
	uint32_t compare_timestamp;
    uint8_t have_phone_gps_data;
	uint8_t have_device_gps_data;
	uint8_t have_app_gps_data;
    uint8_t gps_data_timer;
    uint8_t gps_position_status;
    uint8_t sport_is_app_sponsor;
    uint8_t sport_prepare_sent;
    uint8_t send_request_timeout;   
	auto_pause_dst_t auto_pause_dst;
    uint8_t gps_accuracy;//0->low,1->mid,2->high,10->unkonw
    bool is_auto_sport;//运动识别开关
    uint8_t gps_pre_code;
    bool sport_interval_train_is_close; // 用于副屏运动开始前有间歇训练先关闭间歇训练标志
    bool Sport_save_data_flag;
    bool sports_send_cmd_switch;
    uint32_t Algorithmic_stand_assist;
    auto_sport_ctrl_t auto_sport_ctrl;
    sport_basic_data_t sport_base_data;
    SPORT_app_auto_sport_obj_t auto_sport_obj; // 运动识别缓存区
    bool sport_lock_flag;//锁屏标志
    uint8_t sport_recorde_type;//运动结束时的type
    bool sporting_to_sport_record_flag;//是从运动结束跳到运动记录的标志
    uint32_t sport_roller_data;//roller当前转换后的值
    uint8_t unwear_dura;
	uint16_t pausetostop;
	uint16_t low_speed_cnt;
	 uint32_t app_calories; 
    bool is_enter_interval_training;//是否进入间歇训练
    swim_data_t swim_data;//小节
    swim_data_t swim_segmet_data;//段落
    uint32_t swim_count;
    uint8_t is_set_swim_points;
    bool swim_get_record;//标志位用于获取游泳报告
    double* gps_lon;
    double* gps_lat;
    double* gps_temp_x;
    double* gps_temp_y;
    sport_record_max_t record_max;//用于抽点时候处理某些数据
    uint8_t draw_points_flag;//抽点时的标志
    bool draw_points_complete;//抽点完成调用b
    uint8_t gps_level;
	uint8_t useddeive_cnt;
	uint8_t usedphone_cnt;
	uint8_t newmark;
    uint8_t remind_wear_count;//运动佩戴提醒
    uint16_t sport_loading_count;//运动加载等待时间
    bool support_sport_screen;//支持运动投屏
    uint8_t dev_gps_position_status;
    uint8_t auto_sportting_flag;//从运动识别进入运动中的标志
    uint8_t swim_remind;//游泳锁屏提示,恢复出厂重置
    uint8_t ios_app_exit;
    uint8_t treadmill_timeout;//副屏运动跑步机delay
    uint32_t copy_choose_target;//此变量为复制品为了清除部分运动设置
    uint8_t change_level;//改变系统亮度水平flag
    uint32_t copy_time_cont;
    uint32_t total_avg_steps_lenght;//总步幅
    uint32_t total_avg_steps_lenght_count;//步幅总次数
    uint8_t gps_source ;
	uint32_t auto_sportting_indoor_step;
	uint32_t auto_sportting_indoor_disc;
} ms_sport_misc_t;


#ifdef XIAOMI_ALGO_LIB_ON_LCPU
extern SPORT_HEART_RATE_INFO_STRU heart_range_info;
#else
typedef struct _sport_params_s {
  uint8_t data_len;
  float params[50];
} sport_param_s;
#endif
/********************************************************运动相关 end********************************************************/
extern uint8_t sport_save_data_record_num;
extern uint8_t sport_save_data_record_table[MAX_SPORT_RECORD_NUM];
extern SPORT_setting_target_data_t sport_setting_target_data[MAX_SPORT_SEETING_TARGET_NUM];
extern Sport_Best_Data_t Sport_Best_Data[BEST_LOCAL_MAX];
extern SPORT_app_target_data_t sport_app_target;
extern Sport_Best_Data_t Sport_Best_Data_APP[BEST_LOCAL_MAX];
extern ms_sport_misc_t misc_sport_data;
extern SPORT_data_save_data_t sport_save_data;
extern SPORT_save_data_t sport_save_sport_record_data;
extern sport_param_s indoor_calibration;
extern sport_detect_dst_t sport_detect_dst;

void clear_all_sport_seeting_data(void);
void set_sport_record_data(SPORT_save_data_t *data, uint8_t record_table);
void clear_sports_information_data(void);
void read_sport_information_data_init(void);
void save_sport_information_data_init(void);
void set_sport_record_data(SPORT_save_data_t *data, uint8_t record_table);
void get_sport_record_data(SPORT_save_data_t *data, uint8_t record_table);
// 保存运动数据到外部flash
void Save_Sport_data_to_exflash(uint8_t sport_type);
#define get_sport_save_data_record_num() sport_save_data_record_num
#define set_sport_save_data_record_num(VAL) sport_save_data_record_num = VAL 
//****************************************课程排序结构******************************************************
typedef struct
{
    uint16_t use_count;  // 使用次数
    uint8_t sport_type; // 运动类型
    uint8_t base_index;//出厂位置
} _user_sport_course_type;
typedef struct
{
    _user_sport_course_type sport_course_list[Sport_Cource_max];
} user_sports_course_t;
extern user_sports_course_t sport_course;
void init_app_sports_course_data(void);
void set_app_sports_course_data(user_sports_course_t *p_sports_course);
void get_app_sports_course_data(user_sports_course_t *p_sports_course);
//****************************************运动列表排序结构******************************************************
typedef struct
{
    uint8_t sport_index;
    uint8_t sport_type;
    uint16_t sport_use_count;
    uint8_t sport_gourp; // 1水上运动,2户外运动,3训练,4舞蹈类运动,5搏击类运动,6球类运动,7冰雪运动,8休闲运动,9棋牌运动,10其他运动
} user_sport_list_type_t;
extern user_sport_list_type_t sport_list_sort_array[MAX_SPORT_SEETING_TARGET_NUM];
void init_app_sports_list_data(void);
void set_app_sports_list_data(user_sport_list_type_t *p_sport_list);
void get_app_sports_list_data(user_sport_list_type_t *p_sport_list);
//****************************************************************************************************************
void read_record_to_draw_points(uint16_t sport_type);
#if defined(USING_GYRO_SENSOR) && defined(ENUM_PROJECT_NAME_N65B_GLOBAL) 
extern sw_record_t *p_swim_list;
void zh_app_sport_swim_list_add(sw_record_t *new_data);
// 尾插法插入节点
void zh_app_sport_swim_list_append(sw_record_t **head_ref, sw_record_t *new_data);
// 读取指定节点
sw_record_t *zh_app_sport_swim_list_read(uint16_t offset);
// 删除所有节点
void zh_app_sport_swim_list_delete(void);
// 打印链表
void printList(sw_record_t *node);
#endif
#endif /* _ZH_APP_SPORTS_DATA_H_ */
