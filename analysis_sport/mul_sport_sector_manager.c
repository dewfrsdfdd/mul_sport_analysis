#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#include "mul_sport_sector_manager.h"

bool fm_is_exceed_addr_range
    (const uint32_t upper_border_addr, const uint32_t Lower_border_addr, const uint32_t src_addr)
{
    if (src_addr >= upper_border_addr && src_addr <= Lower_border_addr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

uint32_t fm_get_sector_id_by_addr(uint32_t addr)
{
    return (addr - MS_BASE_ADDR) / MS_SECTOR_SIZE;
}

bool fm_erase_sector(uint16_t sector_idx)
{
    bool ret_flag;

    ret_flag = mul_sport_erase_sector(MS_BASE_ADDR + MS_SECTOR_SIZE * sector_idx);

    return ret_flag;
}

uint32_t fm_get_sector_addr(uint16_t sector_idx)
{
    return sector_idx * MS_SECTOR_SIZE + MS_BASE_ADDR;
}

#endif /* FLASH_MANAGER_SWITCH */
