#include <stdarg.h>  
#include <stdint.h> 
#include <stdio.h>
#include <string.h>  
#include <stddef.h>
#include <limits.h>
#include <unistd.h>  
#include <stdlib.h>  

 
void my_rust(char n){   
   write(1, &n, 1);  
}  
int my_poke(char* str){  
   int i = 0;  
   while(str[i] != '\0'){  
       my_rust(str[i]);  
       i++;  
     }  
     return i;
}  
void my_print(int ac[], int av)           // av = argv, ac = argc
{  
   const char c[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};  
 
   if(av == 0) {  
       my_rust('0');  
   }  
 
   while(av) {  
       my_rust(c[ac[--av]]);  
   }  
}  
int my_norm(unsigned long long nrg, int d)  
{  
   int av = 0;  
   int *ac;  
   ac = (int *)malloc(sizeof(int) * 128);  
 
while(nrg) {  
 ac[av++] = (int)(nrg % d);  
 nrg /= d;  
}  
my_print(ac, av);  
 free(ac);  
   
return av != 0 ? av : 1 ;  
}  
int my_printn(unsigned int nrg)  
{  
   return my_norm(nrg, 10);  
}  
int my_file2(int nrg)  
{  
   int proval = nrg;  // proval = nrg
   int negative = 0;  
 
   if(proval < 0) {  
       putchar('_');  
       proval *= -1;  
       negative = 1;  
   }  
 
   return my_printn(proval) + negative;  
}  
 
int my_ruxshon(void* nrg)  
{  
 
   write(1,"0x",2);  
   return my_norm((unsigned long long)nrg, 0x10);  
}  
int my_file1(unsigned int nrg)  
{  
   return my_norm(nrg, 0x08);  
}  
 
int my_printf(char* str , ...){  
   va_list sine;  
   va_start(sine, str);  
   int sum = 0;  
   char c;  
   char* string;  
   int numb; // numb = number   
   for(int i = 0; str[i] != '\0'; i++){  
       if(str[i] == '%'){  
           i++;  
           switch (str[i]){  // case
             
           case 'd':  
               sum+=my_file2(va_arg(sine,int));  
                break;
           case 'o':  
                numb += my_file1(va_arg(sine, unsigned int));  
             break; 
            case 'u':  
                sum+=my_printn(va_arg(sine,unsigned int));  
            break; 
             case 'x':  
                   numb = va_arg(sine, int);  
                   int ruxshona;  
                   char hc[100];  
                   int fs = 0;  
                   while(numb !=0){  
                       ruxshona = numb %16;  
                       if(ruxshona < 10){  
                           hc[fs++] = 48 + ruxshona;  
                    }else 
                       {  
                            hc[fs++] = 55 + ruxshona;  
                       }  
                       numb = numb/16;    
                   }  
                   fs--;  
                   while(fs>=0) {  
                             my_rust(hc[fs]);  
                             fs--;  
                            sum++;  
                   }  
               break;
                 case 'p':  
                 sum += my_ruxshon(va_arg(sine, void*))+2;  
               break;  
               default:  
                   my_rust('%');  
                   my_rust(str[i]);  
                   sum++;      
               case 'c':  
               c = (char)va_arg(sine, int);  
               my_rust(c);  
               sum++;  
              break;  
                        
           case 's':  
           string = va_arg(sine, char*);  
           if(string == (char*) NULL){  
               string = "(null)";  
           }  
           sum += my_poke(string);  
           break;  
            }  
       }  
       else {  
       my_rust(str[i]);  
       sum++;  
       }  
   }  
   return sum;  
}
int main(){
   char* f = "hello!";
   my_printf("%c%c%c%c%c!\n", 'H', 'e', 'l', 'l', 'o');
   my_printf("Hello world!\n");
   my_printf("%c!\n", 'H');
   my_printf("%s\n",f);
   my_printf("%p!\n", 1337);
}