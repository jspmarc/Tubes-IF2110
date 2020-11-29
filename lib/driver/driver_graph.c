#include <stdlib.h>
#include <stdio.h>
#include "../header/graph.h"
#include "boolean.h"

#define nl printf("\n")

int main() {
    // Kamus
    char ctemp;
    int a;
    Graph G;
    int iprec, isucc;
    adrNode aprec, asucc;

    // ALgoritma
    printf("CREATE GRAPH\n");
    a = 1;
    CreateGraph(a,&G);

    printf("press enter ");
    scanf("%c", &ctemp);nl;

    InsertEdge(&G,iprec,isucc);

    printf("\nDELETE GRAPH\n");

    printf("END OF PROGRAM\n");
    return 0;
}
