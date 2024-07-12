#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#include "ms_sport_category_t2.h"

#include <stdio.h>
#include <string.h>
#include "mul_sport_data_struct.h"
#include "mul_sport_platform.h"
#include "mul_sport_ver_def.h"
#include "multi_motion_sport_handle.h"

#define MS_SPORT_CATEGORY_T2_V1_FIXED_BYTES           13      // 室内跑步固定的数据头的字节数

const uint8_t MUL_SPORT_ALIGN_WAY g_sport_point_header_t2_v1_buf[] = {0x00, 0xEC, 0xC0};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t2_v1_buf[] = {0x00, 0xFF, 0xF0, 0xF8};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_point_header_t2_v6_buf[] = {0x00, 0xEC, 0xCC,0x00,0xCC};
//const uint8_t MUL_SPORT_ALIGN_WAY g_sport_point_header_t2_v6_buf[] = { 0x00,0xff,0xff,0x8b,0xff };
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t2_v5_buf[] = {0x00, 0xFF, 0xF0, 0xFC, 0x3F};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t2_v9_buf[] = {0x00, 0xFF, 0xF0, 0x3F, 0x13,0xF8,0x20};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t2_v10_buf[] = {0x00, 0xFF,0xFE,0x07,0xE2,0x71,0x04,0x00,0x00};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t2_v11_buf[] = {0x00,0xff,0xff,0xff,0xff,0xff,0xf8,0x40,0x00,0x7f };
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t2_v12_buf[] = {0x00, 0xFF, 0xFE, 0x07, 0xC0,0x0C,0x27,0xF0,0x04,0x00,0x00,0x00};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_point_header_t2_v3_buf[] = {0x00, 0xEC, 0xCC};
//-=-=
// V1
static bool MUL_SPORT_POSSIBLY_UNUSED get_indoor_run_data_v1(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Indoor_Run_Data_Type_V1 indoor_run_data;

    memset(&indoor_run_data, 0, sizeof(indoor_run_data));

    indoor_run_data.data_s.data_body.extra_calorie.ec_s.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();

    indoor_run_data.data_s.data_body.extra_calorie.ec_s.extra_step = mul_sport_get_sport_step_num() - multi_motion_get_prev_step();

    indoor_run_data.data_s.data_body.hr = mul_sport_get_sport_heart_rate();

    indoor_run_data.data_s.data_body.extra_distance = (mul_sport_get_sport_distance() - multi_motion_get_prev_distance()) * 10;

    memcpy(p_output_data, \
           (uint8_t *)&indoor_run_data.data_s.data_body, \
           sizeof(indoor_run_data.data_s.data_body));

    *p_output_data_len = sizeof(indoor_run_data.data_s.data_body);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_indoor_run_fixed_data_v1(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Indoor_Run_Data_Type_V1 indoor_run_data;

    memset(&indoor_run_data, 0, sizeof(indoor_run_data));

    uint32_t mul_sport_cnt = get_mul_sport_cnt();

    indoor_run_data.data_s.data_head.restore_time = get_recovery_motion_timestamp();
    indoor_run_data.data_s.data_head.count_sport_hold           =
            get_mul_sport_total_points_cnts() > mul_sport_cnt ?
                    get_mul_sport_total_points_cnts() - mul_sport_cnt : 0;

    set_mul_sport_cnt(get_mul_sport_total_points_cnts());

    memcpy(p_output_data, \
           (uint8_t *)&indoor_run_data.data_s.data_head, \
           sizeof(indoor_run_data.data_s.data_head));

    *p_output_data_len = sizeof(indoor_run_data.data_s.data_head);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_indoor_run_repo_v1(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Indoor_Run_Data_Type_V1 indoor_run_repo_data;

    memset(&indoor_run_repo_data, 0, sizeof(indoor_run_repo_data));

    indoor_run_repo_data.data_s.sport_start_time = get_mul_sport_start_time();

    indoor_run_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();

    indoor_run_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();

    indoor_run_repo_data.data_s.sport_total_distance = mul_sport_get_sport_distance();
    indoor_run_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();
    indoor_run_repo_data.data_s.total_step = mul_sport_get_sport_step_num();

    indoor_run_repo_data.data_s.high_speed = mul_sport_get_sport_maximum_speed_distribution();

    indoor_run_repo_data.data_s.low_speed = mul_sport_get_sport_minimum_speed_distribution();

    indoor_run_repo_data.data_s.max_step_rate = mul_sport_get_sport_maximum_step_frequency();

    indoor_run_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    indoor_run_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();

    indoor_run_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();

    indoor_run_repo_data.data_s.training_effect = 0x00;
    indoor_run_repo_data.data_s.max_oxygen_uptake = 0x00;
    indoor_run_repo_data.data_s.body_power_use = 0x00;
    indoor_run_repo_data.data_s.recover_time = 0x00;

    indoor_run_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    indoor_run_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    indoor_run_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    indoor_run_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    indoor_run_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();

    memcpy(p_output_data, \
           (uint8_t *)&indoor_run_repo_data.data_s, \
           sizeof(indoor_run_repo_data.data_s));

    *p_output_data_len = sizeof(indoor_run_repo_data.data_s);

    return true;
}

//-=-=
// V3
static bool MUL_SPORT_POSSIBLY_UNUSED get_indoor_run_data_v3(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Indoor_Run_Data_Type_V3 indoor_run_data;

    memset(&indoor_run_data, 0, sizeof(indoor_run_data));

    indoor_run_data.data_s.data_body.extra_calorie.ec_s.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();

    indoor_run_data.data_s.data_body.extra_calorie.ec_s.extra_step = mul_sport_get_sport_step_num() - multi_motion_get_prev_step();

    indoor_run_data.data_s.data_body.hr = mul_sport_get_sport_heart_rate();

    indoor_run_data.data_s.data_body.extra_distance = (mul_sport_get_sport_distance() - multi_motion_get_prev_distance()) * 10;
    indoor_run_data.data_s.data_body.extra_stride = mul_sport_get_sport_extra_stride();

    memcpy(p_output_data, \
           (uint8_t *)&indoor_run_data.data_s.data_body, \
           sizeof(indoor_run_data.data_s.data_body));

    *p_output_data_len = sizeof(indoor_run_data.data_s.data_body);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_indoor_run_fixed_data_v3(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Indoor_Run_Data_Type_V3 indoor_run_data;

    memset(&indoor_run_data, 0, sizeof(indoor_run_data));

    uint32_t mul_sport_cnt = get_mul_sport_cnt();

    indoor_run_data.data_s.data_head.restore_time = get_recovery_motion_timestamp();
    indoor_run_data.data_s.data_head.count_sport_hold           =
            get_mul_sport_total_points_cnts() > mul_sport_cnt ?
                    get_mul_sport_total_points_cnts() - mul_sport_cnt : 0;

    set_mul_sport_cnt(get_mul_sport_total_points_cnts());
    

    if (get_is_change_sit_type() == true && get_sport_sit_type() != SIT_NONE)
    {
        indoor_run_data.data_s.data_head.segment_type.st_s.segment_type = 1;
        indoor_run_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();

        set_sport_sit_type(get_sport_next_sit_type());
    }
    else
    {
        indoor_run_data.data_s.data_head.segment_type.st_s.segment_type = 0;
        indoor_run_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();
    }

    set_is_change_sit_type(false);


    memcpy(p_output_data, \
           (uint8_t *)&indoor_run_data.data_s.data_head, \
           sizeof(indoor_run_data.data_s.data_head));

    *p_output_data_len = sizeof(indoor_run_data.data_s.data_head);

    return true;
}

//-=-=
// V5
static bool MUL_SPORT_POSSIBLY_UNUSED get_indoor_run_repo_v5(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Indoor_Run_Data_Type_V5 indoor_run_repo_data;

    memset(&indoor_run_repo_data, 0, sizeof(indoor_run_repo_data));

    indoor_run_repo_data.data_s.sport_start_time = get_mul_sport_start_time();

    indoor_run_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();

    indoor_run_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();

    indoor_run_repo_data.data_s.sport_total_distance = mul_sport_get_sport_distance();
    indoor_run_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();
    indoor_run_repo_data.data_s.total_step = mul_sport_get_sport_step_num();

    indoor_run_repo_data.data_s.high_speed = mul_sport_get_sport_maximum_speed_distribution();

    indoor_run_repo_data.data_s.low_speed = mul_sport_get_sport_minimum_speed_distribution();

    indoor_run_repo_data.data_s.max_step_rate = mul_sport_get_sport_maximum_step_frequency();

    indoor_run_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    indoor_run_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();

    indoor_run_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();

    indoor_run_repo_data.data_s.training_effect = 0x00;
    indoor_run_repo_data.data_s.max_oxygen_uptake = 0x00;
    indoor_run_repo_data.data_s.body_power_use = 0x00;
    indoor_run_repo_data.data_s.recover_time = 0x00;

    indoor_run_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    indoor_run_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    indoor_run_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    indoor_run_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    indoor_run_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();

    indoor_run_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();
    indoor_run_repo_data.data_s.valid_exercise_time = mul_sport_get_sport_time_count();
    indoor_run_repo_data.data_s.designated_courses = 0;
//    indoor_run_repo_data.data_s.courses_id = 0;
    indoor_run_repo_data.data_s.hr_zone_selection = 0;
    indoor_run_repo_data.data_s.target_duration = mul_sport_get_target_duration();
    indoor_run_repo_data.data_s.target_calorie = mul_sport_get_target_calorie();
    indoor_run_repo_data.data_s.target_distance = mul_sport_get_target_distance();
    indoor_run_repo_data.data_s.target_pace = mul_sport_get_target_pace();
    indoor_run_repo_data.data_s.target_cadence = mul_sport_get_target_cadence();
    indoor_run_repo_data.data_s.fixed_distance = mul_sport_get_sport_fixed_distance();

    memcpy(p_output_data, \
           (uint8_t *)&indoor_run_repo_data.data_s, \
           sizeof(indoor_run_repo_data.data_s));

    *p_output_data_len = sizeof(indoor_run_repo_data.data_s);

    return true;
}

//-=-=
// V6
static bool MUL_SPORT_POSSIBLY_UNUSED get_indoor_run_data_v6(void *p_output_data, uint32_t *p_output_data_len)
{
    printf("%s\n",__func__);
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Indoor_Run_Data_Type_V6 indoor_run_data;

    memset(&indoor_run_data, 0, sizeof(indoor_run_data));

    indoor_run_data.data_s.data_body.extra_calorie.ec_s.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();

    indoor_run_data.data_s.data_body.extra_calorie.ec_s.extra_step = mul_sport_get_sport_step_num() - multi_motion_get_prev_step();

    indoor_run_data.data_s.data_body.hr = mul_sport_get_sport_heart_rate();

    indoor_run_data.data_s.data_body.extra_distance = (mul_sport_get_sport_distance() - multi_motion_get_prev_distance()) * 10;
    indoor_run_data.data_s.data_body.extra_stride = mul_sport_get_sport_extra_stride();
    indoor_run_data.data_s.data_body.cadence = mul_sport_get_sport_step_frequency();
    indoor_run_data.data_s.data_body.pace = mul_sport_get_sport_speed_distribution();
    memcpy(p_output_data, \
           (uint8_t *)&indoor_run_data.data_s.data_body, \
           sizeof(indoor_run_data.data_s.data_body));

    *p_output_data_len = sizeof(indoor_run_data.data_s.data_body);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_indoor_run_fixed_data_v6(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Indoor_Run_Data_Type_V6 indoor_run_data;

    memset(&indoor_run_data, 0, sizeof(indoor_run_data));

    uint32_t mul_sport_cnt = get_mul_sport_cnt();

    indoor_run_data.data_s.data_head.restore_time = get_recovery_motion_timestamp();
    indoor_run_data.data_s.data_head.count_sport_hold           =
            get_mul_sport_total_points_cnts() > mul_sport_cnt ?
                    get_mul_sport_total_points_cnts() - mul_sport_cnt : 0;

    set_mul_sport_cnt(get_mul_sport_total_points_cnts());
    indoor_run_data.data_s.data_head.segment_distance = 0;//本段总里程为0，APP会用每秒新增里程打点累加计算


    if (get_is_change_sit_type() == true && get_sport_sit_type() != SIT_NONE)
    {
        indoor_run_data.data_s.data_head.segment_type.st_s.segment_type = 1;
        indoor_run_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();

        set_sport_sit_type(get_sport_next_sit_type());
    }
    else
    {
        indoor_run_data.data_s.data_head.segment_type.st_s.segment_type = 0;
        indoor_run_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();
    }

    set_is_change_sit_type(false);


    memcpy(p_output_data, \
           (uint8_t *)&indoor_run_data.data_s.data_head, \
           sizeof(indoor_run_data.data_s.data_head));

    *p_output_data_len = sizeof(indoor_run_data.data_s.data_head);

    return true;
}

// V9
static bool MUL_SPORT_POSSIBLY_UNUSED get_indoor_run_repo_v9(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Indoor_Run_Data_Type_V9 indoor_run_repo_data;

    memset(&indoor_run_repo_data, 0, sizeof(indoor_run_repo_data));
    indoor_run_repo_data.data_s.sport_start_time = get_mul_sport_start_time();
    indoor_run_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();
    indoor_run_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();
    indoor_run_repo_data.data_s.sport_total_distance = mul_sport_get_sport_distance();
    indoor_run_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();
    indoor_run_repo_data.data_s.high_speed = mul_sport_get_sport_maximum_speed_distribution();
    indoor_run_repo_data.data_s.low_speed = mul_sport_get_sport_minimum_speed_distribution();
    indoor_run_repo_data.data_s.total_step = mul_sport_get_sport_step_num();

    indoor_run_repo_data.data_s.max_step_rate = mul_sport_get_sport_maximum_step_frequency();
    indoor_run_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    indoor_run_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();
    indoor_run_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();
    indoor_run_repo_data.data_s.training_effect = 0x00;
    indoor_run_repo_data.data_s.aerobic_training_effect = 0x00;
    indoor_run_repo_data.data_s.max_oxygen_uptake = 0x00;
    indoor_run_repo_data.data_s.max_oxygen_uptake_rate = 0x00;

    indoor_run_repo_data.data_s.body_power_use = 0x00;
    indoor_run_repo_data.data_s.recover_time = 0x00; 
    indoor_run_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    indoor_run_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    indoor_run_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    indoor_run_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    indoor_run_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();
    indoor_run_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();

    indoor_run_repo_data.data_s.valid_exercise_time = mul_sport_get_sport_time_count();
    indoor_run_repo_data.data_s.anaerobic_training_effect = 0x00;
    indoor_run_repo_data.data_s.anaerobic_training_effect_rate = 0x00;
    indoor_run_repo_data.data_s.subtype = get_sub_sport_type();
    indoor_run_repo_data.data_s.designated_courses = 0x00;
    indoor_run_repo_data.data_s.hr_zone_selection = 0;
    indoor_run_repo_data.data_s.target_duration = mul_sport_get_target_duration();
    indoor_run_repo_data.data_s.target_calorie = mul_sport_get_target_calorie();

    indoor_run_repo_data.data_s.target_distance = mul_sport_get_target_distance();
    indoor_run_repo_data.data_s.target_pace = mul_sport_get_target_pace();
    indoor_run_repo_data.data_s.target_speed = 0x00;
    indoor_run_repo_data.data_s.target_cadence = 0x00;
    indoor_run_repo_data.data_s.fixed_distance = mul_sport_get_sport_fixed_distance();
    indoor_run_repo_data.data_s.training_load = 0x00;
    indoor_run_repo_data.data_s.training_load_rate = 0x00;
    indoor_run_repo_data.data_s.running_power_index = 0x00;

    indoor_run_repo_data.data_s.running_power_level = 0x00;
    indoor_run_repo_data.data_s.training_state = 0x00;
    indoor_run_repo_data.data_s.genki_value = mul_sport_get_sport_genki_value();
    indoor_run_repo_data.data_s.full_palm_landing_time = 0x00;
    indoor_run_repo_data.data_s.forehand_landing_time = 0x00;
    indoor_run_repo_data.data_s.hell_landing_time = 0x00;
    indoor_run_repo_data.data_s.inversion_amplitude = 0x00;



//    indoor_run_repo_data.data_s.courses_id = 0;


    memcpy(p_output_data, \
           (uint8_t *)&indoor_run_repo_data.data_s, \
           sizeof(indoor_run_repo_data.data_s));

    *p_output_data_len = sizeof(indoor_run_repo_data.data_s);

    return true;
}
// V9
static bool MUL_SPORT_POSSIBLY_UNUSED get_indoor_run_repo_v11(void* p_output_data, uint32_t* p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Indoor_Run_Data_Type_V9 indoor_run_repo_data;

    memset(&indoor_run_repo_data, 0, sizeof(indoor_run_repo_data));
    indoor_run_repo_data.data_s.sport_start_time = get_mul_sport_start_time();
    indoor_run_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();
    indoor_run_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();
    indoor_run_repo_data.data_s.sport_total_distance = mul_sport_get_sport_distance();
    indoor_run_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();
    indoor_run_repo_data.data_s.high_speed = mul_sport_get_sport_maximum_speed_distribution();
    indoor_run_repo_data.data_s.low_speed = mul_sport_get_sport_minimum_speed_distribution();
    indoor_run_repo_data.data_s.total_step = mul_sport_get_sport_step_num();

    indoor_run_repo_data.data_s.max_step_rate = mul_sport_get_sport_maximum_step_frequency();
    indoor_run_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    indoor_run_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();
    indoor_run_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();
    indoor_run_repo_data.data_s.training_effect = 0x00;
    indoor_run_repo_data.data_s.aerobic_training_effect = 0x00;
    indoor_run_repo_data.data_s.max_oxygen_uptake = 0x00;
    indoor_run_repo_data.data_s.max_oxygen_uptake_rate = 0x00;

    indoor_run_repo_data.data_s.body_power_use = 0x00;
    indoor_run_repo_data.data_s.recover_time = 0x00;
    indoor_run_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    indoor_run_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    indoor_run_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    indoor_run_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    indoor_run_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();
    indoor_run_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();

    indoor_run_repo_data.data_s.valid_exercise_time = mul_sport_get_sport_time_count();
    indoor_run_repo_data.data_s.anaerobic_training_effect = 0x00;
    indoor_run_repo_data.data_s.anaerobic_training_effect_rate = 0x00;
    indoor_run_repo_data.data_s.subtype = get_sub_sport_type();
    indoor_run_repo_data.data_s.designated_courses = 0x00;
    indoor_run_repo_data.data_s.hr_zone_selection = 0;
    indoor_run_repo_data.data_s.target_duration = mul_sport_get_target_duration();
    indoor_run_repo_data.data_s.target_calorie = mul_sport_get_target_calorie();

    indoor_run_repo_data.data_s.target_distance = mul_sport_get_target_distance();
    indoor_run_repo_data.data_s.target_pace = mul_sport_get_target_pace();
    indoor_run_repo_data.data_s.target_speed = 0x00;
    indoor_run_repo_data.data_s.target_cadence = 0x00;
    indoor_run_repo_data.data_s.fixed_distance = mul_sport_get_sport_fixed_distance();
    indoor_run_repo_data.data_s.training_load = 0x00;
    indoor_run_repo_data.data_s.training_load_rate = 0x00;
    indoor_run_repo_data.data_s.running_power_index = 0x00;

    indoor_run_repo_data.data_s.running_power_level = 0x00;
    indoor_run_repo_data.data_s.training_state = 0x00;
    indoor_run_repo_data.data_s.genki_value = mul_sport_get_sport_genki_value();
    indoor_run_repo_data.data_s.full_palm_landing_time = 0x00;
    indoor_run_repo_data.data_s.forehand_landing_time = 0x00;
    indoor_run_repo_data.data_s.hell_landing_time = 0x00;
    indoor_run_repo_data.data_s.inversion_amplitude = 0x00;



    //    indoor_run_repo_data.data_s.courses_id = 0;


    memcpy(p_output_data, \
        (uint8_t*)&indoor_run_repo_data.data_s, \
        sizeof(indoor_run_repo_data.data_s));

    *p_output_data_len = sizeof(indoor_run_repo_data.data_s);

    return true;
}

// V9
static bool MUL_SPORT_POSSIBLY_UNUSED get_indoor_run_repo_v10(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Indoor_Run_Data_Type_V10 indoor_run_repo_data;

    memset(&indoor_run_repo_data, 0, sizeof(indoor_run_repo_data));
    indoor_run_repo_data.data_s.sport_start_time = get_mul_sport_start_time();
    indoor_run_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();
    indoor_run_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();
    indoor_run_repo_data.data_s.sport_total_distance = mul_sport_get_sport_distance();
    indoor_run_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();
    indoor_run_repo_data.data_s.avg_pace = mul_sport_get_sport_avg_speed_distribution();
    indoor_run_repo_data.data_s.fast_pace = mul_sport_get_sport_maximum_speed_distribution();
    indoor_run_repo_data.data_s.low_pace = mul_sport_get_sport_minimum_speed_distribution();
    indoor_run_repo_data.data_s.total_step = mul_sport_get_sport_step_num();
    indoor_run_repo_data.data_s.avg_stride = mul_sport_get_sport_avg_stride();
    indoor_run_repo_data.data_s.avg_cadence = mul_sport_get_sport_avg_step_frequency();
    indoor_run_repo_data.data_s.max_step_rate = mul_sport_get_sport_maximum_step_frequency();
    indoor_run_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    indoor_run_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();
    indoor_run_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();
    indoor_run_repo_data.data_s.training_effect = 0x00;
    indoor_run_repo_data.data_s.aerobic_training_effect = 0x00;
    indoor_run_repo_data.data_s.max_oxygen_uptake = 0x00;
    indoor_run_repo_data.data_s.max_oxygen_uptake_rate = 0x00;

    indoor_run_repo_data.data_s.body_power_use = 0x00;
    indoor_run_repo_data.data_s.recover_time = 0x00;
    indoor_run_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    indoor_run_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    indoor_run_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    indoor_run_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    indoor_run_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();
    indoor_run_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();

    indoor_run_repo_data.data_s.valid_exercise_time = mul_sport_get_sport_time_count();
    indoor_run_repo_data.data_s.anaerobic_training_effect = 0x00;
    indoor_run_repo_data.data_s.anaerobic_training_effect_rate = 0x00;
    indoor_run_repo_data.data_s.subtype = get_sub_sport_type();
    indoor_run_repo_data.data_s.designated_courses = 0x00;
    indoor_run_repo_data.data_s.hr_zone_selection = 0;
    indoor_run_repo_data.data_s.target_duration = mul_sport_get_target_duration();
    indoor_run_repo_data.data_s.target_calorie = mul_sport_get_target_calorie();

    indoor_run_repo_data.data_s.target_distance = mul_sport_get_target_distance();
    indoor_run_repo_data.data_s.target_pace = mul_sport_get_target_pace();
    indoor_run_repo_data.data_s.target_speed = 0x00;
    indoor_run_repo_data.data_s.target_cadence = 0x00;
    indoor_run_repo_data.data_s.fixed_distance = mul_sport_get_sport_fixed_distance();
    indoor_run_repo_data.data_s.training_load = 0x00;
    indoor_run_repo_data.data_s.training_load_rate = 0x00;
    indoor_run_repo_data.data_s.running_power_index = 0x00;

    indoor_run_repo_data.data_s.running_power_level = 0x00;
    indoor_run_repo_data.data_s.training_state = 0x00;
    indoor_run_repo_data.data_s.genki_value = mul_sport_get_sport_genki_value();
    indoor_run_repo_data.data_s.full_palm_landing_time = 0x00;
    indoor_run_repo_data.data_s.forehand_landing_time = 0x00;
    indoor_run_repo_data.data_s.hell_landing_time = 0x00;
    indoor_run_repo_data.data_s.inversion_amplitude = 0x00;
    indoor_run_repo_data.data_s.main_landing_methods = 0x00;
    indoor_run_repo_data.data_s.running_posture_lead = 0x00;
    indoor_run_repo_data.data_s.running_posture_back = 0x00;
    indoor_run_repo_data.data_s.avg_landing_impact_force = 0x00;
    indoor_run_repo_data.data_s.max_landing_impact_force = 0x00;
    indoor_run_repo_data.data_s.avg_touchdown_time = 0x00;
    indoor_run_repo_data.data_s.min_touchdown_time = 0x00;
    indoor_run_repo_data.data_s.avg_air_time = 0x00;
    indoor_run_repo_data.data_s.max_air_time = 0x00;
    indoor_run_repo_data.data_s.avg_ground_to_air_ratio = 0x00;
    indoor_run_repo_data.data_s.min_ground_to_air_ratio = 0x00;
    //    indoor_run_repo_data.data_s.courses_id = 0;


    memcpy(p_output_data, \
           (uint8_t *)&indoor_run_repo_data.data_s, \
           sizeof(indoor_run_repo_data.data_s));

    *p_output_data_len = sizeof(indoor_run_repo_data.data_s);

    return true;
}

// V12
static bool MUL_SPORT_POSSIBLY_UNUSED get_indoor_run_repo_v12(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Indoor_Run_Data_Type_V12 indoor_run_repo_data;

    memset(&indoor_run_repo_data, 0, sizeof(indoor_run_repo_data));
    indoor_run_repo_data.data_s.sport_start_time = get_mul_sport_start_time();
    indoor_run_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();
    indoor_run_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();
    indoor_run_repo_data.data_s.sport_total_distance = mul_sport_get_sport_distance();
    indoor_run_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();
    indoor_run_repo_data.data_s.avg_speed = mul_sport_get_sport_avg_speed_distribution();
    indoor_run_repo_data.data_s.high_speed = mul_sport_get_sport_maximum_speed_distribution();
    indoor_run_repo_data.data_s.low_speed = mul_sport_get_sport_minimum_speed_distribution();
    indoor_run_repo_data.data_s.total_step = mul_sport_get_sport_step_num();
    indoor_run_repo_data.data_s.avg_stride = mul_sport_get_sport_avg_step_frequency();
    indoor_run_repo_data.data_s.avg_step_rate = mul_sport_get_sport_avg_step_frequency();
    indoor_run_repo_data.data_s.max_step_rate = mul_sport_get_sport_maximum_step_frequency();
    indoor_run_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    indoor_run_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();
    indoor_run_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();
    indoor_run_repo_data.data_s.training_effect = 0x00;

    indoor_run_repo_data.data_s.aerobic_training_effect = 0x00;
    indoor_run_repo_data.data_s.max_oxygen_uptake = 0x00;
    indoor_run_repo_data.data_s.max_oxygen_uptake_rate = 0x00;
    indoor_run_repo_data.data_s.body_power_use = 0x00;
    indoor_run_repo_data.data_s.recover_time = 0x00; 
    indoor_run_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    indoor_run_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    indoor_run_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    indoor_run_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    indoor_run_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();
    indoor_run_repo_data.data_s.hr_zone_5 = 0x00;
    indoor_run_repo_data.data_s.hr_zone_4 = 0x00;
    indoor_run_repo_data.data_s.hr_zone_3 = 0x00;
    indoor_run_repo_data.data_s.hr_zone_2 = 0x00;
    indoor_run_repo_data.data_s.hr_zone_1 = 0x00;
    indoor_run_repo_data.data_s.pace_zone_5 = 0x00;

    indoor_run_repo_data.data_s.pace_zone_4 = 0x00;
    indoor_run_repo_data.data_s.pace_zone_3 = 0x00;
    indoor_run_repo_data.data_s.pace_zone_2 = 0x00;
    indoor_run_repo_data.data_s.pace_zone_1 = 0x00;
    indoor_run_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();
    indoor_run_repo_data.data_s.valid_exercise_time = mul_sport_get_sport_time_count();
    indoor_run_repo_data.data_s.anaerobic_training_effect = 0x00;
    indoor_run_repo_data.data_s.anaerobic_training_effect_rate = 0x00;

    indoor_run_repo_data.data_s.peak_training_effect = 0x00;
    indoor_run_repo_data.data_s.peak_training_effect_rate = 0x00;
    indoor_run_repo_data.data_s.subtype = get_sub_sport_type();
    indoor_run_repo_data.data_s.designated_courses = 0x00;
    indoor_run_repo_data.data_s.hr_zone_selection = 0;
    indoor_run_repo_data.data_s.target_duration = mul_sport_get_target_duration();
    indoor_run_repo_data.data_s.target_calorie = mul_sport_get_target_calorie();
    indoor_run_repo_data.data_s.target_distance = mul_sport_get_target_distance();
    indoor_run_repo_data.data_s.target_pace = mul_sport_get_target_pace();
    indoor_run_repo_data.data_s.target_speed = 0x00;
    indoor_run_repo_data.data_s.target_cadence = 0x00;
    indoor_run_repo_data.data_s.fixed_distance = mul_sport_get_sport_fixed_distance();
    indoor_run_repo_data.data_s.training_load = 0x00;
    indoor_run_repo_data.data_s.training_load_rate = 0x00;
    indoor_run_repo_data.data_s.running_power_index = 0x00;
    indoor_run_repo_data.data_s.running_power_level = 0x00;

    indoor_run_repo_data.data_s.training_state = 0x00;
    indoor_run_repo_data.data_s.performance_prediction_5km = 0x00;
    indoor_run_repo_data.data_s.performance_prediction_10km = 0x00;
    indoor_run_repo_data.data_s.half_marathon = 0x00;
    indoor_run_repo_data.data_s.marathon = 0x00;
    indoor_run_repo_data.data_s.genki_value = mul_sport_get_sport_genki_value();
    indoor_run_repo_data.data_s.full_palm_landing_time = 0x00;
    indoor_run_repo_data.data_s.forehand_landing_time = 0x00;

    indoor_run_repo_data.data_s.hell_landing_time = 0x00;
    indoor_run_repo_data.data_s.inversion_amplitude = 0x00;
    indoor_run_repo_data.data_s.main_landing_methods = 0x00;
    indoor_run_repo_data.data_s.front_foot_landing_ratio = 0x00;
    indoor_run_repo_data.data_s.rear_foot_landing_ratio = 0x00;
    indoor_run_repo_data.data_s.avg_impact_force = 0x00;
    indoor_run_repo_data.data_s.max_impact_force = 0x00;
    indoor_run_repo_data.data_s.avg_touchdown_time = 0x00;

    indoor_run_repo_data.data_s.min_touchdown_time = 0x00;
    indoor_run_repo_data.data_s.avg_duration_of_passage = 0x00;
    indoor_run_repo_data.data_s.max_duration_of_passage = 0x00;
    indoor_run_repo_data.data_s.avg_ground_to_air_ratio = 0x00;
    indoor_run_repo_data.data_s.min_ground_to_air_ratio = 0x00;
    indoor_run_repo_data.data_s.training_experience = 0x00;
    indoor_run_repo_data.data_s.training_tss = 0x00;
    indoor_run_repo_data.data_s.avg_running_power = 0x00;
    
    indoor_run_repo_data.data_s.max_running_power = 0x00;



//    indoor_run_repo_data.data_s.courses_id = 0;


    memcpy(p_output_data, \
           (uint8_t *)&indoor_run_repo_data.data_s, \
           sizeof(indoor_run_repo_data.data_s));

    *p_output_data_len = sizeof(indoor_run_repo_data.data_s);

    return true;
}
const static ms_common_sport_handle_v1_t MUL_SPORT_POSSIBLY_UNUSED g_ms_sport_category_t2_v1_handle = {
    .sport_handle.magic_number            = MUL_SPORT_MAGIC_NUMBER,
    .sport_handle.version                 = MUL_SPORT_VER_1,

    .sport_handle.sport_category          = MS_SPORT_CATEGORY_T2,
    .sport_handle.sport_category_ver      = MS_SPORT_CATEGORY_T2_V1,
    
    .sport_handle.data_ver                = MS_SPORT_CATEGORY_T2_V1_DATA_VER,
    .sport_handle.repo_ver                = MS_SPORT_CATEGORY_T2_V1_REPO_VER,

    .sport_handle.is_record_per_sec       = true,
    
    .sport_handle.sport_fixed_data_len    = MS_SPORT_CATEGORY_T2_V1_FIXED_BYTES,

    .sport_handle.pf_get_sport_data       = MS_GET_FUNC(get_indoor_run_data_v, MS_SPORT_CATEGORY_T2_V1_DATA_VER),
    .sport_handle.pf_get_sport_fixed_data = MS_GET_FUNC(get_indoor_run_fixed_data_v, MS_SPORT_CATEGORY_T2_V1_DATA_VER),
    .sport_handle.pf_get_sport_repo       = MS_GET_FUNC(get_indoor_run_repo_v, MS_SPORT_CATEGORY_T2_V1_REPO_VER),
    .sport_handle.pf_set_sport_data       = NULL,
    .sport_handle.pf_set_sport_repo       = NULL,
};

//-=-=
//

p_ms_abstract_sport_handle_t MUL_SPORT_POSSIBLY_UNUSED get_ms_sport_category_t2_v1(void)
{
    return (p_ms_abstract_sport_handle_t)&g_ms_sport_category_t2_v1_handle;
}

//-=-=
// get header func
static void get_ms_sport_category_t2_point_header(uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    printf("%s,verson:%d\n",__func__,version);
    switch (version)
    {
        case 0x01:
            *pp_header_data = (uint8_t *)g_sport_point_header_t2_v1_buf;
            *p_data_len = sizeof(g_sport_point_header_t2_v1_buf);
            break;

        case 0x03:
            *pp_header_data = (uint8_t *)g_sport_point_header_t2_v3_buf;
            *p_data_len = sizeof(g_sport_point_header_t2_v3_buf);
            break;   

        case 0x06:
            *pp_header_data = (uint8_t *)g_sport_point_header_t2_v6_buf;
            *p_data_len = sizeof(g_sport_point_header_t2_v6_buf);
            break; 

        default:
            break;
    }
}

static void get_ms_sport_category_t2_report_header(uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{

    switch (version)
    {
        case 0x01:
            *pp_header_data = (uint8_t *)g_sport_report_header_t2_v1_buf;
            *p_data_len = sizeof(g_sport_report_header_t2_v1_buf);
            break;

        case 0x05:
            *pp_header_data = (uint8_t *)g_sport_report_header_t2_v5_buf;
            *p_data_len = sizeof(g_sport_report_header_t2_v5_buf);
            break;
        case 0x09:
            *pp_header_data = (uint8_t *)g_sport_report_header_t2_v9_buf;
            *p_data_len = sizeof(g_sport_report_header_t2_v9_buf);
            break;    
        case 0x0A:
            *pp_header_data = (uint8_t *)g_sport_report_header_t2_v10_buf;
            *p_data_len = sizeof(g_sport_report_header_t2_v10_buf);
            break;   
        case 0x0B:
            *pp_header_data = (uint8_t*)g_sport_report_header_t2_v11_buf;
            *p_data_len = sizeof(g_sport_report_header_t2_v11_buf);
            break;
        case 0x0C:
            *pp_header_data = (uint8_t *)g_sport_report_header_t2_v12_buf;
            *p_data_len = sizeof(g_sport_report_header_t2_v12_buf);
            break;
        default:
            break;
    }
}

void get_ms_sport_category_t2_data_header(uint8_t data_type, uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (data_type)
    {
        case ENUM_POINT_DATA_T:
            get_ms_sport_category_t2_point_header(version, pp_header_data, p_data_len);
            break;

        case ENUM_REPORT_DATA_T:
            get_ms_sport_category_t2_report_header(version, pp_header_data, p_data_len);
            break;

        default:
            break;
    }
}

//-=-=
//
bool get_ms_sport_category_t2_record_info(uint8_t version, ms_record_info_t *p_record_info)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x06:
            {
                p_record_info->data_head_len = sizeof(((Indoor_Run_Data_Type_V6 *)NULL)->data_s.data_head);
                p_record_info->data_body_len = sizeof(((Indoor_Run_Data_Type_V6 *)NULL)->data_s.data_body);
            }
            break;

        default:
            ret_rst = false;
            break;
    }

    return ret_rst;
}

bool get_ms_sport_category_t2_record_head(uint8_t version, uint8_t *p_input_read_buf, ms_record_head_t *p_record_head)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x06:
            {
                Indoor_Run_Data_Type_V6 *_ = (Indoor_Run_Data_Type_V6 *)p_input_read_buf;

                p_record_head->count_sport_hold = _->data_s.data_head.count_sport_hold;
            }
            break;

        default:
            ret_rst = false;
            break;
    }

    return ret_rst;
}

bool get_ms_sport_category_t2_record_body(uint8_t version, uint8_t *p_input_read_buf, ms_record_item_t *p_record_item)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x06:
            {
                Indoor_Run_Data_Type_V6 *_ = (Indoor_Run_Data_Type_V6 *)p_input_read_buf;

                p_record_item->indoor_run.hr      = _->data_s.data_body.hr;
                p_record_item->indoor_run.cadence = _->data_s.data_body.cadence;
                p_record_item->indoor_run.pace    = _->data_s.data_body.pace;
            }
            break;

        default:
            ret_rst = false;
            break;
    }

    return ret_rst;
}

//-=-=
//

const ms_common_sport_config_v1_t MUL_SPORT_POSSIBLY_UNUSED g_indoor_run_config = {
    .sport_config.magic_number         = MUL_SPORT_MAGIC_NUMBER,
    .sport_config.version              = MUL_SPORT_VER_1,

    .sport_config.sport_category       = MS_SPORT_CATEGORY_T2,
    .sport_config.sport_category_ver   = MS_SPORT_CATEGORY_T2_V1,

    .sport_config.is_gps_sport         = false,

    .sport_config.sport_type           = ST_INDOOR_RUN,
};

#endif /* FLASH_MANAGER_SWITCH */
