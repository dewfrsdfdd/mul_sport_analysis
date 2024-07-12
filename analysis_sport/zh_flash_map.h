#ifndef __zh_flash_map__h_
#define __zh_flash_map__h_

//#include "zh_flash_map_from_excel.h"


#if 0

#define A_START_ADDR                                  ZH_EXCEL_FLASH_TABLE_START_ADDR


#define FLASH_TABLE_ADDR                              ZH_EXCEL_FLASH_TABLE_START_ADDR                                     
#define FLASH_TABLE_ADDR_SIZE                         ZH_EXCEL_FLASH_TABLE_SIZE//16K


#define BOOTLOADER_START_ADDR                         ZH_EXCEL_FLASH_BOOT_LOADER_START_ADDR                                 
#define BOOTLOADER_START_ADDR_SIZE                    ZH_EXCEL_FLASH_TABLE_SIZE//48K



#define DFU_A_ADDRESS                                  ZH_EXCEL_FLASH_PART2_BASE_ADDR
#define DFU_A_ADDRESS_SIZE                             ZH_EXCEL_FLASH_PART2_SIZE//16K

#define BLE_A_ADDRESS                                  ZH_EXCEL_FLASH_PART3_BASE_ADDR
#define BLE_A_ADDRESS_SIZE                             ZH_EXCEL_FLASH_PART3_SIZE//16K

#define CONTACT_A_ADDRESS                              ZH_EXCEL_FLASH_PART4_BASE_ADDR
#define CONTACT_A_ADDRESS_SIZE                         ZH_EXCEL_FLASH_PART4_SIZE//16K


#define CALL_LOG_A_ADDRESS                             ZH_EXCEL_FLASH_PART8_BASE_ADDR
#define CALL_LOG_A_ADDRESS_SIZE                        ZH_EXCEL_FLASH_PART8_SIZE//16K
  

#define APP_CODE_A_ADDRESS                             ZH_EXCEL_FLASH_PART10_BASE_ADDR
#define APP_CODE_A_ADDRESS_SIZE                        ZH_EXCEL_FLASH_PART10_SIZE//4576k


#define IMG_A_ADDRESS                                  ZH_EXCEL_FLASH_PART11_BASE_ADDR
#define IMG_A_ADDRESS_SIZE                             ZH_EXCEL_FLASH_PART11_SIZE//8304K

#define FONT_A_ADDRESS                                  ZH_EXCEL_FLASH_PART12_BASE_ADDR
#define FONT_A_ADDRESS_SIZE                             ZH_EXCEL_FLASH_PART12_SIZE//2356K

#define OTA_STATE_A_ADDRESS                             ZH_EXCEL_FLASH_PART13_BASE_ADDR
#define OTA_STATE_A_ADDRESS_SIZE                        ZH_EXCEL_FLASH_PART13_SIZE//4K


#define BUS_FLASH_START_ADDR1                          ZH_EXCEL_FLASH_PART14_BASE_ADDR
#define USER_DATA_FLASH_AREA_SIZE1                     ZH_EXCEL_FLASH_PART14_SIZE//992KB


#define BOOT_COPY_CODE_START_ADDRESS				    ZH_EXCEL_FLASH_PART22_BASE_ADDR
#define BOOT_COPY_CODE_SIZE						        ZH_EXCEL_FLASH_PART22_SIZE // 260K
		
#define CODE_BACK_START_ADDRESS				            ZH_EXCEL_FLASH_PART23_BASE_ADDR
#define CODE_BACK_SIZE						            ZH_EXCEL_FLASH_PART23_SIZE // 3140K


#define BUS_FLASH_START_ADDR2                           ZH_EXCEL_FLASH_PART24_BASE_ADDR
#define USER_DATA_FLASH_AREA_SIZE2                      ZH_EXCEL_FLASH_PART24_SIZE//



#define B_FLASH_APP_DB_ADDRESS                          ZH_EXCEL_FLASH_PART25_BASE_ADDR
#define B_FLASH_APP_DB_ADDRESS_SIZE                     ZH_EXCEL_FLASH_PART25_SIZE//152K
	
#define B_FLASH_RING_ADDRESS                            ZH_EXCEL_FLASH_PART26_BASE_ADDR
#define B_FLASH_RING_ADDRESS_SIZE                       ZH_EXCEL_FLASH_PART26_SIZE//400K
	
#define B_FLASH_DIAL_PUSH_A_START_ADDRESS	            ZH_EXCEL_FLASH_PART27_BASE_ADDR
#define B_FLASH_DIAL_PUSH_TOTAL_SIZE		            ZH_EXCEL_FLASH_PART27_SIZE // 1600K



	//temp
