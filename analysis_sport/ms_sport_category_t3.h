#ifndef _MS_SPORT_CATEGORY_T3_H
#define _MS_SPORT_CATEGORY_T3_H

#include "mul_sport_common.h"

#include <stddef.h>

p_ms_abstract_sport_handle_t get_ms_sport_category_t3_v1(void);

void get_ms_sport_category_t3_data_header(uint8_t data_type, uint8_t version, uint8_t **pp_header_data, size_t *p_data_len);

/**
 * @brief: 户外骑行
 */
extern const ms_common_sport_config_v1_t g_outside_cycle_config;

#endif /* _MS_SPORT_CATEGORY_T3_H */
