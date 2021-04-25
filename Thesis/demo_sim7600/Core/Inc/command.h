/*
 * command.h
 *
 *  Created on: Apr 22, 2021
 *      Author: ACER
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_
#include "stdint.h"

typedef enum
{
	AT_CMQTTACCQ,AT_CMQTTCONNECT,AT_CMQTTSUBTOPIC,AT_CMQTTTOPIC,AT_CMQTTPAYLOAD,AT_CMQTTPUB,AT_CMQTTDISC,AT_CMQTTREL
}sim7600state_t;

typedef enum
{
	CPIN, CREG, NETOPEN, CMQTTSTART, CMQTTCONNECT, CMQTTPUB, CMQTTSUB, CMQTTTREL, CMQTTDISC
}err_t;
typedef enum
{
	SUCESSFUL, FAIL, BAD_UTF8_STRING, SOCKET_FAIL, MESSAGE_REV_FAIL = 6, NET_OPEN_FAIL, NET_CLOSE_FAIL, NET_NOT_OPEN, CLIENT_INDEX_ERR, NO_CONNECTION, NOT_SHAKEHAND = 32
}mqtt_err_t;

uint8_t createATcommand(char aux_str[100],uint8_t uistate,sim7600_packet_t packet);
uint8_t sendATcommand(char* ATcommand,char *respect_answer_1, uint32_t timeout);
uint8_t Handler_Err(uint8_t ui_state);
uint8_t ReturnCode(char str[100]);
//uint8_t createJson(char demo[50],char name_dev[10], uint16_t val, uint8_t time[6]);
//uint8_t CreateATcommand(char demo[100],char *ATcommand, int argc, char *argv[]);
//uint8_t sendATcommand_2(char* ATcommand,char *respect_answer_1,char *respect_answer_2,uint32_t timeout);
//uint8_t sendATcommand_3(char* ATcommand,char *respect_answer_1,char *respect_answer_2,char *respect_answer_3,uint32_t timeout);

void UARTIntHandler(void);
//uint8_t* itoa_user(uint32_t val, uint8_t base);

//uint8_t sendATcommand(char* ATcommand, uint32_t timeout);
#endif /* INC_COMMAND_H_ */
