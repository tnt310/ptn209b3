/*
 * sim7600.c
 *
 *  Created on: Apr 22, 2021
 *      Author: ACER
 */

#include "sim7600.h"
#include "command.h"

extern data1_t table1[] =
{
		0,	2,	3,	0,   "CH0_SEN2_LUME0",	"SENSOR",		"TEMPERATURE",	"NUMBER",
		0,	2, 	3,  1, 	 "CH0_INV2_POWR1",	"SENSOR",		"HUMIDITY",	    "NUMBER",
		0,	2,	3,	2,	 "CH0_INV2_POWR2",	"INVERTER",		"POWER",	    "NUMBER",
		0,	2,	3,	3,	 "CH0_SEN2_TEMP3",	"SENSOR",		"LUMEN",	    "NUMBER",
		0,	2,	3,	4,	 "CH0_INV2_RPOWR4",	"METER",	 	"CURRENT",	    "NUMBER",
		0,	2,	3,	5,	 "CH0_INV2_POWR5",	"METER",		"VOLTAGE",	    "NUMBER",
		0,	2,  3, 	6,	 "CH0_NOD2_RELA6",	"INVERTER",		"POWER",	    "NUMBER",
		0,	2,	3,	7,   "CH0_SEN2_LUME7",	"SENSOR",		"TEMPERATURE",	"NUMBER",
		0,	2, 	3,  8, 	 "CH0_INV2_POWR8",	"SENSOR",		"HUMIDITY",	    "NUMBER",
		0,	2,	3,	9,	 "CH0_INV2_POWR9",	"INVERTER",		"POWER",	    "NUMBER",
		0,	2,	3,	10,	 "CH0_SEN2_TEMP10",	"SENSOR",		"LUMEN",	    "NUMBER",
		0,	2,	3,	11,	 "CH0_INV2_RPOWR11","METER",	 	"CURRENT",	    "NUMBER",
		0,	2,	3,	12,	 "CH0_INV2_POWR12",	"METER",		"VOLTAGE",	    "NUMBER",
		0,	2,  3, 	13,	 "CH0_NOD2_RELA13",	"INVERTER",		"POWER",	    "NUMBER",
		0,	2,	3,	14,  "CH0_SEN2_LUME14",	"SENSOR",		"TEMPERATURE",	"NUMBER",
		0,	2, 	3,  15,  "CH0_INV2_POWR15",	"SENSOR",		"HUMIDITY",	 	"NUMBER",
		0,	2,	3,	16,	 "CH0_INV2_POWR16",	"INVERTER",		"POWER",	    "NUMBER",
		0,	2,	3,	17,	 "CH0_SEN2_TEMP17",	"SENSOR",		"LUMEN",	    "NUMBER",
		0,	2,	3,	18,	 "CH0_INV2_RPOWR18","METER",	 	"CURRENT",	   	"NUMBER",
		0,	2,	3,	19,	 "CH0_INV2_POWR19",	"METER",		"VOLTAGE",	    "NUMBER",
};

uint8_t index = 0; // fixed
uint8_t cleansession = 1; // fixed
uint8_t main_time[6];
char aux_str[MAX_VALUE];
/*------------------------------------INIT MODULE --------------------------------------------------------*/
/**AT+CPIN?<CR><LF>  kiểm tra SIM
 * AT+CREG?<CR><LF>  kiểm tra đăng ký mạng
 * AT+CSQ<CR><LF>  kiểm tra chất lượng mạng
 */
uint8_t INIT_SIM7600(void)
{
	sendATcommand("AT\r\n",1000);
	sendATcommand("AT\r\n",1000);
	sendATcommand("ATE0\r\n",1000);
	sendATcommand("AT&W\r\n",1000);
}
/*------------------------------------CONNECT TO SERVER--------------------------------------------------------*/
/*
 * CMQTTACCQ : 0
 * CMQTTCONNECT : 1*/
