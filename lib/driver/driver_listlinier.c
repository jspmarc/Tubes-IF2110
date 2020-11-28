#include <stdlib.h>
#include <stdio.h>
#include "../header/listlinier.h"
#include "boolean.h"

#define nl printf("\n")
#define test  printf("test\n")

int main() {
    // Kamus
    LL L1;
    LL L2;
    LL L3;
    addressLL P1;
    addressLL P2;
    addressLL P3;
    addressLL P4;
    addressLL P5;
    addressLL addtemp;
    infotype eltemp;
    float avg;
    int i;

    // ALgoritma
    printf("CREATE, FILLING, INSVFIRST/LAST\n");
    CreateEmpty(&L1);
    CreateEmpty(&L2);
    CreateEmpty(&L3);
    if(IsEmpty(L1)) printf("kosong\n");
    for (i = 3; i > 0; i--) InsVFirst(&L1, i);
    PrintInfo(L1);nl;
    for (i = 1; i <= 3; i++) InsVLast(&L2, i);
    PrintInfo(L2);nl;nl;
    printf("SEARCH\n");
    P1 = Search(L1, 1);
    printf("%d\n", P1->info);
    if(FSearch(L1, P1)) printf("ada\n");
    P1 = SearchPrec(L1,1);
    if(P1 != Nil) printf("%d\n", P1->info);nl;

    printf("COPY\n");
    CpAlokLL(L1, &L3);
    PrintInfo(L3);nl;nl;

    printf("DEL/INSERT LL (V) FIRST/LAST\n");
    DelLLVFirst(&L3, &eltemp);
    PrintInfo(L3);              // 2 3
    printf(" %d\n", eltemp);    // 1

    DelLLVLast(&L3, &eltemp);
    PrintInfo(L3);              // 2
    printf(" %d\n", eltemp);    // 3

    P4 = AlokasiLL(1);
    InsertLLFirst(&L3, P4);     // 1 2
    PrintInfo(L3);nl;

    // P2 = AlokasiLL(3);
    // P5 = SearchPrec(L1,2);
    // InsertLLAfter(&L3, P2, P5);
    // PrintInfo(L3);nl;nl;     // 1 2 3

    P3 = AlokasiLL(4);
    InsertLLLast(&L3, P3);
    PrintInfo(L3);nl;           // 1 2 4

    DelLLP(&L3,5);
    PrintInfo(L3);nl;nl;        // 1 2 4

    // DelLLFirst(&L3, &P4);
    // DelLLLast(&L3, &P4);
    // DelLLAfter(&L3, &P4);

    printf("MAX, MIN, ADDR, AVG\n");
    eltemp = Max(L1); printf("%d\n", eltemp);
    addtemp = AdrMax(L1); printf("%d\n", addtemp->info);
    eltemp = Min(L1); printf("%d\n", eltemp);
    addtemp = AdrMin(L1); printf("%d\n", addtemp->info);
    avg = Average(L1); printf("%.2f\n", avg);

    printf("INVERS\n");
    DelLLAll(&L2);
    L2 = FInversLL(L1);
    PrintInfo(L2);nl;nl;

    printf("KONKAT, PECAH\n");
    DelLLAll(&L3);
    Konkat(L1,L2,&L3);  // mem leak, cpalokll, alokasill
    PrintInfo(L3);nl;
    Konkat1(&L1,&L2,&L3);
    PrintInfo(L3);nl;
    PecahLL(&L1,&L2,L3);
    PrintInfo(L1);nl;
    PrintInfo(L2);nl;nl;

    printf("DELALL, DEALOKASI\n");
    DelLLAll(&L1);
    DelLLAll(&L2);
    DelLLAll(&L3);
    // ga bener
    // Dealokasi(&P2);
    // Dealokasi(&P3);
    // Dealokasi(&P4);
    // Dealokasi(&P5);
    printf("END OF PROGRAM\n");
    return 0;
}
