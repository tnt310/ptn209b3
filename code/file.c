#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "telemetry.h"
#include "json.h"

/* Shared Variables --------------------------*/
// data1_t *ptr;
/* Private Variables -------------------------*/
/* Start implementation ----------------------*/
static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start
			&& strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}
/*------------------------------------------------------------------------------------------------------------------------------*/
data1_t *parse_device(char *Buffer, uint16_t BufferLen)
{
    #define JSON_MAX_LEN 200
    int i,r;
    static data1_t *ptr, data;
    ptr = &data;
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
			(*ptr).channel = atoi(Buffer + t[i + 1].start);
            //printf("\nPORT = %d\t",ptr->channel);
			i++;

		} else if (jsoneq(Buffer, &t[i], "ID") == 0) {
			(*ptr).deviceID = atoi(Buffer + t[i + 1].start);
            //printf("ID = %d\t",ptr->deviceID);
			i++;
		} else if (jsoneq(Buffer, &t[i], "FC") == 0) {
			(*ptr).func = atoi(Buffer + t[i + 1].start);
            //printf("FC = %d\t",ptr->func);
			i++;

		} else if (jsoneq(Buffer, &t[i], "CHANNEL") == 0) {
            char temp[20];
			memset(temp,'\0',sizeof(temp));
            strncpy(temp,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
            (*ptr).deviceChannel = (uint16_t)strtol(temp, NULL, 0);
            //printf("CHANNEL: %d\t",ptr->deviceChannel);
			i++;
		} else if (jsoneq(Buffer, &t[i], "DEVICETYPE") == 0) {
            char temp[20];
			memset(temp,'\0',sizeof(temp));
            strncpy(temp,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
            (*ptr).deviceType = temp;
            //printf("DEVICETYPE: %s\t",ptr->deviceType);
			i++;
		} else if (jsoneq(Buffer, &t[i], "DEVICENAME") == 0) {
            char temp[20];
			memset(temp,'\0',sizeof(temp));
            strncpy(temp,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
            (*ptr).deviceName = temp;
            //printf("DEVICENAME: %s\t",ptr->deviceName);
			i++;
		} else if (jsoneq(Buffer, &t[i], "CHANNELTITLE") == 0) {
            char temp[20];
			memset(temp,'\0',sizeof(temp));
            strncpy(temp,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
            (*ptr).channeltitle = temp;
            //printf("CHANNELTITLE: %s\t",ptr->channeltitle);
			i++;
		}else if (jsoneq(Buffer, &t[i], "VALUETYPE") == 0) {
            char temp[20];
			memset(temp,'\0',sizeof(temp));
            strncpy(temp,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
            (*ptr).valueType= temp;
            //printf("VALUETYPE: %s\t",ptr->valueType);
			i++;
		} else if (jsoneq(Buffer, &t[i], "DEVICESTATUS") == 0) {
			//printf("DEVICESTATUS: %.*s\t", t[i + 1].end - t[i + 1].start,Buffer + t[i + 1].start);
			(*ptr).devicestatus = atoi(Buffer + t[i + 1].start);
            i++;
		}
	}
    return ptr;
}
void AddDevice(data1_t *destination, data1_t *data)
{
    // static data1_t temp;
    // data = &temp;
    // destination->channel = data->channel;
    // destination->deviceID = data->deviceID;
    // destination->func = data->func;
    // destination->devicestatus = data->devicestatus;
    // destination->deviceChannel = data->deviceChannel;
    // printf("\nlen of device type: %d",strlen(data->deviceType));
    // printf("\nlen of device type: %d",strlen(data->deviceName));
    // printf("\nlen of device type: %d",strlen(data->channeltitle));
    // printf("\nlen of device type: %d\n",strlen(data->valueType));
    // destination->deviceType = data->deviceType;
    // destination->deviceName = data->deviceName;
    // destination->channeltitle = data->channeltitle;
    // destination->valueType = data->valueType;
    // destination->deviceType = "INVERTER";
    // destination->deviceName = "INVERTER-01";
    // destination->channeltitle = "VOLATGE";
    // destination->valueType = "NUMBER";
    //  printf("\nLine : %d\t%d\t%d\t%d\t%s\t%s\t%s\t%s\t%d",destination->channel,destination->deviceID,
    //         destination->func,destination->deviceChannel,destination->deviceType, destination->deviceName,
    //         destination->channeltitle,destination->valueType, destination->devicestatus);
}
void assign(char *destination, char *source)
{
    destination = malloc(strlen(source)+1);
    strcpy(destination, source);
}
void LoadDevice(void)
{
    static data1_t *dynamic;
    static data1_t *p, temp;
    FILE *file;
    char line[200];
    static uint8_t k = 0;
    static uint8_t j = 0;
    file = fopen("DEVICE.TXT","r");
    while(fgets(line,200,file)){
        k++;
    }
    fclose(file);
    printf("\nnum of line k = %d",k);
    dynamic = (data1_t*)calloc(k,sizeof(data1_t));
    if (dynamic!=NULL){
        file = fopen("DEVICE.TXT","r");
        while(fgets(line,200,file)){
            p = parse_device((char*)line, strlen(line));
            //AddDevice((dynamic+j),p);
            (dynamic+j)->channel = p->channel;
            (dynamic+j)->deviceID = p->deviceID;
            (dynamic+j)->func = p->func;
            (dynamic+j)->devicestatus = p->devicestatus;
            (dynamic+j)->deviceChannel = p->deviceChannel;
            (dynamic+j)->deviceType = p->deviceType;
            (dynamic+j)->deviceName = p->deviceName;
            (dynamic+j)->channeltitle = p->channeltitle;
            (dynamic+j)->valueType = p->valueType;
            // assign((dynamic+j)->deviceType ,(p->deviceType));
            // assign((dynamic+j)->deviceName,(p->deviceName));
            // assign((dynamic+j)->channeltitle ,(p->channeltitle));
            // assign((dynamic+j)->valueType ,(p->valueType));
            // (dynamic+j)->deviceType = "INVERTER";
            // (dynamic+j)->deviceName = "INVERTER_01";
            // (dynamic+j)->channeltitle = "VOLATGE";
            // (dynamic+j)->valueType = "NUMBER";


            // printf("\nline %d: %d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",j,
            //         &(dynamic+j)->channel,&(dynamic+j)->deviceID,&(dynamic+j)->func,&(dynamic+j)->devicestatus,
            //         &(dynamic+j)->deviceChannel,&(dynamic+j)->deviceType,&(dynamic+j)->deviceName,
            //         &(dynamic+j)->channeltitle,&(dynamic+j)->valueType);
            printf("\nLine %d: %d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\t%s",j,
                    (dynamic+j)->channel,(dynamic+j)->deviceID,(dynamic+j)->func,(dynamic+j)->devicestatus,
                    (dynamic+j)->deviceChannel,(dynamic+j)->deviceType,(dynamic+j)->deviceName,
                    (dynamic+j)->channeltitle,(dynamic+j)->valueType);
            // printf("\nLine %d: %d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\t%s",j,
            //         p->channel,p->deviceID,p->func,p->devicestatus,
            //         p->deviceChannel,p->deviceType,p->deviceName,p->channeltitle,p->valueType);
            j++;
        }
        fclose(file);
    }
    printf("\n\n----------------DEVICES ADDRESS WERE ADDED TO DYNAMIC ARRAY--------------------------------");
    //     for (uint8_t i = 0; i < k; i++){
    //     printf("\nLine %d: %d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",i,
    //             &(dynamic+i)->channel,&(dynamic+i)->deviceID,&(dynamic+i)->func,&(dynamic+i)->devicestatus,
    //             &(dynamic+i)->deviceChannel,&(dynamic+i)->deviceType,&(dynamic+i)->deviceName,
    //             &(dynamic+i)->channeltitle,&(dynamic+i)->valueType);
    // }
    printf("\n\n----------------DEVICES VALUE WERE ADDED TO DYNAMIC ARRAY--------------------------------");
        for (uint8_t i = 1; i < k; i++){
            printf("\nLine %d: %d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\t%s",i,
                    (dynamic+i)->channel,(dynamic+i)->deviceID,(dynamic+i)->func,(dynamic+i)->devicestatus,
                    (dynamic+i)->deviceChannel,(dynamic+i)->deviceType,(dynamic+i)->deviceName,
                    (dynamic+i)->channeltitle,(dynamic+i)->valueType);
        }
    free(dynamic);
}
int main()
{
    LoadDevice();
}

