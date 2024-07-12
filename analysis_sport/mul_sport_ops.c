#include "mul_sport_common.h"

#include "string.h"

#include "mul_sport_ops.h"
#include "mul_sport_factory.h"
#include "multi_motion_sport_handle.h"
#if GPS_DATA_MANAGER_SWITCH
#include "multi_motion_gps_handle.h"
#endif
#include "multi_motion_public_part.h"


#if FLASH_MANAGER_SWITCH

#define SPACE_MOCK_DATA_SWITCH       0

/**
 * @brief 用于判断是否已经提示过"空间不足,继续将会覆盖.."
 */
static bool MUL_SPORT_POSSIBLY_UNUSED g_is_already_prompted        = false;

static bool MUL_SPORT_POSSIBLY_UNUSED g_mul_sport_was_initialized  = false;


/* 多运动 */
//_

void mul_sport_set_has_reached_last_km(void)
{
    set_is_up_km_status(true);
}

void mul_sport_set_has_reached_last_mile(void)
{
    set_is_up_mile_status(true);
}
void mul_sport_set_has_reached_subsection(void)
{
    //todo:by ly
}
void mul_sport_set_has_reached_segmentation(void)
{
    //todo:by ly    
}
void mul_sport_set_mul_sport_cnt(uint32_t sport_time_cnt)
{
    set_mul_sport_cnt(sport_time_cnt);
}

void mul_sport_add_sport_segment_distance(uint32_t new_point_distance)
{
    add_mul_sport_segment_distance(new_point_distance);
}

void mul_sport_add_sport_segment_count(uint16_t new_point_count)
{
    add_mul_sport_segment_count(new_point_count);
}

void mul_sport_set_sub_sport_type(Sport_Type_Type sport_type)
{
    set_sub_sport_type(sport_type);
}

Sport_Type_Type mul_sport_get_sub_sport_type(void)
{
    return get_sub_sport_type();
}

void mul_sport_set_mul_sport_end_time(utc_time_t timestamp)
{
    set_mul_sport_end_time(timestamp);
}

void mul_sport_set_sport_sit_type(Sport_Interval_Training_Type sit_type)
{
    set_sport_sit_type(sit_type);
}

void mul_sport_set_sport_next_sit_type(Sport_Interval_Training_Type sit_type)
{
    set_sport_next_sit_type(sit_type);
}

void mul_sport_set_is_change_sit_type(bool is_change)
{
    set_is_change_sit_type(is_change);
}

void mul_sport_clear_sport_global_var(void)
{
    multi_motion_clear_sport_global_var();
}

multi_motion_ret mul_sport_get_storage_space_status(void)
{
    multi_motion_ret ret_code = MULTI_MOTION_SPACE_AMPLE;

#if SPACE_MOCK_DATA_SWITCH
    ret_code = MULTI_MOTION_SPACE_WILL_FULLED;
#else

#if GPS_DATA_MANAGER_SWITCH

    /* TODO: 判断is_gps_space_was_full为满的时候, 需要添加判断此次运动是不是GPS运动 */
    if (is_space_was_full() || is_gps_space_was_full())
    {
        ret_code = MULTI_MOTION_SPACE_WAS_FULLED;
    }
    else if (is_space_will_full() || is_gps_space_will_full())
    {
        ret_code = MULTI_MOTION_SPACE_WILL_FULLED;
    }
#else
    if (is_space_was_full())
    {
        ret_code = MULTI_MOTION_SPACE_WAS_FULLED;
    }
    else if (is_space_will_full())
    {
        ret_code = MULTI_MOTION_SPACE_WILL_FULLED;
    }
#endif /* GPS_DATA_MANAGER_SWITCH */

#endif /* SPACE_MOCK_DATA_SWITCH */

    return ret_code;
}

