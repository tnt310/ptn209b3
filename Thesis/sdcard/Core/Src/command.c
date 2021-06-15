#include <command.h>
#include "cmdline.h"
#include "sdcard.h"
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "stdlib.h"
#include "modbus_mqtt_bridge.h"

char SDbuffer[200];
UART_HandleTypeDef huart6;
FATFS fs;
FIL fil;
FRESULT fresult;
static data1_t *ptr;
data1_t *dynamic;
data1_t device;
static uint8_t line;

int Cmd_read_all(int argc, char *argv[]);
int Cmd_load_all(int argc, char *argv[]);

int Cmd_allocate_device(int argc, char *argv[]);
tCmdLineEntry g_psCmdTable[] = {

		{ "read", Cmd_read_all," : load data from sdcard" },
		{ "load", Cmd_load_all," : load data from sdcard" },
		{ "device",  Cmd_allocate_device," : load data from sdcard" },
		{ 0, 0, 0 } };

const char * ErrorCode[4] = { "CMDLINE_BAD_CMD", "CMDLINE_TOO_MANY_ARGS","CMDLINE_TOO_FEW_ARGS", "CMDLINE_INVALID_ARG" };

uint8_t commandBuffer[200];
uint32_t commandBufferIndex = 0;
uint32_t gotCommandFlag = 0;
uint8_t temp[100];

void UARTIntHandler(void) {
	uint8_t receivedChar;
	char *EnterCMD = "\r\n>";
	receivedChar = (uint8_t) ((huart6).Instance->DR & (uint8_t) 0x00FF);
	HAL_UART_Transmit(&huart6, &receivedChar, 1, 100);
	__HAL_UART_ENABLE_IT(&huart6, UART_IT_RXNE);
	if (receivedChar != 13) {
		if ((receivedChar == 8) || (receivedChar == 127)) {
			if (commandBufferIndex > 0)
				commandBufferIndex--;
		} else {
			commandBuffer[commandBufferIndex] = receivedChar;
			commandBufferIndex++;
		}
	} else {
		if (commandBufferIndex != 0) {
			commandBuffer[commandBufferIndex] = 0;
			commandBufferIndex = 0;
			gotCommandFlag = 1;
		}
		HAL_UART_Transmit(&huart6, (uint8_t*)EnterCMD, 3, 100);
	}

}
int Cmd_create_file(int argc, char *argv[])
{

	printf("\nCmd_create_file\r\n");
	printf("------------------\r\n");
	char *file = *(argv+1);
	SD_CREATE_FILE(file);
}
/*
 * 1. port
 * 2. ID
 * 3. function
 * 4. Register
 * 5. Device Type
 * 6. Device Name
 * 7. Device Title
 * 8. value type */
