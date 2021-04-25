
// C program to display hostname
// and IP address
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>
// #include <string.h>

// char *str = "HCMUT";
// void f(const char *str, int str_len)
// {
//   printf("%.*s\n", str_len, str);
// }

// int main()
// {
//     f(str,strlen(str));
// }

// C program to demonstrate strdup()
#include<stdio.h>
#include<string.h>
  
int main()
{
    char source[] = "GeeksForGeeks";
  
    // A copy of source is created dynamically
    // and pointer to copy is returned.
    char* target = strdup(source); 
  
    printf("%s", target);
    return 0;
}