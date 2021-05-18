/*
 * sim7600.h
 *
 *  Created on: Apr 22, 2021
 *      Author: ACER
 */

#ifndef INC_SIM7600_H_
#define INC_SIM7600_H_

#include <stdint.h>


#define MAX_VALUE 500

typedef struct{
	uint8_t channel;
    uint8_t id; // id
    uint8_t func; // function code
    uint16_t reg; // Adress reg
    char *name;
    char *description; // name of device
    char *title; // name of reg
    char *type; // number or boolean
}data1_t;

extern data1_t table1[];
uint8_t INIT_SIM7600(void);
uint8_t CHECK_NETSIM(void);
uint8_t SETUP_CONNECTION(char *server_name,char *username, char *password, char *port);
uint8_t SUBSCRIBE(char *topic);
uint8_t PUBLISH_TELEMETRY(char *topic);
uint8_t PUBLISH_PROVISION(char *topic, char *payload);
void CALLBACK_COMMAND(char* topic, char* payload, uint8_t lengthofpayload);
void CALLBACK_PROVISION(char* topic, char* payload, uint8_t length);
uint8_t RECONNECT(void);
uint16_t DEVSUM(void);

#endif /* INC_SIM7600_H_ */
