#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#if GPS_DATA_MANAGER_SWITCH

#include <stdio.h>
#include <string.h>

#include "mul_sport_platform.h"
#include "ms_gps_sport.h"
#include "mul_sport_data_struct.h"

const uint8_t MUL_SPORT_ALIGN_WAY g_gps_point_header_v1_buf[] = {0x00, 0xE0};
const uint8_t MUL_SPORT_ALIGN_WAY g_gps_point_header_v2_buf[] = {0x00, 0xFC};

static bool MUL_SPORT_POSSIBLY_UNUSED get_gps_data_v1
    (void *p_data, uint32_t *p_data_len, ms_gps_item_t gps_item)
{
    Gps_Data_Type_V1 gps_data;

     if (!p_data || !p_data_len)
     {
         return false;
     }

     gps_data.data_s.gps_timestamp = gps_item.gps_v1.ts;
     gps_data.data_s.gps_longitude = gps_item.gps_v1.longitude;
     gps_data.data_s.gps_latitude  = gps_item.gps_v1.latitude;

     memcpy(p_data,
            (uint8_t *)&gps_data.data_s,
            sizeof(gps_data.data_s));

     *p_data_len = sizeof(gps_data.data_s);

     return true;
}

static bool MUL_SPORT_POSSIBLY_UNUSED get_gps_data_v2
    (void *p_data, uint32_t *p_data_len, ms_gps_item_t gps_item)
{
    Gps_Data_Type_V2 gps_data;

     if (!p_data || !p_data_len)
     {
         return false;
     }

     gps_data.data_s.gps_timestamp                          = gps_item.gps_v2.ts;
     gps_data.data_s.gps_longitude                          = gps_item.gps_v2.longitude;
     gps_data.data_s.gps_latitude                           = gps_item.gps_v2.latitude;
     gps_data.data_s.location_accuracy                      = gps_item.gps_v2.location_accuracy;
     gps_data.data_s.speed_gps_u.speed_gps_s.gps_source     = gps_item.gps_v2.speed_gps_u.speed_gps_s.gps_source;
     gps_data.data_s.speed_gps_u.speed_gps_s.location_speed = gps_item.gps_v2.speed_gps_u.speed_gps_s.location_speed;
    printf("gps_data.data_s.speed_gps_u.speed_gps_s.gps_source:%d\n", gps_data.data_s.speed_gps_u.speed_gps_s.gps_source);
     memcpy(p_data,
            (uint8_t *)&gps_data.data_s,
            sizeof(gps_data.data_s));

     *p_data_len = sizeof(gps_data.data_s);

     return true;
}

//-=-=-=-=-=-=
//

static p_ms_abstract_gps_handle_t MUL_SPORT_POSSIBLY_UNUSED mul_sport_get_gps_handle_v1(void)
{
    const static ms_common_gps_handle_v1_t gps_hanlde_v1_v1 = {
    .gps_handle = {
        .magic_number = MUL_SPORT_MAGIC_NUMBER,
        .version = MUL_SPORT_VER_1,
        .pf_get_gps_data = get_gps_data_v1,
    }
    };

    return (p_ms_abstract_gps_handle_t)&gps_hanlde_v1_v1;
}

static p_ms_abstract_gps_handle_t MUL_SPORT_POSSIBLY_UNUSED mul_sport_get_gps_handle_v2(void)
{
    const static ms_common_gps_handle_v1_t gps_hanlde_v1_v2 = {
    .gps_handle = {
        .magic_number = MUL_SPORT_MAGIC_NUMBER,
        .version = MUL_SPORT_VER_1,
        .pf_get_gps_data = get_gps_data_v2,
}
    };

    return (p_ms_abstract_gps_handle_t)&gps_hanlde_v1_v2;
}

p_ms_abstract_gps_handle_t mul_sport_get_gps_handle_obj(uint32_t gps_version)
{
    p_ms_abstract_gps_handle_t ret_gps_handle_obj = NULL;

    switch (gps_version)
    {
        case 0x01:
            ret_gps_handle_obj = mul_sport_get_gps_handle_v1();
            break;

        case 0x02:
            ret_gps_handle_obj = mul_sport_get_gps_handle_v2();
            break;

        default:
            ret_gps_handle_obj = NULL;
            break;
    }

    return ret_gps_handle_obj;
}

void mul_sport_get_gps_data_header(uint8_t version, uint8_t **pp_header_data, size_t *p_data_len)
{
    switch (version)
    {
        case 0x01:
            *pp_header_data = (uint8_t *)g_gps_point_header_v1_buf;
            *p_data_len = sizeof(g_gps_point_header_v1_buf);
            break;

        case 0x02:
            *pp_header_data = (uint8_t *)g_gps_point_header_v2_buf;
            *p_data_len = sizeof(g_gps_point_header_v2_buf);
            break;

        default:
            break;
    }
}

void mul_sport_get_gps_item_size(uint8_t version, size_t *p_item_size)
{
    switch (version)
    {
        case 0x01:
            *p_item_size = sizeof(ms_gps_item_v1);
            break;

        case 0x02:
            *p_item_size = sizeof(ms_gps_item_v2);
            break;

        default:
            break;
    }
}

#endif /* GPS_DATA_MANAGER_SWITCH */

#endif /* FLASH_MANAGER_SWITCH */