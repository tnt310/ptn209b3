#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint8_t GETJSON(char *payload,char *buffer, char *key1, char *key2);
const char buf[200] = "+CMQTTRXSTART: 0,14,30\n\n+CMQTTRXTOPIC: 0,14\ntelemetrytopic\n+CMQTTRXPAYLOAD: 0,30\n{name:CH1_SEN2_HUMD,value:111}\n+CMQTTRXEND: 0";
const char topic_key[] = "TOPIC";

uint8_t GETJSON(char *payload, char *buffer, char *key1, char *key2){
    memset(payload,0,sizeof(payload));
    uint8_t index_start  = strcspn(buf,key1);
    uint8_t index_end  = strcspn(buf,key2);
    strncpy(payload,&buf[index_start],index_end - index_start + 1);
}
int main()
{
    char payload[100];
    GETJSON(payload,buf, "{","}");
    //uint8_t index_start  = strcspn(buf,"\n");
   // printf("%d\n",index_start);
    printf("%s",payload);
}