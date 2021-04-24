/*
 * provision.c
 *
 *  Created on: Apr 13, 2021
 *      Author: ACER
 */


/* PROVISION MESSAGE */
/* Topic: 606ff2e222c1752264934dbb/upstream/provision
*
	    {
	      v: { type: "number", alias: "Voltage" },
	      i: { type: "number", alias: "Current" },
	      p: { type: "number", alias: "RealPower" },
	      q: { type: "number", alias: "ReactivePower" },
		}

Ex: 	{
	      CH1_INV1_VOLT: { type: "number", alias: "Voltage" },
	      CH1_INV1_CURR: { type: "number", alias: "Current" },
	      CH1_INV1_RPOW: { type: "number", alias: "RealPower" },
	      CH1_INV1_RPOW: { type: "number", alias: "ReactivePower" },
	      CH1_SENSOR1_TEMP: { type: "number", alias: "Temperature" },
	      CH1_SENSOR1_HUMD: { type: "number", alias: "Humidity" },
	      CH1_SENSOR1_LUME: { type: "number", alias: "Lumen" }
		}

		{
	      CH1_INV1_VOLT: { "type": number, "alias":Voltage},
	      CH1_INV1_CURR: { type: "number", alias: "Current" },
	      CH1_INV1_RPOW: { type: "number", alias: "RealPower" },
	      CH1_INV1_RPOW: { type: "number", alias: "ReactivePower" },
	      CH1_SENSOR1_TEMP: { type: "number", alias: "Temperature" },
	      CH1_SENSOR1_HUMD: { type: "number", alias: "Humidity" },
	      CH1_SENSOR1_LUME: { type: "number", alias: "Lumen" }
		}
*/

#include "provision.h"
#include <string.h>
#include "param.h"
/*
 * brief: Provision Json
 * buffer: buffer contains provision json
 * name: name of device
 * type: number/string
 * alias: name of address register*/


uint8_t createJson_provision(char buffer[],char *name,char *type, char *alias)
{
    memset(buffer,0,sizeof(buffer));
    strcat(buffer,"{");
    strcat(buffer,name);
    strcat(buffer,":");
    strcat(buffer, "{\"type\":");
    strcat(buffer,"\"");
    strcat(buffer,type);
    strcat(buffer,"\"");
    strcat(buffer, ",\"description\":");
    strcat(buffer,"\"");
    strcat(buffer,alias);
    strcat(buffer,"\"");
    strcat(buffer,"}");
}
/**
 * Brief: Prepare provision json*/

