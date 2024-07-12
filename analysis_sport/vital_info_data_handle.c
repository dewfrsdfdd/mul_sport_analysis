#include "vital_info_data_handle.h"
#if 0
#include "zh_data_global.h"

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
static vital_info_file_descriptor_t VITAL_INFO_ALIGN_WAY g_gensor_vital_info_file_descriptor;

p_vital_info_file_descriptor_t vital_info_get_gensor_file_descriptor(void)
{
    return &g_gensor_vital_info_file_descriptor;
}

static vital_info_file_descriptor_t VITAL_INFO_ALIGN_WAY g_log_vital_info_file_descriptor;

p_vital_info_file_descriptor_t vital_info_get_log_file_descriptor(void)
{
    return &g_log_vital_info_file_descriptor;
}

static vital_info_file_descriptor_t g_statistics_vital_info_file_descriptor;

p_vital_info_file_descriptor_t vital_info_get_statistics_file_descriptor(void)
{
    return &g_statistics_vital_info_file_descriptor;
}

static vital_info_file_descriptor_t VITAL_INFO_ALIGN_WAY g_vital_info_file_descriptor;

p_vital_info_file_descriptor_t vital_info_get_file_descriptor(void)
{
    return &g_vital_info_file_descriptor;
}

void vital_info_set_file_descriptor(vital_info_file_descriptor_t fd)
{
    g_vital_info_file_descriptor = fd;
}


static vital_info_file_resend_ctrl_t VITAL_INFO_ALIGN_WAY g_vital_info_file_resend_ctrl;

p_vital_info_file_resend_ctrl_t vital_info_get_file_resend_ctrl(void)
{
    return &g_vital_info_file_resend_ctrl;
}

void vital_info_init_file_resend_ctrl(void)
{
    memset(&g_vital_info_file_resend_ctrl, 0, sizeof(vital_info_file_resend_ctrl_t));
}

static vital_info_file_resend_ctrl_t VITAL_INFO_ALIGN_WAY g_log_file_resend_ctrl;

p_vital_info_file_resend_ctrl_t vital_info_get_log_file_resend_ctrl(void)
{
    return &g_log_file_resend_ctrl;
}

void vital_info_init_log_resend_ctrl(void)
{
    memset(&g_log_file_resend_ctrl, 0, sizeof(vital_info_file_resend_ctrl_t));
}

static vital_info_file_resend_ctrl_t VITAL_INFO_ALIGN_WAY g_statistics_file_resend_ctrl;

p_vital_info_file_resend_ctrl_t vital_info_get_statistics_file_resend_ctrl(void)
{
    return &g_statistics_file_resend_ctrl;
}

void vital_info_init_statistics_resend_ctrl(void)
{
    memset(&g_statistics_file_resend_ctrl, 0, sizeof(vital_info_file_resend_ctrl_t));
}

static vital_info_file_resend_ctrl_t VITAL_INFO_ALIGN_WAY g_sensor_file_resend_ctrl;

p_vital_info_file_resend_ctrl_t vital_info_get_sensor_file_resend_ctrl(void)
{
    return &g_sensor_file_resend_ctrl;
}

void vital_info_init_sensor_resend_ctrl(void)
{
    memset(&g_sensor_file_resend_ctrl, 0, sizeof(vital_info_file_resend_ctrl_t));
}

void vital_info_init_all_resend_ctrl(void)
{
    vital_info_init_file_resend_ctrl();
    vital_info_init_log_resend_ctrl();
    vital_info_init_sensor_resend_ctrl();
}

size_t vital_info_get_file_need_len(p_base_file_descriptor_t p_base_fd)
{
    p_vital_info_file_descriptor_t p_vital_info_fd = (p_vital_info_file_descriptor_t)p_base_fd;
    size_t read_len = p_vital_info_fd->read_info.need_len;

    if (p_vital_info_fd->read_info.cur_offset >= p_vital_info_fd->read_info.total_len)
    {
        read_len = 0;
    }
    else if (p_vital_info_fd->read_info.cur_offset + p_vital_info_fd->read_info.need_len > p_vital_info_fd->read_info.total_len)
    {
        if (p_vital_info_fd->read_info.total_len > p_vital_info_fd->read_info.cur_offset)
        {
            read_len = p_vital_info_fd->read_info.total_len - p_vital_info_fd->read_info.cur_offset;
        }
        else
        {
            read_len = 0;
        }
    }

    return read_len;
}

