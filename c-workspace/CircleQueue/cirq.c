/* BDS C */

#include <stdio.h>

struct CircularQueue {
    int front;
    int back;
    char* arr;
    int size;
};

void cirqFree(cirq)
struct CircularQueue cirq;
{
    free(cirq.arr);
}

/* returns a response code. 1 for success 0 for error */
char cirqAdd(cirq, element) /* constraint: element cannot be 0 (null char) */
struct CircularQueue cirq;
char element;
{
    if(element == 0){
        return 0;
    }
    if(cirq.back == -1 && cirq.front == -1){
        cirq.front = 0;
        cirq.back = 0;
        cirq.arr[0] = element;
        return 1;
    }else if(cirq.back == cirq.size-1){
        if(cirq.front == 0){
            return 0; /* overflow */
        }
        cirq.back = 0;
        cirq.arr[0] = element;
        return 1;
    }else if(cirq.back == cirq.front-1){
        return 0; /* overflow */
    }else{
        cirq.arr[++cirq.back] = element;
        return 1;
    }
}

/* returns the removed element, or char 0 if error (element cannot be 0; see cirqAdd) */
char cirqRemove(cirq)
struct CircularQueue cirq;
{
    if(cirq.front == -1 && cirq.back == -1){
        return 0;
    }else if(cirq.back == cirq.front){ /* special case for only 1 element; reset the buffer*/
        char c;
        c = cirq.arr[cirq.back];
        cirq.back = -1;
        cirq.front = -1;
        return c;
    }else if(cirq.front == cirq.size){
        cirq.front = 0;
        return cirq.arr[cirq.size];
    }else{
        return cirq.arr[cirq.front++];
    }
}

int main(argc, argv)
int argc;
char** argv;
{
    int size;
    size = 5;
    printf("Creating circular linked list of size %d", size);
    struct CircularQueue cirq;
    cirq = cirqCreate(size);
    printf("Adding items");
    cirqAdd(cirq, 'a');
    cirqAdd(cirq, 'b');
    cirqAdd(cirq, 'c');
    cirqAdd(cirq, 'd');
    printf("Popping 2 items");
    printf("0: %c", cirqRemove(cirq));
    printf("1: %c", cirqRemove(cirq));
    printf("Adding 3 more items, which would break a normal queue");
    cirqAdd(cirq, 'x');
    cirqAdd(cirq, 'y');
    cirqAdd(cirq, 'z');
    printf("Now let's read the whole list");
    printf("0: %c", cirqRemove(cirq));
    printf("1: %c", cirqRemove(cirq));
    printf("2: %c", cirqRemove(cirq));
    printf("3: %c", cirqRemove(cirq));
    printf("4: %c", cirqRemove(cirq));
}

void cirqInit(cirq, size)
struct CircularQueue* cirq;
int size;
{
    struct CircularQueue cirq;
    cirq->front = -1;
    cirq->back = -1;
    cirq->arr = alloc(cirq->size);
    cirq->size = size;
    return cirq;
}