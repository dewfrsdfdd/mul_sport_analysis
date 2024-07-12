#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "mul_sport_factory.h"
#include "mul_sport_platform.h"


static p_ms_abstract_sport_handle_t MUL_SPORT_ALIGN_WAY g_p_ms_sport_list[MUL_SPORT_SPORT_CATEGORY_MAX_NUMS];
static uint32_t g_mul_sport_sport_list_num = 0;


bool mul_sport_factory_add_sport(const p_ms_abstract_sport_handle_t sport_list_item)
{
    bool ret_flag = false;

    if (g_mul_sport_sport_list_num < MUL_SPORT_SPORT_CATEGORY_MAX_NUMS)
    {
        /* TODO: 缺少去重操作 */
        g_p_ms_sport_list[g_mul_sport_sport_list_num] = sport_list_item;
        g_mul_sport_sport_list_num++;

        ret_flag = true;
    }
    else
    {
        mul_sport_dbg_log("factory item overflow\n");
        ret_flag = false;
    }

    return ret_flag;
}

bool mul_sport_factory_get_sport(void *args, p_ms_abstract_sport_handle_t *pp_sport_handle_item)
{
    int i = 0;

    for (; i < g_mul_sport_sport_list_num; ++i)
    {
        if (mul_sport_platform_compare_key(g_p_ms_sport_list[i], args))
        {
            *pp_sport_handle_item = (p_ms_abstract_sport_handle_t)g_p_ms_sport_list[i];
            return true;
        }
    }

    *pp_sport_handle_item = NULL;

    return false;
}


bool mul_sport_factory_destory(void)
{
    g_mul_sport_sport_list_num = 0;

    memset(&g_p_ms_sport_list, 0, sizeof(g_p_ms_sport_list));

    return true;
}

#endif /* FLASH_MANAGER_SWITCH */
