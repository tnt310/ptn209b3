#include <stdint.h>


typedef struct{
    uint8_t channel;
    uint8_t deviceID;
    uint8_t func;
    uint8_t devicestatus;
    uint16_t deviceChannel;
    char *deviceType;
    char *deviceName;
    char *channeltitle;
    char *valueType;
}data1_t;

uint8_t ping_json(char *buffer, uint8_t id_gateway);

uint8_t  head_provision(char *buffer,uint8_t device_id, char *device_name, char *device_type);
uint8_t  tail_provision(char *buffer,uint16_t channel_id, char *channel_name, char *channel_type, uint8_t function);
uint8_t provision_json(void);

uint8_t head_telemetry(char *buffer, uint8_t time[6], uint8_t device_id);
uint8_t tail_telemetry(char *buffer, uint16_t device_channel, uint16_t value);
uint8_t telemetry_json(void);

uint8_t command_json(char *buffer,uint8_t device_id, uint16_t device_channel,uint16_t value);

//uint8_t parse(char *Buffer,uint16_t BufferLen, data1_t *p);
uint8_t topic(char *buffer, char *apikey, char *topic, char *flow_type);

#define SUM 31

// data1_t table1[] =
// {
// 		0,	2,	3,	0x00,   "INVERTER",		        "INVERTER_01",		"VOLTAGE",	    "NUMBER",
// 		0,	2, 	3,  0x01, 	"INVERTER",		        "INVERTER_01",		"CURRENT",	    "NUMBER",
// 		0,	2,	3,	0x02,	"INVERTER",		        "INVERTER_01",		"POWER",	    "NUMBER",
//         0,	2, 	3,  0x03, 	"INVERTER",		        "INVERTER_01",		"CURRENT",	    "NUMBER",
// 		0,	2,	3,	0x04,	"INVERTER",		        "INVERTER_01",		"POWER",	    "NUMBER",

//         0,	6,	3,	0x03,   "WEATHERSTATION",		"STATION_01",		"TEMPERATURE",	"NUMBER",
// 		0,	6,	3,	0x04,   "WEATHERSTATION",		"STATION_01",		"HUMIDITY",	    "NUMBER",
// 		0,	6, 	3,  0x05, 	"WEATHERSTATION",		"STATION_01",		"LUMEN",	    "NUMBER",

//         0,	3,	3,	0x03,   "WEATHERSTATION",		"STATION_02",		"TEMPERATURE",	"NUMBER",
// 		0,	3,	3,	0x04,   "WEATHERSTATION",		"STATION_02",		"HUMIDITY",	    "NUMBER",
// 		0,	3, 	3,  0x05, 	"WEATHERSTATION",		"STATION_02",		"LUMEN",	    "NUMBER",

//         0,	10,	3,	0x03,   "METER",				"METER_01",		"TEMPERATURE",	"NUMBER",
// 		0,	10,	3,	0x04,   "METER",				"METER_01",		"HUMIDITY",	    "NUMBER",
// 		0,	10, 3,  0x05, 	"METER",				"METER_01",		"LUMEN",	    "NUMBER",

//         0,	5, 	3,  0x03, 	"INVERTER",		        "INVERTER_02",		"CURRENT",	    "NUMBER",
// 		0,	5,	3,	0x04,	"INVERTER",		        "INVERTER_02",		"POWER",	    "NUMBER",
// 		0,	5,	3,	0x05,	"INVERTER",		        "INVERTER_02",		"POWER",	    "NUMBER",

// 		0,	8,	3,	 0x06,   "WEATHERSTATION",		"STATION_03",		"TEMPERATURE",	"NUMBER",
// 		0,	8,	3,	 0x07,   "WEATHERSTATION",		"STATION_03",		"HUMIDITY",	    "NUMBER",
// 		0,	8, 	3,   0x08, 	"WEATHERSTATION",		"STATION_03",		"LUMEN",	    "NUMBER",
// 		0,	8, 	3,   0x09, 	"WEATHERSTATION",		"STATION_03",		"LUMEN",	    "NUMBER",

// 	    0,	100,3,	0x06,   "METER",				"METER_02",		"VOLTAGE",		"NUMBER",
// 		0,	100,3,	0x07,   "METER",				"METER_02",		"CURRENT",	    "NUMBER",
// 		0,	100,3,  0x08, 	"METER",				"METER_02",		"POWER",	    "NUMBER",

// 		0,	8,	3,	0x01,   "WEATHERSTATION",		"STATION_03",		"TEMPERATURE",	"NUMBER",
// 		0,	8,	3,	0x02,   "WEATHERSTATION",		"STATION_03",		"HUMIDITY",	    "NUMBER",
// 		0,	8, 	3,  0x03, 	"WEATHERSTATION",		"STATION_03",		"LUMEN",	    "NUMBER",
// 		0,	8, 	3,  0x04, 	"WEATHERSTATION",		"STATION_03",		"LUMEN",	    "NUMBER",

//         0,	100,3,	0x03,   "METER",				"METER_02",		"VOLTAGE",		"NUMBER",
// 		0,	100,3,	0x04,   "METER",				"METER_02",		"CURRENT",	    "NUMBER",
// 		0,	100,3,  0x05, 	"METER",				"METER_02",		"POWER",	    "NUMBER",
// };


