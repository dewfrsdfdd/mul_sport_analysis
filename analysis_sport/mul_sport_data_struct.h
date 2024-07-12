#ifndef _MUL_SPORT_DATA_STRUCT_H
#define _MUL_SPORT_DATA_STRUCT_H

#include <stdint.h>

#include "vital_info_data_struct.h"

#pragma pack(push, 1)

typedef enum {
    SP_HYBRID = 0,
    SP_BREASTSTROKE,
    SP_FREESTYLE,
    SP_BACKSTROKE,
    SP_BUTTERFLY
} Swimming_Posture_Type;

typedef enum {
    SIT_WARM_UP = 0,
    SIT_TRAINING = 1,
    SIT_REST = 2,
    SIT_RELAX = 3,
    SIT_BEAT_IT = 4,
    SIT_CANTER = 5,
    SIT_MODERATE_PACE = 6,
    SIT_TANTIVY = 7,
    SIT_ACTIVITY = 8,
    SIT_NONE = 127,
} Sport_Interval_Training_Type;

typedef struct _ms_gps_item_v1 {
    uint32_t ts;
    float longitude;
    float latitude;
} ms_gps_item_v1;

typedef struct _ms_gps_item_v2 {
    uint32_t ts;
    float longitude;
    float latitude;
    float location_accuracy;
    union {
        uint16_t fv_d;
        struct {
            uint16_t gps_source : 4;
            uint16_t location_speed : 12;
        } speed_gps_s;
    } speed_gps_u;
} ms_gps_item_v2;

typedef union _ms_gps_item_t
{
    ms_gps_item_v2 gps_vx;
    ms_gps_item_v1 gps_v1;
    ms_gps_item_v2 gps_v2;
} ms_gps_item_t;

typedef union _ms_record_item_t {
    struct {
        uint8_t  hr;
        uint16_t pace;      // 配速
        uint8_t  cadence;   // 步数步频
    } out_run_c;    // 户外跑步类

    struct {
        uint8_t  hr;
        uint16_t pace;      // 配速
        uint8_t  cadence;   // 步数步频
    } indoor_run;    // 室内跑步

    struct {
        uint8_t  hr;
        uint16_t speed;
    } out_non_run_c;    // 户外非跑步类

    struct {
        uint8_t  hr;
    } free_sport;    // 自由训练类

    struct {
        uint8_t  hr;
        uint16_t action_freq; // 跳绳频率
    } rope_skip;    // 跳绳类

    struct {
        uint8_t  hr;
        uint8_t  cadence;   // 椭圆机步频
    } elliptical_m;

    struct {
        uint8_t  hr;
        uint16_t action_freq;   // 划船划频
    } rowing_m;    // 划船机类

    struct {
        uint16_t pace;
        uint16_t swolf;
        uint8_t  pull_rate;      // 游泳划频
    } swimming;    // 游泳类
} ms_record_item_t;

typedef struct _ms_record_info_t {
    uint32_t data_head_len;
    uint32_t data_body_len;
    uint32_t data_section_len;  // 如果运动打点是有部分和整体打点两种情况,则需要先读取部分;判断类型后,再确认是否要读取整体
} ms_record_info_t;

typedef struct _ms_record_head_t {
    uint32_t count_sport_hold;
} ms_record_head_t;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[2];
            struct {
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_extra_calorie;
                        field_valid_l_type fv_hr;
                    }fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_height_change;
                        field_valid_l_type fv_extra_distance;
                    } fv_s;
                } fv_s2;
            } fv_s;
        } field_valid;
    } pack_head;
    union {
        struct {
            float initialize_altitude;
            uint32_t count_sport_hold;
            uint32_t restore_time;
        } data_head;
        struct {
            union {
                uint8_t ec_d;
                struct {
                    uint8_t extra_step : 4;
                    uint8_t extra_calorie : 4;
                }ec_s;
            } extra_calorie;
            uint8_t hr;
            union {
                uint8_t hc_d;
                struct {
                    uint8_t height_change : 6;
                    uint8_t is_up: 1;
                    uint8_t is_km : 1;
                } hc_s;
            } heigth_change;
            uint8_t extra_distance;
        } data_body;
    } data_s;
} Outside_Run_Data_Type_V1;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[2];
            struct {
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_extra_calorie;
                        field_valid_l_type fv_hr;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 4;
                        uint8_t valid : 3;
                        uint8_t exist : 1;
                    } fv_extra_distance;
                } fv_s2;
            } fv_s;
        } field_valid;
    } pack_head;
    union {
        struct {
            uint32_t count_sport_hold;
            uint32_t restore_time;
        } data_head;
        struct {
            union {
                uint8_t ec_d;
                struct {
                    uint8_t extra_step : 4;
                    uint8_t extra_calorie : 4;
                } ec_s;
            } extra_calorie;
            uint8_t hr;
            uint8_t extra_distance;
        } data_body;
    } data_s;
} Indoor_Run_Data_Type_V1;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[2];
            struct {
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_extra_calorie;
                        field_valid_l_type fv_hr;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_extra_stride;
                        field_valid_l_type fv_extra_distance;
                    } fv_s;
                } fv_s2;
            } fv_s;
        } field_valid;
    } pack_head;
    union {
        struct {
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union {
                uint8_t st_d;
                struct {
                    uint8_t training_type: 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
        } data_head;
        struct {
            union {
                uint8_t ec_d;
                struct {
                    uint8_t extra_step : 4;
                    uint8_t extra_calorie : 4;
                } ec_s;
            } extra_calorie;
            uint8_t hr;
            uint8_t extra_distance;
            uint8_t extra_stride;
        } data_body;
    } data_s;
} Indoor_Run_Data_Type_V3;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[4];
            struct {
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_extra_calorie;
                        field_valid_l_type fv_hr;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_extra_stride;
                        field_valid_l_type fv_extra_distance;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_extra_impact_force;
                        field_valid_l_type fv_ground_to_air_ratio;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_cadence;
                        field_valid_l_type fv_pace;
                    } fv_s;
                } fv_s4;
            } fv_s;
        } field_valid;
    } pack_head;
    union {
        struct {
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union {
                uint8_t st_d;
                struct {
                    uint8_t training_type: 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
            uint32_t segment_distance;
        } data_head;
        struct {
            union {
                uint8_t ec_d;
                struct {
                    uint8_t extra_step : 4;
                    uint8_t extra_calorie : 4;
                } ec_s;
            } extra_calorie;
            uint8_t hr;
            uint8_t extra_distance;
            uint8_t extra_stride;
 /*
                union {
                    uint32_t extra;
                    struct {
                        uint32_t extra_t_time : 13;
                        uint32_t extra_time : 13;
                        uint32_t extra_i_f : 6;
                    } ec_s;
                } extra_impact_force;
            uint8_t ground_to_air_ratio;
 */
            uint8_t cadence;
            uint16_t pace;
        } data_body;
    } data_s;
} Indoor_Run_Data_Type_V6;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[2];
            struct {
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_extra_calorie;
                        field_valid_l_type fv_hr;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 4;
                        uint8_t valid : 3;
                        uint8_t exist : 1;
                    } fv_height_change;
                } fv_s2;
            } fv_s;
        } field_valid;
    } pack_head;
    union {
        struct {
            float initialize_altitude;
            uint32_t count_sport_hold;
            uint32_t restore_time;
        } data_head;
        struct {
            uint8_t extra_calorie;
            uint8_t hr;
            union {
                uint8_t hc_d;
                struct {
                    uint8_t height_change : 6;
                    uint8_t is_up: 1;
                    uint8_t is_km : 1;
                } hc_s;
            } heigth_change;
        } data_body;
    } data_s;
} Outside_Cycle_Data_Type_V1;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[3];
            struct {
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_extra_calorie;
                        field_valid_l_type fv_hr;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 4;
                        uint8_t valid : 3;
                        uint8_t exist : 1;
                    } fv_height_change;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_speed;
                        field_valid_l_type fv_cadence;
                    } fv_s;
                } fv_s3;
            } fv_s;
        } field_valid;
    } pack_head;
    union {
        struct {
            float initialize_altitude;
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union {
                uint8_t st_d;
                struct {
                    uint8_t training_type: 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
        } data_head;
        struct {
            uint8_t extra_calorie;
            uint8_t hr;
            union {
                uint8_t hc_d;
                struct {
                    uint8_t height_change : 6;
                    uint8_t is_up: 1;
                    uint8_t is_km : 1;
                } hc_s;
            } heigth_change;
        } data_body;
    } data_s;
} Outside_Cycle_Data_Type_V2;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[3];
            struct {
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_extra_calorie;
                        field_valid_l_type fv_hr;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 4;
                        uint8_t valid : 3;
                        uint8_t exist : 1;
                    } fv_height_change;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 4;
                        uint8_t valid : 3;
                        uint8_t exist : 1;
                    } fv_speed;
                } fv_s3;
            } fv_s;
        } field_valid;
    } pack_head;
    union {
        struct {
            float initialize_altitude;
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union {
                uint8_t st_d;
                struct {
                    uint8_t training_type: 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
            uint32_t segment_total_distance;
        } data_head;
        struct {
            union {
                uint8_t ec_d;
                struct {
                    uint8_t extra_count : 4;
                    uint8_t extra_calorie : 4;
                } ec_s;
            } extra_calorie;
            uint8_t hr;
            union {
                uint8_t hc_d;
                struct {
                    uint8_t height_change : 6;
                    uint8_t is_up: 1;
                    uint8_t is_km : 1;
                } hc_s;
            } heigth_change;
            uint8_t extra_distance;
            uint16_t speed;
            // uint8_t cadence;
        } data_body;
    } data_s;
} Outside_Non_Running_Data_Type_V3;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d;
            struct {
                uint8_t : 6;
                uint8_t fv_extra_calorie : 1;
                uint8_t fv_hr : 1;
            } fv_s;
        } field_valid;
    } pack_head;
    union {
        struct {
            uint32_t count_sport_hold;
            uint32_t restore_time;
        } data_head;
        struct {
            uint8_t hr;
            uint8_t extra_calorie;
        } data_body;
    } data_s;
} Indoor_Cycle_Data_Type_V1;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            }ec_opt;
        } ec_opt_s;
        union {
            uint16_t fv_d;
            struct {
                uint16_t fv_total_turn_count : 1;
                uint16_t fv_total_pull_count : 1;
                uint16_t fv_total_calorie : 1;
                uint16_t fv_total_distance : 1;
                uint16_t fv_swolf : 1;
                uint16_t fv_pace : 1;
                uint16_t fv_posture : 1;
                uint16_t fv_timestamp : 1;

                uint16_t : 2;
                uint16_t fv_butterfly_pull_count : 1;
                uint16_t fv_backstroke_pull_count : 1;
                uint16_t fv_freestyle_pull_count : 1;
                uint16_t fv_breaststroke_pull_count : 1;
                uint16_t fv_unknown_pull_count : 1;
                uint16_t fv_pull_rate : 1;
            } fv_s;
        } field_valid;
    } pack_head;
    union {
        struct {
            uint32_t count_sport_hold;
            uint32_t restore_time;
        } data_head;
        struct {
            uint8_t  data_type;
            uint32_t timestamp;
            Swimming_Posture_Type  posture;
            uint16_t pace;
            uint16_t swolf;
            uint16_t total_distance;
            uint16_t total_calorie;
            uint16_t total_pull_count;
            uint16_t total_turn_count;
            uint8_t  pull_rate;
            uint8_t  unknown_pull_count;
            uint8_t  breaststroke_pull_count;
            uint8_t  freestyle_pull_count;
            uint8_t  backstroke_pull_count;
            uint8_t  butterfly_pull_count;
        } data_body;
    } data_s;
} Swimming_Data_Type_V1;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            }ec_opt;
        } ec_opt_s;
        union {
            uint16_t fv_d;
            struct {
                uint16_t fv_total_turn_count : 1;
                uint16_t fv_total_pull_count : 1;
                uint16_t fv_total_calorie : 1;
                uint16_t fv_total_distance : 1;
                uint16_t fv_swolf : 1;
                uint16_t fv_pace : 1;
                uint16_t fv_posture : 1;
                uint16_t fv_timestamp : 1;

                uint16_t : 2;
                uint16_t fv_butterfly_pull_count : 1;
                uint16_t fv_backstroke_pull_count : 1;
                uint16_t fv_freestyle_pull_count : 1;
                uint16_t fv_breaststroke_pull_count : 1;
                uint16_t fv_unknown_pull_count : 1;
                uint16_t fv_pull_rate : 1;
            } fv_s;
        } field_valid;
    } pack_head;
    union {
        struct {
            uint32_t count_sport_hold;
            uint32_t restore_time;
        } data_head;
        struct {
            struct {
                uint8_t  data_type;
                uint32_t timestamp;
                Swimming_Posture_Type  posture;
                uint16_t pace;
                uint16_t swolf;
            }section_data;
            uint16_t total_distance;
            uint16_t sport_calorie;
            uint16_t total_pull_count;
            uint16_t total_turn_count;
            uint8_t  pull_rate;
            uint8_t  unknown_pull_count;
            uint8_t  breaststroke_pull_count;
            uint8_t  freestyle_pull_count;
            uint8_t  backstroke_pull_count;
            uint8_t  butterfly_pull_count;
            uint16_t total_calorie;
        } data_body;
    } data_s;
} Swimming_Data_Type_V2;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d;
            struct {
                uint8_t : 6;
                uint8_t fv_extra_calorie : 1;
                uint8_t fv_hr : 1;
            } fv_s;
        } field_valid;
    } pack_head;
    union {
        struct {
            uint32_t count_sport_hold;
            uint32_t restore_time;
        } data_head;
        struct {
            uint8_t hr;
            uint8_t extra_calorie;
        } data_body;
    } data_s;
} Free_Sport_Data_Type_V1;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d;
            struct {
                uint8_t : 6;
                uint8_t fv_extra_calorie : 1;
                uint8_t fv_hr : 1;
            } fv_s;
        } field_valid;
    } pack_head;
    union {
        struct {
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union {
                uint8_t st_d;
                struct {
                    uint8_t training_type: 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
        } data_head;
        struct {
            uint8_t hr;
            uint8_t extra_calorie;
        } data_body;
    } data_s;
} Free_Sport_Data_Type_V2;

typedef union {
    uint8_t *p_data;

    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d;
            union {
                field_valid_h_type fv_extra_calorie;
                field_valid_l_type fv_hr;
            }fv_s;
        } field_valid;
    } pack_head;

    union {
        struct {
            uint32_t count_sport_hold;
            uint32_t restore_time;
        } data_head;
        struct {
            union {
                uint8_t ec_d;
                struct {
                    uint8_t extra_step : 4;
                    uint8_t extra_calorie : 4;
                }ec_s;
            } extra_calorie;
            uint8_t hr;
        } data_body;
    } data_s;
} Elliptical_Machine_Data_Type_V1;

