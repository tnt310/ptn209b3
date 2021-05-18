///*
// * sim7600.c
// *
// *  Created on: Apr 22, 2021
// *      Author: ACER
// */
//
//#include "sim7600.h"
//#include "command.h"
//
//extern data1_t table1[] =
//{
//		0,	2,	3,	0,   "CH0_SEN2_LUME0",	"SENSOR",		"TEMPERATURE",	"NUMBER",
//		0,	2, 	3,  1, 	 "CH0_INV2_POWR1",	"SENSOR",		"HUMIDITY",	    "NUMBER",
//		0,	2,	3,	2,	 "CH0_INV2_POWR2",	"INVERTER",		"POWER",	    "NUMBER",
//		0,	2,	3,	3,	 "CH0_SEN2_TEMP3",	"SENSOR",		"LUMEN",	    "NUMBER",
//		0,	2,	3,	4,	 "CH0_INV2_RPOWR4",	"METER",	 	"CURRENT",	    "NUMBER",
//		0,	2,	3,	5,	 "CH0_INV2_POWR5",	"METER",		"VOLTAGE",	    "NUMBER",
//		0,	2,  3, 	6,	 "CH0_NOD2_RELA6",	"INVERTER",		"POWER",	    "NUMBER",
//		0,	2,	3,	7,   "CH0_SEN2_LUME7",	"SENSOR",		"TEMPERATURE",	"NUMBER",
//		0,	2, 	3,  8, 	 "CH0_INV2_POWR8",	"SENSOR",		"HUMIDITY",	    "NUMBER",
//		0,	2,	3,	9,	 "CH0_INV2_POWR9",	"INVERTER",		"POWER",	    "NUMBER",
//		0,	2,	3,	10,	 "CH0_SEN2_TEMP10",	"SENSOR",		"LUMEN",	    "NUMBER",
//		0,	2,	3,	11,	 "CH0_INV2_RPOWR11","METER",	 	"CURRENT",	    "NUMBER",
//		0,	2,	3,	12,	 "CH0_INV2_POWR12",	"METER",		"VOLTAGE",	    "NUMBER",
//		0,	2,  3, 	13,	 "CH0_NOD2_RELA13",	"INVERTER",		"POWER",	    "NUMBER",
//		0,	2,	3,	14,  "CH0_SEN2_LUME14",	"SENSOR",		"TEMPERATURE",	"NUMBER",
//		0,	2, 	3,  15,  "CH0_INV2_POWR15",	"SENSOR",		"HUMIDITY",	 	"NUMBER",
//		0,	2,	3,	16,	 "CH0_INV2_POWR16",	"INVERTER",		"POWER",	    "NUMBER",
//		0,	2,	3,	17,	 "CH0_SEN2_TEMP17",	"SENSOR",		"LUMEN",	    "NUMBER",
//		0,	2,	3,	18,	 "CH0_INV2_RPOWR18","METER",	 	"CURRENT",	   	"NUMBER",
//		0,	2,	3,	19,	 "CH0_INV2_POWR19",	"METER",		"VOLTAGE",	    "NUMBER",
//		0,	10,	6,	12,  "CH0_NOD2_RELA12",	"NODEIOT",		"LIGHT",		"BOOLEAN",
//};
//
//char *client = "gateway";
//char *server = "3.226.137.205";
//char *username = "yktdxpqb";
//char *password = "VKCG6yboYrYd";
//uint16_t port_default = 19613;
//uint8_t index = 0; // fixed
//uint8_t qos = 0; // fixed
//uint8_t cleansession = 1; // fixed
//uint8_t keepalive = 3600;
//uint8_t protocol;
//char enter[] = "\r\n";
//uint8_t main_time[6];
//char aux_str[MAX_VALUE];
//char payload[MAX_VALUE];
//
///*------------------------------------INIT MODULE --------------------------------------------------------*/
///**AT+CPIN?<CR><LF>  kiểm tra SIM
// * AT+CREG?<CR><LF>  kiểm tra đăng ký mạng
// * AT+CSQ<CR><LF>  kiểm tra chất lượng mạng
// */
//uint8_t INIT_SIM7600(void)
//{
//	volatile uint8_t  init = 0;
//	// kích chân PEN để mở nguồn module
//	if (sendATcommand("AT\r\n","OK",2000) == 1 && sendATcommand("AT\r\n","OK",2000) == 1 && sendATcommand("ATE0\r\n","OK",2000) == 1 && sendATcommand("AT&W\r\n","OK",2000))
//	{
//		init = 1;
//	}
//	else
//		for (uint8_t i = 0 ; i < 2; i++)
//		{
//			Init_SIM7600();
//		}
//	return init;
//}
///*------------------------------------CHECK SIM STATE --------------------------------------------------------*/
//uint8_t CHECK_NETSIM(void)
//{
//	volatile uint8_t netsim = 0;
//	if (sendATcommand("AT\r\n","OK",2000) == 1 && sendATcommand("AT+CPIN?\r\n","READY",2000) == 1 && sendATcommand("AT+CREG?\r\n","+CREG: 0,1",1000) == 1)
//	{
//		netsim= 1;
//	}
//	else
//		for (uint8_t i = 0 ; i < 2; i++)
//		{
//			CHECK_NETSIM();
//		}
//	return netsim;
//}
///*------------------------------------CONNECT TO SERVER--------------------------------------------------------*/
///*
// * CMQTTACCQ : 0
// * CMQTTCONNECT : 1*/
////AT+CMQTTSTART<CR><LF>
////AT+CMQTTACCQ=0,"SIMCom_client01",1<CR><LF>
////AT+CMQTTCONNECT=0,"tcp://m14.cloudmqtt.com:19613",180,1,"yktdxpqb","VKCG6yboYrYd"<CR><LF>
//
//uint8_t SETUP_CONNECTION(char *server_name,char *user_name, char *pass_word, char *port)
//{
//	uint8_t start, mqtt, connect;
//	sendATcommand_2("AT+NETOPEN\r\n","already opened","+NETOPEN: 0",2000);
//	start = sendATcommand_2("AT+CMQTTSTART\r\n","+CMQTTSTART: 0","ERROR",2000);
//	if (start == 1){
//		memset(aux_str,0,sizeof(aux_str));
//		snprintf(aux_str, sizeof(aux_str),"AT+CMQTTACCQ=%d,\"%s\"%s",index,client,enter);
//		mqtt = sendATcommand_2(aux_str,"OK","+CMQTTACCQ: 0,19",2000);
//	}
//	if (mqtt == 1){
//		memset(aux_str,0,sizeof(aux_str));
//		snprintf(aux_str, sizeof(aux_str),"AT+CMQTTCONNECT=%d,\"tcp://%s:%d\",%d,%d,\"%s\",\"%s\"%s",index,server,port,keepalive,cleansession,username,password,enter);
//		connect = sendATcommand_2(aux_str,"+CMQTTCONNECT: 0,0","+CMQTTCONNECT: 0,19",3000);
//	}
//	if (connect != 1){
//		RECONNECT();
//		SETUP_CONNECTION(server,username,password,port_default);
//	}
//}
///*------------------------------------SUBSCIBE --------------------------------------------------------*/
//// CMQTTSUBTOPIC : 2
////	AT+CMQTTSUBTOPIC=0,9,0,1<CR><LF> // subscribed  AT+CMQTTSUB=0,9,0,1
//uint8_t SUBSCRIBE(char *topic)
//{
//	uint8_t sub;
//	memset(aux_str,0,sizeof(aux_str));
//	snprintf(aux_str, sizeof(aux_str),"AT+CMQTTSUB=%d,%d,%d%s",index,strlen(topic),qos,enter);
//	if (sendATcommand(aux_str,">",2000) == 1)
//		sub = sendATcommand(topic,"+CMQTTSUB: 0,0",2000);
//}
///*------------------------------------PUBLISH--------------------------------------------------------*/
///*
// * CMQTTTOPIC : 3
// * CMQTTPAYLOAD : 4
// * CMQTTPUB : 5*/
////	AT+CMQTTTOPIC=0,21<CR><LF>  //Set the topic for the PUBLISH message
////	AT+CMQTTPAYLOAD=0,38<CR><LF>//Set the payload for the PUBLISH message
////	AT+CMQTTPUB=0,1,60<CR><LF>  //Publish topic and message
//uint8_t PUBLISH_TELEMETRY(char *topic, char *payload)
//{
//	for (uint8_t i = 0; i< DEVSUM; i++)
//	{
//		memset(aux_str,0,sizeof(aux_str));
//		snprintf(aux_str, sizeof(aux_str),"AT+CMQTTTOPIC=%d,%d%s",index,strlen(topic),enter);
//		if (sendATcommand(aux_str,">",2000) == 1)
//			sendATcommand(topic,"OK",2000);
//		memset(aux_str,0,sizeof(aux_str));
//		memset(payload,0,sizeof(payload));
//		Get_Time(main_time);
//		createJson(payload,table1[i].name,100, main_time); //---------------------------// HERE
//		snprintf(aux_str, sizeof(aux_str),"AT+CMQTTPAYLOAD=%d,%d%s",index,strlen(payload),enter);
//		if (sendATcommand(aux_str,">",2000) == 1)
//			sendATcommand(payload,"OK",2000);
//		memset(aux_str,0,sizeof(aux_str));
//		snprintf(aux_str, sizeof(aux_str),"AT+CMQTTPUB=%d,%d,%d%s",index,qos, strlen(payload)+strlen(topic), enter);
//		sendATcommand(aux_str,"+CMQTTPUB: 0,0",2000);
//		HAL_Delay(1000);
//	}
//}
///*------------------------------------CALLBACK--------------------------------------------------------*/
//void CALLBACK_COMMAND(char* topic, char* payload, uint8_t lengthofpayload)
//{
//
//	}
///*-----------------------------------------------------------------------------------------------------*/
//uint8_t RECONNECT(void)
//{
//	uint8_t state = 0;
//	sendATcommand("AT\r\n","OK",2000);
//	sendATcommand("AT\r\n","OK",2000);
//	sendATcommand("AT\r\n","OK",2000);
//	sendATcommand("AT+NETCLOSE\r\n","+NETCLOSE: 0",2000);
//	uint8_t reconnect = sendATcommand_2("AT+NETOPEN\r\n","already opened","+NETOPEN: 0",2000);
//	if(reconnect == 1)
//		return 1;
//}
///*------DISCONNECTED---------------------------------------------------------------------------------------*/
////* CMQTTDISC : 6
////* CMQTTREL : 7
//uint16_t DEVSUM(void)
//{
//	return sizeof(table1)/sizeof(data1_t);
//	}
