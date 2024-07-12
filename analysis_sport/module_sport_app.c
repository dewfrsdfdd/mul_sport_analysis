
#include <stdio.h>
#include "module_sport_app.h"
// #include "algoTask.h"
// #include "data_processing.h"
// #include "sleepAlgorithm.h"
//#include "wall_clock_timer.h"
// #include "daily_calculate.h"
// #include "sport_calculate.h"
// #include "optional_wrist_posture_classifier.h"
// #include "Process_Acc_Data.h"
// #include "data_get_api.h"
//  #include "second_processing.h"
//  #include "data_manager.h"
// #include "mcif.h"
//#include "zh_data_global.h"
#include "mul_sport_ops.h"
#if defined(SENSOR_USING_HR) && !defined(BSP_USING_PC_SIMULATOR)
#include "hr_config.h"
#include "hr_sensor_service.h"
#include "app_comm_custom.h"
#endif
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
#include "heart_2in1.h"
#include "mi_algo_app.h"
#include "zh_log_recode_process.h"
#include "mi_daily_base.h"
#include "mi_activity_type.h"
#if defined(ENUM_PROJECT_NAME_N65B_GLOBAL) 

#include "gps_alg.h"
#endif
#endif
//#include "zh_app_page_id_string.h"
//#include "zh_thread_comm.h"
//#include "GPSCoordinates.h"
//#include "interconnection_manager.h"
//#include "algoTask.h"
//#include "popups_sporting_remind_data_struct_common.h"
extern uint8_t long_endurance_adv_deal_type;
// #include "gui_config.h"
// #include "lcd_middle_control.h"
// #include "logging.h"
// #include "pedometer.h"
// #include "Gps_cal_distance.h"
// #include "driver_moto.h"
// #include "airpressureProcess.h"
// #include "gps_Processing.h"
// #include "bluetooth_data.h"
// #include <os_common_api.h>
// #include "lcd_middle_control.h"
// #include <zephyr.h>
// #include <assert.h>
// #include <app_manager.h>
// #include <srv_manager.h>
// #include <mem_manager.h>
// #include <msg_manager.h>
// #include <thread_timer.h>
// #include "app_defines.h"
// #include "system_app.h"
// #include "data_manager.h"
// #include "daily_file_update.h"
// #include "page_task_sport_mainmenu_page.h"
// #include "page_task_sport_detail_page.h"
// #include "Gps_cal_distance.h"
// #include "mi_wear_fitness_calories_algo.h"
// #include "pedometer_v2.h"
// #include "mi_gps_opt_main.h"
// #include "mi_gps_rt_auto_pause.h"
// #include "page_task_sport_common_page.h"
// #include "middle_fun_logic_process.h"
// #include "gui_config.h"
// #include "buried_point.h"
// #include "moto_fun_process.h"
// #include "mi_stand.h"
// #include "miwear_task.h"
#if 0
extern stand_handle p_stand_handle ;
extern uint64_t ts_ms_stamp;
extern struct mi_gps_info *p_gps_algo;
extern  auto_pause_info_s *p_auto_pause;
extern struct mi_pedometer *p_mi_pedometer;
extern mi_calories_s *p_mi_calories;
void update_user_calories_info(void);
uint32_t wrist_delay = 0;
float last_sport_consume = 0;
extern uint8_t is_jump_main_page_times ;

extern uint8_t Always_on_Screen_enable_flag;//待机亮屏使能标志

void clearheart5second(void);
uint16_t pause_count = 0;
Sport_type sport_ing_type;
#endif
extern void app_sport_jump_to_list(void);
 extern bool app_sport_disconnect_projection(void);
 uint8_t sport_state_act=0;

 uint8_t had_cailib = 0;
 //extern rt_err_t send_msg_to_protobuf_thread(hl_if_type_t type, uint16_t subtype, uint8_t * data, uint16_t len);
// uint16_t *sport_course_array[] = {NULL, course_class1, course_class2, course_class3, course_class4, course_class5, course_class6, course_class7, course_class8, course_class9, course_class10};
#define MS_SPORT_TYPE_TABLE1(prefix)                                                              \
    prefix(SPORTING_Outdoor_running_TYPE, SportType_RUN_OUTDOOR),                                 \
        prefix(SPORTING_Outdoor_walking_TYPE, SportType_WALK_OUTDOOR),                            \
        prefix(SPORTING_free_activity_TYPE, SportType_FREE_TRAINING),                             \
        prefix(SPORTING_Outdoor_hiking_TYPE, SportType_HIKING_OUTDOOR),                           \
        prefix(SPORTING_Outdoor_cycling_TYPE, SportType_RIDE_OUTDOOR),                            \
        prefix(SPORTING_Indoor_running_TYPE, SportType_RUN_INDOOR),                               \
        prefix(SPORTING_Skipping_rope_H_TYPE, SportType_ROPE_SKIPPING),                           \
        prefix(SPORTING_swim_indoor_TYPE, SportType_SWIM_INDOOR),                                 \
        prefix(SPORTING_swim_outdoor_TYPE, SportType_SWIM_OUTDOOR),                               \
        prefix(SPORTING_sailboat_TYPE, SportType_SAILBOAT),                                       \
        prefix(SPORTING_paddle_board_TYPE, SportType_PADDLE_BOARD),                               \
        prefix(SPORTING_water_polo_TYPE, SportType_WATER_POLO),                                   \
        prefix(SPORTING_aquatic_sport_TYPE, SportType_AQUATIC_SPORT),                             \
        prefix(SPORTING_surfing_TYPE, SportType_SURFING),                                         \
        prefix(SPORTING_canoeing_TYPE, SportType_CANOEING),                                       \
        prefix(SPORTING_kayak_rafting_TYPE, SportType_KAYAK_RAFTING),                             \
        prefix(SPORTING_rowing_TYPE, SportType_ROWING),                                           \
        prefix(SPORTING_motorboat_TYPE, SportType_MOTORBOAT),                                     \
        prefix(SPORTING_web_swimming_TYPE, SportType_WEB_SWIMMING),                               \
        prefix(SPORTING_driving_TYPE, SportType_DRIVING),                                         \
        prefix(SPORTING_fancy_swimming_TYPE, SportType_FANCY_SWIMMING),                           \
        prefix(SPORTING_snorkeling_TYPE, SportType_SNORKELING),                                   \
        prefix(SPORTING_kite_surfing_TYPE, SportType_KITE_SURFING),                               \
        prefix(SPORTING_indoor_surfing_TYPE, SportType_INDOOR_SURFING),                           \
        prefix(SPORTING_dragon_boat_TYPE, SportType_DRAGON_BOAT),                                 \
        prefix(SPORTING_Mountaineering_TYPE, SportType_CLIMBING),                                 \
        prefix(SPORTING_Off_road_TYPE, SportType_CROSS_COUNTRY),                                  \
        prefix(SPORTING_rock_climbing_TYPE, SportType_ROCK_CLIMBING),                             \
        prefix(SPORTING_skateboard_TYPE, SportType_SKATE),                                        \
        prefix(SPORTING_Roller_skating_TYPE, SportType_ROLLER_SKATING),                           \
        prefix(SPORTING_Parkour_TYPE, SportType_PARKOUR),                                         \
        prefix(SPORTING_ATV_TYPE, SportType_ATV),                                                 \
        prefix(SPORTING_Paraglider_TYPE, SportType_PARAGLIDER),                                   \
        prefix(SPORTING_bicycle_moto_TYPE, SportType_BICYCLE_MOTO),                               \
        prefix(SPORTING_heel_and_toe_TYPE, SportType_HEEL_AND_TOE),                               \
        prefix(SPORTING_High_intensity_interval_training_TYPE, SportType_HIGH_INTERVAL_TRAINING), \
        prefix(SPORTING_Yoga_TYPE, SportType_YOGA),                                               \
        prefix(SPORTING_Indoor_cycling_TYPE, SportType_RIDE_INDOOR),                              \
        prefix(SPORTING_Elliptical_machine_TYPE, SportType_ELLIPTICAL_MACHINE),                   \
        prefix(SPORTING_Rowing_machine_TYPE, SportType_ROWING_MACHINE),                           \
        prefix(SPORTING_Climbing_machine_TYPE, SportType_CLIMBING_MACHINE),                       \
        prefix(SPORTING_Stepper_TYPE, SportType_STEPPER),                                         \
        prefix(SPORTING_spinning_TYPE, SportType_SPINNING),                                       \
        prefix(SPORTING_Core_training_TYPE, SportType_CORE_TRAINING),                             \
        prefix(SPORTING_Flexibility_training_TYPE, SportType_FLEXIBILITY_TRAINING),               \
        prefix(SPORTING_Pilates_TYPE, SportType_PILATES),                                         \
        prefix(SPORTING_gymnastics_TYPE, SportType_GYMNASTICS),                                   \
        prefix(SPORTING_Stretch_TYPE, SportType_STRETCH),                                         \
        prefix(SPORTING_Strength_Training_TYPE, SportType_STRENGTH_TRAINING),                     \
        prefix(SPORTING_Cross_training_CrossFit_TYPE, SportType_CROSS_FIT),                       \
        prefix(SPORTING_Climb_the_stairs_TYPE, SportType_CLIMB_STAIRS),                           \
        prefix(SPORTING_Aerobics_TYPE, SportType_AEROBICS),                                       \
        prefix(SPORTING_Physical_Training_TYPE, SportType_PHYSICAL_TRAINING),                     \
        prefix(SPORTING_Wall_ball_TYPE, SportType_WALL_BALL),                                     \
        prefix(SPORTING_Dumbbell_training_TYPE, SportType_DUMBBELL_TRAINING),                     \
        prefix(SPORTING_Barbell_training_TYPE, SportType_BARBELL_TRAINING),                       \
        prefix(PORTING_weightlifting_TYPE, SportType_WEIGHTLIFTING),                              \
        prefix(SPORTING_Deadlift_TYPE, SportType_DEADLIFT),                                       \
        prefix(SPORTING_Bobby_Jump_TYPE, SportType_BOBBY_JUMP),                                   \
        prefix(SPORTING_Sit_ups_TYPE, SportType_SIT_UPS),                                         \
        prefix(SPORTING_Functional_training_TYPE, SportType_FUNCTIONAL_TRAINING),                 \
        prefix(SPORTING_Upper_limb_training_TYPE, SportType_UPPER_LIMB_TRAINING),                 \
        prefix(SPORTING_Lower_limb_training_TYPE, SportType_LOWER_LIMB_TRAINING),                 \
        prefix(SPORTING_Waist_and_abdomen_training_TYPE, SportType_WAIST_TRAINING),               \
        prefix(SPORTING_Back_training_TYPE, SportType_BACK_TRAINING),                             \
        prefix(SPORTING_walking_machine_TYPE, SportType_WALKING_MACHINE),                         \
        prefix(SPORTING_single_bar_TYPE, SportType_SINGLE_BAR),                                   \
        prefix(SPORTING_parallel_bars_TYPE, SportType_PARALLEL_BARS),                             \
        prefix(SPORTING_step_training_TYPE, SportType_STEP_TRAINING),                             \
        prefix(SPORTING_group_callisthenics_TYPE, SportType_GROUP_CALLISTHENICS),                 \
        prefix(SPORTING_strike_TYPE, SportType_STRIKE),                                           \
        prefix(SPORTING_battle_rope_TYPE, SportType_BATTLE_ROPE),                                 \
        prefix(SPORTING_mixed_aerobic_TYPE, SportType_MIXED_AEROBIC),                             \
        prefix(SPORTING_walk_indoor_TYPE, SportType_WALK_INDOOR),                                 \
        prefix(SPORTING_gym_TYPE, SportType_GYM),                                                 \
        prefix(SPORTING_Square_dance_TYPE, SportType_SQUARE_DANCE),                               \
        prefix(SPORTING_Belly_dance_TYPE, SportType_BELLY_DANCE),                                 \
        prefix(SPORTING_ballet_TYPE, SportType_BALLET),                                           \
        prefix(SPORTING_Street_dance_TYPE, SportType_STREET_DANCE),                               \
        prefix(SPORTING_Zumba_TYPE, SportType_ZUMBA),                                             \
        prefix(SPORTING_National_dance_TYPE, SportType_NATIONAL_DANCE),                           \
        prefix(SPORTING_Jazz_TYPE, SportType_JAZZ),                                               \
        prefix(SPORTING_Latin_Dance_TYPE, SportType_LATIN_DANCE),                                 \
        prefix(SPORTING_hip_hop_dance_TYPE, SportType_HIP_HOP_DANCE),                             \
        prefix(SPORTING_pole_dance_TYPE, SportType_POLE_DANCE),                                   \
        prefix(SPORTING_breakdancing_TYPE, SportType_BREAKDANCING),                               \
        prefix(SPORTING_social_dancing_TYPE, SportType_SOCIAL_DANCING),                           \
        prefix(SPORTING_modern_dancing_TYPE, SportType_MODERN_DANCING),                           \
        prefix(SPORTING_dance_TYPE, SportType_DANCE),                                             \
        prefix(SPORTING_boxing_TYPE, SportType_BOXING),                                           \
        prefix(SPORTING_Wrestling_TYPE, SportType_WRESTLING),                                     \
        prefix(SPORTING_Martial_arts_TYPE, SportType_MARTIAL_ARTS),                               \
        prefix(SPORTING_Tai_Chi_TYPE, SportType_TAICHI),                                          \
        prefix(SPORTING_Muay_Thai_TYPE, SportType_MUAY_THAI),                                     \
        prefix(SPORTING_judo_TYPE, SportType_JUDO),                                               \
        prefix(SPORTING_Taekwondo_TYPE, SportType_TAEKWONDO),                                     \
        prefix(SPORTING_karate_TYPE, SportType_KARATE),                                           \
        prefix(SPORTING_free_sparring_TYPE, SportType_FREE_SPARRING),                             \
        prefix(SPORTING_fencing_movement_TYPE, SportType_SWORDSMANSHIP),                          \
        prefix(SPORTING_fencing_TYPE, SportType_FENCING),                                         \
        prefix(SPORTING_jujitsu_TYPE, SportType_JUJITSU),                                         \
        prefix(SPORTING_tennis_TYPE, SportType_TENNIS),                                           \
        prefix(SPORTING_basketball_TYPE, SportType_BASKETBALL),                                   \
        prefix(SPORTING_golf_TYPE, SportType_GOLF),                                               \
        prefix(SPORTING_Soccer_TYPE, SportType_FOOTBALL),                                         \
        prefix(SPORTING_volleyball_TYPE, SportType_VOLLEYBALL),                                   \
        prefix(SPORTING_baseball_TYPE, SportType_BASEBALL),                                       \
        prefix(SPORTING_softball_TYPE, SportType_SOFTBALL),                                       \
        prefix(SPORTING_Rugby_TYPE, SportType_RUGBY),                                             \
        prefix(SPORTING_hockey_TYPE, SportType_HOCKEY),                                           \
        prefix(SPORTING_pingpong_TYPE, SportType_PINGPONG),                                       \
        prefix(SPORTING_badminton_TYPE, SportType_BADMINTON),                                     \
        prefix(SPORTING_cricket_TYPE, SportType_CRICKET),                                         \
        prefix(SPORTING_Handball_TYPE, SportType_HANDBALL),                                       \
        prefix(SPORTING_bowling_TYPE, SportType_BOWLING),                                         \
        prefix(SPORTING_squash_TYPE, SportType_SQUASH),                                           \
        prefix(SPORTING_billiards_TYPE, SportType_BILLIARDS),                                     \
        prefix(SPORTING_Shuttlecock_TYPE, SportType_SHUTTLECOCK),                                 \
        prefix(SPORTING_beach_soccer_TYPE, SportType_BEACH_FOOTBALL),                             \
        prefix(SPORTING_beach_volleyball_TYPE, SportType_BEACH_VOLLEYBALL),                       \
        prefix(SPORTING_Sepak_Takraw_TYPE, SportType_SEPAK_TAKRAW),                               \
        prefix(SPORTING_indoor_football_TYPE, SportType_INDOOR_FOOTBALL),                         \
        prefix(SPORTING_sandbags_ball_TYPE, SportType_SANDBAGS_BALL),                             \
        prefix(SPORTING_bocci_TYPE, SportType_BOCCI),                                             \
        prefix(SPORTING_hihi_ball_TYPE, SportType_HIHI_BALL),                                     \
        prefix(SPORTING_gateball_TYPE, SportType_GATEBALL),                                       \
        prefix(SPORTING_dodgeball_TYPE, SportType_DODGEBALL),                                     \
        prefix(SPORTING_Snowboarding_TYPE, SportType_SNOWBOARDING),                               \
        prefix(SPORTING_Double_board_skiing_TYPE, SportType_DOUBLE_BOARD_SKIING),                 \
        prefix(SPORTING_cross_country_skiing_TYPE, SportType_CROSS_COUNTRY_SKIING),               \
        prefix(SPORTING_Outdoor_skating_TYPE, SportType_OUTDOOR_SKATING),                         \
        prefix(SPORTING_indoor__skating_TYPE, SportType_INDOOR__SKATING),                         \
        prefix(SPORTING_Curling_TYPE, SportType_CURLING),                                         \
        prefix(SPORTING_Snow_sports_TYPE, SportType_SNOW_SPORTS),                                 \
        prefix(SPORTING_Snowmobile_TYPE, SportType_SNOWMOBILE),                                   \
        prefix(SPORTING_puck_TYPE, SportType_PUCK),                                               \
        prefix(SPORTING_Snow_car_TYPE, SportType_SNOW_CAR),                                       \
        prefix(SPORTING_sled_TYPE, SportType_SLED),                                               \
        prefix(SPORTING_Archery_TYPE, SportType_ARCHERY),                                         \
        prefix(SPORTING_Darts_TYPE, SportType_DARTS),                                             \
        prefix(SPORTING_ride_horse_TYPE, SportType_HORSE_RIDING),                                 \
        prefix(SPORTING_Tug_of_war_TYPE, SportType_TUG_OF_WAR),                                   \
        prefix(SPORTING_Hula_Hoop_TYPE, SportType_HULA_HOOP),                                     \
        prefix(SPORTING_fly_a_kite_TYPE, SportType_FLY_KITE),                                     \
        prefix(SPORTING_fishing_TYPE, SportType_FISHING),                                         \
        prefix(SPORTING_Frisbee_TYPE, SportType_FRISBEE),                                         \
        prefix(SPORTING_shuttlecock_kicking_TYPE, SportType_SHUTTLECOCK_KICKING),                 \
        prefix(SPORTING_swing_TYPE, SportType_SWING),                                             \
        prefix(SPORTING_motion_sensing_game_TYPE, SportType_MOTION_SENSING_GAME),                 \
        prefix(SPORTING_foosball_TYPE, SportType_FOOSBALL),                                       \
        prefix(SPORTING_shuffle_ball_TYPE, SportType_SHUFFLE_BALL),                               \
        prefix(SPORTING_electronic_sports_TYPE, SportType_ELECTRONIC_SPORTS),                     \
        prefix(SPORTING_chess_TYPE, SportType_CHESS),                                             \
        prefix(SPORTING_draughts_TYPE, SportType_DRAUGHTS),                                       \
        prefix(SPORTING_weiqi_TYPE, SportType_WEIQI),                                             \
        prefix(SPORTING_bridge_TYPE, SportType_BRIDGE),                                           \
        prefix(SPORTING_board_games_TYPE, SportType_BOARD_GAMES),                                 \
        prefix(SPORTING_equesttrian_TYPE, SportType_EQUESTTRIAN),                                 \
        prefix(SPORTING_track_and_field_TYPE, SportType_TRACK_AND_FIELD),                         \
        prefix(SPORTING_racing_car_TYPE, SportType_RACING_CAR),
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
SportType pb_sport_type_trans(Sport_type local_sport_type)
{
    const SportType local_sport_type_arr[SPORTING_MAX_END_TYPE] =
        {
            MS_SPORT_TYPE_TABLE1(MS_T_CONVERT_DEF)};

    if (local_sport_type >= SPORTING_MAX_END_TYPE)
    {
        return local_sport_type_arr[0];
    }
    printf("%s %d %d\n",__func__,local_sport_type,local_sport_type_arr[local_sport_type]);
    return local_sport_type_arr[local_sport_type];
}
#endif

#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
uint32_t pb_sport_type_trans_to_local(SportType app_sport_type)
{
    const uint32_t local_sport_type_arr[SportType_RACING_CAR + 1] =
    {
         MS_SPORT_TYPE_TABLE1(MS_T_CONVERT_DEF_REV)};

    if (app_sport_type >= SportType_RACING_CAR + 1)
    {
    return local_sport_type_arr[0];
    }
    printf("%s %d %d\n",__func__,app_sport_type,local_sport_type_arr[app_sport_type]);
    return local_sport_type_arr[app_sport_type];
}
#endif
uint8_t Get_current_sporting_course_type(void)
{
    return sport_running_course.sport_course_type;
}
uint16_t sport_course_array[15] = {0};
void init_sport_course_somethings(Running_course_type type)
{
    memset(sport_course_array, 0, sizeof(sport_course_array));
    // 类型加时间组成16位
    //
    uint16_t course_class1[7 + 1] = {
// #if 0
        7 << 8 | 17,           // 总数+时间8次,17分钟
        Beat_It_Type << 8 | 2, // 快走2分钟类型+时间
        Jogging_Type << 8 | 3, // 慢跑3分钟
        Beat_It_Type << 8 | 2, // 快走2分钟
        Jogging_Type << 8 | 3, // 慢跑3分钟
        Beat_It_Type << 8 | 2, // 快走2分钟
        Jogging_Type << 8 | 3, // 慢跑3分钟
        Beat_It_Type << 8 | 2, // 快走2分钟
// #else//test
//         7 << 8 | 7,           // 总数+时间8次,17分钟
//         Beat_It_Type << 8 | 1, // 快走2分钟类型+时间
//         Jogging_Type << 8 | 1, // 慢跑3分钟
//         Beat_It_Type << 8 | 1, // 快走2分钟
//         Jogging_Type << 8 | 1, // 慢跑3分钟
//         Beat_It_Type << 8 | 1, // 快走2分钟
//         Jogging_Type << 8 | 1, // 慢跑3分钟
//         Beat_It_Type << 8 | 1, // 快走2分钟
// #endif
    };
    uint16_t course_class2[7 + 1] = {
        7 << 8 | 23,           // 总数+时间8次,23分钟
        Beat_It_Type << 8 | 2, // 快走2分钟
        Jogging_Type << 8 | 5, // 慢跑5分钟
        Beat_It_Type << 8 | 2, // 快走2分钟
        Jogging_Type << 8 | 5, // 慢跑5分钟
        Beat_It_Type << 8 | 2, // 快走2分钟
        Jogging_Type << 8 | 5, // 慢跑5分钟
        Beat_It_Type << 8 | 2, // 快走2分钟
    };
    uint16_t course_class3[3 + 1] = {
        3 << 8 | 27,            // 总数+时间
        Beat_It_Type << 8 | 3,  // 快走3分钟
        Jogging_Type << 8 | 21, // 慢跑21分钟
        Beat_It_Type << 8 | 3,  // 快走3分钟
    };
    uint16_t course_class4[3 + 1] = {
        3 << 8 | 35,            // 总数+时间
        Beat_It_Type << 8 | 3,  // 快走3分钟
        Jogging_Type << 8 | 30, // 慢跑30分钟
        Beat_It_Type << 8 | 2,  // 快走2分钟
    };
    uint16_t course_class5[3 + 1] = {
        3 << 8 | 45,            // 总数+时间
        Beat_It_Type << 8 | 3,  // 快走3分钟
        Jogging_Type << 8 | 40, // 慢跑40分钟
        Beat_It_Type << 8 | 2,  // 快走2分钟
    };
    uint16_t course_class6[10 + 1] = {
        10 << 8 | 36,                // 总数+时间
        Beat_It_Type << 8 | 2,       // 快走2分钟
        Jogging_Type << 8 | 3,       // 慢跑3分钟
        Moderate_pace_Type << 8 | 5, // 中速跑5分钟
        Jogging_Type << 8 | 3,       // 慢跑3分钟
        Moderate_pace_Type << 8 | 5, // 中速跑5分钟
        Jogging_Type << 8 | 3,       // 慢跑3分钟
        Moderate_pace_Type << 8 | 5, // 中速跑5分钟
        Jogging_Type << 8 | 3,       // 慢跑3分钟
        Moderate_pace_Type << 8 | 5, // 中速跑5分钟
        Beat_It_Type << 8 | 2,       // 快走2分钟
    };
    uint16_t course_class7[3 + 1] = {
        3 << 8 | 35,            // 总数+时间
        Beat_It_Type << 8 | 3,  // 快走3分钟
        Jogging_Type << 8 | 30, // 慢跑30分钟
        Beat_It_Type << 8 | 2,  // 快走2分钟
    };
    uint16_t course_class8[3 + 1] = {
        3 << 8 | 65,            // 总数+时间
        Beat_It_Type << 8 | 3,  // 快走3分钟
        Jogging_Type << 8 | 60, // 慢跑60分钟
        Beat_It_Type << 8 | 2,  // 快走2分钟
    };
    uint16_t course_class9[11 + 1] = {
        11 << 8 | 28,           // 总数+时间
        Beat_It_Type << 8 | 3,  // 快走3分钟
        Run_Fast_Type << 8 | 3, // 快跑3分钟
        Jogging_Type << 8 | 2,  // 慢跑2分钟
        Run_Fast_Type << 8 | 3, // 快跑3分钟
        Jogging_Type << 8 | 2,  // 慢跑2分钟
        Run_Fast_Type << 8 | 3, // 快跑3分钟
        Jogging_Type << 8 | 2,  // 慢跑2分钟
        Run_Fast_Type << 8 | 3, // 快跑3分钟
        Jogging_Type << 8 | 2,  // 慢跑2分钟
        Run_Fast_Type << 8 | 3, // 快跑3分钟
        Beat_It_Type << 8 | 2,  // 快走2分钟
    };
    uint16_t course_class10[11 + 1] = {
        11 << 8 | 38,           // 总数+时间
        Beat_It_Type << 8 | 3,  // 快走3分钟
        Run_Fast_Type << 8 | 5, // 快跑5分钟
        Jogging_Type << 8 | 2,  // 慢跑2分钟
        Run_Fast_Type << 8 | 5, // 快跑5分钟
        Jogging_Type << 8 | 2,  // 慢跑2分钟
        Run_Fast_Type << 8 | 5, // 快跑5分钟
        Jogging_Type << 8 | 2,  // 慢跑2分钟
        Run_Fast_Type << 8 | 5, // 快跑5分钟
        Jogging_Type << 8 | 2,  // 慢跑2分钟
        Run_Fast_Type << 8 | 5, // 快跑5分钟
        Beat_It_Type << 8 | 2,  // 快走2分钟
    };
    switch (type)
    {
    case Combining_Basic_Running_Walking: // 基础跑走结合
        memcpy(sport_course_array, course_class1, sizeof(course_class1));
        break;
    case Advanced_Running_Walking_Combination: // 进阶跑走结合
        memcpy(sport_course_array, course_class2, sizeof(course_class2));
        break;
    case Basic_Jogging: // 基础慢跑
        memcpy(sport_course_array, course_class3, sizeof(course_class3));
        break;
    case Basic_Fuel_Running: // 基础燃脂跑
        memcpy(sport_course_array, course_class4, sizeof(course_class4));
        break;
    case Advanced_Fat_Burning_Run: // 进阶燃脂跑
        memcpy(sport_course_array, course_class5, sizeof(course_class5));
        break;
    case MIIT_Fuel_Run: // MIIT 燃脂跑
        memcpy(sport_course_array, course_class6, sizeof(course_class6));
        break;
    case Basic_Aerobic_Endurance_Run: // 基础有氧耐力跑
        memcpy(sport_course_array, course_class7, sizeof(course_class7));
        break;
    case Advanced_Aerobic_Endurance_Run: // 基础有氧耐力跑
        memcpy(sport_course_array, course_class8, sizeof(course_class8));
        break;
    case Basic_Interval_Running: // 基础间歇跑
        memcpy(sport_course_array, course_class9, sizeof(course_class9));
        break;
    case Advanced_Interval_Running: // 基础间歇跑
        memcpy(sport_course_array, course_class10, sizeof(course_class10));
        break;
    default:
        break;
    }
    switch (type)
    {
    case Combining_Basic_Running_Walking:      // 基础跑走结合
    case Advanced_Running_Walking_Combination: // 进阶跑走结合
    case Basic_Jogging:                        // 基础慢跑
    case Basic_Fuel_Running:                   // 基础燃脂跑
    case Advanced_Fat_Burning_Run:             // 进阶燃脂跑
    case MIIT_Fuel_Run:                        // MIIT 燃脂跑
    case Basic_Aerobic_Endurance_Run:          // 基础有氧耐力跑
    case Advanced_Aerobic_Endurance_Run:       // 基础有氧耐力跑
    case Basic_Interval_Running:               // 基础间歇跑
    case Advanced_Interval_Running:            // 基础间歇跑
    {
        sport_running_course.sport_course_type = type;
        sport_running_course.current_subsection = 1;
        sport_running_course.total_subsection = (sport_course_array[0]) >> 8;
        sport_running_course.total_time_count = ((sport_course_array[0]) & 0xff) * 60;
        sport_running_course.current_course_time_count = 0;
        sport_running_course.total_course_time_count = ((sport_course_array[sport_running_course.current_subsection]) & 0xff) * 60;
        sport_running_course.current_sub_type = (sport_course_array[sport_running_course.current_subsection]) >> 8;
    }
    break;
    default:
        break;
    }
    for(uint8_t i = 0; i < 15; i++)
    {
        printf("sport_course_array:i:%d,0x%x\n",i,sport_course_array[i]);
    }
     printf("sport_course_type:%d,current_subsection:%d,total_course_time_count:%d\n",sport_running_course.sport_course_type,
     sport_running_course.current_subsection,sport_running_course.total_course_time_count);
        for(uint8_t j = 1; j < sport_running_course.total_subsection+1; j++)
        {

            printf("j:%d,total_subsection:%d,to_time:%d,sub_type:%d,time:%d\n",j,sport_running_course.total_subsection,sport_running_course.total_time_count,(sport_course_array[j])>>8,(sport_course_array[j])&0xff);

        }
}

extern int miwear_sport_request(uint8_t cmd, uint16_t sport_type);
extern SPORT_HEART_RATE_INFO_STRU heart_range_info;
extern uint8_t get_avr_heartRate(void);
extern void clearheart5second(void);
Sport_Remind_Type sport_remind_struct =
    {
        .sport_timecount1 = 0,
        .sport_timecount2 = 0,
        .sport_timecount3 = 0,
        .sport_timedelay1 = 0,
        .sport_timedelay2 = 0,
        .sport_timedelay3 = 0,
        .sport_time1_switch = 0,
        .sport_time2_switch = 0,
        .sport_time3_switch = 0,
        .sport_high_low_switch = 0,
        .sport_hr_timeout = 0,
        .sport_hr_timedelay = 0,
};
_Sport_interval_training_type sport_interval_training =
    {
        .completion_times = 0,
        .total_times = 0,
        .current_time_count = 0,
        .total_time_count = 5 * 60,
        .current_distance = 0,
        .total_distance = 0,
        .mode = 0,
        .segment_kcal = 0,
};
Sport_Running_Course_Type sport_running_course =
    {
        .current_subsection = 0,
        .sport_course_type = 1,
        .current_sub_type = 1,
        .total_time_count = 0,
        .total_subsection = 0,
        .current_course_time_count = 0,
};
bool module_ms_sport_app_is_frist_page(uint16_t sport_type) // 判断运动是否在首页
{
#if ENUM_PROJECT_NAME_N65B_GLOBAL
    uint8_t max = 8;
#else
    uint8_t max = 7;
#endif
    for (uint8_t i = 0; i < max; i++)
    {
        if (sport_list_sort_array[i].sport_type == sport_type)
        {
            return true;
        }
    }
    return false;
}
uint8_t module_ms_sport_app_get_group(uint16_t sport_type, bool init)
{
    uint8_t group = 3;
    if (module_ms_sport_app_is_frist_page(sport_type) && !init)
    {
        group = 0;
        return group;
    }
    switch (sport_type)
    {
    //  泳池游泳,开放水域游泳,帆船, 桨板, 水球,水上运动, 滑水, 皮划艇, 皮艇漂流, 划船, 摩托艇, 蹼泳, 跳水, 花样游泳, 浮潜,风筝冲浪, 室内冲浪,龙舟
    case SPORTING_swim_indoor_TYPE:    // 泳池游泳 新增
    case SPORTING_swim_outdoor_TYPE:   // 开放水域游泳 新增
    case SPORTING_sailboat_TYPE:       // 帆船 新增
    case SPORTING_paddle_board_TYPE:   // 桨板 新增
    case SPORTING_water_polo_TYPE:     // 水球 新增
    case SPORTING_aquatic_sport_TYPE:  // 水上运动 新增
    case SPORTING_surfing_TYPE:        // 滑水 新增
    case SPORTING_canoeing_TYPE:       // 皮划艇 新增
    case SPORTING_kayak_rafting_TYPE:  // 皮艇漂流 新增
    case SPORTING_rowing_TYPE:         // 划船 新增
    case SPORTING_motorboat_TYPE:      // 摩托艇 新增
    case SPORTING_web_swimming_TYPE:   // 蹼泳 新增
    case SPORTING_driving_TYPE:        // 跳水 新增
    case SPORTING_fancy_swimming_TYPE: // 花样游泳 新增
    case SPORTING_snorkeling_TYPE:     // 浮潜 新增
    case SPORTING_kite_surfing_TYPE:   // 风筝冲浪 新增
    case SPORTING_indoor_surfing_TYPE: // 室内冲浪 新增
    case SPORTING_dragon_boat_TYPE:    // 龙舟 新增
        group = 1;
        break;
        // 户外跑步,健走,徒步,户外骑行,登山,越野,铁人三项,攀岩,滑板,轮滑,跑酷,沙滩车,滑翔伞,小轮车,竞走
    case SPORTING_Outdoor_running_TYPE: // 户外跑步
    case SPORTING_Outdoor_walking_TYPE: // 户外健走
    case SPORTING_Outdoor_hiking_TYPE:  // 户外徒步
    case SPORTING_Outdoor_cycling_TYPE: // 户外骑行
    case SPORTING_Mountaineering_TYPE:  // 登山
    case SPORTING_Off_road_TYPE:        // 越野
    // case SPORT_triathlon_TYPE:          // 铁人三项 新增
    case SPORTING_rock_climbing_TYPE:  // 攀岩
    case SPORTING_skateboard_TYPE:     // 滑板
    case SPORTING_Roller_skating_TYPE: // 轮滑
    case SPORTING_Parkour_TYPE:        // 跑酷
    case SPORTING_ATV_TYPE:            // 沙滩车
    case SPORTING_Paraglider_TYPE:     // 滑翔伞
    case SPORTING_bicycle_moto_TYPE:   // 小轮车 新增
    case SPORTING_heel_and_toe_TYPE:   // 竞走 新增
        group = 2;
        break;
    // 自由活动,室内跑步,跳绳,高强度间歇训练,瑜伽,室内单车,椭圆机,划船机,爬楼机,踏步机,动感单车,核心训练,柔韧训练,普拉提,体操,拉伸,力量训练,交叉训练,爬楼梯,健身操,体能训练,墙球,哑铃训练,杠铃训练,举重,硬拉,波比跳,仰卧起坐,功能性训练,上肢训练,下肢训练,腰腹训练,背部训练,漫步机,单杠,双杠,踏步训练,团体操,搏击操,战绳,混合有氧,室内步行,室内健身
    case SPORTING_free_activity_TYPE:                    // 自由活动
    case SPORTING_Indoor_running_TYPE:                   // 室内跑步
    case SPORTING_Skipping_rope_H_TYPE:                  // 跳绳
    case SPORTING_High_intensity_interval_training_TYPE: // 高强度间歇训练
    case SPORTING_Yoga_TYPE:                             // 瑜伽
    case SPORTING_Indoor_cycling_TYPE:                   // 室内单车
    case SPORTING_Elliptical_machine_TYPE:               // 椭圆机
    case SPORTING_Rowing_machine_TYPE:                   // 划船机
    case SPORTING_Climbing_machine_TYPE:                 // 爬楼机
    case SPORTING_Stepper_TYPE:                          // 踏步机
    case SPORTING_spinning_TYPE:                         // 动感单车 新增
    case SPORTING_Core_training_TYPE:                    // 核心训练
    case SPORTING_Flexibility_training_TYPE:             // 柔韧训练
    case SPORTING_Pilates_TYPE:                          // 普拉提
    case SPORTING_gymnastics_TYPE:                       // 体操
    case SPORTING_Stretch_TYPE:                          // 拉伸
    case SPORTING_Strength_Training_TYPE:                // 力量训练
    case SPORTING_Cross_training_CrossFit_TYPE:          // 交叉训练CrossFit
    case SPORTING_Climb_the_stairs_TYPE:                 // 爬楼梯
    case SPORTING_Aerobics_TYPE:                         // 健身操
    case SPORTING_Physical_Training_TYPE:                // 体能训练
    case SPORTING_Wall_ball_TYPE:                        // 墙球
    case SPORTING_Dumbbell_training_TYPE:                // 哑铃训练
    case SPORTING_Barbell_training_TYPE:                 // 杠铃训练
    case PORTING_weightlifting_TYPE:                     // 举重
    case SPORTING_Deadlift_TYPE:                         // 硬拉
    case SPORTING_Bobby_Jump_TYPE:                       // 波比跳
    case SPORTING_Sit_ups_TYPE:                          // 仰卧起坐
    case SPORTING_Functional_training_TYPE:              // 功能性训练
    case SPORTING_Upper_limb_training_TYPE:              // 上肢训练
    case SPORTING_Lower_limb_training_TYPE:              // 下肢训练
    case SPORTING_Waist_and_abdomen_training_TYPE:       // 腰腹训练
    case SPORTING_Back_training_TYPE:                    // 背部训练
    case SPORTING_walking_machine_TYPE:                  // 漫步机 新增
    case SPORTING_single_bar_TYPE:                       // 单杠 新增
    case SPORTING_parallel_bars_TYPE:                    // 双杠 新增
    case SPORTING_step_training_TYPE:                    // 踏步训练 新增
    case SPORTING_group_callisthenics_TYPE:              // 团体操 新增
    case SPORTING_strike_TYPE:                           // 搏击操 新增
    case SPORTING_battle_rope_TYPE:                      // 战绳 新增
    case SPORTING_mixed_aerobic_TYPE:                    // 混合有氧 新增
    case SPORTING_walk_indoor_TYPE:                      // 室内步行 新增
    case SPORTING_gym_TYPE:                              // 室内健身 新增
        group = 3;
        break;
    // 广场舞,肚皮舞,芭蕾舞,街舞,尊巴,民族舞,爵士舞,拉丁舞,嘻哈舞,钢管舞,霹雳舞,交际舞,现代舞,舞蹈
    case SPORTING_Square_dance_TYPE:   // 广场舞
    case SPORTING_Belly_dance_TYPE:    // 肚皮舞
    case SPORTING_ballet_TYPE:         // 芭蕾舞
    case SPORTING_Street_dance_TYPE:   // 街舞
    case SPORTING_Zumba_TYPE:          // 尊巴
    case SPORTING_National_dance_TYPE: // 民族舞
    case SPORTING_Jazz_TYPE:           // 爵士舞
    case SPORTING_Latin_Dance_TYPE:    // 拉丁舞
    case SPORTING_hip_hop_dance_TYPE:  // 嘻哈舞 新增
    case SPORTING_pole_dance_TYPE:     // 钢管舞 新增
    case SPORTING_breakdancing_TYPE:   // 霹雳舞 新增
    case SPORTING_social_dancing_TYPE: // 交际舞 新增
    case SPORTING_modern_dancing_TYPE: // 现代舞 新增
    case SPORTING_dance_TYPE:          // 舞蹈
        group = 4;
        break;
    // 拳击,摔跤,武术,太极,泰拳,柔道,跆拳道,空手道,自由搏击,剑术/剑道,击剑,柔术
    case SPORTING_boxing_TYPE:           // 拳击
    case SPORTING_Wrestling_TYPE:        // 摔跤
    case SPORTING_Martial_arts_TYPE:     // 武术
    case SPORTING_Tai_Chi_TYPE:          // 太极
    case SPORTING_Muay_Thai_TYPE:        // 泰拳
    case SPORTING_judo_TYPE:             // 柔道
    case SPORTING_Taekwondo_TYPE:        // 跆拳道
    case SPORTING_karate_TYPE:           // 空手道
    case SPORTING_free_sparring_TYPE:    // 自由搏击
    case SPORTING_fencing_movement_TYPE: // 剑术
    case SPORTING_fencing_TYPE:          // 击剑
    case SPORTING_jujitsu_TYPE:          // 柔术 新增
        group = 5;
        break;
    // 网球,篮球,高尔夫球,足球,排球,棒球,垒球,橄榄球,曲棍球,乒乓球,羽毛球,板球,手球,保龄球,壁球,台球,毽球,沙滩足球,沙滩排球,藤球,室内足球,沙包球,地掷球,回力球,门球,躲避球
    case SPORTING_tennis_TYPE:           // 网球
    case SPORTING_basketball_TYPE:       // 篮球
    case SPORTING_golf_TYPE:             // 高尔夫
    case SPORTING_Soccer_TYPE:           // 足球
    case SPORTING_volleyball_TYPE:       // 排球
    case SPORTING_baseball_TYPE:         // 棒球
    case SPORTING_softball_TYPE:         // 垒球
    case SPORTING_Rugby_TYPE:            // 橄榄球
    case SPORTING_hockey_TYPE:           // 曲棍球
    case SPORTING_pingpong_TYPE:         // 乒乓球
    case SPORTING_badminton_TYPE:        // 羽毛球
    case SPORTING_cricket_TYPE:          // 板球
    case SPORTING_Handball_TYPE:         // 手球
    case SPORTING_bowling_TYPE:          // 保龄球
    case SPORTING_squash_TYPE:           // 壁球
    case SPORTING_billiards_TYPE:        // 台球
    case SPORTING_Shuttlecock_TYPE:      // 毽球
    case SPORTING_beach_soccer_TYPE:     // 沙滩足球
    case SPORTING_beach_volleyball_TYPE: // 沙滩排球
    case SPORTING_Sepak_Takraw_TYPE:     // 藤球
    case SPORTING_indoor_football_TYPE:  // 室内足球 新增
    case SPORTING_sandbags_ball_TYPE:    // 沙包球 新增
    case SPORTING_bocci_TYPE:            // 地掷球 新增
    case SPORTING_hihi_ball_TYPE:        // 回力球 新增
    case SPORTING_gateball_TYPE:         // 门球 新增
    case SPORTING_dodgeball_TYPE:        // 躲避球 新增
        group = 6;
        break;
    // 单板滑雪,双板滑雪,越野滑雪,户外滑冰,室内滑冰,冰壶,雪上运动,雪地摩托,冰球,雪车,雪橇
    case SPORTING_Snowboarding_TYPE:         // 单板滑雪
    case SPORTING_Double_board_skiing_TYPE:  // 双板滑雪
    case SPORTING_cross_country_skiing_TYPE: // 越野滑雪 新增
    case SPORTING_Outdoor_skating_TYPE:      // 户外滑冰
    case SPORTING_indoor__skating_TYPE:      // 室内滑冰 新增
    case SPORTING_Curling_TYPE:              // 冰壶
    case SPORTING_Snow_sports_TYPE:          // 雪上运动
    case SPORTING_Snowmobile_TYPE:           // 雪地摩托
    case SPORTING_puck_TYPE:                 // 冰球
    case SPORTING_Snow_car_TYPE:             // 雪车
    case SPORTING_sled_TYPE:                 // 雪橇
        group = 7;
        break;
    // 射箭,飞镖,骑马,拔河,呼啦圈,放风筝,钓鱼,飞盘,踢毽子,秋千,体感游戏,桌上足球,沙狐球,电子竞技
    case SPORTING_Archery_TYPE:             // 射箭
    case SPORTING_Darts_TYPE:               // 飞镖
    case SPORTING_ride_horse_TYPE:          // 骑马
    case SPORTING_Tug_of_war_TYPE:          // 拔河
    case SPORTING_Hula_Hoop_TYPE:           // 呼啦圈
    case SPORTING_fly_a_kite_TYPE:          // 放风筝
    case SPORTING_fishing_TYPE:             // 钓鱼
    case SPORTING_Frisbee_TYPE:             // 飞盘
    case SPORTING_shuttlecock_kicking_TYPE: // 踢毽子 新增
    case SPORTING_swing_TYPE:               // 秋千 新增
    case SPORTING_motion_sensing_game_TYPE: // 体感游戏 新增
    case SPORTING_foosball_TYPE:            // 桌上足球 新增
    case SPORTING_shuffle_ball_TYPE:        // 沙狐球 新增
    case SPORTING_electronic_sports_TYPE:   // 电子竞技 新增
        group = 8;
        break;
        // 国际象棋,国际跳棋,围棋,桥牌,桌游
    case SPORTING_chess_TYPE:       // 国际象棋 新增
    case SPORTING_draughts_TYPE:    // 国际跳棋 新增
    case SPORTING_weiqi_TYPE:       // 围棋 新增
    case SPORTING_bridge_TYPE:      // 桥牌 新增
    case SPORTING_board_games_TYPE: // 桌游 新增
        group = 9;
        break;
    default:
        // 马术,田径,赛车
        group = 10;
        break;
    }
    return group;
}
void auto_sport_ctrl_init(uint16_t dis_time)
{
    misc_sport_data.auto_sport_ctrl.sport_state = 0;
    misc_sport_data.auto_sport_ctrl.sport_type = 0;
    misc_sport_data.auto_sport_ctrl.time_cnt = 0;
    misc_sport_data.auto_sport_ctrl.sport_disable = dis_time;
}
bool module_ms_app_is_distance_sport_type(Sport_type sport_type)
{
    bool ret_flag = false;

    switch (sport_type)
    {
    /* porting start */
    case SPORTING_Outdoor_running_TYPE: // 跑步
    case SPORTING_Outdoor_walking_TYPE: // 健走
    case SPORTING_Outdoor_hiking_TYPE:  // 徒步
    case SPORTING_Off_road_TYPE:        // 越野
    case SPORTING_Mountaineering_TYPE:  // 登山:
    case SPORTING_Outdoor_cycling_TYPE: // 户外骑行
    case SPORTING_Indoor_running_TYPE:  // 室内跑步
#if 0
    case SPORTING_Snowboarding_TYPE:    //单板滑雪 84
    case  SPORTING_Double_board_skiing_TYPE://双板滑雪   85
#endif
        ret_flag = true;
        break;

    default:
        ret_flag = false;
        break;
    }

    return ret_flag;
}
bool module_ms_app_is_gps_sport_type(Sport_type sport_type)
{
    bool ret_flag = false;

    switch (sport_type)
    {
    /* porting start */
    case SPORTING_Outdoor_running_TYPE: // 跑步
    case SPORTING_Outdoor_walking_TYPE: // 健走
    case SPORTING_Outdoor_hiking_TYPE:  // 徒步
    case SPORTING_Off_road_TYPE:        // 越野
    case SPORTING_Mountaineering_TYPE:  // 登山:
    //  case SPORT_SKATEBOARDING:
    case SPORTING_swim_outdoor_TYPE:    //开放水域游泳
    case SPORTING_Outdoor_cycling_TYPE: // 户外骑行
        //   case SPORT_INDOOR_RUN:
        /* porting end */
        ret_flag = true;
        break;

    default:
        ret_flag = false;
        break;
    }

    return ret_flag;
}
/**
 * @Function name: module_ms_app_get_list_type_array
 * @Descripttion: 运动列表获取该列表要显示的所有类型
 * @param {type} page_index: 列表index，具体参照sport_list_sort_array[i].sport_gourp
 * @param {type} p_buff: 显示内容的数组里面为运动类型
 * @param {type} len:p_buff长度
 * @return: 显示的个数
 * @LastEditTime: Do not Edit
 */
uint8_t module_ms_app_get_list_type_array(uint8_t page_index, uint8_t *p_buff, uint16_t buff_len)
{
#if ENUM_PROJECT_NAME_N65B_GLOBAL
#define MAX 8
#else
#define MAX 7
#endif
    uint8_t *p = NULL;
    uint8_t p_buff_len = buff_len;
    uint8_t count = 0;
    switch (page_index)
    {
    case 0:
        if (p_buff_len >= MAX)
        {
            for (uint8_t i = 0; i < MAX + 1; i++)
            {
                p_buff[i] = sport_list_sort_array[i].sport_type;
            }
            count = MAX;
        }
        break;
    default:
    {
        p = p_buff;
        for (uint16_t i = 0; i < SPORTING_MORE; i++)
        {
            if (module_ms_sport_app_get_group(sport_list_sort_array[i].sport_type, 0) == page_index)
            {
                *p = sport_list_sort_array[i].sport_type;
                count++;
                if (count < p_buff_len - 1)
                {
                    p++;
                }
                else
                {
                    break;
                }
            }
        }
    }
    break;
    }
    for(uint8_t i = 0; i < count; i++)
    {
        for(uint8_t j = i+1; j < count; j++)
        {
            if(p_buff[i] == p_buff[j])
            {
                printf("read sport list faild\n");
                init_app_sports_list_data();//初始化排序结构
            }
        }
    }
    return count;
}
/**
 * @Function name: module_ms_app_get_list_type_array
 * @Descripttion: 运动列表获取该列表要显示的所有类型
 * @param {type} page_index: 列表index，具体参照sport_list_sort_array[i].sport_gourp
 * @param {type} p_buff: 显示内容的数组里面为运动类型
 * @param {type} len:p_buff长度
 * @return: 显示的个数
 * @LastEditTime: Do not Edit
 */
uint8_t module_ms_app_get_running_course_type_array(uint8_t *p_buff, uint16_t buff_len)
{
#if ENUM_PROJECT_NAME_N65B_GLOBAL
#endif
    uint8_t *p = NULL;
    uint8_t p_buff_len = buff_len;
    uint8_t count = 0;
        p = p_buff;
        for (uint16_t i = 0; i < Advanced_Interval_Running; i++)
        {
                *p = sport_course.sport_course_list[i].sport_type;
                count++;
                p++;
        }
    bool flag = false;
    for(uint8_t i = 0; i < count; i++)
    {
        for(uint8_t j = i+1; j < count; j++)
        {
            if(p_buff[i] == p_buff[j])
            {
                printf("read running course faild\n");
                init_app_sports_course_data();//初始化课程排序结构
                flag = true;
                goto reload;
            }
        }
    }
reload:
{

}
    if(flag)
    {
        p = p_buff;
        for (uint16_t i = 0; i < Advanced_Interval_Running; i++)
        {
                *p = sport_course.sport_course_list[i].sport_type;
                count++;
                p++;
        }
    }
    for(uint8_t i = 0; i < buff_len; i++)
    {
        printf("---------course:%d,i:%d,%d\n",p_buff[i],i,sport_course.sport_course_list[i].sport_type);
    }
    return count;
}
void module_ms_app_set_sport_running_course_usecount(uint16_t sport_sub_type) // 使用后加1
{
    int i, j;
    for (i = 0; i < Advanced_Interval_Running; i++) // 使用次数赋值
    {
        if (sport_sub_type == sport_course.sport_course_list[i].sport_type)
        {
            sport_course.sport_course_list[i].use_count++;
        }
    }
    for (i = 0; i < Advanced_Interval_Running - 1; i++) // 排序
    {
        for (j = 0; j < Advanced_Interval_Running - 1 - i; j++)
        {
            if (sport_course.sport_course_list[j].use_count < sport_course.sport_course_list[j + 1].use_count||
           (sport_course.sport_course_list[j].use_count == sport_course.sport_course_list[j + 1].use_count&&sport_course.sport_course_list[j].base_index>
           sport_course.sport_course_list[j+1].base_index))
            {
                _user_sport_course_type temp = sport_course.sport_course_list[j];
                sport_course.sport_course_list[j] = sport_course.sport_course_list[j + 1];
                sport_course.sport_course_list[j + 1] = temp;
            }
        }
    }
    for(uint8_t i = 0; i < Advanced_Interval_Running; i++)
    {
        printf("course:,i:%d,%d,use_cout:%d,base:%d\n",i,sport_course.sport_course_list[i].sport_type,
        sport_course.sport_course_list[i].use_count,sport_course.sport_course_list[i].base_index);
    }
}
void module_ms_app_set_sport_list_usecount(uint16_t sport_type) // 使用后加1
{
    int i, j;
    // for (i = 0; i < SPORTING_MORE; i++) // test
    // {
    //     sport_list_sort_array[i].sport_gourp = rand() % 9;
    //     sport_list_sort_array[i].sport_type = i;
    //     sport_list_sort_array[i].sport_use_count = rand() % 9;
    //     sport_list_sort_array[i].sport_index = rand() % 9;
    // }
    for (i = 0; i < SPORTING_MORE; i++) // 使用次数赋值
    {
        if (sport_type == sport_list_sort_array[i].sport_type)
        {
            sport_list_sort_array[i].sport_use_count++;
        }
    }
    for (i = 0; i < SPORTING_MORE - 1; i++) // 排序
    {
        for (j = 0; j < SPORTING_MORE - 1 - i; j++)
        {
            if (sport_list_sort_array[j].sport_use_count < sport_list_sort_array[j + 1].sport_use_count)//TODO一样的时候判断基础位置
            {
                user_sport_list_type_t temp = sport_list_sort_array[j];
                sport_list_sort_array[j] = sport_list_sort_array[j + 1];
                sport_list_sort_array[j + 1] = temp;
            }
            if (sport_list_sort_array[j].sport_use_count == sport_list_sort_array[j + 1].sport_use_count && \
            sport_list_sort_array[j].sport_type > sport_list_sort_array[j + 1].sport_type) //使用频次一样，基础位置靠前在前面
            {
                user_sport_list_type_t temp = sport_list_sort_array[j];
                sport_list_sort_array[j] = sport_list_sort_array[j + 1];
                sport_list_sort_array[j + 1] = temp;
            }
        }
    }
    // for (i = 0; i < SPORTING_MORE; i++) // 序号重新赋值
    // {
    //     sport_list_sort_array[i].sport_index = i;
    // }

        // for (i = 0; i < SPORTING_MORE; i++)
        // {
        //     printf("i:%d,sport_gourp:%d,sport_index:%d,sport_type:%d,sport_use_count:%d\n", i, sport_list_sort_array[i].sport_gourp, sport_list_sort_array[i].sport_index, sport_list_sort_array[i].sport_type, sport_list_sort_array[i].sport_use_count);
        // }
    //     uint8_t buff[50] = {0};
    //     uint16_t buff_size = 50;
    //     memset(buff, 0, sizeof(buff));
    //     uint8_t count  = 0;
    //     count  =module_ms_app_get_list_type_array(0, buff, &buff_size);
    //     for (uint8_t i = 0; i < count; i++)
    //     {
    //         printf("group0:i:%d,type:%d,total:%d\n", i, buff[i], buff_size);
    //     }
    //     buff_size = 50;
    //     memset(buff, 0, sizeof(buff));
    //     count  =module_ms_app_get_list_type_array(1, buff, &buff_size);
    //     for (uint8_t i = 0; i < count; i++)
    //     {
    //         printf("group1:i:%d,type:%d,total:%d\n", i, buff[i], buff_size);
    //     }
    //     buff_size = 50;
    //     memset(buff, 0, sizeof(buff));
    //     count  =module_ms_app_get_list_type_array(2, buff, &buff_size);
    //     for (uint8_t i = 0; i < count; i++)
    //     {
    //         printf("group2:i:%d,type:%d,total:%d\n", i, buff[i], buff_size);
    //     }
    //     buff_size = 50;
    //     memset(buff, 0, sizeof(buff));
    //     count  =module_ms_app_get_list_type_array(3, buff, &buff_size);
    //     for (uint8_t i = 0; i < count; i++)
    //     {
    //         printf("group3:i:%d,type:%d,total:%d\n", i, buff[i], buff_size);
    //     }
    //     buff_size = 50;
    //     memset(buff, 0, sizeof(buff));
    //     count  =module_ms_app_get_list_type_array(4, buff, &buff_size);
    //     for (uint8_t i = 0; i < count; i++)
    //     {
    //         printf("group4:i:%d,type:%d,total:%d\n", i, buff[i], buff_size);
    //     }
    //     buff_size = 50;
    //     memset(buff, 0, sizeof(buff));
    //     count  =module_ms_app_get_list_type_array(5, buff, &buff_size);
    //     for (uint8_t i = 0; i < count; i++)
    //     {
    //         printf("group5:i:%d,type:%d,total:%d\n", i, buff[i], buff_size);
    //     }
    //     buff_size = 50;
    //     memset(buff, 0, sizeof(buff));
    //     count  =module_ms_app_get_list_type_array(6, buff, &buff_size);
    //     for (uint8_t i = 0; i < count; i++)
    //     {
    //         printf("group6:i:%d,type:%d,total:%d\n", i, buff[i], buff_size);
    //     }
    //     buff_size = 50;
    //     memset(buff, 0, sizeof(buff));
    //     count  =module_ms_app_get_list_type_array(7, buff, &buff_size);
    //     for (uint8_t i = 0; i < count; i++)
    //     {
    //         printf("group7:i:%d,type:%d,total:%d\n", i, buff[i], buff_size);
    //     }
    //     buff_size = 50;
    //     memset(buff, 0, sizeof(buff));
    //     count  =module_ms_app_get_list_type_array(8, buff, &buff_size);
    //     for (uint8_t i = 0; i < count; i++)
    //     {
    //         printf("group8:i:%d,type:%d,total:%d\n", i, buff[i], buff_size);
    //     }
    //     buff_size = 50;
    //     memset(buff, 0, sizeof(buff));
    //    count  = module_ms_app_get_list_type_array(9, buff, &buff_size);
    //     for (uint8_t i = 0; i < count; i++)
    //     {
    //         printf("group9:i:%d,type:%d,total:%d\n", i, buff[i], buff_size);
    //     }
    //     buff_size = 50;
    //     memset(buff, 0, sizeof(buff));
    //     count  =module_ms_app_get_list_type_array(10, buff, &buff_size);
    //     for (uint8_t i = 0; i < count; i++)
    //     {
    //         printf("group10:i:%d,type:%d,total:%d\n", i, buff[i], buff_size);
    //     }
}
void module_ms_app_clear_base_sport_obj(void)
{
    memset(&misc_sport_data.sport_base_data, 0, sizeof(misc_sport_data.sport_base_data));
}
static bool up_load_flag = false;
void module_ms_app_set_upload_flag(bool flag)
{
    up_load_flag = flag;
}
bool module_ms_app_get_upload_flag()
{
    return up_load_flag;
}
bool module_mul_sport_set_best_points(uint16_t sport_type)
{
#ifndef BSP_USING_PC_SIMULATOR
    if (sport_type == SPORTING_Outdoor_running_TYPE)
    {
        if (Sport_Best_Data[BEST_OUTDOOR_RUNNING].duration + 120 <= sport_save_data.sport_time_count)
        {
            Sport_Best_Data[BEST_OUTDOOR_RUNNING].duration = sport_save_data.sport_time_count;
        }
        if (Sport_Best_Data[BEST_OUTDOOR_RUNNING].distance + 100 <= sport_save_data.sport_distance)
        {
            Sport_Best_Data[BEST_OUTDOOR_RUNNING].distance = sport_save_data.sport_distance;
        }
        Sport_Best_Data[BEST_OUTDOOR_RUNNING].sport_type = sport_type;
        printf("[best_point]outdoor_running>>> duration:%d,distance:%d,type:%d\n", Sport_Best_Data[BEST_OUTDOOR_RUNNING].duration,
                      Sport_Best_Data[BEST_OUTDOOR_RUNNING].distance, Sport_Best_Data[BEST_OUTDOOR_RUNNING].sport_type);
        return true;
    }
    else if (sport_type == SPORTING_Outdoor_walking_TYPE)
    {

        if (Sport_Best_Data[BEST_OUTDOOR_WALK].duration + 120 <= sport_save_data.sport_time_count)
        {
            Sport_Best_Data[BEST_OUTDOOR_WALK].duration = sport_save_data.sport_time_count;
        }
        if (Sport_Best_Data[BEST_OUTDOOR_WALK].distance + 100 <= sport_save_data.sport_distance)
        {
            Sport_Best_Data[BEST_OUTDOOR_WALK].distance = sport_save_data.sport_distance;
        }
        Sport_Best_Data[BEST_OUTDOOR_WALK].sport_type = sport_type;
        printf("[best_point]Outdoor_walking>>> duration:%d,distance:%d,type:%d\n", Sport_Best_Data[BEST_OUTDOOR_WALK].duration,
                      Sport_Best_Data[BEST_OUTDOOR_WALK].distance, Sport_Best_Data[BEST_OUTDOOR_WALK].sport_type);
    }
    else if (SPORTING_Outdoor_cycling_TYPE == sport_type)
    {

        if (Sport_Best_Data[BEST_OUTDOOR_CYCLING].duration + 120 <= sport_save_data.sport_time_count)
        {
            Sport_Best_Data[BEST_OUTDOOR_CYCLING].duration = sport_save_data.sport_time_count;
        }
        if (Sport_Best_Data[BEST_OUTDOOR_CYCLING].distance + 100 <= sport_save_data.sport_distance)
        {
            Sport_Best_Data[BEST_OUTDOOR_CYCLING].distance = sport_save_data.sport_distance;
        }
        Sport_Best_Data[BEST_OUTDOOR_CYCLING].sport_type = sport_type;
        printf("[best_point]Outdoor_cycling>>> duration:%d,distance:%d,type:%d\n", Sport_Best_Data[BEST_OUTDOOR_CYCLING].duration,
                      Sport_Best_Data[BEST_OUTDOOR_CYCLING].distance, Sport_Best_Data[BEST_OUTDOOR_CYCLING].sport_type);
    }
    else if (SPORTING_Indoor_running_TYPE == sport_type)
    {

        if (Sport_Best_Data[BEST_INDOOR_RUNNING].duration + 120 <= sport_save_data.sport_time_count)
        {
            Sport_Best_Data[BEST_INDOOR_RUNNING].duration = sport_save_data.sport_time_count;
        }
        if (Sport_Best_Data[BEST_INDOOR_RUNNING].distance + 100 <= sport_save_data.sport_distance)
        {
            Sport_Best_Data[BEST_INDOOR_RUNNING].distance = sport_save_data.sport_distance;
        }
        Sport_Best_Data[BEST_INDOOR_RUNNING].sport_type = sport_type;
        printf("[best_point]Indoor_running>>> duration:%d,distance:%d,type:%d\n", Sport_Best_Data[BEST_INDOOR_RUNNING].duration,
                      Sport_Best_Data[BEST_INDOOR_RUNNING].distance, Sport_Best_Data[BEST_INDOOR_RUNNING].sport_type);
    }
#endif
    return true;
}
void sport_ing_end_jump_to_table()
{
    if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_SWITCH))
    {
       // if(module_ms_app_is_gps_sport_type(Get_current_sporting_type()))
        {
#ifndef BSP_USING_PC_SIMULATOR
            zh_miwear_sport_request(SportState_SPORT_STOP, pb_sport_type_trans(Get_current_sporting_type())); //pb_sport_trans_map[menu_sport_id]);
#endif

        }
         sport_state_act = 46;
        module_ms_app_sport_set_points_flag(SPORT_POINTS_STOP);
        sport_stop();
        module_ms_app_set_sport_list_usecount(Get_current_sporting_type());
        extern SPORT_save_data_t sport_save_sport_record_data;
        memcpy(&sport_save_sport_record_data, &sport_save_data, sizeof(sport_save_data));
        //sport_save_sport_record_data = sport_save_data;
        misc_sport_data.sport_recorde_type = Get_current_sporting_type();
        sport_save_sport_record_data.sport_save_data_record_types = Get_current_sporting_type();
        sport_save_sport_record_data.sport_save_data_sub_type = Get_current_sporting_subtype();
        if (Get_current_sporting_subtype())
        {
            sport_save_sport_record_data.sport_save_data_record_t.sport_seeting_choose_target = 0;
        }
        else
            sport_save_sport_record_data.sport_save_data_record_t.sport_seeting_choose_target = sport_setting_target_data[misc_sport_data.sport_recorde_type].sport_seeting_choose_target & 0x1e;
        misc_sport_data.sporting_to_sport_record_flag = true;
        // misc_sport_data.sporting_to_sport_record_flag = true;
        if (!misc_sport_data.sport_is_app_sponsor)
        {
            module_mul_sport_set_best_points(Get_current_sporting_type());
            if(module_ms_app_sport_is_water_sports(Get_current_sporting_type()))
            {
               // Jump_App_And_Page(APP_DRAIN_WATER_STRING_ID, NULL);//排水
                return;
            }
            misc_sport_data.sport_loading_count = LOAD_TIME_OUT;
            printf("%s %d\n",__func__,__LINE__);
            ///Jump_App_And_Page(APP_SPORT_MAIN_STRING_ID, APP_SPORT_INTERVAL_FINISH_STRING_ID);//间歇训练load
            // if(strcmp(Get_Current_App_Id(), APP_SPORT_MAIN_STRING_ID) == 0)
            // {
            //     gui_app_exit(APP_SPORT_MAIN_STRING_ID);
            // }
            // else if(strcmp(Get_Current_App_Id(), APP_RUN_CLASS_MAIN_STRING_ID) == 0)
            // {
            //     gui_app_exit(APP_RUN_CLASS_MAIN_STRING_ID);               
            // }
        }
        else
        {
            // ThreadGui_TaskSubmit(TASK_MAIN_SPORTING_MENU, SECONDARY__SPORT_MEUN_END_MEUN);
        }
    }
    else
    {

// #ifndef BSP_USING_PC_SIMULATOR
//          miwear_sport_request(SportState_SPORT_STOP, pb_sport_type_trans(Get_current_sporting_type())); //pb_sport_trans_map[menu_sport_id]);
// #endif
        //set_sport_meun_state(false);
        //test_init_sport_data_still();
        if(module_ms_app_sport_is_water_sports(Get_current_sporting_type()))
         {
            if (misc_sport_data.sport_Function_state == Sport_state_start) // 处于开启状态，则进行暂停
            {
                sport_state_act  = 12;
            }
            module_sport_app_send_app_sport_pause();
            sport_pause();
           
         }
         else
         {
             sport_state_act = 47;
             module_ms_app_sport_set_points_flag(SPORT_POINTS_STOP);
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
            zh_miwear_sport_request(SportState_SPORT_STOP, pb_sport_type_trans(Get_current_sporting_type()));//结束
#endif
            sport_stop();
         }
        if(Get_current_sporting_subtype())
        {
            module_ms_app_set_sport_running_course_usecount(Get_current_sporting_subtype());
        }
        else
        {
            module_ms_app_set_sport_list_usecount(Get_current_sporting_type());
        }
        extern SPORT_save_data_t sport_save_sport_record_data;
        memcpy(&sport_save_sport_record_data, &sport_save_data, sizeof(sport_save_data));
        //sport_save_sport_record_data = sport_save_data;
        misc_sport_data.sport_recorde_type = Get_current_sporting_type();
        sport_save_sport_record_data.sport_save_data_record_types = Get_current_sporting_type();
        sport_save_sport_record_data.sport_save_data_sub_type = Get_current_sporting_subtype();
        if (Get_current_sporting_subtype())
        {
            sport_save_sport_record_data.sport_save_data_record_t.sport_seeting_choose_target = 0;
        }
        else
            sport_save_sport_record_data.sport_save_data_record_t.sport_seeting_choose_target = sport_setting_target_data[misc_sport_data.sport_recorde_type].sport_seeting_choose_target & 0x1e;
        misc_sport_data.sporting_to_sport_record_flag = true;
        if (!misc_sport_data.sport_is_app_sponsor)
        {
            module_mul_sport_set_best_points(Get_current_sporting_type());
            if(module_ms_app_sport_is_water_sports(Get_current_sporting_type()))
            {
             //   Jump_App_And_Page(APP_DRAIN_WATER_STRING_ID, NULL);//排水
                return;
            }
            misc_sport_data.sport_loading_count = LOAD_TIME_OUT;
            printf("%s %d\n",__func__,__LINE__);
           // Jump_App_And_Page(APP_SPORT_RECORD_MAIN_STRING_ID, APP_SPORT_LOADING_STRING_ID);//load

        }
        else
        {
            // ThreadGui_TaskSubmit(TASK_MAIN_SPORTING_MENU, SECONDARY__SPORT_MEUN_END_MEUN);
        }
    }

}
void mdoule_ms_sport_app_swim_jump_to_where(void)
{
    module_ms_app_sport_set_points_flag(SPORT_POINTS_STOP);
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
    zh_miwear_sport_request(SportState_SPORT_STOP, pb_sport_type_trans(Get_current_sporting_type()));//结束
#endif
    sport_stop();
    extern uint8_t sport_state_act;
    sport_state_act = 41;
    // sport_stop();

    if (Get_sport_save_status())
    {
        misc_sport_data.sport_loading_count = LOAD_TIME_OUT;
     //   Jump_App_And_Page(APP_SPORT_RECORD_MAIN_STRING_ID, APP_SPORT_LOADING_STRING_ID); // load
    }
    else
    {
       // app_sport_jump_to_list();
    }
}
uint8_t module_ms_app_get_sport_class(uint16_t sport_type)
{
    uint8_t sport_class = 1;
    switch (sport_type)
    {
    case SPORTING_Outdoor_running_TYPE: // 户外跑步
    case SPORTING_Outdoor_walking_TYPE: // 户外健走
        //      case SPORT_INDOOR_RUN:
        //   case SPORT_INDOOR_MOVE:
        sport_class = 1;
        break;
    case SPORTING_Indoor_running_TYPE: // 室内跑步
        //   case SPORT_INDOOR_MOVE:
        sport_class = 4;
        break;
#if 0
    case SPORT_OUTSIDE_HIKING:
        sport_class = 1;
        break;

    case SPORT_INDOOR_RUN:
    case SPORT_INDOOR_MOVE:
        sport_class = 2;
        break;
#endif
    case SPORTING_Outdoor_cycling_TYPE: // 户外骑行
        //        case SPORT_BMX:
        //        case SPORT_SKATEBOARDING:
        //        case SPORT_ROLLER_SKATING:
        sport_class = 3;
        break;
    case SPORTING_Outdoor_hiking_TYPE:
    case SPORTING_Mountaineering_TYPE:
    case SPORTING_Off_road_TYPE:
        sport_class = 2;
        break;
    case SPORTING_Elliptical_machine_TYPE: // 椭圆机
        sport_class = 5;
        break;
    case SPORTING_Rowing_machine_TYPE:  // 划船机
    case SPORTING_Skipping_rope_H_TYPE: // 跳绳
        sport_class = 6;
        break;

        //                  case SPORT_FOR_APP:

        //                  sport_class=8;
        //                  break;
    case SPORTING_swim_indoor_TYPE:    // 泳池游泳
        sport_class = 8;
        break;
    case SPORTING_swim_outdoor_TYPE:   // 开放水域游泳
        sport_class = 9;
        break;
    default:
        sport_class = 7;
        break;
    }
    return sport_class;
}
// 选中该运动目标
void module_ms_app_sport_set_sport_target(uint16_t sport_type, uint8_t setting_type)
{
    sport_setting_target_data[sport_type].sport_seeting_choose_target |= (1 << setting_type);
}
// 清除选中该运动目标
void module_ms_app_sport_clear_sport_target(uint16_t sport_type, uint8_t setting_type)
{
    sport_setting_target_data[sport_type].sport_seeting_choose_target &= ~(1 << setting_type);
}
bool module_ms_app_get__data_target_is_switch(Sport_type sprot_type, SPORT_SEETING_TYPE type)
{
    bool ret = 0;
    if (misc_sport_data.sport_is_app_sponsor)
    {
        //针对app下发的副屏运动
         if (sport_app_target.sport_seeting_choose_target >> type & 1)
         {
             ret = true;
         }
    }
    else
    {

        if (sport_setting_target_data[sprot_type].sport_seeting_choose_target >> type & 1)
        {
            ret = true;
        }
    }
    return ret;
}

// 选中打点
void module_ms_app_sport_set_points_flag(uint8_t setting_type)
{
    misc_sport_data.is_set_swim_points |= (1 << setting_type);
}
// 清除选中打点
void module_ms_app_sport_clear_points_flag()
{
    misc_sport_data.is_set_swim_points = 0;
}
bool module_ms_app_get__data_points_is_switch(SPORT_POINTS_TYPE type)
{
    bool ret = 0;

    if (misc_sport_data.is_set_swim_points >> type & 1)
    {
        ret = true;
    }
    return ret;
}
#if ZH_GPS_DRAW
void module_sport_app_malloc_gps(void)
{
#if defined(ENUM_PROJECT_NAME_N65B_GLOBAL)    
    double *tmp_ptr = NULL;
    if(!misc_sport_data.gps_lat){
        tmp_ptr = malloc(sizeof(double)*GPS_TRACK_LEN*4);

        if(tmp_ptr){
        
            misc_sport_data.gps_lat = tmp_ptr;
            misc_sport_data.gps_lon = tmp_ptr + GPS_TRACK_LEN;
            misc_sport_data.gps_temp_x = tmp_ptr + GPS_TRACK_LEN * 2;
            misc_sport_data.gps_temp_y = tmp_ptr + GPS_TRACK_LEN * 3;
        }
        else{
            misc_sport_data.gps_lat = NULL;
            misc_sport_data.gps_lon = NULL;
            misc_sport_data.gps_temp_x = NULL;
            misc_sport_data.gps_temp_y = NULL;
        }
    }
  /*  if(misc_sport_data.gps_lat == NULL)
    {
        misc_sport_data.gps_lat = malloc(sizeof(double)*GPS_TRACK_LEN);
        memset((uint8_t *)misc_sport_data.gps_lat, 0, sizeof(sizeof(double)*GPS_TRACK_LEN));
    }
    if(misc_sport_data.gps_lon == NULL)
    {
        misc_sport_data.gps_lon = malloc(sizeof(double)*GPS_TRACK_LEN);
        memset((uint8_t *)misc_sport_data.gps_lon, 0, sizeof(sizeof(double)*GPS_TRACK_LEN));
    }
    if(misc_sport_data.gps_temp_x == NULL)
    {
        misc_sport_data.gps_temp_x = malloc(sizeof(double)*GPS_TRACK_LEN);
        memset((uint8_t *)misc_sport_data.gps_temp_x, 0, sizeof(sizeof(double)*GPS_TRACK_LEN));
    }
    if(misc_sport_data.gps_temp_y == NULL)
    {
        misc_sport_data.gps_temp_y = malloc(sizeof(double)*GPS_TRACK_LEN);
        memset((uint8_t *)misc_sport_data.gps_temp_y, 0, sizeof(sizeof(double)*GPS_TRACK_LEN));
    }*/
#endif
}
void module_sport_app_free_gps(void)
{
#if defined(ENUM_PROJECT_NAME_N65B_GLOBAL)

     if(misc_sport_data.gps_lat ){
        misc_sport_data.gps_lon = NULL;
        misc_sport_data.gps_temp_x = NULL;
        misc_sport_data.gps_temp_y = NULL;
        free(misc_sport_data.gps_lat);
         misc_sport_data.gps_lat = NULL;
     }
   /* if(misc_sport_data.gps_lat != NULL)
    {
        free(misc_sport_data.gps_lat);
        misc_sport_data.gps_lat = NULL;
    }   
     if(misc_sport_data.gps_lon != NULL)
    {
        free(misc_sport_data.gps_lon);
        misc_sport_data.gps_lon = NULL;
    }   
     if(misc_sport_data.gps_temp_x != NULL)
    {
        free(misc_sport_data.gps_temp_x);
        misc_sport_data.gps_temp_x = NULL;
    }   
     if(misc_sport_data.gps_temp_y != NULL)
    {
        free(misc_sport_data.gps_temp_y);
        misc_sport_data.gps_temp_y = NULL;
    } */
#endif  
}
#endif
static uint16_t pause_count = 0;
bool sport_start(Sport_type sport_type)
{
#if 1 // todo: by ly
   uint32_t start_timestamp;
   uint32_t recovery_motion_timestamp;
    uint8_t sport_target_choose = 0;
    uint32_t sport_target = 0;
    uint8_t sport_set = 1;
    uint8_t gps_set = 2;
    pause_count = 0;

    // app_calories = 0; //todo: by ly
    // printf("[log_sport_start]state:%d\n", misc_sport_data.sport_Function_state);
    if (misc_sport_data.sport_Function_state == Sport_state_stop) // 处于关闭状态，则进行开启
    {
         
        // log_info2("sport_Function_state :%d\r\n",Sport_state_start);
        // 自动运动识别进入的运动
        /*  if ((misc_sport_data.auto_sports_detection_enter_sport_flag == true)
                  && ((sport_type == SPORTING_Outdoor_running_TYPE) || (sport_type == SPORTING_Outdoor_walking_TYPE) || (sport_type == SPORTING_Indoor_running_TYPE))
             )
          {
              auto_sport_save_data_clear();
              sport_save_data.sport_Step_number = misc_sport_data.auto_sports_detection_step;
              sport_save_data.sport_time_start = get_wall_clock_time_counter() - 5 * 60;
              sport_save_data.sport_time_zone = mul_sport_get_time_zone();
              sport_save_data.sport_time_count = 5 * 60;
              recovery_motion_timestamp = mul_sport_get_timestamp();
              start_timestamp = (recovery_motion_timestamp > 5 * 60) ? (recovery_motion_timestamp - 5 * 60) : 0;
              misc_sport_data.auto_sports_detection_enter_sport_flag = false;
              sport_set = 4;
          }5
          //运动列表进入的运动
          else*/
        {
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
            clearheart5second();
#endif
            sport_save_data_clear(); // 开启多运动需要先将我们的数据清除一下
#if ZH_GPS_DRAW
        if(module_ms_app_is_gps_sport_type(Get_current_sporting_type()))
            module_sport_app_malloc_gps();
        sport_save_data.lon = misc_sport_data.gps_lon;
        sport_save_data.lat = misc_sport_data.gps_lat;
        sport_save_data.len = 0;
        sport_save_data.gps_draw_track_count = 0;
#endif
            start_timestamp = mul_sport_get_timestamp();
            recovery_motion_timestamp = start_timestamp;
        }
        module_sport_app_erase_target();//运动识别释放目标
        // printf("time_switch:%d\n", get_sport_seeting_time_switch(sport_type));
        if (module_ms_app_get__data_target_is_switch(sport_type, SPORT_SEETING_CONSUME))
        {
            sport_save_data.sport_seeting_choose_target = (1 << SPORT_SEETING_CONSUME);
            sport_save_data.sport_setting_target = sport_setting_target_data[sport_type].sport_seeting_consume_data;
            sport_target_choose = 3;
            sport_target = sport_setting_target_data[sport_type].sport_seeting_consume_data;
        }
        else if (module_ms_app_get__data_target_is_switch(sport_type, SPORT_SEETING_DISTANCE))
        {
            sport_save_data.sport_seeting_choose_target = (1 << SPORT_SEETING_DISTANCE);
            sport_save_data.sport_setting_target = sport_setting_target_data[sport_type].sport_seeting_distance_data;
            sport_target_choose = 1;
            sport_target = sport_setting_target_data[sport_type].sport_seeting_distance_data;
        }
        else if (module_ms_app_get__data_target_is_switch(sport_type, SPORT_SEETING_TIME))
        {
            sport_save_data.sport_seeting_choose_target = (1 << SPORT_SEETING_TIME);
            sport_save_data.sport_setting_target = sport_setting_target_data[sport_type].sport_seeting_time_data;
            sport_target_choose = 2;
            sport_target = sport_setting_target_data[sport_type].sport_seeting_time_data;
        }
        else if (module_ms_app_get__data_target_is_switch(sport_type, SPORT_SEETING_COUNT))
        {
            sport_save_data.sport_seeting_choose_target = (1 << SPORT_SEETING_COUNT);
            sport_save_data.sport_setting_target = sport_setting_target_data[sport_type].sport_seeting_count_data;
            sport_target_choose = 4;
            sport_target = sport_setting_target_data[sport_type].sport_seeting_count_data;
        }
        else
        {
            sport_save_data.sport_seeting_choose_target = 0;
            sport_save_data.sport_setting_target = 0;
        }
       // printf("%s target_switch:0x%x\n",__func__,sport_save_data.sport_seeting_choose_target);
        // if ((sport_setting_target_data[Get_current_sporting_type()].sport_seeting_choose_target >> SPORT_INTERVAL_TRAINING_SWITCH & 1) && misc_sport_data.sport_is_app_sponsor) // 间歇训练先清除
        // {
        //     module_ms_app_sport_clear_sport_target(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_SWITCH);
        //     misc_sport_data.sport_interval_train_is_close = true;
        // }
        //   set_sport_altitude_basic_value(Get_Altitude_Value()/10);

        misc_sport_data.auto_sport_obj.data_len = 0;
        misc_sport_data.auto_sport_obj.total_cnts = 0;
        misc_sport_data.auto_sport_obj.sport_type = sport_type;
		misc_sport_data.auto_sportting_indoor_step = 0;
		misc_sport_data.auto_sportting_indoor_disc = 0;
        mul_sport_clear_sport_global_var();
#ifndef BSP_USING_PC_SIMULATOR
		clear_wellness_heartRate();
#endif
        extern void module_ms_app_set_upload_flag(bool flag);
        extern bool module_ms_app_get_upload_flag();
        if (module_ms_app_get_upload_flag())
            module_ms_app_set_upload_flag(0);
        if (misc_sport_data.sport_is_app_sponsor == false && misc_sport_data.is_auto_sport == false)
        {
	       // algoTask_sync_sleep_data_handle(SAA_WAKE_UP_START_SPORT);
            mul_sport_new_sport_file(start_timestamp, false);
            if (Get_current_sporting_subtype())
            {
                if (sport_running_course.current_sub_type >= Beat_It_Type && Sport_Course_Sub_Max > sport_running_course.current_sub_type)
                    mul_sport_set_sport_sit_type((Sport_Interval_Training_Type)sport_running_course.current_sub_type);
                else
                    mul_sport_set_sport_sit_type(SIT_NONE);
            }
            else
            {
                if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_SWITCH))
                {
#if INTERVAL_TRAINING_SELECT
                    if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_WARM_UP_SWITCH))
                    {
                        mul_sport_set_sport_sit_type(SIT_WARM_UP);
                    }
                    else
                    {
                        mul_sport_set_sport_sit_type(SIT_TRAINING);
                    }
#endif
                }
                else
                {
                    mul_sport_set_sport_sit_type(SIT_NONE);
                }
            }
        }
        else
        {
                if(misc_sport_data.is_auto_sport)//运动识别清除所有间歇训练标志
                {
                    printf("%s,SIT_NONE\n",__func__);
                    mul_sport_set_sport_sit_type(SIT_NONE);
                }            
        }
        if (misc_sport_data.sport_is_app_sponsor)
        {
            sport_set = 2;
        }
        if (misc_sport_data.gps_position_status)
        {
            gps_set = 3;
        }
        // TODO: wdh, ly, 埋点
#ifndef BSP_USING_PC_SIMULATOR
        miwear_dev_app_event_set((uint8_t)SPORT_START_EVENT_NAME_ID, mul_sport_get_timestamp(), 0,
                                 pb_sport_type_trans(Get_current_sporting_type()), sport_target_choose, sport_target
                                 , gps_set, sport_set, 0);
#endif
#ifndef BSP_USING_PC_SIMULATOR
        uint32_t remind = 0;
        // 1. 距离提醒
        // 2. 配速提醒（秒单位）
        // 3. 速度提醒（公里/时）
        // 4. 目标心率区间提醒（区间数，1-5表示从低到高）
        // 5. 心率过高提醒
        // 6. 能量补给提醒（为距离时，传入公里数值，例如5；设定为时间时，传入以秒为单位的数据）
        // 7. (滑雪)每趟滑行播报
        // 8. (自由潜)下潜深度提醒
        // 9. (潜水)下潜时长警告
        // 10. 下潜深度警告
        // 11. 水面时间提醒
        // 12. 潜水提醒方式（1声音，2振动，3声音+振动）
        if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_SEETING_DISTANCE_REMIND))
        {
            remind |= 1 << 1;
        }
        if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_SEETING_PACE_REMIND))
        {
            if (Get_current_sporting_type() == SPORTING_Outdoor_cycling_TYPE)
            {
                remind |= 1 << 3;
            }
            else
                remind |= 1 << 2;
        }
        if (sport_setting_target_data[Get_current_sporting_type()].sport_heart_rate_zones)
        {
            remind |= 1 << 4;
        }
        if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_SEETING_HR))
        {
            remind |= 1 << 5;
        }
        if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_ENERGY_SUPPLY_TIME) ||
            module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_ENERGY_SUPPLY_DISTANCE))
        {
            remind |= 1 << 6;
        }
        miwear_dev_app_event_set((uint8_t)SPORT_REMIND_NAME_ID, mul_sport_get_timestamp(), 0,
                                 pb_sport_type_trans(Get_current_sporting_type()), remind, 0, 0, 0, 0);
#endif
        if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_SWITCH))
        {
            uint8_t warm_up = 0, relax = 0;
            if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_WARM_UP_SWITCH))
            {
                warm_up = 1;
            }
            if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_RELAX_SWITCH))
            {
                relax = 1;
            }
            uint8_t mode = 1;
            //             //训练方式
            // 1 // 按时长
            // 2  // 按距离
            // 3  // 按趟数
            // 4  // 按个数
            // 5  // 按次数
            if (sport_interval_training.mode == Sport_MODE_TIME)
            {
                mode = 1;
            }
            else if (sport_interval_training.mode == Sport_MODE_DISTANCE)
            {
                mode = 2;
            }
            else
            {
                if (Get_current_sporting_type() == SPORTING_Skipping_rope_H_TYPE)
                {
                    mode = 4;
                }
                else
                {
                    mode = 5;
                }
            }
            uint8_t loop = sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_loop;
            uint16_t reset_time = sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_rest;
#ifndef BSP_USING_PC_SIMULATOR
            miwear_dev_app_event_set((uint8_t)SPORT_INTERVAL_TRAIN_ID, mul_sport_get_timestamp(), 0,
                                     pb_sport_type_trans(Get_current_sporting_type()), warm_up, mode, loop, reset_time, relax);
#endif
        }
        //  Init_gps_Processing();
        // clear_last_longitude_latitude();//todo:by ly
        // Sport_save_data_flag = false;
        misc_sport_data.Sport_save_data_flag = false;
        misc_sport_data.auto_pause_dst.auto_pause_disable = 21;
        // set_sport_heart_rate_remind_status(false);//todo:by ly
        // set_sport_goal_distance_remind_status(false);//todo:by ly
        // set_sport_goal_calorie_remind_status(false);//todo:by ly
        // set_sport_goal_time_remind_status(false);//todo:by ly
        //  hr_midhight_count = 0;
        //  gps_recived = 0;
        //  gps_recived_delay = 0;
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
		extern uint64_t ts_ms_gps;
		ts_ms_gps = (uint64_t)misc_sport_data.sport_timestamp*1000;
        module_ms_app_sport_init_gps(sport_type);
        misc_sport_data.gps_source = 0xff;
	//	printf("%s %d",__func__,Get_current_sporting_type());
        extern uint64_t ts_ms_course;
        ts_ms_course = ts_ms_gps;
        // zh_miwear_sport_request(SportState_SPORT_START, pb_sport_type_trans(Get_current_sporting_type()));//开始sport
#if defined(ENUM_PROJECT_NAME_N65B_GLOBAL)
		 if ((module_ms_app_is_gps_sport_type(sport_type) || (sport_type == SPORTING_swim_outdoor_TYPE))){
		 	gps_set_user_mark(GPS_USED_BY_PREPEAR_SPORT);

		 }
#endif 
        if(get_vibration_adjustment_status()&&!misc_sport_data.is_auto_sport)
        {
            Set_Moto_Times_Frequence(NOW_VIBRATION_MODE_3,2);
        }

#endif
        // start_sport_counter(sport_type);//todo:by ly
        misc_sport_data.unwear_dura = 0xff;
		misc_sport_data.low_speed_cnt = 0;
       misc_sport_data.sport_Function_state = Sport_state_start; // 初始化完成再打开,防止未初始化完成跑到work队列造成死机
        sport_state_log(1);
        return true;
    }
    else // 处于开启状态，则返回失败
    {
        return false;
    }
#endif
    return false;
}
bool Get_sport_save_status(void)
{
    uint8_t sport_class = module_ms_app_get_sport_class(Get_current_sporting_type());
    if (sport_class == 5 || sport_class == 6 || sport_class == 7)
    {
        if (sport_save_data.sport_time_count >= SPORT_RECORD_TIME_LINE)
        {
            return true;
        }
        else
            return false;
    }
    else if(sport_class == 8 || sport_class == 9)
    {
        if(Get_current_sporting_type() == SPORTING_swim_indoor_TYPE)
        {
            if (sport_save_data.sport_number_of_tips >= 1)//大于一趟
            {
                return true;
            }
            else
                return false;         
        }
        else
        {
            if (sport_save_data.sport_distance >= 15)
            {
                return true;
            }
            else
                return false;
        }
    }
    else
    {
        if (sport_save_data.sport_distance >= 100)
        {
            return true;
        }
        else if (sport_save_data.sport_distance >= 80 && sport_class == 4)
        {
            return true;
        }
        else
            return false;
    }
}

extern void clear_all_sport_status();
bool sport_stop(void)
{
    if (misc_sport_data.sport_interval_train_is_close) // 恢复间歇训练
    {
        module_ms_app_sport_set_sport_target(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_SWITCH);
        misc_sport_data.sport_interval_train_is_close = 0;
    }
    clear_all_sport_status();
    if(1)//interconnection_ioctl_is_report_sport_data_projection())//停止投屏
    {
        zh_sports_data_projection(PROJECTION_DISCONNECT);
    }
    if (misc_sport_data.sport_is_app_sponsor == 0)
    {
#if INTERVAL_TRAINING_SELECT
        if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_SWITCH))
        {
            if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_RELAX_SWITCH))
            {
                // mul_sport_platform_change_sit_type(INTERVAL_TRAINING_RELAX); // 切换状态,
                mul_sport_set_is_change_sit_type(true);
            }
            else
            {
                // mul_sport_platform_change_sit_type(INTERVAL_TRAINING); // 切换状态,
                mul_sport_set_is_change_sit_type(true);
            }
        }
#endif
    }
     printf("func:%x,0x%x line:%x,0x%X sport_save_data.len=%d.\n", misc_sport_data.gps_temp_x, misc_sport_data.gps_temp_y, sport_save_data.lon,sport_save_data.lat,sport_save_data.len);

    // 心率关闭
    module_ms_app_sport_open_heart(0, 0);
    // app_calories = 0;//todo: by ly
    //  if (get_heard_power_state() == true)
    //  {
    //      if (Get_Heart_Messure_State_Style() == ENUM_HEART_MESSUREING_AUTO)
    //      {
    //          //pm_sleep_mode_release(pm_mode_active);
    //      }

    //     Heart_Power_On_Off_Switch(false, false, 0, ENUM_HEART_IDLE);
    // }
    // set_hr_sport_mode(alg_prarmeter_mode_norm);
    misc_sport_data.is_auto_sport = false;
    if (misc_sport_data.sport_Function_state != Sport_state_stop) // 不处于关闭状态，则进行关闭
    {
#ifndef BSP_USING_PC_SIMULATOR
		extern bool acc_odr_status_is_25hz;
		extern uint8_t acc_data_rate_is_8g ;    
    	acc_odr_status_is_25hz = true;
 		acc_data_rate_is_8g = 1;
#endif
        // todo by wdh wdh
#ifndef BSP_USING_PC_SIMULATOR
        uint32_t end_timestamp = mul_sport_get_timestamp();
        uint32_t total_timestamp = end_timestamp-(sport_save_data.sport_time_start - mul_sport_get_time_zone_offset(sport_save_data.sport_time_zone));
         miwear_dev_app_event_set((uint8_t)SPORT_END_EVENT_NAME_ID, end_timestamp, total_timestamp
                                  , pb_sport_type_trans(Get_current_sporting_type()), pause_count, Get_sport_save_status()==1?1:2,
                                  0, 0, 0);
#if ! defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)&&defined(ENUM_PROJECT_NAME_N65B_GLOBAL)
         if (module_ms_app_is_gps_sport_type(Get_current_sporting_type()))
         {
             Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.phone_signal_per = (float)Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.phone_signal_sec / (float)sport_save_data.sport_time_count * 100;
             Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.no_signal_per = (float)Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.no_signal_sec / (float)sport_save_data.sport_time_count * 100;
             // if(Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.phone_signal_per+Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.no_signal_per>100)
             // {
             //     Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.no_signal_per = 100-
             // }
             Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.watch_signal_per = 100 - Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.phone_signal_per - Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.no_signal_per;
             miwear_dev_app_event_set((uint8_t)GNSS_SIGNAL_EVENT_NAME_ID,
                                      Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.start_timestamp,
                                      Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.duration_sec,
                                      Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.switch_cnt,
                                      Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.phone_signal_per,
                                      Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.watch_signal_per,
                                      Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.no_signal_per,
                                      0, 0);
         }
#endif
#endif
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
#if defined(USING_GYRO_SENSOR) && defined(ENUM_PROJECT_NAME_N65B_GLOBAL)
        module_ms_app_sport_swimming_final();
#endif
#ifndef BSP_USING_PC_SIMULATOR
        if(get_vibration_adjustment_status())
        {
            Set_Moto_Times_Frequence(NOW_VIBRATION_MODE_3,2);
        }
#endif
#endif
        misc_sport_data.sport_Function_state = Sport_state_stop;

#if ZH_GPS_DRAW
    if (module_ms_app_is_gps_sport_type(Get_current_sporting_type()))
    {
        if (misc_sport_data.gps_temp_x != NULL)
        {
            memset((uint8_t *)misc_sport_data.gps_temp_x, 0, sizeof(double) * GPS_TRACK_LEN);
        }
        if (misc_sport_data.gps_temp_y != NULL)
        {
            memset((uint8_t *)misc_sport_data.gps_temp_y, 0, sizeof(double) * GPS_TRACK_LEN);
        }
        printf("func:%s, line:%d, sport_save_data.len=%d.\n", __func__, __LINE__, sport_save_data.len);
        if (sport_save_data.lon != NULL && sport_save_data.lat != NULL&&sport_save_data.len>=2)
        {
#ifndef BSP_USING_PC_SIMULATOR
// 视图宽高236*222
//  Lvgl_Coordinates_CS(&Zh_Data_Manager.SystemData.sport_save_data.lon[0], &Zh_Data_Manager.SystemData.sport_save_data.lat[0], (double *)&gps_temp_x[0], (double *)&gps_temp_y[0], Zh_Data_Manager.SystemData.sport_save_data.len, 360, 231);
#if ENUM_PROJECT_NAME_N65B_GLOBAL // N65B  410_502
                // 350*222
            Lvgl_Coordinates_CS(sport_save_data.lon, sport_save_data.lat, misc_sport_data.gps_temp_x, misc_sport_data.gps_temp_y, sport_save_data.len, (350-28), (222-28));
#else
            Lvgl_Coordinates_CS(sport_save_data.lon, sport_save_data.lat, misc_sport_data.gps_temp_x, misc_sport_data.gps_temp_y, sport_save_data.len, (350-28), (222-28));
#endif
#endif
            sport_save_data.gps_draw_track_count = 0;
            for (int i = 0; i < sport_save_data.len; i++)
            {
                sport_save_data.gps_track[sport_save_data.gps_draw_track_count].x = ((uint16_t)misc_sport_data.gps_temp_x[i]+14);
                sport_save_data.gps_track[sport_save_data.gps_draw_track_count].y = ((222-28)-(uint16_t)misc_sport_data.gps_temp_y[i]+14);//((uint16_t)misc_sport_data.gps_temp_y[i]+14);
                sport_save_data.gps_draw_track_count++;
                // printf("func:%s, line:%d, %d, %d.\n", __func__, __LINE__,
                //            sport_save_data.gps_track[sport_save_data.gps_draw_track_count - 1].x,
                //            sport_save_data.gps_track[sport_save_data.gps_draw_track_count - 1].y);
            }
        }
        else
        {
            sport_save_data.gps_draw_track_count = 0;           
        }

        
    }
    module_sport_app_free_gps();
#endif
        if (Get_sport_save_status())
        {
            if (misc_sport_data.sport_is_app_sponsor == false)
            {
                if (Get_current_sporting_type() != SPORTING_Indoor_running_TYPE)
                {
                    mul_sport_set_mul_sport_end_time(mul_sport_get_timestamp());
                }

                save_cur_sport_file_work_start();
            }
        }
        else
        {
            module_sport_app_release_target();
            misc_sport_data.auto_sportting_flag = 0;
            mul_sport_clear_cur_sport_id();
        }
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
        // stop_sport_counter();todo:by ly
       // if (module_ms_app_is_gps_sport_type(Get_current_sporting_type()))
        // {
        //     zh_miwear_sport_request(SportState_SPORT_STOP, pb_sport_type_trans(Get_current_sporting_type())); // 停止GPS
        // }
#if defined(ENUM_PROJECT_NAME_N65B_GLOBAL)
        printf("%s->%s\n", __func__, "All_sport_Close_GPS");
        if ((module_ms_app_is_gps_sport_type(Get_current_sporting_type()) || (Get_current_sporting_type() == SPORTING_swim_outdoor_TYPE)))
        {
            gps_clear_user_mark(GPS_USED_BY_PREPEAR_SPORT);
          //  All_sport_Close_GPS();
        }
#endif

        module_ms_app_sport_deinit_gps();

#endif
        misc_sport_data.sport_upload_steps = 0;
        misc_sport_data.sport_upload_kcal = 0;
        misc_sport_data.sport_is_app_sponsor = false;
        misc_sport_data.copy_time_cont = 0;
        uint32_t* p_lock_time = 0;// (uint32_t*)app_db_get_setting_data(APP_SETTING_LOCK_TIME);
       // app_set_screen_lock_time(*p_lock_time);
printf("stop end\n");
        sport_state_log(2);
//#endif
        return true;
    }
    else // 处于开启状态，则返回失败
    {
        return false;
    }
}

bool sport_stop_when_full(void)
{
#ifndef BSP_USING_PC_SIMULATOR
        uint32_t end_timestamp = mul_sport_get_timestamp();
        uint32_t total_timestamp = end_timestamp-(sport_save_data.sport_time_start - mul_sport_get_time_zone_offset(sport_save_data.sport_time_zone));
         miwear_dev_app_event_set((uint8_t)SPORT_END_EVENT_NAME_ID, end_timestamp, total_timestamp
                                  , pb_sport_type_trans(Get_current_sporting_type()), pause_count,  Get_sport_save_status()==1?1:2,
                                  0, 0, 0);
#endif
    if (misc_sport_data.sport_interval_train_is_close) // 恢复间歇训练
    {
        module_ms_app_sport_set_sport_target(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_SWITCH);
        misc_sport_data.sport_interval_train_is_close = 0;
    }
    clear_all_sport_status();
    if(1)//interconnection_ioctl_is_report_sport_data_projection())//停止投屏
    {
        zh_sports_data_projection(PROJECTION_DISCONNECT);
    }
    if (misc_sport_data.sport_is_app_sponsor == 0)
    {
#if INTERVAL_TRAINING_SELECT
        if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_SWITCH))
        {
            if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_RELAX_SWITCH))
            {
                // mul_sport_platform_change_sit_type(INTERVAL_TRAINING_RELAX); // 切换状态,
                mul_sport_set_is_change_sit_type(true);
            }
            else
            {
                // mul_sport_platform_change_sit_type(INTERVAL_TRAINING); // 切换状态,
                mul_sport_set_is_change_sit_type(true);
            }
        }
#endif
    }
     printf("func:%x,0x%x line:%x,0x%X sport_save_data.len=%d.\n", misc_sport_data.gps_temp_x, misc_sport_data.gps_temp_y, sport_save_data.lon,sport_save_data.lat,sport_save_data.len);

    // 心率关闭
    module_ms_app_sport_open_heart(0, 0);
    // app_calories = 0;//todo: by ly
    //  if (get_heard_power_state() == true)
    //  {
    //      if (Get_Heart_Messure_State_Style() == ENUM_HEART_MESSUREING_AUTO)
    //      {
    //          //pm_sleep_mode_release(pm_mode_active);
    //      }

    //     Heart_Power_On_Off_Switch(false, false, 0, ENUM_HEART_IDLE);
    // }
    // set_hr_sport_mode(alg_prarmeter_mode_norm);
    misc_sport_data.is_auto_sport = false;
    if (misc_sport_data.sport_Function_state != Sport_state_stop) // 不处于关闭状态，则进行关闭
    {
#ifndef BSP_USING_PC_SIMULATOR
		extern bool acc_odr_status_is_25hz;
		extern uint8_t acc_data_rate_is_8g ;    
    	acc_odr_status_is_25hz = true;
 		acc_data_rate_is_8g = 1;
#endif
        // todo by wdh wdh
        //  miwear_dev_app_event_set((uint8_t)SPORT_END_EVENT_NAME_ID, mul_sport_get_timestamp(), sport_save_data.sport_time_count
        //                           , mul_sport_get_sub_sport_type(), pause_count, Get_sport_save_status(),
        //                           0, 0, 0);
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
#if defined(USING_GYRO_SENSOR) && defined(ENUM_PROJECT_NAME_N65B_GLOBAL)
        module_ms_app_sport_swimming_final();
#endif
#ifndef BSP_USING_PC_SIMULATOR
        if(get_vibration_adjustment_status())
        {
            Set_Moto_Times_Frequence(NOW_VIBRATION_MODE_3,2);
        }
#endif
#endif
        misc_sport_data.sport_Function_state = Sport_state_stop;
#if ZH_GPS_DRAW
    if (module_ms_app_is_gps_sport_type(Get_current_sporting_type()))
    {
        if (misc_sport_data.gps_temp_x != NULL)
        {
            memset((uint8_t *)misc_sport_data.gps_temp_x, 0, sizeof(sizeof(double) * GPS_TRACK_LEN));
        }
        if (misc_sport_data.gps_temp_y != NULL)
        {
            memset((uint8_t *)misc_sport_data.gps_temp_y, 0, sizeof(sizeof(double) * GPS_TRACK_LEN));
        }
        printf("func:%s, line:%d, sport_save_data.len=%d.\n", __func__, __LINE__, sport_save_data.len);
       if (sport_save_data.lon != NULL && sport_save_data.lat != NULL&&sport_save_data.len>=2)
        {
#ifndef BSP_USING_PC_SIMULATOR
// 视图宽高236*222
//  lvgl_Coordinates(&Zh_Data_Manager.SystemData.sport_save_data.lon[0], &Zh_Data_Manager.SystemData.sport_save_data.lat[0], (double *)&gps_temp_x[0], (double *)&gps_temp_y[0], Zh_Data_Manager.SystemData.sport_save_data.len, 360, 231);
#if ENUM_PROJECT_NAME_N65B_GLOBAL // N65B  410_502
                // 350*222
            Lvgl_Coordinates_CS(sport_save_data.lon, sport_save_data.lat, misc_sport_data.gps_temp_x, misc_sport_data.gps_temp_y, sport_save_data.len, (350-28), (222-28));
#else
            Lvgl_Coordinates_CS(sport_save_data.lon, sport_save_data.lat, misc_sport_data.gps_temp_x, misc_sport_data.gps_temp_y, sport_save_data.len, (350-28), (222-28));
#endif
#endif
            sport_save_data.gps_draw_track_count = 0;
            for (int i = 0; i < sport_save_data.len; i++)
            {
                sport_save_data.gps_track[sport_save_data.gps_draw_track_count].x = ((uint16_t)misc_sport_data.gps_temp_x[i]+14);
                sport_save_data.gps_track[sport_save_data.gps_draw_track_count].y = ((222-28)-(uint16_t)misc_sport_data.gps_temp_y[i]+14);//((uint16_t)misc_sport_data.gps_temp_y[i]+14);
                sport_save_data.gps_draw_track_count++;
                printf("func:%s, line:%d, %d, %d.\n", __func__, __LINE__,
                           sport_save_data.gps_track[sport_save_data.gps_draw_track_count - 1].x,
                           sport_save_data.gps_track[sport_save_data.gps_draw_track_count - 1].y);
            }
        }
        else
        {
            sport_save_data.gps_draw_track_count = 0;           
        }

        
    }
    module_sport_app_free_gps();
#endif
        if (Get_sport_save_status())
        {
            if (misc_sport_data.sport_is_app_sponsor == false)
            {
                if (Get_current_sporting_type() != SPORTING_Indoor_running_TYPE)
                {
                    mul_sport_set_mul_sport_end_time(mul_sport_get_timestamp());
                }

                save_cur_sport_file_work_start_when_full();
            }
        }
        else
        {
            misc_sport_data.draw_points_complete = true;//用于存储满的提醒退页面时机
            module_sport_app_release_target();
            misc_sport_data.auto_sportting_flag = 0;
            mul_sport_clear_cur_sport_id();
        }
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
        // stop_sport_counter();todo:by ly
       // if (module_ms_app_is_gps_sport_type(Get_current_sporting_type()))
        // {
        //     zh_miwear_sport_request(SportState_SPORT_STOP, pb_sport_type_trans(Get_current_sporting_type())); // 停止GPS
        // }
#if defined(ENUM_PROJECT_NAME_N65B_GLOBAL)
        printf("%s->%s\n", __func__, "All_sport_Close_GPS");
        if ((module_ms_app_is_gps_sport_type(Get_current_sporting_type()) || (Get_current_sporting_type() == SPORTING_swim_outdoor_TYPE)))
        {
            gps_clear_user_mark(GPS_USED_BY_SPORTING);
            All_sport_Close_GPS();
        }
#endif

        module_ms_app_sport_deinit_gps();

#endif
        misc_sport_data.sport_upload_steps = 0;
        misc_sport_data.sport_upload_kcal = 0;
        misc_sport_data.sport_is_app_sponsor = false;
        uint32_t* p_lock_time = 0;// (uint32_t*)app_db_get_setting_data(APP_SETTING_LOCK_TIME);
       // app_set_screen_lock_time(*p_lock_time);
printf("stop end\n");
        sport_state_log(2);
//#endif
        return true;
    }
    else // 处于开启状态，则返回失败
    {
        return false;
    }
}

bool sport_stop_for_power_down(void) // 低电关机的时候直接保存,发消息可能处理不过来
{
    if (misc_sport_data.sport_interval_train_is_close) // 恢复间歇训练
    {
        module_ms_app_sport_set_sport_target(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_SWITCH);
        misc_sport_data.sport_interval_train_is_close = 0;
    }
#ifndef BSP_USING_PC_SIMULATOR
        uint32_t end_timestamp = mul_sport_get_timestamp();
        uint32_t total_timestamp = end_timestamp-(sport_save_data.sport_time_start - mul_sport_get_time_zone_offset(sport_save_data.sport_time_zone));
         miwear_dev_app_event_set((uint8_t)SPORT_END_EVENT_NAME_ID, end_timestamp, total_timestamp
                                  , pb_sport_type_trans(Get_current_sporting_type()), pause_count,  Get_sport_save_status()==1?1:2,
                                  0, 0, 0);
#endif
    if(1)//interconnection_ioctl_is_report_sport_data_projection())//停止投屏
    {
        zh_sports_data_projection(PROJECTION_DISCONNECT);
    }
    clear_all_sport_status();
    if (misc_sport_data.sport_is_app_sponsor == 0)
    {
#if INTERVAL_TRAINING_SELECT
        if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_SWITCH))
        {
            if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_RELAX_SWITCH))
            {
                //mul_sport_platform_change_sit_type(INTERVAL_TRAINING_RELAX); // 切换状态,
                mul_sport_set_is_change_sit_type(true);
            }
            else
            {
                //mul_sport_platform_change_sit_type(INTERVAL_TRAINING); // 切换状态,
                mul_sport_set_is_change_sit_type(true);
            }
        }
#endif
    }
    // 心率关闭
    module_ms_app_sport_open_heart(0,0);
    // app_calories = 0;//todo: by ly
    //  if (get_heard_power_state() == true)
    //  {
    //      if (Get_Heart_Messure_State_Style() == ENUM_HEART_MESSUREING_AUTO)
    //      {
    //          //pm_sleep_mode_release(pm_mode_active);
    //      }

    //     Heart_Power_On_Off_Switch(false, false, 0, ENUM_HEART_IDLE);
    // }
    // set_hr_sport_mode(alg_prarmeter_mode_norm);
  
    if (misc_sport_data.sport_Function_state != Sport_state_stop) // 不处于关闭状态，则进行关闭
    {
        // todo:by wdh wdh
// #ifndef BSP_USING_PC_SIMULATOR
//          miwear_dev_app_event_set((uint8_t)SPORT_END_EVENT_NAME_ID, mul_sport_get_timestamp(), sport_save_data.sport_time_count
//                                   , mul_sport_get_sub_sport_type(), pause_count, Get_sport_save_status(),
//                                   0, 0, 0);
// #endif
        misc_sport_data.sport_Function_state = Sport_state_stop;
#ifndef BSP_USING_PC_SIMULATOR
        sport_pause_calories();
        module_ms_app_sport_deinit_gps();
#endif
        if (Get_sport_save_status() && !misc_sport_data.is_auto_sport )
        {
            if (misc_sport_data.sport_is_app_sponsor == false)
            {
                if (Get_current_sporting_type() != SPORTING_Indoor_running_TYPE)
                {
                    mul_sport_set_mul_sport_end_time(mul_sport_get_timestamp());
                }
                if (Get_current_sporting_type() == SPORTING_swim_outdoor_TYPE || Get_current_sporting_type() == SPORTING_swim_indoor_TYPE)
                    module_ms_app_sport_set_points_flag(SPORT_POINTS_STOP);
                save_cur_sport_file_work_when_full();
                // extern void save_cur_sport_file_work_proc(void);
                // save_cur_sport_file_work_proc(); // 直接保存
                // save_cur_sport_record();//直接抽点
                 misc_sport_data.draw_points_flag = false;
            }
        }
        else
        {
            mul_sport_clear_cur_sport_id();
        }
        misc_sport_data.sport_upload_steps = 0;
        misc_sport_data.sport_upload_kcal = 0;
        misc_sport_data.sport_is_app_sponsor = false;
        misc_sport_data.is_auto_sport = false;
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
#if ZH_GPS_DRAW
        module_sport_app_free_gps();
#endif
        // stop_sport_counter();todo:by ly
    //if(module_ms_app_is_gps_sport_type(Get_current_sporting_type()))
        zh_miwear_sport_request(SportState_SPORT_STOP, pb_sport_type_trans(Get_current_sporting_type()));//停止GPS
    sport_state_act = 59;
#endif
        sport_state_log(2);
        return true;
    }
    else // 处于开启状态，则返回失败
    {
        return false;
    }
}

bool sport_discard(void)
{
    if (misc_sport_data.sport_interval_train_is_close) // 恢复间歇训练
    {
        module_ms_app_sport_set_sport_target(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_SWITCH);
        misc_sport_data.sport_interval_train_is_close = 0;
    }
    // 心率关闭
    //module_ms_app_sport_open_heart(0,0);
    /*if(get_heard_power_state() == true)
    {
        if (Get_Heart_Messure_State_Style() == ENUM_HEART_MESSUREING_AUTO)
        {
            //pm_sleep_mode_release(pm_mode_active);
        }

        Heart_Power_On_Off_Switch(false,false,0,ENUM_HEART_IDLE);
    }*/
    // set_hr_sport_mode(alg_prarmeter_mode_norm);
    misc_sport_data.is_auto_sport = false;
    auto_sport_ctrl_init(0);
    if (misc_sport_data.sport_Function_state != Sport_state_stop) // 不处于关闭状态，则进行关闭
    {
        /*if(Get_sport_save_status())
        {
            //mul_sport_save_cur_sport_file();
            //ThreadCom_Sport_Save_Data_Stop_Notif(0);
            if (misc_sport_data.sport_is_app_sponsor == false)
            {
                save_cur_sport_file_work_start();
            }
        }
        else*/
        {
            mul_sport_clear_cur_sport_id();
        }

        misc_sport_data.sport_Function_state = Sport_state_stop;
#if ZH_GPS_DRAW
        module_sport_app_free_gps();
#endif
        misc_sport_data.sport_is_app_sponsor = false;
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
        // stop_sport_counter();todo:by ly
        module_ms_app_sport_deinit_gps();
		 zh_miwear_sport_request(SportState_SPORT_STOP, pb_sport_type_trans(Get_current_sporting_type()));//开始sport
#if defined(ENUM_PROJECT_NAME_N65B_GLOBAL)
				 if ((module_ms_app_is_gps_sport_type(Get_current_sporting_type()) )){
						gps_clear_user_mark(GPS_USED_BY_PREPEAR_SPORT|GPS_USED_BY_SPORTING);
		//All_sport_Close_GPS();
				 	}
#endif
		
#endif
        return true;
        sport_state_log(2);
    }
    else // 处于开启状态，则返回失败
    {
        return false;
    }
}

void module_ms_exit_app_sport(void)
{
#if 0
    sport_stop();
#endif
    // 心率关闭
    module_ms_app_sport_open_heart(0,0);
    clear_all_sport_status();
#if INTERVAL_TRAINING_SELECT

    if (misc_sport_data.sport_interval_train_is_close) // 恢复间歇训练
    {
        module_ms_app_sport_set_sport_target(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_SWITCH);
        misc_sport_data.sport_interval_train_is_close = 0;
    }
#endif
    if(1)//interconnection_ioctl_is_report_sport_data_projection())//停止投屏
    {
        zh_sports_data_projection(PROJECTION_DISCONNECT);
    }
#ifndef BSP_USING_PC_SIMULATOR
        uint32_t end_timestamp = mul_sport_get_timestamp();
        uint32_t total_timestamp = end_timestamp-(sport_save_data.sport_time_start - mul_sport_get_time_zone_offset(sport_save_data.sport_time_zone));
         miwear_dev_app_event_set((uint8_t)SPORT_END_EVENT_NAME_ID, end_timestamp, total_timestamp
                                  , pb_sport_type_trans(Get_current_sporting_type()), pause_count,  Get_sport_save_status()==1?1:2,
                                  0, 0, 0);
#endif
    // todo:by ly
    //  if (get_heard_power_state() == true)
    //  {
    //      if (Get_Heart_Messure_State_Style() == ENUM_HEART_MESSUREING_AUTO)
    //      {
    //          //pm_sleep_mode_release(pm_mode_active);
    //      }

    //     Heart_Power_On_Off_Switch(false, false, 0, ENUM_HEART_IDLE);
    // }
    // set_hr_sport_mode(alg_prarmeter_mode_norm);
    misc_sport_data.is_auto_sport = false;
    if (misc_sport_data.sport_Function_state != Sport_state_stop) // 不处于关闭状态，则进行关闭
    {

        misc_sport_data.sport_upload_steps = 0;
        misc_sport_data.sport_upload_kcal = 0;
        misc_sport_data.sport_Function_state = Sport_state_stop;
        misc_sport_data.sport_is_app_sponsor = false;
#if ZH_GPS_DRAW
        module_sport_app_free_gps();
#endif 
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
        // stop_sport_counter();todo:by ly
        module_ms_app_sport_deinit_gps();
#endif
        sport_state_log(2);
    }
}

bool module_sport_app_send_app_sport_pause(void)
{
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
    if ((Get_current_sporting_type() != SPORTING_Outdoor_cycling_TYPE) || (misc_sport_data.sport_is_app_sponsor))
        zh_miwear_sport_request(SportState_SPORT_PAUSE, pb_sport_type_trans(Get_current_sporting_type()));
#endif
    return true;
}
#define TREADMILL_TIMEOUT 2 //跑步机delay用于暂停后有三秒钟倒计时不能传数据
bool sport_pause(void)
{

    printf("func:%s\n", __func__);
    pause_count++;//todo:by ly
#if 1
    if (misc_sport_data.sport_Function_state == Sport_state_start) // 处于开启状态，则进行暂停
    {
       // if (misc_sport_data.sport_is_app_sponsor || (module_ms_app_is_gps_sport_type(Get_current_sporting_type())))
        {
// #if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
// 			if((Get_current_sporting_type()!=SPORTING_Outdoor_cycling_TYPE)||(misc_sport_data.sport_is_app_sponsor))
//             zh_miwear_sport_request(SportState_SPORT_PAUSE, pb_sport_type_trans(Get_current_sporting_type()));
// #endif
        }
#ifndef BSP_USING_PC_SIMULATOR
        if(get_vibration_adjustment_status())
        {
            Set_Moto_Times_Frequence(NOW_VIBRATION_MODE_3,2);
        }
#endif
        misc_sport_data.sport_Function_state = Sport_state_pause;
		misc_sport_data.pausetostop = 0;
        // miss_gps_time = 0;todo:by ly
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
        sport_pause_calories();
#endif
        sport_state_log(3);
        misc_sport_data.treadmill_timeout = TREADMILL_TIMEOUT;
        return true;
    }
    else // 处于开启状态，则返回失败
    {
        return false;
    }
#endif
}

bool module_sport_app_send_app_sport_restart(void)
{
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
    if ((Get_current_sporting_type() != SPORTING_Outdoor_cycling_TYPE) || (misc_sport_data.sport_is_app_sponsor))
        zh_miwear_sport_request(SportState_SPORT_RESUME, pb_sport_type_trans(Get_current_sporting_type())); // pb_sport_trans_map[menu_sport_id]);
#endif
    return true;
}

bool sport_restart(void)
{
    if (misc_sport_data.sport_Function_state == Sport_state_pause) // 处于暂停状态，则进行开启
    {
       // if (misc_sport_data.sport_is_app_sponsor || (module_ms_app_is_gps_sport_type(Get_current_sporting_type())))
        {
            // printf("SportState_SPORT_PAUSE local_id:%d,id:%d",menu_sport_id,pb_sport_trans_map[menu_sport_id]);
// #if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
// 			if((Get_current_sporting_type()!=SPORTING_Outdoor_cycling_TYPE)||(misc_sport_data.sport_is_app_sponsor))
//             zh_miwear_sport_request(SportState_SPORT_RESUME, pb_sport_type_trans(Get_current_sporting_type())); // pb_sport_trans_map[menu_sport_id]);
// #endif
        }
#ifndef BSP_USING_PC_SIMULATOR
        if(get_vibration_adjustment_status())
        {
            Set_Moto_Times_Frequence(NOW_VIBRATION_MODE_3,2);
        }

		extern uint64_t ts_ms_course;
		ts_ms_course = get_wall_clock_time_counter()*1000;
#endif
        misc_sport_data.sport_Function_state = Sport_state_start;
		misc_sport_data.unwear_dura = 0xff;
		misc_sport_data.low_speed_cnt = 0;
        misc_sport_data.auto_pause_dst.cur_act_state = 1;
        misc_sport_data.gps_source = 0xff;
        //printf("mi_gps_rt_auto_pause_get_state EXT %d\n", misc_sport_data.auto_pause_dst.cur_act_state);
        // miss_gps_time = 0;todo:by ly
        if (misc_sport_data.sport_is_app_sponsor == false 
        && Get_current_sporting_type() != SPORTING_swim_indoor_TYPE
        && Get_current_sporting_type() != SPORTING_swim_outdoor_TYPE)
        {
            sport_resume_process_work_start();
        }
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
        sport_restart_calories();
#endif
        sport_state_log(4);
        // ThreadCom_Sport_Save_Data_Restart_Notif(0);
        return true;
    }
    else // 处于开启状态，则返回失败0
    {
        return false;
    }
}

uint16_t get_step_count = 0;
uint16_t sport_data_get_second_step(void)
{
    uint16_t return_step;
    return_step = get_step_count;
    get_step_count = 0;
    return return_step;
}
void sport_data_set_second_step(uint16_t step_data)
{
    get_step_count += step_data;
}
void sport_update_skipping_rope_count(uint32_t count, bool clear_flag)
{
    static uint32_t last_count = 0;
    if (clear_flag)
    {
        last_count = 0;
    }
    if (count > last_count)
    {
        uint32_t detail_count = count - last_count;
        sport_interval_training.current_count += detail_count;
    }
    last_count = count;
}
extern int Lcd_Pwm_Light_On_Notify_thread(uint8_t ISR);
extern void thread_gui_blacklight_on_thread(void);
#if 1                                                 // INTERVAL_TRAINING_SELECT
void Processing_after_interval_training(uint8_t flag) // flag->1:发停止命令,0->do not
{
    //if (module_ms_app_is_gps_sport_type(Get_current_sporting_type()))
    {
#ifndef BSP_USING_PC_SIMULATOR
        zh_miwear_sport_request(SportState_SPORT_STOP, pb_sport_type_trans(Get_current_sporting_type())); // pb_sport_trans_map[menu_sport_id]);
#endif
    }
     sport_state_act = 48;
    sport_stop();
    if (Get_sport_save_status())
    {
        module_ms_app_set_sport_list_usecount(Get_current_sporting_type());
        extern SPORT_save_data_t sport_save_sport_record_data;
        memcpy(&sport_save_sport_record_data, &sport_save_data, sizeof(sport_save_data));
        // sport_save_sport_record_data = sport_save_data;
        misc_sport_data.sport_recorde_type = Get_current_sporting_type();
        sport_save_sport_record_data.sport_save_data_record_types = Get_current_sporting_type();
        sport_save_sport_record_data.sport_save_data_sub_type = Get_current_sporting_subtype();
        sport_save_sport_record_data.sport_save_data_record_t.sport_seeting_choose_target = sport_setting_target_data[misc_sport_data.sport_recorde_type].sport_seeting_choose_target & 0x1e;
        misc_sport_data.sporting_to_sport_record_flag = true;
        // misc_sport_data.sporting_to_sport_record_flag = true;
        if (!misc_sport_data.sport_is_app_sponsor)
        {
            module_mul_sport_set_best_points(Get_current_sporting_type());
            // if(Get_current_sporting_type() == SPORTING_swim_indoor_TYPE||Get_current_sporting_type() == SPORTING_swim_outdoor_TYPE)
            // {
            //     Jump_App_And_Page(APP_DRAIN_WATER_STRING_ID, NULL);//排水
            //     return;
            // }
            if (1)//interconnection_ioctl_is_report_sport_data_projection())
            {
                zh_sports_data_projection(PROJECTION_REPORT);//报告
            }
            misc_sport_data.sport_loading_count = LOAD_TIME_OUT;
            printf("%s %d\n",__func__,__LINE__);
          //  Jump_App_And_Page(APP_SPORT_MAIN_STRING_ID, APP_SPORT_INTERVAL_FINISH_STRING_ID); //间歇训练load
        }
        else
        {
            // ThreadGui_TaskSubmit(TASK_MAIN_SPORTING_MENU, SECONDARY__SPORT_MEUN_END_MEUN);
        }
    }
    else
    {
      //  Jump_App_And_Page(APP_SPORT_MAIN_STRING_ID, APP_SPORT_INTERVAL_NOT_ENOUGH_STRING_ID);
       // extern void app_sport_return_list();
       // app_sport_return_list();
    }

    // if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
    // {
    //     // Lcd_Pwm_Light_On_Notify_thread(0);
    //     sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_ON);
    // }
    // else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
    // {
    //     // thread_gui_blacklight_on_thread();
    //     sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_SLEEP_OUT);
    // }
    // Set_Moto_Times_Frequence(VIBRATE_MODE_1, 1);
    // if (!Get_sport_save_status())
    // {
    //     ThreadTimer_Dynamic_GuiTimerStop();
    //     if ((module_ms_app_is_gps_sport_type(Get_current_sporting_type())) && flag)
    //     {
    //         // printf("SportState_SPORT_PAUSE local_id:%d,id:%d",menu_sport_id,pb_sport_trans_map[menu_sport_id]);
    //         miwear_sport_request(SportState_SPORT_STOP, pb_sport_type_trans(Get_current_sporting_type())); // pb_sport_trans_map[menu_sport_id]);
    //     }
    //     Gui_Refresh_Dynamic_Scroll_Init(); // 缓存动态刷新接口clear
    //     Scroll_Start_Init();
    //     Set_Current_Slide_Page_First_Status(0);
    //     Set_Scroll_Effect_Refesh_Style(0);
    //     Set_Current_Scroll_Position(0);
    //     // sport_start(Get_current_sporting_type());
    //     set_sport_meun_state(false);
    //     sport_stop();
    //     ThreadGui_TaskSubmit(TASK_MAIN_SPORTING_MENU, SECONDARY__SPORT_TRAIN_STOP_LESS);
    //     return;
    // }
    // else
    // {

    //     if ((module_ms_app_is_gps_sport_type(Get_current_sporting_type())) && flag)
    //     {
    //         // printf("SportState_SPORT_PAUSE local_id:%d,id:%d",menu_sport_id,pb_sport_trans_map[menu_sport_id]);
    //         miwear_sport_request(SportState_SPORT_STOP, pb_sport_type_trans(Get_current_sporting_type())); // pb_sport_trans_map[menu_sport_id]);
    //     }
    //     ThreadTimer_Dynamic_GuiTimerStop();
    //     // GuiTask_ParaInit(task_para_p, slide_interface_p, 0, 0, 0, 0);
    //     Gui_Refresh_Dynamic_Scroll_Init(); // 缓存动态刷新接口clear
    //     Scroll_Start_Init();
    //     Set_Current_Slide_Page_First_Status(0);
    //     Set_Scroll_Effect_Refesh_Style(0);
    //     Set_Current_Scroll_Position(0);
    //     // sport_start(Get_current_sporting_type());
    //     if (Get_current_sporting_type() == SPORTING_Indoor_running_TYPE)
    //     {
    //         sport_pause();
    //         ThreadGui_TaskSubmit(TASK_MAIN_SPORTING_MENU, SECONDARY__SPORT_DATA_CALIBRATION_REMIND);
    //     }
    //     else
    //     {
    //         sport_stop();
    //         set_sport_meun_state(false);
    //         if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_RELAX_SWITCH))
    //         {
    //             ThreadGui_TaskSubmit(TASK_MAIN_SPORTING_MENU, SECONDARY__SPORT_TRAIN_COMPLETE);
    //         }
    //         else
    //         {
    //             extern SPORT_save_data_t sport_save_sport_record_data;
    //             extern uint8_t sport_recorde_type;
    //             extern bool sporting_to_sport_record_flag;
    //             memcpy(&sport_save_sport_record_data, &sport_save_data, sizeof(sport_save_data));
    //             // sport_save_sport_record_data = sport_save_data;
    //             sport_recorde_type = Get_current_sporting_type();
    //             sport_save_sport_record_data.sport_save_data_record_types = Get_current_sporting_type();
    //             sport_save_sport_record_data.sport_save_data_record_t.sport_seeting_choose_target = sport_setting_target_data[sport_recorde_type].sport_seeting_choose_target & 0x1e;
    //             sporting_to_sport_record_flag = true;
    //             if (!misc_sport_data.sport_is_app_sponsor)
    //             {
    //                 module_mul_sport_set_best_points(Get_current_sporting_type());
    //                 ThreadGui_TaskSubmit(TASK_SPORT_RECORD, SECONDARY___SPORT_RECORD_DETAILED_DATA);
    //             }
    //             else
    //             {
    //                 ThreadGui_TaskSubmit(TASK_MAIN_SPORTING_MENU, SECONDARY__SPORT_MEUN_END_MEUN);
    //             }
    //         }
    //     }
    //     return;
    // }
}
void module_sport_app_sportting_change_page(void)
{
    sport_interval_training.segment_timestamp = mul_sport_get_timestamp();
    printf("%s %d\n", __func__, Get_current_sporting_subtype());
#ifndef BSP_USING_PC_SIMULATOR
    if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
    {
        rt_event_remind_ind_t remind_ind;
        remind_ind.event = REMIND_RAISE_HAND;
        ipc_send_msg_from_sensor_to_app(ZH_SENSOR_TO_APP_EVENT_REMIND_IND, sizeof(rt_event_remind_ind_t), &remind_ind);
    }

    if (Get_current_sporting_subtype())
    {
        if (Judge_Current_App_And_Page_Is_Running(APP_RUN_CLASS_MAIN_STRING_ID,PAGE_RUN_CLASS_RUNNING_STRING_ID))//strcmp(Get_Current_App_Id(), APP_RUN_CLASS_MAIN_STRING_ID) == 0 && strcmp(Get_Current_Page_Id(), PAGE_RUN_CLASS_RUNNING_STRING_ID) == 0)
        {
            // extern void app_sport_running_course_refresh_reload_page(void);
            // app_sport_running_course_refresh_reload_page();
            printf("strcmp complete\n");
			hl_if_data_t *msg = service_fill_msg(APP_INT, ZH_APP_INT_SPORTING_REFRESH_ID, NULL, 0);//刷新本页
			send_msg_to_ui_task(msg, sizeof(msg), NEED_WAKEUP_UI, NULL);
        }
        else
        {
            Jump_App_And_Page(APP_RUN_CLASS_MAIN_STRING_ID, PAGE_RUN_CLASS_RUNNING_STRING_ID);
        }
    }
    else
    {
        if (Judge_Current_App_And_Page_Is_Running(APP_SPORT_MAIN_STRING_ID,APP_SPORT_SPORTING_STRING_ID))//trcmp(Get_Current_App_Id(), APP_SPORT_MAIN_STRING_ID) == 0 && strcmp(Get_Current_Page_Id(), APP_SPORT_SPORTING_STRING_ID) == 0)
        {
            // extern void app_sport_ing_refresh_reload_page(void);
            // app_sport_ing_refresh_reload_page();
            printf("strcmp complete\n");
			hl_if_data_t *msg = service_fill_msg(APP_INT, ZH_APP_INT_SPORTING_REFRESH_ID, NULL, 0);//刷新本页
			send_msg_to_ui_task(msg, sizeof(msg), NEED_WAKEUP_UI, NULL);
        }
        else
        {
            Jump_App_And_Page(APP_SPORT_MAIN_STRING_ID, APP_SPORT_SPORTING_STRING_ID);
        }
    }
    if(get_vibration_adjustment_status())
    {
        Set_Moto_Times_Frequence(NOW_VIBRATION_MODE_3, 2);//震动切换状态
    }
#endif
}
void sport_data_interval_training_processing()
{
#if 0
    static uint32_t total_distance = 0 ;
    if (sport_save_data.sport_time_count == 0)
    {
        total_distance = 0;
    }
    uint32_t detail_distance = sport_save_data.sport_distance - total_distance;
    sport_interval_training.current_distance += detail_distance;
    total_distance = sport_save_data.sport_distance;
    zh_log_printk("detail:%d,last:%d,cur_total:%d\n", detail_distance, total_distance, sport_save_data.sport_distance);
#endif
    extern void set_sport_meun_id(uint16_t data);
    printf("[interval]mode = %d,type = %d,current_time_count = %d,distance = %d,count=%d,\
    train_timcount:%d,res_timcoun:%d\n", sport_interval_training.mode, sport_interval_training.type, sport_interval_training.current_time_count,
            sport_interval_training.current_distance, sport_interval_training.current_count,
            sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_time,
            sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_rest);
    if (sport_interval_training.mode == Sport_MODE_TIME)
    {

        if (sport_interval_training.type == INTERVAL_TRAINING_WARM_UP) // 热身
        {

            if (sport_interval_training.current_time_count < sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_time)
            {
                sport_interval_training.current_time_count++;
                if (sport_interval_training.current_time_count == sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_time)
                {

                    sport_interval_training.current_time_count = 0;
                    sport_interval_training.current_count = 0;
                    sport_interval_training.current_distance = 0;
                    sport_interval_training.segment_kcal = 0;
                    mul_sport_platform_change_sit_type(INTERVAL_TRAINING); // 切换状态,
                    sport_interval_training.type = INTERVAL_TRAINING;
                    sport_interval_training.completion_times++;
                    module_sport_app_sportting_change_page();
                    // todo: by ly
                    //  if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                    //  {
                    //      // Lcd_Pwm_Light_On_Notify_thread(0);
                    //      sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_ON);
                    //      // set_sport_meun_id(ID_COMPOSE(TASK_MAIN_SPORTING_MENU, module_ms_app_get_sport_class(Get_current_sporting_type())));
                    //  }
                    //  else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                    //  {
                    //      // thread_gui_blacklight_on_thread();
                    //      sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_SLEEP_OUT);
                    //      // set_sport_meun_id(ID_COMPOSE(TASK_MAIN_SPORTING_MENU, module_ms_app_get_sport_class(Get_current_sporting_type())));
                    //  }
                    //  else
                    //  {
                    //      module_sport_app_set_scroll_length(sport_interval_training.type);
                    //      module_ms_app_sport_select_class(Get_current_sporting_type());
                    //  }
                }
            }
            else
            {
                sport_interval_training.current_time_count = 0;
                sport_interval_training.current_count = 0;
                sport_interval_training.current_distance = 0;
                sport_interval_training.segment_kcal = 0;
                sport_interval_training.type = INTERVAL_TRAINING;
                // sport_interval_training.completion_times++;
            }
        }
        else if (sport_interval_training.type == INTERVAL_TRAINING) // 训练
        {
            if (sport_interval_training.current_time_count < sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_time)
            {
                sport_interval_training.current_time_count++;
                if (sport_interval_training.current_time_count == sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_time)
                {
                    if (!module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_RELAX_SWITCH) &&
                        sport_interval_training.completion_times == sport_interval_training.total_times)
                    {
                        sport_interval_training.type = 0;
                        sport_interval_training.current_time_count = 0;
                        sport_interval_training.segment_kcal = 0;
                        sport_interval_training.current_count = 0;
                        sport_interval_training.current_distance = 0;
                        Processing_after_interval_training(1);
                    }
                    else
                    {
                        sport_interval_training.type = INTERVAL_TRAINING_REST;
                        sport_interval_training.current_time_count = 0;
                        sport_interval_training.current_count = 0;
                        sport_interval_training.current_distance = 0;
                        sport_interval_training.segment_kcal = 0;
                        sport_interval_training.completion_times++;
                        if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_RELAX_SWITCH) &&
                            sport_interval_training.completion_times == sport_interval_training.total_times)
                        {
                            sport_interval_training.type = INTERVAL_TRAINING_RELAX;
                        }
                        mul_sport_platform_change_sit_type(sport_interval_training.type); // 切换状态,
                        module_sport_app_sportting_change_page();
                        // todo: by ly
                        //  if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                        //  {
                        //      // Lcd_Pwm_Light_On_Notify_thread(0);
                        //      sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_ON);
                        //      // set_sport_meun_id(ID_COMPOSE(TASK_MAIN_SPORTING_MENU, SECONDARY__SPORT_TRAIN_WARM_UP_LIST));
                        //  }
                        //  else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                        //  {
                        //      // thread_gui_blacklight_on_thread();
                        //      sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_SLEEP_OUT);
                        //      // set_sport_meun_id(ID_COMPOSE(TASK_MAIN_SPORTING_MENU, SECONDARY__SPORT_TRAIN_WARM_UP_LIST));
                        //  }
                        //  {
                        //      module_sport_app_set_scroll_length(sport_interval_training.type);
                        //      module_ms_app_sport_select_class(Get_current_sporting_type());
                        //  }
                    }
                }
            }
            else
            {
                sport_interval_training.current_time_count = 0;
                sport_interval_training.current_count = 0;
                sport_interval_training.current_distance = 0;
                sport_interval_training.type = INTERVAL_TRAINING_REST;
                sport_interval_training.segment_kcal = 0;
                if (!module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_RELAX_SWITCH) &&
                    sport_interval_training.completion_times == sport_interval_training.total_times)
                {
                    sport_interval_training.type = 0;
                    sport_interval_training.current_time_count = 0;
                    sport_interval_training.segment_kcal = 0;
                    Processing_after_interval_training(1);
                }
                mul_sport_platform_change_sit_type(sport_interval_training.type); // 切换状态,
            }
        }
        else if (sport_interval_training.type == INTERVAL_TRAINING_REST) // 休息
        {
            printf("INTERVAL_TRAINING_REST\n");
            if (sport_interval_training.current_time_count < sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_rest)
            {
                sport_interval_training.current_time_count++;
                if (sport_interval_training.current_time_count == sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_rest)
                {
                    sport_interval_training.current_time_count = 0;
                    sport_interval_training.current_count = 0;
                    sport_interval_training.current_distance = 0;
                    sport_interval_training.type = INTERVAL_TRAINING;
                    sport_interval_training.segment_kcal = 0;
                    sport_interval_training.completion_times++;
                    mul_sport_platform_change_sit_type(sport_interval_training.type); // 切换状态,
                    module_sport_app_sportting_change_page();
                    // todo: by ly
                    //  if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                    //  {
                    //      // Lcd_Pwm_Light_On_Notify_thread(0);
                    //      sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_ON);
                    //      // set_sport_meun_id(ID_COMPOSE(TASK_MAIN_SPORTING_MENU, module_ms_app_get_sport_class(Get_current_sporting_type())));
                    //  }
                    //  else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                    //  {
                    //      // thread_gui_blacklight_on_thread();
                    //      sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_SLEEP_OUT);
                    //      //  set_sport_meun_id(ID_COMPOSE(TASK_MAIN_SPORTING_MENU, module_ms_app_get_sport_class(Get_current_sporting_type())));
                    //  }
                    //  else
                    //  {
                    //      module_sport_app_set_scroll_length(sport_interval_training.type);
                    //      module_ms_app_sport_select_class(Get_current_sporting_type());
                    //  }
                }
            }
            else
            {
                sport_interval_training.current_time_count = 0;
                sport_interval_training.current_count = 0;
                sport_interval_training.current_distance = 0;
                sport_interval_training.type = INTERVAL_TRAINING;
                sport_interval_training.segment_kcal = 0;
                // sport_interval_training.completion_times++;
            }
        }
        else // 放松
        {
            if (sport_interval_training.current_time_count < sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_time)
            {
                sport_interval_training.current_time_count++;
                if (sport_interval_training.current_time_count == sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_time)
                {
                    sport_interval_training.current_time_count = 0;
                    sport_interval_training.current_count = 0;
                    sport_interval_training.current_distance = 0;
                    sport_interval_training.type = 0;
                    sport_interval_training.completion_times = 0;
                    sport_interval_training.segment_kcal = 0;
                    Processing_after_interval_training(1); // 结束
                }
            }
            else
            {
                sport_interval_training.current_time_count = 0;
                sport_interval_training.current_count = 0;
                sport_interval_training.current_distance = 0;
                sport_interval_training.type = INTERVAL_TRAINING;
                sport_interval_training.segment_kcal = 0;
                // sport_interval_training.completion_times++;
            }
        }
    }
    else if (sport_interval_training.mode == Sport_MODE_DISTANCE) // 距离
    {
        if (sport_interval_training.type == INTERVAL_TRAINING_WARM_UP) // 热身
        {

            if (sport_interval_training.current_distance < sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_dis)
            {
                sport_interval_training.current_time_count++;
            }
            else
            {
                sport_interval_training.current_time_count = 0;
                sport_interval_training.current_count = 0;
                sport_interval_training.current_distance = 0;
                sport_interval_training.type = INTERVAL_TRAINING;
                sport_interval_training.segment_kcal = 0;
                sport_interval_training.completion_times++;
                mul_sport_platform_change_sit_type(sport_interval_training.type); // 切换状态,
                module_sport_app_sportting_change_page();
                // todo: by ly
                //  if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                //  {
                //      // set_sport_meun_id(ID_COMPOSE(TASK_MAIN_SPORTING_MENU, module_ms_app_get_sport_class(Get_current_sporting_type())));
                //      //  Lcd_Pwm_Light_On_Notify_thread(0);
                //      sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_ON);
                //  }
                //  else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                //  {
                //      // thread_gui_blacklight_on_thread();
                //      sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_SLEEP_OUT);
                //      // set_sport_meun_id(ID_COMPOSE(TASK_MAIN_SPORTING_MENU, module_ms_app_get_sport_class(Get_current_sporting_type())));
                //  }
                //  else
                //  {
                //      module_sport_app_set_scroll_length(sport_interval_training.type);
                //      module_ms_app_sport_select_class(Get_current_sporting_type());
                //  }
            }
        }
        else if (sport_interval_training.type == INTERVAL_TRAINING) // 训练
        {
            if (sport_interval_training.current_distance < sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_dis)
            {
            }
            else
            {
                if (!module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_RELAX_SWITCH) &&
                    sport_interval_training.completion_times == sport_interval_training.total_times) // 结束
                {
                    sport_interval_training.type = 0;
                    sport_interval_training.current_time_count = 0;
                    sport_interval_training.current_count = 0;
                    sport_interval_training.current_distance = 0;
                    sport_interval_training.segment_kcal = 0;
                    Processing_after_interval_training(1);
                }
                else
                {
                    sport_interval_training.current_time_count = 0;
                    sport_interval_training.segment_kcal = 0;
                    sport_interval_training.current_count = 0;
                    sport_interval_training.current_distance = 0;
                    sport_interval_training.type = INTERVAL_TRAINING_REST;
                    sport_interval_training.completion_times++;
                    if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_RELAX_SWITCH) &&
                        sport_interval_training.completion_times == sport_interval_training.total_times)
                    {
                        sport_interval_training.type = INTERVAL_TRAINING_RELAX;
                    }
                    mul_sport_platform_change_sit_type(sport_interval_training.type); // 切换状态,
                    module_sport_app_sportting_change_page();
                    // todo: by ly
                    //  if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                    //  {
                    //      // Lcd_Pwm_Light_On_Notify_thread(0);
                    //      sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_ON);
                    //      // set_sport_meun_id(ID_COMPOSE(TASK_MAIN_SPORTING_MENU, SECONDARY__SPORT_TRAIN_WARM_UP_LIST));
                    //  }
                    //  else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                    //  {
                    //      // thread_gui_blacklight_on_thread();
                    //      sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_SLEEP_OUT);
                    //      // set_sport_meun_id(ID_COMPOSE(TASK_MAIN_SPORTING_MENU, SECONDARY__SPORT_TRAIN_WARM_UP_LIST));
                    //  }
                    //  else
                    //  {
                    //      module_sport_app_set_scroll_length(sport_interval_training.type);
                    //      module_ms_app_sport_select_class(Get_current_sporting_type());
                    //  }
                }
            }
        }
        else if (sport_interval_training.type == INTERVAL_TRAINING_REST) // 休息
        {
            if (sport_interval_training.current_time_count < sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_rest)
            {
                sport_interval_training.current_time_count++;
                if (sport_interval_training.current_time_count == sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_rest)
                {
                    sport_interval_training.current_time_count = 0;
                    sport_interval_training.current_count = 0;
                    sport_interval_training.current_distance = 0;
                    sport_interval_training.type = INTERVAL_TRAINING;
                    sport_interval_training.segment_kcal = 0;
                    sport_interval_training.completion_times++;
                    mul_sport_platform_change_sit_type(sport_interval_training.type); // 切换状态,
                    module_sport_app_sportting_change_page();
                    // todo: by ly
                    //  if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                    //  {
                    //      // set_sport_meun_id(ID_COMPOSE(TASK_MAIN_SPORTING_MENU, module_ms_app_get_sport_class(Get_current_sporting_type())));
                    //      // Lcd_Pwm_Light_On_Notify_thread(0);
                    //      sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_ON);
                    //  }
                    //  else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                    //  {
                    //      // thread_gui_blacklight_on_thread();
                    //      sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_SLEEP_OUT);
                    //      // set_sport_meun_id(ID_COMPOSE(TASK_MAIN_SPORTING_MENU, module_ms_app_get_sport_class(Get_current_sporting_type())));
                    //  }
                    //  else
                    //  {
                    //      //Set_Moto_Times_Frequence(VIBRATE_MODE_1, 1);
                    //      module_sport_app_set_scroll_length(sport_interval_training.type);
                    //      module_ms_app_sport_select_class(Get_current_sporting_type());
                    //  }
                }
            }
            //            else
            //            {
            //                sport_interval_training.current_time_count = 0;
            //                sport_interval_training.current_count = 0;
            //                sport_interval_training.current_distance = 0;
            //                sport_interval_training.type = INTERVAL_TRAINING;
            //            }
        }
        else // 放松
        {
            if (sport_interval_training.current_time_count < sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_rest)
            {
                sport_interval_training.current_time_count++;
                if (sport_interval_training.current_time_count == sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_rest)
                {
                    sport_interval_training.current_time_count = 0;
                    sport_interval_training.segment_kcal = 0;
                    sport_interval_training.current_count = 0;
                    sport_interval_training.current_distance = 0;
                    sport_interval_training.type = 0;
                    sport_interval_training.completion_times = 0;
                    Processing_after_interval_training(1); // 结束
                }
            }
            else
            {
                sport_interval_training.current_time_count = 0;
                sport_interval_training.segment_kcal = 0;
                sport_interval_training.current_count = 0;
                sport_interval_training.current_distance = 0;
                sport_interval_training.type = INTERVAL_TRAINING;
                // sport_interval_training.completion_times++;
            }
        }
    }
    else // 次数个数
    {
        if (sport_interval_training.type == INTERVAL_TRAINING_WARM_UP) // 热身
        {

            if ((sport_interval_training.current_count < sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_count &&
                 Get_current_sporting_type() == SPORTING_Skipping_rope_H_TYPE) ||
                (sport_interval_training.current_count < sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_times &&
                 Get_current_sporting_type() == SPORTING_Rowing_machine_TYPE))
            {
                sport_interval_training.current_time_count++;
            }
            else
            {
                sport_interval_training.current_time_count = 0;
                sport_interval_training.segment_kcal = 0;
                sport_interval_training.current_count = 0;
                sport_interval_training.current_distance = 0;
                sport_interval_training.type = INTERVAL_TRAINING;
                mul_sport_platform_change_sit_type(sport_interval_training.type); // 切换状态,
                sport_interval_training.completion_times++;
                module_sport_app_sportting_change_page();
                // if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                // {
                //     // Lcd_Pwm_Light_On_Notify_thread(0);
                //     sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_ON);
                //     // set_sport_meun_id(ID_COMPOSE(TASK_MAIN_SPORTING_MENU, module_ms_app_get_sport_class(Get_current_sporting_type())));
                // }
                // else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                // {
                //     // thread_gui_blacklight_on_thread();
                //     sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_SLEEP_OUT);
                //     // set_sport_meun_id(ID_COMPOSE(TASK_MAIN_SPORTING_MENU, module_ms_app_get_sport_class(Get_current_sporting_type())));
                // }
                // else
                // {
                //     module_sport_app_set_scroll_length(sport_interval_training.type);
                //     module_ms_app_sport_select_class(Get_current_sporting_type());
                // }
            }
        }
        else if (sport_interval_training.type == INTERVAL_TRAINING) // 训练
        {
            if ((sport_interval_training.current_count < sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_count &&
                 Get_current_sporting_type() == SPORTING_Skipping_rope_H_TYPE) ||
                (sport_interval_training.current_count < sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_times &&
                 Get_current_sporting_type() == SPORTING_Rowing_machine_TYPE))
            {
            }
            else
            {
                if (!module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_RELAX_SWITCH) &&
                    sport_interval_training.completion_times == sport_interval_training.total_times) // 结束
                {
                    sport_interval_training.type = 0;
                    sport_interval_training.current_time_count = 0;
                    sport_interval_training.segment_kcal = 0;
                    sport_interval_training.current_count = 0;
                    sport_interval_training.current_distance = 0;
                    Processing_after_interval_training(1);
                }
                else
                {
                    sport_interval_training.current_time_count = 0;
                    sport_interval_training.current_count = 0;
                    sport_interval_training.current_distance = 0;
                    sport_interval_training.segment_kcal = 0;
                    sport_interval_training.type = INTERVAL_TRAINING_REST;
                    sport_interval_training.completion_times++;
                    if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_RELAX_SWITCH) &&
                        sport_interval_training.completion_times == sport_interval_training.total_times)
                    {
                        sport_interval_training.type = INTERVAL_TRAINING_RELAX;
                    }
                    mul_sport_platform_change_sit_type(sport_interval_training.type); // 切换状态,
                    module_sport_app_sportting_change_page();
                    // if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                    // {
                    //     // Lcd_Pwm_Light_On_Notify_thread(0);
                    //     sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_ON);
                    //     // set_sport_meun_id(ID_COMPOSE(TASK_MAIN_SPORTING_MENU, SECONDARY__SPORT_TRAIN_WARM_UP_LIST));
                    // }
                    // else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                    // {
                    //     // thread_gui_blacklight_on_thread();
                    //     sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_SLEEP_OUT);
                    //     // set_sport_meun_id(ID_COMPOSE(TASK_MAIN_SPORTING_MENU, SECONDARY__SPORT_TRAIN_WARM_UP_LIST));
                    // }
                    // else
                    // {
                    //     module_sport_app_set_scroll_length(sport_interval_training.type);
                    //     module_ms_app_sport_select_class(Get_current_sporting_type());
                    // }
                }
            }
        }
        else if (sport_interval_training.type == INTERVAL_TRAINING_REST) // 休息
        {
            if (sport_interval_training.current_time_count < sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_rest)
            {
                sport_interval_training.current_time_count++;
                if (sport_interval_training.current_time_count == sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_rest)
                {
                    sport_interval_training.current_time_count = 0;
                    sport_interval_training.current_count = 0;
                    sport_interval_training.current_distance = 0;
                    sport_interval_training.type = INTERVAL_TRAINING;
                    sport_interval_training.segment_kcal = 0;
                    sport_interval_training.completion_times++;
                    mul_sport_platform_change_sit_type(sport_interval_training.type); // 切换状态,
                    module_sport_app_sportting_change_page();
                    // if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                    // {
                    //     // Lcd_Pwm_Light_On_Notify_thread(0);
                    //     sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_ON);
                    //     // set_sport_meun_id(ID_COMPOSE(TASK_MAIN_SPORTING_MENU, module_ms_app_get_sport_class(Get_current_sporting_type())));
                    // }
                    // else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                    // {
                    //     // thread_gui_blacklight_on_thread();
                    //     sys_lcd_report_status(0, LCD_LIGHT_DISPLAY_SLEEP_OUT);
                    //     // set_sport_meun_id(ID_COMPOSE(TASK_MAIN_SPORTING_MENU, module_ms_app_get_sport_class(Get_current_sporting_type())));
                    // }
                    // else
                    // {
                    //     module_sport_app_set_scroll_length(sport_interval_training.type);
                    //     module_ms_app_sport_select_class(Get_current_sporting_type());
                    // }
                }
            }
            else
            {
                sport_interval_training.current_time_count = 0;
                sport_interval_training.current_count = 0;
                sport_interval_training.type = INTERVAL_TRAINING;
                sport_interval_training.segment_kcal = 0;
            }
        }
        else // 放松
        {
            if (sport_interval_training.current_time_count < sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_rest)
            {
                sport_interval_training.current_time_count++;
                if (sport_interval_training.current_time_count == sport_setting_target_data[Get_current_sporting_type()].sport_interval_training_rest)
                {
                    sport_interval_training.current_time_count = 0;
                    sport_interval_training.segment_kcal = 0;
                    sport_interval_training.type = 0;
                    sport_interval_training.completion_times = 0;
                    Processing_after_interval_training(1); // 结束
                }
            }
            else
            {
                sport_interval_training.current_time_count = 0;
                sport_interval_training.segment_kcal = 0;
                sport_interval_training.type = INTERVAL_TRAINING;
                // sport_interval_training.completion_times++;
            }
        }
    }
}
#endif
//***************************************************跑步课程**************************************************************************
/*
基础入门3种
基础跑走结合:适合初级入门跑者，慢跑和快走交替循环，有助于身体适应跑步等有氧类活动。快走2,慢跑3,快走2,慢跑3,快走2,慢跑3,快走2,总共17分钟。
进阶跑走结合:适合初级入门跑者，慢跑和快走交替循环，适当增加慢跑时长，改善体能表现。快走2,慢跑5,快走2,慢跑5,快走2,慢跑5,快走2,总共23分钟。
基础慢跑:中低强度的跑步训练，适合初级入门跑者，渐进改善自身体能表现。快走3,慢跑21,快走3,总共27分钟。
减脂减重3种
基础燃脂跑:适合希望燃脂减重的跑者，增加能量消耗，促进减脂减重。快走3,慢跑30,快走2,总共35分钟。
进阶燃脂跑:单次长时间的中低强度训练，持续慢跑，持续减脂减重。快走3,慢跑40,快走2,总共45分钟。
MIIT 燃脂跑:中强度间歇燃脂的跑步训练，慢跑、中速跑的交替循环，提高燃脂效率。快走2,慢跑3,中速跑5,慢跑3,中速跑5,慢跑3,中速跑5,慢跑3,中速跑5,快走2,总共36分钟。
耐力提升2种
基础有氧耐力跑:适合希望提升跑步耐力的跑者，改善跑步耐力水平，提升有氧运动能力。快走3,慢跑30,快走2,总共35分钟。
进阶有氧耐力跑:单次长时间的慢跑训练，改善有氧耐力水平，提升长跑能力。快走3,慢跑60,快走2,总共65分钟。
心肺锻炼2种
基础间歇跑:适合希望改善心肺能力的跑者，改善心肺能力，改善最大摄氧量水平。快走3,快跑3,慢跑2,快跑3,慢跑2,快跑3,慢跑2,快跑3,慢跑2,快跑3,快走2,总共28分钟。
进阶间歇跑:适合希望改善心肺能力的跑者，高强度的刺激心肺，提升最大摄氧量水平。快走3,快跑5,慢跑2,快跑5,慢跑2,快跑5,慢跑2,快跑5,慢跑2,快跑5,快走2,总共38分钟。
*/
bool module_sport_app_course_is_sportting(void)
{
    bool flag = false;
    if(mul_sport_platform_get_sport_next_sit_type() != SIT_ACTIVITY)
    {
        flag = true;
    }
    return flag;
}
void sport_course_second_processing()
{
    printf("time_count:%d,total_time:%d,curr_sub:%d,total_sub:%d,sub_type:%d\n",sport_running_course.current_course_time_count,sport_running_course.total_course_time_count
    ,sport_running_course.current_subsection,sport_running_course.total_subsection,sport_running_course.current_sub_type);
    sport_running_course.current_course_time_count++;
    if (sport_running_course.current_course_time_count < sport_running_course.total_course_time_count)
    {
       
    }
    else // 切换状态
    {
#ifndef BSP_USING_PC_SIMULATOR
    if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
    {
        rt_event_remind_ind_t remind_ind;
        remind_ind.event = REMIND_RAISE_HAND;
        ipc_send_msg_from_sensor_to_app(ZH_SENSOR_TO_APP_EVENT_REMIND_IND, sizeof(rt_event_remind_ind_t), &remind_ind);
    }
    if(get_vibration_adjustment_status())
    {
        Set_Moto_Times_Frequence(NOW_VIBRATION_MODE_3, 2);//震动切换状态
    }
#endif
        if (sport_running_course.current_subsection < sport_running_course.total_subsection)
        {
            sport_running_course.current_subsection++;
            sport_running_course.current_sub_type = (sport_course_array[sport_running_course.current_subsection]) >> 8;
            sport_running_course.current_course_time_count = 0;
            sport_running_course.total_course_time_count = ((sport_course_array[sport_running_course.current_subsection]) & 0xff)*60;
           // extern void set_sport_run_remind_state(bool state);
           // set_sport_run_remind_state(1);
    //        if(Judge_Current_App_And_Page_Is_Running(APP_RUN_CLASS_MAIN_STRING_ID,PAGE_RUN_CLASS_RUNNING_STRING_ID))//strcmp(Get_Current_App_Id(),APP_RUN_CLASS_MAIN_STRING_ID) == 0&&strcmp(Get_Current_Page_Id(),PAGE_RUN_CLASS_RUNNING_STRING_ID) == 0)
    //        {
    //            //extern void app_sport_running_course_refresh_reload_page(void);
    //            //app_sport_running_course_refresh_reload_page();
			 //   printf("strcmp complete\n");
				//hl_if_data_t *msg = service_fill_msg(APP_INT, ZH_APP_INT_SPORTING_REFRESH_ID, NULL, 0);//刷新本页
				//send_msg_to_ui_task(msg, sizeof(msg), NEED_WAKEUP_UI, NULL);
    //            //printf("strcmp complete\n");
    //            //Jump_App_And_Page(APP_RUN_CLASS_MAIN_STRING_ID, PAGE_RUN_CLASS_RUNNING_STRING_ID);//先jump后面修改
    //        }
    //        else
    //        {
    //            Jump_App_And_Page(APP_RUN_CLASS_MAIN_STRING_ID, PAGE_RUN_CLASS_RUNNING_STRING_ID);
    //        }
            mul_sport_platform_change_sit_type((SPORT_interval_training_type)sport_running_course.current_sub_type); // 切换状态,
        }
        else
        {
            if (misc_sport_data.sport_Function_state == Sport_state_start) // 处于开启状态，则进行暂停
            {
                sport_state_act  = 13;
            }
            module_sport_app_send_app_sport_pause();
            sport_pause();
          
            sport_running_course.current_sub_type = Sport_Course_Sub_Null;
      //      Jump_App_And_Page(APP_RUN_CLASS_MAIN_STRING_ID, PAGE_RUN_CLASS_FINISH_STRING_ID);
            // 结束
        }
    }
}
void sport_data_running_course_processing(void)
{
    // sport_running_course.sport_course_type = 10;
    // init_sport_course_somethings(sport_running_course.sport_course_type);
    // for(uint8_t j = 1; j < sport_running_course.total_subsection+1; j++)
    // {

    //     printf("j:%d,total_subsection:%d,to_time:%d,sub_type:%d,time:%d\n",j,sport_running_course.total_subsection,sport_running_course.total_time_count,(sport_course_array[j])>>8,(sport_course_array[j])&0xff);

    // }
    if (sport_running_course.current_sub_type == Beat_It_Type) // 快走
    {
        // todo
        sport_course_second_processing();
    }
    else if (sport_running_course.current_sub_type == Jogging_Type) // 慢跑
    {
        // todo
        sport_course_second_processing();
    }
    else if (sport_running_course.current_sub_type == Moderate_pace_Type) // 中速跑
    {
        // todo
        sport_course_second_processing();
    }
    else if (sport_running_course.current_sub_type == Run_Fast_Type) // 快跑
    {
        // todo
        sport_course_second_processing();
    }
}
void clear_sport_remind_state()
{
#if 1 // todo: by ly
    if (sport_remind_struct.sport_time1_switch) //过低
    {
        sport_remind_struct.sport_timedelay1++;
        uint16_t delay_count = 60;
        switch (sport_remind_struct.sport_timecount1_keep)
        {
        case 8:
        {
            delay_count = 600;
        }
        break;
        case 4:
        {
            delay_count = 300;
        }
        break;
        case 2:
        {
            delay_count = 180;
        }
        break;
        default:
        {
            delay_count = 60;
        }
        break;
        }
        if (sport_remind_struct.sport_timedelay1 == delay_count)
        {
            sport_remind_struct.sport_time1_switch = false;
            sport_remind_struct.sport_timecount1 = 0;
            sport_remind_struct.sport_timedelay1 = 0;
        }
    }
    if (sport_remind_struct.sport_time2_switch) //保持
    {
        sport_remind_struct.sport_timedelay2++;
//        if (sport_remind_struct.sport_timedelay2 == 180)
        {
            sport_remind_struct.sport_time2_switch = false;
            sport_remind_struct.sport_timecount2 = 0;
            sport_remind_struct.sport_timedelay2 = 0;
        }
    }
    if (sport_remind_struct.sport_time3_switch) //过高
    {
        sport_remind_struct.sport_timedelay3++;
         uint16_t delay_count = 60;
        switch (sport_remind_struct.sport_timecount3_keep)
        {
        case 8:
        {
            delay_count = 600;
        }
        break;
        case 4:
        {
            delay_count = 300;
        }
        break;
        case 2:
        {
            delay_count = 180;
        }
        break;
        default:
        {
            delay_count = 60;
        }
        break;
        }       
        if (sport_remind_struct.sport_timedelay3 == delay_count)
        {
            sport_remind_struct.sport_time3_switch = false;
            sport_remind_struct.sport_timecount3 = 0;
            sport_remind_struct.sport_timedelay3 = 0;
        }
    }
    if (sport_remind_struct.sport_hr_remind_switch)
    {
        sport_remind_struct.sport_hr_timedelay++;
        uint16_t delay_count = 60;
        switch (sport_remind_struct.hr_remind_keep)
        {
        case 8:
        {
            delay_count = 600;
        }
        break;
        case 4:
        {
            delay_count = 300;
        }
        break;
        case 2:
        {
            delay_count = 180;
        }
        break;
        default:
        {
            delay_count = 60;
        }
        break;
        }
        if (sport_remind_struct.sport_hr_timedelay == delay_count)
        {
            sport_remind_struct.sport_hr_remind_switch = false;
            sport_remind_struct.sport_hr_timeout = 0;
            sport_remind_struct.sport_hr_timedelay = 0;
        }
    }

    // 心率区间提醒清除状态
    if (sport_remind_struct.hr_inter_high_switch)
    {
        sport_remind_struct.hr_inter_delay_high++;
        uint16_t delay_count = 60;
        switch (sport_remind_struct.hr_inter_high_keep)
        {
        case 8:
        {
            delay_count = 600;
        }
        break;
        case 4:
        {
            delay_count = 300;
        }
        break;
        case 2:
        {
            delay_count = 180;
        }
        break;
        default:
        {
            delay_count = 60;
        }
        break;
        }

        if (sport_remind_struct.hr_inter_delay_high == delay_count)
        {
            sport_remind_struct.hr_inter_high_switch = false;
            sport_remind_struct.hr_inter_timecount_high = 0;
            sport_remind_struct.hr_inter_delay_high = 0;
        }
    }
    if (sport_remind_struct.hr_inter_low_switch)
    {
        sport_remind_struct.hr_inter_delay_low++;
        uint16_t delay_count = 60;
        switch (sport_remind_struct.hr_inter_low_keep)
        {
        case 8:
        {
            delay_count = 600;
        }
        break;
        case 4:
        {
            delay_count = 300;
        }
        break;
        case 2:
        {
            delay_count = 180;
        }
        break;
        default:
        {
            delay_count = 60;
        }
        break;
        }

        if (sport_remind_struct.hr_inter_delay_low == delay_count)
        {
            sport_remind_struct.hr_inter_low_switch = false;
            sport_remind_struct.hr_inter_timecount_low = 0;
            sport_remind_struct.hr_inter_delay_low = 0;
        }
    }
    // 智能陪跑
    if (sport_remind_struct.auto_pace_backward_switch)
    {
        sport_remind_struct.auto_pace_delay_backward++;
        uint16_t delay_count = 60 * 5;
        switch (sport_remind_struct.auto_pace_backward_keep)
        {
        case 2:
        {
            delay_count = 60 * 10;
        }
        break;
        default:
        {
            delay_count = 60 * 5;
        }
        break;
        }
        //if (sport_remind_struct.auto_pace_delay_backward == delay_count)
        {
            sport_remind_struct.auto_pace_backward_switch = false;
            sport_remind_struct.auto_pace_timecount_backward = 0;
            sport_remind_struct.auto_pace_delay_backward = 0;
        }
    }
    if (sport_remind_struct.auto_pace_lead_switch)
    {
        //sport_remind_struct.auto_pace_delay_lead++;
        uint16_t delay_count = 60 * 5;
        switch (sport_remind_struct.auto_pace_lead_keep)
        {
        case 2:
        {
            delay_count = 60 * 10;
        }
        break;
        default:
        {
            delay_count = 60 * 5;
        }
        break;
        }
        ///if (sport_remind_struct.auto_pace_delay_lead == delay_count)
        {
            sport_remind_struct.auto_pace_lead_switch = false;
            sport_remind_struct.auto_pace_timecount_lead = 0;
            sport_remind_struct.auto_pace_delay_lead = 0;
        }
    }
#endif
}
uint32_t sport_event_req = 0;
uint32_t sport_event_ongo = 0;

uint32_t Get_sport_event_ongo(void)
{
    return sport_event_ongo;
}

uint8_t sport_disp_timeout = 0;
uint8_t sport_event_wait = 0;
uint8_t sport_event_holding = 0;
uint8_t sport_event_subtype = 0;
static uint32_t status[60] = {0}; // 数组增大防止越界
bool get_remind_status(uint16_t select)
{

    if (select >= 1 && select <= 31)
    {
        if (!((status[0] >> select) & 1))
        {
            return true;
        }
    }
    else if (select >= 32)
    {
        uint8_t index = select / 32;
        uint16_t choose = select % 32;
        if (!((status[index] >> choose) & 1))
        {
            return true;
        }
    }
    return false;
}
void setting_remind_status(uint16_t select)
{

    if (select >= 1 && select <= 31)
    {
        status[0] |= 1 << select;
    }
    else if (select >= 32)
    {
        uint8_t index = select / 32;
        uint16_t choose = select % 32;
        status[index] |= 1 << choose;
    }
}
void clear_all_sport_status()
{
    printf("clear_all_sport_status\n");
    memset(status, 0, sizeof(status));
    memset(&sport_remind_struct, 0, sizeof(sport_remind_struct));
    sport_event_req = 0;
    sport_event_ongo = 0;
    sport_disp_timeout = 0;
    sport_event_wait = 0;
    sport_event_holding = 0;
    sport_event_subtype = 0;
}
extern void set_sr_data_best_score_type(uint8_t type);
uint16_t test_number = 0;
void test_remind_d(void)
{
    // uint16_t test[] = 
    // {
    //     ZH_REMIND_SPORTING_REMIND_DISTANCE_TARGET_STRING_ID,
    //     ZH_REMIND_SPORTING_REMIND_HIGH_HEART_RATE_STRING_ID,
    //     ZH_REMIND_SPORTING_REMIND__TIMES__TARGET_STRING_ID,
    //     ZH_REMIND_SPORTING_REMIND_TIME_TARGET_STRING_ID,
    //     ZH_REMIND_SPORTING_REMIND_KCAL_TARGET_STRING_ID,
    //     ZH_REMIND_SPORTING_REMIND_BEST_SCORE_STRING_ID,
    //     ZH_REMIND_SPORTING_REMIND_DIS_INTEGER_STRING_ID,
    //     ZH_REMIND_SPORTING_REMIND_SPEED_STRING_ID,
    //     ZH_REMIND_SPORTING_REMIND_PACE_STRING_ID,
    //     ZH_REMIND_SPORTING_REMIND_ENERGY_SUPPLY_STRING_ID,
    //     ZH_REMIND_SPORTING_REMIND_PHONE_CONNET_STRING_ID,
    //     ZH_REMIND_SPORTING_REMIND_PHONE_DISCONNET_STRING_ID,
    //     ZH_REMIND_SPORTING_REMIND_HEART_STRING_ID,
    //     ZH_REMIND_SPORTING_REMIND_INTELLIGENT_RUN_STRING_ID,
    // };
    // if(sport_save_data.sport_time_count%30 == 0)
    // {

    //         Jump_Popup_And_event(test[test_number%sizeof(test)],NULL);  
    //         test_number++;   
    // }      

}
uint32_t get_sport_data_best_score_distance(void)
{
#if 1
	if(Get_current_sporting_type() == SPORTING_Outdoor_running_TYPE)
	{
		return Sport_Best_Data[BEST_OUTDOOR_RUNNING].distance;
	}
	else if(Get_current_sporting_type() == SPORTING_Indoor_running_TYPE)
	{
		return Sport_Best_Data[BEST_INDOOR_RUNNING].distance;
	}
	else if(Get_current_sporting_type() == SPORTING_Outdoor_walking_TYPE)
	{
		return Sport_Best_Data[BEST_OUTDOOR_WALK].distance;
	}
	else
	{
		return Sport_Best_Data[BEST_OUTDOOR_CYCLING].distance;	
	}
#endif
}
uint32_t get_sport_data_best_score_time(void)
{
#if 1
	if(Get_current_sporting_type() == SPORTING_Outdoor_running_TYPE)
	{
		return Sport_Best_Data[BEST_OUTDOOR_RUNNING].duration;
	}
	else if(Get_current_sporting_type() == SPORTING_Indoor_running_TYPE)
	{
		return Sport_Best_Data[BEST_INDOOR_RUNNING].duration;
	}
	else if(Get_current_sporting_type() == SPORTING_Outdoor_walking_TYPE)
	{
		return Sport_Best_Data[BEST_OUTDOOR_WALK].duration;
	}
	else
	{
		return Sport_Best_Data[BEST_OUTDOOR_CYCLING].duration;	
	}
#endif
}
void pop_sport_event(void)
{
#define MAX_LOG_SIZE 300
    char* tmp_buff = NULL;
    tmp_buff = malloc(MAX_LOG_SIZE);
#if 1
    printf("pop_sport_event %04x  %04x %d,second:%d\n", sport_event_ongo, sport_event_req, sport_disp_timeout, sport_event_subtype);
    if ((sport_event_ongo == 0 && sport_event_req) || (sport_disp_timeout >= 3 && sport_event_req && sport_event_req >= sport_event_ongo))
    {
        uint8_t moto_intensity = 0;
#if 0
        if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
        {
            Lcd_Pwm_Light_On_Notify_thread(0);
        }
        else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
        {
            thread_gui_blacklight_on_thread();
        }
#endif
        uint16_t len = 0;
        if (tmp_buff)
        {
            len = snprintf(tmp_buff, MAX_LOG_SIZE, "e_req:0x%x on:0x%x ", sport_event_req, sport_event_ongo);
        }
        uint8_t moto_count = 2;
        if (sport_event_req & 1 << COUNT_TARGRT_EVT || sport_event_req & 1 << DURA_TARGRT_EVT || sport_event_req & 1 << CAL_TARGRT_EVT || sport_event_req & 1 << DIST_TARGRT_EVT||
        sport_event_req & 1 << LOCAL_INFO_EVT )
        {
            moto_intensity = 1;// NOW_VIBRATION_MODE_3;
            moto_count = 2;
        }
        else if(sport_event_req & 1 << HR_ZONES_EVT || sport_event_req & 1 << MAX_HR_EVT || sport_event_req & 1 << ENERGY_EVT)
        {
             // - 运动中的心率区间/心率过高/能量补给提醒连续长振
            moto_intensity = 1;// NOW_VIBRATION_MODE_8;
            moto_count = 1;            
        }
        else
        {
            moto_intensity = 4;// NOW_VIBRATION_MODE_3;
        }
        if (sport_event_req & 1 << MAX_HR_EVT)
        {
   //         if (tmp_buff)
   //         {
   //             uint16_t lens = snprintf(tmp_buff + len, MAX_LOG_SIZE - len, "id:%d,tar:%d,hr_v:%d\r\n",
   //                                      ZH_REMIND_SPORTING_REMIND_HIGH_HEART_RATE_STRING_ID,
   //                                      sport_setting_target_data[Get_current_sporting_type()].sport_heart_rate_warn_value,
   //                                      sport_save_data.sport_heart_rate);
   //             len += lens;
   //         }
   //         sport_event_ongo = 1 << MAX_HR_EVT;
			//Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_HIGH_HEART_RATE_STRING_ID,NULL);
            //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_HIGH_HR, SECONDARY__1);
        }
        else if (sport_event_req & 1 << COUNT_TARGRT_EVT)
        {
   //         if (tmp_buff)
   //         {
   //             uint16_t lens = snprintf(tmp_buff + len, MAX_LOG_SIZE - len, "id:%d,tar:%d,count:%d\r\n",
   //                                      ZH_REMIND_SPORTING_REMIND__TIMES__TARGET_STRING_ID,
   //                                      sport_setting_target_data[Get_current_sporting_type()].sport_seeting_count_data,
   //                                      sport_save_data.sport_rm_count);
   //             len += lens;
   //         }
   //         sport_event_ongo = 1 << COUNT_TARGRT_EVT;
			//Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND__TIMES__TARGET_STRING_ID,NULL);
           // Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_COUNT_STANDARD, SECONDARY__1);

        }
        else if (sport_event_req & 1 << DURA_TARGRT_EVT)
        {
   //         if (tmp_buff)
   //         {
   //             uint16_t lens = snprintf(tmp_buff + len, MAX_LOG_SIZE - len, "id:%d,tar:%d,time:%d\r\n",
   //                                      ZH_REMIND_SPORTING_REMIND_TIME_TARGET_STRING_ID,
   //                                      sport_setting_target_data[Get_current_sporting_type()].sport_seeting_time_data,
   //                                      sport_save_data.sport_time_count);
   //             len += lens;
   //         }
   //         sport_event_ongo = 1 << DURA_TARGRT_EVT;					
			//Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_TIME_TARGET_STRING_ID,NULL);
           // Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_TIME_STANDARD, SECONDARY__1);
        }
        else if (sport_event_req & 1 << CAL_TARGRT_EVT)
        {
   //         if (tmp_buff)
   //         {
   //             uint16_t lens = snprintf(tmp_buff + len, MAX_LOG_SIZE - len, "id:%d,tar:%d,kcal:%lf\r\n",
   //                                      ZH_REMIND_SPORTING_REMIND_KCAL_TARGET_STRING_ID,
   //                                      sport_setting_target_data[Get_current_sporting_type()].sport_seeting_consume_data,
   //                                      sport_save_data.sport_consume);
   //             len += lens;
   //         }
   //         sport_event_ongo = 1 << CAL_TARGRT_EVT;
			//Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_KCAL_TARGET_STRING_ID,NULL);
           // Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_CALORIE_STANDARD, SECONDARY__1);
        }

        else if (sport_event_req & 1 << DIST_TARGRT_EVT)
        {
   //         if (tmp_buff)
   //         {
   //             uint16_t lens = snprintf(tmp_buff + len, MAX_LOG_SIZE - len, "id:%d,tar:%d,dis:%d\r\n",
   //                                      ZH_REMIND_SPORTING_REMIND_DISTANCE_TARGET_STRING_ID,
   //                                      sport_setting_target_data[Get_current_sporting_type()].sport_seeting_distance_data,
   //                                      sport_save_data.sport_distance);
   //             len += lens;
   //         }
   //         sport_event_ongo = 1 << DIST_TARGRT_EVT;
			//Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_DISTANCE_TARGET_STRING_ID,NULL);
			//
           // Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_DISTANCE_STANDARD, SECONDARY__1);
        }
        else if (sport_event_req & 1 << DIST_BEST_EVT)
        {
   //         if (tmp_buff)
   //         {
   //             uint16_t lens = snprintf(tmp_buff + len, MAX_LOG_SIZE - len, "id:%d,bset:%d,dis:%d\r\n",
   //                                      ZH_REMIND_SPORTING_REMIND_BEST_SCORE_STRING_ID,
   //                                      get_sport_data_best_score_distance(),
   //                                      sport_save_data.sport_distance);
   //             len += lens;
   //         }
   //         sport_event_ongo = 1 << DIST_BEST_EVT;
   //         set_sr_data_best_score_type(1);
   //         //module_mul_sport_set_best_points(Get_current_sporting_type());
			//Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_BEST_SCORE_STRING_ID,NULL);
           // Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_BEST_DISTANCE_POINTS, SECONDARY__1);
        }
        else if (sport_event_req & 1 << DURA_BEST_EVT)
        {
   //         if (tmp_buff)
   //         {
   //             uint16_t lens = snprintf(tmp_buff + len, MAX_LOG_SIZE - len, "id:%d,bset:%d,time:%d\r\n",
   //                                      ZH_REMIND_SPORTING_REMIND_BEST_SCORE_STRING_ID,
   //                                      get_sport_data_best_score_time(),
   //                                      sport_save_data.sport_time_count);
   //             len += lens;
   //         }
   //         sport_event_ongo = 1 << DURA_BEST_EVT;
   //         set_sr_data_best_score_type(0);
   //         //module_mul_sport_set_best_points(Get_current_sporting_type());
			//Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_BEST_SCORE_STRING_ID,NULL);
           // Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_BEST_DURATION_POINTS, SECONDARY__1);
        }
        else if (sport_event_req & 1 << KM_EVT)
        {
   //         if (tmp_buff)
   //         {
   //             uint16_t lens = snprintf(tmp_buff + len, MAX_LOG_SIZE - len, "id:%d,tar:%d,dis:%d\r\n",
   //                                      ZH_REMIND_SPORTING_REMIND_DIS_INTEGER_STRING_ID,
   //                                      sport_setting_target_data[Get_current_sporting_type()].sport_distance_remind,
   //                                      sport_save_data.sport_distance);
   //             len += lens;
   //         }
   //         sport_event_ongo = 1 << KM_EVT;
			//Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_DIS_INTEGER_STRING_ID,NULL);
            //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_DISTANCE_WHOLE_KILOMTER, SECONDARY__1);
        }
        else if (sport_event_req & 1 << PACE_EVT)
        {
            sport_event_ongo = 1 << PACE_EVT;
            //if (sport_event_subtype == PACE_SPEED_HIGH)
            //{
            //    if (Get_current_sporting_type() == SPORTING_Outdoor_cycling_TYPE)
            //    {
            //        set_sr_speed_suggest_remind(3);
            //        Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_SPEED_STRING_ID, NULL);
            //    }
            //    else
            //    {
            //        set_sr_pace_suggest_remind(3);
            //        Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_PACE_STRING_ID, NULL);
            //    }
            //  //  Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_PACE_SPEED_HIGH, SECONDARY__1);
            //}
            //else if (sport_event_subtype == PACE_SPEED_LOW)
            //{
            //    if (Get_current_sporting_type() == SPORTING_Outdoor_cycling_TYPE)
            //    {
            //        set_sr_speed_suggest_remind(1);
            //        Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_SPEED_STRING_ID, NULL);
            //    }
            //    else
            //    {
            //        set_sr_pace_suggest_remind(1);
            //        Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_PACE_STRING_ID, NULL);
            //    }
            //    //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_PACE_SPEED_LOW, SECONDARY__1);
            //}
            //else
            //{
            //    if (Get_current_sporting_type() == SPORTING_Outdoor_cycling_TYPE)
            //    {
            //        set_sr_speed_suggest_remind(2);
            //        Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_SPEED_STRING_ID, NULL);
            //    }
            //    else
            //    {
            //        set_sr_pace_suggest_remind(2);
            //        Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_PACE_STRING_ID, NULL);
            //    }
            //    //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_PACE_SPEED_HOLD, SECONDARY__1);
            //}
            //if (tmp_buff)
            //{
            //    if (Get_current_sporting_type() == SPORTING_Outdoor_cycling_TYPE)
            //    {
            //        uint16_t lens = snprintf(tmp_buff + len, MAX_LOG_SIZE - len, "id:%d,sec:%d,tar:%d,speed:%d\r\n",
            //                                 ZH_REMIND_SPORTING_REMIND_SPEED_STRING_ID,
            //                                 get_sr_speed_suggest_remind(),
            //                                 sport_setting_target_data[Get_current_sporting_type()].sport_pace_or_speed_remind,
            //                                 sport_save_data.sport_Speed);
            //        len += lens;
            //    }
            //    else
            //    {
            //        uint16_t lens = snprintf(tmp_buff + len, MAX_LOG_SIZE - len, "id:%d,sec:%d,tar:%d,pace:%d\r\n",
            //                                 ZH_REMIND_SPORTING_REMIND_PACE_STRING_ID,
            //                                 get_sr_pace_suggest_remind(),
            //                                 sport_setting_target_data[Get_current_sporting_type()].sport_pace_or_speed_remind,
            //                                 sport_save_data.sport_Speed_distribution);
            //        len += lens;
            //    }
            //}
        }
        else if (sport_event_req & 1 << HR_CHANGING_EVT)
        {
            sport_event_ongo = 1 << HR_CHANGING_EVT;
        }
        else if (sport_event_req & 1 << ENERGY_EVT)
        {
   //         if (tmp_buff)
   //         {
   //             uint16_t lens = snprintf(tmp_buff + len, MAX_LOG_SIZE - len, "id:%d,sec:%d,tar:%d,%d,dis:%d,tim:%d\r\n",
   //                                      ZH_REMIND_SPORTING_REMIND_ENERGY_SUPPLY_STRING_ID,
   //                                      get_sr_data_energy_remind_type(),
   //                                      sport_setting_target_data[Get_current_sporting_type()].sport_energy_supply_remind_dis,
   //                                      sport_setting_target_data[Get_current_sporting_type()].sport_energy_supply_remind_time,
   //                                      sport_save_data.sport_distance,
   //                                      sport_save_data.sport_time_count);
   //             len += lens;
   //         }
   //         sport_event_ongo = 1 << ENERGY_EVT;
			//Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_ENERGY_SUPPLY_STRING_ID,NULL);
           // Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_ENERGY_SUPPLY_REMIND, SECONDARY__1);
        }
        else if (sport_event_req & 1 << LOCAL_INFO_EVT)
        {
            sport_event_ongo = 1 << LOCAL_INFO_EVT;
            // if (sport_event_subtype == 1)
            //{
            //	Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_PHONE_CONNET_STRING_ID,NULL);
            //   // Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_PHONE_CONNECT, SECONDARY__1);
            //}
            //else
            //{
            //	Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_PHONE_DISCONNET_STRING_ID,NULL);
            //   // Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_APP_DISCONNECT, SECONDARY__1);
            //}
            //if (tmp_buff)
            //{
            //    uint16_t lens = snprintf(tmp_buff + len, MAX_LOG_SIZE - len, "id:%d,sec:%d\r\n",
            //                             sport_event_subtype == 1 ? ZH_REMIND_SPORTING_REMIND_PHONE_CONNET_STRING_ID : ZH_REMIND_SPORTING_REMIND_PHONE_DISCONNET_STRING_ID,
            //                             sport_event_subtype);
            //    len += lens;
            //}
        }
        else if(sport_event_req & 1 << HR_ZONES_EVT)
        {
   /*         if (tmp_buff)
            {
                uint16_t lens = snprintf(tmp_buff + len, MAX_LOG_SIZE - len, "id:%d,sec:%d,tar_ZONE:%d,hr:%d\r\n",
                                         ZH_REMIND_SPORTING_REMIND_HEART_STRING_ID,
                                         get_sr_heart_suggest_remind(),
                                         sport_setting_target_data[Get_current_sporting_type()].sport_heart_rate_zones,
                                         sport_save_data.sport_heart_rate);
                len += lens;
            }
            sport_event_ongo = 1 << HR_ZONES_EVT;
            Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_HEART_STRING_ID,NULL); */
        }
        else if(sport_event_req & 1 << AUTO_PACE_EVT)
        {
/*            if (tmp_buff)
            {
                uint16_t lens = snprintf(tmp_buff + len, MAX_LOG_SIZE - len, "id:%d,tar_autop:%d,pace:%d\r\n",
                                         ZH_REMIND_SPORTING_REMIND_INTELLIGENT_RUN_STRING_ID,
                                         sport_setting_target_data[Get_current_sporting_type()].sport_accompanying_running_pace,
                                         sport_save_data.sport_Speed_distribution);
                len += lens;
            }
            sport_event_ongo = 1 << AUTO_PACE_EVT;
            Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_INTELLIGENT_RUN_STRING_ID,NULL);*/           
        }
		#ifndef BSP_USING_PC_SIMULATOR
        if(get_vibration_adjustment_status())
        {
            Set_Moto_Times_Frequence(moto_intensity, moto_count);
        }
		#endif
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
        if (strlen(tmp_buff) != 0)
            Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "%s", tmp_buff);
#endif
        //sport_state_log(5);
        sport_event_req = sport_event_req ^ sport_event_ongo;
       // if (sport_event_req == 0) sport_event_wait = SPORT_EVENT_TIMEOUT;
        //else
            sport_event_wait = 0;
        sport_disp_timeout = 0;
    }
#endif
    if (tmp_buff)
    {
        free(tmp_buff);
    }
}

void sport_event_timing_proc(void)
{
  //  zh_log_printk("sport_event_timing_proc %04x %d %d %d\n", sport_event_req, sport_event_wait, sport_disp_timeout, sport_event_holding);
//
    if (sport_event_ongo)
    {
        sport_disp_timeout++;

        if (sport_disp_timeout > 3)
        {
            sport_event_ongo = 0;
            sport_disp_timeout = 0;
        }

    }
    else
    {
        sport_event_holding = 0;

    }

   // if (sport_event_wait < SPORT_EVENT_TIMEOUT)
    {
       // zh_log_printk("sport_event_timing_proc %04x %d %d\n", sport_event_req, sport_event_wait, sport_disp_timeout);
        /* sport_event_wait++;
       if (sport_event_wait == SPORT_EVENT_TIMEOUT && Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF)
        {
            sport_event_req = 0;

        }
        else*/ if (misc_sport_data.sport_Function_state == Sport_state_start/*&& (Get_Sys_Back_Light_Status() == BACK_LIGHT_ON && Middle_Get_Oled_On_off() == ENUM_OLED_ON)*/)
        {

            pop_sport_event();
            clear_sport_remind_state();
        }
        /*else{
                    sport_event_req = 0;
                    sport_event_wait=SPORT_EVENT_TIMEOUT;
            }*/
    }

}


void push_sport_event(uint16_t evt)
{
    if (sport_event_req == 0 && sport_event_ongo == 0)
    {
        /*if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
        {

            //push_sport_event(KM_EVT);
            // sport_event_holding = 1;
           // Lcd_Pwm_Light_On_Notify_thread(0);
            ///Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_DISTANCE_WHOLE_KILOMTER, SECONDARY__1);
        }
        else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
        {
            //push_sport_event(KM_EVT);
            //sport_event_holding = 1;
          //  thread_gui_blacklight_on_thread();
            //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_DISTANCE_WHOLE_KILOMTER, SECONDARY__1);
        }
        else*/
        sport_event_holding = 1;
    }
    /*  else if((sport_event_req & (1 << evt))&& sport_event_holding ){
           sport_event_holding += 3;
      }*/
    sport_event_req |= 1 << evt;
    sport_event_wait = 0;

    pop_sport_event();
    printf("push_sport_event %04x\n", evt);
}
void module_ms_app_sport_open_heart(bool open, uint8_t heart_style) // style:0->开始运动的心率,1->app课程的运动
{
    printf("%s:%d,%d\n",__func__,open,heart_style);
#if defined(SENSOR_USING_HR) && !defined(BSP_USING_PC_SIMULATOR)
    if (open)
    {
        if(Get_current_sporting_type() == SPORTING_swim_indoor_TYPE||    // 泳池游泳
        Get_current_sporting_type() == SPORTING_swim_outdoor_TYPE)  // 开放水域游泳)//游泳类不开心率
        {
            return;
        }
        /* 设置心率运动模式 */
        if (Get_current_sporting_type() == SPORTING_Outdoor_cycling_TYPE || Get_current_sporting_type() == SPORTING_Indoor_cycling_TYPE) // || Get_current_sporting_type() == SPORTING_Mountain_cycling_TYPE || Get_current_sporting_type() == SPORTING_BMX_TYPE)
        {
            Heart_Set_Sport_Mode(HR_SPORT_MODE_CYCLE);
        }
        else if (Get_current_sporting_type() == SPORTING_Outdoor_walking_TYPE)
        {
            Heart_Set_Sport_Mode(HR_SPORT_MODE_WALKING);
        }
        else if (Get_current_sporting_type() == SPORTING_Skipping_rope_H_TYPE)
        {
            Heart_Set_Sport_Mode(HR_SPORT_MODE_ROPE_SKIPPING);
        }
        else if (Get_current_sporting_type() == SPORTING_High_intensity_interval_training_TYPE
                 || Get_current_sporting_type() == SPORTING_Strength_Training_TYPE)
        {
            Heart_Set_Sport_Mode(HR_SPORT_MODE_HIGH_POWER);
        }
        else
        {
            Heart_Set_Sport_Mode(HR_SPORT_MODE_NORMAL);
        }

        if (module_ms_app_get_upload_flag())
        {
            if (heart_style == 1)
            {
                app_open_sensors(SENSOR_HR_APP_SPORT);
            }
            else
            {
                app_open_sensors(SENSOR_HR_LOCAL_SPORT);
            }
        }
        else
            app_open_sensors(SENSOR_HR_LOCAL_SPORT);
    }
    else
    {
        if (get_heard_power_state() == true)
        {

            if (module_ms_app_get_upload_flag())
            {

                if (Get_Heart_Messure_State_Style() == ENUM_HEART_MESSUREING_APP_SPORT)
                    app_close_sensors(SENSOR_HR_APP_SPORT);
            }
            else
            {

                if (Get_Heart_Messure_State_Style() == ENUM_HEART_MESSUREING_LOCAL_SPORT)
                    app_close_sensors(SENSOR_HR_LOCAL_SPORT);
                else if (Get_Heart_Messure_State_Style() == ENUM_HEART_MESSUREING_APP_SPORT)
                    app_close_sensors(SENSOR_HR_APP_SPORT);
            }
        }
    }
#endif
}

//运动页面强开心率
void module_sport_app_switch_sport_heart(void)
{
#if defined(SENSOR_USING_HR) && !defined(BSP_USING_PC_SIMULATOR)
    if (Get_Heart_Messure_State_Style() != ENUM_HEART_MESSUREING_LOCAL_SPORT)
    {
        module_ms_app_sport_open_heart(true, 0);
    }
#endif
}

void mdoule_sport_app_control_heart(void)
{
    if (misc_sport_data.sport_Function_state == Sport_state_stop)
    {
        //printf("%s %s,%s\n",__func__,Get_Current_App_Id(),Get_Current_Page_Id());
#if defined(SENSOR_USING_HR) && !defined(BSP_USING_PC_SIMULATOR)
        if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
        {
            if (get_heard_power_state() == true)
            {
                if (Get_Heart_Messure_State_Style() == ENUM_HEART_MESSUREING_LOCAL_SPORT)
                {
                    app_close_sensors(SENSOR_HR_LOCAL_SPORT);
                    printf("close %s\n",__func__);
                } 
            }   
        }
       
#endif
    }
}
void sport_state_log(uint8_t act)
{
#define MAX_LOG_SEDENTARY_SIZE (300)
    char *buf;
    buf = malloc(MAX_LOG_SEDENTARY_SIZE);
    if(buf==NULL) return;
   // char buf[MAX_LOG_SEDENTARY_SIZE] = "";
    memset(buf, 0, MAX_LOG_SEDENTARY_SIZE);
    int len = 0;
  
    if (act == 0x0B){
		len = snprintf(buf, MAX_LOG_SEDENTARY_SIZE, "st:%d gps src:%s \r\n", act, misc_sport_data.gps_source?"dev":"app");
	}
   else if (act == 0x0a){
		len = snprintf(buf, MAX_LOG_SEDENTARY_SIZE, "st:%d dev gps:%d gps_level:%d \r\n", act, misc_sport_data.dev_gps_position_status,
                       misc_sport_data.gps_level);
	}
    else if (act == 7)
    {

        // extern mi_daily_base_s* p_mi_daily;
        // uint8_t st;
        // st = mi_get_daily_activity_level_for_one_minute(p_mi_daily);
        //        len=snprintf(buf,MAX_LOG_SEDENTARY_SIZE,"activity_level:%d\r\n",st);
    }
    else if (act == 8) // pace
    {
        len = snprintf(buf, MAX_LOG_SEDENTARY_SIZE, "pace:%d dur:%d k_pace:%d \r\n", sport_app_target.sport_reminder_pace, sport_app_target.sport_reminder_kilometre_duration,
                       sport_app_target.sport_reminder_kilometre_pace);
    }
    else if (act == 9) // 整公里
    {
        len = snprintf(buf, MAX_LOG_SEDENTARY_SIZE, "dur:%d k_pace:%d time:%d dis:%d\r\n", sport_app_target.sport_reminder_kilometre_duration,
                       sport_app_target.sport_reminder_kilometre_pace, sport_save_data.sport_time_count, sport_save_data.sport_distance);
    }
    else if (act == 6)
    {
        len = snprintf(buf, MAX_LOG_SEDENTARY_SIZE, "st:%d status:%x code:%x accuracy:%d \r\n", act, misc_sport_data.gps_position_status,
                       misc_sport_data.gps_pre_code,
                       misc_sport_data.gps_accuracy);
    }

    else if (act == 5)
    {
        len = snprintf(buf, MAX_LOG_SEDENTARY_SIZE, "st:%d req:%x on:%x pace:%d spd:%d hr:%d\r\n", act, sport_event_req,
                       sport_event_ongo, sport_save_data.sport_Speed_distribution,
                       sport_save_data.sport_Speed, sport_save_data.sport_heart_rate);
        // miwear_save_exception_log_data(SPORT_STATE_LOG, buf, len);

        len = snprintf(buf + len, MAX_LOG_SEDENTARY_SIZE - len, "st:%d dura:%d step:%d cal:%d dist:%d cnt:%d,max_fq:%d", misc_sport_data.sport_Function_state,
                       sport_save_data.sport_time_count, sport_save_data.sport_Step_number,
                       (int)sport_save_data.sport_consume, sport_save_data.sport_distance, sport_save_data.sport_rm_count, sport_save_data.sport_max_freq);
    }
    else
    {
        if (misc_sport_data.sport_Function_state == Sport_state_stop)
        {
            snprintf(buf, MAX_LOG_SEDENTARY_SIZE, "st:%d dura:%d step:%d cal:%d dist:%d cnt:%d,max_fq:%d,type:%d", misc_sport_data.sport_Function_state,
                     sport_save_data.sport_time_count, sport_save_data.sport_Step_number,
                     (int)sport_save_data.sport_consume, sport_save_data.sport_distance, sport_save_data.sport_rm_count, sport_save_data.sport_max_freq,Get_current_sporting_type());
        }
        else if (misc_sport_data.sport_Function_state == Sport_state_start)
        {
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
            len = snprintf(buf, MAX_LOG_SEDENTARY_SIZE, "st:%d type:%d w:%d a:%d h:%d s:%d\r\n", misc_sport_data.sport_Function_state,
                           misc_sport_data.auto_sport_obj.sport_type, get_user_profile_weight(),
                           get_user_profile_age(), get_user_profile_hight(), get_migps_gender());
#endif
            // len = strlen(buf);
            printf("\r\n## sport_state_log =%d >>%s\r\n", len, buf);
            uint16_t sport_type = Get_current_sporting_type();
            if(sport_type == SPORTING_Indoor_running_TYPE||
            sport_type == SPORTING_Outdoor_cycling_TYPE||
            sport_type == SPORTING_Outdoor_walking_TYPE||
            sport_type == SPORTING_Outdoor_running_TYPE)
            {
                uint32_t duration = Sport_Best_Data[module_mul_sport_get_best_points_index()].duration;
                uint32_t distance = Sport_Best_Data[module_mul_sport_get_best_points_index()].distance;                       
                uint16_t lens = snprintf(buf + len, MAX_LOG_SEDENTARY_SIZE - len, "type:%d dur:%d dis:%d,", sport_type,duration,distance);
                len += lens;
                printf("\r\n## sport_state_log =%d >>%s\r\n", len, buf);
            }
            if (misc_sport_data.auto_sport_obj.sport_type == SPORTING_Indoor_running_TYPE)
            {
                // miwear_save_exception_log_data(SPORT_STATE_LOG, buf, len);
                // memset(buf,0,MAX_LOG_SEDENTARY_SIZE);
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
                len = snprintf(buf + len, MAX_LOG_SEDENTARY_SIZE - len, "indoor_calibration:%d %f %f %f %f %f", indoor_calibration.data_len,
                               indoor_calibration.params[0], indoor_calibration.params[1],
                               indoor_calibration.params[2], indoor_calibration.params[3],
                               indoor_calibration.params[4]);
#endif
            }
        }
        else if (misc_sport_data.sport_Function_state == Sport_state_pause)
        {
            snprintf(buf, MAX_LOG_SEDENTARY_SIZE, "st:%d dura:%d step:%d cal:%d dist:%d cnt:%d", misc_sport_data.sport_Function_state,
                     sport_save_data.sport_time_count, sport_save_data.sport_Step_number,
                     (int)sport_save_data.sport_consume, sport_save_data.sport_distance, sport_save_data.sport_rm_count);
        }
    }
    len = strlen(buf);
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
    Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG,"sport_state:%d,%s",misc_sport_data.sport_Function_state,buf);
#endif
    printf("\r\n## sport_state_log =%d >>%s\r\n", len, buf);
    if (misc_sport_data.sport_Function_state != Sport_state_stop)
    {
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
        Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "st:%d %d,dura:%d step:%d cal:%d dist:%d cnt:%d",
                                    act,
                                    misc_sport_data.sport_Function_state,
                                    sport_save_data.sport_time_count, sport_save_data.sport_Step_number,
                                    (int)sport_save_data.sport_consume, sport_save_data.sport_distance, sport_save_data.sport_rm_count);
#endif
    }
    free(buf);
}
void miwear_save_vitaliy_log_data_direct_flash(uint8_t *data, uint16_t data_len)
{
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
   // Zh_Log_Fun_Write_Ram_Memory(VITALIY_DATA, "%s", data);
#endif
}
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
void save_sport_status_log(SportRequest *request, char *buff)
{
#define MAX_LOG_SEDENTARY_SIZE (300)
    char *buf;
    buf = malloc(MAX_LOG_SEDENTARY_SIZE);
    if(buf==NULL) return;
   // char buf[MAX_LOG_SEDENTARY_SIZE] = "";
    int len = 0;
    if (request != NULL && buff)
    {
        len = snprintf(buf, MAX_LOG_SEDENTARY_SIZE, "type:%d sport_state:%d %d,response_code:%d,mask:%s\r\n", request->sport_type,
                       request->state, misc_sport_data.sport_Function_state, request->timestamp, buff);
        len = strlen(buf);
        printf("\r\n## sport_state_log =%d >>%s\r\n", len, buf);
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
        Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "type:%d sport_state:%d %d,response_code:%d,mask:%s\r\n", request->sport_type,
                       request->state, misc_sport_data.sport_Function_state, request->timestamp, buff);
#endif
    }
    else if (buff != NULL)
    {
        len = snprintf(buf, MAX_LOG_SEDENTARY_SIZE, "mask:%s\r\n",
                       buff);
        len = strlen(buf);
        printf("\r\n## sport_state_log =%d >>%s\r\n", len, buf);
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
        Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "mask:%s\r\n",
                       buff);
#endif
    }
    free(buf);
}
#endif


void module_ms_app_time_handler()
{
    // MyContinuousHeartRateData *p_hr_obj=module_get_daily_data(CONTINUOUSHEARTRATE_PIEID);
    // bas_data.detail_steps = GsensorParameter_StepGet() - bas_data.steps;
    misc_sport_data.sport_base_data.heart_rate = 3;// get_heart_value_messure_menu();
    //  bas_data.distance =
    printf("%s hr:%d\n",__func__,misc_sport_data.sport_base_data.heart_rate);
}

void sport_handle(void)
{

    if (module_ms_app_get_upload_flag()) // APP当前处于运动前准备状态,课程状态自动上传心率选择sportdata2a
    {
#if defined(SENSOR_USING_HR) && !defined(BSP_USING_PC_SIMULATOR)

        uint8_t current_task = Get_Heart_Messure_State_Style();
        if (current_task != ENUM_HEART_MESSUREING_MENU && current_task != ENUM_HEART_MESSUREING_AUTO && current_task != ENUM_HEART_MESSUREING_SPO2 && current_task != ENUM_HEART_MESSUREING_HRV && current_task != ENUM_HEART_MESSUREING_LIGHT_LEAK && current_task != ENUM_HEART_MESSUREING_GREY_CHIP && current_task != ENUM_HEART_MESSUREING_SAR && current_task != ENUM_HEART_MESSUREING_AUTO_SPO2 && current_task != ENUM_HEART_MESSUREING_AUTO_HRV && current_task != ENUM_HEART_MESSUREING_SCIENCE_SLEEP && current_task != ENUM_HEART_MESSUREING_APP_SPORT && current_task != ENUM_HEART_MESSUREING_LOCAL_SPORT && current_task != ENUM_HEART_MESSUREING_LIVING)
        {

            Set_current_sproting_type(SPORTING_Outdoor_running_TYPE); //!
            module_ms_app_sport_open_heart(true, 1);
        }
#endif

        module_ms_app_time_handler();
#ifndef BSP_USING_PC_SIMULATOR
        zh_wear_upload_sport_base_data();
#endif
    }
    else
    {
        // 关闭
        if (!misc_sport_data.sport_is_app_sponsor)
        {
#if defined(SENSOR_USING_HR) && !defined(BSP_USING_PC_SIMULATOR)
            if (ENUM_HEART_MESSUREING_APP_SPORT == Get_Heart_Messure_State_Style())
#endif
            {
                module_ms_app_sport_open_heart(false, 0);
            }
        }
    }
#if 0
    p_ms_sport_data_t p_sport_data = module_ms_api_get_sport_data();
    /* 补丁 添加运动中蓝牙重连断开亮屏*/
    bool blue_tooth_last_link_state = bluetooth_link_status;
    module_ble_api_get_info(MODULE_BLE_API_GET_CONN_STATE, &bluetooth_link_status);
    if (Get_Ble_Disconnect_Find_Phone())
    {
        bluetooth_link_status = true;
    }
    else
    {
        bluetooth_link_status = false;
    }
    if (module_ms_app_is_gps_sport_type(menu_sport_id) && p_sport_misc->sport_state != SPORT_STATE_STOP && !p_sport_misc->sport_is_app_sponsor)
    {
        //  p_ms_sport_misc_t p_sport_misc = module_ms_app_get_sport_misc();
        if (blue_tooth_last_link_state != bluetooth_link_status)
        {
            module_system_api_send_msg_to_hub_task(HUB_MSG_MOTOR, CYCLE_1_OUT_1_IDLE_1, MSG_MOTOR_START);
            if (bluetooth_link_status)
            {
                zh_miwear_sport_request(SportState_SPORT_START, pb_sport_type_trans(menu_sport_id));
            }
            gui_new_menu_view(MENU_SPORT, SECONDARY__SPORT_BULETOOTH_RELINK);
        }
    }
    else if (p_sport_misc->sport_state != SPORT_STATE_STOP && p_sport_misc->sport_is_app_sponsor)
    {
        if (blue_tooth_last_link_state != bluetooth_link_status)
        {
            if (!bluetooth_link_status)
            {
                DBG_DIRECT("app blue_tooth disconnect!!! state %d", bluetooth_link_status);
                module_system_api_send_msg_to_hub_task(HUB_MSG_MOTOR, CYCLE_1_OUT_1_IDLE_1, MSG_MOTOR_START);
                gui_new_menu_view(MENU_SPORT, SECONDARY__SPORT_BULETOOTH_RELINK_FOR_APP);
            }
        }
    }
#endif
}

#ifndef BSP_USING_PC_SIMULATOR

const uint16_t detecting_stage[] =
{
    [MI_HAR_UNKNOWN] = 0,
    [MI_HAR_WALK] = 180,
    [MI_HAR_RUN] = 30,
    [MI_HAR_ROWING] = 30,
    [MI_HAR_ELLIPTICAL] = 30,
    [MI_HAR_BIKE] = 30,
    [MI_HAR_JUMP_ROPE] = 30,
    [MI_HAR_NUM_TYPES] = 0,

};

const uint16_t remind_stage[] =
{
    [MI_HAR_UNKNOWN] = 0,
    [MI_HAR_WALK] = 420,
    [MI_HAR_RUN] = 180,
    [MI_HAR_ROWING] = 180,
    [MI_HAR_ELLIPTICAL] = 180,
    [MI_HAR_BIKE] = 180,
    [MI_HAR_JUMP_ROPE] = 180,
    [MI_HAR_NUM_TYPES] = 0,

};

const uint16_t end_stage[] =
{
    [MI_HAR_UNKNOWN] = 0,
    [MI_HAR_WALK] = 180,
    [MI_HAR_RUN] = 30,
    [MI_HAR_ROWING] = 30,
    [MI_HAR_ELLIPTICAL] = 30,
    [MI_HAR_BIKE] = 30,
    [MI_HAR_JUMP_ROPE] = 30,
    [MI_HAR_NUM_TYPES] = 0,

};

const uint16_t auto_sport_type[] =
{
    [MI_HAR_UNKNOWN] = 0,
    [MI_HAR_WALK] = SPORTING_Outdoor_walking_TYPE,
    [MI_HAR_RUN] = SPORTING_Outdoor_running_TYPE,
    [MI_HAR_ROWING] = SPORTING_Rowing_machine_TYPE,
    [MI_HAR_ELLIPTICAL] = SPORTING_Elliptical_machine_TYPE,
    [MI_HAR_BIKE] = SPORTING_Outdoor_cycling_TYPE,
    [MI_HAR_JUMP_ROPE] = SPORTING_Skipping_rope_H_TYPE,
    [MI_HAR_NUM_TYPES] = 0,

};

#define ATUO_REMIND_TIMEOUT    20 * 60

#endif

struct app_msg
{
	uint16_t sender;
	uint8_t type;
	uint8_t cmd;
	uint8_t reserve;

};
extern uint8_t menu_sport_id;
void sport_input_event_proc(uint8_t cmd,uint32_t para)
{
#ifndef BSP_USING_PC_SIMULATOR

    printf("sport_input_event_proc:  cmd %d %u, %d\n", cmd, para, misc_sport_data.sport_Function_state);

	//if(misc_sport_data.auto_sport_ctrl.sport_state==AUTO_SPORT_REMIND) 
	//	para = 0;
    switch (cmd)
    {
    case 1:
    {
        if( misc_sport_data.auto_sport_ctrl.sport_type != para){
        //    Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "autoS 0:%d %d %d\r\n",misc_sport_data.auto_sport_ctrl.sport_state,misc_sport_data.auto_sport_ctrl.sport_type , para);
        }
        switch (misc_sport_data.auto_sport_ctrl.sport_state)
        {
        case AUTO_SPORT_IDLE:
            if ((misc_sport_data.sport_Function_state == Sport_state_stop) && para)
            {
                if (no_disturb.no_disturb_alg_status == false && get_app_sleep_mode_take_over_dnd() == false && get_sleep_dnd_mode_status() == false)
                {

                    misc_sport_data.auto_sport_ctrl.time_cnt = 0;
                    misc_sport_data.auto_sport_ctrl.sport_type = para;
                    misc_sport_data.auto_sport_ctrl.sport_state = AUTO_SPORT_DETECING;
                }
            }
            break;

        case AUTO_SPORT_DETECING:
            if (para != misc_sport_data.auto_sport_ctrl.sport_type)
            {
                misc_sport_data.auto_sport_ctrl.sport_state = AUTO_SPORT_IDLE;
                if (misc_sport_data.auto_sport_ctrl.time_cnt >= (detecting_stage[misc_sport_data.auto_sport_ctrl.sport_type] - 15))
                {

                    module_ms_app_sport_open_heart(false,0);
                }
            }

            break;

        case AUTO_SPORT_PREPOINT:
            if (para != misc_sport_data.auto_sport_ctrl.sport_type)
            {
                auto_sport_ctrl_init(0);
                sport_state_act = 63;
                sport_discard();
                // if((Zh_Data_Manager.auto_sport_ctrl.time_cnt > (detecting_stage[Zh_Data_Manager.auto_sport_ctrl.sport_type] - 15))){
                module_ms_app_sport_open_heart(false,0);
                //Zh_Data_Manager.auto_sport_ctrl.sport_state = AUTO_SPORT_END;
                //Zh_Data_Manager.auto_sport_ctrl.time_cnt = 0;
                //sport_stop(auto_sport_type[auto_sport_ctrl.sport_typ);
            }

            //if (Zh_Data_Manager.Date_Struct_System.sport_Function_state == Sport_state_stop)
            // {
            //  }
            /*             if(auto_sport_ctrl.time_cnt>=remind_stage[auto_sport_ctrl.sport_type]){
                 auto_sport_ctrl.sport_state = AUTO_SPORT_REMIND;
                 //
             }*/
            break;

        case AUTO_SPORT_REMIND:
            if (para != misc_sport_data.auto_sport_ctrl.sport_type)
            {
                //auto_sport_ctrl_init(0);
               // sport_discard();

               // module_ms_app_sport_open_heart(false,0);
                //misc_sport_data.auto_sport_ctrl.sport_state = AUTO_SPORT_END;
               // misc_sport_data.auto_sport_ctrl.endtime_cnt = 0;
                   if (misc_sport_data.auto_sport_ctrl.time_cnt + end_stage[misc_sport_data.auto_sport_ctrl.sport_type] < ATUO_REMIND_TIMEOUT){
						misc_sport_data.auto_sport_ctrl.time_cnt = ATUO_REMIND_TIMEOUT - end_stage[misc_sport_data.auto_sport_ctrl.sport_type];
				   }
				
            }

            break;


        case AUTO_SPORT_END:
            if (misc_sport_data.auto_sport_ctrl.time_cnt >= end_stage[misc_sport_data.auto_sport_ctrl.sport_type])
            {
               // misc_sport_data.auto_sport_ctrl.sport_state = AUTO_SPORT_IDLE;

                //
            }
            break;

            //   case AUTO_SPORT_NORMAL:
        }

    }
    break;

    case 2: 
    {
        if(!misc_sport_data.is_auto_sport)//不是运动识别状态
        {
    	if(para==0){
            if (misc_sport_data.sport_Function_state == Sport_state_start) // 处于开启状态，则进行暂停
            {
                sport_state_act  = 14;
            }
            module_sport_app_send_app_sport_pause();
			sport_pause();
          
			Jump_App_And_Page(APP_SPORT_MAIN_STRING_ID, PAGE_SPORT_STOP_ID);
    	}
		else{
            module_sport_app_send_app_sport_restart();
			sport_restart();
            sport_state_act  = 20;
            if(Get_current_sporting_subtype())
            {
	    	    Jump_App_And_Page(APP_RUN_CLASS_MAIN_STRING_ID, PAGE_RUN_CLASS_RUNNING_STRING_ID);
            }
            else
	    	    Jump_App_And_Page(APP_SPORT_MAIN_STRING_ID, APP_SPORT_SPORTING_STRING_ID);
		}
        }
 #if 0   
        if (ThreadGui_CurrentPrimaryIdGet() == TASK_MAIN_SPORTING_MENU)
        {
            if (msg->reserve == 0)
            {
                if ((module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_SEETING_AUTO_PAUSE))/*&&((ThreadGui_CurrentSecondaryIdGet() == SECONDARY__SPORT_MAIN_PAGE1) || (ThreadGui_CurrentSecondaryIdGet() == SECONDARY__SPORT_MAIN_PAGE2)|| (ThreadGui_CurrentSecondaryIdGet() == SECONDARY__SPORT_MAIN_PAGE4))*/)
                {

                    if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                    {


                        //Lcd_Pwm_Light_On_Notify_thread(0);
                           sys_lcd_report_status(0,LCD_LIGHT_DISPLAY_ON);
                    }
                    else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                    {
                                        //thread_gui_blacklight_on_thread();
                        sys_lcd_report_status(0,LCD_LIGHT_DISPLAY_SLEEP_OUT);
                    }
                    ThreadGui_TaskSubmit(TASK_MAIN_SPORTING_MENU, SECONDARY__SPORT_MEUN_STOP_MEUN);
                }
                Set_Moto_Times_Frequence(NOW_VIBRATION_MODE_2_1, 1);
                sport_pause();
            }
            else if (msg->reserve == 1)
            {
                Set_Moto_Times_Frequence(NOW_VIBRATION_MODE_2_1, 1);
                sport_restart();
                if ((ThreadGui_CurrentSecondaryIdGet() == SECONDARY__SPORT_MEUN_STOP_MEUN))
                {

                    if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                    {

                       // Lcd_Pwm_Light_On_Notify_thread(0);
                          sys_lcd_report_status(0,LCD_LIGHT_DISPLAY_ON);
                    }
                    else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                    {
                                        //thread_gui_blacklight_on_thread();
                        sys_lcd_report_status(0,LCD_LIGHT_DISPLAY_SLEEP_OUT);
                    }
                    module_ms_app_sport_select_class(Get_current_sporting_type());
                }
            }
        }
#endif 		
    }
    break;

    case 3:  //app 副屏运动 页面处理
    {
    
#if 1    
        if (para == SportState_SPORT_START)//开始
        {
            module_ms_app_set_upload_flag(0);

            Set_current_sproting_type(menu_sport_id);
            module_ms_app_sport_open_heart(true,0);
            // if (aoto_sport_processing())
            //     sport_discard();
            misc_sport_data.is_auto_sport = false;
            sport_state_act = 34;
            sport_start(menu_sport_id);
			if( menu_sport_id == SPORTING_motion_sensing_game_TYPE){
#ifndef BSP_USING_PC_SIMULATOR
				extern bool acc_odr_status_is_25hz;
				extern uint8_t acc_data_rate_is_8g;	
				acc_odr_status_is_25hz = 0;
				acc_data_rate_is_8g = 2;
#endif
			}
            // if (ThreadGui_CurrentTaskEventDelete() == true)
            //     Delete_Current_Task_Or_Event_Id();
            Jump_App_And_Page(APP_SPORT_MAIN_STRING_ID,APP_SPORT_SPORTING_STRING_ID);
			app_set_is_ready_go_sporting(true);
            //app_popup_exit_self(0);//退弹窗
        }
        else if (para == SportState_SPORT_PAUSE)//暂停
        {
            Jump_App_And_Page(APP_SPORT_MAIN_STRING_ID,PAGE_SPORT_STOP_ID);
        }
        else if (para == SportState_SPORT_RESUME)//继续
        {
            Jump_App_And_Page(APP_SPORT_MAIN_STRING_ID,APP_SPORT_SPORTING_STRING_ID);
        }

        else if (para == SportState_SPORT_STOP)//结束
        {
//        	printf_send("%s %d\r\n",__func__,__LINE__);
            module_ms_app_sport_open_heart(false,0);
            if(Get_sport_save_status())
            {
                Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_APP_REMIND_STRING_ID,NULL);
                //Jump_App_And_Page(APP_CLOCK_STRING_ID,NULL);
            }
            else
            {
            //     extern void app_sport_jump_to_clock(void);
            //    app_sport_jump_to_clock();
                //Jump_App_And_Page(APP_CLOCK_STRING_ID,NULL);
            }

			//jump_to_clock_page(true);
            Jump_App_And_Page_clean_up(APP_CLOCK_STRING_ID,NULL);
           // gui_app_exit(APP_SPORT_MAIN_STRING_ID);

//			printf_send("%s %d\r\n",__func__,__LINE__);
        }
#endif		
    }
    break;

    case 4:    //提醒运动页面
    {
        if (misc_sport_data.auto_sport_ctrl.sport_state == AUTO_SPORT_REMIND)
        {
/*
            if (ThreadGui_CurrentTaskEventDelete() == true)
                Delete_Current_Task_Or_Event_Id();
            GuiParameter_SecondaryIdUpdate(TASK_MAIN_SPORTING_MENU, SECONDARY__SPORT_START_REMIND);
            if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
            {
               // Lcd_Pwm_Light_On_Notify_thread(0);
                  sys_lcd_report_status(0,LCD_LIGHT_DISPLAY_ON);
                miwear_set_active_type_data(SPORT_DETECT_ACTIVE_REASON_ID);
            }
            else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
            {
                  //thread_gui_blacklight_on_thread();
                sys_lcd_report_status(0,LCD_LIGHT_DISPLAY_SLEEP_OUT);
                miwear_set_active_type_data(SPORT_DETECT_ACTIVE_REASON_ID);
            }
            Middle_Set_Task_Meun_idx(TASK_MAIN_SPORTING_MENU);
            ThreadGui_KeySubmit(KEY_NUM__EVENT, KEY__EVENT);
			*/
            //   Set_Moto_Times_Frequence(NOW_VIBRATION_MODE_2_1, 1);

        }
    }
    break;

    }
/*    void save_sport_status_log(SportRequest* request,char* buff);
                        char buff[30] = {0};
                        memset(buff,0,sizeof(buff));
                        sprintf(buff,"0x%x",mkes);
                        save_sport_status_log(NULL,buff);
*/
#endif
}



void auto_sport_ctrl_timing(void)
{
#ifndef BSP_USING_PC_SIMULATOR
    misc_sport_data.auto_sport_ctrl.time_cnt++;
    if (misc_sport_data.auto_sport_ctrl.sport_disable > 0)
        misc_sport_data.auto_sport_ctrl.sport_disable --;
   if (misc_sport_data.sport_prepare_sent > 0)
       misc_sport_data.sport_prepare_sent --;
   // printf("auto_sport_ctrl_timing:  cmd %d %d\n", misc_sport_data.auto_sport_ctrl.time_cnt, misc_sport_data.auto_sport_ctrl.sport_state);
    switch (misc_sport_data.auto_sport_ctrl.sport_state)
    {
    case AUTO_SPORT_IDLE:
        misc_sport_data.auto_sport_ctrl.time_cnt = 0;
        break;

    case AUTO_SPORT_DETECING:
        if (no_disturb.no_disturb_alg_status == false && get_app_sleep_mode_take_over_dnd() == false && get_sleep_dnd_mode_status() == false && (long_endurance_adv_deal_type == EXIT_ENDURANCE))
        {
            if (misc_sport_data.sport_Function_state == Sport_state_stop)
            {
                if (misc_sport_data.auto_sport_ctrl.time_cnt >= detecting_stage[misc_sport_data.auto_sport_ctrl.sport_type])
                {

                    misc_sport_data.is_auto_sport = true;
					if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_SWITCH)) // 间歇训练先清除
					{
						module_ms_app_sport_clear_sport_target(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_SWITCH);
						misc_sport_data.sport_interval_train_is_close = true;
					}
                    sport_state_act = 35;
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
                    zh_miwear_sport_request(SportState_SPORT_START, pb_sport_type_trans(Get_current_sporting_type()));//开始sport
#endif
                    sport_start(auto_sport_type[misc_sport_data.auto_sport_ctrl.sport_type]);
                    misc_sport_data.auto_sport_ctrl.sport_state = AUTO_SPORT_PREPOINT;
					
					 Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "autoS 1:%d %d %d\r\n",misc_sport_data.auto_sport_ctrl.sport_state,misc_sport_data.auto_sport_ctrl.sport_type,misc_sport_data.auto_sport_ctrl.time_cnt);
					// if(){
                    //       Set_current_sproting_type(auto_sport_type[auto_sport_ctrl.sport_type]);
                    //          heart_messure_style = Get_Heart_Messure_State_Style();
                    //if(heart_messure_style == ENUM_HEART_IDLE)

                    //  module_ms_app_sport_open_heart(true);
                    //    }
                    //
                }
                else if (misc_sport_data.auto_sport_ctrl.time_cnt == (detecting_stage[misc_sport_data.auto_sport_ctrl.sport_type] - 15))
                {
                    Set_current_sproting_type(auto_sport_type[misc_sport_data.auto_sport_ctrl.sport_type]);
                    module_ms_app_sport_open_heart(true,0);
					if(module_ms_app_is_gps_sport_type(Get_current_sporting_type()))
					{
						zh_miwear_sport_pre_request(pb_sport_type_trans(auto_sport_type[misc_sport_data.auto_sport_ctrl.sport_type]));
					}
#if defined(ENUM_PROJECT_NAME_N65B_GLOBAL)   
						gps_set_user_mark(GPS_USED_BY_PREPEAR_SPORT);
						app_open_sensors(GPS_COLD_START_CMD);
						 misc_sport_data.dev_gps_position_status = false;
#endif
					 Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "autoS 2:%d %d %d\r\n",misc_sport_data.auto_sport_ctrl.sport_state,misc_sport_data.auto_sport_ctrl.sport_type,misc_sport_data.auto_sport_ctrl.time_cnt);
                }
            }
            else
            {
            	Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "autoS 3:%d %d %d %d\r\n",misc_sport_data.auto_sport_ctrl.sport_state,misc_sport_data.auto_sport_ctrl.sport_type,misc_sport_data.auto_sport_ctrl.time_cnt,__LINE__);
                auto_sport_ctrl_init(0);
            }
        }
        else
        {
        	Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "autoS 4:%d %d %d %d\r\n",misc_sport_data.auto_sport_ctrl.sport_state,misc_sport_data.auto_sport_ctrl.sport_type,misc_sport_data.auto_sport_ctrl.time_cnt,__LINE__);
            auto_sport_ctrl_init(0);
            if ((misc_sport_data.auto_sport_ctrl.time_cnt > (detecting_stage[misc_sport_data.auto_sport_ctrl.sport_type] - 15)))
            {
                module_ms_app_sport_open_heart(false,0);
#if defined(ENUM_PROJECT_NAME_N65B_GLOBAL)   
					
						gps_clear_user_mark(GPS_USED_BY_PREPEAR_SPORT);
		//All_sport_Close_GPS();
#endif
            }
        }
        break;

    case AUTO_SPORT_PREPOINT:
        if (no_disturb.no_disturb_alg_status == false && get_app_sleep_mode_take_over_dnd() == false && get_sleep_dnd_mode_status() == false&&(long_endurance_adv_deal_type == EXIT_ENDURANCE))
        {
            if (misc_sport_data.auto_sport_ctrl.time_cnt == remind_stage[misc_sport_data.auto_sport_ctrl.sport_type])
            {
                misc_sport_data.auto_sport_ctrl.sport_state = AUTO_SPORT_REMIND;
                misc_sport_data.auto_sport_ctrl.time_cnt = misc_sport_data.auto_sport_ctrl.time_cnt - detecting_stage[misc_sport_data.auto_sport_ctrl.sport_type];
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU) 
                if(get_vibration_adjustment_status()) 
                {
                    Set_Moto_Times_Frequence(NOW_VIBRATION_MODE_3, 2);
                }
                if (get_vibration_silent_status() == false)//静音模式关
                {
                    Zh_Ring_Sys_Type(RING_AUTO_SPORT_REMIND_INFO, 1);
                }
#endif

                Jump_Popup_And_event(POPUPS_SPORT_IDENTIFY_ID,NULL);
				Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "autoS 5:%d %d %d %d\r\n",misc_sport_data.auto_sport_ctrl.sport_state,misc_sport_data.auto_sport_ctrl.sport_type,misc_sport_data.auto_sport_ctrl.time_cnt,__LINE__);
                //sport_detect_notify(4, misc_sport_data.auto_sport_ctrl.sport_type);
                //zh_log_printk("auto_sport_ctrl_timing:  cmd %d %d>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n", Zh_Data_Manager.auto_sport_ctrl.time_cnt, Zh_Data_Manager.auto_sport_ctrl.sport_state);
                //
            }
        }
        else
        {
        	Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "autoS 6:%d %d %d %d\r\n",misc_sport_data.auto_sport_ctrl.sport_state,misc_sport_data.auto_sport_ctrl.sport_type,misc_sport_data.auto_sport_ctrl.time_cnt,__LINE__);
            auto_sport_ctrl_init(0);
            sport_state_act = 64;
            sport_discard();
            // if((Zh_Data_Manager.auto_sport_ctrl.time_cnt > (detecting_stage[Zh_Data_Manager.auto_sport_ctrl.sport_type] - 15))){
            module_ms_app_sport_open_heart(false,0);
        }
        break;

    case AUTO_SPORT_REMIND:
        if (misc_sport_data.auto_sport_ctrl.time_cnt > ATUO_REMIND_TIMEOUT||(long_endurance_adv_deal_type == OPEN_ENDURANCE))
        {
            sport_state_act = 65;
        	 sport_discard();   //need
             auto_sport_ctrl_init(300);
			 //if(Judge_Current_Pop_Up_Is_Running(POPUPS_SPORT_IDENTIFY_ID))
			 {
				app_popup_exit(POPUPS_SPORT_IDENTIFY_STRING_ID);
			}
           // set_sport_meun_state(false);
            module_ms_app_sport_open_heart(false,0);
			 Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "autoS 7:%d %d %d %d\r\n",misc_sport_data.auto_sport_ctrl.sport_state,misc_sport_data.auto_sport_ctrl.sport_type,misc_sport_data.auto_sport_ctrl.time_cnt,__LINE__);
         //   set_page_id_to_main_page();
           // sport_discard();   //need
           // auto_sport_ctrl_init(300); // not to save
#if 0        
            if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
            {
            	// to do 页面处理
              //  set_sport_meun_state(false);
                module_ms_app_sport_open_heart(false,0);
              //  set_page_id_to_main_page();
                sport_discard();   //need
                auto_sport_ctrl_init(300);
            }
            else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
            {
               // set_sport_meun_state(false);
                module_ms_app_sport_open_heart(false,0);
            //    set_page_id_to_main_page();
                sport_discard();   //need
                auto_sport_ctrl_init(300);
                // thread_gui_blacklight_on_thread();
            }
#endif 			
        }


        break;


    case AUTO_SPORT_END:
		misc_sport_data.auto_sport_ctrl.endtime_cnt++;
        if (misc_sport_data.auto_sport_ctrl.endtime_cnt >= end_stage[misc_sport_data.auto_sport_ctrl.sport_type])
        {
        	Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "autoS 8:%d %d %d %d\r\n",misc_sport_data.auto_sport_ctrl.sport_state,misc_sport_data.auto_sport_ctrl.sport_type,misc_sport_data.auto_sport_ctrl.time_cnt,__LINE__);
			// to do 页面处理
			//if(Judge_Current_Pop_Up_Is_Running(POPUPS_SPORT_IDENTIFY_ID))
			{
				//printf("auto_sport_ctrl_timing app_popup_exit\n");
				//app_popup_exit(POPUPS_SPORT_IDENTIFY_STRING_ID);
			}
           // set_sport_meun_state(false);
            module_ms_app_sport_open_heart(false,0);
         //   set_page_id_to_main_page();
            sport_state_act = 66;
            sport_discard();   //need
            auto_sport_ctrl_init(300); // not to save
            //
        }
        break;

        //   case AUTO_SPORT_NORMAL:
    }
#endif
}


void check_sport_pause_or_stop(void){
	if(sport_detect_dst.remind_sport_end && !misc_sport_data.sport_is_app_sponsor && !misc_sport_data.is_auto_sport){
		if(misc_sport_data.sport_Function_state != Sport_state_stop){
		
				
			if (1)//(Get_current_sporting_type() != SPORTING_swim_indoor_TYPE && Get_current_sporting_type() != SPORTING_swim_outdoor_TYPE)&&get_global_state_weather_is_on_wrist() == false)
    		{ //未佩戴 超过20s 暂停
    		//	printf_send("%s %d %d\n",__func__,__LINE__,misc_sport_data.unwear_dura);
    			if(misc_sport_data.unwear_dura!=0xff){
    			misc_sport_data.unwear_dura++;
				if(misc_sport_data.unwear_dura==20){
					if(misc_sport_data.sport_Function_state != Sport_state_pause){
                        if (misc_sport_data.sport_Function_state == Sport_state_start) // 处于开启状态，则进行暂停
                        {
                            sport_state_act  = 15;
                        }
						sport_pause();
                        
					//	Jump_App_And_Page(APP_SPORT_MAIN_STRING_ID, PAGE_SPORT_STOP_ID);
						misc_sport_data.pausetostop = 0;
						misc_sport_data.low_speed_cnt = 0;
						// to pause stop display
					}
				}
				else if(misc_sport_data.unwear_dura>=20){
					misc_sport_data.unwear_dura=20;
					misc_sport_data.pausetostop = 0;
					misc_sport_data.low_speed_cnt = 0;
				}
    				}
        		//update_device_state(DEV_NO_WEAR);
    		}
    		else{
				//printf_send("%s %d %d\n",__func__,__LINE__,misc_sport_data.unwear_dura);
				if(misc_sport_data.unwear_dura==0xff||(misc_sport_data.unwear_dura>0 && misc_sport_data.unwear_dura<20)){
					misc_sport_data.unwear_dura=0;
					misc_sport_data.pausetostop = 0;
					misc_sport_data.low_speed_cnt = 0;
				}
				if(misc_sport_data.sport_Function_state == Sport_state_pause){
					
					if(misc_sport_data.unwear_dura>=20){
                        if(misc_sport_data.auto_pause_dst.user_pause==0){
                            module_sport_app_send_app_sport_restart();
						    sport_restart();
            			    sport_state_act  = 20;
                            if(Get_current_sporting_subtype())
                            {
                               // Jump_App_And_Page(APP_RUN_CLASS_MAIN_STRING_ID, PAGE_RUN_CLASS_RUNNING_STRING_ID);
                            }
                            else
                            {
                            }
	    				      //  Jump_App_And_Page(APP_SPORT_MAIN_STRING_ID, APP_SPORT_SPORTING_STRING_ID);
                        }
                    	misc_sport_data.unwear_dura=0;
						misc_sport_data.pausetostop = 0;
						misc_sport_data.low_speed_cnt = 0;
                     
					}
					else{
						misc_sport_data.pausetostop++;
					//printf_send("%s %d %d\n",__func__,__LINE__,misc_sport_data.pausetostop);
						if(misc_sport_data.pausetostop==10*60){
						//	Jump_Popup_And_event(ZH_REMIND_POPUPS_SPORT_END_ID,NULL);
#ifndef BSP_USING_PC_SIMULATOR
        if(get_vibration_adjustment_status())
        {
            Set_Moto_Times_Frequence(NOW_VIBRATION_MODE_3,2);
        }
#endif
							// to stop
						}
						else if(misc_sport_data.pausetostop>=10*60){
							misc_sport_data.pausetostop=10*60;
						}
					}
					//超过 10 分钟
				}
				else{
				//	printf("%s %d %d\n",__func__,__LINE__,misc_sport_data.low_speed_cnt);
					if (Get_current_sporting_type() == SPORTING_Outdoor_cycling_TYPE){
						if(misc_sport_data.low_speed_cnt >= 600){  //低速10分钟
						//	Jump_Popup_And_event(ZH_REMIND_POPUPS_SPORT_END_ID,NULL);
							misc_sport_data.low_speed_cnt = 0;
#ifndef BSP_USING_PC_SIMULATOR
        if(get_vibration_adjustment_status())
        {
            Set_Moto_Times_Frequence(NOW_VIBRATION_MODE_3,2);
        }
#endif						
						}
					} // - 若当前运动为 跑步（含室内跑步、户外跑步）、健走 运动模式 - 持续 3 分钟，每分钟步数小于30步，弹出结束提醒
					else if((Get_current_sporting_type() == SPORTING_Outdoor_running_TYPE)||//module_ms_app_is_gps_sport_type(Get_current_sporting_type()) || 
                    (Get_current_sporting_type() == SPORTING_Outdoor_walking_TYPE)||
                    (Get_current_sporting_type() == SPORTING_Indoor_running_TYPE)){

						if(misc_sport_data.low_speed_cnt >= 180){
						//	Jump_Popup_And_event(ZH_REMIND_POPUPS_SPORT_END_ID,NULL);
							misc_sport_data.low_speed_cnt = 0;
#ifndef BSP_USING_PC_SIMULATOR
        if(get_vibration_adjustment_status())
        {
            Set_Moto_Times_Frequence(NOW_VIBRATION_MODE_3,2);
        }
#endif						
						}
					}
				}
     		//   update_device_state(DEV_PUT_ON);
    		}
			
		}
	}
}


uint8_t get_sport_seeting_data_switch(Sport_type sprot_type,uint16_t start_index,uint16_t end_index)
{
	uint8_t ret = 0;
    if(misc_sport_data.sport_is_app_sponsor){
        sport_app_target.sport_seeting_choose_target&=~1;
	    uint32_t i = 0;
	    for(i = start_index; i < end_index+1; i++)
	    {
		    if(sport_app_target.sport_seeting_choose_target>>i&1)
		    {
					ret=i;
						break;
		    }
	
	    }
    }
    else{
	sport_setting_target_data[sprot_type].sport_seeting_choose_target&=~1;
	uint32_t i = 0;
	for(i = start_index; i < end_index+1; i++)
	{
		if(sport_setting_target_data[sprot_type].sport_seeting_choose_target>>i&1)
		{
					ret=i;
						break;
		}
	
	}
        }
   return ret;
}



void set_event_subtype(uint8_t sub_type)
{
    sport_event_subtype = sub_type;
}

uint16_t module_mul_sport_get_best_points_index()
{
    uint16_t index = 0;
    uint16_t sport_type = Get_current_sporting_type();
    if (sport_type == SPORTING_Outdoor_running_TYPE)
    {
        index = BEST_OUTDOOR_RUNNING;
    }
    else if (SPORTING_Outdoor_walking_TYPE == sport_type)
    {
        index = BEST_OUTDOOR_WALK;
    }
    else if (SPORTING_Indoor_running_TYPE == sport_type)
    {
        index = BEST_INDOOR_RUNNING;
    }
    else if (SPORTING_Outdoor_cycling_TYPE == sport_type)
    {
        index = BEST_OUTDOOR_CYCLING;
    }
    return index;
}


uint16_t check_section_for_sport_remind(uint8_t choose)
{
    uint16_t ret = 0;
    float pre  = 0;
    if (choose == 1) //kcal
    {

        if (misc_sport_data.sport_is_app_sponsor)
        {
            if (sport_app_target.sport_seeting_consume_data != 0)
                pre = (float) sport_save_data.sport_consume / (float)sport_app_target.sport_seeting_consume_data; // [Get_current_sporting_type()].sport_seeting_consume_data;
            else
                pre = 0;
            // zh_log_printk("/////pre:%f\n",pre);
        }
        else
        {
            if (sport_setting_target_data[Get_current_sporting_type()].sport_seeting_consume_data != 0)
                pre  = (float)sport_save_data.sport_consume / (float)sport_setting_target_data[Get_current_sporting_type()].sport_seeting_consume_data;
            else
                pre = 0;
        }
        uint32_t number = (uint32_t)(pre * 10);

        if (number >= 5 && number < 9)
        {
            ret = 1;
        }
        else    if (number >= 9 && number < 10)
        {
            ret = 2;
        }
        else    if (number >= 10)
        {
            uint16_t select = number / 5 + 1;
            ret = select ;
        }
        printf("set_kcal = %d,cur_kcal = %lf,pre = %f,num = %d,ret = %d,app_kcal=%d,app_set_kcal=%d\n", sport_setting_target_data[Get_current_sporting_type()].sport_seeting_consume_data,
                      sport_save_data.sport_consume, pre, number, ret, misc_sport_data.app_calories, sport_app_target.sport_seeting_consume_data);
    }
    else if (choose == 2) //distance
    {
        if (misc_sport_data.sport_is_app_sponsor)
        {
            if (sport_app_target.sport_seeting_distance_data != 0)
                pre = (float)sport_save_data.sport_distance / (float)sport_app_target.sport_seeting_distance_data; // [Get_current_sporting_type()].sport_seeting_consume_data;
            else
                pre = 0;
        }
        else
        {
            if (sport_setting_target_data[Get_current_sporting_type()].sport_seeting_distance_data != 0)
                pre  = (float)sport_save_data.sport_distance / (float)sport_setting_target_data[Get_current_sporting_type()].sport_seeting_distance_data;
            else
                pre = 0;
        }
        uint32_t number = (uint32_t)(pre * 10);

        if (number >= 5 && number < 9)
        {
            ret = 1;
        }
        else    if (number >= 9 && number < 10)
        {
            ret = 2;
        }
        else    if (number >= 10)
        {
            uint16_t select = number / 5 + 1;
            ret = select ;
        }
        printf("set_distance = %d,cur_distance = %d,pre = %f,num = %d,ret = %d\n", sport_setting_target_data[Get_current_sporting_type()].sport_seeting_distance_data,
                      sport_save_data.sport_distance, pre, number, ret);
    }
    else if (choose == 3) //time
    {

        if (misc_sport_data.sport_is_app_sponsor)
        {
            if (sport_app_target.sport_seeting_time_data != 0)
                pre = (float)sport_save_data.sport_time_count / (float)(sport_app_target.sport_seeting_time_data * 60); // [Get_current_sporting_type()].sport_seeting_consume_data;
            else
                pre = 0;
        }
        else
        {
            if (sport_setting_target_data[Get_current_sporting_type()].sport_seeting_time_data != 0)
                pre  = (float)sport_save_data.sport_time_count / (float)(sport_setting_target_data[Get_current_sporting_type()].sport_seeting_time_data * 60);
            else
                pre = 0;
        }
        uint32_t number = (uint32_t)(pre * 10);

        if (number >= 5 && number < 9)
        {
            ret = 1;
        }
        else    if (number >= 9 && number < 10)
        {
            ret = 2;
        }
        else    if (number >= 10)
        {
            uint16_t select = number / 5 + 1;
            ret = select ;
        }
        printf("set_time = %d,cur_time = %d,pre = %f,num = %d,ret = %d\n", sport_setting_target_data[Get_current_sporting_type()].sport_seeting_time_data,
                      sport_save_data.sport_time_count, pre, number, ret);
    }
    else if (choose == 4) //count
    {
        if (misc_sport_data.sport_is_app_sponsor)
        {
            if (sport_app_target.sport_seeting_count_data != 0)
                pre = (float)sport_save_data.sport_rm_count / (float)sport_app_target.sport_seeting_count_data; // [Get_current_sporting_type()].sport_seeting_consume_data;
            else
                pre = 0;
        }
        else
        {
            if(Get_current_sporting_type() == SPORTING_swim_indoor_TYPE)
            {//泳池趟数
                if (sport_setting_target_data[Get_current_sporting_type()].sport_seeting_count_data != 0)
                    pre  = (float)sport_save_data.sport_number_of_tips / (float)sport_setting_target_data[Get_current_sporting_type()].sport_seeting_count_data;
                else
                    pre = 0;
            }
            else
            {
                if (sport_setting_target_data[Get_current_sporting_type()].sport_seeting_count_data != 0)
                    pre  = (float)sport_save_data.sport_rm_count / (float)sport_setting_target_data[Get_current_sporting_type()].sport_seeting_count_data;
                else
                    pre = 0;
            }
        }

        uint32_t number = (uint32_t)(pre * 10);

        if (number >= 5 && number < 9)
        {
            ret = 1;
        }
        else    if (number >= 9 && number < 10)
        {
            ret = 2;
        }
        else    if (number >= 10)
        {
            uint16_t select = number / 5 + 1;
            ret = select ;
        }
        printf("set_count = %d,cur_count = %d,pre = %f,num = %d,ret = %d\n", sport_setting_target_data[Get_current_sporting_type()].sport_seeting_count_data,
                      sport_save_data.sport_rm_count, pre, number, ret);
    }

	if(ret>3) ret = 3;

    return ret;
}
uint16_t check_remind_status(uint16_t sport_type, uint8_t current_remind_type)
{
    uint8_t choose = 0;
    uint16_t select = 0;
    choose = get_sport_seeting_data_switch(Get_current_sporting_type(), 1, 4);
    if (choose == 1 && current_remind_type == REMIND_KCAL) //kcal
    {
        select = check_section_for_sport_remind(choose);

    }
    else if (choose == 2 && REMIND_DISTANCE == current_remind_type) //distance
    {
        select = check_section_for_sport_remind(choose);
    }
    else if (choose == 3 && REMIND_TIME == current_remind_type) //time
    {
        select = check_section_for_sport_remind(choose);

    }
    else if (choose == 4 && REMIND_COUNT == current_remind_type) //count
    {
        select = check_section_for_sport_remind(choose);
    }
    return select;
}


/*******************************************************
* Description:                 运动过程中：距离达标
********************************************************/
#if 0
void Check_Alg_Sport_Distance_up_to_standard(UTCTimeStruct *tmp_time_p)
{
    uint16_t select = check_remind_status(Get_current_sporting_type(),REMIND_DISTANCE);
    bool status = get_remind_status(select);
    printf("select = %d,cur = %d,\n", select, status);
    if (select != 0 && module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_SEETING_DISTANCE))
    {

        if (get_remind_status(select))
        {
            setting_remind_status(select);
        //    Set_Moto_Times_Frequence(VIBRATE_MODE_1, 1);
            //息屏状态下
           /* if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
            {

                Lcd_Pwm_Light_On_Notify_thread(0);
                //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_DISTANCE_STANDARD, SECONDARY__1);
            }
            else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
            {
                //push_sport_event(DIST_TARGRT_EVT);
                thread_gui_blacklight_on_thread();
                //  Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_DISTANCE_STANDARD, SECONDARY__1);
            }*/
          //  else
            {
                 push_sport_event(DIST_TARGRT_EVT);
              //  Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_DISTANCE_STANDARD, SECONDARY__1);
            }
            printf("[distance_up_stand]select = %d,status = %d\n", select, get_remind_status(select));

            // sport_event_id = EVENT__SPORT_CALORIE_STANDARD;
        }

    }
    else
    {
        //clear_all_status();
    }
}

/*******************************************************
* Description:                 运动过程中：卡路里达标
********************************************************/
void Check_Alg_Sport_Consume_up_to_standard(UTCTimeStruct *tmp_time_p)
{
    uint16_t select = check_remind_status(Get_current_sporting_type(),REMIND_KCAL);
    bool status = get_remind_status(select);
    printf("select = %d,cur = %d,%d\n", select, status,module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_SEETING_CONSUME));
    if (select != 0 && module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_SEETING_CONSUME))
    {

        if (get_remind_status(select))
        {
            setting_remind_status(select);
            //息屏状态下
          //  Set_Moto_Times_Frequence(VIBRATE_MODE_1, 1);
          /*  if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
            {

                //push_sport_event(CAL_TARGRT_EVT);
                Lcd_Pwm_Light_On_Notify_thread(0);
                //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_CALORIE_STANDARD, SECONDARY__1);
            }
            else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
            {
               // push_sport_event(CAL_TARGRT_EVT);
                thread_gui_blacklight_on_thread();
                //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_CALORIE_STANDARD, SECONDARY__1);
            }*/
            //else
            {
                push_sport_event(CAL_TARGRT_EVT);
              //  Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_CALORIE_STANDARD, SECONDARY__1);
            }
            printf("[consume_up_stand]select = %d,status = %d\n", select, get_remind_status(select));

            // sport_event_id = EVENT__SPORT_CALORIE_STANDARD;
        }

    }
    else
    {
        //clear_all_status();
    }
}

/*******************************************************
* Description:                 运动过程中：时间达标
********************************************************/
void Check_Alg_Sport_Time_up_to_standard(UTCTimeStruct *tmp_time_p)
{
    uint16_t select = check_remind_status(Get_current_sporting_type(),REMIND_TIME);
    bool status = get_remind_status(select);
    printf("[time_up_stand]select = %d,cur = %d,\n", select, status);
    if (select != 0 && module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_SEETING_TIME))
    {

        if (get_remind_status(select))
        {
            setting_remind_status(select);
            //Set_Moto_Times_Frequence(VIBRATE_MODE_1, 1);
            //息屏状态下
          /*  if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
            {

               // push_sport_event(DURA_TARGRT_EVT);
              //  push_sport_event(MAX_HR_EVT);
                Lcd_Pwm_Light_On_Notify_thread(0);
                //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_TIME_STANDARD, SECONDARY__1);
            }
            else  if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
            {
               // push_sport_event(DURA_TARGRT_EVT);
             //   push_sport_event(MAX_HR_EVT);
                thread_gui_blacklight_on_thread();
                //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_TIME_STANDARD, SECONDARY__1);
            }*/
            //else
            {
                push_sport_event(DURA_TARGRT_EVT);
               // Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_TIME_STANDARD, SECONDARY__1);
            }
            printf("[time_up_stand]select = %d,status = %d\n", select, get_remind_status(select));

            // sport_event_id = EVENT__SPORT_CALORIE_STANDARD;
        }

    }
    else
    {
        //clear_all_status();
    }
}
/*******************************************************
* Description:                 运动过程中：个数达标
********************************************************/
void Check_Alg_Sport_Count_up_to_standard(UTCTimeStruct *tmp_time_p)
{
    uint16_t select = check_remind_status(Get_current_sporting_type(),REMIND_COUNT);
    bool status = get_remind_status(select);
    printf("select = %d,cur = %d,\n", select, status);
    if (select != 0 && module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_SEETING_COUNT))
    {
        if (get_remind_status(select))
        {
            setting_remind_status(select);
            //Set_Moto_Times_Frequence(VIBRATE_MODE_1, 2);
            //息屏状态下
           /* if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
            {

                //push_sport_event(COUNT_TARGRT_EVT);
                Lcd_Pwm_Light_On_Notify_thread(0);
                //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_COUNT_STANDARD, SECONDARY__1);
            }
            else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
            {
                //push_sport_event(COUNT_TARGRT_EVT);
                thread_gui_blacklight_on_thread();
                //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_COUNT_STANDARD, SECONDARY__1);
            }*/
            push_sport_event(COUNT_TARGRT_EVT);
            //else
            //{
             //   Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_COUNT_STANDARD, SECONDARY__1);
           // }
            printf("[time_up_stand]select = %d,status = %d\n", select, get_remind_status(select));
            // sport_event_id = EVENT__SPORT_CALORIE_STANDARD;
        }

    }
    else
    {
        //clear_all_status();
    }
}
/*******************************************************
* Description:                 运动过程中：整公里达标
********************************************************/
void Check_Alg_Sport_Distance_up_to_whole_kilomoter(UTCTimeStruct *tmp_time_p)
{
    static uint32_t distance_index[5] = {0};
    if (sport_save_data.sport_time_count == 0)
    {
        memset(distance_index, 0, sizeof(distance_index));
    }
    int16_t current_sport_type = Get_current_sporting_type();
    uint16_t idnex = sport_save_data.sport_distance / sport_setting_target_data[current_sport_type].sport_distance_remind;

    printf("sport_type:%d,%d\n",current_sport_type,module_ms_app_get__data_target_is_switch(current_sport_type, SPORT_SEETING_DISTANCE_REMIND));
    if (sport_save_data.sport_distance / sport_setting_target_data[current_sport_type].sport_distance_remind != 0 &&
            module_ms_app_get__data_target_is_switch(current_sport_type, SPORT_SEETING_DISTANCE_REMIND))
    {
        idnex -= 1;
        uint16_t index1 = idnex / 32;
        uint16_t left = idnex % 32;
//                          zh_log_printk("cur_distance 0x%x,index =%d,index1 =%d,dis =%d,remind_dis =%d,left =%d,%d\n",distance_index[index1],idnex,index1,Zh_Data_Manager.sport_save_data.sport_distance,
//      Zh_Data_Manager.sport_setting_target_data[current_sport_type].sport_distance_remind,left,!(distance_index[index1]>>left&1));
        if (!(distance_index[index1] >> left & 1))
        {
            distance_index[index1] |= 1 << left;
          //  Set_Moto_Times_Frequence(VIBRATE_MODE_1, 1);                                                                                        //息屏状态下
          /*  if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
            {

                //push_sport_event(KM_EVT);
                Lcd_Pwm_Light_On_Notify_thread(0);
                ///Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_DISTANCE_WHOLE_KILOMTER, SECONDARY__1);
            }
            else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
            {
                //push_sport_event(KM_EVT);
                thread_gui_blacklight_on_thread();
                //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_DISTANCE_WHOLE_KILOMTER, SECONDARY__1);
            }*/
            push_sport_event(KM_EVT);
            //else
            //{
           //     Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_DISTANCE_WHOLE_KILOMTER, SECONDARY__1);
           // }
            //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_DISTANCE_WHOLE_KILOMTER, SECONDARY__1);
        }

    }
}
/*******************************************************
* Description:                 运动过程中：高心率提醒
********************************************************/
void Check_Alg_Sport_High_Hr_Remind(UTCTimeStruct *tmp_time_p)
{
    //此后，若用户持续心率过高，则每隔60、180、300、600秒（最大为600秒，此后以此类推）发出一次，若中途进入预设区间，则时间重新累计（30秒） 
    printf("hr_switch:%d,hr_vaule = %d,set_hr_vaule =%d,sw:%d,to:%d,td:%d,rk:%d\n", module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_SEETING_HR),\
                  sport_save_data.sport_heart_rate, sport_setting_target_data[Get_current_sporting_type()].sport_heart_rate_warn_value,\
                  sport_remind_struct.sport_hr_remind_switch,\
                  sport_remind_struct.sport_hr_timeout,\
                  sport_remind_struct.sport_hr_timedelay,\
                  sport_remind_struct.hr_remind_keep);
    if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_SEETING_HR) &&
            (((sport_setting_target_data[Get_current_sporting_type()].sport_heart_rate_warn_value < sport_save_data.sport_heart_rate)&&!misc_sport_data.sport_is_app_sponsor
    ))&& !sport_remind_struct.sport_hr_remind_switch)
    {
        sport_remind_struct.sport_hr_timeout++;
        if (sport_remind_struct.sport_hr_timeout == 5)  
        {
            sport_remind_struct.sport_hr_remind_switch = true;
            sport_remind_struct.sport_hr_timedelay = 0;
            sport_app_target.sport_heart_rate_warn_value = sport_save_data.sport_heart_rate;
            if (sport_remind_struct.hr_remind_keep == 0)
            {
                sport_remind_struct.hr_remind_keep = 1;
            }
            else if (sport_remind_struct.hr_remind_keep < 8)
            {
                sport_remind_struct.hr_remind_keep = sport_remind_struct.hr_remind_keep << 1;
            }
            else
            {
                sport_remind_struct.hr_remind_keep = 8;
            }
            //Set_Moto_Times_Frequence(VIBRATE_MODE_1, 1);                                                                                                   //息屏状态下
           /* if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
            {

                //push_sport_event(MAX_HR_EVT);
                Lcd_Pwm_Light_On_Notify_thread(0);
                //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_HIGH_HR, SECONDARY__1);
            }
            else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
            {
                //push_sport_event(MAX_HR_EVT);
                thread_gui_blacklight_on_thread();
                //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_HIGH_HR, SECONDARY__1);
            }*/
            push_sport_event(MAX_HR_EVT);
            //else
            //{
             //   Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_HIGH_HR, SECONDARY__1);
            //}
            //  Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_HIGH_HR, SECONDARY__1);
        }
    }
    else
    {
        if (!sport_remind_struct.sport_hr_remind_switch)
        {
            sport_remind_struct.hr_remind_keep = 0;
        }
        //sport_remind_struct.hr_remind_keep = 0;
        sport_remind_struct.sport_hr_timeout = 0;
    }
}
/*******************************************************
* Description:                 运动过程中：心率区间提醒
********************************************************/
extern void set_sr_heart_suggest_remind(uint8_t data);
void Check_Alg_Sport_Heart_Rate_Interval_Remind(UTCTimeStruct *tmp_time_p)
{
    //- 开始运动前 1 分钟不判断，1 分钟后开始判断。
    printf("hr_interval:%d,hr_vaule = %d,set_hr_vaule =%d\n", sport_setting_target_data[Get_current_sporting_type()].sport_heart_rate_zones,
               sport_save_data.sport_heart_rate, sport_setting_target_data[Get_current_sporting_type()].sport_heart_rate_warn_value);
    if (sport_save_data.sport_time_count > 60)
    {
        uint32_t max_hr = get_user_profile_max_hr();
        if (sport_setting_target_data[Get_current_sporting_type()].sport_heart_rate_zones != 0) // 心率区间打开
        {
            uint16_t interval_max = max_hr * 0.6;
            uint16_t interval_min = max_hr * 0.5;
            switch (sport_setting_target_data[Get_current_sporting_type()].sport_heart_rate_zones)
            {
            case 1: // 50%-60%
            {
                interval_max = max_hr * 0.6;
                interval_min = max_hr * 0.5;
            }
            break;
            case 2:
            {
                interval_max = max_hr * 0.7;
                interval_min = max_hr * 0.6;
            }
            break;
            case 3:
            {
                interval_max = max_hr * 0.8;
                interval_min = max_hr * 0.7;
            }
            break;
            case 4:
            {
                interval_max = max_hr * 0.9;
                interval_min = max_hr * 0.8;
            }
            break;
            default:
            {
                interval_max = max_hr;
                interval_min = max_hr * 0.9;
            }
            break;
            }
    printf("\r\ninter_max:%d,inter_min:%d,count1:%d,count2:%d,count3:%d,s1:%d,s2:%d,s3:%d,d1:%d,d2:%d,d3:%d,last_switch:%d,high_keep:%d,low_keep:%d\n",
                  interval_max, interval_min, 
                  sport_remind_struct.hr_inter_timecount_high,
                  sport_remind_struct.hr_inter_timecount_keep, 
                  sport_remind_struct.hr_inter_timecount_low, 
                  sport_remind_struct.hr_inter_high_switch,
                  sport_remind_struct.hr_inter_keep_switch, 
                  sport_remind_struct.hr_inter_low_switch, 
                  sport_remind_struct.hr_inter_delay_high, 
                  sport_remind_struct.hr_inter_delay_keep,
                  sport_remind_struct.hr_inter_delay_low,
                  sport_remind_struct.hr_inter_last_switch,
                  sport_remind_struct.hr_inter_high_keep,
                   sport_remind_struct.hr_inter_low_keep
                  );
            if (interval_max < sport_save_data.sport_heart_rate) // 比此心率区间高
            {
                if (!sport_remind_struct.hr_inter_high_switch)
                {
                    sport_remind_struct.hr_inter_timecount_high++;
                    if (sport_remind_struct.hr_inter_timecount_high >= 15)
                    {
                        sport_remind_struct.hr_inter_high_switch = true;
                        sport_remind_struct.hr_inter_delay_high = 0;
                        set_sr_heart_suggest_remind(3);
                        push_sport_event(HR_ZONES_EVT);
                        if (sport_remind_struct.hr_inter_last_switch == 1)
                        {
                            if (sport_remind_struct.hr_inter_high_keep == 0)
                            {
                                sport_remind_struct.hr_inter_high_keep = 1;
                            }
                            else if (sport_remind_struct.hr_inter_high_keep < 8)
                            {
                                sport_remind_struct.hr_inter_high_keep = sport_remind_struct.hr_inter_high_keep << 1;
                            }
                            else
                            {
                                sport_remind_struct.hr_inter_high_keep = 8;
                            }
                        }
                        else
                        {
                            sport_remind_struct.hr_inter_high_keep = 0;
                            if (sport_remind_struct.hr_inter_high_keep == 0)
                            {
                                sport_remind_struct.hr_inter_high_keep = 1;
                            }
                        }
                        sport_remind_struct.hr_inter_last_switch = 1;
                    }
                }
                sport_remind_struct.hr_inter_timecount_keep = 0;
                sport_remind_struct.hr_inter_timecount_low = 0;
                sport_remind_struct.hr_inter_keep_switch = false;
            }
            else if ((interval_max >= sport_save_data.sport_heart_rate) && interval_min < sport_save_data.sport_heart_rate) // 在目标区间
            {
                if (!sport_remind_struct.hr_inter_keep_switch && sport_remind_struct.hr_inter_last_switch != 2)
                {
                    sport_remind_struct.hr_inter_timecount_keep++;
                    if (sport_remind_struct.hr_inter_timecount_keep >= 15)
                    {
                        sport_remind_struct.hr_inter_keep_switch = true;
                        sport_remind_struct.hr_inter_last_switch = 2;
                        sport_remind_struct.hr_inter_delay_keep = 0;
                        set_sr_heart_suggest_remind(2);
                        push_sport_event(HR_ZONES_EVT);
                    }
                }
                sport_remind_struct.hr_inter_timecount_high = 0;
                sport_remind_struct.hr_inter_timecount_low = 0;
            }
            else // 低于目标区间
            {
                if (!sport_remind_struct.hr_inter_low_switch)
                {
                    sport_remind_struct.hr_inter_timecount_low++;
                    if (sport_remind_struct.hr_inter_timecount_low >= 15)
                    {
                        sport_remind_struct.hr_inter_low_switch = true;
                        sport_remind_struct.hr_inter_delay_low = 0;
                        set_sr_heart_suggest_remind(1);
                        push_sport_event(HR_ZONES_EVT);
                        if (sport_remind_struct.hr_inter_last_switch == 3)
                        {
                            if (sport_remind_struct.hr_inter_low_keep == 0)
                            {
                                sport_remind_struct.hr_inter_low_keep = 1;
                            }
                            else if (sport_remind_struct.hr_inter_low_keep < 8)
                            {
                                sport_remind_struct.hr_inter_low_keep = sport_remind_struct.hr_inter_low_keep << 1;
                            }
                            else
                            {
                                sport_remind_struct.hr_inter_low_keep = 8;
                            }
                        }
                        else
                        {
                            sport_remind_struct.hr_inter_low_keep = 0;
                            if (sport_remind_struct.hr_inter_low_keep == 0)
                            {
                                sport_remind_struct.hr_inter_low_keep = 1;
                            }
                        }
                        sport_remind_struct.hr_inter_last_switch = 3;
                    }
                }
                sport_remind_struct.hr_inter_timecount_high = 0;
                sport_remind_struct.hr_inter_timecount_keep = 0;
                sport_remind_struct.hr_inter_keep_switch = false;
            }
        }
    }
}
/*******************************************************
* Description:                 运动过程中：能量补给提醒
********************************************************/
void Check_Alg_Sport_Energy_Supply_Remind(UTCTimeStruct *tmp_time_p)
{
    static uint32_t bitwise[20] = {0};
    if (sport_save_data.sport_time_count == 0)
    {
        memset(bitwise, 0, sizeof(bitwise));
    }
    if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_ENERGY_SUPPLY_DISTANCE))
    {
        uint32_t select = sport_save_data.sport_distance / sport_setting_target_data[Get_current_sporting_type()].sport_energy_supply_remind_dis;
        printf("energy_switch:%d,select = %d,cur_distance =%d,set_diatance=%d\n", module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_ENERGY_SUPPLY_DISTANCE),
                      select, sport_save_data.sport_distance, sport_setting_target_data[Get_current_sporting_type()].sport_energy_supply_remind_dis);
        if (select)
        {
            select -= 1;
            uint8_t index = select / 32;
            uint16_t left = select % 32;
            if (index > 19)
            {
                index = 19;
            }
            if (!(bitwise[index] >> left & 1))
            {
                bitwise[index] |= 1 << left;
                //Set_Moto_Times_Frequence(VIBRATE_MODE_1, 1);                                                                                                                //息屏状态下
               /* if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                {

                    //push_sport_event(ENERGY_EVT);
                    Lcd_Pwm_Light_On_Notify_thread(0);
                    //  Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_ENERGY_SUPPLY_REMIND, SECONDARY__1);
                }
                else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                {
                    //push_sport_event(ENERGY_EVT);
                    thread_gui_blacklight_on_thread();
                    //  Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_ENERGY_SUPPLY_REMIND, SECONDARY__1);
                }*/
                push_sport_event(ENERGY_EVT);
               // else
               // {
               ///     Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_ENERGY_SUPPLY_REMIND, SECONDARY__1);
               // }
                //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_ENERGY_SUPPLY_REMIND, SECONDARY__1);
            }
        }
    }
    else if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_ENERGY_SUPPLY_TIME))
    {
        uint32_t select = sport_save_data.sport_time_count / (sport_setting_target_data[Get_current_sporting_type()].sport_energy_supply_remind_time * 60);
        printf("energy_switch:%d,select = %d,cur_time =%d,set_time=%d\n", module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_ENERGY_SUPPLY_TIME),
                      select, sport_save_data.sport_time_count, sport_setting_target_data[Get_current_sporting_type()].sport_energy_supply_remind_time);
        if (select)
        {
            select -= 1;
            uint8_t index = select / 32;
            uint16_t left = select % 32;
            if (index > 19)
            {
                index = 19;
            }
            if (!(bitwise[index] >> left & 1))
            {
                bitwise[index] |= 1 << left;
               // Set_Moto_Times_Frequence(VIBRATE_MODE_1, 1);                                                                                                                                //息屏状态下
                /*if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                {
  
                    //push_sport_event(ENERGY_EVT);
                    Lcd_Pwm_Light_On_Notify_thread(0);
                    //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_ENERGY_SUPPLY_REMIND, SECONDARY__1);
                }
                else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                {
                    //push_sport_event(ENERGY_EVT);
                    thread_gui_blacklight_on_thread();
                    //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_ENERGY_SUPPLY_REMIND, SECONDARY__1);
                }*/
                 push_sport_event(ENERGY_EVT);
                //else
               // {
               //     Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_ENERGY_SUPPLY_REMIND, SECONDARY__1);
               // }
                //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_ENERGY_SUPPLY_REMIND, SECONDARY__1);
            }
        }
    }
}
/*******************************************************
* Description:                 运动过程中：最好成绩提醒
********************************************************/
void Check_Alg_Sport_Best_Points_Remind(UTCTimeStruct *tmp_time_p)
{

    static bool distance_state = 0;
    static bool time_state = 0;
    printf("best_dis:%d,cur_dis:%d,best_time:%d,cur_time:%d,index:%d\n",Sport_Best_Data[module_mul_sport_get_best_points_index()].distance,
                 sport_save_data.sport_distance, Sport_Best_Data[module_mul_sport_get_best_points_index()].duration,
                 sport_save_data.sport_time_count,module_mul_sport_get_best_points_index());
//    printf("%d,%d\n",Sport_Best_Data[1].distance,Sport_Best_Data[1].duration);
    if (sport_save_data.sport_time_count == 0)
    {
        distance_state = 0;
        time_state = 0;
    }
    uint16_t sport_type = Get_current_sporting_type();
    if (sport_type == SPORTING_Outdoor_running_TYPE ||
            SPORTING_Outdoor_walking_TYPE == sport_type ||
            SPORTING_Indoor_running_TYPE == sport_type ||
            SPORTING_Outdoor_cycling_TYPE == sport_type)
    {
        uint16_t index = module_mul_sport_get_best_points_index();

        if ((sport_save_data.sport_distance >= 100 + Sport_Best_Data[index].distance)&&Sport_Best_Data[index].distance)
        {

            if (!distance_state)
            {
                distance_state = true;
              //  Set_Moto_Times_Frequence(VIBRATE_MODE_1, 1);                                                                                                                                //息屏状态下
             /*   if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                {
    
                    //push_sport_event(DIST_BEST_EVT);
                    Lcd_Pwm_Light_On_Notify_thread(0);
                    //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_BEST_DISTANCE_POINTS, SECONDARY__1);
                }
                else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                {
                    //push_sport_event(DIST_BEST_EVT);
                    thread_gui_blacklight_on_thread();
                    //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_BEST_DISTANCE_POINTS, SECONDARY__1);
                }*/
                push_sport_event(DIST_BEST_EVT);
                //else
               // {
               //     Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_BEST_DISTANCE_POINTS, SECONDARY__1);
               // }
                //  Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_BEST_DISTANCE_POINTS, SECONDARY__1);

            }
        }
        if ((sport_save_data.sport_time_count >= 120 + Sport_Best_Data[index].duration)&&Sport_Best_Data[index].duration)
        {

            if (!time_state)
            {
                time_state = true;
               // Set_Moto_Times_Frequence(VIBRATE_MODE_1, 1);
                //息屏状态下
                /*if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                {
    
                    //push_sport_event(DURA_BEST_EVT);
                    Lcd_Pwm_Light_On_Notify_thread(0);
                    //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_BEST_DURATION_POINTS, SECONDARY__1);
                }
                else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                {
                   // push_sport_event(DURA_BEST_EVT);
                    thread_gui_blacklight_on_thread();
                    //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_BEST_DURATION_POINTS, SECONDARY__1);
                }*/
                push_sport_event(DURA_BEST_EVT);
                //else
               // {
               //     Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_BEST_DURATION_POINTS, SECONDARY__1);
               // }
                //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_BEST_DURATION_POINTS, SECONDARY__1);
            }
        }
    }
}
/*******************************************************
* Description:                 运动过程中：智能陪跑
********************************************************/
void Check_Alg_Sport_auto_pace_remind(UTCTimeStruct *tmp_time_p)
{
#if 0
    zh_log_printk("%s,cur_pace:%d,t_pace:%d,count1:%d,count2:%d,count3:%d,s1:%d,s2:%d,s3:%d,d1:%d,d2:%d,d3:%d\n", __func__,
                  Zh_Data_Manager.sport_save_data.sport_Speed_distribution, Zh_Data_Manager.sport_setting_target_data[Get_current_sporting_type()].sport_pace_or_speed_remind, sport_remind_struct.sport_timecount1,
                  sport_remind_struct.sport_timecount2, sport_remind_struct.sport_timecount3, sport_remind_struct.sport_time1_switch,
                  sport_remind_struct.sport_time2_switch, sport_remind_struct.sport_time3_switch, sport_remind_struct.sport_timedelay1, sport_remind_struct.sport_timedelay2,
                  sport_remind_struct.sport_timedelay3);
#else
    // printf("autopace:%d,set_pace:%d,count1:%d,count2:%d,s1:%d,s2:%d,d1:%d,d2:%d,last_remind:%d,b_kp:%d,l_kp:%d\n",
    //            sport_save_data.sport_Speed_distribution, 
    //            sport_setting_target_data[current_sport_type].sport_accompanying_running_pace,
    //             sport_remind_struct.auto_pace_timecount_backward,
    //            sport_remind_struct.auto_pace_timecount_lead, 
    //            sport_remind_struct.auto_pace_backward_switch,
    //             sport_remind_struct.auto_pace_lead_switch,
    //            sport_remind_struct.auto_pace_delay_backward, 
    //            sport_remind_struct.auto_pace_delay_lead, 
    //            sport_remind_struct.auto_pace_last_remind, 
    //            sport_remind_struct.auto_pace_backward_keep,
    //            sport_remind_struct.auto_pace_lead_keep);
#endif
    int16_t current_sport_type = Get_current_sporting_type();
    if (module_ms_app_get__data_target_is_switch(current_sport_type, SPORT_INTELLIGENT_COMPANION_RUN))
    {
        if (current_sport_type == SPORTING_Outdoor_running_TYPE)
        {
            printf("autopace:%d,set_pace:%d,count1:%d,count2:%d,s1:%d,s2:%d,d1:%d,d2:%d,last_remind:%d,b_kp:%d,l_kp:%d\n",
                       sport_save_data.sport_Speed_distribution,
                       sport_setting_target_data[current_sport_type].sport_accompanying_running_pace,
                        sport_remind_struct.auto_pace_timecount_backward,
                       sport_remind_struct.auto_pace_timecount_lead,
                       sport_remind_struct.auto_pace_backward_switch,
                        sport_remind_struct.auto_pace_lead_switch,
                       sport_remind_struct.auto_pace_delay_backward,
                       sport_remind_struct.auto_pace_delay_lead,
                       sport_remind_struct.auto_pace_last_remind,
                       sport_remind_struct.auto_pace_backward_keep,
                       sport_remind_struct.auto_pace_lead_keep);
            if ((((sport_save_data.sport_Speed_distribution > sport_setting_target_data[current_sport_type].sport_accompanying_running_pace)) ||sport_save_data.sport_Speed_distribution == 0)&&\
                !sport_remind_struct.auto_pace_backward_switch) // 陪跑配速过低
            {                                                   // 配速比当前设定的慢

                sport_remind_struct.auto_pace_timecount_backward++;
                uint16_t delay_count = 60 * 5;
                switch (sport_remind_struct.auto_pace_backward_keep)
                {
                case 4:
                {
                    delay_count = 60 * 10;
                }
                break;
                case 2:
                {
                    delay_count = 60 * 5;
                }
                break;
                default:
                {
                    delay_count = 60 * 3;
                }
                break;
                }
                if (sport_remind_struct.auto_pace_timecount_backward == delay_count)
                {
                    sport_remind_struct.auto_pace_timecount_backward = 0;
                    sport_remind_struct.auto_pace_backward_switch = true;
                    sport_remind_struct.auto_pace_delay_backward = 0;
                    if (sport_remind_struct.auto_pace_last_remind == 2)
                    {
                        if (sport_remind_struct.auto_pace_backward_keep == 0||
                        sport_remind_struct.auto_pace_backward_keep == 1)
                        {
                            sport_remind_struct.auto_pace_backward_keep = 2;
                        }
                        else
                        {
                            sport_remind_struct.auto_pace_backward_keep = 4;
                        }
                    }
                    else
                    {
                        sport_remind_struct.auto_pace_backward_keep = 0;
                        if (sport_remind_struct.auto_pace_backward_keep == 0||
                        sport_remind_struct.auto_pace_backward_keep == 1)
                        {
                            sport_remind_struct.auto_pace_backward_keep = 2;
                        }
                    }
                    sport_remind_struct.auto_pace_last_remind = 2;
                    // set_event_subtype(PACE_SPEED_LOW);
                    set_sr_Intelligent_Run_remind(1);//请加速
                    push_sport_event(AUTO_PACE_EVT);
                    sport_remind_struct.auto_pace_lead_keep = 0;
                }
                sport_remind_struct.auto_pace_timecount_lead = 0;
            }
            else if (sport_save_data.sport_Speed_distribution <= sport_setting_target_data[current_sport_type].sport_accompanying_running_pace) // 领先
            {
                if (sport_save_data.sport_Speed_distribution != 0&&!sport_remind_struct.auto_pace_lead_switch)
                {
                    sport_remind_struct.auto_pace_timecount_lead++;
                    uint16_t delay_count = 60 * 5;
                    switch (sport_remind_struct.auto_pace_lead_keep)
                    {
                    case 4:
                    {
                        delay_count = 60 * 10;
                    }
                    break;
                    case 2:
                    {
                        delay_count = 60 * 5;
                    }
                    break;
                    default:
                    {
                        delay_count = 60 * 3;
                    }
                    break;
                    }
                    if (sport_remind_struct.auto_pace_timecount_lead == delay_count)
                    {
                        sport_remind_struct.auto_pace_timecount_lead = 0;
                        sport_remind_struct.auto_pace_lead_switch = true;
                        sport_remind_struct.auto_pace_delay_lead = 0;
                        if (sport_remind_struct.auto_pace_last_remind == 1)
                        {
                            if (sport_remind_struct.auto_pace_lead_keep == 0||
                            sport_remind_struct.auto_pace_lead_keep == 1)
                            {
                                sport_remind_struct.auto_pace_lead_keep = 2;
                            }
                            else
                            {
                                sport_remind_struct.auto_pace_lead_keep = 4;
                            }
                        }
                        else
                        {
                            sport_remind_struct.auto_pace_lead_keep = 0;
                            if (sport_remind_struct.auto_pace_lead_keep == 0||
                            sport_remind_struct.auto_pace_lead_keep == 1)
                            {
                                sport_remind_struct.auto_pace_lead_keep = 2;
                            }
                        }
                        sport_remind_struct.auto_pace_last_remind = 1;
                        sport_remind_struct.auto_pace_backward_keep = 0;
                        // set_event_subtype(PACE_SPEED_LOW);
                        set_sr_Intelligent_Run_remind(1);//请减速
                        push_sport_event(AUTO_PACE_EVT);
                    }
                    sport_remind_struct.auto_pace_timecount_backward = 0;
                }
                else
                {
                    sport_remind_struct.auto_pace_timecount_lead = 0;
                    sport_remind_struct.auto_pace_timecount_backward = 0;
                }
            }
        }
    }
}
/*******************************************************
* Description:                 运动过程中：配速,速度过高过低
********************************************************/
void Check_Alg_Sport_pace_speed_remind(UTCTimeStruct *tmp_time_p)
{
#if 0
    zh_log_printk("%s,cur_pace:%d,t_pace:%d,count1:%d,count2:%d,count3:%d,s1:%d,s2:%d,s3:%d,d1:%d,d2:%d,d3:%d\n", __func__,
                  Zh_Data_Manager.sport_save_data.sport_Speed_distribution, Zh_Data_Manager.sport_setting_target_data[Get_current_sporting_type()].sport_pace_or_speed_remind, sport_remind_struct.sport_timecount1,
                  sport_remind_struct.sport_timecount2, sport_remind_struct.sport_timecount3, sport_remind_struct.sport_time1_switch,
                  sport_remind_struct.sport_time2_switch, sport_remind_struct.sport_time3_switch, sport_remind_struct.sport_timedelay1, sport_remind_struct.sport_timedelay2,
                  sport_remind_struct.sport_timedelay3);
#else
    if (module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_SEETING_PACE_REMIND))
        printf("%s,cur_spd:%d,t_ce:%d,co1:%d,co2:%d,co3:%d,s1:%d,s2:%d,s3:%d,d1:%d,d2:%d,d3:%d,ls:%d,t1_k:%d,t2_k:%d,t3_k:%d\n", __func__,
                   sport_save_data.sport_Speed, sport_setting_target_data[Get_current_sporting_type()].sport_pace_or_speed_remind, sport_remind_struct.sport_timecount1,
                   sport_remind_struct.sport_timecount2, sport_remind_struct.sport_timecount3, sport_remind_struct.sport_time1_switch,
                   sport_remind_struct.sport_time2_switch, sport_remind_struct.sport_time3_switch, sport_remind_struct.sport_timedelay1, sport_remind_struct.sport_timedelay2,
                   sport_remind_struct.sport_timedelay3,
                   sport_remind_struct.sport_pace_speed_last_remind,
                   sport_remind_struct.sport_timecount1_keep,
                   sport_remind_struct.sport_timecount2_keep,
                   sport_remind_struct.sport_timecount3_keep);
#endif
    int16_t current_sport_type = Get_current_sporting_type();
    if (sport_save_data.sport_time_count >= 60)
    {
        if (current_sport_type == SPORTING_Outdoor_running_TYPE || current_sport_type == SPORTING_Outdoor_walking_TYPE || current_sport_type == SPORTING_Indoor_running_TYPE)
        {
        	
            if (module_ms_app_get__data_target_is_switch(current_sport_type, SPORT_SEETING_PACE_REMIND) &&
                   sport_save_data.sport_Speed_distribution >sport_setting_target_data[current_sport_type].sport_pace_or_speed_remind
                    && !sport_remind_struct.sport_time1_switch)//配速过低
            {

                sport_remind_struct.sport_timecount1++;
                if (sport_remind_struct.sport_timecount1 == 15)
                {
                    sport_remind_struct.sport_timecount1 = 0;
                    sport_remind_struct.sport_time1_switch = true;
                    sport_remind_struct.sport_high_low_switch = true;
                    sport_remind_struct.sport_timedelay1 = 0;
                    if (sport_remind_struct.sport_pace_speed_last_remind == 1)
                    {
                        if (sport_remind_struct.sport_timecount1_keep == 0)
                        {
                            sport_remind_struct.sport_timecount1_keep = 1;
                        }
                        else if (sport_remind_struct.sport_timecount1_keep < 8)
                        {
                            sport_remind_struct.sport_timecount1_keep = sport_remind_struct.sport_timecount1_keep<<1;
                        }
                        else
                        {
                            sport_remind_struct.sport_timecount1_keep = 8;
                        }
                    }
                    else
                    {
                        sport_remind_struct.sport_timecount1_keep = 0;
                        if (sport_remind_struct.sport_timecount1_keep == 0)
                        {
                            sport_remind_struct.sport_timecount1_keep = 1;
                        }
                    }
                    sport_remind_struct.sport_pace_speed_last_remind = 1;
                   // Set_Moto_Times_Frequence(VIBRATE_MODE_1, 1);
                   /* if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                    {

                        //push_sport_event(PACE_EVT);
                        //set_event_subtype(PACE_SPEED_LOW);
                        Lcd_Pwm_Light_On_Notify_thread(0);
                        //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_BEST_DISTANCE_POINTS, SECONDARY__1);
                    }
                    else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                    {
                        //push_sport_event(PACE_EVT);
                        //set_event_subtype(PACE_SPEED_LOW);
                        thread_gui_blacklight_on_thread();
                        //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_BEST_DISTANCE_POINTS, SECONDARY__1);
                    }*/
                    printf("PACE_SPEED_LOW\n");
                    set_event_subtype(PACE_SPEED_LOW);
                    push_sport_event(PACE_EVT);
                    //else
                    //{
                    //    Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_PACE_SPEED_LOW, SECONDARY__1);
                    //}



                    //提醒
                }
                sport_remind_struct.sport_timecount2 = 0;
                sport_remind_struct.sport_timecount3 = 0;
            }
            else if (module_ms_app_get__data_target_is_switch(current_sport_type, SPORT_SEETING_PACE_REMIND) &&
                    sport_save_data.sport_Speed_distribution <= sport_setting_target_data[current_sport_type].sport_pace_or_speed_remind
                    )
            {
                if (sport_save_data.sport_Speed_distribution >= (sport_setting_target_data[current_sport_type].sport_pace_or_speed_remind - 30) &&
                    !sport_remind_struct.sport_time2_switch) //配速,速度保持
                {
                    //- 配速过高或过低提醒后，配速进入 [预设配速 - 30", 预设配速] 区间段，持续 15s 后播报。（持续处于该区间段，则播报间隔3分钟循环）
                    if (sport_remind_struct.sport_high_low_switch&&sport_remind_struct.sport_pace_speed_last_remind != 2)
                    {
                        sport_remind_struct.sport_timecount2++;
                        if (sport_remind_struct.sport_timecount2 == 15)
                        {
                            sport_remind_struct.sport_timecount2 = 0;
                            sport_remind_struct.sport_time2_switch = true;
                            sport_remind_struct.sport_timedelay2 = 0;
                            if (sport_remind_struct.sport_pace_speed_last_remind == 2)
                            {
                                if (sport_remind_struct.sport_timecount2_keep == 0)
                                {
                                    sport_remind_struct.sport_timecount2_keep = 1;
                                }
                                else if (sport_remind_struct.sport_timecount2_keep < 8)
                                {
                                    sport_remind_struct.sport_timecount2_keep = sport_remind_struct.sport_timecount2_keep << 1;
                                }
                                else
                                {
                                    sport_remind_struct.sport_timecount2_keep = 8;
                                }
                            }
                            else
                            {
                                sport_remind_struct.sport_timecount2_keep = 0;
                                if (sport_remind_struct.sport_timecount2_keep == 0)
                                {
                                    sport_remind_struct.sport_timecount2_keep = 1;
                                }
                            }
                            sport_remind_struct.sport_pace_speed_last_remind = 2;
                            printf("pace_hold\n");
                            set_event_subtype(PACE_SPEED_HOLD);
                            push_sport_event(PACE_EVT);
                        }
                    }
                    else
                    {
// - 开始运动前 1 分钟不判断，1 分钟后开始判断。配速持续3分钟在 [预设配速 - 30", 预设配速] 区间段，3分钟后播报。（持续处于该区间段，则播报间隔3分钟循环）
                        sport_remind_struct.sport_timecount2++;
                        if (sport_remind_struct.sport_timecount2 == 3*60)
                        {
                            sport_remind_struct.sport_timecount2 = 0;
                            sport_remind_struct.sport_time2_switch = true;
                            sport_remind_struct.sport_timedelay2 = 0;
                            if (sport_remind_struct.sport_pace_speed_last_remind == 2)
                            {
                                if (sport_remind_struct.sport_timecount2_keep == 0)
                                {
                                    sport_remind_struct.sport_timecount2_keep = 1;
                                }
                                else if (sport_remind_struct.sport_timecount2_keep < 8)
                                {
                                    sport_remind_struct.sport_timecount2_keep = sport_remind_struct.sport_timecount2_keep << 1;
                                }
                                else
                                {
                                    sport_remind_struct.sport_timecount2_keep = 8;
                                }
                            }
                            else
                            {
                                sport_remind_struct.sport_timecount2_keep = 0;
                                if (sport_remind_struct.sport_timecount2_keep == 0)
                                {
                                    sport_remind_struct.sport_timecount2_keep = 1;
                                }
                            }
                            sport_remind_struct.sport_pace_speed_last_remind = 2;
                            printf("pace_hold\n");
                            set_event_subtype(PACE_SPEED_HOLD);
                            push_sport_event(PACE_EVT);
                        }                        
                    }
                    sport_remind_struct.sport_timecount1 = 0;
                    sport_remind_struct.sport_timecount3 = 0;
                }
                else
                    //配速,速度过高
                {
                    if(sport_save_data.sport_Speed_distribution == 0)
                    {
                        goto tis;//配速等于0时跳过
                    }
                    if (!sport_remind_struct.sport_time3_switch)
                    {
                        sport_remind_struct.sport_timecount3++;
                        if (sport_remind_struct.sport_timecount3 == 15)
                        {
                            sport_remind_struct.sport_timecount3 = 0;
                            sport_remind_struct.sport_time3_switch = true;
                            sport_remind_struct.sport_high_low_switch = true;
                            sport_remind_struct.sport_timedelay3 = 0;
                            if (sport_remind_struct.sport_pace_speed_last_remind == 3)
                            {
                                if (sport_remind_struct.sport_timecount3_keep == 0)
                                {
                                    sport_remind_struct.sport_timecount3_keep = 1;
                                }
                                else if (sport_remind_struct.sport_timecount3_keep < 8)
                                {
                                    sport_remind_struct.sport_timecount3_keep = sport_remind_struct.sport_timecount3_keep << 1;
                                }
                                else
                                {
                                    sport_remind_struct.sport_timecount3_keep = 8;
                                }
                            }
                            else
                            {
                                sport_remind_struct.sport_timecount3_keep = 0;
                                if (sport_remind_struct.sport_timecount3_keep == 0)
                                {
                                    sport_remind_struct.sport_timecount3_keep = 1;
                                }
                            }
                            sport_remind_struct.sport_pace_speed_last_remind = 3;
                            // Set_Moto_Times_Frequence(VIBRATE_MODE_1, 1);
                            /*  if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                              {

                                  //push_sport_event(PACE_EVT);
                                  //set_event_subtype(PACE_SPEED_HIGH);
                                  Lcd_Pwm_Light_On_Notify_thread(0);
                                  //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_BEST_DISTANCE_POINTS, SECONDARY__1);
                              }
                              else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                              {
                                  //push_sport_event(PACE_EVT);
                                  //set_event_subtype(PACE_SPEED_HIGH);
                                  thread_gui_blacklight_on_thread();
                                  //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_BEST_DISTANCE_POINTS, SECONDARY__1);
                              }*/
                               printf("PACE_SPEED_HIGH\n");
                            set_event_subtype(PACE_SPEED_HIGH);
                            push_sport_event(PACE_EVT);

                            //else
                            //    Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_PACE_SPEED_HIGH, SECONDARY__1);
                            //提醒
                        }

                    }
                    tis:
                    {};
                    sport_remind_struct.sport_timecount1 = 0;
                    sport_remind_struct.sport_timecount2 = 0;
                }
            }
        }
        else if (current_sport_type == SPORTING_Outdoor_cycling_TYPE)
        {
            if (module_ms_app_get__data_target_is_switch(current_sport_type, SPORT_SEETING_PACE_REMIND) &&sport_save_data.sport_Speed&&
                    sport_save_data.sport_Speed < (sport_setting_target_data[current_sport_type].sport_pace_or_speed_remind / 10)//left放大100,right放大1000
                    && !sport_remind_struct.sport_time1_switch)//速度低
            {

                sport_remind_struct.sport_timecount1++;
                if (sport_remind_struct.sport_timecount1 == 15)
                {
                    sport_remind_struct.sport_timecount1 = 0;
                    sport_remind_struct.sport_time1_switch = true;
                    sport_remind_struct.sport_high_low_switch = true;
                    sport_remind_struct.sport_timedelay1 = 0;
                    if (sport_remind_struct.sport_pace_speed_last_remind == 1)
                    {
                        if (sport_remind_struct.sport_timecount1_keep == 0)
                        {
                            sport_remind_struct.sport_timecount1_keep = 1;
                        }
                        else if (sport_remind_struct.sport_timecount1_keep < 8)
                        {
                            sport_remind_struct.sport_timecount1_keep = sport_remind_struct.sport_timecount1_keep << 1;
                        }
                        else
                        {
                            sport_remind_struct.sport_timecount1_keep = 8;
                        }
                    }
                    else
                    {
                        sport_remind_struct.sport_timecount1_keep = 0;
                        if (sport_remind_struct.sport_timecount1_keep == 0)
                        {
                            sport_remind_struct.sport_timecount1_keep = 1;
                        }
                    }
                    sport_remind_struct.sport_pace_speed_last_remind = 1;
                    //Set_Moto_Times_Frequence(VIBRATE_MODE_1, 1);
                 /*   if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                    {
        
                        //push_sport_event(PACE_EVT);
                        //set_event_subtype(PACE_SPEED_LOW);
                        Lcd_Pwm_Light_On_Notify_thread(0);
                        //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_BEST_DISTANCE_POINTS, SECONDARY__1);
                    }
                    else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                    {
                        //push_sport_event(PACE_EVT);
                        //set_event_subtype(PACE_SPEED_LOW);
                        thread_gui_blacklight_on_thread();
                        //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_BEST_DISTANCE_POINTS, SECONDARY__1);
                    }*/
                    set_event_subtype(PACE_SPEED_LOW);
                    push_sport_event(PACE_EVT);
                    //else
                     //   Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_PACE_SPEED_LOW, SECONDARY__1);
                    //提醒
                }
                sport_remind_struct.sport_timecount2 = 0;
                sport_remind_struct.sport_timecount3 = 0;
            }
            else if (module_ms_app_get__data_target_is_switch(current_sport_type, SPORT_SEETING_PACE_REMIND) &&
                    sport_save_data.sport_Speed >= sport_setting_target_data[current_sport_type].sport_pace_or_speed_remind / 10
                    )//速度高
            {
                if (sport_save_data.sport_Speed <= (sport_setting_target_data[current_sport_type].sport_pace_or_speed_remind/1000 + 5) * 100 &&
                    !sport_remind_struct.sport_time2_switch) //速度保持
                {
                    if (sport_remind_struct.sport_high_low_switch&&sport_remind_struct.sport_pace_speed_last_remind != 2)
                    {
                        sport_remind_struct.sport_timecount2++;
                        if (sport_remind_struct.sport_timecount2 == 15)
                        {
                            sport_remind_struct.sport_timecount2 = 0;
                            sport_remind_struct.sport_time2_switch = true;
                            sport_remind_struct.sport_timedelay2 = 0;
                            if (sport_remind_struct.sport_pace_speed_last_remind == 2)
                            {
                                if (sport_remind_struct.sport_timecount2_keep == 0)
                                {
                                    sport_remind_struct.sport_timecount2_keep = 1;
                                }
                                else if (sport_remind_struct.sport_timecount2_keep < 8)
                                {
                                    sport_remind_struct.sport_timecount2_keep = sport_remind_struct.sport_timecount2_keep << 1;
                                }
                                else
                                {
                                    sport_remind_struct.sport_timecount2_keep = 8;
                                }
                            }
                            else
                            {
                                sport_remind_struct.sport_timecount2_keep = 0;
                                if (sport_remind_struct.sport_timecount2_keep == 0)
                                {
                                    sport_remind_struct.sport_timecount2_keep = 1;
                                }
                            }
                            sport_remind_struct.sport_pace_speed_last_remind = 2;
                            set_event_subtype(PACE_SPEED_HOLD);
                            push_sport_event(PACE_EVT);
                        }
                    }
                    else
                    {
                        sport_remind_struct.sport_timecount2++;
                        if (sport_remind_struct.sport_timecount2 == 3 * 60)
                        {
                            sport_remind_struct.sport_timecount2 = 0;
                            sport_remind_struct.sport_time2_switch = true;
                            sport_remind_struct.sport_timedelay2 = 0;
                            if (sport_remind_struct.sport_pace_speed_last_remind == 2)
                            {
                                if (sport_remind_struct.sport_timecount2_keep == 0)
                                {
                                    sport_remind_struct.sport_timecount2_keep = 1;
                                }
                                else if (sport_remind_struct.sport_timecount2_keep < 8)
                                {
                                    sport_remind_struct.sport_timecount2_keep = sport_remind_struct.sport_timecount2_keep << 1;
                                }
                                else
                                {
                                    sport_remind_struct.sport_timecount2_keep = 8;
                                }
                            }
                            else
                            {
                                sport_remind_struct.sport_timecount2_keep = 0;
                                if (sport_remind_struct.sport_timecount2_keep == 0)
                                {
                                    sport_remind_struct.sport_timecount2_keep = 1;
                                }
                            }
                            sport_remind_struct.sport_pace_speed_last_remind = 2;
                            set_event_subtype(PACE_SPEED_HOLD);
                            push_sport_event(PACE_EVT);
                        }
                    }
                    sport_remind_struct.sport_timecount1 = 0;
                    sport_remind_struct.sport_timecount3 = 0;
                }
                else if (sport_save_data.sport_Speed > (sport_setting_target_data[current_sport_type].sport_pace_or_speed_remind/1000 + 5) * 100) //速度高
                {
                    if (!sport_remind_struct.sport_time3_switch)
                    {
                        sport_remind_struct.sport_timecount3++;
                        if (sport_remind_struct.sport_timecount3 == 15)
                        {
                            sport_remind_struct.sport_timecount3 = 0;
                            sport_remind_struct.sport_time3_switch = true;
                            sport_remind_struct.sport_high_low_switch = true;
                            sport_remind_struct.sport_timedelay3 = 0;
                        if (sport_remind_struct.sport_pace_speed_last_remind == 3)
                        {
                            if (sport_remind_struct.sport_timecount3_keep == 0)
                            {
                                sport_remind_struct.sport_timecount3_keep = 1;
                            }
                            else if (sport_remind_struct.sport_timecount3_keep < 8)
                            {
                                sport_remind_struct.sport_timecount3_keep = sport_remind_struct.sport_timecount3_keep << 1;
                            }
                            else
                            {
                                sport_remind_struct.sport_timecount3_keep = 8;
                            }
                        }
                        else
                        {
                            sport_remind_struct.sport_timecount3_keep = 0;
                            if (sport_remind_struct.sport_timecount3_keep == 0)
                            {
                                sport_remind_struct.sport_timecount3_keep = 1;
                            }
                        }
                        sport_remind_struct.sport_pace_speed_last_remind = 3;
                            //Set_Moto_Times_Frequence(VIBRATE_MODE_1, 1);
                         /*   if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
                            {
                    
                               // push_sport_event(PACE_EVT);
                                //set_event_subtype(PACE_SPEED_HIGH);
                                Lcd_Pwm_Light_On_Notify_thread(0);
                                //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_BEST_DISTANCE_POINTS, SECONDARY__1);
                            }
                            else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
                            {
                                
                                
                                thread_gui_blacklight_on_thread();
                                //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_BEST_DISTANCE_POINTS, SECONDARY__1);
                            }*/
                            set_event_subtype(PACE_SPEED_HIGH);
                            push_sport_event(PACE_EVT);
                           // else
                             //   Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_PACE_SPEED_HIGH, SECONDARY__1);
                            //提醒
                        }
                    }
                    sport_remind_struct.sport_timecount1 = 0;
                    sport_remind_struct.sport_timecount2 = 0;
                }
                else
                {
                    sport_remind_struct.sport_timecount1 = 0;
                    sport_remind_struct.sport_timecount2 = 0;
                    sport_remind_struct.sport_timecount3 = 0;
                }
            }
        }
    }
}
void Check_Alg_Sport_GPS_singnal_weak(UTCTimeStruct *tmp_time_p)
{
}

/*******************************************************
* Description:                 运动过程中：手机断开连接提醒
********************************************************/
void Check_Alg_Sport_Phone_Connect_Disconnect(UTCTimeStruct *tmp_time_p)
{
    static bool last_status = 0;
    static bool gps_position = 0;
    //bool this_status = get_system_ble_connect_state();
    bool this_status = 0;
    if (get_system_Spp_connect_state())
    {
        this_status = 1;
    }
    else
    {
        this_status = get_system_ble_connect_state();

        if(module_ms_app_get_ios_app_exit()==0){
            this_status = 0;
        }
    }
    //printf("bluethis:%d,last:%d,is_gps:%d\n", this_status, last_status, mul_sport_get_open_gps_sport_status());
    //运动采集蓝牙连接状态
    if (misc_sport_data.sport_Function_state != Sport_state_stop)
    {
        uint32_t sport_tyep = Get_current_sporting_type();
        if (mul_sport_get_open_gps_sport_status() && !misc_sport_data.sport_is_app_sponsor)
        {
            if (last_status != this_status)
            {
//                if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
//                {

//                    Lcd_Pwm_Light_On_Notify_thread(0);
//                }
//                else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
//                {
//                    thread_gui_blacklight_on_thread();
//                }
//                Set_Moto_Times_Frequence(NOW_VIBRATION_MODE_2_1, 1);
#if ENUM_PROJECT_NAME_N65B_GLOBAL//do nothing
				#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
    				Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG,"65Bconenct: %d",this_status);
				#endif
#else
                if (this_status)
                {
                    //连上
                     set_event_subtype(1);
                     push_sport_event(LOCAL_INFO_EVT);
                    //Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_PHONE_CONNECT, SECONDARY__1);
                }
                else
                {
                    //断连
                    set_event_subtype(0);
                    push_sport_event(LOCAL_INFO_EVT);
                   // Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_PHONE_CONNECT, SECONDARY__1);
                }
				#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
    				Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG,"conenct: %d",this_status);
				#endif
#endif
            }
        }
        printf("this_report:%d,%d\n",interconnection_ioctl_is_report_sport_data_projection(),this_status);
        if(interconnection_ioctl_is_report_sport_data_projection())//断开蓝牙并且连上数据投屏就需要清除结构体
        {
            if (last_status != this_status)
            {
                if (!this_status)
                    interconnection_ioctl_clear_sport_data_projection(); // memset struct
            }
        }
        if (misc_sport_data.sport_is_app_sponsor)
        {
            if (!this_status)
            {
                //set_sport_meun_state(false);
              //  Zh_Data_Manager.misc_sport_data.sport_is_app_sponsor = 0;
                sport_state_act = 52;
                module_ms_exit_app_sport();
                Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_BLE_DISCONNECT_STRING_ID,NULL);
                //去主页
                extern void popups_sporting_remind_send_jump_app(void);//发消息退出运动app
                popups_sporting_remind_send_jump_app();
                // Jump_App_And_Page(APP_CLOCK_STRING_ID,NULL);
//                Set_Moto_Times_Frequence(NOW_VIBRATION_MODE_2_1, 1);
//                if (Get_Sys_Back_Light_Status() == BACK_LIGHT_OFF && Middle_Get_Oled_On_off() == ENUM_OLED_ON)
//                {

//                    Lcd_Pwm_Light_On_Notify_thread(0);
//                }
//                else if (Middle_Get_Oled_On_off() == ENUM_OLED_OFF)
//                {
//                    thread_gui_blacklight_on_thread();
//                }
//                Middle_ThreadGui_EventSubmit(false, EVENT__SPORT_APP_DISCONNECT, SECONDARY__1);
                  //Middle_Set_Event_Pre_Meun_idx(TASK__MAIN+Get_record_main_page_sec_id() - 1);//设置id为主页
                  //Middle_Set_Task_Meun_idx_Secondary_ID(SECONDARY__1);  
                //   set_event_subtype(2);
                //   push_sport_event(LOCAL_INFO_EVT);
            }
        }
    }
    last_status = this_status;
    if (module_ms_app_is_gps_sport_type(Get_current_sporting_type()) &&
        ((strcmp(Get_Current_App_Id(), APP_SPORT_MAIN_STRING_ID) == 0 &&
        (strcmp(Get_Current_Page_Id(), PAGE_SPORT_PREPARE_STRING_ID) == 0 ||
         strcmp(Get_Current_Page_Id(), APP_SPORT_SPORTING_STRING_ID) == 0 ||
         strcmp(Get_Current_Page_Id(), PAGE_SPORT_GPS_REMIND_STRING_ID) == 0 ||
         strcmp(Get_Current_Page_Id(), PAGE_SPORT_GPS_PHONE_STRING_ID) == 0))||((strcmp(Get_Current_App_Id(), APP_RUN_CLASS_MAIN_STRING_ID) == 0)&&
         (strcmp(Get_Current_Page_Id(), PAGE_RUN_CLASS_RUNNING_STRING_ID) == 0))))
    {
        printf("last_pos:%d,this_pos:%d\n",gps_position, module_sport_get_gps_status());
        if (gps_position != module_sport_get_gps_status())
        {
            if (module_sport_get_gps_status())
            {
#ifndef BSP_USING_PC_SIMULATOR
         if(get_vibration_adjustment_status())
        {
            Set_Moto_Times_Frequence(NOW_VIBRATION_MODE_3,2);
        } // 定位成功增加震动
#endif
            }
        }
    }
    gps_position = module_sport_get_gps_status();
}


/*******************************************************
* Description:                 运动过程中：卫星信号弱
********************************************************/
extern uint8_t get_sport_gps_signal();
void Check_Alg_Sport_Phone_Gps_Weak(UTCTimeStruct *tmp_time_p)
{
    static bool last_status = 0;
    static bool gps_position = 0;
    static bool last_iphone_state = 0;
    //bool this_status = get_system_ble_connect_state();
    bool this_status = 0;
    if (module_sport_get_gps_status())
    {
        this_status = 1;
    }
    else
    {
        this_status = 0;
    }
    // printf("gps_state:%d,signal:%d,is_gps:%d,last:%d,%d,%d\n", module_sport_get_gps_status(), get_sport_gps_signal(), mul_sport_get_open_gps_sport_status(),last_status,sport_remind_struct.gps_weak_time_count,
    // sport_remind_struct.gps_weak_delay_count);
    //- 从定位成功状态变为未定位成功或卫星信号0~1格，持续20秒时发出提示
#if ENUM_PROJECT_NAME_N65B_GLOBAL
    if (misc_sport_data.sport_Function_state != Sport_state_stop)
#else
    if (misc_sport_data.sport_Function_state != Sport_state_stop && (get_system_ble_connect_state() || get_system_Spp_connect_state()))
#endif
    {
        uint32_t sport_tyep = Get_current_sporting_type();
        if (mul_sport_get_open_gps_sport_status() && !misc_sport_data.sport_is_app_sponsor&&!sport_remind_struct.gps_weak_no_remind)
        {
            if (last_status != this_status)
            {
                if (!this_status)
                {
                    if(module_sport_get_gps_status())
                    {
                        goto br_end;
                    }
                    sport_remind_struct.gps_weak_time_count = 0;
                    sport_remind_struct.gps_weak_flag = true;
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
                    Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "acc->lost!!!->%d",misc_sport_data.gps_accuracy);
#endif
                }
            }

            if (module_sport_get_gps_status())
            {
                if (sport_remind_struct.gps_weak_flag)
                {
                    sport_remind_struct.gps_weak_time_count = 0;
                }
                if (get_sport_gps_signal() >= 2)
                {
                    sport_remind_struct.gps_weak_delay_count = 20;
                }
                sport_remind_struct.gps_weak_flag = 0;
            }

            if(sport_remind_struct.gps_weak_flag)//从定位成功状态变为未定位成功持续20S
            {
                sport_remind_struct.gps_weak_time_count++;
                if(sport_remind_struct.gps_weak_time_count>=sport_remind_struct.gps_weak_delay_count)
                {
                    sport_remind_struct.gps_weak_time_count = 0;
                    sport_remind_struct.gps_weak_flag = 0;
                    if(module_sport_get_gps_status())
                    {
                        goto br_end;
                    }
                    Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_GPS_WEAK_STRING_ID,NULL);
                }
            }
            else if((get_sport_gps_signal() == 0||get_sport_gps_signal() == 1)&&module_sport_get_gps_status())//卫星信号0~1格，持续20秒时发出提示
            {
                sport_remind_struct.gps_weak_time_count++;
                if(sport_remind_struct.gps_weak_time_count>=sport_remind_struct.gps_weak_delay_count)
                {
                    sport_remind_struct.gps_weak_time_count = 0;
                    sport_remind_struct.gps_weak_flag = 0;
                    // if(module_sport_get_gps_status())
                    // {
                    //     goto br_end;
                    // }
                    Jump_Popup_And_event(ZH_REMIND_SPORTING_REMIND_GPS_WEAK_STRING_ID,NULL);
                }
            }
            else
            {
                sport_remind_struct.gps_weak_flag = 0;
                sport_remind_struct.gps_weak_time_count = 0;
            }
        }
        else
        {
            sport_remind_struct.gps_weak_flag = 0;
            sport_remind_struct.gps_weak_time_count = 0;
        }
#if ! defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)&&defined(ENUM_PROJECT_NAME_N65B_GLOBAL)
        if (module_sport_get_gps_status())
        {
            Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.duration_sec++;
        }
        if (misc_sport_data.gps_position_status)
        {
            Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.phone_signal_sec++;
        }
        else if (misc_sport_data.dev_gps_position_status)
        {
            Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.watch_signal_sec++;
        }
        else
        {
            Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.no_signal_sec++;
        }
        if (last_iphone_state != misc_sport_data.gps_position_status)
        {
            Zh_Data_Manager.Data_Struct_System.miwear_bp_gnss_signal_switch.switch_cnt++;
        }
#endif
    }
    else
    {
        sport_remind_struct.gps_weak_flag = 0;
        sport_remind_struct.gps_weak_time_count = 0;
    }
br_end:
{}
    last_status = this_status;
    last_iphone_state = misc_sport_data.gps_position_status;
}
#endif
 void _module_sport_app_update_sport_points(Sport_Points_type param)
{
    uint16_t sport_type = param.sport_type;
    SPORT_point_max_t type = param.type;
    uint32_t value = param.value;
    printf("sub_count:%d,type:%d,value:%d\n",mul_sport_get_swimming_turn_cnt(),sport_type,value);
    switch(sport_type)
    {
        case SPORTING_Outdoor_running_TYPE:
        case SPORTING_Indoor_running_TYPE:
        case SPORTING_Outdoor_walking_TYPE:
        {
            if(type == MAX_HR_POINT)
            {
                misc_sport_data.record_max.run_c.max_hr_point = sport_save_data.sport_time_count;             
            }
            else if(type == MIN_HR_POINT)
            {
                misc_sport_data.record_max.run_c.min_hr_point = sport_save_data.sport_time_count;                     
            }
            else if(type == MAX_PACE_POINT)
            {
                misc_sport_data.record_max.run_c.max_pace_point = sport_save_data.sport_time_count;
                if (value)
                {
                    misc_sport_data.record_max.run_c.max_pace_value.values.valid = 1;
                    misc_sport_data.record_max.run_c.max_pace_value.values.value = value;
                }
            }
            else if(type == MIN_PACE_POINT)
            {
                misc_sport_data.record_max.run_c.min_pace_point = sport_save_data.sport_time_count;  
                if (value)
                {
                    misc_sport_data.record_max.run_c.min_pace_value.values.valid = 1;
                    misc_sport_data.record_max.run_c.min_pace_value.values.value = value;
                }                   
            }
            else if(type == MAX_CADENCE_POINT)
            {
                misc_sport_data.record_max.run_c.max_cadence_point = sport_save_data.sport_time_count;             
            }
            else if(type == MIN_CADENCE_POINT)
            {
                misc_sport_data.record_max.run_c.min_cadence_point = sport_save_data.sport_time_count;                     
            }
        }
        break;
        case SPORTING_Mountaineering_TYPE: // 登山
        case SPORTING_Off_road_TYPE:       // 越野
        case SPORTING_Outdoor_cycling_TYPE:
        case SPORTING_Outdoor_hiking_TYPE:
        {
            if(type == MAX_HR_POINT)
            {
                misc_sport_data.record_max.out_non_run_c.max_hr_point = sport_save_data.sport_time_count;             
            }
            else if(type == MIN_HR_POINT)
            {
                misc_sport_data.record_max.out_non_run_c.min_hr_point = sport_save_data.sport_time_count;                     
            }
            else if(type == MAX_SPEED_POINT)
            {
                misc_sport_data.record_max.out_non_run_c.max_speed_point = sport_save_data.sport_time_count;   
                if (value)
                {
                    misc_sport_data.record_max.out_non_run_c.max_speed_value.values.valid = 1;
                    misc_sport_data.record_max.out_non_run_c.max_speed_value.values.value = value;
                }          
            }
            else if(type == MIN_SPEED_POINT)
            {
                misc_sport_data.record_max.out_non_run_c.min_speed_point = sport_save_data.sport_time_count;   
                if (value)
                {
                    misc_sport_data.record_max.out_non_run_c.min_speed_value.values.valid = 1;
                    misc_sport_data.record_max.out_non_run_c.min_speed_value.values.value = value;
                }                   
            }
        }
        break;
        case SPORTING_Elliptical_machine_TYPE:
        {
            if(type == MAX_HR_POINT)
            {
                misc_sport_data.record_max.elliptical_m.max_hr_point = sport_save_data.sport_time_count;             
            }
            else if(type == MIN_HR_POINT)
            {
                misc_sport_data.record_max.elliptical_m.min_hr_point = sport_save_data.sport_time_count;                     
            }
            else if(type == MAX_CADENCE_POINT)
            {
                misc_sport_data.record_max.elliptical_m.max_cadence_point = sport_save_data.sport_time_count;             
            }
            else if(type == MIN_CADENCE_POINT)
            {
                misc_sport_data.record_max.elliptical_m.min_cadence_point = sport_save_data.sport_time_count;                     
            }
        }
        break;
        case SPORTING_Rowing_machine_TYPE:
        {
            if(type == MAX_HR_POINT)
            {
                misc_sport_data.record_max.rowing_m.max_hr_point = sport_save_data.sport_time_count;             
            }
            else if(type == MIN_HR_POINT)
            {
                misc_sport_data.record_max.rowing_m.min_hr_point = sport_save_data.sport_time_count;                     
            }
            else if(type == MAX_ACTION_FREQ_POINT)
            {
                misc_sport_data.record_max.rowing_m.max_action_freq_point = sport_save_data.sport_time_count;             
            }
            else if(type == MIN_ACTION_FREQ_POINT)
            {
                misc_sport_data.record_max.rowing_m.min_action_freq_point = sport_save_data.sport_time_count;                     
            }
        }
        break;
        case SPORTING_Skipping_rope_H_TYPE:
        {
            if(type == MAX_HR_POINT)
            {
                misc_sport_data.record_max.rope_skip.max_hr_point = sport_save_data.sport_time_count;             
            }
            else if(type == MIN_HR_POINT)
            {
                misc_sport_data.record_max.rope_skip.min_hr_point = sport_save_data.sport_time_count;                     
            }
            else if(type == MAX_ACTION_FREQ_POINT)
            {
                misc_sport_data.record_max.rope_skip.max_action_freq_point = sport_save_data.sport_time_count;             
            }
            else if(type == MIN_ACTION_FREQ_POINT)
            {
                misc_sport_data.record_max.rope_skip.min_action_freq_point = sport_save_data.sport_time_count;                     
            }
        }
        break;
        case SPORTING_swim_indoor_TYPE:  // 泳池游泳
        case SPORTING_swim_outdoor_TYPE: // 开放水域游泳:
        {
            if (type == MAX_PACE_POINT)
            {
                misc_sport_data.record_max.swimming.max_pace_point = misc_sport_data.swim_data.sub_section_count;
            }
            else if (type == MIN_PACE_POINT)
            {
                misc_sport_data.record_max.swimming.min_pace_point = misc_sport_data.swim_data.sub_section_count;
            }
            else if (type == MAX_SWOLF_POINT)
            {
                misc_sport_data.record_max.swimming.max_swolf_point = misc_sport_data.swim_data.sub_section_count;
            }
            else if (type == MIN_SWOLF_POINT)
            {
                misc_sport_data.record_max.swimming.min_swolf_point = misc_sport_data.swim_data.sub_section_count;
            }
            else if (type == MAX_PULL_RATE_POINT)
            {
                misc_sport_data.record_max.swimming.max_pull_rate_point = misc_sport_data.swim_data.sub_section_count;
            }
            else if (type == MIN_PULL_RATE_POINT)
            {
                misc_sport_data.record_max.swimming.min_pull_rate_point = misc_sport_data.swim_data.sub_section_count;
            }
        }
        break;
        default:
        {
            if(type == MAX_HR_POINT)
            {
                misc_sport_data.record_max.free_sport.max_hr_point = sport_save_data.sport_time_count;             
            }
            else if(type == MIN_HR_POINT)
            {
                misc_sport_data.record_max.free_sport.min_hr_point = sport_save_data.sport_time_count;                     
            }
        }
        break;
    }
}

void zh_miwear_sport_pre_request(uint16_t sport_type)
{
#ifndef BSP_USING_PC_SIMULATOR
    uint16_t type = sport_type;
    send_msg_to_protobuf_thread(APP_BLE, ZH_APP_TO_BLE_SPORT_PREPARE_REQUEST, (uint8_t*)&type, sizeof(uint16_t));
#endif
}

int zh_miwear_sport_request(uint16_t cmd, uint16_t sport_type)
{
    uint16_t buff[3] = {0};
    buff[0] = cmd;//指令类型
    buff[1] = sport_type;//运动类型
    buff[2] = 0;//这个字段确定是不是app发起后，本地结束发送指令
   // rt_err_t err = RT_ERROR; 
#ifndef BSP_USING_PC_SIMULATOR
    if (misc_sport_data.sport_is_app_sponsor || module_ms_app_is_gps_sport_type(Get_current_sporting_type()))
    {
        if (misc_sport_data.sport_is_app_sponsor)
        {
            buff[2] = 1;
        }
        goto SEND;
        // 副屏运动必须发送
    }
    // else if (!module_ms_app_is_gps_sport_type(Get_current_sporting_type())) // 室内运动走这儿
    // {
    //     printf("this is indoor sport type:%d\n", Get_current_sporting_type());
    //     return -1; // 不上传
    // }


    SEND:
    {

    }
    err = send_msg_to_protobuf_thread(APP_BLE, ZH_APP_TO_BLE_SPORT_REQUEST, (uint8_t*)&buff[0], sizeof(buff));
#endif
    printf("%s cmd:%d,type:%d\n",__func__,cmd,sport_type);
    if(1)//err == RT_EOK)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

void zh_wear_upload_sport_v2a_data(void)
{
#ifndef BSP_USING_PC_SIMULATOR
    send_msg_to_protobuf_thread(APP_BLE, ZH_APP_TO_BLE_SPORT_V2A_DATA, RT_NULL, 0);
#endif
}

void zh_wear_upload_sport_base_data(void)
{
#ifndef BSP_USING_PC_SIMULATOR
    send_msg_to_protobuf_thread(APP_BLE, ZH_APP_TO_BLE_SPORT_BASE_DATA,  RT_NULL, 0);
#endif
}

void zh_wear_upload_sport_sensor_data(uint8_t sector)
{
#ifndef BSP_USING_PC_SIMULATOR
    uint8_t sec = sector;
    send_msg_to_protobuf_thread(APP_BLE, ZH_APP_TO_BLE_SPORT_WEAR_SENSOR_DATA, &sec, sizeof(sec));
#endif
    if(sector == 1)
    {
        printf("%s%d, cout:%d\n",__func__,sector,misc_sport_data.auto_sport_obj.data.Sensory_course.sensor_data1.accel_count);
    }
    else if(sector == 2)
    {
        printf("%s%d, cout:%d\n",__func__,sector,misc_sport_data.auto_sport_obj.data.Sensory_course.sensor_data2.accel_count);
    }
    else if(sector == 1)
    {
        printf("%s%d, cout:%d\n",__func__,sector,misc_sport_data.auto_sport_obj.data.Sensory_course.sensor_data3.accel_count);
    }
    else if(sector == 1)
    {
        printf("%s%d, cout:%d\n",__func__,sector,misc_sport_data.auto_sport_obj.data.Sensory_course.sensor_data4.accel_count);
    }
}

//连接新手机操作
void module_sport_app_new_iphone_operate(void)
{
    misc_sport_data.remind_wear_count = 0;//
    sport_stop();//连接新手机运动停止
}
void module_sport_app_new_sport_screen_state(bool flg)
{
    misc_sport_data.support_sport_screen = flg;
}


uint8_t module_sport_get_gps_status(void){
#if defined(USING_GYRO_SENSOR) && defined(ENUM_PROJECT_NAME_N65B_GLOBAL) 

	bool wireless_conn_state = false;
    if (get_phone_device_type() == Phone_Device_Type_IOS)
    {
        wireless_conn_state = get_system_ble_connect_state();
    }
    else
    {
        wireless_conn_state = get_system_ble_connect_state() | get_system_Spp_connect_state();
    }


	//printf("##[%s] used = %u %d %d %d %d\r\n",__func__,misc_sport_data.used_timestamp,misc_sport_data.have_app_gps_data,misc_sport_data.have_device_gps_data,wireless_conn_state,misc_sport_data.gps_accuracy);
    if((wireless_conn_state && misc_sport_data.gps_accuracy == GpsAccuracy_GPS_UNKNOWN) || wireless_conn_state==false||used_local_gps){
	//if((wireless_conn_state &&  (misc_sport_data.gps_pre_code||misc_sport_data.gps_accuracy == GpsAccuracy_GPS_UNKNOWN)) || wireless_conn_state==false||used_local_gps){
		//printf_send("%s dev %d\r\n",__func__,misc_sport_data.dev_gps_position_status);
		return misc_sport_data.dev_gps_position_status;
		}
	else
#endif
	{
		//printf_send("%s app %d\r\n",__func__,misc_sport_data.gps_position_status);
		return misc_sport_data.gps_position_status;

	}
}

static uint8_t sport_target = 0;
void module_sport_app_erase_target(void)
{
    if (misc_sport_data.is_auto_sport||module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_SWITCH))
    {
        printf("%s\n",__func__);
        sport_target = sport_setting_target_data[Get_current_sporting_type()].sport_seeting_choose_target & 0xff;
        module_ms_app_sport_clear_sport_target(Get_current_sporting_type(), SPORT_SEETING_COUNT);
        module_ms_app_sport_clear_sport_target(Get_current_sporting_type(), SPORT_SEETING_CONSUME);
        module_ms_app_sport_clear_sport_target(Get_current_sporting_type(), SPORT_SEETING_TIME);
        module_ms_app_sport_clear_sport_target(Get_current_sporting_type(), SPORT_SEETING_DISTANCE);
    }
}

void module_sport_app_clear_target(uint32_t flag)
{
    if (flag)
    {
        printf("%s\n", __func__);
        misc_sport_data.copy_choose_target = sport_setting_target_data[Get_current_sporting_type()].sport_seeting_choose_target;
        for (uint8_t i = 0; i < SPORT_SETTING_MAX; i++)
        {
            if ((flag >> i) & 1)
            {
                printf("%s:%d\n", __func__,i);
                module_ms_app_sport_clear_sport_target(Get_current_sporting_type(), i);
            }
        }
        if(sport_setting_target_data[Get_current_sporting_type()].sport_heart_rate_zones)//除去心率区间提醒
        {
            uint32_t flag = 0;
            flag = 1 << (SPORT_SETTING_MAX + sport_setting_target_data[Get_current_sporting_type()].sport_heart_rate_zones);
            misc_sport_data.copy_choose_target |= flag;
            sport_setting_target_data[Get_current_sporting_type()].sport_heart_rate_zones = 0;
            printf("erase flag:0x%x,0x%x\n",flag,misc_sport_data.copy_choose_target);
        }
    }
}

void module_sport_app_release_target(void)
{
    if (misc_sport_data.auto_sportting_flag||module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_INTERVAL_TRAINING_SWITCH))
    {
        for (uint8_t i = 1; i < 5; i++)
        {
            if (sport_target >> i & 1)
            {
                module_ms_app_sport_set_sport_target(Get_current_sporting_type(), i);
            }
        }
    }
    if(misc_sport_data.copy_choose_target)
    {
         for (uint8_t i = 0; i < SPORT_SETTING_MAX; i++)
        {
            if ((misc_sport_data.copy_choose_target >> i) & 1)
            {
                module_ms_app_sport_set_sport_target(Get_current_sporting_type(), i);
            }
        }
        if (misc_sport_data.copy_choose_target & 0xFE0000) // 恢复心率区间
        {
            uint32_t flag = 0;
            for (uint8_t i = SPORT_SETTING_MAX; i < (SPORT_SETTING_MAX + 5); i++)
            {
                if ((misc_sport_data.copy_choose_target >> i) & 1)
                {
                    sport_setting_target_data[Get_current_sporting_type()].sport_heart_rate_zones = flag;
                    printf("restorehr_zones:%d,0x%x\n", flag, sport_setting_target_data[Get_current_sporting_type()].sport_seeting_choose_target);
                }
                flag++;
            }
        }
    }
    misc_sport_data.copy_choose_target = 0;
    misc_sport_data.auto_sportting_flag = 0;
}

bool module_sport_app_is_sportting(void)
{
    if(misc_sport_data.sport_Function_state != Sport_state_stop)
    {
        //extern bool app_sport_remind_is_running(void);
        //if(app_sport_remind_is_running())
        //{
        //    //app_popup_exit_self(0);
        //    // extern void app_sport_remind_kill(void);
        //    // app_sport_remind_kill();
        //}
        return true;
    }
    else
    {
        return false;
    }
}

void zh_sports_data_projection_ble_process(uint8_t type)
{
    printf("%s,type:%d\n",__func__,type);
#ifndef BSP_USING_PC_SIMULATOR
    switch (type)
    {
    case PROJECTION_POINT:
    {
        interconnection_ioctl_report_sport_data_projection(NULL);
    }
    break;
    case PROJECTION_REPORT:
    {
        interconnection_ioctl_report_sport_report_projection(NULL);
    }
    break;
    case PROJECTION_DISCONNECT:
    {
        app_sport_disconnect_projection();
    }
    break;
    case PROJECTION_CONNECT:
    {
        // app_sport_disconnect_projection();
    }
    break;
    default:
        break;
    }
#endif
}

void zh_sports_data_projection(uint8_t type)
{
#ifndef BSP_USING_PC_SIMULATOR
    uint8_t this_type = type;
    send_msg_to_protobuf_thread(APP_BLE, ZH_APP_TO_BLE_SPORTS_DATA_PROJECTION, &this_type, sizeof(this_type));
#endif
}

void module_ms_app_set_ios_app_exit(uint8_t ios_app_exit)
{
    misc_sport_data.ios_app_exit = ios_app_exit;
     //printf("\r\n ios app enable:%d \r\n",ios_app_exit);
}

uint8_t module_ms_app_get_ios_app_exit(void)
{
    uint8_t uret;
    uret = misc_sport_data.ios_app_exit;
   
    return uret;
}

bool module_ms_app_sport_is_water_sports(uint16_t type)
{
    bool rets = false;
    switch (type)
    {
    case SPORTING_swim_indoor_TYPE:    // 泳池游泳
    case SPORTING_swim_outdoor_TYPE:   // 开放水域游泳
    case SPORTING_sailboat_TYPE:       // 帆船
    case SPORTING_paddle_board_TYPE:   // 桨板
    case SPORTING_water_polo_TYPE:     // 水球
    case SPORTING_aquatic_sport_TYPE:  // 水上运动
    case SPORTING_surfing_TYPE:        // 滑水
    case SPORTING_canoeing_TYPE:       // 皮划艇
    case SPORTING_kayak_rafting_TYPE:  // 皮艇漂流
    case SPORTING_rowing_TYPE:         // 划船
    case SPORTING_motorboat_TYPE:      // 摩托艇
    case SPORTING_web_swimming_TYPE:   // 蹼泳
    case SPORTING_driving_TYPE:        // 跳水
    case SPORTING_fancy_swimming_TYPE: // 花样游泳
    case SPORTING_snorkeling_TYPE:     // 浮潜
    case SPORTING_kite_surfing_TYPE:   // 风筝冲浪
    case SPORTING_indoor_surfing_TYPE: // 室内冲浪
    case SPORTING_dragon_boat_TYPE:    // 龙舟
    {
        rets = true;
    }
    break;
    default:
        break;
    }
    return rets;
}

uint8_t app_sporting_get_brightness_level(void)
{
    uint8_t* brightness = 0;// (uint8_t*)app_db_get_setting_data(APP_SETTING_BACKLIGHT);
	uint8_t set_level = *brightness/2;
    uint8_t ext = 10;
    // if (*brightness > USER_BRIGHTNESS_THREE_LEVEL)
    // {
    //     ext = 20;
    // }
    // else
    // {
    //     ext = 10;
    // }

    // if ((*brightness -ext) < USER_BRIGHTNESS_ONE_LEVEL)
	// {
	// 	set_level = USER_BRIGHTNESS_ONE_LEVEL;
	// }
	// else
	// {
    //     if ((*brightness - ext) <= 0)
    //     {
    //         set_level = USER_BRIGHTNESS_ONE_LEVEL;
    //     }
    //     else
    //         set_level = (*brightness - ext);
    // }
    if (set_level < 1)//USER_BRIGHTNESS_ONE_LEVEL/2)
    {
        set_level = 1;// USER_BRIGHTNESS_ONE_LEVEL / 2;
    }
    printf("set_level:%d,cur:%d,ext:%d\n",set_level,*brightness,ext);
	return set_level;
}

bool app_sportting_is_change_brightness_level(void)
{
    bool flag = false;
#if 0
    if ((Judge_Current_App_And_Page_Is_Running(APP_SPORT_MAIN_STRING_ID, APP_SPORT_SPORTING_STRING_ID) ||
         Judge_Current_App_And_Page_Is_Running(APP_SPORT_MAIN_STRING_ID, PAGE_SPORT_STOP_ID) ||
         Judge_Current_App_And_Page_Is_Running(APP_SPORT_MAIN_STRING_ID, PAGE_SPORT_MUSIC_ID)) &&
        module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_SCREEN_ALWAYS_ON))
    {
        if (mdoule_sport_app_get_change_level())
        {
            if (Get_now_have_popup_status()) // 有弹窗
            {
                flag = false;
            }
            else
            {
                flag = true;
            }
        }
        else
        {
            flag = false;
        }
    }
    else
    {
        flag = false;
    }
#endif
    return flag;
}

void module_sport_app_set_change_level(uint8_t level)
{
    misc_sport_data.change_level = level;
}

uint8_t mdoule_sport_app_get_change_level(void)
{
    return misc_sport_data.change_level;
}

bool app_sportting_is_close_screen(void)
{
    bool flag = false;
    //if ((Judge_Current_App_And_Page_Is_Running(APP_SPORT_MAIN_STRING_ID, APP_SPORT_SPORTING_STRING_ID) ||
    //     Judge_Current_App_And_Page_Is_Running(APP_SPORT_MAIN_STRING_ID, PAGE_SPORT_STOP_ID) ||
    //     Judge_Current_App_And_Page_Is_Running(APP_SPORT_MAIN_STRING_ID, PAGE_SPORT_MUSIC_ID)) &&
    //    module_ms_app_get__data_target_is_switch(Get_current_sporting_type(), SPORT_SCREEN_ALWAYS_ON))
    //{
    //    flag = true;
    //}
    //else
    //{
    //    flag = false;
    //}
    return flag;
}
#if 0
const char *app_sport_app_id_tab[] =
    {
        APP_SPORT_MAIN_STRING_ID,
        APP_RUN_CLASS_MAIN_STRING_ID,
};

const char *app_sport_page_id_tab[] =
    {
        APP_SPORT_SPORTING_STRING_ID,
        PAGE_SPORT_STOP_ID,
        PAGE_SPORT_MUSIC_ID,
        PAGE_SPORT_ALIPAY_QR_CODE_ID,
        PAGE_SPORT_WECHAT_QR_CODE_ID,
        PAGE_SPORT_WECHA_PAGE_QR_CODE_ID,
        APP_SPORT_END_REMIND_STRING_ID,           // 运动结束询问
        APP_SPORT_DISTANCE_CALIBRATION_STRING_ID, // 距离校准
        PAGE_RUN_CLASS_FINISH_STRING_ID,
        PAGE_RUN_CLASS_RUNNING_STRING_ID,
};

uint16_t get_app_sport_app_id_tab_len(void)
{
    return sizeof(app_sport_app_id_tab) / sizeof(char *);
}

uint16_t get_app_sport_page_id_tab_len(void)
{
    return sizeof(app_sport_page_id_tab) / sizeof(char *);
}

bool module_sport_app_get_is_running_page(void)
{
    printf("%s\n",__func__);
    bool ret = false;
    if (misc_sport_data.sport_Function_state != Sport_state_stop)
    {
        uint8_t app_len = get_app_sport_app_id_tab_len();
        uint8_t page_len = get_app_sport_page_id_tab_len();
        for (uint8_t i = 0; i < app_len; i++)
        {
            for (uint8_t j = 0; i < page_len; j++)
            {
                if (Judge_Current_App_And_Page_Is_Running(app_sport_app_id_tab[i], app_sport_page_id_tab[j]))
                {
                    printf("->app_id:%s,page_id:%s\n",app_sport_app_id_tab[i], app_sport_page_id_tab[j]);
                    ret = true;
                    break;
                }
            }
        }
    }
    return ret;
}

void module_sport_app_save_running_page_id(rt_list_t *rt_list)
{
    if (rt_list != NULL)
    {
        uint32_t len = rt_list_len(rt_list);
        if (misc_sport_data.sport_Function_state != Sport_state_stop)
        {
            if (len >= 2) // 大于两个保存一下
            {
                rt_list_t *pos, *next;

                rt_list_for_each_safe(pos, next, rt_list)
                {
                    app_idle_node_t *app_node = (app_idle_node_t *)rt_list_entry(pos, app_idle_node_t, list);
#if !defined(BSP_USING_PC_SIMULATOR) && defined(XIAOMI_ALGO_LIB_ON_LCPU)
                    Zh_Log_Fun_Write_Ram_Memory(SPORT_STATE_LOG, "app_id:%s,page_id:%s,state:%d,len:%d",
                                                app_node->app_id,
                                                app_node->page_id,
                                                app_node->state,
                                                len);
#endif
                }
            }
        }
    }
}
#endif