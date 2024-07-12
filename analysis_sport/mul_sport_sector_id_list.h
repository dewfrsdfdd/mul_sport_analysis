#ifndef _MUL_SPORT_SECTOR_ID_LIST_H

#define _MUL_SPORT_SECTOR_ID_LIST_H

#include "mul_sport_common.h"

#include "mul_sport_sector_manager.h"

#define FLASH_MANAGER_START_SECTOR_ID            0x00
#define FLASH_MANAGER_END_SECTOR_ID              (FLASH_MANAGER_SECTOR_NUMS - 1)

/* 交换分区的起始扇区号 */
#define SWAP_SECTOR_ID                           (FLASH_MANAGER_START_SECTOR_ID)

/* 多运动索引表的起始扇区号 */
#define MULTI_MOTION_IDX_TABLE_SECTOR_ID         (SWAP_SECTOR_ID + 0x01)

/* GPS数据索引表的起始扇区号(和多运动索引表用同一个扇区) */
#if GPS_DATA_MANAGER_SWITCH
#    define MULTI_MOTION_GPS_IDX_TABLE_SECTOR_ID  (MULTI_MOTION_IDX_TABLE_SECTOR_ID)
#endif

/* 多运动和GPS数据存储的起始扇区号(使用同一个扇区) */
#define MULTI_MOTION_SECTOR_LIST_ID              (MULTI_MOTION_IDX_TABLE_SECTOR_ID + 0x01)
#define MULTI_MOTION_GPS_LIST_SECTOR_ID          (MULTI_MOTION_SECTOR_LIST_ID)

#define MULTI_MOTION_SPORT_NUMS                  (FLASH_MANAGER_SECTOR_NUMS - MULTI_MOTION_SECTOR_LIST_ID)


#endif /* _MUL_SPORT_SECTOR_ID_LIST_H */
