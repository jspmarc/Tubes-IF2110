/* Include(s) */
#include <stdio.h>
#include "../lib/header/mesinkata.h"
#include "./../lib/header/boolean.h"
#include "./../lib/header/str.h"
#include "../lib/header/resources.h"
#include "../lib/header/stacklist.h"
#include "../lib/header/wahana.h"
#include "../lib/header/globals.h"
#include "map.h"

void ShowMenu() {
    printf("new : New Game\n");
    printf("load : Load Game\n");
    printf("exit : Exit Game\n");
}

/* Main */
int main () {
    /* KAMUS */
    init();

    Kata new, load, exit;
    new.TabKata[0] = 'n';
    new.TabKata[1] = 'e';
    new.TabKata[2] = 'w';
    new.TabKata[3] = '\0';
    new.Length = 3;
    load.TabKata[0] = 'l';
    load.TabKata[1] = 'o';
    load.TabKata[2] = 'a';
    load.TabKata[3] = 'd';
    load.TabKata[4] = '\0';
    load.Length = 4;
    exit.TabKata[0] = 'e';
    exit.TabKata[1] = 'x';
    exit.TabKata[2] = 'i';
    exit.TabKata[3] = 't';
    exit.TabKata[4] = '\0';
    exit.Length = 4;

    /* ALGORITMA */
    // Accept input
    printf("Willy Wangky no Fum Factory e Youkoso\n");

    ShowMenu(); printf("$ ");
    STARTKATA();

		do{
			if(IsKataSama(CKata, new)){
				// ke new
				printf("Masukkan nama: ");
				IgnoreBlank();
				ADVKATA();
				SalinKataKe(&Nama);
				printf("Selamat datang, ");
				TulisKataKe(Nama, stdout);
				printf("!\n");
				ShowMap(crrntMapID, playerPos, Map1);
			}
			else if(IsKataSama(CKata, load)){
				// ke load ?
			}
			else{
				// input gak valid...
			}
			// Akuisisi kata baru kalo gak kosong
			if(!IsKataSama(CKata, exit)){
				ShowMenu(); printf("$ ");
				IgnoreBlank();
				ADVKATA();
			}
		} while(!IsKataSama(CKata, exit) && !EndKata);

    printf("Jaa matane\n");

    return 0;
}
