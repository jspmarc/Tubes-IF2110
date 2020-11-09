#include <stdio.h>
#include "../header/listlinier.h"

int main()
{
    List L1, L2, L3, L4, L5;
    address P1, P2, P3;

    CreateEmpty(&L1);
    CreateEmpty(&L2);
    CreateEmpty(&L3);
    CreateEmpty(&L4);
    CreateEmpty(&L5);

    P1 = Alokasi(10);
    P2 = Alokasi(20);
    P3 = Alokasi(30);

    InsertFirst(&L1, P1);
    InsertFirst(&L1, P2);
    InsertFirst(&L1, P3);

    for (int i = 0; i < 8; ++i)
        InsVLast(&L2, i);

    PrintInfo(L1);
    puts("");
    PrintInfo(L2);
    puts("");

    printf("\nFSearch\tSearchPrec\tInfo(AdrMax)\tMin\tInfo(AdrMin)\tAvg\n");

    printf("%d\t", FSearch(L1, P1));
    printf("%p\t\t", (SearchPrec(L1, 30)));
    printf("%d\t\t", Info(AdrMax(L1)));
    printf("%d\t", Min(L1));
    printf("%d\t\t", Info(AdrMin(L1)));
    printf("%.2f\n", Average(L1));

    printf("%d\t", FSearch(L2, P1));
    printf("%d\t\t", Info(SearchPrec(L2, 2)));
    printf("%d\t\t", Info(AdrMax(L2)));
    printf("%d\t", Min(L2));
    printf("%d\t\t", Info(AdrMin(L2)));
    printf("%.2f\n", Average(L2));

    CopyList(&L1, &L4);
    puts("\nCopyList: ");
    printf("L1: ");
    PrintInfo(L1);
    printf("\nL1 Copied: ");
    PrintInfo(L4);

    L3 = FCopyList(L2);
    puts("\n\nFCopyList: ");
    printf("L2: ");
    PrintInfo(L2);
    printf("\nL2 Copied: ");
    PrintInfo(L3);


    DelAll(&L2);
    puts("\n\nDelAll:");
    printf("L2 Deleted: ");
    PrintInfo(L2);

    puts("\nCopying L2 back to its original place... (CpAlokList)");
    CpAlokList(L3, &L2);
    PrintInfo(L2);

    puts("\n\nKonkat:");
    Konkat(L1, L2, &L5);
    printf("L1: ");
    PrintInfo(L1);
    printf("\nL2: ");
    PrintInfo(L2);
    printf("\nKonkat L1 dan L2: ");
    PrintInfo(L5);

    CpAlokList(L1, &L4);
    puts("\n\nMembalikkan L1...");
    printf("L1: ");
    PrintInfo(L4);
    puts("");
    InversList(&L4);
    PrintInfo(L4);

    CpAlokList(L2, &L5);
    puts("\n\nMembalikkan L2...");
    printf("L2: ");
    PrintInfo(L3);
    L3 = FInversList(L5);
    puts("");
    PrintInfo(L3);

    CpAlokList(L1, &L5);
    puts("\n\nMemecah list L1...");
    PecahList(&L3, &L4, L5);
    printf("L1: ");
    PrintInfo(L5);
    printf("\nSetengah L1: ");
    PrintInfo(L3);
    printf("\nSetengah lain L1: ");
    PrintInfo(L4);
}
