#ifndef _VITAL_INFO_PLATFORM_H
#define _VITAL_INFO_PLATFORM_H

#include <stdint.h>
#include <stdio.h>

/* porting start */
//#include "rtconfig.h"
#if XIAOMI_SDK_PROTOBUF_ZH
#include "miwear_api.h"
#else
typedef enum {
    FILE_TYPE_SENSOR,
    FILE_TYPE_FITNESS,
    FILE_TYPE_LOG,
    FILE_TYPE_STATISTICS,
    FILE_TYPE_MAX_NUM
} miwear_file_type_t;

typedef void (*file_open_cb_t)(int index, int handle);
typedef void (*file_read_cb_t)(int handle, int result);
typedef void (*file_close_cb_t)(int result);
#endif
/*
* #include "wall_clock_timer.h"
#include "zh_middle_data_manager.h"
#include "zh_flash_memory.h"
#include "zh_flash_map.h"
#include "rtthread.h"
#include "ble_service.h"
#include "zh_log_recode_process.h"
#include "app_heart_rate_data_struct_common.h"
#include "zh_app_heart_rate_data.h"
#include "zh_app_spo2_data.h"
#include "zh_app_hrv_data.h"
*/

// #include "pb_main.h"

// TODO: wdh,
// extern Phone_Device_Type_t get_phone_device_type(void);
// extern uint32_t get_today_step_number(void);
// extern int get_today_calorie_number(void);
// extern int get_today_mileage_number(void);
// uint16_t get_today_activity_duration_number(void);
// uint8_t get_today_his_eff_sta(uint8_t * data);
/* porting end */

/** @def VITAL_INFO_ALIGN_WAY @note vital info 全局变量对齐方式 */
#define VITAL_INFO_ALIGN_WAY            ALIGN(4)

/** @def VITAL_INFO_LOG_DBG_SWITCH @note log */
#define VITAL_INFO_LOG_DBG_SWITCH       0

/** @def VITAL_INFO_PC_SIMULATOR @note 是否使用PC模拟器 */
#if defined(BSP_USING_PC_SIMULATOR)
#define VITAL_INFO_PC_SIMULATOR         1
#else
#define VITAL_INFO_PC_SIMULATOR         0
#endif

/** @def VITAL_INFO_ALIGN_WAY @note 是否使用可变数组 */
#define VITAL_INFO_VAL_SWITCH           (VITAL_INFO_PC_SIMULATOR == 0)

/** @def VITAL_INFO_MALLOC_SWITCH @note 是否使用动态分配 */
#define VITAL_INFO_MALLOC_SWITCH        1

#define VITAL_INFO_SECTOR_SIZE          4096

#if VITAL_INFO_LOG_DBG_SWITCH
#define vital_info_dbg_log(fmt, ...)    printf("\r\n[vital info] "fmt, ##__VA_ARGS__)
#else
#define vital_info_dbg_log(fmt, ...)
#endif

#define vital_malloc    malloc
#define vital_free      free

typedef uint32_t flash_api_file;

int32_t  vital_info_flash_read(flash_api_file p_file, uint32_t addr, uint8_t *p_data, uint32_t len);

int32_t vital_info_flash_write(flash_api_file p_file, uint32_t addr, uint8_t *p_data, uint32_t len);

int32_t vital_info_flash_erase(flash_api_file p_file, uint32_t addr, uint32_t len);

uint32_t vital_info_get_steps_day(void);

uint32_t vital_info_get_calories_day(void);

uint32_t vital_info_get_distance_day(void);

uint8_t vital_info_get_low_genki_day(void);
uint8_t vital_info_get_medium_genki_day(void);
uint8_t vital_info_get_high_genki_day(void);
uint16_t vital_info_get_total_genki_7_day(void);
uint8_t vital_info_get_next_genki_suggest_type(void);
uint8_t vital_info_get_next_genki_suggest_dur(void);

void vital_info_set_cur_hr(uint8_t hr);

void vital_info_set_cur_spo2(uint8_t spo2);

void vital_info_set_cur_hrv(uint8_t hrv);

void vital_info_set_abn_hr(uint8_t hr);

uint8_t vital_info_get_calm_hr(void);

void vital_info_set_exist_calm_hr(void);

uint8_t vital_info_get_power_level(void);

uint8_t vital_info_get_s_type(void);

void vital_info_get_valid_stand(uint8_t *p_valid_data);

void vital_info_platform_min_hr_cb(uint8_t hr);

void vital_info_platform_min_spo2_cb(uint8_t spo2);

void vital_info_platform_min_hrv_cb(uint8_t hrv);

void vital_info_platform_malloc_failed(const char *func_name, uint32_t line);

#define VITAL_INFO_PLATFORM_MALLOC_FAILED() vital_info_platform_malloc_failed(__func__, __LINE__)

#endif /* _VITAL_INFO_PLATFORM_H */
