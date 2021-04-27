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
	//int16toint8 regAdr;
	uint16_t regAdr;
	char name[10];
}device_t;

typedef struct{ // STRUCT DATA FROM EEPROM
	uint8_t port;
    uint8_t id; // id
    uint8_t func; // function code
    //int16toint8 reg_adr;
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
extern const char *tel_topic;
extern const char *command;
extern const char *down_pro;
extern const char *pro_topic;

#endif /* PARAM_H_ */
