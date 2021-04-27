#include <command.h>
#include <string.h>
#include "cmdline.h"
#include "main.h"
#include "param.h"
#include "usart.h"
#include "envtask.h"
#include "epprom.h"
#include "rak.h"
tCmdLineEntry g_psCmdTable[] = {
		{ "help", Cmd_help," : Display list of commands" },
		{ "set", Cmd_set," : Set the specific param in the next arg" },
		{ "get", Cmd_get," : Get the specific param in the next arg" },
		{ "setserial", Cmd_set_serial," : Set the specific terminal" },
		{ "setch1config", Cmd_set_ch1_conf," : Set the channel 1 configuration" },
		{ "setparam", Cmd_set_ch1_param," : Set the channel 1 parameter" },
		{ "delete",Cmd_delete_device," : Delete device" },
		{ "save",Cmd_save," : save" },
		{ "reset",Cmd_reset," : reset" },
		{ 0, 0, 0 } };

const char * ErrorCode[4] = { "CMDLINE_BAD_CMD", "CMDLINE_TOO_MANY_ARGS","CMDLINE_TOO_FEW_ARGS", "CMDLINE_INVALID_ARG" };

uint8_t commandBuffer[100];
uint8_t commandSendBuffer[100];
uint32_t commandBufferIndex = 0;
uint32_t gotCommandFlag = 0;
uint8_t isEcho = 1;

static uint8_t stt = 0;
int16toint8 RegAdr;
/*Brief: must be mapped to Rx Interrupt!
 *
 * */
/*--------------------------------------------------------UART INTERRUPT ----------------------------------------------------------------------*/
void command_recv_callback_irq(UART_HandleTypeDef *huart) {

	uint8_t receivedChar;
		uint32_t ui32Status;
		char *EnterCMD = "\r\n>";
		receivedChar = (uint8_t) ((*huart).Instance->DR & (uint8_t) 0x00FF);
		if (isEcho == 1)
			HAL_UART_Transmit_IT(huart, &receivedChar, 1);
	//	__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
			if ((receivedChar != 10) && (receivedChar != 13)) {
				if ((receivedChar == 8) || (receivedChar == 127)) {
					if (commandBufferIndex > 0)
						commandBufferIndex--;
				} else {
					commandBuffer[commandBufferIndex] = receivedChar;
					commandBufferIndex++;
				}
			} else {
				if (commandBufferIndex != 0) {
					commandBuffer[commandBufferIndex] = 0;
					commandBufferIndex = 0;
					gotCommandFlag = 1;
				}
				if (isEcho == 1)
	//			HAL_UART_Transmit_IT(huart, EnterCMD, 3);
					PRINTF_EN = 0;
			}
}
int Cmd_save(int argc, char *argv[])
{
	v_epr_save(PARAM_LOAD_ALL);
	char *reponse = "OK\r\n";
	HAL_UART_Transmit(&huart2, reponse, 4, 1000);
}

