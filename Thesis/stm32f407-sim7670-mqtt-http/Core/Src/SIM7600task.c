/*
 * SIM7600task.c
 *
 *  Created on: May 5, 2021
 *      Author: ACER
 */
/* Built-in C library includes ---------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
/* Platform includes --------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "main.h"
#include "sim7600.h"

/* Shared Variables ----------------------------------*/
osThreadId netSIMTask;
extern osMessageQId xQueueControlHandle;
extern osMessageQId xQueueMessageHandle;
extern osSemaphoreId netMqttIpSemaphoreHandle;
extern osMessageQId xQueueDownlinkHandle;
extern osMessageQId xQueueUplinkHandle;

char *client = "mqtt";
const char *server = "m14.cloudmqtt.com";
const char *mqtt_id = "NULL";
const char *mqtt_user = "yktdxpqb";
const char *mqtt_password = "VKCG6yboYrYd";
const uint16_t u16_mqtt_port = 	19613;
const char *telemetry = "upstream/telemetry";
const char *provision = "upstream/provision";
const char *command = "downstream/command";
const char *down_pro = "downstream/provision";

void netsimTask(void *arg);

void netsimTask(void *arg)
{
	//printf("\r\n netsimTask \r\n");
	xQueueControl_t xQueueControl;
	uint8_t uiSysState;
	xQueueControl.xTask = netSIMTask;
	/*Waiting for controller start this task*/
	do {
		osDelay(10);
		xQueuePeek(xQueueMessageHandle, &uiSysState, 0);
	}
	while (uiSysState != SYS_SIM_TASK);
	xQueueReceive(xQueueMessageHandle, &uiSysState, 0);
	//printf("\r\b SIM Service starting \r\n");
	/*Starting initial*/
	INIT_SIM7600();   // HERE
	sim7600_info_t sim7600_client;
	sim7600_client.client_id = mqtt_id;
	sim7600_client.client_user = mqtt_user;
	sim7600_client.client_pass = mqtt_password;
	sim7600_client.port= u16_mqtt_port;
	sim7600_client.keepalive = 1000;
	sim7600_client.will_topic = NULL;
	sim7600_client.qos = 1;
	sim7600_client.retain = 0;
	uint8_t state = SIM7600_NEW_CONNECTION(client,server,sim7600_client.client_user,sim7600_client.client_pass,sim7600_client.port,sim7600_client.keepalive);
	if (state == 1) {
		SUBSCRIBE(command,sim7600_client.qos);
		HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_14);
		HAL_Delay(100);
		SUBSCRIBE(down_pro,sim7600_client.qos);
	} else {
		//printf("\r\n Failed to connect to MQTT server with er: %d", er);
	}
	/*Notify controller the starting is successful*/
	xQueueControl.xState = TASK_RUNNING;
	xQueueSend(xQueueControlHandle, &xQueueControl, 10);
	#define port_DEFAULT_DELAY 	1000
	/*a loop in mqtt_modbus_thread_up(); function*/
	//MQTT_SIM7600_UPSTREAM(telemetry, provision, sim7600_client.qos);
	//SIM7600_PUBLISH_PACKET(tel_topic,sim7600_client.qos);
	while (1)
		;
}
