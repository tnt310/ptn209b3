#include <command.h>
#include "cmdline.h"
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "stdlib.h"


extern osThreadId defaultTaskHandle;
extern osSemaphoreId resetHandle;
extern osMessageQId xQueueResetHandle;
extern osMessageQId xQueueUplinkHandle;

char SDbuffer[200];
UART_HandleTypeDef huart6;
static data1_t *ptr;
data1_t *dynamic;
data1_t device;
static uint8_t line;

int Cmd_set_allocation(int argc, char *argv[]);
int Cmd_read_all(int argc, char *argv[]);
int Cmd_load_all(int argc, char *argv[]);
int Cmd_allocate_device(int argc, char *argv[]);

tCmdLineEntry g_psCmdTable[] = {
		{ "read", Cmd_read_all," : load data from sdcard" },
		{ "allocation",  Cmd_set_allocation," : load data from sdcard" },
		{ "load", Cmd_load_all," : load data from sdcard" },
		{ "table",  Cmd_allocate_device," : load data from sdcard" },
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
//
int Cmd_read_all(int argc, char *argv[])
{
	printf("\nCmd_read_all\r\n");
	printf("------------------\r\n");
	//SD_READ_ALL("DEVICE.TXT");
}
int Cmd_load_all(int argc, char *argv[])
{
	printf("\nCmd_load_all\r\n");
	printf("------------------\r\n");
//	fresult = f_mount(&fs, "", 1);
//	fresult = f_open(&fil,"DEVICE.TXT", FA_READ|FA_WRITE);
//	for (line = 0; (f_eof(&fil) == 0); line++)
//	{
//	   f_gets((char*)SDbuffer, sizeof(SDbuffer), &fil);
//	}
//	printf("\nNum of line: %d\r\n", line);
//	fresult = f_close(&fil);
//
//		dynamic = (data1_t*)calloc(line, sizeof(data1_t));
//		fresult = f_mount(&fs, "", 1);
//		fresult = f_open(&fil,"DEVICE.TXT", FA_READ|FA_WRITE);
//		for (uint8_t i = 0; (f_eof(&fil) == 0); i++)
//		{
//		   memset(SDbuffer,0, sizeof(SDbuffer));
//		   f_gets((char*)SDbuffer, sizeof(SDbuffer), &fil);
//		   ptr = parse_device(SDbuffer, strlen(SDbuffer));
//		   addDevice((dynamic+i), ptr);
//		   printf("\r\nLine %d: %d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\t%s",i ,(ptr)->channel,(ptr)->deviceID,(ptr)->func,
//				   (ptr)->deviceChannel,(ptr)->devicestatus,(ptr)->deviceType,(ptr)->deviceName,
//		           (ptr)->channeltitle,(ptr)->valueType);
//		}
//		fresult = f_close(&fil);
//		printf("\r\nALLOCATED DEVICE MEMORY--------------------------------------------------------\r\n");
////		for (uint8_t i = 0; i < line; i++)
////		{
////		   printf("\r\nDevice %d: %d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\t%s",i,(dynamic+i)->channel,(dynamic+i)->deviceID,(dynamic+i)->func,
////				   (dynamic+i)->deviceChannel,(dynamic+i)->devicestatus,(dynamic+i)->deviceType,(dynamic+i)->deviceName,
////				   (dynamic+i)->channeltitle,(dynamic+i)->valueType);
////		}
//		printf("\nNum of line: %d\r\n", line);
//		printf("\r\nADDRESS--------------------------------------------------------\r\n");
////		for (uint8_t i = 0; i < line; i++)
////		{
////			   printf("\r\nDevice %d: %d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",i,&(dynamic+i)->channel,&(dynamic+i)->deviceID,&(dynamic+i)->func,
////					   &(dynamic+i)->deviceChannel,&(dynamic+i)->devicestatus,&(dynamic+i)->deviceType,&(dynamic+i)->deviceName,
////					   &(dynamic+i)->channeltitle,&(dynamic+i)->valueType);
////		}
}
int Cmd_allocate_device(int argc, char *argv[])
{
	printf("\nCmd_allocate_device\r\n");
	printf("------------------\r\n");
	printf("\r\nALLOCATED DEVICE MEMORY--------------------------------------------------------\r\n");
//	for (uint8_t i = 0; i < 28; i++)
//	{
//	   printf("\r\nDevice %d: %d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\t%s",i,(dynamic+i)->channel,(dynamic+i)->deviceID,(dynamic+i)->func,
//			   (dynamic+i)->deviceChannel,(dynamic+i)->devicestatus,(dynamic+i)->deviceType,(dynamic+i)->deviceName,
//			   (dynamic+i)->channeltitle,(dynamic+i)->valueType);
//	}
//	printf("\r\nADDRESS--------------------------------------------------------\r\n");
//	for (uint8_t i = 0; i < 28; i++)
//	{
//		   printf("\r\nDevice %d: %d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",i,&(dynamic+i)->channel,&(dynamic+i)->deviceID,&(dynamic+i)->func,
//				   &(dynamic+i)->deviceChannel,&(dynamic+i)->devicestatus,&(dynamic+i)->deviceType,&(dynamic+i)->deviceName,
//				   &(dynamic+i)->channeltitle,&(dynamic+i)->valueType);
//	}
}
int Cmd_set_allocation(int argc, char *argv[])
{
	printf("\nCmd_set_allocation\r\n");
	printf("------------------\r\n");
	uint32_t handle = 1;
	xQueueSend(xQueueResetHandle,&handle,portMAX_DELAY);
}
