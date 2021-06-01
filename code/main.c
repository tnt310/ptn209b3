#include <stdio.h>
#include <stdint.h>
#include "telemetry.h"

/*------------------------------------------------------------------------------*/
data1_t table1[] =
{
		0,	2,	3,	0x00,   "INVERTER",		        "INVERTER_01",		"VOLTAGE",	    "NUMBER",
		0,	2, 	3,  0x01, 	"INVERTER",		        "INVERTER_01",		"CURRENT",	    "NUMBER",
		0,	2,	3,	0x02,	"INVERTER",		        "INVERTER_01",		"POWER",	    "NUMBER",
        0,	2, 	3,  0x03, 	"INVERTER",		        "INVERTER_01",		"CURRENT",	    "NUMBER",
		0,	2,	3,	0x04,	"INVERTER",		        "INVERTER_01",		"POWER",	    "NUMBER",

        0,	6,	3,	0x03,   "WEATHERSTATION",		"STATION_01",		"TEMPERATURE",	"NUMBER",
		0,	6,	3,	0x04,   "WEATHERSTATION",		"STATION_01",		"HUMIDITY",	    "NUMBER",
		0,	6, 	3,  0x05, 	"WEATHERSTATION",		"STATION_01",		"LUMEN",	    "NUMBER",

        0,	3,	3,	0x03,   "WEATHERSTATION",		"STATION_02",		"TEMPERATURE",	"NUMBER",
		0,	3,	3,	0x04,   "WEATHERSTATION",		"STATION_02",		"HUMIDITY",	    "NUMBER",
		0,	3, 	3,  0x05, 	"WEATHERSTATION",		"STATION_02",		"LUMEN",	    "NUMBER",

        0,	10,	3,	0x03,   "METER",				"METER_01",		"TEMPERATURE",	"NUMBER",
		0,	10,	3,	0x04,   "METER",				"METER_01",		"HUMIDITY",	    "NUMBER",
		0,	10, 3,  0x05, 	"METER",				"METER_01",		"LUMEN",	    "NUMBER",

        0,	5, 	3,  0x03, 	"INVERTER",		        "INVERTER_02",		"CURRENT",	    "NUMBER",
		0,	5,	3,	0x04,	"INVERTER",		        "INVERTER_02",		"POWER",	    "NUMBER",
		0,	5,	3,	0x05,	"INVERTER",		        "INVERTER_02",		"POWER",	    "NUMBER",

		0,	8,	3,	 0x06,   "WEATHERSTATION",		"STATION_03",		"TEMPERATURE",	"NUMBER",
		0,	8,	3,	 0x07,   "WEATHERSTATION",		"STATION_03",		"HUMIDITY",	    "NUMBER",
		0,	8, 	3,   0x08, 	"WEATHERSTATION",		"STATION_03",		"LUMEN",	    "NUMBER",
		0,	8, 	3,   0x09, 	"WEATHERSTATION",		"STATION_03",		"LUMEN",	    "NUMBER",

	    0,	100,3,	0x06,   "METER",				"METER_02",		"VOLTAGE",		"NUMBER",
		0,	100,3,	0x07,   "METER",				"METER_02",		"CURRENT",	    "NUMBER",
		0,	100,3,  0x08, 	"METER",				"METER_02",		"POWER",	    "NUMBER",

		0,	8,	3,	0x01,   "WEATHERSTATION",		"STATION_03",		"TEMPERATURE",	"NUMBER",
		0,	8,	3,	0x02,   "WEATHERSTATION",		"STATION_03",		"HUMIDITY",	    "NUMBER",
		0,	8, 	3,  0x03, 	"WEATHERSTATION",		"STATION_03",		"LUMEN",	    "NUMBER",
		0,	8, 	3,  0x04, 	"WEATHERSTATION",		"STATION_03",		"LUMEN",	    "NUMBER",

        0,	100,3,	0x03,   "METER",				"METER_02",		"VOLTAGE",		"NUMBER",
		0,	100,3,	0x04,   "METER",				"METER_02",		"CURRENT",	    "NUMBER",
		0,	100,3,  0x05, 	"METER",				"METER_02",		"POWER",	    "NUMBER",
};
int main()
{
    uint8_t SUM = sizeof(table1)/sizeof(data1_t);
    uint8_t SUM = sizeof(table1)/sizeof(data1_t);
    char demo[100];
    // static uint8_t id1,id2,temp;
    // temp = table1[0].deviceID;
    // for (uint8_t i = 0; i <SUM; i++)
    // {
    //     id1 = table1[i].deviceID;
    //     for (uint8_t j = 0; j <SUM; j++)
    //     {
    //         if (table1[j].deviceID == id1 ){
    //             printf("%d\t",table1[j].deviceID);
    //             break;
    //         }
    //     }
    // }
    ping_json(demo,111);
    //printf("%s",demo);
}



