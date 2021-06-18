/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "command.h"
#include "cmdline.h"

osThreadId resetHandlerTask;
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
FATFS fs;
FIL fil;
FRESULT fresult;
char SDbuffer[200];
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
osThreadId defaultTaskHandle;
extern UART_HandleTypeDef huart6;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void ResetHandlerTask(void *arg);
void Callback01(void const * argument);
/* USER CODE END FunctionPrototypes */
void StartDefaultTask(void const * argument);
void MX_FREERTOS_Init(void);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
	  osSemaphoreDef(netMqttIpSemaphore);
	  netMqttIpSemaphoreHandle = osSemaphoreCreate(osSemaphore(netMqttIpSemaphore), 1);
  /* definition and creation of netMqttIpSemaphore */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of myTimer01 */
  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */


	  /* USER CODE BEGIN RTOS_SEMAPHORES */
		/* add semaphores, ... */
	  /* USER CODE END RTOS_SEMAPHORES */

	  /* Create the timer(s) */
	  /* definition and creation of myTimer01 */

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
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 1024);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
}
  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
void StartDefaultTask(void const * argument)
 {
   /* USER CODE BEGIN StartDefaultTask */
 	/*Create Task Modules in this line*/
 	/*SIm serive*/
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
 			printf("\r\n SYS_START: Implementing...  \r\n");
 			uiSysUpdate = TRUE;
 			uiSysState++;
 			break;
 		case SYS_DEVICE:
 			printf("\r\n SYS_DEVICE: Implementing...  \r\n");
			  MX_FATFS_Init();
			  if (BSP_SD_Init() == MSD_OK)
			  {
				  fresult = f_mount(&fs, "", 1);
				  fresult = f_open(&fil, "device.txt", FA_READ);
					for (uint8_t i = 0; (f_eof(&fil) == 0); i++)
					{
					   memset(SDbuffer,0, sizeof(SDbuffer));
					   f_gets((char*)SDbuffer, sizeof(SDbuffer), &fil);
					   printf("\r\nLine %d: %s",i, SDbuffer);

					}
					fresult = f_close(&fil);
			  }
 			uiSysUpdate = TRUE;
 			uiSysState++;
 			break;
		case SYS_DEFAULT:
			if (gotCommandFlag == 1) {
				gotCommandFlag = 0;
				ret = CmdLineProcess(commandBuffer);
				if (ret == CMDLINE_BAD_CMD){
					HAL_UART_Transmit(&huart6, Badcommand, strlen(Badcommand),100);
				}
			}
			//osDelay(10);
			break;
		}
		if ((uiSysUpdate == TRUE) && (uiSysState != SYS_DEFAULT)) {
			xQueueSend(xQueueMessageHandle, &uiSysState, 0);
			uiSysUpdate = FALSE;
		}
 	}
   /* USER CODE END StartDefaultTask */
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
				handle = 0;
				//osThreadDef(flashSave, FlashTask, osPriorityRealtime,0, 2 * 128);
				//flashTask = osThreadCreate(osThread(flashSave), NULL);
				//xFlashSave();
				//osDelay(10);
				printf("\r\n System reset \r\n");
				NVIC_SystemReset();
			}
		}
		vTaskDelay(100);
	}
}
  /* USER CODE END RTOS_THREADS */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
