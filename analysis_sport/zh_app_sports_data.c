#include "zh_app_sports_data.h"
//#include "zh_thread_comm.h"
//#include "app_db.h"
//#include "module_sport_app.h"
#include "mul_sport_ops.h"
#if defined(USING_GYRO_SENSOR) && defined(ENUM_PROJECT_NAME_N65B_GLOBAL) 
#include "mi_gps_trk_simplify.h"
#include "mi_swimming_analyzer.h"
#endif
#if defined(USING_GYRO_SENSOR) && defined(ENUM_PROJECT_NAME_N65B_GLOBAL) 
sw_record_t *p_swim_list = NULL;
static uint16_t swim_list_count = 0;
void zh_app_sport_swim_list_add(sw_record_t *new_data)
{
    zh_app_sport_swim_list_append(&p_swim_list,new_data);
}
// 尾插法插入节点
void zh_app_sport_swim_list_append(sw_record_t **head_ref, sw_record_t *new_data)
{
    sw_record_t *new_node = (sw_record_t *)malloc(sizeof(sw_record_t));
    printf("new_node:0x%x,szie:%d\n", new_node,sizeof(sw_record_t));
    // 本小节最后一次划次的时间
    new_node->end_time = new_data->end_time;
    // 当前小节用时
    new_node->duration_s = new_data->duration_s;
    // 本小节主泳姿
    new_node->main_style = new_data->main_style;
    // 本小节配速（秒/百米）
    new_node->pace = new_data->pace;
    // 本小节swolf
    new_node->swolf = new_data->swolf;
    // 里程（米），室内游泳为泳池长度
    new_node->distance = new_data->distance;
    // 划水次数
    new_node->strokes = new_data->strokes;
    // 本小节划频(次/分钟)
    new_node->stroke_rate = new_data->stroke_rate;
    // 当前趟总卡路里（千卡），包含基础代谢BM
    new_node->total_cal = new_data->total_cal;
    // 当前趟活动卡路里（千卡）
    new_node->active_cal = new_data->active_cal;
    new_node->next = NULL;

    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        swim_list_count++;
    }
    else
    {
        sw_record_t *last = *head_ref;
        while (last->next != NULL)
        {
           // printf("last:0x%x,last_next:0x%x\n",last,last->next);
            last = last->next;
        }
        last->next = new_node;
        swim_list_count++;
    }
    printf("%s,0x%x,count:%d\n", __func__, new_node, swim_list_count);
    printList(p_swim_list);
}

// 读取指定节点
sw_record_t *zh_app_sport_swim_list_read(uint16_t offset)
{
    uint16_t i = 0;
    sw_record_t * cur = p_swim_list;
    if (cur != NULL)
    {
        while(cur != NULL)
        {
            if(i == offset)
            {
               // printf("offset:%d,cur:0x%x\n",offset,cur);
                return cur;
            }
            cur = cur->next;
            i++;
        }
        //没找到
        return NULL;
    }
    else
    {
        return NULL;
    }
}

// 删除所有节点
void zh_app_sport_swim_list_delete(void)
{
    if(p_swim_list){
    printf("delete_satrt:0x%x,0x%x\n", p_swim_list,p_swim_list->next);
        sw_record_t* list = p_swim_list->next;
        while (list != NULL)//第二个节点以及后面
        {
            printf("deletelist_addr:0x%x\n ", list);
            sw_record_t* next_list = list->next;
            free(list);
            list = next_list;
            swim_list_count--;
        }
        if(p_swim_list)//第一个节点
        {
             printf("headdeletelist_addr:0x%x\n ", p_swim_list);
             free(p_swim_list);
             p_swim_list = NULL;
             swim_list_count--;
        }
    printf("%s,%d\n", __func__, swim_list_count);
    }
}
// 打印链表
void printList(sw_record_t *head)
{
    // sw_record_t* list = head;
    // while (list != NULL)
    // {
    //     printf("list_addr:0x%x\n ", list);
    //     list = list->next;
    // }
}
#endif
//****************************************课程排序结构******************************************************
user_sports_course_t sport_course;
void init_app_sports_course_data(void)
{
    printf("init_app_sports_list_data:%d,%d\n", sizeof(sport_list_sort_array), sizeof(user_sport_list_type_t));
    memset(&sport_course, 0, sizeof(user_sports_course_t));
    for (uint8_t i = 0; i < Sport_Cource_max; i++)
    {
        sport_course.sport_course_list[i].sport_type = i + 1;
        sport_course.sport_course_list[i].base_index = i;
    }
}
void set_app_sports_course_data(user_sports_course_t *p_sport_course)
{
    memcpy(&sport_course, p_sport_course, sizeof(user_sports_course_t));
}
void get_app_sports_course_data(user_sports_course_t *p_sport_course)
{
    memcpy(p_sport_course, &sport_course, sizeof(user_sports_course_t));
}
//****************************************运动列表排序结构******************************************************
user_sport_list_type_t sport_list_sort_array[MAX_SPORT_SEETING_TARGET_NUM];
void init_app_sports_list_data(void)
{
    printf("init_app_sports_list_data:%d,%d\n", sizeof(sport_list_sort_array), sizeof(user_sport_list_type_t));
    memset(sport_list_sort_array, 0, sizeof(user_sport_list_type_t) * MAX_SPORT_SEETING_TARGET_NUM);
    for (uint8_t i = 0; i < MAX_SPORT_SEETING_TARGET_NUM; i++)
    {
        sport_list_sort_array[i].sport_use_count = 0;
        sport_list_sort_array[i].sport_type = i;
        sport_list_sort_array[i].sport_index = i;
        sport_list_sort_array[i].sport_gourp = module_ms_sport_app_get_group(sport_list_sort_array[i].sport_type, 1); // todo:by ly 增加运动类型分
    }
}
void set_app_sports_list_data(user_sport_list_type_t *p_sport_list)
{
    memcpy(sport_list_sort_array, p_sport_list, sizeof(user_sport_list_type_t) * MAX_SPORT_SEETING_TARGET_NUM);
}
void get_app_sports_list_data(user_sport_list_type_t *p_sport_list)
{
    memcpy(p_sport_list, sport_list_sort_array, sizeof(user_sport_list_type_t) * MAX_SPORT_SEETING_TARGET_NUM);
}

