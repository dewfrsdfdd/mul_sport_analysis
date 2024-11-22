#ifndef _MS_SPORT_ANALYSIS_H
#define _MS_SPORT_ANALYSIS_H

#include "mul_sport_common.h"

#include <stddef.h>
#define USE_BINARY_FILES 1
#ifdef __cplusplus
extern "C" {
#endif

	// ÄãµÄº¯ÊýÉùÃ÷
	extern void mul_sport_analysis_points(void);
	extern void mul_sport_analysis_record(void);
	extern void mul_sport_analysis_gps_points(void);
	extern void mul_sport_analysis_daily_data_points(void);
	extern void mul_sport_analysis_daily_data_record(void);
#ifdef __cplusplus
}
#endif

#endif /* _MS_SPORT_ANALYSIS_H */
