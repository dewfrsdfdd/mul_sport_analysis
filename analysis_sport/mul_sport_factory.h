#include "mul_sport_common.h"

#if FLASH_MANAGER_SWITCH

#ifndef _MUL_SPORT_FACTORY_H
#define _MUL_SPORT_FACTORY_H

#include <stdint.h>
#include "mul_sport_common.h"


bool mul_sport_factory_add_sport(const p_ms_abstract_sport_handle_t sport_list_item);
bool mul_sport_factory_get_sport(void *args, p_ms_abstract_sport_handle_t *pp_sport_list_item);
bool mul_sport_factory_destory(void);


#endif /* _MUL_SPORT_FACTORY_H */

#endif /* FLASH_MANAGER_SWITCH */
