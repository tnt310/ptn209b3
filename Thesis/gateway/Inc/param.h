/*
 * param.h
 *
 *  Created on: Mar 31, 2021
 *      Author: ACER
 */

#ifndef PARAM_H_
#define PARAM_H_
#include "main.h"

typedef struct
{
	uint8_t channel;
	uint8_t id;
	uint8_t func;
	uint16_t regAdr;
	char name[10];
}device_t;

typedef struct{ // STRUCT DATA FROM EEPROM
	uint8_t port;
    uint8_t id; // id
    uint8_t func; // function code
    uint16_t reg_adr; // Adress reg
    char *name_dev;// name of address device
    char *type; // number or boolean
    char *name; // name of address reg
}data1_t;

typedef struct
{
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t day;
	uint8_t month;
	uint8_t year;
}Time_t;

extern data1_t table1[];

//extern data_t table[] =   // CHANNEL 1
//{
//		3,	3,	0,	"TEMP", 	"INV1",
//		3, 	3,  1,	"HUMD", 	"SENSOR2",
//		3,	3,	2,	"POWR",		"METER1",
//		3,	3,	3,	"LUME", 	"SENSOR4",
//		3,	3,	4,	"CURR", 	"INV2",
//		3,	3,	5,	"VOLT", 	"INV3",
//		3,  3, 	6,	"POWR", 	"INV2",
//		3, 	3,	7,	"RPOW",		"INV8",
//		3,	3,	8,	"HUMD",		"SENSOR7",
//		3,	3,	9,	"POWR",		"METER1"
//
//};
//extern data_t table_2[] =  // CHANNEL 2
//{
//		4,	3,	100,	"TEMP", 	"INV4",
//		4,  3,  101,	"HUMD", 	"SENSOR5",
//		4,	3,	102,	"POWR",		"METER6",
//		4,	3,	103, 	"LUME", 	"SENSOR2",
//		4,	3,	104,	"CURR", 	"INV3",
//		4,	3,	105,	"VOLT", 	"INV4",
//		4,  3, 	106,	"POWR", 	"INV6",
//		4, 	3,	107,	"RPOW",		"INV7",
//		4,	3,	108,	"HUMD",		"SENSOR8",
//		4,	3,	109,	"POWR",		"METER1"
//};
//extern data_t table_3[] =  // CHANNEL 3
//{
//		5,	3,	100,	"TEMP", 	"INV4",
//		5,  3,  101,	"HUMD", 	"SENSOR5",
//		5,	3,	102,	"POWR",		"METER6",
//		5,	3,	103, 	"LUME", 	"SENSOR2",
//		5,	3,	104,	"CURR", 	"INV3",
//		5,	3,	105,	"VOLT", 	"INV4",
//		5,  3, 	106,	"POWR", 	"INV6",
//		5, 	3,	107,	"RPOW",		"INV7",
//		5,	3,	108,	"HUMD",		"SENSOR8",
//		5,	3,	109,	"POWR",		"METER1"
//};

//extern data1_t table2[] =   // CHANNEL 2
//{
//		6,	3,	0,  "CH2_SEN2_TEMP",		"Temperature",
//		6, 	3,  1, 	"CH2_SEN2_HUMD", 		"Humidity",
//		6,	3,	2,	"CH2_INV2_POWR", 		"Power",
//		6,	3,	3,	"CH2_SEN1_LUME",		"Lumen",
//		6,	3,	4,	"CH2_INV1_CURR",		"Current",
//		6,	3,	5,	"CH2_INV1_VOLT",		"Voltage",
//		6,  3, 	6,	"CH2_INV1_POWR",		"Power",
//		6, 	3,	7,	"CH2_INV1_RPOWR",		"React Power",
//		6,	3,	8,	"CH2_SEN1_HUMD",		"Humidity",
//		6,	3,	9,	"CH2_INV1_POWR",		"Power",
//		6,	3,	10,  "CH2_SEN2_TEMP",		"Temperature",
//		6, 	3,  11, "CH2_SEN2_HUMD", 		"Humidity",
//		6,	3,	12,	"CH2_INV2_POWR", 		"Power",
//		6,	3,	13,	"CH2_SEN1_LUME",		"Lumen",
//		6,	3,	14,	"CH2_INV1_CURR",		"Current",
//		6,	3,	15,	"CH2_INV1_VOLT",		"Voltage",
//		6,  3, 	16,	"CH2_INV1_POWR",		"Power",
//		6, 	3,	17,	"CH2_INV1_RPOWR",		"React Power",
//		6,	3,	18,	"CH2_SEN1_HUMD",		"Humidity",
//		6,	3,	19,	"CH2_INV1_POWR",		"Power"
//
//};
//extern data1_t table3[] =   // CHANNEL 3
//{
//		8,	3,	0,  "CH3_SEN2_TEMP",		"Temperature",
//		8, 	3,  1, 	"CH3_SEN2_HUMD", 		"Humidity",
//		8,	3,	2,	"CH3_INV2_POWR", 		"Power",
//		8,	3,	3,	"CH3_SEN1_LUME",		"Lumen",
//		8,	3,	4,	"CH3_INV1_CURR",		"Current",
//		8,	3,	5,	"CH3_INV1_VOLT",		"Voltage",
//		8,  3, 	6,	"CH3_INV1_POWR",		"Power",
//		8, 	3,	7,	"CH3_INV1_RPOWR",		"React Power",
//		8,	3,	8,	"CH3_SEN1_HUMD",		"Humidity",
//		8,	3,	9,	"CH3_INV1_POWR",		"Power",
//		8,	3,	10,  "CH3_SEN2_TEMP",		"Temperature",
//		8, 	3,  11, "CH3_SEN2_HUMD", 		"Humidity",
//		8,	3,	12,	"CH3_INV2_POWR", 		"Power",
//		8,	3,	13,	"CH3_SEN1_LUME",		"Lumen",
//		8,	3,	14,	"CH3_INV1_CURR",		"Current",
//		8,	3,	15,	"CH3_INV1_VOLT",		"Voltage",
//		8,  3, 	16,	"CH3_INV1_POWR",		"Power",
//		8, 	3,	17,	"CH3_INV1_RPOWR",		"React Power",
//		8,	3,	18,	"CH3_SEN1_HUMD",		"Humidity",
//		8,	3,	19,	"CH3_INV1_POWR",		"Power"
//};
#endif /* PARAM_H_ */
