#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#include "ms_sport_category_t6.h"

#include <stdio.h>
#include <string.h>
#include "mul_sport_data_struct.h"
#include "mul_sport_platform.h"
#include "mul_sport_ver_def.h"
#include "multi_motion_sport_handle.h"

#define MS_SPORT_CATEGORY_T6_V1_FIXED_BYTES         13      // 划船机

const uint8_t MUL_SPORT_ALIGN_WAY g_sport_point_header_t6_v1_buf[] = {0x00, 0xCC, 0x90};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_point_header_t6_v2_buf[] = {0x00, 0xCC, 0x90};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_point_header_t6_v4_buf[] = {0x00, 0xCC, 0xC0};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t6_v1_buf[] = {0x00, 0xFE, 0x3E, 0xE0};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t6_v4_buf[] = {0x00, 0xFE, 0x3F, 0xE0, 0x1C};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t6_v6_buf[] = {0x00, 0xFE, 0x1F, 0xF0, 0x07,0x20};
//-=-=
// V1
static bool MUL_SPORT_POSSIBLY_UNUSED get_rowing_machine_data_v1(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Rowing_Machine_Data_Type_V1 rowing_machine_data;

    memset(&rowing_machine_data, 0, sizeof(rowing_machine_data));

    rowing_machine_data.data_s.data_body.hr = mul_sport_get_sport_heart_rate();
    rowing_machine_data.data_s.data_body.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();
    rowing_machine_data.data_s.data_body.extra_stroke.es_s.is_drive = 0;
    rowing_machine_data.data_s.data_body.extra_stroke.es_s.is_put = 0;
    rowing_machine_data.data_s.data_body.extra_stroke.es_s.extra_stroke = mul_sport_get_cyclic_sport_counter() - multi_motion_get_prev_cyclic_sport_counter();

    memcpy(p_output_data, \
           (uint8_t *)&rowing_machine_data.data_s.data_body, \
           sizeof(rowing_machine_data.data_s.data_body));

    *p_output_data_len = sizeof(rowing_machine_data.data_s.data_body);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_rowing_machine_fixed_data_v1(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Rowing_Machine_Data_Type_V1 rowing_machine_data;

    memset(&rowing_machine_data, 0, sizeof(rowing_machine_data));

    uint32_t mul_sport_cnt = get_mul_sport_cnt();

    rowing_machine_data.data_s.data_head.restore_time = get_recovery_motion_timestamp();
    rowing_machine_data.data_s.data_head.count_sport_hold =
            get_mul_sport_total_points_cnts() > mul_sport_cnt ?
                    get_mul_sport_total_points_cnts() - mul_sport_cnt : 0;

    rowing_machine_data.data_s.data_head.is_group = 0;
    rowing_machine_data.data_s.data_head.count_until_next_group = get_mul_sport_total_points_cnts(); // XXX:目前没有使用分组

    set_mul_sport_cnt(get_mul_sport_total_points_cnts());

    memcpy(p_output_data,
           (uint8_t *)&rowing_machine_data.data_s.data_head,
           sizeof(rowing_machine_data.data_s.data_head));

    *p_output_data_len = sizeof(rowing_machine_data.data_s.data_head);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_rowing_machine_repo_v1(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Rowing_Machine_Data_Type_V1 rowing_machine_repo_data;

    memset(&rowing_machine_repo_data, 0, sizeof(rowing_machine_repo_data));

    rowing_machine_repo_data.data_s.sport_start_time = get_mul_sport_start_time();
    rowing_machine_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();
    rowing_machine_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();
    rowing_machine_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();

    rowing_machine_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    rowing_machine_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();
    rowing_machine_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();

    rowing_machine_repo_data.data_s.training_effect = 0x00;
    rowing_machine_repo_data.data_s.body_power_use = 0x00;
    rowing_machine_repo_data.data_s.recover_time = 0x00;

    rowing_machine_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    rowing_machine_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    rowing_machine_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    rowing_machine_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    rowing_machine_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();

    rowing_machine_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();
    rowing_machine_repo_data.data_s.total_strokes = mul_sport_get_cyclic_sport_counter();
    rowing_machine_repo_data.data_s.avg_stroke_freq = mul_sport_get_avg_cyclic_sport_counter();
    rowing_machine_repo_data.data_s.best_stroke_freq = mul_sport_get_max_cyclic_sport_counter();

    rowing_machine_repo_data.data_s.drive_time = 0;
    rowing_machine_repo_data.data_s.put_time = 0;
    rowing_machine_repo_data.data_s.total_rest_time = 0;
    rowing_machine_repo_data.data_s.group_cnts = 0;

    memcpy(p_output_data,
           (uint8_t *)&rowing_machine_repo_data.data_s,
           sizeof(rowing_machine_repo_data.data_s));

    *p_output_data_len = sizeof(rowing_machine_repo_data.data_s);

    return true;
}

//-=-=
// V2
static bool MUL_SPORT_POSSIBLY_UNUSED get_rowing_machine_data_v2(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Rowing_Machine_Data_Type_V2 rowing_machine_data;

    memset(&rowing_machine_data, 0, sizeof(rowing_machine_data));

    rowing_machine_data.data_s.data_body.hr = mul_sport_get_sport_heart_rate();
    rowing_machine_data.data_s.data_body.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();
    rowing_machine_data.data_s.data_body.extra_stroke.es_s.is_drive = 0;
    rowing_machine_data.data_s.data_body.extra_stroke.es_s.is_put = 0;
    rowing_machine_data.data_s.data_body.extra_stroke.es_s.extra_stroke = mul_sport_get_cyclic_sport_counter() - multi_motion_get_prev_cyclic_sport_counter();

    memcpy(p_output_data, \
           (uint8_t *)&rowing_machine_data.data_s.data_body, \
           sizeof(rowing_machine_data.data_s.data_body));

    *p_output_data_len = sizeof(rowing_machine_data.data_s.data_body);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_rowing_machine_fixed_data_v2(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Rowing_Machine_Data_Type_V2 rowing_machine_data;

    memset(&rowing_machine_data, 0, sizeof(rowing_machine_data));

    uint32_t mul_sport_cnt = get_mul_sport_cnt();

    rowing_machine_data.data_s.data_head.restore_time = get_recovery_motion_timestamp();
    rowing_machine_data.data_s.data_head.count_sport_hold =
            get_mul_sport_total_points_cnts() > mul_sport_cnt ?
                    get_mul_sport_total_points_cnts() - mul_sport_cnt : 0;

    set_mul_sport_cnt(get_mul_sport_total_points_cnts());


    if (get_is_change_sit_type() == true && get_sport_sit_type() != SIT_NONE)
    {
        rowing_machine_data.data_s.data_head.segment_type.st_s.segment_type = 1;
        rowing_machine_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();

        set_sport_sit_type(get_sport_next_sit_type());
    }
    else
    {
        rowing_machine_data.data_s.data_head.segment_type.st_s.segment_type = 0;
        rowing_machine_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();
    }

    set_is_change_sit_type(false);


    memcpy(p_output_data,
           (uint8_t *)&rowing_machine_data.data_s.data_head,
           sizeof(rowing_machine_data.data_s.data_head));

    *p_output_data_len = sizeof(rowing_machine_data.data_s.data_head);

    return true;
}

//-=-=
// V4
static bool MUL_SPORT_POSSIBLY_UNUSED get_rowing_machine_repo_v4(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Rowing_Machine_Data_Type_V4 rowing_machine_repo_data;

    memset(&rowing_machine_repo_data, 0, sizeof(rowing_machine_repo_data));

    rowing_machine_repo_data.data_s.sport_start_time = get_mul_sport_start_time();
    rowing_machine_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();
    rowing_machine_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();
    rowing_machine_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();

    rowing_machine_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    rowing_machine_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();
    rowing_machine_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();

    rowing_machine_repo_data.data_s.training_effect = 0x00;
    rowing_machine_repo_data.data_s.body_power_use = 0x00;
    rowing_machine_repo_data.data_s.recover_time = 0x00;

    rowing_machine_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    rowing_machine_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    rowing_machine_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    rowing_machine_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    rowing_machine_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();

    rowing_machine_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();
    rowing_machine_repo_data.data_s.total_strokes = mul_sport_get_cyclic_sport_counter();
    rowing_machine_repo_data.data_s.avg_stroke_freq = mul_sport_get_avg_cyclic_sport_counter();
    rowing_machine_repo_data.data_s.best_stroke_freq = mul_sport_get_max_cyclic_sport_counter();

    rowing_machine_repo_data.data_s.drive_time = 0;
    rowing_machine_repo_data.data_s.put_time = 0;
    rowing_machine_repo_data.data_s.total_rest_time = 0;
    rowing_machine_repo_data.data_s.group_cnts = 0;

    rowing_machine_repo_data.data_s.valid_exercise_time = 0;
    rowing_machine_repo_data.data_s.anaerobic_training_effect = 0;
    rowing_machine_repo_data.data_s.designated_courses = 0;
    rowing_machine_repo_data.data_s.hr_zone_selection = 0;
    rowing_machine_repo_data.data_s.target_duration = mul_sport_get_target_duration();
    rowing_machine_repo_data.data_s.target_calorie = mul_sport_get_target_calorie();
    rowing_machine_repo_data.data_s.target_times = mul_sport_get_target_times();

    memcpy(p_output_data,
           (uint8_t *)&rowing_machine_repo_data.data_s,
           sizeof(rowing_machine_repo_data.data_s));

    *p_output_data_len = sizeof(rowing_machine_repo_data.data_s);

    return true;
}

//-=-=
// V4
static bool MUL_SPORT_POSSIBLY_UNUSED get_rowing_machine_data_v4(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Rowing_Machine_Data_Type_V4 rowing_machine_data;

    memset(&rowing_machine_data, 0, sizeof(rowing_machine_data));

    rowing_machine_data.data_s.data_body.hr = mul_sport_get_sport_heart_rate();
    rowing_machine_data.data_s.data_body.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();
    // rowing_machine_data.data_s.data_body.extra_stroke.es_s.is_drive = 0;
    // rowing_machine_data.data_s.data_body.extra_stroke.es_s.is_put = 0;
    // rowing_machine_data.data_s.data_body.extra_stroke.es_s.extra_stroke = mul_sport_get_cyclic_sport_counter() - multi_motion_get_prev_cyclic_sport_counter();
    rowing_machine_data.data_s.data_body.sliding_frequency = mul_sport_get_sport_rm_frequency();
    memcpy(p_output_data, \
           (uint8_t *)&rowing_machine_data.data_s.data_body, \
           sizeof(rowing_machine_data.data_s.data_body));

    *p_output_data_len = sizeof(rowing_machine_data.data_s.data_body);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_rowing_machine_fixed_data_v4(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Rowing_Machine_Data_Type_V4 rowing_machine_data;

    memset(&rowing_machine_data, 0, sizeof(rowing_machine_data));

    uint32_t mul_sport_cnt = get_mul_sport_cnt();

    rowing_machine_data.data_s.data_head.restore_time = get_recovery_motion_timestamp();
    rowing_machine_data.data_s.data_head.count_sport_hold =
            get_mul_sport_total_points_cnts() > mul_sport_cnt ?
                    get_mul_sport_total_points_cnts() - mul_sport_cnt : 0;

    set_mul_sport_cnt(get_mul_sport_total_points_cnts());


    if (get_is_change_sit_type() == true && get_sport_sit_type() != SIT_NONE)
    {
        rowing_machine_data.data_s.data_head.segment_type.st_s.segment_type = 1;
        rowing_machine_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();

        set_sport_sit_type(get_sport_next_sit_type());
    }
    else
    {
        rowing_machine_data.data_s.data_head.segment_type.st_s.segment_type = 0;
        rowing_machine_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();
    }
    // rowing_machine_data.data_s.data_head.segment_times = 0;//TODO本段划次
    uint32_t mul_segment_count = get_mul_sport_segment_count();

    rowing_machine_data.data_s.data_head.segment_times = 
    mul_sport_get_cyclic_sport_counter() > mul_segment_count ?
     mul_sport_get_cyclic_sport_counter() - mul_segment_count : 0; // 本段划次
    set_mul_sport_segment_count(mul_sport_get_cyclic_sport_counter());
    
    set_is_change_sit_type(false);


    memcpy(p_output_data,
           (uint8_t *)&rowing_machine_data.data_s.data_head,
           sizeof(rowing_machine_data.data_s.data_head));

    *p_output_data_len = sizeof(rowing_machine_data.data_s.data_head);

    return true;
}

//-=-=
// V6
static bool MUL_SPORT_POSSIBLY_UNUSED get_rowing_machine_repo_v6(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Rowing_Machine_Data_Type_V6 rowing_machine_repo_data;

    memset(&rowing_machine_repo_data, 0, sizeof(rowing_machine_repo_data));

    rowing_machine_repo_data.data_s.sport_start_time = get_mul_sport_start_time();
    rowing_machine_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();
    rowing_machine_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();
    rowing_machine_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();

    rowing_machine_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    rowing_machine_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();
    rowing_machine_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();

    rowing_machine_repo_data.data_s.training_effect = 0x00;
    rowing_machine_repo_data.data_s.body_power_use = 0x00;
    rowing_machine_repo_data.data_s.recover_time = 0x00;

    rowing_machine_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    rowing_machine_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    rowing_machine_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    rowing_machine_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    rowing_machine_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();

    rowing_machine_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();
    rowing_machine_repo_data.data_s.total_strokes = mul_sport_get_cyclic_sport_counter();
    rowing_machine_repo_data.data_s.avg_stroke_freq = mul_sport_get_avg_cyclic_sport_counter();
    rowing_machine_repo_data.data_s.best_stroke_freq = mul_sport_get_max_cyclic_sport_counter();

    rowing_machine_repo_data.data_s.drive_time = 0;
    rowing_machine_repo_data.data_s.put_time = 0;
    rowing_machine_repo_data.data_s.total_rest_time = 0;
    rowing_machine_repo_data.data_s.group_cnts = 0;

    rowing_machine_repo_data.data_s.valid_exercise_time = 0;
    rowing_machine_repo_data.data_s.anaerobic_training_effect = 0;
    rowing_machine_repo_data.data_s.designated_courses = 0;
    rowing_machine_repo_data.data_s.hr_zone_selection = 0;
    rowing_machine_repo_data.data_s.target_duration = mul_sport_get_target_duration();
    rowing_machine_repo_data.data_s.target_calorie = mul_sport_get_target_calorie();
    rowing_machine_repo_data.data_s.target_times = mul_sport_get_target_times();
    rowing_machine_repo_data.data_s.genki_value = mul_sport_get_sport_genki_value();
    memcpy(p_output_data,
           (uint8_t *)&rowing_machine_repo_data.data_s,
           sizeof(rowing_machine_repo_data.data_s));

    *p_output_data_len = sizeof(rowing_machine_repo_data.data_s);

    return true;
}

//-=-=
//

const static ms_common_sport_handle_v1_t MUL_SPORT_POSSIBLY_UNUSED g_ms_sport_category_t6_v1_handle = {
    .sport_handle.magic_number            = MUL_SPORT_MAGIC_NUMBER,
    .sport_handle.version                 = MUL_SPORT_VER_1,

    .sport_handle.sport_category          = MS_SPORT_CATEGORY_T6,
    .sport_handle.sport_category_ver      = MS_SPORT_CATEGORY_T6_V1,
    
    .sport_handle.data_ver                = MS_SPORT_CATEGORY_T6_V1_DATA_VER,
    .sport_handle.repo_ver                = MS_SPORT_CATEGORY_T6_V1_REPO_VER,

    .sport_handle.is_record_per_sec       = true,
    
    .sport_handle.sport_fixed_data_len    = MS_SPORT_CATEGORY_T6_V1_FIXED_BYTES,

    .sport_handle.pf_get_sport_data       = MS_GET_FUNC(get_rowing_machine_data_v, MS_SPORT_CATEGORY_T6_V1_DATA_VER),
    .sport_handle.pf_get_sport_fixed_data = MS_GET_FUNC(get_rowing_machine_fixed_data_v, MS_SPORT_CATEGORY_T6_V1_DATA_VER),
    .sport_handle.pf_get_sport_repo       = MS_GET_FUNC(get_rowing_machine_repo_v, MS_SPORT_CATEGORY_T6_V1_REPO_VER),
    .sport_handle.pf_set_sport_data       = NULL,
    .sport_handle.pf_set_sport_repo       = NULL,
};

//-=-=
//

p_ms_abstract_sport_handle_t MUL_SPORT_POSSIBLY_UNUSED get_ms_sport_category_t6_v1(void)
{
    return (p_ms_abstract_sport_handle_t)&g_ms_sport_category_t6_v1_handle;
}

//-=-=
// get header func
static void get_ms_sport_category_t6_point_header(uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (version)
    {
        case 0x01:
            *pp_header_data = (uint8_t *)g_sport_point_header_t6_v1_buf;
            *p_data_len = sizeof(g_sport_point_header_t6_v1_buf);
            break;

        case 0x02:
            *pp_header_data = (uint8_t *)g_sport_point_header_t6_v2_buf;
            *p_data_len = sizeof(g_sport_point_header_t6_v2_buf);
            break;

        case 0x04:
            *pp_header_data = (uint8_t *)g_sport_point_header_t6_v4_buf;
            *p_data_len = sizeof(g_sport_point_header_t6_v4_buf);
            break;
            
        default:
            break;
    }
}

static void get_ms_sport_category_t6_report_header(uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (version)
    {
        case 0x01:
            *pp_header_data = (uint8_t *)g_sport_report_header_t6_v1_buf;
            *p_data_len = sizeof(g_sport_report_header_t6_v1_buf);
            break;

        case 0x04:
            *pp_header_data = (uint8_t *)g_sport_report_header_t6_v4_buf;
            *p_data_len = sizeof(g_sport_report_header_t6_v4_buf);
            break;

        case 0x06:
            *pp_header_data = (uint8_t *)g_sport_report_header_t6_v6_buf;
            *p_data_len = sizeof(g_sport_report_header_t6_v6_buf);
            break;

        default:
            break;
    }
}

void get_ms_sport_category_t6_data_header(uint8_t data_type, uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (data_type)
    {
        case ENUM_POINT_DATA_T:
            get_ms_sport_category_t6_point_header(version, pp_header_data, p_data_len);
            break;

        case ENUM_REPORT_DATA_T:
            get_ms_sport_category_t6_report_header(version, pp_header_data, p_data_len);
            break;

        default:
            break;
    }
}

//-=-=
//
bool get_ms_sport_category_t6_record_info(uint8_t version, ms_record_info_t *p_record_info)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x04:
            {
                p_record_info->data_head_len = sizeof(((Rowing_Machine_Data_Type_V4 *)NULL)->data_s.data_head);
                p_record_info->data_body_len = sizeof(((Rowing_Machine_Data_Type_V4 *)NULL)->data_s.data_body);
            }
            break;

        default:
            ret_rst = false;
            break;
    }

    return ret_rst;
}

bool get_ms_sport_category_t6_record_head(uint8_t version, uint8_t *p_input_read_buf, ms_record_head_t *p_record_head)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x04:
            {
                Rowing_Machine_Data_Type_V4 *_ = (Rowing_Machine_Data_Type_V4 *)p_input_read_buf;

                p_record_head->count_sport_hold = _->data_s.data_head.count_sport_hold;
            }
            break;

        default:
            ret_rst = false;
            break;
    }

    return ret_rst;
}

bool get_ms_sport_category_t6_record_body(uint8_t version, uint8_t *p_input_read_buf, ms_record_item_t *p_record_item)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x04:
            {
                Rowing_Machine_Data_Type_V4 *_ = (Rowing_Machine_Data_Type_V4 *)p_input_read_buf;

                p_record_item->rowing_m.hr          = _->data_s.data_body.hr;
                p_record_item->rowing_m.action_freq = _->data_s.data_body.sliding_frequency;
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

//-=-=
//
const ms_common_sport_config_v1_t MUL_SPORT_POSSIBLY_UNUSED g_rowing_machine_config = {
    .sport_config.magic_number         = MUL_SPORT_MAGIC_NUMBER,
    .sport_config.version              = MUL_SPORT_VER_1,

    .sport_config.sport_category       = MS_SPORT_CATEGORY_T6,
    .sport_config.sport_category_ver   = MS_SPORT_CATEGORY_T6_V1,

    .sport_config.is_gps_sport         = false,

    .sport_config.sport_type           = ST_ROWING_MACHINE,
};



#endif /* FLASH_MANAGER_SWITCH */
