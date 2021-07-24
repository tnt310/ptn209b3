 // Change a positive integer to a string in C 
  
 #include <stdio.h> 
 #include <stdlib.h>  // for malloc
 #include <math.h>  // for pow
  
 int get_number_of_digits(int n) 
 { 
     int i, count; 
     for (i = 10, count = 0; ; i *= 10, count++) { 
         if ((int)n / i == 0) { 
             break; 
         } 
     } 
     return count + 1; 
 } 
  
 int main() 
 { 
     int number, no_of_digits, prev = 0, i, j; 
     char *number_string; 
  
     scanf("%d", &number); 
     no_of_digits = get_number_of_digits(number); 
  
     number_string = (char *)malloc(sizeof(char) * (no_of_digits + 1)); // +1 for NULL 
     for (i = 0, j = pow(10, no_of_digits - 1); i < no_of_digits; i++, j /= 10) { 
         number_string[i] = (number / j - (prev * 10)) + 48;  // int to ascii
         prev             = number / j; 
     } 
     number_string[i] = '\0'; 
     printf("Int to String: %s\n", number_string); 
 }