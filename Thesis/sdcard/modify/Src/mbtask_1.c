/* Built-in C library includes ---------------*/
#include <param.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "main.h"
#include "sharedmem.h"
//#include "mb.h"
#include "mb_m.h"
#include "mbframe.h"
#include "mbport.h"
#include "mbconfig.h"
#include "param.h"
#include "flash.h"

/* Shared Variable ----------------------------------*/
uint8_t test;
char publish_buffer[100];
char pub[10];
static uint8_t count = 0;

osThreadId mbProtocolTask;
osThreadId mbAppTask;
osThreadId netPROVISIONTask; //HERE
osThreadId mbDownlinkTask;
extern osMessageQId xQueueDownlinkHandle;
extern osMessageQId xQueueUplinkHandle;
extern TIM_HandleTypeDef htim7;
extern osTimerId myTimer01Handle;
extern osMessageQId xQueueControlHandle;
extern osMessageQId xQueueMessageHandle;

extern data1_t *dynamic;
extern uint32_t modbus_mutex;
extern uint32_t timeDelay;
/* Private variables ---------------------------------------------------------*/

#define M_REG_HOLDING_START            1
#define M_REG_HOLDING_NREGS            65000

#define M_REG_INPUT_START              1
#define M_REG_INPUT_NREGS             65000

#define M_REG_COIL_START               1
#define M_REG_COIL_NREGS              65000

#define M_REG_DISCRETE_START           1
#define M_REG_DISCRETE_NREGS          65000

data_t table1[] =
{
		0,	2, 	3,  0x01, 	"INVERTER",		        "INVERTER_01",		"CURRENT",	    "NUMBER",
		0,	2,	3,	0x02,	"INVERTER",		        "INVERTER_01",		"POWER",	    "NUMBER",
        0,	2, 	3,  0x03, 	"INVERTER",		        "INVERTER_01",		"CURRENT",	    "NUMBER",
		0,	2,	3,	0x04,	"INVERTER",		        "INVERTER_01",		"POWER",	    "NUMBER",
};
/*----------------------------------------------------------------------------------------------------------------------------------*/

void ModbusRTUTask(void const *argument) {
	#define PORT_INF_DELAY 0
	osDelay(150);
	printf("\r\n ModbusRTUTask \r\n");
	BaseType_t xError;
	xQueueControl_t xQueueControl;
	uint8_t uiSysState;
	xQueueControl.xTask = mbProtocolTask;
	do {
		osDelay(10);
		xQueuePeek(xQueueMessageHandle, &uiSysState, 0);
	} while (uiSysState != SYS_MB_PROTOCOL);
	xQueueReceive(xQueueMessageHandle, &uiSysState, 0);
	printf("\r\n ModbusRTUTask Initing");
	eMBErrorCode eStatus = eMBMasterInit(MB_RTU, 1, 9600, MB_PAR_NONE);
	eStatus = eMBMasterEnable(PORT1);
	eStatus = eMBMasterEnable(PORT2);
	HAL_TIM_Base_Start_IT(&htim7);
	/*State control machine*/
	xQueueControl.xState = TASK_RUNNING;
	xQueueSend(xQueueControlHandle, &xQueueControl, 10);
	while (1) {
		eMBMasterPoll();
		vTaskDelay(1);
	}
}
/************************************************************************************************************************************-*/

