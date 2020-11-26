/* File : stacklist.c */
#include "boolean.h"
#include "../header/stacklist.h"
#include <stdlib.h>

void AlokasiStack (StackAddress *P, StackInfoType X) {
    *P = (StackAddress) malloc(sizeof(ElmtStack));
    if (P != Nil) {
        StackInfo(*P) = X;
        StackNext(*P) = Nil;
    }
}
void DealokasiStack (StackAddress P) {
    free(P);
}

/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
boolean IsStackEmpty (Stack S) {
    return Top(S) == Nil;
}
void CreateEmptyStack (Stack * S) {
    Top(*S) = Nil;
}
void Push (Stack * S, StackInfoType X, PropertiAksi prop) {
    StackAddress P;

    AlokasiStack(&P, X);

    if (P != Nil) {
        StackNext(P) = Top(*S);
        Aksi(P) = prop;
        Top(*S) = P;
    }
}
void Pop (Stack * S, StackInfoType * X, PropertiAksi *prop) {
    StackAddress P;

    P = Top(*S);
    *X = StackInfo(P);
    *prop = Aksi(P);
    Top(*S) = StackNext(P);

    DealokasiStack(P);
}
