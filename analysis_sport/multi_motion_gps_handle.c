#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#if GPS_DATA_MANAGER_SWITCH

#include <stdio.h>
#include <string.h>

#include "multi_motion_gps_handle.h"
#include "multi_motion_data_rollback_handle.h"
#include "mul_sport_platform.h"
#include "multi_motion_public_part.h"
#include "ms_gps_sport.h"
#include "mul_sport_factory.h"

typedef struct
{
#define MUL_SPORT_GPS_SAVE_BUF_NUM  90   // 最多buf存储14个gps点
#define MUL_SPORT_GPS_BUF_SIZE      (3 * MUL_SPORT_GPS_SAVE_BUF_NUM)

    bool     buf_is_full_flg;
    uint16_t write_buf_len;
    uint8_t  mul_sport_gps_buf[MUL_SPORT_GPS_BUF_SIZE];
} mul_sport_gps_buf_t;

static volatile multi_motion_gps_idx_table_t MUL_SPORT_ALIGN_WAY g_multi_motion_gps_idx_table;

static volatile mul_sport_gps_buf_t MUL_SPORT_ALIGN_WAY g_mul_sport_gps_buf_obj;

static volatile data_id_t MUL_SPORT_ALIGN_WAY g_cur_gps_data_id;

static volatile p_ms_abstract_gps_handle_t MUL_SPORT_ALIGN_WAY g_p_ms_gps_handle_obj = NULL;

static volatile ms_idx_pos_t MUL_SPORT_ALIGN_WAY g_ms_gps_idx_pos = {
    .magic_number = MUL_SPORT_MAGIC_NUMBER,
    .version      = MUL_SPORT_VER_1,
    .cur_idx_pos  = 0,
};

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 声明
void              free_all_mul_motion_gps_sector(void);
static bool       __free_gps_sector(uint16_t sector_id);
static bool       alloc_available_gps_sector(uint16_t *sector_id);
uint16_t          get_next_valid_gps_id_pos(void);
multi_motion_ret  write_gps_data(uint16_t idx_pos, const void *pdata, uint32_t data_len, uint32_t offset, bool flag);

void              set_gps_id(uint16_t idx_pos, const data_id_t *p_id);
data_id_t         get_gps_id(uint16_t idx_pos);
uint16_t          get_next_gps_id_pos(uint16_t idx_pos);
void              set_gps_data_len(uint16_t idx_pos, uint32_t gps_data_len);
uint32_t          get_gps_data_len(uint16_t idx_pos);
void              set_gps_data_flag(uint16_t idx_pos, store_flag_type_t flag);
store_flag_type_t get_gps_data_flag(uint16_t idx_pos);
void              set_gps_sector_nums(uint16_t idx_pos, uint16_t sector_nums);
uint16_t          get_gps_sector_nums(uint16_t idx_pos);
void              set_gps_sector_id(uint16_t idx_pos, uint16_t idx, uint16_t sector_id);
uint16_t          get_gps_sector_id(uint16_t idx_pos, uint16_t idx);



multi_motion_gps_idx_table_t *get_multi_motion_gps_idx_table(void)
{
    return (multi_motion_gps_idx_table_t *)&g_multi_motion_gps_idx_table;
}


void read_multi_motion_gps_idx_table(void)
{
    uint32_t start_addr;
    uint32_t head_addr;
    uint32_t data_addr;
    flash_storage_head_t flash_storage_head;

    start_addr = fm_get_sector_addr(MULTI_MOTION_GPS_IDX_TABLE_SECTOR_ID) + MULTI_MOTION_GPS_IDX_TABLE_SECTOR_OFFSET;

    head_addr = start_addr;
    data_addr = start_addr + sizeof(flash_storage_head_t);


    memset(&flash_storage_head, 0, sizeof(flash_storage_head_t));

    read_info_data(&flash_storage_head, head_addr, sizeof(flash_storage_head_t));

    if (flash_storage_head.magic_num == MUL_SPORT_MAGIC_NUMBER
        && flash_storage_head.version == MUL_SPORT_VER_1
        && flash_storage_head.store_flash_flag == STORED_DATA_NOT_UPLOADED
        && flash_storage_head.data_len == sizeof(multi_motion_gps_idx_table_t))
    {
        read_info_data(&g_multi_motion_gps_idx_table, data_addr, sizeof(multi_motion_gps_idx_table_t));

        mul_sport_dbg_log("g_multi_motion_gps_idx_table r_succeed, idx_nums = %d, magic_num = %x, ver = %d, flag = %x, crc = %x",
                           g_multi_motion_gps_idx_table.idx_nums,
                           g_multi_motion_gps_idx_table.magic_number,
                           g_multi_motion_gps_idx_table.version,
                           g_multi_motion_gps_idx_table.store_flash_flag,
                           g_multi_motion_gps_idx_table.flash_crc);
    }
    else
    {
        memset((void *)&g_multi_motion_gps_idx_table, 0, sizeof(multi_motion_gps_idx_table_t));

        mul_sport_dbg_log("g_multi_motion_gps_idx_table read idx data failed");
    }
}

