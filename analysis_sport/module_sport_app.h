#ifndef _MODULE_SPORT_APP_H
#define _MODULE_SPORT_APP_H

#include "stdbool.h"
#include "stdint.h"
//#include "zh_middle_data_manager.h"
#include "mul_sport_platform.h"
#include "mul_sport_common.h"
#include "zh_app_sports_data.h"

#if defined(ENUM_PROJECT_NAME_N65B_GLOBAL)  
#define ZH_GPS_DRAW 1
#endif
#define MI_GPS_DRAW 0
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
	uint32_t segment_timestamp;
	float segment_kcal;
} _Sport_interval_training_type; // 间歇训练结构体
typedef struct
{
	uint32_t sport_timecount1;
	uint32_t sport_timecount2;
	uint32_t sport_timecount3;
	uint32_t sport_timedelay1;
	uint32_t sport_timedelay2;
	uint32_t sport_timedelay3;
	bool sport_time1_switch;
	bool sport_time2_switch;
	bool sport_time3_switch;
	uint8_t sport_timecount1_keep;//持续处于该区间段，则播报间隔60、180、300、600秒 bit0->60....bit3->600
	uint8_t sport_timecount2_keep;//持续处于该区间段，则播报间隔60、180、300、600秒 bit0->60....bit3->600
	uint8_t sport_timecount3_keep;//持续处于该区间段，则播报间隔60、180、300、600秒 bit0->60....bit3->600
	uint8_t sport_pace_speed_last_remind;//上一次是什么提醒
	bool sport_high_low_switch;
	bool sport_hr_remind_switch;
	uint8_t hr_remind_keep;//持续处于该区间段，则播报间隔60、180、300、600秒 bit0->60....bit3->600
	uint32_t sport_hr_timeout;
	uint32_t sport_hr_timedelay;
	//心率区间
	uint16_t hr_inter_timecount_high;
	uint16_t hr_inter_timecount_keep;
	uint16_t hr_inter_timecount_low;
	uint16_t hr_inter_delay_high;
	uint16_t hr_inter_delay_keep;
	uint16_t hr_inter_delay_low;
	uint8_t hr_inter_last_switch;//上一次是哪个区间提醒 1->high 2->keep 3->low
	bool hr_inter_high_switch;
	bool hr_inter_keep_switch;
	bool hr_inter_low_switch;	
	uint8_t hr_inter_high_keep;//持续处于该区间段，则播报间隔60、180、300、600秒 bit0->60....bit3->600
	uint8_t hr_inter_low_keep;//持续处于该区间段，则播报间隔60、180、300、600秒 bit0->60....bit3->600	
	//智能陪跑
	uint16_t auto_pace_timecount_lead;//领先
	uint16_t auto_pace_delay_lead;//领先
	uint16_t auto_pace_timecount_backward;//落后
	uint16_t auto_pace_delay_backward;//落后
	uint8_t auto_pace_last_remind;// 1 领先 2落后
	uint8_t auto_pace_lead_keep;//持续处于该区间段，则播报间隔3min,5min,10min bit0->3....bit2->10
	uint8_t auto_pace_backward_keep;//持续处于该区间段，则播报间隔3min,5min,10min bit0->3....bit2->10	
	bool auto_pace_lead_switch;//
	bool auto_pace_backward_switch;
	bool gps_weak_no_remind;
	uint32_t gps_weak_time_count;
	uint16_t gps_weak_delay_count;
	bool gps_weak_flag;
} Sport_Remind_Type; // 提醒状态结构体
typedef struct
{
	Running_course_type sport_course_type;//课程类型,0代表无课程,
	Running_course_sub_type current_sub_type;//当前课程子类型
	uint8_t current_subsection;//当前是第几小节
	uint8_t total_subsection;//总共多少小节
	uint16_t current_course_time_count;
	uint16_t total_course_time_count;
	uint32_t total_time_count;
} Sport_Running_Course_Type; //课程结构体
enum
{
    AUTO_SPORT_IDLE,
    AUTO_SPORT_DETECING,
    AUTO_SPORT_PREPOINT,
    AUTO_SPORT_REMIND,
    AUTO_SPORT_ONGO,
    AUTO_SPORT_END,
};

enum
{
	REMIND_KCAL,
	REMIND_DISTANCE,
	REMIND_TIME,
	REMIND_COUNT,
};
typedef enum 
{
    SPORT_POINTS_NULL = 0,
    SPORT_POINTS_SUBSECTION = 1,//小节
    SPORT_POINTS_SEGMENT = 2,//段落
    SPORT_POINTS_PAUSE = 3,//暂停
    SPORT_POINTS_STOP = 4,//结束
} SPORT_POINTS_TYPE;

