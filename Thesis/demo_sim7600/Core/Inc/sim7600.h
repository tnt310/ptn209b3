/*
 * sim7600.h
 *
 *  Created on: Apr 22, 2021
 *      Author: ACER
 */

#ifndef INC_SIM7600_H_
#define INC_SIM7600_H_

#include <stdint.h>



typedef struct
{
	char *client_name;
	char *server_name;
	char *username;
	char *password;
	char *pub_topic;
	char *sub_topic;
	uint16_t port;
	uint16_t keepalive;
	uint8_t cleansession;
	uint8_t index_client;
	uint8_t protocol;
	uint8_t qos;
	uint16_t timeout;

}sim7600_packet_t;

uint8_t Init_SIM7600(void);
uint8_t Setup_connection(char *server_name, char *port , uint16_t keep_alive);
uint8_t Subscibe(char *sub_topic);
uint8_t unSubscibe(char *sub_topic);
uint8_t Publish(char *pub_topic, char *payload);
uint8_t Disconnected(uint8_t index);
uint8_t Handler_err(char *err);

#endif /* INC_SIM7600_H_ */
