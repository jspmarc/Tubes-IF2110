/* File : prioqueuell.c */
/* Representasi queue dengan list berkait dengan first (HEAD) dan last (TAIL) */
#include <stdlib.h>
#include <stdio.h>
#include "../header/prioqueuell.h"

void AlokasiElQueue (address *P, infotype X, int prio){
    *P = malloc(sizeof(ElmtQueue));
    if (*P != Nil) {
        Info(*P) = X;
        Prio(*P) = prio;
        Next(*P) = Nil;
    }
}

void DealokasiElQueue (address  P) {
    free (P);
}

boolean IsQueueEmpty (Queue Q) {
    return Head(Q) == Nil && Tail(Q) == Nil;
}

int NbElmtQueue(Queue Q) {
    int cnt = 0;
    if (!IsQueueEmpty(Q)) for (address P = Head(Q); P != Tail(Q); P = Next(P), ++cnt);
    return cnt;
}
/*** Kreator ***/
void CreateEmptyQueue(Queue * Q) {
    Head(*Q) = Nil;
    Tail(*Q) = Nil;
}
/*** Primitif Enqueue/Dequeue ***/
void Enqueue(Queue * Q, infotype X, int prio) {
    address P, Piterator;
    AlokasiElQueue(&P, X, prio);
    if (P != Nil) {
        if (IsQueueEmpty(*Q)) {
            Head(*Q) = P;
            Tail(*Q) = P;
        } else {
            for (Piterator = Head(*Q);
                    Next(Piterator) != Tail(*Q) && Prio(Next(Piterator)) <= prio;
                    Piterator = Next(Piterator));

            /* node setelah Piterator adalah tail atau prio dari node
             * setelah Piterator lebih besar dari prio */

            /* node setelah Piterator adalah tail dan prionya lebih kecil atau
             * sama dengan variabel prio */
            if (Next(Piterator) == Tail(*Q) && Prio(Tail(*Q)) <= prio) {
                /* prionya ga ada yg lbh kecil, P dimasukin jadi tail */
                Next(P) = Next(Tail(*Q));
                Next(Tail(*Q)) = P;
                Tail(*Q) = P;
            }

            /* prio dari node setelah Piterator memiliki prio yang lebih besar
             * dari variabel prio */
            Next(P) = Next(Piterator);
            Next(Piterator) = P;
        }
    }
}
void Dequeue(Queue * Q, infotype * X) {
    address P = Head(*Q);

    *X = Info(P);

    if (Tail(*Q) == Head(*Q)) { /* Cuman ada satu elemen */
        Tail(*Q) = Nil;
        Head(*Q) = Nil;
    } else {
        Head(*Q) = Next(P);
    }

    DealokasiElQueue(P);
}