//-----------------------------------------运动记录运动设置相关数据---------------------------------------
uint8_t sport_save_data_record_num = 0;
uint8_t sport_save_data_record_table[MAX_SPORT_RECORD_NUM] = {0};
SPORT_setting_target_data_t sport_setting_target_data[MAX_SPORT_SEETING_TARGET_NUM] = {0};
Sport_Best_Data_t Sport_Best_Data[BEST_LOCAL_MAX] = {0};
SPORT_app_target_data_t sport_app_target = {0};
Sport_Best_Data_t Sport_Best_Data_APP[BEST_LOCAL_MAX] = {0};
ms_sport_misc_t misc_sport_data;
sport_detect_dst_t sport_detect_dst;
SPORT_data_save_data_t sport_save_data;
sport_param_s indoor_calibration;
SPORT_save_data_t sport_save_sport_record_data;
void clear_all_sport_seeting_data(void)
{

    for (uint32_t i = 0; i < MAX_SPORT_SEETING_TARGET_NUM; i++)
    {
        sport_setting_target_data[i].sport_seeting_choose_target = 0;
        sport_setting_target_data[i].sport_seeting_consume_data = 300;
        sport_setting_target_data[i].sport_seeting_distance_data = 5000;
        sport_setting_target_data[i].sport_seeting_time_data = 10;
        sport_setting_target_data[i].sport_seeting_count_data = 1000;
        if(i == SPORTING_swim_indoor_TYPE)//室内游泳默认 8 趟
        {
            sport_setting_target_data[i].sport_seeting_count_data = 8;        
        }
        if(i == SPORTING_swim_outdoor_TYPE)//开放水域游泳默认 1km
        {
            sport_setting_target_data[i].sport_seeting_distance_data = 1000;        
        }        
        if(i == SPORTING_Rowing_machine_TYPE)//划船机泳默认 200次
        {
            sport_setting_target_data[i].sport_seeting_count_data = 200;           
        }
        sport_setting_target_data[i].sport_heart_rate_warn_value = 150;
        // sport_list_array[i].sport_use_count = 0;
        // sport_list_array[i].sport_type =  i;
        // sport_list_array[i].sport_index = i;
        // sport_list_array[i].sport_gourp = 0;//todo:by ly 增加运动类型分组
        module_ms_app_sport_set_sport_target(i, SPORT_SEETING_HR); // hr默认开
        if (i == SPORTING_swim_indoor_TYPE || i == SPORTING_swim_outdoor_TYPE)
        {
            module_ms_app_sport_clear_sport_target(i, SPORT_SEETING_HR); // 游泳心率关
        }
        if (module_ms_app_is_distance_sport_type(i))
        {
            module_ms_app_sport_set_sport_target(i, SPORT_SEETING_DISTANCE_REMIND);
            sport_setting_target_data[i].sport_distance_remind = 1000;
        }
        else
        {
            module_ms_app_sport_clear_sport_target(i, SPORT_SEETING_DISTANCE_REMIND);
            sport_setting_target_data[i].sport_distance_remind = 0;
        }
        if (i == SPORTING_Outdoor_cycling_TYPE)
        {
            sport_setting_target_data[i].sport_pace_or_speed_remind = 25 * 1000; // 放大1000用于转换
            sport_setting_target_data[i].sport_seeting_distance_data = 10000;
        }
        else
        {
            if(i == SPORTING_Outdoor_walking_TYPE)
            {
                sport_setting_target_data[i].sport_pace_or_speed_remind = 600;
            }
            else
                sport_setting_target_data[i].sport_pace_or_speed_remind = 330;
        }
        sport_setting_target_data[i].sport_energy_supply_remind_dis = 1000;
        sport_setting_target_data[i].sport_energy_supply_remind_time = 30;
        // 间歇训练
        module_ms_app_sport_clear_sport_target(i, SPORT_INTERVAL_TRAINING_SWITCH);
        module_ms_app_sport_clear_sport_target(i, SPORT_WARM_UP_SWITCH);
        module_ms_app_sport_clear_sport_target(i, SPORT_RELAX_SWITCH);
        module_ms_app_sport_clear_sport_target(i, SPORT_SEETING_AUTO_PAUSE);
        if (i == SPORTING_Outdoor_cycling_TYPE)
        {
            sport_setting_target_data[i].sport_interval_training_dis = 5000;
        }
        else if (i == SPORTING_Outdoor_running_TYPE)
        {
            sport_setting_target_data[i].sport_interval_training_dis = 2000;
        }
        else
        {
            sport_setting_target_data[i].sport_interval_training_dis = 0;
        }
        if (i == SPORTING_Rowing_machine_TYPE)
        {
            sport_setting_target_data[i].sport_interval_training_times = 200;
        }
        else if (i == SPORTING_Skipping_rope_H_TYPE)
        {
            sport_setting_target_data[i].sport_interval_training_count = 500;
        }
        else
        {
            sport_setting_target_data[i].sport_interval_training_count = 0;
            sport_setting_target_data[i].sport_interval_training_times = 0;
        }
        module_ms_app_sport_set_sport_target(i, SPORT_INTERVAL_TRAINING_TIME); // 间歇训练时间默认开
        module_ms_app_sport_clear_sport_target(i, SPORT_INTERVAL_TRAINING_TIMES);
        module_ms_app_sport_clear_sport_target(i, SPORT_INTERVAL_TRAINING_DEST);
        module_ms_app_sport_clear_sport_target(i, SPORT_INTERVAL_TRAINING_COUNT);
        sport_setting_target_data[i].sport_interval_training_time = 5 * 60;    // 秒
        sport_setting_target_data[i].sport_interval_training_rest = 2 * 60;    // 秒
        sport_setting_target_data[i].sport_interval_training_loop = 3;
        sport_setting_target_data[i].sport_accompanying_running_pace = 330; // 陪跑配速
        sport_setting_target_data[i].sport_pool_length = 25;                //泳池长度最大200
        sport_setting_target_data[i].sport_heart_rate_zones = 0;//心率区间0->closs,1->热身.....5->极限
    }
    indoor_calibration.data_len = 0;
	memset(&sport_detect_dst,0,sizeof(sport_detect_dst));
    sport_detect_dst.remind_sport_end = 1;//出厂默认开启结束提醒
    for (uint8_t i = 0; i < BEST_LOCAL_MAX; i++)
    {
            memset(&Sport_Best_Data[i], 0, sizeof(Sport_Best_Data_t));
            memset(&Sport_Best_Data_APP[i], 0, sizeof(Sport_Best_Data_t));
    }
    misc_sport_data.swim_remind = 0;
    // Goal_Type Goal_array[4] = {Goal_Type_STEP, Goal_Type_CALORIE, Goal_Type_INTENSITY, Goal_Type_STAND};
    // vigor_index_list.current_count = 3;
    // for (uint8_t i = 0; i < 3; i++)
    // {
    //         vigor_index_list.current_goals_type[i].type = Goal_array[i];
    // }
    // vigor_index_list.supported_count = 4;
    // for (uint8_t i = 0; i < 4; i++)
    // {
    //         vigor_index_list.supported_goals_type[i].type = Goal_array[i];
    // }
}
void sport_save_data_clear(void)
{
    // #ifndef BSP_USING_PC_SIMULATOR
    /* 运动开始需要清除数据 */
    sport_save_data.sport_time_start = 0;// get_wall_clock_time_counter(); // 开始时间（秒)
    sport_save_data.sport_time_zone = mul_sport_get_time_zone();
    sport_save_data.sport_time_count = 0;                  // 用时（秒）
    sport_save_data.sport_distance = 0;                    // 距离（米/秒）
    sport_save_data.sport_Speed_distribution = 0;          // 当前配速（秒/米）
    sport_save_data.sport_avg_Speed_distribution = 0;      // 平均配速（秒/米）
    sport_save_data.sport_Speed_distribution_last_1km = 0; // 上公里配速（秒/米）
    sport_save_data.sport_Maximum_Speed_distribution = 0;  // 上公里最大配速（秒/米）
    sport_save_data.sport_Miximum_Speed_distribution = 0;  // 上公里最小配速（秒/米）
    sport_save_data.sport_Speed_distribution_max = 0;      // 最高配速
    sport_save_data.sport_Speed_distribution_min = 0;      // 最低配速
// sport_data_get_second_step();//todo:by ly
#ifndef BSP_USING_PC_SIMULATOR
    memset(&heart_range_info, 0, sizeof(SPORT_HEART_RATE_INFO_STRU)); // 清除上一次心率区间值
#endif
    sport_save_data.sport_Step_number = 0;                      // 步数
    sport_save_data.sport_Step_frequency = 0;                   // 当前步频
    sport_save_data.sport_Maximum_Step_frequency = 0;           // 最大步频
    sport_save_data.sport_Maximum_Step_frequency_timestamp = 0; // 最大步频出现的时间戳（秒）
    sport_save_data.sport_ave_Step_frequency = 0;               // 平均步频
    sport_save_data.sport_step_length = 0;                      // 当前步幅

    sport_save_data.sport_Speed = 0;                         // 当前速度（米/秒）
    sport_save_data.sport_average_velocity = 0;              // 平均速度（米/秒）
    sport_save_data.sport_onekilometre_average_velocity = 0; // 上公里速度（米/秒）
    sport_save_data.sport_Limit_speed = 0;                   // 最大速度（米/秒）
    sport_save_data.sport_Limit_speed_timestamp = 0;         // 最大速度出现的时间戳（秒）

    sport_save_data.sport_strength = 0; // 运动强度
    sport_save_data.sport_consume = 0;  // 消耗（cal）
    misc_sport_data.total_consume = 0;
    misc_sport_data.sport_timestamp = (sport_save_data.sport_time_start - mul_sport_get_time_zone_offset(mul_sport_get_time_zone()));
    sport_save_data.sport_heart_rate = 4;// get_heart_value_messure_menu();// 心率
    sport_save_data.sport_Mean_heart_rate = 0;        // 平均心率
    sport_save_data.sport_Maximum_heart_rate = 0;     // 最大心率
    sport_save_data.sport_Miximum_heart_rate = 0;     // 最小心率
    sport_save_data.sport_heart_rate_count = 0;       // 心率-总时长（秒）
    sport_save_data.sport_heart_rate_count_1 = 0;     // 心率-极限时长（秒）
    sport_save_data.sport_heart_rate_count_2 = 0;     // 心率-无氧耐力时长（秒）
    sport_save_data.sport_heart_rate_count_3 = 0;     // 心率-有氧耐力时长（秒）
    sport_save_data.sport_heart_rate_count_4 = 0;     // 心率-燃脂时长（秒）
    sport_save_data.sport_heart_rate_count_5 = 0;     // 心率-热身时长（秒）
    sport_save_data.sport_basic_altitude = 0;         // 基础海拔
    sport_save_data.sport_relative_up_altitude = 0;   // 累计上升
    sport_save_data.sport_relative_down_altitude = 0; // 累计下降
    sport_save_data.sport_max_altitude = 0;           // 最高海拔
    sport_save_data.sport_min_altitude = 0;           // 最低海拔
    sport_save_data.sport_current_altitude = 0;       // 当前海拔
    sport_save_data.sport_avg_high = 0;               // 平均高度
    sport_save_data.sport_max_high = 0;               // 最大高度
    sport_save_data.sport_min_high = 0;               // 最小高度
    misc_sport_data.sport_upload_steps = 0;
    sport_save_data.sport_seeting_choose_target = 0;
    sport_save_data.sport_setting_target = 0;
    sport_save_data.sport_rm_count = 0;     //    跳绳划船机次数
    sport_save_data.sport_rm_frequency = 0; //  跳绳划船机频率
    sport_save_data.sport_max_freq = 0;
    sport_save_data.sport_avg_freq = 0;
    misc_sport_data.have_phone_gps_data = 0;
    misc_sport_data.gps_data_timer = 0;
    misc_sport_data.cal_distance = 0;
    misc_sport_data.sport_upload_kcal = 0;
    sport_save_data.sport_number_of_tips = 0;                     // 泳池趟数
    sport_save_data.sport_main_swimming_posture = 0;               // 主要泳姿
    sport_save_data.sport_avg_swolf = 0;                          // 游泳平均swolf
    sport_save_data.sport_paddling_count = 0;                     // 划水数
    sport_save_data.avg_sliding_frequency = 0;                    // 平均频次/分
    memset(&misc_sport_data.swim_data,0,sizeof(misc_sport_data.swim_data));
    memset(&misc_sport_data.swim_segmet_data,0,sizeof(misc_sport_data.swim_segmet_data));
    misc_sport_data.swim_count = 0;
    misc_sport_data.swim_data.sub_section_count = 0;
    mul_sport_platform_auto_sport_memset_gps_data();//清除运动识别gps缓存buffer
#if GPS_TRACK_DRAW == 1
    misc_sport_data.gps_lat = NULL;
    misc_sport_data.gps_lon = NULL;
    misc_sport_data.gps_temp_x = NULL;
    misc_sport_data.gps_temp_y = NULL;
    sport_save_data.lon = NULL;
    sport_save_data.lat = NULL;
    sport_save_data.len = 0;
    sport_save_data.gps_draw_track_count = 0;
    memset(&sport_save_data.gps_track[0],0,sizeof(gps_track_t)*GPS_TRACK_LEN);
    memset(&misc_sport_data.auto_sport_obj,0,sizeof(misc_sport_data.auto_sport_obj));
    misc_sport_data.swim_data.swim_is_write = 0;
    misc_sport_data.swim_get_record = 0;
#endif
    memset(&sport_save_data.sport_heart_chart[0], 0, sizeof(lv_point_t) * CHART_MAX);
    memset(&sport_save_data.sport_steps_frequency_chart[0], 0, sizeof(lv_point_t) * CHART_MAX);
    memset(&sport_save_data.sport_pace_chart[0], 0, sizeof(lv_point_t) * CHART_MAX);
    sport_save_data.sport_Speed_distribution_min = 0;
    sport_save_data.sport_genki_value = 0;            // 元气值
    sport_save_data.sport_Minimum_Step_frequency = 0; // 最小步频大于0
    sport_save_data.sport_Min_speed = 0;              // 最小速度(千米/小时(已放大100倍使用进行单位转换))（已有数据）大于0
    sport_save_data.sport_min_freq = 0;               // 划船机跳绳最小频率大于0
    sport_save_data.sport_pace_chart_count = 0;
    sport_save_data.sport_heart_chart_count = 0;
    sport_save_data.sport_steps_frequency_chart_count = 0;
    misc_sport_data.draw_points_complete = 0;
    misc_sport_data.draw_points_flag = 0;
    misc_sport_data.sport_loading_count = 1;
    sport_save_data.sport_min_swolf = 0;
    sport_save_data.sport_max_swolf = 0;
  //  sport_remind_struct.gps_weak_no_remind = 0;
  ///  sport_remind_struct.gps_weak_delay_count = 20;
  //  sport_remind_struct.gps_weak_time_count = 0;
    misc_sport_data.total_avg_steps_lenght = 0;
    misc_sport_data.total_avg_steps_lenght_count = 0;
    if(Get_current_sporting_type() != SPORTING_swim_indoor_TYPE&&Get_current_sporting_type() != SPORTING_swim_outdoor_TYPE)
    misc_sport_data.sport_lock_flag = 0;
#if INTERVAL_TRAINING_SELECT
    if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_SWITCH))
    {
        if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_DEST))
        {
            sport_interval_training.mode = Sport_MODE_DISTANCE;
        }
        else if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_TIME))
        {
            sport_interval_training.mode = Sport_MODE_TIME;
        }
        else
        {
            sport_interval_training.mode = Sport_MODE_COUNT;
        }
        sport_interval_training.completion_times = 1;
        sport_interval_training.total_times = sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_loop * 2 - 1;
        if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_WARM_UP_SWITCH))
        {
            sport_interval_training.total_times++;
        }
        if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_RELAX_SWITCH))
        {
            sport_interval_training.total_times++;
        }

        if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_WARM_UP_SWITCH))
        {
            sport_interval_training.type = INTERVAL_TRAINING_WARM_UP;
        }
        else
        {
            // sport_interval_training.type = INTERVAL_TRAINING_WARM_UP;
            sport_interval_training.type = INTERVAL_TRAINING;
        }
        sport_interval_training.segment_timestamp = mul_sport_get_timestamp();
        sport_interval_training.current_distance = 0;
        sport_interval_training.total_distance = sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_dis;
        sport_interval_training.current_time_count = 0;
        sport_interval_training.current_count = 0;
        sport_interval_training.total_time_count = sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_time;
        sport_interval_training.total_count = sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_count;
    }
    else
    {
        sport_interval_training.completion_times = 0;
        sport_interval_training.current_distance = 0;
        sport_interval_training.current_time_count = 0;
        sport_interval_training.mode = 0;
        sport_interval_training.total_distance = 0;
        sport_interval_training.total_times = 0;
        sport_interval_training.total_time_count = 0;
        sport_interval_training.type = 0;
    }