int Cmd_reset(int argc, char *argv[])
{
	NVIC_SystemReset();
	char *reponse = "OK\r\n";
	HAL_UART_Transmit(&huart2, reponse, 4, 1000);
}
/*--------------------------------------------------------SET DATA ----------------------------------------------------------------------*/
int Cmd_set(int argc, char *argv[]) {

	//device_param_t device;
	char merg[4];
	uint8_t port;
	/*********************SET CHANNEL BAUDRATE******************************/
	if ((strcmp(*(argv + 1), "mb") == 0)) {

		if ((strcmp(*(argv + 2), "mode") == 0)) {
			u_mem_set(NODE_MB_MODE_ADR, atoi(*(argv + 3)));

		} else if ((strcmp(*(argv + 2), "baud") == 0)) {
			u_mem_set(NODE_MB_BAUD_ADR, atoi(*(argv + 3)));

		} else if ((strcmp(*(argv + 2), "db") == 0)) {
			u_mem_set(NODE_MB_DATABITS_ADR, atoi(*(argv + 3)));

		} else if ((strcmp(*(argv + 2), "stbi") == 0)) {
			u_mem_set(NODE_MB_STOPBITS_ADR, atoi(*(argv + 3)));

		} else if ((strcmp(*(argv + 2), "pari") == 0)) {
			u_mem_set(NODE_MB_PARTITY_ADR, atoi(*(argv + 3)));

		} else if ((strcmp(*(argv + 2), "id") == 0)) {
			u_mem_set(NODE_MB_ID_ADR, atoi(*(argv + 3)));
		}
	}
/**************************SET NETWORK***********************************************************************************/
	if ((strcmp(*(argv + 1), "network") == 0)) {

		if ((strcmp(*(argv + 2), "ip") == 0)) {
			u_mem_set(NODE_NETWORK_IP_ADR, atoi(*(argv + 3)));

		} else if ((strcmp(*(argv + 2), "netmask") == 0)) {
			u_mem_set(NODE_NETWORK_NETMASK_ADR, atoi(*(argv + 3)));

		} else if ((strcmp(*(argv + 2), "gateway") == 0)) {
			u_mem_set(NODE_NETWORK_GATEWAY_ADR, atoi(*(argv + 3)));

		} else if ((strcmp(*(argv + 2), "mqtt") == 0)) {
			u_mem_set(NODE_NETWORK_MQTT_ADR, atoi(*(argv + 3)));
		}
}
/**************************SET CHANNEL CONFIGURATION************************************************************************/
	if ((strcmp(*(argv + 1), "channel1") == 0)) {

		if ((strcmp(*(argv + 2), "baud") == 0)) {
			u_mem_set(NODE_CHANEL_1_BAUD, atoi(*(argv + 3)));

		} else if ((strcmp(*(argv + 2), "db") == 0)) {
			u_mem_set(NODE_CHANEL_1_DATABITS , atoi(*(argv + 3)));

		} else if ((strcmp(*(argv + 2), "stbi") == 0)) {
			u_mem_set(NODE_CHANEL_1_STOPBIT, atoi(*(argv + 3)));

		} else if ((strcmp(*(argv + 2), "pari") == 0)) {
			u_mem_set(NODE_CHANEL_1_PARITY, atoi(*(argv + 3)));
		}
	}
/**************************SET ID, TOPIC, SERVER FOR GATEWAY************************************************************************/
	else if ((strcmp(*(argv + 1), "id") == 0)) {
		u_mem_set(NODE_ID_ADR, atoi(*(argv + 2)));
	}
	else if ((strcmp(*(argv + 1), "topic") == 0)) {
		u_mem_set(NODE_TOPIC_ADR, atoi(*(argv + 2)));
	}
	else if ((strcmp(*(argv + 1), "server") == 0)) {
		u_mem_set(NODE_SERVER_ADR, atoi(*(argv + 2)));
	}
	else if ((strcmp(*(argv + 1), "cf") == 0)) {
		u_mem_set(NODE_HAVE_PARAM_ADR, EEP_PARAM);
	}
	/* Reponse -----------------------------------------------------*/
	char *reponse = "OK\r\n";
	HAL_UART_Transmit(&huart2, reponse, 4, 1000);
}