bool mul_sport_recycle_the_first_sport_index(void)
{
    bool ret_val = true;
    bool is_deal = false;
    data_id_t sport_id;
    Sport_Type_Type sub_sport_type = ST_NONE;

#if GPS_DATA_MANAGER_SWITCH
    data_id_t gps_id;
    if (is_space_was_full())
    {
        if (app_get_id_by_idx(&sport_id, 0))
        {
            gps_id = sport_id;
            gps_id.type_desc.data_type = ENUM_SPORT_GPS_DATA_T;
            multi_motion_get_sub_sport_type(&sport_id, &sub_sport_type);
            del_sport_file_by_idx_num(0);       // 回收第一个索引
            del_gps_file(&gps_id);

            multi_motion_write_idx_table();

            is_deal = true;
        }
    }
    else if (is_gps_space_was_full())
    {
        if (app_get_gps_id_by_idx(&gps_id, 0))
        {
            sport_id = gps_id;
            sport_id.type_desc.data_type = ENUM_POINT_DATA_T;
            multi_motion_get_sub_sport_type(&sport_id, &sub_sport_type);
            del_gps_file(&gps_id);
            del_sport_file(&sport_id);

            multi_motion_write_idx_table();

            is_deal = true;
        }
        else if (app_get_id_by_idx(&sport_id, 0))
        {
            multi_motion_get_sub_sport_type(&sport_id, &sub_sport_type);
            del_sport_file_by_idx_num(0);       // 回收第一个索引

            multi_motion_write_idx_table();

            is_deal = true;
        }
    }
#else
    if (is_space_was_full())
    {
        app_get_id_by_idx(&sport_id, 0);
        del_sport_file_by_idx_num(0);       // 回收第一个索引
        write_multi_motion_idx_table();

        is_deal = true;
    }
#endif

    if (is_deal)
    {
        mul_sport_delete_sport_file_succeed_cb(sport_id, sub_sport_type);
    }

    return ret_val;
}


bool mul_sport_recycle_the_first_sport_index_by_auto_sport(void)
{
    bool ret_val = true;
    bool is_deal = false;
    data_id_t sport_id;
    Sport_Type_Type sub_sport_type = ST_NONE;

#if GPS_DATA_MANAGER_SWITCH
    data_id_t gps_id;
    if (is_space_was_full_by_auto_sport())
    {
        do
        {
            if (app_get_id_by_idx(&sport_id, 0))
            {
                gps_id = sport_id;
                gps_id.type_desc.data_type = ENUM_SPORT_GPS_DATA_T;
                multi_motion_get_sub_sport_type(&sport_id, &sub_sport_type);
                del_sport_file_by_idx_num(0);       // 回收第一个索引
                del_gps_file(&gps_id);

                mul_sport_delete_sport_file_succeed_cb(sport_id, sub_sport_type);
            }
            if (MULTI_MOTION_DATA_SECTOR_NUM <= MIN_AUTO_SPORT_SECTOR_NUMS)
            {
                break;
            }
        } while (is_space_was_full_by_auto_sport());
        multi_motion_write_idx_table();
    }
    else if (is_gps_space_was_full())
    {
        if (app_get_gps_id_by_idx(&gps_id, 0))
        {
            sport_id = gps_id;
            sport_id.type_desc.data_type = ENUM_POINT_DATA_T;
            multi_motion_get_sub_sport_type(&sport_id, &sub_sport_type);
            del_gps_file(&gps_id);
            del_sport_file(&sport_id);

            multi_motion_write_idx_table();

            is_deal = true;
        }
        else if (app_get_id_by_idx(&sport_id, 0))
        {
            multi_motion_get_sub_sport_type(&sport_id, &sub_sport_type);
            del_sport_file_by_idx_num(0);       // 回收第一个索引

            multi_motion_write_idx_table();

            is_deal = true;
        }
    }
#else
    if (is_space_was_full())
    {
        app_get_id_by_idx(&sport_id, 0);
        del_sport_file_by_idx_num(0);       // 回收第一个索引
        write_multi_motion_idx_table();

        is_deal = true;
    }
#endif

    if (is_deal)
    {
        mul_sport_delete_sport_file_succeed_cb(sport_id, sub_sport_type);
    }

    return ret_val;
}

