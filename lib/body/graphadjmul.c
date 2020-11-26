/* file : graph.h */
/* deklarasi graph dengan representasi multi list */

#include "../header/graphadjmul.h"
#include "boolean.h"
#include <stdlib.h>

#define MaxNode 5
#define Nil NULL

// typedef int Node;

// GraphAdjMul : list of pointer to Edge [0..MaxNode-1]
// typedef struct {
//     address edge[MaxNode];
// } GraphAdjMul;

// typedef struct tNode *address;
// typedef struct tNode {
//     boolean m;
//     Node node1;
//     Node node2;
//     address edge1;
//     address edge2;
// } Edge;


/* Selektor */
// #define GraphAdjMulEdge(G, i) (G).edge[i]
// #define Nodes(G)
// #define IsChecked(E) (E).m
// #define Node1(E) (E).node1
// #define Node2(E) (E).node2
// #define Edge1(E) (E).edge1
// #define Edge2(E) (E).edge2

void CreateEmptyGraphAdjMul (GraphAdjMul * G) {
/* Mengembalikan graph kosong */
/* tabel [0..MaxNode-1] menunjuk ke NULL */
  for (int i = 0; i < MaxNode; i++) {
    GraphAdjMulEdge(*G, i) = Nil;
  }
}

void Connect (GraphAdjMul * G, Node N1, Node N2) {
/* Menghubungkan node N1 dengan node N2 di graph G secara langsung */
  /* KAMUS */
  address E;
  int i;

  /* ALGORITMA */
  E = AlokasiGraphAdjMul(N1, N2);
  for (i = 0; i < MaxEdge && GraphAdjMulEdge(*G, i) != Nil; i++);
  GraphAdjMulEdge(*G, i) = E;
}

void Disconnect (GraphAdjMul * G, Node N1, Node N2) {
/* Memutuskan hubungan langsung antara node N1 dengan node N2 di graph G */
/* address kemudian di-dealokasi */
  /* KAMUS */
  int i;
  address P;

  /* ALGORITMA */
  i = 0;
  while ((i < MaxEdge) && (Node1(GraphAdjMulEdge(*G, i)) != N1) && (Node2(GraphAdjMulEdge(*G, i)) != N2)) {
    i++;
  }
  
  if ((Node1(GraphAdjMulEdge(*G, i)) == N1) && (Node2(GraphAdjMulEdge(*G, i)) == N2)) {
    P = GraphAdjMulEdge(*G, i);

    /* Jika ada next elemen, geser maju elemen list berikutnya */
    if ((GraphAdjMulEdge(*G, i+1) != Nil) && (i != MaxEdge-1)) { 
      GraphAdjMulEdge(*G, i) = GraphAdjMulEdge(*G, i+1);
    }

    DealokasiGraphAdjMul(&P);
  }
}

address AlokasiGraphAdjMul (Node N1, Node N2) {
/* Mengalokasi address dengan nilai node1 N1 dan node2 N2 */
/* Jika alokasi gagal mengembalikan Nil */
  /* KAMUS */
  address P;

  /* ALGORITMA */
  P = (address) malloc(sizeof(Edge));
  if (P != Nil) {
    IsChecked(P) = false;
    Node1(P) = N1;
    Node2(P) = N2;
    Edge1(P) = Nil;
    Edge1(P) = Nil;
  }
  return P;
}

void DealokasiGraphAdjMul (address * P) {
/* Mengembalikan address ke sistem */
  free(P);
}

boolean IsConnected (GraphAdjMul G, Node N1, Node N2) {
/* Menghasilkan true juga node N1 terhubung dengan N2 di graph G 
  Terhubung di sini tidak secara langsung */
  // cek m dahulu
  /* KAMUS */
  int i, j;
  address E;
  boolean connected;

  /* ALGORITMA */
  connected = false;
  for (i = 0; i < MaxNode; i++) {
    /* Set E ke edge ke-i */
    E = GraphAdjMulEdge(G, i);
    /* Memeriksa edge yang belum diperiksa */
    if (!IsChecked(E)) {
      // Jika node1 adalah N1, periksa :
      if (Node1(E) == N1) {
        /* Jika node2 adalah N2, maka terhubung */
        if (Node1(E) == N2) {
          connected = true;
        } else {
        /* Jika node2 bukan N2, maka lanjut pemeriksaan ke
           edge untuk mencari node yang terhubung tidak langsung */
          IsChecked(E) = true;
          E = Edge1(E);
        }
      } else if (Node2(E) == N1) {
        if (Node2(E) == N2) {
          connected = true;
        } else {
          IsChecked(E) = true;
          E = Edge2(E);
        }
      }
    }

    // Set kembali semua ke unchecked
    for (j = 0; j < MaxNode; j++) {
      IsChecked(GraphAdjMulEdge(G, i)) = false;
    }
  }
  return connected;
}
