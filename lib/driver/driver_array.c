#include <stdlib.h>
#include <stdio.h>
#include "../header/array.h"
#include "boolean.h"

#define nl printf("\n")

int main() {
    // Kamus
    array A;
    array B;
    ArrayElType El;
    ArrayElType El1;
    ArrayElType temp;
    int hasil;
    int i;
    int j;
    char ctemp;

    // Algoritma
    CreateArray(&A,3);
    CreateArray(&B,3);
    printf("CREATE ARRAY, PRINTING ISI ARRAY\n");
    PrintArr(A); nl;
    PrintArr(B); nl;
    printf("press enter ");
    scanf("%c", &ctemp);nl;

    printf("\nEMPTY\n");
    if(IsArrEmpty(A)) printf("array A kosong\n");
    else printf("array B tidak kosong\n");
    if(IsArrEmpty(B)) printf("array B kosong\n");
    else printf("array B tidak kosong\n");
    
    printf("press enter ");
    scanf("%c", &ctemp);nl;
    printf("\nINSERT\n");
    printf("inslast\n");
    for(j = 1; j <= 3; j++) {
        El1.id = j;
        El1.info = j;
        InsArrLast(&A, El1);
    }
    PrintArr(A); nl; nl;
    printf("insfirst\n");
    for(i = 3; i > 0; i--) {
        El1.id = i;
        El1.info = i;
        InsArrLast(&B, El1);
    }
    PrintArr(B); nl;
    
    printf("press enter ");
    scanf("%c", &ctemp);nl;
    printf("\nCOPY\n");
    CopyArr(A, &B);
    PrintArr(A);nl;
    PrintArr(B);nl;

    printf("press enter ");
    scanf("%c", &ctemp);nl;
    printf("\nDELETE\n");
    printf("delfirst\n");
    temp = DelArrFirst(&B);
    printf("id: %d\ninfo: %d\n", temp.id, temp.info);
    PrintArr(B);nl;nl;
    CopyArr(A, &B);
    printf("dellast\n");
    temp = DelArrLast(&B);
    printf("id: %d\ninfo: %d\n", temp.id, temp.info);
    PrintArr(B);nl;

    printf("press enter ");
    scanf("%c", &ctemp);nl;
    printf("\nCOPY\n");
    CopyArr(A, &B);
    PrintArr(A);nl;
    PrintArr(B);nl;

    printf("press enter ");
    scanf("%c", &ctemp);nl;
    printf("\nGROW SHRINK\n");
    GrowArray(&B,3); // newsize
    printf("Grow jadi %d\n", A.MaxEl);
    PrintArr(B); nl;
    ShrinkArray(&B,3); // newsize
    printf("Shrink jadi %d\n", A.MaxEl);
    PrintArr(B); nl;
    
    printf("press enter ");
    scanf("%c", &ctemp);nl;
    printf("\nFULL\n");
    if(IsArrFull(A)) printf("array penuh\n");
    else printf("array penuh\n");

    printf("press enter ");
    scanf("%c", &ctemp);nl;
    printf("\nSEARCH\n");
    printf("masukkan id: ");
    scanf("%d", &El.id);
    printf("masukkan info: ");
    scanf("%d", &El.info);
    hasil = SearchArrEl(A,El);
    printf("hasil: %d\n\nini arraynya\n", hasil);
    PrintArr(A);nl;

    // ini sort dibuang
    // printf("press enter ");
    // scanf("%c", &ctemp);nl;
    // printf("\nSORT\n");
    // printf("Before\n");
    // PrintArr(A);nl;
    // printf("press enter ");
    // scanf("%c", &ctemp);nl;
    // printf("asc\n");
    // SortArr(&A,true);
    // PrintArr(A);nl;
    // printf("press enter ");
    // scanf("%c", &ctemp);nl;
    // printf("desc\n");
    // SortArr(&A,false);
    // PrintArr(A);nl;

    printf("press enter ");
    scanf("%c", &ctemp);nl;
    printf("\nSHIFTING\n");
    printf("before\n");
    PrintArr(B); nl; CopyArr(A, &B);
    printf("shift array left 1\n");
    ShiftArrLeft(&B,1);
    PrintArr(B); nl; CopyArr(A, &B);
    printf("press enter ");
    scanf("%c", &ctemp);nl;
    printf("shift array left 3 = MaxEl\n");
    ShiftArrLeft(&B,10);
    PrintArr(B); nl; CopyArr(A, &B);
    printf("press enter ");
    scanf("%c", &ctemp);nl;
    // printf("shift array left -1\n"); // TODO: BUG shift right
    // ShiftArrLeft(&B,(-1));
    // PrintArr(B); nl; CopyArr(A, &B);

    printf("press enter ");
    scanf("%c", &ctemp);nl;
    printf("before\n");
    PrintArr(B); nl;
    // printf("shift array right 1\n"); // TODO:Bbug
    // ShiftArrRight(&B,1);
    // PrintArr(B); nl; CopyArr(A, &B);
    printf("press enter ");
    scanf("%c", &ctemp);nl;
    printf("shift array right 3 = MaxEl\n");
    ShiftArrRight(&B,10);
    PrintArr(B); nl; CopyArr(A, &B);
    printf("press enter ");
    scanf("%c", &ctemp);nl;
    printf("shift array right -1\n");
    ShiftArrRight(&B,(-1));
    PrintArr(B); nl; CopyArr(A, &B);

    printf("press enter ");
    scanf("%c", &ctemp);nl;
    printf("\nDELETE ARRAY\n");
    DeleteArray(&A);
    DeleteArray(&B);
    printf("yes\n");
    return 0;
}
