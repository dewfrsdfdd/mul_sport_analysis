#ifndef __zh_flash_memory_h__
#define __zh_flash_memory_h__

#include "stdbool.h"
#include "stdint.h"
#include <string.h>
#if 0
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "rtconfig.h"
#ifndef BSP_USING_PC_SIMULATOR
#include "drv_flash.h"
#endif
#include "os_adaptor.h"
#endif
extern int ad_nvms_read(uint32_t handle_base_addr, uint32_t addr, uint8_t *buf, uint32_t len);
extern void Erase_Flash_Memory_With_Crc( uint32_t offset, uint32_t size);
extern int ad_nvms_write(uint32_t handle_base_addr , uint32_t addr,  uint8_t *buf, uint32_t size);
extern int ad_nvms_erase_region(uint32_t handle_base_addr, uint32_t addr, size_t size);
int ad_nvms_write_not_erase(uint32_t handle_base_addr , uint32_t addr,  uint8_t *buf, uint32_t size);
#endif