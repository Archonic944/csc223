#include <stdio.h>

// EXERCISE 5-2 - strcat with pointers

strcat(s, t)
char *s, *t;
{
    while (*s != '\0'){
        s++;
    }
    while((*s = *t) != '\0'){
        s++;
        t++;
    }
} 


atoi(s, result)
char *s;
int* result;
{
    *result = 0;
    char c;

    for(c = 0; (c = *s++) != 0; ){
        if(c < '0' || c > '9'){
            return(-1);
        }
        *result = *result * 10 + (c - '0');
    }
    return(0);
}

itoa(n, s)
int n;
char *s;
{
    int i;
    int sign;
    char *p = s;
    if((sign = n) < 0){
        n = -n;
    }
    i = 0;
    do{
        *s++ = n % 10 + '0';
        i++;
    }while((n /= 10) > 0);
    if(sign < 0){
        *s++ = '-';
        i++;
    }
    *s = '\0';
    reverse(p, i);
}

reverse(str, len)
char *str;
int len;
{
    char *end;
    end = str + sizeof(char) * len - sizeof(char);
    char temp;
    while(str < end){
        temp = *str;
        *str++ = *end;
        *end-- = temp;
    }
}