#define  NVMS_GPS_RAM_DATA_START_ADDRESS			   BUS_FLASH_START_ADDR2	 //GPS RAM 200K
#define  NVMS_GPS_RAM_DATA_TOTAL_SIZE				   0x33000//204K

#define  NVMS_GPS_LTO_DATA_START_ADDRESS			  (NVMS_GPS_RAM_DATA_START_ADDRESS+NVMS_GPS_RAM_DATA_TOTAL_SIZE)	//GPS LTO 400K
#define  NVMS_GPS_LTO_DATA_TOTAL_SIZE				   0x63000//396K

#define  FLASH_MIWEAR_SENSOR_DATA_PART_START          (NVMS_GPS_LTO_DATA_START_ADDRESS + NVMS_GPS_LTO_DATA_TOTAL_SIZE)
#define  FLASH_MIWEAR_SENSOR_DATA_PART_SIZE            0x36000 // 216K (128+88)//do not delete

#define  USER_DATA_START_ADDRESS 					  (FLASH_MIWEAR_SENSOR_DATA_PART_START + FLASH_MIWEAR_SENSOR_DATA_PART_SIZE)
#define  USER_DATA_TOTAL_SIZE						   0x57000 // 348K


#pragma region user_flash_save_h

#define user_account_band_data_start                  0x00
#define user_account_band_data_size                   0x1000 // 4k

#define Miware_data_recode_start                      (user_account_band_data_start + user_account_band_data_size)
#define Miware_data_recode_size                       0x3000 // 12k

#define battery_info_data_save_start                  (Miware_data_recode_start + Miware_data_recode_size)
#define battery_info_data_save_size                   0x1000 //4k

#define daily_struct_data_write_start                 (battery_info_data_save_start + battery_info_data_save_size)
#define daily_struct_data_write_size                  0x5000 // 20k

#define daily_local_sleep_data_start                  (daily_struct_data_write_start + daily_struct_data_write_size) 
#define daily_local_sleep_data_size                   0x2000 // 8k

#define alipay_data_save_start                        (daily_local_sleep_data_start + daily_local_sleep_data_size)
#define alipay_data_save_size                         0x1000 // 4k

#define sport_record_save_data_start                  (alipay_data_save_start + alipay_data_save_size)
#define sport_record_save_data_size                   0x1c000 //0x1b800//110k 20个99K

#define supplement_of_sports_data_start               (sport_record_save_data_start + sport_record_save_data_size)
#define supplement_of_sports_data_size                0x3000 // 12k

#define user_information_data_start                   (supplement_of_sports_data_start + supplement_of_sports_data_size)
#define user_information_data_size                    0x1E000 // 120k

#define user_daily_data_start                         (user_information_data_start + user_information_data_size)
#define user_daily_data_size                          0x2000 //8k

	//用作log head
#define system_log_head_start				     	  (user_daily_data_start + user_daily_data_size)
#define system_log_head_start_size				 	  0x1000				//4K


	//用作ota font res full check
#define ota_res_system_log_head_start				  (system_log_head_start + system_log_head_start_size)//2C000
#define ota_res_system_log_head_start_size			  0x1000				//4K

	//用作connect new phone
#define connect_new_phone_flag_head_start			  (ota_res_system_log_head_start + ota_res_system_log_head_start_size)//2C000
#define connect_new_phone_flag_start_size			  0x1000				//4K

	//用作log head
#define sasert_system_log_head_start				   (connect_new_phone_flag_head_start + connect_new_phone_flag_start_size)//2C000
#define sasert_system_log_head_start_size			   0x1000				//4K

//用作Monkey test
#define sasert_system_monkey_test_start				   (sasert_system_log_head_start + sasert_system_log_head_start_size)//2C000
#define sasert_system_monkey_test_size			   0x1000				//4K

#define wxcodepay_data_save_start    					(sasert_system_monkey_test_start+sasert_system_monkey_test_size)
#define wxcodepay_data_save_size     					0x1000 // 4k



#define USER_FLASH_CUR_MAX_END_ADDR                   (sasert_system_monkey_test_start + sasert_system_monkey_test_size)

#define user_flash_max_address                        USER_DATA_TOTAL_SIZE
#define user_use_max_address                          (USER_FLASH_CUR_MAX_END_ADDR)
#if (user_use_max_address > user_flash_max_address)
	    #error "user flash over_flow"
#endif

#pragma endregion

