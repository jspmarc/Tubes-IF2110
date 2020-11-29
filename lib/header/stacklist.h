/* File : stacklist.h */
#ifndef _STACKLIST_H
#define _STACKLIST_H

#include "boolean.h"
#include "jam.h"
#include <stdlib.h>

/* Konstanta */
#define Nil NULL

/* Deklarasi StackInfoType */
/* Nunjuk ke struk eksekusi aksi */
typedef void* StackInfoType;
//typedef union {
//} StackInfo;
//typedef StackInfo* StackInfoType;

typedef struct {
    unsigned char idAksi;
    JAM durasiAksi;
} PropertiAksi;

/* Stack dengan representasi berkait dengan pointer */
typedef struct tElmtStack * StackAddress;
typedef struct tElmtStack {
    StackInfoType StackInfo;
    StackAddress StackNext;
    PropertiAksi prop;
} ElmtStack;

/* Struktur data stack dengan akses element Top()
 * Digunakan untuk menyimpan action-action pada game.
 * StackInfo adalah integer yang menyimpan id aksi.
 */
typedef struct {
    StackAddress TOP;  /* alamat TOP: elemen puncak */
} Stack;


/* Selektor */
#define Top(S) (S).TOP
#define StackInfoTop(S) (S).TOP->StackInfo
#define AksiTop(S) (S).TOP->idAksi
#define StackNext(P) (P)->StackNext
#define StackInfo(P) (P)->StackInfo
#define Aksi(P) (P)->prop
#define IdAksi(P) (P).idAksi
#define DurasiAksi(P) (P).durasiAksi

/* Prototype manajemen memori */
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka StackInfo(P)=X dan
        StackNext(P)=Nil */
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
void Push (Stack * S, StackInfoType X, PropertiAksi prop);
/* Menghapus X dari Stack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */
void Pop (Stack * S, StackInfoType * X, PropertiAksi *prop);
#endif
