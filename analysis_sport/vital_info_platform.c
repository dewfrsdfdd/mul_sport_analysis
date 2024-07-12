#include "vital_info_platform.h"
#if 0
#include "daily_data_handle.h"
#include "manual_measure_data_handle.h"
#include "vital_info_data_handle.h"
#include "zh_data_global.h"


int32_t vital_info_flash_read(flash_api_file p_file, uint32_t addr, uint8_t *p_data, uint32_t len)
{
#if VITAL_INFO_PC_SIMULATOR
    return 0;
#else
    return ad_nvms_read(p_file, addr, p_data, len);
#endif
}

int32_t vital_info_flash_write(flash_api_file p_file, uint32_t addr, uint8_t *p_data, uint32_t len)
{
#if VITAL_INFO_PC_SIMULATOR
    return 0;
#else
    return ad_nvms_write(p_file, addr, p_data, len);
#endif
}

int32_t vital_info_flash_erase(flash_api_file p_file, uint32_t addr, uint32_t len)
{
#if VITAL_INFO_PC_SIMULATOR
    return 0;
#else
    return ad_nvms_erase_region(p_file, addr, len);
#endif
}

uint32_t vital_info_get_steps_day(void)
{
    return get_today_step_number(); 
}

uint32_t vital_info_get_calories_day(void)
{
    return get_today_calorie_number();
}

uint32_t vital_info_get_distance_day(void)
{
    return get_today_mileage_number();
}

uint8_t vital_info_get_low_genki_day(void)
{
    uint8_t low_genki_day = 0;
#ifdef XIAOMI_ALGO_LIB_ON_LCPU
    low_genki_day = (uint8_t)today_daily_data.wellness_genki_data.prev_result.low_score;
#endif
    return low_genki_day;
}

uint8_t vital_info_get_medium_genki_day(void)
{
    uint8_t medium_genki_day = 0;
#ifdef XIAOMI_ALGO_LIB_ON_LCPU
    medium_genki_day = (uint8_t)today_daily_data.wellness_genki_data.prev_result.mid_score;
#endif
    return medium_genki_day;
}

uint8_t vital_info_get_high_genki_day(void)
{
    uint8_t high_genki_day = 0;
#ifdef XIAOMI_ALGO_LIB_ON_LCPU
    high_genki_day = (uint8_t)today_daily_data.wellness_genki_data.prev_result.high_score;
#endif
    return high_genki_day;
}

uint16_t vital_info_get_total_genki_7_day(void)
{
    uint16_t total_genki_7_day = 0;
#ifdef XIAOMI_ALGO_LIB_ON_LCPU
    total_genki_7_day = (uint16_t)today_daily_data.wellness_genki_data.prev_result.sum_score;
#endif
    return total_genki_7_day;
}

uint8_t vital_info_get_next_genki_suggest_type(void)
{
    uint8_t next_genki_suggest_type = 0;
#ifdef XIAOMI_ALGO_LIB_ON_LCPU
    next_genki_suggest_type = (uint8_t)today_daily_data.wellness_genki_data.prev_result.target_stage;
#endif
    return next_genki_suggest_type;
}

uint8_t vital_info_get_next_genki_suggest_dur(void)
{
    uint8_t next_genki_suggest_dur = 0;
#ifdef XIAOMI_ALGO_LIB_ON_LCPU
    next_genki_suggest_dur = today_daily_data.wellness_genki_data.prev_result.target_duration;
#endif
    return next_genki_suggest_dur;
}

void vital_info_set_cur_hr(uint8_t hr)
{
    p_daily_data_interact_t p_interact_s = daily_data_get_interact_s();

    p_interact_s->point_s.cur_hr = hr;

    daily_data_set_hr_local_ts(get_local_timestamp());
}

void vital_info_set_cur_spo2(uint8_t spo2)
{
    p_daily_data_interact_t p_interact_s = daily_data_get_interact_s();

    p_interact_s->point_s.cur_spo2 = spo2;

    daily_data_set_spo2_local_ts(get_local_timestamp());
}

void vital_info_set_cur_hrv(uint8_t hrv)
{
    p_daily_data_interact_t p_interact_s = daily_data_get_interact_s();

    p_interact_s->point_s.cur_hrv = hrv;

    daily_data_set_hrv_local_ts(get_local_timestamp());
}

void vital_info_set_abn_hr(uint8_t hr)
{
    return;
}

uint8_t vital_info_get_calm_hr(void)
{
    return get_app_heart_rate_today_data()->detail.last_calm_val;
}

void vital_info_set_exist_calm_hr(void)
{
    p_daily_data_interact_t p_interact_s = daily_data_get_interact_s();

    p_interact_s->point_s.exist_status.es_s.calm_hr_is_existed = 1;
}

uint8_t vital_info_get_power_level(void)
{
#ifdef XIAOMI_ALGO_LIB_ON_LCPU
    extern  uint8_t minute_act_intensity_pro(void);
    return minute_act_intensity_pro();
#else
    return 0;
#endif
}

uint8_t vital_info_get_s_type(void)
{
//    extern uint8_t get_amd_type(void);

//    if (get_amd_type() == MI_AMD_STATIC)
//    {
//        return 1;
//    }
//    else
//    {
//        return 2;
//    }

    return 0;
}

void vital_info_get_valid_stand(uint8_t *p_valid_data)
{
    get_today_his_eff_sta(p_valid_data);
}

