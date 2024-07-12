#ifndef _MUL_SPORT_PLATFORM_H
#define _MUL_SPORT_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "mul_sport_common.h"
#include "mul_sport_data_struct.h"
#include "vital_info_platform.h"

/* porting start */
//#include "rtthread.h"
//#include "zh_middle_data_manager.h"
#include "zh_app_sports_data.h"
#include "zh_flash_memory.h"
#include "zh_flash_map.h"
/* porting end */

/** @def FLASH_MANAGER_START_ADDR @note flash_manager开始flash地址, 需要设置 */
#define FLASH_MANAGER_START_ADDR   (0x00000000)

/** @def FLASH_MANAGER_END_ADDR @note flash_manager结束flash地址, 需要设置 */
#define FLASH_MANAGER_END_ADDR     (FLASH_MANAGER_START_ADDR + SPORT_DATA_TOTAL_SIZE)

/** @def FLASH_MANAGER_SECTOR_SIZE @note flash_manager扇区的大小, 需要设置 */
#define FLASH_MANAGER_SECTOR_SIZE  (0x01000)

/** @def MUL_SPORT_ALIGN_WAY @note 多运动全局变量对齐方式 */
#define MUL_SPORT_ALIGN_WAY          __declspec(align(4))

/** @def MUL_SPOmalloc_SWITCH @note 是否使用动态分配 */
#define MUL_SPOmalloc_SWITCH        1

#if MUL_SPORT_LOG_DBG_SWITCH
#define mul_sport_dbg_log(fmt, ...)    printf("\r\n[mul sport] "fmt, ##__VA_ARGS__)
#else
#define mul_sport_dbg_log(fmt, ...)
#endif

#define mul_spomalloc    malloc
#define mul_spofree      free

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
extern uint8_t sport_state_act;
/* porting start */
typedef uint32_t input_sport_t; //!< @brief 运动类型    // TODO: porting
/* porting end */

uint16_t Convert_Sport_Store_Type_to_Sport_Task_Type(Sport_Type_Type sport_type);

utc_time_t mul_sport_get_timestamp(void);

int8_t mul_sport_get_time_zone(void);

uint32_t mul_sport_get_rand(void);

bool mul_sport_write_info_data(uint8_t *p_data, uint32_t addr, uint16_t data_len);

bool mul_sport_read_info_data(uint8_t *p_data, uint32_t addr, uint16_t data_len);

bool mul_sport_erase_sector(uint32_t sector_addr);

/* 多运动运动打点 */
//
uint32_t mul_sport_get_sport_time_start(void);
uint32_t mul_sport_get_sport_time_count(void);
uint32_t mul_sport_get_sport_distance(void);
uint32_t mul_sport_get_sport_fixed_distance(void);
uint16_t mul_sport_get_sport_speed_distribution(void);
uint16_t mul_sport_get_sport_avg_speed_distribution(void);
uint32_t mul_sport_get_sport_maximum_speed_distribution(void);
uint32_t mul_sport_get_sport_minimum_speed_distribution(void);
uint8_t  mul_sport_get_sport_heart_rate(void);
uint16_t mul_sport_get_sport_rm_frequency(void);
uint16_t mul_sport_get_sport_step_frequency(void);
uint16_t mul_sport_get_sport_maximum_step_frequency(void);
uint16_t mul_sport_get_sport_avg_step_frequency(void);
uint32_t mul_sport_get_sport_speed(void);
uint32_t mul_sport_get_sport_step_num(void);
float    mul_sport_get_sport_consume(void);
uint16_t mul_sport_get_sport_total_consume(void);
uint8_t  mul_sport_get_sport_extra_stride(void);
uint32_t mul_sport_get_cyclic_sport_counter(void);
uint32_t mul_sport_get_max_cyclic_sport_counter(void);
uint32_t mul_sport_get_avg_cyclic_sport_counter(void);
uint32_t mul_sport_get_target_duration(void);
uint16_t mul_sport_get_target_calorie(void);
uint32_t mul_sport_get_target_distance(void);
uint16_t mul_sport_get_target_times(void);
uint16_t mul_sport_get_target_cadence(void);
uint32_t mul_sport_get_target_pace(void);
bool mul_sport_report_ver_special_handler(Sport_Type_Type sport_type, uint8_t *p_report_ver);

void write_sport_data_work_start(void);
float mul_sport_get_sport_restart_altitude(void);
float mul_sport_get_sport_basic_altitude(void);
uint8_t mul_sport_get_sport_altitude_change_type(void);
uint8_t mul_sport_get_sport_altitude_change_val(void);
float mul_sport_get_total_up(void);
float mul_sport_get_total_down(void);
float mul_sport_get_avg_height(void);
float mul_sport_get_max_height(void);
float mul_sport_get_min_height(void);

