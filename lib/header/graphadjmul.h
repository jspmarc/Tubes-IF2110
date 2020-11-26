/* file : graph.h */
/* deklarasi graph dengan representasi multi list */

#ifndef _GRAPH_H
#define _GRAPH_H

#include "boolean.h"

#define MaxEdge 5
#define Nil NULL

typedef int Node;

// GraphAdjMul : list of pointer to Edge [0..MaxNode-1]
typedef struct tEdge *address;

/* Edge,
  m : untuk cek apakah sudah dicek
  node1 : simpul1 yang terhubung
  node2 : simpul2 yang terhubung dengan simpul1
  edge1 : alamat edge lain yang terhubung dengan node1
  edge2 : alamat edge lain yang terhubung dengan node2
*/
typedef struct tEdge {
    boolean m;
    Node node1;
    Node node2;
    address edge1;
    address edge2;
} Edge;

// Array [0..MaxNode-1] penyimpan address-address edge
typedef struct {
    address edge[MaxEdge];
} GraphAdjMul;
/* GraphAdjMul.edge[i] menunjuk pada edge ke-i */
/* GraphAdjMul kosong setiap elemennya nil */


/* Selektor */
#define GraphAdjMulEdge(G, i) (G).edge[i]
#define Nodes(G) 
#define IsChecked(E) E->m
#define Node1(E) E->node1
#define Node2(E) E->node2
#define Edge1(E) E->edge1
#define Edge2(E) E->edge2

void CreateEmptyGraphAdjMul (GraphAdjMul * G);
/* Mengembalikan graph kosong */
/* tabel [0..MaxNode-1] menunjuk ke NULL */

void Connect (GraphAdjMul * G, Node N1, Node N2);
/* Menghubungkan node N1 dengan node N2 di graph G */

void Disconnect (GraphAdjMul * G, Node N1, Node N2);
/* Memutuskan hubungan node N1 dengan node N2 di graph G */

address AlokasiGraphAdjMul (Node N1, Node N2);
/* Mengalokasi address dengan nilai N */

void DealokasiGraphAdjMul (address * P);
/* Mengembalikan address ke sistem */

boolean IsConnected (GraphAdjMul G, Node N1, Node N2);
/* Menghasilkan true juga node N1 terhubung dengan N2 di graph G */

#endif
