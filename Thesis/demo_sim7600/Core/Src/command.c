/*
 * command.c
 *
 *  Created on: Apr 22, 2021
 *      Author: ACER
 */

#include "main.h"
#include "sim7600.h"
#include "string.h"
#include "stdlib.h"
#include "stm32f4xx_it.h"
#include "command.h"

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart1;

char enter[] = "\r\n";
char aux_str[100];
volatile uint8_t gotCommandFlag = 0;
uint8_t commandBuffer[100];
uint8_t commandBufferIndex = 0;
char *sub="";
char *pub="";
char *payload="";

/***************************************Response from SIM800A**************************************************************/
void UARTIntHandler(void)
{
	uint8_t receivedChar = (uint8_t)((huart2).Instance->DR);
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
	if (__HAL_UART_GET_FLAG(&huart2, UART_IT_RXNE) == RESET) // if flag is set, data in DR register
		{
			commandBuffer[commandBufferIndex] = receivedChar;
			commandBufferIndex++;
		}
	gotCommandFlag = 1;
}
/*---------------------Send AT command---------------------------------------------------------------------------------------*/
uint8_t sendATcommand(char* ATcommand,char *respect_answer_1, uint32_t timeout)
{
	volatile uint8_t answer = 0;
	HAL_UART_Transmit(&huart2,(uint8_t*)ATcommand,strlen(ATcommand)+1,1000);
	uint32_t  tickstart = HAL_GetTick();
	timeout += (uint32_t)(uwTickFreq); // HERE
	do
	{
		if (gotCommandFlag == 1)
		{
//			gotCommandFlag = 0;
//			commandBufferIndex = 0;
			if (strstr(commandBuffer,respect_answer_1) != NULL)
			{
				answer = 1;
				memset(commandBuffer,'\0',100);
			}
		}
	}
	while((answer == 0) && ((HAL_GetTick() - tickstart) < timeout)); // HERE
	gotCommandFlag = 0;
	commandBufferIndex = 0;
	memset(commandBuffer,'\0',100);
	return answer;
}

///*---------------------Send AT command with 2 answer------------------------------------------------------------------*/
//uint8_t sendATcommand_2(char* ATcommand,char *respect_answer_1,char *respect_answer_2,uint32_t timeout)
//{
//	uint8_t volatile answer=0;
//	HAL_UART_Transmit(&huart1,(uint8_t*)ATcommand,strlen(ATcommand) + 1,1000);
//	uint32_t  tickstart = HAL_GetTick();
//	timeout += (uint32_t)(uwTickFreq); // HERE
//	do
//	{
//		if (gotCommandFlag == 1)
//		{
//			gotCommandFlag = 0;
//			commandBufferIndex = 0;
//			if (strstr(commandBuffer,respect_answer_1) != NULL){
//				return answer = 1;
//				memset(commandBuffer,'\0',100);}
//            else if (strstr(commandBuffer, respect_answer_2) != NULL){
//                return answer = 2;
//				memset(commandBuffer,'\0',100);}
//		}
//	}
//	while((answer == 0) && ((HAL_GetTick() - tickstart) < timeout)); // HERE
//	return answer;
//}
///*---------------------Send AT command with 3 answer------------------------------------------------------------------*/
//uint8_t sendATcommand_3(char* ATcommand,char *respect_answer_1,char *respect_answer_2,char *respect_answer_3,uint32_t timeout)
//{
//	uint8_t volatile answer=0;
//	HAL_UART_Transmit(&huart1,(uint8_t*)ATcommand,strlen(ATcommand) + 1,1000);
//	uint32_t  tickstart = HAL_GetTick();
//	timeout += (uint32_t)(uwTickFreq); // HERE
//	do
//	{
//		if (gotCommandFlag == 1)
//		{
//			gotCommandFlag = 0;
//			commandBufferIndex = 0;
//			if (strstr(commandBuffer,respect_answer_1) != NULL){
//				return answer = 1;
//				memset(commandBuffer,'\0',100);}
//            if (strstr(commandBuffer, respect_answer_2) != NULL){
//                return answer = 2;
//				memset(commandBuffer,'\0',100);}
//            else if (strstr(commandBuffer, respect_answer_3) != NULL){
//            	return answer = 3;
//            	memset(commandBuffer,'\0',100);}
//		}
//	}
//	while((answer == 0) && ((HAL_GetTick() - tickstart) < timeout)); // HERE
//	return answer;
//}
///*---------------------Create AT command------------------------------------------------------------------*/
/*
 * Brief: Create AT command
 * aux_str: buffer contains AT command
 * ATcommand: */