#define  SLEEP_DATA_START_ADDRESS					  (USER_DATA_START_ADDRESS + USER_DATA_TOTAL_SIZE)
#define  SLEEP_DATA_SIZE 							   0x4B000 // 300K 

#define  MANUAL_MEASURE_DATA_START_ADDRESS			  (SLEEP_DATA_START_ADDRESS + SLEEP_DATA_SIZE)
#define  MANUAL_MEASURE_DATA_SIZE					   0x2000  // 8K

#define  ABN_RECORD_DATA_START_ADDRESS				  (MANUAL_MEASURE_DATA_START_ADDRESS + MANUAL_MEASURE_DATA_SIZE)
#define  ABN_RECORD_DATA_SIZE						   0x2000  // 8K

#define  BACKUP_AREA_START_ADDRESS					  (ABN_RECORD_DATA_START_ADDRESS + ABN_RECORD_DATA_SIZE)
#define  BACKUP_AREA_TOTAL_SIZE						   0x2000  // 8K


#define  FACTORY_DATA_START_ADDRESS					  (BACKUP_AREA_START_ADDRESS + BACKUP_AREA_TOTAL_SIZE)
#define  FACTORY_DATA_TOTAL_SIZE 					   0x1A000 // 104K

#define factory_test_data_start                      	0
#define factory_test_data_size                        	0x8000             //32k

#define factory_Three_tuple_start                     	(factory_test_data_start + factory_test_data_size)
#define factory_Three_tuple_size                       	0x1000             //36k

#define factory_SN_number_start                     	(factory_Three_tuple_start + factory_Three_tuple_size)
#define factory_SN_number_size                       	0x1000             //40k

#define factory_PCBASN_number_start                     (factory_SN_number_start + factory_SN_number_size)
#define factory_PCBASN_number_size                      0x1000             //44k

#define factory_fire_version_start				    	(factory_PCBASN_number_start + factory_PCBASN_number_size)
#define factory_fire_version_size				    	0x1000				//48K

#define factory_Reserved_flag_start				    	(factory_fire_version_start + factory_fire_version_size)
#define factory_Reserved_flag_size				    	0x1000				//44K

#define factory_model_id_start					    	(factory_Reserved_flag_start + factory_Reserved_flag_size)
#define factory_model_id_size					    	0x1000				//52K

#define factory_R_code_start					        (factory_model_id_start + factory_model_id_size)
#define factory_R_code_size						        0x1000				//56K

#define factory_MAKE_YEAR_start					        (factory_R_code_start + factory_R_code_size)
#define factory_MAKE_YEAR_size						    0x1000				//60K

#define factory_flash_read_write_start				    (factory_MAKE_YEAR_start + factory_MAKE_YEAR_size)
#define factory_flash_read_write_size					0x1000				//64K


#define factory_other_data_start				        (factory_flash_read_write_start + factory_flash_read_write_size)
#define factory_other_data_size					        0x1000              //68K

	//存储产测中sar校准值（用户模式不可修改）
#define factory_sar_adjust_data_start			        (factory_other_data_start + factory_other_data_size)
#define factory_sar_adjust_data_size			        0x1000              //72K


#define Save_ACC_calibrate_start						(factory_sar_adjust_data_start + factory_sar_adjust_data_size)
#define Save_ACC_calibrate_size							0x1000              //76K


#define factory_BIS_info_data_start				        (Save_ACC_calibrate_start + Save_ACC_calibrate_size)
#define factory_BIS_info_data_size				        0x1000              //80K


#define factory_debug_log_start                         (factory_BIS_info_data_start + factory_BIS_info_data_size)
#define factory_debug_log_size                          0x3000              //88K


#define factory_SKU_start					        	(factory_debug_log_start + factory_debug_log_size)
#define factory_SKU_size						   		 0x1000				//92K


#define factory_Three_tuple_start_back                  factory_test_data_start + 0x19000   //备份在产测数据的最后4kflash上
#define factory_Three_tuple_size_back                   0x1000             //100k


#if (factory_Three_tuple_start_back + factory_Three_tuple_size_back) >(FACTORY_DATA_TOTAL_SIZE)
  #error "fw flash over_flow_two_factory"
#endif



