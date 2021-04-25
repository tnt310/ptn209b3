
// C program to display hostname
// and IP address
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char *str = "HCMUT";
void f(const char *str, int str_len)
{
  printf("%.*s\n", str_len, str);
}

int main()
{
    f(str,strlen(str));
}