typedef union {
    uint8_t *p_data;

    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d;
            union {
                field_valid_h_type fv_extra_calorie;
                field_valid_l_type fv_hr;
            }fv_s;
        } field_valid;
    } pack_head;

    union {
        struct {
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union {
                uint8_t st_d;
                struct {
                    uint8_t training_type: 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
        } data_head;
        struct {
            union {
                uint8_t ec_d;
                struct {
                    uint8_t extra_step : 4;
                    uint8_t extra_calorie : 4;
                }ec_s;
            } extra_calorie;
            uint8_t hr;
        } data_body;
    } data_s;
} Elliptical_Machine_Data_Type_V2;

typedef union {
    uint8_t *p_data;

    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[2];
            struct {
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_hr;
                        field_valid_l_type fv_extra_calorie;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_cadence;
                    } fv_s;
                } fv_s2;
            } fv_s;
        } field_valid;
    } pack_head;

    union {
        struct {
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union {
                uint8_t st_d;
                struct {
                    uint8_t training_type: 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
        } data_head;
        struct {
            union {
                uint8_t ec_d;
                struct {
                    uint8_t extra_step : 4;
                    uint8_t extra_calorie : 4;
                }ec_s;
            } extra_calorie;
            uint8_t hr;
            uint8_t cadence;
        } data_body;
    } data_s;
} Elliptical_Machine_Data_Type_V3;
typedef union {
    uint8_t *p_data;

    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d;
            union {
                uint8_t : 4;
                uint8_t fv_takeoff_height: 1;
                uint8_t fv_extra_jumps : 1;
                uint8_t fv_extra_calorie : 1;
                uint8_t hr : 1;
            }fv_s;
        } field_valid;
    } pack_head;

    union {
        struct {
            uint32_t count_sport_hold;
            uint32_t restore_time;
            uint8_t  is_group;
            uint32_t count_until_next_group;
        } data_head;
        struct {
            uint8_t hr;
            uint8_t extra_calorie;
            uint8_t extra_jumps;
            uint8_t takeoff_height;
        } data_body;
    } data_s;
} Rope_Skipping_Data_Type_V1;

typedef union {
    uint8_t *p_data;

    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d;
            union {
                uint8_t : 3;
                uint8_t fv_extra_trips : 1;
                uint8_t fv_takeoff_height: 1;
                uint8_t fv_extra_jumps : 1;
                uint8_t fv_extra_calorie : 1;
                uint8_t hr : 1;
            }fv_s;
        } field_valid;
    } pack_head;

    union {
        struct {
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union {
                uint8_t st_d;
                struct {
                    uint8_t training_type: 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
        } data_head;
        struct {
            uint8_t hr;
            uint8_t extra_calorie;
            uint8_t extra_jumps;
            uint8_t takeoff_height;
            uint8_t extra_trips;
        } data_body;
    } data_s;
} Rope_Skipping_Data_Type_V3;
typedef union {
    uint8_t *p_data;

    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[3];
            struct {
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_hr;
                        field_valid_l_type fv_extra_calorie;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_cadence;
                        field_valid_l_type fv_hight;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 4;
                        uint8_t valid : 3;
                        uint8_t exist : 1;
                    } fv_extra_trips;
                } fv_s3;
            } fv_s;
        } field_valid;
    } pack_head;

    union {
        struct {
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union {
                uint8_t st_d;
                struct {
                    uint8_t training_type: 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
            uint32_t segment_count; 
        } data_head;
        struct {
            uint8_t hr;
            uint8_t extra_calorie;
            uint16_t cadence;
            // uint8_t takeoff_height;
            // uint8_t extra_trips;
        } data_body;
    } data_s;
} Rope_Skipping_Data_Type_V5;
typedef union {
    uint8_t *p_data;

    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[2];
            struct {
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_extra_calorie;
                        field_valid_l_type fv_hr;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 4;
                        uint8_t valid : 3;
                        uint8_t exist : 1;
                    } fv_extra_stroke;
                } fv_s2;
            } fv_s;
        } field_valid;
    } pack_head;
    union {
        struct {
            uint32_t count_sport_hold;
            uint32_t restore_time;
            uint8_t  is_group;
            uint32_t count_until_next_group;
        } data_head;
        struct {
            uint8_t hr;
            uint8_t extra_calorie;
            union {
                uint8_t es_d;
                struct {
                    uint8_t extra_stroke : 6;
                    uint8_t is_put: 1;
                    uint8_t is_drive : 1;
                } es_s;
            } extra_stroke;
        } data_body;
    } data_s;
} Rowing_Machine_Data_Type_V1;

typedef union {
    uint8_t *p_data;

    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[2];
            struct {
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_extra_calorie;
                        field_valid_l_type fv_hr;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 4;
                        uint8_t valid : 3;
                        uint8_t exist : 1;
                    } fv_extra_stroke;
                } fv_s2;
            } fv_s;
        } field_valid;
    } pack_head;
    union {
        struct {
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union {
                uint8_t st_d;
                struct {
                    uint8_t training_type: 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
        } data_head;
        struct {
            uint8_t hr;
            uint8_t extra_calorie;
            union {
                uint8_t es_d;
                struct {
                    uint8_t extra_stroke : 6;
                    uint8_t is_put: 1;
                    uint8_t is_drive : 1;
                } es_s;
            } extra_stroke;
        } data_body;
    } data_s;
} Rowing_Machine_Data_Type_V2;
typedef union {
    uint8_t *p_data;

    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[2];
            struct {
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_extra_calorie;
                        field_valid_l_type fv_hr;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 4;
                        uint8_t valid : 3;
                        uint8_t exist : 1;
                    } fv_cadence;
                } fv_s2;
            } fv_s;
        } field_valid;
    } pack_head;
    union {
        struct {
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union {
                uint8_t st_d;
                struct {
                    uint8_t training_type: 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
            uint32_t segment_times;//本段总划次
        } data_head;
        struct {
            uint8_t hr;
            uint8_t extra_calorie;
            uint8_t sliding_frequency;
        } data_body;
    } data_s;
} Rowing_Machine_Data_Type_V4;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[3];
            struct {
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_extra_calorie;
                        field_valid_l_type fv_hr;
                    }fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_height_change;
                        field_valid_l_type fv_extra_distance;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_stride;
                        field_valid_l_type fv_tbd;
                    } fv_s;
                } fv_s3;
            } fv_s;
        } field_valid;
    } pack_head;
    union {
        struct {
            float initialize_altitude;
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union {
                uint8_t st_d;
                struct {
                    uint8_t training_type: 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
        } data_head;
        struct {
            union {
                uint8_t ec_d;
                struct {
                    uint8_t extra_step : 4;
                    uint8_t extra_calorie : 4;
                }ec_s;
            } extra_calorie;
            uint8_t hr;
            union {
                uint8_t hc_d;
                struct {
                    uint8_t height_change : 6;
                    uint8_t is_up: 1;
                    uint8_t is_km : 1;
                } hc_s;
            } heigth_change;
            uint8_t extra_distance;
            uint8_t extra_stride;
        } data_body;
    } data_s;
} Outside_Run_Category_Data_Type_V2;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[5];
            struct {
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_extra_calorie;//kcal step
                        field_valid_l_type fv_hr;
                    }fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_height_change;
                        field_valid_l_type fv_extra_distance;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_stride;
                        field_valid_l_type fv_tbd;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_ground_to_air_ratio;
                        field_valid_l_type fv_cadence;
                    } fv_s;
                } fv_s4;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_pace;
                    } fv_s;
                } fv_s5;
            } fv_s;
        } field_valid;
    } pack_head;
    union {
        struct {
            float initialize_altitude;
            uint32_t count_sport_hold;
            uint32_t restore_time;
            union {
                uint8_t st_d;
                struct {
                    uint8_t training_type: 7;
                    uint8_t segment_type : 1;
                } st_s;
            } segment_type;
            uint32_t segment_distance;
        } data_head;
        struct {
            union {
                uint8_t ec_d;
                struct {
                    uint8_t extra_step : 4;
                    uint8_t extra_calorie : 4;
                }ec_s;
            } extra_calorie;
            uint8_t hr;
            union {
                uint8_t hc_d;
                struct {
                    uint8_t height_change : 6;
                    uint8_t is_up: 1;
                    uint8_t is_km : 1;
                } hc_s;
            } heigth_change;
            uint8_t extra_distance;
            uint8_t extra_stride;
            uint8_t cadence;
            uint16_t pace; 
        } data_body;
    } data_s;
} Outside_Run_Category_Data_Type_V5;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint32_t fv_d;
            struct {
                uint32_t fv_fast_speed : 1;
                uint32_t fv_low_speed : 1;
                uint32_t fv_high_speed : 1;
                uint32_t fv_sport_calorie : 1;
                uint32_t fv_sport_total_distance : 1;
                uint32_t fv_sport_total_time : 1;
                uint32_t fv_sport_stop_time : 1;
                uint32_t fv_sport_start_time : 1;

                uint32_t fv_avg_height : 1;
                uint32_t fv_total_down : 1;
                uint32_t fv_total_up : 1;
                uint32_t fv_min_hr : 1;
                uint32_t fv_max_hr : 1;
                uint32_t fv_avg_hr : 1;
                uint32_t fv_max_step_rate : 1;
                uint32_t fv_total_step : 1;

                uint32_t fv_hr_without_oxygen : 1;
                uint32_t fv_hr_limit_time : 1;
                uint32_t fv_recover_time : 1;
                uint32_t fv_body_power_use : 1;
                uint32_t fv_max_oxygen_uptake : 1;
                uint32_t fv_training_effect : 1;
                uint32_t fv_min_height : 1;
                uint32_t fv_max_height : 1;

                uint32_t : 5;
                uint32_t fv_hr_warmup : 1;
                uint32_t fv_hr_expend_fat : 1;
                uint32_t fv_hr_with_oxygen : 1;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint32_t sport_total_distance;
        uint16_t sport_calorie;
        uint32_t high_speed;
        uint32_t low_speed;
        float fast_speed;
        uint32_t total_step;
        uint16_t max_step_rate;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float total_up;
        float total_down;
        float avg_height;
        float max_height;
        float min_height;
        float training_effect;
        uint8_t max_oxygen_uptake;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
    } data_s;
} Report_Outside_Run_Data_Type_V1;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[5];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_fast_speed : 1;
                        uint8_t fv_low_speed : 1;
                        uint8_t fv_high_speed : 1;
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_sport_total_distance : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_avg_height : 1;
                        uint8_t fv_total_down : 1;
                        uint8_t fv_total_up : 1;
                        uint8_t fv_min_hr : 1;
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_max_step_rate : 1;
                        uint8_t fv_total_step : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_recover_time : 1;
                        uint8_t fv_body_power_use : 1;
                        uint8_t fv_max_oxygen_uptake : 1;
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_height : 1;
                        uint8_t fv_max_height : 1;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_hr_zone_selection : 1;
                        uint8_t fv_designated_courses : 1;
                        uint8_t fv_anaerobic_training_effect : 1;
                        uint8_t fv_valid_exercise_time: 1;
                        uint8_t fv_total_calorie : 1;
                        uint8_t fv_hr_warmup : 1;
                        uint8_t fv_hr_expend_fat : 1;
                        uint8_t fv_hr_with_oxygen : 1;
                    } fv_s;
                } fv_s4;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 3;
                        uint8_t fv_target_cadence : 1;
                        uint8_t fv_target_pace : 1;
                        uint8_t fv_target_distance : 1;
                        uint8_t fv_target_calorie : 1;
                        uint8_t fv_target_duration : 1;
                    } fv_s;
                } fv_s5;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint32_t sport_total_distance;
        uint16_t sport_calorie;
        uint32_t high_speed;
        uint32_t low_speed;
        float fast_speed;
        uint32_t total_step;
        uint16_t max_step_rate;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float total_up;
        float total_down;
        float avg_height;
        float max_height;
        float min_height;
        float training_effect;
        uint8_t max_oxygen_uptake;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
        uint16_t total_calorie;
        uint32_t valid_exercise_time;
        uint32_t anaerobic_training_effect;
        uint8_t  designated_courses;
