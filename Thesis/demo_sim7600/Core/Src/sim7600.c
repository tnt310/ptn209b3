/*
 * sim7600.c
 *
 *  Created on: Apr 22, 2021
 *      Author: ACER
 */

#include "sim7600.h"
#include "command.h"

char enter[] = "\r\n";
char *client = "mqtt";
char *server = "m14.cloudmqtt.com";
char *username = "yktdxpqb";
char *password = "VKCG6yboYrYd";
extern data1_t table1[] =   // CHANNEL 1
{
		2,	3,	0,  "CH1_SEN2_TEMP",	"number",		"Temperature",
		2, 	3,  1, 	"CH1_SEN2_HUMD", 	"number",		"Humidity",
		2,	3,	2,	"CH1_INV2_POWR",	"number",		"Power",
		2,	3,	3,	"CH1_SEN1_LUME",	"number",		"Lumen",
		2,	3,	4,	"CH1_INV1_CURR",	"number",		"Current",
		2,	3,	5,	"CH1_INV1_VOLT",	"number",		"Voltage",
		2,  3, 	6,	"CH1_INV1_POWR",	"number",		"Power",
		2, 	3,	7,	"CH1_INV1_RPOWR",	"number",		"React Power",
		2,	3,	8,	"CH1_SEN1_HUMD",	"number",		"Humidity",
		2,	3,	9,	"CH1_INV1_POWR",	"number",		"Power",
		2,	3,	10, "CH1_SEN2_TEMP",	"number",		"Temperature",
		2, 	3,  11, "CH1_SEN2_HUMD",	"number", 		"Humidity",
		2,	3,	12,	"CH1_INV2_POWR",	"number", 		"Power",
		2,	3,	13,	"CH1_SEN1_LUME",	"number",		"Lumen",
		2,	3,	14,	"CH1_INV1_CURR",	"number",		"Current",
		2,	3,	15,	"CH1_INV1_VOLT",	"number",		"Voltage",
		8,  3, 	16,	"CH3_INV1_POWR",	"number",		"Power",
		8, 	3,	17,	"CH3_INV1_RPOWR",	"number",		"React Power",
		8,	3,	18,	"CH3_SEN1_HUMD",	"number",		"Humidity",
		8,	3,	19,	"CH3_INV1_POWR",	"number",		"Power",
		10,	6,	8,	"CH1_INV1_FAN",		"number",		"Fan",
		10,	6,	7,	"CH1_INV3_FAN",		"number",		"Fan",
		10,	6,	6,	"CH1_NODE1_REL1",	"boolean",		"Light",
		10,	6,	5,	"CH1_NODE1_REL2",	"boolean",		"Light",
		10,	6,	4,	"CH1_NODE1_REL3",	"boolean",		"Light"
};
//char *sub = "subscribe";
//char *pub = "606ff2e222c1752264934dbb/upstream/telemetry";
//char *payload = "{CH1_INV1_SEN1:[{time:14:47:45 4.14.21,value:12345}],CH1_INV2_SEN2:[{time:14:47:45 4.14.21,value:12345}]}";
uint16_t keepalive = 3600;
uint8_t cleansession = 1;
uint8_t protocol;
uint16_t port = 19613;
uint8_t index = 0;
char buffer[100];
char aux_str[100];

uint8_t connect1;
uint8_t connect2;
uint8_t connect3;
uint8_t connect4;
uint8_t connect5;
uint8_t connect6;
uint8_t connect7;
uint8_t connect8;
/*------------------------------------INIT MODULE --------------------------------------------------------*/
/**AT+CPIN?<CR><LF>  kiểm tra SIM
 * AT+CREG?<CR><LF>  kiểm tra đăng ký mạng
 * AT+CSQ<CR><LF>  kiểm tra chất lượng mạng
 */
uint8_t Init_SIM7600(void)
{
	volatile uint8_t  status = 0;
	// kích chân PEN để mở nguồn module
	if (sendATcommand("AT\r\n","OK",2000) == 1 && sendATcommand("AT\r\n","OK",2000) == 1 && sendATcommand("ATE0\r\n","OK",2000) == 1 && sendATcommand("AT&W\r\n","OK",2000))
	{
		status = 1;
	}
	else
		for (uint8_t i = 0 ; i < 3; i++)
		{
			Init_SIM7600();}
	return status;
}
/*------------------------------------CHECK SIM STATE --------------------------------------------------------*/
uint8_t Check_NETSIMstate(void)
{
	volatile uint8_t status = 0;
	if (sendATcommand("AT\r\n","OK",2000) == 1 && sendATcommand("AT+CPIN?\r\n","READY",2000) == 1 && sendATcommand("AT+CREG?\r\n","+CREG: 0,1",1000) == 1)
	{
		status = 1;
	}
	else
		for (uint8_t i = 0 ; i < 3; i++)
		{
			Check_NETSIMstate();}
	return status;
}
/*------------------------------------CONNECT TO SERVER--------------------------------------------------------*/
/*
 * CMQTTACCQ : 0
 * CMQTTCONNECT : 1*/