bool mul_sport_new_sport_file(utc_time_t sport_start_timestamp, bool is_auto_sport)
{
    bool ret_flag = false;
    
    p_ms_abstract_config_t p_ms_sport_config = NULL;

    utc_time_t m_sport_start_timestamp = 0;

    m_sport_start_timestamp = sport_start_timestamp;
    
    if (!mul_sport_get_cur_sport_config((void **)&p_ms_sport_config))
    {
        app_clear_cur_sport_data_id();
        multi_motion_delete_cur_sport_list_item();

#if GPS_DATA_MANAGER_SWITCH
        app_clear_cur_gps_data_id();
        app_delete_cur_gps_handle_obj();
#endif

        return ret_flag;
    }

    if (is_auto_sport == true)
    {
        mul_sport_recycle_the_first_sport_index_by_auto_sport();
    }
    else
    {
        mul_sport_recycle_the_first_sport_index();
        multi_motion_clear_sport_global_var();
    }   

    if (multi_motion_new_sport_file(p_ms_sport_config, m_sport_start_timestamp) == MULTI_MOTION_SUCCESS)
    {
        ret_flag = true;

        if (is_auto_sport == true)
        {
            // 写入运动识别缓存数据
            mul_sport_platform_auto_sport_write_data();
        }

#if GPS_DATA_MANAGER_SWITCH
        if (multi_motion_new_gps_sport_file(p_ms_sport_config, m_sport_start_timestamp) == MULTI_MOTION_SUCCESS)
        {
            app_clear_gps_global_var();

            if (is_auto_sport == true)
            {
                mul_sport_platform_auto_sport_write_gps();
            }

#if 0
            ms_gps_item_t gps_item;

            gps_item.gps_vx.ts = (1659789174);gps_item.gps_vx.longitude = (float)106.319032, gps_item.gps_vx.latitude = (float)29.542488;
            mul_sport_write_gps_data(gps_item);
            gps_item.gps_vx.ts = (1659789174 + 60 * 5 * 1);gps_item.gps_vx.longitude = (float)106.319104, gps_item.gps_vx.latitude = (float)29.542116;
            mul_sport_write_gps_data(gps_item);
            gps_item.gps_vx.ts = (1659789174 + 60 * 5 * 2);gps_item.gps_vx.longitude = (float)106.319168, gps_item.gps_vx.latitude = (float)29.541820;
            mul_sport_write_gps_data(gps_item);
            gps_item.gps_vx.ts = (1659789174 + 60 * 5 * 3);gps_item.gps_vx.longitude = (float)106.319392, gps_item.gps_vx.latitude = (float)29.541724;
            mul_sport_write_gps_data(gps_item);
            gps_item.gps_vx.ts = (1659789174 + 60 * 5 * 4);gps_item.gps_vx.longitude = (float)106.319736, gps_item.gps_vx.latitude = (float)29.541786;
            mul_sport_write_gps_data(gps_item);
            gps_item.gps_vx.ts = (1659789174 + 60 * 5 * 5);gps_item.gps_vx.longitude = (float)106.320080, gps_item.gps_vx.latitude = (float)29.541870;
            mul_sport_write_gps_data(gps_item);
            gps_item.gps_vx.ts = (1659789174 + 60 * 5 * 6);gps_item.gps_vx.longitude = (float)106.320360, gps_item.gps_vx.latitude = (float)29.541926;
            mul_sport_write_gps_data(gps_item);
            gps_item.gps_vx.ts = (1659789174 + 60 * 5 * 7);gps_item.gps_vx.longitude = (float)106.320552, gps_item.gps_vx.latitude = (float)29.542010;
            mul_sport_write_gps_data(gps_item);
            gps_item.gps_vx.ts = (1659789174);gps_item.gps_vx.longitude = (float)106.320880, gps_item.gps_vx.latitude = (float)29.541360;
            mul_sport_write_gps_data(gps_item);
            gps_item.gps_vx.ts = (1659789174 + 60 * 5 * 1);gps_item.gps_vx.longitude = (float)106.321024, gps_item.gps_vx.latitude = (float)29.541388;
            mul_sport_write_gps_data(gps_item);
            gps_item.gps_vx.ts = (1659789174 + 60 * 5 * 2);gps_item.gps_vx.longitude = (float)106.321304, gps_item.gps_vx.latitude = (float)29.541424;
            mul_sport_write_gps_data(gps_item);
            gps_item.gps_vx.ts = (1659789174 + 60 * 5 * 3);gps_item.gps_vx.longitude = (float)106.321624, gps_item.gps_vx.latitude = (float)29.541472;
            mul_sport_write_gps_data(gps_item);
            gps_item.gps_vx.ts = (1659789174 + 60 * 5 * 4);gps_item.gps_vx.longitude = (float)106.321920, gps_item.gps_vx.latitude = (float)29.541564;
            mul_sport_write_gps_data(gps_item);
            gps_item.gps_vx.ts = (1659789174 + 60 * 5 * 5);gps_item.gps_vx.longitude = (float)106.322024, gps_item.gps_vx.latitude = (float)29.541824;
            mul_sport_write_gps_data(gps_item);
            gps_item.gps_vx.ts = (1659789174 + 60 * 5 * 6);gps_item.gps_vx.longitude = (float)106.321952, gps_item.gps_vx.latitude = (float)29.542208;
            mul_sport_write_gps_data(gps_item);
            gps_item.gps_vx.ts = (1659789174 + 60 * 5 * 7);gps_item.gps_vx.longitude = (float)106.321880, gps_item.gps_vx.latitude = (float)29.542628;
            mul_sport_write_gps_data(gps_item);
            gps_item.gps_vx.ts = (1659789174 + 60 * 5 * 10);gps_item.gps_vx.longitude = (float)106.321792, gps_item.gps_vx.latitude = (float)39.543046;
            mul_sport_write_gps_data(gps_item);
#endif

#if 0
            mul_sport_save_sport_buffer_data();

            uint32_t cur_item_nums = mul_sport_get_cur_gps_item_nums();
            mul_sport_dbg_log("[mul sport] cur_item_num = %d\n", cur_item_nums);
            if (cur_item_nums)
            {
                ms_gps_item_v1 gps_item[50];
                memset(gps_item, 0, sizeof(gps_item));
                mul_sport_get_cur_gps_nitem(gps_item, 0, cur_item_nums);

                for (uint32_t i = 0; i < cur_item_nums; i++)
                {
                    mul_sport_dbg_log("[mul sport] gps i = %d, ts = %d, long = %f, lat = %f\n", i, gps_item[i].ts, gps_item[i].longitude, gps_item[i].latitude);
                }
            }
#endif
        }
#endif
    }

    g_is_already_prompted = false;

    return ret_flag;
}

