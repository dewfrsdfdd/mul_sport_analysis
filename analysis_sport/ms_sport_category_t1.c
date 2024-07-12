#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#include "ms_sport_category_t1.h"

#include <stdio.h>
#include <string.h>
#include "mul_sport_data_struct.h"
#include "mul_sport_platform.h"
#include "mul_sport_ver_def.h"
#include "multi_motion_sport_handle.h"

#define MS_SPORT_CATEGORY_T1_V1_FIXED_BYTES          12     // 户外运动固定的数据头的字节数

const uint8_t MUL_SPORT_ALIGN_WAY g_sport_point_header_t1_v1_buf[] = {0x00, 0xEC, 0xCC};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t1_v1_buf[] = {0x00, 0xFF, 0xF8, 0x03, 0xE0};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t1_v4_buf[] = {0x00, 0xFF, 0xF8, 0x03, 0xF0, 0xF8};

//-=-=
// V1
static bool MUL_SPORT_POSSIBLY_UNUSED get_outside_run_data_v1(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Outside_Run_Data_Type_V1 outside_run_data;

    memset(&outside_run_data, 0, sizeof(outside_run_data));

    outside_run_data.data_s.data_body.extra_calorie.ec_s.extra_calorie        =
                    mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();

    outside_run_data.data_s.data_body.extra_calorie.ec_s.extra_step           =
                    mul_sport_get_sport_step_num() - multi_motion_get_prev_step();

    outside_run_data.data_s.data_body.hr = mul_sport_get_sport_heart_rate();

    outside_run_data.data_s.data_body.extra_distance                          =
                    (mul_sport_get_sport_distance() - multi_motion_get_prev_distance()) * 10;

    if (get_is_up_km_status())
    {
        outside_run_data.data_s.data_body.heigth_change.hc_s.is_km = 1;
        set_is_up_km_status(false);
    }
    else
    {
        outside_run_data.data_s.data_body.heigth_change.hc_s.is_km = 0;
    }
    
    outside_run_data.data_s.data_body.heigth_change.hc_s.is_up                =
                    mul_sport_get_sport_altitude_change_type();
    outside_run_data.data_s.data_body.heigth_change.hc_s.height_change        =
                    mul_sport_get_sport_altitude_change_val();

    memcpy(p_output_data,
           (uint8_t *)&outside_run_data.data_s.data_body,
           sizeof(outside_run_data.data_s.data_body));

    *p_output_data_len = sizeof(outside_run_data.data_s.data_body);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_outside_run_fixed_data_v1(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Outside_Run_Data_Type_V1 outside_run_data;

    memset(&outside_run_data, 0, sizeof(outside_run_data));

    uint32_t mul_sport_cnt = get_mul_sport_cnt();

    outside_run_data.data_s.data_head.initialize_altitude = get_initialize_altitude();
    outside_run_data.data_s.data_head.restore_time        = get_recovery_motion_timestamp();
    outside_run_data.data_s.data_head.count_sport_hold              =
            get_mul_sport_total_points_cnts() > mul_sport_cnt ?
                    get_mul_sport_total_points_cnts() - mul_sport_cnt : 0;

    set_mul_sport_cnt(get_mul_sport_total_points_cnts());

    memcpy(p_output_data, \
           (uint8_t *)&outside_run_data.data_s.data_head, \
           sizeof(outside_run_data.data_s.data_head));

    *p_output_data_len = sizeof(outside_run_data.data_s.data_head);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_outside_run_repo_v1(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Outside_Run_Data_Type_V1 outside_run_repo_data;

    memset(&outside_run_repo_data, 0, sizeof(outside_run_repo_data));

    outside_run_repo_data.data_s.sport_start_time = get_mul_sport_start_time();

    outside_run_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();

    outside_run_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();

    outside_run_repo_data.data_s.sport_total_distance = mul_sport_get_sport_distance();
    outside_run_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();
    outside_run_repo_data.data_s.total_step = mul_sport_get_sport_step_num();

    outside_run_repo_data.data_s.high_speed = mul_sport_get_sport_maximum_speed_distribution();

    outside_run_repo_data.data_s.low_speed = mul_sport_get_sport_minimum_speed_distribution();
    outside_run_repo_data.data_s.fast_speed = mul_sport_get_sport_limit_speed();

    outside_run_repo_data.data_s.max_step_rate = mul_sport_get_sport_maximum_step_frequency();
    outside_run_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    outside_run_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();

    outside_run_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();

    outside_run_repo_data.data_s.total_up = mul_sport_get_total_up();
    outside_run_repo_data.data_s.total_down = mul_sport_get_total_down();
    outside_run_repo_data.data_s.avg_height = mul_sport_get_avg_height();
    outside_run_repo_data.data_s.max_height = mul_sport_get_max_height();
    outside_run_repo_data.data_s.min_height = mul_sport_get_min_height();
    outside_run_repo_data.data_s.training_effect = 0x00;
    outside_run_repo_data.data_s.max_oxygen_uptake = 0x00;
    outside_run_repo_data.data_s.body_power_use = 0x00;
    outside_run_repo_data.data_s.recover_time = 0x00;

    outside_run_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    outside_run_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    outside_run_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    outside_run_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    outside_run_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();

    memcpy(p_output_data, \
           (uint8_t *)&outside_run_repo_data.data_s, \
           sizeof(outside_run_repo_data.data_s));

    *p_output_data_len = sizeof(outside_run_repo_data.data_s);

    return true;
}

//-=-=
// V4
static bool MUL_SPORT_POSSIBLY_UNUSED get_outside_run_repo_v4(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Outside_Run_Data_Type_V4 outside_run_repo_data;

    memset(&outside_run_repo_data, 0, sizeof(outside_run_repo_data));

    outside_run_repo_data.data_s.sport_start_time = get_mul_sport_start_time();

    outside_run_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();

    outside_run_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();

    outside_run_repo_data.data_s.sport_total_distance = mul_sport_get_sport_distance();
    outside_run_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();
    outside_run_repo_data.data_s.total_step = mul_sport_get_sport_step_num();

    outside_run_repo_data.data_s.high_speed = mul_sport_get_sport_maximum_speed_distribution();

    outside_run_repo_data.data_s.low_speed = mul_sport_get_sport_minimum_speed_distribution();
    outside_run_repo_data.data_s.fast_speed = mul_sport_get_sport_limit_speed();

    outside_run_repo_data.data_s.max_step_rate = mul_sport_get_sport_maximum_step_frequency();
    outside_run_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    outside_run_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();

    outside_run_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();

    outside_run_repo_data.data_s.total_up = mul_sport_get_total_up();
    outside_run_repo_data.data_s.total_down = mul_sport_get_total_down();
    outside_run_repo_data.data_s.avg_height = mul_sport_get_avg_height();
    outside_run_repo_data.data_s.max_height = mul_sport_get_max_height();
    outside_run_repo_data.data_s.min_height = mul_sport_get_min_height();
    outside_run_repo_data.data_s.training_effect = 0x00;
    outside_run_repo_data.data_s.max_oxygen_uptake = 0x00;
    outside_run_repo_data.data_s.body_power_use = 0x00;
    outside_run_repo_data.data_s.recover_time = 0x00;

    outside_run_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    outside_run_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    outside_run_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    outside_run_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    outside_run_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();
    
    outside_run_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();
    outside_run_repo_data.data_s.valid_exercise_time = 0;
    outside_run_repo_data.data_s.anaerobic_training_effect = 0;
    outside_run_repo_data.data_s.designated_courses = 0;
    outside_run_repo_data.data_s.hr_zone_selection = 0;
    outside_run_repo_data.data_s.target_duration = mul_sport_get_target_duration();
    outside_run_repo_data.data_s.target_calorie = mul_sport_get_target_calorie();
    outside_run_repo_data.data_s.target_distance = mul_sport_get_target_distance();
    outside_run_repo_data.data_s.target_pace = mul_sport_get_target_pace();
    outside_run_repo_data.data_s.target_cadence = mul_sport_get_target_cadence();

    memcpy(p_output_data, \
           (uint8_t *)&outside_run_repo_data.data_s, \
           sizeof(outside_run_repo_data.data_s));

    *p_output_data_len = sizeof(outside_run_repo_data.data_s);

    return true;
}

//-=-=
//

const static ms_common_sport_handle_v1_t MUL_SPORT_POSSIBLY_UNUSED g_ms_sport_category_t1_v1_handle = {
    .sport_handle.magic_number            = MUL_SPORT_MAGIC_NUMBER,
    .sport_handle.version                 = MUL_SPORT_VER_1,
    
    .sport_handle.sport_category          = MS_SPORT_CATEGORY_T1,
    .sport_handle.sport_category_ver      = MS_SPORT_CATEGORY_T1_V1,
    
    .sport_handle.data_ver                = MS_SPORT_CATEGORY_T1_V1_DATA_VER,
    .sport_handle.repo_ver                = MS_SPORT_CATEGORY_T1_V1_REPO_VER,

    .sport_handle.is_record_per_sec       = true,

    .sport_handle.sport_fixed_data_len    = MS_SPORT_CATEGORY_T1_V1_FIXED_BYTES,

    .sport_handle.pf_get_sport_data       = MS_GET_FUNC(get_outside_run_data_v, MS_SPORT_CATEGORY_T1_V1_DATA_VER),
    .sport_handle.pf_get_sport_fixed_data = MS_GET_FUNC(get_outside_run_fixed_data_v, MS_SPORT_CATEGORY_T1_V1_DATA_VER),
    .sport_handle.pf_get_sport_repo       = MS_GET_FUNC(get_outside_run_repo_v, MS_SPORT_CATEGORY_T1_V1_REPO_VER),
    .sport_handle.pf_set_sport_data       = NULL,
    .sport_handle.pf_set_sport_repo       = NULL,
};

//-=-=
//

p_ms_abstract_sport_handle_t MUL_SPORT_POSSIBLY_UNUSED get_ms_sport_category_t1_v1(void)
{
    return (p_ms_abstract_sport_handle_t)&g_ms_sport_category_t1_v1_handle;
}

//-=-=
// get header func
static void get_ms_sport_category_t1_point_header(uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (version)
    {
        case 0x01:
            *pp_header_data = (uint8_t *)g_sport_point_header_t1_v1_buf;
            *p_data_len = sizeof(g_sport_point_header_t1_v1_buf);
            break;

        default:
            break;
    }
}

static void get_ms_sport_category_t1_report_header(uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (version)
    {
        case 0x01:
            *pp_header_data = (uint8_t *)g_sport_report_header_t1_v1_buf;
            *p_data_len = sizeof(g_sport_report_header_t1_v1_buf);
            break;

        case 0x04:
            *pp_header_data = (uint8_t *)g_sport_report_header_t1_v4_buf;
            *p_data_len = sizeof(g_sport_report_header_t1_v4_buf);
            break;

        default:
            break;
    }
}

void get_ms_sport_category_t1_data_header(uint8_t data_type, uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (data_type)
    {
        case ENUM_POINT_DATA_T:
            get_ms_sport_category_t1_point_header(version, pp_header_data, p_data_len);
            break;

        case ENUM_REPORT_DATA_T:
            get_ms_sport_category_t1_report_header(version, pp_header_data, p_data_len);
            break;

        default:
            break;
    }
}
//-=-=
//

const ms_common_sport_config_v1_t MUL_SPORT_POSSIBLY_UNUSED g_outside_run_config = {
    .sport_config.magic_number         = MUL_SPORT_MAGIC_NUMBER,
    .sport_config.version              = MUL_SPORT_VER_1,

    .sport_config.sport_category       = MS_SPORT_CATEGORY_T1,
    .sport_config.sport_category_ver   = MS_SPORT_CATEGORY_T1_V1,

    .sport_config.is_gps_sport         = true,
        
    .sport_config.gps_ver              = MS_SPORT_CATEGORY_T1_V1_GPS_VER,

    .sport_config.sport_type           = ST_OUTSIDE_RUN,
};

const ms_common_sport_config_v1_t MUL_SPORT_POSSIBLY_UNUSED g_outside_move_config = {
    .sport_config.magic_number         = MUL_SPORT_MAGIC_NUMBER,
    .sport_config.version              = MUL_SPORT_VER_1,

    .sport_config.sport_category       = MS_SPORT_CATEGORY_T1,
    .sport_config.sport_category_ver   = MS_SPORT_CATEGORY_T1_V1,

    .sport_config.is_gps_sport         = true,

    .sport_config.gps_ver              = MS_SPORT_CATEGORY_T1_V1_GPS_VER,

    .sport_config.sport_type           = ST_OUTSIDE_MOVE,
};

const ms_common_sport_config_v1_t MUL_SPORT_POSSIBLY_UNUSED g_outside_climb_config = {
    .sport_config.magic_number         = MUL_SPORT_MAGIC_NUMBER,
    .sport_config.version              = MUL_SPORT_VER_1,

    .sport_config.sport_category       = MS_SPORT_CATEGORY_T1,
    .sport_config.sport_category_ver   = MS_SPORT_CATEGORY_T1_V1,

    .sport_config.is_gps_sport         = true,

    .sport_config.gps_ver              = MS_SPORT_CATEGORY_T1_V1_GPS_VER,

    .sport_config.sport_type           = ST_CLIMB,
};

const ms_common_sport_config_v1_t MUL_SPORT_POSSIBLY_UNUSED g_outside_cross_country_config = {
    .sport_config.magic_number         = MUL_SPORT_MAGIC_NUMBER,
    .sport_config.version              = MUL_SPORT_VER_1,

    .sport_config.sport_category       = MS_SPORT_CATEGORY_T1,
    .sport_config.sport_category_ver   = MS_SPORT_CATEGORY_T1_V1,

    .sport_config.is_gps_sport         = true,

    .sport_config.gps_ver              = MS_SPORT_CATEGORY_T1_V1_GPS_VER,

    .sport_config.sport_type           = ST_CROSS_COUNTRY,
};

const ms_common_sport_config_v1_t MUL_SPORT_POSSIBLY_UNUSED g_outside_hiking_config = {
    .sport_config.magic_number         = MUL_SPORT_MAGIC_NUMBER,
    .sport_config.version              = MUL_SPORT_VER_1,

    .sport_config.sport_category       = MS_SPORT_CATEGORY_T1,
    .sport_config.sport_category_ver   = MS_SPORT_CATEGORY_T1_V1,

    .sport_config.is_gps_sport         = true,

    .sport_config.gps_ver              = MS_SPORT_CATEGORY_T1_V1_GPS_VER,

    .sport_config.sport_type           = ST_OUTSIDE_HIKING,
};

#endif /* FLASH_MANAGER_SWITCH */
