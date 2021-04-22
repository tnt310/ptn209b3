#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
typedef struct{ // STRUCT DATA FROM EEPROM
    int id; // id
    int func;
    int  reg_adr; // Adress reg
    char name_reg[10]; // name of address reg
    char name_dev[10];
} data_t;

extern data_t table[] =   // CHANNEL 1
{
		3,	3,	0,	"TEMP", 	"INV1",
		3, 	3,  1,	"HUMD", 	"SENSOR2",
		3,	3,	2,	"POWR",		"METER1",
		3,	3,	3,	"LUME", 	"SENSOR4",
		3,	3,	4,	"CURR", 	"INV2",
		3,	3,	5,	"VOLT", 	"INV3",
		3,  3, 	6,	"POWR", 	"INV2",
		3, 	3,	7,	"RPOW",		"INV8",
		3,	3,	8,	"HUMD",		"SENSOR7",
		3,	3,	9,	"POWR",		"METER1"

};
uint16_t port = 19613;
uint16_t keepalive = 180;
uint8_t index = 0;
uint8_t protocol = 1;
uint8_t cleansession = 1;
uint8_t timeout = 120;
char aux_str[100];
char server[]="tcp://m14.cloumqtt.com";
char username[]="yktdxpqb";
char password[]="VKCG6yboYrYd";
char client[] = "client";
char enter[] = "\r\n";
char sub[] = "subscribe";
char pub[] = "606ff2e222c1752264934dbb/upstream/telemetry";
char payload[] = "{CH1_INV1_SEN1:[{time:14:47:45 4.14.21,value:12345}],CH1_INV2_SEN2:[{time:14:47:45 4.14.21,value:12345}]}";


// 1. AT+NETOPEN<CR><LF>
// 2. AT+IPADDR<CR><LF>
// 3. AT+CMQTTSTART<CR><LF>
//	AT+CMQTTCONNECT=0,"tcp://m14.cloudmqtt.com:19613",180,1,"yktdxpqb","VKCG6yboYrYd"<CR><LF>
//  sprintf(api,"%s%c",GET,(char) 26);
// AT+CMQTTACCQ=0,"SIMCom_client01",1<CR><LF>
// AT+CMQTTSUBTOPIC=0,9,0,1<CR><LF>
// AT+CMQTTTOPIC=0,43<CR><LF>
// AT+CMQTTPAYLOAD=0,105<CR><LF>
// AT+CMQTTPUB=0,1,148<CR><LF>
// #DISCONNECT AND RELEASE MQTT CLIENT
// 11. AT+CMQTTDISC=0,120<CR><LF> // Disconnect from server
// 12. AT+CMQTTREL=0<CR><LF> // release a client
// 13. AT+CMQTTSTOP<CR><LF> //stop MQTT Service
// 14. AT+NETCLOSE<CR><LF>
int main()
{
	//snprintf(aux_str, sizeof(aux_str),"AT+NETOPEN%s",enter);
	//snprintf(aux_str, sizeof(aux_str),"AT+IPADDR%s",enter);
	//snprintf(aux_str, sizeof(aux_str),"AT+CMQTTSTART%s",enter);
	//snprintf(aux_str, sizeof(aux_str),"AT+CMQTTACCQ=%d,\"%s\",%d%s",index,client,protocol,enter);
	//snprintf(aux_str, sizeof(aux_str),"AT+CMQTTCONNECT=%d,\"%s:%d\",%d,%d,\"%s\",\"%s\"%s",index,server,port,keepalive,1,username,password,enter);
	
	//snprintf(aux_str, sizeof(aux_str),"AT+CMQTTSUBTOPIC=%d,%d,%d,%d%s",index,strlen(sub),protocol,cleansession,enter);
	
	//snprintf(aux_str, sizeof(aux_str),"AT+CMQTTTOPIC=%d,%d%s",index,strlen(pub),enter);
	//snprintf(aux_str, sizeof(aux_str),"AT+CMQTTPAYLOAD=%d,%d%s",index,strlen(payload),enter);
	//snprintf(aux_str, sizeof(aux_str),"AT+CMQTTPUB=%d,%d,%d%s",index,protocol,strlen(payload)+strlen(pub),enter);

	//snprintf(aux_str, sizeof(aux_str),"AT+CMQTTDISC=%d,%d%s",index,timeout,enter);
	//snprintf(aux_str, sizeof(aux_str),"AT+CMQTTREL=%d%s",index,enter);
	//snprintf(aux_str, sizeof(aux_str),"AT+CMQTTSTOP%s",enter);
	//snprintf(aux_str, sizeof(aux_str),"AT+NETCLOSE%s",enter);
	printf("%s",aux_str);
}
