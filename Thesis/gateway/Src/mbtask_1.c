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

/* Shared Variable ----------------------------------*/
uint8_t test;
char publish_buffer[100];
char pub[10];
static uint8_t count = 0;
static uint8_t SUM_DEV0 = 0;

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

/* Private variables ---------------------------------------------------------*/

#define M_REG_HOLDING_START            1
#define M_REG_HOLDING_NREGS            65000

#define M_REG_INPUT_START              1
#define M_REG_INPUT_NREGS             65000

#define M_REG_COIL_START               1
#define M_REG_COIL_NREGS              65000

#define M_REG_DISCRETE_START           1
#define M_REG_DISCRETE_NREGS          65000

/********************************************************************************-*/
extern data1_t table1[] =   // CHANNEL 1
{
		0,	2,	3,	0,  "CH1_SEN2_TEMP",	"number",		"Temperature",
		0,	2, 	3,  1, 	"CH1_SEN2_HUMD", 	"number",		"Humidity",
		0,	2,	3,	2,	"CH1_INV2_POWR",	"number",		"Power",
		0,	2,	3,	3,	"CH1_SEN1_LUME",	"number",		"Lumen",
		0,	2,	3,	4,	"CH1_INV1_CURR",	"number",		"Current",
		0,	2,	3,	5,	"CH1_INV1_VOLT",	"number",		"Voltage",
		0,	2,  3, 	6,	"CH1_INV1_POWR",	"number",		"Power",
		0,	10,	6,	8,	"CH1_INV1_FAN",		"number",		"Fan",
		0,	10,	6,	7,	"CH1_INV3_FAN",		"number",		"Fan",
		0,	10,	6,	6,	"CH1_NODE1_REL1",	"boolean",		"Light",
		0,	10,	6,	5,	"CH1_NODE1_REL2",	"boolean",		"Light",
		0,	10,	6,	4,	"CH1_NODE1_REL3",	"boolean",		"Light",
		0,	10,	6,	3,	"CH1_INV1_FAN",		"number",		"Fan",
		0,	10,	6,	2,	"CH1_INV3_FAN",		"number",		"Fan",
		0,	10,	6,	1,	"CH1_NODE1_REL1",	"boolean",		"Light",
		0,	10,	6,	10,	"CH1_NODE1_REL2",	"boolean",		"Light",
		0,	10,	6,	9,	"CH1_NODE1_REL3",	"boolean",		"Light"
//		0,	2, 	3,	7,	"CH1_INV1_RPOWR",	"number",		"React Power",
//		0,	2,	3,	8,	"CH1_SEN1_HUMD",	"number",		"Humidity",
//		0,	2,	3,	9,	"CH1_INV1_POWR",	"number",		"Power",
//		0,	2,	3,	10, "CH1_SEN2_TEMP",	"number",		"Temperature",
//		0,	2, 	3,  11, "CH1_SEN2_HUMD",	"number", 		"Humidity",
//		0,	2,	3,	12,	"CH1_INV2_POWR",	"number", 		"Power",
//		0,	2,	3,	13,	"CH1_SEN1_LUME",	"number",		"Lumen",
//		0,	2,	3,	14,	"CH1_INV1_CURR",	"number",		"Current",
//		0,	2,	3,	15,	"CH1_INV1_VOLT",	"number",		"Voltage",
//		0,	2,  3, 	16,	"CH1_INV1_POWR",	"number",		"Power",
//		0,	2, 	3,	17,	"CH1_INV1_RPOWR",	"number",		"React Power",
//		0,	2,	3,	18,	"CH1_SEN1_HUMD",	"number",		"Humidity",
//		0,	2,	3,	19,	"CH1_INV1_POWR",	"number",		"Power",
//		0,	6,	3,	0,  "CH2_SEN2_TEMP",	"number",		"Temperature",
//		0,	6, 	3,  1, 	"CH2_SEN2_HUMD",	"number", 		"Humidity",
//		0,	6,	3,	2,	"CH2_INV2_POWR",	"number", 		"Power",
//		0,	6,	3,	3,	"CH2_SEN1_LUME",	"number",		"Lumen",
//		0,	6,	3,	4,	"CH2_INV1_CURR",	"number",		"Current",
//		0,	6,	3,	5,	"CH2_INV1_VOLT",	"number",		"Voltage",
//		0,	6,  3, 	6,	"CH2_INV1_POWR",	"number",		"Power",
//		0,	6, 	3,	7,	"CH2_INV1_RPOWR",	"number",		"React Power",
//		0,	6,	3,	8,	"CH2_SEN1_HUMD",	"number",		"Humidity",
//		0,	6,	3,	9,	"CH2_INV1_POWR",	"number",		"Power",
//		0,	6,	3,	10,  "CH2_SEN2_TEMP",	"number",		"Temperature",
//		0,	6, 	3,  11, "CH2_SEN2_HUMD",	"number", 		"Humidity",
//		0,	6,	3,	12,	"CH2_INV2_POWR",	"number", 		"Power",
//		0,	6,	3,	13,	"CH2_SEN1_LUME",	"number",		"Lumen",
//		0,	6,	3,	14,	"CH2_INV1_CURR",	"number",		"Current",
//		0,	6,	3,	15,	"CH2_INV1_VOLT",	"number",		"Voltage",
//		0,	6,  3, 	16,	"CH2_INV1_POWR",	"number",		"Power",
//		0,	6, 	3,	17,	"CH2_INV1_RPOWR",	"number",		"React Power",
//		0,	6,	3,	18,	"CH2_SEN1_HUMD",	"number",		"Humidity",
//		0,	6,	3,	19,	"CH2_INV1_POWR",	"number",		"Power",
//		0,	8,	3,	0,  "CH3_SEN2_TEMP",	"number",		"Temperature",
//		0,	8, 	3,  1, 	"CH3_SEN2_HUMD",	"number", 		"Humidity",
//		0,	8,	3,	2,	"CH3_INV2_POWR",	"number", 		"Power",
//		0,	8,	3,	3,	"CH3_SEN1_LUME",	"number",		"Lumen",
//		0,	8,	3,	4,	"CH3_INV1_CURR",	"number",		"Current",
//		0,	8,	3,	5,	"CH3_INV1_VOLT",	"number",		"Voltage",
//		0,	8,  3, 	6,	"CH3_INV1_POWR",	"number",		"Power",
//		0,	8, 	3,	7,	"CH3_INV1_RPOWR",	"number",		"React Power",
//		0,	8,	3,	8,	"CH3_SEN1_HUMD",	"number",		"Humidity",
//		0,	8,	3,	9,	"CH3_INV1_POWR",	"number",		"Power",
//		0,	8,	3,	10,  "CH3_SEN2_TEMP",	"number",		"Temperature",
//		0,	8, 	3,  11, "CH3_SEN2_HUMD",	"number", 		"Humidity",
//		0,	8,	3,	12,	"CH3_INV2_POWR",	"number", 		"Power",
//		0,	8,	3,	13,	"CH3_SEN1_LUME",	"number",		"Lumen",
//		0,	8,	3,	14,	"CH3_INV1_CURR",	"number",		"Current",
//		0,	8,	3,	15,	"CH3_INV1_VOLT",	"number",		"Voltage",
//		0,	8,  3, 	16,	"CH3_INV1_POWR",	"number",		"Power",
//		0,	8, 	3,	17,	"CH3_INV1_RPOWR",	"number",		"React Power",
//		0,	8,	3,	18,	"CH3_SEN1_HUMD",	"number",		"Humidity",
//		0,	8,	3,	19,	"CH3_INV1_POWR",	"number",		"Power",
};

