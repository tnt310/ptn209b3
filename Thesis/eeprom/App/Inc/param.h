#ifndef __PARAM_H__
#define __PARAM_H__

#include <stdio.h>
#include <stdint.h>
#include  "epprom.h"

/* Default config
 * */
#define NODE_ID_ADR_DEFAULT				1
/* Modbus salve parameters---*/
#define NODE_MB_ID_DEFAULT				1
#define NODE_MB_SERCFG_DEFAULT			1
#define NODE_MB_MODE_DEFAULT			1  //RTU OR ASCII
#define NODE_MB_BAUD_DEFAULT			1
#define NODE_MB_DATABITS_DEFAULT		1
#define NODE_MB_PARTITY_DEFAULT			1
#define NODE_MB_STOPBITS_DEFAULT		1

#define NODE_LRWAN_DATARATE_DEFAULT 	0
#define NODE_LRWAN_CLASS_DEFAULT		2
#define NODE_LRWAN_FREQ_DEFAULT			0
#define NODE_LRWAN_CONFIRM_DEFAULT		1
#define NODE_LRWAN_MODE_DEFAULT			0
#define NODE_LRWAN_TX_POWER_DEFAULT 	0  // max
#define NODE_LRWAN_AUTO_JOIN_DEFAULT    0

#define NODE_IO_PORT_0_DEFAULT			0
#define NODE_IO_PORT_1_DEFAULT			1
#define NODE_IO_PORT_2_DEFAULT			2
#define NODE_IO_PORT_3_DEFAULT			2
#define NODE_IO_PORT_4_DEFAULT			4
#define NODE_IO_PORT_5_DEFAULT			5
#define NODE_IO_PORT_6_DEFAULT			6



/**
 *
 *
 *
 * */
/* Salve parameters---*/
#define NODE_HAVE_PARAM_ADR			0
#define NODE_ID_ADR					1
#define NODE_TOPIC_ADR				125
#define NODE_SERVER_ADR				126

/* GATEWAY CONFIGURATION---------------------------------------------------------*/
#define NODE_MB_ID_ADR				2
#define NODE_MB_SERCFG_ADR 			3
#define NODE_MB_MODE_ADR			4  //RTU OR ASCII
#define NODE_MB_BAUD_ADR			5
#define NODE_MB_DATABITS_ADR		6
#define NODE_MB_PARTITY_ADR			7
#define NODE_MB_STOPBITS_ADR		8
#define NODE_MB_WORKMODE_ADR		9 // 0: Slave 1: Master
#define NODE_MB_DEFAULT_LEN

/* GATEWAY CHANNEL  CONFIGURATION---------------------------------------------------*/
#define NODE_CHANEL_1_BAUD			10 // CHANNEL 1 CONFIGURATION
#define NODE_CHANEL_1_DATABITS      11
#define NODE_CHANEL_1_STOPBIT		12
#define NODE_CHANEL_1_PARITY        13

#define NODE_CHANEL_2_BAUD          14 // CHANNEL 2 CONFIGURATION
#define NODE_CHANEL_2_STOPBIT       15
#define NODE_CHANEL_2_PARITY    	16
#define NODE_CHANEL_2_DATABITS      17

#define NODE_CHANEL_3_BAUD			18 // CHANNEL 3 CONFIGURATION
#define NODE_CHANEL_3_STOPBIT       19
#define NODE_CHANEL_3_PARITY        20
#define NODE_CHANEL_3_DATABITS      21

/*GATEWAY  NETWORK PARAMETER------------------------------------------------------*/
#define NODE_NETWORK_BASE 			30

#define NODE_NETWORK_IP_ADR			NODE_NETWORK_BASE + 0
#define NODE_NETWORK_DEFAULT_LEN 	4

#define NODE_NETWORK_NETMASK_ADR	NODE_NETWORK_IP_ADR	+ NODE_NETWORK_DEFAULT_LEN
#define NODE_NETWORK_DEFAULT_LEN 	4

#define NODE_NETWORK_GATEWAY_ADR	NODE_NETWORK_NETMASK_ADR + NODE_NETWORK_DEFAULT_LEN
#define NODE_NETWORK_DEFAULT_LEN 	4

#define NODE_NETWORK_MQTT_ADR		NODE_NETWORK_GATEWAY_ADR + NODE_NETWORK_DEFAULT_LEN
#define NODE_NETWORK_DEFAULT_LEN 	4

/*GATEWAY  CHANNEl PARAMETER---------------------------------------------------*/
#define NODE_CHANNEL_1_BASE 		50     // CHANNEL 1 PARAMETER
#define NODE_CHANNEL_1_ID_LEN		1
#define NODE_CHANNEL_1_FUNC_LEN		1
#define NODE_CHANNEL_1_REGADR_LEN	2
#define NODE_CHANNEL_1_OFFSET		NODE_CHANNEL_1_ID_LEN + NODE_CHANNEL_1_FUNC_LEN	+ NODE_CHANNEL_1_REGADR_LEN

#define NODE_CHANNEL_2_BASE 		100  // CHANNEL 2 PARAMETER
#define NODE_CHANNEL_2_ID_LEN		1
#define NODE_CHANNEL_2_FUNC_LEN		1
#define NODE_CHANNEL_2_REGADR_LEN	2

/* LoRa parameters---*/
typedef struct
{
	uint8_t uAdr;
	uint8_t uLen;
} uParam_t;

enum{
	NO_PARAM,
	EEP_PARAM,
	FLASH_PARAM
};
enum{
	LR_WAN,
	LR_NONE,
	LR_DISABLE
};
enum{
	MB_SLAVE,
	MB_MASTER,
	MB_DISABLE
};
/*----------------------------------------------------------------------------------------------------------------------------*/
typedef union
{
	uint16_t i16data;
	uint8_t  i8data[2];
}int16toint8;

typedef union
{
	uint32_t idata;
	uint8_t  cdata[4];

}int_to_byte;

typedef struct  // network parameter
{
	int_to_byte ip;
	int_to_byte netmask;
	int_to_byte gateway;

}network_param_t;

//typedef struct   // channel parameters
//{
//	uint8_t id;
//	uint8_t func;
//	int16_to_byte Reg_addr;
//}device_param_t;
/*----------------------------------------------------------------------------------------------------------------------------*/
/*
 *
 * */

#define PARAM_MAX_SIZE 			192
#define PARAM_LOAD_ALL			0xFFFF

#define PARAM_CH1_ALL			255
#define PARAM_CH2_ALL			0xFFFF


extern uint8_t PARAM[EEP_MAX_SIZE];


uint8_t u_mem_get(uint16_t usAdr);
void u_mem_set(uint16_t usAdr, uint8_t uVal);
void u_mem_set_16(uint16_t usAdr, uint16_t uVal);

void v_epr_load(uint16_t usAdr);
void v_epr_save(uint16_t usAdr);

#endif

