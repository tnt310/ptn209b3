/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdint.h"
#include "stdio.h"
#include <stdlib.h>
#include "rtc.h"
#include "usart.h"
#include <command.h>
#include "cmdline.h"
#include "fatfs.h"
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
/* Shared variables ------------------*/

FATFS fs;
FIL fil;
FRESULT fresult;
char SDbuffer[200];

static data1_t *ptr;
data1_t *dynamic;

extern osThreadId mbProtocolTask;
extern osThreadId mbAppTask;
extern osThreadId netPROVISIONTask; // HERE
extern osThreadId netSIMTask;  // HERE
extern osThreadId mbDownlinkTask; // HERE
extern osThreadId netTimeTask;
extern osThreadId netHTTPTask;
extern osThreadId netMQTTTask;
extern osThreadId netTcpEchoTask;
osThreadId resetHandlerTask;
osThreadId flashTask;
extern uint32_t gotCommandFlag;
extern uint8_t commandBuffer[200];
extern uint32_t commandBufferIndex;

osMessageQId xQueueControlHandle;
osMessageQId xQueueMessageHandle;
osMessageQId xQueueDownlinkHandle;
osMessageQId xQueueUplinkHandle;
osMessageQId xQueueResetHandle;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osTimerId myTimer01Handle;
osSemaphoreId netMqttIpSemaphoreHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
extern void ModbusRTUTask(void const * argument);
extern void ModbusTestTask(void const * argument);
extern void ModbusDownlinkTask(void const * argument); //HERE
extern void http_server_netconn_init();
extern void NetworkTimeTask(void const *arg);
extern void TcpDiscoverTask(void *arg);
extern void http_server_netconn_thread();
extern void netmqttTask(void const *arg);
extern void netsimTask(void const *arg); // HERE
extern void ProvisionTestTask(void const *arg); // HERE
void SdcardLoadDevice(char *buffer, uint8_t count);
void ResetHandlerTask(void *arg);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void Callback01(void const * argument);

extern void MX_LWIP_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* Hook prototypes */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);
void vApplicationMallocFailedHook(void);
void vApplicationDaemonTaskStartupHook(void);