/*--------------------------------------------------------GET DATA ----------------------------------------------------------------------*/
int Cmd_get(int argc, char *argv[]) {

	uint8_t port = 0;
	memset(commandSendBuffer, 0, 50);
	/**************************GET MODBUS SLAVE******************************/
	if ((strcmp(*(argv + 1), "mb") == 0)) {
		if ((strcmp(*(argv + 2), "mode") == 0)) {
			strcat(commandSendBuffer,itoa_user(u_mem_get(NODE_MB_MODE_ADR), 10));

		} else if ((strcmp(*(argv + 2), "baud") == 0)) {
			strcat(commandSendBuffer,itoa_user(u_mem_get(NODE_CHANEL_1_BAUD), 10));

		} else if ((strcmp(*(argv + 2), "db") == 0)) {
			strcat(commandSendBuffer,itoa_user(u_mem_get(NODE_MB_DATABITS_ADR), 10));

		} else if ((strcmp(*(argv + 2), "stbi") == 0)) {
			strcat(commandSendBuffer,itoa_user(u_mem_get(NODE_MB_STOPBITS_ADR), 10));

		} else if ((strcmp(*(argv + 2), "pari") == 0)) {
			strcat(commandSendBuffer,itoa_user(u_mem_get(NODE_MB_PARTITY_ADR), 10));

		} else if ((strcmp(*(argv + 2), "id") == 0)) {
			strcat(commandSendBuffer, itoa_user(u_mem_get(NODE_MB_ID_ADR), 10));
		}
	}
	/**************************GET CHANNEL CONFIGURATION******************************/
	if ((strcmp(*(argv + 1), "channel1") == 0)) {

		if ((strcmp(*(argv + 2), "baud") == 0)) {
			strcat(commandSendBuffer,itoa_user(u_mem_get(NODE_CHANEL_1_BAUD), 10));

		} else if ((strcmp(*(argv + 2), "db") == 0)) {
			strcat(commandSendBuffer,itoa_user(u_mem_get(NODE_CHANEL_1_DATABITS), 10));

		} else if ((strcmp(*(argv + 2), "stbi") == 0)) {
			strcat(commandSendBuffer,itoa_user(u_mem_get(NODE_CHANEL_1_STOPBIT), 10));

		} else if ((strcmp(*(argv + 2), "pari") == 0)) {
			strcat(commandSendBuffer,itoa_user(u_mem_get(NODE_CHANEL_1_PARITY), 10));
		}
}
	/**************************GET CHANNEL PARAMETERS******************************/
	else if ((strcmp(*(argv + 1), "id") == 0)) {
		strcat(commandSendBuffer, itoa_user(u_mem_get(NODE_ID_ADR), 10));
	}
	else if ((strcmp(*(argv + 1), "cf") == 0)) {
		strcat(commandSendBuffer,itoa_user(u_mem_get(NODE_HAVE_PARAM_ADR), 10));
	}
	strcat(commandSendBuffer, "\r\n");
	/* Reponse -----------------------------------------------------*/
	HAL_UART_Transmit(&huart2, commandSendBuffer, strlen(commandSendBuffer),1000);
}

int Cmd_help(int argc, char *argv[]) {

	tCmdLineEntry *pEntry;
	// Print some header text.
	printf("\nAvailable commands\r\n");
	printf("------------------\r\n");
	// Point at the beginning of the command table.
	pEntry = &g_psCmdTable[0];

// Enter a loop to read each entry from the command table.  The
// end of the table has been reached when the command name is NULL.
	while (pEntry->pcCmd) {
// Print the command name and the brief description.
		printf("%s%s\n\r", pEntry->pcCmd, pEntry->pcHelp);

// Advance to the next entry in the table.
		pEntry++;

	}
	printf("------------------\r\n");
// Return success.
	return (0);
}

