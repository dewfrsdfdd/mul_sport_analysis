

#if 1
#include "mul_sport_common.h"

#if 1///FLASH_MANAGER_SWITCH

#include "mul_sport_platform.h"
#include "mul_sport_factory.h"
#include "ms_gps_sport.h"
#include "ms_sport_category_t1.h"
#include "ms_sport_category_t2.h"
#include "ms_sport_category_t3.h"
#include "ms_sport_category_t4.h"
#include "ms_sport_category_t5.h"
#include "ms_sport_category_t6.h"
#include "ms_sport_category_t7.h"
#include "ms_sport_category_t8.h"
#include "ms_sport_category_t9.h"
#include "ms_sport_category_t10.h"
#include "mul_sport_ops.h"
#if (dg_configUSE_APP_PROTOCOL)
#if K_APP_PROTOCOL_TYPE == 1
/* porting start */
#include "pb_main.h"
#endif
#endif


#define FLASH_SPORT_POINT_DATA_PART SPORT_DATA_START_ADDRESS

#define MS_SPORT_TYPE_TABLE(prefix)                                                         \
    prefix(SPORTING_Outdoor_running_TYPE, ST_OUTSIDE_RUN),                                  \
        prefix(SPORTING_Outdoor_walking_TYPE, ST_OUTSIDE_MOVE),                             \
        prefix(SPORTING_free_activity_TYPE, ST_FREE_SPORT),                                 \
        prefix(SPORTING_Outdoor_hiking_TYPE, ST_OUTSIDE_HIKING),                            \
        prefix(SPORTING_Outdoor_cycling_TYPE, ST_OUTSIDE_CYCLE),                            \
        prefix(SPORTING_Indoor_running_TYPE, ST_INDOOR_RUN),                                \
        prefix(SPORTING_Skipping_rope_H_TYPE, ST_ROPE_SKIPPING),                            \
        prefix(SPORTING_Mountaineering_TYPE, ST_CLIMB),                                     \
        prefix(SPORTING_Off_road_TYPE, ST_CROSS_COUNTRY),                                   \
        prefix(SPORTING_rock_climbing_TYPE, ST_ROCK_CLIMBING),                              \
        prefix(SPORTING_skateboard_TYPE, ST_SKATEBOARDING),                                 \
        prefix(SPORTING_Roller_skating_TYPE, ST_ROLLER_SKATING),                            \
        prefix(SPORTING_Parkour_TYPE, ST_PARKOUR),                                          \
        prefix(SPORTING_ATV_TYPE, ST_ATV),                                                  \
        prefix(SPORTING_Paraglider_TYPE, ST_PARAGLIDER),                                    \
        prefix(SPORTING_High_intensity_interval_training_TYPE, ST_HIGH_INTENSITY_TRAINING), \
        prefix(SPORTING_Yoga_TYPE, ST_YOGA),                                                \
        prefix(SPORTING_Indoor_cycling_TYPE, ST_INDOOR_CYCLE),                              \
        prefix(SPORTING_Elliptical_machine_TYPE, ST_ELLIPTICAL_MACHINE),                    \
        prefix(SPORTING_Rowing_machine_TYPE, ST_ROWING_MACHINE),                            \
        prefix(SPORTING_Climbing_machine_TYPE, ST_CLIMBING_MACHINE),                        \
        prefix(SPORTING_Stepper_TYPE, ST_STEPPER),                                          \
        prefix(SPORTING_Core_training_TYPE, ST_CORE_TRAINING),                              \
        prefix(SPORTING_Flexibility_training_TYPE, ST_FLEXIBILITY_TRAINING),                \
        prefix(SPORTING_Pilates_TYPE, ST_PILATES),                                          \
        prefix(SPORTING_gymnastics_TYPE, ST_GYMNASTICS),                                    \
        prefix(SPORTING_Stretch_TYPE, ST_STRETCHING),                                       \
        prefix(SPORTING_Strength_Training_TYPE, ST_STRENGTH_TRAINING),                      \
        prefix(SPORTING_Cross_training_CrossFit_TYPE, ST_CROSS_FIT),                        \
        prefix(SPORTING_Climb_the_stairs_TYPE, ST_CLIMB_STAIRS),                            \
        prefix(SPORTING_Aerobics_TYPE, ST_AEROBICS),                                        \
        prefix(SPORTING_Physical_Training_TYPE, ST_PHYSICAL_TRAINING),                      \
        prefix(SPORTING_Wall_ball_TYPE, ST_WALL_BALL),                                      \
        prefix(SPORTING_Dumbbell_training_TYPE, ST_DUMBBELL_TRAINING),                      \
        prefix(SPORTING_Barbell_training_TYPE, ST_BARBELL_TRAINING),                        \
        prefix(PORTING_weightlifting_TYPE, ST_WEIGHTLIFTING),                               \
        prefix(SPORTING_Deadlift_TYPE, ST_DEADLIFT),                                        \
        prefix(SPORTING_Bobby_Jump_TYPE, ST_BOBBY_JUMP),                                    \
        prefix(SPORTING_Sit_ups_TYPE, ST_SIT_UPS),                                          \
        prefix(SPORTING_Functional_training_TYPE, ST_FUNCTIONAL_TRAINING),                  \
        prefix(SPORTING_Upper_limb_training_TYPE, ST_UPPER_LIMB_TRAINING),                  \
        prefix(SPORTING_Lower_limb_training_TYPE, ST_LOWER_LIMB_TRAINING),                  \
        prefix(SPORTING_Waist_and_abdomen_training_TYPE, ST_WAIST_TRAINING),                \
        prefix(SPORTING_Back_training_TYPE, ST_BACK_TRAINING),                              \
        prefix(SPORTING_Square_dance_TYPE, ST_SQUARE_DANCE),                                \
        prefix(SPORTING_Belly_dance_TYPE, ST_BELLY_DANCE),                                  \
        prefix(SPORTING_ballet_TYPE, ST_BALLET),                                            \
        prefix(SPORTING_Street_dance_TYPE, ST_STREET_DANCE),                                \
        prefix(SPORTING_Zumba_TYPE, ST_ZUMBA),                                              \
        prefix(SPORTING_National_dance_TYPE, ST_NATIONAL_DANCE),                            \
        prefix(SPORTING_Jazz_TYPE, ST_JAZZ),                                                \
        prefix(SPORTING_Latin_Dance_TYPE, ST_LATIN_DANCE),                                  \
        prefix(SPORTING_dance_TYPE, ST_DANCE),                                              \
        prefix(SPORTING_boxing_TYPE, ST_BOXING),                                            \
        prefix(SPORTING_Wrestling_TYPE, ST_WRESTLING),                                      \
        prefix(SPORTING_Martial_arts_TYPE, ST_MARTIAL_ARTS),                                \
        prefix(SPORTING_Tai_Chi_TYPE, ST_TAICHI),                                           \
        prefix(SPORTING_Muay_Thai_TYPE, ST_MUAY_THAI),                                      \
        prefix(SPORTING_judo_TYPE, ST_JUDO),                                                \
        prefix(SPORTING_Taekwondo_TYPE, ST_TAEKWONDO),                                      \
        prefix(SPORTING_karate_TYPE, ST_KARATE),                                            \
        prefix(SPORTING_free_sparring_TYPE, ST_FREE_SPARRING),                              \
        prefix(SPORTING_fencing_movement_TYPE, ST_SWORDSMANSHIP),                           \
        prefix(SPORTING_fencing_TYPE, ST_FENCING),                                          \
        prefix(SPORTING_tennis_TYPE, ST_TENNIS),                                            \
        prefix(SPORTING_basketball_TYPE, ST_BASKETBALL),                                    \
        prefix(SPORTING_golf_TYPE, ST_GOLF),                                                \
        prefix(SPORTING_Soccer_TYPE, ST_FOOTBALL),                                          \
        prefix(SPORTING_volleyball_TYPE, ST_VOLLEYBALL),                                    \
        prefix(SPORTING_baseball_TYPE, ST_BASEBALL),                                        \
        prefix(SPORTING_softball_TYPE, ST_SOFTBALL),                                        \
        prefix(SPORTING_Rugby_TYPE, ST_RUGBY),                                              \
        prefix(SPORTING_hockey_TYPE, ST_HOCKEY),                                            \
        prefix(SPORTING_pingpong_TYPE, ST_TABLE_TENNIS),                                    \
        prefix(SPORTING_badminton_TYPE, ST_BADMINTON),                                      \
        prefix(SPORTING_cricket_TYPE, ST_CRICKET),                                          \
        prefix(SPORTING_Handball_TYPE, ST_HANDBALL),                                        \
        prefix(SPORTING_bowling_TYPE, ST_BOWLING),                                          \
        prefix(SPORTING_squash_TYPE, ST_SQUASH),                                            \
        prefix(SPORTING_billiards_TYPE, ST_BILLIARDS),                                      \
        prefix(SPORTING_Shuttlecock_TYPE, ST_SHUTTLECOCK),                                  \
        prefix(SPORTING_beach_soccer_TYPE, ST_BEACH_FOOTBALL),                              \
        prefix(SPORTING_beach_volleyball_TYPE, ST_BEACH_VOLLEYBALL),                        \
        prefix(SPORTING_Sepak_Takraw_TYPE, ST_SEPAK_TAKRAW),                                \
        prefix(SPORTING_Snowboarding_TYPE, ST_SNOWBOARDING),                                \
        prefix(SPORTING_Double_board_skiing_TYPE, ST_DOUBLE_BOARD_SKIING),                  \
        prefix(SPORTING_Outdoor_skating_TYPE, ST_OUTDOOR_SKATING),                          \
        prefix(SPORTING_Curling_TYPE, ST_CURLING),                                          \
        prefix(SPORTING_Snow_sports_TYPE, ST_SNOW_SPORTS),                                  \
        prefix(SPORTING_Snowmobile_TYPE, ST_SNOWMOBILE),                                    \
        prefix(SPORTING_puck_TYPE, ST_PUCK),                                                \
        prefix(SPORTING_Snow_car_TYPE, ST_SNOW_CAR),                                        \
        prefix(SPORTING_sled_TYPE, ST_SLED),                                                \
        prefix(SPORTING_Archery_TYPE, ST_ARCHERY),                                          \
        prefix(SPORTING_Darts_TYPE, ST_DARTS),                                              \
        prefix(SPORTING_ride_horse_TYPE, ST_HORSE_RIDING),                                  \
        prefix(SPORTING_Tug_of_war_TYPE, ST_TUG_OF_WAR),                                    \
        prefix(SPORTING_Hula_Hoop_TYPE, ST_HULA_HOOP),                                      \
        prefix(SPORTING_fly_a_kite_TYPE, ST_FLY_KITE),                                      \
        prefix(SPORTING_fishing_TYPE, ST_FISHING),                                          \
        prefix(SPORTING_Frisbee_TYPE, ST_FRISBEE),                                          \
        prefix(SPORTING_swim_indoor_TYPE, ST_SWIM_INDOOR),                                  \
        prefix(SPORTING_swim_outdoor_TYPE, ST_SWIM_OUTDOOR),                                \
        prefix(SPORTING_sailboat_TYPE, ST_SAILBOAT),                                        \
        prefix(SPORTING_paddle_board_TYPE, ST_PADDLE_BOARD),                                \
        prefix(SPORTING_water_polo_TYPE, ST_WATER_POLO),                                    \
        prefix(SPORTING_aquatic_sport_TYPE, ST_AQUATIC_SPORT),                              \
        prefix(SPORTING_surfing_TYPE, ST_SURFING),                                          \
        prefix(SPORTING_canoeing_TYPE, ST_CANOEING),                                        \
        prefix(SPORTING_kayak_rafting_TYPE, ST_KAYAK_RAFTING),                              \
        prefix(SPORTING_rowing_TYPE, ST_ROWING),                                            \
        prefix(SPORTING_motorboat_TYPE, ST_MOTORBOAT),                                      \
        prefix(SPORTING_web_swimming_TYPE, ST_WEB_SWIMMING),                                \
        prefix(SPORTING_driving_TYPE, ST_DRIVING),                                          \
        prefix(SPORTING_fancy_swimming_TYPE, ST_FANCY_SWIMMING),                            \
        prefix(SPORTING_snorkeling_TYPE, ST_SNORKELING),                                    \
        prefix(SPORTING_kite_surfing_TYPE, ST_KITE_SURFING),                                \
        prefix(SPORTING_indoor_surfing_TYPE, ST_INDOOR_SURFING),                            \
        prefix(SPORTING_dragon_boat_TYPE, ST_DRAGON_BOAT),                                  \
        prefix(SPORTING_bicycle_moto_TYPE, ST_BICYCLE_MOTO),                                \
        prefix(SPORTING_heel_and_toe_TYPE, ST_HEEL_AND_TOE),                                \
        prefix(SPORTING_spinning_TYPE, ST_SPINNING),                                        \
        prefix(SPORTING_walking_machine_TYPE, ST_WALKING_MACHINE),                          \
        prefix(SPORTING_step_training_TYPE, ST_STEP_TRAINING),                              \
        prefix(SPORTING_single_bar_TYPE, ST_SINGLE_BAR),                                    \
        prefix(SPORTING_parallel_bars_TYPE, ST_PARALLEL_BARS),                              \
        prefix(SPORTING_group_callisthenics_TYPE, ST_GROUP_CALLISTHENICS),                  \
        prefix(SPORTING_strike_TYPE, ST_STRIKE),                                            \
        prefix(SPORTING_battle_rope_TYPE, ST_BATTLE_ROPE),                                  \
        prefix(SPORTING_mixed_aerobic_TYPE, ST_MIXED_AEROBIC),                              \
        prefix(SPORTING_walk_indoor_TYPE, ST_WALK_INDOOR),                                  \
        prefix(SPORTING_gym_TYPE, ST_GYM),                                                  \
        prefix(SPORTING_hip_hop_dance_TYPE, ST_HIP_HOP_DANCE),                              \
        prefix(SPORTING_pole_dance_TYPE, ST_POLE_DANCE),                                    \
        prefix(SPORTING_breakdancing_TYPE, ST_BREAKDANCING),                                \
        prefix(SPORTING_social_dancing_TYPE, ST_SOCIAL_DANCING),                            \
        prefix(SPORTING_modern_dancing_TYPE, ST_MODERN_DANCING),                            \
        prefix(SPORTING_jujitsu_TYPE, ST_JUJITSU),                                          \
        prefix(SPORTING_indoor_football_TYPE, ST_INDOOR_FOOTBALL),                          \
        prefix(SPORTING_sandbags_ball_TYPE, ST_SANDBAGS_BALL),                              \
        prefix(SPORTING_bocci_TYPE, ST_BOCCI),                                              \
        prefix(SPORTING_hihi_ball_TYPE, ST_HIHI_BALL),                                      \
        prefix(SPORTING_gateball_TYPE, ST_GATEBALL),                                        \
        prefix(SPORTING_dodgeball_TYPE, ST_DODGEBALL),                                      \
        prefix(SPORTING_cross_country_skiing_TYPE, ST_CROSS_COUNTRY_SKIING),                \
        prefix(SPORTING_indoor__skating_TYPE, ST_INDOOR__SKATING),                          \
        prefix(SPORTING_shuttlecock_kicking_TYPE, ST_SHUTTLECOCK_KICKING),                  \
        prefix(SPORTING_swing_TYPE, ST_SWING),                                              \
        prefix(SPORTING_motion_sensing_game_TYPE, ST_MOTION_SENSING_GAME),                  \
        prefix(SPORTING_foosball_TYPE, ST_FOOSBALL),                                        \
        prefix(SPORTING_shuffle_ball_TYPE, ST_SHUFFLE_BALL),                                \
        prefix(SPORTING_electronic_sports_TYPE, ST_ELECTRONIC_SPORTS),                      \
        prefix(SPORTING_chess_TYPE, ST_CHESS),                                              \
        prefix(SPORTING_draughts_TYPE, ST_DRAUGHTS),                                        \
        prefix(SPORTING_weiqi_TYPE, ST_WEIQI),                                              \
        prefix(SPORTING_bridge_TYPE, ST_BRIDGE),                                            \
        prefix(SPORTING_board_games_TYPE, ST_BOARD_GAMES),                                  \
        prefix(SPORTING_equesttrian_TYPE, ST_EQUESTTRIAN),                                  \
        prefix(SPORTING_track_and_field_TYPE, ST_TRACK_AND_FIELD),                          \
        prefix(SPORTING_racing_car_TYPE, ST_RACING_CAR),

  
 
