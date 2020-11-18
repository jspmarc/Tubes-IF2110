/* File : str.c */
/* fungsi tambahan string */

#include "boolean.h"
#include "../header/str.h"

/* fungsi menghitung panjang karakter di string */
int strLen(char * string) {
    int i;
    for (i = 0; string[i] != '\0'; i++);

    return i;
}

/* fungsi membandingkan dua string */
boolean strIsEqual(char * s1, char * s2) {
    int i;
    boolean eq, endofs1, endofs2;

    eq = true;
    i = 0;

    if (strLen(s1) != strLen(s2)) {
        eq = false;
    } else {
        while (eq && (i <= strLen(s1))) {
            if (s1[i] != s2[i]) {
                eq = false;
            }
            i++;
        }
    }

    return eq;
}
