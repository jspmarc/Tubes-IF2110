/* File: mesinkata.c */
/* Realisasi Mesin Kata: Model Akuisisi Versi I */
/* Josep Marcello
 * 13519164
 * 30 September 2020 */

#include "../header/mesinkata.h"
#include <stdio.h>

boolean EndKata;
Kata CKata;

void IgnoreBlank() {
    while (CC == BLANK) ADV();
}

void STARTKATA() {
    START(stdin);
    IgnoreBlank();

    if (CC == MARK) {
        EndKata = true;
    } else {
        EndKata = false;
        SalinKata();
    }
}

void ADVKATA() {
    if (CC == MARK) {
        EndKata = true;
    } else {
        SalinKata();
        IgnoreBlank();
    }
}

void SalinKata() {
    int i;

    i = 0;

    while(i < NMax && CC != MARK && CC != BLANK) {
        CKata.TabKata[i++] = CC;
        ADV();
    }

    CKata.TabKata[i] = '\0';
    CKata.Length = i;
}