uint8_t mul_sport_get_sport_Task_type(void)
{
    // return TASK_MAIN_SPORTING_MENU;
    return 0; // TODO: 需要添加接口 @sport storage
}

uint16_t Convert_Sport_Store_Type_to_Sport_Task_Type(Sport_Type_Type sport_type)
{
    const input_sport_t local_sport_type_arr[ST_SPORT_MAX] = {
        MS_SPORT_TYPE_TABLE(MS_T_CONVERT_DEF_REV)
    };

    if (sport_type >= ST_SPORT_MAX)
    {
        return SPORTING_MAX_END_TYPE;
    }

    return local_sport_type_arr[sport_type];
}


Sport_Type_Type module_ms_api_sport_type_convert_upload(Sport_type local_sport_type)
{
    const Sport_Type_Type local_sport_type_arr[SPORTING_MAX_END_TYPE] =
    {
        MS_SPORT_TYPE_TABLE(MS_T_CONVERT_DEF)
    };

    if (local_sport_type >= SPORTING_MAX_END_TYPE)
    {
        return ST_NONE;
    }
    return local_sport_type_arr[local_sport_type];
}

uint16_t This_sporting_type = 0; // 本次运动的运动类型

uint16_t Get_current_sporting_type(void)
{
    return This_sporting_type;
}
void Set_current_sproting_type(uint16_t type)
{
    This_sporting_type = type;
    misc_sport_data.sport_prepare_sent=0;
    Set_current_sproting_subtype(0);//指定课程需要再设置到其他
}
uint16_t This_sporting_subtype = 0; // 本次运动的子类型

uint16_t Get_current_sporting_subtype(void)
{
    return This_sporting_subtype;
}
void Set_current_sproting_subtype(uint16_t type)
{
    This_sporting_subtype = type;
}
bool mul_sport_get_open_gps_sport_status(void)
{
    bool ret_flag = false;
    input_sport_t input_sport_type;
    input_sport_type = Get_current_sporting_type();

    switch (input_sport_type)
    {
        case SPORTING_Outdoor_running_TYPE:
        case SPORTING_Outdoor_walking_TYPE:
        case SPORTING_Outdoor_hiking_TYPE:
        case SPORTING_Outdoor_cycling_TYPE:
        case SPORTING_Mountaineering_TYPE:
        case SPORTING_Off_road_TYPE:
            ret_flag = true;
            break;

    default:
        ret_flag = false;
        break;
    }

    return ret_flag;
}

Sport_Type_Type mul_sport_get_cur_sport_type(void)
{
    input_sport_t    input_sport_type;

    input_sport_type = mul_sport_get_input_sport_type();

    const Sport_Type_Type upload_sport_type_arr[SPORTING_MAX_END_TYPE] = {
        MS_SPORT_TYPE_TABLE(MS_T_CONVERT_DEF)
    };

    if (input_sport_type >= SPORTING_MAX_END_TYPE)
    {
        return ST_NONE;
    }

    return upload_sport_type_arr[input_sport_type];
}

void clear_sport_record_data(void)
{
    for (uint8_t j = 0; j < MAX_SPORT_RECORD_NUM; j++)
    {
            sport_save_data_record_table[j] = 0xAA;
    }
}

uint8_t Comparison_sport_record_display_table(uint8_t data)
{
    for (uint8_t j = 0; j < MAX_SPORT_RECORD_NUM; j++)
    {
            if (sport_save_data_record_table[j] == data)
            {
                    return j;
            }
    }
    return 0;
}

/* porting end */

utc_time_t mul_sport_get_timestamp(void)
{
    /* 获取时间戳 */
    mul_sport_time_union_t time_s;
    uint32_t timestamp = 0;
    int8_t time_zone = 0;
#if 0
    UTCTimeStruct *tm = get_wall_clock_time();

    time_s.time.year = tm->year - 1970;
    time_s.time.month = tm->month;
    time_s.time.day = tm->day;
    time_s.time.hours = tm->hour;
    time_s.time.minute = tm->minutes;
    time_s.time.seconds = tm->seconds;

    timestamp = mul_sport_convert_time_to_sec(time_s);
    time_zone = mul_sport_get_time_zone();

    timestamp -= (int32_t)time_zone * 15 * 60;

    return timestamp;
#endif 
    return 0;
}

int8_t mul_sport_get_time_zone(void)
{
    /* 获取时区 */
    return 0;// get_time_zone();
}

uint32_t mul_sport_get_rand(void)
{
    /* 获取随机种子 */

    return 0;// (uint32_t)get_wall_clock_time_counter();
}

bool mul_sport_write_info_data(uint8_t *p_data, uint32_t addr, uint16_t data_len)
{
    bool write_ret_flag;

    write_ret_flag = true;

  //  vital_info_flash_write(FLASH_SPORT_POINT_DATA_PART, addr, p_data, data_len);

    return write_ret_flag;
}

bool mul_sport_read_info_data(uint8_t *p_data, uint32_t addr, uint16_t data_len)
{
    bool read_ret_flag;

    read_ret_flag = true;

 //   vital_info_flash_read(FLASH_SPORT_POINT_DATA_PART, addr, p_data, data_len);

    return read_ret_flag;
}

bool mul_sport_erase_sector(uint32_t sector_addr)
{
    bool erase_ret_flag;

    erase_ret_flag = false;

   // vital_info_flash_erase(FLASH_SPORT_POINT_DATA_PART, sector_addr, FLASH_MANAGER_SECTOR_SIZE);

    return erase_ret_flag;
}

/* 多运动 */
//

uint32_t mul_sport_get_sport_time_start(void)
{
    /* 运动开始时间 */
    return sport_save_data.sport_time_start;
}

uint32_t mul_sport_get_sport_time_count(void)
{
    /* 运动用时 */
    return sport_save_data.sport_time_count;
}

uint32_t mul_sport_get_sport_distance(void)
{
    /* 运动距离 */
    return sport_save_data.sport_distance;
}

uint32_t mul_sport_get_sport_fixed_distance(void)
{
    return misc_sport_data.cal_distance;
}
uint16_t mul_sport_get_sport_speed_distribution(void)
{
    /* 运动配速 */
    return sport_save_data.sport_Speed_distribution;
}

uint16_t mul_sport_get_sport_avg_speed_distribution(void)
{
    /* 平均配速 */
    /* do nothing */
    return sport_save_data.sport_avg_Speed_distribution;
}

uint32_t mul_sport_get_sport_maximum_speed_distribution(void)
{
    /* 最大配速 */
    if (sport_save_data.sport_Speed_distribution_max > 60 * 99)
    {
        return 0;
    }
    else
    {
        return sport_save_data.sport_Speed_distribution_max;
    }
}

uint32_t mul_sport_get_sport_minimum_speed_distribution(void)
{
    /* 最小配速 */
    if (sport_save_data.sport_Speed_distribution_min > 60 * 99)
    {
        return 0;
    }
    else
    {
        return sport_save_data.sport_Speed_distribution_min;
    }
}

uint8_t mul_sport_get_sport_heart_rate(void)
{
    /* 心率 */
    return sport_save_data.sport_heart_rate;
}

uint16_t mul_sport_get_sport_rm_frequency(void)
{
    /* 划船机椭圆机跳绳频率 */
    return (uint16_t)sport_save_data.sport_rm_frequency;
}

uint16_t mul_sport_get_sport_step_frequency(void)
{
    /* 步频 */
    /* do noting */
    return sport_save_data.sport_Step_frequency;
}

uint16_t mul_sport_get_sport_maximum_step_frequency(void)
{
    /* 最大步频 */
    return sport_save_data.sport_Maximum_Step_frequency;
}

