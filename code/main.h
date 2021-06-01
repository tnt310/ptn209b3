#ifndef _MAIN_H
#define _MAIN_H

#include <stdint.h>

uint8_t PRINTF_EN = 1;
#define p(fmt,...) if (PRINTF_EN == 1) printf(fmt,##__VA_ARGS__)
#define s(fmt,...) if (PRINTF_EN == 1) scanf(fmt,##__VA_ARGS__)


#endif