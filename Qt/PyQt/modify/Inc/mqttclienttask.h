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
extern const char *mqtt_id;
extern const char *mqtt_user;
extern const char *mqtt_password;
extern const uint16_t u16_mqtt_port;

#endif
