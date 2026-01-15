#include <stdio.h>
#include "LLIST.H"
#define NULL 0

int main(argc, argv)
int argc;
char* argv[];
{
    struct Node* ll;
    ll = buildLL();
    char* str[100];
    itoa(ll->data, str);
    puts(str);
    ll = ll->next;
    itoa(ll->data, str);
    puts(str);
}

struct Node* buildLL()
{
    struct Node first;
    first.data = 1;
    struct Node second;
    first.next = &second;
    second.data = 2;
    second.next = 0;
    return &first;
}