//AT+CMQTTSTART<CR><LF>
//AT+CMQTTACCQ=0,"SIMCom_client01",1<CR><LF>
//AT+CMQTTCONNECT=0,"tcp://m14.cloudmqtt.com:19613",180,1,"yktdxpqb","VKCG6yboYrYd"<CR><LF>

uint8_t SIM7600_NEW_CONNECTION(char *client,char *server,char *user, char *pass, uint16_t port, uint16_t keepalive)
{
//	uint8_t start, mqtt, connect, reconnect;
//	sendATcommand("AT\r\n",1000);
//	sendATcommand("AT\r\n",1000);
//	sendATcommand("AT+NETOPEN\r\n",1000);
//	sendATcommand("AT+CMQTTSTART\r\n",1000);
//	memset(aux_str,0,sizeof(aux_str));
//	snprintf(aux_str, sizeof(aux_str),"AT+CMQTTACCQ=%d,\"%s\"%s",index,client,"\r\n");
//	sendATcommand(aux_str,1000);
//
//	memset(aux_str,0,sizeof(aux_str));
//	snprintf(aux_str, sizeof(aux_str),"AT+CMQTTCONNECT=%d,\"tcp://%s:%d\",%d,%d,\"%s\",\"%s\"%s",index,server,port,keepalive,cleansession,user,pass,"\r\n");
//	connect = sendATcommand2(aux_str,"+CMQTTCONNECT: 0,0","+CMQTTCONNECT: 0,19",3000);
//	if (connect != 1){
//		sendATcommand("AT\r\n",1000);
//		reconnect = RECONNECT();
//		if ( reconnect == 1){
//			sendATcommand("AT\r\n",1000);
//			sendATcommand("AT+CMQTTSTART\r\n",1000);
//			memset(aux_str,0,sizeof(aux_str));
//			snprintf(aux_str, sizeof(aux_str),"AT+CMQTTACCQ=%d,\"%s\"%s",index,client,"\r\n");
//			sendATcommand(aux_str,1000);
//			memset(aux_str,0,sizeof(aux_str));
//			snprintf(aux_str, sizeof(aux_str),"AT+CMQTTCONNECT=%d,\"tcp://%s:%d\",%d,%d,\"%s\",\"%s\"%s",index,server,port,keepalive,cleansession,user,pass,"\r\n");
//			sendATcommand2(aux_str,"+CMQTTCONNECT: 0,0","+CMQTTCONNECT: 0,19",3000);
//		}
//	}
	uint8_t start, mqtt, connect;
	sendATcommand("AT+NETOPEN\r\n",1000);
	sendATcommand("AT+CMQTTSTART\r\n",1000);

	memset(aux_str,0,sizeof(aux_str));
	snprintf(aux_str, sizeof(aux_str),"AT+CMQTTACCQ=%d,\"%s\"%s",index,client,"\r\n");
	sendATcommand(aux_str,1000);

	memset(aux_str,0,sizeof(aux_str));
	snprintf(aux_str, sizeof(aux_str),"AT+CMQTTCONNECT=%d,\"tcp://%s:%d\",%d,%d,\"%s\",\"%s\"%s",index,server,port,keepalive,cleansession,user,pass,"\r\n");
	connect = sendATcommand2(aux_str,"+CMQTTCONNECT: 0,0","+CMQTTCONNECT: 0,19",3000);
	if (connect != 1){
		sendATcommand("AT\r\n",1000);
		sendATcommand("AT+NETCLOSE\r\n",1000);
		RECONNECT();
	}
}
/*-----------------------------------------------------------------------------------------------------*/
uint8_t RECONNECT(void)
{
	uint8_t state = 0;
	sendATcommand("AT\r\n",1000);
	sendATcommand("AT\r\n",1000);
	sendATcommand("AT+CMQTTDISC=0,120\r\n",1000);
	sendATcommand("AT+CMQTTREL=0\r\n",1000);
	sendATcommand("AT+CMQTTSTOP\r\n",1000);
	sendATcommand1("AT+NETCLOSE\r\n","+NETCLOSE: 0",2000);
	uint8_t reconnect = sendATcommand2("AT+NETOPEN\r\n","+NETOPEN: 0","already opened",2000);
	if(reconnect == 1)
		state = 1;
	return state;
}
/*------------------------------------SUBSCIBE --------------------------------------------------------*/
// CMQTTSUBTOPIC : 2
//	AT+CMQTTSUBTOPIC=0,9,0<CR><LF> // subscribed  AT+CMQTTSUB=0,9,0
uint8_t SUBSCRIBE(char *topic, uint8_t qos)
{
	memset(aux_str,0,sizeof(aux_str));
	snprintf(aux_str, sizeof(aux_str),"AT+CMQTTSUB=%d,%d,%d%s",index,strlen(topic),qos,"\r\n");
	if (sendATcommand1(aux_str,">",2000) == 1)
		sendATcommand(topic,1000);
}
/*------------------------------------PUBLISH--------------------------------------------------------*/
/*
 * CMQTTTOPIC : 3
 * CMQTTPAYLOAD : 4
 * CMQTTPUB : 5*/
