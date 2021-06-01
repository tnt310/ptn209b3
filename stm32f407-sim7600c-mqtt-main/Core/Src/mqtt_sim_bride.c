/*
 * mqtt_sim7600_brigd.c
 *
 *  Created on: May 5, 2021
 *      Author: ACER
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "main.h"
#include "sim7600.h"
#include "command.h"

extern osMessageQId xQueueDownlinkHandle;
extern osMessageQId xQueueUplinkHandle;

void MQTT_SIM7600_UPSTREAM(char *telemetry, char *provision, uint8_t qos){

//	uint8_t main_time[6];
	BaseType_t Err = pdFALSE;
	xQueueMbMqtt_t xQueueMbMqtt;
	#define portDEFAULT_WAIT_TIME 1000
//	portCHAR publish_buffer[MAX_JSON_LEN];
//	portCHAR publish_provision[MAX_JSON_LEN];
//	err_t err;
	while (1) {
		Err = xQueueReceive(xQueueUplinkHandle, &xQueueMbMqtt,portDEFAULT_WAIT_TIME * 3);
		if (Err == pdPASS) {
//			if (xQueueMbMqtt.gotflagProvision == 1 && xQueueMbMqtt.sum_dev != 0)
//				{
//					memset(publish_provision, 0,MAX_JSON_LEN);
//					err_t err;
//					for (uint16_t i = 0 ; i < xQueueMbMqtt.sum_dev; i++)
//					{
//						provision ++;
//						if (provision == 1){
//							strcat(publish_provision,"{");
//						}
//						createJson_provision(buffer,table1[i].name,table1[i].type,table1[i].title, table1[i].description);  // HERE
//						if (provision < 2)
//							{
//								strcat(buffer,",");
//							}
//						strcat(publish_provision,buffer);
//						if (provision == 2)
//						{
//						strcat(publish_provision,"}");
//						//err = mqtt_publish(client,pro_topic, publish_provision,strlen(publish_provision), QOS_0, 0,mqtt_bridge_provision_request_cb,NULL);
//						PUBLISH_TELEMETRY(pro_topic);  // HERE
//						memset(publish_provision, 0, MAX_JSON_LEN);
//						provision = 0;
//						if (err != ERR_OK) {
//							printf("\r\n Publish Provision err: %d\n", err);
//							}
//						osDelay(200);
//						}
//					}
//					BaseType_t er = pdFALSE;
//					er = xQueueSend(xQueueDownlinkHandle, &xQueueMbMqtt,portDEFAULT_WAIT_TIME);
//					if (er == pdPASS) {
//					}
//				}// END OF SENDING PROVISION
//			dem ++;
//			countDelay++;  // HERE
//			if (dem == 1){
//				strcat(publish_buffer,"{");
//			}
//			memset(buffer,0,500);
//			/*Create Json and publish to mqtt */
//			Get_Time(main_time);
//			//createJson(buffer,chan,table[xQueueMbMQtt.countflag].name,table[xQueueMbMQtt.countflag].name_dev, xQueueMbMQtt.RegData.i16data, main_time);
//			createJson_v1(buffer,table1[xQueueMbMqtt.countflag].name, xQueueMbMqtt.RegData.i16data, main_time);
//			if (dem < 20)
//				{
//					strcat(buffer,",");
//				}
//			strcat(publish_buffer,buffer);
//			/*publish to mqtt */
//			if (dem == 20)
//			{
//				strcat(publish_buffer,"}");
//				err = mqtt_publish(client, pub_topic, publish_buffer,strlen(publish_buffer), QOS_0, 0,mqtt_bridge_pub_request_cb,NULL);
//				memset(publish_buffer, 0, MAX_JSON_LEN);
//				dem = 0;
//			}
//
//		} else {
//		}
//
		}
	}
}

