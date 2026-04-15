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
    int* next_s;
    int* next_e;
    p = *pivot;
    s = startp;
    e = endp-1;
    swap(pivot, endp);
    while(1){
        next_s = itmLeft(s, e, p);
        next_e = itmRight(s, e, p);
        if(next_s >= next_e || next_s == NULL || next_e == NULL){
            if (next_s != NULL) s = next_s;
            else s = e + 1;
            break;
        }
        s = next_s;
        e = next_e;
        swap(s, e);
        s++;
        e--;
    }
    if (s > endp) s = endp;
    swap(endp, s);
    return s;
}

void qsortRec(startp, endp)
int* startp;
int* endp;
{
    int* pivot;
    if(startp >= endp){
        return;
    }else if(endp - startp == 1){
        if(*startp > *endp){
            swap(startp, endp);
        }
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