/* Include(s) */
#include <stdio.h>
#include "./../lib/header/boolean.h"
#include "./../lib/header/str.h"
#include "../lib/header/resources.h"
#include "../lib/header/stacklist.h"
#include "../lib/header/wahana.h"
#include "../lib/header/globals.h"

extern Stack actionStack;
extern Resource playerResources;

void ShowMenu() {
    printf("new : New Game\n");
    printf("load : Load Game\n");
    printf("exit : Exit Game\n");
}

/* Main */
int main () {
    /* KAMUS */
    init();
    char main_opt[5];
    char new[]="new";
    char load[]="load";
    char exit[]="exit";

    /* ALGORITMA */
    // Accept input
    printf("Willy Wangky no Fum Factory e Youkoso\n");

    ShowMenu(); printf("$ ");
    scanf("%[^\n]%*c", main_opt);

    while (!strIsEqual(main_opt, exit)) {
        if (strIsEqual(main_opt, new)) {
            // ke new
            printf("new\n");
        } else if (strIsEqual(main_opt, load)) {
            // ke load
            printf("load\n");
        }
        // Request input
        ShowMenu(); printf("$ ");
        scanf("%[^\n]%*c", main_opt);
    }

    printf("Jaa matane\n");

    return 0;
}