#if  USER_DATA_FLASH_AREA_SIZE1!=0


   #define SPORT_DATA_START_ADDRESS					   (BUS_FLASH_START_ADDR1 + 0)
   #define SPORT_DATA_TOTAL_SIZE						    0x64000 // 400K


   #define GPS_DOT_DATA_START_ADDRESS					 (SPORT_DATA_START_ADDRESS + SPORT_DATA_TOTAL_SIZE)
   #define GPS_DOT_DATA_TOTAL_SIZE					     0x50000 // 320K

   #pragma region gps_dot_region
   #define trace_gps_buffer_address                     (0x000000)
   #define trace_gps_buffer_size                        (GPS_DOT_DATA_TOTAL_SIZE)
   #pragma endregion /* gps_dot_region */

   #define DAILY_POINT_DATA_START_ADDRESS				 (GPS_DOT_DATA_START_ADDRESS + GPS_DOT_DATA_TOTAL_SIZE)
   #define DAILY_POINT_DATA_SIZE						  0x44000 // 272K

    #if (DAILY_POINT_DATA_START_ADDRESS + DAILY_POINT_DATA_SIZE) >(BUS_FLASH_START_ADDR1+USER_DATA_FLASH_AREA_SIZE1)
     #error "fw flash over_flow_two"
    #endif 
#else
   #define SPORT_DATA_START_ADDRESS					   (FACTORY_DATA_START_ADDRESS + FACTORY_DATA_TOTAL_SIZE)
   #define SPORT_DATA_TOTAL_SIZE						    0x64000 // 400K


   #define GPS_DOT_DATA_START_ADDRESS					 (SPORT_DATA_START_ADDRESS + SPORT_DATA_TOTAL_SIZE)
   #define GPS_DOT_DATA_TOTAL_SIZE					     0x50000 // 320K

  #pragma region gps_dot_region
   #define trace_gps_buffer_address                     (0x000000)
   #define trace_gps_buffer_size                        (GPS_DOT_DATA_TOTAL_SIZE)
   #pragma endregion /* gps_dot_region */

   #define DAILY_POINT_DATA_START_ADDRESS				 (GPS_DOT_DATA_START_ADDRESS + GPS_DOT_DATA_TOTAL_SIZE)
   #define DAILY_POINT_DATA_SIZE						  0x44000 // 272K

  #if (DAILY_POINT_DATA_START_ADDRESS + DAILY_POINT_DATA_SIZE) >(BUS_FLASH_START_ADDR2+USER_DATA_FLASH_AREA_SIZE2)
    #error "fw flash over_flow_three"
   #endif

#endif

#else
#define A_START_ADDR                                  ZH_EXCEL_FLASH_TABLE_START_ADDR


#define FLASH_TABLE_ADDR                              ZH_EXCEL_FLASH_TABLE_START_ADDR                                     
#define FLASH_TABLE_ADDR_SIZE                         ZH_EXCEL_FLASH_TABLE_SIZE//16K


#define BOOTLOADER_START_ADDR                         ZH_EXCEL_FLASH_BOOT_LOADER_START_ADDR                                 
#define BOOTLOADER_START_ADDR_SIZE                    ZH_EXCEL_FLASH_TABLE_SIZE//48K



#define DFU_A_ADDRESS                                  ZH_EXCEL_FLASH_PART2_BASE_ADDR
#define DFU_A_ADDRESS_SIZE                             ZH_EXCEL_FLASH_PART2_SIZE//16K

#define BLE_A_ADDRESS                                  ZH_EXCEL_FLASH_PART3_BASE_ADDR
#define BLE_A_ADDRESS_SIZE                             ZH_EXCEL_FLASH_PART3_SIZE//16K

#define CONTACT_A_ADDRESS                              ZH_EXCEL_FLASH_PART4_BASE_ADDR
#define CONTACT_A_ADDRESS_SIZE                         ZH_EXCEL_FLASH_PART4_SIZE//16K


#define CALL_LOG_A_ADDRESS                             ZH_EXCEL_FLASH_PART8_BASE_ADDR
#define CALL_LOG_A_ADDRESS_SIZE                        ZH_EXCEL_FLASH_PART8_SIZE//16K
  
 #if 1
   #define APP_CODE_A_ADDRESS                             ZH_EXCEL_FLASH_PART10_BASE_ADDR
   #define APP_CODE_A_ADDRESS_SIZE                        ZH_EXCEL_FLASH_PART10_SIZE//5448k

   #define IMG_A_ADDRESS                                  ZH_EXCEL_FLASH_PART11_BASE_ADDR
   #define IMG_A_ADDRESS_SIZE                             ZH_EXCEL_FLASH_PART11_SIZE//7244K
   #if ENUM_PROJECT_NAME_N65B_GLOBAL
	 #define FONT_A_ADDRESS                                  ZH_EXCEL_FLASH_PART12_BASE_ADDR
	 #define FONT_A_ADDRESS_SIZE                             (ZH_EXCEL_FLASH_PART12_SIZE-(160*1024))//2748K//留160k用来存储app推送的图片
	 #define APPICON_PIC_ADDRESS							(FONT_A_ADDRESS + FONT_A_ADDRESS_SIZE)
	 #define APPICON_PIC_ADDRESS_SIZE						(160*1024)
   #else
	 #define FONT_A_ADDRESS                                  ZH_EXCEL_FLASH_PART12_BASE_ADDR
	 #define FONT_A_ADDRESS_SIZE                             ZH_EXCEL_FLASH_PART12_SIZE//2748K
   #endif