uint16_t mul_sport_get_sport_avg_step_frequency(void)
{
    /* 平均步频 */
    /* do nothing */
    return sport_save_data.sport_ave_Step_frequency;
}

uint32_t mul_sport_get_sport_speed(void)
{
    /* 速度 */
    return sport_save_data.sport_Speed/10;
}

uint32_t mul_sport_get_sport_step_num(void)
{
    /* 步数 */
    return sport_save_data.sport_Step_number;
}

float mul_sport_get_sport_consume(void)
{
    /* 卡路里消耗 */
    return sport_save_data.sport_consume;
}

uint16_t mul_sport_get_sport_total_consume(void)
{
    /* 总卡路里消耗 */
    return (uint16_t)misc_sport_data.total_consume;
}

uint16_t mul_sport_get_sport_avg_stride(void)
{
    /* 平均步幅 */
    return (uint16_t)sport_save_data.sport_avg_step_length;
}

uint8_t mul_sport_get_sport_extra_stride(void)
{
    /* 步幅 */
    uint32_t extra_stride = 0;

    extra_stride = (uint32_t)(sport_save_data.sport_step_length  * 100);

    if (extra_stride > 255)
    {
        extra_stride = 255;
    }

    return (uint8_t)extra_stride;
}

float mul_sport_get_sport_restart_altitude(void)
{
    /* TODO: porting */
    /* 暂停后, 再恢复运动时需要获取的海拔 */

    return 0.0; //((float)Get_Altitude_Value()) / 10.0;
}

float mul_sport_get_sport_basic_altitude(void)
{
    /* TODO: porting */
    /* 获取运动刚开始时的初始海拔 */

    return 0.0; //(float)((float)sport_save_data.sport_basic_altitude);
}
uint8_t mul_sport_get_sport_altitude_change_type(void)
{
    /* TODO: porting */
    /* 海拔变化类型 0 -> 下降; 1 -> 上升 */

    return 0;
    //    if(Get_Sport_altitude_up_donw())
    //    {
    //       return 1;
    //    }
    //    else
    //    {
    //       return 0;
    //    }
}

uint8_t mul_sport_get_sport_altitude_change_val(void)
{
    /* TODO: porting */
    /* 海拔变化大小 0 -> 下降; 1 -> 上升*/

    return 0;
    //    if(Get_Sport_altitude_up_donw())
    //    {
    //        return (uint8_t)(Get_Sport_altitude_add_data()*10);
    //    }
    //    else
    //    {
    //        return (uint8_t)(Get_Sport_altitude_reduce_data()*10);
    //    }
}

float mul_sport_get_total_up(void)
{
    /* TODO: porting */
    /* 累计上升 */

    return 0.0; //(float)(sport_save_data.sport_relative_up_altitude*1.0);
}

float mul_sport_get_total_down(void)
{
    /* TODO: porting */
    /* 累计下降 */

    return 0.0; //(float)(sport_save_data.sport_relative_down_altitude*1.0);
}

float mul_sport_get_avg_height(void)
{
    /* TODO: porting */
    /* 平均高度 */
    return 0.0; // return (float)(sport_save_data.sport_avg_high*1.0);
}

float mul_sport_get_max_height(void)
{
    /* TODO: porting */
    /* 最大高度 */

    return 0.0; // return (float)(sport_save_data.sport_max_high*1.0);
}

float mul_sport_get_min_height(void)
{
    /* TODO: porting */
    /* 最小高度 */

    return 0.0; // return (float)(sport_save_data.sport_min_high*1.0);
}

float mul_sport_get_sport_avg_speed(void)
{

    /* 平均速度 */
    /* do nothing */
    return (float)sport_save_data.sport_average_velocity/100.0;
}

uint32_t mul_sport_get_sport_last_km_avg_speed(void)
{
    /* 上公里速度 */
    /* do nothing */
    return sport_save_data.sport_onekilometre_average_velocity;
}

float mul_sport_get_sport_limit_speed(void)
{
    /* 最快速度 */
    /* 返回的最快速度的单位为: km/h */

    return (float)sport_save_data.sport_Limit_speed/100.0;
}

uint8_t mul_sport_get_sport_avg_heart_rate(void)
{
    /* 平均心率 */
    return sport_save_data.sport_Mean_heart_rate;
}

uint8_t mul_sport_get_sport_maximum_heart_rate(void)
{

    /* 最大心率 */
    return sport_save_data.sport_Maximum_heart_rate;
}

uint8_t mul_sport_get_sport_minimum_heart_rate(void)
{

    /* 最小心率 */
    return sport_save_data.sport_Miximum_heart_rate;
}

uint32_t mul_sport_get_sport_heart_rate_limit_time(void)
{

    /* 极限时长 */
    return sport_save_data.sport_heart_rate_count_1;
}

uint32_t mul_sport_get_sport_heart_rate_without_oxygen_time(void)
{
    /* 无氧耐力时长(anaerobic endurance) */
    return sport_save_data.sport_heart_rate_count_2;
}

uint32_t mul_sport_get_sport_heart_rate_with_oxygen_time(void)
{
    /* 有氧耐力时长(aerobic endurance) */
    return sport_save_data.sport_heart_rate_count_3;
}

uint32_t mul_sport_get_sport_heart_rate_fat_burning_time(void)
{
    /* 燃脂时长 */
    return sport_save_data.sport_heart_rate_count_4;
}

uint32_t mul_sport_get_sport_heart_rate_warming_up_time(void)
{
    /* 热身时长 */
    return sport_save_data.sport_heart_rate_count_5;
}
uint8_t mul_sport_get_sport_genki_value(void)
{
    /* 元气值 */
    return (uint8_t)sport_save_data.sport_genki_value;
}
input_sport_t mul_sport_get_input_sport_type(void)
{
    /* 获取当前运动的类型 */
    return Get_current_sporting_type();
}

uint32_t mul_sport_get_swimming_turn_cnt(void)
{
    /* 游泳趟数(包括小节和段落) */
    return misc_sport_data.swim_count;
}

uint32_t mul_sport_get_swimming_subsection(void)
{
    /* 游泳小节个数 */
    return misc_sport_data.swim_data.sub_section_count;
}

uint32_t mul_sport_get_cyclic_sport_counter(void)
{
    /* cyclic 总计数 */
    return  sport_save_data.sport_rm_count;
}

uint32_t mul_sport_get_max_cyclic_sport_counter(void)
{
    return sport_save_data.sport_max_freq;
}

uint32_t mul_sport_get_avg_cyclic_sport_counter(void)
{
    return sport_save_data.sport_avg_freq;
}

uint32_t mul_sport_get_target_duration(void)
{
    uint32_t target_duration = 0;

    if (sport_setting_target_data[Get_current_sporting_type()].sport_seeting_choose_target& (1<<SPORT_SEETING_TIME))
    {
        target_duration = sport_setting_target_data[Get_current_sporting_type()].sport_seeting_time_data * 60;
    }

    return target_duration;
}

uint16_t mul_sport_get_target_calorie(void)
{
    uint16_t target_calorie = 0;

    if (sport_setting_target_data[Get_current_sporting_type()].sport_seeting_choose_target& (1<<SPORT_SEETING_CONSUME))
    {
        target_calorie = sport_setting_target_data[Get_current_sporting_type()].sport_seeting_consume_data;
    }

    return target_calorie;
}

uint32_t mul_sport_get_target_distance(void)
{
    uint32_t target_distance = 0;

    if (sport_setting_target_data[Get_current_sporting_type()].sport_seeting_choose_target& (1<<SPORT_SEETING_DISTANCE))
    {
        target_distance = sport_setting_target_data[Get_current_sporting_type()].sport_seeting_distance_data;
    }

    return target_distance;
}

uint16_t mul_sport_get_target_times(void)
{
    uint16_t target_times = 0;

    if (sport_setting_target_data[Get_current_sporting_type()].sport_seeting_choose_target& (1<<SPORT_SEETING_COUNT))
    {
        target_times = sport_setting_target_data[Get_current_sporting_type()].sport_seeting_count_data;
    }

    return target_times;
}

uint16_t mul_sport_get_target_cadence(void)
{
    uint16_t target_cadence = 0;


    if (sport_setting_target_data[Get_current_sporting_type()].sport_seeting_choose_target& (1<<SPORT_SEETING_STEPFREQ))
    {
        target_cadence = sport_setting_target_data[Get_current_sporting_type()].sport_seeting_step_freq;
    }

    return target_cadence;
}

uint32_t mul_sport_get_target_pace(void)
{
    uint32_t target_pace = 0;

    if (sport_setting_target_data[Get_current_sporting_type()].sport_seeting_choose_target& (1<<SPORT_SEETING_PACE_REMIND))
    {
            target_pace = sport_setting_target_data[Get_current_sporting_type()].sport_seeting_step_freq;
    }

    return target_pace;
}

bool mul_sport_report_ver_special_handler(Sport_Type_Type sport_type, uint8_t *p_report_ver)
{
    bool is_handle = false;

    switch (sport_type)
    {
    case ST_OUTSIDE_HIKING:
        if (*p_report_ver == 0x04)
        {
            *p_report_ver = 0x03;
        }
        is_handle = true;
        break;

    default:
        break;
    }

    return is_handle;
}
void mul_sport_space_is_not_enouth_cb(void)
{
    /* TODO: porting */
    /* 空间不足的回调函数  */

    return;
}

/**
 * @Function name: mul_sport_space_is_exhausted_cb
 * @Descripttion: 运动过程中空间已经用尽回调函数
 * @param {type}
 * @return:
 * @LastEditTime: Do not Edit
 */
void mul_sport_space_is_exhausted_cb(void)
{
#if 1 // TODO: wdh, ly
    //息屏状态下亮屏动作
#if 0
     sport_state_act = 49;
    module_ms_app_sport_set_points_flag(SPORT_POINTS_STOP);
    //sport_stop();
    sport_stop_when_full();
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
    zh_miwear_sport_request(SportState_SPORT_STOP, pb_sport_type_trans(Get_current_sporting_type()));
    if(get_vibration_adjustment_status())
        Set_Moto_Times_Frequence(NOW_VIBRATION_MODE_3,2);
#endif
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
    Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "no memory:%d", SPORT_POINTS_STOP);
#endif
    Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_NOT_ENOUGH_STORAGE_STRING_ID, NULL);
    if (Get_sport_save_status())
    {
        misc_sport_data.sporting_to_sport_record_flag = true;
        misc_sport_data.sport_loading_count = LOAD_TIME_OUT;
        Jump_App_And_Page(APP_SPORT_RECORD_MAIN_STRING_ID, APP_SPORT_LOADING_STRING_ID); // load
    }
    else
    {
        extern void app_sport_jump_to_list(void);
        app_sport_jump_to_list();
    }
#endif
    return;
#endif
}

