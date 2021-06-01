#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "telemetry.h"
#include "json.h"
int main()
{
    data1_t *ptr;
    FILE *file;
    file = fopen("DEVICE.TXT","r");
    char line[255];
    static uint8_t k = 0;
    while(fgets(line,255,file)){
        k++;
        //p("%s",line);
        parse(line, strlen(line));
    }
    p("line: %d",k);
    // ptr = (data1_t*)calloc(k, sizeof(data1_t));
    // if (ptr != NULL){
    //     for (size_t i = 0; i < k; i++){
    //     }
    //     free(ptr);
    // }
    fclose(file);
    return 0;
}