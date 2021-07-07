/* Built-in C library includes ---------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <param.h>
#include <stdlib.h>
/* Platform includes --------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "main.h"
#include "mqttclienttask.h"
#include "flash.h"
#include "rtc.h"
#include "usart.h"
#include "json.h"
#include "modbus_mqtt_bridge.h"
#include "mbproto.h"

/* Network includes----------------------------*/
#include "lwip/apps/mqtt.h"
#include "lwip/apps/mqtt_priv.h"
#include "err.h"
#include "lwip.h"
#include "lwip/init.h"
#include "lwip/netif.h"

#include "command.h"
#include "http_client.h"
#include "param.h"
#include "time_value.h"
#include "telemetry.h"


/* Shared Variables --------------------------*/
extern osMessageQId xQueueDownlinkHandle;
extern osMessageQId xQueueUplinkHandle;
/* Private Variables -------------------------*/
uint8_t mqtt_couter_err = 0;
char buffer[100];
char temp[20];
char temp0[10];
char temp1[20];
char temp2[20];
char temp3[20];
uint8_t port, func, id;
uint16_t channel;
static data1_t *ptr;
data1_t test;
data1_t *dynamic;
static uint8_t dem = 0;  // count
uint8_t id_temp[2];
/* Start implementation ----------------------*/

char *allocate(char *src)
{
	char *dst = pvPortMalloc(strlen(src)+1);
	strcpy(dst, src);
	return dst;
	}

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start
			&& strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}