#endif
    misc_sport_data.sports_send_cmd_switch = false;
    misc_sport_data.send_request_timeout = 0;
    misc_sport_data.sport_interval_train_is_close = 0;
	misc_sport_data.used_timestamp = 0;
	misc_sport_data.have_phone_gps_data = 0;
	misc_sport_data.have_device_gps_data = 0;
	misc_sport_data.have_app_gps_data = 0;
	misc_sport_data.useddeive_cnt = 0;
	misc_sport_data.usedphone_cnt = 0;
	misc_sport_data.newmark = 0;
   // trace_gps_obj_init();
    module_ms_app_sport_clear_points_flag();//清除游泳flag
    misc_sport_data.auto_sportting_flag = false;//从运动识别进入运动中的标志
	//printf("used_timestamp x %d\n",misc_sport_data.used_timestamp);
    /// zh_log_printk("interval_training_type = %d,switch = %d,cur_sport_type:%d\n",sport_interval_training.type,module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_WARM_UP_SWITCH),Get_current_sporting_type());
    // set_sport_time_count(0);//todo:by ly
    // clear_all_sport_status();//todo:by ly
#if USE_APP_ASSIST_SPORT_SWITCH
    clear_last_longitude_latitude();
#endif
#if ! defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)&&defined(ENUM_PROJECT_NAME_N65B_GLOBAL)
    uint32_t time =  Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.start_timestamp;
    memset(&Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch,0,sizeof(Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch));
    Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.start_timestamp = time;