p_data_id_t mul_sport_get_cur_sport_data_id(void)
{
    return get_cur_sport_data_id();
}

void mul_sport_clear_cur_sport_id(void)
{
    del_sport_file(get_cur_sport_data_id());
    app_clear_cur_sport_data_id();
    multi_motion_delete_cur_sport_list_item();

#if GPS_DATA_MANAGER_SWITCH
    del_gps_file(get_cur_gps_data_id());
    app_clear_cur_gps_data_id();
    app_delete_cur_gps_handle_obj();
#endif
}


bool mul_sport_resume_process(void)
{
    bool ret_val = true;

    multi_motion_save_sport_data();
    multi_motion_write_sport_fixed_data();
    set_recovery_motion_timestamp(mul_sport_get_timestamp());
    set_fixed_data_base_pos(get_cur_sport_handle_data_len());
    set_sport_data_len_offset();
    set_initialize_altitude(mul_sport_get_sport_restart_altitude());

    return ret_val;
}

bool mul_sport_save_cur_sport_file(void)
{
    bool ret_val = true;
    bool is_modify = false;
#if !defined(BSP_USING_PC_SIMULATOR) && (LOG_FLASH_USED_CFG == 0)
    //Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG,"mul_sport is_do_sport start =%d,%d_%d\n", is_doing_sports(), is_doing_gps_sport(),get_sport_idx_nums());
#endif
    if (is_doing_sports())
    {
        multi_motion_save_sport_file();

        is_modify = true;
    }

#if GPS_DATA_MANAGER_SWITCH
    if (is_doing_gps_sport())
    {
        multi_motion_save_gps_data();

        if (app_get_cur_gps_file_len())
        {
            app_save_gps_file();
        }
        else
        {
            del_gps_file(get_cur_gps_data_id());
        }

        is_modify = true;
    }
#endif

    if (is_modify)
    {
        multi_motion_write_idx_table();
    }
#if !defined(BSP_USING_PC_SIMULATOR) && (LOG_FLASH_USED_CFG == 0)
    //Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG,"mul_sport is_do_sport end =%d,%d_%d\n", is_doing_sports(), is_doing_gps_sport(),get_sport_idx_nums());
#endif
    return ret_val;
}

