#include <stdio.h>
#include <string.h>
#include <math.h>
typedef struct{ // STRUCT DATA FROM EEPROM
    int id; // id
    int func;
    int  reg_adr; // Adress reg
    char name_reg[10]; // name of address reg
    char name_dev[10];
} data_t;

data_t table[] =   // CHANNEL 1
{
		3,	3,	100,	"TEMP", 	"INV1",
		3, 	3,  101,	"HUMD", 	"SENSOR2",
		3,	3,	102,	"POWR",		"METER1",
		3,	3,	103,	"LUME", 	"SENSOR4",
		3,	3,	104,	"CURR", 	"INV2",
		3,	3,	105,	"VOLT", 	"INV3",
		3,  3, 	106,	"POWR", 	"INV2",
		3, 	3,	107,	"RPOW",		"INV8",
		3,	3,	108,	"HUMD",		"SENSOR7",
		3,	3,	109,	"POWR",		"METER1",	
};
data_t t[]=
{

}

int main()
{
    int a =  ((sizeof(t))/(sizeof(data_t)));
    printf("%d",a);
}