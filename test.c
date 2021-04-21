#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
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
char aux_str[100];
char server[]="tcp://m14.cloumqtt.com";
int port = 19613;
int keepalive = 180;
char username[]="yktdxpqb";
char password[]="VKCG6yboYrYd";
int state = 0;

int main()
{
    // int a =  ((sizeof(table))/(sizeof(data_t)));
    // printf("%d",a);
	snprintf(aux_str, sizeof(aux_str),"AT+CMQTTCONNECT=%d,\"%s:%d\",%d,%d,\"%s\",\"%s\"",state,server,port,keepalive,1,username,password);
	printf("%s",aux_str);
}
//	AT+CMQTTCONNECT=0,"tcp://m14.cloudmqtt.com:19613",180,1,"yktdxpqb","VKCG6yboYrYd"<CR><LF>
//  sprintf(api,"%s%c",GET,(char) 26);