#include <stdio.h>
#include "maxheap.h"
#define NULL 0

/* struct and function headers are in maxheap.h */

void swap(a, b)
int* a;
int* b;
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int* max(a, b)
int* a;
int* b;
{
    if(*a > *b)
        return a;
    return b;
}

struct MaxHeap* mkmaxheap(max_capacity)
int max_capacity;
{
    struct MaxHeap* heap;
    heap = alloc(sizeof(*heap));
    heap->data = alloc(max_capacity * sizeof(*heap->data));
    heap->size = 0;
    heap->capacity = max_capacity;
    return heap;
}

char insert(heap, num)
struct MaxHeap* heap;
int num;
{
    int* dat;
    int i;
    if(heap->size == heap->capacity)
        return 1;
    dat = heap->data;
    i = heap->size++;
    dat[i] = num;
    while(i > 0){
        if(dat[(i-1)/2] < num){
            swap(dat+i, dat+(i-1)/2);
            i = (i-1)/2;
        }else{
            break;
        }
    }
    return 0;
}

int remove_max(heap)
struct MaxHeap* heap;
{
    int ret;
    int* dat;
    int i;
    if(heap->size == 0){
        return -1; /* idk lol */
    }
    dat = heap->data;
    ret = dat[0];
    dat[0] = dat[--(heap->size)];
    i = 0;
    while(i < heap->size){
        int left_idx;
        int right_idx;
        int max_idx;

        left_idx = 2*i + 1;
        right_idx = 2*i + 2;
        max_idx = i;

        if(left_idx < heap->size && dat[left_idx] > dat[max_idx]){
            max_idx = left_idx;
        }
        if(right_idx < heap->size && dat[right_idx] > dat[max_idx]){
            max_idx = right_idx;
        }

        if(max_idx == i){
            break;
        }

        swap(dat + i, dat + max_idx);
        i = max_idx;
    }
    return ret;
}
