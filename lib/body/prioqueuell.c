/* File : prioqueuell.c */
/* Representasi queue dengan list berkait dengan first (HEAD) dan last (TAIL) */
#include <stdlib.h>
#include <stdio.h>
#include "../header/prioqueuell.h"
#include "../header/globals.h"

void AlokasiElQueue (address *P, QueueInfoType X, int prio){
    *P = malloc(sizeof(ElmtQueue));
    if (*P != NULL) {
        Kesabaran(*P) = X;
        Prio(*P) = prio;
        NextQueue(*P) = NULL;
        LL wahanaIDList;
        CreateEmpty(&wahanaIDList);
        wahanaID(*P) = wahanaIDList;
    }
}

void DealokasiElQueue (address  P) {
    free (P);
}

boolean IsQueueEmpty (Queue Q) {
    return Head(Q) == NULL && Tail(Q) == NULL;
}

int NbElmtQueue(Queue Q) {
    int cnt = 0;
    if (!IsQueueEmpty(Q)) for (address P = Head(Q); P != Tail(Q); P = NextQueue(P), ++cnt);
    return cnt;
}
/*** Kreator ***/
void CreateEmptyQueue(Queue * Q) {
    Head(*Q) = NULL;
    Tail(*Q) = NULL;
}
/*** Primitif Enqueue/Dequeue ***/
void Enqueue(Queue * Q, address * A) {
	if (NbElmtQueue(*Q) != MAX_ANTRIAN) {
		address Piterator;

		Piterator = Head(*Q);
		if (IsQueueEmpty(*Q)) {
			Head(*Q) = *A;
			Tail(*Q) = *A;
		} else {
			for (Piterator = Head(*Q);
					NextQueue(Piterator) != Tail(*Q) && Prio(NextQueue(Piterator)) <= Prio(*A);
					Piterator = NextQueue(Piterator));

			/* node setelah Piterator adalah tail atau prio dari node
				* setelah Piterator lebih besar dari prio */

			/* node setelah Piterator adalah tail dan prionya lebih kecil atau
				* sama dengan variabel prio */
			if (NextQueue(Piterator) == Tail(*Q) && Prio(Tail(*Q)) <= Prio(*A)) {
				/* prionya ga ada yg lbh kecil, P dimasukin jadi tail */
				NextQueue(Piterator) = NextQueue(Tail(*Q));
				NextQueue(Tail(*Q)) = Piterator;
				Tail(*Q) = Piterator;
			}

			/* prio dari node setelah Piterator memiliki prio yang lebih besar
				* dari variabel prio */
			NextQueue(Piterator) = NextQueue(Piterator);
			NextQueue(Piterator) = Piterator;
		}
	}
}
void Dequeue(Queue * Q, address * X) {

    *X = Head(*Q);

    if (Tail(*Q) == Head(*Q)) { /* Cuman ada satu elemen */
        Tail(*Q) = NULL;
        Head(*Q) = NULL;
    } else {
        Head(*Q) = NextQueue(Head(*Q));
    }
}
