#include <stdlib.h>
#include <stdio.h>
#include "../header/matriks.h"
#include "boolean.h"

#define nl printf("\n")

int main() {
    // Kamus
    MATRIKS M1;
    MATRIKS M2;
    MATRIKS M3;
    int nb;
    int nk;

    // Algoritma
    nb = 3;
    nk = 3;
    printf("MAKE MATRIKS");nl;
    MakeMATRIKS(nb,nk,&M3);

    printf("BACA MATRIKS");nl;
    printf("M1");nl;
    BacaMATRIKS(&M1,nb,nk);
    printf("M2");nl;
    BacaMATRIKS(&M2,nb,nk);
    printf("M3");nl;

    printf("PRINTING MATRIKS");nl;
    TulisMATRIKS(M1);nl;
    TulisMATRIKS(M2);nl;
    return 0;
}