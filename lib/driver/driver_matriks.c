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
    int i;
    int j;
    char ctemp;

    // Algoritma
    printf("BACA MATRIKS");nl;
    printf("masukkan nb: "); scanf("%d", &nb);
    printf("masukkan nk: "); scanf("%d", &nk);
    printf("press enter...");
    scanf("%c", &ctemp);
    printf("pressed...");
    printf("M1");
    BacaMATRIKS(&M1,nb,nk);
    printf("press enter...");
    scanf("%c", &ctemp);
    printf("pressed...");
    printf("M2");
    BacaMATRIKS(&M2,nb,nk);

    nl;printf("PERINDEKSAN MATRIKS");nl;
    printf("First Index Baris : %d", GetFirstIdxBrs(M1));nl;
    printf("First Index Kolom : %d", GetFirstIdxKol(M1));nl;
    printf("Last Index Baris : %d", GetLastIdxBrs(M1));nl;
    printf("Last Index Kolom : %d\n", GetLastIdxKol(M1));
    printf("masukkan i: "); scanf("%d",&i);
    printf("masukkan j: "); scanf("%d",&j);
    if (IsIdxEff(M1,i,j)) printf("indeks efektif\n");
    else printf("indeks tidak efektif\n");

    nl;printf("EQUIVALENCE");nl;
    if (MatriksEQ(M1,M2)) printf("Matriks M1 dan M2 sama\n");
    else printf("Matriks M1 dan M2 tidak sama\n");
    if (MatriksEQSize(M1,M2)) printf("Matriks M1 dan M2 sama ukuran efektifnya\n");
    else printf("Matriks M1 dan M2 tidak sama ukuran efektifnya\n");
    
    nl;printf("SYMMETRY");nl;
    if (IsBujurSangkar(M1)) printf("Matriks M1 adalah matriks bujur sangkar\n");
    else printf("Matriks M1 bukan matriks bujur sangkat\n");
    if (IsSimetri(M1)) printf("Matriks M1 simetris\n");
    else printf("Matriks M1 tidak simetris\n");

    nl;printf("PRINTING MATRIKS");nl;
    printf("M1\n");
    TulisMATRIKS(M1);nl;
    printf("M2\n");
    TulisMATRIKS(M2);nl;

    nl;printf("COPYING");nl;
    printf("Matriks M1 -> M3");nl;
    CopyMATRIKS(M1,&M3);
    printf("M3\n");
    TulisMATRIKS(M3);nl;

    nl;printf("TRANSPOSING");nl;
    printf("Matriks M3");nl;
    Transpose(&M3);
    printf("M3\n");
    TulisMATRIKS(M3);nl;

    printf("END OF PROGRAM\n");
    return 0;
}
