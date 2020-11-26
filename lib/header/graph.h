/* File : graph.h */
/* Definisi ADT Graph */
/* Menggunakan representai multilist */

#ifndef GRAPH_H
#define GRAPH_H

#include "boolean.h"
#include "listlinier.h"

#define Nil NULL

typedef struct tNode * adrNode;
typedef struct tSuccNode * adrSuccNode;
typedef struct tNode {
    int Id;
    int NPred;
    adrSuccNode Trail;
    adrNode Next;
} Node;
typedef struct tSuccNode {
    adrNode Succ;
    adrSuccNode Next;
} SuccNode;

typedef struct {
    adrNode First;
} Graph;

/* SELEKTOR */
#define GraphFirst(G) (G).First
#define Id(Pn) (Pn)->Id
#define NPred(Pn) (Pn)->NPred
#define Trail(Pn) (Pn)->Trail
#define GraphNext(Pn) (Pn)->Next
#define Succ(Pt) (Pt)->Succ

/****************** PEMBUATAN GRAPH KOSONG ******************/
/* I.S. G sembarang */
/* F.S. Terbentuk graph kosong */
void CreateGraph(int X, Graph * G);

/****************** TEST GRAPH KOSONG ******************/
/* mengeluarkan true jika graph G kosong */
boolean IsEmptyGraph(Graph G);

/****************** Manajemen Memori ******************/
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka GraphInfo(P)=X, GraphNext(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
adrNode AlokNode (int X);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
void DealokNode (adrNode P);

/* Mengembalikan address hasil alokasi. */
/* Jika alokasi berhasil, maka address tidak Nil, misalnya
    menghasilkan Pt, maka Succ(Pt)=Pn dan GraphNext(Pt)=Nil. Jika
    alokasi gagal, mengembalikan Nil. */
adrSuccNode AlokSuccNode (adrNode Pn);

/* I.S. P terdefinisi; F.S. P dikembalikan ke sistem */
/* *** Manajemen Memory List Successor (Trailer) *** */
void DealokSuccNode (adrSuccNode P);

/* Mengembalikan address simpul dengan I */
adrNode SearchNode (Graph G, int X);

/* mengembalikan address trailer yang menyimpan info busur (prec,succ)
jika sudah ada pada graph G, Nil jika belum */
adrSuccNode SearchEdge (Graph G, int prec, int succ);

/* { Menambahkan simpul X ke dalam graph, jika alokasi X berhasil. */
/* I.S. G terdefinisi, X terdefinisi dan belum ada pada G. */
/* F.S. Jika alokasi berhasil, X menjadi elemen terakhir G, Pn berisi
    address simpul X. Jika alokasi gagal, G tetap, Pn berisi Nil */
void InsertNode (Graph * G, int X, adrNode * Pn);

/* Menambahkan busur dari prec menuju succ ke dalam G */
/* I.S. G, prec, succ terdefinisi. */
/* F.S. Jika belum ada busur (prec,succ) di G, maka tambahkan busur
(prec,succ) ke G. Jika simpul prec/succ belum ada pada G,
tambahkan simpul tersebut dahulu. Jika sudah ada busur (prec,succ)
di G, maka G tetap. */
void InsertEdge (Graph * G, int prec, int succ);

/* Menghapus simpul X dari G */
/* I.S. G terdefinisi, X terdefinisi dan ada pada G, jumlah simpul
pada G lebih dari 1. */
/* F.S. simpul X dan semua busur yang terhubung ke X dihapus
dari G. */
void DeleteNode (Graph * G, int X);

#endif
