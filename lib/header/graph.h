/* File : graph.h */
/* Definisi ADT Graph */
/* Menggunakan representai multilist */

#ifndef GRAPH_H
#define GRAPH_H

#include "boolean.h"
#include "listlinier.h"

#define NodeUndef 0

typedef List infotypeG;
typedef struct tElmtGraph *addressG;
typedef struct tElmtGraph {
    infotypeG info;
    addressG next;
} ElmtGraph;
typedef struct {
    addressG FirstG;
} Graph;

/* SELEKTOR */
#define Info(P) (P)->info
#define Next(P) (P)->next
#define FirstG(G) (G).FirstG

/****************** PEMBUATAN GRAPH KOSONG ******************/
void CreateEmptyGraph(Graph *G);
/* I.S. G sembarang */
/* F.S. Terbentuk graph kosong */

/****************** TEST GRAPH KOSONG ******************/
boolean IsEmptyGraph(Graph G);
/* mengeluarkan true jika graph G kosong */

/****************** Manajemen Memori ******************/
addressG AlokasiGraph (infotypeG X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokasiGraph (addressG *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

/*** PENAMBAHAN ELEMEN ***/
void InsVFirstGraph (Graph *G, infotypeG X);
/* I.S. G mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan list X jika alokasi berhasil */
void InsVLastGraph(Graph *G, infotypeG X);
/* I.S. G mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen graph di akhir: elemen terakhir yang baru */
/* merupakan list X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENCARIAN ELEMEN ***/
boolean IsNodeConnected(Graph G, infotype X1, infotype X2);
/* true jika X1 dan X2 terhubung, false jika tidak */

#endif