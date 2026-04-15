#include "BDSCTEST.h"
#include "QSORT.H"

#define MAX_ELEMENTS 1000

/* Custom is_space to avoid missing <ctype.h> dependencies */
int is_space(c)
char c;
{
    return (c == ' ' || c == '\n' || c == '\r' || c == '\t');
}

/* Custom is_digit */
int is_digit(c)
char c;
{
    return (c >= '0' && c <= '9');
}

/* Reads integers from an open file until EOF or max_size is reached */
int read_ints(fp, arr, max_size)
FILE *fp;
int *arr;
int max_size;
{
    int count;
    int c;
    int val;
    int sign;
    
    count = 0;
    while (count < max_size) {
        c = getc(fp);
        
        /* Skip whitespace */
        while (c != EOF && is_space(c)) {
            c = getc(fp);
        }
        
        if (c == EOF || c == 26) /* 26 is ^Z, EOF in CP/M */
            break;
        
        sign = 1;
        if (c == '-') {
            sign = -1;
            c = getc(fp);
        }
        
        val = 0;
        while (c != EOF && c != 26 && is_digit(c)) {
            val = val * 10 + (c - '0');
            c = getc(fp);
        }
        
        arr[count++] = val * sign;
    }
    
    return count;
}

int main(argc, argv)
int argc;
char **argv;
{
    FILE *fin;
    FILE *fout;
    int arr[MAX_ELEMENTS];
    int count;
    int i;
    int is_sorted;
    
    if (argc < 3) {
        printf("Usage: testqs <input_file> <output_file>\n");
        return 1;
    }
    
    /* Open input file */
    fin = fopen(argv[1], "r");
    if (!fin) {
        printf("Error: Could not open input file %s\n", argv[1]);
        return 1;
    }
    
    /* Read data */
    count = read_ints(fin, arr, MAX_ELEMENTS);
    fclose(fin);
    
    printf("Read %d elements from %s. Sorting...\n", count, argv[1]);
    
    START_TESTING("QuickSort File I/O Tests");
    
    TEST_CASE("Sort data from input file");
    
    /* Sort data using the algorithm from QSORT.H */
    myQsort(arr, count);
    
    /* Verify the array is sorted */
    is_sorted = 1;
    for (i = 0; i < count - 1; i++) {
        if (arr[i] > arr[i+1]) {
            is_sorted = 0;
            break;
        }
    }
    
    /* Assert that the file data was successfully sorted */
    ASSERT(is_sorted);
    
    END_TESTING();
    
    /* Open output file */
    fout = fopen(argv[2], "w");
    if (!fout) {
        printf("Error: Could not open output file %s\n", argv[2]);
        return 1;
    }
    
    /* Write results */
    for (i = 0; i < count; i++) {
        fprintf(fout, "%d\n", arr[i]);
    }
    
    fclose(fout);
    
    printf("Successfully wrote sorted results to %s\n", argv[2]);
    return 0;
}