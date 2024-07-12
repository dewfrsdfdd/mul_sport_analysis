#include "mul_sport_common.h"


#ifndef _MUL_SPORT_OPS_H
#define _MUL_SPORT_OPS_H

#ifdef __cplusplus
extern "C" {
#endif


#include "stdint.h"
#include "stdbool.h"

#include "mul_sport_data_struct.h"
#include "mul_sport_platform.h"

/* 多运动 */
//

/**
 * @brief  设置达到了上公里
 * @note   在多运动中达到上公里的时候,需要调用该函数设置状态.
 */
void mul_sport_set_has_reached_last_km(void);

/**
 * @brief  设置达到了上英里
 * @note   在多运动中达到上英里的时候,需要调用该函数设置状态.
 */
void mul_sport_set_has_reached_last_mile(void);

/**
 * @brief  设置运动计时时间
 * @note   当运动需要做补偿的时候, 需要调用该函数进行时间补偿
 * @param[in] sport_time_cnt 设置的补偿时间
 */
void mul_sport_set_mul_sport_cnt(uint32_t sport_time_cnt);

/**
 * @brief  设置本段总里程
 * @note   多运动打点进行累加
 * @param[in] new_point_distance 距离增加量
 */
void mul_sport_add_sport_segment_distance(uint32_t new_point_distance);

/**
 * @brief  设置本段总数
 * @note   多运动打点进行累加
 * @param[in] new_point_count 个数增加量
 */
void mul_sport_add_sport_segment_count(uint16_t new_point_count);

void mul_sport_set_sub_sport_type(Sport_Type_Type sport_type);

Sport_Type_Type mul_sport_get_sub_sport_type(void);

void mul_sport_set_mul_sport_end_time(utc_time_t timestamp);

void mul_sport_set_sport_sit_type(Sport_Interval_Training_Type sit_type);

void mul_sport_set_sport_next_sit_type(Sport_Interval_Training_Type sit_type);

void mul_sport_set_is_change_sit_type(bool is_change);

void mul_sport_clear_sport_global_var(void);

multi_motion_ret mul_sport_write_mass_auto_sport_data(void *p_data, uint32_t data_len, uint32_t data_cnts);

multi_motion_ret mul_sport_write_mass_auto_sport_gps(void *p_data, uint32_t data_len, uint32_t data_cnts);

/**
 * @brief  获得多运动存储状态
 * @retval MULTI_MOTION_SPACE_AMPLE 空间充足
 * @retval MULTI_MOTION_SPACE_WAS_FULLED 空间已满, 继续将会覆盖
 * @retval MULTI_MOTION_SPACE_WILL_FULLED 空间即将用尽
 */
multi_motion_ret mul_sport_get_storage_space_status(void);

/**
 * @brief 回收第一个运动索引
 * @note  需要在"空间不足,继续将会覆盖"中的继续按钮中调用.
 */
bool mul_sport_recycle_the_first_sport_index(void);

/**
 * @brief 新建运动文件
 * @param[in] 传入运动开始的时间戳
 * @param[in] 传入是否是通过运动识别开启的运动
 */
bool mul_sport_new_sport_file(utc_time_t sport_start_timestamp, bool is_auto_sport);

/**
 * @brief 写入运动打点数据
 * @note  使用运动打点V1，则每秒钟调用一次；使用运动打点V2，则每10秒钟调用一次
 */
multi_motion_ret mul_sport_write_sport_data(void);

/**
 * @brief 写入gps打点数据
 * @note  GPS数据有变化的时候才打点，不需要每秒钟打点
 */
multi_motion_ret mul_sport_write_gps_data(ms_gps_item_t gps_item);

/**
 * @brief 上层主动调用该接口写入数据
 * @note  例如游泳运动：当游泳每出现一节或者一段落的时候, 需要调用该函数
 * @param[in] p_input_data 要写入的数据，为结构体
 * @param[in] p_input_data_args 要写入数据的参数，默认填写NULL即可
 */
multi_motion_ret mul_sport_app_write_sport_data(void *p_input_data, void *p_input_data_args);

/**
 * @brief 上层主动调用该接口设置运动报告
 * @note  例如游泳运动：当运动结束时,需要保存数据的时候, 需要调用改函数设置运动报告
 * @param[in] p_input_data 要写入的数据，为结构体
 * @param[in] p_input_data_args 要写入数据的参数，默认填写NULL即可
 */
multi_motion_ret mul_sport_app_set_sport_repo(void *p_input_data, void *p_input_data_args);


/**
 * @brief 获取当前正在运行的运动ID
 */
p_data_id_t mul_sport_get_cur_sport_data_id(void);


/**
 * @brief 清除运动ID
 */
void mul_sport_clear_cur_sport_id(void);

/**
 * @brief 运动重新继续时需要进行一些处理
 * @note  主要是重新赋值时间戳,需要在运动中点击继续按钮或手机端点击继续按钮的时候调用.
 */
bool mul_sport_resume_process(void);

/**
 * @brief 保存当前运动文件
 */
bool mul_sport_save_cur_sport_file(void);

/**
 * @brief 清除运动缓存数据; 结束运动，保存完运动数据之后，抽完点后需要调用该函数
 */
bool mul_sport_clear_cur_sport_cache(void);

//

/**
 * @brief 写入多运动索引表,包括打点、报告、GPS
 */
bool mul_sport_write_idx_table(void);


/**
 * @brief 将多运动中的缓存数据写入到flash
 */
void mul_sport_save_sport_buffer_data(void);

/**
 * @brief 根据id，获取该id的gps打点总个数
 * @param[in] p_id 要读取的gps id指针
 * @retval 返回gps打点总个数
 */
uint32_t mul_sport_get_gps_item_nums(p_data_id_t p_id);

/**
 * @brief 根据id，获取该id的gps打点数据
 * @param[in]  p_id 要获取的gps id指针
 * @param[out] p_item 要读取的gps打点数组buffer
 * @param[in]  offset_item 从哪个gps点开始读取(offset_item从0开始, 最大值为 mul_sport_get_gps_item_nums 函数获取的个数减一)
 * @param[in]  need_item_nums 要读取的个数
 * @retval 返回实际读取到的gps个数
 */
uint32_t mul_sport_get_gps_nitem(p_data_id_t p_id, ms_gps_item_v1 *p_item, const uint32_t offset_item, const uint32_t need_item_nums);

/**
 * @brief  获取当前运动的gps打点个数
 * @retval 返回gps打点总个数
 */
uint32_t mul_sport_get_cur_gps_item_nums(void);

/**
 * @brief  获取当前运动的gps打点数据
 * @param[out] p_item 要读取的gps打点数组buffer
 * @param[in]  offset_item 从哪个gps点开始读取(offset_item从0开始, 最大值为 mul_sport_get_cur_gps_item_nums 函数获取的个数减一)
 * @param[in]  need_item_nums 要读取的个数
 * @retval 返回实际读取到的gps个数
 */
uint32_t mul_sport_get_cur_gps_nitem(ms_gps_item_v1 *p_item, const uint32_t offset_item, const uint32_t need_item_nums);

/**
 * @brief  获取当前运动的record打点个数
 * @retval 返回record打点总个数
 */
uint32_t mul_sport_get_cur_record_item_nums(void);

/**
 * @brief  获取当前运动的record打点数据
 * @param[out] p_item 要读取的record打点数组buffer
 * @param[in]  offset_item 从哪个record点开始读取(offset_item从0开始, 最大值为 mul_sport_get_cur_record_item_nums 函数获取的个数减一)
 * @param[in]  need_item_nums 要读取的个数
 * @retval 返回实际读取到的record个数
 */
uint32_t mul_sport_get_cur_record_nitem(ms_record_item_t *p_item, const uint32_t offset_item, const uint32_t need_item_nums);
/* */
//

/**
 * @brief 多运动初始化
 */
bool mul_sport_init(void);

/**
 * @brief 多运动取消初始化
 */
bool mul_sport_deinit(void);

/**
 * @brief 将运动数据索引表到flash中
 */
bool mul_sport_save_data_process(void);

/* 多运动上传部分 */
//

/**
 * @brief 获得当天数据ID
 */
bool mul_sport_get_intraday_valid_id(data_id_t *p_id, uint32_t *id_nums, const uint32_t max_id_nums);

/**
 * @brief 获得历史数据ID
 */
bool mul_sport_get_sport_historical_valid_id(data_id_t *p_id, uint32_t *id_nums, const uint32_t max_id_nums);

/**
 * @brief 获取多运动头部
 */
bool mul_sport_get_data_header_ptr(data_id_t *p_id, uint8_t **pp_header_data, size_t *header_data_len);

/**
 * @brief 获取多运动数据起始地址
 */
bool mul_sport_get_data_start_addr(data_id_t *p_id, uint32_t *p_start_addr);

/**
 * @brief 获取多运动数据项存储信息
 */
bool mul_sport_get_data_item_info(data_id_t *p_id, uint32_t *p_start_addr, size_t *p_data_len);

/**
 * @brief 根据数据ID, 读取数据
 */
bool mul_sport_read_upload_data(data_id_t *p_id, uint32_t read_addr, uint8_t *buf_ptr, size_t read_len);

/**
 * @brief 根据数据ID, 获取数据的长度
 */
bool mul_sport_get_data_len(const data_id_t *p_id, uint32_t *data_len);

/**
 * @brief 删除数据ID
 */
bool mul_sport_delete_id(const data_id_t *p_id);

/**
 * @brief  设置小节达到状态
 * @note   在多运动游泳中达到小节后,需要设置
 */
void mul_sport_set_has_reached_subsection(void);
/**
 * @brief  设置分段达到状态
 * @note   在多运动游泳中达到分段后,需要设置,小米规定一百米一个分段
 */
void mul_sport_set_has_reached_segmentation(void);
//


#ifdef __cplusplus
}
#endif


#endif /* _MUL_SPORT_OPS_H */
