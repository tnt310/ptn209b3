#ifndef __PARAM_H__
#define __PARAM_H__

#include <stdio.h>
#include <stdint.h>
#include  "eeprom.h"

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
/* Modbus salve parameters---*/
#define NODE_MB_ID_ADR				2
#define NODE_MB_SERCFG_ADR 			3
#define NODE_MB_MODE_ADR			4  //RTU OR ASCII
#define NODE_MB_BAUD_ADR			5
#define NODE_MB_DATABITS_ADR		6
#define NODE_MB_PARTITY_ADR			7
#define NODE_MB_STOPBITS_ADR		8
#define NODE_MB_WORKMODE_ADR		9 // 0: Slave 1: Master
#define NODE_MB_DEFAULT_LEN


/*UART PARAMETER CONFIGURATURE*/
/*--------------------------------SERIAL, CH1, CH2, CH3--------------------------------------------------------------------------------------------------------*/
#define GATEWAY_HAVE_PARAM_ADR	0
#define GATEWAY_ID_ADR			1
#define CHANNEL1_BAUD_ADR		2
#define CHANNEL1_DATABITS_ADR	3
#define CHANNEL1_PARTITY_ADR	4
#define CHANNEL1_STOPBITS_ADR	5
#define CHANNEL1_WORKMODE_ADR	6

#define CHANNEL2_BAUD_ADR		7
#define CHANNEL2_DATABITS_ADR	8
#define CHANNEL2_PARTITY_ADR	9
#define CHANNEL2_STOPBITS_ADR	10
#define CHANNEL2_WORKMODE_ADR	11

#define CHANNEL3_BAUD_ADR			12
#define CHANNEL3_DATABITS_ADR		13
#define CHANNEL3_PARTITY_ADR		14
#define CHANNEL3_STOPBITS_ADR		15
#define CHANNEL3_WORKMODE_ADR		16

#define RS232_BAUD_ADR			17
#define RS232_DATABITS_ADR		18
#define RS232_PARTITY_ADR		19
#define RS232_STOPBITS_ADR		20
#define RS232_WORKMODE_ADR		21

/*---------------------------------NETWORK---------------------------------------------------*/
#define NETWORK_ID_ADR				24
#define NETWORK_NETMASK_ADR			28
#define NETWORK_GATEWAY_ADR			32
#define NETWORK_MQTT_ADR			36

/*---------------------------------API KEY, SERVER, ID, USER, PASSWORD, TOPIC-----------------*/

#define API_KEY_ADR					40
#define API_KEY_ADR_LEN				20

#define MQTT_SERVERNAME_ADR			MQTT_SERVER_BASE + API_KEY_ADR_LEN
#define MQTT_SERVERNAME_ADR_LEN

#define MQTT_ID_ADR					MQTT_SERVERNAME_ADR	+ MQTT_SERVERNAME_ADR_LEN
#define MQTT_ID_ADR_LEN

#define MQTT_USER_ADR				MQTT_ID_ADR	+ MQTT_ID_ADR_LEN
#define MQTT_USER_ADR_LEN

#define MQTT_PASSWORD_ADR			MQTT_USER_ADR + MQTT_USER_ADR_LEN
#define MQTT_PASSWORD_ADR_LEN

/*---------------------------------DEVCE CONFIGURATUE---------------------------------------------------*/
#define DEVICE_BASE 				//

#define DEVICE_CHANNEL_ADR		 	DEVICE_BASE
#define DEVICE_CHANNEL_ADR_LEN		1

#define DEVICE_ID_ADR		    	DEVICE_CHANNEL_ADR + DEVICE_CHANNEL_ADR_LEN
#define DEVICE_ID_ADR_LEN			1

#define DEVICE_FUNC_ADR			 	DEVICE_ID_ADR + DEVICE_ID_ADR_LEN
#define DEVICE_FUNC_ADR_LEN			1

#define DEVICE_REG_ADR			 	DEVICE_FUNC_ADR + DEVICE_FUNC_ADR_LEN
#define DEVICE_REG_ADR_LEN			2

#define DEVICE_ALIAS_ADR            DEVICE_REG_ADR + DEVICE_REG_ADR_LEN
#define DEVICE_ALIAS_ADR_LEN		15

#define DEVICE_REG_TYPE_ADR	     	DEVICE_ALIAS_ADR  +  DEVICE_ALIAS_ADR_LEN
#define DEVICE_REG_TYPE_ADR_LEN

#define DEVICE_REG_TITLE_ADR      	DEVICE_REG_TYPE_ADR	+ DEVICE_REG_TYPE_ADR_LEN
#define DEVICE_REG_TITLE_ADR_LEN

#define DEVICE_DESCRIPTION_ADR	   	DEVICE_REG_TITLE_ADR + DEVICE_REG_TITLE_ADR_LEN
#define DEVICE_DESCRIPTION_ADR_LEN




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
/*
 *
 * */

#define PARAM_MAX_SIZE 			192
#define PARAM_LOAD_ALL			0xFFFF



extern uint8_t PARAM[EEP_MAX_SIZE];


uint8_t u_mem_get(uint16_t usAdr);
void u_mem_set(uint16_t usAdr, uint8_t uVal);
void v_epr_load(uint16_t usAdr);
void v_epr_save(uint16_t usAdr);

#endif

