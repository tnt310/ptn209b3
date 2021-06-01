#include <stdio.h>
#include <string.h>
#include <stdint.h>

	char pub[1000];
    char device[200];
    char attribute[200];
/*----------------------------ITOA_USER--------------------------------------*/
uint8_t* itoa_user(uint32_t val, uint8_t base) {
	static uint8_t buf[32] = { 0 };  // 32 bits
	int i = 30;
	if (val == 0)
		buf[i--] = '0';
	for (; val && i; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];

	return &buf[i + 1];
}
/*------------------------------------------	------------------------------------*/
typedef struct{
   uint8_t channel;
   uint8_t deviceID; // id : 01
   uint8_t func; // function code
   uint16_t deviceChannel; // Adress reg (0x10)
   char *deviceType; // name of device  : INVERTER
   char *deviceName; // : INVERTER1
   char *deviceTitle; // name of reg
   char *valueType; // number or boolean: 100, true, false
}data1_t;

data1_t table1[50] =
{
		0,	2,	3,	0x00,   "WEATHERSTATION",		"STATION_01",		"TEMPERATURE",	"NUMBER",   
		0,	2, 	3,  0x01, 	"WEATHERSTATION",		"STATION_01",		"HUMIDITY",	    "NUMBER",
		0,	2,	3,	0x03,	"WEATHERSTATION",		"STATION_01",		"LUMEN",	    "NUMBER",

        0,	3,	3,	0x00,   "WEATHERSTATION",		"STATION_02",		"TEMPERATURE",	"NUMBER",
		0,	3,	3,	0x01,   "WEATHERSTATION",		"STATION_02",		"HUMIDITY",	    "NUMBER",
		0,	3, 	3,  0x03, 	"WEATHERSTATION",		"STATION_02",		"LUMEN",	    "NUMBER",

        0,	4,	3,	0x00,   "WEATHERSTATION",		"STATION_03",		"TEMPERATURE",	"NUMBER",
		0,	4, 	3,  0x01, 	"WEATHERSTATION",		"STATION_04",		"HUMIDITY",	    "NUMBER",
		0,	4,	3,	0x03,	"WEATHERSTATION",		"STATION_04",		"LUMEN",	    "NUMBER",


		0,	6,	3,	0x04,	 "METER",	 			"METER_01",			"CURRENT",	    "NUMBER",
		0,	6,	3,	0x05,	 "METER",				"METER_01",			"VOLTAGE",	    "NUMBER",
        0,	6,	3,	0x04,	 "METER",	 			"METER_01",			"CURRENT",	    "NUMBER",
		0,	6,	3,	0x05,	 "METER",				"METER_01",			"VOLTAGE",	    "NUMBER",

        0,	5,	3,	0x09,	 "INVERTER",			"INVERTER_01",		"VOLTAGE",	    "NUMBER",
		0,	5,  3, 	0x06,	 "INVERTER",			"INVERTER_01",		"POWER",	    "NUMBER",
		0,	5,	3,	0x02,	 "INVERTER",			"INVERTER_01",		"VOLTAGE",	    "NUMBER",
		0,	5,	3,	0x09,	 "INVERTER",			"INVERTER_01",		"POWER",	    "NUMBER",
        0,	5,  3, 	0x06,	 "INVERTER",			"INVERTER_01",		"POWER",	    "NUMBER",
        0,	5, 	6,  0x01, 	 "INVERTER",			"INVERTER_01",		"POWER",	    "NUMBER",

		0,	10,	6,	0x00,   "RELAY",				"RELAY_01",			"LIGHT",		"NUMBER",
		0,	12,	6,	0x02,	"RELAY",				"RELAY_02",			"LIGHT",	    "NUMBER",

};
uint8_t device(char *buffer, uint8_t deviceId, char *device_name, char *device_type)
{
        memset(buffer,0,sizeof(buffer));
        strcat(buffer,"{");
        strcat(buffer, "\"data\":[{");
        strcat(buffer, "\"device_id\":");
        strcat(buffer,"\"");
        strcat(buffer,itoa_user(deviceId,10));
        strcat(buffer,"\"");
        strcat(buffer, ",\"device_name\":");
        strcat(buffer,"\"");
        strcat(buffer,device_name);
        strcat(buffer,"\"");
        strcat(buffer, ",\"device_kind\":");
        strcat(buffer,"\"");
        strcat(buffer,device_type);
        strcat(buffer,"\"");
        strcat(buffer, ",\"device_channel\":[");
}
uint8_t channel(char *buffer,uint16_t deviceChannel, char *deviceTitle,char *valueType)
{
        memset(buffer,0,sizeof(buffer));
        strcat(buffer,"{");
        strcat(buffer, "\"attr_id\":");  // deviceChannel
        strcat(buffer,"\"");
        strcat(buffer,itoa_user(deviceChannel,10));
        strcat(buffer,"\"");
        strcat(buffer, ",\"attr_name\":");  // name of reg
        strcat(buffer,"\"");
        strcat(buffer,deviceTitle);
        strcat(buffer,"\"");
        strcat(buffer, ",\"attr_type\":");
        strcat(buffer,"\"");
        strcat(buffer,valueType);  // NUMBER or BOOLEAN
        strcat(buffer,"\"");
        strcat(buffer,"}");
}
int main()
{
    
}
data1_t table1[] =
{
		0,	2,	3,	0x00,   "INVERTER",		        "INVERTER_01",		"VOLTAGE",	    "NUMBER",   
		0,	2, 	3,  0x01, 	"INVERTER",		        "INVERTER_01",		"CURRENT",	    "NUMBER",
		0,	2,	3,	0x03,	"INVERTER",		        "INVERTER_01",		"POWER",	    "NUMBER",

        0,	3,	3,	0x00,   "WEATHERSTATION",		"STATION_02",		"TEMPERATURE",	"NUMBER",
		0,	3,	3,	0x01,   "WEATHERSTATION",		"STATION_02",		"HUMIDITY",	    "NUMBER",
		0,	3, 	3,  0x03, 	"WEATHERSTATION",		"STATION_02",		"LUMEN",	    "NUMBER",

        0,	4,	3,	0x00,   "WEATHERSTATION",		"STATION_03",		"TEMPERATURE",	"NUMBER",
		0,	4, 	3,  0x01, 	"WEATHERSTATION",		"STATION_03",		"HUMIDITY",	    "NUMBER",
		0,	4,	3,	0x03,	"WEATHERSTATION",		"STATION_03",		"LUMEN",	    "NUMBER",

		0,	6,	3,	0x05,	 "METER",				"METER_01",			"VOLTAGE",	    "NUMBER",
        0,	6,	3,	0x04,	 "METER",	 			"METER_01",			"CURRENT",	    "NUMBER",
		0,	6,	3,	0x05,	 "METER",				"METER_01",			"VOLTAGE",	    "NUMBER",

        0,	8,	3,	0x00,   "WEATHERSTATION",		"STATION_04",		"TEMPERATURE",	"NUMBER",
		0,	8, 	3,  0x01, 	"WEATHERSTATION",		"STATION_04",		"HUMIDITY",	    "NUMBER",
		0,	8,	3,	0x03,	"WEATHERSTATION",		"STATION_04",		"LUMEN",	    "NUMBER",

		0,	10,	3,	0x04,	 "METER",				"METER_02",			"VOLTAGE",	    "NUMBER",
        0,	10,	3,	0x05,	 "METER",	 			"METER_02",			"CURRENT",	    "NUMBER",
		0,	10,	3,	0x06,	 "METER",				"METER_02",			"VOLTAGE",	    "NUMBER",

};