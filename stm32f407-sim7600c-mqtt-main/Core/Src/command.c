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

//char aux_str[100];
uint8_t commandBuffer[100];
uint32_t commandBufferIndex = 0;
uint32_t gotCommandFlag = 0;
/***************************************Response from SIM7600**************************************************************/
void UARTIntHandler(void)
{
		uint8_t receivedChar;
		receivedChar = (uint8_t) ((huart2).Instance->DR & (uint8_t) 0x00FF);
		__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
		if (receivedChar != 13) {
			commandBuffer[commandBufferIndex] = receivedChar;
			commandBufferIndex++;
		} else {
			if (commandBufferIndex != 0) {
				commandBuffer[commandBufferIndex] = 0;
				commandBufferIndex = 0;
				gotCommandFlag = 1;
			}
		}
	}
/*---------------------------------------------------------------------------------------------------------------------------*/
uint8_t sendATcommand(char* ATcommand, uint32_t timeout)
{
	HAL_UART_Transmit(&huart2,(uint8_t*)ATcommand,strlen(ATcommand)+1,1000);
	HAL_Delay(timeout);
	memset(commandBuffer,'\0',100);
	}
/*---------------------Send AT command---------------------------------------------------------------------------------------*/
uint8_t sendATcommand1(char* ATcommand,char *respect_answer_1, uint32_t timeout)
{
//	uint8_t status;
	volatile uint8_t answer = 0;
	HAL_UART_Transmit(&huart2,(uint8_t*)ATcommand,strlen(ATcommand)+1,1000);
	uint32_t  tickstart = HAL_GetTick();
	timeout += (uint32_t)(uwTickFreq); // HERE
	do
	{
		if (gotCommandFlag == 1)
		{
			if (strstr(commandBuffer,respect_answer_1) != NULL)
			{
				answer = 1;
			}
			else
			{
			}
		}
	}
	while((answer == 0) && ((HAL_GetTick() - tickstart) < timeout));
	gotCommandFlag = 0;
	commandBufferIndex = 0;
	memset(commandBuffer,'\0',100);
	return answer;
}
/*---------------------Handler ERROR------------------------------------------------------------------*/
/*-----------------RETURN CODE--------------------------------------------------------------------------------*/
//uint8_t ReturnCode(char str[])
//{
//	char err[2];
//	for (uint8_t i = 0; i< strlen(str); i++)
//	{
//		if (str[i] == ','){
//			err[0] = str[i+1];
//			err[1] = str[i+2];
//		}
//	}
//	return atoi(err);
//}

///*-------------------------------------------------------------------------------------*/
uint8_t* itoa_user(uint32_t val, uint8_t base) {
	static uint8_t buf[32] = { 0 };  // 32 bits
	int i = 30;
	if (val == 0)
		buf[i--] = '0';
	for (; val && i; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];

	return &buf[i + 1];
}
/*---------------------Send AT command with 2 respect_answer------------------------------------------------------------------*/
uint8_t sendATcommand2(char* ATcommand,char *respect_answer_1,char *respect_answer_2,uint32_t timeout)
{
	uint8_t status;
	volatile uint8_t answer = 0;
	HAL_UART_Transmit(&huart2,(uint8_t*)ATcommand,strlen(ATcommand)+1,1000);
	uint32_t  tickstart = HAL_GetTick();
	timeout += (uint32_t)(uwTickFreq); // HERE
	do
	{
		if (gotCommandFlag == 1)
		{
			if (strstr(commandBuffer,respect_answer_1) != NULL)
			{
				answer = 1;
			}
			else if (strstr(commandBuffer,respect_answer_2) != NULL)
			{
				answer = 1;
			}
		}
	}
	while((answer == 0) && ((HAL_GetTick() - tickstart) < timeout));
	gotCommandFlag = 0;
	commandBufferIndex = 0;
	memset(commandBuffer,'\0',100);
	return answer;
}
/*
 * return mqtt error code
 *
 * */
uint8_t createJson(char demo[500],char name[10], uint16_t val)
{

	memset(demo,0,sizeof(demo));
	strcat(demo,"{");
    strcat(demo,"\"");
    strcat(demo,name);
    strcat(demo,"\"");
	strcat(demo,":");
    strcat(demo,"\"value\"");
    strcat(demo,":");
    strcat(demo,itoa_user(val, 10));
    strcat(demo,"}");

	}
uint8_t createJson_provision(char buffer[],char *name,char *type, char *title, char *description)
{
     memset(buffer,0,sizeof(buffer));
     strcat(buffer,"\"");
     strcat(buffer,name);
     strcat(buffer,"\"");
     strcat(buffer,":");
     strcat(buffer, "{\"type\":");
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
uint8_t Get_Time(uint8_t time[6])
{
	time[0] = 10;
	time[1] = 10;
	time[2] = 10;
	time[3] = 4;
	time[4] = 25;
	time[5] = 21;
	}