#endif
    // #endif
}
void set_sport_record_data(SPORT_save_data_t *data, uint8_t record_table)
{
    // nvms_t account_part = ad_nvms_open(NVMS_USER_DATA_PART);
  //  ad_nvms_write(USER_DATA_START_ADDRESS, sport_record_save_data_start + sizeof(SPORT_save_data_t) * record_table, (uint8_t *)data, sizeof(SPORT_save_data_t));
}
void get_sport_record_data(SPORT_save_data_t *data, uint8_t record_table)
{
 //   ad_nvms_read(USER_DATA_START_ADDRESS, sport_record_save_data_start + sizeof(SPORT_save_data_t) * record_table, (uint8_t *)data, sizeof(SPORT_save_data_t));
}
void clear_sports_information_data(void)
{
    // nvms_t account_part = ad_nvms_open(NVMS_USER_DATA_PART);
  //  ad_nvms_erase_region(USER_DATA_START_ADDRESS, supplement_of_sports_data_start, 4096); // supplement_of_sports_data_size);
    sport_save_data_record_num = 0;                                                       // 多运动数据存储的个数
    for (uint8_t i = 0; i < MAX_SPORT_RECORD_NUM; i++)
    {
        sport_save_data_record_table[i] = 0xAA; // 多运动数据
    }
    misc_sport_data.remind_wear_count = 0;
    misc_sport_data.support_sport_screen = 0;
    clear_all_sport_seeting_data();
}
void check_sport_record_table_was_true(void)
{
        uint8_t recrod_sport_num = 0;
        uint8_t j = 0;
        for (j = 0; j < MAX_SPORT_RECORD_NUM; j++)
        {
                if (sport_save_data_record_table[j] < MAX_SPORT_RECORD_NUM)
                {
                        recrod_sport_num++;
                }
        }
        if (recrod_sport_num != sport_save_data_record_num)
        {
                sport_save_data_record_num =0;
                for (j = 0; j < MAX_SPORT_RECORD_NUM; j++)
                {
                        sport_save_data_record_table[j] = 0xAA;  
                }
        }
                
}
void read_sport_information_data_init(void)
{
    // nvms_t account_part = ad_nvms_open(NVMS_USER_DATA_PART);
    uint8_t *buffer = malloc(supplement_of_sports_data_size);
    if (buffer == NULL) // zhang add 补丁
    {
        return;
    }
   // ad_nvms_read(USER_DATA_START_ADDRESS, supplement_of_sports_data_start, (uint8_t *)buffer, supplement_of_sports_data_size);
    uint16_t buffer_size = 0;
    if (buffer[0] == 0xA6 && buffer[1] == 0xA6 && buffer[2] == 0xA6 && buffer[3] == 0xA6) // head 头
    {
        buffer_size += 4;
        // 21 多运动数据存储的个数
        memcpy((uint8_t *)&sport_save_data_record_num, &buffer[buffer_size], sizeof(uint8_t));
        buffer_size += (sizeof(uint8_t) / sizeof(uint8_t));
        if (sport_save_data_record_num > MAX_SPORT_RECORD_NUM)
        {
            sport_save_data_record_num = 0;
        }

        // 22 多运动数据
        memcpy((uint8_t *)&sport_save_data_record_table[0], &buffer[buffer_size], sizeof(uint8_t) * MAX_SPORT_RECORD_NUM);
        buffer_size += (sizeof(uint8_t) * MAX_SPORT_RECORD_NUM / sizeof(uint8_t));
        // 运动设置
        memcpy((uint8_t *)&sport_setting_target_data[0], &buffer[buffer_size], sizeof(SPORT_setting_target_data_t) * MAX_SPORT_SEETING_TARGET_NUM);
        buffer_size += (sizeof(SPORT_setting_target_data_t) * MAX_SPORT_SEETING_TARGET_NUM / sizeof(uint8_t));//
        memcpy((uint8_t *)&Sport_Best_Data[0], &buffer[buffer_size], sizeof(Sport_Best_Data_t) * BEST_LOCAL_MAX);
        buffer_size += (sizeof(Sport_Best_Data_t) * BEST_LOCAL_MAX);
        memcpy((uint8_t *)&Sport_Best_Data_APP[0],&buffer[buffer_size] , sizeof(Sport_Best_Data_t) * BEST_LOCAL_MAX);
        buffer_size += (sizeof(Sport_Best_Data_t) * BEST_LOCAL_MAX);
        memcpy((uint8_t *)&indoor_calibration,&buffer[buffer_size] , sizeof(sport_param_s));//室内校准读
        buffer_size += (sizeof(sport_param_s));   
		 memcpy((uint8_t *)&sport_detect_dst,&buffer[buffer_size] , sizeof(sport_detect_dst));//室内校准读
        buffer_size += (sizeof(sport_detect_dst)); 
        memcpy((uint8_t *)&misc_sport_data.remind_wear_count ,&buffer[buffer_size] ,sizeof(uint8_t));//弹窗次数,恢复出厂或者链接手机时清除
        buffer_size += (sizeof(uint8_t) / sizeof(uint8_t));
        memcpy((uint8_t *)&misc_sport_data.support_sport_screen ,&buffer[buffer_size] ,sizeof(uint8_t));//投屏是否支持,连接手表时会下发
        buffer_size += (sizeof(uint8_t) / sizeof(uint8_t));
        memcpy((uint8_t *)&misc_sport_data.swim_remind ,&buffer[buffer_size] ,sizeof(uint8_t));//游泳锁屏提示,恢复出厂重置
        buffer_size += (sizeof(uint8_t) / sizeof(uint8_t));
        check_sport_record_table_was_true();
        printf("%s size:%d\n",__func__,buffer_size);
    }
    else
    {
        clear_all_sport_seeting_data();
        clear_sports_information_data();
        save_sport_information_data_init();
    }
    free(buffer);
}
void save_sport_information_data_init(void)
{
    // nvms_t account_part = ad_nvms_open(NVMS_USER_DATA_PART);
    uint8_t *buffer = malloc(supplement_of_sports_data_size);
    if (buffer == NULL) // zhang add 补丁
    {
        return;
    }
    uint16_t buffer_size = 0;
    buffer[0] = 0xA6; // head 头
    buffer[1] = 0xA6;
    buffer[2] = 0xA6;
    buffer[3] = 0xA6;
    buffer_size += 4;
    memcpy(&buffer[buffer_size], (uint8_t *)&sport_save_data_record_num, sizeof(uint8_t)); // 21 多运动数据存储的个数
    buffer_size += (sizeof(uint8_t) / sizeof(uint8_t));
    memcpy(&buffer[buffer_size], (uint8_t *)&sport_save_data_record_table[0], sizeof(uint8_t) * MAX_SPORT_RECORD_NUM); // 22 多运动表格
    buffer_size += (sizeof(uint8_t) * MAX_SPORT_RECORD_NUM / sizeof(uint8_t));
    memcpy(&buffer[buffer_size], (uint8_t *)&sport_setting_target_data[0], sizeof(SPORT_setting_target_data_t) * MAX_SPORT_SEETING_TARGET_NUM);
    buffer_size += (sizeof(SPORT_setting_target_data_t) * MAX_SPORT_SEETING_TARGET_NUM / sizeof(uint8_t));
    memcpy(&buffer[buffer_size], (uint8_t *)&Sport_Best_Data[0], sizeof(Sport_Best_Data_t) * BEST_LOCAL_MAX);
    buffer_size += (sizeof(Sport_Best_Data_t) * BEST_LOCAL_MAX);
    memcpy(&buffer[buffer_size], (uint8_t *)&Sport_Best_Data_APP[0], sizeof(Sport_Best_Data_t) * BEST_LOCAL_MAX);
    buffer_size += (sizeof(Sport_Best_Data_t) * BEST_LOCAL_MAX);
    memcpy(&buffer[buffer_size], (uint8_t *)&indoor_calibration, sizeof(sport_param_s));//室内校准存
    buffer_size += (sizeof(sport_param_s));   
	memcpy(&buffer[buffer_size], (uint8_t *)&sport_detect_dst, sizeof(sport_detect_dst));//室内校准存
    buffer_size += (sizeof(sport_detect_dst));  
    memcpy(&buffer[buffer_size] ,(uint8_t *)&misc_sport_data.remind_wear_count,sizeof(uint8_t));//弹窗次数,恢复出厂或者链接手机时清除
    buffer_size += (sizeof(uint8_t) / sizeof(uint8_t)); 
    memcpy(&buffer[buffer_size] ,(uint8_t *)&misc_sport_data.support_sport_screen ,sizeof(uint8_t));//投屏是否支持,连接手表时会下发
    buffer_size += (sizeof(uint8_t) / sizeof(uint8_t));
    memcpy(&buffer[buffer_size] ,(uint8_t *)&misc_sport_data.swim_remind ,sizeof(uint8_t));//游泳锁屏提示,恢复出厂重置
    buffer_size += (sizeof(uint8_t) / sizeof(uint8_t));
    printf("%s buffer_size:%d\n",__func__, buffer_size);
 //   ad_nvms_write(USER_DATA_START_ADDRESS, supplement_of_sports_data_start, (uint8_t *)buffer, buffer_size);
    free(buffer);
}
void get_max_min_data_postion(double max_pre, double min_pre, uint16_t *max_tmp, uint16_t *min_tmp)
{
#define TARGET_MAX 60
    uint32_t total_points = 0;
    uint32_t T = mul_sport_get_cur_record_item_nums();
    uint16_t M = T / TARGET_MAX;
    if (T % TARGET_MAX != 0)
    {
        M = M + 1; // 向上取整
    }
    uint16_t N = T / M;
    if (T % M != 0)
    {
        N = N + 1; // 向上取整
    }
    if (N > TARGET_MAX)
    {
        N = TARGET_MAX;
    }
    if (*min_tmp == *max_tmp)
    {
        if (max_pre > min_pre)
        {
            if (*max_tmp < N)
            {
                *min_tmp = *max_tmp - 1;
            }
            else
            {
                *max_tmp = N;
                *min_tmp = *max_tmp - 1;
            }
        }
        else
        {
            if (*min_tmp < N)
            {
                *max_tmp = *min_tmp - 1;
            }
            else
            {
                *min_tmp = N;
                *max_tmp = *min_tmp - 1;
            }
        }
    }
}
#define PATCH_OPERATION(MAX_POPINT, MIN_POINT, T, N, chart, max_value, min_value) \
    {                                                                             \
        double max_pre = (double)MAX_POPINT / (double)T;                          \
        uint16_t max_tmp = max_pre * N;                                           \
        bool is_assign = true;                                                    \
        double min_pre = (double)MIN_POINT / (double)T;                           \
        uint16_t min_tmp = min_pre * N;                                           \
        printf("max_tmp:%d,min_tmp:%d,%lf,%lf\n",max_tmp,min_tmp,max_pre,min_pre);\
        get_max_min_data_postion(max_pre, min_pre, &max_tmp, &min_tmp);           \
        if (MAX_POPINT)                                                           \
        {                                                                         \
            if (max_tmp <= N)                                                     \
            {                                                                     \
                for (uint8_t i = 0; i < N; i++)                                   \
                {                                                                 \
                    if (chart[i].v.value == max_value)                            \
                    {                                                             \
                        is_assign = false;                                        \
                    }                                                             \
                }                                                                 \
                if (is_assign)                                                    \
                {                                                                 \
                    printf("insertmax:%d\n",max_value);                       \
                    chart[max_tmp].v.value = max_value;                           \
                }                                                                 \
            }                                                                     \
        }                                                                         \
        is_assign = true;                                                         \
        if (MIN_POINT)                                                            \
        {                                                                         \
            if (min_tmp <= N)                                                     \
            {                                                                     \
                for (uint8_t i = 0; i < N; i++)                                   \
                {                                                                 \
                    if (chart[i].v.value == min_value)                            \
                    {                                                             \
                        is_assign = false;                                        \
                    }                                                             \
                }                                                                 \
                if (is_assign)                                                    \
                {                                                                 \
                    printf("insertmin:%d\n",max_value);                       \
                    chart[min_tmp].v.value = min_value;                           \
                }                                                                 \
            }                                                                     \
        }                                                                         \
    }