void vCmdTask(const void *arg) {
	char *Badcommand = "Bad Command\r\n>";
	int ret;
	while (1) {
		if (gotCommandFlag) {
			gotCommandFlag = 0;
			ret = CmdLineProcess(commandBuffer);
			if (ret == CMDLINE_BAD_CMD)
				HAL_UART_Transmit(&huart2, Badcommand, strlen(Badcommand), 100);
		}
		osDelay(10);
	}
}
/*---------------------------------------------------SERIAL SERIAL---------------------------------------------------------------------------------------*/
int Cmd_set_serial(int argc, char *argv[])
{
	if ((strcmp(*(argv + 0), "setserial") == 0)) {
		u_mem_set(NODE_MB_BAUD_ADR, atoi(*(argv + 1)));
		u_mem_set(NODE_MB_DATABITS_ADR, atoi(*(argv + 2)));
		u_mem_set(NODE_MB_STOPBITS_ADR, atoi(*(argv + 3)));
		u_mem_set(NODE_MB_PARTITY_ADR, atoi(*(argv + 4)));
	}
	char *reponse = "OK\r\n";
	HAL_UART_Transmit(&huart2, reponse, 4, 1000);
}
/*---------------------------------------------------CHANNEL 1 CONFIGURATION--------------------------------------------------------------------------------------*/
int Cmd_set_ch1_conf(int argc, char *argv[])
{
	if ((strcmp(*(argv + 0), "setch1config") == 0)) {
		u_mem_set(NODE_CHANEL_1_BAUD, atoi(*(argv + 1)));
		u_mem_set(NODE_CHANEL_1_DATABITS, atoi(*(argv + 2)));
		u_mem_set(NODE_CHANEL_1_STOPBIT, atoi(*(argv + 3)));
		u_mem_set(NODE_CHANEL_1_PARITY, atoi(*(argv + 4)));
	}
	char *reponse = "OK\r\n";
	HAL_UART_Transmit(&huart2, reponse, 4, 1000);
}
/*--------------------------------------------------CHANNEL 1 PARAMETER------------------------------------------------------------------------------*/
int Cmd_set_ch1_param(int argc, char *argv[]) // 0,10,6,1,0,12,'C','H','1','_','I','N','V','3','_','F','A','N',1,3,'F','A','N',
{
	char name[20];
    stt = u_mem_get(NODE_CHANNEL_1_BASE);
	#define NODE_CHANNEL_1_ADR      NODE_CHANNEL_1_BASE + 1 + (5 * stt)
	if ((strcmp(*(argv + 0), "setparam") == 0)) {
		u_mem_set(NODE_CHANNEL_1_ADR , atoi(*(argv + 1))); 		// CHANNEL
		u_mem_set(NODE_CHANNEL_1_ADR + 1 , atoi(*(argv + 2))); 	// ID
		u_mem_set((NODE_CHANNEL_1_ADR  + 2), atoi(*(argv + 3))); // FUNC
		uint16_t temp = atoi(*(argv + 4)); // REGADR
		u_mem_set((NODE_CHANNEL_1_ADR  + 3), (uint8_t)temp);
		u_mem_set((NODE_CHANNEL_1_ADR  + 4), (uint8_t)(temp >>8));
		u_memset((NODE_CHANNEL_1_ADR  + 5), atoi(*(argv + 5))); //SL1
		strncpy(name,(argv + 6),atoi(*(argv + 5)));
		for (uint8_t i = 0; i< atoi(*(argv + 5); i++)
		{
				u_memset((NODE_CHANNEL_1_ADR  + 6 + i), name[i]);
		}
	}
	stt ++;
	PARAM[NODE_CHANNEL_1_BASE] = stt;
	char *reponse = "\r\nOK\r\n";
	HAL_UART_Transmit(&huart2, reponse, 4, 1000);
}
/*---------------------------------------------DELETE DEVICE OF CHANNEL---------------------------------------------------------*/

int Cmd_delete_device(int argc, char *argv[])
{
	uint8_t channel = atoi(*(argv + 1)); // which channel ?
	uint8_t temp_id = atoi(*(argv + 2)); // which id ?
	uint16_t temp_reg = atoi(*(argv + 3)); // which addr of id?
	switch (channel)
	{
		case DELETE_ALL: //  DELETE ALL DEVICE OF 3 CHANNEL
			for (uint16_t i = 0; i< 300; i++)
			{
				u_mem_set(NODE_CHANNEL_1_BASE + i, 0);
			}
			break;

		case DELETE_CH1: //  DELETE ALL DEVICE OF CH1
			for (uint8_t i = 0; i < 50; i++)
			{
				u_mem_set(NODE_CHANNEL_1_BASE + i, 0);
			}
			char *result = "\r\nOK\r\n";
			HAL_UART_Transmit(&huart2,result, 4, 1000);
			break;

		default:	// DELETE DEVICE AT SPECIFIC ADDRESS
			for (uint16_t i = 0; i< 50; i = i + 5)  // COMPARE ID
				{
					if (PARAM[NODE_CHANNEL_1_BASE + 1 + i] == temp_id)
						{
							RegAdr.i8data[0] = PARAM[NODE_CHANNEL_1_BASE + 1 + i + 3];
							RegAdr.i8data[1] = PARAM[NODE_CHANNEL_1_BASE + 1 + i + 4];
							if (RegAdr.i16data == temp_reg)
							{
								for (uint8_t j = 0; j <5; j++) // DELETE MEMORY
								{
									u_mem_set(NODE_CHANNEL_1_BASE + 1 + i + j, 0);
								}
								for (uint8_t z = 0; z < 50; z++) // COLLECT MEMORY
								{
									if ((NODE_CHANNEL_1_BASE + 1 + i + z) < 100)
									{
										PARAM[NODE_CHANNEL_1_BASE + 1 + i + z] = PARAM[NODE_CHANNEL_1_BASE + 1 + i + 5 + z];
									}
								}
							}
						}
				}
			PARAM[NODE_CHANNEL_1_BASE] -- ;
			char *reponse = "\r\nOK\r\n";
			HAL_UART_Transmit(&huart2, reponse, 4, 1000);
			break;
	}
}
