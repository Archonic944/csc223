#include <stdio.h>

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
int *result;
{
    char c;
    *result = 0;

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
    char *p;
    p = s;
    if((sign = n) < 0){
        n = -n;
    }
    i = 0;
    do{
        *s++ = n % 10 + '0';
        i++;
    }while((n = n / 10) > 0);
    if(sign < 0){
        *s++ = '-';
        i++;
    }
    *s = '\0';
    revstr(p, i);
}

revstr(str, len)
char *str;
int len;
{
    char *p2;
    char temp;
    p2 = str + len - 1;
    while(str < p2){
        temp = *str;
        *str++ = *p2;
        *p2-- = temp;
    }
}