#else

 //向上中间版本
	 #if ENUM_PROJECT_NAME_N65B_GLOBAL

		  #define APP_CODE_A_ADDRESS							   ZH_EXCEL_FLASH_PART10_BASE_ADDR
		  #define APP_CODE_A_ADDRESS_SIZE 					   (5448*1024)//ZH_EXCEL_FLASH_PART10_SIZE//5448k

		  #define IMG_A_ADDRESS								   (APP_CODE_A_ADDRESS+APP_CODE_A_ADDRESS_SIZE)
		  #define IMG_A_ADDRESS_SIZE							   (7244*1024)//ZH_EXCEL_FLASH_PART11_SIZE//7244K
		 
		  #define FONT_A_ADDRESS                                  (IMG_A_ADDRESS+IMG_A_ADDRESS_SIZE)
		  #define FONT_A_ADDRESS_SIZE                             (2360*1024)

		  #define APPICON_PIC_ADDRESS							   (FONT_A_ADDRESS + FONT_A_ADDRESS_SIZE)
		  #define APPICON_PIC_ADDRESS_SIZE						   (160*1024)
	  #elif ENUM_PROJECT_NAME_N65A_GLOBAL

		  #define APP_CODE_A_ADDRESS								 ZH_EXCEL_FLASH_PART10_BASE_ADDR
		  #define APP_CODE_A_ADDRESS_SIZE 					     (5448*1024)//ZH_EXCEL_FLASH_PART10_SIZE//5448k

		  #define IMG_A_ADDRESS								      (APP_CODE_A_ADDRESS+APP_CODE_A_ADDRESS_SIZE)
		  #define IMG_A_ADDRESS_SIZE								  (7244*1024)//ZH_EXCEL_FLASH_PART11_SIZE//7244K

		 
		  #define FONT_A_ADDRESS                                  (IMG_A_ADDRESS+IMG_A_ADDRESS_SIZE)
		  #define FONT_A_ADDRESS_SIZE                             (2520*1024)
	 #else

		 #define APP_CODE_A_ADDRESS                             ZH_EXCEL_FLASH_PART10_BASE_ADDR
		 #define APP_CODE_A_ADDRESS_SIZE                        ZH_EXCEL_FLASH_PART10_SIZE//5020k

		 #define IMG_A_ADDRESS                                  ZH_EXCEL_FLASH_PART11_BASE_ADDR
		 #define IMG_A_ADDRESS_SIZE                             ZH_EXCEL_FLASH_PART11_SIZE//7404K

		 
		 #define FONT_A_ADDRESS                                  ZH_EXCEL_FLASH_PART12_BASE_ADDR
		 #define FONT_A_ADDRESS_SIZE                             ZH_EXCEL_FLASH_PART12_SIZE//2748K
	 #endif
#endif

#define OTA_STATE_A_ADDRESS                             ZH_EXCEL_FLASH_PART13_BASE_ADDR
#define OTA_STATE_A_ADDRESS_SIZE                        ZH_EXCEL_FLASH_PART13_SIZE//4K


#define BUS_FLASH_START_ADDR1                          ZH_EXCEL_FLASH_PART14_BASE_ADDR
#define USER_DATA_FLASH_AREA_SIZE1                     ZH_EXCEL_FLASH_PART14_SIZE//1056KB

#define CODE_BACK_START_ADDRESS				            ZH_EXCEL_FLASH_PART22_BASE_ADDR
#define CODE_BACK_SIZE						            ZH_EXCEL_FLASH_PART22_SIZE // 3400K
		

#define B_FLASH_RING_ADDRESS                            ZH_EXCEL_FLASH_PART23_BASE_ADDR
#define B_FLASH_RING_ADDRESS_SIZE                       ZH_EXCEL_FLASH_PART23_SIZE//400K|1000K


