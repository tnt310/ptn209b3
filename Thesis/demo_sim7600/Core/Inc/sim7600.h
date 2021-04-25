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
typedef struct{ // STRUCT DATA FROM EEPROM
    uint8_t id; // id
    uint8_t func; // function code
    uint16_t reg_adr; // Adress reg
    char *name_dev;// name of address device
    char *type;
    char *name; // name of address reg
}data1_t;
extern data1_t table1[];
extern sim7600_packet_t sim7600;
uint8_t Init_SIM7600(void);
uint8_t Check_NETSIMstate(void);
uint8_t setupCONNECTION(void);
uint8_t Setup_connection(char *server_name, char *port , uint16_t keep_alive);
uint8_t Subscibe(char *sub_topic, uint8_t qos);
uint8_t unSubscibe(char *sub_topic);
uint8_t Publish(char *pub_topic, uint8_t qos);
uint8_t Disconnected(uint8_t index);
uint16_t cal_sum_dev();
#endif /* INC_SIM7600_H_ */