void write_multi_motion_gps_idx_table(void)
{
    uint32_t start_addr;
    uint32_t head_addr;
    uint32_t data_addr;
    flash_storage_head_t flash_storage_head;
    bool write_flag;

    start_addr = fm_get_sector_addr(MULTI_MOTION_GPS_IDX_TABLE_SECTOR_ID) + MULTI_MOTION_GPS_IDX_TABLE_SECTOR_OFFSET;
    
    head_addr = start_addr;
    data_addr = start_addr + sizeof(flash_storage_head_t);

    g_multi_motion_gps_idx_table.magic_number     = MUL_SPORT_MAGIC_NUMBER;
    g_multi_motion_gps_idx_table.version          = MUL_SPORT_VER_1;
    g_multi_motion_gps_idx_table.store_flash_flag = STORED_DATA_NOT_UPLOADED;
    g_multi_motion_gps_idx_table.flash_crc        = 0x0000;

    write_flag = write_info_data(&g_multi_motion_gps_idx_table, data_addr, sizeof(multi_motion_gps_idx_table_t));
    
    if (write_flag)
    {
        flash_storage_head.magic_num = MUL_SPORT_MAGIC_NUMBER;
        flash_storage_head.version = MUL_SPORT_VER_1;
        flash_storage_head.store_flash_flag = STORED_DATA_NOT_UPLOADED;
        flash_storage_head.data_len = sizeof(multi_motion_gps_idx_table_t);
        flash_storage_head.flash_crc = 0x0000;

        mul_sport_dbg_log("g_multi_motion_gps_idx_table write idx data succeed");
    }
    else
    {
        flash_storage_head.magic_num = 0xFF;
        flash_storage_head.version = 0xFF;
        flash_storage_head.store_flash_flag = NO_STORE_DATA;
        flash_storage_head.data_len = 0;
        flash_storage_head.flash_crc = 0xFFFF;

        mul_sport_dbg_log("g_multi_motion_gps_idx_table write idx data failed");
    }

    write_info_data(&flash_storage_head, head_addr, sizeof(flash_storage_head));
}

void erase_multi_motion_gps_idx_table(void)
{
    fm_erase_sector(MULTI_MOTION_GPS_IDX_TABLE_SECTOR_ID);
}


bool read_multi_motion_gps_sector_table(void)
{
    uint16_t sector_num;
    uint16_t tmp_idx_pos = 0;

    multi_motion_sector_table_t *p_multi_motion_sector_table;

    p_multi_motion_sector_table = get_multi_motion_sector_table();

    if (g_multi_motion_gps_idx_table.idx_nums == (uint16_t)-1)
    {
        return true;
    }

    for (uint16_t i = 0; i < g_multi_motion_gps_idx_table.idx_nums && tmp_idx_pos < MULTI_GPS_IDX_NUMS; i++)
    {
        sector_num = get_gps_sector_nums(tmp_idx_pos);

        uint16_t sector_id;
        for (uint16_t k = 0; k < sector_num; k++)
        {
            sector_id = get_gps_sector_id(tmp_idx_pos, k);

            if (sector_id - MULTI_MOTION_GPS_LIST_SECTOR_ID >= MULTI_MOTION_GPS_SECTOR_NUM)
            {
                return false;
            }

            p_multi_motion_sector_table->sector_table[sector_id - MULTI_MOTION_GPS_LIST_SECTOR_ID] = 1;
        }

        p_multi_motion_sector_table->remind_sector_num -= sector_num;

        if (p_multi_motion_sector_table->remind_sector_num < 0) // 正常运行的情况下remind_sector_num永远不会小于0
        {
            p_multi_motion_sector_table->remind_sector_num = 0;
        }

        tmp_idx_pos = get_next_gps_id_pos(tmp_idx_pos);
    }

    return true;
}


static bool alloc_available_gps_sector(uint16_t *sector_id)
{
    uint32_t rand_pos  = mul_sport_get_rand() % MULTI_MOTION_GPS_SECTOR_NUM;
    uint32_t final_pos = 0;
    bool     ret_val   = false;
    multi_motion_sector_table_t * p_sector_table;

    p_sector_table = get_multi_motion_sector_table();

    if (rand_pos < MULTI_MOTION_GPS_SECTOR_NUM
        && !p_sector_table->sector_table[rand_pos])
    {
        final_pos = rand_pos;
        ret_val   = true;
    }
    else
    {
        for (uint16_t i = 0; i < MULTI_MOTION_GPS_SECTOR_NUM; i++)
        {
            if (!p_sector_table->sector_table[i])
            {
                final_pos = i;
                ret_val = true;

                break;
            }
        }
    }

    if (ret_val)
    {
        p_sector_table->sector_table[final_pos] = 1;
        p_sector_table->remind_sector_num--;

        if (p_sector_table->remind_sector_num < 0)
        {
            p_sector_table->remind_sector_num = 0;
        }

        *sector_id = final_pos + MULTI_MOTION_GPS_LIST_SECTOR_ID;
    }

    return ret_val;
}

static bool __free_gps_sector(uint16_t sector_id)
{
    multi_motion_sector_table_t * p_sector_table;

    p_sector_table = get_multi_motion_sector_table();

    if (sector_id - MULTI_MOTION_GPS_LIST_SECTOR_ID >= MULTI_MOTION_GPS_SECTOR_NUM
        || sector_id < MULTI_MOTION_GPS_LIST_SECTOR_ID)
    {
        return false;
    }

    if (!p_sector_table->sector_table[sector_id - MULTI_MOTION_GPS_LIST_SECTOR_ID])
    {
        return false;
    }

    p_sector_table->sector_table[sector_id - MULTI_MOTION_GPS_LIST_SECTOR_ID] = 0;
    p_sector_table->remind_sector_num++;

    return true;
}


