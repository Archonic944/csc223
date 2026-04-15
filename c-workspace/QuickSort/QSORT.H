/* BDS C Quick Sort */
/* Gabe Cohen */
/* (in BDS c function parameter types are defined after the function header) */

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
            break;
        }
        swap(s, e);
    }
    swap(endp, s);
    return s;
}

void qsortRec(startp, endp)
int* startp;
int* endp;
{
    int* pivot;
    if(endp - startp == 1){
        if(*startp > *endp){
            swap(startp, endp);
        }
        return;
    }else if(endp - startp < 1){
        return;
    }
    pivot = medianOfThree(startp, endp);
    pivot = partition(startp, endp, pivot);
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