/* File : graph.h */
/* Definisi ADT Graph */
/* Menggunakan representasi multilist */

#include "../header/graph.h"
#include <stdlib.h>
#include <stdio.h>

void CreateGraph(int X, Graph * G) {
  GraphFirst(*G) = AlokNode(X);
}

adrNode AlokNode (int X) {
  /* KAMUS */
  adrNode P;

  /* ALGORITMA */
  P = (adrNode) malloc (sizeof(Node));
  if (P != Nil) {
    Id(P) = X;
    NPred(P) = 0;
    Trail(P) = Nil;
    GraphNext(P) = Nil;
  }
  return P;
}

void DealokNode (adrNode P) {
  free(P);
}
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

adrSuccNode AlokSuccNode (adrNode Pn) {
  /* KAMUS */
  adrSuccNode P;

  /* ALGORITMA */
  P = (adrSuccNode) malloc(sizeof(SuccNode));
  if (P != Nil) {
    Succ(P) = Pn;
    GraphNext(P) = Nil;
  }
  return P;
}
/* Mengembalikan address hasil alokasi. */
/* Jika alokasi berhasil, maka address tidak Nil, misalnya
  menghasilkan Pt, maka Succ(Pt)=Pn dan GraphNext(Pt)=Nil. Jika
  alokasi gagal, mengembalikan Nil. */

void DealokSuccNode (adrSuccNode P) {
  free(P);
}
/* I.S. P terdefinisi; F.S. P dikembalikan ke sistem */
/* *** Manajemen Memory List Successor (Trailer) *** */

adrNode SearchNode (Graph G, int X) {
/* Mengembalikan address simpul dengan I */
  /* KAMUS */
  adrNode P = GraphFirst(G);

  /* ALGORITMA */
  while ((P != Nil) && (Id(P) != X)) {
    P = GraphNext(P);
  }
  return P;
}

adrSuccNode SearchEdge (Graph G, int prec, int succ) {
/* mengembalikan address trailer yang menyimpan info busur (prec,succ)
jika sudah ada pada graph G, Nil jika belum */
  /* KAMUS */
  adrNode P;
  adrSuccNode Pt;

  /* ALGORITMA */
  Pt = Nil;

  // Cari node dengan ID prec di graf
  P = SearchNode(G, prec);

  // Ada node dengan ID prec di graf
  if (P != Nil) {
    // Cari Edge dengan Succ adalah succ
    Pt = Trail(P);
    while(Pt != Nil && Id(Succ(Pt)) != succ) 
        Pt = GraphNext(Pt);

    // Edge ditemukan
    if (Pt != Nil){
        return Pt;
    }
  }
    return Nil;
}

void InsertNode (Graph * G, int X, adrNode * Pn) {
  adrNode P;
  adrNode CrrntElmt;

  CrrntElmt = GraphFirst(*G);
  while (GraphNext(CrrntElmt) != Nil) {
    CrrntElmt = GraphNext(CrrntElmt);
  }

  P = AlokNode(X);
  GraphNext(CrrntElmt) = P;

  *Pn = P;
}

void InsertEdge (Graph * G, int prec, int succ) {
  adrNode NP, NS;
  adrSuccNode Trail;
  // Tambah dulu prec dan succ kalau belum ada

  NP = SearchNode(*G, prec);
  if(NP == Nil) InsertNode(G, prec, &NP);

  NS = SearchNode(*G, succ);
  if(NS == Nil) InsertNode(G, succ, &NS);

  // Baru tambah edgenya, kalau belum ada
  if(SearchEdge(*G, prec, succ) == Nil){
    Trail = Trail(NP);
    if(Trail == Nil) Trail(NP) = AlokSuccNode(NS);
    else{
      while(GraphNext(Trail) != Nil) Trail = GraphNext(Trail);
      GraphNext(Trail) = AlokSuccNode(NS);
    }
    NPred(NS)++; // Tambah jumlah predecessor dari successor node
  }
}

void DeleteNode (Graph * G, int X) {
  adrNode P, Q, T;
  adrSuccNode R, S;
  
  P = SearchNode(*G, X);
  Q = GraphFirst(*G);
  while(Q != Nil){
    // Cari semua kemunculan edge Q, P
    R = SearchEdge(*G, Id(Q), X);
    //kalau ada, hapus
    if(R != Nil){
      S = Trail(Q);
      if(S == R) Trail(Q) = GraphNext(S);
      else{
        while(GraphNext(S) != R) S = GraphNext(S);
        GraphNext(S) = GraphNext(R);
      }
      DealokSuccNode(R);
    }
  }
  // baru hapus node P
  T = GraphFirst(*G);
  if(T == P) GraphFirst(*G) = GraphNext(T);
  else{
    while(GraphNext(T) != P) T = GraphNext(P);
    GraphNext(T) = GraphNext(P);
  }
  GraphNext(P) = Nil;
  Trail(P) = Nil;
  DealokNode(P);
}
/* Menghapus simpul X dari G */
/* I.S. G terdefinisi, X terdefinisi dan ada pada G, jumlah simpul
pada G lebih dari 1. */
/* F.S. simpul X dan semua busur yang terhubung ke X dihapus
dari G. */
