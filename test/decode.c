#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// static uint8_t z =0;
//uint16_t arr[3];
uint8_t decode (char *str, uint16_t arr[3])
{
    char* const s = (char*)malloc(sizeof(strlen(str))+1);
    strcpy(s, "a");
    strcpy(s + strlen(s), str);
    uint8_t  total_n = 0;
    int n;
    uint16_t i;
    static uint8_t z =0;
    while (1 == sscanf(s + total_n, "%*[^0123456789-]%d%n", &i, &n))
    {
        arr[z] = i;
        total_n += n;
        z++;
       // printf("%d\t", i);
    }
}

int main()
{
    uint16_t arr[3];
    char *str = "CH2_SEN12_TEMP118";
    decode(str,arr);
    printf("%d\t%d\t%d\t", arr[0],arr[1],arr[2]);
}
