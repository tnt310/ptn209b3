/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cmsis_os.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

extern uint8_t PRINTF_EN;


#define DBG(fmt,...) if (PRINTF_EN == 1) printf(fmt,##__VA_ARGS__)

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
typedef enum{
	TASK_NONE= 0,
	TASK_INIT,
	TASK_RUNNING,
	TASK_ERR_1,
	TASK_ERR_2,
	TASK_KILL
}xTaskState_t;

typedef struct{
	osThreadId xTask;
	xTaskState_t xState;
}xQueueControl_t;
typedef union
{
	uint16_t i16data;
	uint8_t  i8data[2];
}int16toint8;
typedef struct{

	uint8_t  PortID;
	uint8_t  NodeID;
	uint8_t  FunC;
	int16toint8 RegAdr;
	int16toint8 RegData;
	uint8_t  countflag;
	char alias[10];
	uint8_t gotflagProvision;
	uint8_t mutex;
	uint16_t sum_dev;
}xQueueMbMqtt_t;


typedef struct {
    uint8_t channel;
    uint8_t deviceID;
    uint8_t func;
    uint8_t devicestatus;
    uint16_t deviceChannel;
    char *deviceType;
    char *deviceName;
    char *channeltitle;
    char *valueType;
}data1_t;

extern data1_t *dynamic;

enum {
	SYS_START,SYS_DEVICE, SYS_DEFAULT
};
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
