#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

/*----------------------------ITOA_USER--------------------------------------*/
uint8_t* itoa_user(int val, int  base) {

	static uint8_t buf[32] = { 0 };  // 32 bits
	int i = 30;
	if (val == 0)
		buf[i--] = '0';
	for (; val && i; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];

	return &buf[i + 1];
}

char demo[100];

uint8_t CreateATcommand(int argc, char *argv[])
{
	//snprintf(aux_str, sizeof(aux_str),"AT+CMQTTCONNECT=%d,\"%s:%d\",%d,%d,\"%s\",\"%s\"",state,server,port,keepalive,1,username,password);
	//sprintf(api,"%s%c",GET,(char) 26);
	memset(demo,0,100);
	strcat(demo,argv[0]);
	strcat(demo,"=");
	for (uint8_t i = 1; i< argc; i++)
	{
		strcat(demo,itoa_user(argv[i],10));
        strcat(demo,",");
	}
	strcat(demo,"\r\n");
}

int main()
{
    CreateATcommand("AT+CSQ",50);
    printf("%s",demo);
    return 0;
}