#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct{ 
	uint8_t channel;
    uint8_t id; // id
    uint8_t func; // function code
    uint16_t reg_adr; // Adress reg
    char *description;
    char *title; // name of address reg
    char *type; // number or boolean
}data1_t;

typedef struct{
	uint8_t channel;
    uint8_t id;
    uint8_t func;
    uint16_t reg_adr;
    char *alias;
}data_t;

uint8_t  createJson_provision(char *buffer, char *name,uint8_t channel, uint8_t id, char *type, char *title, char *description)
{
        memset(buffer,0,sizeof(buffer));
        strcat(buffer,"\"");
        strcat(buffer,name);
        strcat(buffer,"\"");
        strcat(buffer,":");
        strcat(buffer, "{\"type\":");
        strcat(buffer,"\"");
        strcat(buffer,type);
        strcat(buffer,"\"");
        strcat(buffer, ",\"title\":");
        strcat(buffer,"\"");
        strcat(buffer,title);
        strcat(buffer,"\"");
        strcat(buffer, ",\"description\":");
        strcat(buffer,"\"");
        strcat(buffer,description);
        strcat(buffer,"\"");
        strcat(buffer,"}");
}
uint8_t create_name(char buffer[20],uint8_t channel,uint8_t id,uint16_t reg, char *title, char *description)
{
    memset(buffer,0,20);
    char temp[5];
    switch(channel)
    {
        case 0:
        {
            strcat(buffer,"CH0_");
            strncpy(temp,description,3);
            strcat(buffer,temp);
            memset(temp,0,4);
            sprintf(temp,"%d",id);
            strcat(buffer,temp);
            strcat(buffer,"_");
            strncpy(temp,title,4);
            strcat(buffer,temp);
             memset(temp,0,4);
            sprintf(temp,"%d",reg);
            strcat(buffer,temp);
            break;
         }
         case 1:
        {
            strcat(buffer,"CH1_");
            strncpy(temp,description,3);
            strcat(buffer,temp);
            memset(temp,0,4);
            sprintf(temp,"%d",id);
            strcat(buffer,temp);
            strcat(buffer,"_");
            strncpy(temp,title,4);
            strcat(buffer,temp);
            memset(temp,0,4);
            sprintf(temp,"%d",reg);
            strcat(buffer,temp);
            break;
         }
        case 2:
        {
            strcat(buffer,"CH2_");
            strncpy(temp,description,3);
            strcat(buffer,temp);
            memset(temp,0,4);
            sprintf(temp,"%d",id);
            strcat(buffer,temp);
            strcat(buffer,"_");
            strncpy(temp,title,4);
            strcat(buffer,temp);
             memset(temp,0,4);
            sprintf(temp,"%d",reg);
            strcat(buffer,temp);
            break;
         }
    }
}
data1_t table1[] = 
{
		0,	2,	3,	0,   "SENSOR",		"TEMPERATURE",	"NUMBER",
		0,	2, 	3,  1, 	 "SENSOR",		"HUMIDITY",	    "NUMBER",
		0,	2,	3,	2,	 "INVERTER",	"POWER",	    "NUMBER",
		0,	2,	3,	3,	 "SENSOR",		"LUMEN",	    "NUMBER",
		0,	2,	3,	4,	 "METER",	 	"CURRENT",	    "NUMBER",
		0,	2,	3,	5,	 "METER",		"VOLTAGE",	    "NUMBER",
		0,	2,  3, 	6,	 "INVERTER",	"POWER",	    "NUMBER",
        1,  3,  6,  10,   "RELAY",       "LIGHT",       "BOOLEAN",
        1,  3,  6,  15,   "RELAY",       "LIGHT",       "BOOLEAN",
        2,  4,  6,  11,   "RELAY",       "FAN",         "BOOLEAN",
};
data_t table[];

uint8_t convert_table(data_t t1[], data1_t t2[])
{
    char name[20];
    uint8_t sum = sizeof(t2)/sizeof(data1_t);
    printf("%d",sum);
    for (uint8_t i = 0 ; i < sum ; i++)
    {
        t1[i].channel = t2[i].channel;
        t1[i].id = t2[i].id;
        t1[i].func = t2[i].func;
        t1[i].reg_adr = t2[i].reg_adr;
        create_name(name,t2[i].channel, t2[i].id,t2[i].reg_adr, t2[i].title, t2[i].description);
        t1[i].alias = name;
        printf("%d\t%d\t%d\t%d\t%s\n",t1[i].channel, t1[i].id,t1[i].func,t1[i].reg_adr, t1[i].alias);
    }
}

int main()
{
    char pub[100];
    char name[20];
    uint8_t cal = sizeof(table1)/sizeof(data1_t);
    convert_table(table,table1);
    // for (uint8_t i = 0; i < cal; i++)
    // {
    //     table[i].channel = table1[i].channel;
    //     table[i].id = table1[i].id;
    //     table[i].func = table1[i].func;
    //     table[i].reg_adr = table1[i].reg_adr;
    //     create_name(name,table1[i].channel, table1[i].id,table1[i].reg_adr, table1[i].title, table1[i].description);
    //     table[i].alias = name;
    //     printf("%d\t%d\t%d\t%d\t%s\n", table[i].channel, table[i].id, table[i].func, table[i].reg_adr,  table[i].alias);
    // }
}
