#ifndef _DAILY_ACTIVITY_DATA_STRUCT_H
#define _DAILY_ACTIVITY_DATA_STRUCT_H

#include <stdint.h>

#include "vital_info_data_struct.h"

#pragma pack(push, 1)

typedef enum {
    SPL_STANBY = 0,
    SPL_WEAK,
    SPL_LOW,
    SPL_MEDIUM,
    SPL_HIGH,
    SPL_VIOLENT,
    SPL_UNKNOW = 7
}Sport_Power_Level_Type;

typedef enum {
    SM_WAKE = 0,
    SM_DEEP = 2,
    SM_LIGHT,
    SM_REM,
    SM_WAKEUP
}Sleep_Mode_Type;

typedef enum {
    PS_UNKONW = 0,
    PS_SPORT,
    PS_PRESSURE,
    PS_RECOVER
}Power_State_Type;

typedef enum {
    MMD_HR = 1,
    MMD_SPO2,
    MMD_HRV,
} Manual_Measure_Data_Type;

typedef enum {
    ARD_HR_HIGH      = 1,   // 心率过高
    ARD_HR_LOW       = 2,   // 心率过低
    ARD_SPO2_LOW     = 3,   // 血氧过低
    ARD_HRV_HIGH     = 4,   // 压力过高
    ARD_HB_ABNORMAL  = 5,   // 异常心博
} Abn_Record_Data_Type;

typedef enum {
    ARM_HR = 1,
    ARM_SPO2 = 2,
} Abn_Record_Measure_Type;

typedef enum {
    DAILY_DATA_VALID = 0,           // 数据有效
    DAILY_DATA_INVALID = 1,         // 数据无效
    DAILY_DATA_MALLOC_FAILED = 2,   // 内存分配失败
    DAILY_DATA_NOT_POINT_DATA = 3,  // 不是打点数据
} Daily_Data_Valid_Type;

typedef union{
    uint8_t *p_data;
    struct {
        union{
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
                    union {
                        field_valid_h_type fv_extra_step;
                        field_valid_l_type fv_activity_type;
                    }fv_s;
                }fv_s1;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_sports_type;
                        field_valid_l_type fv_extra_distance;
                    }fv_s;
                }fv_s2;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_hr;
                        field_valid_l_type fv_left_power;
                    }fv_s;
                }fv_s3;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_total_cal;
                        field_valid_l_type fv_spo2;
                    }fv_s;
                }fv_s4;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_hrv;
                        field_valid_l_type fv_null;
                    }fv_s;
                }fv_s5;
            }fv_s;
        }field_valid;
    }pack_head;
    struct {
        union {
            uint16_t step_d;
            struct {
                uint16_t extra_step : 14;
                uint16_t is_include_abn_hr_data : 1;
                uint16_t tbd : 1;
            } step_s;
        } step;
        union {
            uint8_t sports_type_d;
            struct {
                uint8_t extra_cal : 6;
                uint8_t s_type : 2;
            } sports_type_s;
        } sports_type;
        union {
            uint8_t sports_level_d;
            struct {
                uint8_t sport_type : 5;
                uint8_t sport_power_level : 3;
            } sports_level_s;
        } sports_level;
        uint16_t extra_distance;
        uint8_t hr;
        uint8_t spo2;
        uint8_t hrv;
        uint8_t abn_hr_data;
    }data_s;
}Point_Activity_Day_Type;

