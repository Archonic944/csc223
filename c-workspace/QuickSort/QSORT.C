/* BDS C Quick Sort */
/* Gabe Cohen */
/* (in BDS c function parameter types are defined after the function header) */

#include <stdio.h>
#define NULL 0

void swap(a, b)
int* a;
int* b;
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int* medianOfThree(startp, endp)
int* startp;
int* endp;
{
    int* midp;
    int startn;
    int endn;
    int midn;
    midp = startp + (endp - startp)/2;
    
    startn = *startp;
    endn = *endp;
    midn = *midp;
    if((startn < endn && startn > midn) || (startn < midn && startn > endn)){
        return startp;
    }else if((endn < startn && endn > midn) || (endn < midn && endn > startn)){
        return endp;
    }
    return midp;
}

int* itmLeft(startp, endp, pivot)
int* startp;
int* endp;
int pivot;
{
    int* i;
    for(i = startp; i <= endp; i++){
        if(*i >= pivot){
            return i;
        }else{
            printf("%d was not ge to %d\n", *i, pivot);
        }
    }
    return NULL;
}

int* itmRight(startp, endp, pivot)
int* startp;
int* endp;
int pivot;
{
    int* i;
    for(i = endp; i >= startp; i--){
        if(*i <= pivot){
            return i;
        }
    }
    return NULL;
}

int* partition(startp, endp, pivot)
int* startp;
int* endp;
int* pivot;
{
    int* s;
    int* e;
    int p;
    p = *pivot;
    s = startp;
    e = endp-1;
    swap(pivot, endp);
    while(1){
        s = itmLeft(s, e, p);
        e = itmRight(s, e, p);
        if(s >= e || s == NULL || e == NULL){
            printf("s=%d e=%d\n", *s, *e);
            break;
        }
        swap(s, e);
    }
    if(s == NULL){
        printf("s is NULL\n");
    }
    swap(endp, s);
    return s;
}

void qsortRec(startp, endp)
int* startp;
int* endp;
{
    int* i;
    int* pivot;
    printf("Recursing from %d to %d\n", *startp, *endp);
    if(endp - startp == 2){
        if(*startp > *endp){
            swap(startp, endp);
        }
        return;
    }else if(endp - startp == 1){
        return;
    }
    pivot = medianOfThree(startp, endp);
    printf("Pivot: %d\n", *pivot);
    pivot = partition(startp, endp, pivot);
    printf("Partitioned: ");
    for(i = startp; i <= endp; i++){
        printf("%d ", *i);
    }
    printf("\n");
    qsortRec(startp, pivot-1);
    qsortRec(pivot+1, endp);
}

void myQsort(arr, size)
int* arr;
int size;
{
    if(size <= 1){
        return;
    }
    
    qsortRec(arr, arr+size-1);
}

int main(){
    int arr[10];
    int i;
    initw(arr, "10,9,8,7,6,5,4,3,2,1");
    myQsort(arr, 10);
    for(i = 0; i < 10; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}