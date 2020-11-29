#include "boolean.h"
#include "../header/stacklist.h"
#include <stdlib.h>
#include <stdio.h>

#define nl printf("\n")

int main() {
    // Kamus
    Stack S;
    void * el; //StackInfoType
    PropertiAksi propAct;
    JAM J;

    // Algoritma
    CreateEmptyStack(&S);
    if(IsStackEmpty(S)) printf("kosong_1\n");
    propAct.idAksi = 2;
    J = MakeJAM(2,0,0);
    propAct.durasiAksi = J;
    Push(&S, el, propAct);
    if(IsStackEmpty(S)) printf("kosong_2\n");
    Pop(&S, &el, &propAct);
    if(IsStackEmpty(S)) printf("kosong_3\n");
    printf("END OF PROGRAM\n");
    return 0;
}