//        uint64_t courses_id;
        uint8_t hr_zone_selection;
        uint32_t target_duration;
        uint16_t target_calorie;
        uint32_t target_distance;
        uint32_t target_pace;
        uint16_t target_cadence;
    } data_s;
} Report_Outside_Run_Data_Type_V4;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[3];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_total_step : 1;
                        uint8_t fv_low_speed : 1;
                        uint8_t fv_high_speed : 1;
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_sport_total_distance : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_recover_time : 1;
                        uint8_t fv_body_power_use : 1;
                        uint8_t fv_max_oxygen_uptake : 1;
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_hr : 1;
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_max_step_rate : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 3;
                        uint8_t fv_hr_warmup : 1;
                        uint8_t fv_hr_expend_fat : 1;
                        uint8_t fv_hr_with_oxygen : 1;
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                    } fv_s;
                } fv_s3;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint32_t sport_total_distance;
        uint16_t sport_calorie;
        uint32_t high_speed;
        uint32_t low_speed;
        uint32_t total_step;
        uint16_t max_step_rate;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float training_effect;
        uint8_t max_oxygen_uptake;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
    } data_s;
} Report_Indoor_Run_Data_Type_V1;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            }ec_opt;
        }ec_opt_s;
        union {
            uint32_t fv_d;
            struct {
                uint32_t fv_total_step : 1;
                uint32_t fv_low_speed : 1;
                uint32_t fv_high_speed : 1;
                uint32_t fv_sport_calorie : 1;
                uint32_t fv_sport_total_distance : 1;
                uint32_t fv_sport_total_time : 1;
                uint32_t fv_sport_stop_time : 1;
                uint32_t fv_sport_start_time : 1;
                
                uint32_t fv_recover_time : 1;
                uint32_t fv_body_power_use : 1;
                uint32_t fv_max_oxygen_uptake : 1;
                uint32_t fv_training_effect : 1;
                uint32_t fv_min_hr : 1;
                uint32_t fv_max_hr : 1;
                uint32_t fv_avg_hr : 1;
                uint32_t fv_max_step_rate : 1;

                uint32_t fv_anaerobic_training_effect : 1;
                uint32_t fv_valid_exercise_time: 1;
                uint32_t fv_total_calorie : 1;
                uint32_t fv_hr_warmup : 1;
                uint32_t fv_hr_expend_fat : 1;
                uint32_t fv_hr_with_oxygen : 1;
                uint32_t fv_hr_without_oxygen : 1;
                uint32_t fv_hr_limit_time : 1;

                uint32_t fv_fixed_distance : 1;
                uint32_t fv_target_cadence : 1;
                uint32_t fv_target_pace : 1;
                uint32_t fv_target_distance : 1;
                uint32_t fv_target_calorie : 1;
                uint32_t fv_target_duration : 1;
                uint32_t fv_hr_zone_selection : 1;
                uint32_t fv_designated_courses : 1;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint32_t sport_total_distance;
        uint16_t sport_calorie;
        uint32_t high_speed;
        uint32_t low_speed;
        uint32_t total_step;
        uint16_t max_step_rate;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float training_effect;
        uint8_t max_oxygen_uptake;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
        uint16_t total_calorie;
        uint32_t valid_exercise_time;
        uint32_t anaerobic_training_effect;
        uint8_t  designated_courses;
//        uint64_t courses_id;
        uint8_t hr_zone_selection;
        uint32_t target_duration;
        uint16_t target_calorie;
        uint32_t target_distance;
        uint32_t target_pace;
        uint16_t target_cadence;
        uint32_t fixed_distance;
    } data_s;
} Report_Indoor_Run_Data_Type_V5;
typedef union {
  uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            }ec_opt;
        }ec_opt_s;
        union {
            uint8_t fv_d[6];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_total_step : 1;
                        uint8_t fv_low_speed : 1;
                        uint8_t fv_high_speed : 1;
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_sport_total_distance : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_max_oxygen_uptake_rate : 1;
                        uint8_t fv_max_oxygen_uptake : 1;
                        uint8_t fv_aerobic_training_effect : 1;
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_hr : 1;
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_max_step_rate : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_total_calorie : 1;
                        uint8_t fv_hr_warmup : 1;
                        uint8_t fv_hr_expend_fat : 1;
                        uint8_t fv_hr_with_oxygen : 1;
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_recover_time : 1;
                        uint8_t fv_body_power_use : 1;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_target_calorie : 1;
                        uint8_t fv_target_duration : 1;
                        uint8_t fv_hr_zone_selection : 1;
                        uint8_t fv_designated_courses : 1;
                        uint8_t fv_subtype : 1;
                        uint8_t fv_anaerobic_training_effect_rate : 1;
                        uint8_t fv_anaerobic_training_effect : 1;
                        uint8_t fv_valid_exercise_time : 1;
                    } fv_s;
                } fv_s4;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_running_power_index : 1;
                        uint8_t fv_training_load_rate : 1;
                        uint8_t fv_training_load : 1;
                        uint8_t fv_fixed_distance : 1;
                        uint8_t fv_target_cadence : 1;
                        uint8_t fv_target_speed : 1;
                        uint8_t fv_target_pace : 1;
                        uint8_t fv_target_distance : 1;
                    } fv_s;
                } fv_s5;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 1;
                        uint8_t fv_inversion_amplitude : 1;
                        uint8_t fv_hell_landing_time : 1;
                        uint8_t fv_forehand_landing_time : 1;
                        uint8_t fv_full_palm_landing_time : 1;
                        uint8_t fv_genki_value : 1;
                        uint8_t fv_training_state : 1;
                        uint8_t fv_running_power_level : 1;
                    } fv_s;
                } fv_s6;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint32_t sport_total_distance;
        uint16_t sport_calorie;
        uint32_t high_speed;
        uint32_t low_speed;
        uint32_t total_step;

        uint16_t max_step_rate;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float training_effect;
        uint8_t aerobic_training_effect;
        uint8_t max_oxygen_uptake;
        uint8_t max_oxygen_uptake_rate;

        uint8_t body_power_use;
        uint16_t recover_time; 
        uint32_t hr_limit_time; 
        uint32_t hr_without_oxygen; 
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
        uint16_t total_calorie;

        uint32_t valid_exercise_time;
        float anaerobic_training_effect;
        uint8_t anaerobic_training_effect_rate;
        uint16_t subtype;
        uint8_t designated_courses;
         //uint64_t courses_id;
        uint8_t hr_zone_selection;
        uint32_t target_duration;
        uint16_t target_calorie;

        uint32_t target_distance;
        uint32_t target_pace;
        float target_speed;
        uint16_t target_cadence;
        uint32_t fixed_distance;
        uint16_t training_load;
        uint8_t training_load_rate;
        float running_power_index;

        uint8_t running_power_level;
        uint8_t training_state;
        uint8_t genki_value;
        uint32_t full_palm_landing_time;
        uint32_t forehand_landing_time;
        uint32_t hell_landing_time;
        uint8_t inversion_amplitude;
    } data_s;
} Report_Indoor_Run_Data_Type_V9;

