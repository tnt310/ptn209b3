#include <stdio.h>
#include <string.h>

int channel = 1;
static int i = 0;
char reg[10];
char dev[10];
char publish_buffer[1000];
char chan[5] ="CH1";
char buffer[50];
char publih_buffer[200];
int main_time[6] = {15,11,25,26,6,21};
/*------------------------------------------	------------------------------------*/
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
	1,	3,	5,	"Temp", "SENSOR2",
	10, 3,  4,	"Humidity", "SENSOR2",
	1,	3,	2,	"Lumen", "SENSOR4",
	//2,	3,	8,	"Current", "INV2",
	//2,	3,	9,	"Voltage", "INV2",
	//5, 3, 	5,	"Power", "INV5"
};
/*----------------------------ITOA_USER--------------------------------------*/
int* itoa_user(int val, int  base) {

	static int buf[32] = { 0 };  // 32 bits
	int i = 30;
	if (val == 0)
		buf[i--] = '0';
	for (; val && i; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];

	return &buf[i + 1];
}
/*----------------------------GET REG NAME AND DEV NAME--------------------------------------*/
int Get_name(char name_reg[10],char name_dev[10],char channel[5], unsigned int id, unsigned int func, unsigned short reg)
{
	memset(name_reg,0,10);
    memset(name_dev,0,10);
	for ( int j = 0; j< 10; j++)
	{
		name_reg[j] = table[i].name[j];
        name_dev[j] = table[i].name_dev[j];
	}
}
/*----------------------------CREATE JSON STRING--------------------------------------------------*/
int createJson(char demo[100],char channel[5],char name_reg[10],char name_dev[10], int val, int time[6])
{
	memset(demo,0,100);
	strcat(demo,chan);
	strcat(demo,"_");
	strcat(demo,name_dev);
	strcat(demo,"_");
	strcat(demo,name_reg);
	strcat(demo,":");
    strcat(demo,"[{time:");
    strcat(demo,itoa_user(time[0], 10)); // Hour
    strcat(demo,":");
    strcat(demo,itoa_user(time[1], 10)); // Minute
    strcat(demo,":");
    strcat(demo,itoa_user(time[2], 10)); //Second
    strcat(demo," ");
    strcat(demo,itoa_user(time[3], 10));// Month
    strcat(demo,".");
    strcat(demo,itoa_user(time[4], 10)); // Day
    strcat(demo,".");
    strcat(demo,itoa_user(time[5], 10)); //Year
    strcat(demo,",");
    strcat(demo,"value");
    strcat(demo,":");
    strcat(demo,itoa_user(val, 10));
    strcat(demo,"}]");

	}
/*------------------------------------------------------------------------------*/
int main()
{

    //Get_name(reg, dev, chan, table[i].id, table[i].func, table[i].reg_adr);
    //printf("%s\n",reg);
   // printf("%s",dev);
   strcat(publih_buffer,"{");
   for (i = 0; i< 4; i++)
   {
        createJson(buffer,chan,table[i].name,table[i].name_dev,table[i].reg_adr,main_time);
        if (i < 3)
        {
            strcat(publih_buffer,buffer);
            strcat(publih_buffer,",");
        }
        else
        {
            strcat(publih_buffer,"}");
            printf("\n%s",publih_buffer);
            memset(publih_buffer,0,sizeof(buffer));
        }
       
   }
    return 0;
}
// CH1_INV1_VOLT: 	[{time: 10:10:25 26.6.2021, value: 220}],