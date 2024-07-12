#ifndef _VITAL_INFO_DATA_HANDLE_H
#define _VITAL_INFO_DATA_HANDLE_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "vital_info_data_struct.h"


#include "mul_sport_common.h"
#include "vital_info_platform.h"
//#include "daily_data_handle.h"
//#include "manual_measure_data_handle.h"
//#include "sleep_data_handle.h"
//#include "abn_record_data_handle.h"
#include "mul_sport_ops.h"


#define STORE_NODE_CAN_BE_ALLOCATED(flag) ((flag) != STORE_NODE_ALLOCATED_NOT_SAVE && (flag) != STORE_NODE_ALLOCATED_AND_SAVED)

typedef struct
{
    struct
    {
        miwear_file_type_t file_type;
        int file_index;
        int file_handle;
        int result;
    } file_info;

    struct
    {
        file_open_cb_t open_cb;
        file_read_cb_t read_cb;
        file_close_cb_t close_cb;
    } cbs;
} base_file_descriptor_t, *p_base_file_descriptor_t;

typedef struct
{    
    base_file_descriptor_t base;

    union
    {
        uint8_t   p_data_id[50];
        data_id_t data_id;
    } id_info;

    struct
    {
        uint8_t  *buf_ptr;
        size_t   need_len;
        uint32_t start_addr;
        size_t   cur_offset;
        size_t   total_len;
    } read_info;
} vital_info_file_descriptor_t, *p_vital_info_file_descriptor_t;

typedef struct
{    
    base_file_descriptor_t base;
} exception_file_descriptor_t, *p_exception_file_descriptor_t;

typedef struct
{
    int resend_handle;
    int resend_type;
} vital_info_file_resend_ctrl_t, *p_vital_info_file_resend_ctrl_t;

typedef mul_sport_utc_time_t vital_info_utc_time_t;

bool vital_info_data_init(void);

bool vital_info_data_deinit(void);

bool vital_info_data_save_process(void);

uint32_t vital_info_get_timestamp(void);

int8_t vital_info_get_time_zone(void);

bool vital_info_is_the_same_day(uint32_t dst_local_timestamp, uint32_t src_local_timestamp);

int32_t vital_info_get_time_zone_offset(int8_t time_zone);

vital_info_utc_time_t vital_info_get_clock_time(utc_time_t utc_time, int8_t time_zone);

void vital_info_min_hr_cb(uint8_t hr);

void vital_info_min_spo2_cb(uint8_t spo2);

void vital_info_min_hrv_cb(uint8_t hrv);

void vital_info_sec_handle_process(void);

void vital_info_min_handle_process(void);

void vital_info_print_fitness_id(const char *desc_str, data_id_t *p_id);

bool vital_info_get_data_header_ptr(data_id_t *p_id, uint8_t **pp_header_data, size_t *header_data_len);

bool vital_info_get_intraday_vaild_id(data_id_t *p_id, uint32_t *id_nums, const uint32_t max_id_nums);

bool vital_info_get_historical_vaild_id(data_id_t *p_id, uint32_t *id_nums, const uint32_t max_id_nums);

bool vital_info_get_data_len(data_id_t *p_id, size_t *header_data_len);

bool vital_info_get_data_start_addr(data_id_t *p_id, uint32_t *p_start_addr);

bool vital_info_get_data_item_info(data_id_t *p_id, uint32_t *p_start_addr, size_t *p_data_len);

bool vital_info_read_upload_data(data_id_t *p_id, uint32_t read_addr, uint8_t *buf_ptr, size_t read_len);

bool vital_info_delete_id(data_id_t *p_id);

p_vital_info_file_descriptor_t vital_info_get_file_descriptor(void);

p_vital_info_file_descriptor_t vital_info_get_log_file_descriptor(void);

p_vital_info_file_descriptor_t vital_info_get_gensor_file_descriptor(void);

p_vital_info_file_descriptor_t vital_info_get_statistics_file_descriptor(void);

p_vital_info_file_resend_ctrl_t vital_info_get_file_resend_ctrl(void);

void vital_info_init_file_resend_ctrl(void);

p_vital_info_file_resend_ctrl_t vital_info_get_log_file_resend_ctrl(void);

void vital_info_init_log_resend_ctrl(void);

p_vital_info_file_resend_ctrl_t vital_info_get_statistics_file_resend_ctrl(void);

void vital_info_init_statistics_resend_ctrl(void);

p_vital_info_file_resend_ctrl_t vital_info_get_sensor_file_resend_ctrl(void);

void vital_info_init_sensor_resend_ctrl(void);

void vital_info_init_all_resend_ctrl(void);

size_t vital_info_get_file_need_len(p_base_file_descriptor_t p_base_fd);

void vital_info_resend_ctrl_handler(void);

#endif /* _VITAL_INFO_DATA_HANDLE_H */
