#ifndef _MUL_SPORT_COMMON_H
#define _MUL_SPORT_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/** @def FLASH_MANAGER_SWITCH @note flash_manager开关 */
#define FLASH_MANAGER_SWITCH 1
#define BSP_USING_PC_SIMULATOR 1
/** @def GPS_DATA_MANAGER_SWITCH @note gps数据存储开关 */
#define GPS_DATA_MANAGER_SWITCH 1

/** @def MUL_SPORT_LOG_DBG_SWITCH @note log */
#define MUL_SPORT_LOG_DBG_SWITCH 0

/** @def MUL_SPORT_SPORT_CATEGORY_NUMS @note 运动类别的最大个数 */
#define MUL_SPORT_SPORT_CATEGORY_MAX_NUMS    (20)

#define MUL_SPORT_WEAK //__weak

#define MUL_SPORT_POSSIBLY_UNUSED //__attribute__((unused))   // possibly unused



/** @def MUL_SPORT_GPS_WILL_FULL_NUMS @note GPS数据即将存储满的条数  */
#define MUL_SPORT_GPS_WILL_FULL_NUMS   (15)

/** @def MUL_SPORT_GPS_WAS_FULL_NUMS @note  GPS数据已经存储满的条数 */
#define MUL_SPORT_GPS_WAS_FULL_NUMS    (20)

/** @def MUL_SPORT_POINT_WILL_FULL_NUMS @note 运动打点即将存储满的条数 */
#define MUL_SPORT_POINT_WILL_FULL_NUMS (15)

/** @def MUL_SPORT_POINT_WAS_FULL_NUMS @note 运动打点已经存储满的条数 */
#define MUL_SPORT_POINT_WAS_FULL_NUMS  (20)



#include <stdint.h>
#include <stdbool.h>
#include "mul_sport_data_struct.h"

typedef struct
{
    uint16_t year;       // 2000+
    uint8_t month;       // 0-11
    uint8_t day;         // 0-30
    uint8_t seconds;     // 0-59
    uint8_t minutes;     // 0-59
    uint8_t hour;        // 0-23
    int8_t offset;       // 时区
} mul_sport_utc_time_t;

typedef struct
{
    uint32_t seconds  :
        6;
    uint32_t minute  :
        6;
    uint32_t hours  :
        5;
    uint32_t day   :
        5;
    uint32_t month  :
        4;
    uint32_t year   :
        6;
} mul_sport_time_bit_field_type_t;

typedef union
{
    uint32_t data;
    mul_sport_time_bit_field_type_t time;
} mul_sport_time_union_t;

typedef uint32_t utc_time_t; /* used to store the second counts for RTC */

typedef enum
{
    MULTI_MOTION_SUCCESS = 0,
    MULTI_MOTION_WRITE_SUCCESS = 1,
    MULTI_MOTION_WRITE_FAILED = 2,
    MULTI_MOTION_READ_SUCCESS = 3,
    MULTI_MOTION_READ_FAILED = 4,
    MULTI_MOTION_SPACE_WAS_FULLED = 5,
    MULTI_MOTION_NOT_FOUND_SPORT_ID = 6,
    MULTI_MOTION_SPACE_WILL_FULLED = 7,
    MULTI_MOTION_SPACE_AMPLE = 8,  // 空间充足
    MULTI_MOTION_ERROR = 0xFF,
} multi_motion_ret;


#define MUL_SPORT_MAGIC_NUMBER      0xA5
#define MUL_SPORT_VER_1             0x01
#define MUL_SPORT_RELEASED_VERSION  "3.0.2"

#define __MS_GET_FUNC(func, ver)    func##ver
#define MS_GET_FUNC(func, ver)      __MS_GET_FUNC(func, ver)

#define _MS_T_CONVERT_DEF(type_a, type_b) [type_a] = type_b
#define _MS_T_CONVERT_DEF_REV(type_a, type_b) [type_b] = type_a

#define MS_T_CONVERT_DEF(type_a, type_b)      _MS_T_CONVERT_DEF(type_a, type_b)
#define MS_T_CONVERT_DEF_REV(type_a, type_b)  _MS_T_CONVERT_DEF_REV(type_a, type_b)

typedef bool (*ms_bool_ret_void_s_uint32_t_s) (void *, uint32_t *);

typedef bool (*ms_sport_set_data_func_t) (void *, void *);

typedef bool (*ms_gps_write_func_t) (void *, uint32_t *, ms_gps_item_t);

typedef struct {
    uint8_t   magic_number;
    uint8_t   version;
    uint8_t   sport_category;
    uint8_t   sport_category_ver;
    
    uint8_t   data_ver;
    uint8_t   repo_ver;

    bool     is_record_per_sec;

    uint16_t  sport_fixed_data_len;

    ms_bool_ret_void_s_uint32_t_s    pf_get_sport_data;
    ms_bool_ret_void_s_uint32_t_s    pf_get_sport_fixed_data;
    ms_bool_ret_void_s_uint32_t_s    pf_get_sport_repo;
    ms_sport_set_data_func_t         pf_set_sport_data;
    ms_sport_set_data_func_t         pf_set_sport_repo;
} ms_abstract_sport_handle_t, *p_ms_abstract_sport_handle_t;

typedef struct {
    uint8_t  magic_number;
    uint8_t  version;

    ms_gps_write_func_t            pf_get_gps_data;
} ms_abstract_gps_handle_t, *p_ms_abstract_gps_handle_t;


typedef struct {
    uint8_t  magic_number;
    uint8_t  version;

    uint8_t  sport_category;
    uint8_t  sport_category_ver;

    bool     is_gps_sport;

    uint8_t  gps_ver;

    uint16_t sport_type;
} ms_abstract_config_t, *p_ms_abstract_config_t;


typedef struct {
    uint8_t   magic_number;
    uint8_t   version;

    ms_abstract_config_t        *ms_config;
    ms_abstract_sport_handle_t  *ms_handle;
    void                        *reserved_args;
} ms_abstract_sport_list_t, *p_ms_abstract_sport_list_t;


//-=-=
//

typedef struct
{
    ms_abstract_sport_handle_t sport_handle;
} ms_common_sport_handle_v1_t, *p_ms_common_sport_handle_v1_t;

typedef struct
{
    ms_abstract_config_t sport_config;
} ms_common_sport_config_v1_t, *p_ms_common_sport_config_v1_t;

typedef struct {
    ms_abstract_gps_handle_t gps_handle;
} ms_common_gps_handle_v1_t, *p_ms_common_gps_handle_v1_t;

typedef struct
{
    ms_abstract_sport_list_t ms_sport_list;
} ms_common_sport_list_v1_t, *p_ms_common_sport_list_v1_t;

//-=-=
//

typedef struct {
    uint8_t   magic_number;
    uint8_t   version;
    uint32_t  cur_idx_pos;
} ms_idx_pos_t, *p_ms_idx_pos;

//-=-=
//

utc_time_t convert_time_to_sec(mul_sport_time_union_t time);

int32_t mul_sport_get_time_zone_offset(int8_t time_zone);

utc_time_t mul_sport_convert_time_to_sec(mul_sport_time_union_t time);

mul_sport_utc_time_t mul_sport_get_clock_time(utc_time_t utc_time, int8_t time_zone);

bool mul_sport_is_the_same_day(uint32_t dst_timestamp, uint32_t src_timestamp);

#ifdef __cplusplus
}
#endif


#endif /* _MUL_SPORT_COMMON_H */