int main()
{
    uint8_t SUM = sizeof(table1)/sizeof(data1_t);
    char head[1000];
    char tail[1000];
    char demo[100];
    char temp[31];
    static uint8_t count = 0;
    for (uint8_t i = 0; i <SUM; i++) // duyệt từng phần tử trong mảng
    {
        temp[i] = table1[i].deviceID;
        for (uint8_t j = 0; j <SUM; j++)  // duyệt ID device
        {
            if (table1[j].deviceID == table1[i].deviceID && table1[i].deviceID != table1[i-1].deviceID)
            {
                count++;
                if (count == 1)
                    {
                        head_provision(head);
                        mid_provision(demo,table1[j].deviceID,table1[j].deviceName,table1[j].deviceType);
                        strcat(head,demo);
                        for (uint8_t z = 0; z < SUM; z++)  // duyệt các channel thuộc về ID
                        {
                            if (table1[z].deviceID == table1[j].deviceID){
                                tail_provision(tail,table1[z].deviceChannel,table1[z].deviceTitle,table1[z].valueType,NULL);
                                strcat(head,tail);
                            }
                        }
                        strcat(head,"}");
                        printf("\n%s\n",head);
                    }
            }
        }
        count = 0;
    }
    //printf("\n%d\n",SUM);
}

int main()
{
    char head[1000];
    char tail[500];
    char demo[100];
    static uint8_t count = 0;
    for (uint8_t i = 0; i <SUM; i++) // duyệt từng phần tử trong mảng
    {
        for (uint8_t j = 0; j <SUM; j++)  // duyệt ID device
        {
            if (table1[j].deviceID == table1[i].deviceID && table1[i].deviceID != table1[i-1].deviceID)
            {
                count++;
                if (count == 1)
                    {
                        head_provision(head);
                        mid_provision(demo,table1[j].deviceID,table1[j].deviceName,table1[j].deviceType);
                        strcat(head,demo);
                        for (uint8_t z = 0; z < SUM; z++)  // duyệt các channel thuộc về ID
                        {
                            if (table1[z].deviceID == table1[j].deviceID){
                                tail_provision(tail,table1[z].deviceChannel,table1[z].deviceTitle,table1[z].valueType,NULL);
                                strcat(head,tail);
                            }
                        }
                        strcat(head,"}");
                        printf("\n%s\n",head);
                    }
            }
        }
        count = 0;
    }
}


int main()
{
    char head[1000];
    char tail[500];
    char demo[500];
    char temp[SUM];
    volatile uint8_t mutex = 0;
    static uint8_t count = 0;
    for (uint8_t i = 0; i <SUM; i++) // duyệt từng phần tử trong mảng
    {
        temp[i] = table1[i].deviceID;
        for (uint8_t j = 0; j <SUM; j++)  // duyệt ID device
        {
            if (table1[j].deviceID == table1[i].deviceID)
            {
                for (uint8_t k = 0; k < i; k++)
                {
                    if(i == 0){
                        break;
                    }
                    else if (table1[i].deviceID == temp[k]){
                        mutex = 1;
                    }
                }
                if (mutex == 1)
                {
                    count ++;
                    if (count == 1)
                    {
                        head_provision(head);
                        mid_provision(demo,table1[j].deviceID,table1[j].deviceName,table1[j].deviceType);
                        strcat(head,demo);
                        for (uint8_t z = 0; z < SUM; z++)  // duyệt các channel thuộc về ID
                        {
                            if (table1[z].deviceID == table1[j].deviceID){
                                tail_provision(tail,table1[z].deviceChannel,table1[z].deviceTitle,table1[z].valueType,NULL);
                                strcat(head,tail);
                            }
                        }
                        head[strlen(head) - 1] = '\0';
                        strcat(head,"}");
                        printf("\n%s\n",head);
                    }
                }

            }
        }
        count = 0;
    }
}