void ModbusTestTask(void const *argument) {

	osDelay(100);
	printf("\r\n ModbusTestTask \r\n");
	BaseType_t xError;
	xQueueControl_t xQueueControl;
	uint8_t uiSysState;
	xQueueControl.xTask = mbAppTask;
	do {
		osDelay(10);
		xQueuePeek(xQueueMessageHandle, &uiSysState, 0);
	} while (uiSysState != SYS_MB_APP);
	xQueueReceive(xQueueMessageHandle, &uiSysState, 0);
	printf("\r\n ModbusTestTask: Starting");
	#define portDEFAULT_WAIT_TIME 1000
	BaseType_t Err = pdFALSE;
	xQueueMbMqtt_t xQueueMbMqtt;
	osDelay(500);
	eMBErrorCode eStatus = MB_ENOERR;
	xQueueControl.xState = TASK_RUNNING;
	xQueueSend(xQueueControlHandle, &xQueueControl, 10);
	#define MB_DEFAULT_TEST_NREG	0x01
	#define MB_DEFAULT_TEST_TIMEOUT  1
	device_t device;
	while (1) {
		while(modbus_mutex){
			device.channel = table1[count].channel;
								device.id = table1[count].deviceID;
								device.func = table1[count].func;
								device.regAdr = table1[count].deviceChannel;
								switch(device.channel)
								{
								case 0:
									switch(device.func)
									{
									case MB_FUNC_READ_HOLDING_REGISTER:
										eMBMasterReqReadHoldingRegister(device.channel, device.id, device.regAdr,MB_DEFAULT_TEST_NREG, MB_DEFAULT_TEST_TIMEOUT);
										break;
									}
								break;
								}
								count ++;
								if (count > (4 - 1)){
									count = 0;
									osDelay(1000 * 3);
								}
								osDelay(1000);
		}
	}
//	while (1) {
//		while(modbus_mutex){
//			for (uint8_t i = 0;i < 28; i++){
//				for (uint8_t j = 0; j < 28; j++){
//					if ((dynamic+j)->deviceID== (dynamic+i)->deviceID && (dynamic+i)->deviceID != (dynamic+i-1)->deviceID){
//		                count++;
//		                if (count == 1)
//		                    {
//		                        for (uint8_t z = 0; z < 28; z++)
//		                        {
//		                            if ((dynamic+z)->deviceID == (dynamic+j)->deviceID){
//		                            	device.channel = (dynamic+z)->channel;
//		                            	device.id = (dynamic+z)->deviceID;
//		                            	device.func = (dynamic+z)->func;
//		                            	device.regAdr = (dynamic+z)->deviceChannel;
//		                            	switch(device.channel)
//		                            	{
//		                            		case 0:
//		                            		switch(device.func)
//		                            		{
//		                            			case MB_FUNC_READ_HOLDING_REGISTER:
//		                            				eMBMasterReqReadHoldingRegister(device.channel, device.id, device.regAdr,MB_DEFAULT_TEST_NREG, MB_DEFAULT_TEST_TIMEOUT);
//		                            				break;
//		                            		}
//		                            		break;
//		                            	}
//		                            	osDelay(500);
//		                            }
//		                        }
//		                    }
//					}
//				}
//				count = 0;
//			}
//		}
//	}
}
/*--------------------------Master Callback Function for Holding Register---------------------------------------------------------------------------*/
eMBErrorCode eMBMasterRegHoldingCB(UCHAR ucPort, UCHAR * pucRegBuffer, USHORT usAddress,USHORT usNRegs, eMBRegisterMode eMode)
{
	eMBErrorCode eStatus = MB_ENOERR;
	USHORT iRegIndex;
	USHORT REG_HOLDING_START = M_REG_HOLDING_START;
	USHORT REG_HOLDING_NREGS = M_REG_HOLDING_NREGS;
	/* FreeRTOS variable*/
	xQueueMbMqtt_t xQueueMbMqtt;
	xQueueMbMqtt.PortID = ucPort;
	xQueueMbMqtt.NodeID = ucMBMasterGetDestAddress(ucPort);
	/* if mode is read, the master will write the received date to buffer. */
	usAddress--;
	xQueueMbMqtt.RegAdr.i8data[0] = (uint8_t)usAddress;
	xQueueMbMqtt.RegAdr.i8data[1] = (uint8_t)(usAddress >>8);
	if ((usAddress >= REG_HOLDING_START)&& ((uint8_t)usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS)) {
		iRegIndex = usAddress - REG_HOLDING_START;
		switch (eMode) {
		case MB_REG_READ:
			xQueueMbMqtt.FunC = MB_FUNC_READ_HOLDING_REGISTER;
			while (usNRegs > 0)
			{
				xQueueMbMqtt.RegData.i8data[1] = (*pucRegBuffer);  // High Byte
				xQueueMbMqtt.RegData.i8data[0] = *(pucRegBuffer + 1); // Low Byte
				iRegIndex++;
				usNRegs--;
				printf("\r\n  data telemetry: %d ",xQueueMbMqtt.RegData.i16data);
				printf("\r\n-------------\r\n");
			}
			break;
		}
//		xQueueMbMqtt.countflag = count; // update count for device
//		BaseType_t Err = pdFALSE;
//		Err = xQueueSend(xQueueUplinkHandle, &xQueueMbMqtt,portDEFAULT_WAIT_TIME);
//		if (Err == pdPASS) {
//			} else {
//			printf("\r\n Modbus_MQTT Up queued: False \r\n");
//		}
		}
//	else {
//		eStatus = MB_ENOREG;
//	}
	return eStatus;
}