#define BUS_FLASH_START_ADDR2                           ZH_EXCEL_FLASH_PART24_BASE_ADDR
#define USER_DATA_FLASH_AREA_SIZE2                      ZH_EXCEL_FLASH_PART24_SIZE//1580|980



#define B_FLASH_APP_DB_ADDRESS                          ZH_EXCEL_FLASH_PART25_BASE_ADDR
#define B_FLASH_APP_DB_ADDRESS_SIZE                     ZH_EXCEL_FLASH_PART25_SIZE//152K
	

#define BOOT_COPY_CODE_START_ADDRESS				    ZH_EXCEL_FLASH_PART26_BASE_ADDR
#define BOOT_COPY_CODE_SIZE						        ZH_EXCEL_FLASH_PART26_SIZE // 260K


	
#define B_FLASH_DIAL_PUSH_A_START_ADDRESS	            ZH_EXCEL_FLASH_PART27_BASE_ADDR
#define B_FLASH_DIAL_PUSH_TOTAL_SIZE		            ZH_EXCEL_FLASH_PART27_SIZE // 2400K


//user one

#define SPORT_DATA_START_ADDRESS					(BUS_FLASH_START_ADDR1 + 0)
#define SPORT_DATA_TOTAL_SIZE						 0x64000 // 400K
	
	
#define GPS_DOT_DATA_START_ADDRESS					  (SPORT_DATA_START_ADDRESS + SPORT_DATA_TOTAL_SIZE)
#define GPS_DOT_DATA_TOTAL_SIZE 					  0x50000 // 320K
	
#pragma region gps_dot_region
#define trace_gps_buffer_address					 (0x000000)
#define trace_gps_buffer_size						 (GPS_DOT_DATA_TOTAL_SIZE)
#pragma endregion /* gps_dot_region */
	
#define DAILY_POINT_DATA_START_ADDRESS				  (GPS_DOT_DATA_START_ADDRESS + GPS_DOT_DATA_TOTAL_SIZE)
#define DAILY_POINT_DATA_SIZE						   0x44000 // 272K
	
 #if (DAILY_POINT_DATA_START_ADDRESS + DAILY_POINT_DATA_SIZE) >(BUS_FLASH_START_ADDR1+USER_DATA_FLASH_AREA_SIZE1)
 // #error "fw flash over_flow_two"
 #endif 
//remain 56k


#if ENUM_PROJECT_NAME_N65A_INDIA

  #define  NVMS_GPS_LTO_DATA_START_ADDRESS			   (BUS_FLASH_START_ADDR2+0)	//GPS LTO 400K
  #define  NVMS_GPS_LTO_DATA_TOTAL_SIZE				   0//
  //temp
  #define  NVMS_GPS_RAM_DATA_START_ADDRESS			   (NVMS_GPS_LTO_DATA_START_ADDRESS + NVMS_GPS_LTO_DATA_TOTAL_SIZE)	 //GPS RAM 200K
  #define  NVMS_GPS_RAM_DATA_TOTAL_SIZE				    0
 
  #define  FLASH_MIWEAR_SENSOR_DATA_PART_START           (NVMS_GPS_RAM_DATA_START_ADDRESS + NVMS_GPS_RAM_DATA_TOTAL_SIZE)
  #define  FLASH_MIWEAR_SENSOR_DATA_PART_SIZE             0x29000//164K   //0x36000 // 216K (128+88)//do not delete
#else
  #define  NVMS_GPS_LTO_DATA_START_ADDRESS			  (BUS_FLASH_START_ADDR2+0)	//GPS LTO 400K
  #define  NVMS_GPS_LTO_DATA_TOTAL_SIZE				   0x63000//396K
 //temp
  #define  NVMS_GPS_RAM_DATA_START_ADDRESS			    (NVMS_GPS_LTO_DATA_START_ADDRESS + NVMS_GPS_LTO_DATA_TOTAL_SIZE)	 //GPS RAM 200K
  #define  NVMS_GPS_RAM_DATA_TOTAL_SIZE				     0x33000//204K

  #define  FLASH_MIWEAR_SENSOR_DATA_PART_START           (NVMS_GPS_RAM_DATA_START_ADDRESS + NVMS_GPS_RAM_DATA_TOTAL_SIZE)
  #define  FLASH_MIWEAR_SENSOR_DATA_PART_SIZE             0x29000//164K   //0x36000 // 216K (128+88)//do not delete
#endif
	

#define  SLEEP_DATA_START_ADDRESS					  (FLASH_MIWEAR_SENSOR_DATA_PART_START + FLASH_MIWEAR_SENSOR_DATA_PART_SIZE)
#define  SLEEP_DATA_SIZE 							   0x4B000 // 300K 