bool mul_sport_delete_sport_file_succeed_cb(data_id_t sport_id, uint32_t args)
{
#if 1
  //  uint8_t checknum = 0;
    uint8_t sport_store_num = 0;
    Sport_Type_Type sport_type = (Sport_Type_Type)(sport_id.type_desc.specific_type);
    Sport_Type_Type sub_sport_type = (Sport_Type_Type)args;
    Sport_Type_Type cmp_sport_type = ST_NONE;

    /* 如果是自由训练或者户外跑步类则需要用到子类型运动 */
    if (sport_type == ST_FREE_SPORT \
        || sport_type == ST_OUTSIDE_RUN_CATEGORY)
    {
        cmp_sport_type = sub_sport_type;
    }
    else
    {
        cmp_sport_type = sport_type;
    }
#if 0
    for ( uint8_t i = 0; i < 20; i++)
    {
        sport_store_num = Comparison_sport_record_display_table(i);
        SPORT_save_data_t sport_save_data_record;
        get_sport_record_data(&sport_save_data_record, sport_store_num);
        if ((sport_id.timestamp == sport_save_data_record.sport_save_data_record_t.sport_time_start) \
            && (Convert_Sport_Store_Type_to_Sport_Task_Type(cmp_sport_type) == sport_save_data_record.sport_save_data_record_types))
        {
            sport_save_data_record_table[sport_store_num] = 0xAA;
            sport_save_data_record_num = sport_save_data_record_num -1;

            return true;
        }
    }
#else
    //使用malloc方式
    SPORT_save_data_t* p_sport_save_data_record = NULL;
    p_sport_save_data_record = (SPORT_save_data_t*)malloc(sizeof(SPORT_save_data_t));
    if(p_sport_save_data_record == NULL)
    {
        printf("%s malloc_fail\n",__func__);
        return false;
    }
    for ( uint8_t i = 0; i < 20; i++)
    {
        sport_store_num = Comparison_sport_record_display_table(i);
        
        get_sport_record_data(p_sport_save_data_record, sport_store_num);
        // printf("----------sport_type:%d,num:%d,tamp:%d,%d,%d\n",p_sport_save_data_record->sport_save_data_record_types,sport_store_num,sport_id.timestamp,(p_sport_save_data_record->sport_save_data_record_t.sport_time_start - mul_sport_get_time_zone_offset(p_sport_save_data_record->sport_save_data_record_t.sport_time_zone)),
        // Convert_Sport_Store_Type_to_Sport_Task_Type(cmp_sport_type),p_sport_save_data_record->sport_save_data_record_types);
        if ((sport_id.timestamp == (p_sport_save_data_record->sport_save_data_record_t.sport_time_start - mul_sport_get_time_zone_offset(p_sport_save_data_record->sport_save_data_record_t.sport_time_zone))) \
            && (Convert_Sport_Store_Type_to_Sport_Task_Type(cmp_sport_type) == p_sport_save_data_record->sport_save_data_record_types))
        {
            sport_save_data_record_table[sport_store_num] = 0xAA;
            sport_save_data_record_num = sport_save_data_record_num -1;
            if(p_sport_save_data_record != NULL)
            {
                free(p_sport_save_data_record);
                printf("free success %d\n",__LINE__);
                p_sport_save_data_record = NULL;
            }
            return true;
        }
    }
    if(p_sport_save_data_record != NULL)
    {
        free(p_sport_save_data_record);
        printf("free success %d\n",__LINE__);
        p_sport_save_data_record = NULL;
    }
#endif
    return false;
#endif
    return true;
}

bool mul_sport_upload_sport_file_succeed_cb(data_id_t sport_id, uint32_t args)
{
#if 1
//    uint8_t checknum = 0;
    uint8_t sport_store_num = 0;
    Sport_Type_Type sport_type = (Sport_Type_Type)(sport_id.type_desc.specific_type);
    Sport_Type_Type sub_sport_type = (Sport_Type_Type)args;
    Sport_Type_Type cmp_sport_type = ST_NONE;

    /* 如果是自由训练或者户外跑步类则需要用到子类型运动 */
    if (sport_type == ST_FREE_SPORT \
        || sport_type == ST_OUTSIDE_RUN_CATEGORY)
    {
        cmp_sport_type = sub_sport_type;
    }
    else
    {
        cmp_sport_type = sport_type;
    }

    for ( uint8_t i = 0; i < MAX_SPORT_RECORD_NUM; i++)
    {
        sport_store_num = Comparison_sport_record_display_table(i);
        SPORT_save_data_t sport_save_data_record;
        get_sport_record_data(&sport_save_data_record, sport_store_num);

#if sport_log_dump
        log_printf(9, "SPORT", "sport_id.timestamp = %d  \r\nsport_time_start = %d\r\n",sport_id.timestamp,sport_save_data_record.sport_save_data_record_t.sport_time_start);
#endif
        if ((sport_id.timestamp == sport_save_data_record.sport_save_data_record_t.sport_time_start) \
        && (Convert_Sport_Store_Type_to_Sport_Task_Type(cmp_sport_type) == sport_save_data_record.sport_save_data_record_types))
        {
            sport_save_data_record.sport_save_uploat_flag = true;
            set_sport_record_data(&sport_save_data_record, sport_store_num);
#if sport_log_dump
            log_printf(9, "SPORT", "upload sports_data_success");
#endif
            return true;
        }
    }

    return false;
#endif
    return true;
}
void write_sport_data_work_start(void)
{
    // todo: by wdh重写线程调度
    #if 0//!defined (BSP_USING_PC_SIMULATOR)
        uint8_t data;
        hl_if_data_t *msg = service_fill_msg(SEN_APP, SENSOR_APP_SPORT_POINT_DATA, (uint8_t *)&data, sizeof(uint8_t));
        extern void DeBug_Memory_System_Zh(uint8_t *data,uint16_t type,uint16_t len);
           DeBug_Memory_System_Zh(msg->data,msg->sub_type,msg->data_len);
        send_msg_to_preprocess_thread(msg, sizeof(msg));
    #endif
}
void sport_resume_process_work_start(void)
{
    // todo: by wdh重写线程调度
    #if 0//!defined (BSP_USING_PC_SIMULATOR)
        uint8_t data;
        hl_if_data_t *msg = service_fill_msg(SEN_APP, SENSOR_APP_SPORT_RESUME_PROCESS, (uint8_t *)&data, sizeof(uint8_t));
         extern void DeBug_Memory_System_Zh(uint8_t *data,uint16_t type,uint16_t len);
           DeBug_Memory_System_Zh(msg->data,msg->sub_type,msg->data_len);
        send_msg_to_preprocess_thread(msg, sizeof(msg));
    #endif
}
void save_cur_sport_file_work_start(void)
{
    //todo: by wdh重写线程调度
    #if 0//!defined (BSP_USING_PC_SIMULATOR)
        uint8_t data;
        hl_if_data_t *msg = service_fill_msg(SEN_APP, SENSOR_APP_SPORT_SAVE_PROCESS, (uint8_t *)&data, sizeof(uint8_t));
       
        extern void DeBug_Memory_System_Zh(uint8_t *data,uint16_t type,uint16_t len);
           DeBug_Memory_System_Zh(msg->data,msg->sub_type,msg->data_len);
        send_msg_to_preprocess_thread(msg, sizeof(msg));
    #endif
}
void save_cur_sport_file_work_start_when_full(void)
{
    //todo: by wdh重写线程调度
    #if 0//!defined (BSP_USING_PC_SIMULATOR)
        uint8_t data;
        hl_if_data_t *msg = service_fill_msg(SEN_APP, SENSOR_APP_SPORT_SAVE_FULL_PROCESS, (uint8_t *)&data, sizeof(uint8_t));
       
        extern void DeBug_Memory_System_Zh(uint8_t *data,uint16_t type,uint16_t len);
           DeBug_Memory_System_Zh(msg->data,msg->sub_type,msg->data_len);
        send_msg_to_preprocess_thread(msg, sizeof(msg));
    #endif
}
void draw_cur_sport_points_work(void)
{
    //todo: by wdh重写线程调度
    #if 0//!defined (BSP_USING_PC_SIMULATOR)
        uint8_t data;
        hl_if_data_t *msg = service_fill_msg(SEN_APP, SENSOR_APP_SPORT_DRAW_POINTS, (uint8_t *)&data, sizeof(uint8_t));
        extern void DeBug_Memory_System_Zh(uint8_t *data,uint16_t type,uint16_t len);
           DeBug_Memory_System_Zh(msg->data,msg->sub_type,msg->data_len);
        send_msg_to_preprocess_thread(msg, sizeof(msg));
    #endif
}

void mul_sport_new_iphone_work(void)
{
    //todo: by wdh重写线程调度
    #if 0//!defined (BSP_USING_PC_SIMULATOR)
        uint8_t data;
        hl_if_data_t *msg = service_fill_msg(SEN_APP, SENSOR_APP_SPORT_NEW_IPHONE, (uint8_t *)&data, sizeof(uint8_t));
        extern void DeBug_Memory_System_Zh(uint8_t *data,uint16_t type,uint16_t len);
           DeBug_Memory_System_Zh(msg->data,msg->sub_type,msg->data_len);
        send_msg_to_preprocess_thread(msg, sizeof(msg));
    #endif
}

bool mul_sport_platform_change_sit_type(SPORT_interval_training_type next_type)
{
    printf("%s %d\n",__func__,next_type);
    if (misc_sport_data.sport_is_app_sponsor == false)
    {
        Sport_Interval_Training_Type next_sit_type = SIT_NONE;

        if (next_type >= INTERVAL_TRAINING_WARM_UP && next_type <= COURSE_ACTIVITY)
        {
            next_sit_type = (Sport_Interval_Training_Type)next_type;
        }

        mul_sport_set_sport_next_sit_type(next_sit_type);
        mul_sport_set_is_change_sit_type(true);

        extern void sport_resume_process_work_start(void);
        sport_resume_process_work_start(); // XXX: 注意如果是手表可以快速点击跳过间歇训练,这里预计要改成直接调用函数,不发送work queue

        return true;
    }
    else
    {
        return false;
    }
}
Sport_Interval_Training_Type mul_sport_platform_get_sport_next_sit_type(void)
{
    return get_sport_next_sit_type();
}
bool mul_sport_platform_change_sit_type_not_resume(SPORT_interval_training_type next_type)
{
    printf("%s %d\n",__func__,next_type);
    if (misc_sport_data.sport_is_app_sponsor == false)
    {
        Sport_Interval_Training_Type next_sit_type = SIT_NONE;

        if (next_type >= INTERVAL_TRAINING_WARM_UP && next_type <= COURSE_ACTIVITY)
        {
            next_sit_type = (Sport_Interval_Training_Type)next_type;
        }

        mul_sport_set_sport_next_sit_type(next_sit_type);
        mul_sport_set_is_change_sit_type(true);

        // extern void sport_resume_process_work_start(void);
        // sport_resume_process_work_start(); // XXX: 注意如果是手表可以快速点击跳过间歇训练,这里预计要改成直接调用函数,不发送work queue

        return true;
    }
    else
    {
        return false;
    }
}

bool mul_sport_platform_get_data_header_ptr(data_id_t *p_id, uint8_t **pp_header_data, size_t *p_data_len)
{
    if (p_id->type_desc.data_type == ENUM_SPORT_GPS_DATA_T)
    {
        mul_sport_get_gps_data_header(p_id->version, pp_header_data, p_data_len);
    }
    else
    {
        switch (p_id->type_desc.specific_type)
        {
        /* t1 */
        case ST_OUTSIDE_RUN:
        case ST_OUTSIDE_MOVE:
        case ST_CLIMB:
        case ST_CROSS_COUNTRY:
            get_ms_sport_category_t1_data_header(p_id->type_desc.data_type, p_id->version, pp_header_data, p_data_len);
            break;

        /* 特殊处理-户外徒步 */
        case ST_OUTSIDE_HIKING:
        {
            uint8_t version = p_id->version;
            if (version == 0x03)
            {
                version = 0x04;
            }
            get_ms_sport_category_t1_data_header(p_id->type_desc.data_type, version, pp_header_data, p_data_len);
        }
        break;

        /* t2 */
        case ST_INDOOR_RUN:
            get_ms_sport_category_t2_data_header(p_id->type_desc.data_type, p_id->version, pp_header_data, p_data_len);
            break;

        /* t3 */
        case ST_OUTSIDE_CYCLE:
            get_ms_sport_category_t3_data_header(p_id->type_desc.data_type, p_id->version, pp_header_data, p_data_len);
            break;

        /* t4 */
        case ST_INDOOR_CYCLE:
        case ST_FREE_SPORT:
            get_ms_sport_category_t4_data_header(p_id->type_desc.data_type, p_id->version, pp_header_data, p_data_len);
            break;

        /* t5 */
        case ST_SWIM_INDOOR:
        case ST_SWIM_OUTDOOR:
            get_ms_sport_category_t5_data_header(p_id->type_desc.data_type, p_id->version, pp_header_data, p_data_len);
            break;

        /* t6 - 划船机 */
        case ST_ROWING_MACHINE:
            get_ms_sport_category_t6_data_header(p_id->type_desc.data_type, p_id->version, pp_header_data, p_data_len);
            break;

        /* t7 - 跳绳 */
        case ST_ROPE_SKIPPING:
            get_ms_sport_category_t7_data_header(p_id->type_desc.data_type, p_id->version, pp_header_data, p_data_len);
            break;

        /* t8 - 椭圆机 */
        case ST_ELLIPTICAL_MACHINE:
            get_ms_sport_category_t8_data_header(p_id->type_desc.data_type, p_id->version, pp_header_data, p_data_len);
            break;

        /* t9 - 户外跑步类 */
        case ST_OUTSIDE_RUN_CATEGORY:
            get_ms_sport_category_t9_data_header(p_id->type_desc.data_type, p_id->version, pp_header_data, p_data_len);
            break;
        /* t10 */
        case ST_OUTSIDE_NOT_RUN_CATEGORY://户外骑行改为户外非跑走类
            get_ms_sport_category_t10_data_header(p_id->type_desc.data_type, p_id->version, pp_header_data, p_data_len);
            break;

        default:
            break;
        }
    }

    return true;
}

