/*
 * sim7600.c
 *
 *  Created on: Apr 22, 2021
 *      Author: ACER
 */

#include "sim7600.h"

sim7600_packet_connection_t sim7600;
/*------------------------------------INIT MODULE --------------------------------------------------------*/
uint8_t Init_SIM7600(void)
{
	sendATcommand1("AT\r\n",1000);
	sendATcommand1("AT\r\n",1000);
//	sendATcommand("ATE0\r\n","OK",1000);
//	sendATcommand("AT&W\r\n","OK",1000);
//	sendATcommand("AT+NETOPEN\r\n","OK",1000);
//	sendATcommand("AT+IPADDR\r\n","OK",1000);
// kích chân PEN để mở nguồn module
//AT<CR><LF>
//ATE0<CR><LF>
//AT&W<CR><LF>
//AT+NETOPEN<CR><LF>
//AT+IPADDR<CR><LF>

}
/*------------------------------------CONNECT TO SERVER--------------------------------------------------------*/
uint8_t Setup_connection(char *server_name, char *port , uint16_t keep_alive)
{
	sendATcommand("AT+CMQTTSTART\r\n","OK",1000);
//	AT+CMQTTSTART<CR><LF>
//	 AT+CMQTTACCQ=0,"SIMCom_client01",1<CR><LF>
//	AT+CMQTTCONNECT=0,"tcp://m14.cloudmqtt.com:19613",180,1,"yktdxpqb","VKCG6yboYrYd"<CR><LF>
	//snprintf(aux_str, sizeof(aux_str),"AT+CMQTTCONNECT=%d,\"%s:%d\",%d,%d,\"%s\",\"%s\"",state,server,port,keepalive,1,username,password);
}
/*------------------------------------SUBSCIBE --------------------------------------------------------*/
uint8_t Subscibe(char *sub_topic)
{
//	AT+CMQTTSUBTOPIC=0,21,1<CR><LF> // Second param to CMQTTSUBTOPIC is size of topic string

	}
/*------------------------------------PUBLISH--------------------------------------------------------*/
uint8_t Publish(char *pub_topic, char *payload)
{
//	AT+CMQTTTOPIC=0,21<CR><LF> // Set the topic for the PUBLISH message
//	AT+CMQTTPAYLOAD=0,38<CR><LF>// Set the payload for the PUBLISH message
//	AT+CMQTTPUB=0,1,60<CR><LF>  // Publish topic and message

	}