#define  MANUAL_MEASURE_DATA_START_ADDRESS			  (SLEEP_DATA_START_ADDRESS + SLEEP_DATA_SIZE)
#define  MANUAL_MEASURE_DATA_SIZE					   0x2000  // 8K

#define  ABN_RECORD_DATA_START_ADDRESS				  (MANUAL_MEASURE_DATA_START_ADDRESS + MANUAL_MEASURE_DATA_SIZE)
#define  ABN_RECORD_DATA_SIZE						   0x2000  // 8K

#define  BACKUP_AREA_START_ADDRESS					  (ABN_RECORD_DATA_START_ADDRESS + ABN_RECORD_DATA_SIZE)
#define  BACKUP_AREA_TOTAL_SIZE						   0x2000  // 8K


#define  FACTORY_DATA_START_ADDRESS					  (BACKUP_AREA_START_ADDRESS + BACKUP_AREA_TOTAL_SIZE)
#define  FACTORY_DATA_TOTAL_SIZE 					   0x1A000 // 104K

#define factory_test_data_start                      	0
#define factory_test_data_size                        	0x8000             //32k

#define factory_Three_tuple_start                     	(factory_test_data_start + factory_test_data_size)
#define factory_Three_tuple_size                       	0x1000             //36k

#define factory_SN_number_start                     	(factory_Three_tuple_start + factory_Three_tuple_size)
#define factory_SN_number_size                       	0x1000             //40k

#define factory_PCBASN_number_start                     (factory_SN_number_start + factory_SN_number_size)
#define factory_PCBASN_number_size                      0x1000             //44k

#define factory_fire_version_start				    	(factory_PCBASN_number_start + factory_PCBASN_number_size)
#define factory_fire_version_size				    	0x1000				//48K

#define factory_Reserved_flag_start				    	(factory_fire_version_start + factory_fire_version_size)
#define factory_Reserved_flag_size				    	0x1000				//44K

#define factory_model_id_start					    	(factory_Reserved_flag_start + factory_Reserved_flag_size)
#define factory_model_id_size					    	0x1000				//52K

#define factory_R_code_start					        (factory_model_id_start + factory_model_id_size)
#define factory_R_code_size						        0x1000				//56K

#define factory_MAKE_YEAR_start					        (factory_R_code_start + factory_R_code_size)
#define factory_MAKE_YEAR_size						    0x1000				//60K

#define factory_flash_read_write_start				    (factory_MAKE_YEAR_start + factory_MAKE_YEAR_size)
#define factory_flash_read_write_size					0x1000				//64K


#define factory_other_data_start				        (factory_flash_read_write_start + factory_flash_read_write_size)
#define factory_other_data_size					        0x1000              //68K

	//存储产测中sar校准值（用户模式不可修改）
#define factory_sar_adjust_data_start			        (factory_other_data_start + factory_other_data_size)
#define factory_sar_adjust_data_size			        0x1000              //72K


#define Save_ACC_calibrate_start						(factory_sar_adjust_data_start + factory_sar_adjust_data_size)
#define Save_ACC_calibrate_size							0x1000              //76K


#define factory_BIS_info_data_start				        (Save_ACC_calibrate_start + Save_ACC_calibrate_size)
#define factory_BIS_info_data_size				        0x1000              //80K


#define factory_debug_log_start                         (factory_BIS_info_data_start + factory_BIS_info_data_size)
#define factory_debug_log_size                          0x3000              //88K


#define factory_SKU_start					        	(factory_debug_log_start + factory_debug_log_size)
#define factory_SKU_size						   		 0x1000				//92K


#define factory_Three_tuple_start_back                  factory_test_data_start + 0x19000   //备份在产测数据的最后4kflash上
#define factory_Three_tuple_size_back                   0x1000             //100k

#if (factory_Three_tuple_start_back + factory_Three_tuple_size_back) >(FACTORY_DATA_TOTAL_SIZE)
  #error "fw flash over_flow_two_factory"
#endif

#define user_information_data_start                   (FACTORY_DATA_START_ADDRESS + FACTORY_DATA_TOTAL_SIZE)
#define user_information_data_size                    0x14000 // 80k


#define  USER_DATA_START_ADDRESS 					  (user_information_data_start + user_information_data_size)
#define  USER_DATA_TOTAL_SIZE						   0x4a000//296k  //0x5b000 //364K


#pragma region user_flash_save_h

#define user_account_band_data_start                  0x00
#define user_account_band_data_size                   0x1000 // 4k

