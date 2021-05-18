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
#define MAX_JSON_LEN 180

typedef struct{
	uint8_t channel;
    uint8_t id; // id
    uint8_t func; // function code
    uint16_t reg; // Adress reg
	char *IDkey;
    char *name;
    char *description; // name of device
    char *title; // name of reg
    char *type; // number or boolean
}data1_t;

typedef struct{

	char *client_id;
	char *client_user;
	char *client_pass;
	uint16_t port;
	uint16_t keepalive;
	char *will_topic;
	uint8_t qos;
	uint8_t retain;
}sim7600_info_t;

extern data1_t table1[];
uint8_t INIT_SIM7600(void);
uint8_t CHECK_NETSIM(void);
uint8_t SIM7600_NEW_CONNECTION(char *client,char *server,char *user, char *pass, uint16_t port, uint16_t keepalive);
uint8_t SUBSCRIBE(char *topic, uint8_t qos);
uint8_t SIM7600_PUBLISH_PACKET(char *topic, char payload[], uint8_t qos);
void CALLBACK_COMMAND(char* payload, uint8_t lengthofpayload);
void CALLBACK_PROVISION(char* topic, char* payload, uint8_t length);
uint8_t RECONNECT(void);
uint16_t DEVSUM(void);
void MQTT_SIM7600_UPSTREAM(char *telemetry, char *provision, uint8_t qos);
void MQTT_SIM7600_DOWNSTREAM(char *pJsonMQTTBuffer,uint16_t pJsonMQTTBufferLen);
uint8_t GETJSON(char *payload,char *buffer, char *key1, char *key2);
uint16_t cal_sum_dev(void);
#endif /* INC_SIM7600_H_ */