bool mul_sport_clear_cur_sport_cache(void)
{
    if (is_doing_sports())
    {
        app_clear_cur_sport_data_id();
        multi_motion_delete_cur_sport_list_item();
    }

    if (is_doing_gps_sport())
    {
        app_clear_cur_gps_data_id();
        app_delete_cur_gps_handle_obj();
    }

    return true;
}

bool mul_sport_write_idx_table(void)
{
    return multi_motion_write_idx_table();
}


multi_motion_ret mul_sport_write_sport_data(void)
{
    multi_motion_ret  ret_code;

    ret_code = multi_motion_write_sport_sec_point_data();

#if SPACE_MOCK_DATA_SWITCH
    ret_code = MULTI_MOTION_SPACE_WAS_FULLED;
#endif

    if (ret_code == MULTI_MOTION_SPACE_WAS_FULLED)
    {

        /* FIXME: 如果需要"空间已满, 继续将会覆盖"这个页面, 则需要修改这里的代码 */
#if 0
        if (get_sport_idx_nums() == 1)
        {
            mul_sport_space_is_exhausted_cb();
        }
        else
        {
            if (g_is_already_prompted)
            {
                mul_sport_recycle_the_first_sport_index();  // 不提示, 直接回收第一个索引
            }
            else
            {
                g_is_already_prompted = true;

                mul_sport_space_is_not_enouth_cb();
            }
        }
#else
        if (get_sport_idx_nums() == 1)
        {
            mul_sport_space_is_exhausted_cb();
        }
        else
        {
            mul_sport_recycle_the_first_sport_index();  // 不提示, 直接回收第一个索引
        }
#endif
    }

    return ret_code;
}

#if GPS_DATA_MANAGER_SWITCH
multi_motion_ret mul_sport_write_gps_data(ms_gps_item_t gps_item)
{
    multi_motion_ret  ret_code;

    ret_code = multi_motion_write_gps_data(gps_item);

    if (ret_code == MULTI_MOTION_SPACE_WAS_FULLED)
    {
        if (get_gps_sport_idx_nums() == 1)
        {
            mul_sport_space_is_exhausted_cb();
        }
        else
        {
            mul_sport_recycle_the_first_sport_index();  // 不提示, 直接回收第一个索引
        }
    }

    return ret_code;
}
#else
multi_motion_ret mul_sport_write_gps_data(ms_gps_item_t gps_item)
{
    multi_motion_ret  ret_code = MULTI_MOTION_WRITE_SUCCESS;

    return ret_code;
}
#endif

