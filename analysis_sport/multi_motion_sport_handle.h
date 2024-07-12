#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#ifndef _MULTI_MOTION_SPORT_HANDLE_H
#define _MULTI_MOTION_SPORT_HANDLE_H

#include "stdint.h"
#include "stdbool.h"
#include "mul_sport_data_struct.h"
#include "mul_sport_sector_id_list.h"


#if (MULTI_MOTION_SPORT_NUMS < 2)
//#error "Insufficient storage space for multiple sports!"
#endif

#define MULTI_MOTION_DATA_SECTOR_NUM    (MULTI_MOTION_SPORT_NUMS)

#define MULTI_IDX_NUMS                  620

#define SPORT_DATA_ID_SIZE              7   // 运动数据索引ID的占用字节数
#define SPORT_DATA_LEN_SIZE             4   // 写入运动数据的占用字节数
#define SPORT_DATA_FLAG_SIZE            1   // 写入运动数据报告标志位占用的字节数
#define SPORT_REPORT_FLAG_SIZE          1   // 写入运动报告标志位的占用字节数
#define SPORT_REPORT_ID_SIZE            7   // 运动报告索引ID的占用字节数
#define SPORT_REPORT_LEN_SIZE           2   // 运动报告的占用字节数
#define SECTOR_NUMS_SIZE                2   // 写入扇区数量的占用字节数
#define SECTOR_NUM_SIZE                 2   // 分配的扇区编号的占用字节数

/* MIN_SPORT_IDX_SIZE == 25 */
#define MIN_SPORT_IDX_SIZE              \
    (SPORT_DATA_ID_SIZE + SPORT_DATA_LEN_SIZE + SPORT_DATA_FLAG_SIZE + SPORT_REPORT_FLAG_SIZE \
    + SPORT_REPORT_ID_SIZE + SPORT_REPORT_LEN_SIZE + SECTOR_NUMS_SIZE + SECTOR_NUM_SIZE)

#define MIN_AUTO_SPORT_SECTOR_NUMS      (4)
#define MIN_AUTO_SPORT_IDX_SIZE         ((MIN_SPORT_IDX_SIZE) + ((MIN_AUTO_SPORT_SECTOR_NUMS - 1)  * (SECTOR_NUM_SIZE)))

#define SPORT_ID_POS                    0                                                   // 0
#define SPORT_DATA_LEN_POS              (SPORT_ID_POS + SPORT_DATA_ID_SIZE)                 // 0 + 7
#define SPORT_DATA_FLAG_POS             (SPORT_DATA_LEN_POS + SPORT_DATA_LEN_SIZE)          // 0 + 7 + 4
#define SPORT_REPORT_FLAG_POS           (SPORT_DATA_FLAG_POS + SPORT_DATA_FLAG_SIZE)        // 0 + 7 + 4 + 1
#define SPORT_REPORT_ID_POS             (SPORT_REPORT_FLAG_POS + SPORT_REPORT_FLAG_SIZE)    // 0 + 7 + 4 + 1 + 1
#define SPORT_REPORT_LEN_POS            (SPORT_REPORT_ID_POS + SPORT_REPORT_ID_SIZE)        // 0 + 7 + 4 + 1 + 1 + 7
#define SECTOR_NUMS_POS                 (SPORT_REPORT_LEN_POS + SPORT_REPORT_LEN_SIZE)      // 0 + 7 + 4 + 1 + 1 + 7 + 1
#define SECTOR_NUM_POS                  (SECTOR_NUMS_POS + SECTOR_NUMS_SIZE)                // 0 + 7 + 4 + 1 + 1 + 7 + 1 + 2

#define SPORT_REPORT_MAX_BYTES           200    // 运动报告的最大字节数


#define OUTSIDE_RUN_FIXED_BYTES          12     // 户外运动固定的数据头的字节数
#define OUTSIDE_CYCLE_FIXED_BYTES        12     // 户外骑行
#define INDOOR_RUN_FIXED_BYTES           8      // 室内跑步固定的数据头的字节数
#define INDOOR_CYCLE_FIXED_BYTES         8      // 室内骑行/自由训练
#define SWIMMING_FIXED_BYTES             8      // 游泳/开放泳池游泳

