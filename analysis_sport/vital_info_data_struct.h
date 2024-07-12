#ifndef _VITAL_INFO_DATA_STRUCT_H
#define _VITAL_INFO_DATA_STRUCT_H

#include <stdint.h>

#pragma pack(push, 1)

#define VITAL_INFO_MAGIC_NUMBER 0x5A
#define VITAL_INFO_VER_USED 0x01
#define VITAL_TABLE_NOSAVE_FLAG 0XAA

typedef enum
{
    ST_NONE = 0,

    ST_OUTSIDE_RUN = 1,               // 户外跑步
    ST_OUTSIDE_MOVE = 2,              // 户外健走
    ST_INDOOR_RUN = 3,                // 室内跑
    ST_CLIMB = 4,                     // 登山
    ST_CROSS_COUNTRY = 5,             // 越野
    ST_OUTSIDE_CYCLE = 6,             // 户外单车
    ST_INDOOR_CYCLE = 7,              // 室内单车(自由训练类型)
    ST_FREE_SPORT = 8,                // 自由训练(自由训练类型)
    ST_SWIM_INDOOR = 9,               // 室内游泳
    ST_SWIM_OUTDOOR = 10,             // 户外游泳
    ST_ELLIPTICAL_MACHINE = 11,       // 椭圆机
    ST_YOGA = 12,                     // 瑜伽(自由训练类型)
    ST_ROWING_MACHINE = 13,           // 划船机
    ST_ROPE_SKIPPING = 14,            // 跳绳
    ST_OUTSIDE_HIKING = 15,           // 户外徒步
    ST_HIGH_INTENSITY_TRAINING = 16,  // 高强度间歇训练(自由训练类型)
    ST_SKIING = 21,                   // 滑雪(小米协议已不支持该运动的自由训练类型)
    ST_OUTSIDE_RUN_CATEGORY = 22,     // 户外跑步类
    ST_OUTSIDE_NOT_RUN_CATEGORY = 23, // 户外非跑步类
    ST_SAILBOAT = 100,                // 帆船(自由训练类型)
    ST_PADDLE_BOARD = 101,            // 桨板(自由训练类型)
    ST_WATER_POLO = 102,              // 水球(自由训练类型)
    ST_AQUATIC_SPORT = 103,           // 水上运动(自由训练类型)
    ST_SURFING = 104,                 // 滑水(自由训练类型)
    ST_CANOEING = 105,                // 皮划艇(自由训练类型)
    ST_KAYAK_RAFTING = 106,           // 皮艇漂流(自由训练类型)
    ST_ROWING = 107,                  // 划船(自由训练类型)
    ST_MOTORBOAT = 108,               // 摩托艇(自由训练类型)
    ST_WEB_SWIMMING = 109,            // 蹼泳(自由训练类型)
    ST_DRIVING = 110,                 // 跳水(自由训练类型)
    ST_FANCY_SWIMMING = 111,          // 花样游泳(自由训练类型)
    ST_SNORKELING = 112,              // 浮潜(自由训练类型)
    ST_KITE_SURFING = 113,            // 风筝冲浪(自由训练类型)
    ST_INDOOR_SURFING = 114,          // 室内冲浪(自由训练类型)pb没有
    ST_DRAGON_BOAT = 115,             // 龙舟(自由训练类型)pb没有
    ST_ROCK_CLIMBING = 200,           // 攀岩(自由训练类型)
    ST_SKATEBOARDING = 201,           // 滑板(自由训练类型)
    ST_ROLLER_SKATING = 202,          // 轮滑(自由训练类型)
    ST_PARKOUR = 203,                 // 跑酷(自由训练类型)
    ST_ATV = 204,                     // 沙滩车(自由训练类型)
    ST_PARAGLIDER = 205,              // 滑翔伞(自由训练类型)
    ST_BICYCLE_MOTO = 206,            // 小轮车(自由训练类型)
    ST_HEEL_AND_TOE = 207,            // 竞走(自由训练类型)
    ST_CLIMBING_MACHINE = 300,        // 爬楼机(自由训练类型)
    ST_CLIMB_STAIRS = 301,            // 爬楼梯(自由训练类型)
    ST_STEPPER = 302,                 // 踏步机(自由训练类型)
    ST_CORE_TRAINING = 303,           // 核心训练(自由训练类型)
    ST_FLEXIBILITY_TRAINING = 304,    // 柔韧训练(自由训练类型)
    ST_PILATES = 305,                 // 普拉提(自由训练类型)
    ST_GYMNASTICS = 306,              // 体操(自由训练类型)
    ST_STRETCHING = 307,              // 拉伸(自由训练类型)
    ST_STRENGTH_TRAINING = 308,       // 力量训练(自由训练类型)
    ST_CROSS_FIT = 309,               // 交叉训练CrossFit(自由训练类型)
    ST_AEROBICS = 310,                // 健身操(自由训练类型)
    ST_PHYSICAL_TRAINING = 311,       // 体能训练(自由训练类型)
    ST_WALL_BALL = 312,               // 墙球(自由训练类型)
    ST_DUMBBELL_TRAINING = 313,       // 哑铃训练(自由训练类型)
    ST_BARBELL_TRAINING = 314,        // 杠铃训练(自由训练类型)
    ST_WEIGHTLIFTING = 315,           // 举重(自由训练类型)
    ST_DEADLIFT = 316,                // 硬拉(自由训练类型)
    ST_BOBBY_JUMP = 317,              // 波比跳(自由训练类型)
    ST_SIT_UPS = 318,                 // 仰卧起坐(自由训练类型)
    ST_FUNCTIONAL_TRAINING = 319,     // 功能性训练(自由训练类型)
    ST_UPPER_LIMB_TRAINING = 320,     // 上肢训练(自由训练类型)
    ST_LOWER_LIMB_TRAINING = 321,     // 下肢训练(自由训练类型)
    ST_WAIST_TRAINING = 322,          // 腰腹训练(自由训练类型)
    ST_BACK_TRAINING = 323,           // 背部训练(自由训练类型)
    ST_SPINNING = 324,                // 动感单车(自由训练类型)
    ST_WALKING_MACHINE = 325,         // 漫步机(自由训练类型)
    ST_STEP_TRAINING = 326,           // 单杠(自由训练类型)
    ST_SINGLE_BAR = 327,              // 双杠(自由训练类型)
    ST_PARALLEL_BARS = 328,           // 踏步训练(自由训练类型)
    ST_GROUP_CALLISTHENICS = 329,     // 团体操(自由训练类型)
    ST_STRIKE = 330,                  // 搏击操(自由训练类型)
    ST_BATTLE_ROPE = 331,             // 战绳(自由训练类型)
    ST_MIXED_AEROBIC = 332,           // 混合有氧(自由训练类型)
    ST_WALK_INDOOR = 333,             // 室内步行(自由训练类型)
    ST_GYM = 399,                     // 室内健身(自由训练类型)
    ST_SQUARE_DANCE = 400,            // 广场舞(自由训练类型)
    ST_BELLY_DANCE = 401,             // 肚皮舞(自由训练类型)
    ST_BALLET = 402,                  // 芭蕾舞(自由训练类型)
    ST_STREET_DANCE = 403,            // 街舞(自由训练类型)
    ST_ZUMBA = 404,                   // 尊巴(自由训练类型)
    ST_NATIONAL_DANCE = 405,          // 民族舞(自由训练类型)
    ST_JAZZ = 406,                    // 爵士舞(自由训练类型)
    ST_LATIN_DANCE = 407,             // 拉丁舞(自由训练类型)
    ST_HIP_HOP_DANCE = 408,           // 嘻哈舞(自由训练类型)
    ST_POLE_DANCE = 409,              // 钢管舞(自由训练类型)
    ST_BREAKDANCING = 410,            // 霹雳舞(自由训练类型)
    ST_SOCIAL_DANCING = 411,          // 交际舞(自由训练类型)
    ST_MODERN_DANCING = 412,          // 现代舞(自由训练类型)
    ST_DANCE = 499,                   // 舞蹈(自由训练类型)

    ST_BOXING = 500,                  // 拳击(自由训练类型)
    ST_WRESTLING = 501,               // 摔跤(自由训练类型)
    ST_MARTIAL_ARTS = 502,            // 武术(自由训练类型)
    ST_TAICHI = 503,                  // 太极(自由训练类型)
    ST_MUAY_THAI = 504,               // 泰拳(自由训练类型)
    ST_JUDO = 505,                    // 柔道(自由训练类型)
    ST_TAEKWONDO = 506,               // 跆拳道(自由训练类型)
    ST_KARATE = 507,                  // 空手道(自由训练类型)
    ST_FREE_SPARRING = 508,           // 自由搏击(自由训练类型)
    ST_SWORDSMANSHIP = 509,           // 剑术/剑道(自由训练类型)
    ST_FENCING = 510,                 // 击剑(自由训练类型)
    ST_JUJITSU = 511,                 // 柔术(自由训练类型)
    ST_FOOTBALL = 600,                // 足球(自由训练类型)
    ST_BASKETBALL = 601,              // 篮球(自由训练类型)
    ST_VOLLEYBALL = 602,              // 排球(自由训练类型)
    ST_BASEBALL = 603,                // 棒球(自由训练类型)
    ST_SOFTBALL = 604,                // 垒球(自由训练类型)
    ST_RUGBY = 605,                   // 橄榄球(自由训练类型)
    ST_HOCKEY = 606,                  // 曲棍球(自由训练类型)
    ST_TABLE_TENNIS = 607,            // 乒乓球(自由训练类型)
    ST_BADMINTON = 608,               // 羽毛球(自由训练类型)
    ST_TENNIS = 609,                  // 网球(自由训练类型)
    ST_CRICKET = 610,                 // 板球(自由训练类型)
    ST_HANDBALL = 611,                // 手球(自由训练类型)

    ST_BOWLING = 612,                 // 保龄球(自由训练)
    ST_SQUASH = 613,                  // 壁球(自由训练)
    ST_BILLIARDS = 614,               // 台球(自由训练)
    ST_SHUTTLECOCK = 615,             // 毽球(自由训练)
    ST_BEACH_FOOTBALL = 616,          // 沙滩足球(自由训练)
    ST_BEACH_VOLLEYBALL = 617,        // 沙滩排球(自由训练)
    ST_SEPAK_TAKRAW = 618,            // 藤球(自由训练)
    ST_GOLF = 619,                    // 高尔夫球(自由训练类型)
    ST_FOOSBALL = 620,                // 桌上足球(自由训练类型)
    ST_INDOOR_FOOTBALL = 621,         // 室内足球(自由训练类型)
    ST_SANDBAGS_BALL = 622,           // 沙包球(自由训练类型)
    ST_BOCCI = 623,                   // 地掷球(自由训练类型)
    ST_HIHI_BALL = 624,               // 回力球(自由训练类型)
    ST_GATEBALL = 625,                // 门球(自由训练类型)
    ST_DODGEBALL = 626,               // 躲避球(自由训练类型)

    ST_SHUFFLE_BALL = 627,            // 沙狐球(自由训练类型)
    ST_OUTDOOR_SKATING = 700,         // 户外滑冰(自由训练类型)
    ST_CURLING = 701,                 // 冰壶(自由训练)
    ST_SNOW_SPORTS = 702,             // 雪上运动(自由训练)
    ST_SNOWMOBILE = 703,              // 雪地摩托(自由训练)
    ST_PUCK = 704,                    // 冰球(自由训练)
    ST_SNOW_CAR = 705,                // 雪车(自由训练)
    ST_SLED = 706,                    // 雪橇(自由训练)

    ST_INDOOR__SKATING = 707,         // 室内滑冰(自由训练类型)
    ST_SNOWBOARDING = 708,            // 单板滑雪(自由训练类型)
    ST_DOUBLE_BOARD_SKIING = 709,     // 双板滑雪(自由训练类型)
    ST_CROSS_COUNTRY_SKIING = 710,    // 越野滑雪(自由训练类型)

    ST_ARCHERY = 800,                 // 射箭(自由训练类型)
    ST_DARTS = 801,                   // 飞镖(自由训练类型)
    ST_HORSE_RIDING = 802,            // 骑马(自由训练类型)
    ST_TUG_OF_WAR = 803,              // 拔河(自由训练类型)
    ST_HULA_HOOP = 804,               // 呼啦圈(自由训练类型)
    ST_FLY_KITE = 805,                // 放风筝(自由训练类型)
    ST_FISHING = 806,                 // 钓鱼(自由训练类型)
    ST_FRISBEE = 807,                 // 飞盘(自由训练类型)
    ST_SHUTTLECOCK_KICKING = 808,     // 踢毽子(自由训练类型)
    ST_SWING = 809,                   // 秋千(自由训练类型)
    ST_MOTION_SENSING_GAME = 810,     // 体感游戏(自由训练类型)
    ST_ELECTRONIC_SPORTS = 811,       // 电子竞技(自由训练类型)
    ST_CHESS = 900,                   // 国际象棋(自由训练类型)
    ST_DRAUGHTS = 901,                // 国际跳棋(自由训练类型)
    ST_WEIQI = 902,                   // 围棋(自由训练类型)
    ST_BRIDGE = 903,                  // 桥牌(自由训练类型)
    ST_BOARD_GAMES = 904,             // 桌游(自由训练类型)
    ST_EQUESTTRIAN = 10000,           // 马术(自由训练类型)
    ST_TRACK_AND_FIELD = 10001,       // 田径(自由训练类型)
    ST_RACING_CAR = 10002,            // 赛车(自由训练类型)
    ST_SPORT_MAX,
} Sport_Type_Type;

