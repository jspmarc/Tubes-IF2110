#include <stdlib.h>
#include <stdio.h>
#include "../header/prioqueuell.h"

#define nl printf("\n");
#define testa printf("testa\n");
#define testb printf("testb\n");

int main() {
    // Kamus
    Queue Q;
    QueueInfoType el;

    // Algoritma
    CreateEmptyQueue(&Q);
    if(IsQueueEmpty(Q)) printf("kosong1\n");
    el = 123;
    Enqueue(&Q, el, 1);
    if(IsQueueEmpty(Q)) printf("kosong2\n");
    Dequeue(&Q, &el);
    if(IsQueueEmpty(Q)) printf("kosong3\n");
    printf("%d\n", el);

    printf("END OF PROGRAM\n");
    return 0;
}
