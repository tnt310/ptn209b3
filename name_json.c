#include <stdio.h>
#include <string.h>

int channel = 1;
static int i = 3;
char reg[10];
char dev[10];
char publish_buffer[1000];
/*------------------------------------------------------------------------------*/
enum
typedef struct{ // STRUCT DATA FROM EEPROM
    int id; // id
    int func;
    unsigned short reg_adr; // Adress reg
    char name[10]; // name of address reg
    char name_dev[10];
}data_t;
/*------------------------------------------------------------------------------*/
data_t table[200] =
{
	1,	3,	5,	"Temperture", "INV",
	10, 3,  4,	"Humidity", "SENSOR",
	1,	3,	2,	"Lumen", "SENSOR",
	2,	3,	8,	"Current", "INV",
	2,	3,	9,	"Voltage", "INV",
	5, 3, 	5,	"Power", "INV"
};
/*----------------------------GET REG NAME AND DEV NAME--------------------------------------*/
int Get_name(char name_1[10],char name_2[10],unsigned int channel, unsigned int id, unsigned int func, unsigned short reg)
{
	memset(name_1,0,10);
	for ( int j = 0; j< 10; j++)
	{
		name_1[j] = table[i].name[j];
        name_2[j] = table[i].name_dev[j];
	}
}
/*----------------------------CREATE JSON STRING--------------------------------------------------*/
int createJson(char demo[20],int channel,char name_reg[10],char name_dev[10], int val)
{
	memset(demo,0,20);
	strcat(demo,"\"");
	strcat(demo,name_dev);
	strcat(demo,"\"");
	strcat(demo,":");
	strcat(demo,itoa_user(val, 10));
	return demo;
	}
/*------------------------------------------------------------------------------*/
int main()
{

    Get_name(reg,dev,channel,table[i].id,table[i].func,table[i].reg_adr);
    printf("%s\n",reg);
    printf("%s",dev);
}