typedef struct
{
    int16_t remind_sector_num;
    uint8_t sector_table[MULTI_MOTION_DATA_SECTOR_NUM];
} multi_motion_sector_table_t;


typedef struct
{
    uint8_t            magic_number;
    uint8_t            version;
    uint16_t           flash_crc;
    store_flag_type_t  store_flash_flag;
    uint16_t           idx_nums;  // 索引数量
    uint8_t            idx_data[MULTI_IDX_NUMS];
} multi_motion_data_idx_table_t;

multi_motion_data_idx_table_t *get_multi_motion_idx_table(void);

void read_multi_motion_idx_table(void);

bool clear_abnormal_multi_motion_id(void);

void free_all_mul_motion_sector(void);

void erase_multi_motion_idx_table(void);
bool read_motion_sector_table(void);

void set_outside_run_data(void);
void set_indoor_run_data(void);
void set_outside_cycle_data(void);
void set_indoor_cycle_data(void);

void set_outside_run_repo_data(void);
void set_indoor_run_repo_data(void);
void set_outside_cycle_repo_data(void);
void set_indoor_cycle_repo_data(void);

uint16_t get_sport_idx_nums(void);

//void multi_motion_init(void);
//void multi_motion_deinit(void);
bool del_sport_file(const data_id_t *p_id);
bool del_sport_file_by_idx_num(uint16_t idx_num);

/* 写入运动头部 */
multi_motion_ret app_write_sport_head(void);

/* 写入运动数据 */
multi_motion_ret app_write_sport_data(void);

/* 写入运动数据的固定头部 */
multi_motion_ret app_write_sport_fixed_data(void);

/* 写入运动报告 */
multi_motion_ret app_write_sport_report(void);

void app_clear_sport_data(void);
void app_clear_sport_report(void);
void app_clear_cur_sport_data_id(void);


/* 获得有效的数据索引 */
bool app_get_multi_motion_intraday_valid_id(data_id_t *p_id, uint32_t *id_num, const uint32_t max_id_nums);
bool app_get_multi_motion_historical_valid_id(data_id_t *p_id, uint32_t *id_num, const uint32_t max_id_nums);

/* 根据数据ID, 获取数据的大小 */
bool app_get_multi_motion_data_len(const data_id_t *p_id, uint32_t *data_len);

/* 根据数据ID和数据长度和偏移量, 获得对应的数据 */
bool app_read_multi_motion_data
(const data_id_t *p_id, void *pdata, uint32_t data_len, uint32_t offset);

bool app_del_multi_motion_id(const data_id_t *p_id);

p_data_id_t get_cur_sport_data_id(void);

void set_sport_data_len_offset(void);

void set_recovery_motion_timestamp(utc_time_t);
void set_fixed_data_base_pos(uint32_t);
void set_mul_sport_cnt(uint32_t);
void set_swimming_turn_cnt(uint32_t);

uint32_t get_swimming_turn_cnt(void);

void set_mul_sport_start_time(utc_time_t);
utc_time_t get_mul_sport_start_time(void);
void set_mul_sport_end_time(utc_time_t timestamp);
utc_time_t get_mul_sport_end_time(void);
uint32_t get_recovery_motion_timestamp(void);
uint32_t get_mul_sport_cnt(void);
void set_mul_sport_total_point_cnts(uint32_t new_point_cnts);
void add_mul_sport_total_point_cnts(uint32_t delta_point_cnts);
uint32_t get_mul_sport_total_points_cnts(void);
void set_mul_sport_segment_distance(uint32_t new_point_distance);
void add_mul_sport_segment_distance(uint32_t new_point_distance);
uint32_t get_mul_sport_segment_distance(void);
void set_mul_sport_segment_count(uint16_t new_point_count);
void add_mul_sport_segment_count(uint32_t new_point_count);
uint32_t get_mul_sport_segment_count(void);
void set_initialize_altitude(float new_altitude);
float get_initialize_altitude(void);
Sport_Type_Type get_sub_sport_type(void);
void set_sub_sport_type(Sport_Type_Type sport_type);
void set_sport_sit_type(Sport_Interval_Training_Type sit_type);
Sport_Interval_Training_Type get_sport_sit_type(void);
void set_sport_next_sit_type(Sport_Interval_Training_Type sit_type);
Sport_Interval_Training_Type get_sport_next_sit_type(void);
void set_is_change_sit_type(bool is_change);
bool get_is_change_sit_type(void);