multi_motion_ret mul_sport_app_write_sport_data(void *p_input_data, void *p_input_data_args)
{
    multi_motion_ret ret_code;

    ret_code = multi_motion_app_write_sport_data(p_input_data, p_input_data_args);

    if (ret_code == MULTI_MOTION_SPACE_WAS_FULLED)
    {
        if (get_sport_idx_nums() == 1)
        {
            mul_sport_space_is_exhausted_cb();
        }
        else
        {
            mul_sport_recycle_the_first_sport_index();  // 不提示, 直接回收第一个索引
        }
    }

    return ret_code;
}

multi_motion_ret mul_sport_write_mass_auto_sport_data(void *p_data, uint32_t data_len, uint32_t data_cnts)
{
    multi_motion_ret ret_code;

    ret_code = multi_motion_write_mass_sport_data(p_data, data_len);

    if (ret_code == MULTI_MOTION_WRITE_SUCCESS)
    {
        set_mul_sport_total_point_cnts(data_cnts);
    }

    if (ret_code == MULTI_MOTION_SPACE_WAS_FULLED)
    {
        if (get_sport_idx_nums() == 1)
        {
            mul_sport_space_is_exhausted_cb();
        }
        else
        {
            mul_sport_recycle_the_first_sport_index();  // 不提示, 直接回收第一个索引
        }
    }

    return ret_code;
}

multi_motion_ret mul_sport_write_mass_auto_sport_gps(void *p_data, uint32_t data_len, uint32_t data_cnts)
{
    multi_motion_ret ret_code;

    ret_code = multi_motion_write_mass_sport_gps(p_data, data_len);

    if (ret_code == MULTI_MOTION_SPACE_WAS_FULLED)
    {
        if (get_gps_sport_idx_nums() == 1)
        {
            mul_sport_space_is_exhausted_cb();
        }
        else
        {
            mul_sport_recycle_the_first_sport_index();  // 不提示, 直接回收第一个索引
        }
    }

    return ret_code;
}


multi_motion_ret mul_sport_app_set_sport_repo(void *p_input_data, void *p_input_data_args)
{
    multi_motion_ret ret_code;

    ret_code = multi_motion_app_set_sport_repo(p_input_data, p_input_data_args);

    return ret_code;
}

void mul_sport_save_sport_buffer_data(void)
{
    if (is_doing_sports())
    {
        multi_motion_save_sport_data();
    }

#if GPS_DATA_MANAGER_SWITCH
    if (is_doing_gps_sport())
    {
        multi_motion_save_gps_data();
    }
#endif
}

uint32_t mul_sport_get_gps_item_nums(p_data_id_t p_id)
{
    return multi_motion_get_gps_item_nums(p_id);
}

uint32_t mul_sport_get_gps_nitem(p_data_id_t p_id, ms_gps_item_v1 *p_item, const uint32_t offset_item, const uint32_t need_item_nums)
{
    return multi_motion_get_gps_nitem(p_id, p_item, offset_item, need_item_nums);
}

uint32_t mul_sport_get_cur_gps_item_nums(void)
{
    return multi_motion_get_cur_gps_item_nums();
}

uint32_t mul_sport_get_cur_gps_nitem(ms_gps_item_v1 *p_item, const uint32_t offset_item, const uint32_t need_item_nums)
{
    return multi_motion_get_cur_gps_nitem(p_item,offset_item, need_item_nums);
}

//

/* */
//
uint32_t mul_sport_get_cur_record_item_nums(void)
{
    return multi_motion_get_cur_record_item_nums();
}

uint32_t mul_sport_get_cur_record_nitem(ms_record_item_t *p_item, const uint32_t offset_item, const uint32_t need_item_nums)
{
    return multi_motion_get_cur_record_nitem(p_item, offset_item, need_item_nums);
}

