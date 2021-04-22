/*
 * sim7600.c
 *
 *  Created on: Apr 22, 2021
 *      Author: ACER
 */

#include "sim7600.h"

/***************************************Response from SIM800A**************************************************************/


uint8_t Init_SIM7600(void)
{
	sendATcommand("AT\r\n","OK",1000);
}
