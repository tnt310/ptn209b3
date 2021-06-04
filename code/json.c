/* Built-in C library includes ---------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
/* Platform includes --------------------------*/
#include "main.h"
#include "json.h"
#include "telemetry.h"
/* Shared Variables --------------------------*/
/* Private Variables -------------------------*/
#define JSON_MAX_LEN 200
char temp[20];
int i;
int r;
/* Start implementation ----------------------*/
static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start
			&& strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}
/*------------------------------------------------------------------------------------------------------------------------------*/

uint8_t parse(char *Buffer,uint16_t BufferLen, data1_t *p){

	jsmn_parser p;
	jsmntok_t t[JSON_MAX_LEN]; /* We expect no more than JSON_MAX_LEN tokens */
	jsmn_init(&p);
	r = jsmn_parse(&p, Buffer,BufferLen, t,sizeof(t) / sizeof(t[0]));
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
		if (jsoneq(Buffer, &t[i], "PORT") == 0) {
			printf("\r\nPORT: %.*s\t", t[i + 1].end - t[i + 1].start,Buffer + t[i + 1].start);
			//data.port= atoi(pJsonMQTTBuffer + t[i + 1].start);
			i++;

		} else if (jsoneq(Buffer, &t[i], "ID") == 0) {
			printf("ID: %.*s\t", t[i + 1].end - t[i + 1].start,Buffer + t[i + 1].start);
			//data.deviceID = atoi(pJsonMQTTBuffer + t[i + 1].start);
			i++;

		} else if (jsoneq(Buffer, &t[i], "FC") == 0) {
			printf("FC: %.*s\t", t[i + 1].end - t[i + 1].start,Buffer + t[i + 1].start);
			//data.func = atoi(pJsonMQTTBuffer + t[i + 1].start);
			i++;

		} else if (jsoneq(Buffer, &t[i], "CHANNEL") == 0) {
			printf("CHANNEL: %.*s\t", t[i + 1].end - t[i + 1].start,Buffer + t[i + 1].start);
			//data.deviceChannel= atoi(pJsonMQTTBuffer + t[i + 1].start);
			i++;

		} else if (jsoneq(Buffer, &t[i], "DEVICETYPE") == 0) {
			printf("DEVICETYPE: %.*s\t", t[i + 1].end - t[i + 1].start,Buffer + t[i + 1].start);
			//data.deviceType = *(pJsonMQTTBuffer + t[i + 1].start);
			i++;

		} else if (jsoneq(Buffer, &t[i], "DEVICENAME") == 0) {
			printf("DEVICENAME: %.*s\t", t[i + 1].end - t[i + 1].start,Buffer + t[i + 1].start);
			//data.deviceName = *(pJsonMQTTBuffer + t[i + 1].start);
			i++;

		} else if (jsoneq(Buffer, &t[i], "CHANNELTITLE") == 0) {
			printf("CHANNELTITLE: %.*s\t", t[i + 1].end - t[i + 1].start,Buffer + t[i + 1].start);
			//data.deviceTitle = *(pJsonMQTTBuffer + t[i + 1].start);
			i++;
		}else if (jsoneq(Buffer, &t[i], "VALUETYPE") == 0) {
			printf("VALUETYPE: %.*s\t", t[i + 1].end - t[i + 1].start,Buffer + t[i + 1].start);
			//data.valueType = *(pJsonMQTTBuffer + t[i + 1].start);
			i++;

		} else if (jsoneq(Buffer, &t[i], "DEVICESTATUS") == 0) {
			printf("DEVICESTATUS: %.*s\t", t[i + 1].end - t[i + 1].start,Buffer + t[i + 1].start);
			//data.deviceStatus = atoi(pJsonMQTTBuffer + t[i + 1].start);
			i++;
		}
	}
}