//

/* */
//

bool mul_sport_init(void)
{
    bool ret_val = true;

    if (!g_mul_sport_was_initialized)
    {
        g_mul_sport_was_initialized = true;

        multi_motion_init();

        mul_sport_factory_destory();

        mul_sport_platform_init();
    }

    return ret_val;
}

bool mul_sport_deinit(void)
{
    bool ret_val = true;

    multi_motion_deinit();

    g_mul_sport_was_initialized = false;

    return ret_val;
}


bool mul_sport_save_data_process(void)
{
    bool ret_val = true;

    multi_motion_write_idx_table();

    g_mul_sport_was_initialized = false;

    return ret_val;
}

bool mul_sport_get_intraday_valid_id(data_id_t *p_id, uint32_t *id_nums, const uint32_t max_id_nums)
{
    uint32_t tmp_id_nums = *id_nums;
    uint32_t delta_nums = 0;

    if (!p_id || *id_nums >= max_id_nums)
    {
        return false;
    }

#if GPS_DATA_MANAGER_SWITCH
    app_get_multi_motion_gps_intraday_valid_id(p_id, id_nums, max_id_nums);
#endif
    
    delta_nums = *id_nums - tmp_id_nums;

    app_get_multi_motion_intraday_valid_id(p_id + delta_nums, id_nums, max_id_nums);

    return true;
}

bool mul_sport_get_sport_historical_valid_id(data_id_t *p_id, uint32_t *id_nums, const uint32_t max_id_nums)
{
    uint32_t tmp_id_nums = *id_nums;
    uint32_t delta_nums = 0;

    if (!p_id)
    {
        return false;
    }

#if GPS_DATA_MANAGER_SWITCH
    app_get_multi_motion_gps_historical_valid_id(p_id, id_nums, max_id_nums);
#endif

    delta_nums = *id_nums - tmp_id_nums;

    app_get_multi_motion_historical_valid_id(p_id + delta_nums, id_nums, max_id_nums);

    return true;
}

bool mul_sport_get_data_len(const data_id_t *p_id, uint32_t *data_len)
{
    if (!p_id)
    {
        *data_len = 0;
        return false;
    }

    app_get_multi_motion_data_len(p_id, data_len);

    mul_sport_dbg_log("[mul sport] get len, data_len = %d", *data_len);

    return true;
}

bool mul_sport_get_data_header_ptr(data_id_t *p_id, uint8_t **pp_header_data, size_t *header_data_len)
{
    if (!p_id)
    {
        return false;
    }

    mul_sport_platform_get_data_header_ptr(p_id, pp_header_data, header_data_len);

    return true;
}

bool mul_sport_get_data_start_addr(data_id_t *p_id, uint32_t *p_start_addr)
{
    if (!p_id)
    {
        return false;
    }

    *p_start_addr = 0;  // 多运动起始偏移地址都是0

    return true;
}

bool mul_sport_get_data_item_info(data_id_t *p_id, uint32_t *p_start_addr, size_t *p_data_len)
{
    if (!p_id)
    {
        return false;
    }

    mul_sport_get_data_len(p_id, p_data_len);

    *p_start_addr = 0;  // 多运动起始偏移地址都是0

    return true;
}

bool mul_sport_read_upload_data(data_id_t *p_id, uint32_t read_addr, uint8_t *buf_ptr, size_t read_len)
{
    if (!p_id)
    {
        return false;
    }

    mul_sport_dbg_log("[mul sport] read data, data_len = %d", read_len);
    
    switch (p_id->type_desc.type)
    {
        case ENUM_SPORT_DATA_T:
            app_read_multi_motion_data(p_id, buf_ptr, read_len, read_addr);
            break;
        default:
            return false;
    }

    return true;
}

