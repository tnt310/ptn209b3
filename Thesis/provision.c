#include <stdio.h>
#include <string.h>
#include "provision.h"

// CH1_INV1_VOLT: 	{ type: "number", alias: "Voltage" },
int creatJson_provison(char buffer[30], char *name, char *type, char *alias)
{
    memset(buffer,0,sizeof(buffer));
    strcat(buffer,"{");
    strcat(buffer, name);
    strcat(buffer,":");
    strcat(buffer,"{type:");
    strcat(buffer,type);
    strcat(buffer,"",alias:"");

}

int main()
{
    char buf[30];
    return 0;
}