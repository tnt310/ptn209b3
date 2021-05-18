#include <command.h>
#include "cmdline.h"
#include "sdcard.h"
#include <stdio.h>
#include "main.h"
#include "stdlib.h"

char SDbuffer[200];
UART_HandleTypeDef huart2;
int Cmd_write_sdcard(int argc, char *argv[]);
int Cmd_read_sdcard(int argc, char *argv[]);
int Cmd_create_file(int argc, char *argv[]);

tCmdLineEntry g_psCmdTable[] = {
		{ "wsd", Cmd_write_sdcard," : put data to sdcard" },
		{ "rsd", Cmd_read_sdcard," : load data from sdcard" },
		{ "setsd", Cmd_create_file," : create new file" },
		{ 0, 0, 0 } };

const char * ErrorCode[4] = { "CMDLINE_BAD_CMD", "CMDLINE_TOO_MANY_ARGS","CMDLINE_TOO_FEW_ARGS", "CMDLINE_INVALID_ARG" };

uint8_t commandBuffer[100];
uint32_t commandBufferIndex = 0;
uint32_t gotCommandFlag = 0;
uint8_t temp[100];

void UARTIntHandler(void) {
	uint8_t receivedChar;
	char *EnterCMD = "\r\n>";
	receivedChar = (uint8_t) ((huart2).Instance->DR & (uint8_t) 0x00FF);

	HAL_UART_Transmit(&huart2, &receivedChar, 1, 100);
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
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
		HAL_UART_Transmit(&huart2, EnterCMD, 3, 100);
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
	SD_Json(sd_temp,sd.port,sd.deviceID,sd.func,sd.deviceChannel,sd.deviceType,sd.deviceTitle,sd.deviceName,sd.valueType);
	printf("%s",sd_temp);
	SD_WRITE_LINE("DEVICE.txt",sd_temp);
	printf("\r\n------------------\r\n");
}


int Cmd_read_sdcard(int argc, char *argv[])
{
	printf("\nCmd_read_sdcard\r\n");
	printf("------------------\r\n");
}