/* USER CODE BEGIN 4 */
__weak void vApplicationStackOverflowHook(xTaskHandle xTask,
		signed char *pcTaskName) {
	/* Run time stack overflow checking is performed if
	 configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
	 called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN 5 */
__weak void vApplicationMallocFailedHook(void) {
	/* vApplicationMallocFailedHook() will only be called if
	 configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
	 function that will get called if a call to pvPortMalloc() fails.
	 pvPortMalloc() is called internally by the kernel whenever a task, queue,
	 timer or semaphore is created. It is also called by various parts of the
	 demo application. If heap_1.c or heap_2.c are used, then the size of the
	 heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	 FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	 to query the size of free heap space that remains (although it does not
	 provide information on how the remaining heap might be fragmented). */
}
/* USER CODE END 5 */

/* USER CODE BEGIN DAEMON_TASK_STARTUP_HOOK */
void vApplicationDaemonTaskStartupHook(void) {
}
/* USER CODE END DAEMON_TASK_STARTUP_HOOK */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
		StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
	*ppxIdleTaskStackBuffer = &xIdleStack[0];
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
	/* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
		StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize) {
	*ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
	*ppxTimerTaskStackBuffer = &xTimerStack[0];
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
	/* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of netMqttIpSemaphore */
  osSemaphoreDef(netMqttIpSemaphore);
  netMqttIpSemaphoreHandle = osSemaphoreCreate(osSemaphore(netMqttIpSemaphore), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of myTimer01 */
  osTimerDef(myTimer01, Callback01);
  myTimer01Handle = osTimerCreate(osTimer(myTimer01), osTimerPeriodic, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */

	osMessageQDef(xQueueControl, 1, xQueueControl_t);
	xQueueControlHandle = osMessageCreate(osMessageQ(xQueueControl), NULL);

	osMessageQDef(xQueueMessage, 1, uint8_t);
	xQueueMessageHandle = osMessageCreate(osMessageQ(xQueueMessage), NULL);

	osMessageQDef(xQueueDownlink, 1, xQueueMbMqtt_t);
	xQueueDownlinkHandle = osMessageCreate(osMessageQ(xQueueDownlink), NULL);

	osMessageQDef(xQueueUplink, 1, xQueueMbMqtt_t);
	xQueueUplinkHandle = osMessageCreate(osMessageQ(xQueueUplink), NULL);

	osMessageQDef(xQueueReset, 1, sizeof(uint32_t));
	xQueueResetHandle = osMessageCreate(osMessageQ(xQueueUplink), NULL);

  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 512);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */

  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for LWIP */
	MX_LWIP_Init();
  /* USER CODE BEGIN StartDefaultTask */
	/*Create Task Modules in this line*/

	/*Modbus protocol stack*/
	osThreadDef(mbProtocolTask, ModbusRTUTask, osPriorityNormal, 0, 4 * 128);
	mbProtocolTask = osThreadCreate(osThread(mbProtocolTask), NULL);
	printf("\r\n MemFree: %d", xPortGetFreeHeapSize());

	/*Modbus app*/
	osThreadDef(mbAppTask, ModbusTestTask, osPriorityNormal, 0, 2 * 128);
	mbAppTask = osThreadCreate(osThread(mbAppTask), NULL);
	printf("\r\n MemFree: %d", xPortGetFreeHeapSize());

	/*Modbus Downlink */
	osThreadDef(mbDownlinkTask, ModbusDownlinkTask, osPriorityNormal, 0, 2 * 128);
	mbDownlinkTask= osThreadCreate(osThread(mbDownlinkTask), NULL);
	printf("\r\n MemFree: %d", xPortGetFreeHeapSize());

	/*Get time*/
	osThreadDef(netTimeTask, NetworkTimeTask, osPriorityNormal, 0, 4 * 128);
	netTimeTask = osThreadCreate(osThread(netTimeTask), NULL);
	printf("\r\n MemFree: %d", xPortGetFreeHeapSize());

	/*Tcp Server for CORE discovery*/
	osThreadDef(netTcpEchoTask, TcpDiscoverTask, osPriorityNormal, 0, 2 * 128);
	netTcpEchoTask = osThreadCreate(osThread(netTcpEchoTask), NULL);
	printf("\r\n MemFree: %d", xPortGetFreeHeapSize());

	/*MQTT serive*/
	osThreadDef(netMQTTTask, netmqttTask, osPriorityNormal, 0, 14 * 256);
	netMQTTTask = osThreadCreate(osThread(netMQTTTask), NULL);
	printf("\r\n MemFree: %d", xPortGetFreeHeapSize());

	/*HTTP service*/
	osThreadDef(netHTTPTask, http_server_netconn_thread, osPriorityNormal, 0,2 * 128);
	netHTTPTask = osThreadCreate(osThread(netHTTPTask), NULL);
	if (netHTTPTask == NULL) {
		printf("\r\n netHTTP task cannot be created!");
	}
	/*Reset Handler*/
	osThreadDef(resetHandlerTask, ResetHandlerTask, osPriorityRealtime, 0, 128);
	resetHandlerTask = osThreadCreate(osThread(resetHandlerTask), NULL);
	printf("\r\n MemFree: %d", xPortGetFreeHeapSize());
	printf("\r\n MemFree: %d", xPortGetFreeHeapSize());

	/*Controller*/
	xQueueControl_t xQueueControl;
	#define PORT_DEFAULT_DELAY	1000
	uint8_t uiSysState = SYS_START;
	uint8_t uiSysUpdate = FALSE;
	BaseType_t sysError;
	int ret;
	char *Badcommand = "Bad Command\r\n>";
	/* Infinite loop */
	for (;;) {
		switch (uiSysState) {
		case SYS_START:
			printf("\r\n Task Controller: Implementing...  \r\n");
			uiSysUpdate = TRUE;
			uiSysState++;
			break;
		case SYS_MB_PROTOCOL:
			printf("\r\n Starting mbProtocolTask module:  \r\n");
			sysError = xQueueReceive(xQueueControlHandle, &xQueueControl,
			portMAX_DELAY);
			if (sysError == pdPASS) {
				if ((xQueueControl.xState == TASK_RUNNING)
						&& (xQueueControl.xTask == mbProtocolTask)) {

					printf("\r\n Starting mbProtocolTask module: OK \r\n");
					uiSysUpdate = TRUE;
					uiSysState++;
				}

			} else {
				printf("\r\n Starting mbProtocolTask module: Responding Timeout \r\n");
			}
			break;
		case SYS_MB_APP:
			printf("\r\n Starting mbAppTask module:  \r\n");
			sysError = xQueueReceive(xQueueControlHandle, &xQueueControl,
			portMAX_DELAY);
			if (sysError == pdTRUE) {
				if ((xQueueControl.xState == TASK_RUNNING)
						&& (xQueueControl.xTask == mbAppTask)) {
					printf("\r\n Starting mbAppTask module: OK \r\n");
					uiSysUpdate = TRUE;
					uiSysState++;

				}
			} else {
				printf("\r\n Starting mbAppTask module: Responding Timeout \r\n");
			}
			break;
		case SYS_MB_DOWNLINK:
			printf("\r\n Starting mbDownlinkTask module:  \r\n");
			sysError = xQueueReceive(xQueueControlHandle, &xQueueControl,
			portMAX_DELAY);
			if (sysError == pdTRUE) {
				if ((xQueueControl.xState == TASK_RUNNING)
						&& (xQueueControl.xTask == mbDownlinkTask)) {
					printf("\r\n Starting mbDownlinkTask module: OK \r\n");
					uiSysUpdate = TRUE;
					uiSysState++;

				}
			} else {
				printf("\r\n Starting mbDownlinkTask module: Responding Timeout \r\n");
			}
			break;
		case SYS_NET_TIME:
			#define portDEFAULT_DELAY 1000
			printf("\r\n Starting netTimeTask");
			sysError = xQueueReceive(xQueueControlHandle, &xQueueControl,
			portDEFAULT_DELAY);
			if (sysError == pdTRUE) {
				if ((xQueueControl.xState == TASK_RUNNING)
						&& (xQueueControl.xTask == netTimeTask)) {
					printf("\r\n Starting netTimeTask  module: OK \r\n");
					uiSysUpdate = TRUE;
					uiSysState++;
				}
			} else {
				printf("\r\n Starting netTimeTask module: Responding Timeout \r\n");
				uiSysUpdate = TRUE;
				uiSysState++;
			}
			break;
		case SYS_CORE_DISCOV:
			printf("\r\n Waiting for CORE discovery in %d ms:  \r\n",
			portDEFAULT_DELAY);
			sysError = xQueueReceive(xQueueControlHandle, &xQueueControl,
			portDEFAULT_DELAY);
			if (sysError == pdTRUE) {
				if ((xQueueControl.xState == TASK_RUNNING)
						&& (xQueueControl.xTask == netTcpEchoTask)) {
					printf("\r\n  Waiting for CORE discovery: OK \r\n");
					uiSysUpdate = TRUE;
					uiSysState++;
				} else if ((xQueueControl.xState == TASK_ERR_1)
						&& (xQueueControl.xTask == netTcpEchoTask)) {
					printf("\r\n  Waiting for CORE discovery: Timeout, use pre-configured MQTT server \r\n");
				}
			} else {
				printf("\r\n Waiting for CORE discovery: Timeout \r\n");
				uiSysUpdate = TRUE;
				uiSysState++;
			}
			break;
		case SYS_MQTT:
			printf("\r\n Starting netMQTTTask module:  \r\n");
			sysError = xQueueReceive(xQueueControlHandle, &xQueueControl,
			portDEFAULT_DELAY);
			if (sysError == pdTRUE) {
				if ((xQueueControl.xState == TASK_RUNNING)
						&& (xQueueControl.xTask == netMQTTTask)) {
					printf("\r\n Starting netMQTTTask module: OK \r\n");
					uiSysUpdate = TRUE;
					uiSysState++;
				}
			} else {
				printf("\r\n Starting netMQTTTask module: Responding Timeout \r\n");
				uiSysUpdate = TRUE;
				uiSysState++;
			}
			break;
		case SYS_HTTP:
			sysError = xQueueReceive(xQueueControlHandle, &xQueueControl,portMAX_DELAY);
			if (sysError == pdTRUE) {
				if ((xQueueControl.xState == TASK_RUNNING)
						&& (xQueueControl.xTask == netHTTPTask)) {
					printf("\r\n Starting netHTTPTask module: OK \r\n");
					uiSysUpdate = TRUE;
					uiSysState++;
				}
			} else {
				printf("\r\n Starting netHTTPTask module: Responding Timeout \r\n");
				uiSysUpdate = TRUE;
				uiSysState++;
			}
			break;
		case SYS_DEVICE:
			printf("\r\n SYS_DEVICE: Implementing...  \r\n");
			MX_FATFS_Init();
			uint8_t line,i;
			dynamic = NULL;
			if (BSP_SD_Init() == MSD_OK)
				{
					fresult = f_mount(&fs, "", 1);
					fresult = f_open(&fil,"device.txt", FA_READ);
					for (line= 0; (f_eof(&fil) == 0); line++)
						{
							f_gets((char*)SDbuffer, sizeof(SDbuffer), &fil);
							//printf("\r\n Line %d: %s",line,SDbuffer);
						}
					fresult = f_close(&fil);
					printf("\r\nNum of line: %d\r\n", line);
					dynamic = (data1_t*)pvPortMalloc(line * sizeof(data1_t));
					if (dynamic !=NULL){
						fresult = f_mount(&fs, "", 1);
						fresult = f_open(&fil,"device.txt", FA_READ);
						for (i = 0; (f_eof(&fil) == 0); i++)
							{
								f_gets((char*)SDbuffer, sizeof(SDbuffer), &fil);
								ptr = parse_device((char*)SDbuffer, strlen(SDbuffer));
								addDevice((dynamic+i), ptr);
								printf("\r\nLine %d: %d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\t%s",i ,ptr->channel,ptr->deviceID,ptr->func,
										   ptr->deviceChannel,ptr->devicestatus,ptr->deviceType,ptr->deviceName,
								           ptr->channeltitle,ptr->valueType);
							}
						fresult = f_close(&fil);
						printf("\r\nNum of line: %d\r\n", line);
					}
					else
						printf("\r\n FAIL IN LOADING DEVICE DATA FROM SD CARD, PLEASE CHECK SDCARD\r\n");
				}
			else{
				printf("\r\n NOT MOUTING SDCARD\r\n");
			}
				uiSysUpdate = TRUE;
				uiSysState++;
			break;
		case SYS_DEFAULT:
			if (gotCommandFlag) {
				gotCommandFlag = 0;
				ret = CmdLineProcess(commandBuffer);
				if (ret == CMDLINE_BAD_CMD)
					HAL_UART_Transmit(&huart6, Badcommand, strlen(Badcommand),100);
			}
			//osDelay(10);
			break;

		}
		if ((uiSysUpdate == TRUE) && (uiSysState != SYS_DEFAULT)) {
			xQueueSend(xQueueMessageHandle, &uiSysState, 0);
			uiSysUpdate = FALSE;
		}
//		osDelay(200);
	}
  /* USER CODE END StartDefaultTask */
}
/*----------------------------------------------------------------------------------------------*/
//void SdcardLoadDevice(char *buffer, uint8_t count)
//{
//	printf("\nSdcardLoadDevice module\r\n");
//	printf("------------------\r\n");
//	dynamic = pvPortMalloc(28 * sizeof(data1_t));
//	if (dynamic != NULL){
//		printf("\nDynamic return address : %d\r\n",&dynamic);
//		for (line = 0; (f_eof(&fil) == 0); line++)
//		{
//		   f_gets((char*)SDbuffer, sizeof(SDbuffer), &fil);
//		   ptr = parse_device(SDbuffer, strlen(SDbuffer));
//		   addDevice((dynamic+line), ptr);
//		}
//		fresult = f_close(&fil);
//	}
//	else{
//		printf("\n Allocate fail cmnr\r\n");
//	}
////	ptr = parse_device(SDbuffer, strlen(SDbuffer));
////	addDevice((dynamic+line), ptr);
//}
/*----------------------------------------------------------------------------------------------*/
/* Callback01 function */
void Callback01(void const * argument)
{
  /* USER CODE BEGIN Callback01 */
	/*FreeRTOS Timer API for Modbus protocol stack*/
	prvvMasterTIMERExpiredISR();
  /* USER CODE END Callback01 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/*Brief: Waiting until semaphore do someting
 * 	+ Flash save
 * 	+ Reset Machine
 *
 * */
void FlashTask(void *arg) {
	xFlashSave();
	vTaskDelay(100);
	NVIC_SystemReset();

	while (1)
		;

}
void ResetHandlerTask(void *arg)
{
	BaseType_t err = pdFALSE;
	uint32_t handle;
	while (1)
	{
		err = xQueueReceive(xQueueResetHandle, &handle, portMAX_DELAY);
		if (err == pdTRUE) {
			if (handle == 1) {
				osThreadDef(flashSave, FlashTask, osPriorityRealtime,0, 2 * 128);
				flashTask = osThreadCreate(osThread(flashSave), NULL);
				xFlashSave();
				osDelay(10);
				printf("\r\n System reset \r\n");
				NVIC_SystemReset();
			}
		}
		vTaskDelay(100);
	}
}

//void SdcardTaskWrite(void *arg)
//{
//	BaseType_t err = pdFALSE;
//	uint32_t handle;
//	while (1)
//	{
//		err = xQueueReceive(xQueueResetHandle, &handle, portMAX_DELAY);
//		if (err == pdTRUE) {
//			if (handle = 1) {
//				osThreadDef(flashSave, SDcardTaskWrite, osPriorityRealtime,0, 2 * 128);
//				sdcardTask = osThreadCreate(osThread(flashSave), NULL);
//				xFlashSave();
//				osDelay(10);
//				printf("\r\n System reset \r\n");
//				NVIC_SystemReset();
//			}
//		}
//		vTaskDelay(100);
//	}
//}
/* USER CODE END Application */
