    // data1_t *p;
    // data1_t *dynamic;
    // FILE *file;
    // file = fopen("DEVICE.TXT","r");
    // char line[200];
    // static uint8_t k = 0;
    // static uint8_t j = 0;
    // while(fgets(line,200,file)){
    //     k++; // get lines
    // }
    // fclose(file);
    // printf("\nnum of line k =: %d",k);
    // dynamic = (data1_t*)calloc(k,sizeof(data1_t));
    // if (dynamic!=NULL){
    //     file = fopen("DEVICE.TXT","r");
    //     while(fgets(line,200,file)){
    //         j++;
    //         p = parse((char*)line, strlen(line));
    //         AddDevice((dynamic+j-1),p);
    //         printf("\nline %d: %d\t%d\t%d\t%d\t%s\t%s\t%s\t%s\t%d",j-1,
    //         (dynamic+j-1)->channel,(dynamic+j-1)->deviceID,(dynamic+j-1)->func,
    //         (dynamic+j-1)->deviceChannel,(dynamic+j-1)->deviceType,(dynamic+j-1)->deviceName,
    //         (dynamic+j-1)->channeltitle,(dynamic+j-1)->valueType,(dynamic+j-1)->devicestatus);
    //     }
    //     fclose(file);
    // }
    // printf("\n\nDEVICES WERE ADDED TO DYNAMIC ARRAY");
    // for (uint8_t i = 0; i < k; i++){
    //     printf("\nLine %d: %d\t%d\t%d\t%d\t%s\t%s\t%s\t%s\t%d",i,
    //     (dynamic+i)->channel,(dynamic+i)->deviceID,(dynamic+i)->func,
    //     (dynamic+i)->deviceChannel,(dynamic+i)->deviceType,(dynamic+i)->deviceName,
    //     (dynamic+i)->channeltitle,(dynamic+i)->valueType,(dynamic+i)->devicestatus);
    // }
    // free(dynamic);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

typedef struct backup
{
    char *deviceType;
    char *deviceName;
    char *channeltitle;
    char *valueType;
};


void convert(char *destination, char *source)
{
    strncpy(destination, source,strlen(source)+1);
    //printf("destination: %s",destination);
}
int main()
{
    struct backup *data;
    char *s="INVERTER";
    convert(data->deviceType,s);
    printf("%s",data->deviceType);

}