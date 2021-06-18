#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

char *nhapchuoi(char *&s)
{
   char a[1000];
   printf("NHAP VAO CHUOI:");
   fgets(a,sizeof(a),stdin);
   s = strdup(a);
   return s;
}

int main()
{
   char *s;
   nhapchuoi(s);
   if (s != NULL){
      printf("chuoi vua nhap la: %s",s);
      free(s);
   }
}