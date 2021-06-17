/*
 * sdcard.h
 *
 *  Created on: May 15, 2021
 *      Author: ACER
 */

#ifndef INC_SDCARD_H_
#define INC_SDCARD_H_

#include "fatfs.h"
#include "fatfs_sd.h"
#include "ff.h"

typedef struct{
	uint8_t deviceStatus;
	uint8_t port;
    uint8_t deviceID; // id : 01
    uint8_t func; // function code
    char *deviceChannel; // Adress reg (0x10)
    char *deviceType; // name of device  : INVERTER
    char *deviceTitle; // name of reg : POWER
    char *deviceName; // : INVERTER_01
    char *valueType;  // NUMBER or BOOLEAN
}SDcard_t;

uint8_t  SD_CREATE_FILE(char *filename);
uint8_t  SD_READ_LINE(char *filename);
uint8_t  SD_READ_ALL(char *filename);
uint8_t  SD_WRITE_LINE(char *filename, const TCHAR* data);
uint32_t SD_GET_FREESPACE(void);
uint8_t  SD_LOAD_ALL(char *filename);
uint8_t SD_Json(char buffer[200],uint8_t port,uint8_t deviceID,uint8_t func,char *deviceChannel,char *deviceType,char *deviceTitle,char *deviceName,char *valueType, uint8_t devicestatus);


#endif /* INC_SDCARD_H_ */
