/* file : graph.h */
/* deklarasi graph dengan representasi multi list */

#ifndef _GRAPH_H
#define _GRAPH_H

#include "boolean.h"

#define MaxEdge 5
#define Nil NULL

typedef int Node;

// Graph : list of pointer to Edge [0..MaxNode-1]
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
} Graph;
/* Graph.edge[i] menunjuk pada edge ke-i */
/* Graph kosong setiap elemennya nil */


/* Selektor */
#define GraphEdge(G, i) (G).edge[i]
#define Nodes(G) 
#define IsChecked(E) E->m
#define Node1(E) E->node1
#define Node2(E) E->node2
#define Edge1(E) E->edge1
#define Edge2(E) E->edge2

void CreateEmptyGraph (Graph * G);
/* Mengembalikan graph kosong */
/* tabel [0..MaxNode-1] menunjuk ke NULL */

void Connect (Graph * G, Node N1, Node N2);
/* Menghubungkan node N1 dengan node N2 di graph G */

void Disconnect (Graph * G, Node N1, Node N2);
/* Memutuskan hubungan node N1 dengan node N2 di graph G */

address Alokasi (Node N1, Node N2);
/* Mengalokasi address dengan nilai N */

void Dealokasi (address * P);
/* Mengembalikan address ke sistem */

boolean IsConnected (Graph G, Node N1, Node N2);
/* Menghasilkan true juga node N1 terhubung dengan N2 di graph G */

#endif
