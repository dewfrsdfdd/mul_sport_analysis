#ifndef _MS_SPORT_ANALYSIS_H
#define _MS_SPORT_ANALYSIS_H

#include "mul_sport_common.h"

#include <stddef.h>
#define USE_BINARY_FILES 1
#ifdef __cplusplus
extern "C" {
#endif
	typedef enum
	{
		ANALYSIS_NULL = 0,//null
		DAILY_POINTS = 1,
		DAILY_RECORD = 2,
		MUL_SPORT_POINTS = 3,
		MUL_SPORT_RECORD = 4,
		MUL_GPS_POINTS = 5,
	} mul_point_type_t;
	// ÄãµÄº¯ÊýÉùÃ÷
	extern void mul_sport_analysis_points(void);
	extern void mul_sport_analysis_record(void);
	extern void mul_sport_analysis_gps_points(void);
	extern void mul_sport_analysis_daily_data_points(void);
	extern void mul_sport_analysis_daily_data_record(void);
	extern char *analysis_to_name(mul_point_type_t msg);

#ifdef __cplusplus
}
#endif

#endif /* _MS_SPORT_ANALYSIS_H */