void free_all_mul_motion_gps_sector(void)
{
    /* do nothing */
}

static bool exceed_storage_addr_handler(uint32_t addr, uint32_t data_len)
{
    return multi_motion_exceed_storage_addr_handler(addr, data_len);
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//

bool is_can_alloc_gps_sector(uint16_t idx_pos)
{
    multi_motion_sector_table_t * p_sector_table;

    p_sector_table = get_multi_motion_sector_table();

    if (!p_sector_table->remind_sector_num
        || get_next_gps_id_pos(idx_pos) + GPS_SECTOR_NUMS_SIZE > MULTI_GPS_IDX_NUMS)
    {
        return false;
    }

    return true;
}

bool is_can_write_gps_data(uint16_t idx_pos, uint32_t data_len)
{
    multi_motion_sector_table_t * p_sector_table;

    p_sector_table = get_multi_motion_sector_table();

    /* 空间已用尽 */
    if (!p_sector_table->remind_sector_num
        || get_next_gps_id_pos(idx_pos) + GPS_SECTOR_NUMS_SIZE > MULTI_GPS_IDX_NUMS)
    {
        if (get_gps_data_len(idx_pos) % MS_SECTOR_SIZE + data_len >= MS_SECTOR_SIZE - GPS_LAST_SECTOR_MAX_BYTES
            && (get_gps_data_len(idx_pos) / MS_SECTOR_SIZE) + 1 == get_gps_sector_nums(idx_pos))
        {
            return false;
        }

    }

    return true;
}

bool is_gps_space_will_full(void)
{
    multi_motion_sector_table_t * p_sector_table;

    p_sector_table = get_multi_motion_sector_table();

    /* 空间即将用尽 */
    if (p_sector_table->remind_sector_num <= 8
        || get_next_valid_gps_id_pos() + 3 * MIN_GPS_IDX_SIZE > MULTI_GPS_IDX_NUMS
        || (g_multi_motion_gps_idx_table.idx_nums != (uint16_t)-1 && g_multi_motion_gps_idx_table.idx_nums >= MUL_SPORT_GPS_WILL_FULL_NUMS))
    {
        return true;
    }

    return false;
}


bool is_gps_space_was_full(void)
{
    multi_motion_sector_table_t * p_sector_table;

    p_sector_table = get_multi_motion_sector_table();

    /* 空间已经用尽 */
    if (p_sector_table->remind_sector_num < 2
        || get_next_valid_gps_id_pos() +  MIN_GPS_IDX_SIZE > MULTI_GPS_IDX_NUMS
        || (g_multi_motion_gps_idx_table.idx_nums != (uint16_t)-1 && g_multi_motion_gps_idx_table.idx_nums >= MUL_SPORT_GPS_WAS_FULL_NUMS))
    {
        return true;
    }

    return false;
}


bool set_cur_gps_data_id(const data_id_t *p_id)
{
    if (!p_id)
    {
        return false;
    }

    g_cur_gps_data_id = *p_id;

    return true;
}

p_data_id_t get_cur_gps_data_id(void)
{
    return (p_data_id_t)&g_cur_gps_data_id;
}

uint16_t get_gps_sport_idx_nums(void)
{
    return g_multi_motion_gps_idx_table.idx_nums;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
bool get_id_pos_by_gps_id(const data_id_t *p_id, uint16_t *id_pos)
{
    if (g_multi_motion_gps_idx_table.idx_nums == (uint16_t)-1)
    {
        return false;
    }

    data_id_t tmp_id;
    uint16_t tmp_idx_pos = 0;

    for (uint16_t i = 0; i < g_multi_motion_gps_idx_table.idx_nums && tmp_idx_pos < MULTI_GPS_IDX_NUMS; i++)
    {
        tmp_id = get_gps_id(tmp_idx_pos);

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

        tmp_idx_pos = get_next_gps_id_pos(tmp_idx_pos);
    }

    return false;    
}


uint16_t get_next_valid_gps_id_pos(void)
{
    uint16_t tmp_idx_pos = 0;
    uint16_t ret_idx_pos = 0;

    if (g_multi_motion_gps_idx_table.idx_nums == (uint16_t)-1)
    {
        return ret_idx_pos;
    }

    for (uint16_t i = 0; i < g_multi_motion_gps_idx_table.idx_nums && tmp_idx_pos < MULTI_GPS_IDX_NUMS; i++)
    {
        tmp_idx_pos = get_next_gps_id_pos(tmp_idx_pos);
    }

    ret_idx_pos = tmp_idx_pos;

    return ret_idx_pos;
}

bool alloc_gps_id_pos(uint16_t *id_pos)
{
    uint16_t tmp_idx_pos;

    tmp_idx_pos = get_next_valid_gps_id_pos();

    if (!tmp_idx_pos)
    {
        //free_all_mul_motion_gps_sector();
    }

    if (tmp_idx_pos + MIN_GPS_IDX_SIZE > MULTI_GPS_IDX_NUMS)
    {
        return false;
    }

    *id_pos = tmp_idx_pos;

    return true;
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// set get
void set_gps_id(uint16_t idx_pos, const data_id_t *p_id)
{
    *(data_id_t *)(g_multi_motion_gps_idx_table.idx_data + idx_pos + GPS_ID_POS) = *p_id;
}

data_id_t get_gps_id(uint16_t idx_pos)
{
    return *(data_id_t *)(g_multi_motion_gps_idx_table.idx_data + idx_pos + GPS_ID_POS);
}

uint16_t get_next_gps_id_pos(uint16_t idx_pos)
{
    return (uint16_t)(idx_pos + GPS_SECTOR_NUM_POS + get_gps_sector_nums(idx_pos) * GPS_SECTOR_NUM_SIZE);
}

void set_gps_data_len(uint16_t idx_pos, uint32_t gps_data_len)
{
    *(uint32_t *)(g_multi_motion_gps_idx_table.idx_data + idx_pos + GPS_DATA_LEN_POS) = gps_data_len;
}

uint32_t get_gps_data_len(uint16_t idx_pos)
{
    return *(uint32_t *)(g_multi_motion_gps_idx_table.idx_data + idx_pos + GPS_DATA_LEN_POS);
}

void set_gps_data_flag(uint16_t idx_pos, store_flag_type_t flag)
{
    *(store_flag_type_t *)(g_multi_motion_gps_idx_table.idx_data + idx_pos + GPS_DATA_FLAG_POS) = flag;
}

store_flag_type_t get_gps_data_flag(uint16_t idx_pos)
{
    return *(store_flag_type_t *)(g_multi_motion_gps_idx_table.idx_data + idx_pos + GPS_DATA_FLAG_POS);
}

void set_gps_sector_nums(uint16_t idx_pos, uint16_t sector_nums)
{
    *(uint16_t *)(g_multi_motion_gps_idx_table.idx_data + idx_pos + GPS_SECTOR_NUMS_POS) = sector_nums;
}

uint16_t get_gps_sector_nums(uint16_t idx_pos)
{
    return *(uint16_t *)(g_multi_motion_gps_idx_table.idx_data + idx_pos + GPS_SECTOR_NUMS_POS);
}

/* idx 从0开始 */
void set_gps_sector_id(uint16_t idx_pos, uint16_t idx, uint16_t sector_id)
{
    *(uint16_t *)(g_multi_motion_gps_idx_table.idx_data + idx_pos + GPS_SECTOR_NUM_POS + idx * GPS_SECTOR_NUM_SIZE) = sector_id;
}

/* idx 从0开始 */
uint16_t get_gps_sector_id(uint16_t idx_pos, uint16_t idx)
{
    return *(uint16_t *)(g_multi_motion_gps_idx_table.idx_data + idx_pos + GPS_SECTOR_NUM_POS + idx * GPS_SECTOR_NUM_SIZE);
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
bool add_new_gps_idx(const data_id_t *p_id, uint16_t *idx_pos)
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
    if (get_id_pos_by_gps_id(p_id, &id_pos))
    {
        multi_motion_delete_sport_file(*p_id);
    }

    if (!alloc_gps_id_pos(&new_idx_pos))
    {
        return ret_flag;
    }

    if (!alloc_available_gps_sector(&sector_id))
    {
        return ret_flag;
    }

    set_gps_id(new_idx_pos, p_id);
    set_gps_data_flag(new_idx_pos, NO_STORE_DATA);
    set_gps_data_len(new_idx_pos, 0);
    set_gps_sector_nums(new_idx_pos, 1);

    set_gps_sector_id(new_idx_pos, 0, sector_id);
    fm_erase_sector(sector_id);

    if (g_multi_motion_gps_idx_table.idx_nums == (uint16_t)-1)
    {
        g_multi_motion_gps_idx_table.idx_nums = 1;
    }
    else
    {
        g_multi_motion_gps_idx_table.idx_nums++;
    }

    *idx_pos = new_idx_pos;

    ret_flag = true;

    return ret_flag;
}

multi_motion_ret write_gps_data(uint16_t idx_pos, const void *pdata, uint32_t data_len, uint32_t offset, bool flag)
{
    uint32_t sector_nums;
    uint32_t i;
    uint16_t write_sector_id;
    uint32_t write_sector_addr;
    uint32_t write_offset = offset;

    /* 获得扇区数量 */
    sector_nums = get_gps_sector_nums(idx_pos);

    for (i = 0; i < data_len;)
    {
        uint32_t left_space = MS_SECTOR_SIZE - (write_offset % MS_SECTOR_SIZE);
        uint32_t write_size = (data_len - i) < left_space ? (data_len - i) : left_space;

        while (write_offset / MS_SECTOR_SIZE >= sector_nums)
        {
            if (!is_can_alloc_gps_sector(idx_pos))
            {
                return MULTI_MOTION_SPACE_WAS_FULLED;
            }

            if (!alloc_available_gps_sector(&write_sector_id))
            {
                return MULTI_MOTION_SPACE_WAS_FULLED;
            }

            fm_erase_sector(write_sector_id);
            set_gps_sector_id(idx_pos, sector_nums, write_sector_id);
            sector_nums++;
            set_gps_sector_nums(idx_pos, sector_nums);
        }

        if(flag)
        {
            if (!is_can_write_gps_data(idx_pos, data_len - i))
            {
                return MULTI_MOTION_SPACE_WAS_FULLED;
            }
        }
        
        write_sector_id =  get_gps_sector_id(idx_pos, (write_offset / MS_SECTOR_SIZE) % sector_nums);

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

    set_gps_data_len(idx_pos,
                       write_offset < get_gps_data_len(idx_pos) ? get_gps_data_len(idx_pos) : write_offset);

    return MULTI_MOTION_WRITE_SUCCESS;
}


bool read_gps_data(uint16_t idx_pos, void *pdata, uint32_t data_len, uint32_t offset)
{
    uint32_t i;
    uint32_t sport_data_len;
    uint32_t read_offset = offset;
    uint16_t sector_idx;
    uint16_t sector_num;
    uint32_t read_sector_id;
    uint32_t read_sector_addr;

    // 1.读取当前运动长度
    sport_data_len = get_gps_data_len(idx_pos);
    // 判断offset + data_len是否大于当前运动数据的长度
    if (read_offset + data_len > sport_data_len)
    {
        return false;
    }

    sector_num = get_gps_sector_nums(idx_pos);

    for (i = 0; i < data_len;)
    {
        sector_idx = read_offset / MS_SECTOR_SIZE;             // 获得所在扇区的索引

        if (sector_idx + 1 > sector_num)
        {
            return false;
        }

        read_sector_id = get_gps_sector_id(idx_pos, sector_idx);   // 根据索引获得扇区的实际id号

        read_sector_addr = fm_get_sector_addr(read_sector_id); // 根据扇区的id号, 获得扇区的起始地址

        uint32_t left_space = MS_SECTOR_SIZE - (read_offset % MS_SECTOR_SIZE);
        uint32_t read_size = (data_len - i) < left_space ? (data_len - i) : left_space;

        read_info_data(pdata + i, read_sector_addr + (read_offset % MS_SECTOR_SIZE), read_size);

        i += read_size;
        read_offset += read_size;
    }

    return true;
}



//
bool app_get_id_pos_by_gps_id(const data_id_t *p_id, uint16_t *idx_pos)
{
    uint16_t tmp_idx_pos;

    if (!get_id_pos_by_gps_id(p_id, &tmp_idx_pos))
    {
        return false;
    }

    *idx_pos = tmp_idx_pos;

    return true;
}


bool app_get_gps_id_by_idx(data_id_t *p_id, uint16_t idx)
{
    bool ret_flag = false;

    if (g_multi_motion_gps_idx_table.idx_nums == (uint16_t)-1)
    {
        return ret_flag;
    }

    if ((idx + 1) > g_multi_motion_gps_idx_table.idx_nums)
    {
        return ret_flag;
    }

    data_id_t tmp_id;
    uint16_t tmp_idx_pos = 0;

    for (uint16_t i = 0; i < idx && tmp_idx_pos < MULTI_GPS_IDX_NUMS; i++)
    {
        tmp_idx_pos = get_next_gps_id_pos(tmp_idx_pos);
    }

    if (tmp_idx_pos < MULTI_GPS_IDX_NUMS)
    {
        tmp_id = get_gps_id(tmp_idx_pos);

        *p_id = tmp_id;

        ret_flag = true;
    }

    return ret_flag;
}

//=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
bool clear_abnormal_multi_motion_gps_id(void)
{
    uint16_t tmp_idx_pos = 0;
    data_id_t tmp_data_id;
    bool is_modify_multi_motion_gps_table = false;

    if (g_multi_motion_gps_idx_table.idx_nums == (uint16_t)-1)
    {
        return is_modify_multi_motion_gps_table;
    }

    tmp_idx_pos = 0;

    for (uint16_t i = 0; i < g_multi_motion_gps_idx_table.idx_nums && tmp_idx_pos < MULTI_GPS_IDX_NUMS; i++)
    {
        if (get_gps_data_flag(tmp_idx_pos) == NO_STORE_DATA
            || get_gps_data_flag(tmp_idx_pos) == STORED_DATA_AND_UPLOADED
            || get_gps_data_len(tmp_idx_pos) == 0)
        {
            tmp_data_id = get_gps_id(tmp_idx_pos);
            multi_motion_delete_sport_file(tmp_data_id);

            is_modify_multi_motion_gps_table = true;
        }

        tmp_idx_pos = get_next_gps_id_pos(tmp_idx_pos);
    }

    return is_modify_multi_motion_gps_table;
}


//=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 多运动GPS存储时调用得函数的集合

multi_motion_ret multi_motion_save_gps_data(void)
{
    multi_motion_ret ret_code = MULTI_MOTION_SUCCESS;

    if (g_mul_sport_gps_buf_obj.write_buf_len)
    {
        ret_code = write_gps_data(g_ms_gps_idx_pos.cur_idx_pos,
                                  (void *)g_mul_sport_gps_buf_obj.mul_sport_gps_buf,
                                  g_mul_sport_gps_buf_obj.write_buf_len,
                                  get_gps_data_len(g_ms_gps_idx_pos.cur_idx_pos),
                                  true);

        g_mul_sport_gps_buf_obj.write_buf_len = 0;
        g_mul_sport_gps_buf_obj.buf_is_full_flg = false;
    }

    return ret_code;
}

void app_save_gps_file(void)
{
    if (g_p_ms_gps_handle_obj && g_p_ms_gps_handle_obj->magic_number == MUL_SPORT_MAGIC_NUMBER)
    {
        multi_motion_save_gps_data();

        set_gps_data_flag(g_ms_gps_idx_pos.cur_idx_pos, STORED_DATA_NOT_UPLOADED);
    }
}

uint32_t app_get_cur_gps_file_len(void)
{
    return get_gps_data_len(g_ms_gps_idx_pos.cur_idx_pos);
}

void app_clear_gps_global_var(void)
{
    memset((void *)&g_mul_sport_gps_buf_obj, 0, sizeof(g_mul_sport_gps_buf_obj));
}

void app_clear_cur_gps_data_id(void)
{
    memset((void *)&g_cur_gps_data_id, 0, sizeof(g_cur_gps_data_id));
}

void app_delete_cur_gps_handle_obj(void)
{
    g_p_ms_gps_handle_obj = NULL;
}

bool is_doing_gps_sport(void)
{
    if (g_p_ms_gps_handle_obj && g_p_ms_gps_handle_obj->magic_number == MUL_SPORT_MAGIC_NUMBER)
    {
        return true;
    }

    return false;
}


bool del_gps_file(const data_id_t *p_id)
{
    uint16_t tmp_id_pos = 0;
    uint16_t cur_id_pos = 0;
    bool ret_val = false;

    if (!app_get_id_pos_by_gps_id(p_id, &cur_id_pos))
    {
        return ret_val;
    }

    if (g_p_ms_gps_handle_obj && g_p_ms_gps_handle_obj->magic_number == MUL_SPORT_MAGIC_NUMBER)
    {
        tmp_id_pos = g_ms_gps_idx_pos.cur_idx_pos;
    }
    else
    {
        tmp_id_pos = cur_id_pos;
    }

    if (tmp_id_pos > cur_id_pos)
    {
        tmp_id_pos -= (get_next_gps_id_pos(cur_id_pos) - cur_id_pos);
    }

    /* 1.释放掉占用的扇区 */
    for (uint16_t i = 0; i < get_gps_sector_nums(cur_id_pos); i++)
    {
        __free_gps_sector(get_gps_sector_id(cur_id_pos, i));
    }

    /* TODO: 这里要加互斥操作 start */

    /* 2.释放掉索引 */
    memmove((uint8_t *)g_multi_motion_gps_idx_table.idx_data + cur_id_pos,
            (uint8_t *)g_multi_motion_gps_idx_table.idx_data + get_next_gps_id_pos(cur_id_pos),
            MULTI_GPS_IDX_NUMS > get_next_gps_id_pos(cur_id_pos) ? MULTI_GPS_IDX_NUMS - get_next_gps_id_pos(cur_id_pos) : 0);

    if (g_p_ms_gps_handle_obj && g_p_ms_gps_handle_obj->magic_number == MUL_SPORT_MAGIC_NUMBER)
    {
        g_ms_gps_idx_pos.cur_idx_pos = tmp_id_pos;
    }
    /* end */

    /* 3. 索引数减1 */
    if (g_multi_motion_gps_idx_table.idx_nums)
    {
        g_multi_motion_gps_idx_table.idx_nums--;
    }

    ret_val = true;

    return ret_val;    
}




//=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//

static multi_motion_ret multi_motion_write_gps_sport_data(uint8_t *p_buf, uint32_t buf_len)
{
    if ((g_mul_sport_gps_buf_obj.write_buf_len + buf_len) > MUL_SPORT_GPS_BUF_SIZE)
    {
        return MULTI_MOTION_ERROR;
    }

    memcpy((uint8_t *)g_mul_sport_gps_buf_obj.mul_sport_gps_buf + g_mul_sport_gps_buf_obj.write_buf_len,
           p_buf,
           buf_len);

    g_mul_sport_gps_buf_obj.write_buf_len += buf_len;

    uint16_t tmp_len = g_mul_sport_gps_buf_obj.write_buf_len + buf_len * 2;

    if (!is_can_write_gps_data(g_ms_gps_idx_pos.cur_idx_pos, tmp_len))
    {
        return MULTI_MOTION_SPACE_WAS_FULLED;
    }

    if (tmp_len > sizeof(g_mul_sport_gps_buf_obj.mul_sport_gps_buf) / sizeof(g_mul_sport_gps_buf_obj.mul_sport_gps_buf[0]))
    {
        g_mul_sport_gps_buf_obj.buf_is_full_flg = true;
    }

    multi_motion_ret ret_code = MULTI_MOTION_WRITE_SUCCESS;

    if (g_mul_sport_gps_buf_obj.buf_is_full_flg)
    {
        ret_code = multi_motion_save_gps_data();
    }

    return ret_code;
}

//=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//

multi_motion_ret multi_motion_new_gps_sport_file(void *args,uint32_t sport_start_timestamp)
{
    p_ms_abstract_config_t p_ms_sport_config  = (p_ms_abstract_config_t)args;   

    if (p_ms_sport_config->is_gps_sport)
    {
        mul_sport_dbg_log("found gps sport\n");

        uint16_t idx_pos;
        data_id_t gps_id;

        gps_id.timestamp                = sport_start_timestamp;
        gps_id.timezone                 = mul_sport_get_time_zone();

        gps_id.version                  = p_ms_sport_config->gps_ver;

        gps_id.type_desc.type           = ENUM_SPORT_DATA_T;
        gps_id.type_desc.specific_type  = p_ms_sport_config->sport_type;
        gps_id.type_desc.data_type      = ENUM_SPORT_GPS_DATA_T;

        if (!add_new_gps_idx(&gps_id, &idx_pos))
        {
            g_p_ms_gps_handle_obj = NULL;
            return MULTI_MOTION_ERROR;
        }

        g_p_ms_gps_handle_obj = mul_sport_get_gps_handle_obj(p_ms_sport_config->gps_ver);

        if (!g_p_ms_gps_handle_obj)
        {
            return MULTI_MOTION_ERROR;
        }

        g_ms_gps_idx_pos.cur_idx_pos = idx_pos;
        set_cur_gps_data_id(&gps_id);

        return MULTI_MOTION_SUCCESS;
    }
    else
    {
        mul_sport_dbg_log("not found sport\n");

        g_p_ms_gps_handle_obj = NULL;

        return MULTI_MOTION_ERROR;
    }
}

multi_motion_ret multi_motion_write_gps_data(ms_gps_item_t gps_item)
{
    multi_motion_ret ret_code = MULTI_MOTION_WRITE_FAILED;
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

    if (!g_p_ms_gps_handle_obj)
    {
#if MUL_SPOmalloc_SWITCH
        if (sport_buf)
        {
            mul_spofree(sport_buf);
        }
#endif
        return MULTI_MOTION_ERROR;
    }

    if (g_p_ms_gps_handle_obj->magic_number != MUL_SPORT_MAGIC_NUMBER)
    {
#if MUL_SPOmalloc_SWITCH
        if (sport_buf)
        {
            mul_spofree(sport_buf);
        }
#endif
        return MULTI_MOTION_ERROR;
    }

    if (g_p_ms_gps_handle_obj->version == MUL_SPORT_VER_1)
    {
        p_ms_common_gps_handle_v1_t p_ms_common_gps_handle_obj     =
                                          (p_ms_common_gps_handle_v1_t)g_p_ms_gps_handle_obj;

        if (p_ms_common_gps_handle_obj->gps_handle.pf_get_gps_data)
        {
            p_ms_common_gps_handle_obj->gps_handle.pf_get_gps_data(sport_buf,
                                                                   &sport_buf_len,
                                                                   gps_item);
        }
    }

    if (sport_buf_len)
    {
        ret_code = multi_motion_write_gps_sport_data(sport_buf, sport_buf_len);
    }

#if MUL_SPOmalloc_SWITCH
        if (sport_buf)
        {
            mul_spofree(sport_buf);
        }
#endif

    return ret_code;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// GPS上传

/* 获得有效的索引 */
bool app_get_multi_motion_gps_intraday_valid_id(data_id_t *p_id, uint32_t *id_nums, const uint32_t max_id_nums)
{
    uint16_t tmp_idx_pos = 0;
    uint32_t tmp_id_nums = *id_nums;

    if (g_multi_motion_gps_idx_table.idx_nums == (uint16_t)-1)
    {
        return false;
    }

    if (!p_id || *id_nums >= max_id_nums)
    {
        return false;
    }

    for (uint16_t i = 0; i < g_multi_motion_gps_idx_table.idx_nums && tmp_idx_pos < MULTI_GPS_IDX_NUMS; i++)
    {
//        if (mul_sport_is_the_same_day(get_gps_id(tmp_idx_pos).timestamp + mul_sport_get_time_zone_offset(get_gps_id(tmp_idx_pos).timezone),
//                mul_sport_get_timestamp() + mul_sport_get_time_zone_offset(mul_sport_get_time_zone())))
        if (true)   // FIXME: vital 因为id个数不够,目前都放在当天
        {
            if (get_gps_data_flag(tmp_idx_pos) == STORED_DATA_NOT_UPLOADED)
            {
                if (get_gps_data_len(tmp_idx_pos))
                {
                    if (tmp_id_nums < max_id_nums)
                    {
                        *p_id++ = get_gps_id(tmp_idx_pos);
                        tmp_id_nums++;                        
                    }
                }
            }
        }

        tmp_idx_pos = get_next_gps_id_pos(tmp_idx_pos);
    }

    *id_nums = tmp_id_nums;

    return true;
}

bool app_get_multi_motion_gps_historical_valid_id(data_id_t *p_id, uint32_t *id_nums, const uint32_t max_id_nums)
{
    uint16_t tmp_idx_pos = 0;
    uint32_t tmp_id_nums = *id_nums;

    if (g_multi_motion_gps_idx_table.idx_nums == (uint16_t)-1)
    {
        return false;
    }

    if (!p_id || *id_nums >= max_id_nums)
    {
        return false;
    }

    for (uint16_t i = 0; i < g_multi_motion_gps_idx_table.idx_nums && tmp_idx_pos < MULTI_GPS_IDX_NUMS; i++)
    {
        if (!mul_sport_is_the_same_day(get_gps_id(tmp_idx_pos).timestamp + mul_sport_get_time_zone_offset(get_gps_id(tmp_idx_pos).timezone),
            mul_sport_get_timestamp() + mul_sport_get_time_zone_offset(mul_sport_get_time_zone())))
        {
            if (get_gps_data_flag(tmp_idx_pos) == STORED_DATA_NOT_UPLOADED)
            {
                if (get_gps_data_len(tmp_idx_pos))
                {
                    if (tmp_id_nums < max_id_nums)
                    {
                        *p_id++ = get_gps_id(tmp_idx_pos);
                        tmp_id_nums++;
                    }
                }
            }
        }

        tmp_idx_pos = get_next_gps_id_pos(tmp_idx_pos);
    }

    *id_nums = tmp_id_nums;

    return true;
}

/* 根据数据ID, 获取数据的大小 */
bool app_get_multi_motion_gps_data_len(const data_id_t *p_id, uint32_t *data_len)
{
    uint16_t tmp_idx_pos = 0;

    if (!app_get_id_pos_by_gps_id(p_id, &tmp_idx_pos))
    {
        if (data_len)
        {
            *data_len = 0;
        }

        return false;
    }

    switch ((*p_id).type_desc.data_type)
    {
        case ENUM_SPORT_GPS_DATA_T:
            *data_len = get_gps_data_len(tmp_idx_pos);
            break;

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
bool app_read_multi_motion_gps_data
    (const data_id_t *p_id, void *pdata, uint32_t data_len, uint32_t offset)
{
    uint16_t tmp_idx_pos = 0;

    if (!app_get_id_pos_by_gps_id(p_id, &tmp_idx_pos))
    {
        return false;
    }

    switch ((*p_id).type_desc.data_type)
    {
        case ENUM_SPORT_GPS_DATA_T:
            break;

        default:
            return false;
    }

    read_gps_data(tmp_idx_pos, pdata, data_len, offset);

    return true;
}

bool app_del_multi_motion_gps_id(const data_id_t *p_id)
{
    bool ret_flag = false;

    uint16_t tmp_idx_pos = 0;

    if (!app_get_id_pos_by_gps_id(p_id, &tmp_idx_pos))
    {
        return false;
    }

    switch ((*p_id).type_desc.data_type)
    {
        case ENUM_SPORT_GPS_DATA_T:
            set_gps_data_flag(tmp_idx_pos, STORED_DATA_AND_UPLOADED);
            break;

        default:
            break;
    }

    if (get_gps_data_flag(tmp_idx_pos) == STORED_DATA_AND_UPLOADED)
    {
        ret_flag = del_gps_file(p_id);

        if (ret_flag)
        {
//            multi_motion_write_idx_table();
        }
    }

    return ret_flag;
}

//=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 运动识别写入gps打点数据
multi_motion_ret multi_motion_write_mass_sport_gps(void *data, uint32_t data_len)
{
    multi_motion_ret ret_code = MULTI_MOTION_SUCCESS;

    ret_code = write_gps_data(g_ms_gps_idx_pos.cur_idx_pos,
                                (uint8_t *)data,
                                data_len,
                                get_gps_data_len(g_ms_gps_idx_pos.cur_idx_pos),
                                true);

    return ret_code;
}

//=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 本地获取gps打点数据
uint32_t multi_motion_get_gps_item_nums(p_data_id_t p_id)
{
    uint32_t item_nums = 0;
    uint32_t data_len = 0;
    uint32_t item_size = 0;

    app_get_multi_motion_gps_data_len(p_id, &data_len);
    mul_sport_get_gps_item_size((uint8_t)p_id->version, &item_size);

    if (item_size)
    {
        item_nums = data_len / item_size;
    }

    return item_nums;
}

uint32_t multi_motion_get_gps_nitem(p_data_id_t p_id, ms_gps_item_v1 *p_item, const uint32_t offset_item, const uint32_t need_item_nums)
{
    uint32_t item_total_nums = 0;
    uint32_t final_need_item_nums = need_item_nums;
    uint32_t item_size = 0;
    bool read_rst = false;

    item_total_nums = multi_motion_get_gps_item_nums(p_id);
    mul_sport_get_gps_item_size((uint8_t)p_id->version, &item_size);

    if (offset_item >= item_total_nums)
    {
        final_need_item_nums = 0;
    }
    else if (offset_item + need_item_nums > item_total_nums)
    {
        final_need_item_nums = item_total_nums - offset_item;
    }

    if (final_need_item_nums)
    {
        app_read_multi_motion_gps_data(p_id, p_item, final_need_item_nums * item_size, offset_item * item_size);
    }

    return final_need_item_nums;
}

uint32_t multi_motion_get_cur_gps_item_nums(void)
{
    return multi_motion_get_gps_item_nums(get_cur_gps_data_id());
}

uint32_t multi_motion_get_cur_gps_nitem(ms_gps_item_v1 *p_item, const uint32_t offset_item, const uint32_t need_item_nums)
{
    return multi_motion_get_gps_nitem(get_cur_gps_data_id(), p_item, offset_item, need_item_nums);
}

#endif /* GPS_DATA_MANAGER_SWITCH */

#endif /* FLASH_MANAGER_SWITCH */

