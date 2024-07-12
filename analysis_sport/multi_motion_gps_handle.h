#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#if GPS_DATA_MANAGER_SWITCH

#ifndef _MULTI_MOTION_GPS_HANDLE_H
#define _MULTI_MOTION_GPS_HANDLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mul_sport_sector_id_list.h"


#define MULTI_GPS_IDX_NUMS                  620

#define MULTI_MOTION_GPS_SECTOR_NUM         MULTI_MOTION_SPORT_NUMS

#if (MULTI_MOTION_GPS_SECTOR_NUM < 2)
//#error "Insufficient storage space for gps sports!"
#endif


#define GPS_DATA_ID_SIZE              7   // GPS ID大小
#define GPS_DATA_LEN_SIZE             4   // GPS长度大小
#define GPS_DATA_FLAG_SIZE            1   // GPS标志位大小
#define GPS_SECTOR_NUMS_SIZE          2   // GPS扇区个数大小
#define GPS_SECTOR_NUM_SIZE           2   // GPS扇区大小

#define MIN_GPS_IDX_SIZE \
( \
    GPS_DATA_ID_SIZE \
    + GPS_DATA_LEN_SIZE \
    + GPS_DATA_FLAG_SIZE \
    + GPS_SECTOR_NUMS_SIZE \
    + GPS_SECTOR_NUM_SIZE \
)

#define GPS_ID_POS                    0                                            // 0
#define GPS_DATA_LEN_POS              (GPS_ID_POS + GPS_DATA_ID_SIZE)              // 0 + 7
#define GPS_DATA_FLAG_POS             (GPS_DATA_LEN_POS + GPS_DATA_LEN_SIZE)       // 0 + 7 + 4
#define GPS_SECTOR_NUMS_POS           (GPS_DATA_FLAG_POS + GPS_DATA_FLAG_SIZE)     // 0 + 7 + 4 + 1
#define GPS_SECTOR_NUM_POS            (GPS_SECTOR_NUMS_POS + GPS_SECTOR_NUMS_SIZE) // 0 + 7 + 4 + 1 + 2

#define GPS_LAST_SECTOR_MAX_BYTES     200

#define MULTI_MOTION_GPS_IDX_TABLE_SECTOR_OFFSET  (2048)

typedef struct
{
    int16_t remind_sector_num;
    uint8_t sector_table[MULTI_MOTION_GPS_SECTOR_NUM];
} multi_motion_gps_sector_table_t;

typedef struct
{
    uint8_t            magic_number;
    uint32_t           version;
    uint16_t           flash_crc;
    store_flag_type_t  store_flash_flag;
    uint16_t           idx_nums;  // 索引数量
    uint8_t            idx_data[MULTI_GPS_IDX_NUMS];
} multi_motion_gps_idx_table_t;


multi_motion_gps_idx_table_t *get_multi_motion_gps_idx_table(void);

void read_multi_motion_gps_idx_table(void);

void write_multi_motion_gps_idx_table(void);

bool clear_abnormal_multi_motion_gps_id(void);

bool read_multi_motion_gps_sector_table(void);

p_data_id_t get_cur_gps_data_id(void);
uint16_t get_gps_sport_idx_nums(void);
bool is_doing_gps_sport(void);
/*
 * @note idx从0开始
 */
bool app_get_gps_id_by_idx(data_id_t *p_id, uint16_t idx);

void app_clear_gps_global_var(void);
void app_clear_cur_gps_data_id(void);
void app_delete_cur_gps_handle_obj(void);

bool is_gps_space_will_full(void);
bool is_gps_space_was_full(void);


multi_motion_ret app_write_gps_head(void);
multi_motion_ret app_write_gps_data(uint32_t timestamp, float gps_longitude, float gps_latitude);


multi_motion_ret multi_motion_save_gps_data(void);

void app_save_gps_file(void);

uint32_t app_get_cur_gps_file_len(void);

//void multi_motion_gps_init(void);
//void multi_motion_gps_deinit(void);


bool app_get_multi_motion_gps_intraday_valid_id(data_id_t *p_id, uint32_t *id_nums, const uint32_t max_id_nums);
bool app_get_multi_motion_gps_historical_valid_id(data_id_t *p_id, uint32_t *id_nums, const uint32_t max_id_nums);
bool app_get_multi_motion_gps_data_len(const data_id_t *p_id, uint32_t *data_len);
bool app_read_multi_motion_gps_data
    (const data_id_t *p_id, void *pdata, uint32_t data_len, uint32_t offset);
bool app_del_multi_motion_gps_id(const data_id_t *p_id);

multi_motion_ret multi_motion_write_mass_sport_gps(void *data, uint32_t data_len);

uint32_t multi_motion_get_gps_item_nums(p_data_id_t p_id);
uint32_t multi_motion_get_gps_nitem(p_data_id_t p_id, ms_gps_item_v1 *p_item, const uint32_t offset_item, const uint32_t need_item_nums);
uint32_t multi_motion_get_cur_gps_item_nums(void);
uint32_t multi_motion_get_cur_gps_nitem(ms_gps_item_v1 *p_item, const uint32_t offset_item, const uint32_t need_item_nums);

multi_motion_ret multi_motion_new_gps_sport_file(void *args, uint32_t sport_start_timestamp);
bool del_gps_file(const data_id_t *p_id);
multi_motion_ret multi_motion_write_gps_data(ms_gps_item_t gps_item);

#ifdef __cplusplus
}
#endif


#endif /* _MULTI_MOTION_GPS_HANDLE_H */

#endif /* GPS_DATA_MANAGER_SWITCH */

#endif /* FLASH_MANAGER_SWITCH */
