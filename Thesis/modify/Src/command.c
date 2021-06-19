#include <command.h>
#include "cmdline.h"
#include "usart.h"
#include "flash.h"
#include "FreeRTOS.h"
#include "main.h"
#include "param.h"
#include "lwip.h"
#include "socket.h"
#include "lwip/ip4_addr.h"
#include "modbus_mqtt_bridge.h"
#include "fatfs.h"
#include <stdlib.h>

extern network_param_t netParam;
extern network_param_t mqttHostParam;
extern osThreadId netFlashSave;
extern osThreadId defaultTaskHandle;
extern osSemaphoreId resetHandle;
extern osMessageQId xQueueResetHandle;
extern osMessageQId xQueueUplinkHandle;
extern int_to_byte netIdn[3];
extern osThreadId sdcardTask;

UART_HandleTypeDef huart6;

FATFS fs;
FIL fil;
FRESULT fresult;
char SDbuffer[200];
extern data1_t *dynamic;

uint32_t modbus_mutex;
uint32_t modbus_telemetry;
uint32_t timeDelay;;

int Cmd_off_mutex(int argc, char *argv[]);
int Cmd_set_modbusmutex(int argc, char *argv[]);
int Cmd_set_localip(int argc, char *argv[]);
int Cmd_set_mqttip(int argc, char *argv[]);
int Cmd_set_id(int argc, char *argv[]);
int Cmd_save(int argc, char *argv[]);
int Cmd_set_localgw(int argc, char *argv[]);
int Cmd_set_netmask(int argc, char *argv[]);
int Cmd_set_url(int argc, char *argv[]);
int Cmd_send_provision(int argc, char *argv[]);
int Cmd_update_network(int argc, char *argv[]);
int Cmd_allocate_device(int argc, char *argv[]);
int Cmd_load_all(int argc, char *argv[]);
tCmdLineEntry g_psCmdTable[] = {
		{ "help", Cmd_help," : Display list of commands" },
		{ "setip", Cmd_set_localip," : Set static ip for brigde" },
		{ "setmqttip", Cmd_set_mqttip," : Set mqtt server ip for brigde" },
		{ "setid", Cmd_set_id," : Set mqtt server ip for brigde" },
		{ "save", Cmd_save," : Save all configuration to flash and reboot" },
		{ "setgateway", Cmd_set_localgw," : Set default gateway for board" },
		{ "setnetmask", Cmd_set_netmask," : Set netmask for board" },
		{ "test", Cmd_set_url," : Set ip server from url" },
		{ "sendprovision", Cmd_send_provision," : Send provision request" },
		{ "network", Cmd_update_network," : Update network" },
		{ "loadtable", Cmd_allocate_device," : Update network" },
		{ "load", Cmd_load_all," : Update network" },
		{ "setmutex", Cmd_set_modbusmutex," : Update network" },
		{ "offmutex", Cmd_off_mutex," : Send provision request" },
		{ 0, 0, 0 } };

const char * ErrorCode[4] = { "CMDLINE_BAD_CMD", "CMDLINE_TOO_MANY_ARGS",
		"CMDLINE_TOO_FEW_ARGS", "CMDLINE_INVALID_ARG" };

uint8_t commandBuffer[200];
uint32_t commandBufferIndex = 0;
uint32_t gotCommandFlag = 0;



void UARTIntHandler(void) {
	uint8_t receivedChar;
	uint32_t ui32Status;
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
		HAL_UART_Transmit(&huart6, EnterCMD, 3, 100);
	}

}
/*-----------------------------------------------------------------------------------------------*/
int Cmd_set_modbusmutex(int argc, char *argv[])
{
	printf("\nCmd_set_telemetry\r\n");
	printf("------------------\r\n");
	modbus_mutex = 1;
	uint32_t handle = 1;
	xQueueSend(xQueueResetHandle,&handle,portMAX_DELAY);
	}
/*-----------------------------------------------------------------------------------------------*/
int Cmd_off_mutex(int argc, char *argv[]) {
	printf("\nCmd_off_telemetry\r\n");
	printf("------------------\r\n");
	modbus_mutex = 0;
	uint32_t handle = 1;
	xQueueSend(xQueueResetHandle,&handle,portMAX_DELAY);
}
/*------------------------UPDATE NETWORK-----------------------------------------------------------------------------------*/
int Cmd_update_network(int argc, char *argv[])
{
	ip4_addr_t ip,netmask,gateway,mqtt;
	if (ipaddr_aton(*(argv + 1), &ip)) {
		netParam.ip.idata = ip.addr;
		printf("\r\n New IP: %d %d %d %d", netParam.ip.cdata[0],
				netParam.ip.cdata[1], netParam.ip.cdata[2],
				netParam.ip.cdata[3]);
	}
	if (ipaddr_aton(*(argv + 2), &netmask)) {
		netParam.netmask.idata = netmask.addr;
		printf("\r\n New netmask: %d %d %d %d", netParam.netmask.cdata[0],
				netParam.netmask.cdata[1],netParam.netmask.cdata[2],
				netParam.netmask.cdata[3]);
	}
	if (ipaddr_aton(*(argv + 3), &gateway)) {
		netParam.gateway.idata = gateway.addr;
		printf("\r\n New gateway: %d %d %d %d", netParam.gateway.cdata[0],
				netParam.gateway.cdata[1],netParam.gateway.cdata[2],
				netParam.gateway.cdata[3]);
	}
	if (ipaddr_aton(*(argv + 4), &mqtt)) {
		mqttHostParam.ip.idata = mqtt.addr;
		printf("\r\n New Broker IP: %d %d %d %d", mqttHostParam.ip.cdata[0],
				mqttHostParam.ip.cdata[1], mqttHostParam.ip.cdata[2],
				mqttHostParam.ip.cdata[3]);
	}
	}
