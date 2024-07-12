#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#include "ms_sport_category_t5.h"

#include <stdio.h>
#include <string.h>
#include "mul_sport_data_struct.h"
#include "mul_sport_platform.h"
#include "mul_sport_ver_def.h"
#include "multi_motion_sport_handle.h"



#define MS_SPORT_CATEGORY_T5_V1_FIXED_BYTES             8      // 游泳/开放泳池游泳

const uint8_t MUL_SPORT_ALIGN_WAY g_sport_point_header_t5_v2_buf[] = {0x00, 0xFF, 0xFF};
const uint8_t MUL_SPORT_ALIGN_WAY g_sport_report_header_t5_v6_buf[] = {0x00, 0xFE, 0x7F, 0xBE, 0x04};
#if 0
static Swimming_Data_Type_V1         MUL_SPORT_ALIGN_WAY g_swimming_data;
static Report_Swimming_Data_Type_V1  MUL_SPORT_ALIGN_WAY g_swimming_repo_data;
#else
static Swimming_Data_Type_V2         MUL_SPORT_ALIGN_WAY g_swimming_data;
static Report_Swimming_Data_Type_V6  MUL_SPORT_ALIGN_WAY g_swimming_repo_data;
#endif
//-=-=
// V1
static bool MUL_SPORT_POSSIBLY_UNUSED get_swimming_sport_data_v2(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Swimming_Data_Type_V2    swimming_data;

    memset(&swimming_data, 0, sizeof(swimming_data));    

    swimming_data = g_swimming_data;

    // printf("sw_func_cb t5 point af %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
    //        swimming_data.data_s.data_body.section_data.data_type,
    //        swimming_data.data_s.data_body.section_data.timestamp,
    //        swimming_data.data_s.data_body.section_data.posture,
    //        swimming_data.data_s.data_body.section_data.pace,
    //        swimming_data.data_s.data_body.section_data.swolf,
    //        swimming_data.data_s.data_body.pull_rate,
    //        swimming_data.data_s.data_body.total_distance,
    //        swimming_data.data_s.data_body.sport_calorie,
    //        swimming_data.data_s.data_body.total_calorie,
    //        swimming_data.data_s.data_body.total_pull_count,
    //        swimming_data.data_s.data_body.total_turn_count);

    //     "数据类型
    // 0）小节；1）段落；2）计圈分段"		
    if(swimming_data.data_s.data_body.section_data.data_type == 0)
    {
        memcpy(p_output_data,
            (uint8_t *)&swimming_data.data_s.data_body,
            sizeof(swimming_data.data_s.data_body));

        *p_output_data_len = sizeof(swimming_data.data_s.data_body);
    }
    else
    {
         memcpy(p_output_data,
            (uint8_t *)&swimming_data.data_s.data_body.section_data,
            sizeof(swimming_data.data_s.data_body.section_data));

        *p_output_data_len = sizeof(swimming_data.data_s.data_body.section_data);       
    }

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_swimming_sport_fixed_data_v2(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Swimming_Data_Type_V2        swimming_data;

    memset(&swimming_data, 0, sizeof(swimming_data));

    uint32_t swimming_turn_cnt = get_swimming_turn_cnt();

    swimming_data.data_s.data_head.restore_time = get_recovery_motion_timestamp();

    swimming_data.data_s.data_head.count_sport_hold       =
                mul_sport_get_swimming_turn_cnt() > swimming_turn_cnt ?
                        mul_sport_get_swimming_turn_cnt() - swimming_turn_cnt : 0;

    set_swimming_turn_cnt(mul_sport_get_swimming_turn_cnt());

    memcpy(p_output_data,
           (uint8_t *)&swimming_data.data_s.data_head,
           sizeof(swimming_data.data_s.data_head));

    *p_output_data_len = sizeof(swimming_data.data_s.data_head);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_swimming_sport_repo_v6(void *p_output_data, uint32_t *p_output_data_len)
{
    if (!p_output_data || !p_output_data_len)
    {
        return false;
    }

    Report_Swimming_Data_Type_V6 swimming_repo_data;

    memset(&swimming_repo_data, 0, sizeof(swimming_repo_data));

    /* XXX: 时间和计数我这边来赋值 */
    g_swimming_repo_data.data_s.sport_start_time = get_mul_sport_start_time();
    g_swimming_repo_data.data_s.sport_stop_time = get_mul_sport_end_time();
    g_swimming_repo_data.data_s.sport_total_time = mul_sport_get_sport_time_count();
    g_swimming_repo_data.data_s.target_calorie = mul_sport_get_target_calorie();
    g_swimming_repo_data.data_s.target_distance = mul_sport_get_target_distance();
    g_swimming_repo_data.data_s.target_time = mul_sport_get_target_duration();
    g_swimming_repo_data.data_s.target_times = mul_sport_get_target_times();//趟数
    
    // printf("sw_func_cb t5 sport t=%d,s_t=%d,t_t=%d\n", g_swimming_repo_data.data_s.sport_start_time, g_swimming_repo_data.data_s.sport_stop_time, g_swimming_repo_data.data_s.sport_total_time);

    swimming_repo_data = g_swimming_repo_data;

    memcpy(p_output_data,
           (uint8_t *)&swimming_repo_data.data_s,
           sizeof(swimming_repo_data.data_s));

    *p_output_data_len = sizeof(swimming_repo_data.data_s);

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED set_swimming_sport_data_v2(void *p_input_data, void *p_input_data_args)
{
    if (!p_input_data)
    {
        return false;
    }

    Swimming_Data_Type_V2    *p_input_swimming_data = (Swimming_Data_Type_V2 *)p_input_data;

    g_swimming_data.data_s.data_body = p_input_swimming_data->data_s.data_body;

    return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED set_swimming_sport_repo_v6(void *p_input_data, void *p_input_data_args)
{
    if (!p_input_data)
    {
        return false;
    }

    Report_Swimming_Data_Type_V6    *p_input_swimming_data = (Report_Swimming_Data_Type_V6 *)p_input_data;

    g_swimming_repo_data.data_s = p_input_swimming_data->data_s;

    return true;
}

//-=-=
// get header func
static void get_ms_sport_category_t5_point_header(uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (version)
    {
        case 0x02:
            *pp_header_data = (uint8_t *)g_sport_point_header_t5_v2_buf;
            *p_data_len = sizeof(g_sport_point_header_t5_v2_buf);
            break;

        default:
            break;
    }
}

static void get_ms_sport_category_t5_report_header(uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (version)
    {
        case 0x06:
            *pp_header_data = (uint8_t *)g_sport_report_header_t5_v6_buf;
            *p_data_len = sizeof(g_sport_report_header_t5_v6_buf);
            break;

        default:
            break;
    }
}

void get_ms_sport_category_t5_data_header(uint8_t data_type, uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (data_type)
    {
        case ENUM_POINT_DATA_T:
            get_ms_sport_category_t5_point_header(version, pp_header_data, p_data_len);
            break;

        case ENUM_REPORT_DATA_T:
            get_ms_sport_category_t5_report_header(version, pp_header_data, p_data_len);
            break;

        default:
            break;
    }
}

//-=-=
//
bool get_ms_sport_category_t5_record_info(uint8_t version, ms_record_info_t *p_record_info)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x02:
            {
                p_record_info->data_head_len    = sizeof(((Swimming_Data_Type_V2 *)NULL)->data_s.data_head);
                p_record_info->data_body_len    = sizeof(((Swimming_Data_Type_V2 *)NULL)->data_s.data_body);
                p_record_info->data_section_len = sizeof(((Swimming_Data_Type_V2 *)NULL)->data_s.data_body.section_data);
            }
            break;

        default:
            ret_rst = false;
            break;
    }

    return ret_rst;
}

bool get_ms_sport_category_t5_record_head(uint8_t version, uint8_t *p_input_read_buf, ms_record_head_t *p_record_head)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x02:
            {
                Swimming_Data_Type_V2 *_ = (Swimming_Data_Type_V2 *)p_input_read_buf;

                p_record_head->count_sport_hold = _->data_s.data_head.count_sport_hold;
            }
            break;

        default:
            ret_rst = false;
            break;
    }

    return ret_rst;
}

