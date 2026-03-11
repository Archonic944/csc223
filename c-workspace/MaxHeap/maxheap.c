struct maxheap {
    int *data;
    int size;
    int capacity;
};

struct maxheap* mkmaxheap(int capacity);
void insert(struct maxheap* heap, int data);
int remove_max(struct maxheap* heap);
