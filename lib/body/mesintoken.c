/* File: mesintoken.c */
/* Definisi Mesin Token: Model Akuisisi Versi I */

#include "../header/mesintoken.h"
#include <stdio.h>

/* State Mesin Kata */
boolean EndToken;
Token CToken;

void IgnoreBlank() {
    while (CC == BLANK) ADV();
}

void STARTTOKEN() {
    START();
    IgnoreBlank();
    if (CC == MARK) EndToken = true;
    else {
        EndToken = false;
        SalinToken();
    }
}

void ADVTOKEN() {
    IgnoreBlank();
    if (CC == MARK) EndToken = true;
    else SalinToken();
}

void SalinToken() {
    int i = 0;

    CToken.val = 0;
    while (i < NMax && CC != BLANK && CC != MARK) {
        if (CC == '+' || CC == '-'
            || CC == '*' || CC == '/'
            || CC == '^') {
            CToken.tkn = CC;
            CToken.val = -1;
        } else if ('0' <= CC && CC <= '9') {
            CToken.val *= 10;
            CToken.val += (CC - '0');
            CToken.tkn = 'b';
        }
        ADV();
        i++;
    }
}