/*************************SET IP FROM URL*************************************************************-*/
int Cmd_set_url(int argc, char *argv[])
{
	printf("\nCmd_test_dynamic\r\n");
	printf("------------------\r\n");

}
/*************************SEND PROVISION REQUEST*************************************************************-*/
int Cmd_send_provision(int argc, char *argv[])
{
	printf("\nCmd_send_provision\r\n");
	printf("------------------\r\n");
	xQueueMbMqtt_t xQueueMbMqtt;
	BaseType_t Err = pdFALSE;
	#define portDEFAULT_WAIT_TIME 1000
	xQueueMbMqtt.gotflagProvision = 1;
	uint16_t sum_dev =  28;
	xQueueMbMqtt.sum_dev = sum_dev;
	Err = xQueueSend(xQueueUplinkHandle, &xQueueMbMqtt,portDEFAULT_WAIT_TIME);
		if (Err == pdPASS) {
			xQueueMbMqtt.gotflagProvision = 0;
			}
		else {
		printf("\r\n Modbus_MQTT Up queued: False \r\n");
		}
}

/*--------------SAVE------------------------------------------------------------------------------*/
int Cmd_save(int argc, char *argv[]) {

	uint32_t handle = 1;
	xQueueSend(xQueueResetHandle,&handle,portMAX_DELAY);

}
/*-----------------------------------------------------------------------------------------------*/
int Cmd_set_mqttip(int argc, char *argv[]) {
	printf("\nCmd_set_mqttip\r\n");
	printf("------------------\r\n");
	ip4_addr_t mqtt;
	if (ipaddr_aton(*(argv + 1), &mqtt)) {
		mqttHostParam.ip.idata = mqtt.addr;
		printf("\r\n New Broker IP: %d %d %d %d", mqttHostParam.ip.cdata[0],
				mqttHostParam.ip.cdata[1], mqttHostParam.ip.cdata[2],
				mqttHostParam.ip.cdata[3]);
	} else {
		printf("\r\nInvalid param\r\n");

		printf("\r\n------------------\r\n");
		return 0;
	}
}
int Cmd_set_id(int argc, char *argv[]) {
	printf("\nCmd_set_id\r\n");
	printf("\r\n------------------\r\n");
//	HAL_UART_Transmit(&huart1, argv, argc, 100);
	//netId = atol(*(argv+1));
//	memcpy(netIdn, *(argv+1), 12);
	//printf("\r\n New net ID: %d",netId);
	printf("\r\n------------------\r\n");
	return 0;
}
int Cmd_help(int argc, char *argv[]) {
	tCmdLineEntry *pEntry;
//      HAL_UART_Transmit(&huart1, "\nAvailable commands\r\n", 1, 100);
// Print some header text.
	printf("\nAvailable commands\r\n");
	printf("------------------\r\n");

// Point at the beginning of the command table.
	pEntry = &g_psCmdTable[0];

// Enter a loop to read each entry from the command table.  The
// end of the table has been reached when the command name is NULL.
	while (pEntry->pcCmd) {
		// Print the command name and the brief description.
		printf("%s%s\n\r", pEntry->pcCmd, pEntry->pcHelp);

		// Advance to the next entry in the table.
		pEntry++;

	}
	printf("------------------\r\n");
// Return success.
	return (0);
}

