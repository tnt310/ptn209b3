#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct{ // STRUCT DATA FROM EEPROM
	uint8_t channel;
    uint8_t id; // id
    uint8_t func; // function code
    uint16_t reg_adr; // Adress reg
    char *description;
    char *title; // name of address reg
    char *type; // number or boolean
}data1_t;
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
        2,  4,  6,  11,   "RELAY",       "FAN",       "BOOLEAN",
       
};
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
int main()
{
    uint8_t cal = sizeof(table1)/sizeof(data1_t);
    char pub[100];
    char name[20];
    //create_name(pub,table1[0].channel, table1[0].id, table1[0].title, table1[0].description);
    
    for (uint8_t i = 0 ; i < cal; i++)
    {
       create_name(name,table1[i].channel, table1[i].id,table1[i].reg_adr, table1[i].title, table1[i].description);
       createJson_provision(pub,name,table1[i].channel, table1[i].id, table1[i].type, table1[i].title, table1[i].description);
       printf("%s\n",pub);
    }
}
