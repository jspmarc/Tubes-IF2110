/* File : listlinier.c */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi addressLL dengan pointer */
/* infotype adalah integer */
#include "../header/listlinier.h"
#include "boolean.h"
#include <stdlib.h>
#include <stdio.h>

boolean IsEmpty (LL L) {
    return LLFirst(L) == Nil;
}

void CreateEmpty (LL *L) {
    LLFirst(*L) = Nil;
}

addressLL AlokasiLL (infotype X) {
    addressLL P;

    P = (addressLL) malloc(sizeof(ElmtLL));
    if  (P != Nil) {
        Info(P) = X;
        LLNext(P) = Nil;
    }

    return P;
}

void Dealokasi (addressLL *P) {
    free(*P);
}

addressLL Search (LL L, infotype X) {
    addressLL P;

    P =  LLFirst(L);
    if (!IsEmpty(L)) {
        while (Info(P) != X && LLNext(P) != Nil) P = LLNext(P);

        return Info(P) == X ? P : Nil;
    } else return Nil;
}

boolean FSearch (LL L, addressLL P) {
    addressLL curP;

    curP = LLFirst(L);
    while (curP != P && curP != Nil) curP = LLNext(curP);

    return curP == Nil;
}

addressLL SearchPrec (LL L, infotype X) {
    addressLL P;

    P = LLFirst(L);
    if (IsEmpty(L) || Info(P) == X) return Nil;

    for(; Info(LLNext(P)) != X && LLNext(LLNext(P)) != Nil; P = LLNext(P));

    if (Info(LLNext(P)) == X) return P;

    /* Artinya Info(LLNext(P)) bukan X, meskipun P satu node sebelum node
     * terakhir, akan tetap masuk ke if apabila X ada di Info node terakhir */
    return Nil;
}

void InsVFirst (LL *L, infotype X) {
    addressLL P;

    P = AlokasiLL(X);
    if (P != Nil) InsertLLFirst(L, P);
}

void InsVLast (LL *L, infotype X) {
    addressLL P;

    P = AlokasiLL(X);
    if (P != Nil) InsertLast(L, P);
}

void DelVFirst (LL *L, infotype *X) {
    addressLL P;

    DelLLFirst(L, &P);
    *X = Info(P);
    Dealokasi(&P);
}

void DelVLast (LL *L, infotype *X) {
    addressLL P;

    DelLast(L, &P);
    *X = Info(P);
    Dealokasi(&P);
}

void InsertFirst (LL *L, addressLL P) {
    LLNext(P) = LLFirst(*L);
    LLFirst(*L) = P;
}

void InsertAfter (LL *L, addressLL P, addressLL Prec) {
    LLNext(P) = LLNext(Prec);
    LLNext(Prec) = P;
}

void InsertLast (LL *L, addressLL P) {
    addressLL curNode;

    if (IsEmpty(*L)) InsertLLFirst(L, P);
    else {
        curNode = LLFirst(*L);
        while (LLNext(curNode) != Nil) curNode = LLNext(curNode);

        LLNext(curNode) = P;
    }
}

void DelFirst (LL *L, addressLL *P) {
    *P = LLFirst(*L);
    LLFirst(*L) = LLNext(*P);
}

void DelP (LL *L, infotype X)
{
    addressLL P, bP;

    if (!IsEmpty(*L)) {
        P = LLFirst(*L);
        bP = Nil;
        while (Info(P) != X && LLNext(P) != Nil) {
            bP = P;
            P = LLNext(P);
        }

        if (bP == Nil && Info(P) == X) /* X adalah elemen pertama */ {
            DelLLFirst(L, &bP);
            Dealokasi(&P);
        } else if (Info(P) == X) {
            LLNext(bP) = LLNext(P);
            Dealokasi(&P);
        }
    }
}

void DelLast (LL *L, addressLL *P) {
    addressLL V, beforeV;

    V = LLFirst(*L);
    beforeV = Nil;
    while (LLNext(V) != Nil) {
        beforeV = V;
        V = LLNext(V);
    }

    *P = V;
    if (beforeV != Nil) /* Bukan elemen pertama */ LLNext(beforeV) = Nil;
    else LLFirst(*L) = Nil;
}

void DelAfter (LL *L, addressLL *Pdel, addressLL Prec) {
    /* Pdel adalah node setelah Prec, node yang mau dihapus */
    *Pdel = LLNext(Prec);

    LLNext(Prec) = LLNext(*Pdel);
}

void PrintInfo (LL L) {
    printf("[");
    for (addressLL P = LLFirst(L); P != Nil; P = LLNext(P)) {
        if (LLNext(P) != Nil) printf("%d,", Info(P));
        else printf("%d", Info(P));
    }
    printf("]");
}

int NbElmt (LL L) {
    int count = 0;

    for (addressLL P = LLFirst(L); P != Nil; P = LLNext(P), ++count);

    return count;
}

infotype Max (LL L) {
    addressLL P;
    infotype max;

    P = LLFirst(L);
    max = Info(P);
    P = LLNext(P);
    for (; P != Nil; P = LLNext(P)) max = Info(P) > max ? Info(P) : max;

    return max;
}

