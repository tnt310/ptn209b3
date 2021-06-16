#include <command.h>
#include "cmdline.h"
#include "sdcard.h"
#include <stdio.h>
#include "main.h"
#include "stdlib.h"

char SDbuffer[200];
uint16_t *dynamic;
data_t *table;
UART_HandleTypeDef huart6;
int Cmd_write_sdcard(int argc, char *argv[]);
int Cmd_read_sdcard(int argc, char *argv[]);
int Cmd_create_file(int argc, char *argv[]);
int Cmd_read_all(int argc, char *argv[]);
int Cmd_load_all(int argc, char *argv[]);

int Cmd_allocate_device(int argc, char *argv[]);
int Cmd_read_table(int argc, char *argv[]);
int Cmd_read_address(int argc, char *argv[]);
tCmdLineEntry g_psCmdTable[] = {
		{ "wsd", Cmd_write_sdcard," : put data to sdcard" },
		{ "rsd", Cmd_read_sdcard," : load data from sdcard" },
		{ "read", Cmd_read_all," : load data from sdcard" },
		{ "load", Cmd_load_all," : load data from sdcard" },
		{ "setsd", Cmd_create_file," : create new file" },
		{ "device",Cmd_allocate_device," : allcate memory and write data" },
		{ "table", Cmd_read_table," : read data from allcated memory" },
		{ "address", Cmd_read_address," : read data from allcated memory" },
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
	SD_LOAD_ALL("DEVICE.TXT");
}
/*----------------------------------------------------------------------------------------------------------------*/
int Cmd_allocate_device(int argc, char *argv[])
{
	printf("\nCmd_allocate_device\r\n");
	printf("------------------\r\n");
	table = calloc(10, sizeof(data_t));
	if (table != NULL){
		for (uint8_t i = 0; i < 10; i++){
			(table+i)->channel = i;
			(table+i)->deviceID = i * 2;
			(table+i)->func = 3;
			(table+i)->devicestatus = 0;
			(table+i)->deviceChannel = i * 10;
		}
	}
	for (uint8_t i = 0; i < 10; i++){
		printf("\r\nRow %d: %d\t%d\t%d\t%d\t%d", i,(table+i)->channel,(table+i)->deviceID ,(table+i)->func,(table+i)->devicestatus,(table+i)->deviceChannel);
	}
	}
int Cmd_read_table(int argc, char *argv[])
{
	printf("\nCmd_read_table\r\n");
	printf("------------------\r\n");
	for (uint8_t i = 0; i < 10; i++){
		printf("\r\nRow %d: %d\t%d\t%d\t%d\t%d", i,(table+i)->channel,(table+i)->deviceID ,(table+i)->func,(table+i)->devicestatus,(table+i)->deviceChannel);
	}
	}
int Cmd_read_address(int argc, char *argv[])
{
	printf("\nCmd_read_address\r\n");
	printf("------------------\r\n");
	for (uint8_t i = 0; i < 10; i++){
		printf("\r\nRow %d: %x\t%x\t%x\t%x\t%x", i,&(table+i)->channel,&(table+i)->deviceID ,&(table+i)->func,&(table+i)->devicestatus,&(table+i)->deviceChannel);
	}
	for (uint8_t i = 0; i < 10; i++){
		printf("\r\nRow %d: %d\t%d\t%d\t%d\t%d", i,&(table+i)->channel,&(table+i)->deviceID ,&(table+i)->func,&(table+i)->devicestatus,&(table+i)->deviceChannel);
	}
}
