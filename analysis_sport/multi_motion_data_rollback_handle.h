#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#ifndef _MULTI_MOTION_DATA_ROLLBACK_HANDLE_H
#define _MULTI_MOTION_DATA_ROLLBACK_HANDLE_H


#include "stdint.h"
#include "stdbool.h"
#include "mul_sport_data_struct.h"
#include "mul_sport_sector_id_list.h"

#define DATA_ROLLBACK_SWITCH 1

#if DATA_ROLLBACK_SWITCH

#define DISK_SWAP_SIZE 512

bool write_data_rollback
    (uint32_t write_sector_addr, uint32_t write_offset, uint32_t write_size, uint8_t *swap_buffer, uint32_t swap_buffer_size);

bool data_rollback_data_check
        (const void * pdata, uint32_t write_sector_addr, uint32_t write_size, uint32_t write_offset);

#endif



#endif /* _MULTI_MOTION_DATA_ROLLBACK_HANDLE_H  */

#endif /* FLASH_MANAGER_SWITCH */