void vital_info_platform_min_hr_cb(uint8_t hr)
{
    if (hr)
    {
        uint8_t max_hr = 0;

        if (get_user_profile_max_hr() > 0)
        {
            max_hr = get_user_profile_max_hr();
        }
        else
        {
            max_hr = 220 - get_user_profile_age();
        }

        if (hr > max_hr * 0.9)
        {
            get_app_heart_rate_today_data()->detail.hr_limit_time_time++;
        }
        else if (hr > max_hr * 0.8)
        {
            get_app_heart_rate_today_data()->detail.hr_without_oxygen_time++;
        }
        else if (hr > max_hr * 0.7)
        {
            get_app_heart_rate_today_data()->detail.hr_with_oxygen_time++;
        }
        else if (hr > max_hr * 0.6)
        {
            get_app_heart_rate_today_data()->detail.hr_expend_fat_time++;
        }
        else if (hr > max_hr * 0.5)
        {
            get_app_heart_rate_today_data()->detail.hr_warmup_time++;
        }

        do
        {
            bool is_manu_hr_measuring = false;  // 是否正在手动心率测量
            bool can_update_manu_hr = false;    // 能否更新手动测量的心率存储点
            app_heart_rate_main_page_t *p_hr_main_page = get_heart_rate_main_page_ptr();
            app_heart_rate_main_page_t *p_hr_tlv_page = get_heart_rate_tlv_page_ptr();

            if (p_hr_main_page && (p_hr_main_page->is_hr_main_page == true) && (p_hr_main_page->is_hr_main_running == true))
            {
                if (p_hr_main_page->page_status == STATUS_BE_MEASURING
                    || p_hr_main_page->page_status == STATUS_GENERATED_VALUE)
                {
                    is_manu_hr_measuring = true;

                    if (p_hr_main_page->page_status == STATUS_GENERATED_VALUE)
                    {
                        can_update_manu_hr = true;
                    }
                }
            }
            else if (p_hr_tlv_page && (p_hr_tlv_page->is_hr_main_page == true) && (p_hr_tlv_page->is_hr_main_running == true))
            {
                if (p_hr_tlv_page->page_status == STATUS_BE_MEASURING
                    || p_hr_tlv_page->page_status == STATUS_GENERATED_VALUE)
                {
                    is_manu_hr_measuring = true;

                    if (p_hr_tlv_page->page_status == STATUS_GENERATED_VALUE)
                    {
                        can_update_manu_hr = true;
                    }
                }
            }

            uint32_t last_hr_local_ts = daily_data_get_hr_local_ts();
            uint32_t cur_local_ts = get_local_timestamp();
            bool is_same_day = vital_info_is_the_same_day(last_hr_local_ts, cur_local_ts);

            if (is_same_day)
            {
                if ((cur_local_ts > last_hr_local_ts) && (cur_local_ts - last_hr_local_ts <= 60))
                {
                    if (is_manu_hr_measuring == false)
                    {
                        set_heard_vaule_messure_display_system(hr);
                        set_heard_vaule_system_timestamp(last_hr_local_ts);
                        set_heard_vaule_system_timezone(get_time_zone());

                        get_app_heart_rate_hr_disp()->last_value = get_heard_vaule_messure_display_system();
                        get_app_heart_rate_hr_disp()->last_timestamp = get_heard_vaule_system_timestamp();
                        get_app_heart_rate_hr_disp()->last_timezone = get_heard_vaule_system_timezone();

                        update_today_hr_data(hr, last_hr_local_ts);

                        vital_info_set_cur_hr(hr);
                    }
                    else
                    {
                        if (can_update_manu_hr)
                        {
                            mm_data_new_single_item_file(MMD_HR, hr);
#ifndef BSP_USING_PC_SIMULATOR
                            extern void fitness_health_sport_sys(void);
                            fitness_health_sport_sys();
#endif
                        }
                    }
                }
            }
        } while (0);
    }
}

void vital_info_platform_min_spo2_cb(uint8_t spo2)
{
    if (spo2)
    {
        uint32_t last_spo2_local_ts = daily_data_get_spo2_local_ts();
        uint32_t cur_local_ts = get_local_timestamp();
        bool is_same_day = vital_info_is_the_same_day(last_spo2_local_ts, cur_local_ts);

        if (is_same_day)
        {
            if ((cur_local_ts > last_spo2_local_ts) && (cur_local_ts - last_spo2_local_ts <= 60))
            {
                update_today_spo2_data(spo2, true, last_spo2_local_ts);
            }
        }
    }
}

void vital_info_platform_min_hrv_cb(uint8_t hrv)
{
    if (hrv)
    {
        uint32_t last_hrv_local_ts = daily_data_get_hrv_local_ts();
        uint32_t cur_local_ts = get_local_timestamp();
        bool is_same_day = vital_info_is_the_same_day(last_hrv_local_ts, cur_local_ts);

        if (is_same_day)
        {
            if ((cur_local_ts > last_hrv_local_ts) && (cur_local_ts - last_hrv_local_ts <= 60))
            {
                // sth to do.
            }
        }
    }
}

void vital_info_platform_malloc_failed(const char *func_name, uint32_t line)
{
    vital_info_dbg_log(" malloc failed! func=%s, line=%d\n", func_name, line);

    
    
    (MALLOC_FAIL_EXCEPTION_LOG_ID,
                                " malloc failed, func=%s, line=%d",
                                func_name,
                                line);
}
#endif