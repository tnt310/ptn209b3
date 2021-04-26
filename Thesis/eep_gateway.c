#include<stdio.h>
#include<string.h>
#include <stdint.h>


char eep[] = {0,10,6,1,0,12,'C','H','1','_','I','N','V','3','_','F','A','N',1,3,'F','A','N',
               0,10,6,2,0,14,'C','H','1','_','N','O','D','E','1','_','R','E','L','1',1,5,'L','I','G','H','T',
               0,10,6,2,0,15,'C','H','1','_','N','O','D','E','1','2','_','R','E','L','1',1,8,'H','U','M','I','D','I','T','Y'};
typedef union        //  state = state + 6 + eep[state+5] + eep[state + 7 + eep[state+5]];
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
static uint8_t state = 0;
uint8_t sl =3;
data_t table[];
uint8_t convert()
{
    for (int i = 0; i < sl; i++)
    {   
        table[i].port = eep[state + 0];
        table[i].id = eep[state + 1];
        table[i].func = eep[state + 2];
        table[i].reg.i8data[1] = eep[state + 3];
        table[i].reg.i8data[0] = eep[state + 4];
        strncpy(table[i].name_reg, &eep[state + 6], eep[state+5]);
        if (eep[state + 6 + eep[state+5]] == 1){
            table[i].type = "number";}
        else{
            table[i].type = "boolean";}
        strncpy(table[i].name_dev, &eep[state + 8 + eep[state+5]] ,eep[state + 7 + eep[state+5]]);
        state = state + 8 + eep[state+5] + eep[state + 7 + eep[state+5]];
    }
}
int main()
{
    
    convert();
    for (uint8_t i = 0; i< sl; i++)
    {
        printf("%d\t%d\t%d\t%d\t%s\t%s\t%s\n",table[i].port,table[i].id,table[i].func,table[i].reg.i16data,
                                    table[i].name_reg,table[i].type,table[i].name_dev);

    }
}



// data_t table[] =   // CHANNEL 1
// {
// 	0,	10,	6,	7,	"CH1_INV3_FAN",		"number",		"Fan",
// 	0,	10,	6,	6,	"CH1_NODE1_REL1",	"boolean",		"Light",
// 	0,	10,	6,	5,	"CH1_NODE1_REL2",	"boolean",		"Light",
// 	0,	10,	6,	4,	"CH1_NODE1_REL3",	"boolean",		"Light"
// };
