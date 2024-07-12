#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#include "ms_sport_category_t4.h"

#include <stdio.h>
#include <string.h>
#include "mul_sport_data_struct.h"
#include "mul_sport_platform.h"
#include "mul_sport_ver_def.h"
#include "multi_motion_sport_handle.h"

#define MS_SPORT_CATEGORY_T4_V1_FIXED_BYTES         9      // 自由训练

const uint8_t MUL_SPORT_ALIGN_WAY g_sport_point_header_t4_v1_buf[] = {0x00, 0xC0};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_point_header_t4_v2_buf[] = {0x00, 0xC0};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t4_v4_buf[] = {0x00, 0xFE, 0x3E, 0x20};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t4_v5_buf[] = {0x00, 0xFE, 0x3F, 0x26};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t4_v8_buf[] = {0x00, 0xFE, 0x00, 0x7E,0x26,0x40,0x00};
//-=-=
// V1
static bool MUL_SPORT_POSSIBLY_UNUSED get_free_sport_data_v1(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Free_Sport_Data_Type_V1 free_sport_data;

    memset(&free_sport_data, 0, sizeof(free_sport_data));

    free_sport_data.data_s.data_body.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();

    free_sport_data.data_s.data_body.hr = mul_sport_get_sport_heart_rate();

    memcpy(p_output_data,
           (uint8_t *)&free_sport_data.data_s.data_body,
           sizeof(free_sport_data.data_s.data_body));

    *p_output_data_len = sizeof(free_sport_data.data_s.data_body);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_free_sport_fixed_data_v1(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Free_Sport_Data_Type_V1 free_sport_data;

    memset(&free_sport_data, 0, sizeof(free_sport_data));

    uint32_t mul_sport_cnt = get_mul_sport_cnt();

    free_sport_data.data_s.data_head.restore_time = get_recovery_motion_timestamp();
    free_sport_data.data_s.data_head.count_sport_hold =
            get_mul_sport_total_points_cnts() > mul_sport_cnt ?
                    get_mul_sport_total_points_cnts() - mul_sport_cnt : 0;

    set_mul_sport_cnt(get_mul_sport_total_points_cnts());

    memcpy(p_output_data,
           (uint8_t *)&free_sport_data.data_s.data_head,
           sizeof(free_sport_data.data_s.data_head));

    *p_output_data_len = sizeof(free_sport_data.data_s.data_head);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_free_sport_repo_v1(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Repofree_Sport_Data_Type_V1 free_sport_repo_data;

    memset(&free_sport_repo_data, 0, sizeof(free_sport_repo_data));

    free_sport_repo_data.data_s.sport_start_time = get_mul_sport_start_time();

    free_sport_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();

    free_sport_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();

    free_sport_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();

    free_sport_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    free_sport_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();

    free_sport_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();


    free_sport_repo_data.data_s.training_effect = 0x00;
    free_sport_repo_data.data_s.body_power_use = 0x00;
    free_sport_repo_data.data_s.recover_time = 0x00;

    free_sport_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    free_sport_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    free_sport_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    free_sport_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    free_sport_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();

    memcpy(p_output_data,
           (uint8_t *)&free_sport_repo_data.data_s,
           sizeof(free_sport_repo_data.data_s));

    *p_output_data_len = sizeof(free_sport_repo_data.data_s);

    return true;
}

//-=-=
// V2
static bool MUL_SPORT_POSSIBLY_UNUSED get_free_sport_data_v2(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Free_Sport_Data_Type_V2 free_sport_data;

    memset(&free_sport_data, 0, sizeof(free_sport_data));

    free_sport_data.data_s.data_body.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();

    free_sport_data.data_s.data_body.hr = mul_sport_get_sport_heart_rate();

    memcpy(p_output_data,
           (uint8_t *)&free_sport_data.data_s.data_body,
           sizeof(free_sport_data.data_s.data_body));

    *p_output_data_len = sizeof(free_sport_data.data_s.data_body);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_free_sport_fixed_data_v2(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Free_Sport_Data_Type_V2 free_sport_data;

    memset(&free_sport_data, 0, sizeof(free_sport_data));

    uint32_t mul_sport_cnt = get_mul_sport_cnt();

    free_sport_data.data_s.data_head.restore_time = get_recovery_motion_timestamp();
    free_sport_data.data_s.data_head.count_sport_hold =
            get_mul_sport_total_points_cnts() > mul_sport_cnt ?
                    get_mul_sport_total_points_cnts() - mul_sport_cnt : 0;

    set_mul_sport_cnt(get_mul_sport_total_points_cnts());


    if (get_is_change_sit_type() == true && get_sport_sit_type() != SIT_NONE)
    {
        free_sport_data.data_s.data_head.segment_type.st_s.segment_type = 1;
        free_sport_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();

        set_sport_sit_type(get_sport_next_sit_type());
    }
    else
    {
        free_sport_data.data_s.data_head.segment_type.st_s.segment_type = 0;
        free_sport_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();
    }

    set_is_change_sit_type(false);


    memcpy(p_output_data,
           (uint8_t *)&free_sport_data.data_s.data_head,
           sizeof(free_sport_data.data_s.data_head));

    *p_output_data_len = sizeof(free_sport_data.data_s.data_head);

    return true;
}

//-=-=
// V4
static bool MUL_SPORT_POSSIBLY_UNUSED get_free_sport_repo_v4(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Repofree_Sport_Data_Type_V4 free_sport_repo_data;

    memset(&free_sport_repo_data, 0, sizeof(free_sport_repo_data));

    free_sport_repo_data.data_s.sport_start_time = get_mul_sport_start_time();

    free_sport_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();

    free_sport_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();

    free_sport_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();

    free_sport_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    free_sport_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();

    free_sport_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();


    free_sport_repo_data.data_s.training_effect = 0x00;
    free_sport_repo_data.data_s.body_power_use = 0x00;
    free_sport_repo_data.data_s.recover_time = 0x00;

    free_sport_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    free_sport_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    free_sport_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    free_sport_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    free_sport_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();
    free_sport_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();
    free_sport_repo_data.data_s.valid_exercise_time = mul_sport_get_sport_time_count();
    free_sport_repo_data.data_s.without_oxygen_training_time = 0;
    free_sport_repo_data.data_s.free_style_sub_sport_type = get_sub_sport_type();

    memcpy(p_output_data,
           (uint8_t *)&free_sport_repo_data.data_s,
           sizeof(free_sport_repo_data.data_s));

    *p_output_data_len = sizeof(free_sport_repo_data.data_s);

    return true;
}

//-=-=
// V5
static bool MUL_SPORT_POSSIBLY_UNUSED get_free_sport_repo_v5(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Repofree_Sport_Data_Type_V5 free_sport_repo_data;

    memset(&free_sport_repo_data, 0, sizeof(free_sport_repo_data));

    free_sport_repo_data.data_s.sport_start_time = get_mul_sport_start_time();

    free_sport_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();

    free_sport_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();

    free_sport_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();

    free_sport_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    free_sport_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();

    free_sport_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();


    free_sport_repo_data.data_s.training_effect = 0x00;
    free_sport_repo_data.data_s.body_power_use = 0x00;
    free_sport_repo_data.data_s.recover_time = 0x00;

    free_sport_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    free_sport_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    free_sport_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    free_sport_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    free_sport_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();
    free_sport_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();
    free_sport_repo_data.data_s.valid_exercise_time = mul_sport_get_sport_time_count();
    free_sport_repo_data.data_s.without_oxygen_training_time = 0;
    free_sport_repo_data.data_s.free_style_sub_sport_type = get_sub_sport_type();
    free_sport_repo_data.data_s.designated_courses = 0;
    free_sport_repo_data.data_s.hr_zone_selection = 0;
    free_sport_repo_data.data_s.target_duration = mul_sport_get_target_duration();
    free_sport_repo_data.data_s.target_calorie = mul_sport_get_target_calorie();

    memcpy(p_output_data,
           (uint8_t *)&free_sport_repo_data.data_s,
           sizeof(free_sport_repo_data.data_s));

    *p_output_data_len = sizeof(free_sport_repo_data.data_s);

    return true;
}
//-=-=
// V8
static bool MUL_SPORT_POSSIBLY_UNUSED get_free_sport_repo_v8(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Repofree_Sport_Data_Type_V8 free_sport_repo_data;

    memset(&free_sport_repo_data, 0, sizeof(free_sport_repo_data));
    free_sport_repo_data.data_s.sport_start_time = get_mul_sport_start_time();

    free_sport_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();

    free_sport_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();

    free_sport_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();
    free_sport_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    free_sport_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();

    free_sport_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();
    free_sport_repo_data.data_s.avg_spo2 = 0x00;
    free_sport_repo_data.data_s.max_spo2 = 0x00;
    free_sport_repo_data.data_s.min_spo2 = 0x00;
    free_sport_repo_data.data_s.avg_stress = 0x00;
    free_sport_repo_data.data_s.max_stress = 0x00;
    free_sport_repo_data.data_s.min_stress = 0x00;
    free_sport_repo_data.data_s.training_effect = 0x00;
    free_sport_repo_data.data_s.training_effect_rating = 0x00;
    free_sport_repo_data.data_s.body_power_use = 0x00;
    free_sport_repo_data.data_s.recover_time = 0x00;
    free_sport_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    free_sport_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    free_sport_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    free_sport_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    free_sport_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();
    free_sport_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();
    free_sport_repo_data.data_s.valid_exercise_time = mul_sport_get_sport_time_count();
    free_sport_repo_data.data_s.without_oxygen_training_time = 0;
    free_sport_repo_data.data_s.without_oxygen_training_time_rate = 0;
    free_sport_repo_data.data_s.free_style_sub_sport_type = get_sub_sport_type();
    free_sport_repo_data.data_s.designated_courses = 0;
    free_sport_repo_data.data_s.hr_zone_selection = 0;
    free_sport_repo_data.data_s.target_duration = mul_sport_get_target_duration();
    free_sport_repo_data.data_s.target_calorie = mul_sport_get_target_calorie();
    free_sport_repo_data.data_s.training_load = 0;
    free_sport_repo_data.data_s.training_load_rate = 0;
    free_sport_repo_data.data_s.genki_value = mul_sport_get_sport_genki_value();
    free_sport_repo_data.data_s.total_punching_count = 0;
    free_sport_repo_data.data_s.total_perfect_count = 0;
    free_sport_repo_data.data_s.total_good_count = 0;
    free_sport_repo_data.data_s.total_miss_count = 0;
    free_sport_repo_data.data_s.max_punching_force = 0;
    free_sport_repo_data.data_s.max_double_hit = 0;
    free_sport_repo_data.data_s.hit_rate = 0;


    memcpy(p_output_data,
           (uint8_t *)&free_sport_repo_data.data_s,
           sizeof(free_sport_repo_data.data_s));

    *p_output_data_len = sizeof(free_sport_repo_data.data_s);

    return true;
}
//-=-=
// get header func
static void get_ms_sport_category_t4_point_header(uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (version)
    {
        case 0x01:
            *pp_header_data = (uint8_t *)g_sport_point_header_t4_v1_buf;
            *p_data_len = sizeof(g_sport_point_header_t4_v1_buf);
            break;

        case 0x02:
            *pp_header_data = (uint8_t *)g_sport_point_header_t4_v2_buf;
            *p_data_len = sizeof(g_sport_point_header_t4_v2_buf);
            break;

        default:
            break;
    }
}

static void get_ms_sport_category_t4_report_header(uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (version)
    {
        case 0x04:
            *pp_header_data = (uint8_t *)g_sport_report_header_t4_v4_buf;
            *p_data_len = sizeof(g_sport_report_header_t4_v4_buf);
            break;

        case 0x05:
            *pp_header_data = (uint8_t *)g_sport_report_header_t4_v5_buf;
            *p_data_len = sizeof(g_sport_report_header_t4_v5_buf);
            break;

        case 0x08:
            *pp_header_data = (uint8_t *)g_sport_report_header_t4_v8_buf;
            *p_data_len = sizeof(g_sport_report_header_t4_v8_buf);
            break;

        default:
            break;
    }
}

void get_ms_sport_category_t4_data_header(uint8_t data_type, uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (data_type)
    {
        case ENUM_POINT_DATA_T:
            get_ms_sport_category_t4_point_header(version, pp_header_data, p_data_len);
            break;

        case ENUM_REPORT_DATA_T:
            get_ms_sport_category_t4_report_header(version, pp_header_data, p_data_len);
            break;

        default:
            break;
    }
}

//-=-=
//

bool get_ms_sport_category_t4_record_info(uint8_t version, ms_record_info_t *p_record_info)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x02:
            {
                p_record_info->data_head_len = sizeof(((Free_Sport_Data_Type_V2 *)NULL)->data_s.data_head);
                p_record_info->data_body_len = sizeof(((Free_Sport_Data_Type_V2 *)NULL)->data_s.data_body);
            }
            break;

        default:
            ret_rst = false;
            break;
    }

    return ret_rst;
}

bool get_ms_sport_category_t4_record_head(uint8_t version, uint8_t *p_input_read_buf, ms_record_head_t *p_record_head)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x02:
            {
                Free_Sport_Data_Type_V2 *_ = (Free_Sport_Data_Type_V2 *)p_input_read_buf;

                p_record_head->count_sport_hold = _->data_s.data_head.count_sport_hold;
            }
            break;

        default:
            ret_rst = false;
            break;
    }

    return ret_rst;
}

