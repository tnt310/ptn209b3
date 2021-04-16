#include <stdio.h>
#include <string.h>
//#include "provision.h"

char *main_channel = "CH1";
char *main_dev = "SENSOR1";
char *main_reg = "HUMD";
char *main_type = "number";
char *main_alias = "Voltage";

int createJson_provision(char buffer[], char *channel, char *name_dev, char *name_reg, char *type, char *alias)
{
    memset(buffer,0,sizeof(buffer));
    strcat(buffer,"{");
    strcat(buffer, channel);
    strcat(buffer, "_");
    strcat(buffer, name_dev);
    strcat(buffer, "_");
    strcat(buffer, name_reg);
    strcat(buffer,":");
    strcat(buffer, "{\"type\":");
    strcat(buffer,type);
    strcat(buffer, ",\"alias\":");
    strcat(buffer,alias);
    strcat(buffer,"}");
}
// CH1_INV1_VOLT: 	{ type: "number", alias: "Voltage" },
int main()
{
    char pub[30];
    createJson_provision(pub,main_name,main_type,main_alias);
    printf("%s",pub);
    return 0;
}