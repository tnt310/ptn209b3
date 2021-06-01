/*
 * http_client.c
 *
 *  Created on: Mar 30, 2021
 *      Author: ACER
 */

#include "http_client.h"
/* Built-in C library includes ---------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Platform includes --------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "main.h"
#include "fs.h"
#include "rtc.h"
#include "flash.h"
/* Shared Variable ----------------------------------*/

extern host_param_t hostParam;
extern port_param_t portParam[MB_MAX_PORT];
extern network_param_t mqttHostParam;

extern UART_HandleTypeDef huart1;

#include "lwip.h"
#include "socket.h"

/* Includes ------------------------------------------------------------------*/
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/apps/fs.h"
#include "tcp.h"
#include "string.h"
#include "cmsis_os.h"
#include <stdio.h>


char req[200];
const char AccessToken[] = "ruhUAP87vw4xHT7yCQ14";
uint8_t lengthOfJSON = 34;
uint8_t temp = 30;
uint8_t humd=  90;

void http_client_init(void)
{
	struct netconn *conn;
	err_t err;
	ip_addr_t server_addr;
	/* Create a new TCP connection handle */
	conn = netconn_new(NETCONN_TCP);
	if (conn != NULL)
	{
		IP4_ADDR(&server_addr, 184, 106, 153, 149 ); //server ip
		err = netconn_connect(conn, &server_addr,80); //connect to the server
		if (err  == ERR_OK)
		{
			memset(req,0,200);
			strcat(req,"GET https://api.thingspeak.com/update?api_key=GSSURCMMYMTLW9KG&field1=20\r\n\r\n");
//			strcat(req,"POST /api/v1/ruhUAP87vw4xHT7yCQ14/telemetry HTTP/1.1\r\nHost: demo.thingsboard.io\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length:34\r\n\r\n");
//			strcat(req,"{\"temperature\":");
//			strcat(req, itoa_user(temp, 10));
//			strcat(req,",\"humidity\":");
//			strcat(req, itoa_user(humd, 10));
//			strcat(req,"}");
			netconn_write(conn, req ,strlen(req) , NETCONN_NOCOPY);
			printf("\r\nSEND DATA TO THINGSBOARD: OK\r\n");
		}
		else
		{
			printf("/r/n FAIL cmnr /r/n");
		}
	}
	if (netconn_close(conn) == ERR_OK)
	{
		printf("\r\nClose: OK\r\n");
	}
}