typedef union {
  uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            }ec_opt;
        }ec_opt_s;
        union {
            uint8_t fv_d[8];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_low_pace : 1;
                        uint8_t fv_fast_pace : 1;
                        uint8_t fv_avg_pace : 1;
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_sport_total_distance : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_hr : 1;
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_max_step_rate : 1;
                        uint8_t fv_avg_cadence : 1;
                        uint8_t fv_avg_stride : 1;
                        uint8_t fv_total_step : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_hr_with_oxygen : 1;
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_recover_time : 1;
                        uint8_t fv_body_power_use : 1;
                        uint8_t fv_max_oxygen_uptake_rate : 1;
                        uint8_t fv_max_oxygen_uptake : 1;
                        uint8_t fv_aerobic_training_effect : 1;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_designated_courses : 1;
                        uint8_t fv_subtype : 1;
                        uint8_t fv_anaerobic_training_effect_rate : 1;
                        uint8_t fv_anaerobic_training_effect : 1;
                        uint8_t fv_valid_exercise_time : 1;
                        uint8_t fv_total_calorie : 1;
                        uint8_t fv_hr_warmup : 1;
                        uint8_t fv_hr_expend_fat : 1;
                    } fv_s;
                } fv_s4;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_fixed_distance : 1;
                        uint8_t fv_target_cadence : 1;
                        uint8_t fv_target_speed : 1;
                        uint8_t fv_target_pace : 1;
                        uint8_t fv_target_distance : 1;
                        uint8_t fv_target_calorie : 1;
                        uint8_t fv_target_duration : 1;
                        uint8_t fv_hr_zone_selection : 1;
                    } fv_s;
                } fv_s5;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_forehand_landing_time : 1;
                        uint8_t fv_full_palm_landing_time : 1;
                        uint8_t fv_genki_value : 1;
                        uint8_t fv_training_state : 1;
                        uint8_t fv_running_power_level : 1;
                        uint8_t fv_running_power_index : 1;
                        uint8_t fv_training_load_rate : 1;
                        uint8_t fv_training_load : 1;
                    } fv_s;
                } fv_s6;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_avg_touchdown_time : 1;
                        uint8_t fv_max_landing_impact_force : 1;
                        uint8_t fv_avg_landing_impact_force : 1;
                        uint8_t fv_running_posture_back: 1;
                        uint8_t fv_running_posture_lead : 1;
                        
                        uint8_t main_landing_methods: 1;
                        uint8_t fv_inversion_amplitude : 1;
                        uint8_t fv_hell_landing_time : 1;
                    } fv_s;
                } fv_s7;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t  : 3;
                        uint8_t fv_min_ground_to_air_ratio : 1;
                        uint8_t fv_avg_ground_to_air_ratio : 1;
                        uint8_t fv_max_air_time : 1;
                        uint8_t fv_avg_air_time : 1;
                        uint8_t fv_min_touchdown_time : 1;
                    } fv_s;
                } fv_s8;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t sport_start_time ;
        uint32_t sport_stop_time ;
        uint32_t sport_total_time ;
        uint32_t sport_total_distance ;
        uint16_t sport_calorie ;
        uint32_t avg_pace ;
        uint32_t fast_pace ;
        uint32_t low_pace ;

        uint32_t total_step ;
        uint16_t avg_stride ;
        uint16_t avg_cadence ;
        uint16_t max_step_rate ;
        uint8_t avg_hr ;
        uint8_t max_hr ;
        uint8_t min_hr ;
        float training_effect ;

        uint8_t aerobic_training_effect ;
        uint8_t max_oxygen_uptake ;
        uint8_t max_oxygen_uptake_rate ;
        uint8_t body_power_use ;
        uint16_t recover_time ;
        uint32_t hr_limit_time ;
        uint32_t hr_without_oxygen ;
        uint32_t hr_with_oxygen ;

        uint32_t hr_expend_fat ;
        uint32_t hr_warmup ;
        uint16_t total_calorie ;
        uint32_t valid_exercise_time ;
        float anaerobic_training_effect ;
        uint8_t anaerobic_training_effect_rate;
        uint16_t subtype ;
        uint8_t designated_courses ;

        uint8_t hr_zone_selection ;
        uint32_t target_duration ;
        uint16_t target_calorie ;
        uint32_t target_distance ;
        uint32_t target_pace ;
        float target_speed ;
        uint16_t target_cadence ;
        uint32_t fixed_distance ;

        uint16_t training_load ;
        uint8_t training_load_rate ;
        float running_power_index ;
        uint8_t running_power_level ;
        uint8_t training_state ;
        uint8_t genki_value ;
        uint32_t full_palm_landing_time ;
        uint32_t forehand_landing_time ;

        uint32_t hell_landing_time ;
        uint8_t inversion_amplitude ;
        uint8_t main_landing_methods;
        uint8_t running_posture_lead ;
        uint8_t running_posture_back;
        uint8_t avg_landing_impact_force ;
        uint8_t max_landing_impact_force ;
        uint16_t avg_touchdown_time ;

        uint16_t min_touchdown_time ;
        uint16_t avg_air_time ;
        uint16_t max_air_time ;
        uint8_t avg_ground_to_air_ratio ;
        uint8_t min_ground_to_air_ratio ;

    } data_s;
} Report_Indoor_Run_Data_Type_V10;
typedef union {
    uint8_t* p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            }ec_opt;
        }ec_opt_s;
        union {
            uint8_t fv_d[9];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_low_pace : 1;
                        uint8_t fv_fast_pace : 1;
                        uint8_t fv_avg_pace : 1;
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_sport_total_distance : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_hr : 1;
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_max_step_rate : 1;
                        uint8_t fv_avg_cadence : 1;
                        uint8_t fv_avg_stride : 1;
                        uint8_t fv_total_step : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_hr_with_oxygen : 1;
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_recover_time : 1;
                        uint8_t fv_body_power_use : 1;
                        uint8_t fv_max_oxygen_uptake_rate : 1;
                        uint8_t fv_max_oxygen_uptake : 1;
                        uint8_t fv_aerobic_training_effect : 1;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_designated_courses : 1;
                        uint8_t fv_subtype : 1;
                        uint8_t fv_anaerobic_training_effect_rate : 1;
                        uint8_t fv_anaerobic_training_effect : 1;
                        uint8_t fv_valid_exercise_time : 1;
                        uint8_t fv_total_calorie : 1;
                        uint8_t fv_hr_warmup : 1;
                        uint8_t fv_hr_expend_fat : 1;
                    } fv_s;
                } fv_s4;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_fixed_distance : 1;
                        uint8_t fv_target_cadence : 1;
                        uint8_t fv_target_speed : 1;
                        uint8_t fv_target_pace : 1;
                        uint8_t fv_target_distance : 1;
                        uint8_t fv_target_calorie : 1;
                        uint8_t fv_target_duration : 1;
                        uint8_t fv_hr_zone_selection : 1;
                    } fv_s;
                } fv_s5;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_forehand_landing_time : 1;
                        uint8_t fv_full_palm_landing_time : 1;
                        uint8_t fv_genki_value : 1;
                        uint8_t fv_training_state : 1;
                        uint8_t fv_running_power_level : 1;
                        uint8_t fv_running_power_index : 1;
                        uint8_t fv_training_load_rate : 1;
                        uint8_t fv_training_load : 1;
                    } fv_s;
                } fv_s6;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_avg_touchdown_time : 1;
                        uint8_t fv_max_landing_impact_force : 1;
                        uint8_t fv_avg_landing_impact_force : 1;
                        uint8_t fv_running_posture_back : 1;
                        uint8_t fv_running_posture_lead : 1;

                        uint8_t main_landing_methods : 1;
                        uint8_t fv_inversion_amplitude : 1;
                        uint8_t fv_hell_landing_time : 1;
                    } fv_s;
                } fv_s7;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 3;
                        uint8_t fv_min_ground_to_air_ratio : 1;
                        uint8_t fv_avg_ground_to_air_ratio : 1;
                        uint8_t fv_max_air_time : 1;
                        uint8_t fv_avg_air_time : 1;
                        uint8_t fv_min_touchdown_time : 1;
                    } fv_s;
                } fv_s8;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint32_t sport_total_distance;
        uint16_t sport_calorie;
        uint32_t avg_pace;
        uint32_t fast_pace;
        uint32_t low_pace;

        uint32_t total_step;
        uint16_t avg_stride;
        uint16_t avg_cadence;
        uint16_t max_step_rate;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float training_effect;

        uint8_t aerobic_training_effect;
        uint8_t max_oxygen_uptake;
        uint8_t max_oxygen_uptake_rate;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;

        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
        uint16_t total_calorie;
        uint32_t valid_exercise_time;
        float anaerobic_training_effect;
        uint8_t anaerobic_training_effect_rate;
        uint16_t subtype;
        uint8_t designated_courses;

        uint8_t hr_zone_selection;
        uint32_t target_duration;
        uint16_t target_calorie;
        uint32_t target_distance;
        uint32_t target_pace;
        float target_speed;
        uint16_t target_cadence;
        uint32_t fixed_distance;

        uint16_t training_load;
        uint8_t training_load_rate;
        float running_power_index;
        uint8_t running_power_level;
        uint8_t training_state;
        uint16_t s5_score;
        uint16_t s10_score;
        uint16_t s21_score;
        uint16_t s42_score;
        uint8_t genki_value;
        uint32_t full_palm_landing_time;
        uint32_t forehand_landing_time;

        uint32_t hell_landing_time;
        uint8_t inversion_amplitude;
        uint8_t main_landing_methods;
        uint8_t running_posture_lead;
        uint8_t running_posture_back;
        uint8_t avg_landing_impact_force;
        uint8_t max_landing_impact_force;
        uint16_t avg_touchdown_time;

        uint16_t min_touchdown_time;
        uint16_t avg_air_time;
        uint16_t max_air_time;
        uint8_t avg_ground_to_air_ratio;
        uint8_t min_ground_to_air_ratio;
        uint8_t train_k;
    } data_s;
} Report_Indoor_Run_Data_Type_V11;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            }ec_opt;
        }ec_opt_s;
        union {
            uint8_t fv_d[11];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_low_speed : 1;
                        uint8_t fv_high_speed : 1;
                        uint8_t fv_avg_speed : 1;
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_sport_total_distance : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_hr : 1;
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_max_step_rate : 1;
                        uint8_t fv_avg_step_rate : 1;
                        uint8_t fv_avg_stride : 1;
                        uint8_t fv_total_step : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_hr_with_oxygen : 1;
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_recover_time : 1;
                        uint8_t fv_body_power_use : 1;
                        uint8_t fv_max_oxygen_uptake_rate : 1;
                        uint8_t fv_max_oxygen_uptake : 1;
                        uint8_t fv_aerobic_training_effect : 1;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_pace_zone_5 : 1;
                        uint8_t fv_hr_zone_1 : 1;
                        uint8_t fv_hr_zone_2 : 1;
                        uint8_t fv_hr_zone_3 : 1;
                        uint8_t fv_hr_zone_4 : 1;
                        uint8_t fv_hr_zone_5 : 1;
                        uint8_t fv_hr_warmup : 1;
                        uint8_t fv_hr_expend_fat : 1;
                    } fv_s;
                } fv_s4;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_anaerobic_training_effect_rate : 1;
                        uint8_t fv_anaerobic_training_effect : 1;
                        uint8_t fv_valid_exercise_time : 1;
                        uint8_t fv_total_calorie : 1;
                        uint8_t fv_pace_zone_1 : 1;
                        uint8_t fv_pace_zone_2 : 1;
                        uint8_t fv_pace_zone_3 : 1;
                        uint8_t fv_pace_zone_4 : 1;
                    } fv_s;
                } fv_s5;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_target_distance : 1;
                        uint8_t fv_target_calorie : 1;
                        uint8_t fv_target_duration : 1;
                        uint8_t fv_hr_zone_selection : 1;
                        uint8_t fv_designated_courses : 1;
                        uint8_t fv_subtype : 1;
                        uint8_t fv_peak_training_effect_rate : 1;
                        uint8_t fv_peak_training_effect : 1;
                    } fv_s;
                } fv_s6;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_running_power_level : 1;
                        uint8_t fv_running_power_index : 1;
                        uint8_t fv_training_load_rate : 1;
                        uint8_t fv_training_load : 1;
                        uint8_t fv_fixed_distance : 1;
                        uint8_t fv_target_cadence : 1;
                        uint8_t fv_target_speed : 1;
                        uint8_t fv_target_pace : 1;
                    } fv_s;
                } fv_s7;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_forehand_landing_time : 1;
                        uint8_t fv_full_palm_landing_time : 1;
                        uint8_t fv_genki_value : 1;
                        uint8_t fv_marathon : 1;
                        uint8_t fv_half_marathon : 1;
                        uint8_t fv_performance_prediction_10km : 1;
                        uint8_t fv_performance_prediction_5km : 1;
                        uint8_t fv_training_state : 1;
                    } fv_s;
                } fv_s8;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_avg_touchdown_time : 1;
                        uint8_t fv_max_impact_force : 1;
                        uint8_t fv_avg_impact_force : 1;
                        uint8_t fv_rear_foot_landing_ratio : 1;
                        uint8_t fv_front_foot_landing_ratio : 1;
                        uint8_t fv_main_landing_methods : 1;
                        uint8_t fv_inversion_amplitude : 1;
                        uint8_t fv_hell_landing_time : 1;
                    } fv_s;
                } fv_s9;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_avg_running_power : 1;
                        uint8_t fv_training_tss : 1;
                        uint8_t fv_training_experience : 1;
                        uint8_t fv_min_ground_to_air_ratio : 1;
                        uint8_t fv_avg_ground_to_air_ratio : 1;
                        uint8_t fv_max_duration_of_passage : 1;
                        uint8_t fv_avg_duration_of_passage : 1;
                        uint8_t fv_min_touchdown_time : 1;
                    } fv_s;
                } fv_s10;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 7;
                        uint8_t fv_max_running_power : 1;
                    } fv_s;
                } fv_s11;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint32_t sport_total_distance;
        uint16_t sport_calorie;
        uint32_t avg_speed;
        uint32_t high_speed;
        uint32_t low_speed;

        uint32_t total_step;
        uint16_t avg_stride;
        uint16_t avg_step_rate;
        uint16_t max_step_rate;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float training_effect;

        uint8_t aerobic_training_effect;
        uint8_t max_oxygen_uptake;
        uint8_t max_oxygen_uptake_rate;
        uint8_t body_power_use;
        uint16_t recover_time; 
        uint32_t hr_limit_time; 
        uint32_t hr_without_oxygen; 
        uint32_t hr_with_oxygen;

        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
        uint8_t hr_zone_5;
        uint8_t hr_zone_4;
        uint8_t hr_zone_3;
        uint8_t hr_zone_2;
        uint8_t hr_zone_1;
        uint32_t pace_zone_5;

        uint32_t pace_zone_4;
        uint32_t pace_zone_3;
        uint32_t pace_zone_2;
        uint32_t pace_zone_1;
        uint16_t total_calorie;
        uint32_t valid_exercise_time;
        float anaerobic_training_effect;
        uint8_t anaerobic_training_effect_rate;

        float peak_training_effect;
        uint8_t peak_training_effect_rate;
        uint16_t subtype;
        uint8_t designated_courses;
         //uint64_t courses_id;
        uint8_t hr_zone_selection;
        uint32_t target_duration;
        uint16_t target_calorie;
        uint32_t target_distance;

        uint32_t target_pace;
        float target_speed;
        uint16_t target_cadence;
        uint32_t fixed_distance;
        uint16_t training_load;
        uint8_t training_load_rate;
        float running_power_index;
        uint8_t running_power_level;

        uint8_t training_state;
        uint16_t performance_prediction_5km;
        uint16_t performance_prediction_10km;
        uint16_t half_marathon;
        uint16_t marathon;
        uint8_t genki_value;
        uint32_t full_palm_landing_time;
        uint32_t forehand_landing_time;

        uint32_t hell_landing_time;
        uint8_t inversion_amplitude;
        uint8_t main_landing_methods;
        uint8_t front_foot_landing_ratio;
        uint8_t rear_foot_landing_ratio;
        uint8_t avg_impact_force;
        uint8_t max_impact_force;
        uint16_t avg_touchdown_time;

        uint16_t min_touchdown_time;
        uint16_t avg_duration_of_passage;
        uint16_t max_duration_of_passage;
        uint8_t avg_ground_to_air_ratio;
        uint8_t min_ground_to_air_ratio;
        uint16_t training_experience;
        uint16_t training_tss;
        uint16_t avg_running_power;
        
        uint16_t max_running_power;
    } data_s;
} Report_Indoor_Run_Data_Type_V12;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            }ec_opt;
        }ec_opt_s;
        union {
            uint32_t fv_d;
            struct {
                uint32_t fv_fast_speed : 1;
                uint32_t fv_low_speed : 1;
                uint32_t fv_high_speed : 1;
                uint32_t fv_sport_calorie : 1;
                uint32_t fv_sport_total_distance : 1;
                uint32_t fv_sport_total_time : 1;
                uint32_t fv_sport_stop_time : 1;
                uint32_t fv_sport_start_time : 1;

                uint32_t fv_min_height : 1;
                uint32_t fv_max_height : 1;
                uint32_t fv_avg_height : 1;
                uint32_t fv_total_down : 1;
                uint32_t fv_total_up : 1;
                uint32_t fv_min_hr : 1;
                uint32_t fv_max_hr : 1;
                uint32_t fv_avg_hr : 1;

                uint32_t fv_hr_expend_fat : 1;
                uint32_t fv_hr_with_oxygen : 1;
                uint32_t fv_hr_without_oxygen : 1;
                uint32_t fv_hr_limit_time : 1;
                uint32_t fv_recover_time : 1;
                uint32_t fv_body_power_use : 1;
                uint32_t fv_max_oxygen_uptake : 1;
                uint32_t fv_training_effect : 1;

                uint32_t : 7;
                uint32_t fv_hr_warmup : 1;
            }fv_s;
        }field_valid;
    }pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint32_t sport_total_distance;
        uint16_t sport_calorie;
        uint32_t high_speed;
        uint32_t low_speed;
        float fast_speed;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float total_up;
        float total_down;
        float avg_height;
        float max_height;
        float min_height;
        float training_effect;
        uint8_t max_oxygen_uptake;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
    }data_s;
} Report_Outside_Cycle_Data_Type_V1;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            }ec_opt;
        }ec_opt_s;
        union {
            uint8_t fv_d[5];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_fast_speed : 1;
                        uint8_t fv_low_speed : 1;
                        uint8_t fv_high_speed : 1;
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_sport_total_distance : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_min_height : 1;
                        uint8_t fv_max_height : 1;
                        uint8_t fv_avg_height : 1;
                        uint8_t fv_total_down : 1;
                        uint8_t fv_total_up : 1;
                        uint8_t fv_min_hr : 1;
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_hr_expend_fat : 1;
                        uint8_t fv_hr_with_oxygen : 1;
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_recover_time : 1;
                        uint8_t fv_body_power_use : 1;
                        uint8_t fv_max_oxygen_uptake : 1;
                        uint8_t fv_training_effect : 1;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_target_calorie : 1;
                        uint8_t fv_target_duration : 1;
                        uint8_t fv_hr_zone_selection : 1;
                        uint8_t fv_designated_courses : 1;
                        uint8_t fv_anaerobic_training_effect : 1;
                        uint8_t fv_valid_exercise_time: 1;
                        uint8_t fv_total_calorie : 1;
                        uint8_t fv_hr_warmup : 1;
                    } fv_s;
                } fv_s4;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 6;
                        uint8_t fv_target_pace : 1;
                        uint8_t fv_target_distance : 1;
                    } fv_s;
                } fv_s5;
            } fv_s;
        } field_valid;
    }pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint32_t sport_total_distance;
        uint16_t sport_calorie;
        uint32_t high_speed;
        uint32_t low_speed;
        float fast_speed;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float total_up;
        float total_down;
        float avg_height;
        float max_height;
        float min_height;
        float training_effect;
        uint8_t max_oxygen_uptake;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
        uint16_t total_calorie;
        uint32_t valid_exercise_time;
        uint32_t anaerobic_training_effect;
        uint8_t  designated_courses;