int Cmd_write_sdcard(int argc, char *argv[])
{
	printf("\nCmd_write_sdcard\r\n");
	printf("------------------\r\n");
	SDcard_t sd;
	char sd_temp[200];
	sd.port= atoi(*(argv+1));
	sd.deviceID = atoi(*(argv+2));
	sd.func = atoi(*(argv+3));
	sd.deviceChannel= atoi(*(argv+4));
	sd.deviceType= *(argv+5);
	sd.deviceName = *(argv+6);
	sd.deviceTitle= *(argv+7);
	sd.valueType= *(argv+8);
	sd.deviceStatus= atoi(*(argv+9));
	SD_Json(sd_temp,sd.port,sd.deviceID,sd.func,sd.deviceChannel,sd.deviceType,sd.deviceTitle,sd.deviceName,sd.valueType,sd.deviceStatus);
	printf("%s",sd_temp);
	SD_WRITE_LINE("DEVICE.txt",sd_temp);
}
int Cmd_read_sdcard(int argc, char *argv[])
{
	printf("\nCmd_read_sdcard\r\n");
	printf("------------------\r\n");
	SD_READ_LINE("DEVICE.txt");
	printf("%s",SDbuffer);
}
int Cmd_read_all(int argc, char *argv[])
{
	printf("\nCmd_read_all\r\n");
	printf("------------------\r\n");
	SD_READ_ALL("DEVICE.TXT");
}
int Cmd_load_all(int argc, char *argv[])
{
	printf("\nCmd_load_all\r\n");
	printf("------------------\r\n");
	fresult = f_mount(&fs, "", 1);
	fresult = f_open(&fil,"DEVICE.TXT", FA_READ|FA_WRITE);
	for (line = 0; (f_eof(&fil) == 0); line++)
	{
	   f_gets((char*)SDbuffer, sizeof(SDbuffer), &fil);
	}
	printf("\nNum of line: %d\r\n", line);
	fresult = f_close(&fil);

		dynamic = (data1_t*)calloc(line, sizeof(data1_t));
		fresult = f_mount(&fs, "", 1);
		fresult = f_open(&fil,"DEVICE.TXT", FA_READ|FA_WRITE);
		for (uint8_t i = 0; (f_eof(&fil) == 0); i++)
		{
		   memset(SDbuffer,0, sizeof(SDbuffer));
		   f_gets((char*)SDbuffer, sizeof(SDbuffer), &fil);
		   ptr = parse_device(SDbuffer, strlen(SDbuffer));
		   addDevice((dynamic+i), ptr);
		   printf("\r\nLine %d: %d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\t%s",i ,(ptr)->channel,(ptr)->deviceID,(ptr)->func,
				   (ptr)->deviceChannel,(ptr)->devicestatus,(ptr)->deviceType,(ptr)->deviceName,
		           (ptr)->channeltitle,(ptr)->valueType);
		}
		fresult = f_close(&fil);
		printf("\r\nALLOCATED DEVICE MEMORY--------------------------------------------------------\r\n");
//		for (uint8_t i = 0; i < line; i++)
//		{
//		   printf("\r\nDevice %d: %d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\t%s",i,(dynamic+i)->channel,(dynamic+i)->deviceID,(dynamic+i)->func,
//				   (dynamic+i)->deviceChannel,(dynamic+i)->devicestatus,(dynamic+i)->deviceType,(dynamic+i)->deviceName,
//				   (dynamic+i)->channeltitle,(dynamic+i)->valueType);
//		}
		printf("\nNum of line: %d\r\n", line);
		printf("\r\nADDRESS--------------------------------------------------------\r\n");
//		for (uint8_t i = 0; i < line; i++)
//		{
//			   printf("\r\nDevice %d: %d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",i,&(dynamic+i)->channel,&(dynamic+i)->deviceID,&(dynamic+i)->func,
//					   &(dynamic+i)->deviceChannel,&(dynamic+i)->devicestatus,&(dynamic+i)->deviceType,&(dynamic+i)->deviceName,
//					   &(dynamic+i)->channeltitle,&(dynamic+i)->valueType);
//		}
}
int Cmd_allocate_device(int argc, char *argv[])
{
	printf("\nCmd_allocate_device\r\n");
	printf("------------------\r\n");
	printf("\r\nALLOCATED DEVICE MEMORY--------------------------------------------------------\r\n");
	for (uint8_t i = 0; i < 28; i++)
	{
	   printf("\r\nDevice %d: %d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\t%s",i,(dynamic+i)->channel,(dynamic+i)->deviceID,(dynamic+i)->func,
			   (dynamic+i)->deviceChannel,(dynamic+i)->devicestatus,(dynamic+i)->deviceType,(dynamic+i)->deviceName,
			   (dynamic+i)->channeltitle,(dynamic+i)->valueType);
	}
	printf("\r\nADDRESS--------------------------------------------------------\r\n");
	for (uint8_t i = 0; i < 28; i++)
	{
		   printf("\r\nDevice %d: %d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",i,&(dynamic+i)->channel,&(dynamic+i)->deviceID,&(dynamic+i)->func,
				   &(dynamic+i)->deviceChannel,&(dynamic+i)->devicestatus,&(dynamic+i)->deviceType,&(dynamic+i)->deviceName,
				   &(dynamic+i)->channeltitle,&(dynamic+i)->valueType);
	}
}
