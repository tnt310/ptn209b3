#include <stdio.h>
#include <string.h>
#include <stdint.h>
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
extern data1_t table1[] =
{
		0,	2,	3,	0,   "608a78baaa969877dec4e6f4", 	"CH0_SEN2_LUME0",	"SENSOR",		"TEMPERATURE",	"NUMBER",
		0,	2, 	3,  1, 	 "608a78baaa969877dec4e6f4",	"CH0_INV2_POWR1",	"SENSOR",		"HUMIDITY",	    "NUMBER",
		0,	2,	3,	2,	 "608a78baaa969877dec4e6f4",	"CH0_INV2_POWR2",	"INVERTER",		"POWER",	    "NUMBER",
		0,	2,	3,	3,	 "608a78baaa969877dec4e6bb",	"CH0_SEN2_TEMP3",	"SENSOR",		"LUMEN",	    "NUMBER",
		0,	2,	3,	4,	 "608a78baaa969877dec4e6bb",	"CH0_INV2_RPOWR4",	"METER",	 	"CURRENT",	    "NUMBER",
		0,	2,	3,	5,	 "608a78baaa969877dec4e6bb",	"CH0_INV2_POWR5",	"METER",		"VOLTAGE",	    "NUMBER",
		0,	2,  3, 	6,	 "608a78baaa969877dec4e6de",	"CH0_NOD2_RELA6",	"INVERTER",		"POWER",	    "NUMBER",
		0,	2,	3,	7,   "606ff2e222c1752264934dde",	"CH0_SEN2_LUME7",	"SENSOR",		"TEMPERATURE",	"NUMBER",
		0,	2, 	3,  8, 	 "606ff2e222c1752264934dde",	"CH0_INV2_POWR8",	"SENSOR",		"HUMIDITY",	    "NUMBER",
		0,	2,	3,	9,	 "606ff2e222c1752264934dbb",	"CH0_INV2_POWR9",	"INVERTER",		"POWER",	    "NUMBER",
		0,	2,	3,	10,	 "606ff2e222c1752264934dbb",	"CH0_SEN2_TEMP10",	"SENSOR",		"LUMEN",	    "NUMBER",
};
uint8_t  createJson_provision(char *buffer,char *id,  char *name, char *type, char *title, char *description)
{
        memset(buffer,0,sizeof(buffer));
        strcat(buffer, "\"id\":");
        strcat(buffer,"\"");
        strcat(buffer,id);
        strcat(buffer,"\"");
        strcat(buffer,",");
        strcat(buffer, "\"data\":{");
        strcat(buffer,"\"");
        strcat(buffer,name);
        strcat(buffer,"\"");
        strcat(buffer, ":{\"type\":");
        strcat(buffer,"\"");
        strcat(buffer,type);
        strcat(buffer,"\"");
        strcat(buffer, ",\"title\":");
        strcat(buffer,"\"");
        strcat(buffer,title);
        strcat(buffer,"\"");
        strcat(buffer, ",\"description\":");
        strcat(buffer,"\"");
        strcat(buffer,description);
        strcat(buffer,"\"");
        strcat(buffer,"}");
}

int main()
{
    uint16_t SUM = sizeof(table1)/sizeof(data1_t);
	char pub[50];
    for (uint16_t i = 0; i < SUM; i++){
        char *id_temp = table1[i].IDkey;
        if 
    }
    createJson_provision(pub,table1[0].IDkey, table1[0].name, table1[0].type, table1[0].title, table1[0].description);
    printf("%s",pub);
}
// {
//     "id": "",
//     "data": {
//         "CH1_NODE1_SEN1": {
//             "type": "number",
//             "title": "voltage",
//             "kind": "sensor"
//         },
//         "CH1_NODE2_MET1": {
//             "type": "number",
//             "title": "power",
//             "kind": "meter"
//         },
//         "CH1_NODE3_REL1": {
//             "type": "string",
//             "title": "state",
//             "kind": "switch"
//         },
//         "CH1_NODE4_SEN1": {
//             "type": "number",
//             "title": "temperature",
//             "kind": "sensor"
//         },
//         "CH1_NODE5_REG1": {
//             "type": "boolean",
//             "title": "register",
//             "kind": "register"
//         }
//     }
// }