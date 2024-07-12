#ifndef _MS_SPORT_CATEGORY_T1_H
#define _MS_SPORT_CATEGORY_T1_H

#include "mul_sport_common.h"

#include <stddef.h>


p_ms_abstract_sport_handle_t get_ms_sport_category_t1_v1(void);

void get_ms_sport_category_t1_data_header(uint8_t data_type, uint8_t version, uint8_t **pp_header_data, size_t *p_data_len);

/**
 * @brief: 户外跑
 */
extern const ms_common_sport_config_v1_t g_outside_run_config;

/**
 * @brief: 户外健走
 */
extern const ms_common_sport_config_v1_t g_outside_move_config;

/**
 * @brief: 户外登山
 */
extern const ms_common_sport_config_v1_t g_outside_climb_config;

/**
 * @brief: 户外越野
 */
extern const ms_common_sport_config_v1_t g_outside_cross_country_config;

/**
 * @brief: 户外徒步
 */
extern const ms_common_sport_config_v1_t g_outside_hiking_config;

#endif /* _MS_SPORT_CATEGORY_T1_H */
