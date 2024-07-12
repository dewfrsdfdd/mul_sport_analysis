#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#include "ms_sport_category_t10.h"

#include <stdio.h>
#include <string.h>
#include "mul_sport_data_struct.h"
#include "mul_sport_platform.h"
#include "mul_sport_ver_def.h"
#include "multi_motion_sport_handle.h"

#define MS_SPORT_CATEGORY_T10_V1_FIXED_BYTES         17      // 户外非跑走类

const uint8_t MUL_SPORT_ALIGN_WAY g_sport_point_header_t10_v3_buf[] = {0x00, 0xCC, 0xCC,0xC0};

const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t10_v4_buf[] = {0x00, 0xF7, 0xFC, 0x00, 0x0F, 0xF8,0x10};


//-=-=
// V4
static bool MUL_SPORT_POSSIBLY_UNUSED get_outside_non_running_category_repo_v4(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Outside_Non_Running_Data_Type_V4 outside_non_running_repo_data;
    memset(&outside_non_running_repo_data, 0, sizeof(outside_non_running_repo_data));
    outside_non_running_repo_data.data_s.non_running_style_sub_sport_type = get_sub_sport_type();
    outside_non_running_repo_data.data_s.sport_start_time = get_mul_sport_start_time();
    outside_non_running_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();
    outside_non_running_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();
    outside_non_running_repo_data.data_s.valid_exercise_time = 0x0;
    outside_non_running_repo_data.data_s.sport_total_distance = mul_sport_get_sport_distance();
    outside_non_running_repo_data.data_s.total_calorie = mul_sport_get_sport_total_consume();
    outside_non_running_repo_data.data_s.sport_calorie = mul_sport_get_sport_consume();
    outside_non_running_repo_data.data_s.high_speed = mul_sport_get_sport_maximum_speed_distribution();

    outside_non_running_repo_data.data_s.low_speed = mul_sport_get_sport_minimum_speed_distribution();

    outside_non_running_repo_data.data_s.fast_speed = mul_sport_get_sport_limit_speed();
    outside_non_running_repo_data.data_s.avg_hr = mul_sport_get_sport_avg_heart_rate();
    outside_non_running_repo_data.data_s.max_hr = mul_sport_get_sport_maximum_heart_rate();

    outside_non_running_repo_data.data_s.min_hr = mul_sport_get_sport_minimum_heart_rate();
    outside_non_running_repo_data.data_s.total_up = mul_sport_get_total_up();
    outside_non_running_repo_data.data_s.total_down = mul_sport_get_total_down();
    outside_non_running_repo_data.data_s.avg_height = mul_sport_get_avg_height();
    outside_non_running_repo_data.data_s.max_height = mul_sport_get_max_height();
    outside_non_running_repo_data.data_s.min_height = mul_sport_get_min_height();
    outside_non_running_repo_data.data_s.training_effect = 0x00;
    outside_non_running_repo_data.data_s.training_effect_rating = 0x00;
    outside_non_running_repo_data.data_s.anaerobic_training_effect = 0x00;
    outside_non_running_repo_data.data_s.anaerobic_training_effect_rate = 0x00;
    outside_non_running_repo_data.data_s.max_oxygen_uptake = 0x00;
    outside_non_running_repo_data.data_s.max_oxygen_uptake_rate = 0x00;
    outside_non_running_repo_data.data_s.body_power_use = 0x00;
    outside_non_running_repo_data.data_s.recover_time = 0x00;
    outside_non_running_repo_data.data_s.hr_zone_selection = 0x00;
    outside_non_running_repo_data.data_s.hr_limit_time = mul_sport_get_sport_heart_rate_limit_time();
    outside_non_running_repo_data.data_s.hr_without_oxygen = mul_sport_get_sport_heart_rate_without_oxygen_time();
    outside_non_running_repo_data.data_s.hr_with_oxygen = mul_sport_get_sport_heart_rate_with_oxygen_time();
    outside_non_running_repo_data.data_s.hr_expend_fat = mul_sport_get_sport_heart_rate_fat_burning_time();
    outside_non_running_repo_data.data_s.hr_warmup = mul_sport_get_sport_heart_rate_warming_up_time();
    outside_non_running_repo_data.data_s.target_duration = mul_sport_get_target_duration();
    outside_non_running_repo_data.data_s.target_calorie = mul_sport_get_target_calorie();
    outside_non_running_repo_data.data_s.target_distance = mul_sport_get_target_distance();
    outside_non_running_repo_data.data_s.target_speed = mul_sport_get_target_pace();
    outside_non_running_repo_data.data_s.designated_courses = 0x00;
    outside_non_running_repo_data.data_s.training_load = 0x00;
    outside_non_running_repo_data.data_s.training_load_rate = 0x00;
    outside_non_running_repo_data.data_s.running_power_index = 0x00;
    outside_non_running_repo_data.data_s.running_power_level = 0x00;  
    outside_non_running_repo_data.data_s.train_state = 0x00;
    outside_non_running_repo_data.data_s.genki_value = mul_sport_get_sport_genki_value();
    outside_non_running_repo_data.data_s.avg_cadence = 0x00;
    outside_non_running_repo_data.data_s.max_cadence = 0x00;

    memcpy(p_output_data,
           (uint8_t *)&outside_non_running_repo_data.data_s,
           sizeof(outside_non_running_repo_data.data_s));

    *p_output_data_len = sizeof(outside_non_running_repo_data.data_s);
    return true;
}