#define PATCH_OPERATIONS(MAX_POPINT, MIN_POINT, T, N, chart, max_values, min_values)       \
    {                                                                                      \
        double max_pre = (double)MAX_POPINT / (double)T;                                   \
        uint16_t max_tmp = max_pre * N;                                                    \
        bool is_assign = true;                                                             \
        double min_pre = (double)MIN_POINT / (double)T;                                    \
        uint16_t min_tmp = min_pre * N;                                                    \
        printf("max_tmp:%d,min_tmp:%d,%lf,%lf\n", max_tmp, min_tmp, max_pre, min_pre); \
        get_max_min_data_postion(max_pre, min_pre, &max_tmp, &min_tmp);                    \
        if (MAX_POPINT)                                                                    \
        {                                                                                  \
            if (max_tmp <= N)                                                              \
            {                                                                              \
                for (uint8_t i = 0; i < N; i++)                                            \
                {                                                                          \
                    if (chart[i].v.value == max_values.values.value)                       \
                    {                                                                      \
                        is_assign = false;                                                 \
                    }                                                                      \
                }                                                                          \
                if (is_assign && max_values.values.valid)                                  \
                {                                                                          \
                    printf("insertmax:%d\n", max_values.values.value);                 \
                    chart[max_tmp].v.value = max_values.values.value;                      \
                }                                                                          \
            }                                                                              \
        }                                                                                  \
        is_assign = true;                                                                  \
        if (MIN_POINT)                                                                     \
        {                                                                                  \
            if (min_tmp <= N)                                                              \
            {                                                                              \
                for (uint8_t i = 0; i < N; i++)                                            \
                {                                                                          \
                    if (chart[i].v.value == min_values.values.value)                       \
                    {                                                                      \
                        is_assign = false;                                                 \
                    }                                                                      \
                }                                                                          \
                if (is_assign && min_values.values.valid)                                  \
                {                                                                          \
                    printf("insertmin:%d\n", min_values.values.value);                 \
                    chart[min_tmp].v.value = min_values.values.value;                      \
                }                                                                          \
            }                                                                              \
        }                                                                                  \
    }
void record_supplementary_point(uint16_t sport_type) // 补点
{
#define TARGET_MAX 60
    uint32_t total_points = 0;
    uint32_t T = mul_sport_get_cur_record_item_nums();
    uint16_t M = T / TARGET_MAX;
    if (T % TARGET_MAX != 0)
    {
        M = M + 1; // 向上取整
    }
    uint16_t N = T / M;
    if (T % M != 0)
    {
        N = N + 1; // 向上取整
    }
    if (N > TARGET_MAX)
    {
        N = TARGET_MAX;
    }
    printf("record_supplementary_point M:%d,N:%d\n", M, N);
    switch (sport_type)
    {
    case SPORTING_Outdoor_running_TYPE: // 心率,pace,步频
    case SPORTING_Indoor_running_TYPE:  // 心率,pace,步频
    case SPORTING_Outdoor_walking_TYPE: // 心率,pace,步频
    {
        // 心率
        PATCH_OPERATION(misc_sport_data.record_max.run_c.max_hr_point,
                        misc_sport_data.record_max.run_c.min_hr_point, T, N,
                        sport_save_data.sport_heart_chart, sport_save_data.sport_Maximum_heart_rate, sport_save_data.sport_Miximum_heart_rate);
        printf("runc_max_p:%d,runc_min_p:%d,hr_:%d,hr1:%d,cad:%d,cad1:%d,%d,%d\n",
                   misc_sport_data.record_max.run_c.max_pace_point,
                   misc_sport_data.record_max.run_c.min_pace_point,
                   misc_sport_data.record_max.run_c.max_hr_point,
                   misc_sport_data.record_max.run_c.min_hr_point,
                   misc_sport_data.record_max.run_c.max_cadence_point,
                   misc_sport_data.record_max.run_c.min_cadence_point,
                   misc_sport_data.record_max.run_c.max_pace_value,
                   misc_sport_data.record_max.run_c.min_pace_value);
            // pace
            PATCH_OPERATIONS(misc_sport_data.record_max.run_c.max_pace_point,
                            misc_sport_data.record_max.run_c.min_pace_point, T, N,
                            sport_save_data.sport_pace_chart, misc_sport_data.record_max.run_c.max_pace_value, misc_sport_data.record_max.run_c.min_pace_value);
        // cadence
        PATCH_OPERATION(misc_sport_data.record_max.run_c.max_cadence_point,
                        misc_sport_data.record_max.run_c.min_cadence_point, T, N,
                        sport_save_data.sport_steps_frequency_chart, sport_save_data.sport_Maximum_Step_frequency, sport_save_data.sport_Minimum_Step_frequency);
    }
    break;
    case SPORTING_Outdoor_cycling_TYPE: // 心率,speed
    case SPORTING_Mountaineering_TYPE:  // 登山
    case SPORTING_Off_road_TYPE:        // 越野
    case SPORTING_Outdoor_hiking_TYPE:
    {
        // 心率
        PATCH_OPERATION(misc_sport_data.record_max.out_non_run_c.max_hr_point,
                        misc_sport_data.record_max.out_non_run_c.min_hr_point, T, N,
                        sport_save_data.sport_heart_chart, sport_save_data.sport_Maximum_heart_rate, sport_save_data.sport_Miximum_heart_rate);
        // 速度
        PATCH_OPERATIONS(misc_sport_data.record_max.out_non_run_c.max_speed_point,
                        misc_sport_data.record_max.out_non_run_c.min_speed_point, T, N,
                        sport_save_data.sport_pace_chart, misc_sport_data.record_max.out_non_run_c.max_speed_value, misc_sport_data.record_max.out_non_run_c.min_speed_value);//这里是放大100倍,图表放大十倍,显示除以10
    }
    break;
    case SPORTING_Skipping_rope_H_TYPE: // 心率,频率
    {
        // 心率
        PATCH_OPERATION(misc_sport_data.record_max.rope_skip.max_hr_point,
                        misc_sport_data.record_max.rope_skip.min_hr_point, T, N,
                        sport_save_data.sport_heart_chart, sport_save_data.sport_Maximum_heart_rate, sport_save_data.sport_Miximum_heart_rate);
        // 频率
        PATCH_OPERATION(misc_sport_data.record_max.rope_skip.max_action_freq_point,
                        misc_sport_data.record_max.rope_skip.min_action_freq_point, T, N,
                        sport_save_data.sport_steps_frequency_chart, sport_save_data.sport_max_freq, sport_save_data.sport_min_freq);
    }
    break;
    case SPORTING_Elliptical_machine_TYPE: // 心率,步频
    {
        // 心率
        PATCH_OPERATION(misc_sport_data.record_max.elliptical_m.max_hr_point,
                        misc_sport_data.record_max.elliptical_m.min_hr_point, T, N,
                        sport_save_data.sport_heart_chart, sport_save_data.sport_Maximum_heart_rate, sport_save_data.sport_Miximum_heart_rate);
        // 步频
        PATCH_OPERATION(misc_sport_data.record_max.elliptical_m.max_cadence_point,
                        misc_sport_data.record_max.elliptical_m.min_cadence_point, T, N,
                        sport_save_data.sport_steps_frequency_chart, sport_save_data.sport_Maximum_Step_frequency, sport_save_data.sport_Minimum_Step_frequency);
    }
    break;
    case SPORTING_Rowing_machine_TYPE: // 心率,划频
    {
        // 心率
        PATCH_OPERATION(misc_sport_data.record_max.rowing_m.max_hr_point,
                        misc_sport_data.record_max.rowing_m.min_hr_point, T, N,
                        sport_save_data.sport_heart_chart, sport_save_data.sport_Maximum_heart_rate, sport_save_data.sport_Miximum_heart_rate);
        // 划频
        PATCH_OPERATION(misc_sport_data.record_max.rowing_m.max_action_freq_point,
                        misc_sport_data.record_max.rowing_m.min_action_freq_point, T, N,
                        sport_save_data.sport_steps_frequency_chart, sport_save_data.sport_max_freq, sport_save_data.sport_min_freq);
    }
    break;
    case SPORTING_swim_indoor_TYPE:  // 泳池游泳
    case SPORTING_swim_outdoor_TYPE: // 开放水域游泳:
    {
        if (mul_sport_get_cur_record_item_nums() > TARGET_MAX)
        {
            // pace
            PATCH_OPERATION(misc_sport_data.record_max.swimming.max_pace_point,
                            misc_sport_data.record_max.swimming.min_pace_point, T, N,
                            sport_save_data.sport_pace_chart, sport_save_data.sport_Speed_distribution_max, sport_save_data.sport_Speed_distribution_min);
            // 划频
            PATCH_OPERATION(misc_sport_data.record_max.swimming.max_pull_rate_point,
                            misc_sport_data.record_max.swimming.min_pull_rate_point, T, N,
                            sport_save_data.sport_steps_frequency_chart, sport_save_data.sport_max_freq, sport_save_data.sport_min_freq);
            // swolf
            PATCH_OPERATION(misc_sport_data.record_max.swimming.max_swolf_point,
                            misc_sport_data.record_max.swimming.min_swolf_point, T, N,
                            sport_save_data.sport_heart_chart, sport_save_data.sport_max_swolf, sport_save_data.sport_min_swolf);
        }
        else
        {
        }
    }
    break;
    default: // 心率
    {
        // 心率
        PATCH_OPERATION(misc_sport_data.record_max.free_sport.max_hr_point,
                        misc_sport_data.record_max.free_sport.min_hr_point, T, N,
                        sport_save_data.sport_heart_chart, sport_save_data.sport_Maximum_heart_rate, sport_save_data.sport_Miximum_heart_rate);
    }
    break;
    }
}
#if defined(USING_GYRO_SENSOR) && defined(ENUM_PROJECT_NAME_N65B_GLOBAL) 
extern trk_out_s trk_max[4];
lv_point_t zh_sport_center_to_window_coordinates(trace_gps_point_t* p_point, double width, double hight)
{
    lv_point_t point;
    point = center_to_window_coordinates(p_point, width, hight);
    return point;
}
#endif

