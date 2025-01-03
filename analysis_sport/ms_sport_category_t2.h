#ifndef _MS_SPORT_CATEGORY_T2_H
#define _MS_SPORT_CATEGORY_T2_H

#include "mul_sport_common.h"

#include <stddef.h>

p_ms_abstract_sport_handle_t get_ms_sport_category_t2_v1(void);

void get_ms_sport_category_t2_data_header(uint8_t data_type, uint8_t version, uint8_t **pp_header_data, size_t *p_data_len);

bool get_ms_sport_category_t2_record_info(uint8_t version, ms_record_info_t *p_record_info);
bool get_ms_sport_category_t2_record_head(uint8_t version, uint8_t *p_input_read_buf, ms_record_head_t *p_record_head);
bool get_ms_sport_category_t2_record_body(uint8_t version, uint8_t *p_input_read_buf, ms_record_item_t *p_record_item);

/**
 * @brief: 室内跑步
 */
extern const ms_common_sport_config_v1_t g_indoor_run_config;

#endif /* _MS_SPORT_CATEGORY_T2_H */
