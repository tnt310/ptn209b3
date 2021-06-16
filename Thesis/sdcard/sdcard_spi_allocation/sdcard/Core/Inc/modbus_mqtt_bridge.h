#ifndef __MODBUS_MQTT_BRIDGE__H__
#define __MODBUS_MQTT_BRIDGE__H__

/* Public define*/
#define JSON_MAX_LEN 	200

/* Public function prototype ----------------*/
uint8_t parse_json(char *pJsonMQTTBuffer,uint16_t pJsonMQTTBufferLen);
data_t *parse_device(char *Buffer, uint16_t BufferLen);
void addDevice(data_t *destination, data_t *data);
void LoadDevice(void);


#endif