/*************************Set Default Gateway**************************************************************-*/
int Cmd_set_localgw(int argc, char *argv[]) {
	printf("\nCmd_set_gateway\r\n");
	printf("------------------\r\n");
	ip4_addr_t gateway;
	if (ipaddr_aton(*(argv + 1), &gateway)) {
		netParam.gateway.idata = gateway.addr;
		printf("\r\n New gateway: %d %d %d %d", netParam.gateway.cdata[0],
				netParam.gateway.cdata[1],netParam.gateway.cdata[2],
				netParam.gateway.cdata[3]);
	} else {
		printf("\r\nInvalid param\r\n");
	}
	printf("\r\n------------------\r\n");
	return 0;
}
/*************************Set Netmask**************************************************************-*/
int Cmd_set_netmask(int argc, char *argv[]) {
	printf("\nCmd_set_netmask\r\n");
	printf("------------------\r\n");
	ip4_addr_t netmask;
	if (ipaddr_aton(*(argv + 1), &netmask)) {
		netParam.netmask.idata = netmask.addr;
		printf("\r\n New netmask: %d %d %d %d", netParam.netmask.cdata[0],
				netParam.netmask.cdata[1],netParam.netmask.cdata[2],
				netParam.netmask.cdata[3]);
	} else {
		printf("\r\nInvalid param\r\n");
	}
	printf("\r\n------------------\r\n");
	return 0;
}
int Cmd_set_localip(int argc, char *argv[]) {
	printf("\nCmd_set_localip\r\n");
	printf("------------------\r\n");
	ip4_addr_t ip;
	if (ipaddr_aton(*(argv + 1), &ip)) {
		netParam.ip.idata = ip.addr;
		printf("\r\n New IP: %d %d %d %d", netParam.ip.cdata[0],
				netParam.ip.cdata[1], netParam.ip.cdata[2],
				netParam.ip.cdata[3]);
	} else {
		printf("\r\nInvalid param\r\n");
	}
	printf("\r\n------------------\r\n");
	return 0;
}
int Cmd_load_all(int argc, char *argv[])
{
	printf("\nCmd_load_all\r\n");
	printf("------------------\r\n");
	uint32_t handle = 2;
	xQueueSend(xQueueResetHandle,&handle,portMAX_DELAY);
//		MX_FATFS_Init();
//		uint8_t line;
//	fresult = f_mount(&fs, "", 1);
//	fresult = f_open(&fil,"device.txt", FA_READ);
//	for (line = 0; (f_eof(&fil) == 0); line++)
//	{
//	   f_gets((char*)SDbuffer, sizeof(SDbuffer), &fil);
//	}
//	printf("\nNum of line: %d\r\n", line);
//	fresult = f_close(&fil);
//
//		dynamic = (data1_t*)calloc(line, sizeof(data1_t));
//		if (dynamic == NULL){
//			fresult = f_mount(&fs, "", 1);
//			fresult = f_open(&fil,"device.txt", FA_READ);
//			for (uint8_t i = 0; (f_eof(&fil) == 0); i++)
//			{
//			   memset(SDbuffer,0, sizeof(SDbuffer));
//			   f_gets((char*)SDbuffer, sizeof(SDbuffer), &fil);
//			   ptr = parse_device(SDbuffer, strlen(SDbuffer));
//			   addDevice((dynamic+i), ptr);
//			}
//			fresult = f_close(&fil);
//		}
//		else
//			 printf("\r\n FAIL IN LOADING DEVICE DATA FROM SD CARD, PLEASE CHECK SDCARD\r\n");
//
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
	for (uint8_t i = 0; i < 20; i++)
	{
//		   printf("\r\nDevice %d: %d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\t%s",i,(dynamic+i)->channel,(dynamic+i)->deviceID,(dynamic+i)->func,
//				   (dynamic+i)->deviceChannel,(dynamic+i)->devicestatus);
	   printf("\r\nDevice %d: %d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\t%s",i,(dynamic+i)->channel,(dynamic+i)->deviceID,(dynamic+i)->func,(dynamic+i)->devicestatus,
			   (dynamic+i)->deviceChannel,(dynamic+i)->deviceType,(dynamic+i)->deviceName,
			   (dynamic+i)->channeltitle,(dynamic+i)->valueType);
	}
	printf("\r\nADDRESS--------------------------------------------------------\r\n");
	for (uint8_t i = 0; i < 20; i++)
	{
//		   printf("\r\nDevice %d: %d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\t%s",i,&(dynamic+i)->channel,&(dynamic+i)->deviceID,&(dynamic+i)->func,
//				   &(dynamic+i)->deviceChannel,&(dynamic+i)->devicestatus);
		   printf("\r\nDevice %d: %d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",i,&(dynamic+i)->channel,&(dynamic+i)->deviceID,&(dynamic+i)->func,&(dynamic+i)->devicestatus,
				   &(dynamic+i)->deviceChannel,&(dynamic+i)->deviceType,&(dynamic+i)->deviceName,
				   &(dynamic+i)->channeltitle,&(dynamic+i)->valueType);
	}
}
void SdcardTask(void *arg) {

	for (uint8_t i = 0; i < 20; i++)
	{
	   printf("\r\nDevice %d: %d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\t%s",i,(dynamic+i)->channel,(dynamic+i)->deviceID,(dynamic+i)->func,
			   (dynamic+i)->deviceChannel,(dynamic+i)->devicestatus,(dynamic+i)->deviceType,(dynamic+i)->deviceName,
			   (dynamic+i)->channeltitle,(dynamic+i)->valueType);
	}
	vTaskDelay(100);
	while (1)
		;

}
void SdcardHandlerTask(void *arg)
{
	BaseType_t err = pdFALSE;
	uint32_t handle;
	while (1)
	{
		err = xQueueReceive(xQueueResetHandle, &handle, portMAX_DELAY);
		if (err == pdTRUE) {
			if (handle == 2) {
				osThreadDef(flashSave, SdcardTask, osPriorityRealtime,0, 4 * 128);
				sdcardTask = osThreadCreate(osThread(flashSave), NULL);
				osDelay(10);
			}
		}
		vTaskDelay(100);
	}
}
