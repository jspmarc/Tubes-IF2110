/* File: listrek.c */

#include <stdlib.h>
#include <stdio.h>
#include "../header/listrek.h"

address Alokasi(infotype X) {
    address P = (address) malloc(sizeof(ElmtList));
    if (P != Nil) {
        Info(P) = X;
        Next(P) = Nil;
    }

    return P;
}

void Dealokasi(address P) {
    free(P);
}

int IsEmpty(List  L) {
    return L == Nil;
}

int IsOneElmt(List L) {
    if (IsEmpty(L)) return 0;
    else return Next(L) == Nil;
}

infotype FirstElmt(List L) {
    return Info(L);
}

List Tail(List L) {
    return Next(L);
}


List Konso(infotype e, List L) {
    address P = Alokasi(e);
    List LRet = L;

    if (P != Nil) {
        if (!IsEmpty(L)) {
            Next(P) = L;
        }
        LRet = P;
    }

    return LRet;
}

List KonsB(List L, infotype e) {
    address P = Alokasi(e);
    List LRet = L;

    if (P != Nil) {
        if (IsEmpty(L)) {
            LRet = P;
        } else {
            if (IsOneElmt(L)) {
                Next(L) = P;
                LRet = L;
            } else {
                Dealokasi(P) /* P tidak digunakan */;
                LRet = KonsB(Tail(L), e) /* e di-KonsB dgn tail L*/;
                Next(L) = LRet; /* "Konso" L dgn tail L yg sudah ada e */
                LRet = L;
            }
        }
    }

    return LRet;
}

List Copy(List L) {
    List L2 = Nil, LTemp;

    if (!IsEmpty(L)) {
        L2 = Alokasi(FirstElmt(L));
        if (L2 == Nil) {
            L2 = L;
        } else {
            if (!IsOneElmt(L)) {
                LTemp = Copy(Tail(L));
                Next(L2) = LTemp;
            } else /* Udah dihandle di L2 = Alokasi... */;
        }
    }
    return L2;
}

void MCopy(List Lin, List *Lout) {
    *Lout = Copy(Lin);
    /**Lout = Lin;*/
}

List Concat(List L1, List L2) {
    List LRet = Nil;

    if (!IsEmpty(L2) || !IsEmpty(L1)) {
        if (IsEmpty(L1)) LRet = Copy(L2);
        else if (IsEmpty(L2)) LRet = Copy(L1);
        else {
            LRet = Copy(L1);
            LRet = KonsB(LRet, FirstElmt(L2));
            if (!IsOneElmt(L2)) LRet = Concat(LRet, Tail(L2));
        }
    }

    return LRet;
}

void MConcat(List L1, List L2, List *LHsl) {
    *LHsl = Concat(L1, L2);
    /**LHsl = L1;*/
}

void PrintList(List L) {
    if (!IsEmpty(L)) {
        printf("%d\n", FirstElmt(L));
        PrintList(Tail(L));
    }
}

int NbElmtList(List L) {
    int count;
    if (IsEmpty(L)) count = 0;
    else count = 1 + NbElmtList(Tail(L));

    return count;
}

boolean Search(List L, infotype X) {
    boolean found;

    if (IsEmpty(L)) found = false;
    else if (FirstElmt(L) == X) found = true;
    else found = Search(Tail(L), X);

    return found;
}

/*
int main() {
    List L1, L2, L3;
    L1 = Nil;
    L2 = Nil;
    L3 = Nil;


    for (int i = 0; i < 10; ++i) {
        L1 = KonsB(L1, i);
        L2 = Konso(i*i, L2);
    }

    printf("Banyak elemen L1: %d\n\n", NbElmtList(L1));

    PrintList(L1);
    puts("");
    PrintList(L2);

    puts("Menyambungkan L1 dengan L2 lalu ditaro di L3...");
    L3 = Concat(L1, L2);
    PrintList(L3);
    puts("");

    for (int i = 0; !IsEmpty(L3); ++i) {
        address P = L3;
        L3 = Tail(L3);
        Dealokasi(P);
    }

    puts("Menyalin L1 ke L3...");
    L3 = Copy(L1);
    PrintList(L3);
    puts("");

    printf("Keberadaan 5 di L1: %d\n", Search(L1, 5));
    printf("Keberadaan 50 di L1: %d\n", Search(L1, 50));

    for (int i = 0; !IsEmpty(L1); ++i) {
        address P = L1;
        L1 = Tail(L1);
        Dealokasi(P);
    }
    for (int i = 0; !IsEmpty(L2); ++i) {
        address P = L2;
        L2 = Tail(L2);
        Dealokasi(P);
    }
    for (int i = 0; !IsEmpty(L3); ++i) {
        address P = L3;
        L3 = Tail(L3);
        Dealokasi(P);
    }
}
*/