multi_motion_ret multi_motion_save_sport_data(void);

/*
 * @note idx从0开始
 */
bool app_get_id_by_idx(data_id_t *p_id, uint16_t idx);

void set_is_up_km_status(bool status);
bool get_is_up_km_status(void);
void set_is_up_mile_status(bool status);
bool get_is_up_mile_status(void);

void write_multi_motion_idx_table(void);

/* 空间即将用尽 */
bool is_space_will_full(void);

/* 空间已满 */
bool is_space_was_full(void);

/* 运动识别空间已满 */
bool is_space_was_full_by_auto_sport(void);

uint32_t get_cur_sport_handle_data_len(void);

multi_motion_ret app_set_sport_data(void);
multi_motion_ret app_set_sport_repo_data(void);

multi_motion_ret app_set_swimming_data(Swimming_Data_Type_V1 swimming_data);
multi_motion_ret app_set_swimming_repo_data(Report_Swimming_Data_Type_V1 swimming_repo_data);

/**
 * @brief 是否正在运动
 */
bool is_doing_sports(void);


uint32_t multi_motion_get_prev_calorie(void);
void     multi_motion_set_prev_calorie(uint32_t new_calorie);
uint32_t multi_motion_get_prev_step(void);
void     multi_motion_set_prev_step(uint32_t new_step);
uint32_t multi_motion_get_prev_distance(void);
void     multi_motion_set_prev_distance(uint32_t new_distance);
void     multi_motion_set_prev_cyclic_sport_counter(uint32_t new_counter);
uint32_t multi_motion_get_prev_cyclic_sport_counter(void);

void multi_motion_delete_cur_sport_list_item(void);
void multi_motion_clear_sport_global_var(void);

multi_motion_ret multi_motion_new_sport_file(void *args, uint32_t time_stamp);
multi_motion_ret multi_motion_write_sport_fixed_data(void);
multi_motion_ret multi_motion_write_sport_sec_point_data(void);
multi_motion_ret multi_motion_write_sport_head(void);
multi_motion_ret multi_motion_write_sport_report(void);
void multi_motion_save_sport_file(void);
multi_motion_ret multi_motion_app_write_sport_data(void *p_input_data, void *p_input_data_args);
multi_motion_ret multi_motion_app_set_sport_repo(void *p_input_data, void *p_input_data_args);
bool multi_motion_get_sub_sport_type(const data_id_t *p_id, Sport_Type_Type *sub_sport_type);

void set_cyclic_sport_counter(uint32_t new_counter);
uint32_t get_cyclic_sport_counter(void);
multi_motion_ret multi_motion_write_mass_sport_data(void *data, uint32_t data_len);

uint32_t multi_motion_get_record_item_nums(p_data_id_t p_id);
uint32_t multi_motion_get_record_nitem(p_data_id_t p_id, ms_record_item_t *p_item, const uint32_t offset_item, const uint32_t need_item_nums);
uint32_t multi_motion_get_cur_record_item_nums(void);
uint32_t multi_motion_get_cur_record_nitem(ms_record_item_t *p_item, const uint32_t offset_item, const uint32_t need_item_nums);


#endif /* _MULTI_MOTION_SPORT_HANDLE_H */

#endif /* FLASH_MANAGER_SWITCH */
