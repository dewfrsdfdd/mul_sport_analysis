#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#ifndef _MUL_SPORT_SECTOR_MANAGER_H
#define _MUL_SPORT_SECTOR_MANAGER_H

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
//

#include "mul_sport_platform.h"

#define MS_BASE_ADDR                 FLASH_MANAGER_START_ADDR

#define MS_SECTOR_MAX_ADDR           FLASH_MANAGER_END_ADDR

#define MS_SECTOR_SIZE               FLASH_MANAGER_SECTOR_SIZE   // 4k

#define FLASH_MANAGER_SECTOR_NUMS    ((MS_SECTOR_MAX_ADDR - MS_BASE_ADDR) / MS_SECTOR_SIZE)


#define write_info_data(data, addr, data_len) \
    mul_sport_write_info_data((uint8_t *)data, addr, data_len)

#define read_info_data(data, addr, data_len) \
    mul_sport_read_info_data((uint8_t *)data, addr,data_len)

/**
  *    @name   :  fm_erase_sector
  *    @brief  :  擦除扇区
  *    @param  :  sector_idx -> 扇区号
  *    @retval :  返回true代表擦除成功
  *    @author :  wth
  *    @date   :  2019-09-21
  */
bool fm_erase_sector(uint16_t sector_idx);

/**
  *    @name   :  fm_get_sector_addr
  *    @brief  :  获得对应扇区的Flash地址
  *    @param  :  sector_idx -> 扇区号
  *    @retval :  返回该扇区号对应的实际Flash的地址
  *    @author :  wth
  *    @date   :  2019-09-21
  */
uint32_t fm_get_sector_addr(uint16_t sector_idx);

/**
  *    @name   :  fm_get_sector_id_by_addr
  *    @brief  :  获得对应地址所在的扇区号
  *    @param  :  addr -> 需要获取扇区号的地址
  *    @retval :  返回该地址所在的扇区号
  *    @author :  wth
  *    @date   :  2019-09-21
  */
uint32_t fm_get_sector_id_by_addr(uint32_t addr);

/**
  *    @name   :  fm_is_exceed_addr_range
  *    @brief  :  判断要写入的地址是否超过边界
  *    @param  :  upper_border_addr -> 地址上边界
  *    @param  :  Lower_border_addr -> 地址下边界
  *    @param  :  src_addr -> 要写入的地址
  *    @retval :  返回true代表超过范围
  *    @author :  wth
  *    @date   :  2019-09-21
  */
bool fm_is_exceed_addr_range
    (const uint32_t upper_border_addr, const uint32_t Lower_border_addr, const uint32_t src_addr);

#endif /* _MUL_SPORT_SECTOR_MANAGER_H */

#endif /* FLASH_MANAGER_SWITCH */
