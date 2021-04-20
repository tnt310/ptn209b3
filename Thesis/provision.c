#include <stdio.h>
#include <string.h>

char *main_name = "CH1_INV1_VOLT";
char *main_type = "number";
char *main_alias = "Voltage";

    int createJson_provision(char buffer[30], char *name, char *type, char *alias)
    {
        memset(buffer,0,sizeof(buffer));
        strcat(buffer,"{");
        strcat(buffer,name);
        strcat(buffer,":");
        strcat(buffer, "{\"type\":");
        strcat(buffer,"\"");
        strcat(buffer,type);
        strcat(buffer,"\"");
        strcat(buffer, ",\"alias\":");
        strcat(buffer,"\"");
        strcat(buffer,alias);
        strcat(buffer,"\"");
        strcat(buffer,"}");
    }
// CH1_INV1_VOLT: 	{ "type": "number", "alias": "Voltage" },
int main()
{
    char pub[30];
    createJson_provision(pub,main_name,main_type,main_alias);
    printf("%s",pub);
    return 0;
}