
// C program to display hostname
// and IP address
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>
// #include <string.h>

// char *str = "HCMUT";
// void f(const char *str, int str_len)
// {
//   printf("%.*s\n", str_len, str);
// }

// int main()
// {
//     f(str,strlen(str));
// }

// C program to demonstrate strdup()
#include<stdio.h>
#include<string.h>
#include <stdint.h>

typedef struct{ // STRUCT DATA FROM EEPROM
    uint8_t port;   
    uint8_t id; // id
    uint8_t func;
    uint16_t reg;
    char *name_dev; // Adress reg
    char *type; // name of address reg
    char *name_reg;
} data_t;

data_t table[] =   // CHANNEL 1
{
	0,	10,	6,	7,	"CH1_INV3_FAN",		"number",		"Fan",
	0,	10,	6,	6,	"CH1_NODE1_REL1",	"boolean",		"Light",
	0,	10,	6,	5,	"CH1_NODE1_REL2",	"boolean",		"Light",
	0,	10,	6,	4,	"CH1_NODE1_REL3",	"boolean",		"Light"

};
//char *source = "CH3_INV1_VOLT";
char *source = "";
int main()
{
    for (uint8_t i = 0; i< (sizeof(table)/sizeof(data_t)); i++)
    {
        if (strstr(table[i].name_dev,source) != NULL)
        {
            printf("%d\t",table[i].port);
            printf("%d\t",table[i].id);
            printf("%d\t",table[i].func);
            printf("%d\t",table[i].reg);
            printf("%s\t",table[i].name_dev);
            printf("%s\t",table[i].type);
            printf("%s\t\n",table[i].name_reg);
        }
    }
}