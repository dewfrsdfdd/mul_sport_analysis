#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#include <stdio.h>
#include <string.h>

#include "multi_motion_public_part.h"

#include "multi_motion_gps_handle.h"
#include "multi_motion_sport_handle.h"



/* 多运动数据存储扇区表, 用于记录扇区块是否已经被使用 */
static multi_motion_sector_table_t MUL_SPORT_ALIGN_WAY g_sector_table = {.remind_sector_num = MULTI_MOTION_DATA_SECTOR_NUM, };


multi_motion_sector_table_t * get_multi_motion_sector_table(void)
{
        return &g_sector_table;
}

bool multi_motion_read_motion_sector_table(void)
{
    multi_motion_data_idx_table_t   *p_multi_motion_data_idx_table;  // 多运动数据索引表

#if GPS_DATA_MANAGER_SWITCH
    multi_motion_gps_idx_table_t    *p_multi_motion_gps_idx_table;   // gps索引表
#endif

    p_multi_motion_data_idx_table = get_multi_motion_idx_table();

#if GPS_DATA_MANAGER_SWITCH
    p_multi_motion_gps_idx_table  = get_multi_motion_gps_idx_table();
#endif

    free_all_mul_motion_sector();

    if (p_multi_motion_data_idx_table->magic_number != MUL_SPORT_MAGIC_NUMBER)
    {
        memset(p_multi_motion_data_idx_table, 0, sizeof(multi_motion_data_idx_table_t));

#if GPS_DATA_MANAGER_SWITCH
        memset(p_multi_motion_gps_idx_table, 0, sizeof(multi_motion_gps_idx_table_t));
#endif

        return true;
    }

#if GPS_DATA_MANAGER_SWITCH
    if (p_multi_motion_gps_idx_table->magic_number != MUL_SPORT_MAGIC_NUMBER)
    {
        memset(p_multi_motion_gps_idx_table, 0, sizeof(multi_motion_gps_idx_table_t));
    }
#endif

    bool read_sector_table_status = false;

    if (p_multi_motion_data_idx_table->idx_nums == (uint16_t)-1)
    {

#if GPS_DATA_MANAGER_SWITCH
        p_multi_motion_gps_idx_table->idx_nums = (uint16_t)-1;
#endif
        read_sector_table_status = true;
    }
    else
    {
        do
        {
            read_sector_table_status = read_motion_sector_table();
            if (!read_sector_table_status)
            {
                break;
            }

#if GPS_DATA_MANAGER_SWITCH
            read_sector_table_status = read_multi_motion_gps_sector_table();
#endif

        } while (0);

        if (!read_sector_table_status)
        {
            multi_motion_deinit();
            multi_motion_read_idx_table();
        }
    }

    return read_sector_table_status;
}

bool multi_motion_clear_abnormal_multi_motion_id(void)
{
    bool ret_flag = false;
    bool clear_abnormal_id_multi_motion_status;

#if GPS_DATA_MANAGER_SWITCH
    bool clear_abnormal_id_multi_motion_gps_status;
#endif

    clear_abnormal_id_multi_motion_status = clear_abnormal_multi_motion_id();

#if GPS_DATA_MANAGER_SWITCH
    clear_abnormal_id_multi_motion_gps_status = clear_abnormal_multi_motion_gps_id();
#endif

#if GPS_DATA_MANAGER_SWITCH
    if (clear_abnormal_id_multi_motion_status
        || clear_abnormal_id_multi_motion_gps_status)
#else
    if (clear_abnormal_id_multi_motion_status)
#endif
    {
        multi_motion_write_idx_table();
    }

    ret_flag = true;

    return ret_flag;
}

bool multi_motion_read_idx_table(void)
{
    bool ret_flag = false;

    read_multi_motion_idx_table();

#if GPS_DATA_MANAGER_SWITCH
    read_multi_motion_gps_idx_table();
#endif

    ret_flag = true;

    return ret_flag;
}

bool multi_motion_init(void)
{
    bool ret_flag = false;

    multi_motion_read_idx_table();

    multi_motion_read_motion_sector_table();

    multi_motion_clear_abnormal_multi_motion_id();

    app_clear_cur_sport_data_id();
    multi_motion_delete_cur_sport_list_item();

#if GPS_DATA_MANAGER_SWITCH
    app_clear_gps_global_var();
    app_clear_cur_gps_data_id();
    app_delete_cur_gps_handle_obj();
#endif

    ret_flag = true;

    return ret_flag;
}

bool multi_motion_deinit(void)
{
    bool ret_flag = false;

    free_all_mul_motion_sector();
    erase_multi_motion_idx_table();

    ret_flag = true;

    return ret_flag;
}

bool multi_motion_delete_sport_file(data_id_t delete_id)
{
    bool ret_flag;
    Sport_Type_Type sub_sport_type = ST_NONE;

#if GPS_DATA_MANAGER_SWITCH
    data_id_t gps_id;
    gps_id = delete_id;

    gps_id.type_desc.data_type = ENUM_SPORT_GPS_DATA_T;
    del_gps_file(&gps_id);
#endif

    data_id_t sport_id;
    sport_id = delete_id;

    sport_id.type_desc.data_type = ENUM_POINT_DATA_T;

    del_sport_file(&sport_id);

    multi_motion_get_sub_sport_type(&sport_id, &sub_sport_type);

    mul_sport_delete_sport_file_succeed_cb(sport_id, sub_sport_type);    

    ret_flag = true;
   
    return ret_flag;
}

bool multi_motion_write_idx_table(void)
{
    bool ret_flag = false;

    fm_erase_sector(MULTI_MOTION_IDX_TABLE_SECTOR_ID);

    write_multi_motion_idx_table();

#if GPS_DATA_MANAGER_SWITCH
    write_multi_motion_gps_idx_table();
#endif

    ret_flag = true;

    return ret_flag;
}

bool multi_motion_exceed_storage_addr_handler(uint32_t addr, uint32_t data_len)
{
    const uint32_t upper_border_addr = fm_get_sector_addr(MULTI_MOTION_SECTOR_LIST_ID) + data_len;                      // 地址上边界往下移data_len个长度
    const uint32_t Lower_border_addr = fm_get_sector_addr(MULTI_MOTION_SECTOR_LIST_ID + MULTI_MOTION_DATA_SECTOR_NUM);  // 地址下边界

    if (fm_is_exceed_addr_range(upper_border_addr, Lower_border_addr, addr))
    {
        /* Exception Handling */
        multi_motion_deinit();
        multi_motion_init();

        return true;
    }
    else
    {
        return false;
    }
}

#endif /* FLASH_MANAGER_SWITCH */
