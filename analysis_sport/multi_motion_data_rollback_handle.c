#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#include "multi_motion_data_rollback_handle.h"
#include "mul_sport_sector_manager.h"
#include "string.h"

#if DATA_ROLLBACK_SWITCH


bool write_data_rollback
    (uint32_t write_sector_addr, uint32_t write_offset, uint32_t write_size, uint8_t *swap_buffer, uint32_t swap_buffer_size)
{
    uint32_t swap_sector_addr = fm_get_sector_addr(SWAP_SECTOR_ID);

    uint32_t cp_size = swap_buffer_size;
    uint8_t *cp_buf = swap_buffer;
    
    if (write_sector_addr > write_offset)
    {
        return false;
    }

    fm_erase_sector(SWAP_SECTOR_ID);                                   // 擦除交换分区
    
    for (uint32_t j = 0; j < MS_SECTOR_SIZE;)
    {
        uint32_t cp_len = MS_SECTOR_SIZE - j > cp_size ? cp_size : MS_SECTOR_SIZE - j;

        read_info_data(cp_buf, write_sector_addr + j, cp_len);      // 将出错的扇区的数据依次写到cp_buf中

        write_info_data(cp_buf, swap_sector_addr + j, cp_len);      // 将cp_buf的数据依次写入到交换区中

        j += cp_len;
    }

    fm_erase_sector(fm_get_sector_id_by_addr(write_sector_addr));                // 擦除出错的扇区

    /* 重新写入从所在扇区首地址到写入出错的首地址这部分的数据 */
    for (uint32_t j = 0; j < write_offset - write_sector_addr;)
    {
        uint32_t cp_len = write_offset - write_sector_addr - j > cp_size ? cp_size : write_offset - write_sector_addr - j;

        read_info_data(cp_buf, swap_sector_addr + j, cp_len);       // 将swap扇区中的数据依次写入到cp_buf中

        write_info_data(cp_buf, write_sector_addr + j, cp_len);     // 将cp_buf中的数据写回到之前出错的扇区中

        j += cp_len;
    }

    /* 重新写入从写入出错的结束地址到所在扇区结束地址这部分的数据 */
    for (uint32_t j = write_offset - write_sector_addr + write_size; j < MS_SECTOR_SIZE;)
    {
        uint32_t cp_len = MS_SECTOR_SIZE - j > cp_size ? cp_size : MS_SECTOR_SIZE - j;

        read_info_data(cp_buf, swap_sector_addr + j, cp_len);       // 将swap扇区中的数据依次写入到cp_buf中

        write_info_data(cp_buf, write_sector_addr + j, cp_len);     // 将cp_buf中的数据写回到之前出错的扇区中

        j += cp_len;
    }

    return true;
}

bool data_rollback_data_check
    (const void * pdata, uint32_t write_sector_addr, uint32_t write_size, uint32_t write_offset)
{
    uint8_t disk_swap_buffer[DISK_SWAP_SIZE];

    uint32_t cmp_size = DISK_SWAP_SIZE;
    uint8_t *cmp_buf = disk_swap_buffer;

    for (uint32_t write_check = 0; write_check < write_size;)
    {
        uint32_t cmp_len = write_size - write_check > cmp_size ? cmp_size : write_size - write_check;

        read_info_data(cmp_buf, write_sector_addr + (write_offset % MS_SECTOR_SIZE) + write_check, cmp_len);

        if (memcmp(cmp_buf, ((uint8_t *)pdata + write_check), cmp_len))
        {
            /* 数据回滚 */
            write_data_rollback(write_sector_addr, write_sector_addr + (write_offset % MS_SECTOR_SIZE), write_size, cmp_buf, cmp_size);

            /* 写入之前的出错数据 */
            write_info_data((uint8_t *)pdata, write_sector_addr + (write_offset % MS_SECTOR_SIZE), write_size);

            read_info_data(cmp_buf, write_sector_addr + (write_offset % MS_SECTOR_SIZE) + write_check, cmp_len);

            if (memcmp(cmp_buf, ((uint8_t *)pdata + write_check), cmp_len))
            {
                return false;
            }
        }

        write_check += cmp_len;
    }

    return true;
}

#endif  /* DATA_ROLLBACK_SWITCH */

#endif  /* FLASH_MANAGER_SWITCH */
