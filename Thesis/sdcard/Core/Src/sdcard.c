/*
 * sd.c
 *
 *  Created on: May 15, 2021
 *      Author: ACER
 */

#include "sdcard.h"
#include "stdio.h"
#include "stdint.h"

FATFS fs;
FIL fil;
FRESULT fresult;
extern char SDbuffer[200];

uint8_t  SD_CREATE_FILE(char *filename)
{
	fresult = f_mount(&fs, "/", 1);
	fresult = f_open(&fil,filename, FA_CREATE_ALWAYS|FA_WRITE);
	fresult = f_close(&fil);
}
uint8_t  SD_READ_LINE(char *filename)
{
	memset(SDbuffer,0, sizeof(SDbuffer));
	fresult = f_mount(&fs, "/", 1);
	fresult = f_open(&fil,filename, FA_READ|FA_WRITE);
	f_gets(SDbuffer,sizeof(SDbuffer), &fil);
	fresult = f_close(&fil);
}
uint8_t  SD_WRITE_LINE(char *filename, const TCHAR* data)
{
	f_mount(&fs,"/", 1);
	f_open(&fil,filename, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
	f_puts(data, &fil);
	f_close(&fil);
}
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
uint8_t SD_Json(char buffer[200],uint8_t port,uint8_t deviceID,uint8_t func,uint16_t deviceChannel,char *deviceType,char *deviceTitle,char *deviceName,char *valueType)
{
    memset(buffer,0,200);
    sprintf(buffer,"{\"PORT\":%d,\"ID\":%d,\"FC\":%d,\"CHANNEL\":%d,\"DEVICETYPE\":\"%s\",\"DEVICENAME\":\"%s\",\"CHANNELTITLE\":\"%s\",\"VALUETYPE\":\"%s\"}\n",port,deviceID,func,deviceChannel,deviceType,deviceName,deviceTitle,valueType);
}