float mul_sport_get_sport_avg_speed(void);
uint32_t mul_sport_get_sport_last_km_avg_speed(void);
float    mul_sport_get_sport_limit_speed(void);
uint8_t  mul_sport_get_sport_avg_heart_rate(void);
uint8_t  mul_sport_get_sport_maximum_heart_rate(void);
uint8_t  mul_sport_get_sport_minimum_heart_rate(void);
uint32_t mul_sport_get_sport_heart_rate_limit_time(void);
uint32_t mul_sport_get_sport_heart_rate_without_oxygen_time(void);
uint32_t mul_sport_get_sport_heart_rate_with_oxygen_time(void);
uint32_t mul_sport_get_sport_heart_rate_fat_burning_time(void);
uint32_t mul_sport_get_sport_heart_rate_warming_up_time(void);
uint8_t mul_sport_get_sport_genki_value(void);
uint16_t mul_sport_get_sport_avg_stride(void);
bool mul_sport_get_cur_sport_config(void **pp_sport_cofig);

uint32_t mul_sport_get_swimming_turn_cnt(void);
uint32_t mul_sport_get_swimming_subsection(void);

input_sport_t mul_sport_get_input_sport_type(void);

void mul_sport_space_is_exhausted_cb(void);
void mul_sport_space_is_not_enouth_cb(void);

bool mul_sport_upload_sport_file_succeed_cb(data_id_t sport_id, uint32_t args);
bool mul_sport_delete_sport_file_succeed_cb(data_id_t sport_id, uint32_t args);

bool mul_sport_platform_init(void);
bool mul_sport_platform_compare_key(const void *dist_args_obj, const void *src_args_obj);

bool mul_sport_platform_change_sit_type(SPORT_interval_training_type next_type);
bool mul_sport_platform_get_data_header_ptr(data_id_t *p_id, uint8_t **pp_header_data, size_t *p_data_len);
uint32_t mul_sport_platform_get_item_nums(p_data_id_t p_id);
bool mul_sport_platform_get_record_info(data_id_t *p_id, ms_record_info_t *p_record_info);
bool mul_sport_platform_get_record_head(data_id_t *p_id, uint8_t *p_input_read_buf, ms_record_head_t *p_record_head);
bool mul_sport_platform_get_record_body(data_id_t *p_id, uint8_t *p_input_read_buf, ms_record_item_t *p_record_item);
bool mul_sport_platform_get_record_is_detail_body(data_id_t *p_id, uint8_t *p_input_read_buf);
void mul_sport_platform_auto_sport_write_data(void);
void mul_sport_platform_auto_sport_write_gps(void);
void mul_sport_platform_auto_sport_put_data(void);

// extern void music_timeout_timer_start(void);
bool mul_sport_get_open_gps_sport_status(void);
uint16_t Get_current_sporting_type(void);
void write_sport_data_work_start(void);
void sport_resume_process_work_start(void);
void save_cur_sport_file_work_start(void);
void write_sport_data_work_proc(void);
void save_cur_sport_file_work_proc(void);
void Set_current_sproting_type(uint16_t type);
uint8_t Comparison_sport_record_display_table(uint8_t data);
void save_cur_sport_record(void);
void draw_cur_sport_points_work(void);//抽点函数调用
uint16_t Get_current_sporting_subtype(void);
void Set_current_sproting_subtype(uint16_t type);
bool mul_sport_platform_change_sit_type_not_resume(SPORT_interval_training_type next_type);
Sport_Interval_Training_Type mul_sport_platform_get_sport_next_sit_type(void);
void mul_sport_platform_malloc_failed(const char *func_name, uint32_t line);
void save_cur_sport_file_work_when_full(void);//空间满需要调用此函数保存运动记录抽点等流程都在里面
void save_cur_sport_file_work_start_when_full(void);
void mul_sport_new_iphone_work(void);
SPORT_app_auto_sport_gps_obj_t* mul_sport_platform_auto_sport_get_gps_data(void);
void mul_sport_platform_auto_sport_memset_gps_data(void);
void mul_sport_platform_auto_sport_put_gps_data(ms_gps_item_t gps_item);
#define  MUL_SPORT_PLATFORM_MALLOC_FAILED()  mul_sport_platform_malloc_failed(__func__, __LINE__)

#ifdef __cplusplus
}
#endif


#endif /* _MUL_SPORT_PLATFORM_H */
