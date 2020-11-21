/* File : listlinier.c */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */
/* infotype adalah integer */
#include "../header/listlinier.h"
#include "boolean.h"
#include <stdlib.h>
#include <stdio.h>

boolean IsEmpty (List L) {
    return First(L) == Nil;
}

void CreateEmpty (List *L) {
    First(*L) = Nil;
}

address Alokasi (infotype X) {
    address P;

    P = (address) malloc(sizeof(ElmtList));
    if  (P != Nil) {
        Info(P) = X;
        Next(P) = Nil;
    }

    return P;
}

void Dealokasi (address *P) {
    free(*P);
}

address Search (List L, infotype X) {
    address P;

    P =  First(L);
    if (!IsEmpty(L)) {
        while (Info(P) != X && Next(P) != Nil) P = Next(P);

        return Info(P) == X ? P : Nil;
    } else return Nil;
}

boolean FSearch (List L, address P) {
    address curP;

    curP = First(L);
    while (curP != P && curP != Nil) curP = Next(curP);

    return curP == Nil;
}

address SearchPrec (List L, infotype X) {
    address P;

    P = First(L);
    if (IsEmpty(L) || Info(P) == X) return Nil;

    for(; Info(Next(P)) != X && Next(Next(P)) != Nil; P = Next(P));

    if (Info(Next(P)) == X) return P;

    /* Artinya Info(Next(P)) bukan X, meskipun P satu node sebelum node
     * terakhir, akan tetap masuk ke if apabila X ada di Info node terakhir */
    return Nil;
}

void InsVFirst (List *L, infotype X) {
    address P;

    P = Alokasi(X);
    if (P != Nil) InsertFirst(L, P);
}

void InsVLast (List *L, infotype X) {
    address P;

    P = Alokasi(X);
    if (P != Nil) InsertLast(L, P);
}

void DelVFirst (List *L, infotype *X) {
    address P;

    DelFirst(L, &P);
    *X = Info(P);
    Dealokasi(&P);
}

void DelVLast (List *L, infotype *X) {
    address P;

    DelLast(L, &P);
    *X = Info(P);
    Dealokasi(&P);
}

void InsertFirst (List *L, address P) {
    Next(P) = First(*L);
    First(*L) = P;
}

void InsertAfter (List *L, address P, address Prec) {
    Next(P) = Next(Prec);
    Next(Prec) = P;
}

void InsertLast (List *L, address P) {
    address curNode;

    if (IsEmpty(*L)) InsertFirst(L, P);
    else {
        curNode = First(*L);
        while (Next(curNode) != Nil) curNode = Next(curNode);

        Next(curNode) = P;
    }
}

void DelFirst (List *L, address *P) {
    *P = First(*L);
    First(*L) = Next(*P);
}

void DelP (List *L, infotype X)
{
    address P, bP;

    if (!IsEmpty(*L)) {
        P = First(*L);
        bP = Nil;
        while (Info(P) != X && Next(P) != Nil) {
            bP = P;
            P = Next(P);
        }

        if (bP == Nil && Info(P) == X) /* X adalah elemen pertama */ {
            DelFirst(L, &bP);
            Dealokasi(&P);
        } else if (Info(P) == X) {
            Next(bP) = Next(P);
            Dealokasi(&P);
        }
    }
}

void DelLast (List *L, address *P) {
    address V, beforeV;

    V = First(*L);
    beforeV = Nil;
    while (Next(V) != Nil) {
        beforeV = V;
        V = Next(V);
    }

    *P = V;
    if (beforeV != Nil) /* Bukan elemen pertama */ Next(beforeV) = Nil;
    else First(*L) = Nil;
}

void DelAfter (List *L, address *Pdel, address Prec) {
    /* Pdel adalah node setelah Prec, node yang mau dihapus */
    *Pdel = Next(Prec);

    Next(Prec) = Next(*Pdel);
}

void PrintInfo (List L) {
    printf("[");
    for (address P = First(L); P != Nil; P = Next(P)) {
        if (Next(P) != Nil) printf("%d,", Info(P));
        else printf("%d", Info(P));
    }
    printf("]");
}

int NbElmt (List L) {
    int count = 0;

    for (address P = First(L); P != Nil; P = Next(P), ++count);

    return count;
}

infotype Max (List L) {
    address P;
    infotype max;

    P = First(L);
    max = Info(P);
    P = Next(P);
    for (; P != Nil; P = Next(P)) max = Info(P) > max ? Info(P) : max;

    return max;
}

address AdrMax (List L) {
    address P, maxP;

    P = First(L);
    maxP = P;
    P = Next(P);
    for (; P != Nil; P = Next(P)) maxP = Info(maxP) > Info(P) ? maxP : P;

    return maxP;
}