addressLL AdrMax (LL L) {
    addressLL P, maxP;

    P = LLFirst(L);
    maxP = P;
    P = LLNext(P);
    for (; P != Nil; P = LLNext(P)) maxP = Info(maxP) > Info(P) ? maxP : P;

    return maxP;
}

infotype Min (LL L) {
    addressLL P;
    infotype min;

    P = LLFirst(L);
    min = Info(P);
    P = LLNext(P);
    for (; P != Nil; P = LLNext(P))
        min = Info(P) < min ? Info(P) : min;

    return min;
}

addressLL AdrMin (LL L) {
    addressLL P, minP;

    P = LLFirst(L);
    minP = P;
    P = LLNext(P);
    for (; P != Nil; P = LLNext(P)) minP = Info(minP) < Info(P) ? minP : P;

    return minP;
}

float Average (LL L) {
    addressLL P = LLFirst(L);
    float sum = 0;
    int count = 0;

    for(; P != Nil; sum += Info(P), ++count, P = LLNext(P));

    return sum/count;
}

void DelAll (LL *L) {
    infotype _;

    for (addressLL P = LLFirst(*L); LLNext(P) != Nil;) {
        addressLL tempP;
        DelLast(L, &tempP);
        Dealokasi(&tempP);
    }

    /* P ada di node terakhir */
    DelVLLFirst(L, &_);
}

void InversLL (LL *L) {
    addressLL P, tempP;
    int Q;

    if (!IsEmpty(*L)) {
        DelLast(L, &tempP);
        InsertLLFirst(L, tempP);
        P = tempP;

        Q = NbElmt(*L)-1;
        while(Q--) {
            DelLast(L, &tempP);
            InsertAfter(L, tempP, P);
            P = tempP;
        }
    }
}

LL FInversLL (LL L) {
    LL newL;

    CreateEmpty(&newL);
    CpAlokLL(L, &newL);
    InversLL(&newL);

    return newL;
}

void CopyLL (LL *L1, LL *L2) {
    LLFirst(*L2) = LLFirst(*L1);
}

LL FCopyLL (LL L) {
    addressLL P, P2, newP2;
    LL L2;

    /* Menyalin elemen pertama */
    P = LLFirst(L);
    CreateEmpty(&L2);
    P2 = AlokasiLL(Info(P));
    if (P2 == Nil) /* AlokasiLL gagal */ return L2;
    LLFirst(L2) = P2;

    P = LLNext(P);

    /* P menunjuk ke node kedua */

    for (; P != Nil; P = LLNext(P), P2 = LLNext(P2)) {
        newP2 = AlokasiLL(Info(P));
        if (newP2 == Nil) /* AlokasiLL gagal */ {
            DelAll(&L2);
            return L2;
        }
        LLNext(P2) = newP2;
    }

    return L2;
}

void CpAlokLL (LL Lin, LL *Lout) {
    addressLL P, P2, newP2;

    /* Menyalin elemen pertama */
    P = LLFirst(Lin);
    P2 = AlokasiLL(Info(P));
    if (P2 == Nil) /* AlokasiLL gagal */ return;
    LLFirst(*Lout) = P2;

    P = LLNext(P);

    /* P menunjuk ke node kedua */

    for (; P != Nil; P = LLNext(P), P2 = LLNext(P2)) {
        newP2 = AlokasiLL(Info(P));
        if (newP2 == Nil) /* AlokasiLL gagal */ {
            DelAll(Lout);
            return;
        }
        LLNext(P2) = newP2;
    }
}

void Konkat (LL L1, LL L2, LL * L3) {
    LL L4, L5;

    CreateEmpty(&L4);
    CreateEmpty(&L5);

    if (!IsEmpty(L1)) /* L1 tidak kosong  */ {
        CpAlokLL(L1, &L4);
        if (IsEmpty(L2)) /* L1 tidak kosong, L2 kosong */ {
            CpAlokLL(L4, L3);
            return;
        }
        /* L1 dan L2 tidak kosong */
        CpAlokLL(L2, &L5);
        Konkat1(&L4, &L5, L3);
    }

    if (IsEmpty(L1) && !IsEmpty(L2)) /* L1 kosong, L2 tidak kosong */ {
        CpAlokLL(L2, L3);
        PrintInfo(*L3);
        return;
    }
}

void Konkat1 (LL *L1, LL *L2, LL *L3) {
    addressLL lastL1;

    if  (!IsEmpty(*L1) || !IsEmpty(*L2)) {
        LLFirst(*L3) = LLFirst(*L1);

        if (!IsEmpty(*L1)) {
            lastL1 = LLFirst(*L1);
            for(; LLNext(lastL1) != Nil; lastL1 = LLNext(lastL1));
            LLNext(lastL1) = LLFirst(*L2);
        } else LLFirst(*L3) = LLFirst(*L2);

        LLFirst(*L1) = Nil;
        LLFirst(*L2) = Nil;
    }
}

void PecahLL (LL *L1, LL *L2, LL L){
    int i, count;
    addressLL P;

    count = NbElmt(L)/2;
    i = 0;
    CreateEmpty(L1);
    P = LLFirst(L);
    while(i < count){
        InsertLast(L1, AlokasiLL(Info(P)));
        P = LLNext(P);
        i++;
    }
    CreateEmpty(L2);
    while(P != Nil){
        InsertLast(L2, AlokasiLL(Info(P)));
        P = LLNext(P);
    }
}
