/* File : stacklist.h */
#ifndef _STACKLIST_H
#define _STACKLIST_H

#include "boolean.h"
#include "jam.h"
#include <stdlib.h>

/* Konstanta */
#define Nil NULL

/* List ID aksi: (Prep phase)
 * ID   -   Aksi
 * 1    -   Build
 * 2    -   Upgrade
 * 3    -   Buy
 * 4    -   Undo
 * 5    -   Execute
 * 6    -   Main (play)
 */
#define BUILD 1
#define UPGRD 2
#define BUY 3

/* Deklarasi StackInfoType */
/* Nunjuk ke struk eksekusi aksi */
typedef void* StackInfoType;

typedef struct {
    unsigned char idAksi;
    JAM durasiAksi;
} PropertiAksi;

/* Stack dengan representasi berkait dengan pointer */
typedef struct tElmtStack * StackAddress;
typedef struct tElmtStack {
    StackInfoType Info;
    StackAddress Next;
    PropertiAksi prop;
} ElmtStack;

/* Struktur data stack dengan akses element Top()
 * Digunakan untuk menyimpan action-action pada game.
 * Info adalah integer yang menyimpan id aksi.
 */
typedef struct {
    StackAddress TOP;  /* alamat TOP: elemen puncak */
} Stack;


/* Selektor */
#define Top(S) (S).TOP
#define InfoTop(S) (S).TOP->Info
#define AksiTop(S) (S).TOP->idAksi
#define Next(P) (P)->Next
#define Info(P) (P)->Info
#define Aksi(P) (P)->idAksi

/* Prototype manajemen memori */
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
void AlokasiStack (StackAddress *P, StackInfoType X);
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
void DealokasiStack (StackAddress P);

/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
/* Mengirim true jika Stack kosong: TOP(S) = Nil */
boolean IsStackEmpty (Stack S);
/* I.S. sembarang */
/* F.S. Membuat sebuah stack S yang kosong */
void CreateEmptyStack (Stack * S);
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
void Push (Stack * S, StackInfoType X, unsigned char idAksi);
/* Menghapus X dari Stack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */
void Pop (Stack * S, StackInfoType * X);

#endif