void vital_info_resend_ctrl_handler(void)
{
#if !defined(BSP_USING_PC_SIMULATOR)

    bool wireless_conn_state = false;

    if (get_phone_device_type() == Phone_Device_Type_IOS)
    {
        wireless_conn_state = get_system_ble_connect_state();
    }
    else
    {
        wireless_conn_state = get_system_ble_connect_state() | get_system_Spp_connect_state();
    }

    if (wireless_conn_state == true)
    {
        p_vital_info_file_resend_ctrl_t p_resend_ctrl;
        bool send_msg_rst = false;

        // fitness file
        p_resend_ctrl = vital_info_get_file_resend_ctrl();
        if (p_resend_ctrl->resend_type)
        {
            ipc_send_msg_from_ble_to_app(p_resend_ctrl->resend_type, sizeof(int), (uint8_t *)&p_resend_ctrl->resend_handle);

            send_msg_rst = true; // 默认都是发送成功

            if (send_msg_rst)
            {
                vital_info_init_file_resend_ctrl();
            }
        }

        // log file
        p_resend_ctrl = vital_info_get_log_file_resend_ctrl();
        if (p_resend_ctrl->resend_type)
        {
            ipc_send_msg_from_ble_to_app(p_resend_ctrl->resend_type, sizeof(int), (uint8_t *)&p_resend_ctrl->resend_handle);

            send_msg_rst = true; // 默认都是发送成功

            if (send_msg_rst)
            {
                vital_info_init_log_resend_ctrl();
            }
        }

        // statistics file
        p_resend_ctrl = vital_info_get_statistics_file_resend_ctrl();
        if (p_resend_ctrl->resend_type)
        {
            ipc_send_msg_from_ble_to_app(p_resend_ctrl->resend_type, sizeof(int), (uint8_t *)&p_resend_ctrl->resend_handle);

            send_msg_rst = true; // 默认都是发送成功

            if (send_msg_rst)
            {
                vital_info_init_statistics_resend_ctrl();
            }
        }

        // sensor file
        p_resend_ctrl = vital_info_get_sensor_file_resend_ctrl();
        if (p_resend_ctrl->resend_type)
        {
            ipc_send_msg_from_ble_to_app(p_resend_ctrl->resend_type, sizeof(int), (uint8_t *)&p_resend_ctrl->resend_handle);

            send_msg_rst = true; // 默认都是发送成功

            if (send_msg_rst)
            {
                vital_info_init_sensor_resend_ctrl();
            }
        }
    }
#endif
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//

uint32_t vital_info_get_timestamp(void)
{
    return get_local_timestamp_stander();
}

int8_t vital_info_get_time_zone(void)
{
    return get_time_zone();
}

int32_t vital_info_get_time_zone_offset(int8_t time_zone)
{
    return mul_sport_get_time_zone_offset(time_zone);
}

vital_info_utc_time_t vital_info_get_clock_time(utc_time_t utc_time, int8_t time_zone)
{
    return mul_sport_get_clock_time(utc_time, time_zone);
}

bool vital_info_is_the_same_day(uint32_t dst_local_timestamp, uint32_t src_local_timestamp)
{
    return mul_sport_is_the_same_day(dst_local_timestamp, src_local_timestamp);
}

bool vital_info_data_init(void)
{
    daily_data_idx_init();
    mul_sport_init();
    mm_data_idx_init();
    sleep_data_idx_init();
    abn_record_data_idx_init();

    vital_info_init_all_resend_ctrl();

    return true;
}

bool vital_info_data_deinit(void)
{
    daily_data_idx_deinit();
    mul_sport_deinit();
    mm_data_idx_deinit();
    sleep_data_idx_deinit();
    abn_record_data_idx_deinit();

    return true;
}

bool vital_info_data_save_process(void)
{
    daily_data_save_data_process();
    mul_sport_save_data_process();
    mm_data_save_data_process();
    sleep_data_save_data_process();
    abn_record_data_save_data_process();

    return true;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
void vital_info_min_hr_cb(uint8_t hr)
{
    sleep_data_set_hr_point_val(hr);

    vital_info_platform_min_hr_cb(hr);
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
void vital_info_min_spo2_cb(uint8_t spo2)
{
    sleep_data_set_spo2_point_val(spo2);

    vital_info_platform_min_spo2_cb(spo2);
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
void vital_info_min_hrv_cb(uint8_t hrv)
{
    vital_info_platform_min_hrv_cb(hrv);
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
void vital_info_sec_handle_process(void)
{
    daily_data_sec_handle_process();
}

void vital_info_min_handle_process(void)
{

}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
void vital_info_print_fitness_id(const char *desc_str, data_id_t *p_id)
{
    uint8_t *p_disp_str = (uint8_t *)p_id;

    p_disp_str = (void *)p_disp_str; // avoid warning
    vital_info_dbg_log("%s, id = %x-%x-%x-%x-%x-%x-%x\r\n", \
                       desc_str, \
                       p_disp_str[0], \
                       p_disp_str[1], \
                       p_disp_str[2], \
                       p_disp_str[3], \
                       p_disp_str[4], \
                       p_disp_str[5], \
                       p_disp_str[6]);
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
bool vital_info_get_intraday_vaild_id(data_id_t *p_id, uint32_t *id_nums, const uint32_t max_id_nums)
{
    if (!p_id || !id_nums)
    {
        return false;
    }

    if (id_nums)
    {
        *id_nums = 0;
    }

    daily_data_get_intraday_vaild_id(p_id + *id_nums, id_nums, max_id_nums);

    sleep_data_get_intraday_vaild_id(p_id + *id_nums, id_nums, max_id_nums);

    mul_sport_get_intraday_valid_id(p_id + *id_nums, id_nums, max_id_nums);

    mm_data_get_intraday_vaild_id(p_id + *id_nums, id_nums, max_id_nums);

    abn_record_data_get_intraday_vaild_id(p_id + *id_nums, id_nums, max_id_nums);

    return true;
}

bool vital_info_get_historical_vaild_id(data_id_t *p_id, uint32_t *id_nums, const uint32_t max_id_nums)
{
    if (!p_id || !id_nums)
    {
        return false;
    }

    if (id_nums)
    {
        *id_nums = 0;
    }

//    daily_data_get_historical_vaild_id(p_id + *id_nums, id_nums, max_id_nums);

//    mul_sport_get_sport_historical_valid_id(p_id + *id_nums, id_nums, max_id_nums);

//    sleep_data_get_historical_vaild_id(p_id + *id_nums, id_nums, max_id_nums);

//    mm_data_get_historical_vaild_id(p_id + *id_nums, id_nums, max_id_nums);

//    abn_record_data_get_historical_vaild_id(p_id + *id_nums, id_nums, max_id_nums);

    return true;
}

bool vital_info_get_data_len(data_id_t *p_id, size_t *p_data_len)
{
    if (p_id->type_desc.type == ENUM_DAILY_DATA_T)
    {
        switch (p_id->type_desc.specific_type)
        {
            case ENUM_DAILY_ACTIVITY_DATA_T:
                daily_data_get_data_len(p_id, p_data_len);
                break;

            case ENUM_MANUAL_MEASURE:
                mm_data_get_data_len(p_id, p_data_len);
                break;

            case ENUM_SLEEP_MI_DEV:
                sleep_data_get_data_len(p_id, p_data_len);
                break;

            case ENUM_ABN_RECORD_DATA:
                abn_record_data_get_data_len(p_id, p_data_len);
                break;

            default:
                break;
        }
    }
    else if (p_id->type_desc.type == ENUM_SPORT_DATA_T)
    {
        mul_sport_get_data_len(p_id, p_data_len);
    }

    return true;
}


bool vital_info_get_data_header_ptr(data_id_t *p_id, uint8_t **pp_header_data, size_t *header_data_len)
{
    if (p_id->type_desc.type == ENUM_DAILY_DATA_T)
    {
        switch (p_id->type_desc.specific_type)
        {
            case ENUM_DAILY_ACTIVITY_DATA_T:
                daily_data_get_data_header_ptr(p_id, pp_header_data, header_data_len);
                break;

            case ENUM_MANUAL_MEASURE:
                mm_data_get_data_header_ptr(p_id, pp_header_data, header_data_len);
                break;

            case ENUM_SLEEP_MI_DEV:
                sleep_data_get_data_header_ptr(p_id, pp_header_data, header_data_len);
                break;

            case ENUM_ABN_RECORD_DATA:
                abn_record_data_get_data_header_ptr(p_id, pp_header_data, header_data_len);
                break;

            default:
                break;
        }
    }
    else if (p_id->type_desc.type == ENUM_SPORT_DATA_T)
    {
        mul_sport_get_data_header_ptr(p_id, pp_header_data, header_data_len);
    }

    return true;
}

bool vital_info_get_data_start_addr(data_id_t *p_id, uint32_t *p_start_addr)
{
    if (p_id->type_desc.type == ENUM_DAILY_DATA_T)
    {
        switch (p_id->type_desc.specific_type)
        {
            case ENUM_DAILY_ACTIVITY_DATA_T:
                daily_data_get_data_start_addr(p_id, p_start_addr);
                break;

            case ENUM_MANUAL_MEASURE:
                mm_data_get_data_start_addr(p_id, p_start_addr);
                break;

            case ENUM_SLEEP_MI_DEV:
                sleep_data_get_data_start_addr(p_id, p_start_addr);
                break;

            case ENUM_ABN_RECORD_DATA:
                abn_record_data_get_data_start_addr(p_id, p_start_addr);
                break;

            default:
                break;
        }
    }
    else if (p_id->type_desc.type == ENUM_SPORT_DATA_T)
    {
        mul_sport_get_data_start_addr(p_id, p_start_addr);
    }

    return true;
}

bool vital_info_get_data_item_info(data_id_t *p_id, uint32_t *p_start_addr, size_t *p_data_len)
{
    if (p_id->type_desc.type == ENUM_DAILY_DATA_T)
    {
        switch (p_id->type_desc.specific_type)
        {
            case ENUM_DAILY_ACTIVITY_DATA_T:
                daily_data_get_data_item_info(p_id, p_start_addr, p_data_len);
                break;

            case ENUM_MANUAL_MEASURE:
                mm_data_get_data_item_info(p_id, p_start_addr, p_data_len);
                break;

            case ENUM_SLEEP_MI_DEV:
                sleep_data_get_data_item_info(p_id, p_start_addr, p_data_len);
                break;

            case ENUM_ABN_RECORD_DATA:
                abn_record_data_get_data_item_info(p_id, p_start_addr, p_data_len);
                break;

            default:
                break;
        }
    }
    else if (p_id->type_desc.type == ENUM_SPORT_DATA_T)
    {
        mul_sport_get_data_item_info(p_id, p_start_addr, p_data_len);   
    }

    return true;
}

bool vital_info_read_upload_data(data_id_t *p_id, uint32_t read_addr, uint8_t *buf_ptr, size_t read_len)
{
    if (p_id->type_desc.type == ENUM_DAILY_DATA_T)
    {
        switch (p_id->type_desc.specific_type)
        {
            case ENUM_DAILY_ACTIVITY_DATA_T:
                daily_data_read_upload_data(p_id, read_addr, buf_ptr, read_len);
                break;

            case ENUM_MANUAL_MEASURE:
                mm_data_read_upload_data(p_id, read_addr, buf_ptr, read_len);
                break;

            case ENUM_SLEEP_MI_DEV:
                sleep_data_read_upload_data(p_id, read_addr, buf_ptr, read_len);
                break;

            case ENUM_ABN_RECORD_DATA:
                abn_record_data_read_upload_data(p_id, read_addr, buf_ptr, read_len);
                break;

            default:
                break;
        }
    }
    else if (p_id->type_desc.type == ENUM_SPORT_DATA_T)
    {
        mul_sport_read_upload_data(p_id, read_addr, buf_ptr, read_len);
    }

    return true;
}

bool vital_info_delete_id(data_id_t *p_id)
{
    if (p_id->type_desc.type == ENUM_DAILY_DATA_T)
    {
        switch (p_id->type_desc.specific_type)
        {
            case ENUM_DAILY_ACTIVITY_DATA_T:
                daily_data_delete_id(p_id);
                break;

            case ENUM_MANUAL_MEASURE:
                mm_data_delete_id(p_id);
                break;

            case ENUM_SLEEP_MI_DEV:
                sleep_data_delete_id(p_id);
                break;

            case ENUM_ABN_RECORD_DATA:
                abn_record_data_delete_id(p_id);
                break;

            default:
                break;
        }
    }
    else if (p_id->type_desc.type == ENUM_SPORT_DATA_T)
    {
        mul_sport_delete_id(p_id);
    }

    return true;
}
#endif
