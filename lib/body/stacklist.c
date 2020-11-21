/* File : stacklist.c */
#include "boolean.h"
#include "../header//stacklist.h"
#include <stdlib.h>

void Alokasi (StackAddress *P, infotype X) {
    *P = (StackAddress) malloc(sizeof(ElmtStack));
    if (P != Nil) {
        Info(*P) = X;
        Next(*P) = Nil;
    }
}
void Dealokasi (StackAddress P) {
    free(P);
}

/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
boolean IsEmpty (Stack S) {
    return Top(S) == Nil;
}
void CreateEmpty (Stack * S) {
    Top(*S) = Nil;
}
void Push (Stack * S, infotype X) {
    StackAddress P;

    Alokasi(&P, X);

    if (P != Nil) {
        Next(P) = Top(*S);
        Top(*S) = P;
    }
}
void Pop (Stack * S, infotype * X) {
    StackAddress P;

    P = Top(*S);
    *X = Info(P);
    Top(*S) = Next(P);

    Dealokasi(P);
}
