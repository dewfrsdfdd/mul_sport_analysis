#include <stdio.h>
#include <string.h>

#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#include "multi_motion_sport_handle.h"
#include "multi_motion_gps_handle.h"
#include "multi_motion_data_rollback_handle.h"
#include "mul_sport_factory.h"
#include "mul_sport_sector_manager.h"
#include "mul_sport_common.h"
#include "mul_sport_platform.h"
#include "multi_motion_public_part.h"
#include "ms_sport_category_t4.h"
#include "ms_sport_category_t9.h"
#include "ms_sport_category_t10.h"

#define MS_TMP_READ_BUF_SIZE    (256)

typedef struct
{
#define MUL_SPORT_SAVE_MIN_INTERVAL 1   // 间隔多少分钟存储一次数据
#define MUL_SPORT_BUF_SIZE (4 * 60 * MUL_SPORT_SAVE_MIN_INTERVAL)

    bool     buf_is_full_flg;
    uint16_t write_buf_len;
    uint8_t  mul_sport_buf[MUL_SPORT_BUF_SIZE];
} mul_sport_buf_t;


static volatile multi_motion_data_idx_table_t MUL_SPORT_ALIGN_WAY g_multi_motion_idx_table;

static volatile data_id_t MUL_SPORT_ALIGN_WAY g_cur_sport_data_id;

static volatile uint32_t g_prev_calorie = 0;
static volatile uint32_t g_prev_step = 0;
static volatile uint32_t g_prev_distance = 0;
static volatile uint32_t g_prev_cyclic_sport_counter = 0;

static volatile uint32_t g_mul_sport_start_time = 0;
static volatile uint32_t g_mul_sport_end_time = 0;
static volatile uint32_t g_recovery_motion_timestamp = 0;
static volatile uint32_t g_mul_sport_cnt = 0;
static volatile uint32_t g_swimming_turn_cnt = 0;
static volatile uint32_t g_fixed_data_base_pos = 0;
static volatile float    g_initialize_altitude = 0;
static volatile uint32_t g_mul_sport_total_point_cnts;      // 总打点条数
static volatile uint32_t g_mul_sport_segment_distance;      // 本段总里程
static volatile uint16_t g_mul_sport_segment_count;      // 本段总数
static volatile Sport_Type_Type g_sub_sport_type = ST_NONE;
static volatile Sport_Interval_Training_Type g_sit_type = SIT_NONE;
static volatile Sport_Interval_Training_Type g_next_sit_type = SIT_NONE;
static volatile bool g_is_change_sit_type = false;


static volatile bool  g_is_up_km_status = false;     // 判断当前是否为上公立状态
static volatile bool  g_is_up_mile_status = false;   // 判断当前是否为上英里状态

static volatile mul_sport_buf_t MUL_SPORT_ALIGN_WAY g_mul_sport_buf_obj;

static volatile ms_idx_pos_t MUL_SPORT_ALIGN_WAY g_ms_idx_pos;

static volatile p_ms_abstract_sport_list_t MUL_SPORT_ALIGN_WAY g_p_sport_list_item_obj = NULL;

static volatile ms_idx_pos_t MUL_SPORT_ALIGN_WAY g_ms_idx_pos = {
    .magic_number = MUL_SPORT_MAGIC_NUMBER,
    .version      = MUL_SPORT_VER_1,
    .cur_idx_pos  = 0,
};



//=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 声明
void set_sport_id(uint16_t, const data_id_t *);
data_id_t get_sport_id(uint16_t);
uint16_t get_sport_sector_nums(uint16_t);
uint16_t get_sport_sector_id(uint16_t, uint16_t);
uint16_t get_next_sport_id_pos(uint16_t);
uint16_t get_next_valid_id_pos(void);
uint32_t get_sport_data_len(uint16_t);
bool set_cur_sport_data_id(const data_id_t *);

//=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//

multi_motion_data_idx_table_t *get_multi_motion_idx_table(void)
{
    return (multi_motion_data_idx_table_t *)&g_multi_motion_idx_table;
}

void read_multi_motion_idx_table(void)
{
    uint32_t start_addr;
    uint32_t head_addr;
    uint32_t data_addr;
    flash_storage_head_t flash_storage_head;

    start_addr = fm_get_sector_addr(MULTI_MOTION_IDX_TABLE_SECTOR_ID);

    head_addr = start_addr;
    data_addr = start_addr + sizeof(flash_storage_head_t);

    memset(&flash_storage_head, 0, sizeof(flash_storage_head_t));

    read_info_data(&flash_storage_head, head_addr, sizeof(flash_storage_head_t));

    if (flash_storage_head.magic_num == MUL_SPORT_MAGIC_NUMBER
        && flash_storage_head.version == MUL_SPORT_VER_1
        && flash_storage_head.store_flash_flag == STORED_DATA_NOT_UPLOADED
        && flash_storage_head.data_len == sizeof(multi_motion_data_idx_table_t))
    {
        read_info_data(&g_multi_motion_idx_table, data_addr, sizeof(multi_motion_data_idx_table_t));        

        mul_sport_dbg_log("g_multi_motion_idx_table r_succeed, idx_nums = %d, magic_num = %x, ver = %d, flag = %x, crc = %x",
                           g_multi_motion_idx_table.idx_nums,
                           g_multi_motion_idx_table.magic_number,
                           g_multi_motion_idx_table.version,
                           g_multi_motion_idx_table.store_flash_flag,
                           g_multi_motion_idx_table.flash_crc);
    }
    else
    {
        memset((void *)&g_multi_motion_idx_table, 0, sizeof(multi_motion_data_idx_table_t));

        mul_sport_dbg_log("g_multi_motion_idx_table read idx data failed");
    }
}

void write_multi_motion_idx_table(void)
{
    uint32_t start_addr;
    uint32_t head_addr;
    uint32_t data_addr;
    flash_storage_head_t flash_storage_head;
    bool write_flag;

    start_addr = fm_get_sector_addr(MULTI_MOTION_IDX_TABLE_SECTOR_ID);

    head_addr = start_addr;
    data_addr = start_addr + sizeof(flash_storage_head_t);

    g_multi_motion_idx_table.magic_number     = MUL_SPORT_MAGIC_NUMBER;
    g_multi_motion_idx_table.version          = MUL_SPORT_VER_1;
    g_multi_motion_idx_table.store_flash_flag = STORED_DATA_NOT_UPLOADED;
    g_multi_motion_idx_table.flash_crc        = 0x0000;

    write_flag = write_info_data(&g_multi_motion_idx_table, data_addr, sizeof(multi_motion_data_idx_table_t));

    if (write_flag)
    {
        flash_storage_head.magic_num = MUL_SPORT_MAGIC_NUMBER;
        flash_storage_head.version = MUL_SPORT_VER_1;
        flash_storage_head.store_flash_flag = STORED_DATA_NOT_UPLOADED;
        flash_storage_head.data_len = sizeof(multi_motion_data_idx_table_t);
        flash_storage_head.flash_crc = 0x0000;

        mul_sport_dbg_log("g_multi_motion_idx_table write idx data succeed");
    }
    else
    {
        flash_storage_head.magic_num = 0xFF;
        flash_storage_head.version = 0xFF;
        flash_storage_head.store_flash_flag = NO_STORE_DATA;
        flash_storage_head.data_len = 0;
        flash_storage_head.flash_crc = 0xFFFF;

        mul_sport_dbg_log("g_multi_motion_idx_table write idx data failed");
    }

    write_info_data(&flash_storage_head, head_addr, sizeof(flash_storage_head));
}

