#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main()
{
    int n = 0;
    do {
        printf("NHAP SO PHAN TU MANG: ");
        scanf("%d",&n);
    }
    while(n <= 0);
    printf("SO PHAN TU MANG: N = %d", n);
    printf("\nNHAP TUNG PHAN TU MANG: ");
    int a[n];
    for (uint8_t i = 0; i < n; i++){
        scanf("%d",&a[i]);
        printf("\na[%d]= %d",i,a[i]);
    }
    printf("\nMANG NGUOC: ");
    int b[n];
    int x = 0;
    for (uint8_t i = 1; i <= n; i++){
        a[n-i] = a[i];
        printf("\na[%d]= %d",n-i,a[n-i]);
    }
}