/* File : graph.h */
/* Definisi ADT Graph */
/* Menggunakan representasi multilist */

#include "../header/graph.h"
#include <stdlib.h>

// #define Nil NULL

// typedef struct tNode * adrNode;
// typedef struct tSuccNode * adrSuccNode;
// typedef struct tNode {
//     int Id;
//     int NPred;
//     adrSuccNode Trail;
//     adrNode Next;
// } Node;
// typedef struct tSuccNode {
//     adrNode Succ;
//     adrSuccNode Next;
// } SuccNode;

// typedef struct {
//     adrNode First;
// } Graph;

/* SELEKTOR */
// #define First(G) (G).First
// #define Id(Pn) (Pn)->Id
// #define NPred(Pn) (Pn)->NPred
// #define Trail(Pn) (Pn)->Trail
// #define Next(Pn) (Pn)->Next
// #define Succ(Pt) (Pt)->Succ
// #define Next(Pt) (Pt)->Next

/****************** PEMBUATAN GRAPH KOSONG ******************/
void CreateGraph(int X, Graph * G) {
    First(*G) = Nil;
}
/* I.S. G sembarang */
/* F.S. Terbentuk graph kosong */

/****************** Manajemen Memori ******************/
adrNode AlokNode (int X) {
    /* KAMUS */
    adrNode P;

    /* ALGORITMA */
    P = (adrNode) malloc (sizeof(Node));
    if (P != Nil) {
        Id(P) = X;
        NPred(P) = 0;
        Trail(P) = Nil;
        Next(P) = Nil;
    }
    return P;
}
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */


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
        Next(P) = Nil;
    }
    return P;
}
/* Mengembalikan address hasil alokasi. */
/* Jika alokasi berhasil, maka address tidak Nil, misalnya
    menghasilkan Pt, maka Succ(Pt)=Pn dan Next(Pt)=Nil. Jika
    alokasi gagal, mengembalikan Nil. */

void DealokSuccNode (adrSuccNode P) {
    free(P);
}
/* I.S. P terdefinisi; F.S. P dikembalikan ke sistem */
/* *** Manajemen Memory List Successor (Trailer) *** */

adrNode SearchNode (Graph G, int X) {
/* Mengembalikan address simpul dengan I */
    /* KAMUS */
    adrNode P = First(G);

    /* ALGORITMA */
    while ((P != Nil) && (Id(P) != X)) {
        P = Next(P);
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
    P = SearchNode(G, prec);
    if (P != Nil) {
        Pt = Trail(P);
        while ((Pt != Nil) && (Id(Succ(Pt)) != succ)) {
            Pt = Next(Pt);
        }
        return Pt;
    } else {
        return Nil;
    }
}

void InsertNode (Graph * G, int X, adrNode * Pn) {
    adrNode P;
    adrNode CrrntElmt;

    CrrntElmt = First(*G);
    while (Next(CrrntElmt) != Nil) {
        CrrntElmt = Next(CrrntElmt);
    }

    P = AlokNode(X);
    if (P != Nil) {
        Next(CrrntElmt) = P;
    }

    *Pn = P;
}
/* Menambahkan simpul X ke dalam graph, jika alokasi X berhasil. */
/* I.S. G terdefinisi, X terdefinisi dan belum ada pada G. */
/* F.S. Jika alokasi berhasil, X menjadi elemen terakhir G, Pn berisi
    address simpul X. Jika alokasi gagal, G tetap, Pn berisi Nil */

void InsertEdge (Graph * G, int prec, int succ) {
    adrSuccNode P1, P2, P3, P4;
    adrSuccNode NodeSuccBaru;
    adrNode NodeBaru, NodeBaruPrec, NodeBaruSucc;

    /* Kondisi : Edge prec,succ sudah ada */
    // Nothing
    /* Kondisi : Edge prec,succ belum ada */
    if (SearchEdge(*G, prec, succ) == Nil) {
        P1 = SearchNode(*G, prec);
        P2 = SearchNode(*G, prec);
        /* Kondisi : Node prec dan succ ada */
        if ((P1 != Nil) && (P2 != Nil)) {
            if (Trail(P1) != Nil) {
                P1 = Trail(P1);
                while (Next(P1) != Nil) {
                    P1 = Next(P1);
                }
                NodeBaru = AlokSuccNode(P2);
                if (NodeSuccBaru != Nil) {
                    Next(P1) = NodeSuccBaru;
                }
            }
        }
        /* Kondisi : Node prec ada, succ belum */
        else if ((P1 != Nil) && (P2 == Nil)) {
            P3 = First(*G);
            while (Next(P3) != Nil) {
                P3 = Next(P3);
            }
            NodeBaru = AlokNode(succ);
            if (NodeBaru != Nil) {
                Next(P3) = NodeBaru;
                P4 = Trail(P1);
                while (Next(P4) != Nil) {
                    P4 = Next(P4);
                }
                NodeSuccBaru = AlokNode(NodeBaru);
                if (NodeSuccBaru != Nil) {
                    Next(P4) = NodeSuccBaru;
                }
            }
        }
        /* Kondisi : Node prec belum ada, succ ada */
        else if ((P1 == Nil) && (P2 != Nil)) {
            P3 = First(*G);
            while (Next(P3) != Nil) {
                P3 = Next(P3);
            }
            NodeBaru = AlokNode(prec);
            if (NodeBaru != Nil) {
                Next(P3) = NodeBaru;
                NodeSuccBaru = AlokSuccNode(succ);
                if (NodeSuccBaru != Nil) {
                    Trail(P3) = NodeSuccBaru;
                }
            }
        }
        /* Kondisi : Node prec dan succ belum ada */
        else {
            P3 = First(*G);
            while (Next(P3) != Nil) {
                P3 = Next(P3);
            }
            NodeBaruPrec = AlokNode(prec);
            if (NodeBaruPrec != Nil) {
                Next(P3) = NodeBaruPrec;
                NodeBaruSucc = AlokNode(succ);
                if (NodeBaruSucc != Nil) {
                    Next(NodeBaruPrec) = NodeBaruSucc;
                    NodeSuccBaru = AlokSuccNode(NodeBaruSucc);
                    if (NodeSuccBaru != Nil) {
                        Trail(NodeBaruPrec) = NodeSuccBaru;
                    }
                }
            }
        }
    }
}
/* Menambahkan busur dari prec menuju succ ke dalam G */
/* I.S. G, prec, succ terdefinisi. */
/* F.S. Jika belum ada busur (prec,succ) di G, maka tambahkan busur
(prec,succ) ke G. Jika simpul prec/succ belum ada pada G,
tambahkan simpul tersebut dahulu. Jika sudah ada busur (prec,succ)
di G, maka G tetap. */

void DeleteNode (Graph * G, int X) {
    adrNode P;
    
    P = SearchNode(*G, X);
    Next(P) = Nil;
    Trail(P) = Nil;
    DealokNode(P);
}
/* Menghapus simpul X dari G */
/* I.S. G terdefinisi, X terdefinisi dan ada pada G, jumlah simpul
pada G lebih dari 1. */
/* F.S. simpul X dan semua busur yang terhubung ke X dihapus
dari G. */
