/* File: mesinkar.c */
/* Implementasi Mesin Karakter */

#include "../header/mesinkar.h"
#include <stdio.h>

char CC;
boolean EOP;

static FILE * pita;
static int retval;

void START(FILE* f) {
    pita = f;
    ADV();
}

void ADV() {
    retval = fscanf(pita,"%c",&CC);
    EOP = (CC == MARK);
    if (EOP) {
       fclose(pita);
    }
}
