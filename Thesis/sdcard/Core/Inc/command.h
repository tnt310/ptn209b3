#ifndef	_COMMAND_H
#define	_COMMAND_H
#include "cmdline.h"
#include <stdint.h>
#include <stdbool.h>

#define MAX_BUFFER_VALUE 200

extern uint32_t gotCommandFlag;
extern uint8_t commandBuffer[200];
void UARTIntHandler(void);
#endif