//        uint64_t courses_id;
        uint8_t hr_zone_selection;
        uint32_t target_duration;
        uint16_t target_calorie;
        uint32_t target_distance;
        uint32_t target_pace;
    }data_s;
} Report_Outside_Cycle_Data_Type_V4;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            }ec_opt;
        }ec_opt_s;
        union {
            uint8_t fv_d[6];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_total_calorie : 1;
                        uint8_t fv_sport_total_distance : 1;
                        uint8_t fv_valid_exercise_time : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                        uint8_t fv_non_running_style_sub_sport_type : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_total_down : 1;
                        uint8_t fv_total_up : 1;
                        uint8_t fv_min_hr : 1;
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_fast_speed : 1;
                        uint8_t fv_low_speed : 1;
                        uint8_t fv_high_speed : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_max_oxygen_uptake : 1;
                        uint8_t fv_anaerobic_training_effect_rate : 1;
                        uint8_t fv_anaerobic_training_effect : 1;
                        uint8_t fv_training_effect_rating : 1;
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_height : 1;
                        uint8_t fv_max_height : 1;
                        uint8_t fv_avg_height : 1;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_hr_expend_fat : 1;
                        uint8_t fv_hr_with_oxygen : 1;
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_hr_zone_selection : 1;
                        uint8_t fv_recover_time : 1;
                        uint8_t fv_body_power_use : 1;
                        uint8_t fv_max_oxygen_uptake_rate : 1;
                    } fv_s;
                } fv_s4;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_training_load_rate : 1;
                        uint8_t fv_training_load : 1;
                        uint8_t fv_designated_courses : 1;
                        uint8_t fv_target_speed : 1;
                        uint8_t fv_target_distance : 1;
                        uint8_t fv_target_calorie : 1;
                        uint8_t fv_target_duration : 1;                
                        uint8_t fv_hr_warmup : 1;
                    } fv_s;
                } fv_s5;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t  : 2;
                        uint8_t fv_max_cadence : 1;
                        uint8_t fv_avg_cadence : 1;
                        uint8_t fv_genki_value : 1;
                        uint8_t fv_train_state : 1;
                        uint8_t fv_running_power_level : 1;                
                        uint8_t fv_running_power_index : 1;
                    } fv_s;
                } fv_s6;
            } fv_s;
        } field_valid;
    }pack_head;
    struct {
        uint16_t non_running_style_sub_sport_type;
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint32_t valid_exercise_time;
        uint32_t sport_total_distance;
        uint16_t total_calorie;
        uint16_t sport_calorie;

        uint32_t high_speed;
        uint32_t low_speed;
        float fast_speed;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float total_up;
        float total_down;

        float avg_height;
        float max_height;
        float min_height;
        float training_effect;
        uint8_t training_effect_rating;
        float anaerobic_training_effect;
        uint8_t anaerobic_training_effect_rate;
        uint8_t max_oxygen_uptake;

        uint8_t max_oxygen_uptake_rate;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint8_t hr_zone_selection;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;

        uint32_t hr_warmup;
        uint32_t target_duration; 
        uint16_t target_calorie;  
        uint32_t target_distance;
        uint32_t target_speed;
        uint8_t designated_courses;
        //        uint64_t courses_id;
        uint16_t training_load;
        uint8_t training_load_rate;

        float running_power_index;
        uint8_t running_power_level;  
        uint8_t train_state;
        uint8_t genki_value;
        uint16_t avg_cadence;
        uint16_t max_cadence;
    }data_s;
} Report_Outside_Non_Running_Data_Type_V4;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint16_t fv_d;
            struct {
                uint16_t fv_training_effect : 1;
                uint16_t fv_min_hr : 1;
                uint16_t fv_max_hr : 1;
                uint16_t fv_avg_hr : 1;
                uint16_t fv_sport_calorie : 1;
                uint16_t fv_sport_total_time : 1;
                uint16_t fv_sport_stop_time : 1;
                uint16_t fv_sport_start_time : 1;

                uint16_t : 1;
                uint16_t fv_hr_warmup : 1;
                uint16_t fv_hr_expend_fat : 1;
                uint16_t fv_hr_with_oxygen : 1;
                uint16_t fv_hr_without_oxygen : 1;
                uint16_t fv_hr_limit_time : 1;
                uint16_t fv_recover_time : 1;
                uint16_t fv_body_power_use : 1;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint16_t sport_calorie;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float training_effect;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
    } data_s;
} Repofree_Sport_Data_Type_V1;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[3];
            struct
            {
                uint16_t fv_training_effect : 1;
                uint16_t fv_min_hr : 1;
                uint16_t fv_max_hr : 1;
                uint16_t fv_avg_hr : 1;
                uint16_t fv_sport_calorie : 1;
                uint16_t fv_sport_total_time : 1;
                uint16_t fv_sport_stop_time : 1;
                uint16_t fv_sport_start_time : 1;
                uint16_t fv_total_calorie : 1;
                uint16_t fv_hr_warmup : 1;
                uint16_t fv_hr_expend_fat : 1;
                uint16_t fv_hr_with_oxygen : 1;
                uint16_t fv_hr_without_oxygen : 1;
                uint16_t fv_hr_limit_time : 1;
                uint16_t fv_recover_time : 1;
                uint16_t fv_body_power_use : 1;
                uint16_t : 5;
                uint16_t fv_free_style_sub_sport_type : 1;
                uint16_t fv_without_oxygen_training_time : 1;
                uint16_t fv_valid_exercise_time : 1;
            } fv_s;
        } field_valid;
    } pack_head;

    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint16_t sport_calorie;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float training_effect;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
        uint16_t total_calorie;
        uint32_t valid_exercise_time;
        uint32_t without_oxygen_training_time;
        uint16_t free_style_sub_sport_type;
    } data_s;
} Repofree_Sport_Data_Type_V4;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[3];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_hr : 1;
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_total_calorie : 1;
                        uint8_t fv_hr_warmup : 1;
                        uint8_t fv_hr_expend_fat : 1;
                        uint8_t fv_hr_with_oxygen : 1;
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_recover_time : 1;
                        uint8_t fv_body_power_use : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 1;
                        uint8_t fv_target_calorie : 1;
                        uint8_t fv_target_duration : 1;
                        uint8_t fv_hr_zone_selection : 1;
                        uint8_t fv_designated_courses : 1;
                        uint16_t fv_free_style_sub_sport_type : 1;
                        uint16_t fv_without_oxygen_training_time : 1;
                        uint16_t fv_valid_exercise_time : 1;
                    } fv_s;
                } fv_s3;
            } fv_s;
        } field_valid;
    } pack_head;

    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint16_t sport_calorie;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float training_effect;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
        uint16_t total_calorie;
        uint32_t valid_exercise_time;
        uint32_t without_oxygen_training_time;
        uint16_t free_style_sub_sport_type;
        uint8_t  designated_courses;