/*---------------------------------------------------PARSING DARA-----------------------------------------------------------------------------*/
data1_t *parse_device(char *Buffer, uint16_t BufferLen)
{
	ptr = &test;
	int i,r;
	jsmn_parser p;
	jsmntok_t t[JSON_MAX_LEN]; /* We expect no more than JSON_MAX_LEN tokens */
	jsmn_init(&p);
	r = jsmn_parse(&p, Buffer,BufferLen, t,sizeof(t) / sizeof(t[0]));
	for (i = 1; i < r; i++) {
		if (jsoneq(Buffer, &t[i], "PORT") == 0) {
			ptr->channel = (uint8_t)atoi(Buffer + t[i + 1].start);
			i++;
		} else if (jsoneq(Buffer, &t[i], "ID") == 0) {
			ptr->deviceID = (uint8_t)atoi(Buffer + t[i + 1].start);
			i++;
		} else if (jsoneq(Buffer, &t[i], "FC") == 0) {
			ptr->func = (uint8_t)atoi(Buffer + t[i + 1].start);
			i++;
		} else if (jsoneq(Buffer, &t[i], "CHANNEL") == 0) {
			memset(temp0,'\0',sizeof(temp0));
			strncpy(temp0,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			ptr->deviceChannel = (uint16_t)strtol(temp0, NULL, 0);
			i++;
		} else if (jsoneq(Buffer, &t[i], "DEVICETYPE") == 0) {
			//char temp[20];
			memset(temp,'\0',sizeof(temp));
			strncpy(temp,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			ptr->deviceType = temp;
			i++;
		} else if (jsoneq(Buffer, &t[i], "DEVICENAME") == 0) {
			//char temp[20];
			memset(temp1,'\0',sizeof(temp));
			strncpy(temp1,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			ptr->deviceName = temp1;
			i++;
		} else if (jsoneq(Buffer, &t[i], "CHANNELTITLE") == 0) {
			//char temp[20];
			memset(temp2,'\0',sizeof(temp2));
			strncpy(temp2,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			ptr->channeltitle = temp2;
			i++;
		}else if (jsoneq(Buffer, &t[i], "VALUETYPE") == 0) {
			//char temp[20];
			memset(temp3,'\0',sizeof(temp3));
			strncpy(temp3,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			ptr->valueType= temp3;
			i++;
		} else if (jsoneq(Buffer, &t[i], "DEVICESTATUS") == 0) {
			ptr->devicestatus = atoi(Buffer + t[i + 1].start);
			i++;
		}
	}
	return ptr;
}

void addDevice(data1_t *destination, data1_t *data)
{
   destination->channel = data->channel;
   destination->deviceID = data->deviceID;
   destination->func = data->func;
   destination->devicestatus = data->devicestatus;
   destination->deviceChannel = data->deviceChannel;
//   destination->deviceType = data->deviceType;
//   destination->deviceName = data->deviceName;
//   destination->channeltitle = data->channeltitle;
//   destination->valueType = data->valueType;
//   destination->deviceType = strdup(data->deviceType);
//   destination->deviceName = strdup(data->deviceName);
//   destination->channeltitle = strdup(data->channeltitle);
//   destination->valueType = strdup(data->valueType);
     destination->deviceType = allocate(data->deviceType);
     destination->deviceName = allocate(data->deviceName);
     destination->channeltitle = allocate(data->channeltitle);
     destination->valueType = allocate(data->valueType);

}

/*---------------------------------------------------MODBUS MQTT BRIGDE FUNCTION-----------------------------------------------------------------------------*/
static void mqtt_bridge_pub_request_cb(void *arg, err_t result) {
	if (result != ERR_OK) {
		printf("\r\n Publish telemetry result: %d\n", result);
	} else {
	}
}
static void mqtt_bridge_provision_request_cb(void *arg, err_t result) {
	if (result != ERR_OK) {
		printf("\r\n Publish provision result: %d\n", result);
	} else {
	}
}
static void mqtt_bridge_command_request_cb(void *arg, err_t result) {
	if (result != ERR_OK) {
		printf("\r\n Publish command result: %d\n", result);
	} else {
	}
}
/**@ Brief: Get data from modbus dev and forward it to mqtt server
 * @ Todo:
 * 		Parse json object from server
 * */
/*------------------------------------------------------------------------------------------------------------------------------*/
void mqtt_modbus_thread_up(mqtt_client_t *client, char *pub_topic, char* pro_topic, char* command_topic, char* test_topic) {

	uint8_t main_time[6];
	BaseType_t Err = pdFALSE;
	xQueueMbMqtt_t xQueueMbMqtt;
	portCHAR head[MAX_JSON_LEN];
	portCHAR tail[MAX_JSON_LEN];
	static uint8_t count = 0;
	err_t err;

	while (1) {
		Err = xQueueReceive(xQueueUplinkHandle, &xQueueMbMqtt,portDEFAULT_WAIT_TIME*3);
		if (Err == pdPASS) {
			if (xQueueMbMqtt.gotflagProvision == 1 && xQueueMbMqtt.sum_dev != 0)  // check provision ?
				{
					err_t err;
					uint16_t SUM = 20;
				    for (uint8_t i = 0; i < SUM; i++)// duyệt từng phần tử trong mảng
				    {
				        for (uint8_t j = 0; j < SUM; j++)  // duyệt ID device
				        {
				            if ((dynamic+j)->deviceID == (dynamic+i)->deviceID && (dynamic+i)->deviceID != (dynamic+i-1)->deviceID){
				                    count ++;
				                    if (count == 1){
				                        if (i > 0){
				                        for (uint8_t a = 0; a < i; a++){
				                             if ((dynamic+a)->deviceID == (dynamic+j)->deviceID){
				                                goto TEST;
				                                }
				                            }
				                        }
				                        head_provision(head,(dynamic+j)->deviceID,(dynamic+j)->deviceName,(dynamic+j)->deviceType);
				                        for (uint8_t z = 0; z < SUM; z++)  // duyệt channel ID
				                        {
				                            if ((dynamic+z)->deviceID == (dynamic+j)->deviceID){
				                            	tail_provision(tail,(dynamic+z)->deviceChannel,(dynamic+z)->channeltitle,(dynamic+z)->valueType, (dynamic+z)->func);
				                                strcat(head,tail);
				                            }
				                        }
				                        head[strlen(head) - 1] = '\0';
				                        strcat(head,"]}]}");
				                        err = mqtt_publish(client,pro_topic, head,strlen(head), QOS_0, 0,mqtt_bridge_provision_request_cb,NULL);
				                        memset(head,'\0',sizeof(head));
										if (err != ERR_OK) {
											printf("\r\n Publish Provision err: %d\n", err);
											}
										osDelay(200);
				                    }
				            }
				        }
				        TEST: count = 0;
				    }
					BaseType_t er = pdFALSE;
					er = xQueueSend(xQueueDownlinkHandle, &xQueueMbMqtt,portDEFAULT_WAIT_TIME);
					if (er == pdPASS) {
					}
				}/* END OF SENDING PROVISION---------------------------------------------------------------------*/
			else if (xQueueMbMqtt.gotflagcommand == 3){  // check command
				if (xQueueMbMqtt.FunC == 3)
					command_read_json(head, xQueueMbMqtt.NodeID, xQueueMbMqtt.RegAdr.i16data, xQueueMbMqtt.RegData.i16data);
				else if (xQueueMbMqtt.FunC == 6)
					command_write_json(head, xQueueMbMqtt.NodeID, xQueueMbMqtt.RegAdr.i16data);
				err = mqtt_publish(client,command_topic, head,strlen(head), QOS_0, 0,mqtt_bridge_command_request_cb,NULL);
				if (err != ERR_OK) {
					printf("\r\n Publish command err: %d\n", err);
					}
				else if (err == ERR_OK){
					xQueueMbMqtt.gotflagcommand = 0;
				}
			}/* END OF SENDING COMMNAND---------------------------------------------------------------------*/
			else if (xQueueMbMqtt.gotflagtelemetry == 2){ // check telemetry
			dem ++;
			Get_Time(main_time);
			if (dem == 1){
				id_temp[0] = xQueueMbMqtt.NodeID;
				head_telemetry(head, main_time, xQueueMbMqtt.NodeID);
				strcat(head,"{");
			}
			id_temp[1] = xQueueMbMqtt.NodeID;
			tail_telemetry(tail,xQueueMbMqtt.RegAdr.i16data, xQueueMbMqtt.RegData.i16data);
			strcat(head,tail);
			if (id_temp[0] != id_temp[1])
			{
               	head[strlen(head) - 1] = '\0';
		        strcat(head,"}}}");
				err = mqtt_publish(client, pub_topic,head,strlen(head), QOS_0, 0,mqtt_bridge_pub_request_cb,NULL);
				dem = 0;
				if (err != ERR_OK) {
					printf("\r\n Publish err: %d\n", err);
					if (err == -11){
						//MX_LWIP_Init();
					}
				}
				else if (err == ERR_OK){
					xQueueMbMqtt.gotflagtelemetry = 0;
				}
			}
		}/* END OF SENDING TELEMETRY---------------------------------------------------------------------*/
	} else {
			/*Create Json and publish to mqtt */
//			memset(publish_buffer, 0, MAX_JSON_LEN);
//			strcat(publish_buffer, "{\"NodeID\":");
//			strcat(publish_buffer, itoa_user(0, 10));
//			strcat(publish_, ",\"FunC\":");
//			strcat(publish_buffer, itoa_user(MB_FUNC_ACK, 10));
//			strcat(publish_buffer, ",\"RegAdrH\":");
//			strcat(publish_buffer,
//					itoa_user(xQueueMbMQtt.RegAdr.i8data[1], 10));
//			strcat(publish_buffer, ",\"RegAdrL\":");
//			strcat(publish_buffer,
//					itoa_user(xQueueMbMQtt.RegAdr.i8data[0], 10));
//			strcat(publish_buffer, ",\"RegDataH\":");
//			strcat(publish_buffer,
//					itoa_user(xQueueMbMQtt.RegData.i8data[1], 10));
//			strcat(publish_buffer, ",\"RegDataL\":");
//			strcat(publish_buffer,
//					itoa_user(xQueueMbMQtt.RegData.i8data[0], 10));
//			strcat(publish_buffer, ",\"PortID\":");
//			strcat(publish_buffer, itoa_user(xQueueMbMQtt.PortID, 10));
//			strcat(publish_buffer, "}");
////			HAL_UART_Transmit(&huart1, publish_buffer, MAX_JSON_LEN, 1000);
//			err = mqtt_publish(client, pub_topic, publish_buffer,
//					strlen(publish_buffer), QOS_0, 0,
//					mqtt_bridge_pub_request_cb,
//					NULL);
//			if (err != ERR_OK) {
//				mqtt_couter_err++;
//
//				printf("\r\n Publish err: %d\n", err);
//				if (mqtt_couter_err == 10) NVIC_SystemReset();
//			}
//			else
//			{
//				mqtt_couter_err = 0;
//			}

		}
//		vTaskDelay(10);

	}
}
//	how to got mqtt intance??
/*-------------------------------------PROVISION DOWNSTREAM---------------------------------------------------------------------------------------*/
uint8_t mqtt_modbus_thread_down_provision(char *pJsonMQTTBuffer,uint16_t pJsonMQTTBufferLen) {

	int i;
	int r;
	jsmn_parser p;
	jsmntok_t t[JSON_MAX_LEN]; /* We exect no morep than JSON_MAX_LEN tokens */
	jsmn_init(&p);
	xQueueMbMqtt_t xQueueMbMqtt;
	r = jsmn_parse(&p, pJsonMQTTBuffer, pJsonMQTTBufferLen, t,sizeof(t) / sizeof(t[0]));
	printf("\r\n - r: %d\r\n", r);
	if (r < 0) {
		printf("Failed to parse JSON: %d\n", r);
		return 1;
	}
	/* Assume the top-level element is an object */
	if (r < 1 || t[0].type != JSMN_OBJECT) {
		printf("Object expected\n");
		return 1;
	}
	/* Loop over all keys of the root object */\
	xQueueMbMqtt.NodeID = atoi(pJsonMQTTBuffer + t[0 + 1].start);
	printf("\r\n- device_id:%d\r\n",xQueueMbMqtt.NodeID);  // device_id
	char jasmine[100];
	strncpy(jasmine, pJsonMQTTBuffer + t[1 + 1].start, t[1 + 1].end - t[1 + 1].start);
	printf("\r\n- jasmine:%s\r\n",jasmine);  // device_id
	for (i = 2; i < r -1; i = i +2) {
		xQueueMbMqtt.RegAdr.i16data = atoi(pJsonMQTTBuffer + t[i + 1].start);
		int8_t device_status = atoi(pJsonMQTTBuffer + t[(i + 1) + 1].start);
		printf("\r\n+ channel_id:%d\tstatus:%d\r\n",xQueueMbMqtt.RegAdr.i16data,device_status);  // channel
		//printf("value: %.*s at i = %d\r\n",t[i + 1].end - t[i + 1].start,pJsonMQTTBuffer + t[i + 1].start,i);
	}

}
/*--------------------------------------COMMAND DOWNSTREAM-------------------------------------------------------------------------*/
uint8_t mqtt_modbus_thread_down_command(char *pJsonMQTTBuffer,uint16_t pJsonMQTTBufferLen) {
	/*Parsing json by using clone source :) */
		int i;
		int r;
		jsmn_parser p;
		jsmntok_t t[JSON_MAX_LEN]; /* We expect no more than JSON_MAX_LEN tokens */
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
		for (i = 1; i < r; i++) {
			if (jsoneq(pJsonMQTTBuffer, &t[i], "device_id") == 0) {
				printf("\r\n - device_id: %.*s\n", t[i + 1].end - t[i + 1].start,pJsonMQTTBuffer + t[i + 1].start);
				xQueueMbMqtt.NodeID = atoi(pJsonMQTTBuffer + t[i + 1].start);
				i++;
			}
			else if (jsoneq(pJsonMQTTBuffer, &t[i], "channel_id") == 0) {
				printf("\r\n - channel_id: %.*s\n", t[i + 1].end - t[i + 1].start,pJsonMQTTBuffer + t[i + 1].start);
				xQueueMbMqtt.RegAdr.i16data = atoi(pJsonMQTTBuffer + t[i + 1].start);
				i++;
			}
			else if (jsoneq(pJsonMQTTBuffer, &t[i], "command") == 0) {
				uint8_t command = 0;
				char cmd[20];
				printf("\r\n - command: %.*s\n", t[i + 1].end - t[i + 1].start,pJsonMQTTBuffer + t[i + 1].start);
				strncpy(cmd, pJsonMQTTBuffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
				if (strstr(cmd,"read") != NULL){
					command = 3;
					uint16_t value = 1;
					xQueueMbMqtt.RegData.i8data[0] = (uint8_t)value;
					xQueueMbMqtt.RegData.i8data[1] = (uint8_t)(value >> 8);
				}
				else if (strstr(cmd,"write") != NULL)
					command = 6;
				xQueueMbMqtt.FunC = command;
				i++;
			}
			else if (jsoneq(pJsonMQTTBuffer, &t[i], "value") == 0) {
				uint16_t value = 0;
				char val[10];
				printf("\r\n - value: %.*s\n", t[i + 1].end - t[i + 1].start,pJsonMQTTBuffer + t[i + 1].start);
				strncpy(val, pJsonMQTTBuffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
				//printf("\r\nval: %s\r\n",val);
				if (strstr(val,"true") != NULL || strstr(val,"on") != NULL)
					value = 1;
				else if (strstr(val,"false") != NULL || strstr(val,"off") != NULL)
					value = 0;
				else
					value = atoi(pJsonMQTTBuffer + t[i + 1].start);
				xQueueMbMqtt.RegData.i8data[0] = (uint8_t)value;
				xQueueMbMqtt.RegData.i8data[1] = (uint8_t)(value >> 8);
				i++;
			}
		}
		BaseType_t Err = pdFALSE;
		Err = xQueueSend(xQueueDownlinkHandle, &xQueueMbMqtt,portDEFAULT_WAIT_TIME);
		if (Err == pdPASS) {
			memset(pJsonMQTTBuffer,'\0',pJsonMQTTBufferLen);
		} else {
			printf("\r\n Modbus_MQTT Downlink queued: False \r\n");
		}
}