uint8_t createATcommand(char aux_str[100],uint8_t uistate,sim7600_packet_t packet)
{
	memset(aux_str,0,100);
	switch(uistate)
	{
		case NETOPEN:
			snprintf(aux_str, sizeof(aux_str),"AT+NETOPEN%s",enter);
		break;

		case IPADDR:
			snprintf(aux_str, sizeof(aux_str),"AT+IPADDR%s",enter);
		break;

		case CMQTTSTART:
			snprintf(aux_str, sizeof(aux_str),"AT+CMQTTSTART%s",enter);
		break;

		case CMQTTACCQ:
			snprintf(aux_str, sizeof(aux_str),"AT+CMQTTACCQ=%d,\"%s\",%d%s",packet.index_client,packet.client_name,enter); //maybe not protocol
		break;

		case CMQTTCONNECT:
			snprintf(aux_str, sizeof(aux_str),"AT+CMQTTCONNECT=%d,\"%s:%d\",%d,%d,\"%s\",\"%s\"%s",packet.index_client,packet.server_name,
																								   packet.port,packet.keepalive,packet.cleansession,
																								   packet.username,packet.password,enter);
		break;

		case CMQTTSUBTOPIC:
			snprintf(aux_str, sizeof(aux_str),"AT+CMQTTSUBTOPIC=%d,%d,%d,%d%s",packet.index_client,strlen(sub),packet.protocol,packet.qos,enter);
		break;

		case CMQTTTOPIC:
			snprintf(aux_str, sizeof(aux_str),"AT+CMQTTTOPIC=%d,%d%s",packet.index_client,strlen(pub),enter);
		break;

		case CMQTTPAYLOAD:
		snprintf(aux_str, sizeof(aux_str),"AT+CMQTTPAYLOAD=%d,%d%s",packet.index_client,strlen(payload),enter);
		break;

		case CMQTTPUB:
		snprintf(aux_str, sizeof(aux_str),"AT+CMQTTPUB=%d,%d,%d%s",packet.index_client,packet.qos,strlen(payload)+strlen(pub),enter);
		break;

		case CMQTTDISC:
		snprintf(aux_str, sizeof(aux_str),"AT+CMQTTDISC=%d,%d%s",packet.index_client,packet.timeout,enter);
		break;

		case CMQTTREL:
		snprintf(aux_str, sizeof(aux_str),"AT+CMQTTREL=%d%s",packet.index_client,enter);
		break;

		case CMQTTSTOP:
		snprintf(aux_str, sizeof(aux_str),"AT+CMQTTSTOP%s",enter);
		break;

		case NETCLOSE:
		snprintf(aux_str, sizeof(aux_str),"AT+NETCLOSE%s",enter);
		break;
	}
}
///*---------------------Create Json------------------------------------------------------------------*/
//uint8_t createJson(char demo[100],char *name_dev, uint16_t val, uint8_t time[6])
//{
//	memset(demo,0,100);
//	strcat(demo,name_dev);
//	strcat(demo,":");
//    strcat(demo,"[{time:");
//    strcat(demo,itoa_user(time[0], 10)); // Hour
//    strcat(demo,":");
//    strcat(demo,itoa_user(time[1], 10)); // Minute
//    strcat(demo,":");
//    strcat(demo,itoa_user(time[2], 10)); //Second
//    strcat(demo," ");
//    strcat(demo,itoa_user(time[3], 10));// Month
//    strcat(demo,".");
//    strcat(demo,itoa_user(time[4], 10)); // Day
//    strcat(demo,".");
//    strcat(demo,itoa_user(time[5], 10)); //Year
//    strcat(demo,",");
//    strcat(demo,"value");
//    strcat(demo,":");
//    strcat(demo,itoa_user(val, 10));
//    strcat(demo,"}]");
//
//	}
///*-------------------------------------------------------------------------------------*/
//uint8_t* itoa_user(uint32_t val, uint8_t base) {
//	static uint8_t buf[32] = { 0 };  // 32 bits
//	int i = 30;
//	if (val == 0)
//		buf[i--] = '0';
//	for (; val && i; --i, val /= base)
//		buf[i] = "0123456789abcdef"[val % base];
//
//	return &buf[i + 1];
//}
///*---------------------Send AT command------------------------------------------------------------------*/
//uint8_t sendATcommand(char* ATcommand, uint32_t timeout)
//{
//	HAL_UART_Transmit(&huart2,(uint8_t*)ATcommand,strlen(ATcommand)+1,1000);
//	HAL_Delay(timeout);
//	}
