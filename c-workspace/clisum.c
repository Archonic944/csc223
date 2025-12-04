/* BDS C */

#include <stdio.h>

main(argc, argv)
int argc;
char* argv[];
{
    int i,sum;
    
    for(i = 1, sum = 0; i<argc; i++){
        int num;
        num = atoi(argv[i]);
        if (num == -1) {
            printf("Invalid input: %s\n", argv[i]);
            return(1);
        }
        sum += num;
    }
    printf("Sum: %d\n", sum);
}

atoi(s)
char s[];
{
    int i,n;

    n = 0;

    for(i = 0; s[i] != 0; i++){
        if(s[i] < '0' || s[i] > '9'){
            return(-1);
        }
        n = n * 10 + (s[i] - '0');
    }

    return(n);
}