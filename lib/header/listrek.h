/* File: listrek.h */
/* ADT list linier dengan representasi pointer */
/* Implementasi list linier secara rekursif */

#ifndef _LISTREK_H_
#define _LISTREK_H_

#include "boolean.h"

#define Nil NULL

/* Definisi Type */
typedef int ListRekInfoType;
typedef struct tElmtlist *address;
typedef struct tElmtlist {
    ListRekInfoType info;
    address next;
} ElmtListRek;

/* Definisi list : */
/* ListRek kosong : L = Nil */
typedef address ListRek;

/* Deklarasi  nama untuk variabel kerja */
/*  	L : ListRek */
/*  	P : address 	*/
/* Maka penulisan First(L) menjadi L */
/*                P.info menjadi Info(P); P.next menjadi Next(P) */

/* Selektor */
#define InfoListRek(P) (P)->info
#define NextListRek(P) (P)->next

/* *** Manajemen Memori *** */
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak Nil, dan misalnya menghasilkan P,
  maka Info(P) = X, Next(P) = Nil */
/* Jika alokasi gagal, mengirimkan Nil */
address AlokasiListRek (ListRekInfoType X);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
void DealokasiListRek (address P);

/* *** Primitif-primitif yang harus direalisasikan *** */

/* Pemeriksaan Kondisi ListRek */
/* Mengirimkan 1 jika L kosong dan 0 jika L tidak kosong */
int IsListRekEmpty(ListRek L);
/* Mengirimkan 1 jika L berisi 1 elemen dan 0 jika > 1 elemen atau kosong */
int IsListRekOneElmt(ListRek L);

/* *** Selektor *** */
/* Mengirimkan elemen pertama sebuah list L yang tidak kosong */
ListRekInfoType FirstListRekElmt (ListRek L);
/* Mengirimkan list L tanpa elemen pertamanya, mungkin menjadi list kosong */
ListRek ListRekTail(ListRek L);

/* *** Konstruktor *** */
/* Mengirimkan list L dengan tambahan e sebagai elemen pertamanya.
e dialokasi terlebih dahulu. Jika alokasi gagal, mengirimkan L. */
ListRek KonsoListRek(ListRekInfoType e, ListRek L);
/* Mengirimkan list L dengan tambahan e sebagai elemen terakhirnya */
/* e harus dialokasi terlebih dahulu */
/* Jika alokasi e gagal, mengirimkan L */
ListRek KonsBListRek(ListRek L, ListRekInfoType e);

/* *** Operasi Lain *** */
/* Mengirimkan salinan list L (menjadi list baru) */
/* Jika ada alokasi gagal, mengirimkan L */
ListRek CopyListRek(ListRek L);
/* I.S. Lin terdefinisi */
/* F.S. Lout berisi salinan dari Lin */
/* Proses : menyalin Lin ke Lout */
void MCopyListRek(ListRek Lin, ListRek *Lout);
/* Mengirimkan salinan hasil konkatenasi list L1 dan L2 (menjadi list baru) */
/* Jika ada alokasi gagal, menghasilkan Nil */
ListRek ConcatListRek(ListRek L1, ListRek L2);
/* I.S. L1, L2 terdefinisi */
/* F.S. LHsl adalah hasil melakukan konkatenasi L1 dan L2 dengan cara "disalin" */
/* Proses : Menghasilkan salinan hasil konkatenasi list L1 dan L2 */
void MConcatListRek(ListRek L1, ListRek L2, ListRek *LHsl);
/* I.S. L terdefinisi. */
/* F.S. Setiap elemen list dicetak. */
void PrintListRek(ListRek L);
/* Mengirimkan banyaknya elemen list L, Nol jika L kosong */
int NbElmtListRek(ListRek L);
/* Mengirim true jika X adalah anggota list, false jika tidak */
boolean SearchListRek(ListRek L, ListRekInfoType X);

#endif