uint32_t mul_sport_platform_get_item_nums(p_data_id_t p_id)
{
    uint32_t item_nums = 0;

    switch (p_id->type_desc.specific_type)
    {
        /* t5 - 游泳 */
        case ST_SWIM_INDOOR:
        case ST_SWIM_OUTDOOR:
            item_nums = mul_sport_get_swimming_subsection();
            break;

        default:
            item_nums = mul_sport_get_sport_time_count();
            break;
    }

    return item_nums;
}

bool mul_sport_platform_get_record_info(data_id_t *p_id, ms_record_info_t *p_record_info)
{
    bool get_rst = true;

    memset(p_record_info, 0, sizeof(ms_record_info_t));

    switch (p_id->type_desc.specific_type)
    {
        /* t2 - 室内跑 */
        case ST_INDOOR_RUN:
            get_ms_sport_category_t2_record_info(p_id->version, p_record_info);
            break;

        /* t4 - 自由训练 */
        case ST_INDOOR_CYCLE:
        case ST_FREE_SPORT:
            get_ms_sport_category_t4_record_info(p_id->version, p_record_info);
            break;

        /* t5 - 游泳 */
        case ST_SWIM_INDOOR:
        case ST_SWIM_OUTDOOR:
            get_ms_sport_category_t5_record_info(p_id->version, p_record_info);
            break;

        /* t6 - 划船机 */
        case ST_ROWING_MACHINE:
            get_ms_sport_category_t6_record_info(p_id->version, p_record_info);
            break;

        /* t7 - 跳绳 */
        case ST_ROPE_SKIPPING:
            get_ms_sport_category_t7_record_info(p_id->version, p_record_info);
            break;

        /* t8 - 椭圆机 */
        case ST_ELLIPTICAL_MACHINE:
            get_ms_sport_category_t8_record_info(p_id->version, p_record_info);
            break;

        /* t9 - 户外跑步类 */
        case ST_OUTSIDE_RUN_CATEGORY:
            get_ms_sport_category_t9_record_info(p_id->version, p_record_info);
            break;

        /* t10 - 户外非跑走类*/
        case ST_OUTSIDE_NOT_RUN_CATEGORY:
            get_ms_sport_category_t10_record_info(p_id->version, p_record_info);
            break;

        default:
            get_rst = false;
            break;
    }

    return get_rst;
}

bool mul_sport_platform_get_record_head(data_id_t *p_id, uint8_t *p_input_read_buf, ms_record_head_t *p_record_head)
{
    bool get_rst = true;

    memset(p_record_head, 0, sizeof(ms_record_head_t));

    switch (p_id->type_desc.specific_type)
    {
        /* t2 - 室内跑 */
        case ST_INDOOR_RUN:
            get_ms_sport_category_t2_record_head(p_id->version, p_input_read_buf, p_record_head);
            break;

        /* t4 - 自由训练 */
        case ST_INDOOR_CYCLE:
        case ST_FREE_SPORT:
            get_ms_sport_category_t4_record_head(p_id->version, p_input_read_buf, p_record_head);
            break;

        /* t5 - 游泳 */
        case ST_SWIM_INDOOR:
        case ST_SWIM_OUTDOOR:
            get_ms_sport_category_t5_record_head(p_id->version, p_input_read_buf, p_record_head);
            break;

        /* t6 - 划船机 */
        case ST_ROWING_MACHINE:
            get_ms_sport_category_t6_record_head(p_id->version, p_input_read_buf, p_record_head);
            break;

        /* t7 - 跳绳 */
        case ST_ROPE_SKIPPING:
            get_ms_sport_category_t7_record_head(p_id->version, p_input_read_buf, p_record_head);
            break;

        /* t8 - 椭圆机 */
        case ST_ELLIPTICAL_MACHINE:
            get_ms_sport_category_t8_record_head(p_id->version, p_input_read_buf, p_record_head);
            break;

        /* t9 - 户外跑步类 */
        case ST_OUTSIDE_RUN_CATEGORY:
            get_ms_sport_category_t9_record_head(p_id->version, p_input_read_buf, p_record_head);
            break;

        /* t10 - 户外非跑走类*/
        case ST_OUTSIDE_NOT_RUN_CATEGORY:
            get_ms_sport_category_t10_record_head(p_id->version, p_input_read_buf, p_record_head);
            break;

        default:
            get_rst = false;
            break;
    }

    return get_rst;
}

bool mul_sport_platform_get_record_body(data_id_t *p_id, uint8_t *p_input_read_buf, ms_record_item_t *p_record_item)
{
    bool get_rst = true;

    memset(p_record_item, 0, sizeof(ms_record_item_t));

    switch (p_id->type_desc.specific_type)
    {
        /* t2 - 室内跑 */
        case ST_INDOOR_RUN:
            get_ms_sport_category_t2_record_body(p_id->version, p_input_read_buf, p_record_item);
            break;

        /* t4 - 自由训练 */
        case ST_INDOOR_CYCLE:
        case ST_FREE_SPORT:
            get_ms_sport_category_t4_record_body(p_id->version, p_input_read_buf, p_record_item);
            break;

        /* t5 - 游泳 */
        case ST_SWIM_INDOOR:
        case ST_SWIM_OUTDOOR:
            get_ms_sport_category_t5_record_body(p_id->version, p_input_read_buf, p_record_item);
            break;

        /* t6 - 划船机 */
        case ST_ROWING_MACHINE:
            get_ms_sport_category_t6_record_body(p_id->version, p_input_read_buf, p_record_item);
            break;

        /* t7 - 跳绳 */
        case ST_ROPE_SKIPPING:
            get_ms_sport_category_t7_record_body(p_id->version, p_input_read_buf, p_record_item);
            break;

        /* t8 - 椭圆机 */
        case ST_ELLIPTICAL_MACHINE:
            get_ms_sport_category_t8_record_body(p_id->version, p_input_read_buf, p_record_item);
            break;

        /* t9 - 户外跑步类 */
        case ST_OUTSIDE_RUN_CATEGORY:
            get_ms_sport_category_t9_record_body(p_id->version, p_input_read_buf, p_record_item);
            break;

        /* t10 - 户外非跑走类*/
        case ST_OUTSIDE_NOT_RUN_CATEGORY:
            get_ms_sport_category_t10_record_body(p_id->version, p_input_read_buf, p_record_item);
            break;

        default:
            get_rst = false;
            break;
    }

    return get_rst;
}

bool mul_sport_platform_get_record_is_detail_body(data_id_t *p_id, uint8_t *p_input_read_buf)
{
    bool get_rst = false;

    switch (p_id->type_desc.specific_type)
    {
        /* t5 - 游泳 */
        case ST_SWIM_INDOOR:
        case ST_SWIM_OUTDOOR:
            get_rst = get_ms_sport_category_t5_record_is_detail_body(p_id->version, p_input_read_buf);
            break;

        default:
            get_rst = true;
            break;
    }

    return get_rst;
}

