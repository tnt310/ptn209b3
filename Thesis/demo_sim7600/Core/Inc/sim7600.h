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
	char *pub_topic;
	char *sub_topic;
	uint8_t port;
	uint16_t keepalive;
	uint8_t cleansession;

}sim7600_packet_connection_t;

uint8_t Init_SIM7600(void);
uint8_t Setup_connection(char *server_name, char *port , uint16_t keep_alive);
uint8_t Subscibe(char *sub_topic);
uint8_t Publish(char *pub_topic, char *payload);


#endif /* INC_SIM7600_H_ */
