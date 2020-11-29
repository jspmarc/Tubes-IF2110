/* File : prioqueuell.h */
/* Representasi queue dengan list berkait dengan first (HEAD) dan last (TAIL) */
#ifndef _PRIOQUEUELL_H
#define _PRIOQUEUELL_H
#include "boolean.h"
#include "../header/listlinier.h"
#include <stdlib.h>

#define KAKI_PEGEL 100

/* Deklarasi QueueInfoType */
/* Kesabaran pengunjung */
typedef int QueueInfoType;

/* Queue dengan representasi berkait dengan pointer */
typedef struct tElmtQueue * address;
typedef struct tElmtQueue {
    QueueInfoType kesabaran; /* Kesabaran pengunjung */
    address NextQueue; /* Pengunjung di belakangnya */
    int prio; /* prioritas pengunjung */
    LL wahanaID; /* Wahana yang mau dinaikin pengunjung */
} ElmtQueue;

/* Type queue dengan ciri HEAD dan TAIL : */
typedef struct {
    address HEAD;  /* alamat penghapusan */
    address TAIL;  /* alamat penambahan */
} Queue;

/* Selektor */
#define Head(Q)      (Q).HEAD
#define Tail(Q)      (Q).TAIL
#define InfoHead(Q)  (Q).HEAD->Info
#define InfoTail(Q)  (Q).TAIL->Info
#define NextQueue(P) (P)->NextQueue
#define Kesabaran(P) (P)->kesabaran
#define Prio(P)      (P)->prio
#define wahanaID(P)  (P)->wahanaID

/* Prototype manajemen memori */
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan
        NextQueue(P)=Nil */
/*      P=Nil jika alokasi gagal */
void AlokasiQueue(address *P, QueueInfoType X, int prio);

/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
void DealokasiQueue(address  P);

/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
boolean IsQueueEmpty(Queue Q);

/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */
/*** Kreator ***/
int NbElmtQueue(Queue Q);

/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
/*** Primitif Enqueue/Dequeue ***/
void CreateEmptyQueue(Queue * Q);

/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q
   jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
void Enqueue(Queue * Q, address * A);

/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi
   elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */
void Dequeue(Queue * Q, address * X);

void PelangganMarah(Queue *Q);

#endif
