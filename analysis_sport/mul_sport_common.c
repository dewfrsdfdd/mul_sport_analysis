#include "mul_sport_common.h"


#if FLASH_MANAGER_SWITCH


#define IsLeapYear(yr) (!((yr) % 400) || (((yr) % 100) && !((yr) % 4)))

#define YearLength(yr) (IsLeapYear(yr) ? 366 : 365)

#define MUL_SPORT_BEGYEAR  1970     // UTC started at 00:00:00 January 1, 1970

#define DAY             86400UL  // 24 hours * 60 minutes * 60 seconds


uint8_t mul_sport_monthLength( uint8_t lpyr, uint8_t mon )
{
    uint8_t days = 31;

    if ( mon == 1 ) // feb
    {
        days = ( 28 + lpyr );
    } else {
        if ( mon > 6 ) // aug-dec
        {
            mon--;
        }

        if ( mon & 1 ) {
            days = 30;
        }
    }

    return ( days );
}


utc_time_t mul_sport_convert_time_to_sec(mul_sport_time_union_t time)
{
    uint32_t i = 0;
    utc_time_t offset = 0;

    //day time
    offset += time.time.seconds;
    offset += time.time.minute * 60;
    offset += time.time.hours * 60 * 60;

    uint8_t leapYear = IsLeapYear(time.time.year + 1970);

    offset += DAY * (time.time.day - 1);

    for(i = 0; i < time.time.month - 1; ++i) { // month start from 1
        offset += mul_sport_monthLength(leapYear,i) * DAY;
    }

    for(i = 0; i< time.time.year ;++i) {
        if(IsLeapYear(i + 1970)) {
            offset += DAY * 366;
        } else {
            offset += DAY * 365;
        }
    }

    return offset;
}

void mul_sport_convert_to_utc_time(mul_sport_utc_time_t* tm, utc_time_t secTime)
{
    // calculate the time less than a day - hours, minutes, seconds
    {
        uint32_t day = secTime % DAY;
        tm->seconds = day % 60UL;
        tm->minutes = (uint8_t)((day % 3600UL) / 60UL);
        tm->hour = (uint8_t)(day / 3600UL);
    }

    // Fill in the calendar - day, month, year
    {
        uint16_t numDays = (uint16_t)(secTime / DAY);
        tm->year = MUL_SPORT_BEGYEAR;
        while (numDays >= YearLength(tm->year))
        {
            numDays -= YearLength(tm->year);
            tm->year++;
        }

        tm->month = 0;
        while (numDays >= mul_sport_monthLength(IsLeapYear(tm->year), tm->month))
        {
            numDays -= mul_sport_monthLength(IsLeapYear(tm->year), tm->month);
            tm->month++;
        }

        tm->day = (uint8_t)numDays;
    }
}

/******************************************************
* Get time zone offset
*******************************************************/
int32_t mul_sport_get_time_zone_offset(int8_t time_zone)
{
    return time_zone * 15 * 60;
}

/******************************************************
* Determine if the two timestamps are the same day
*******************************************************/
bool mul_sport_is_the_same_day(uint32_t dst_timestamp, uint32_t src_timestamp)
{
    mul_sport_utc_time_t dst_timestruct;
    mul_sport_utc_time_t src_timestruct;

    mul_sport_convert_to_utc_time(&dst_timestruct, dst_timestamp);
    mul_sport_convert_to_utc_time(&src_timestruct, src_timestamp);

    if (dst_timestruct.year == src_timestruct.year
        && dst_timestruct.month == src_timestruct.month
        && dst_timestruct.day == src_timestruct.day)
    {
        return true;
    }

    return false;
}

mul_sport_utc_time_t mul_sport_get_clock_time(utc_time_t utc_time, int8_t time_zone)
{
    mul_sport_utc_time_t utc_time_s;

    mul_sport_convert_to_utc_time(&utc_time_s, utc_time + mul_sport_get_time_zone_offset(time_zone));

    utc_time_s.month += 1;  // calibration
    utc_time_s.day += 1;    // calibration

    return utc_time_s;
}

#endif /* FLASH_MANAGER_SWITCH */