//	AT+CMQTTTOPIC=0,21<CR><LF>  //Set the topic for the PUBLISH message
//	AT+CMQTTPAYLOAD=0,38<CR><LF>//Set the payload for the PUBLISH message
//	AT+CMQTTPUB=0,1,60<CR><LF>  //Publish topic and message
uint8_t SIM7600_PUBLISH_PACKET(char *topic, uint8_t qos)
{
//	char *payload;
//	uint16_t sum = DEVSUM();
//	static uint16_t count = 0;
//	for (uint16_t count = 0; count < (sum - 1); count ++)
//	{
//		memset(aux_str,0,sizeof(aux_str));
//		snprintf(aux_str, sizeof(aux_str),"AT+CMQTTTOPIC=%d,%d%s",index,strlen(topic),"\r\n");
//		sendATcommand(aux_str,2000);
//		sendATcommand(topic,2000);
//
//		memset(aux_str,0,sizeof(aux_str));
//		memset(payload,0,sizeof(payload));
//		Get_Time(main_time);
//		createJson(payload,table1[count].name,100);
//		snprintf(aux_str, sizeof(aux_str),"AT+CMQTTPAYLOAD=%d,%d%s",index,strlen(payload),"\r\n");
//		sendATcommand(aux_str,2000);
//		sendATcommand(payload,2000);
//
//		memset(aux_str,0,sizeof(aux_str));
//		snprintf(aux_str, sizeof(aux_str),"AT+CMQTTPUB=%d,%d,%d%s",index,qos, strlen(payload)+strlen(topic),"\r\n");
//		sendATcommand(aux_str,1000);
//	}
	char payload[200];
	for (uint8_t i = 0; i< 20; i++)
	{
		memset(aux_str,0,sizeof(aux_str));
		snprintf(aux_str, sizeof(aux_str),"AT+CMQTTTOPIC=%d,%d%s",index,43,"\r\n");
		sendATcommand(aux_str,1000);
		sendATcommand("upstream/telemetry/608a78baaa969877dec4e6f4",1000);

		memset(aux_str,0,sizeof(aux_str));
		createJson(payload,table1[i].name,100);
		snprintf(aux_str, sizeof(aux_str),"AT+CMQTTPAYLOAD=%d,%d%s",index,strlen(payload),"\r\n");
		sendATcommand(aux_str,1000);
		sendATcommand(payload,1000);

		memset(aux_str,0,sizeof(aux_str));
		snprintf(aux_str, sizeof(aux_str),"AT+CMQTTPUB=%d,%d,%d%s",index,qos,strlen(payload)+strlen(topic),"\r\n");
		sendATcommand(aux_str,1000);
	}
}
/*------------------------------------CALLBACK--------------------------------------------------------*/
void CALLBACK_COMMAND(char* topic, char* payload, uint8_t lengthofpayload)
{

	}
uint16_t DEVSUM(void)
{
	return sizeof(table1)/sizeof(data1_t);
	}
