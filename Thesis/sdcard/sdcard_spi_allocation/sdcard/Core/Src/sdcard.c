/*
 * sd.c
 *
 *  Created on: May 15, 2021
 *      Author: ACER
 */

#include "sdcard.h"
#include "stdio.h"
#include "stdint.h"
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "modbus_mqtt_bridge.h"


FATFS fs;
FIL fil;
FRESULT fresult;
static data_t *ptr;

extern char SDbuffer[200];

uint16_t lines = 0;
uint8_t  SD_CREATE_FILE(char *filename)
{
	fresult = f_mount(&fs, "", 1);
	fresult = f_open(&fil,filename, FA_CREATE_ALWAYS|FA_WRITE);
	fresult = f_close(&fil);
}
/*-----------------------------------------------------------------------------------------*/
uint8_t  SD_READ_LINE(char *filename)
{
	memset(SDbuffer,0, sizeof(SDbuffer));
	fresult = f_mount(&fs, "", 1);
	fresult = f_open(&fil,filename, FA_READ|FA_WRITE);
	f_gets(SDbuffer,sizeof(SDbuffer), &fil);
	fresult = f_close(&fil);
}
/*-----------------------------------------------------------------------------------------*/
uint8_t  SD_READ_ALL(char *filename)
{
	uint16_t lines = 0;
	memset(SDbuffer,0, sizeof(SDbuffer));
	fresult = f_mount(&fs, "", 1);
	fresult = f_open(&fil,filename, FA_READ|FA_WRITE);
	for (lines = 0; (f_eof(&fil) == 0); lines++)
	{
	   memset(SDbuffer,0, sizeof(SDbuffer));
	   f_gets((char*)SDbuffer, sizeof(SDbuffer), &fil);
	   printf("%s\r",SDbuffer);
	}
	printf("%d lines in file\r\n", lines);
	fresult = f_close(&fil);
}
/*-----------------------------------------------------------------------------------------*/
uint8_t  SD_LOAD_ALL(char *filename)
{
//	uint16_t lines = 0;
//	memset(SDbuffer,0, sizeof(SDbuffer));
//	fresult = f_mount(&fs, "", 1);
//	fresult = f_open(&fil,filename, FA_READ|FA_WRITE);
//	for (lines = 0; (f_eof(&fil) == 0); lines++)
//	{
//	   memset(SDbuffer,0, sizeof(SDbuffer));
//	   f_gets((char*)SDbuffer, sizeof(SDbuffer), &fil);
//	   ptr = parse_device(SDbuffer, strlen(SDbuffer));
//	   printf("\r\nLine %d: %d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\t%s",lines,(ptr)->channel,(ptr)->deviceID,(ptr)->func,(ptr)->devicestatus,
//			   (ptr)->deviceChannel,(ptr)->deviceType,(ptr)->deviceName,
//	           (ptr)->channeltitle,(ptr)->valueType);
//	}
//	printf("\r\n%d lines in file\r\n", lines);
//	printf("\r\n----------------DEVICES VALUE WERE ADDED TO DYNAMIC ARRAY--------------------------------");
//	fresult = f_close(&fil);
}
/*-----------------------------------------------------------------------------------------*/
uint8_t  SD_WRITE_LINE(char *filename, const TCHAR* data)
{
	f_mount(&fs,"/", 1);
	f_open(&fil,filename, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
	f_puts(data, &fil);
	f_close(&fil);
}
/*-----------------------------------------------------------------------------------------*/
uint32_t  SD_GET_FREESPACE(void)
{
	FATFS *pfs;
	DWORD fre_clust;
	uint32_t total, free_space;
	f_getfree("", &fre_clust, &pfs);
	total = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
	free_space = (uint32_t)(fre_clust * pfs->csize * 0.5);
	return free_space;
}
uint8_t SD_Json(char buffer[200],uint8_t port,uint8_t deviceID,uint8_t func,uint16_t deviceChannel,char *deviceType,char *deviceTitle,char *deviceName,char *valueType, uint8_t devicestatus)
{
    memset(buffer,0,200);
    sprintf(buffer,"{\"PORT\":%d,\"ID\":%d,\"FC\":%d,\"CHANNEL\":%d,\"DEVICETYPE\":\"%s\",\"DEVICENAME\":\"%s\",\"CHANNELTITLE\":\"%s\",\"VALUETYPE\":\"%s\",\"DEVICESTATUS\":%d}\n",port,deviceID,func,deviceChannel,deviceType,deviceName,deviceTitle,valueType,devicestatus);
}
