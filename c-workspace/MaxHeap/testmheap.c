#include <stdio.h>
#include "maxheap.h"

int main()
{
    struct MaxHeap* heap;
    int i;
    heap = mkmaxheap(1000);
    for(i = 0; i < 1000; i++){
        printf("%d ", i);
        insert(heap, i);
    }
    printf("\n------------------------------\n");
    for(i = 0; i < 1000; i++){
        printf("%d ", remove_max(heap));
    }
    printf("\n");
}