//        uint64_t courses_id;
        uint8_t hr_zone_selection;
        uint32_t target_duration;
        uint16_t target_calorie;
    } data_s;
} Repofree_Sport_Data_Type_V5;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[6];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_avg_spo2 : 1;
                        uint8_t fv_min_hr : 1;
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_body_power_use : 1;
                        uint8_t fv_training_effect_rating : 1;
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_stress : 1;
                        uint8_t fv_max_stress : 1;
                        uint8_t fv_avg_stress : 1;
                        uint8_t fv_min_spo2 : 1;
                        uint8_t fv_max_spo2 : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint16_t fv_valid_exercise_time : 1;
                        uint8_t fv_total_calorie : 1;
                        uint8_t fv_hr_warmup : 1;
                        uint8_t fv_hr_expend_fat : 1;
                        uint8_t fv_hr_with_oxygen : 1;
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_recover_time : 1;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_training_load : 1;
                        uint8_t fv_target_calorie : 1;
                        uint8_t fv_target_duration : 1;
                        uint8_t fv_hr_zone_selection : 1;
                        uint8_t fv_designated_courses : 1;
                        uint16_t fv_free_style_sub_sport_type : 1;
                        uint16_t fv_without_oxygen_training_time_rate : 1;
                        uint16_t fv_without_oxygen_training_time : 1;
                    } fv_s;
                } fv_s4;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_max_double_hit : 1;
                        uint8_t fv_max_punching_force : 1;
                        uint8_t fv_total_miss_count : 1;
                        uint8_t fv_total_good_count : 1;
                        uint8_t fv_total_perfect_count : 1;
                        uint8_t fv_total_punching_count : 1;
                        uint8_t fv_genki_value : 1;
                        uint8_t fv_training_load_rate : 1;
                    } fv_s;
                } fv_s5;
                union {
                    uint8_t fv_d;
                    struct {

                        uint8_t  : 7;
                        uint8_t fv_hit_rate : 1;
                    } fv_s;
                } fv_s6;
            } fv_s;
        } field_valid;
    } pack_head;

    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint16_t sport_calorie;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        uint8_t avg_spo2;

        uint8_t max_spo2;
        uint8_t min_spo2;
        uint8_t avg_stress;
        uint8_t max_stress;
        uint8_t min_stress;
        float training_effect;
        uint8_t training_effect_rating;
        uint8_t body_power_use;

        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
        uint16_t total_calorie;
        uint32_t valid_exercise_time;

        uint32_t without_oxygen_training_time;
        uint8_t without_oxygen_training_time_rate;
        uint16_t free_style_sub_sport_type;
        uint8_t  designated_courses;
//        uint64_t courses_id;
        uint8_t hr_zone_selection;
        uint32_t target_duration;
        uint16_t target_calorie;
        uint16_t training_load;

        uint8_t training_load_rate;
        uint8_t genki_value;
        uint16_t total_punching_count;
        uint16_t total_perfect_count;
        uint16_t total_good_count;
        uint16_t total_miss_count;
        float max_punching_force;
        uint16_t max_double_hit;

        uint8_t hit_rate;
    } data_s;
} Repofree_Sport_Data_Type_V8;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            }ec_opt;
        } ec_opt_s;
        union {
            uint16_t fv_d;
            struct {
                uint16_t fv_body_power_use : 1;
                uint16_t fv_low_speed : 1;
                uint16_t fv_high_speed : 1;
                uint16_t fv_sport_calorie : 1;
                uint16_t fv_sport_total_distance : 1;
                uint16_t fv_sport_total_time : 1;
                uint16_t fv_sport_stop_time : 1;
                uint16_t fv_sport_start_time : 1;

                uint16_t fv_pool_width : 1;
                uint16_t fv_best_swolf : 1;
                uint16_t fv_avg_swolf : 1;
                uint16_t fv_turn_count : 1;
                uint16_t fv_pull_rate : 1;
                uint16_t fv_posture : 1;
                uint16_t fv_arm_pull_count : 1;
                uint16_t fv_recover_time : 1;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint32_t sport_total_distance;
        uint16_t sport_calorie;
        uint32_t high_speed;
        uint32_t low_speed;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint16_t arm_pull_count;
        Swimming_Posture_Type posture;
        uint8_t pull_rate;
        uint16_t turn_count;
        uint16_t avg_swolf;
        uint16_t best_swolf;
        uint8_t pool_width;
    } data_s;
} Report_Swimming_Data_Type_V1;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            }ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[4];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_body_power_use : 1;
                        uint8_t fv_low_speed : 1;
                        uint8_t fv_high_speed : 1;
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_sport_total_distance : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_pool_width : 1;
                        uint8_t fv_best_swolf : 1;
                        uint8_t fv_avg_swolf : 1;
                        uint8_t fv_turn_count : 1;
                        uint8_t fv_pull_rate : 1;
                        uint8_t fv_posture : 1;
                        uint8_t fv_arm_pull_count : 1;
                        uint8_t fv_recover_time : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_target_times : 1;
                        uint8_t fv_target_pace : 1;
                        uint8_t fv_target_distance : 1;
                        uint8_t fv_target_calorie : 1;
                        uint8_t fv_target_duration : 1;
                        uint8_t fv_valid_exercise_time : 1;
                        uint8_t fv_total_calorie : 1;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 2;
                        uint8_t fv_genki_value : 1;
                        uint8_t fv_training_load_rate : 1;
                        uint8_t fv_training_load : 1;
                        uint8_t fv_anaerobic_training_effect_rate : 1;
                        uint8_t fv_anaerobic_training_effect : 1;
                        uint8_t fv_training_effect_rate : 1;
                    } fv_s;
                } fv_s4;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint32_t sport_total_distance;
        uint16_t sport_calorie;
        uint32_t high_speed;
        uint32_t low_speed;
        uint8_t body_power_use;

        uint16_t recover_time;
        uint16_t arm_pull_count;
        Swimming_Posture_Type posture;
        uint8_t pull_rate;
        uint16_t turn_count;
        uint16_t avg_swolf;
        uint16_t best_swolf;
        uint8_t pool_width;

        uint16_t total_calorie;
        uint32_t valid_exercise_time;
        uint32_t target_time;
        uint16_t target_calorie;
        uint32_t target_distance;
        uint32_t target_pace;
        uint16_t target_times;
        uint32_t training_effect;

        uint8_t training_effect_rate;
        uint32_t anaerobic_training_effect;  
        uint8_t anaerobic_training_effect_rate;
        uint16_t training_load;
        uint8_t training_load_rate;
        uint8_t genki_value;
    } data_s;
} Report_Swimming_Data_Type_V6;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[3];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_max_step_rate : 1;
                        uint8_t fv_total_step : 1;
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_hr_expend_fat : 1;
                        uint8_t fv_hr_with_oxygen : 1;
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_recover_time : 1;   
                        uint8_t fv_body_power_use : 1;
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_hr : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 6;
                        uint8_t fv_total_calorie : 1;
                        uint8_t fv_hr_warmup : 1;
                    } fv_s;
                } fv_s3;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint16_t sport_calorie;
        uint32_t total_step;
        uint16_t max_step_rate;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float training_effect;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
        uint16_t total_calorie;
    } data_s;
} Report_Elliptical_Machine_Data_Type_V1;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[4];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_max_step_rate : 1;
                        uint8_t fv_total_step : 1;
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_hr_expend_fat : 1;
                        uint8_t fv_hr_with_oxygen : 1;
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_recover_time : 1;   
                        uint8_t fv_body_power_use : 1;
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_hr : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_target_calorie : 1;
                        uint8_t fv_target_duration : 1;
                        uint8_t fv_hr_zone_selection : 1;
                        uint8_t fv_designated_courses : 1;
                        uint8_t fv_anaerobic_training_effect : 1;
                        uint8_t fv_valid_exercise_time : 1;
                        uint8_t fv_total_calorie : 1;
                        uint8_t fv_hr_warmup : 1;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 7;
                        uint8_t target_cadence : 1;
                    } fv_s;
                } fv_s4;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint16_t sport_calorie;
        uint32_t total_step;
        uint16_t max_step_rate;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float training_effect;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
        uint16_t total_calorie;
        uint32_t valid_exercise_time;
        uint32_t anaerobic_training_effect;
        uint8_t  designated_courses;
//        uint64_t courses_id;
        uint8_t hr_zone_selection;
        uint32_t target_duration;
        uint16_t target_calorie;
        uint16_t target_cadence;
    } data_s;
} Report_Elliptical_Machine_Data_Type_V3;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[4];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_max_step_rate : 1;
                        uint8_t fv_total_step : 1;
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_hr_with_oxygen : 1;
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_recover_time : 1;   
                        uint8_t fv_body_power_use : 1;
                        uint8_t fv_training_effect_rate : 1;
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_hr : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_hr_zone_selection : 1;
                        uint8_t fv_designated_courses : 1;
                        uint8_t fv_anaerobic_training_effect_rate : 1;
                        uint8_t fv_anaerobic_training_effect : 1;
                        uint8_t fv_valid_exercise_time : 1;
                        uint8_t fv_total_calorie : 1;
                        uint8_t fv_hr_warmup : 1;
                        uint8_t fv_hr_expend_fat : 1;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 2;
                        uint8_t fv_genki_value : 1;
                        uint8_t training_load_rate : 1;
                        uint8_t training_load : 1;
                        uint8_t target_cadence : 1;
                        uint8_t fv_target_calorie : 1;
                        uint8_t fv_target_duration : 1;
                    } fv_s;
                } fv_s4;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint16_t sport_calorie;
        uint32_t total_step;
        uint16_t max_step_rate;
        uint8_t avg_hr;
        uint8_t max_hr;

        uint8_t min_hr;
        float training_effect;
        uint8_t training_effect_rate;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;

        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
        uint16_t total_calorie;
        uint32_t valid_exercise_time;
        uint32_t anaerobic_training_effect;
        uint8_t anaerobic_training_effect_rate;
        uint8_t  designated_courses;
