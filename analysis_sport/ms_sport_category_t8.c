#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#include "ms_sport_category_t8.h"

#include <stdio.h>
#include <string.h>
#include "mul_sport_data_struct.h"
#include "mul_sport_platform.h"
#include "mul_sport_ver_def.h"
#include "multi_motion_sport_handle.h"

#define MS_SPORT_CATEGORY_T8_V1_FIXED_BYTES         9      // 椭圆机

const uint8_t MUL_SPORT_ALIGN_WAY g_sport_point_header_t8_v1_buf[] = {0x00, 0xEC};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_point_header_t8_v2_buf[] = {0x00, 0xEC};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_point_header_t8_v3_buf[] = {0x00, 0xEC,0xC0};

const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t8_v1_buf[] = {0x00, 0xFF, 0x8F, 0x80};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t8_v3_buf[] = {0x00, 0xFF, 0x8F, 0xC3, 0x10};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t8_v5_buf[] = {0x00, 0xFF, 0x87, 0xE0, 0xE4};
//-=-=
// V1
static bool MUL_SPORT_POSSIBLY_UNUSED get_elliptical_machine_data_v1(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Elliptical_Machine_Data_Type_V1 elliptical_machine_data;

    memset(&elliptical_machine_data, 0, sizeof(elliptical_machine_data));

    elliptical_machine_data.data_s.data_body.extra_calorie.ec_s.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();
    elliptical_machine_data.data_s.data_body.extra_calorie.ec_s.extra_step = mul_sport_get_cyclic_sport_counter() - multi_motion_get_prev_cyclic_sport_counter();

    elliptical_machine_data.data_s.data_body.hr = mul_sport_get_sport_heart_rate();

    memcpy(p_output_data,
           (uint8_t *)&elliptical_machine_data.data_s.data_body,
           sizeof(elliptical_machine_data.data_s.data_body));

    *p_output_data_len = sizeof(elliptical_machine_data.data_s.data_body);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_elliptical_machine_fixed_data_v1(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Elliptical_Machine_Data_Type_V1 elliptical_machine_data;

    memset(&elliptical_machine_data, 0, sizeof(elliptical_machine_data));

    uint32_t mul_sport_cnt = get_mul_sport_cnt();

    elliptical_machine_data.data_s.data_head.restore_time = get_recovery_motion_timestamp();
    elliptical_machine_data.data_s.data_head.count_sport_hold =
            get_mul_sport_total_points_cnts() > mul_sport_cnt ?
                    get_mul_sport_total_points_cnts() - mul_sport_cnt : 0;

    set_mul_sport_cnt(get_mul_sport_total_points_cnts());

    memcpy(p_output_data,
           (uint8_t *)&elliptical_machine_data.data_s.data_head,
           sizeof(elliptical_machine_data.data_s.data_head));

    *p_output_data_len = sizeof(elliptical_machine_data.data_s.data_head);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_elliptical_machine_repo_v1(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Elliptical_Machine_Data_Type_V1 elliptical_machine_repo_data;

    memset(&elliptical_machine_repo_data, 0, sizeof(elliptical_machine_repo_data));

    elliptical_machine_repo_data.data_s.sport_start_time = get_mul_sport_start_time();

    elliptical_machine_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();

    elliptical_machine_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();

    elliptical_machine_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();
    elliptical_machine_repo_data.data_s.total_step = mul_sport_get_cyclic_sport_counter();

    elliptical_machine_repo_data.data_s.max_step_rate = mul_sport_get_max_cyclic_sport_counter();

    elliptical_machine_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    elliptical_machine_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();

    elliptical_machine_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();

    elliptical_machine_repo_data.data_s.training_effect = 0x00;
    elliptical_machine_repo_data.data_s.body_power_use = 0x00;
    elliptical_machine_repo_data.data_s.recover_time = 0x00;

    elliptical_machine_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    elliptical_machine_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    elliptical_machine_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    elliptical_machine_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    elliptical_machine_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();
    elliptical_machine_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();

    memcpy(p_output_data,
           (uint8_t *)&elliptical_machine_repo_data.data_s,
           sizeof(elliptical_machine_repo_data.data_s));

    *p_output_data_len = sizeof(elliptical_machine_repo_data.data_s);

    return true;
}

//-=-=
// V2
static bool MUL_SPORT_POSSIBLY_UNUSED get_elliptical_machine_data_v2(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Elliptical_Machine_Data_Type_V2 elliptical_machine_data;

    memset(&elliptical_machine_data, 0, sizeof(elliptical_machine_data));

    elliptical_machine_data.data_s.data_body.extra_calorie.ec_s.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();
    elliptical_machine_data.data_s.data_body.extra_calorie.ec_s.extra_step = mul_sport_get_cyclic_sport_counter() - multi_motion_get_prev_cyclic_sport_counter();

    elliptical_machine_data.data_s.data_body.hr = mul_sport_get_sport_heart_rate();

    memcpy(p_output_data,
           (uint8_t *)&elliptical_machine_data.data_s.data_body,
           sizeof(elliptical_machine_data.data_s.data_body));

    *p_output_data_len = sizeof(elliptical_machine_data.data_s.data_body);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_elliptical_machine_fixed_data_v2(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Elliptical_Machine_Data_Type_V2 elliptical_machine_data;

    memset(&elliptical_machine_data, 0, sizeof(elliptical_machine_data));

    uint32_t mul_sport_cnt = get_mul_sport_cnt();

    elliptical_machine_data.data_s.data_head.restore_time = get_recovery_motion_timestamp();
    elliptical_machine_data.data_s.data_head.count_sport_hold =
            get_mul_sport_total_points_cnts() > mul_sport_cnt ?
                    get_mul_sport_total_points_cnts() - mul_sport_cnt : 0;

    set_mul_sport_cnt(get_mul_sport_total_points_cnts());


    if (get_is_change_sit_type() == true && get_sport_sit_type() != SIT_NONE)
    {
        elliptical_machine_data.data_s.data_head.segment_type.st_s.segment_type = 1;
        elliptical_machine_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();

        set_sport_sit_type(get_sport_next_sit_type());
    }
    else
    {
        elliptical_machine_data.data_s.data_head.segment_type.st_s.segment_type = 0;
        elliptical_machine_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();
    }

    set_is_change_sit_type(false);


    memcpy(p_output_data,
           (uint8_t *)&elliptical_machine_data.data_s.data_head,
           sizeof(elliptical_machine_data.data_s.data_head));

    *p_output_data_len = sizeof(elliptical_machine_data.data_s.data_head);

    return true;
}

//-=-=
// V3
static bool MUL_SPORT_POSSIBLY_UNUSED get_elliptical_machine_repo_v3(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Elliptical_Machine_Data_Type_V3 elliptical_machine_repo_data;

    memset(&elliptical_machine_repo_data, 0, sizeof(elliptical_machine_repo_data));

    elliptical_machine_repo_data.data_s.sport_start_time = get_mul_sport_start_time();

    elliptical_machine_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();

    elliptical_machine_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();

    elliptical_machine_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();
    elliptical_machine_repo_data.data_s.total_step = mul_sport_get_cyclic_sport_counter();

    elliptical_machine_repo_data.data_s.max_step_rate = mul_sport_get_max_cyclic_sport_counter();

    elliptical_machine_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    elliptical_machine_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();

    elliptical_machine_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();

    elliptical_machine_repo_data.data_s.training_effect = 0x00;
    elliptical_machine_repo_data.data_s.body_power_use = 0x00;
    elliptical_machine_repo_data.data_s.recover_time = 0x00;

    elliptical_machine_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    elliptical_machine_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    elliptical_machine_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    elliptical_machine_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    elliptical_machine_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();
    elliptical_machine_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();

    elliptical_machine_repo_data.data_s.valid_exercise_time = 0;
    elliptical_machine_repo_data.data_s.anaerobic_training_effect = 0;
    elliptical_machine_repo_data.data_s.designated_courses = 0;
    elliptical_machine_repo_data.data_s.hr_zone_selection = 0;
    elliptical_machine_repo_data.data_s.target_duration = mul_sport_get_target_duration();
    elliptical_machine_repo_data.data_s.target_calorie = mul_sport_get_target_calorie();
    elliptical_machine_repo_data.data_s.target_cadence = mul_sport_get_target_cadence();

    memcpy(p_output_data,
           (uint8_t *)&elliptical_machine_repo_data.data_s,
           sizeof(elliptical_machine_repo_data.data_s));

    *p_output_data_len = sizeof(elliptical_machine_repo_data.data_s);

    return true;
}

//-=-=
// V3
static bool MUL_SPORT_POSSIBLY_UNUSED get_elliptical_machine_data_v3(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Elliptical_Machine_Data_Type_V3 elliptical_machine_data;

    memset(&elliptical_machine_data, 0, sizeof(elliptical_machine_data));

    elliptical_machine_data.data_s.data_body.extra_calorie.ec_s.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();
    elliptical_machine_data.data_s.data_body.extra_calorie.ec_s.extra_step = mul_sport_get_cyclic_sport_counter() - multi_motion_get_prev_cyclic_sport_counter();

    elliptical_machine_data.data_s.data_body.hr = mul_sport_get_sport_heart_rate();
    elliptical_machine_data.data_s.data_body.cadence = mul_sport_get_sport_rm_frequency();//mul_sport_get_sport_step_frequency(); 
    memcpy(p_output_data,
           (uint8_t *)&elliptical_machine_data.data_s.data_body,
           sizeof(elliptical_machine_data.data_s.data_body));

    *p_output_data_len = sizeof(elliptical_machine_data.data_s.data_body);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_elliptical_machine_fixed_data_v3(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Elliptical_Machine_Data_Type_V3 elliptical_machine_data;

    memset(&elliptical_machine_data, 0, sizeof(elliptical_machine_data));

    uint32_t mul_sport_cnt = get_mul_sport_cnt();

    elliptical_machine_data.data_s.data_head.restore_time = get_recovery_motion_timestamp();
    elliptical_machine_data.data_s.data_head.count_sport_hold =
            get_mul_sport_total_points_cnts() > mul_sport_cnt ?
                    get_mul_sport_total_points_cnts() - mul_sport_cnt : 0;

    set_mul_sport_cnt(get_mul_sport_total_points_cnts());


    if (get_is_change_sit_type() == true && get_sport_sit_type() != SIT_NONE)
    {
        elliptical_machine_data.data_s.data_head.segment_type.st_s.segment_type = 1;
        elliptical_machine_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();

        set_sport_sit_type(get_sport_next_sit_type());
    }
    else
    {
        elliptical_machine_data.data_s.data_head.segment_type.st_s.segment_type = 0;
        elliptical_machine_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();
    }

    set_is_change_sit_type(false);


    memcpy(p_output_data,
           (uint8_t *)&elliptical_machine_data.data_s.data_head,
           sizeof(elliptical_machine_data.data_s.data_head));

    *p_output_data_len = sizeof(elliptical_machine_data.data_s.data_head);

    return true;
}

//-=-=
// V5
static bool MUL_SPORT_POSSIBLY_UNUSED get_elliptical_machine_repo_v5(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Elliptical_Machine_Data_Type_V5 elliptical_machine_repo_data;

    memset(&elliptical_machine_repo_data, 0, sizeof(elliptical_machine_repo_data));

    elliptical_machine_repo_data.data_s.sport_start_time = get_mul_sport_start_time();

    elliptical_machine_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();

    elliptical_machine_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();

    elliptical_machine_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();
    elliptical_machine_repo_data.data_s.total_step = mul_sport_get_cyclic_sport_counter();

    elliptical_machine_repo_data.data_s.max_step_rate = mul_sport_get_max_cyclic_sport_counter();

    elliptical_machine_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    elliptical_machine_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();

    elliptical_machine_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();

    elliptical_machine_repo_data.data_s.training_effect = 0x00;
    elliptical_machine_repo_data.data_s.training_effect_rate = 0x00;
    elliptical_machine_repo_data.data_s.body_power_use = 0x00;
    elliptical_machine_repo_data.data_s.recover_time = 0x00;

    elliptical_machine_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    elliptical_machine_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    elliptical_machine_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    elliptical_machine_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    elliptical_machine_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();
    elliptical_machine_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();

    elliptical_machine_repo_data.data_s.valid_exercise_time = 0;
    elliptical_machine_repo_data.data_s.anaerobic_training_effect = 0;
    elliptical_machine_repo_data.data_s.anaerobic_training_effect_rate = 0x00;
    elliptical_machine_repo_data.data_s.designated_courses = 0;
    elliptical_machine_repo_data.data_s.hr_zone_selection = 0;
    elliptical_machine_repo_data.data_s.target_duration = mul_sport_get_target_duration();
    elliptical_machine_repo_data.data_s.target_calorie = mul_sport_get_target_calorie();
    elliptical_machine_repo_data.data_s.target_cadence = mul_sport_get_target_cadence();
    elliptical_machine_repo_data.data_s.tarining_load = 0x00;
    elliptical_machine_repo_data.data_s.traing_load_rate = 0x00;
    elliptical_machine_repo_data.data_s.genki_value = mul_sport_get_sport_genki_value();
    memcpy(p_output_data,
           (uint8_t *)&elliptical_machine_repo_data.data_s,
           sizeof(elliptical_machine_repo_data.data_s));

    *p_output_data_len = sizeof(elliptical_machine_repo_data.data_s);

    return true;
}

//-=-=
//

const static ms_common_sport_handle_v1_t MUL_SPORT_POSSIBLY_UNUSED g_ms_sport_category_t8_v1_handle = {
    .sport_handle.magic_number            = MUL_SPORT_MAGIC_NUMBER,
    .sport_handle.version                 = MUL_SPORT_VER_1,

    .sport_handle.sport_category          = MS_SPORT_CATEGORY_T8,
    .sport_handle.sport_category_ver      = MS_SPORT_CATEGORY_T8_V1,
    
    .sport_handle.data_ver                = MS_SPORT_CATEGORY_T8_V1_DATA_VER,
    .sport_handle.repo_ver                = MS_SPORT_CATEGORY_T8_V1_REPO_VER,

    .sport_handle.is_record_per_sec       = true,
    
    .sport_handle.sport_fixed_data_len    = MS_SPORT_CATEGORY_T8_V1_FIXED_BYTES,

    .sport_handle.pf_get_sport_data       = MS_GET_FUNC(get_elliptical_machine_data_v, MS_SPORT_CATEGORY_T8_V1_DATA_VER),
    .sport_handle.pf_get_sport_fixed_data = MS_GET_FUNC(get_elliptical_machine_fixed_data_v, MS_SPORT_CATEGORY_T8_V1_DATA_VER),
    .sport_handle.pf_get_sport_repo       = MS_GET_FUNC(get_elliptical_machine_repo_v, MS_SPORT_CATEGORY_T8_V1_REPO_VER),
    .sport_handle.pf_set_sport_data       = NULL,
    .sport_handle.pf_set_sport_repo       = NULL,
};

//-=-=
//

p_ms_abstract_sport_handle_t MUL_SPORT_POSSIBLY_UNUSED get_ms_sport_category_t8_v1(void)
{
    return (p_ms_abstract_sport_handle_t)&g_ms_sport_category_t8_v1_handle;
}

//-=-=
// get header func
static void get_ms_sport_category_t8_point_header(uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (version)
    {
        case 0x01:
            *pp_header_data = (uint8_t *)g_sport_point_header_t8_v1_buf;
            *p_data_len = sizeof(g_sport_point_header_t8_v1_buf);
            break;

        case 0x02:
            *pp_header_data = (uint8_t *)g_sport_point_header_t8_v2_buf;
            *p_data_len = sizeof(g_sport_point_header_t8_v2_buf);
            break;

        case 0x03:
            *pp_header_data = (uint8_t *)g_sport_point_header_t8_v3_buf;
            *p_data_len = sizeof(g_sport_point_header_t8_v3_buf);
            break;

        default:
            break;
    }
}

static void get_ms_sport_category_t8_report_header(uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (version)
    {
        case 0x01:
            *pp_header_data = (uint8_t *)g_sport_report_header_t8_v1_buf;
            *p_data_len = sizeof(g_sport_report_header_t8_v1_buf);
            break;

        case 0x03:
            *pp_header_data = (uint8_t *)g_sport_report_header_t8_v3_buf;
            *p_data_len = sizeof(g_sport_report_header_t8_v3_buf);
            break;

        case 0x05:
            *pp_header_data = (uint8_t *)g_sport_report_header_t8_v5_buf;
            *p_data_len = sizeof(g_sport_report_header_t8_v5_buf);
            break;

        default:
            break;
    }
}

void get_ms_sport_category_t8_data_header(uint8_t data_type, uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (data_type)
    {
        case ENUM_POINT_DATA_T:
            get_ms_sport_category_t8_point_header(version, pp_header_data, p_data_len);
            break;

        case ENUM_REPORT_DATA_T:
            get_ms_sport_category_t8_report_header(version, pp_header_data, p_data_len);
            break;

        default:
            break;
    }
}

//-=-=
//
bool get_ms_sport_category_t8_record_info(uint8_t version, ms_record_info_t *p_record_info)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x03:
            {
                p_record_info->data_head_len = sizeof(((Elliptical_Machine_Data_Type_V3 *)NULL)->data_s.data_head);
                p_record_info->data_body_len = sizeof(((Elliptical_Machine_Data_Type_V3 *)NULL)->data_s.data_body);
            }
            break;

        default:
            ret_rst = false;
            break;
    }

    return ret_rst;
}

bool get_ms_sport_category_t8_record_head(uint8_t version, uint8_t *p_input_read_buf, ms_record_head_t *p_record_head)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x03:
            {
                Elliptical_Machine_Data_Type_V3 *_ = (Elliptical_Machine_Data_Type_V3 *)p_input_read_buf;

                p_record_head->count_sport_hold = _->data_s.data_head.count_sport_hold;
            }
            break;

        default:
            ret_rst = false;
            break;
    }

    return ret_rst;
}

bool get_ms_sport_category_t8_record_body(uint8_t version, uint8_t *p_input_read_buf, ms_record_item_t *p_record_item)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x03:
            {
                Elliptical_Machine_Data_Type_V3 *_ = (Elliptical_Machine_Data_Type_V3 *)p_input_read_buf;

                p_record_item->elliptical_m.hr      = _->data_s.data_body.hr;
                p_record_item->elliptical_m.cadence = _->data_s.data_body.cadence;
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
const ms_common_sport_config_v1_t MUL_SPORT_POSSIBLY_UNUSED g_elliptical_machine_config = {
    .sport_config.magic_number         = MUL_SPORT_MAGIC_NUMBER,
    .sport_config.version              = MUL_SPORT_VER_1,

    .sport_config.sport_category       = MS_SPORT_CATEGORY_T8,
    .sport_config.sport_category_ver   = MS_SPORT_CATEGORY_T8_V1,

    .sport_config.is_gps_sport         = false,

    .sport_config.sport_type           = ST_ELLIPTICAL_MACHINE,
};

#endif /* FLASH_MANAGER_SWITCH */
