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
#include "json.h"
#include "mqtt_sim_bride.h"

extern osMessageQId xQueueDownlinkHandle;
extern osMessageQId xQueueUplinkHandle;
extern data1_t table1[];

/* Start implementation ----------------------*/

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start
			&& strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

void MQTT_SIM7600_UPSTREAM(char *telemetry, char *provision, uint8_t qos){

		BaseType_t Err = pdFALSE;
		xQueueMbMqtt_t xQueueMbMqtt;
		#define portDEFAULT_WAIT_TIME 1000
		portCHAR publish_buffer[MAX_JSON_LEN];
		portCHAR publish_provision[MAX_JSON_LEN];
		portCHAR buffer[200];
		memset(publish_provision, 0,MAX_JSON_LEN);
		for (uint16_t i = 0 ; i < cal_sum_dev(); i++)
			{
				strcat(publish_provision,"{");
				createJson_provision(buffer,table1[i].IDkey,table1[i].name,table1[i].type,table1[i].title, table1[i].description);  // HERE
				strcat(publish_provision,buffer);
				strcat(publish_provision,"}");
				SIM7600_PUBLISH_PACKET(provision,publish_provision,1);  // HERE
				memset(publish_provision, 0, MAX_JSON_LEN);
				osDelay(200);
			}
}
//void MQTT_SIM7600_UPSTREAM(char *telemetry, char *provision, uint8_t qos){
//
//	BaseType_t Err = pdFALSE;
//	xQueueMbMqtt_t xQueueMbMqtt;
//	#define portDEFAULT_WAIT_TIME 1000
//	portCHAR publish_buffer[MAX_JSON_LEN];
//	portCHAR publish_provision[MAX_JSON_LEN];
//	portCHAR buffer[200];
//	while (1) {
//		Err = xQueueReceive(xQueueUplinkHandle, &xQueueMbMqtt,portDEFAULT_WAIT_TIME * 3);
//		if (Err == pdPASS) {
//			if (xQueueMbMqtt.gotflagProvision == 1 && xQueueMbMqtt.sum_dev != 0)
//				{
//					memset(publish_provision, 0,MAX_JSON_LEN);
//					for (uint16_t i = 0 ; i < xQueueMbMqtt.sum_dev; i++)
//					{
//						strcat(publish_provision,"{");
//						createJson_provision(buffer,table1[i].name,table1[i].type,table1[i].title, table1[i].description);  // HERE
//						strcat(publish_provision,buffer);
//						strcat(publish_provision,"}");
//						//err = mqtt_publish(client,pro_topic, publish_provision,strlen(publish_provision), QOS_0, 0,mqtt_bridge_provision_request_cb,NULL);
//						SIM7600_PUBLISH_PACKET(provision,publish_provision,1);  // HERE
//						memset(publish_provision, 0, MAX_JSON_LEN);
//						osDelay(200);
//					}
//				}
//			memset(publish_buffer,0,sizeof(publish_buffer));
//			strcat(publish_buffer,"{");
//			memset(buffer,0,200);
//			/*Create Json and publish to mqtt */
//			createJson(buffer,table1[xQueueMbMqtt.countflag].name, xQueueMbMqtt.RegData.i16data);
//			strcat(publish_buffer,buffer);
//			/*publish to mqtt */
//			strcat(publish_buffer,"}");
//			//err = mqtt_publish(client, pub_topic, publish_buffer,strlen(publish_buffer), QOS_0, 0,mqtt_bridge_pub_request_cb,NULL);
//			SIM7600_PUBLISH_PACKET(telemetry,publish_buffer,1);  // HERE
//			memset(publish_buffer, 0, MAX_JSON_LEN);
//		} else {
//
//		}
//	}
//}
void MQTT_SIM7600_DOWNSTREAM(char *pJsonMQTTBuffer,uint16_t pJsonMQTTBufferLen)
{
	/*Parsing json by using clone source :) */
		int i;
		int r;
		jsmn_parser p;
		jsmntok_t t[100]; /* We expect no more than JSON_MAX_LEN tokens */
		jsmn_init(&p);
		xQueueMbMqtt_t xQueueMbMqtt;
		r = jsmn_parse(&p, pJsonMQTTBuffer, pJsonMQTTBufferLen, t,sizeof(t) / sizeof(t[0]));
		if (r < 0) {
			printf("Failed to parse JSON: %d\n", r);
			return 1;
		}

		/* Assume the top-level element is an object */
		if (r < 1 || t[0].type != JSMN_OBJECT) {
			printf("Object expected\n");
			return 1;
		}
		/* Loop over all keys of the root object */
		for (i = 1; i < r; i++) {
			if (jsoneq(pJsonMQTTBuffer, &t[i], "name") == 0) {
				/* We may use strndup() to fetch string value */
				printf("\r\n - name: %.*s\n", t[i + 1].end - t[i + 1].start,pJsonMQTTBuffer + t[i + 1].start);
				char name[20];
				strncpy(name, pJsonMQTTBuffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
				for (uint16_t j = 0; j < DEVSUM(); j++)
				{
					if (strstr(table1[j].name, name) != NULL)
					{
						printf("\r\n - name_dev: %s\n",table1[j].name);
						printf("\r\n device created successfully %s\n");
					}
					else
					{
						printf("\r\n device not created with %s\n", table1[j].name);
					}
				}
				i++;
			}
			else if (jsoneq(pJsonMQTTBuffer, &t[i], "value") == 0) {
				/* We may additionally check if the value is either "true" or "false" */
				char value[20];
				printf("\r\n - value: %.*s\n", t[i + 1].end - t[i + 1].start,pJsonMQTTBuffer + t[i + 1].start);
				strncpy(value, pJsonMQTTBuffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
				//i++;
			}
		}
		memset(pJsonMQTTBuffer,"\0",pJsonMQTTBufferLen);
		fflush(stdin);
		//xQueueMbMqtt.mutex = 1;  // set mutex for mdtask;
		BaseType_t Err = pdFALSE;
		Err = xQueueSend(xQueueDownlinkHandle, &xQueueMbMqtt,portDEFAULT_WAIT_TIME);
		if (Err == pdPASS) {
		} else {
			printf("\r\n Modbus_MQTT Downlink queued: False \r\n");
		}
	}