void read_sport_gps_points(uint16_t sport_type)
{
    // for(uint8_t i = 0; i < 4; i++)
    // {
    //         char tmptest[100];
    //         sprintf(tmptest, "i:%d,x:%lf,y:%lf\n", i, trk_max[i].x, trk_max[i].y);
    //         printf("%s\n", tmptest);
    // }
    double width = 0;
    double hight = 0;
#if defined(USING_GYRO_SENSOR) && defined(ENUM_PROJECT_NAME_N65B_GLOBAL) 
    if (trk_max[0].x < 0 && trk_max[1].x < 0)
    {
        if (trk_max[0].x < trk_max[1].x)
        {
            width = fabs(trk_max[0].x) - fabs(trk_max[1].x);
        }
        else
        {
            width = fabs(trk_max[1].x) - fabs(trk_max[0].x);
        }
    }
    else if (trk_max[0].x < 0 && trk_max[1].x >= 0)
    {
        width = fabs(trk_max[0].x) + fabs(trk_max[1].x);
    }
    else if (trk_max[0].x >= 0 && trk_max[1].x < 0)
    {
        width = fabs(trk_max[0].x) + fabs(trk_max[1].x);
    }
    else
    {
        if (trk_max[0].x < trk_max[1].x)
        {
            width = fabs(trk_max[1].x) - fabs(trk_max[0].x);
        }
        else
        {
            width = fabs(trk_max[0].x) - fabs(trk_max[1].x);
        }
    }

    if (trk_max[2].x < 0 && trk_max[3].x < 0)
    {
        if (trk_max[2].x < trk_max[3].x)
        {
            hight = fabs(trk_max[2].x) - fabs(trk_max[3].x);
        }
        else
        {
            hight = fabs(trk_max[3].x) - fabs(trk_max[2].x);
        }
    }
    else if (trk_max[2].x < 0 && trk_max[3].x >= 0)
    {
        hight = fabs(trk_max[0].x) + fabs(trk_max[1].x);
    }
    else if (trk_max[2].x >= 0 && trk_max[3].x < 0)
    {
        hight = fabs(trk_max[0].x) + fabs(trk_max[1].x);
    }
    else
    {
        if (trk_max[2].x < trk_max[3].x)
        {
            hight = fabs(trk_max[3].x) - fabs(trk_max[2].x);
        }
        else
        {
            hight = fabs(trk_max[2].x) - fabs(trk_max[3].x);
        }
    }
    char tmptest[100];
    sprintf(tmptest, "width:%lf,hight:%lf\n",width,hight);
    printf("%s", tmptest);
#endif
    sport_save_data.gps_draw_track_count = 0;
    memset(sport_save_data.gps_track, 0, sizeof(sport_save_data.gps_track)); // 清除
    if (module_ms_app_is_gps_sport_type(sport_type))
    {
        uint32_t total_gps = 0;
        total_gps = 1;// trace_gps_get_total_point_num();
        printf("gps_total_count:%d\n",total_gps);
        if (total_gps == 0)
        {
            return;
        }
        else if (total_gps > 0 && total_gps <= GPS_TRACK_LEN)
        {
            for (uint8_t i = 0; i < total_gps; i++)
            {
#if 0
                trace_gps_point_t point;
                memset(&point, 0, sizeof(point));
                uint32_t record = 0;
                record = trace_gps_read_data(&point, i, 1);
                char tmptest[100];
                memset(tmptest,0,sizeof(tmptest));
                sprintf(tmptest, "read data %d,%d,%lf, %lf", record, i, point.x, point.y);
                printf("%s\n", tmptest);
                if (record)
                {
                    lv_point_t points = zh_sport_center_to_window_coordinates(&point,width,hight);
                    sport_save_data.gps_track[sport_save_data.gps_draw_track_count].x = points.x;
                    sport_save_data.gps_track[sport_save_data.gps_draw_track_count].y = points.y;
                    sport_save_data.gps_draw_track_count++;
                }
#endif
                // 直接保存
            }
        }
        else if (total_gps > GPS_TRACK_LEN) // 抽点
        {
            uint32_t T = 1;// trace_gps_get_total_point_num();
            uint16_t M = T / GPS_TRACK_LEN;
            if (T % GPS_TRACK_LEN != 0)
            {
                M = M + 1; // 向上取整
            }
            uint16_t N = T / M;
            if (T % M != 0)
            {
                N = N + 1; // 向上取整
            }
            if (N > GPS_TRACK_LEN)
            {
                N = GPS_TRACK_LEN;
            }
            for (uint8_t i = 0; i < N; i++)
            {
#if 0
                trace_gps_point_t point;
                memset(&point, 0, sizeof(point));
                uint32_t record = 0;
                if (i == (N - 1))
                {
                    record = trace_gps_read_data(&point, trace_gps_get_total_point_num() - 1, 1);
                    printf("______________record:%d,%d\n", record, trace_gps_get_total_point_num() - 1);
                    if (record)
                    {
                        lv_point_t points = zh_sport_center_to_window_coordinates(&point,width,hight);
                        sport_save_data.gps_track[sport_save_data.gps_draw_track_count].x = points.x;
                        sport_save_data.gps_track[sport_save_data.gps_draw_track_count].y = points.y;
                        sport_save_data.gps_draw_track_count++;
                    }
                    continue;
                }
                uint16_t offset = (i * M + 1) - 1;
                record = trace_gps_read_data(&point, offset, 1);
                printf("______________record:%d,%d\n", record, offset);
                if (record)
                {
                    lv_point_t points = zh_sport_center_to_window_coordinates(&point,width,hight);
                    sport_save_data.gps_track[sport_save_data.gps_draw_track_count].x = points.x;
                    sport_save_data.gps_track[sport_save_data.gps_draw_track_count].y = points.y;
                    sport_save_data.gps_draw_track_count++;
                }
#endif
            }

        }
    }
}
void read_record_to_draw_points(uint16_t sport_type) // 抽点
{
#define TARGET_MAX 60
    //      - 以60点为目标做绘制:
    //     - 运动时长以秒为单位 T，除以 点数目标，向上取整得到抽点间隔 M
    //     - 点数数量 N = T/M (上取整)
    //     - 确保最值点被选取
    //     - 选取获取的最后一个有效数据点，确保绘图区域完整性
    //     - 选取结果为 第1秒，第1+M秒，1 + 2M，..., 1 +(N-1)M 秒，T秒，最值点
    uint32_t total_points = 0;
    uint32_t T = mul_sport_get_cur_record_item_nums();
    uint16_t M = T / TARGET_MAX;
    if (T % TARGET_MAX != 0)
    {
        M = M + 1; // 向上取整
    }
    uint16_t N = T / M;
    if (T % M != 0)
    {
        N = N + 1; // 向上取整
    }
    if (N > TARGET_MAX)
    {
        N = TARGET_MAX;
    }
    printf("read_record_to_draw_points M:%d,N:%d\n", M, N);
    switch (sport_type)
    {
                                        // 心率,pace,步频
    case SPORTING_Mountaineering_TYPE:  // 登山TODO配速转化成速度
    case SPORTING_Off_road_TYPE:        // 越野
    case SPORTING_Outdoor_hiking_TYPE:
    {
        for (uint8_t i = 0; i < N; i++)
        {
            ms_record_item_t item;
            memset(&item, 0, sizeof(item));
            uint32_t record = 0;
            if (i == (N - 1))
            {
                record = mul_sport_get_cur_record_nitem(&item, mul_sport_get_cur_record_item_nums() - 1, 1);
                printf("______________record:%d,%d\n", record, mul_sport_get_cur_record_item_nums() - 1);
                if (record)
                {
                    sport_save_data.sport_heart_chart[i].v.value = item.out_run_c.hr;
                    sport_save_data.sport_steps_frequency_chart[i].v.value = item.out_run_c.cadence;
                    //pace to speed
                    if (item.out_run_c.pace != 0)
                    {
                        sport_save_data.sport_pace_chart[i].v.value = 100 * 3600 / item.out_run_c.pace;//放大一百倍
                    }
                    else
                    {
                        sport_save_data.sport_pace_chart[i].v.value = 0;
                    }
                }
                continue;
            }
            uint16_t offset = (i * M + 1) - 1;
            record = mul_sport_get_cur_record_nitem(&item, offset, 1);
            printf("______________record:%d,%d\n", record, offset);
            if (record)
            {
                sport_save_data.sport_heart_chart[i].v.value = item.out_run_c.hr;
                sport_save_data.sport_steps_frequency_chart[i].v.value = item.out_run_c.cadence;
                //pace to speed
                if (item.out_run_c.pace != 0)
                {
                    sport_save_data.sport_pace_chart[i].v.value = 100 * 3600 / item.out_run_c.pace;
                }
                else
                {
                    sport_save_data.sport_pace_chart[i].v.value = 0;
                }
            }
        }
    }
    break;
    case SPORTING_Indoor_running_TYPE: // 心率,pace,步频
    case SPORTING_Outdoor_walking_TYPE://健走
    case SPORTING_Outdoor_running_TYPE: 
    {
        for (uint8_t i = 0; i < N; i++)
        {
            ms_record_item_t item;
            memset(&item, 0, sizeof(item));
            uint32_t record = 0;
            if (i == (N - 1))
            {
                record = mul_sport_get_cur_record_nitem(&item, mul_sport_get_cur_record_item_nums() - 1, 1);
                if (record)
                {
                    sport_save_data.sport_heart_chart[i].v.value = item.indoor_run.hr;
                    sport_save_data.sport_steps_frequency_chart[i].v.value = item.indoor_run.cadence;
                    sport_save_data.sport_pace_chart[i].v.value = item.indoor_run.pace;
                }
                continue;
            }
            uint16_t offset = (i * M + 1) - 1;
            record = mul_sport_get_cur_record_nitem(&item, offset, 1);
            if (record)
            {
                sport_save_data.sport_heart_chart[i].v.value = item.indoor_run.hr;
                sport_save_data.sport_steps_frequency_chart[i].v.value = item.indoor_run.cadence;
                sport_save_data.sport_pace_chart[i].v.value = item.indoor_run.pace;
            }
        }
    }
    break;
    case SPORTING_Outdoor_cycling_TYPE: // 心率,speed
    {
        for (uint8_t i = 0; i < N; i++)
        {
            ms_record_item_t item;
            memset(&item, 0, sizeof(item));
            uint32_t record = 0;
            if (i == (N - 1))
            {
                record = mul_sport_get_cur_record_nitem(&item, mul_sport_get_cur_record_item_nums() - 1, 1);
                if (record)
                {
                    sport_save_data.sport_heart_chart[i].v.value = item.out_non_run_c.hr;
                    sport_save_data.sport_pace_chart[i].v.value = item.out_non_run_c.speed*10;//保存的点放大十倍,还要放大十倍
                }
                continue;
            }
            uint16_t offset = (i * M + 1) - 1;
            record = mul_sport_get_cur_record_nitem(&item, offset, 1);
            if (record)
            {
                sport_save_data.sport_heart_chart[i].v.value = item.out_non_run_c.hr;
                sport_save_data.sport_pace_chart[i].v.value = item.out_non_run_c.speed*10;//保存的点放大十倍,还要放大十倍
            }
        }
    }
    break;
    case SPORTING_Skipping_rope_H_TYPE: // 心率,频率
    {
        for (uint8_t i = 0; i < N; i++)
        {
            ms_record_item_t item;
            memset(&item, 0, sizeof(item));
            uint32_t record = 0;
            if (i == (N - 1))
            {
                record = mul_sport_get_cur_record_nitem(&item, mul_sport_get_cur_record_item_nums() - 1, 1);
                if (record)
                {
                    sport_save_data.sport_heart_chart[i].v.value = item.rope_skip.hr;
                    sport_save_data.sport_steps_frequency_chart[i].v.value = item.rope_skip.action_freq;
                }
                continue;
            }
            uint16_t offset = (i * M + 1) - 1;
            record = mul_sport_get_cur_record_nitem(&item, offset, 1);
            if (record)
            {
                sport_save_data.sport_heart_chart[i].v.value = item.rope_skip.hr;
                sport_save_data.sport_steps_frequency_chart[i].v.value = item.rope_skip.action_freq;
            }
        }
    }
    break;
    case SPORTING_Elliptical_machine_TYPE: // 心率,步频
    {
        for (uint8_t i = 0; i < N; i++)
        {
            ms_record_item_t item;
            memset(&item, 0, sizeof(item));
            uint32_t record = 0;
            if (i == (N - 1))
            {
                record = mul_sport_get_cur_record_nitem(&item, mul_sport_get_cur_record_item_nums() - 1, 1);
                if (record)
                {
                    sport_save_data.sport_heart_chart[i].v.value = item.rope_skip.hr;
                    sport_save_data.sport_steps_frequency_chart[i].v.value = item.elliptical_m.cadence;
                }
                continue;
            }
            uint16_t offset = (i * M + 1) - 1;
            record = mul_sport_get_cur_record_nitem(&item, offset, 1);
            if (record)
            {
                sport_save_data.sport_heart_chart[i].v.value = item.rope_skip.hr;
                sport_save_data.sport_steps_frequency_chart[i].v.value = item.elliptical_m.cadence;
            }
        }
    }
    break;
    case SPORTING_Rowing_machine_TYPE: // 心率,划频
    {
        for (uint8_t i = 0; i < N; i++)
        {
            ms_record_item_t item;
            memset(&item, 0, sizeof(item));
            uint32_t record = 0;
            if (i == (N - 1))
            {
                record = mul_sport_get_cur_record_nitem(&item, mul_sport_get_cur_record_item_nums() - 1, 1);
                if (record)
                {
                    sport_save_data.sport_heart_chart[i].v.value = item.rope_skip.hr;
                    sport_save_data.sport_steps_frequency_chart[i].v.value = item.rowing_m.action_freq;
                }
                continue;
            }
            uint16_t offset = (i * M + 1) - 1;
            record = mul_sport_get_cur_record_nitem(&item, offset, 1);
            if (record)
            {
                sport_save_data.sport_heart_chart[i].v.value = item.rope_skip.hr;
                sport_save_data.sport_steps_frequency_chart[i].v.value = item.rowing_m.action_freq;
            }
        }
    }
    break;
    case SPORTING_swim_indoor_TYPE:  // 泳池游泳
    case SPORTING_swim_outdoor_TYPE: // 开放水域游泳:
    {
        if (T < TARGET_MAX)
        {
            for (uint8_t i = 0; i < T; i++)
            {
                ms_record_item_t item;
                memset(&item, 0, sizeof(item));
                uint32_t record = 0;
                // if (i == (T - 1))
                // {
                //     record = mul_sport_get_cur_record_nitem(&item, mul_sport_get_cur_record_item_nums() - 1, 1);
                //     if (record)
                //     {
                //         sport_save_data.sport_heart_chart[i].v.value = item.rope_skip.hr;
                //         sport_save_data.sport_steps_frequency_chart[i].v.value = item.rowing_m.action_freq;
                //     }
                //     continue;
                // }
                uint16_t offset = i;
                record = mul_sport_get_cur_record_nitem(&item, offset, 1);
                if (record)
                {
#if defined(USING_GYRO_SENSOR) && defined(ENUM_PROJECT_NAME_N65B_GLOBAL)
                    sw_record_t *sw_record = zh_app_sport_swim_list_read(i);
                    if (sw_record != NULL)
                    {
                        sport_save_data.sport_pace_chart[i].v.offset = sw_record->duration_s;
                        sport_save_data.sport_steps_frequency_chart[i].v.offset = sw_record->duration_s;
                        sport_save_data.sport_heart_chart[i].v.offset = sw_record->duration_s;
                    }
                    sport_save_data.sport_pace_chart[i].v.value = item.swimming.pace;
                    sport_save_data.sport_steps_frequency_chart[i].v.value = item.swimming.pull_rate;
                    sport_save_data.sport_heart_chart[i].v.value = item.swimming.swolf; // 心率代替swolf
                    printf("pace:%d,pull_rate:%d,swolf:%d\n", item.swimming.pace, item.swimming.pull_rate, item.swimming.swolf);
                    printf("sport_pace_chart:%d,%d,pull_rate:%d,%d,swolf:%d,%d\n",
                               sport_save_data.sport_pace_chart[i].v.value,
                               sport_save_data.sport_pace_chart[i].v.offset,
                               sport_save_data.sport_steps_frequency_chart[i].v.value,
                               sport_save_data.sport_steps_frequency_chart[i].v.offset,
                               sport_save_data.sport_heart_chart[i].v.value,
                               sport_save_data.sport_heart_chart[i].v.offset);
#endif
                }
            }
            sport_save_data.sport_pace_chart_count = T;
            sport_save_data.sport_heart_chart_count = T;
            sport_save_data.sport_steps_frequency_chart_count = T;
        }
        else // 抽点游泳
        {
            for (uint8_t i = 0; i < N; i++)
            {
                ms_record_item_t item;
                memset(&item, 0, sizeof(item));
                uint32_t record = 0;
                if (i == (N - 1))
                {
                    record = mul_sport_get_cur_record_nitem(&item, mul_sport_get_cur_record_item_nums() - 1, 1);
                    if (record)
                    {
#if defined(USING_GYRO_SENSOR) && defined(ENUM_PROJECT_NAME_N65B_GLOBAL)
                    sw_record_t *sw_record = zh_app_sport_swim_list_read(mul_sport_get_cur_record_item_nums() - 1);
                    if (sw_record != NULL)
                    {
                        sport_save_data.sport_pace_chart[i].v.offset = sw_record->duration_s;
                        sport_save_data.sport_steps_frequency_chart[i].v.offset = sw_record->duration_s;
                        sport_save_data.sport_heart_chart[i].v.offset = sw_record->duration_s;
                    }
                    sport_save_data.sport_pace_chart[i].v.value = item.swimming.pace;
                    sport_save_data.sport_steps_frequency_chart[i].v.value = item.swimming.pull_rate;
                    sport_save_data.sport_heart_chart[i].v.value = item.swimming.swolf; // 心率代替swolf
                    printf("pace:%d,pull_rate:%d,swolf:%d\n", item.swimming.pace, item.swimming.pull_rate, item.swimming.swolf);
                    printf("sport_pace_chart:%d,%d,pull_rate:%d,%d,swolf:%d,%d\n",
                               sport_save_data.sport_pace_chart[i].v.value,
                               sport_save_data.sport_pace_chart[i].v.offset,
                               sport_save_data.sport_steps_frequency_chart[i].v.value,
                               sport_save_data.sport_steps_frequency_chart[i].v.offset,
                               sport_save_data.sport_heart_chart[i].v.value,
                               sport_save_data.sport_heart_chart[i].v.offset);
#endif
                    }
                    continue;
                }
                uint16_t offset = (i * M + 1) - 1;
                record = mul_sport_get_cur_record_nitem(&item, offset, 1);
                if (record)
                {
#if defined(USING_GYRO_SENSOR) && defined(ENUM_PROJECT_NAME_N65B_GLOBAL)
                    sw_record_t *sw_record = zh_app_sport_swim_list_read(offset);
                    if (sw_record != NULL)
                    {
                        sport_save_data.sport_pace_chart[i].v.offset = sw_record->duration_s;
                        sport_save_data.sport_steps_frequency_chart[i].v.offset = sw_record->duration_s;
                        sport_save_data.sport_heart_chart[i].v.offset = sw_record->duration_s;
                    }
                    sport_save_data.sport_pace_chart[i].v.value = item.swimming.pace;
                    sport_save_data.sport_steps_frequency_chart[i].v.value = item.swimming.pull_rate;
                    sport_save_data.sport_heart_chart[i].v.value = item.swimming.swolf; // 心率代替swolf
                    printf("pace:%d,pull_rate:%d,swolf:%d\n", item.swimming.pace, item.swimming.pull_rate, item.swimming.swolf);
                    printf("sport_pace_chart:%d,%d,pull_rate:%d,%d,swolf:%d,%d\n",
                               sport_save_data.sport_pace_chart[i].v.value,
                               sport_save_data.sport_pace_chart[i].v.offset,
                               sport_save_data.sport_steps_frequency_chart[i].v.value,
                               sport_save_data.sport_steps_frequency_chart[i].v.offset,
                               sport_save_data.sport_heart_chart[i].v.value,
                               sport_save_data.sport_heart_chart[i].v.offset);
#endif
                }
            }
            sport_save_data.sport_pace_chart_count = N;
            sport_save_data.sport_heart_chart_count = N;
            sport_save_data.sport_steps_frequency_chart_count = N;
        }
    }
    break;
    default: // 心率
    {
        for (uint8_t i = 0; i < N; i++)
        {
            ms_record_item_t item;
            memset(&item, 0, sizeof(item));
            uint32_t record = 0;
            if (i == (N - 1))
            {
                record = mul_sport_get_cur_record_nitem(&item, mul_sport_get_cur_record_item_nums() - 1, 1);
                if (record)
                {
                    sport_save_data.sport_heart_chart[i].v.value = item.free_sport.hr;
                }
                continue;
            }
            uint16_t offset = (i * M + 1) - 1;
            record = mul_sport_get_cur_record_nitem(&item, offset, 1);
            if (record)
            {
                sport_save_data.sport_heart_chart[i].v.value = item.free_sport.hr;
            }
        }
    }
    break;
    }
    if (sport_type != SPORTING_swim_indoor_TYPE && sport_type != SPORTING_swim_outdoor_TYPE)
    {
        sport_save_data.sport_pace_chart_count = N;
        sport_save_data.sport_heart_chart_count = N;
        sport_save_data.sport_steps_frequency_chart_count = N;
    }

    // 补点
    record_supplementary_point(Get_current_sporting_type());
    for (uint8_t i = 0; i <  sport_save_data.sport_pace_chart_count; i++)
    {
        printf("i:%d,hr:%d,pace:%d,cadence:%d\n",i, sport_save_data.sport_heart_chart[i].v.value, sport_save_data.sport_pace_chart[i].v.value, sport_save_data.sport_steps_frequency_chart[i].v.value);
    }
#if MI_GPS_DRAW
    extern void mi_gps_to_draw_point(void);
    mi_gps_to_draw_point();
#endif
    //read_sport_gps_points(sport_type);//抽取GPS点
    for(uint16_t i = 0; i < sport_save_data.gps_draw_track_count; i++)
    {
        printf("gps_draw_tack_x:%d,y:%d,i:%d\n",sport_save_data.gps_track[i].x,sport_save_data.gps_track[i].y,i);
    }
#if defined(USING_GYRO_SENSOR) && defined(ENUM_PROJECT_NAME_N65B_GLOBAL)

    printList(p_swim_list);
    zh_app_sport_swim_list_delete();

#endif
    misc_sport_data.draw_points_complete = true;
}
// 保存运动数据到外部flash
void Save_Sport_data_to_exflash(uint8_t sport_type)
{
    printf("staert:recod_num:%d\n",sport_save_data_record_num);
#if 1
    if (!misc_sport_data.Sport_save_data_flag)
    {
        misc_sport_data.Sport_save_data_flag = true;
        // 运动记录
        uint8_t use_id = 0;
        uint8_t j = 0;
        bool sport_save_data_record_flat = false;
        sport_save_data_record_num = 0;
        for (j = 0; j < MAX_SPORT_RECORD_NUM; j++)
        {
            sport_save_data_record_table[j] += 1;
            printf("sport_save_data_record_table:J:%d\n",sport_save_data_record_table[j]);
            if (sport_save_data_record_table[j] >= MAX_SPORT_RECORD_NUM)
            {
                if (sport_save_data_record_flat == false)
                {
                    sport_save_data_record_num++;
                    sport_save_data_record_table[j] = 0;
                    use_id = j;
                    sport_save_data_record_flat = true;
                }
            }
            else
            {
                sport_save_data_record_num++;
            }
        }
        printf("save_satrt:record_num:%d\n",sport_save_data_record_num);
        SPORT_save_data_t *sport_save_data_record = (SPORT_save_data_t *)malloc(sizeof(SPORT_save_data_t));
#if 0        

        /***************************************************************************************************/
        //�������˶���¼����
        if (sport_type == TASK_SPORT_OUTDOOR_RUNNING)
        {
            week_data_record.outdoor_Running_Distance += (uint32_t)sport_save_data.sport_distance;
        }
        else if (sport_type == TASK_SPORT_INDOOR_RUNNING)
        {
            week_data_record.indoor_Running_Distance += (uint32_t)sport_save_data.sport_distance;
        }
        else if (sport_type == TASK_SPORT_OUTDOOR_RIDING)
        {
            week_data_record.outdoor_Riding_Distance += (uint32_t)sport_save_data.sport_distance;
        }
        else if (sport_type == TASK_SPORT_INDOOR_RIDING)
        {
            week_data_record.indoor_Riding_Time += sport_save_data.sport_time_count;
        }
        else if (sport_type == TASK_SPOfree_TEAINING)
        {
            week_data_record.free_training_Time += sport_save_data.sport_time_count;
        }
        else if (sport_type == TASK_SPORT_OUTDOOR_WALKING)
        {
            week_data_record.outdoor_Walking_Distance += (uint32_t)sport_save_data.sport_distance;
        }
        else if(sport_type == TASK_SPORT_SWIMMING)
        {
            week_data_record.outdoor_Swimming_Time += sport_save_data.sport_time_count;
            //同�?�游泳数�??进入sport_save_data_record�??
            cpy_swimmingdata_to_sport_save_data();
        }
#endif
        if (sport_save_data_record)
        {
            memcpy(&sport_save_data_record->sport_save_data_record_t, &sport_save_data, sizeof(sport_save_data));
            sport_save_data_record->sport_save_data_record_types = sport_type;
            sport_save_data_record->sport_save_data_sub_type = Get_current_sporting_subtype();
            sport_save_data_record->sport_save_uploat_flag = false;
            if(Get_current_sporting_subtype())
            {
                sport_save_data_record->sport_save_data_record_t.sport_seeting_choose_target = 0;
            }
             printf("set_sport_type:%d\n",sport_save_data_record->sport_save_data_record_types);
            set_sport_record_data(sport_save_data_record, use_id);
            //   save_user_information_data_init();
            //  today_daily_temp_data_save();
            //  save_sport_information_data_init();todo:by ly
            printf("%s %d,%d,%d,%d\n",__func__,use_id,sport_save_data_record->sport_save_data_record_types,sport_save_data_record->sport_save_data_record_t.gps_draw_track_count,sport_save_data_record->sport_save_data_record_t.len);

            free(sport_save_data_record);
            get_sport_record_data(&sport_save_sport_record_data, use_id);
         printf("get_sport_record_data1 %d,%d,%d,%d,%d,%d,%d\n",use_id,
         sport_save_sport_record_data.sport_save_data_record_types,
         sport_save_sport_record_data.sport_save_data_record_t.sport_max_swolf,
         sport_save_sport_record_data.sport_save_data_record_t.sport_min_swolf,
         sport_save_sport_record_data.sport_save_data_record_t.sport_pace_chart_count,
          sport_save_sport_record_data.sport_save_data_record_t.sport_heart_chart_count,
           sport_save_sport_record_data.sport_save_data_record_t.sport_steps_frequency_chart_count);
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
         Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "save_type:%d start:%d time_count:%d cal:%lf dist:%d cnt:%d,chs:0x%x",
                                     sport_save_sport_record_data.sport_save_data_record_types,
                                     (sport_save_sport_record_data.sport_save_data_record_t.sport_time_start - mul_sport_get_time_zone_offset(sport_save_sport_record_data.sport_save_data_record_t.sport_time_zone)),
                                     sport_save_sport_record_data.sport_save_data_record_t.sport_time_count,
                                     sport_save_sport_record_data.sport_save_data_record_t.sport_consume,
                                     sport_save_sport_record_data.sport_save_data_record_t.sport_distance,
                                     sport_save_sport_record_data.sport_save_data_record_t.sport_rm_count,
                                     sport_save_sport_record_data.sport_save_data_record_t.sport_seeting_choose_target);
#endif
        }
    }

#endif
}
