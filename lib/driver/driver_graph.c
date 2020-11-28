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

    // ALgoritma
    printf("CREATE GRAPH\n");
    a = 1;
    CreateGraph(a,&G);

    printf("press enter ");
    scanf("%c", &ctemp);nl;


    printf("\nDELETE GRAPH\n");

    printf("yes\n");
    return 0;
}