bool get_ms_sport_category_t4_record_body(uint8_t version, uint8_t *p_input_read_buf, ms_record_item_t *p_record_item)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x02:
            {
                Free_Sport_Data_Type_V2 *_ = (Free_Sport_Data_Type_V2 *)p_input_read_buf;

                p_record_item->free_sport.hr = _->data_s.data_body.hr;
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

bool get_ms_sport_category_t4_sub_sport_type(uint8_t version, void *p_input_data, uint16_t *sub_sport_type)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x04:
            {
                Repofree_Sport_Data_Type_V4 *p_free_sport_repo_data;
                p_free_sport_repo_data = p_input_data;
                *sub_sport_type = p_free_sport_repo_data->data_s.free_style_sub_sport_type;
            }
            break;

        case 0x05:
            {
                Repofree_Sport_Data_Type_V5 *p_free_sport_repo_data;
                p_free_sport_repo_data = p_input_data;
                *sub_sport_type = p_free_sport_repo_data->data_s.free_style_sub_sport_type;
            }
            break;

        case 0x08:
            {
                Repofree_Sport_Data_Type_V8 *p_free_sport_repo_data;
                p_free_sport_repo_data = p_input_data;
                *sub_sport_type = p_free_sport_repo_data->data_s.free_style_sub_sport_type;
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

const static ms_common_sport_handle_v1_t MUL_SPORT_POSSIBLY_UNUSED g_ms_sport_category_t4_v1_handle = {
    .sport_handle.magic_number            = MUL_SPORT_MAGIC_NUMBER,
    .sport_handle.version                 = MUL_SPORT_VER_1,

    .sport_handle.sport_category          = MS_SPORT_CATEGORY_T4,
    .sport_handle.sport_category_ver      = MS_SPORT_CATEGORY_T4_V1,
    
    .sport_handle.data_ver                = MS_SPORT_CATEGORY_T4_V1_DATA_VER,
    .sport_handle.repo_ver                = MS_SPORT_CATEGORY_T4_V1_REPO_VER,

    .sport_handle.is_record_per_sec       = true,

    .sport_handle.sport_fixed_data_len    = MS_SPORT_CATEGORY_T4_V1_FIXED_BYTES,

    .sport_handle.pf_get_sport_data       = MS_GET_FUNC(get_free_sport_data_v, MS_SPORT_CATEGORY_T4_V1_DATA_VER),
    .sport_handle.pf_get_sport_fixed_data = MS_GET_FUNC(get_free_sport_fixed_data_v, MS_SPORT_CATEGORY_T4_V1_DATA_VER),
    .sport_handle.pf_get_sport_repo       = MS_GET_FUNC(get_free_sport_repo_v, MS_SPORT_CATEGORY_T4_V1_REPO_VER),
    .sport_handle.pf_set_sport_data       = NULL,
    .sport_handle.pf_set_sport_repo       = NULL,
};


//-=-=
//

p_ms_abstract_sport_handle_t MUL_SPORT_POSSIBLY_UNUSED get_ms_sport_category_t4_v1(void)
{
    return (p_ms_abstract_sport_handle_t)&g_ms_sport_category_t4_v1_handle;
}

//-=-=
//
const ms_common_sport_config_v1_t MUL_SPORT_POSSIBLY_UNUSED g_free_sport_config = {
    .sport_config.magic_number         = MUL_SPORT_MAGIC_NUMBER,
    .sport_config.version              = MUL_SPORT_VER_1,

    .sport_config.sport_category       = MS_SPORT_CATEGORY_T4,
    .sport_config.sport_category_ver   = MS_SPORT_CATEGORY_T4_V1,

    .sport_config.is_gps_sport         = false,

    .sport_config.sport_type           = ST_FREE_SPORT,
};

#endif /* FLASH_MANAGER_SWITCH */