void erase_multi_motion_idx_table(void)
{
    fm_erase_sector(MULTI_MOTION_IDX_TABLE_SECTOR_ID);
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
bool read_motion_sector_table(void)
{
    uint16_t sector_num;
    uint16_t tmp_idx_pos = 0;

    multi_motion_sector_table_t *p_multi_motion_sector_table;

    p_multi_motion_sector_table = get_multi_motion_sector_table();

    if (g_multi_motion_idx_table.idx_nums == (uint16_t)-1)
    {
        return true;
    }

    for (uint16_t i = 0; i < g_multi_motion_idx_table.idx_nums && tmp_idx_pos < MULTI_IDX_NUMS; i++)
    {
        sector_num = get_sport_sector_nums(tmp_idx_pos);

        uint16_t sector_id;
        for (uint16_t k = 0; k < sector_num; k++)
        {
            sector_id = get_sport_sector_id(tmp_idx_pos, k);

            if (sector_id - MULTI_MOTION_SECTOR_LIST_ID >= MULTI_MOTION_DATA_SECTOR_NUM)
            {
                return false;
            }

            p_multi_motion_sector_table->sector_table[sector_id - MULTI_MOTION_SECTOR_LIST_ID] = 1;
        }

        p_multi_motion_sector_table->remind_sector_num -= sector_num;

        if (p_multi_motion_sector_table->remind_sector_num < 0) // 正常运行的情况下remind_sector_num永远不会小于0
        {
            p_multi_motion_sector_table->remind_sector_num = 0;
        }

        tmp_idx_pos = get_next_sport_id_pos(tmp_idx_pos);
    }

    return true;
}

static bool alloc_available_sector(uint16_t *sector_id)
{
    uint32_t rand_pos  = mul_sport_get_rand() % MULTI_MOTION_DATA_SECTOR_NUM;
    uint32_t final_pos = 0;
    bool     ret_val   = false;

    multi_motion_sector_table_t * p_multi_motion_sector_table;

    p_multi_motion_sector_table = get_multi_motion_sector_table();

    if (rand_pos < MULTI_MOTION_DATA_SECTOR_NUM
        && !p_multi_motion_sector_table->sector_table[rand_pos])
    {
        final_pos = rand_pos;
        ret_val   = true;
    }
    else
    {
        for (uint16_t i = 0; i < MULTI_MOTION_DATA_SECTOR_NUM; i++)
        {
            if (!p_multi_motion_sector_table->sector_table[i])
            {
                final_pos = i;
                ret_val = true;

                break;
            }
        }
    }

    if (ret_val)
    {
        p_multi_motion_sector_table->sector_table[final_pos] = 1;
        p_multi_motion_sector_table->remind_sector_num--;

        if (p_multi_motion_sector_table->remind_sector_num < 0)
        {
                p_multi_motion_sector_table->remind_sector_num = 0;
        }

        *sector_id = final_pos + MULTI_MOTION_SECTOR_LIST_ID;
    }

    return ret_val;
}

static bool __free_sector(uint16_t sector_id)
{
    multi_motion_sector_table_t * p_multi_motion_sector_table;

    p_multi_motion_sector_table = get_multi_motion_sector_table();

    if (sector_id - MULTI_MOTION_SECTOR_LIST_ID >= MULTI_MOTION_DATA_SECTOR_NUM
        || sector_id < MULTI_MOTION_SECTOR_LIST_ID)
    {
        return false;
    }

    if (!p_multi_motion_sector_table->sector_table[sector_id - MULTI_MOTION_SECTOR_LIST_ID])
    {
        return false;
    }

    p_multi_motion_sector_table->sector_table[sector_id - MULTI_MOTION_SECTOR_LIST_ID] = 0;
    p_multi_motion_sector_table->remind_sector_num++;

    return true;
}

void free_all_mul_motion_sector(void)
{
    multi_motion_sector_table_t * p_multi_motion_sector_table;

    p_multi_motion_sector_table = get_multi_motion_sector_table();

    for (uint16_t i = 0; i < MULTI_MOTION_DATA_SECTOR_NUM; i++)
    {
        p_multi_motion_sector_table->sector_table[i] = 0;
    }

    p_multi_motion_sector_table->remind_sector_num = MULTI_MOTION_DATA_SECTOR_NUM;
}

static bool exceed_storage_addr_handler(uint32_t addr, uint32_t data_len)
{
    return multi_motion_exceed_storage_addr_handler(addr, data_len);
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
/* 判断是否还可以写入运动数据 */
bool is_can_write_sport_data(uint16_t idx_pos)
{
    multi_motion_sector_table_t * p_multi_motion_sector_table;

    p_multi_motion_sector_table = get_multi_motion_sector_table();

    /* 空间已用尽 */
    if (!p_multi_motion_sector_table->remind_sector_num
        || get_next_sport_id_pos(idx_pos) + SECTOR_NUM_SIZE > MULTI_IDX_NUMS)
    {
        return false;
    }

    return true;
}

/* 能否写入报告 */
bool is_can_app_write_sport_report(uint16_t idx_pos, uint32_t data_len)
{
    multi_motion_sector_table_t * p_multi_motion_sector_table;

    p_multi_motion_sector_table = get_multi_motion_sector_table();

    /* 空间已用尽 */
    if (!p_multi_motion_sector_table->remind_sector_num
        || get_next_sport_id_pos(idx_pos) + SECTOR_NUM_SIZE > MULTI_IDX_NUMS)
    {
        if (get_sport_data_len(idx_pos) % MS_SECTOR_SIZE + data_len >= MS_SECTOR_SIZE - SPORT_REPORT_MAX_BYTES
            && (get_sport_data_len(idx_pos) / MS_SECTOR_SIZE) + 1 == get_sport_sector_nums(idx_pos))
        {
            return false;
        }
    }

    return true;
}

bool is_space_will_full(void)
{
    multi_motion_sector_table_t * p_multi_motion_sector_table;

    p_multi_motion_sector_table = get_multi_motion_sector_table();

    /* 空间即将用尽 */
    if (p_multi_motion_sector_table->remind_sector_num <= 8
        || get_next_valid_id_pos() + 3 * MIN_SPORT_IDX_SIZE > MULTI_IDX_NUMS
        || (g_multi_motion_idx_table.idx_nums != (uint16_t)-1 && g_multi_motion_idx_table.idx_nums >= MUL_SPORT_POINT_WILL_FULL_NUMS))
    {
        return true;
    }

    return false;
}

bool is_space_was_full(void)
{
    multi_motion_sector_table_t * p_multi_motion_sector_table;

    p_multi_motion_sector_table = get_multi_motion_sector_table();

    /* 空间已经用尽 */
    if (!p_multi_motion_sector_table->remind_sector_num
        || get_next_valid_id_pos() +  MIN_SPORT_IDX_SIZE > MULTI_IDX_NUMS
        || (g_multi_motion_idx_table.idx_nums != (uint16_t)-1 && g_multi_motion_idx_table.idx_nums >= MUL_SPORT_POINT_WAS_FULL_NUMS))
    {
        return true;
    }

    return false;
}

bool is_space_was_full_by_auto_sport(void)
{
    multi_motion_sector_table_t * p_multi_motion_sector_table;

    p_multi_motion_sector_table = get_multi_motion_sector_table();

    /* 空间已经用尽 */
    if (p_multi_motion_sector_table->remind_sector_num < MIN_AUTO_SPORT_SECTOR_NUMS \
        || get_next_valid_id_pos() +  MIN_AUTO_SPORT_IDX_SIZE > MULTI_IDX_NUMS \
        || (g_multi_motion_idx_table.idx_nums != (uint16_t)-1 && g_multi_motion_idx_table.idx_nums >= MUL_SPORT_POINT_WAS_FULL_NUMS))
    {
        return true;
    }

    return false;
}



bool is_doing_sports()
{
    return g_cur_sport_data_id.timestamp;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
bool get_id_pos_by_id(const data_id_t *p_id, uint16_t *id_pos)
{
    if (g_multi_motion_idx_table.idx_nums == (uint16_t)-1)
    {
        return false;
    }

    data_id_t tmp_id;
    uint16_t tmp_idx_pos = 0;

    for (uint16_t i = 0; i < g_multi_motion_idx_table.idx_nums && tmp_idx_pos < MULTI_IDX_NUMS; i++)
    {
        tmp_id = get_sport_id(tmp_idx_pos);

        if (tmp_id.timestamp == (*p_id).timestamp
            && tmp_id.timezone == (*p_id).timezone
            && tmp_id.type_desc.specific_type == (*p_id).type_desc.specific_type)   // TODO: sport 需要添加百大运动子类型
        {
            if (id_pos)
            {
                *id_pos = tmp_idx_pos;
            }

            return true;
        }

        tmp_idx_pos = get_next_sport_id_pos(tmp_idx_pos);
    }

    return false;
}


uint16_t get_next_valid_id_pos(void)
{
    uint16_t tmp_idx_pos = 0;
    uint16_t ret_idx_pos = 0;

    if (g_multi_motion_idx_table.idx_nums == (uint16_t)-1)
    {
        return ret_idx_pos;
    }

    for (uint16_t i = 0; i < g_multi_motion_idx_table.idx_nums && tmp_idx_pos < MULTI_IDX_NUMS; i++)
    {
        tmp_idx_pos = get_next_sport_id_pos(tmp_idx_pos);
    }

    ret_idx_pos = tmp_idx_pos;

    return ret_idx_pos;
}

bool alloc_id_pos(uint16_t *id_pos)
{
    uint16_t tmp_idx_pos;

    tmp_idx_pos = get_next_valid_id_pos();

    if (!tmp_idx_pos)
    {
        //free_all_mul_motion_sector();
    }

    if (tmp_idx_pos + MIN_SPORT_IDX_SIZE > MULTI_IDX_NUMS)
    {
        return false;
    }

    *id_pos = tmp_idx_pos;

    return true;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// set get
void set_sport_id(uint16_t idx_pos, const data_id_t *p_id)
{
    *(data_id_t *)(g_multi_motion_idx_table.idx_data + idx_pos) = *p_id;
}

data_id_t get_sport_id(uint16_t idx_pos)
{
    return *(data_id_t *)(g_multi_motion_idx_table.idx_data + idx_pos);
}

uint16_t get_next_sport_id_pos(uint16_t idx_pos)
{
    return (uint16_t)(idx_pos + SECTOR_NUM_POS + get_sport_sector_nums(idx_pos) * SECTOR_NUM_SIZE);
}

void set_sport_report_id(uint16_t idx_pos, const data_id_t *p_id)
{
    *(data_id_t *)(g_multi_motion_idx_table.idx_data + idx_pos + SPORT_REPORT_ID_POS) = *p_id;
}

data_id_t get_sport_report_id(uint16_t idx_pos)
{
    return *(data_id_t *)(g_multi_motion_idx_table.idx_data + idx_pos + SPORT_REPORT_ID_POS);
}

void set_sport_data_len(uint16_t idx_pos, uint32_t sport_data_len)
{
    *(uint32_t *)(g_multi_motion_idx_table.idx_data + idx_pos + SPORT_DATA_LEN_POS) = sport_data_len;
}

uint32_t get_sport_data_len(uint16_t idx_pos)
{
    return *(uint32_t *)(g_multi_motion_idx_table.idx_data + idx_pos + SPORT_DATA_LEN_POS);
}

void set_sport_data_flag(uint16_t idx_pos, store_flag_type_t flag)
{
    *(store_flag_type_t *)(g_multi_motion_idx_table.idx_data + idx_pos + SPORT_DATA_FLAG_POS) = flag;
}

store_flag_type_t get_sport_data_flag(uint16_t idx_pos)
{
    return *(store_flag_type_t *)(g_multi_motion_idx_table.idx_data + idx_pos + SPORT_DATA_FLAG_POS);
}

void set_sport_report_flag(uint16_t idx_pos, store_flag_type_t flag)
{
    *(store_flag_type_t *)(g_multi_motion_idx_table.idx_data + idx_pos + SPORT_REPORT_FLAG_POS) = flag;
}

store_flag_type_t get_sport_report_flag(uint16_t idx_pos)
{
    return *(store_flag_type_t *)(g_multi_motion_idx_table.idx_data + idx_pos + SPORT_REPORT_FLAG_POS);
}

void set_sport_report_len(uint16_t idx_pos, uint8_t report_len)
{
    *(uint8_t *)(g_multi_motion_idx_table.idx_data + idx_pos + SPORT_REPORT_LEN_POS) = report_len;
}

uint8_t get_sport_report_len(uint16_t idx_pos)
{
    return *(uint8_t *)(g_multi_motion_idx_table.idx_data + idx_pos + SPORT_REPORT_LEN_POS);
}

void set_sport_sector_nums(uint16_t idx_pos, uint16_t sector_nums)
{
    *(uint16_t *)(g_multi_motion_idx_table.idx_data + idx_pos + SECTOR_NUMS_POS) = sector_nums;
}

uint16_t get_sport_sector_nums(uint16_t idx_pos)
{
    return *(uint16_t *)(g_multi_motion_idx_table.idx_data + idx_pos + SECTOR_NUMS_POS);
}

/* idx 从0开始 */
void set_sport_sector_id(uint16_t idx_pos, uint16_t idx, uint16_t sector_id)
{
    *(uint16_t *)(g_multi_motion_idx_table.idx_data + idx_pos + SECTOR_NUM_POS + idx * SECTOR_NUM_SIZE) = sector_id;
}

/* idx 从0开始 */
uint16_t get_sport_sector_id(uint16_t idx_pos, uint16_t idx)
{
    return *(uint16_t *)(g_multi_motion_idx_table.idx_data + idx_pos + SECTOR_NUM_POS + idx * SECTOR_NUM_SIZE);
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
bool add_new_sport_idx(const data_id_t *p_id, uint16_t *idx_pos)
{
    uint16_t id_pos;
    uint16_t sector_id;
    uint16_t new_idx_pos;
    bool     ret_flag = false;

    if (!idx_pos)
    {
        return ret_flag;
    }

    /* 判断传进来的id是否已经在索引表中存在 */
    if (get_id_pos_by_id(p_id, &id_pos))
    {
        multi_motion_delete_sport_file(*p_id);
    }

    if (!alloc_id_pos(&new_idx_pos))
    {
        return ret_flag;
    }

    if (!alloc_available_sector(&sector_id))
    {
        return ret_flag;
    }

    /* 写入数据索引ID，写入运动数据长度为0，写入运动报告标志位为0xFF，写入占用扇区数量为1，分配对应的扇区编号，写入对应扇区编号 */
    set_sport_id(new_idx_pos, p_id);
    set_sport_data_flag(new_idx_pos, STORED_DATA_NOT_UPLOADED);
    set_sport_data_len(new_idx_pos, 0);
    set_sport_report_flag(new_idx_pos, NO_STORE_DATA);
    set_sport_sector_nums(new_idx_pos, 1);

    set_sport_sector_id(new_idx_pos, 0, sector_id);
    fm_erase_sector(sector_id);

    if (g_multi_motion_idx_table.idx_nums == (uint16_t)-1)
    {
        g_multi_motion_idx_table.idx_nums = 1;
    }
    else
    {
        g_multi_motion_idx_table.idx_nums++;
    }

    *idx_pos = new_idx_pos;

    ret_flag = true;

    return ret_flag;
}

//=====================================================
// 多运动读写
multi_motion_ret write_sport_data(uint16_t idx_pos, const void *pdata, uint32_t data_len, uint32_t offset, bool flag)
{
    uint32_t sector_nums;
    uint32_t i;
    uint16_t write_sector_id;
    uint32_t write_sector_addr;
    uint32_t write_offset = offset;

    /* 获得扇区数量 */
    sector_nums = get_sport_sector_nums(idx_pos);

    for (i = 0; i < data_len;)
    {
        uint32_t left_space = MS_SECTOR_SIZE - (write_offset % MS_SECTOR_SIZE);
        uint32_t write_size = (data_len - i) < left_space ? (data_len - i) : left_space;

        while (write_offset / MS_SECTOR_SIZE >= sector_nums)
        {
            if (!is_can_write_sport_data(idx_pos))
            {
                return MULTI_MOTION_SPACE_WAS_FULLED;
            }

            if (!alloc_available_sector(&write_sector_id))
            {
                return MULTI_MOTION_SPACE_WAS_FULLED;
            }

            fm_erase_sector(write_sector_id);
            set_sport_sector_id(idx_pos, sector_nums, write_sector_id);
            sector_nums++;
            set_sport_sector_nums(idx_pos, sector_nums);
        }

        if(flag)
        {
            if (!is_can_app_write_sport_report(idx_pos, data_len - i))
            {
                return MULTI_MOTION_SPACE_WAS_FULLED;
            }
        }

        write_sector_id =  get_sport_sector_id(idx_pos, (write_offset / MS_SECTOR_SIZE) % sector_nums);

        write_sector_addr = fm_get_sector_addr(write_sector_id);   // 根据扇区的id号, 获得扇区的起始地址

        if (exceed_storage_addr_handler(write_sector_addr + (write_offset % MS_SECTOR_SIZE) + write_size,
                                        write_size))
        {
            return MULTI_MOTION_ERROR;
        }

        write_info_data(pdata + i, write_sector_addr + (write_offset % MS_SECTOR_SIZE), write_size);

#if DATA_ROLLBACK_SWITCH
        bool ret = data_rollback_data_check((uint8_t *)pdata + i, write_sector_addr, write_size, write_offset);

        if (!ret)
        {
            return MULTI_MOTION_WRITE_FAILED;
        }
#endif

        i += write_size;
        write_offset += write_size;
    }

    set_sport_data_len(idx_pos,
                       write_offset < get_sport_data_len(idx_pos) ? get_sport_data_len(idx_pos) : write_offset);

    return MULTI_MOTION_WRITE_SUCCESS;
}


bool read_sport_data(uint16_t idx_pos, void *pdata, uint32_t data_len, uint32_t offset)
{
    uint32_t i;
    uint32_t sport_data_len;
    uint32_t read_offset = offset;
    uint16_t sector_idx;
    uint16_t sector_num;
    uint32_t read_sector_id;
    uint32_t read_sector_addr;

    // 1.读取当前运动长度
    sport_data_len = get_sport_data_len(idx_pos);
    // 判断offset + data_len是否大于当前运动数据的长度
    if (read_offset + data_len > sport_data_len)
    {
        return false;
    }

    sector_num = get_sport_sector_nums(idx_pos);

    for (i = 0; i < data_len;)
    {
        sector_idx = read_offset / MS_SECTOR_SIZE;             // 获得所在扇区的索引

        if (sector_idx + 1 > sector_num)
        {
            return false;
        }

        read_sector_id = get_sport_sector_id(idx_pos, sector_idx);   // 根据索引获得扇区的实际id号

        read_sector_addr = fm_get_sector_addr(read_sector_id); // 根据扇区的id号, 获得扇区的起始地址

        uint32_t left_space = MS_SECTOR_SIZE - (read_offset % MS_SECTOR_SIZE);
        uint32_t read_size = (data_len - i) < left_space ? (data_len - i) : left_space;

        read_info_data(pdata + i, read_sector_addr + (read_offset % MS_SECTOR_SIZE), read_size);

        i += read_size;
        read_offset += read_size;
    }

    return true;

}


bool read_sport_report_data(uint16_t idx_pos, void *pdata, uint32_t data_len)
{
    uint32_t sport_data_len;

    if (get_sport_report_flag(idx_pos) == NO_STORE_DATA)
    {
        return false;
    }

    // 1.读取当前运动长度
    sport_data_len = get_sport_data_len(idx_pos);

    read_sport_data(idx_pos, pdata, data_len, sport_data_len - 1);

    return true;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// set get

bool set_cur_sport_data_id(const data_id_t *p_id)
{
    if (!p_id)
    {
        return false;
    }

    g_cur_sport_data_id = *p_id;

    return true;
}


p_data_id_t get_cur_sport_data_id(void)
{
    return (p_data_id_t)&g_cur_sport_data_id;
}
//
//

uint16_t get_sport_idx_nums(void)
{
    return g_multi_motion_idx_table.idx_nums;
}

void set_mul_sport_start_time(utc_time_t timestamp)
{
    g_mul_sport_start_time = timestamp;
}

utc_time_t get_mul_sport_start_time(void)
{
    return g_mul_sport_start_time;
}

void set_mul_sport_end_time(utc_time_t timestamp)
{
    g_mul_sport_end_time = timestamp;
}

utc_time_t get_mul_sport_end_time(void)
{
    return g_mul_sport_end_time;
}

uint32_t multi_motion_get_prev_calorie(void)
{
    return g_prev_calorie;
}

void multi_motion_set_prev_calorie(uint32_t new_calorie)
{
    g_prev_calorie = new_calorie;
}

uint32_t multi_motion_get_prev_step(void)
{
    return g_prev_step;
}

void multi_motion_set_prev_step(uint32_t new_step)
{
    g_prev_step = new_step;
}

uint32_t multi_motion_get_prev_distance(void)
{
    return g_prev_distance;
}

void multi_motion_set_prev_cyclic_sport_counter(uint32_t new_counter)
{
    g_prev_cyclic_sport_counter = new_counter;
}

uint32_t multi_motion_get_prev_cyclic_sport_counter(void)
{
    return g_prev_cyclic_sport_counter;
}

void multi_motion_set_prev_distance(uint32_t new_distance)
{
    g_prev_distance = new_distance;
}

void set_recovery_motion_timestamp(utc_time_t timestamp)
{
    g_recovery_motion_timestamp = timestamp;
}

uint32_t get_recovery_motion_timestamp(void)
{
    return g_recovery_motion_timestamp;
}

void set_mul_sport_cnt(uint32_t sport_time_cnt)
{
    g_mul_sport_cnt = sport_time_cnt;
}

uint32_t get_mul_sport_cnt(void)
{
    return g_mul_sport_cnt;
}

void set_mul_sport_total_point_cnts(uint32_t new_point_cnts)
{
    g_mul_sport_total_point_cnts = new_point_cnts;
}

void add_mul_sport_total_point_cnts(uint32_t delta_point_cnts)
{
    g_mul_sport_total_point_cnts += delta_point_cnts;
}

uint32_t get_mul_sport_total_points_cnts(void)
{
    return g_mul_sport_total_point_cnts;
}

void set_mul_sport_segment_distance(uint32_t new_point_distance)
{
    g_mul_sport_segment_distance = new_point_distance;
}

void add_mul_sport_segment_distance(uint32_t new_point_distance)
{
    g_mul_sport_segment_distance += new_point_distance;
}

uint32_t get_mul_sport_segment_distance(void)
{
    return g_mul_sport_segment_distance;
}

void set_mul_sport_segment_count(uint16_t new_point_count)
{
    g_mul_sport_segment_count = new_point_count;
}

void add_mul_sport_segment_count(uint32_t new_point_count)
{
    g_mul_sport_segment_count += new_point_count;
}

uint32_t get_mul_sport_segment_count(void)
{
    return g_mul_sport_segment_count;
}

void set_swimming_turn_cnt(uint32_t swimming_turn_cnt)
{
    g_swimming_turn_cnt = swimming_turn_cnt;
}

uint32_t get_swimming_turn_cnt(void)
{
    return g_swimming_turn_cnt;
}

void set_fixed_data_base_pos(uint32_t base_pos)
{
    g_fixed_data_base_pos = base_pos;
}

uint32_t get_fixed_data_base_pos(void)
{
    return g_fixed_data_base_pos;
}

void set_initialize_altitude(float new_altitude)
{
    g_initialize_altitude = new_altitude;
}

float get_initialize_altitude(void)
{
    return g_initialize_altitude;
}

Sport_Type_Type get_sub_sport_type(void)
{
    return g_sub_sport_type;
}

void set_sub_sport_type(Sport_Type_Type sport_type)
{
    g_sub_sport_type = sport_type;
}

void set_sport_sit_type(Sport_Interval_Training_Type sit_type)
{
    g_sit_type = sit_type;
}

Sport_Interval_Training_Type get_sport_sit_type(void)
{
    return g_sit_type;
}

void set_sport_next_sit_type(Sport_Interval_Training_Type sit_type)
{
    g_next_sit_type = sit_type;
}

Sport_Interval_Training_Type get_sport_next_sit_type(void)
{
    return g_next_sit_type;
}

void set_is_change_sit_type(bool is_change)
{
    g_is_change_sit_type = is_change;
}

bool get_is_change_sit_type(void)
{
    return g_is_change_sit_type;
}

void set_sport_data_len_offset(void)
{
    uint32_t data_len_offset = 0;

    if (!g_p_sport_list_item_obj)
    {
        return;
    }

    if (g_p_sport_list_item_obj->magic_number != MUL_SPORT_MAGIC_NUMBER)
    {
        return;
    }

    if (g_p_sport_list_item_obj->version == MUL_SPORT_VER_1)
    {
        p_ms_common_sport_list_v1_t p_common_sport_list_item     =
                                        (p_ms_common_sport_list_v1_t)g_p_sport_list_item_obj;

        data_len_offset = p_common_sport_list_item->ms_sport_list.ms_handle->sport_fixed_data_len;
    }

    if (is_can_app_write_sport_report(g_ms_idx_pos.cur_idx_pos, data_len_offset))
    {
        set_sport_data_len(g_ms_idx_pos.cur_idx_pos,
                           get_sport_data_len(g_ms_idx_pos.cur_idx_pos) + data_len_offset);
    }
}

bool app_get_id_pos_by_id(const data_id_t *p_id, uint16_t *idx_pos)
{
    uint16_t tmp_idx_pos;

    if (!get_id_pos_by_id(p_id, &tmp_idx_pos))
    {
        return false;
    }

    *idx_pos = tmp_idx_pos;

    return true;
}

bool app_get_id_by_idx(data_id_t *p_id, uint16_t idx)
{
    bool ret_flag = false;

    if (g_multi_motion_idx_table.idx_nums == (uint16_t)-1)
    {
        return ret_flag;
    }

    if ((idx + 1) > g_multi_motion_idx_table.idx_nums)
    {
        return ret_flag;
    }

    data_id_t tmp_id;
    uint16_t tmp_idx_pos = 0;

    for (uint16_t i = 0; i < idx && tmp_idx_pos < MULTI_IDX_NUMS; i++)
    {
        tmp_idx_pos = get_next_sport_id_pos(tmp_idx_pos);
    }

    if (tmp_idx_pos < MULTI_IDX_NUMS)
    {
        tmp_id = get_sport_id(tmp_idx_pos);

        *p_id = tmp_id;

        ret_flag = true;
    }

    return ret_flag;
}

void set_is_up_km_status(bool status)
{
    g_is_up_km_status = status;
}

bool get_is_up_km_status(void)
{
    return g_is_up_km_status;
}

void set_is_up_mile_status(bool status)
{
    g_is_up_mile_status = status;
}

bool get_is_up_mile_status(void)
{
    return g_is_up_mile_status;
}

uint32_t get_cur_sport_handle_data_len(void)
{
    if (!g_p_sport_list_item_obj)
    {
        return 0;
    }

    if (g_p_sport_list_item_obj->magic_number != MUL_SPORT_MAGIC_NUMBER)
    {
        return 0;
    }

    return get_sport_data_len(g_ms_idx_pos.cur_idx_pos);
}


//=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//

bool del_sport_file(const data_id_t *p_id)
{
    uint16_t tmp_id_pos = 0;
    uint16_t cur_id_pos = 0;
    bool ret_val = false;

    if (!app_get_id_pos_by_id(p_id, &cur_id_pos))
    {
        return ret_val;
    }


    if (g_p_sport_list_item_obj && g_p_sport_list_item_obj->magic_number == MUL_SPORT_MAGIC_NUMBER)
    {
        tmp_id_pos = g_ms_idx_pos.cur_idx_pos;
    }
    else
    {
        tmp_id_pos = cur_id_pos;
    }

    if (tmp_id_pos > cur_id_pos)
    {
        tmp_id_pos -= (get_next_sport_id_pos(cur_id_pos) - cur_id_pos);
    }

    /* 1.释放掉占用的扇区 */
    for (uint16_t i = 0; i < get_sport_sector_nums(cur_id_pos); i++)
    {
        __free_sector(get_sport_sector_id(cur_id_pos, i));
    }

    /* TODO: 这里要加互斥操作 start */

    /* 2.释放掉索引 */
    memmove((uint8_t *)g_multi_motion_idx_table.idx_data + cur_id_pos,
            (uint8_t *)g_multi_motion_idx_table.idx_data + get_next_sport_id_pos(cur_id_pos),
            MULTI_IDX_NUMS > get_next_sport_id_pos(cur_id_pos) ? MULTI_IDX_NUMS - get_next_sport_id_pos(cur_id_pos) : 0);

    if (g_p_sport_list_item_obj && g_p_sport_list_item_obj->magic_number == MUL_SPORT_MAGIC_NUMBER)
    {
        g_ms_idx_pos.cur_idx_pos = tmp_id_pos;
    }
    /* end */

    /* 3. 索引数减1 */
    if (g_multi_motion_idx_table.idx_nums)
    {
        g_multi_motion_idx_table.idx_nums--;
    }

    ret_val = true;

    return ret_val;
}

bool del_sport_file_by_idx_num(uint16_t idx_num)
{
    uint16_t tmp_id_pos = 0;
    uint16_t cur_id_pos = 0;
    bool ret_val = false;

    if (g_multi_motion_idx_table.idx_nums == (uint16_t)-1
        || idx_num > g_multi_motion_idx_table.idx_nums)
    {
        return ret_val;
    }

    for (uint16_t i = 0; i < idx_num && cur_id_pos < MULTI_IDX_NUMS; i++)
    {
        cur_id_pos = get_next_sport_id_pos(cur_id_pos);
    }

    if (g_p_sport_list_item_obj && g_p_sport_list_item_obj->magic_number == MUL_SPORT_MAGIC_NUMBER)
    {
        tmp_id_pos = g_ms_idx_pos.cur_idx_pos;
    }
    else
    {
        tmp_id_pos = cur_id_pos;
    }

    if (tmp_id_pos > cur_id_pos)
    {
        tmp_id_pos -= (get_next_sport_id_pos(cur_id_pos) - cur_id_pos);
    }

    /* 1.释放掉占用的扇区 */
    for (uint16_t i = 0; i < get_sport_sector_nums(cur_id_pos); i++)
    {
        __free_sector(get_sport_sector_id(cur_id_pos, i));
    }

    /* TODO: 这里要加互斥操作 start */

    /* 2.释放掉索引 */
    memmove((uint8_t *)g_multi_motion_idx_table.idx_data + cur_id_pos,
            (uint8_t *)g_multi_motion_idx_table.idx_data + get_next_sport_id_pos(cur_id_pos),
            MULTI_IDX_NUMS > get_next_sport_id_pos(cur_id_pos) ? MULTI_IDX_NUMS - get_next_sport_id_pos(cur_id_pos) : 0);

    if (g_p_sport_list_item_obj && g_p_sport_list_item_obj->magic_number == MUL_SPORT_MAGIC_NUMBER)
    {
        g_ms_idx_pos.cur_idx_pos = tmp_id_pos;
    }
    /* end */

    /* 3. 索引数减1 */
    if (g_multi_motion_idx_table.idx_nums)
    {
        g_multi_motion_idx_table.idx_nums--;
    }

    return true;
}

bool clear_abnormal_multi_motion_id(void)
{
    uint16_t tmp_idx_pos = 0;
    data_id_t tmp_data_id;
    bool is_modify_multi_motion_table = false;

    if (g_multi_motion_idx_table.idx_nums == (uint16_t)-1)
    {
        return is_modify_multi_motion_table;
    }

    tmp_idx_pos = 0;

    for (uint16_t i = 0; i < g_multi_motion_idx_table.idx_nums && tmp_idx_pos < MULTI_IDX_NUMS; i++)
    {
        if (get_sport_report_flag(tmp_idx_pos) == NO_STORE_DATA
            || (get_sport_data_flag(tmp_idx_pos) == STORED_DATA_AND_UPLOADED
                && get_sport_report_flag(tmp_idx_pos) == STORED_DATA_AND_UPLOADED)
            || !get_sport_data_len(tmp_idx_pos)
            || !get_sport_report_len(tmp_idx_pos))
        {
            tmp_data_id = get_sport_id(tmp_idx_pos);

            multi_motion_delete_sport_file(tmp_data_id);

            is_modify_multi_motion_table = true;
        }

        tmp_idx_pos = get_next_sport_id_pos(tmp_idx_pos);
    }

    return is_modify_multi_motion_table;
}

multi_motion_ret multi_motion_save_sport_data(void)
{
    multi_motion_ret ret_code = MULTI_MOTION_SUCCESS;

    if (g_mul_sport_buf_obj.write_buf_len)
    {
        ret_code = write_sport_data((uint16_t)g_ms_idx_pos.cur_idx_pos,
                                    (uint8_t *)g_mul_sport_buf_obj.mul_sport_buf,
                                    g_mul_sport_buf_obj.write_buf_len,
                                    get_sport_data_len(g_ms_idx_pos.cur_idx_pos),
                                    true);

        g_mul_sport_buf_obj.write_buf_len = 0;
        g_mul_sport_buf_obj.buf_is_full_flg = false;
    }

    return ret_code;
}

multi_motion_ret multi_motion_write_mass_sport_data(void *data, uint32_t data_len)
{
    multi_motion_ret ret_code = MULTI_MOTION_SUCCESS;

    ret_code = write_sport_data((uint16_t)g_ms_idx_pos.cur_idx_pos,
                                (uint8_t *)data,
                                data_len,
                                get_sport_data_len(g_ms_idx_pos.cur_idx_pos),
                                true);

    return ret_code;
}


//=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 多运动运动时调用的函数集合

void app_clear_cur_sport_data_id(void)
{
    memset((void *)&g_cur_sport_data_id, 0, sizeof(g_cur_sport_data_id));
}

void multi_motion_clear_sport_global_var(void)
{
    multi_motion_set_prev_calorie(0);
    multi_motion_set_prev_step(0);
    multi_motion_set_prev_distance(0);
    multi_motion_set_prev_cyclic_sport_counter(0);

    set_recovery_motion_timestamp(0);
    set_fixed_data_base_pos(0);
    set_mul_sport_start_time(0);
    set_mul_sport_end_time(0);
    set_mul_sport_cnt(0);
    set_mul_sport_total_point_cnts(0);
    set_swimming_turn_cnt(0);
    set_is_up_km_status(false);
    set_is_up_mile_status(false);
    set_initialize_altitude(0);
//    set_sport_sit_type(SIT_NONE);
    set_sport_next_sit_type(SIT_NONE);
    set_is_change_sit_type(false);
    set_mul_sport_segment_distance(0);
    set_mul_sport_segment_count(0);
    memset((void *)&g_mul_sport_buf_obj, 0, sizeof(g_mul_sport_buf_obj));
}

void multi_motion_delete_cur_sport_list_item(void)
{
    g_p_sport_list_item_obj = NULL;
}

multi_motion_ret multi_motion_new_sport_file(void *args, uint32_t sport_start_timestamp)
{
    bool ret_flag;

    p_ms_abstract_config_t p_ms_sport_config  = (p_ms_abstract_config_t)args;    
    p_ms_abstract_sport_handle_t p_ms_sport_handle = NULL;

    ret_flag = mul_sport_factory_get_sport(p_ms_sport_config, &p_ms_sport_handle);
    
    static ms_common_sport_list_v1_t s_ms_sport_list;
    
    s_ms_sport_list.ms_sport_list.magic_number  = MUL_SPORT_MAGIC_NUMBER;
    s_ms_sport_list.ms_sport_list.version       = MUL_SPORT_VER_1;
    s_ms_sport_list.ms_sport_list.ms_config     = p_ms_sport_config;
    s_ms_sport_list.ms_sport_list.ms_handle     = p_ms_sport_handle;

    if (ret_flag)
    {
        mul_sport_dbg_log("find sport\n");
        
        g_p_sport_list_item_obj = (p_ms_abstract_sport_list_t)&s_ms_sport_list;

        uint16_t idx_pos;
        data_id_t mul_id;

        mul_id.timestamp                = sport_start_timestamp;
        mul_id.timezone                 = mul_sport_get_time_zone();
        mul_id.version                  = g_p_sport_list_item_obj->ms_handle->data_ver;

        mul_id.type_desc.type           = ENUM_SPORT_DATA_T;
        mul_id.type_desc.specific_type  = g_p_sport_list_item_obj->ms_config->sport_type;
        mul_id.type_desc.data_type      = ENUM_POINT_DATA_T;

        if (!add_new_sport_idx(&mul_id, &idx_pos))
        {
            g_p_sport_list_item_obj = NULL;
            return MULTI_MOTION_ERROR;
        }

        set_cur_sport_data_id(&mul_id);

        set_recovery_motion_timestamp(sport_start_timestamp);

        set_mul_sport_start_time(sport_start_timestamp);

        set_initialize_altitude(mul_sport_get_sport_basic_altitude());

        g_ms_idx_pos.cur_idx_pos = idx_pos;

        /* 获取运动固定头部的字节大小 */
        {
            uint32_t sport_fixed_data_len = 0;
            
            if (g_p_sport_list_item_obj->version == MUL_SPORT_VER_1)
            {
                p_ms_common_sport_list_v1_t p_common_sport_list_item     =
                                                  (p_ms_common_sport_list_v1_t)g_p_sport_list_item_obj;

                sport_fixed_data_len = p_common_sport_list_item->ms_sport_list.ms_handle->sport_fixed_data_len;
            }
            set_sport_data_len(g_ms_idx_pos.cur_idx_pos, sport_fixed_data_len);
        }
    }
    else
    {
        mul_sport_dbg_log("not found sport\n");
        
        g_p_sport_list_item_obj = NULL;

        return MULTI_MOTION_ERROR;
    }

    return MULTI_MOTION_SUCCESS;
}

bool multi_motion_get_sub_sport_type(const data_id_t *p_id, Sport_Type_Type *sub_sport_type)
{
    uint16_t cur_id_pos     = 0;
    uint32_t sport_repo_len = 0;
    uint32_t data_offset    = 0;
    bool ret_flag = 0;
#if MUL_SPOmalloc_SWITCH
    uint8_t *sport_buf = mul_spomalloc(512);
#else
    uint8_t sport_buf[512];
#endif
    uint16_t tmp_sport_type = 0;
    data_id_t repo_id = {.timestamp = 0,};

#if MUL_SPOmalloc_SWITCH
    if (!sport_buf)
    {
        MUL_SPORT_PLATFORM_MALLOC_FAILED();
        return false;
    }
#endif

    if (!p_id)
    {
#if MUL_SPOmalloc_SWITCH
        if (sport_buf)
        {
            mul_spofree(sport_buf);
        }
#endif
         return false;
    }

    if (p_id->type_desc.specific_type != ST_FREE_SPORT \
        && p_id->type_desc.specific_type != ST_OUTSIDE_RUN_CATEGORY)
    {
#if MUL_SPOmalloc_SWITCH
        if (sport_buf)
        {
            mul_spofree(sport_buf);
        }
#endif
        return false;
    }

    ret_flag = app_get_id_pos_by_id(p_id, &cur_id_pos);

    if (ret_flag == false)
    {
#if MUL_SPOmalloc_SWITCH
        if (sport_buf)
        {
            mul_spofree(sport_buf);
        }
#endif
        return false;
    }

    if (get_sport_report_flag(cur_id_pos) != STORED_DATA_AND_UPLOADED
        && get_sport_report_flag(cur_id_pos) != STORED_DATA_NOT_UPLOADED)
    {
#if MUL_SPOmalloc_SWITCH
        if (sport_buf)
        {
            mul_spofree(sport_buf);
        }
#endif
        return false;
    }

    sport_repo_len = get_sport_report_len(cur_id_pos);

    data_offset = get_sport_data_len(cur_id_pos) - sport_repo_len;

    if (!read_sport_data(cur_id_pos, (uint8_t *)sport_buf, sport_repo_len, data_offset))
    {
#if MUL_SPOmalloc_SWITCH
        if (sport_buf)
        {
            mul_spofree(sport_buf);
        }
#endif
        return false;
    }

    repo_id = get_sport_report_id(cur_id_pos);

    if (repo_id.type_desc.specific_type == ST_OUTSIDE_RUN_CATEGORY)
    {
        get_ms_sport_category_t9_sub_sport_type(repo_id.version, sport_buf, &tmp_sport_type);
    }
    else if (repo_id.type_desc.specific_type == ST_OUTSIDE_NOT_RUN_CATEGORY)
    {
        get_ms_sport_category_t10_sub_sport_type(repo_id.version, sport_buf, &tmp_sport_type);
    }
    else
    {
        get_ms_sport_category_t4_sub_sport_type(repo_id.version, sport_buf, &tmp_sport_type);
    }

    *sub_sport_type = (Sport_Type_Type)tmp_sport_type;

#if MUL_SPOmalloc_SWITCH
    if (sport_buf)
    {
        mul_spofree(sport_buf);
    }
#endif

    return true;
}

static multi_motion_ret multi_motion_write_sport_data(uint8_t *p_buf, uint32_t buf_len)
{
    uint16_t tmp_len;

    tmp_len = g_mul_sport_buf_obj.write_buf_len + buf_len * 2;
    if (!is_can_app_write_sport_report(g_ms_idx_pos.cur_idx_pos, tmp_len))
    {
        /* 超出范围异常写入, 返回MULTI_MOTION_ERROR */
        return MULTI_MOTION_ERROR;
    }


    if ((g_mul_sport_buf_obj.write_buf_len + buf_len > MUL_SPORT_BUF_SIZE))
    {
        return MULTI_MOTION_ERROR;
    }

    memcpy((uint8_t *)g_mul_sport_buf_obj.mul_sport_buf + g_mul_sport_buf_obj.write_buf_len,
           p_buf,
           buf_len);

    g_mul_sport_buf_obj.write_buf_len += buf_len;

    tmp_len = g_mul_sport_buf_obj.write_buf_len + buf_len * 2;
    if (!is_can_app_write_sport_report(g_ms_idx_pos.cur_idx_pos, tmp_len))
    {
        return MULTI_MOTION_SPACE_WAS_FULLED;
    }

    if (tmp_len > sizeof(g_mul_sport_buf_obj.mul_sport_buf) / sizeof(g_mul_sport_buf_obj.mul_sport_buf[0]))
    {
        g_mul_sport_buf_obj.buf_is_full_flg = true;
    }

    multi_motion_set_prev_calorie(mul_sport_get_sport_consume());
    multi_motion_set_prev_step(mul_sport_get_sport_step_num());
    multi_motion_set_prev_distance(mul_sport_get_sport_distance());
    multi_motion_set_prev_cyclic_sport_counter(mul_sport_get_cyclic_sport_counter());

    multi_motion_ret ret_code = MULTI_MOTION_WRITE_SUCCESS;

    if (g_mul_sport_buf_obj.buf_is_full_flg)
    {
        ret_code = multi_motion_save_sport_data();
    }

    return ret_code;
}

multi_motion_ret multi_motion_write_sport_sec_point_data(void)
{
#if MUL_SPOmalloc_SWITCH
    uint8_t *sport_buf = mul_spomalloc(512);
#else
    uint8_t sport_buf[512];
#endif
    uint32_t sport_buf_len = 0;

#if MUL_SPOmalloc_SWITCH
    if (!sport_buf)
    {
        MUL_SPORT_PLATFORM_MALLOC_FAILED();
        return false;
    }
#endif

    if (!g_p_sport_list_item_obj)
    {
#if MUL_SPOmalloc_SWITCH
        if (sport_buf)
        {
            mul_spofree(sport_buf);
        }
#endif
        return MULTI_MOTION_ERROR;
    }

    if (g_p_sport_list_item_obj->magic_number != MUL_SPORT_MAGIC_NUMBER)
    {
#if MUL_SPOmalloc_SWITCH
        if (sport_buf)
        {
            mul_spofree(sport_buf);
        }
#endif
        return MULTI_MOTION_ERROR;
    }

    if (g_p_sport_list_item_obj->version == MUL_SPORT_VER_1)
    {
        p_ms_common_sport_list_v1_t p_common_sport_list_item     =
                                          (p_ms_common_sport_list_v1_t)g_p_sport_list_item_obj;

        if (p_common_sport_list_item->ms_sport_list.ms_handle->is_record_per_sec == false)
        {
#if MUL_SPOmalloc_SWITCH
            if (sport_buf)
            {
                mul_spofree(sport_buf);
            }
#endif
            return MULTI_MOTION_ERROR;
        }

        if (p_common_sport_list_item->ms_sport_list.ms_handle->pf_get_sport_data)
        {
            p_common_sport_list_item->ms_sport_list.ms_handle->pf_get_sport_data(sport_buf, &sport_buf_len);
        }
    }

    multi_motion_ret ret_code = MULTI_MOTION_ERROR;

    if (sport_buf_len)
    {
        ret_code = multi_motion_write_sport_data(sport_buf, sport_buf_len);

        if (ret_code != MULTI_MOTION_ERROR)
        {
            add_mul_sport_total_point_cnts(1);
        }
    }

#if MUL_SPOmalloc_SWITCH
    if (sport_buf)
    {
        mul_spofree(sport_buf);
    }
#endif

    return ret_code;
}

multi_motion_ret multi_motion_app_write_sport_data(void *p_input_data, void *p_input_data_args)
{
#if MUL_SPOmalloc_SWITCH
    uint8_t *sport_buf = mul_spomalloc(512);
#else
    uint8_t sport_buf[512];
#endif
    uint32_t sport_buf_len = 0;

#if MUL_SPOmalloc_SWITCH
    if (!sport_buf)
    {
        MUL_SPORT_PLATFORM_MALLOC_FAILED();
        return false;
    }
#endif

    if (!g_p_sport_list_item_obj)
    {
#if MUL_SPOmalloc_SWITCH
        if (sport_buf)
        {
            mul_spofree(sport_buf);
        }
#endif
        return MULTI_MOTION_ERROR;
    }

    if (g_p_sport_list_item_obj->magic_number != MUL_SPORT_MAGIC_NUMBER)
    {
#if MUL_SPOmalloc_SWITCH
        if (sport_buf)
        {
            mul_spofree(sport_buf);
        }
#endif
        return MULTI_MOTION_ERROR;
    }

    if (g_p_sport_list_item_obj->version == MUL_SPORT_VER_1)
    {
        p_ms_common_sport_list_v1_t p_common_sport_list_item     =
                                          (p_ms_common_sport_list_v1_t)g_p_sport_list_item_obj;

        if (p_common_sport_list_item->ms_sport_list.ms_handle->is_record_per_sec == true)
        {
#if MUL_SPOmalloc_SWITCH
            if (sport_buf)
            {
                mul_spofree(sport_buf);
            }
#endif
            return MULTI_MOTION_ERROR;
        }

        if (p_common_sport_list_item->ms_sport_list.ms_handle->pf_set_sport_data)
        {
            p_common_sport_list_item->ms_sport_list.ms_handle->pf_set_sport_data(p_input_data, p_input_data_args);
        }

        if (p_common_sport_list_item->ms_sport_list.ms_handle->pf_get_sport_data)
        {
            p_common_sport_list_item->ms_sport_list.ms_handle->pf_get_sport_data(sport_buf, &sport_buf_len);
        }
    }

    multi_motion_ret ret_code = MULTI_MOTION_ERROR;

    if (sport_buf_len)
    {
        ret_code = multi_motion_write_sport_data(sport_buf, sport_buf_len);
    }

#if MUL_SPOmalloc_SWITCH
    if (sport_buf)
    {
        mul_spofree(sport_buf);
    }
#endif

    return ret_code;
}

multi_motion_ret multi_motion_write_sport_fixed_data(void)
{
#if MUL_SPOmalloc_SWITCH
    uint8_t *sport_buf = mul_spomalloc(512);
#else
    uint8_t sport_buf[512];
#endif
    uint32_t sport_buf_len = 0;

#if !defined(BSP_USING_PC_SIMULATOR) && (LOG_FLASH_USED_CFG == 0)
   // Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "ms_fixed_data %d", __LINE__);
#endif

#if MUL_SPOmalloc_SWITCH
    if (!sport_buf)
    {
        MUL_SPORT_PLATFORM_MALLOC_FAILED();
        return MULTI_MOTION_ERROR;
    }
#endif

#if !defined(BSP_USING_PC_SIMULATOR) && (LOG_FLASH_USED_CFG == 0)
   /// Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "ms_fixed_data %d", __LINE__);
#endif

    if (!g_p_sport_list_item_obj)
    {
#if MUL_SPOmalloc_SWITCH
        if (sport_buf)
        {
            mul_spofree(sport_buf);
        }
#endif
        return MULTI_MOTION_ERROR;
    }

#if !defined(BSP_USING_PC_SIMULATOR) && (LOG_FLASH_USED_CFG == 0)
  //  Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "ms_fixed_data %d", __LINE__);
#endif

    if (g_p_sport_list_item_obj->magic_number != MUL_SPORT_MAGIC_NUMBER)
    {
#if MUL_SPOmalloc_SWITCH
        if (sport_buf)
        {
            mul_spofree(sport_buf);
        }
#endif
        return MULTI_MOTION_ERROR;
    }

#if !defined(BSP_USING_PC_SIMULATOR) && (LOG_FLASH_USED_CFG == 0)
  //  Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "ms_fixed_data %d", __LINE__);
#endif

    if (g_p_sport_list_item_obj->version == MUL_SPORT_VER_1)
    {
        p_ms_common_sport_list_v1_t p_common_sport_list_item     =
                                          (p_ms_common_sport_list_v1_t)g_p_sport_list_item_obj;

        if (p_common_sport_list_item->ms_sport_list.ms_handle->pf_get_sport_fixed_data)
        {
            p_common_sport_list_item->ms_sport_list.ms_handle->pf_get_sport_fixed_data(sport_buf, &sport_buf_len);
        }
    }

    multi_motion_ret ret_code = MULTI_MOTION_ERROR;

    if (sport_buf_len)
    {
        ret_code = write_sport_data(g_ms_idx_pos.cur_idx_pos,
                                    sport_buf,
                                    sport_buf_len,
                                    get_fixed_data_base_pos(),
                                    false);
    }

#if MUL_SPOmalloc_SWITCH
    if (sport_buf)
    {
        mul_spofree(sport_buf);
    }
#endif

#if !defined(BSP_USING_PC_SIMULATOR) && (LOG_FLASH_USED_CFG == 0)
  //  Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "ms_fixed_data %d, %d", __LINE__, ret_code);
#endif
    return ret_code;
}

multi_motion_ret multi_motion_app_set_sport_repo(void *p_input_data, void *p_input_data_args)
{
    if (!g_p_sport_list_item_obj)
    {
        return MULTI_MOTION_ERROR;
    }

    if (g_p_sport_list_item_obj->magic_number != MUL_SPORT_MAGIC_NUMBER)
    {
        return MULTI_MOTION_ERROR;
    }

    if (g_p_sport_list_item_obj->version == MUL_SPORT_VER_1)
    {
        p_ms_common_sport_list_v1_t p_common_sport_list_item     =
                                          (p_ms_common_sport_list_v1_t)g_p_sport_list_item_obj;

        if (p_common_sport_list_item->ms_sport_list.ms_handle->pf_set_sport_repo)
        {
            p_common_sport_list_item->ms_sport_list.ms_handle->pf_set_sport_repo(p_input_data, p_input_data_args);
        }
    }

    return MULTI_MOTION_SUCCESS;
}

multi_motion_ret multi_motion_write_sport_report(void)
{
#if MUL_SPOmalloc_SWITCH
    uint8_t *sport_buf = mul_spomalloc(512);
#else
    uint8_t sport_buf[512];
#endif
    uint32_t sport_buf_data_len = 0;

#if !defined(BSP_USING_PC_SIMULATOR) && (LOG_FLASH_USED_CFG == 0)
 //   Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "ms_report %d", __LINE__);
#endif

#if MUL_SPOmalloc_SWITCH
    if (!sport_buf)
    {
        MUL_SPORT_PLATFORM_MALLOC_FAILED();
        return MULTI_MOTION_ERROR;
    }
#endif

#if !defined(BSP_USING_PC_SIMULATOR) && (LOG_FLASH_USED_CFG == 0)
  //  Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "ms_report %d", __LINE__);
#endif

    if (!g_p_sport_list_item_obj)
    {
#if MUL_SPOmalloc_SWITCH
        if (sport_buf)
        {
            mul_spofree(sport_buf);
        }
#endif
        return MULTI_MOTION_ERROR;
    }

#if !defined(BSP_USING_PC_SIMULATOR) && (LOG_FLASH_USED_CFG == 0)
  //  Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "ms_report %d", __LINE__);
#endif

    if (g_p_sport_list_item_obj->magic_number != MUL_SPORT_MAGIC_NUMBER)
    {
#if MUL_SPOmalloc_SWITCH
        if (sport_buf)
        {
            mul_spofree(sport_buf);
        }
#endif
        return MULTI_MOTION_ERROR;
    }

#if !defined(BSP_USING_PC_SIMULATOR) && (LOG_FLASH_USED_CFG == 0)
 //   Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "ms_report %d", __LINE__);
#endif

    if (g_p_sport_list_item_obj->version == MUL_SPORT_VER_1)
    {
        p_ms_common_sport_list_v1_t p_common_sport_list_item     =
                                          (p_ms_common_sport_list_v1_t)g_p_sport_list_item_obj;

        if (p_common_sport_list_item->ms_sport_list.ms_handle->pf_get_sport_repo)
        {
            p_common_sport_list_item->ms_sport_list.ms_handle->pf_get_sport_repo(sport_buf, &sport_buf_data_len);
        }
    }

    multi_motion_ret ret_code = MULTI_MOTION_ERROR;

    if (sport_buf_data_len)
    {
        ret_code = write_sport_data(g_ms_idx_pos.cur_idx_pos,
                                    sport_buf,
                                    sport_buf_data_len,
                                    get_sport_data_len(g_ms_idx_pos.cur_idx_pos),
                                    false);
    }

#if !defined(BSP_USING_PC_SIMULATOR) && (LOG_FLASH_USED_CFG == 0)
//    Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "ms_report ret_code=%d", ret_code);
#endif

    if (ret_code == MULTI_MOTION_WRITE_SUCCESS)
    {
        data_id_t repo_id;
        repo_id = g_cur_sport_data_id;

        uint8_t repo_ver = g_p_sport_list_item_obj->ms_handle->repo_ver;
        mul_sport_report_ver_special_handler(repo_id.type_desc.specific_type, &repo_ver);
        repo_id.type_desc.data_type = ENUM_REPORT_DATA_T;
        repo_id.version = repo_ver;

        set_sport_report_id(g_ms_idx_pos.cur_idx_pos, &repo_id);
        set_sport_report_flag(g_ms_idx_pos.cur_idx_pos, STORED_DATA_NOT_UPLOADED);
        set_sport_report_len(g_ms_idx_pos.cur_idx_pos, sport_buf_data_len);
    }

#if MUL_SPOmalloc_SWITCH
    if (sport_buf)
    {
        mul_spofree(sport_buf);
    }
#endif

#if !defined(BSP_USING_PC_SIMULATOR) && (LOG_FLASH_USED_CFG == 0)
  //  Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "ms_report %d", __LINE__);
#endif

    return ret_code;
}


void multi_motion_save_sport_file(void)
{
    if (!g_cur_sport_data_id.timestamp)
    {
        return;
    }

    multi_motion_save_sport_data();

    multi_motion_write_sport_fixed_data();
    multi_motion_write_sport_report();
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 多运动上传

/* 获得有效的索引 */
bool app_get_multi_motion_intraday_valid_id(data_id_t *p_id, uint32_t *id_nums, const uint32_t max_id_nums)
{
    uint16_t tmp_idx_pos = 0;
    uint32_t tmp_id_nums = *id_nums;

    if (g_multi_motion_idx_table.idx_nums == (uint16_t)-1)
    {
        return false;
    }

    if (!p_id || *id_nums >= max_id_nums)
    {
        return false;
    }

    for (uint16_t i = 0; i < g_multi_motion_idx_table.idx_nums && tmp_idx_pos < MULTI_IDX_NUMS; i++)
    {
//        if (mul_sport_is_the_same_day(get_sport_id(tmp_idx_pos).timestamp + mul_sport_get_time_zone_offset(get_sport_id(tmp_idx_pos).timezone),
//                mul_sport_get_timestamp() + mul_sport_get_time_zone_offset(mul_sport_get_time_zone())))
        if (true)  // FIXME: vital 因为id个数不够,目前都放在当天
        {
            if (get_sport_report_flag(tmp_idx_pos) == STORED_DATA_NOT_UPLOADED
                || get_sport_report_flag(tmp_idx_pos) == STORED_DATA_AND_UPLOADED)
            {
                if (get_sport_data_len(tmp_idx_pos))
                {
                    if (tmp_id_nums < max_id_nums)
                    {
                        *p_id++ = get_sport_id(tmp_idx_pos);
                        tmp_id_nums++;
                    }
                }
            }

            if (get_sport_report_flag(tmp_idx_pos) == STORED_DATA_NOT_UPLOADED
                || get_sport_report_flag(tmp_idx_pos) == STORED_DATA_AND_UPLOADED)
            {
                if (get_sport_report_len(tmp_idx_pos))
                {
                    if (tmp_id_nums < max_id_nums)
                    {
                        *p_id++ = get_sport_report_id(tmp_idx_pos);
                        tmp_id_nums++;
                    }
                }
            }
        }

        tmp_idx_pos = get_next_sport_id_pos(tmp_idx_pos);
    }

    *id_nums = tmp_id_nums;

    return true;
}

bool app_get_multi_motion_historical_valid_id(data_id_t *p_id, uint32_t *id_nums, const uint32_t max_id_nums)
{
    uint16_t tmp_idx_pos = 0;
    uint32_t tmp_id_nums = *id_nums;

    if (g_multi_motion_idx_table.idx_nums == (uint16_t)-1)
    {
        return false;
    }

    if (!p_id || *id_nums >= max_id_nums)
    {
        return false;
    }

    for (uint16_t i = 0; i < g_multi_motion_idx_table.idx_nums && tmp_idx_pos < MULTI_IDX_NUMS; i++)
    {
        if (!mul_sport_is_the_same_day(get_sport_id(tmp_idx_pos).timestamp + mul_sport_get_time_zone_offset(get_sport_id(tmp_idx_pos).timezone),
            mul_sport_get_timestamp() + mul_sport_get_time_zone_offset(mul_sport_get_time_zone())))
        {
            if (get_sport_report_flag(tmp_idx_pos) == STORED_DATA_NOT_UPLOADED
                || get_sport_report_flag(tmp_idx_pos) == STORED_DATA_AND_UPLOADED)
            {
                if (get_sport_data_len(tmp_idx_pos))
                {
                    if (tmp_id_nums < max_id_nums)
                    {
                        *p_id++ = get_sport_id(tmp_idx_pos);
                        tmp_id_nums++;                        
                    }
                }
            }

            if (get_sport_report_flag(tmp_idx_pos) == STORED_DATA_NOT_UPLOADED
                || get_sport_report_flag(tmp_idx_pos) == STORED_DATA_AND_UPLOADED)
            {
                if (get_sport_report_len(tmp_idx_pos))
                {
                    if (tmp_id_nums < max_id_nums)
                    {
                        *p_id++ = get_sport_report_id(tmp_idx_pos);
                        tmp_id_nums++;
                    }
                }
            }
        }

        tmp_idx_pos = get_next_sport_id_pos(tmp_idx_pos);
    }

    *id_nums = tmp_id_nums;

    return true;
}

/* 根据数据ID, 获取数据的大小 */
bool app_get_multi_motion_data_len(const data_id_t *p_id, uint32_t *data_len)
{
    uint16_t tmp_idx_pos = 0;

    if ((*p_id).type_desc.data_type == ENUM_POINT_DATA_T
        || (*p_id).type_desc.data_type == ENUM_REPORT_DATA_T)
    {
        if (!app_get_id_pos_by_id(p_id, &tmp_idx_pos))
        {
            if (data_len)
            {
                *data_len = 0;
            }

            return false;
        }
    }


    switch ((*p_id).type_desc.data_type)
    {
        case ENUM_POINT_DATA_T:
            *data_len = get_sport_data_len(tmp_idx_pos) - get_sport_report_len(tmp_idx_pos);
            break;
        case ENUM_REPORT_DATA_T:
            *data_len = get_sport_report_len(tmp_idx_pos);
            break;
#if GPS_DATA_MANAGER_SWITCH
        case ENUM_SPORT_GPS_DATA_T:
            return app_get_multi_motion_gps_data_len(p_id, data_len);
#endif
        default:
            if (data_len)
            {
                *data_len = 0;
            }

            return false;
    }

    return true;
}

/* 根据数据ID和数据长度和偏移量, 获得对应的数据 */
bool app_read_multi_motion_data
(const data_id_t *p_id, void *pdata, uint32_t data_len, uint32_t offset)
{
    uint16_t tmp_idx_pos = 0;

    if ((*p_id).type_desc.data_type == ENUM_POINT_DATA_T
        || (*p_id).type_desc.data_type == ENUM_REPORT_DATA_T)
    {
        if (!app_get_id_pos_by_id(p_id, &tmp_idx_pos))
        {
            return false;
        }
    }

    switch ((*p_id).type_desc.data_type)
    {
        case ENUM_POINT_DATA_T:
            /* 运动数据打点是没有偏移的, 因为运动数据报告是存在运动打点里面的,因此需要做偏移 */
            break;

        case ENUM_REPORT_DATA_T:
            offset = get_sport_data_len(tmp_idx_pos) - get_sport_report_len(tmp_idx_pos);
            break;

#if GPS_DATA_MANAGER_SWITCH
        case ENUM_SPORT_GPS_DATA_T:
            return app_read_multi_motion_gps_data(p_id, pdata, data_len, offset);
#endif

        default:
            return false;
    }

    read_sport_data(tmp_idx_pos, pdata, data_len, offset);

    return true;
}

bool app_del_multi_motion_id(const data_id_t *p_id)
{
    bool ret_flag = false;

    uint16_t tmp_idx_pos = 0;
    Sport_Type_Type sub_sport_type = ST_NONE;

    if ((*p_id).type_desc.data_type == ENUM_POINT_DATA_T
        || (*p_id).type_desc.data_type == ENUM_REPORT_DATA_T)
    {
        if (!app_get_id_pos_by_id(p_id, &tmp_idx_pos))
        {
            return false;
        }
    }

    switch ((*p_id).type_desc.data_type)
    {
        case ENUM_POINT_DATA_T:
            set_sport_data_flag(tmp_idx_pos, STORED_DATA_AND_UPLOADED);
            break;
        case ENUM_REPORT_DATA_T:
            set_sport_report_flag(tmp_idx_pos, STORED_DATA_AND_UPLOADED);
            break;
#if GPS_DATA_MANAGER_SWITCH
        case ENUM_SPORT_GPS_DATA_T:
            ret_flag = app_del_multi_motion_gps_id(p_id);
            return ret_flag;
#endif
        default:
            break;
    }

    if (get_sport_data_flag(tmp_idx_pos) == STORED_DATA_AND_UPLOADED
        && get_sport_report_flag(tmp_idx_pos) == STORED_DATA_AND_UPLOADED)
    {
        multi_motion_get_sub_sport_type(p_id, &sub_sport_type);

        ret_flag = del_sport_file(p_id);

        if (ret_flag)
        {
            multi_motion_write_idx_table();
        }

        mul_sport_upload_sport_file_succeed_cb(*p_id, sub_sport_type);
    }

    return ret_flag;
}

//=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 本地获取record打点数据
uint32_t multi_motion_get_record_item_nums(p_data_id_t p_id)
{
    uint32_t item_nums = 0;
    item_nums = mul_sport_platform_get_item_nums(p_id);
    return item_nums;
}

// 获取分段打点的运动
static uint32_t multi_motion_get_section_record_nitem(p_data_id_t p_id, ms_record_item_t *p_item, const uint32_t offset_item, const uint32_t need_item_nums, ms_record_info_t record_info)
{
    uint32_t            num_items_read = 0;
    uint32_t            cur_len_offset = 0;
    uint32_t            data_total_len = 0;
    uint32_t            cur_item_offset = 0;
    uint32_t            start_item_offset = offset_item;
    bool                is_read_completed = false;
    uint32_t            tmp_delta_item_num = 0;
    uint32_t            tmp_delta_len_offset = 0;
    bool                is_detail_body = true;
    ms_record_head_t    record_head;

    uint8_t *p_read_buf = (uint8_t *)malloc(MS_TMP_READ_BUF_SIZE);

    if (p_read_buf)
    {
        app_get_multi_motion_data_len(p_id, &data_total_len);

        while ((cur_len_offset < data_total_len) && (is_read_completed == false))
        {
            memset(p_read_buf, 0, record_info.data_head_len);
            app_read_multi_motion_data(p_id, p_read_buf, record_info.data_head_len, cur_len_offset);

            cur_len_offset += record_info.data_head_len;

            mul_sport_dbg_log("[%d], section cur_len_offset = %d, data_head_len=%d, data_body_len=%d\n",
                              __LINE__,
                              cur_len_offset,
                              record_info.data_head_len,
                              record_info.data_body_len);

            mul_sport_platform_get_record_head(p_id, p_read_buf, &record_head);

            mul_sport_dbg_log("[%d], section cur_len_offset = %d, count_sport_hold=%d\n",
                              __LINE__,
                              cur_len_offset,
                              record_head.count_sport_hold);

            tmp_delta_item_num = 0;
            tmp_delta_len_offset = 0;

            if (record_head.count_sport_hold)
            {
                int32_t j = 0;
                int32_t j_limit = record_head.count_sport_hold;

                for (; j < j_limit && num_items_read < need_item_nums; j++)
                {
                    memset(p_read_buf, 0, record_info.data_body_len);

                    app_read_multi_motion_data(p_id,
                                               p_read_buf,
                                               record_info.data_section_len,
                                               cur_len_offset + tmp_delta_len_offset);

                    is_detail_body = mul_sport_platform_get_record_is_detail_body(p_id, p_read_buf);

                    if (is_detail_body)
                    {
                        if (cur_item_offset + tmp_delta_item_num == start_item_offset + num_items_read)
                        {
                            app_read_multi_motion_data(p_id,
                                                    p_read_buf,
                                                    record_info.data_body_len,
                                                    cur_len_offset + tmp_delta_len_offset);


                            mul_sport_platform_get_record_body(p_id, p_read_buf, &p_item[num_items_read]);

                            num_items_read++;

                            if (num_items_read >= need_item_nums)
                            {
                                is_read_completed = true;
                                break;
                            }
                        }

                        mul_sport_dbg_log("[%d], section !!! read_data_body, offset = %d\n",
                                          __LINE__,
                                          cur_len_offset + tmp_delta_len_offset);

                        tmp_delta_item_num++;
                        tmp_delta_len_offset += record_info.data_body_len;

                    }
                    else
                    {
                        tmp_delta_len_offset += record_info.data_section_len;
                    }
                }

                cur_item_offset += tmp_delta_item_num;
                cur_len_offset += tmp_delta_len_offset;

                mul_sport_dbg_log("[%d], section postprocess, d_n=%d, d_l_off=%d, item_offset=%d, len_offset=%d\n",
                                  __LINE__,
                                  tmp_delta_item_num,
                                  tmp_delta_len_offset,
                                  cur_item_offset,
                                  cur_len_offset);
            }
        }

        if (p_read_buf)
        {
            free(p_read_buf);
        }
    }

    mul_sport_dbg_log("multi_motion_get_record_nitem section end >>>>>>>!\n");

    return num_items_read;
}

// 获取秒打点的运动
static uint32_t multi_motion_get_second_record_nitem(p_data_id_t p_id, ms_record_item_t *p_item, const uint32_t offset_item, const uint32_t need_item_nums, ms_record_info_t record_info)
{
    uint32_t            num_items_read = 0;
    uint32_t            cur_len_offset = 0;
    uint32_t            data_total_len = 0;
    uint32_t            cur_item_offset = 0;
    uint32_t            start_item_offset = offset_item;
    bool                is_read_completed = false;
    uint32_t            tmp_delta_item_num = 0;
    uint32_t            tmp_delta_len_offset = 0;
    ms_record_head_t    record_head;

    uint8_t *p_read_buf = (uint8_t *)malloc(MS_TMP_READ_BUF_SIZE);

    if (p_read_buf)
    {
        app_get_multi_motion_data_len(p_id, &data_total_len);

        while ((cur_len_offset < data_total_len) && (is_read_completed == false))
        {
            memset(p_read_buf, 0, record_info.data_head_len);
            app_read_multi_motion_data(p_id, p_read_buf, record_info.data_head_len, cur_len_offset);

            cur_len_offset += record_info.data_head_len;

            mul_sport_dbg_log("[%d], second cur_len_offset = %d, data_head_len=%d, data_body_len=%d\n",
                              __LINE__,
                              cur_len_offset,
                              record_info.data_head_len,
                              record_info.data_body_len);

            mul_sport_platform_get_record_head(p_id, p_read_buf, &record_head);

            mul_sport_dbg_log("[%d], second cur_len_offset = %d, count_sport_hold=%d\n",
                              __LINE__,
                              cur_len_offset,
                              record_head.count_sport_hold);

            tmp_delta_item_num = 0;
            tmp_delta_len_offset = 0;

            if (record_head.count_sport_hold)
            {
                if (cur_item_offset + record_head.count_sport_hold >= start_item_offset + num_items_read)
                {
                    int32_t j = 0;
                    int32_t j_limit = record_head.count_sport_hold;

                    j_limit = (cur_item_offset + record_head.count_sport_hold) - (start_item_offset + num_items_read);
                    tmp_delta_item_num = (start_item_offset + num_items_read) - cur_item_offset;
                    tmp_delta_len_offset = record_info.data_body_len * (start_item_offset + num_items_read - cur_item_offset);

                    mul_sport_dbg_log("[%d], second preprocess, d_n=%d, d_l_off=%d\n",
                                      __LINE__,
                                      tmp_delta_item_num,
                                      tmp_delta_len_offset);

                    for (; j < j_limit && num_items_read < need_item_nums; j++)
                    {
                        memset(p_read_buf, 0, record_info.data_body_len);

                        app_read_multi_motion_data(p_id, \
                                                    p_read_buf, \
                                                    record_info.data_body_len, \
                                                    cur_len_offset + tmp_delta_len_offset);

                        mul_sport_dbg_log("[%d], second !!! read_data_body, offset = %d\n",
                                          __LINE__,
                                          cur_len_offset + tmp_delta_len_offset);

                        mul_sport_platform_get_record_body(p_id, p_read_buf, &p_item[num_items_read]);

                        tmp_delta_len_offset += record_info.data_body_len;
                        tmp_delta_item_num++;
                        num_items_read++;

                        if (num_items_read >= need_item_nums)
                        {
                            is_read_completed = true;
                            break;
                        }
                    }

                    cur_item_offset += tmp_delta_item_num;
                    cur_len_offset += tmp_delta_len_offset;
                }
                else
                {
                    cur_item_offset += record_head.count_sport_hold;
                    cur_len_offset += (record_head.count_sport_hold * record_info.data_body_len);
                }

                mul_sport_dbg_log("[%d], second postprocess, d_n=%d, d_l_off=%d, item_offset=%d, len_offset=%d\n",
                                  __LINE__,
                                  tmp_delta_item_num,
                                  tmp_delta_len_offset,
                                  cur_item_offset,
                                  cur_len_offset);
            }
        }

        if (p_read_buf)
        {
            free(p_read_buf);
        }
    }

    mul_sport_dbg_log("multi_motion_get_record_nitem second end >>>>>>>!\n");

    return num_items_read;
}

uint32_t multi_motion_get_record_nitem(p_data_id_t p_id, ms_record_item_t *p_item, const uint32_t offset_item, const uint32_t need_item_nums)
{
    uint32_t num_items_read = 0;

    if (need_item_nums)
    {
        mul_sport_dbg_log("multi_motion_get_record_nitem start offset_i=%d, need_i=%d>>>>>>>!\n", offset_item, need_item_nums);

        ms_record_info_t record_info;
        mul_sport_platform_get_record_info(p_id, &record_info);

        // 有分段的运动,需要强制遍历(eg: swimming sport)
        if (record_info.data_section_len)
        {
            num_items_read = multi_motion_get_section_record_nitem(p_id, p_item, offset_item, need_item_nums, record_info);
        }
        else
        {
            num_items_read = multi_motion_get_second_record_nitem(p_id, p_item, offset_item, need_item_nums, record_info);
        }

    }

    return num_items_read;
}

uint32_t multi_motion_get_cur_record_item_nums(void)
{
    return multi_motion_get_record_item_nums(get_cur_sport_data_id());
}

uint32_t multi_motion_get_cur_record_nitem(ms_record_item_t *p_item, const uint32_t offset_item, const uint32_t need_item_nums)
{
    return multi_motion_get_record_nitem(get_cur_sport_data_id(), p_item, offset_item, need_item_nums);
}

#endif /* FLASH_MANAGER_SWITCH */