typedef union{
    uint8_t *p_data;
    struct {
        union{
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
                    union {
                        field_valid_h_type fv_extra_step;
                        field_valid_l_type fv_activity_type;
                    }fv_s;
                }fv_s1;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_sports_type;
                        field_valid_l_type fv_extra_distance;
                    }fv_s;
                }fv_s2;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_hr;
                        field_valid_l_type fv_left_power;
                    }fv_s;
                }fv_s3;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_total_cal;
                        field_valid_l_type fv_spo2;
                    }fv_s;
                }fv_s4;
                union {
                    uint8_t fv_d;
                    union {
                        field_valid_h_type fv_hrv;
                        field_valid_l_type fv_null;
                    }fv_s;
                }fv_s5;
            }fv_s;
        }field_valid;
    }pack_head;
    struct {
        union {
            uint16_t step_d;
            struct {
                uint16_t extra_step : 14;
                uint16_t is_include_abn_hr_data : 1;
                uint16_t tbd : 1;
            } step_s;
        } step;
        union {
            uint8_t sports_type_d;
            struct {
                uint8_t extra_cal : 6;
                uint8_t s_type : 2;
            } sports_type_s;
        } sports_type;
        union {
            uint8_t sports_level_d;
            struct {
                uint8_t sport_type : 5;
                uint8_t sport_power_level : 3;
            } sports_level_s;
        } sports_level;
        uint16_t extra_distance;
        uint8_t hr;
        uint8_t spo2;
        uint8_t hrv;
    }data_s;
} Point_Activity_Day_Read_Type;

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
                        uint8_t fv_min_hr_time_day : 1;
                        uint8_t fv_min_hr_day : 1;
                        uint8_t fv_max_hr_time_day : 1;
                        uint8_t fv_max_hr_day : 1;
                        uint8_t fv_calm_hr_day : 1;
                        uint8_t fv_hr_now : 1;
                        uint8_t fv_total_calorie_now : 1;
                        uint8_t fv_total_step_now : 1;
                    } fv_s;
                } fv_s1;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_spo2_now : 1;
                        uint8_t fv_recover_time : 1;
                        uint8_t fv_total_calorie : 1;
                        uint8_t fv_valid_stand : 1;
                        uint8_t fv_min_pressure_day : 1;
                        uint8_t fv_max_pressure_day : 1;
                        uint8_t fv_avg_pressure_day : 1;
                        uint8_t fv_avg_hr_day : 1;
                    } fv_s;
                } fv_s2;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t fv_workload_level : 1;
                        uint8_t fv_total_workload_7_day : 1;
                        uint8_t fv_workload_day : 1;
                        uint8_t fv_avg_spo2_day : 1;
                        uint8_t fv_min_spo2_time_day : 1;
                        uint8_t fv_min_spo2_day : 1;
                        uint8_t fv_max_spo2_time_day : 1;
                        uint8_t fv_max_spo2_day : 1;
                    } fv_s;
                } fv_s3;
                union {
                    uint8_t fv_d;
                    struct {
                        uint8_t : 2;
                        uint8_t fv_next_genki_suggest_dur : 1;
                        uint8_t fv_next_genki_suggest_type : 1;
                        uint8_t fv_total_genki_7_day : 1;
                        uint8_t fv_high_genki_day : 1;
                        uint8_t fv_medium_genki_day : 1;
                        uint8_t fv_low_genki_day : 1;
                    } fv_s;
                } fv_s4;
            } fv_s;
        }field_valid;
    } pack_head;

    struct {
        uint32_t total_step_now;
        uint16_t total_calorie_now;
        uint8_t hr_now;
        uint8_t calm_hr_day;
        uint8_t max_hr_day;
        uint32_t max_hr_time_day;
        uint8_t min_hr_day;
        uint32_t min_hr_time_day;
        uint8_t avg_hr_day;
        uint8_t avg_pressure_day;
        uint8_t max_pressure_day;
        uint8_t min_pressure_day;
        uint8_t valid_stand[3];

        uint16_t total_calorie;
        uint16_t recover_time;
        uint8_t spo2_now;
        uint8_t max_spo2_day;
        uint32_t max_spo2_time_day;
        uint8_t min_spo2_day;
        uint32_t min_spo2_time_day;
        uint8_t avg_spo2_day;

        uint16_t workload_day;
        uint16_t total_workload_7_day;
        uint8_t  workload_level;
        uint8_t low_genki_day;
        uint8_t medium_genki_day;
        uint8_t high_genki_day;
        uint16_t total_genki_7_day;
        uint8_t next_genki_suggest_type;
        uint8_t next_genki_suggest_dur;
    } data_s;
} Report_Activity_Day_Type;