#define Miware_data_recode_start                      (user_account_band_data_start + user_account_band_data_size)
#define Miware_data_recode_size                       0x3000 // 12k

#define battery_info_data_save_start                  (Miware_data_recode_start + Miware_data_recode_size)
#define battery_info_data_save_size                   0x1000 //4k

#define daily_struct_data_write_start                 (battery_info_data_save_start + battery_info_data_save_size)
#define daily_struct_data_write_size                  0x5000 // 20k

#define daily_local_sleep_data_start                  (daily_struct_data_write_start + daily_struct_data_write_size) 
#define daily_local_sleep_data_size                   0x2000 // 8k

#define alipay_data_save_start                        (daily_local_sleep_data_start + daily_local_sleep_data_size)
#define alipay_data_save_size                         0x1000 // 4k

#define sport_record_save_data_start                  (alipay_data_save_start + alipay_data_save_size)
#define sport_record_save_data_size                   0x1c000 //0x1b800//112k 20个99K

#define supplement_of_sports_data_start               (sport_record_save_data_start + sport_record_save_data_size)
#define supplement_of_sports_data_size                0x3000 // 12k

#define user_daily_data_start                         (supplement_of_sports_data_start + supplement_of_sports_data_size)
#define user_daily_data_size                          0x2000 //8k

	//用作log head
#define system_log_head_start				     	  (user_daily_data_start + user_daily_data_size)
#define system_log_head_start_size				 	  0x1000				//4K


	//用作ota font res full check
#define ota_res_system_log_head_start				  (system_log_head_start + system_log_head_start_size)//2C000
#define ota_res_system_log_head_start_size			  0x1000				//4K

	//用作connect new phone
#define connect_new_phone_flag_head_start			  (ota_res_system_log_head_start + ota_res_system_log_head_start_size)//2C000
#define connect_new_phone_flag_start_size			  0x1000				//4K

	//用作log head
#define sasert_system_log_head_start				   (connect_new_phone_flag_head_start + connect_new_phone_flag_start_size)//2C000
#define sasert_system_log_head_start_size			   0x1000				//4K

//用作Monkey test
#define sasert_system_monkey_test_start				   (sasert_system_log_head_start + sasert_system_log_head_start_size)//2C000
#define sasert_system_monkey_test_size			   0x1000				//4K

#define wxcodepay_data_save_start    					(sasert_system_monkey_test_start+sasert_system_monkey_test_size)
#define wxcodepay_data_save_size     					0x1000 // 4k


#define save_reset_counter_start    					(wxcodepay_data_save_start+wxcodepay_data_save_size)
#define save_reset_counter_size     					0x1000 // 4k

#define sys_time_zone_data_save_start                 (save_reset_counter_start + save_reset_counter_size)
#define sys_time_zone_data_save_size                  (0x1000)    // 4k


#define zh_sys_ota_use_data_save_start                 (sys_time_zone_data_save_start + sys_time_zone_data_save_size)
#define zh_sys_ota_use_data_save_size                  (0x1000)    // 4k

#define sys_poweroff_timestamp_data_save_start         (zh_sys_ota_use_data_save_start + zh_sys_ota_use_data_save_size)
#define sys_poweroff_timestamp_data_save_size          (0x1000)    // 4k

#define buried_point_sys_data_save_start               (sys_poweroff_timestamp_data_save_start + sys_poweroff_timestamp_data_save_size)
#define buried_point_sys_data_save_size                (0x1000)    // 4k

#define app_weather_data_save_start                    (buried_point_sys_data_save_start + buried_point_sys_data_save_size)
#define app_weather_data_save_size                     (0x4000)    // 16k

#define app_photo_bg_data_save_start                    (app_weather_data_save_start + app_weather_data_save_size)
#define app_photo_bg_data_save_size                     (0x1000)    // 4k
#define USER_FLASH_CUR_MAX_END_ADDR                   (app_photo_bg_data_save_start + app_photo_bg_data_save_size)

#define user_flash_max_address                        USER_DATA_TOTAL_SIZE
#define user_use_max_address                          (USER_FLASH_CUR_MAX_END_ADDR)

#pragma endregion


#if (user_use_max_address > user_flash_max_address)
	    #error "user flash over_flow"
#endif




#if (USER_DATA_START_ADDRESS + USER_DATA_TOTAL_SIZE) >(BUS_FLASH_START_ADDR2+USER_DATA_FLASH_AREA_SIZE2)
  //#error "fw flash over_flow_flash_two_size"
#endif

#endif

#endif
