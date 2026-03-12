#include <stdio.h>
#include "maxheap.h"
#define NULL 0

/* struct and function headers are in maxheap.h */

void swap(a, b)
int* a;
int* b;
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

struct mkmaxheap(capacity)
int capacity;
{
    struct MaxHeap* heap;
    heap = alloc(sizeof(struct MaxHeap));
    heap->data = alloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

char insert(struct MaxHeap* heap, int num)
{
    if(heap->size == heap->capacity)
        return 1;
    int* data;
    data = heap->data;
    int i;
    i = heap->size++;
    data[i] = num;
    while(i > 0){
        if(data[i/2] < num){
            swap(data+i, data+i/2);
            i /= 2;
        }else{
            break;
        }
    }
    return 0;
}

int remove_max(struct MaxHeap* heap){
    if(heap->size == 0){
        return -1; /* idk lol */
    }
}