typedef enum 
{
    SPORT_MUL_SET_DISTANCE = 0,//距离设置
    SPORT_MUL_SET_TIME,//时间设置
    SPORT_MUL_SET_KCAL,//卡路里设置
    SPORT_MUL_SET_COUNT,//个数设置
    SPORT_MUL_SET_TIMES,//次数设置
	SPORT_MUL_SET_TRIPS,//趟数设置
	SPORT_MUL_SET_POOL_LENS,//泳池长度
    SPORT_MUL_DISTANCE_KM,//距离km
    SPORT_MUL_DISTANCE_M,//距离m	
	VITALITY_STEPS_UNIT,//活力指标%d步
	VITALITY_INTENSITY_UNIT,//活力指标%d分钟
	VITALITY_STAND_UNIT,//活力指标%d次
	SPORT_MUL_SPM,//划频(次/分)
	SPORT_MUL_STEPS_UNIT,//运动中步数
	SPORT_MUL_SET_GROUP,//组数设置
} SPORT_MUL_TYPE;//多语言case

extern uint8_t sport_state_act;

// 选中打点

extern uint8_t sport_state_act;
extern uint8_t used_local_gps;
extern uint8_t had_cailib;

void module_ms_app_sport_set_points_flag(uint8_t setting_type);
// 清除选中打点
void module_ms_app_sport_clear_points_flag();
bool module_ms_app_get__data_points_is_switch(SPORT_POINTS_TYPE type);
extern Sport_Remind_Type sport_remind_struct;
extern _Sport_interval_training_type sport_interval_training;
extern Sport_Running_Course_Type sport_running_course;
uint8_t module_ms_app_get_sport_class(uint16_t sport_type);
void module_ms_app_set_sport_list_usecount(uint16_t sport_type); // 使用后加1
bool module_ms_app_get__data_target_is_switch(Sport_type sprot_type, SPORT_SEETING_TYPE type);
void module_ms_app_sport_set_sport_target(uint16_t sport_type, uint8_t setting_type);
void module_ms_app_sport_clear_sport_target(uint16_t sport_type, uint8_t setting_type);
bool module_ms_sport_app_is_frist_page(uint16_t sport_type); // 判断运动是否在首页
uint8_t module_ms_sport_app_get_group(uint16_t sport_type,bool init);
bool module_ms_app_is_distance_sport_type(Sport_type sport_type);
void sport_data_processing(void);
uint16_t sport_data_get_send_step(uint16_t step_data);
void sport_data_set_second_step(uint16_t step_data);

bool sport_pause(void);
bool sport_stop(void);
bool sport_start(Sport_type sport_type);
bool sport_restart(void);
bool sport_discard(void);

void sport_update_skipping_rope_count(uint32_t count, bool clear_flag);
bool module_ms_app_is_gps_sport_type(Sport_type sport_type);
void auto_sport_ctrl_init(uint16_t dis_time);
void pop_sport_event(void);
void push_sport_event(uint16_t evt);
void sport_state_log(uint8_t act);
void sport_data_running_course_processing(void);
void sport_course_second_processing();
uint8_t Get_current_sporting_course_type(void);
void init_sport_course_somethings(Running_course_type type);
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
SportType pb_sport_type_trans(Sport_type local_sport_type);
uint32_t pb_sport_type_trans_to_local(SportType app_sport_type);
extern void miwear_sport_pre_request(uint16_t sport_type);
extern int miwear_sport_request(uint8_t cmd, uint16_t sport_type);
#else

 typedef enum {
   MI_HAR_UNKNOWN = 0,
   MI_HAR_WALK,
   MI_HAR_RUN,
   MI_HAR_ROWING,
   MI_HAR_ELLIPTICAL,
   MI_HAR_BIKE,
   MI_HAR_JUMP_ROPE,
   MI_HAR_NUM_TYPES,
 } MIHARType;

