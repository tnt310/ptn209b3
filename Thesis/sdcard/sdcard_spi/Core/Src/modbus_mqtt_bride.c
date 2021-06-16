/* Built-in C library includes ---------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Platform includes --------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "main.h"
#include "json.h"
#include "modbus_mqtt_bridge.h"


/* Network includes----------------------------*/

/* Shared Variables --------------------------*/
static data1_t *ptr;
static data1_t test, device;
/* Private Variables -------------------------*/


/* Start implementation ---------------------- ---------------------- ---------------------- ---------------------- ----------------------*/

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start
			&& strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}


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
			(ptr)->channel = atoi(Buffer + t[i + 1].start);
			i++;

		} else if (jsoneq(Buffer, &t[i], "ID") == 0) {
			(ptr)->deviceID = atoi(Buffer + t[i + 1].start);
			i++;
		} else if (jsoneq(Buffer, &t[i], "FC") == 0) {
			(ptr)->func = atoi(Buffer + t[i + 1].start);
			i++;

		} else if (jsoneq(Buffer, &t[i], "CHANNEL") == 0) {
			char temp[20];
			memset(temp,'\0',sizeof(temp));
			strncpy(temp,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			(ptr)->deviceChannel = (uint16_t)strtol(temp, NULL, 0);
			i++;
		} else if (jsoneq(Buffer, &t[i], "DEVICETYPE") == 0) {
			char temp[20];
			memset(temp,'\0',sizeof(temp));
			strncpy(temp,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			(ptr)->deviceType = temp;
			i++;
		} else if (jsoneq(Buffer, &t[i], "DEVICENAME") == 0) {
			char temp[20];
			memset(temp,'\0',sizeof(temp));
			strncpy(temp,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			(ptr)->deviceName = temp;
			i++;
		} else if (jsoneq(Buffer, &t[i], "CHANNELTITLE") == 0) {
			char temp[20];
			memset(temp,'\0',sizeof(temp));
			strncpy(temp,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			(ptr)->channeltitle = temp;
			i++;
		}else if (jsoneq(Buffer, &t[i], "VALUETYPE") == 0) {
			char temp[20];
			memset(temp,'\0',sizeof(temp));
			strncpy(temp,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			(ptr)->valueType= temp;
			i++;
		} else if (jsoneq(Buffer, &t[i], "DEVICESTATUS") == 0) {
			(ptr)->devicestatus = atoi(Buffer + t[i + 1].start);
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
   destination->deviceType = strdup(data->deviceType); // return NULL means fail
   destination->deviceName = strdup(data->deviceName);
   destination->channeltitle = strdup(data->channeltitle);
   destination->valueType = strdup(data->valueType);

}
