#include <stdio.h>

main() {
    int biggest;
    unsigned ubiggest;
    unsigned n, m, prod;
    biggest = 32767;
    ubiggest = 65535;
    printf("The value of biggest is now %d.\n", biggest);
    printf("The value of ubiggest is now %u.\n", ubiggest);
    biggest++;
    ubiggest++;
    printf("Add 1 to it and we get %u!\n", biggest);
    printf("Add 1 to it and we get %d!\n", ubiggest);
    biggest++;
    printf("Add another 1 to biggest and we get %d!\n", biggest);
    ubiggest--;
    printf("Subtract 1 from ubiggest and we get %d!\n", ubiggest);
    ubiggest = -65535;
    printf("ubiggest = -65535: %d\n", ubiggest);
    ubiggest = -1;
    printf("ubiggest = -1: %d\n", ubiggest);
    n =  65000;
    m = 3;
    prod = n * m;
    printf("%u * %u = %u -- Why?\n", m, n, prod);
}