/* Include(s) */
#include <stdio.h>
#include "./../header/boolean.h"

void ShowMenu() {
    printf("new : New Game\n");
    printf("load : Load Game\n");
    printf("exit : Exit Game\n");
}

/* fungsi membandingkan dua string */
// pindahin ke mana ya?
boolean strIsEqual(char * s1, char * s2) {
    int i;
    boolean eq;

    eq = true;
    i = 0;
    while (eq && (s1[i] != '\0') && (s2[i] != '\0')) {
        if (s1[i] != s2[i]) {
            eq = false;
        }
        i++;
    }
    return eq;
}

/* Main */
int main () {
    /* KAMUS */
    char main_opt[5];
    char new[]="new";
    char load[]="load";
    char exit[]="exit";

    /* ALGORITMA */
    // Accept input
    printf("Willy Wangky no Fum Factory e Youkoso\n");
    
    ShowMenu();
    fgets(main_opt, 5, stdin);

    while (!strIsEqual(main_opt, exit)) {
        if (strIsEqual(main_opt, new)) {
            // ke new
            printf("new\n");
        } else if (strIsEqual(main_opt, load)) {
            // ke load
            printf("load\n");
        }
        // Request input
        ShowMenu();
        fgets(main_opt, 5, stdin);
    }

    printf("Jaa matane\n");

    return 0;
}