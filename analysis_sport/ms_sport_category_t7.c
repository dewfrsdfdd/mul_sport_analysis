#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#include "ms_sport_category_t7.h"

#include <stdio.h>
#include <string.h>
#include "mul_sport_data_struct.h"
#include "mul_sport_platform.h"
#include "mul_sport_ver_def.h"
#include "multi_motion_sport_handle.h"


#define MS_SPORT_CATEGORY_T7_V1_FIXED_BYTES         13      // 跳绳

const uint8_t MUL_SPORT_ALIGN_WAY g_sport_point_header_t7_v1_buf[] = {0x00, 0xE0};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_point_header_t7_v3_buf[] = {0x00, 0xE0};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_point_header_t7_v5_buf[] = {0x00, 0xCC,0xC0,0x00};

const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t7_v1_buf[] = {0x00, 0xFE, 0x3E, 0xE0, 0x00};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t7_v3_buf[] = {0x00, 0xFE, 0x3F, 0xE0, 0x03, 0x80};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t7_v5_buf[] = {0x00, 0xFE, 0x1F, 0xF0, 0x00, 0xE2};

//-=-=
// V1
static bool MUL_SPORT_POSSIBLY_UNUSED get_rope_skipping_data_v1(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Rope_Skipping_Data_Type_V1 rope_skipping_data;

    memset(&rope_skipping_data, 0, sizeof(rope_skipping_data));

    rope_skipping_data.data_s.data_body.hr = mul_sport_get_sport_heart_rate();
    rope_skipping_data.data_s.data_body.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();
    rope_skipping_data.data_s.data_body.extra_jumps = mul_sport_get_cyclic_sport_counter() - multi_motion_get_prev_cyclic_sport_counter();
    rope_skipping_data.data_s.data_body.takeoff_height = 0;

    memcpy(p_output_data, \
           (uint8_t *)&rope_skipping_data.data_s.data_body, \
           sizeof(rope_skipping_data.data_s.data_body));

    *p_output_data_len = sizeof(rope_skipping_data.data_s.data_body);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_rope_skipping_fixed_data_v1(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Rope_Skipping_Data_Type_V1 rope_skipping_data;

    memset(&rope_skipping_data, 0, sizeof(rope_skipping_data));

    uint32_t mul_sport_cnt = get_mul_sport_cnt();

    rope_skipping_data.data_s.data_head.restore_time = get_recovery_motion_timestamp();
    rope_skipping_data.data_s.data_head.count_sport_hold =
            get_mul_sport_total_points_cnts() > mul_sport_cnt ?
                    get_mul_sport_total_points_cnts() - mul_sport_cnt : 0;

    rope_skipping_data.data_s.data_head.is_group = 0;
    rope_skipping_data.data_s.data_head.count_until_next_group = get_mul_sport_total_points_cnts(); // XXX:目前没有使用分组

    set_mul_sport_cnt(get_mul_sport_total_points_cnts());

    memcpy(p_output_data,
           (uint8_t *)&rope_skipping_data.data_s.data_head,
           sizeof(rope_skipping_data.data_s.data_head));

    *p_output_data_len = sizeof(rope_skipping_data.data_s.data_head);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_rope_skipping_repo_v1(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Rope_Skipping_Data_Type_V1 rope_skipping_repo_data;

    memset(&rope_skipping_repo_data, 0, sizeof(rope_skipping_repo_data));

    rope_skipping_repo_data.data_s.sport_start_time = get_mul_sport_start_time();
    rope_skipping_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();
    rope_skipping_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();
    rope_skipping_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();

    rope_skipping_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    rope_skipping_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();
    rope_skipping_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();

    rope_skipping_repo_data.data_s.training_effect = 0x00;
    rope_skipping_repo_data.data_s.body_power_use = 0x00;
    rope_skipping_repo_data.data_s.recover_time = 0x00;

    rope_skipping_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    rope_skipping_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    rope_skipping_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    rope_skipping_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    rope_skipping_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();

    rope_skipping_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();
    rope_skipping_repo_data.data_s.total_jumps = mul_sport_get_cyclic_sport_counter();
    rope_skipping_repo_data.data_s.avg_jump_freq = mul_sport_get_avg_cyclic_sport_counter();
    rope_skipping_repo_data.data_s.best_jump_freq = mul_sport_get_max_cyclic_sport_counter();

    rope_skipping_repo_data.data_s.total_rest_time = 0;
    rope_skipping_repo_data.data_s.avg_takeoff_height = 0;
    rope_skipping_repo_data.data_s.max_takeoff_height = 0;
    rope_skipping_repo_data.data_s.min_takeoff_height = 0;
    rope_skipping_repo_data.data_s.airborne_time = 0;
    rope_skipping_repo_data.data_s.acting = 0;
    rope_skipping_repo_data.data_s.group_cnts = 0;

    memcpy(p_output_data,
           (uint8_t *)&rope_skipping_repo_data.data_s,
           sizeof(rope_skipping_repo_data.data_s));

    *p_output_data_len = sizeof(rope_skipping_repo_data.data_s);

    return true;
}

//-=-=
// V3
static bool MUL_SPORT_POSSIBLY_UNUSED get_rope_skipping_data_v3(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Rope_Skipping_Data_Type_V3 rope_skipping_data;

    memset(&rope_skipping_data, 0, sizeof(rope_skipping_data));

    rope_skipping_data.data_s.data_body.hr = mul_sport_get_sport_heart_rate();
    rope_skipping_data.data_s.data_body.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();
    rope_skipping_data.data_s.data_body.extra_jumps = mul_sport_get_cyclic_sport_counter() - multi_motion_get_prev_cyclic_sport_counter();
    rope_skipping_data.data_s.data_body.takeoff_height = 0;
    rope_skipping_data.data_s.data_body.extra_trips = 0;

    memcpy(p_output_data, \
           (uint8_t *)&rope_skipping_data.data_s.data_body, \
           sizeof(rope_skipping_data.data_s.data_body));

    *p_output_data_len = sizeof(rope_skipping_data.data_s.data_body);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_rope_skipping_fixed_data_v3(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Rope_Skipping_Data_Type_V3 rope_skipping_data;

    memset(&rope_skipping_data, 0, sizeof(rope_skipping_data));

    uint32_t mul_sport_cnt = get_mul_sport_cnt();

    rope_skipping_data.data_s.data_head.restore_time = get_recovery_motion_timestamp();
    rope_skipping_data.data_s.data_head.count_sport_hold =
            get_mul_sport_total_points_cnts() > mul_sport_cnt ?
                    get_mul_sport_total_points_cnts() - mul_sport_cnt : 0;

    set_mul_sport_cnt(get_mul_sport_total_points_cnts());


    if (get_is_change_sit_type() == true && get_sport_sit_type() != SIT_NONE)
    {
        rope_skipping_data.data_s.data_head.segment_type.st_s.segment_type = 1;
        rope_skipping_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();

        set_sport_sit_type(get_sport_next_sit_type());
    }
    else
    {
        rope_skipping_data.data_s.data_head.segment_type.st_s.segment_type = 0;
        rope_skipping_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();
    }

    set_is_change_sit_type(false);


    memcpy(p_output_data,
           (uint8_t *)&rope_skipping_data.data_s.data_head,
           sizeof(rope_skipping_data.data_s.data_head));

    *p_output_data_len = sizeof(rope_skipping_data.data_s.data_head);

    return true;
}


static bool MUL_SPORT_POSSIBLY_UNUSED get_rope_skipping_repo_v3(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Rope_Skipping_Data_Type_V3 rope_skipping_repo_data;

    memset(&rope_skipping_repo_data, 0, sizeof(rope_skipping_repo_data));

    rope_skipping_repo_data.data_s.sport_start_time = get_mul_sport_start_time();
    rope_skipping_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();
    rope_skipping_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();
    rope_skipping_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();

    rope_skipping_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    rope_skipping_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();
    rope_skipping_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();

    rope_skipping_repo_data.data_s.training_effect = 0x00;
    rope_skipping_repo_data.data_s.body_power_use = 0x00;
    rope_skipping_repo_data.data_s.recover_time = 0x00;

    rope_skipping_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    rope_skipping_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    rope_skipping_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    rope_skipping_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    rope_skipping_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();

    rope_skipping_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();
    rope_skipping_repo_data.data_s.total_jumps = mul_sport_get_cyclic_sport_counter();
    rope_skipping_repo_data.data_s.avg_jump_freq = mul_sport_get_avg_cyclic_sport_counter();
    rope_skipping_repo_data.data_s.best_jump_freq = mul_sport_get_max_cyclic_sport_counter();

    rope_skipping_repo_data.data_s.total_rest_time = 0;
    rope_skipping_repo_data.data_s.avg_takeoff_height = 0;
    rope_skipping_repo_data.data_s.max_takeoff_height = 0;
    rope_skipping_repo_data.data_s.min_takeoff_height = 0;
    rope_skipping_repo_data.data_s.airborne_time = 0;
    rope_skipping_repo_data.data_s.acting = 0;
    rope_skipping_repo_data.data_s.group_cnts = 0;

    rope_skipping_repo_data.data_s.valid_exercise_time = 0;
    rope_skipping_repo_data.data_s.anaerobic_training_effect = 0;
    rope_skipping_repo_data.data_s.designated_courses = 0;
    rope_skipping_repo_data.data_s.hr_zone_selection = 0;
    rope_skipping_repo_data.data_s.target_duration = mul_sport_get_target_duration();
    rope_skipping_repo_data.data_s.target_calorie = mul_sport_get_target_calorie();
    rope_skipping_repo_data.data_s.target_times = mul_sport_get_target_times();
    rope_skipping_repo_data.data_s.total_stumbles = 0;

    memcpy(p_output_data,
           (uint8_t *)&rope_skipping_repo_data.data_s,
           sizeof(rope_skipping_repo_data.data_s));

    *p_output_data_len = sizeof(rope_skipping_repo_data.data_s);

    return true;
}

//-=-=
// V5
static bool MUL_SPORT_POSSIBLY_UNUSED get_rope_skipping_data_v5(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Rope_Skipping_Data_Type_V5 rope_skipping_data;

    memset(&rope_skipping_data, 0, sizeof(rope_skipping_data));

    rope_skipping_data.data_s.data_body.hr = mul_sport_get_sport_heart_rate();
    rope_skipping_data.data_s.data_body.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();
    rope_skipping_data.data_s.data_body.cadence = mul_sport_get_sport_rm_frequency();
    //rope_skipping_data.data_s.data_body.extra_jumps = mul_sport_get_cyclic_sport_counter() - multi_motion_get_prev_cyclic_sport_counter();
    // rope_skipping_data.data_s.data_body.takeoff_height = 0;
    // rope_skipping_data.data_s.data_body.extra_trips = 0;

    memcpy(p_output_data, \
           (uint8_t *)&rope_skipping_data.data_s.data_body, \
           sizeof(rope_skipping_data.data_s.data_body));

    *p_output_data_len = sizeof(rope_skipping_data.data_s.data_body);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_rope_skipping_fixed_data_v5(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Rope_Skipping_Data_Type_V5 rope_skipping_data;

    memset(&rope_skipping_data, 0, sizeof(rope_skipping_data));

    uint32_t mul_sport_cnt = get_mul_sport_cnt();

    rope_skipping_data.data_s.data_head.restore_time = get_recovery_motion_timestamp();
    rope_skipping_data.data_s.data_head.count_sport_hold =
            get_mul_sport_total_points_cnts() > mul_sport_cnt ?
                    get_mul_sport_total_points_cnts() - mul_sport_cnt : 0;

    set_mul_sport_cnt(get_mul_sport_total_points_cnts());

    uint32_t mul_segment_count = get_mul_sport_segment_count();

    rope_skipping_data.data_s.data_head.segment_count = 
    mul_sport_get_cyclic_sport_counter() > mul_segment_count ?
     mul_sport_get_cyclic_sport_counter() - mul_segment_count : 0; // 本段总数
    set_mul_sport_segment_count(mul_sport_get_cyclic_sport_counter());

    if (get_is_change_sit_type() == true && get_sport_sit_type() != SIT_NONE)
    {
        rope_skipping_data.data_s.data_head.segment_type.st_s.segment_type = 1;
        rope_skipping_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();

        set_sport_sit_type(get_sport_next_sit_type());
    }
    else
    {
        rope_skipping_data.data_s.data_head.segment_type.st_s.segment_type = 0;
        rope_skipping_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();
    }

    set_is_change_sit_type(false);


    memcpy(p_output_data,
           (uint8_t *)&rope_skipping_data.data_s.data_head,
           sizeof(rope_skipping_data.data_s.data_head));

    *p_output_data_len = sizeof(rope_skipping_data.data_s.data_head);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_rope_skipping_repo_v5(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Rope_Skipping_Data_Type_V5 rope_skipping_repo_data;

    memset(&rope_skipping_repo_data, 0, sizeof(rope_skipping_repo_data));
    rope_skipping_repo_data.data_s.sport_start_time = get_mul_sport_start_time();
    rope_skipping_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();
    rope_skipping_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();
    rope_skipping_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();
    rope_skipping_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    rope_skipping_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();
    rope_skipping_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();
    rope_skipping_repo_data.data_s.training_effect = 0x00;
    rope_skipping_repo_data.data_s.training_effect_rate = 0x00;
    rope_skipping_repo_data.data_s.body_power_use = 0x00;
    rope_skipping_repo_data.data_s.recover_time = 0x00;
    rope_skipping_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    rope_skipping_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    rope_skipping_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    rope_skipping_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    rope_skipping_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();
    rope_skipping_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();
    rope_skipping_repo_data.data_s.total_jumps = mul_sport_get_cyclic_sport_counter();
    rope_skipping_repo_data.data_s.avg_jump_freq = mul_sport_get_avg_cyclic_sport_counter();
    rope_skipping_repo_data.data_s.best_jump_freq = mul_sport_get_max_cyclic_sport_counter();
    rope_skipping_repo_data.data_s.total_rest_time = 0;
    rope_skipping_repo_data.data_s.avg_takeoff_height = 0;
    rope_skipping_repo_data.data_s.max_takeoff_height = 0;
    rope_skipping_repo_data.data_s.min_takeoff_height = 0;
    rope_skipping_repo_data.data_s.airborne_time = 0;
    rope_skipping_repo_data.data_s.acting = 0;
    rope_skipping_repo_data.data_s.group_cnts = 0;
    rope_skipping_repo_data.data_s.valid_exercise_time = 0x00;
    rope_skipping_repo_data.data_s.anaerobic_training_effect = 0x00;
    rope_skipping_repo_data.data_s.anaerobic_training_effect_rate = 0x00;
    rope_skipping_repo_data.data_s.designated_courses = 0x00;
    rope_skipping_repo_data.data_s.hr_zone_selection = 0x00;
    rope_skipping_repo_data.data_s.target_duration = mul_sport_get_target_duration();
    rope_skipping_repo_data.data_s.target_calorie = mul_sport_get_target_calorie();
    rope_skipping_repo_data.data_s.target_times = mul_sport_get_target_times();
    rope_skipping_repo_data.data_s.total_stumbles = 0;
    rope_skipping_repo_data.data_s.training_load = 0x00;
    rope_skipping_repo_data.data_s.training_load_rate = 0x00;
    rope_skipping_repo_data.data_s.genki_value = mul_sport_get_sport_genki_value();
    memcpy(p_output_data,
           (uint8_t *)&rope_skipping_repo_data.data_s,
           sizeof(rope_skipping_repo_data.data_s));

    *p_output_data_len = sizeof(rope_skipping_repo_data.data_s);

    return true;
}

//-=-=
//

const static ms_common_sport_handle_v1_t MUL_SPORT_POSSIBLY_UNUSED g_ms_sport_category_t7_v1_handle = {
    .sport_handle.magic_number            = MUL_SPORT_MAGIC_NUMBER,
    .sport_handle.version                 = MUL_SPORT_VER_1,

    .sport_handle.sport_category          = MS_SPORT_CATEGORY_T7,
    .sport_handle.sport_category_ver      = MS_SPORT_CATEGORY_T7_V1,
    
    .sport_handle.data_ver                = MS_SPORT_CATEGORY_T7_V1_DATA_VER,
    .sport_handle.repo_ver                = MS_SPORT_CATEGORY_T7_V1_REPO_VER,

    .sport_handle.is_record_per_sec       = true,
    
    .sport_handle.sport_fixed_data_len    = MS_SPORT_CATEGORY_T7_V1_FIXED_BYTES,

    .sport_handle.pf_get_sport_data       = MS_GET_FUNC(get_rope_skipping_data_v, MS_SPORT_CATEGORY_T7_V1_DATA_VER),
    .sport_handle.pf_get_sport_fixed_data = MS_GET_FUNC(get_rope_skipping_fixed_data_v, MS_SPORT_CATEGORY_T7_V1_DATA_VER),
    .sport_handle.pf_get_sport_repo       = MS_GET_FUNC(get_rope_skipping_repo_v, MS_SPORT_CATEGORY_T7_V1_REPO_VER),
    .sport_handle.pf_set_sport_data       = NULL,
    .sport_handle.pf_set_sport_repo       = NULL,
};

//-=-=
//

p_ms_abstract_sport_handle_t MUL_SPORT_POSSIBLY_UNUSED get_ms_sport_category_t7_v1(void)
{
    return (p_ms_abstract_sport_handle_t)&g_ms_sport_category_t7_v1_handle;
}

//-=-=
// get header func
static void get_ms_sport_category_t7_point_header(uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (version)
    {
        case 0x01:
            *pp_header_data = (uint8_t *)g_sport_point_header_t7_v1_buf;
            *p_data_len = sizeof(g_sport_point_header_t7_v1_buf);
            break;

        case 0x03:
            *pp_header_data = (uint8_t *)g_sport_point_header_t7_v3_buf;
            *p_data_len = sizeof(g_sport_point_header_t7_v3_buf);
            break;

        case 0x05:
            *pp_header_data = (uint8_t *)g_sport_point_header_t7_v5_buf;
            *p_data_len = sizeof(g_sport_point_header_t7_v5_buf);
            break;

        default:
            break;
    }
}

static void get_ms_sport_category_t7_report_header(uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (version)
    {
        case 0x01:
            *pp_header_data = (uint8_t *)g_sport_report_header_t7_v1_buf;
            *p_data_len = sizeof(g_sport_report_header_t7_v1_buf);
            break;

        case 0x03:
            *pp_header_data = (uint8_t *)g_sport_report_header_t7_v3_buf;
            *p_data_len = sizeof(g_sport_report_header_t7_v3_buf);
            break;

        case 0x05:
            *pp_header_data = (uint8_t *)g_sport_report_header_t7_v5_buf;
            *p_data_len = sizeof(g_sport_report_header_t7_v5_buf);
            break;

        default:
            break;
    }
}

void get_ms_sport_category_t7_data_header(uint8_t data_type, uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (data_type)
    {
        case ENUM_POINT_DATA_T:
            get_ms_sport_category_t7_point_header(version, pp_header_data, p_data_len);
            break;

        case ENUM_REPORT_DATA_T:
            get_ms_sport_category_t7_report_header(version, pp_header_data, p_data_len);
            break;

        default:
            break;
    }
}

//-=-=
//
bool get_ms_sport_category_t7_record_info(uint8_t version, ms_record_info_t *p_record_info)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x05:
            {
                p_record_info->data_head_len = sizeof(((Rope_Skipping_Data_Type_V5 *)NULL)->data_s.data_head);
                p_record_info->data_body_len = sizeof(((Rope_Skipping_Data_Type_V5 *)NULL)->data_s.data_body);
            }
            break;

        default:
            ret_rst = false;
            break;
    }

    return ret_rst;
}

bool get_ms_sport_category_t7_record_head(uint8_t version, uint8_t *p_input_read_buf, ms_record_head_t *p_record_head)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x05:
            {
                Rope_Skipping_Data_Type_V5 *_ = (Rope_Skipping_Data_Type_V5 *)p_input_read_buf;

                p_record_head->count_sport_hold = _->data_s.data_head.count_sport_hold;
            }
            break;

        default:
            ret_rst = false;
            break;
    }

    return ret_rst;
}

bool get_ms_sport_category_t7_record_body(uint8_t version, uint8_t *p_input_read_buf, ms_record_item_t *p_record_item)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x05:
            {
                Rope_Skipping_Data_Type_V5 *_ = (Rope_Skipping_Data_Type_V5 *)p_input_read_buf;

                p_record_item->rope_skip.hr         = _->data_s.data_body.hr;
                p_record_item->rowing_m.action_freq = _->data_s.data_body.cadence;
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
const ms_common_sport_config_v1_t MUL_SPORT_POSSIBLY_UNUSED g_rope_skipping_config = {
    .sport_config.magic_number         = MUL_SPORT_MAGIC_NUMBER,
    .sport_config.version              = MUL_SPORT_VER_1,

    .sport_config.sport_category       = MS_SPORT_CATEGORY_T7,
    .sport_config.sport_category_ver   = MS_SPORT_CATEGORY_T7_V1,

    .sport_config.is_gps_sport         = false,

    .sport_config.sport_type           = ST_ROPE_SKIPPING,
};

#endif /* FLASH_MANAGER_SWITCH */
