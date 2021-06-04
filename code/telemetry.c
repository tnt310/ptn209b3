#include <stdio.h>
#include <string.h>
#include <stdint.h>
// #include "telemetry.h"
//#include "main.h"

#define SUM 31
typedef struct{
    uint8_t channel;
    uint8_t deviceID;
    uint8_t func;
    uint16_t deviceChannel;
    char *deviceType;
    char *deviceName;
    char *deviceTitle;
    char *valueType;
}data1_t;
data1_t table1[] =
{
		0,	2,	3,	0x00,   "INVERTER",		        "INVERTER_01",		"VOLTAGE",	    "NUMBER",
		0,	2, 	3,  0x01, 	"INVERTER",		        "INVERTER_01",		"CURRENT",	    "NUMBER",
		0,	2,	3,	0x02,	"INVERTER",		        "INVERTER_01",		"POWER",	    "NUMBER",
        0,	2, 	3,  0x03, 	"INVERTER",		        "INVERTER_01",		"CURRENT",	    "NUMBER",
		0,	2,	3,	0x04,	"INVERTER",		        "INVERTER_01",		"POWER",	    "NUMBER",

        0,	6,	3,	0x03,   "WEATHERSTATION",		"STATION_01",		"TEMPERATURE",	"NUMBER",
		0,	6,	3,	0x04,   "WEATHERSTATION",		"STATION_01",		"HUMIDITY",	    "NUMBER",
		0,	6, 	3,  0x05, 	"WEATHERSTATION",		"STATION_01",		"LUMEN",	    "NUMBER",

        0,	3,	3,	0x03,   "WEATHERSTATION",		"STATION_02",		"TEMPERATURE",	"NUMBER",
		0,	3,	3,	0x04,   "WEATHERSTATION",		"STATION_02",		"HUMIDITY",	    "NUMBER",
		0,	3, 	3,  0x05, 	"WEATHERSTATION",		"STATION_02",		"LUMEN",	    "NUMBER",
};
/*-----------------------------------------------------------------------------------------------*/
uint8_t ping_json(char *buffer, uint8_t id_gateway)
{
    memset(buffer,0,sizeof(buffer));
    sprintf(buffer,"{\"gateway\":%d,\"message\":\"HELLO SERVER\"}",id_gateway);
}
/*-----------------------------------------------------------------------------------------------*/
uint8_t command_json(char *buffer,uint8_t device_id, uint16_t device_channel,uint16_t value)
{
    memset(buffer,0,sizeof(buffer));
    sprintf(buffer,"{\"data\":{\"%d\":{\"%d\":%d}}}",device_id,device_channel,value);
}
/*-----------------------------------------------------------------------------------------------*/
uint8_t head_telemetry(char *buffer, uint8_t time[6], uint8_t device_id)
{
    memset(buffer,'\0',sizeof(buffer));
    sprintf(buffer,"{\"timestamp\":\"%d-%d-%dT%d:%d:%d.000Z\",\"data\":{\"%d\":",time[0],time[1],time[2],time[3],time[4],time[5],device_id);
}
uint8_t tail_telemetry(char *buffer, uint16_t device_channel, uint16_t value) //
{
    memset(buffer,'\0',sizeof(buffer));
    sprintf(buffer,"{\"%d\":%d,",device_channel, value);
    //strcat(buffer,",");
}
/*-----------------------------------------------------------------------------------------------*/
uint8_t  head_provision(char *buffer,uint8_t device_id, char *device_name, char *device_type)
{
    memset(buffer,'\0',sizeof(buffer));
    sprintf(buffer,"{\"data\":[{\"device_id\":\"%d\",\"device_name\":\"%s\",\"device_kind\":\"%s\",\"device_channels\":[",device_id,device_name,device_type);
}
uint8_t  tail_provision(char *buffer,uint16_t channel_id, char *channel_name, char *channel_type, uint8_t function)
{
    memset(buffer,'\0',sizeof(buffer));
    sprintf(buffer,"{\"channel_id\":%d,\"channel_name\":\"%s\",\"channel_type\":\"%s\",\"channel_commands\":{",channel_id,channel_name,channel_type);
	if(function == 3){
		strcat(buffer,"\"READ\":[]}");
	}
	if(function == 6){
		strcat(buffer,"\"WRITE\":[]}");
	}
    strcat(buffer,"},");
}
/*-----------------------------------------------------------------------------------------------*/
uint8_t topic(char *buffer, char *apikey, char *topic, char *flow_type)
{
	memset(buffer,'\0',sizeof(buffer));
	sprintf(buffer,"%s/%s/%s",flow_type,topic,apikey);
}
// int main()
// {
//     char head[1000];
//     char tail[500];
//     char id[SUM];
//     static uint8_t count = 0;
//     static uint8_t count_t = 0;
// 				    for (uint8_t i = 0; i < SUM; i++)// duyệt từng phần tử trong mảng
// 				    {
// 				        for (uint8_t j = 0; j < SUM; j++)  // duyệt ID device
// 				        {
// 				            if (table1[j].deviceID == table1[i].deviceID && table1[i].deviceID != table1[i-1].deviceID){
// 				                    count ++;
// 				                    if (count == 1){
// 				                        if (i > 0){
// 				                        for (uint8_t a = 0; a < i; a++){
// 				                             if (table1[a].deviceID == table1[j].deviceID){
// 				                                goto TEST;
// 				                                }
// 				                            }
// 				                        }
// 				                        head_provision(head,table1[j].deviceID,table1[j].deviceName,table1[j].deviceType);
// 				                        for (uint8_t z = 0; z < SUM; z++)  // duyệt channel ID
// 				                        {
// 				                            if (table1[z].deviceID == table1[j].deviceID ){
// 				                            	tail_provision(tail,table1[z].deviceChannel,table1[z].deviceTitle,table1[z].valueType, table1[z].func);
// 				                                strcat(head,tail);
// 				                            }
// 				                        }
// 				                        head[strlen(head) - 1] = '\0';
// 				                        strcat(head,"]}]}");
// 				                        printf("\n%s\n",head);
// 				                        memset(head,'\0',sizeof(head));
// 				                    }
// 				            }
// 				        }
// 				        TEST: count = 0;
// 				    }
// }
/*-----------------------------------------------------------------------------------------------*/

