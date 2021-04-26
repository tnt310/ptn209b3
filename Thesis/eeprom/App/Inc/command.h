#ifndef	_COMMAND_H
#define	_COMMAND_H
#include "cmdline.h"
#include <stdint.h>
#include <stdbool.h>
#include "usart.h"
#include "main.h"

//#define NODE_CHANNEL_1_ADR      NODE_CHANNEL_1_BASE + (NODE_CHANNEL_1_OFFSET * stt)
enum {DELETE_ALL, DELETE_CH1, DELETE_CH2, DELETE_CH3};

extern uint32_t gotCommandFlag;
extern uint8_t commandBuffer[100];
int
Cmd_help(int argc, char *argv[]);
int
setRGBLED(int argc, char *argv[]);
int Cmd_set(int argc, char *argv[]);
int Cmd_get(int argc, char *argv[]);

int Cmd_set_serial (int argc, char *argv[]);
int  Cmd_set_ch1_conf(int argc, char *argv[]);
int  Cmd_set_ch2_conf(int argc, char *argv[]);
int  Cmd_set_ch1_param(int argc, char *argv[]);
int  Cmd_set_ch2_param(int argc, char *argv[]);

int Cmd_delete_device(int argc, char *argv[]);

int Cmd_save(int argc, char *argv[]);
int Cmd_reset(int argc, char *argv[]);

void command_recv_callback_irq(UART_HandleTypeDef *huart) ;

void vCmdTask(const void *arg);


void CH1_ADR(uint8_t n);
#endif