uint8_t setupCONNECTION(void)
{

	connect1 = sendATcommand_2("AT+NETOPEN\r\n","already opened","+NETOPEN: 0",2000);
	connect2 = sendATcommand_2("AT+CMQTTSTART\r\n","+CMQTTSTART: 0","ERROR",2000);

	memset(aux_str,0,100);
	snprintf(aux_str, sizeof(aux_str),"AT+CMQTTACCQ=%d,\"%s\"%s",index,client,enter);
	connect3 = sendATcommand_2(aux_str,"OK","+CMQTTACCQ: 0,19",2000);

	memset(aux_str,0,100);
	snprintf(aux_str, sizeof(aux_str),"AT+CMQTTCONNECT=%d,\"tcp://%s:%d\",%d,%d,\"%s\",\"%s\"%s",index,server,port,keepalive,cleansession,username,password,enter);
	connect4 = sendATcommand_2(aux_str,"+CMQTTCONNECT: 0,0","+CMQTTCONNECT: 0,19",3000);
//AT+CMQTTSTART<CR><LF>
//AT+CMQTTACCQ=0,"SIMCom_client01",1<CR><LF>
//AT+CMQTTCONNECT=0,"tcp://m14.cloudmqtt.com:19613",180,1,"yktdxpqb","VKCG6yboYrYd"<CR><LF>
}
/*------------------------------------SUBSCIBE --------------------------------------------------------*/
// CMQTTSUBTOPIC : 2
uint8_t Subscibe(char *sub_topic)
{
	memset(aux_str,0,100);
	snprintf(aux_str, sizeof(aux_str),"AT+CMQTTSUB=%d,%d,%d,%d%s",index,strlen(sub_topic),0,1,enter);
	connect8 = sendATcommand(aux_str,">",2000);
	sendATcommand(sub_topic,"OK",2000);
//	AT+CMQTTSUBTOPIC=0,9,0,1<CR><LF> // subscribed  AT+CMQTTSUB=0,9,0,1

}
/*------------------------------------PUBLISH--------------------------------------------------------*/
/*
 * CMQTTTOPIC : 3
 * CMQTTPAYLOAD : 4
 * CMQTTPUB : 5*/
//	AT+CMQTTTOPIC=0,21<CR><LF>  //Set the topic for the PUBLISH message
//	AT+CMQTTPAYLOAD=0,38<CR><LF>//Set the payload for the PUBLISH message
//	AT+CMQTTPUB=0,1,60<CR><LF>  //Publish topic and message
uint8_t Publish(char *pub_topic, char *payload, uint8_t qos)
{
	memset(aux_str,0,100);
	snprintf(aux_str, sizeof(aux_str),"AT+CMQTTTOPIC=%d,%d%s",index,strlen(pub_topic),enter);
	connect5 = sendATcommand(aux_str,">",2000);
    sendATcommand(pub_topic,"OK",2000);

    memset(aux_str,0,100);
    snprintf(aux_str, sizeof(aux_str),"AT+CMQTTPAYLOAD=%d,%d%s",index,strlen(payload),enter);
    connect6 = sendATcommand(aux_str,">",2000);
    sendATcommand(payload,"OK",2000);

    memset(aux_str,0,100);
    snprintf(aux_str, sizeof(aux_str),"AT+CMQTTPUB=%d,%d,%d%s",index,qos, strlen(payload)+strlen(pub_topic), enter);
    connect7 = sendATcommand(aux_str,"+CMQTTPUB: 0,0",2000);
	}
//uint8_t reconnect(void)
//{
//	sendATcommand(sendATcommand("AT\r\n","OK",2000));
//	sendATcommand(sendATcommand("AT\r\n","OK",2000));
	//Init_SIM7600();
	//Check_NETSIMstate();
//	}
/*------DISCONNECTED---------------------------------------------------------------------------------------*/
//* CMQTTDISC : 6
//* CMQTTREL : 7
