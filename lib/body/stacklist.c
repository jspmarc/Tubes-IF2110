/* File : stacklist.c */
#include "boolean.h"
#include "../header//stacklist.h"
#include <stdlib.h>

/* Prototype manajemen memori */
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
void Alokasi (address *P, infotype X) {
    *P = (address) malloc(sizeof(ElmtStack));
    if (P != Nil) {
        Info(*P) = X;
        Next(*P) = Nil;
    }
}
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
void Dealokasi (address P) {
    free(P);
}

/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
/* Mengirim true jika Stack kosong: TOP(S) = Nil */
boolean IsEmpty (Stack S) {
    return Top(S) == Nil;
}
/* I.S. sembarang */
/* F.S. Membuat sebuah stack S yang kosong */
void CreateEmpty (Stack * S) {
    Top(*S) = Nil;
}
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
void Push (Stack * S, infotype X) {
    address P;

    Alokasi(&P, X);

    if (P != Nil) {
        Next(P) = Top(*S);
        Top(*S) = P;
    }
}
/* Menghapus X dari Stack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */
void Pop (Stack * S, infotype * X) {
    address P;

    P = Top(*S);
    *X = Info(P);
    Top(*S) = Next(P);

    Dealokasi(P);
}