bool get_ms_sport_category_t5_record_body(uint8_t version, uint8_t *p_input_read_buf, ms_record_item_t *p_record_item)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x02:
            {
                Swimming_Data_Type_V2 *_ = (Swimming_Data_Type_V2 *)p_input_read_buf;

                p_record_item->swimming.pace      = _->data_s.data_body.section_data.pace;
                p_record_item->swimming.swolf     = _->data_s.data_body.section_data.swolf;
                p_record_item->swimming.pull_rate = _->data_s.data_body.pull_rate;
            }
            break;

        default:
            ret_rst = false;
            break;
    }

    return ret_rst;
}

bool get_ms_sport_category_t5_record_is_detail_body(uint8_t version, uint8_t *p_input_read_buf)
{
    bool ret_rst = true;

    switch (version)
    {
        case 0x02:
            {
                Swimming_Data_Type_V2 *_ = (Swimming_Data_Type_V2 *)p_input_read_buf;

                if (_->data_s.data_body.section_data.data_type == 0)
                {
                    ret_rst = true;
                }
                else
                {
                    ret_rst = false;
                }
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

const static ms_common_sport_handle_v1_t MUL_SPORT_POSSIBLY_UNUSED g_ms_sport_category_t5_v1_handle = {
    .sport_handle.magic_number            = MUL_SPORT_MAGIC_NUMBER,
    .sport_handle.version                 = MUL_SPORT_VER_1,

    .sport_handle.sport_category          = MS_SPORT_CATEGORY_T5,
    .sport_handle.sport_category_ver      = MS_SPORT_CATEGORY_T5_V1,
    
    .sport_handle.data_ver                = MS_SPORT_CATEGORY_T5_V1_DATA_VER,
    .sport_handle.repo_ver                = MS_SPORT_CATEGORY_T5_V1_REPO_VER,

    .sport_handle.is_record_per_sec       = false,

    .sport_handle.sport_fixed_data_len    = MS_SPORT_CATEGORY_T5_V1_FIXED_BYTES,

    .sport_handle.pf_get_sport_data       = MS_GET_FUNC(get_swimming_sport_data_v, MS_SPORT_CATEGORY_T5_V1_DATA_VER),
    .sport_handle.pf_get_sport_fixed_data = MS_GET_FUNC(get_swimming_sport_fixed_data_v, MS_SPORT_CATEGORY_T5_V1_DATA_VER),
    .sport_handle.pf_get_sport_repo       = MS_GET_FUNC(get_swimming_sport_repo_v, MS_SPORT_CATEGORY_T5_V1_REPO_VER),
    .sport_handle.pf_set_sport_data       = MS_GET_FUNC(set_swimming_sport_data_v, MS_SPORT_CATEGORY_T5_V1_DATA_VER),
    .sport_handle.pf_set_sport_repo       = MS_GET_FUNC(set_swimming_sport_repo_v, MS_SPORT_CATEGORY_T5_V1_REPO_VER),
};

//-=-=
//

p_ms_abstract_sport_handle_t MUL_SPORT_POSSIBLY_UNUSED get_ms_sport_category_t5_v1(void)
{
    return (p_ms_abstract_sport_handle_t)&g_ms_sport_category_t5_v1_handle;
}

//-=-=
//

const ms_common_sport_config_v1_t MUL_SPORT_POSSIBLY_UNUSED g_indoor_swimming_h_config = {
    .sport_config.magic_number         = MUL_SPORT_MAGIC_NUMBER,
    .sport_config.version              = MUL_SPORT_VER_1,

    .sport_config.is_gps_sport         = false,

    .sport_config.sport_category       = MS_SPORT_CATEGORY_T5,
    .sport_config.sport_category_ver   = MS_SPORT_CATEGORY_T5_V1,

    .sport_config.sport_type           = ST_SWIM_INDOOR,
};

const ms_common_sport_config_v1_t MUL_SPORT_POSSIBLY_UNUSED g_outside_swimming_h_config = {
    .sport_config.magic_number         = MUL_SPORT_MAGIC_NUMBER,
    .sport_config.version              = MUL_SPORT_VER_1,

    .sport_config.sport_category       = MS_SPORT_CATEGORY_T5,
    .sport_config.sport_category_ver   = MS_SPORT_CATEGORY_T5_V1,

    .sport_config.is_gps_sport         = true,

    .sport_config.gps_ver              = MS_SPORT_CATEGORY_T5_V1_GPS_VER,

    .sport_config.sport_type           = ST_SWIM_OUTDOOR,
};

#endif /* FLASH_MANAGER_SWITCH */
