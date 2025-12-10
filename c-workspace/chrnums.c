#include <stdio.h>
#define MAX_LINE 100

main(argc, argv)
int argc;
char* argv[];
{
    if(argc != 2){
        printf("Usage: chrnums <file>\n");
        exit();
    }

    FILE *fp;
    if((fp = fopen(argv[1], "r")) == NULL){
        printf("Error: Cannot open file %s\n", argv[1]);
        exit();
    }

    char lnbuf[MAX_LINE];
    int line_num;
    line_num = 1;
    while(fgets(lnbuf, MAX_LINE, fp) != NULL){
        printf("%d: %s", line_num++, lnbuf);
    }
    fclose(fp);
    exit();
}