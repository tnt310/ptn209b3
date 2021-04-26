#include<stdio.h>
#include<string.h>
#include <stdint.h>


char eep[] = {0,10,6,1,0,12,'C','H','1','_','I','N','V','3','_','F','A','N',1,3,'F','A','N',
              0,10,6,6,8,14,'C','H','1','_','N','O','D','E','1','_','R','E','L','1',1,5,'L','I','G','H','T'};

typedef union
{
	uint16_t i16data;
	uint8_t  i8data[2];
}int16toint8;
typedef struct{ // STRUCT DATA FROM EEPROM
    uint8_t port;   
    uint8_t id; // id
    uint8_t func;
    int16toint8 reg;
    char name_dev[20]; // Adress reg
    char *type; // name of address reg
    char name_reg[20];
} data_t;

data_t table[];
uint8_t convert()
{
    for (int i = 0; i < 1; i++)
    {
        table[i].port = eep[i];
        table[i].id = eep[i + 1];
        table[i].func = eep[i + 2];
        table[i].reg.i8data[1] = eep[i + 3];
        table[i].reg.i8data[0] = eep[i + 4];
        strncpy(table[i].name_reg, &eep[i + 6], eep[i+5]);
        if (eep[i + 6 + eep[i+5]] == 1){
            table[i].type = "number";}
        else{
            table[i].type = "boolean";}
        strncpy(table[i].name_dev, &eep[i + 8 + eep[i+5]] ,eep[i + 7 + eep[i+5]]);
    }
}
int main()
{
    convert();
    printf("%d\t%d\t%d\t%d\t%s\t%s\t%s",table[0].port,table[0].id,table[0].func,table[0].reg.i16data,
                                    table[0].name_reg,table[0].type,table[0].name_dev);
}



// data_t table[] =   // CHANNEL 1
// {
// 	0,	10,	6,	7,	"CH1_INV3_FAN",		"number",		"Fan",
// 	0,	10,	6,	6,	"CH1_NODE1_REL1",	"boolean",		"Light",
// 	0,	10,	6,	5,	"CH1_NODE1_REL2",	"boolean",		"Light",
// 	0,	10,	6,	4,	"CH1_NODE1_REL3",	"boolean",		"Light"
// };
