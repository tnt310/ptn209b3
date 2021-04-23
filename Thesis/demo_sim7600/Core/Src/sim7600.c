/*
 * sim7600.c
 *
 *  Created on: Apr 22, 2021
 *      Author: ACER
 */

#include "sim7600.h"

sim7600_packet_t sim7600;
char buffer[100];
/*------------------------------------INIT MODULE --------------------------------------------------------*/
uint8_t Init_SIM7600(void)
{
	if (sendATcommand("AT\r\n","OK",2000) == 1){
		if (sendATcommand("ATE0\r\n","OK",2000) == 1)
			(sendATcommand("AT&W\r\n","OK",2000) == 1);
	}
//	sendATcommand("AT+NETOPEN\r\n","OK",1000);
// kích chân PEN để mở nguồn module
}
/*------------------------------------CONNECT TO SERVER--------------------------------------------------------*/
uint8_t setupCONNECTION(sim7600_packet_t xsim7600)
{
	sendATcommand("AT+CMQTTSTART\r\n","OK",2000);

	createATcommand(buffer,"CMQTTACCQ");
	sendATcommand(buffer,"OK",2000);

	createATcommand(buffer,"CMQTTCONNECT");
	sendATcommand(buffer,"OK",2000);

//AT+CMQTTSTART<CR><LF>
//AT+CMQTTACCQ=0,"SIMCom_client01",1<CR><LF>
//AT+CMQTTCONNECT=0,"tcp://m14.cloudmqtt.com:19613",180,1,"yktdxpqb","VKCG6yboYrYd"<CR><LF>
}
/*------------------------------------SUBSCIBE --------------------------------------------------------*/
uint8_t Subscibe(char *sub_topic)
{
	createATcommand(buffer,"AT+CMQTTSUBTOPIC");
	sendATcommand(buffer,"OK",1000);
//	AT+CMQTTSUBTOPIC=0,9,0,1<CR><LF> // subscribed  AT+CMQTTSUB=0,9,0,1

	}
/*------------------------------------PUBLISH--------------------------------------------------------*/
uint8_t Publish(char *pub_topic, char *payload)
{
	createATcommand(buffer,"AT+CMQTTTOPIC");
	sendATcommand(buffer,"OK",1000);

	createATcommand(buffer,"AT+CMQTTPAYLOAD");
	sendATcommand(buffer,"OK",1000);

	createATcommand(buffer,"AT+CMQTTPUB");
	sendATcommand(buffer,"OK",1000);

//	AT+CMQTTTOPIC=0,21<CR><LF> // Set the topic for the PUBLISH message
//	AT+CMQTTPAYLOAD=0,38<CR><LF>// Set the payload for the PUBLISH message
//	AT+CMQTTPUB=0,1,60<CR><LF>  // Publish topic and message

	}
uint8_t Handler_err(char *err)
{

	}
