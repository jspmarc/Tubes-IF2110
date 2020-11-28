/* Include(s) */
#include <stdio.h>
#include "../lib/header/mesinkata.h"
#include "../lib/header/boolean.h"
#include "../lib/header/str.h"
#include "../lib/header/resources.h"
#include "../lib/header/stacklist.h"
#include "../lib/header/wahana.h"
#include "../lib/header/globals.h"
#include "../lib/header/parser.h"
#include "../lib/header/map.h"
#include "commands.h"
#include "prepPhase.h"

MAP Map1;
Kata BuildableWahana[6];

#define KataTBFO BuildableWahana[0]
#define KataAlstrukdat BuildableWahana[1]
#define KataAlgeo BuildableWahana[2]
#define KataMatdis BuildableWahana[3]
#define KataOrkom BuildableWahana[4]
#define KataLogkom BuildableWahana[5]

void IsiBuildableWahana() {
	/**
	 * Index 0: TBFO (4),
	 * Index 1: Alstrukdat (10),
	 * Index 2: Algeo (5),
	 * Index 3: Matdis (6),
	 * Index 4: Orkom (5),
	 * Index 5: Logkom(6),
	 */
	BuildableWahana[0].TabKata[0] = 'T';
	BuildableWahana[0].TabKata[1] = 'B';
	BuildableWahana[0].TabKata[2] = 'F';
	BuildableWahana[0].TabKata[3] = 'O';
	BuildableWahana[0].Length = 4;

	BuildableWahana[1].TabKata[0] = 'A';
	BuildableWahana[1].TabKata[1] = 'l';
	BuildableWahana[1].TabKata[2] = 's';
	BuildableWahana[1].TabKata[3] = 't';
	BuildableWahana[1].TabKata[4] = 'r';
	BuildableWahana[1].TabKata[5] = 'u';
	BuildableWahana[1].TabKata[6] = 'k';
	BuildableWahana[1].TabKata[7] = 'd';
	BuildableWahana[1].TabKata[8] = 'a';
	BuildableWahana[1].TabKata[9] = 't';
	BuildableWahana[1].Length = 10;

	BuildableWahana[2].TabKata[0] = 'A';
	BuildableWahana[2].TabKata[1] = 'l';
	BuildableWahana[2].TabKata[2] = 'g';
	BuildableWahana[2].TabKata[3] = 'e';
	BuildableWahana[2].TabKata[4] = 'o';
	BuildableWahana[2].Length = 5;

	BuildableWahana[3].TabKata[0] = 'M';
	BuildableWahana[3].TabKata[1] = 'a';
	BuildableWahana[3].TabKata[2] = 't';
	BuildableWahana[3].TabKata[3] = 'd';
	BuildableWahana[3].TabKata[4] = 'i';
	BuildableWahana[3].TabKata[5] = 's';
	BuildableWahana[3].Length = 6;

	BuildableWahana[4].TabKata[0] = 'O';
	BuildableWahana[4].TabKata[1] = 'r';
	BuildableWahana[4].TabKata[2] = 'k';
	BuildableWahana[4].TabKata[3] = 'o';
	BuildableWahana[4].TabKata[4] = 'm';
	BuildableWahana[4].Length = 5;

	BuildableWahana[5].TabKata[0] = 'L';
	BuildableWahana[5].TabKata[1] = 'o';
	BuildableWahana[5].TabKata[2] = 'g';
	BuildableWahana[5].TabKata[3] = 'k';
	BuildableWahana[5].TabKata[4] = 'o';
	BuildableWahana[5].TabKata[5] = 'm';
	BuildableWahana[5].Length = 6;

}

void ShowMenu() {
	printf("new : New Game\n");
	printf("load : Load Game\n");
	printf("exit : Exit Game\n");
}

/* Main */
int main () {
	/* KAMUS */
	boolean isIngame = false;
	IsiBuildableWahana();
	init();
	initCommands();
	/* ALGORITMA */
	printf("\n");
	/* Pembacaan file wahana dilakukan di init() */
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
			if(CKata.TabKata[0] == 'w') MoveW();
			if(CKata.TabKata[0] == 'a') MoveA();
			if(CKata.TabKata[0] == 's') MoveS();
			if(CKata.TabKata[0] == 'd') MoveD();
		}
		else if(IsKataSama(CKata, build)){
			Kata Wahana;
			int idxWahana;
			// Build Logic
			printf("Ingin membangun apa?\nList:\n");
			for (int i = 0; i < AvailableWahana.NbEl; ++i) {
				printf("    - ");
				TulisKataKe(Akar((WahanaTree) AvailableWahana.arr[i].metadata).nama, stdout);
				puts("");
			}
			printf("\n$ ");
			/* Ngebaca wahana yang mau dibangun */
			IgnoreBlank();
			ADVKATA();
			SalinKataKe(&Wahana);

			if (IsKataSama(Wahana, KataTBFO)) {
				idxWahana = 0;
			} else if (IsKataSama(Wahana, KataAlstrukdat)) {
				idxWahana = 1;
			} else if (IsKataSama(Wahana, KataAlgeo)) {
				idxWahana = 2;
			} else if (IsKataSama(Wahana, KataMatdis)) {
				idxWahana = 3;
			} else if (IsKataSama(Wahana, KataOrkom)) {
				idxWahana = 4;
			} else if (IsKataSama(Wahana, KataLogkom))  {
				idxWahana = 5;
			} else {
				puts("Wahana itu tidak ada dan tidak nyata");
				continue;
			}

			BuildWahana(Akar((WahanaTree) AvailableWahana.arr[idxWahana].metadata), playerPos);
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
				JAM durasi = DetikToJAM(Durasi(currentJam, OpeningJam));
				
				ShowMap();
				puts("Legend:");
				puts("A = Antrian");
				puts("P = Player");
				puts("W = Wahana");
				puts("O = Office");
				puts("<, ^, >, V = Gerbang");

				puts("");
				printf("Name: ");
				TulisKataKe(Nama, stdout);
				printf("\nMoney: %d\n", playerResources.uang);
				printf("Current Time: %02d.%02d\n", currentJam.HH, currentJam.MM);
				printf("Opening Time: %02d.%02d\n", OpeningJam.HH, OpeningJam.MM);
				printf("Time Remaining:");
				if (durasi.HH != 0) printf(" %d hour%c", durasi.HH, durasi.HH > 1 ? 's':'\0');
				if (durasi.MM != 0) printf(" %d minute%c", durasi.MM, durasi.MM > 1 ? 's':'\0');
				if (durasi.SS != 0) printf(" %d second%c", durasi.SS, durasi.SS > 1 ? 's':'\0');
				puts("");
				printf("Total aksi yang akan dilakukan: %d", NbElmtStack(actionStack));

				puts("");
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