//        uint64_t courses_id;
        uint8_t hr_zone_selection;

        uint32_t target_duration;
        uint16_t target_calorie;
        uint16_t target_cadence;
        uint16_t tarining_load;
        uint8_t traing_load_rate;
        uint8_t genki_value;
    } data_s;
} Report_Elliptical_Machine_Data_Type_V5;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            }ec_opt;
        }ec_opt_s;
        union {
            uint32_t fv_d;
            struct {
                uint32_t fv_training_effect : 1;
                uint32_t fv_min_hr : 1;
                uint32_t fv_max_hr : 1;
                uint32_t fv_avg_hr : 1;
                uint32_t fv_sport_calorie : 1;
                uint32_t fv_sport_total_time : 1;
                uint32_t fv_sport_stop_time : 1;
                uint32_t fv_sport_start_time : 1;

                uint32_t fv_hr_warmup : 1;
                uint32_t fv_hr_expend_fat : 1;
                uint32_t fv_hr_with_oxygen : 1;
                uint32_t fv_hr_without_oxygen : 1;
                uint32_t fv_hr_limit_time : 1;
                uint32_t fv_recover_time : 1;
                uint32_t fv_body_power_use : 1;

                uint32_t fv_min_takeoff_height : 1;
                uint32_t fv_max_takeoff_height : 1;
                uint32_t fv_avg_takeoff_height : 1;
                uint32_t fv_total_rest_time : 1;
                uint32_t fv_best_jump_freq : 1;
                uint32_t fv_avg_jump_freq : 1;
                uint32_t fv_total_jumps : 1;
                uint32_t fv_total_calorie : 1;
                
                uint32_t : 5;
                uint32_t fv_group_cnt : 1;
                uint32_t fv_acting : 1;
                uint32_t fv_airborne_time : 1;
            }fv_s;
        }field_valid;
    }pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint16_t sport_calorie;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float training_effect;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
        uint16_t total_calorie;
        uint32_t total_jumps;
        uint32_t avg_jump_freq;
        uint32_t best_jump_freq;
        uint32_t total_rest_time;
        uint32_t avg_takeoff_height;
        uint32_t max_takeoff_height;
        uint32_t min_takeoff_height;
        uint32_t airborne_time;
        uint32_t acting;
        uint8_t  group_cnts;
    }data_s;
} Report_Rope_Skipping_Data_Type_V1;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            }ec_opt;
        }ec_opt_s;
        union {
            uint8_t fv_d[4];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_hr : 1;
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_hr_warmup : 1;
                        uint8_t fv_hr_expend_fat : 1;
                        uint8_t fv_hr_with_oxygen : 1;
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_recover_time : 1;
                        uint8_t fv_body_power_use : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_min_takeoff_height : 1;
                        uint8_t fv_max_takeoff_height : 1;
                        uint8_t fv_avg_takeoff_height : 1;
                        uint8_t fv_total_rest_time : 1;
                        uint8_t fv_best_jump_freq : 1;
                        uint8_t fv_avg_jump_freq : 1;
                        uint8_t fv_total_jumps : 1;
                        uint8_t fv_total_calorie : 1;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_target_duration : 1;
                        uint8_t fv_hr_zone_selection : 1;
                        uint8_t fv_designated_courses : 1;
                        uint8_t fv_anaerobic_training_effect : 1;
                        uint8_t fv_valid_exercise_time : 1;
                        uint32_t fv_group_cnt : 1;
                        uint32_t fv_acting : 1;
                        uint32_t fv_airborne_time : 1;
                    } fv_s;
                } fv_s4;
                union {
                    uint8_t fv_d;
                    struct {
                        uint32_t : 5;
                        uint8_t fv_total_stumbles : 1;
                        uint8_t fv_target_times : 1;
                        uint8_t fv_target_calorie : 1;
                    } fv_s;
                } fv_s5;
            } fv_s;
        } field_valid;
    }pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint16_t sport_calorie;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float training_effect;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
        uint16_t total_calorie;
        uint32_t total_jumps;
        uint32_t avg_jump_freq;
        uint32_t best_jump_freq;
        uint32_t total_rest_time;
        uint32_t avg_takeoff_height;
        uint32_t max_takeoff_height;
        uint32_t min_takeoff_height;
        uint32_t airborne_time;
        uint32_t acting;
        uint8_t  group_cnts;
        uint32_t valid_exercise_time;
        uint32_t anaerobic_training_effect;
        uint8_t  designated_courses;
//        uint64_t courses_id;
        uint8_t hr_zone_selection;
        uint32_t target_duration;
        uint16_t target_calorie;
        uint16_t target_times;
        uint16_t total_stumbles;
    }data_s;
} Report_Rope_Skipping_Data_Type_V3;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            }ec_opt;
        }ec_opt_s;
        union {
            uint8_t fv_d[4];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_hr : 1;
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_hr_warmup : 1;
                        uint8_t fv_hr_expend_fat : 1;
                        uint8_t fv_hr_with_oxygen : 1;
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_recover_time : 1;
                        uint8_t fv_body_power_use : 1;
                        uint8_t fv_training_effect_rate : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_min_takeoff_height : 1;
                        uint8_t fv_max_takeoff_height : 1;
                        uint8_t fv_avg_takeoff_height : 1;
                        uint8_t fv_total_rest_time : 1;
                        uint8_t fv_best_jump_freq : 1;
                        uint8_t fv_avg_jump_freq : 1;
                        uint8_t fv_total_jumps : 1;
                        uint8_t fv_total_calorie : 1;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_hr_zone_selection : 1;
                        uint8_t fv_designated_courses : 1;
                        uint8_t fv_anaerobic_training_effect_rate : 1;
                        uint8_t fv_anaerobic_training_effect : 1;
                        uint8_t fv_valid_exercise_time : 1;
                        uint8_t fv_group_cnt : 1;
                        uint8_t fv_acting : 1;
                        uint8_t fv_airborne_time : 1;
                    } fv_s;
                } fv_s4;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 1;
                        uint8_t fv_genki_value : 1;
                        uint8_t fv_training_load_rate : 1;
                        uint8_t fv_training_load : 1;
                        uint8_t fv_total_stumbles : 1;
                        uint8_t fv_target_times : 1;
                        uint8_t fv_target_calorie : 1;
                        uint8_t fv_target_duration : 1;
                    } fv_s;
                } fv_s5;
            } fv_s;
        } field_valid;
    }pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint16_t sport_calorie;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float training_effect;

        uint8_t training_effect_rate;        
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;

        uint16_t total_calorie;
        uint32_t total_jumps;
        uint32_t avg_jump_freq;
        uint32_t best_jump_freq;
        uint32_t total_rest_time;
        uint32_t avg_takeoff_height;
        uint32_t max_takeoff_height;
        uint32_t min_takeoff_height;

        uint32_t airborne_time;
        uint32_t acting;
        uint8_t  group_cnts;
        uint32_t valid_exercise_time;
        uint32_t anaerobic_training_effect;
        uint8_t anaerobic_training_effect_rate;
        uint8_t  designated_courses;
//        uint64_t courses_id;
        uint8_t hr_zone_selection;

        uint32_t target_duration;
        uint16_t target_calorie;
        uint16_t target_times;
        uint16_t total_stumbles;
        uint16_t training_load;
        uint8_t training_load_rate;
        uint8_t genki_value;
    }data_s;
} Report_Rope_Skipping_Data_Type_V5;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[3];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_hr : 1;
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_total_calorie : 1;
                        uint8_t fv_hr_warmup : 1;
                        uint8_t fv_hr_expend_fat : 1;
                        uint8_t fv_hr_with_oxygen : 1;
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_recover_time : 1;   
                        uint8_t fv_body_power_use : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 1;
                        uint8_t fv_group_cnt : 1;
                        uint8_t fv_total_rest_time : 1;
                        uint8_t put_time : 1;
                        uint8_t drive_time : 1;
                        uint8_t best_stroke_freq : 1;
                        uint8_t fv_stroke_freq : 1;
                        uint8_t fv_total_strokes : 1;
                    } fv_s;
                } fv_s3;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint16_t sport_calorie;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float training_effect;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
        uint16_t total_calorie;
        uint32_t total_strokes;
        uint32_t avg_stroke_freq;
        uint32_t best_stroke_freq;
        uint32_t drive_time;
        uint32_t put_time;
        uint32_t total_rest_time;
        uint8_t  group_cnts;
    }data_s;
} Report_Rowing_Machine_Data_Type_V1;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[4];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_hr : 1;
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_total_calorie : 1;
                        uint8_t fv_hr_warmup : 1;
                        uint8_t fv_hr_expend_fat : 1;
                        uint8_t fv_hr_with_oxygen : 1;
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_recover_time : 1;   
                        uint8_t fv_body_power_use : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_valid_exercise_time: 1;
                        uint8_t fv_group_cnt : 1;
                        uint8_t fv_total_rest_time : 1;
                        uint8_t put_time : 1;
                        uint8_t drive_time : 1;
                        uint8_t best_stroke_freq : 1;
                        uint8_t fv_stroke_freq : 1;
                        uint8_t fv_total_strokes : 1;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 2;
                        uint8_t fv_target_times : 1;
                        uint8_t fv_target_calorie : 1;
                        uint8_t fv_target_duration : 1;
                        uint8_t fv_hr_zone_selection : 1;
                        uint8_t fv_designated_courses : 1;
                        uint8_t fv_anaerobic_training_effect : 1;
                    } fv_s;
                } fv_s4;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint16_t sport_calorie;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float training_effect;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
        uint16_t total_calorie;
        uint32_t total_strokes;
        uint32_t avg_stroke_freq;
        uint32_t best_stroke_freq;
        uint32_t drive_time;
        uint32_t put_time;
        uint32_t total_rest_time;
        uint8_t  group_cnts;

        uint32_t valid_exercise_time;
        uint32_t anaerobic_training_effect;
        uint8_t  designated_courses;
//        uint64_t courses_id;
        uint8_t hr_zone_selection;
        uint32_t target_duration;
        uint16_t target_calorie;
        uint16_t target_times;
    }data_s;
} Report_Rowing_Machine_Data_Type_V4;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[5];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_hr : 1;
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_hr_warmup : 1;
                        uint8_t fv_hr_expend_fat : 1;
                        uint8_t fv_hr_with_oxygen : 1;
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_recover_time : 1;   
                        uint8_t fv_body_power_use : 1;
                        uint8_t fv_training_effect_rate : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_group_cnt : 1;
                        uint8_t fv_total_rest_time : 1;
                        uint8_t put_time : 1;
                        uint8_t drive_time : 1;
                        uint8_t best_stroke_freq : 1;
                        uint8_t fv_stroke_freq : 1;
                        uint8_t fv_total_strokes : 1;
                        uint8_t fv_total_calorie : 1;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_target_times : 1;
                        uint8_t fv_target_calorie : 1;
                        uint8_t fv_target_duration : 1;
                        uint8_t fv_hr_zone_selection : 1;
                        uint8_t fv_designated_courses : 1;
                        uint8_t fv_anaerobic_training_effect_rate : 1;
                        uint8_t fv_anaerobic_training_effect : 1;
                        uint8_t fv_valid_exercise_time: 1;
                    } fv_s;
                } fv_s4;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t  : 5;
                        uint8_t fv_genki_value : 1;
                        uint8_t fv_training_load_rate : 1;
                        uint8_t fv_training_load: 1;
                    } fv_s;
                } fv_s5;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint16_t sport_calorie;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float training_effect;

        uint8_t training_effect_rate;       
        uint8_t body_power_use;
        uint16_t recover_time;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;

        uint16_t total_calorie;
        uint32_t total_strokes;
        uint32_t avg_stroke_freq;
        uint32_t best_stroke_freq;
        uint32_t drive_time;
        uint32_t put_time;
        uint32_t total_rest_time;
        uint8_t  group_cnts;

        uint32_t valid_exercise_time;
        uint32_t anaerobic_training_effect;
        uint8_t anaerobic_training_effect_rate;
        uint8_t  designated_courses;