bool mul_sport_get_cur_sport_config(void **pp_sport_cofig)
{
    bool ret_flag = true;

    //    /* 获取运动类型 */
    input_sport_t input_sport_type = 0;
    Sport_Type_Type sport_type = ST_NONE;

    input_sport_type = mul_sport_get_input_sport_type();

    typedef struct {
        const void  *ret_val;
    } ms_sport_type_item_t;

    const ms_sport_type_item_t m_sport_type_table[SPORTING_MAX_END_TYPE] = {
        [SPORTING_Outdoor_running_TYPE]                          = {&g_outside_run_category_config},    // 户外跑步
        [SPORTING_Outdoor_walking_TYPE]                          = {&g_outside_run_category_config},    // 户外健走
        [SPORTING_free_activity_TYPE]                            = {&g_free_sport_config},              // 自由训练
        [SPORTING_Outdoor_hiking_TYPE]                           = {&g_outside_run_category_config},    // 户外徒步
        [SPORTING_Outdoor_cycling_TYPE]                          = {&g_outside_non_running_category_config}, // 户外骑行,户外非跑走类型
        [SPORTING_Indoor_running_TYPE]                           = {&g_indoor_run_config},              // 室内跑步
        [SPORTING_Skipping_rope_H_TYPE]                          = {&g_rope_skipping_config},           // 跳绳
        [SPORTING_swim_indoor_TYPE]                              = {&g_indoor_swimming_h_config},       // 泳池游泳
        [SPORTING_swim_outdoor_TYPE]                             = {&g_outside_swimming_h_config},      // 开放水域游泳
        [SPORTING_sailboat_TYPE]                                 = {&g_free_sport_config},              // 帆船
        [SPORTING_paddle_board_TYPE]                             = {&g_free_sport_config},              // 桨板
        [SPORTING_water_polo_TYPE]                               = {&g_free_sport_config},              // 水球
        [SPORTING_aquatic_sport_TYPE]                            = {&g_free_sport_config},              // 水上运动
        [SPORTING_surfing_TYPE]                                  = {&g_free_sport_config},              // 滑水
        [SPORTING_canoeing_TYPE]                                 = {&g_free_sport_config},              // 皮划艇
        [SPORTING_kayak_rafting_TYPE]                            = {&g_free_sport_config},              // 皮艇漂流
        [SPORTING_rowing_TYPE]                                   = {&g_free_sport_config},              // 划船
        [SPORTING_motorboat_TYPE]                                = {&g_free_sport_config},              // 摩托艇
        [SPORTING_web_swimming_TYPE]                             = {&g_free_sport_config},              // 蹼泳
        [SPORTING_driving_TYPE]                                  = {&g_free_sport_config},              // 跳水
        [SPORTING_fancy_swimming_TYPE]                           = {&g_free_sport_config},              // 花样游泳
        [SPORTING_snorkeling_TYPE]                               = {&g_free_sport_config},              // 浮潜
        [SPORTING_kite_surfing_TYPE]                             = {&g_free_sport_config},              // 风筝冲浪
        [SPORTING_indoor_surfing_TYPE ]                          = {&g_free_sport_config},              // 室内冲浪
        [SPORTING_dragon_boat_TYPE ]                             = {&g_free_sport_config},              // 龙舟
        [SPORTING_Mountaineering_TYPE]                           = {&g_outside_run_category_config},    // 登山
        [SPORTING_Off_road_TYPE]                                 = {&g_outside_run_category_config},    // 越野
        [SPORTING_rock_climbing_TYPE]                            = {&g_free_sport_config},              // 攀岩
        [SPORTING_skateboard_TYPE]                               = {&g_free_sport_config},              // 滑板
        [SPORTING_Roller_skating_TYPE]                           = {&g_free_sport_config},              // 轮滑
        [SPORTING_Parkour_TYPE]                                  = {&g_free_sport_config},              // 跑酷
        [SPORTING_ATV_TYPE]                                      = {&g_free_sport_config},              // 沙滩车
        [SPORTING_Paraglider_TYPE]                               = {&g_free_sport_config},              // 滑翔伞
        [SPORTING_High_intensity_interval_training_TYPE]         = {&g_free_sport_config},              // 高强度间歇训练
        [SPORTING_Yoga_TYPE]                                     = {&g_free_sport_config},              // 瑜伽
        [SPORTING_Indoor_cycling_TYPE]                           = {&g_free_sport_config},              // 室内单车
        [SPORTING_Elliptical_machine_TYPE]                       = {&g_elliptical_machine_config},      // 椭圆机
        [SPORTING_Rowing_machine_TYPE]                           = {&g_rowing_machine_config},          // 划船机
        [SPORTING_Climbing_machine_TYPE]                         = {&g_free_sport_config},              // 爬楼机
        [SPORTING_Stepper_TYPE]                                  = {&g_free_sport_config},              // 踏步机
        [SPORTING_Core_training_TYPE]                            = {&g_free_sport_config},              // 核心训练
        [SPORTING_Flexibility_training_TYPE]                     = {&g_free_sport_config},              // 柔韧训练
        [SPORTING_Pilates_TYPE]                                  = {&g_free_sport_config},              // 普拉提
        [SPORTING_gymnastics_TYPE]                               = {&g_free_sport_config},              // 体操
        [SPORTING_Stretch_TYPE]                                  = {&g_free_sport_config},              // 拉伸
        [SPORTING_Strength_Training_TYPE]                        = {&g_free_sport_config},              // 力量训练
        [SPORTING_Cross_training_CrossFit_TYPE]                  = {&g_free_sport_config},              // 交叉训练CrossFit
        [SPORTING_Climb_the_stairs_TYPE]                         = {&g_free_sport_config},              // 爬楼梯
        [SPORTING_Aerobics_TYPE]                                 = {&g_free_sport_config},              // 健身操
        [SPORTING_Physical_Training_TYPE]                        = {&g_free_sport_config},              // 体能训练
        [SPORTING_Wall_ball_TYPE]                                = {&g_free_sport_config},              // 墙球
        [SPORTING_Dumbbell_training_TYPE]                        = {&g_free_sport_config},              // 哑铃训练
        [SPORTING_Barbell_training_TYPE]                         = {&g_free_sport_config},              // 杠铃训练
        [PORTING_weightlifting_TYPE]                             = {&g_free_sport_config},              // 举重
        [SPORTING_Deadlift_TYPE]                                 = {&g_free_sport_config},              // 硬拉
        [SPORTING_Bobby_Jump_TYPE]                               = {&g_free_sport_config},              // 波比跳
        [SPORTING_Sit_ups_TYPE]                                  = {&g_free_sport_config},              // 仰卧起坐
        [SPORTING_Functional_training_TYPE]                      = {&g_free_sport_config},              // 功能性训练
        [SPORTING_Upper_limb_training_TYPE]                      = {&g_free_sport_config},              // 上肢训练
        [SPORTING_Lower_limb_training_TYPE]                      = {&g_free_sport_config},              // 下肢训练
        [SPORTING_Waist_and_abdomen_training_TYPE]               = {&g_free_sport_config},              // 腰腹训练
        [SPORTING_Back_training_TYPE]                            = {&g_free_sport_config},              // 背部训练
        [SPORTING_Square_dance_TYPE]                             = {&g_free_sport_config},              // 广场舞
        [SPORTING_Belly_dance_TYPE]                              = {&g_free_sport_config},              // 肚皮舞
        [SPORTING_ballet_TYPE]                                   = {&g_free_sport_config},              // 芭蕾舞
        [SPORTING_Street_dance_TYPE]                             = {&g_free_sport_config},              // 街舞
        [SPORTING_Zumba_TYPE]                                    = {&g_free_sport_config},              // 尊巴
        [SPORTING_National_dance_TYPE]                           = {&g_free_sport_config},              // 民族舞
        [SPORTING_Jazz_TYPE]                                     = {&g_free_sport_config},              // 爵士舞
        [SPORTING_Latin_Dance_TYPE]                              = {&g_free_sport_config},              // 拉丁舞
        [SPORTING_dance_TYPE]                                    = {&g_free_sport_config},              // 舞蹈
        [SPORTING_boxing_TYPE]                                   = {&g_free_sport_config},              // 拳击
        [SPORTING_Wrestling_TYPE]                                = {&g_free_sport_config},              // 摔跤
        [SPORTING_Martial_arts_TYPE]                             = {&g_free_sport_config},              // 武术
        [SPORTING_Tai_Chi_TYPE]                                  = {&g_free_sport_config},              // 太极
        [SPORTING_Muay_Thai_TYPE]                                = {&g_free_sport_config},              // 泰拳
        [SPORTING_judo_TYPE]                                     = {&g_free_sport_config},              // 柔道
        [SPORTING_Taekwondo_TYPE]                                = {&g_free_sport_config},              // 跆拳道
        [SPORTING_karate_TYPE]                                   = {&g_free_sport_config},              // 空手道
        [SPORTING_free_sparring_TYPE]                            = {&g_free_sport_config},              // 自由搏击
        [SPORTING_fencing_movement_TYPE]                         = {&g_free_sport_config},              // 剑术
        [SPORTING_fencing_TYPE]                                  = {&g_free_sport_config},              // 击剑
        [SPORTING_tennis_TYPE]                                   = {&g_free_sport_config},              // 网球
        [SPORTING_basketball_TYPE]                               = {&g_free_sport_config},              // 篮球
        [SPORTING_golf_TYPE]                                     = {&g_free_sport_config},              // 高尔夫
        [SPORTING_Soccer_TYPE]                                   = {&g_free_sport_config},              // 足球
        [SPORTING_volleyball_TYPE]                               = {&g_free_sport_config},              // 排球
        [SPORTING_baseball_TYPE]                                 = {&g_free_sport_config},              // 棒球
        [SPORTING_softball_TYPE]                                 = {&g_free_sport_config},              // 垒球
        [SPORTING_Rugby_TYPE]                                    = {&g_free_sport_config},              // 橄榄球
        [SPORTING_hockey_TYPE]                                   = {&g_free_sport_config},              // 曲棍球
        [SPORTING_pingpong_TYPE]                                 = {&g_free_sport_config},              // 乒乓球
        [SPORTING_badminton_TYPE]                                = {&g_free_sport_config},              // 羽毛球
        [SPORTING_cricket_TYPE]                                  = {&g_free_sport_config},              // 板球
        [SPORTING_Handball_TYPE]                                 = {&g_free_sport_config},              // 手球
        [SPORTING_bowling_TYPE]                                  = {&g_free_sport_config},              // 保龄球
        [SPORTING_squash_TYPE]                                   = {&g_free_sport_config},              // 壁球
        [SPORTING_billiards_TYPE]                                = {&g_free_sport_config},              // 台球
        [SPORTING_Shuttlecock_TYPE]                              = {&g_free_sport_config},              // 毽球
        [SPORTING_beach_soccer_TYPE]                             = {&g_free_sport_config},              // 沙滩足球
        [SPORTING_beach_volleyball_TYPE]                         = {&g_free_sport_config},              // 沙滩排球
        [SPORTING_Sepak_Takraw_TYPE]                             = {&g_free_sport_config},              // 藤球
        [SPORTING_Snowboarding_TYPE]                             = {&g_free_sport_config},              // 单板滑雪
        [SPORTING_Double_board_skiing_TYPE]                      = {&g_free_sport_config},              // 双板滑雪
        [SPORTING_Outdoor_skating_TYPE]                          = {&g_free_sport_config},              // 户外滑冰
        [SPORTING_Curling_TYPE]                                  = {&g_free_sport_config},              // 冰壶
        [SPORTING_Snow_sports_TYPE]                              = {&g_free_sport_config},              // 雪上运动
        [SPORTING_Snowmobile_TYPE]                               = {&g_free_sport_config},              // 雪地摩托
        [SPORTING_puck_TYPE]                                     = {&g_free_sport_config},              // 冰球
        [SPORTING_Snow_car_TYPE]                                 = {&g_free_sport_config},              // 雪车
        [SPORTING_sled_TYPE]                                     = {&g_free_sport_config},              // 雪橇
        [SPORTING_Archery_TYPE]                                  = {&g_free_sport_config},              // 射箭
        [SPORTING_Darts_TYPE]                                    = {&g_free_sport_config},              // 飞镖
        [SPORTING_ride_horse_TYPE]                               = {&g_free_sport_config},              // 骑马
        [SPORTING_Tug_of_war_TYPE]                               = {&g_free_sport_config},              // 拔河
        [SPORTING_Hula_Hoop_TYPE]                                = {&g_free_sport_config},              // 呼啦圈
        [SPORTING_fly_a_kite_TYPE]                               = {&g_free_sport_config},              // 放风筝
        [SPORTING_fishing_TYPE]                                  = {&g_free_sport_config},              // 钓鱼
        [SPORTING_Frisbee_TYPE]                                  = {&g_free_sport_config},              // 飞盘
        [SPORTING_bicycle_moto_TYPE ]                            = {&g_free_sport_config},              // 小轮车
        [SPORTING_heel_and_toe_TYPE ]                            = {&g_free_sport_config},              // 竞走
        [SPORTING_spinning_TYPE ]                                = {&g_free_sport_config},              // 动感单车
        [SPORTING_walking_machine_TYPE ]                         = {&g_free_sport_config},              // 漫步机
        [SPORTING_step_training_TYPE ]                           = {&g_free_sport_config},              // 单杠
        [SPORTING_single_bar_TYPE ]                              = {&g_free_sport_config},              // 双杠
        [SPORTING_parallel_bars_TYPE ]                           = {&g_free_sport_config},              // 踏步训练
        [SPORTING_group_callisthenics_TYPE ]                     = {&g_free_sport_config},              // 团体操
        [SPORTING_strike_TYPE ]                                  = {&g_free_sport_config},              // 搏击操
        [SPORTING_battle_rope_TYPE ]                             = {&g_free_sport_config},              // 战绳
        [SPORTING_mixed_aerobic_TYPE ]                           = {&g_free_sport_config},              // 混合有氧
        [SPORTING_walk_indoor_TYPE ]                             = {&g_free_sport_config},              // 室内步行
        [SPORTING_gym_TYPE ]                                     = {&g_free_sport_config},              // 室内健身
        [SPORTING_hip_hop_dance_TYPE ]                           = {&g_free_sport_config},              // 嘻哈舞
        [SPORTING_pole_dance_TYPE ]                              = {&g_free_sport_config},              // 钢管舞
        [SPORTING_breakdancing_TYPE ]                            = {&g_free_sport_config},              // 霹雳舞
        [SPORTING_social_dancing_TYPE ]                          = {&g_free_sport_config},              // 交际舞
        [SPORTING_modern_dancing_TYPE ]                          = {&g_free_sport_config},              // 现代舞
        [SPORTING_jujitsu_TYPE ]                                 = {&g_free_sport_config},              // 柔术
        [SPORTING_indoor_football_TYPE ]                         = {&g_free_sport_config},              // 室内足球
        [SPORTING_sandbags_ball_TYPE ]                           = {&g_free_sport_config},              // 沙包球
        [SPORTING_bocci_TYPE ]                                   = {&g_free_sport_config},              // 地掷球
        [SPORTING_hihi_ball_TYPE ]                               = {&g_free_sport_config},              // 回力球
        [SPORTING_gateball_TYPE ]                                = {&g_free_sport_config},              // 门球
        [SPORTING_dodgeball_TYPE ]                               = {&g_free_sport_config},              // 躲避球
        [SPORTING_cross_country_skiing_TYPE ]                    = {&g_free_sport_config},              // 越野滑雪
        [SPORTING_indoor__skating_TYPE ]                         = {&g_free_sport_config},              // 室内滑冰
        [SPORTING_shuttlecock_kicking_TYPE ]                     = {&g_free_sport_config},              // 踢毽子
        [SPORTING_swing_TYPE ]                                   = {&g_free_sport_config},              // 秋千
        [SPORTING_motion_sensing_game_TYPE ]                     = {&g_free_sport_config},              // 体感游戏
        [SPORTING_foosball_TYPE ]                                = {&g_free_sport_config},              // 桌上足球
        [SPORTING_shuffle_ball_TYPE ]                            = {&g_free_sport_config},              // 沙狐球
        [SPORTING_electronic_sports_TYPE ]                       = {&g_free_sport_config},              // 电子竞技
        [SPORTING_chess_TYPE ]                                   = {&g_free_sport_config},              // 国际象棋
        [SPORTING_draughts_TYPE ]                                = {&g_free_sport_config},              // 国际跳棋
        [SPORTING_weiqi_TYPE ]                                   = {&g_free_sport_config},              // 围棋
        [SPORTING_bridge_TYPE ]                                  = {&g_free_sport_config},              // 桥牌
        [SPORTING_board_games_TYPE ]                             = {&g_free_sport_config},              // 桌游
        [SPORTING_equesttrian_TYPE ]                             = {&g_free_sport_config},              // 马术
        [SPORTING_track_and_field_TYPE]                          = {&g_free_sport_config},              // 田径
        [SPORTING_racing_car_TYPE ]                              = {&g_free_sport_config},              // 赛车                         
    };

    ret_flag = false;

    if (input_sport_type >= SPORTING_MAX_END_TYPE)
    {
        return ret_flag;
    }

    if (m_sport_type_table[input_sport_type].ret_val == NULL)
    {
        return ret_flag;
    }

    sport_type = module_ms_api_sport_type_convert_upload(input_sport_type);

    mul_sport_set_sub_sport_type(sport_type);

    *pp_sport_cofig = (void *)m_sport_type_table[input_sport_type].ret_val;

    ret_flag = true;
    return ret_flag;
}

