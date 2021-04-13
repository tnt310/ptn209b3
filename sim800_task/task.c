/*
 * sim800a.c
 *
 *  Created on: Mar 5, 2021
 *      Author: ACER
 */
#include "main.h"
#include "sim800a.h"
#include "string.h"
#include "stdlib.h"
#include "stm32f4xx_it.h"

char aux_str[100];
char apn[] = "m-wap";
char protocol[] = "TCP";
char server[] = "api.thingspeak.com";
char port[] = "80\r\n";
char api[80];
char GET[] = "GET https://api.thingspeak.com/update?api_key=GSSURCMMYMTLW9KG&field1=50\r\n";
char ip[20];

volatile uint8_t gotCommandFlag = 0;
uint8_t commandBuffer[100];
uint8_t commandBufferIndex = 0;
volatile uint8_t answer = 0;
uint32_t tick = 0;

/***************************************Send AT command**************************************************************/
void sendATcommand(char* ATcommand,uint32_t timeout)
{
	HAL_UART_Transmit(&huart2,(uint8_t*)ATcommand,strlen(ATcommand)+1,1000);
	HAL_Delay(timeout);
	}
/***************************************Send AT command**************************************************************/
uint8_t sendATcommand2(char* ATcommand, char *respect_answer, uint32_t timeout)
{
		TIM2->CNT = 0;
		HAL_UART_Transmit(&huart2,(uint8_t*)ATcommand,strlen(ATcommand)+1,1000);
		HAL_TIM_Base_Start(&htim2);
		HAL_Delay(50);  // osDelay(); chờ event từ Queue để xử lí
		while(gotCommandFlag)
		{
			gotCommandFlag = 0;
			commandBufferIndex = 0;
			do
			{
				if(strstr(commandBuffer,respect_answer) != NULL)
				{
					answer = 1;
					memset(commandBuffer,'\0',100);
					HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);
				}
				else
					answer = 0;

			    tick = ((TIM2->CNT)+1) * 5;
			}
			while (answer == 0 && tick < timeout);
		}
		return answer;
}

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
/***************************************Operate SIM800A**************************************************************/
uint8_t SIM800_ON (void)
{
	sendATcommand("AT\r\n",1000);
	if (sendATcommand2("AT\r\n","OK",1000) == 1)
		while (sendATcommand2("AT+CPIN?\r\n","READY",1000) == 1 && sendATcommand2("AT+CREG?\r\n","OK",1000) == 1 && sendATcommand2("AT+CGATT?\r\n","OK",1000) == 1)
			{
				sendATcommand("AT&W\r\n",1000);
				sendATcommand2("AT+CIPSHUT\r\n","OK",1000);
				return 1;
				break;
			}
}
/***************************************Init SIM800A**************************************************************/
uint8_t SIM800_Init(void)
{
		sendATcommand("AT\r\n",1000);
		sendATcommand("AT\r\n",1000);
		sendATcommand("AT+CIPSTATUS\r\n", 1000);
				//sendATcommand2("AT+CIPMUX=0\r\n","OK",1);
				//snprintf(aux_str, sizeof(aux_str), "AT+CSTT=\"%s\"\r\n",apn);
				//sendATcommand2(aux_str,"OK",1);
				//sendATcommand2("AT+CIICR\r\n","OK",1000);
		sendATcommand("AT+CIFSR\r\n",1000); // get local IP
		return 1;
}
/***************************************Update data to Thingspeak*************************************************************/
uint8_t Update_data(void)
{
	sendATcommand2("AT\r\n","OK",1000);
	sendATcommand2("AT\r\n","OK",1000);
	snprintf(aux_str, sizeof(aux_str),"AT+CIPSTART=\"%s\",\"%s\",%s",protocol,server,port);
	sendATcommand(aux_str,3000);
	sendATcommand("AT+CIPSEND\r\n",1000);
	sprintf(api,"%s%c",GET,(char) 26);
	while (sendATcommand2(api,"CLOSED",5000) == 1)
			break;
	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_13);
}

/***************************************Handler_error**************************************************************/
void Handler_error(void)
{
	sendATcommand2("AT\r\n","OK",2000);
	sendATcommand2("AT\r\n","OK",2000);
	sendATcommand2("AT\r\n","OK",2000);
	}


