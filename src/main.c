/* Include(s) */
#include <stdio.h>
#include "../lib/header/mesinkata.h"
#include "./../lib/header/boolean.h"
#include "./../lib/header/str.h"
#include "../lib/header/resources.h"
#include "../lib/header/stacklist.h"
#include "../lib/header/wahana.h"
#include "../lib/header/globals.h"
#include "commands.h"
#include "map.h"

void ShowMenu() {
    printf("new : New Game\n");
    printf("load : Load Game\n");
    printf("exit : Exit Game\n");
}

/* Main */
int main () {
    /* KAMUS */
		boolean isIngame = 0;
    init();
    initCommands();
    /* ALGORITMA */
    // Accept input
    printf("Willy Wangky no Fum Factory e Youkoso\n");

    ShowMenu(); printf("$ ");
    STARTKATA();

		do{
			// main game loop
			if(IsKataSama(CKata, newC) && !isIngame){
				// ke new
				printf("Masukkan nama: ");
				IgnoreBlank();
				ADVKATA();
				SalinKataKe(&Nama);
				printf("Selamat datang, ");
				TulisKataKe(Nama, stdout);
				printf("!\n");
				isIngame = 1;
			}
			else if(IsKataSama(CKata, load)){
				// ke load ?
			}
			else if(CKata.Length == 1){
				// w,a,s,d
				if(CKata.TabKata[0] == 'w') MoveW(Map1);
				if(CKata.TabKata[0] == 'a') MoveA(Map1);
				if(CKata.TabKata[0] == 's') MoveS(Map1);
				if(CKata.TabKata[0] == 'd') MoveD(Map1);
			}
			else if(IsKataSama(CKata, build)){
				// Build Logic
			}
			else if(IsKataSama(CKata, upgrade)){
				// Upgrade Logic
			}
			else if(IsKataSama(CKata, buy)){
				// Buy Logic
			}
			else if(IsKataSama(CKata, undo)){
				// Undo Logic
			}
			else if(IsKataSama(CKata, execute)){
				// Execute Logic
			}
			else if(IsKataSama(CKata, mainC)){
				// main Logic
			}
			else if(IsKataSama(CKata, serve)){
				// Serve Logic
			}
			else if(IsKataSama(CKata, repair)){
				// Repair Logic
			}
			else if(IsKataSama(CKata, detail)){
				// Detail Logic
			}
			else if(IsKataSama(CKata, office)){
				// Office Logic
			}
			else if(IsKataSama(CKata, prepare)){
				// Prepare Logic
			}
			else{
				// input gak valid...
			}
			// perintah lain lagi: main phase, etc etc
			// Akuisisi kata baru kalo gak kosong
			if(!IsKataSama(CKata, exitC)){
				if(!isIngame) ShowMenu();
				else{
					ShowMap(crrntMapID, playerPos, Map1);
					printf("Masukkan perintah:\n");
				} 
				printf("$ ");
				IgnoreBlank();
				ADVKATA();
			}
		} while(!IsKataSama(CKata, exitC) && !EndKata);

    printf("Jaa matane\n");

    return 0;
}
