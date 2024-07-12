#ifndef _MS_GPS_SPORT_H
#define _MS_GPS_SPORT_H

#include "mul_sport_common.h"
#include <stddef.h>

/**
 * @brief: 获取gps处理结构体
 */
p_ms_abstract_gps_handle_t mul_sport_get_gps_handle_obj(uint32_t gps_version);

void mul_sport_get_gps_data_header(uint8_t version, uint8_t **pp_header_data, size_t *p_data_len);

void mul_sport_get_gps_item_size(uint8_t version, size_t *p_item_size);

#endif /* _MS_GPS_SPORT_H */