bool mul_sport_delete_id(const data_id_t *p_id)
{
    bool ret_flag = false;

    if (!p_id)
    {
        return false;
    }

    switch (p_id->type_desc.type)
    {
        case ENUM_SPORT_DATA_T:
            ret_flag = app_del_multi_motion_id(p_id);
            break;
        default:
            ret_flag = false;
            break;
    }

    return ret_flag;
}
//

#else


void MUL_SPORT_WEAK mul_sport_set_has_reached_last_km(void) {return;}

void MUL_SPORT_WEAK mul_sport_set_has_reached_last_mile(void) {return;}

void MUL_SPORT_WEAK mul_sport_set_mul_sport_cnt(uint32_t sport_time_cnt) {return;}

void mul_sport_set_sub_sport_type(Sport_Type_Type sport_type) {return;}

Sport_Type_Type mul_sport_get_sub_sport_type(void) {return ST_NONE;}

void mul_sport_set_mul_sport_end_time(utc_time_t timestamp) {return;}

multi_motion_ret MUL_SPORT_WEAK mul_sport_get_storage_space_status(void) {return MULTI_MOTION_SUCCESS;}

bool MUL_SPORT_WEAK mul_sport_recycle_the_first_sport_index(void) {return true;}

bool MUL_SPORT_WEAK mul_sport_new_sport_file(utc_time_t sport_start_timestamp) {return true;}

multi_motion_ret mul_sport_write_sport_data(void) {return MULTI_MOTION_SUCCESS;}

multi_motion_ret MUL_SPORT_WEAK mul_sport_write_gps_data
    (uint32_t timestamp, float gps_longitude, float gps_latitude) {return MULTI_MOTION_SUCCESS;}
    
multi_motion_ret mul_sport_app_write_sport_data
    (void *p_input_data, void *p_input_data_args) {return MULTI_MOTION_SUCCESS;}

multi_motion_ret mul_sport_app_set_sport_repo
    (void *p_input_data, void *p_input_data_args) {return MULTI_MOTION_SUCCESS;}

p_data_id_t MUL_SPORT_WEAK mul_sport_get_cur_sport_data_id(void) {p_data_id_t tmp_id = {0}; return tmp_id;}
void MUL_SPORT_WEAK mul_sport_clear_cur_sport_id(void) {return;}
bool MUL_SPORT_WEAK mul_sport_resume_process(void) {return true;}
bool MUL_SPORT_WEAK mul_sport_save_cur_sport_file(void) {return true;}
bool MUL_SPORT_WEAK mul_sport_init(void) {return true;}
bool MUL_SPORT_WEAK mul_sport_deinit(void) {return true;}
bool MUL_SPORT_WEAK mul_sport_save_data_process(void) {return true;}
bool MUL_SPORT_WEAK mul_sport_get_intraday_valid_id(data_id_t *p_id, uint32_t *id_nums, const uint32_t max_id_nums) {return true;}
bool MUL_SPORT_WEAK mul_sport_get_sport_historical_valid_id(data_id_t *p_id, uint32_t *id_nums, const uint32_t max_id_nums) {return true;}
bool MUL_SPORT_WEAK mul_sport_get_data_len(const data_id_t *p_id, uint32_t *data_len) {return true;}
bool mul_sport_get_data_header_ptr(data_id_t *p_id, uint8_t **pp_header_data, size_t *header_data_len) {return true;}
bool mul_sport_get_data_start_addr(data_id_t *p_id, uint32_t *p_start_addr) {return true;}
bool mul_sport_get_data_item_info(data_id_t *p_id, uint32_t *p_start_addr, size_t *p_data_len) {return true;}
bool mul_sport_read_upload_data(data_id_t *p_id, uint32_t read_addr, uint8_t *buf_ptr, size_t read_len) {return true;}
bool MUL_SPORT_WEAK mul_sport_delete_id(const data_id_t *p_id) {return true;}

#endif /* FLASH_MANAGER_SWITCH */