#endif
#define LOAD_TIME_OUT 300
typedef enum
{
	PROJECTION_POINT = 1,//投屏打点
	PROJECTION_REPORT,//投屏报告
	PROJECTION_CONNECT,
	PROJECTION_DISCONNECT,
}PROJECTION_type;
typedef struct
{
	uint16_t sport_type;
	SPORT_point_max_t type;
	uint32_t value;
} Sport_Points_type;
 void miwear_save_vitaliy_log_data_direct_flash(uint8_t *data, uint16_t data_len);
 void module_ms_app_sport_open_heart(bool open,uint8_t heart_style);
 void module_ms_app_set_upload_flag(bool flag);
 bool module_ms_app_get_upload_flag();
 void module_ms_app_clear_base_sport_obj(void);
 uint8_t module_ms_app_get_list_type_array(uint8_t page_index, uint8_t *p_buff, uint16_t buff_len);
 void sport_handle(void);
 bool Get_sport_save_status(void);
 void auto_sport_ctrl_timing(void);
 void sport_input_event_proc(uint8_t cmd,uint32_t para);
 void sport_ing_end_jump_to_table();
 void sport_data_interval_training_processing();
 void check_sport_pause_or_stop(void);
#if 0
 void Check_Alg_Sport_Distance_up_to_standard(UTCTimeStruct *tmp_time_p);
 void Check_Alg_Sport_Consume_up_to_standard(UTCTimeStruct *tmp_time_p);
 void Check_Alg_Sport_Time_up_to_standard(UTCTimeStruct *tmp_time_p);
 void Check_Alg_Sport_Count_up_to_standard(UTCTimeStruct *tmp_time_p);
 void Check_Alg_Sport_Best_Points_Remind(UTCTimeStruct *tmp_time_p);     	
 void Check_Alg_Sport_pace_speed_remind(UTCTimeStruct *tmp_time_p);
 void Check_Alg_Sport_High_Hr_Remind(UTCTimeStruct *tmp_time_p);
 void Check_Alg_Sport_Distance_up_to_whole_kilomoter(UTCTimeStruct *tmp_time_p);
 void Check_Alg_Sport_Energy_Supply_Remind(UTCTimeStruct *tmp_time_p);             
 void _module_sport_app_update_sport_points(Sport_Points_type param);
 bool module_sport_app_course_is_sportting(void);
 void Check_Alg_Sport_Phone_Connect_Disconnect(UTCTimeStruct *tmp_time_p);
 void Check_Alg_Sport_Phone_Gps_Weak(UTCTimeStruct *tmp_time_p);
#endif
uint8_t module_ms_app_get_running_course_type_array(uint8_t *p_buff, uint16_t buff_len);
void module_ms_app_set_sport_running_course_usecount(uint16_t sport_sub_type);
void zh_miwear_sport_pre_request(uint16_t sport_type);
int zh_miwear_sport_request(uint16_t cmd, uint16_t sport_type);
void zh_wear_upload_sport_v2a_data(void);
void zh_wear_upload_sport_base_data(void);
void zh_wear_upload_sport_sensor_data(uint8_t sector);
#if 0
void Check_Alg_Sport_Heart_Rate_Interval_Remind(UTCTimeStruct *tmp_time_p);
void Check_Alg_Sport_auto_pace_remind(UTCTimeStruct *tmp_time_p);
#endif
uint16_t module_mul_sport_get_best_points_index();
void module_sport_app_new_iphone_operate(void);
void mdoule_ms_sport_app_swim_jump_to_where(void);
void module_sport_app_new_sport_screen_state(bool flg);
uint8_t module_sport_get_gps_status(void);
void module_sport_app_erase_target(void);
void module_sport_app_release_target(void);
bool module_sport_app_send_app_sport_pause(void);
bool module_sport_app_send_app_sport_restart(void);
void mdoule_sport_app_control_heart(void);
bool module_sport_app_is_sportting(void);
void set_event_subtype(uint8_t sub_type);
bool sport_stop_when_full(void);
void zh_sports_data_projection_ble_process(uint8_t type);
void zh_sports_data_projection(uint8_t type);
uint8_t module_ms_app_get_ios_app_exit(void);
void module_ms_app_set_ios_app_exit(uint8_t ios_app_exit);
bool module_ms_app_sport_is_water_sports(uint16_t type);
void module_sport_app_clear_target(uint32_t flag);
#define module_sport_app_update_sport_points(...) _module_sport_app_update_sport_points((Sport_Points_type){__VA_ARGS__})
uint8_t app_sporting_get_brightness_level(void);
bool app_sportting_is_change_brightness_level(void);
void module_sport_app_set_change_level(uint8_t level);
uint8_t mdoule_sport_app_get_change_level(void);
bool app_sportting_is_close_screen(void);
bool module_sport_app_get_is_running_page(void);
void module_sport_app_switch_sport_heart(void);
 #define INTERVAL_TRAINING_SELECT 1
#endif
