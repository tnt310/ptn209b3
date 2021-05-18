#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main_time[6] = {15,11,25,26,6,21};
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

data1_t table1[] =
{
		0,	2,	3,	0,   "WEATHERSTATION",		"STATION_01",		"TEMPERATURE",	"NUMBER",   
		0,	2, 	3,  1, 	 "WEATHERSTATION",		"STATION_02",		"HUMIDITY",	    "NUMBER",
		0,	2,	3,	2,	 "INVERTER",			"INVERTER_01",		"POWER",	    "NUMBER",
		0,	2,	3,	3,	 "WEATHERSTATION",		"STATION_03",		"LUMEN",	    "NUMBER",
		0,	2,	3,	4,	 "METER",	 			"METER_01",			"CURRENT",	    "NUMBER",
		0,	2,	3,	5,	 "METER",				"METER_02",			"VOLTAGE",	    "NUMBER",
		0,	2,  3, 	6,	 "INVERTER",			"INVERTER2",		"POWER",	    "NUMBER",
		0,	2,	3,	7,   "WEATHERSTATION",		"STATION_04",		"TEMPERATURE",	"NUMBER",
		0,	2, 	3,  8, 	 "WEATHERSTATION",		"STATION_05",		"POWER",	    "NUMBER",
		0,	2,	3,	10,	 "WEATHERSTATION",		"STATION_06",		"HUMIDITY",	    "NUMBER",
		0,	2,	3,	9,	 "INVERTER",			"INVERTER_03",		"LUMEN",	    "NUMBER",
		0,	6,	3,	0,   "WEATHERSTATION",		"STATION_07",		"TEMPERATURE",	"NUMBER",
		0,	6, 	3,  1, 	 "WEATHERSTATION",		"STATION_08",		"HUMIDITY",	    "NUMBER",
		0,	6,	3,	2,	 "INVERTER",			"INVERTER_04",		"POWER",	    "NUMBER",
		0,	6,	3,	3,	 "WEATHERSTATION",		"STATION_09",		"LUMEN",	    "NUMBER",
		0,	6,	3,	4,	 "METER",	 			"METER_03",			"CURRENT",	    "NUMBER",
		0,	6,	3,	5,	 "METER",				"METER_04",			"VOLTAGE",	    "NUMBER",
		0,	6,  3, 	6,	 "INVERTER",			"INVERTER_05",		"POWER",	    "NUMBER",
		0,	6,	3,	7,   "WEATHERSTATION",		"STATION_10",		"TEMPERATURE",	"NUMBER",
		0,	6, 	3,  8, 	 "WEATHERSTATION",		"STATION_11",		"HUMIDITY",	    "NUMBER",
		0,	6,	3,	9,	 "INVERTER",			"INVERTER_06",		"POWER",	    "NUMBER",
		0,	6,	3,	10,	 "WEATHERSTATION",		"STATION_12",		"LUMEN",	    "NUMBER",
		0,	6,	6,	0,   "RELAY",				"RELAY_01",			"LIGHT",		"NUMBER",
		0,	6, 	6,  1, 	 "INVERTER",			"INVERTER_07",		"POWER",	    "NUMBER",
		0,	6,	6,	2,	 "RELAY",				"RELAY_02",			"POWER",	    "NUMBER",

};
uint8_t  createJson_provision(char *buffer,char *device_id, char *device_name, char *device_type,uint16_t deviceChannel,
                                char *deviceTitle,char *valueType)
{
        memset(buffer,0,sizeof(buffer));
        strcat(buffer, "\"data\":[{");
        strcat(buffer, "\"device_id\":");
        strcat(buffer,"\"");
        strcat(buffer,device_id);
        strcat(buffer,"\"");
        strcat(buffer, ",\"device_name\":");
        strcat(buffer,"\"");
        strcat(buffer,device_name);
        strcat(buffer,"\"");
        strcat(buffer, ",\"device_type\":");
        strcat(buffer,"\"");
        strcat(buffer,device_type);
        strcat(buffer,"\"");
        strcat(buffer, ",\"device_attrs\":[{");
        strcat(buffer, "\"attr_id\":");  // deviceChannel
        strcat(buffer,"\"");
        strcat(buffer,deviceChannel);
        strcat(buffer,"\"");
        strcat(buffer, ",\"attr_name\":");  // name of reg
         strcat(buffer,"\"");
        strcat(buffer,deviceTitle);
        strcat(buffer,"\"");
        strcat(buffer, ",\"attr_type\":");
        strcat(buffer,"\"");
        strcat(buffer,valueType);
        strcat(buffer,"\"");
        strcat(buffer,"]}");
        strcat(buffer,"]}");
}
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
int main()
{
    char buffer[200];
    char pub[200];
    createJson_provision(pub,table1[1].deviceID,table1[1].deviceName,table1[1].deviceType,table1[1].deviceChannel,table1[1].deviceTitle,table1[1].valueType);
    printf("%s",pub);
}



uint8_t SDformatJson(char *buffer,uint8_t port,uint8_t deviceID,uint8_t func,uint16_t deviceChannel,char *deviceType,char *deviceTitle,char *deviceName,char *valueType)
{
        memset(buffer,0,sizeof(buffer));
        strcat(buffer,"{");
        strcat(buffer, "\"port\":");
        strcat(buffer,"\"");
        strcat(buffer,itoa_user(port,10));
        strcat(buffer,"\"");
        strcat(buffer, ",\"ID\":");
        strcat(buffer,"\"");
        strcat(buffer,itoa_user(deviceID,10));
        strcat(buffer,"\"");
        strcat(buffer, ",\"FC\":");
        strcat(buffer,"\"");
        strcat(buffer,func);
        strcat(buffer,"\"");
        strcat(buffer, ",\"DEVICETYPE\":");
        strcat(buffer,"\"");
        strcat(buffer,deviceType);
        strcat(buffer,"\"");
        strcat(buffer, ",\"DEVICETYPE\":");
        strcat(buffer,"\"");
        strcat(buffer,deviceType);
        strcat(buffer,"\"");
        strcat(buffer, ",\"DEVICETYPE\":");
        strcat(buffer,"\"");
        strcat(buffer,deviceType);
        strcat(buffer,"\"");
        strcat(buffer, ",\"DEVICETYPE\":");
        strcat(buffer,"\"");
        strcat(buffer,deviceType);
        strcat(buffer,"\"");

        strcat(buffer,"}");
}

uint8_t  createJson_provision(char *buffer,uint8_t deviceId, char *device_name, char *device_type,uint16_t deviceChannel,
                                char *deviceTitle,char *valueType)
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
        strcat(buffer, ",\"device_type\":");
        strcat(buffer,"\"");
        strcat(buffer,device_type);
        strcat(buffer,"\"");
        strcat(buffer, ",\"device_attrs\":[");
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
        strcat(buffer,valueType);
        strcat(buffer,"\"");
        strcat(buffer,"}");
}