/**************************************************************************************-*/

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
	eStatus = eMBMasterEnable(PORT3);
	eStatus = eMBMasterEnable(PORT4);
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
		Err = xQueueReceive(xQueueDownlinkHandle, &xQueueMbMqtt,portDEFAULT_WAIT_TIME);
		if (Err == pdPASS)
		{
			while (xQueueMbMqtt.mutex == 1)
			{
				SUM_DEV0 =  ((sizeof(table1))/(sizeof(data1_t)));
				device.channel = table1[count].port;
				device.id = table1[count].id;
				device.func = table1[count].func;
				device.regAdr = table1[count].reg_adr;
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
				if (count > (SUM_DEV0 - 1))
					count = 0;
				osDelay(500);
			}
		}
	}
}

/************************Master Callback Function for Holding Register****************************************************************************/
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
	//usAddress--;
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
//				printf("\r\n  data: %d ",xQueueMbMqtt.RegData.i16data);
//				printf("\r\n*****************\r\n");
			}
			break;
		}
		xQueueMbMqtt.countflag = count; // update count for device
		BaseType_t Err = pdFALSE;
		Err = xQueueSend(xQueueUplinkHandle, &xQueueMbMqtt,portDEFAULT_WAIT_TIME);
		if (Err == pdPASS) {
			} else {
			printf("\r\n Modbus_MQTT Up queued: False \r\n");
		}
		}
	else {
		eStatus = MB_ENOREG;
	}
	return eStatus;
}

uint16_t cal_sum_dev()
{
	return sizeof(table1)/sizeof(data1_t);
	}