typedef union {
    uint8_t data[35];
    struct {
        union {
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            }ec_opt;
        }ec_opt_s;
        union {
            uint16_t fv_d;
            struct {
                uint16_t fv_sleep_exit_time : 1;
                uint16_t fv_sleep_enter_time : 1;
                uint16_t fv_sleep_time : 1;
                uint16_t fv_sleep_suggest : 1;
                uint16_t fv_sleep_conclusion : 1;
                uint16_t fv_sleep_time_score : 1;
                uint16_t fv_sleep_quality_score : 1;
                uint16_t fv_sleep_total_score : 1;
                uint16_t fv_sleep_friendly_score : 1;
                uint16_t fv_sleep_awake_time : 1;
                uint16_t fv_sleep_rem_time : 1;
                uint16_t fv_sleep_light_time : 1;
                uint16_t fv_sleep_deep_time : 1;
                uint16_t fv_sleep_wake_count : 1;
                uint16_t fv_sleep_uneasy_score : 1;
                uint16_t fv_sleep_recover_score : 1;
            }fv_s;
        }field_valid;
    }pack_head;
    struct {
        uint8_t sleep_total_score;
        uint8_t sleep_quality_score;
        uint8_t sleep_time_score;
        uint8_t sleep_conclusion;
        uint8_t sleep_suggest;
        uint16_t sleep_time;
        uint32_t sleep_enter_time;
        uint32_t sleep_exit_time;
        uint8_t sleep_recover_score;
        uint8_t sleep_uneasy_score;
        uint8_t sleep_wake_count;
        uint16_t sleep_deep_time;
        uint16_t sleep_light_time;
        uint16_t sleep_rem_time;
        uint16_t sleep_awake_time;
        uint8_t  sleep_friendly_score;
        uint32_t sleep_mode_change_time;
        union{
            uint8_t sm_d;
            Sleep_Mode_Type sm_s;
        }sleep_mode_after_change;
    }data_s;
}Sleep_Night_Type;

typedef union{
    uint8_t *p_data;
    struct {
        union{
            uint8_t ec_opt_d;
            struct {
                uint8_t encry : 4;
                uint8_t zip : 4;
            }ec_opt;
        }ec_opt_s;
        union {
            uint8_t fv_d;
            struct {
                uint8_t : 5;
                uint8_t fv_data_val : 1;
                uint8_t fv_data_type : 1;
                uint8_t fv_time_stamp : 1;
            } fv_s;
        }field_valid;
    }pack_head;
    struct {
        uint32_t time_stamp;
        Manual_Measure_Data_Type data_type;
        uint8_t data_val;
    }data_s;
} Manual_Measure_Type;

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
                uint8_t : 1;
                uint8_t : 1;
                uint8_t : 1;
                uint8_t : 1;
                uint8_t : 1;
                uint8_t : 1;
                uint8_t : 1;
                uint8_t fv_is_completed: 1;
            } fv_s;
        } field_valid;
    } pack_head;
    struct {
        uint8_t  is_completed;      // 本段睡眠是否完整
        uint32_t sleep_enter_time;  // 入睡时间戳
        uint32_t sleep_exit_time;   // 出睡时间戳
        uint16_t hr_interval;       // 心率打点时间间隔
        uint16_t hr_cnts;           // 心率打点个数
        uint32_t first_hr_time;     // 第一个心率点的时间戳
                                    // 心率打点值
        uint16_t spo2_interval;     // 血氧打点时间间隔
        uint16_t spo2_cnts;         // 血氧打点个数
        uint32_t first_spo2_time;   // 第一个心率点的时间戳
                                    // 血氧打点值
    } data_s;
} Sleep_Mi_Dev_Type;

typedef struct
{
    uint32_t timestamp;
    uint8_t  abn_val;
} Abn_Record_Item_Type;

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
    } pack_head;
    struct {
        struct {
            uint32_t start_timestamp;                                     // 异常记录开始时间戳
            uint32_t end_timestamp;                                       // 异常记录结束时间戳
            Abn_Record_Data_Type abn_type;                                // 异常类型
            uint16_t abn_record_cnts;                                     // 异常记录条数
        } data_fixed;
        // struct {
            
        // } data_dynamics;
    } data_s;
} Abn_Record_Type;

#pragma pack(pop)

#endif /* _DAILY_ACTIVITY_DATA_STRUCT_H */