bool mul_sport_platform_compare_key(const void *dist_args_obj, const void *src_args_obj)
{
    if (!dist_args_obj || !src_args_obj)
    {
        return false;
    }

    p_ms_abstract_sport_handle_t p_sport_handle_item =
        (p_ms_abstract_sport_handle_t)dist_args_obj;

    p_ms_abstract_config_t p_sport_config_item =
        (p_ms_abstract_config_t)src_args_obj;

    if (p_sport_handle_item->version == MUL_SPORT_VER_1) // XXX: p_sport_config_item版本号暂时没用到
    {
        p_ms_common_sport_handle_v1_t p_common_sport_handle_item =
            (p_ms_common_sport_handle_v1_t)p_sport_handle_item;

        p_ms_common_sport_config_v1_t p_ms_common_sport_config_item =
            (p_ms_common_sport_config_v1_t)p_sport_config_item;

        if (p_common_sport_handle_item->sport_handle.sport_category == p_ms_common_sport_config_item->sport_config.sport_category && p_common_sport_handle_item->sport_handle.sport_category_ver == p_ms_common_sport_config_item->sport_config.sport_category_ver)
        {
            return true;
        }
    }

    return false;
}

void mul_sport_platform_auto_sport_write_data(void)
{
#if 1
    uint32_t write_data_len = 0;

    pSPORT_app_auto_sport_data_t p_read_sport_data = NULL;
    pSPORT_app_auto_sport_data_t p_write_sport_data = NULL;

    if (misc_sport_data.auto_sport_obj.sport_type == SPORTING_Indoor_running_TYPE)
    {
        for (int32_t i = 0; i < misc_sport_data.auto_sport_obj.data_len;)
        {
            p_read_sport_data = (pSPORT_app_auto_sport_data_t)&misc_sport_data.auto_sport_obj.data.data_array[i];
            p_write_sport_data = (pSPORT_app_auto_sport_data_t)&misc_sport_data.auto_sport_obj.data.data_array[write_data_len];
    
            p_write_sport_data->indoor_run.extra_calorie.ec_s.extra_step = p_read_sport_data->run_category.extra_calorie.ec_s.extra_step;
            p_write_sport_data->indoor_run.extra_calorie.ec_s.extra_calorie = p_read_sport_data->run_category.extra_calorie.ec_s.extra_calorie;
            p_write_sport_data->indoor_run.hr = p_read_sport_data->run_category.hr;
            p_write_sport_data->indoor_run.extra_distance = p_read_sport_data->run_category.extra_distance;
            p_write_sport_data->indoor_run.extra_stride = p_read_sport_data->run_category.extra_stride;
            p_write_sport_data->indoor_run.cadence = p_read_sport_data->run_category.cadence;
            p_write_sport_data->indoor_run.pace = p_read_sport_data->run_category.pace;

            i += sizeof(p_read_sport_data->run_category);
            write_data_len += sizeof(p_write_sport_data->indoor_run);
        }

        misc_sport_data.auto_sport_obj.data_len = write_data_len;
    }

    mul_sport_write_mass_auto_sport_data(misc_sport_data.auto_sport_obj.data.data_array, \
                                         misc_sport_data.auto_sport_obj.data_len, \
                                         misc_sport_data.auto_sport_obj.total_cnts);


    misc_sport_data.auto_sport_obj.total_cnts = 0;
    misc_sport_data.auto_sport_obj.data_len = 0;
    misc_sport_data.auto_sport_obj.sport_type = SPORTING_MAX_END_TYPE;
#endif
}

void mul_sport_platform_auto_sport_write_gps(void)
{
#if 1
    SPORT_app_auto_sport_gps_obj_t *p_sport_gps_obj = mul_sport_platform_auto_sport_get_gps_data();
    mul_sport_write_mass_auto_sport_gps(p_sport_gps_obj->data_array,
                                        p_sport_gps_obj->data_len,
                                        p_sport_gps_obj->total_cnts);

    mul_sport_platform_auto_sport_memset_gps_data();//清除
#endif
}

void mul_sport_platform_auto_sport_put_data(void)
{
#if 1
    if (misc_sport_data.auto_sport_obj.data_len + sizeof(pSPORT_app_auto_sport_data_t) < MAX_SPORT_APP_AUTO_SPORT_DATA)
    {
        pSPORT_app_auto_sport_data_t p_sport_data = (pSPORT_app_auto_sport_data_t)&misc_sport_data.auto_sport_obj.data.data_array[misc_sport_data.auto_sport_obj.data_len];
        bool is_execute = true;
        // printf("putdata hr->%d,kcal->%lf,s_counter->%d,flq->%d\n",
        // mul_sport_get_sport_heart_rate(),
        // mul_sport_get_sport_consume(),
        // mul_sport_get_cyclic_sport_counter(),
        // mul_sport_get_sport_rm_frequency());
        switch (misc_sport_data.auto_sport_obj.sport_type)
        {
            case SPORTING_Skipping_rope_H_TYPE:
                p_sport_data->rope_skipping.hr = mul_sport_get_sport_heart_rate();
                p_sport_data->rope_skipping.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();
                // p_sport_data->rope_skipping.extra_jumps = mul_sport_get_cyclic_sport_counter() - multi_motion_get_prev_cyclic_sport_counter();
                // p_sport_data->rope_skipping.takeoff_height = 0;
                // p_sport_data->rope_skipping.extra_trips = 0;
                p_sport_data->rope_skipping.cadence = mul_sport_get_sport_rm_frequency();
                misc_sport_data.auto_sport_obj.data_len += sizeof(p_sport_data->rope_skipping);
                break;
            case SPORTING_Rowing_machine_TYPE:
                p_sport_data->rowing_machine.hr = mul_sport_get_sport_heart_rate();
                p_sport_data->rowing_machine.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();
                p_sport_data->rowing_machine.sliding_frequency = mul_sport_get_sport_rm_frequency();
                // p_sport_data->rowing_machine.extra_stroke.es_s.is_drive = 0;
                // p_sport_data->rowing_machine.extra_stroke.es_s.is_put = 0;
                // p_sport_data->rowing_machine.extra_stroke.es_s.extra_stroke = mul_sport_get_cyclic_sport_counter() - multi_motion_get_prev_cyclic_sport_counter();
                misc_sport_data.auto_sport_obj.data_len += sizeof(p_sport_data->rowing_machine);
                break;
            case SPORTING_Elliptical_machine_TYPE:
                p_sport_data->elliptical_machine.extra_calorie.ec_s.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();
                p_sport_data->elliptical_machine.extra_calorie.ec_s.extra_step = mul_sport_get_cyclic_sport_counter() - multi_motion_get_prev_cyclic_sport_counter();
                p_sport_data->elliptical_machine.hr = mul_sport_get_sport_heart_rate();
                p_sport_data->elliptical_machine.cadence = mul_sport_get_sport_rm_frequency();
                misc_sport_data.auto_sport_obj.data_len += sizeof(p_sport_data->elliptical_machine);
                break;
            case SPORTING_Outdoor_cycling_TYPE:
                p_sport_data->outside_cycle.extra_calorie.ec_s.extra_calorie = mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();
                p_sport_data->outside_cycle.extra_calorie.ec_s.extra_count = 0;//部分非户外跑走类帆船龙舟的划次
                p_sport_data->outside_cycle.speed = mul_sport_get_sport_speed();//速度
                p_sport_data->outside_cycle.hr = mul_sport_get_sport_heart_rate();

                p_sport_data->outside_cycle.extra_distance                          =
                                (mul_sport_get_sport_distance() - multi_motion_get_prev_distance());

                if (get_is_up_km_status())
                {
                    p_sport_data->outside_cycle.heigth_change.hc_s.is_km = 1;
                    set_is_up_km_status(false);
                }
                else
                {
                    p_sport_data->outside_cycle.heigth_change.hc_s.is_km = 0;
                }
                misc_sport_data.auto_sport_obj.data_len += sizeof(p_sport_data->outside_cycle);
                break;
            case SPORTING_Outdoor_walking_TYPE:
            case SPORTING_Outdoor_running_TYPE:
                p_sport_data->run_category.extra_calorie.ec_s.extra_calorie        =
                                mul_sport_get_sport_consume() - multi_motion_get_prev_calorie();

                p_sport_data->run_category.extra_calorie.ec_s.extra_step           =
                                mul_sport_get_sport_step_num() - multi_motion_get_prev_step();

                p_sport_data->run_category.hr = mul_sport_get_sport_heart_rate();

                p_sport_data->run_category.extra_distance                          =
                                (mul_sport_get_sport_distance() - multi_motion_get_prev_distance()) * 10;

                p_sport_data->run_category.extra_stride = mul_sport_get_sport_extra_stride();
                p_sport_data->run_category.cadence = mul_sport_get_sport_step_frequency();
                p_sport_data->run_category.pace = mul_sport_get_sport_speed_distribution();
                if (get_is_up_km_status())
                {
                    p_sport_data->run_category.heigth_change.hc_s.is_km = 1;
                    set_is_up_km_status(false);
                }
                else
                {
                    p_sport_data->run_category.heigth_change.hc_s.is_km = 0;
                }
                
                p_sport_data->run_category.heigth_change.hc_s.is_up                =
                                mul_sport_get_sport_altitude_change_type();
                p_sport_data->run_category.heigth_change.hc_s.height_change        =
                                mul_sport_get_sport_altitude_change_val();
                misc_sport_data.auto_sport_obj.data_len += sizeof(p_sport_data->run_category);

                break;
            default:
                is_execute = false;
                break;
        }

        if (is_execute)
        {
            misc_sport_data.auto_sport_obj.total_cnts++;

            multi_motion_set_prev_calorie(mul_sport_get_sport_consume());
            multi_motion_set_prev_step(mul_sport_get_sport_step_num());
            multi_motion_set_prev_distance(mul_sport_get_sport_distance());
            multi_motion_set_prev_cyclic_sport_counter(mul_sport_get_cyclic_sport_counter());
        }
    }
#endif
}
static SPORT_app_auto_sport_gps_obj_t auto_sport_gps_obj;
SPORT_app_auto_sport_gps_obj_t* mul_sport_platform_auto_sport_get_gps_data(void)
{
    return &auto_sport_gps_obj;
}
void mul_sport_platform_auto_sport_memset_gps_data(void)
{
    memset(&auto_sport_gps_obj,0,sizeof(auto_sport_gps_obj));
}