infotype Min (List L) {
    address P;
    infotype min;

    P = First(L);
    min = Info(P);
    P = Next(P);
    for (; P != Nil; P = Next(P))
        min = Info(P) < min ? Info(P) : min;

    return min;
}

address AdrMin (List L) {
    address P, minP;

    P = First(L);
    minP = P;
    P = Next(P);
    for (; P != Nil; P = Next(P)) minP = Info(minP) < Info(P) ? minP : P;

    return minP;
}

float Average (List L) {
    address P = First(L);
    float sum = 0;
    int count = 0;

    for(; P != Nil; sum += Info(P), ++count, P = Next(P));

    return sum/count;
}

void DelAll (List *L) {
    infotype _;

    for (address P = First(*L); Next(P) != Nil;) {
        address tempP;
        DelLast(L, &tempP);
        Dealokasi(&tempP);
    }

    /* P ada di node terakhir */
    DelVFirst(L, &_);
}

void InversList (List *L) {
    address P, tempP;
    int Q;

    if (!IsEmpty(*L)) {
        DelLast(L, &tempP);
        InsertFirst(L, tempP);
        P = tempP;

        Q = NbElmt(*L)-1;
        while(Q--) {
            DelLast(L, &tempP);
            InsertAfter(L, tempP, P);
            P = tempP;
        }
    }
}

List FInversList (List L) {
    List newL;

    CreateEmpty(&newL);
    CpAlokList(L, &newL);
    InversList(&newL);

    return newL;
}

void CopyList (List *L1, List *L2) {
    First(*L2) = First(*L1);
}

List FCopyList (List L) {
    address P, P2, newP2;
    List L2;

    /* Menyalin elemen pertama */
    P = First(L);
    CreateEmpty(&L2);
    P2 = Alokasi(Info(P));
    if (P2 == Nil) /* Alokasi gagal */ return L2;
    First(L2) = P2;

    P = Next(P);

    /* P menunjuk ke node kedua */

    for (; P != Nil; P = Next(P), P2 = Next(P2)) {
        newP2 = Alokasi(Info(P));
        if (newP2 == Nil) /* Alokasi gagal */ {
            DelAll(&L2);
            return L2;
        }
        Next(P2) = newP2;
    }

    return L2;
}

void CpAlokList (List Lin, List *Lout) {
    address P, P2, newP2;

    /* Menyalin elemen pertama */
    P = First(Lin);
    P2 = Alokasi(Info(P));
    if (P2 == Nil) /* Alokasi gagal */ return;
    First(*Lout) = P2;

    P = Next(P);

    /* P menunjuk ke node kedua */

    for (; P != Nil; P = Next(P), P2 = Next(P2)) {
        newP2 = Alokasi(Info(P));
        if (newP2 == Nil) /* Alokasi gagal */ {
            DelAll(Lout);
            return;
        }
        Next(P2) = newP2;
    }
}

void Konkat (List L1, List L2, List * L3) {
    List L4, L5;

    CreateEmpty(&L4);
    CreateEmpty(&L5);

    if (!IsEmpty(L1)) /* L1 tidak kosong  */ {
        CpAlokList(L1, &L4);
        if (IsEmpty(L2)) /* L1 tidak kosong, L2 kosong */ {
            CpAlokList(L4, L3);
            return;
        }
        /* L1 dan L2 tidak kosong */
        CpAlokList(L2, &L5);
        Konkat1(&L4, &L5, L3);
    }

    if (IsEmpty(L1) && !IsEmpty(L2)) /* L1 kosong, L2 tidak kosong */ {
        CpAlokList(L2, L3);
        PrintInfo(*L3);
        return;
    }
}

void Konkat1 (List *L1, List *L2, List *L3) {
    address lastL1;

    if  (!IsEmpty(*L1) || !IsEmpty(*L2)) {
        First(*L3) = First(*L1);

        if (!IsEmpty(*L1)) {
            lastL1 = First(*L1);
            for(; Next(lastL1) != Nil; lastL1 = Next(lastL1));
            Next(lastL1) = First(*L2);
        } else First(*L3) = First(*L2);

        First(*L1) = Nil;
        First(*L2) = Nil;
    }
}

void PecahList (List *L1, List *L2, List L){
    int i, count;
    address P;

    count = NbElmt(L)/2;
    i = 0;
    CreateEmpty(L1);
    P = First(L);
    while(i < count){
        InsertLast(L1, Alokasi(Info(P)));
        P = Next(P);
        i++;
    }
    CreateEmpty(L2);
    while(P != Nil){
        InsertLast(L2, Alokasi(Info(P)));
        P = Next(P);
    }
}
