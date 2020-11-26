/* file : graph.h */
/* deklarasi graph dengan representasi multi list */

#include "../header/graph.h"
#include <stdlib.h>


/* SELEKTOR */
// #define Info(P) (P)->info
// #define Next(P) (P)->next
// #define FirstG(G) (G).FirstG

void CreateEmptyGraph (Graph * G) {
   FirstG(*G) = Nil;
}

/****************** TEST GRAPH KOSONG ******************/
boolean IsEmptyGraph(Graph G) {
  return (FirstG(G) == Nil);
}

/****************** Manajemen Memori ******************/
addressG AlokasiGraph (infotypeG X) {
    /* KAMUS */
    addressG P;

    /* ALGORITMA */
    P = (addressG) malloc (sizeof(ElmtGraph));
    if (P != Nil) {
        Info(P) = X;
        Next(P) = Nil;
    }
}

void DealokasiGraph (addressG *P) {
    free(P);
}

/*** PENAMBAHAN ELEMEN ***/
void InsVFirstGraph (Graph *G, infotypeG X) {
    addressG P;

    P = AlokasiGraph(X);
    if (P != Nil) {
        if (IsEmptyGraph(*G)) {
            FirstG(*G) = P;
        } else {
            Next(P) = FirstG(*G);
            FirstG(*G) = P;
        }
    }
}

void InsVLastGraph(Graph *G, infotypeG X) {
    addressG P;
    addressG last;

    P = AlokasiGraph(X);
    if (P != Nil) {
        if (IsEmptyGraph(*G)) {
            FirstG(*G) = P;
        } else {
            last = FirstG(*G);
            while (Next(last) != Nil) {
                last = Next(last);
            }
            Next(last) = P;
        }
    }
}


/*** PENCARIAN ELEMEN ***/
boolean IsNodeConnected(Graph G, infotype X1, infotype X2) {
    
}
