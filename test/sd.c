#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main()
{
    char buffer[200];
    SDformatJson(buffer,0,10,3,1000,"STATION","TEMPERATURE","STATION_01","NUMBER");
    printf("%s\n",buffer);
    printf("%d",strlen(buffer));
}