#include <stdio.h>
#include <string.h>

int channel = 1;
static int i = 3;
char reg[10];
char dev[10];
char buffer[30];
char publish_buffer[1000];
/*------------------------------------------------------------------------------*/
typedef enum
{
	CHANNEL_1,
	CHANNEL_2,
	CHANNEL_3
}channel_t;
/*------------------------------------------------------------------------------*/
typedef struct{ // STRUCT DATA FROM EEPROM
    int id; // id
    int func;
    int  reg_adr; // Adress reg
    char name_reg[10]; // name of address reg
    char name_dev[10];
} data_t;
/*------------------------------------------------------------------------------*/
data_t table[200] =
{
	1,	3,	5,	"Temp", "INV",
	10, 3,  4,	"Humidity", "SENSOR",
	1,	3,	2,	"Lumen", "SENSOR",
	2,	3,	8,	"Current", "INV",
	2,	3,	9,	"Voltage", "INV",
	5, 3, 	5,	"Power", "INV"
};
/*------------------------------------------------------------------*/
int* itoa_user(int  val, unsigned int base) {
	static unsigned int buf[32] = { 0 };  // 32 bits
	int i = 30;
	if (val == 0)
		buf[i--] = '0';
	for (; val && i; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];

	return &buf[i + 1];
}
/*----------------------------GET REG NAME AND DEV NAME--------------------------------------*/
int Get_name(char name_1[10],char name_2[10],unsigned int channel, unsigned int id, unsigned int func, int  reg)
{
	memset(name_1,0,10);
	for ( int j = 0; j< 10; j++)
	{
		name_1[j] = table[i].name_reg[j];
        name_2[j] = table[i].name_dev[j];
	}
}
/*----------------------------CREATE JSON STRING--------------------------------------------------*/
uint8_t createJson(char demo[30], char channel[10],char name_reg[10],char name_dev[10], uint16_t val)
{
	memset(demo,0,30);
	strcat(demo,"{\"");
	strcat(demo,channel);
	strcat(demo,"_");
	strcat(demo,name_reg);
	strcat(demo,"_");
	strcat(demo,name_dev);
	strcat(demo,"\"");
	strcat(demo,":");
	strcat(demo,itoa_user(val, 10));
	strcat(demo, "}");
	}
/*------------------------------------------------------------------------------*/
int main()
{
	channel_t CH;
	
    //Get_name(reg,dev,CHANNEL_1,table[i].id,table[i].func,table[i].reg_adr);
	createJson(buffer,"CH1",table[xQueueMbMQtt.countflag].name,table[xQueueMbMQtt.countflag].name_dev, xQueueMbMQtt.RegData.i16data);
    //printf("%s\n",reg);
	printf("%s\n",buffer);
    //printf("%s",dev);
	return 0;
}