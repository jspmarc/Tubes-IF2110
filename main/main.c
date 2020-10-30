/* Include(s) */
#include <stdio.h>
#include <string.h>

void ShowMenu() {
    printf("new : New Game\n");
    printf("load : Load Game\n");
    printf("exit : Exit Game\n");
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

    while (strcmp(main_opt, exit) != 0) {
        if (strcmp(main_opt, new) == 0) {
            // ke new
            printf("new\n");
        } else if (strcmp(main_opt, load) == 0) {
            // ke load
            printf("load\n");
        }
        // Request input
        menu();
        fgets(main_opt, 5, stdin);
    }

    printf("Jaa matane\n");

    return 0;
}