//-=-=
// V3
static bool MUL_SPORT_POSSIBLY_UNUSED get_outside_non_running_category_data_v3(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Outside_Non_Running_Data_Type_V3 outside_non_running_data;

    memset(&outside_non_running_data, 0, sizeof(outside_non_running_data));

    outside_non_running_data.data_s.data_body.extra_calorie.ec_s.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();
    outside_non_running_data.data_s.data_body.extra_calorie.ec_s.extra_count = 0;
    outside_non_running_data.data_s.data_body.hr = mul_sport_get_sport_heart_rate();
    outside_non_running_data.data_s.data_body.extra_distance                          =
                    (mul_sport_get_sport_distance() - multi_motion_get_prev_distance());
    outside_non_running_data.data_s.data_body.speed = mul_sport_get_sport_speed();
    // outside_non_running_data.data_s.data_body.cadence = 0;

    if (get_is_up_km_status())
    {
        outside_non_running_data.data_s.data_body.heigth_change.hc_s.is_km = 1;
        set_is_up_km_status(false);
    }
    else
    {
        outside_non_running_data.data_s.data_body.heigth_change.hc_s.is_km = 0;
    }

    memcpy(p_output_data,
           (uint8_t *)&outside_non_running_data.data_s.data_body,
           sizeof(outside_non_running_data.data_s.data_body));

    *p_output_data_len = sizeof(outside_non_running_data.data_s.data_body);
    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_outside_non_running_category_fixed_data_v3(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Outside_Non_Running_Data_Type_V3 outside_non_running_data;

    memset(&outside_non_running_data, 0, sizeof(outside_non_running_data));

    uint32_t mul_sport_cnt = get_mul_sport_cnt();

    outside_non_running_data.data_s.data_head.initialize_altitude = get_initialize_altitude();
    outside_non_running_data.data_s.data_head.restore_time        = get_recovery_motion_timestamp();
    outside_non_running_data.data_s.data_head.count_sport_hold         =
            get_mul_sport_total_points_cnts() > mul_sport_cnt ?
                    get_mul_sport_total_points_cnts() - mul_sport_cnt : 0;

    set_mul_sport_cnt(get_mul_sport_total_points_cnts());
    outside_non_running_data.data_s.data_head.segment_total_distance = get_mul_sport_segment_distance();
    set_mul_sport_segment_distance(0);

    if (get_is_change_sit_type() == true && get_sport_sit_type() != SIT_NONE)
    {
        outside_non_running_data.data_s.data_head.segment_type.st_s.segment_type = 1;
        outside_non_running_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();

        set_sport_sit_type(get_sport_next_sit_type());
    }
    else
    {
        outside_non_running_data.data_s.data_head.segment_type.st_s.segment_type = 0;
        outside_non_running_data.data_s.data_head.segment_type.st_s.training_type = get_sport_sit_type();
    }

    set_is_change_sit_type(false);


    memcpy(p_output_data,
           (uint8_t *)&outside_non_running_data.data_s.data_head,
           sizeof(outside_non_running_data.data_s.data_head));

    *p_output_data_len = sizeof(outside_non_running_data.data_s.data_head);
    return true;
}

//-=-=
//

const static ms_common_sport_handle_v1_t MUL_SPORT_POSSIBLY_UNUSED g_ms_sport_category_t10_v1_handle = {
    .sport_handle.magic_number            = MUL_SPORT_MAGIC_NUMBER,
    .sport_handle.version                 = MUL_SPORT_VER_1,
    
    .sport_handle.sport_category          = MS_SPORT_CATEGORY_T10,
    .sport_handle.sport_category_ver      = MS_SPORT_CATEGORY_T10_V1,
    
    .sport_handle.data_ver                = MS_SPORT_CATEGORY_T10_V3_DATA_VER,
    .sport_handle.repo_ver                = MS_SPORT_CATEGORY_T10_V4_REPO_VER,

    .sport_handle.is_record_per_sec       = true,

    .sport_handle.sport_fixed_data_len    = MS_SPORT_CATEGORY_T10_V1_FIXED_BYTES,

    .sport_handle.pf_get_sport_data       = MS_GET_FUNC(get_outside_non_running_category_data_v, MS_SPORT_CATEGORY_T10_V3_DATA_VER),
    .sport_handle.pf_get_sport_fixed_data = MS_GET_FUNC(get_outside_non_running_category_fixed_data_v, MS_SPORT_CATEGORY_T10_V3_DATA_VER),
    .sport_handle.pf_get_sport_repo       = MS_GET_FUNC(get_outside_non_running_category_repo_v, MS_SPORT_CATEGORY_T10_V4_REPO_VER),
    .sport_handle.pf_set_sport_data       = NULL,
    .sport_handle.pf_set_sport_repo       = NULL,
};

//-=-=
//

p_ms_abstract_sport_handle_t MUL_SPORT_POSSIBLY_UNUSED get_ms_sport_category_t10_v1(void)
{
    return (p_ms_abstract_sport_handle_t)&g_ms_sport_category_t10_v1_handle;
}

//-=-=
// get header func
static void get_ms_sport_category_t10_point_header(uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (version)
    {
        case 0x03:
            *pp_header_data = (uint8_t *)g_sport_point_header_t10_v3_buf;
            *p_data_len = sizeof(g_sport_point_header_t10_v3_buf);
            break;

        default:
            break;
    }
}

static void get_ms_sport_category_t10_report_header(uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{

    switch (version)
    {
        case 0x04:
            *pp_header_data = (uint8_t *)g_sport_report_header_t10_v4_buf;
            *p_data_len = sizeof(g_sport_report_header_t10_v4_buf);
            break;

        default:
            break;
    }
}

void get_ms_sport_category_t10_data_header(uint8_t data_type, uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (data_type)
    {
        case ENUM_POINT_DATA_T:
            get_ms_sport_category_t10_point_header(version, pp_header_data, p_data_len);
            break;

        case ENUM_REPORT_DATA_T:
            get_ms_sport_category_t10_report_header(version, pp_header_data, p_data_len);
            break;

        default:
            break;
    }
}

bool get_ms_sport_category_t10_sub_sport_type(uint8_t version, void *p_input_data, uint16_t *sub_sport_type)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x04:
            {
                Report_Outside_Run_Category_Data_Type_V4 *p_outside_run_category_repo_data;
                p_outside_run_category_repo_data = p_input_data;
                *sub_sport_type = p_outside_run_category_repo_data->data_s.sub_sport_type;
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
bool get_ms_sport_category_t10_record_info(uint8_t version, ms_record_info_t *p_record_info)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x03:
            {
                p_record_info->data_head_len = sizeof(((Outside_Non_Running_Data_Type_V3 *)NULL)->data_s.data_head);
                p_record_info->data_body_len = sizeof(((Outside_Non_Running_Data_Type_V3 *)NULL)->data_s.data_body);
            }
            break;

        default:
            ret_rst = false;
            break;
    }

    return ret_rst;    
}

bool get_ms_sport_category_t10_record_head(uint8_t version, uint8_t *p_input_read_buf, ms_record_head_t *p_record_head)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x03:
            {
                Outside_Non_Running_Data_Type_V3 *_ = (Outside_Non_Running_Data_Type_V3 *)p_input_read_buf;

                p_record_head->count_sport_hold = _->data_s.data_head.count_sport_hold;
            }
            break;

        default:
            ret_rst = false;
            break;
    }

    return ret_rst;
}

bool get_ms_sport_category_t10_record_body(uint8_t version, uint8_t *p_input_read_buf, ms_record_item_t *p_record_item)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x03:
            {
                Outside_Non_Running_Data_Type_V3 *_ = (Outside_Non_Running_Data_Type_V3 *)p_input_read_buf;

                p_record_item->out_non_run_c.hr    = _->data_s.data_body.hr;
                p_record_item->out_non_run_c.speed = _->data_s.data_body.speed;
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
const ms_common_sport_config_v1_t MUL_SPORT_POSSIBLY_UNUSED g_outside_non_running_category_config = {
    .sport_config.magic_number         = MUL_SPORT_MAGIC_NUMBER,
    .sport_config.version              = MUL_SPORT_VER_1,

    .sport_config.sport_category       = MS_SPORT_CATEGORY_T10,
    .sport_config.sport_category_ver   = MS_SPORT_CATEGORY_T10_V1,

    .sport_config.is_gps_sport         = true,

    .sport_config.gps_ver              = MS_SPORT_CATEGORY_T10_V1_GPS_VER,

    .sport_config.sport_type           = ST_OUTSIDE_NOT_RUN_CATEGORY,
};


#endif /* FLASH_MANAGER_SWITCH */
