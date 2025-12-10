#include <stdio.h>

main(argc, argv)
int argc;
char* argv[];
{
    if(argc != 3){
        printf("Usage: backward <file> <outfile>\n");
        exit();
    }

    FILE* fp;
    FILE* wfp;
    if(!(fp = fopen(argv[1], "r"))){
        printf("Error opening file %s", argv[1]);
        exit();
    }

    if(!(wfp = fopen(argv[2], "w"))){
        printf("Error opening file to write: %s", argv[2]);
        exit();
    }

    printf("Starting to process file...\n");
    int debug;
    char line[100];
    debug = 0;
    while(fgets(line, 100, fp) != NULL){
        int length;
        length = slen(line);
        reverse(line, length);
        fputs(line, wfp);
        debug++;
    }
    if(debug == 0){
        printf("No lines were processed.");
    }else{
        printf("Processed %d lines.", debug);
    }
    fclose(fp);
    fclose(wfp);
    exit();
}

reverse(str, len)
char str[];
int len;
{
    int i;
    char temp;
    for(i = 0; i<(len/2); i++){
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

slen(str)
char str[];
{
    int i;
    for(i = 0; str[i] != 0; i++);
    return(i-1);
}