struct MaxHeap {
    int* data;
    int size;
    int capacity;
};

struct MaxHeap* mkmaxheap();
/* Exit code 1 for full heap */
char insert();
int remove_max();
