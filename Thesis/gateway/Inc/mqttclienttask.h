#ifndef __MQTT_CLIENT_TASH__H__
#define __MQTT_CLIENT_TASH__H__

enum {
	QOS_0 = 0,
	QOS_1,
	QOS_2
};

typedef struct
{
	uint8_t topic[10];
	uint8_t user[10];
	uint8_t password[10];
}mqtt_info_t;

#endif