typedef struct
{
    uint8_t : 4;
    uint8_t valid : 3;
    uint8_t exist : 1;
} field_valid_h_type;

typedef struct
{
    uint8_t valid : 3;
    uint8_t exist : 1;
    uint8_t : 4;
} field_valid_l_type;

typedef enum
{
    NO_STORE_DATA = 0xFF,
    STORED_DATA_NOT_UPLOADED = 0x5A,
    STORED_DATA_AND_UPLOADED = 0x18,
    STORED_DATA_BUT_NOT_TO_UPLOAD = 0x10,
} store_flag_type_t;

typedef enum
{
    STORE_NODE_NULL = 0xFF,                // 节点为空,可以被分配
    STORE_NODE_ALLOCATED_NOT_SAVE = 0x5A,  // 节点已经分配,但是没有存储节点进flash
    STORE_NODE_ALLOCATED_AND_SAVED = 0x18, // 节点已经分配,并且已经存入flash,可以上传
    STORE_NODE_INVALID = 0x10,             // 节点已经失效,可以被分配
} store_node_flag_type_t;

typedef enum
{
    STORE_TODAY_ID,   // 当天ID
    STORE_HISTORY_ID, // 历史ID
} data_id_time_attr_t;

enum
{
    ENUM_DAILY_DATA_T = 0,
    ENUM_SPORT_DATA_T,
};

enum
{
    ENUM_DAILY_ACTIVITY_DATA_T = 0,
    ENUM_DAYTIME_SLEEP_T = 2,
    ENUM_SLEEP_NIGHT_T = 3,
    ENUM_USER_INFO_T = 5,
    ENUM_MANUAL_MEASURE = 6,
    ENUM_SLEEP_MI_DEV = 8,
    ENUM_ABN_RECORD_DATA = 9,
};

enum
{
    ENUM_POINT_DATA_T = 0,
    ENUM_REPORT_DATA_T,
    ENUM_SPORT_GPS_DATA_T,
};

typedef struct
{
    uint32_t timestamp;
    int8_t timezone;
    uint8_t version;
    struct
    {

        uint8_t data_type : 2;
        uint8_t specific_type : 5;
        uint8_t type : 1;
    } type_desc;
} data_id_t, *p_data_id_t;

typedef struct
{
    uint8_t magic_num;
    uint8_t version;
    store_flag_type_t store_flash_flag;
    uint32_t data_len;
    uint16_t flash_crc;
} flash_storage_head_t;

#pragma pack(pop)

#endif /* _VITAL_INFO_DATA_STRUCT_H */
