///*
// * netsimTask.c
// *
// *  Created on: Apr 18, 2021
// *      Author: ACER
// */
///* Includes ------------------------------------------------------------------*/
//#include "FreeRTOS.h"
//#include "task.h"
//#include "main.h"
//#include "cmsis_os.h"
//
///* Private includes ----------------------------------------------------------*/
///* USER CODE BEGIN Includes */
//#include "stdint.h"
//#include "stdio.h"
//#include "rtc.h"
//#include "usart.h"
//#include <command.h>
//#include "cmdline.h"
//
//osThreadId netSIMTask;
//extern osMessageQId xQueueControlHandle;
//extern osMessageQId xQueueMessageHandle;
//
//void netsimTask(void const *arg)
//{
//	printf("\r\n netsimTask \r\n");
//	xQueueControl_t xQueueControl;
//	uint8_t uiSysState;
//	xQueueControl.xTask = netSIMTask;
//	/*Waiting for controller start this task*/
//	do {
//		osDelay(10);
//		xQueuePeek(xQueueMessageHandle, &uiSysState, 0);
//	}
//	while (uiSysState != SYS_SIM);
//	xQueueReceive(xQueueMessageHandle, &uiSysState, 0);
//	printf("\r\b Module SIM Service starting \r\n");
//	while(1)
//		;
//	}
