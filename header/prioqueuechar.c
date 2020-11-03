#include <stdio.h>
#include "boolean.h"
#include "prioqueuechar.h"
#include <stdlib.h>

/* ********* Prototype ********* */
boolean IsEmpty (PrioQueueChar Q) {

    return Head(Q) == Nil && Tail(Q) == Nil;
}
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsFull (PrioQueueChar Q) {

    if (Head(Q) == 0) {
        return Tail(Q) == MaxEl(Q) - 1;
    }
    else { //Head(Q) != 0 
        return Tail(Q) == Head(Q) - 1;
    } 
}
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */

int NBElmt (PrioQueueChar Q) {
    if (IsFull(Q)) {
        return MaxEl(Q);
    } else if (IsEmpty(Q)){
        return 0;
    } else if (Tail(Q) >= Head(Q)) {
        return Tail(Q) - Head(Q) + 1;
    } else {
        return MaxEl(Q) - (Head(Q) - Tail(Q) + 1); 
    }
}
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

/* *** Kreator *** */
void MakeEmpty (PrioQueueChar * Q, int Max) {
    (*Q).T = (infotype *) malloc (Max * sizeof(infotype));
    if ((*Q).T != NULL) {
        MaxEl(*Q) = Max;
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
    } else {
        MaxEl(*Q) = 0;
    }
}
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void DeAlokasi(PrioQueueChar * Q) {
    MaxEl(*Q) = 0;
    free((*Q).T);
}
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void Enqueue (PrioQueueChar * Q, infotype X) {

    //Algoritma
    if (IsEmpty(*Q)) {
        Head(*Q) = 0;
        Tail(*Q) = 0;
        InfoTail(*Q) = X;
    } else if (Tail(*Q) == MaxEl(*Q) - 1) {
        Tail(*Q) = 0;
        if (Prio(Elmt(*Q, MaxEl(*Q) - 1)) <= Prio(X)) {
            InfoTail(*Q) = X;
        } else {
            boolean found = false;
            int i = MaxEl(*Q) - 2;
            int count = 0;
            while (i >= Head(*Q) && !found) {
                if (Prio(Elmt(*Q, i)) <= Prio(X)) {
                    found = true;
                }
                count++;
                i--;
            }
            int j = MaxEl(*Q) - 1;
            Elmt(*Q, 0) = Elmt(*Q, j);
            while (j > Head(*Q)) {
                Elmt(*Q, j) = Elmt(*Q, j - 1);
                j--;
                }
            Elmt(*Q, j) = X;
            }
        } else {
        Tail(*Q)++;
        if (Prio(Elmt(*Q, MaxEl(*Q) - 1)) <= Prio(X)) {
            InfoTail(*Q) = X;
        } else {
            boolean found = false;
            int i = MaxEl(*Q) - 1;
            int count = 0;
            while (i >= Head(*Q) && !found) {
                if (Prio(Elmt(*Q, i)) <= Prio(X)) {
                    found = true;
                }
                count++;
                i--;
            }
            if (found) {
                int n = count;
                int j = Tail(*Q);
                Elmt(*Q, 0) = Elmt(*Q, Tail(*Q));
                while (j > Head(*Q)) {
                    Elmt(*Q, j) = Elmt(*Q, j - 1);
                    j--;
                    }
                Elmt(*Q, j) = X;
                }
            
        }
    }
}
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */

void Dequeue (PrioQueueChar * Q, infotype * X) {

    *X = InfoHead(*Q);
    if (Head(*Q) == Tail(*Q)) {
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
    } else if (Head(*Q) == MaxEl(*Q) - 1) {
        Head(*Q) = 0;
    } else {
        Head(*Q)++;
    }
}
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */

void PrintPrioQueueChar (PrioQueueChar Q) {
    if (IsEmpty(Q)) {
        printf ("#\n");
    }
    else {
        int i = Head(Q);
        while (i != Tail(Q) + 1) {
            if (i == MaxEl(Q)) {
                i = 0;
            }
            printf ("%d %c\n", Prio(Elmt(Q, i)), Info(Elmt(Q, i)));
            i++;
        }
        printf("#\n");
    }
}
/* Mencetak isi queue Q ke layar */
/* I.S. Q terdefinisi, mungkin kosong */
/* F.S. Q tercetak ke layar dengan format:
<prio-1> <elemen-1>
...
<prio-n> <elemen-n>
#
*/