void mul_sport_platform_auto_sport_put_gps_data(ms_gps_item_t gps_item)
{
#if 1
    p_ms_abstract_config_t p_ms_sport_config = NULL;
    bool externn = 0;
    if (!mul_sport_get_cur_sport_config((void **)&p_ms_sport_config))
    {
        return;
    }
    switch (p_ms_sport_config->gps_ver)
    {
    case 0x1:
    {
        if (auto_sport_gps_obj.data_len + sizeof(SPORT_app_auto_sport_gpsv1_data_t) < MAX_SPORT_APP_AUTO_SPORT_GPS_DATA)
        {
            pSPORT_app_auto_sport_gpsv1_data_t p_gps_data = (pSPORT_app_auto_sport_gpsv1_data_t)&auto_sport_gps_obj.data_array[auto_sport_gps_obj.data_len];
            p_gps_data->gps_latitude = gps_item.gps_vx.latitude;
            p_gps_data->gps_longitude = gps_item.gps_vx.longitude;
            p_gps_data->gps_timestamp = gps_item.gps_vx.ts;
            auto_sport_gps_obj.data_len += sizeof(SPORT_app_auto_sport_gpsv1_data_t);
            externn = true;
        }
    }
    break;
    case 0x2:
    {
        if (auto_sport_gps_obj.data_len + sizeof(SPORT_app_auto_sport_gpsv2_data_t) < MAX_SPORT_APP_AUTO_SPORT_GPS_DATA)
        {
            pSPORT_app_auto_sport_gpsv2_data_t p_gps_data = (pSPORT_app_auto_sport_gpsv2_data_t)&auto_sport_gps_obj.data_array[auto_sport_gps_obj.data_len];
            p_gps_data->gps_latitude = gps_item.gps_vx.latitude;
            p_gps_data->gps_longitude = gps_item.gps_vx.longitude;
            p_gps_data->gps_timestamp = gps_item.gps_vx.ts;
            p_gps_data->location_accuracy = gps_item.gps_vx.location_accuracy;
            p_gps_data->speed_gps_u.speed_gps_s.gps_source = gps_item.gps_vx.speed_gps_u.speed_gps_s.gps_source;
            p_gps_data->speed_gps_u.speed_gps_s.location_speed =  gps_item.gps_vx.speed_gps_u.speed_gps_s.location_speed;
            auto_sport_gps_obj.data_len += sizeof(SPORT_app_auto_sport_gpsv2_data_t);
            externn = true;
        }
    }
    break;
    default:
        externn = false;
        break;
    }
    if (externn)
        auto_sport_gps_obj.total_cnts++;
#endif
}

bool mul_sport_platform_auto_sport_mock_put_data(uint32_t cnts)
{
    bool ret_rst = true;

    // TODO: wdh, ly
    // sport_save_data.sport_heart_rate = 78;

    for (int32_t i = 0; i < cnts; i++)
    {
        mul_sport_platform_auto_sport_put_data();
    }

    return ret_rst;
}

bool mul_sport_platform_auto_sport_mock_gps_data(uint32_t cnts)
{
#if 0
    bool ret_rst = true;

    uint32_t start_ts = mul_sport_get_timestamp();

    const float gps_arr[][2] = {
        {(float)113.83342,(float)22.631945},
        {(float)113.83341,(float)22.631937},
        {(float)113.83339,(float)22.631956},
        {(float)113.83338,(float)22.631962},
        {(float)113.83338,(float)22.631968},
        {(float)113.833374,(float)22.631975},
        {(float)113.83335,(float)22.63197},
        {(float)113.83336,(float)22.631975},
        {(float)113.833374,(float)22.631979},
        {(float)113.83338,(float)22.631985},
        {(float)113.83339,(float)22.631987},
        {(float)113.8334,(float)22.63199},
        {(float)113.8334,(float)22.631994},
        {(float)113.8334,(float)22.631994},
        {(float)113.833405,(float)22.631998},
        {(float)113.8334,(float)22.631992},
        {(float)113.8334,(float)22.631987},
        {(float)113.8334,(float)22.631983},
        {(float)113.83339,(float)22.631977},
        {(float)113.83339,(float)22.631973},
        {(float)113.83339,(float)22.631968},
        {(float)113.83339,(float)22.631962},
        {(float)113.8334,(float)22.631958},
        {(float)113.8334,(float)22.631956},
        {(float)113.8334,(float)22.63196},
        {(float)113.8334,(float)22.631968},
        {(float)113.8334,(float)22.631975},
        {(float)113.83339,(float)22.631979},
        {(float)113.83339,(float)22.631983},
        {(float)113.83339,(float)22.631989},
        {(float)113.83339,(float)22.631996},
        {(float)113.83339,(float)22.632002},
        {(float)113.83339,(float)22.631996},
        {(float)113.83339,(float)22.631989},
        {(float)113.83339,(float)22.631983},
        {(float)113.83339,(float)22.631985},
        {(float)113.83339,(float)22.631992},
        {(float)113.83339,(float)22.632},
        {(float)113.83339,(float)22.632006},
        {(float)113.83339,(float)22.632013},
        {(float)113.8334,(float)22.632019},
        {(float)113.833405,(float)22.632025},
        {(float)113.833405,(float)22.632032},
        {(float)113.83341,(float)22.632038},
        {(float)113.83342,(float)22.632044},
        {(float)113.83343,(float)22.632048},
        {(float)113.833435,(float)22.632053},
        {(float)113.83344,(float)22.63206},
        {(float)113.83344,(float)22.632065},
        {(float)113.83345,(float)22.632072},
        {(float)113.83346,(float)22.632078},
        {(float)113.833466,(float)22.632084},
        {(float)113.833466,(float)22.63209},
        {(float)113.833466,(float)22.632097},
        {(float)113.833466,(float)22.632103},
        {(float)113.83347,(float)22.632113},
        {(float)113.83348,(float)22.63212},
        {(float)113.83349,(float)22.632128},
        {(float)113.8335,(float)22.632132},
        {(float)113.83352,(float)22.632133},
        {(float)113.83353,(float)22.632135},
        {(float)113.83354,(float)22.632137},
        {(float)113.83354,(float)22.632141},
        {(float)113.83355,(float)22.632145},
        {(float)113.83357,(float)22.632149},
        {(float)113.83358,(float)22.632154},
        {(float)113.83359,(float)22.632162},
        {(float)113.8336,(float)22.632168},
        {(float)113.83362,(float)22.632175},
        {(float)113.83363,(float)22.632181},
        {(float)113.83364,(float)22.632183},
        {(float)113.83364,(float)22.632187},
        {(float)113.83365,(float)22.632187},
        {(float)113.833664,(float)22.63219},
        {(float)113.83368,(float)22.632196},
        {(float)113.833694,(float)22.632202},
        {(float)113.83371,(float)22.63221},
        {(float)113.83372,(float)22.632217},
        {(float)113.83373,(float)22.632225},
        {(float)113.83374,(float)22.63223},
        {(float)113.83375,(float)22.632236},
        {(float)113.83376,(float)22.632244},
        {(float)113.83377,(float)22.63225},
        {(float)113.83378,(float)22.632256},
        {(float)113.833786,(float)22.632257},
        {(float)113.833786,(float)22.63226},
        {(float)113.8338,(float)22.632261},
        {(float)113.83382,(float)22.632265},
        {(float)113.83383,(float)22.632269},
        {(float)113.83384,(float)22.63227},
        {(float)113.833855,(float)22.63227},
        {(float)113.83386,(float)22.632273},
        {(float)113.83387,(float)22.632273},
        {(float)113.83388,(float)22.632275},
        {(float)113.83389,(float)22.63228},
        {(float)113.83391,(float)22.632286},
        {(float)113.83392,(float)22.632294},
        {(float)113.83394,(float)22.6323},
        {(float)113.83395,(float)22.632305},
        {(float)113.833954,(float)22.63231},
        {(float)113.83396,(float)22.632315},
        {(float)113.83397,(float)22.632318},
        {(float)113.833984,(float)22.632318},
        {(float)113.834,(float)22.632317},
        {(float)113.83401,(float)22.63231},
        {(float)113.834015,(float)22.632301},
        {(float)113.834015,(float)22.632288},
        {(float)113.83402,(float)22.632273},
        {(float)113.83402,(float)22.63226},
        {(float)113.83402,(float)22.632244},
        {(float)113.83403,(float)22.632229},
        {(float)113.83403,(float)22.632215},
        {(float)113.83403,(float)22.6322},
        {(float)113.83402,(float)22.632189},
        {(float)113.83402,(float)22.63218},
        {(float)113.834015,(float)22.632172},
        {(float)113.83401,(float)22.632168},
    };

    const uint32_t gps_arr_size = sizeof(gps_arr) / sizeof(gps_arr[0]);

    ms_gps_item_t gps_item;

    gps_item.gps_vx.ts = start_ts;

    for (int32_t i = 0; i < cnts; i++)
    {
        gps_item.gps_vx.longitude = gps_arr[i % gps_arr_size][0];
        gps_item.gps_vx.latitude = gps_arr[i % gps_arr_size][1];

        mul_sport_platform_auto_sport_put_gps_data(gps_item);

        gps_item.gps_vx.ts++;
    }

    return ret_rst;
#else
    return true;
#endif
}

void write_sport_data_work_proc(void){
//关机直接调
    if (misc_sport_data.is_auto_sport == true)
    {
        mul_sport_platform_auto_sport_put_data();
    }
    else if (misc_sport_data.sport_is_app_sponsor == false)
    {
        mul_sport_write_sport_data();
    }
}

void save_cur_sport_file_work_when_full(void)
{
#if defined(ENUM_PROJECT_NAME_N65B_GLOBAL)
#ifndef BSP_USING_PC_SIMULATOR
    if ((Get_current_sporting_type() == SPORTING_swim_indoor_TYPE) || (Get_current_sporting_type() == SPORTING_swim_outdoor_TYPE))
    {
        bool zh_swiming_save_total_data(void);
        zh_swiming_save_total_data();
    }
#endif
#endif
    mul_sport_save_cur_sport_file();
   // tracp_gps_flush_data();//保存GPS轨迹点
    module_sport_app_release_target();//释放运动目标
    misc_sport_data.draw_points_flag = true;//抽点开始 
    save_cur_sport_record();//保存运动记录
}

void save_cur_sport_file_work_proc(void)
{
#if defined(ENUM_PROJECT_NAME_N65B_GLOBAL)
#ifndef BSP_USING_PC_SIMULATOR
    if ((Get_current_sporting_type() == SPORTING_swim_indoor_TYPE) || (Get_current_sporting_type() == SPORTING_swim_outdoor_TYPE))
    {
        bool zh_swiming_save_total_data(void);
        zh_swiming_save_total_data();
    }
#endif
#endif
    mul_sport_save_cur_sport_file();
    //tracp_gps_flush_data();//保存GPS轨迹点
    module_sport_app_release_target();//释放运动目标
    misc_sport_data.draw_points_flag = true;//抽点开始 
    //save_sport_information_data_init();
}

void save_cur_sport_record(void)
{
    read_record_to_draw_points(Get_current_sporting_type());//抽点
    Save_Sport_data_to_exflash(Get_current_sporting_type());
    save_sport_information_data_init();//save sport total count
    mul_sport_clear_cur_sport_cache();

#ifndef BSP_USING_PC_SIMULATOR
    extern void fitness_health_sport_sys(void);
    fitness_health_sport_sys();
#endif
}

void mul_sport_platform_malloc_failed(const char *func_name, uint32_t line)
{
    mul_sport_dbg_log(" malloc failed! func=%s, line=%d\n", func_name, line);

    //Zh_Log_Fun_Write_Ram_Memory(MALLOC_FAIL_EXCEPTION_LOG_ID,
     //                           " malloc failed, func=%s, line=%d",
     //                           func_name,
     //                           line);
}


bool mul_sport_platform_init(void)
{
    bool ret_flag = true;

    mul_sport_factory_add_sport(get_ms_sport_category_t1_v1());
    mul_sport_factory_add_sport(get_ms_sport_category_t2_v1());
    mul_sport_factory_add_sport(get_ms_sport_category_t3_v1());
    mul_sport_factory_add_sport(get_ms_sport_category_t4_v1());
    mul_sport_factory_add_sport(get_ms_sport_category_t5_v1());
    mul_sport_factory_add_sport(get_ms_sport_category_t6_v1());
    mul_sport_factory_add_sport(get_ms_sport_category_t7_v1());
    mul_sport_factory_add_sport(get_ms_sport_category_t8_v1());
    mul_sport_factory_add_sport(get_ms_sport_category_t9_v1());
    mul_sport_factory_add_sport(get_ms_sport_category_t10_v1());
    return ret_flag;
}


 



#else
utc_time_t mul_sport_get_timestamp(void) { return 0; }
#endif /* FLASH_MANAGER_SWITCH */
#endif