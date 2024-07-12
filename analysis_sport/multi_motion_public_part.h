#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#ifndef _MULTI_MOTION_PUBLIC_PART_H_

#define _MULTI_MOTION_PUBLIC_PART_H_

#include "multi_motion_sport_handle.h"
#include "multi_motion_gps_handle.h"

multi_motion_sector_table_t * get_multi_motion_sector_table(void);

bool multi_motion_exceed_storage_addr_handler(uint32_t addr, uint32_t data_len);


bool multi_motion_init(void);
bool multi_motion_deinit(void);
bool multi_motion_delete_sport_file(data_id_t delete_id);
bool multi_motion_write_idx_table(void);
bool multi_motion_read_idx_table(void);
bool multi_motion_clear_abnormal_multi_motion_id(void);
bool multi_motion_read_motion_sector_table(void);

#endif /* FLASH_MANAGER_SWITCH */

#endif /* _MULTI_MOTION_PUBLIC_PART_H_ */
