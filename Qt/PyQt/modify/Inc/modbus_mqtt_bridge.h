#ifndef __MODBUS_MQTT_BRIDGE__H__
#define __MODBUS_MQTT_BRIDGE__H__
//#include "MQTTClient.h"
#include "lwip/apps/mqtt.h"
#include "lwip/apps/mqtt_priv.h"
#include "lwip/err.h"
#include "param.h"
#include <stdint.h>
/* Public define*/
#define JSON_MAX_LEN 200
#define portDEFAULT_WAIT_TIME 1000
#define MAX_JSON_LEN 		  1000

//#define ""


/* Public function prototype ----------------*/
uint8_t mqtt_modbus_thread_down_provision(char *pJsonMQTTBuffer,uint16_t pJsonMQTTBufferLen);
void mqtt_modbus_thread_up(mqtt_client_t *client, char *pub_topic, char* pro_topic, char* command_topic, char* test_topic);

uint8_t mqtt_modbus_thread_down_command(char *pJsonMQTTBuffer,uint16_t pJsonMQTTBufferLen);
uint8_t mqtt_thread_down_test(char *pJsonMQTTBuffer,uint16_t pJsonMQTTBufferLen);
uint16_t cal_sum_dev(void);

uint8_t create_topic(char *buffer, char *flow, char *topic, char *api_key);

data1_t *parse_device(char *Buffer, uint16_t BufferLen);
void addDevice(data1_t *destination, data1_t *data);
void LoadDevice(void);
#endif