//        uint64_t courses_id;
        uint8_t hr_zone_selection;
        uint32_t target_duration;
        uint16_t target_calorie;
        uint16_t target_times;

        uint16_t training_load;
        uint8_t training_load_rate;
        uint8_t genki_value;
    }data_s;
} Report_Rowing_Machine_Data_Type_V6;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[7];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_total_calorie : 1;
                        uint8_t fv_sport_total_distance : 1;
                        uint8_t fv_valid_exercise_time : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                        uint8_t fv_sub_sport_type : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_min_hr : 1;
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_max_step_rate : 1;
                        uint8_t fv_total_step : 1;
                        uint8_t fv_fast_speed : 1;
                        uint8_t fv_low_speed : 1;
                        uint8_t fv_high_speed : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_anaerobic_training_effect : 1;
                        uint8_t fv_training_effect_rating : 1;
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_height : 1;
                        uint8_t fv_max_height : 1;
                        uint8_t fv_avg_height : 1;
                        uint8_t fv_total_down : 1;
                        uint8_t fv_total_up : 1;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_hr_zone_selection : 1;
                        uint8_t fv_recover_time : 1;
                        uint8_t fv_body_power_use : 1;
                        uint8_t fv_max_oxygen_uptake_rating : 1;
                        uint8_t fv_max_oxygen_uptake : 1;
                        uint8_t fv_anaerobic_training_effect_rating : 1;
                    } fv_s;
                } fv_s4;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_target_speed : 1;
                        uint8_t fv_target_pace : 1;
                        uint8_t fv_target_distance : 1;
                        uint8_t fv_target_calorie : 1;
                        uint8_t fv_target_duration : 1;
                        uint8_t fv_hr_warmup : 1;
                        uint8_t fv_hr_expend_fat : 1;
                        uint8_t fv_hr_with_oxygen : 1;
                    } fv_s;
                } fv_s5;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_training_status : 1;
                        uint8_t fv_running_power_level : 1;
                        uint8_t fv_running_power_index : 1;
                        uint8_t fv_training_load_rating : 1;
                        uint8_t fv_training_load : 1;
                        uint8_t : 1;
                        uint8_t fv_designated_courses : 1;
                        uint8_t fv_target_cadence : 1;
                    } fv_s;
                } fv_s6;

                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t  : 3;
                        uint8_t fv_inversion_amplitude : 1;
                        uint8_t fv_hell_landing_time : 1;
                        uint8_t fv_forehand_landing_time : 1;
                        uint8_t fv_full_palm_landing_time : 1;
                        uint8_t fv_genki_value : 1;
                    } fv_s;
                } fv_s7;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint16_t sub_sport_type;
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint32_t valid_exercise_time;
        uint32_t sport_total_distance;
        uint16_t total_calorie;
        uint16_t sport_calorie;
        uint32_t high_speed;
        uint32_t low_speed;
        float fast_speed;
        uint32_t total_step;
        uint16_t max_step_rate;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float total_up;
        float total_down;
        float avg_height;
        float max_height;
        float min_height;
        float training_effect;
        uint8_t training_effect_rating;
        float anaerobic_training_effect;

        uint8_t anaerobic_training_effect_rating;
        uint8_t max_oxygen_uptake;
        uint8_t max_oxygen_uptake_rating;
        uint8_t body_power_use;
        uint16_t recover_time;
        uint8_t hr_zone_selection;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;

        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
        uint32_t target_duration;
        uint16_t target_calorie;
        uint32_t target_distance;
        uint32_t target_pace;
        float target_speed;

        uint16_t target_cadence;
        uint8_t  designated_courses;
        //uint64_t courses_id;
        uint16_t training_load;
        uint8_t  training_load_rating;
        uint32_t running_power_index;
        uint8_t running_power_level;
        uint8_t training_status;

        uint8_t genki_value;
        uint32_t full_palm_landing_time;
        uint32_t forehand_landing_time;
        uint32_t hell_landing_time;
        uint8_t inversion_amplitude;
    } data_s;
} Report_Outside_Run_Category_Data_Type_V4;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d[9];
            struct {
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_sport_calorie : 1;
                        uint8_t fv_total_calorie : 1;
                        uint8_t fv_sport_total_distance : 1;
                        uint8_t fv_valid_exercise_time : 1;
                        uint8_t fv_sport_total_time : 1;
                        uint8_t fv_sport_stop_time : 1;
                        uint8_t fv_sport_start_time : 1;
                        uint8_t fv_sub_sport_type : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_avg_cadence : 1;
                        uint8_t fv_avg_stride : 1;
                        uint8_t fv_total_steps : 1;
                        uint8_t fv_max_speed : 1;
                        uint8_t fv_avg_speed : 1;
                        uint8_t fv_low_pace : 1;
                        uint8_t fv_max_pace : 1;
                        uint8_t fv_avg_pace : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_max_hight : 1;
                        uint8_t fv_avg_hight : 1;
                        uint8_t fv_total_down : 1;
                        uint8_t fv_total_up : 1;
                        uint8_t fv_min_hr : 1;
                        uint8_t fv_max_hr : 1;
                        uint8_t fv_avg_hr : 1;
                        uint8_t fv_max_cadence : 1;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_body_power_use : 1;
                        uint8_t fv_max_oxygen_uptake_rating : 1;
                        uint8_t fv_max_oxygen_uptake : 1;
                        uint8_t fv_anaerobic_training_effect_rating : 1;
                        uint8_t fv_anaerobic_training_effect : 1;
                        uint8_t fv_training_effect_rating : 1;
                        uint8_t fv_training_effect : 1;
                        uint8_t fv_min_hight : 1;
                    } fv_s;
                } fv_s4;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_target_duration : 1;
                        uint8_t fv_hr_warmup : 1;
                        uint8_t fv_hr_expend_fat : 1;
                        uint8_t fv_hr_with_oxygen : 1;
                        uint8_t fv_hr_without_oxygen : 1;
                        uint8_t fv_hr_limit_time : 1;
                        uint8_t fv_hr_zone_selection : 1;
                        uint8_t fv_recover_time : 1;

                    } fv_s;
                } fv_s5;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_training_load_rating : 1;
                        uint8_t fv_training_load : 1;
                        uint8_t fv_designated_courses : 1;
                        uint8_t fv_target_cadence : 1;
                        uint8_t fv_target_speed : 1;
                        uint8_t fv_target_pace : 1;
                        uint8_t fv_target_distance : 1;
                        uint8_t fv_target_calorie : 1;
                    } fv_s;
                } fv_s6;

                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_inversion_amplitude : 1;
                        uint8_t fv_hell_landing_time : 1;
                        uint8_t fv_forehand_landing_time : 1;
                        uint8_t fv_full_palm_landing_time : 1;
                        uint8_t fv_genki_value : 1;
                        uint8_t fv_training_status : 1;
                        uint8_t fv_running_power_level : 1;
                        uint8_t fv_running_power_index : 1;
                    } fv_s;
                } fv_s7;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t  : 8;
                    } fv_s;
                } fv_s8;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t  : 8;
                    } fv_s;
                } fv_s9;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint16_t sub_sport_type;
        uint32_t sport_start_time;
        uint32_t sport_stop_time;
        uint32_t sport_total_time;
        uint32_t valid_exercise_time;
        uint32_t sport_total_distance;
        uint16_t total_calorie;
        uint16_t sport_calorie;

        uint32_t avg_pace;
        uint32_t high_pace;
        uint32_t low_pace;
        float avg_speed;
        float max_speed;
        uint32_t total_step;
        uint16_t avg_stride;
        uint16_t avg_cadence;

        uint16_t max_step_rate;
        uint8_t avg_hr;
        uint8_t max_hr;
        uint8_t min_hr;
        float total_up;
        float total_down;
        float avg_height;
        float max_height;

        float min_height;
        float training_effect;
        uint8_t training_effect_rating;
        float anaerobic_training_effect;
        uint8_t anaerobic_training_effect_rating;
        uint8_t max_oxygen_uptake;
        uint8_t max_oxygen_uptake_rating;
        uint8_t body_power_use;

        uint16_t recover_time;
        uint8_t hr_zone_selection;
        uint32_t hr_limit_time;
        uint32_t hr_without_oxygen;
        uint32_t hr_with_oxygen;
        uint32_t hr_expend_fat;
        uint32_t hr_warmup;
        uint32_t target_duration;

        uint16_t target_calorie;
        uint32_t target_distance;
        uint32_t target_pace;
        float target_speed;
        uint16_t target_cadence;
        uint8_t  designated_courses;
        //uint64_t courses_id;
        uint16_t training_load;
        uint8_t  training_load_rating;

        uint32_t running_power_index;
        uint8_t running_power_level;
        uint8_t training_status;
        uint8_t genki_value;
        uint32_t full_palm_landing_time;
        uint32_t forehand_landing_time;
        uint32_t hell_landing_time;
        uint8_t inversion_amplitude;

        uint8_t main_landing_method;
        uint8_t running_posture1;//前
        uint8_t running_posture2;//后
        uint8_t :8;
        uint8_t :8;
        uint16_t :16;
        uint16_t :16;
        uint16_t :16;

        uint16_t :16;
        uint8_t :8;
        uint8_t :8;
    } data_s;
} Report_Outside_Run_Category_Data_Type_V5;
typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d;
            struct {
                uint8_t                  : 5;
                uint8_t fv_gps_timestamp : 1;
                uint8_t fv_gps_longitude : 1;
                uint8_t fv_gps_latitude  : 1;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t gps_timestamp;
        float    gps_longitude;
        float    gps_latitude;
    } data_s;
} Gps_Data_Type_V1;

typedef union {
    uint8_t *p_data;
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            } ec_opt;
        } ec_opt_s;
        union {
            uint8_t fv_d;
            struct {
                uint8_t                  : 5;
                uint8_t fv_gps_timestamp : 1;
                uint8_t fv_gps_longitude : 1;
                uint8_t fv_gps_latitude  : 1;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint32_t gps_timestamp;
        float    gps_longitude;
        float    gps_latitude;
        float    location_accuracy;
        union {
            uint16_t fv_d;
            struct {
                uint16_t gps_source : 4;
                uint16_t location_speed : 12;
            } speed_gps_s;
        } speed_gps_u;
    } data_s;
} Gps_Data_Type_V2;

#define MAX_SPORT_APP_AUTO_SPORT_GPS_DATA (22 * 1024)
typedef struct _SPORT_app_auto_sport_gps_obj_t
{
    uint32_t total_cnts;
    uint32_t data_len;
    uint8_t data_array[MAX_SPORT_APP_AUTO_SPORT_GPS_DATA];
} SPORT_app_auto_sport_gps_obj_t;
#pragma pack(pop)

#endif /* _MUL_SPORT_DATA_STRUCT_H */
