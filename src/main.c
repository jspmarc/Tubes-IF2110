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
#include "mainPhase.h"

long totalDetikAksi = 0;

void ShowMenu() {
	printf("new : New Game\n");
	printf("load : Load Game\n");
	printf("exit : Exit Game\n");
}

void IsiTotalResourceAksi(Resource *totalResourceAksi) {
	totalResourceAksi->uang = 0;
	CreateArray(&totalResourceAksi->materials, MAX_MATERIAL);
	for (int i = 0; i < BuyableMaterials.NbEl; ++i) {
		ArrayElType el;
		Material *mater = (Material *) malloc(sizeof(Material));

		el.id = ((Material *) BuyableMaterials.arr[i].metadata)->idMaterial;
		el.info = ((Material *) BuyableMaterials.arr[i].metadata)->biayaMaterial;

		mater->biayaMaterial = el.info;
		mater->idMaterial = el.id;
		mater->jumlahMaterial = 0;
		SalinKataDariKe(((Material *) BuyableMaterials.arr[i].metadata)->namaMaterial, &mater->namaMaterial);

		el.metadata = mater;

		InsArrLast(&totalResourceAksi->materials, el);
	}
}

void EfektifkanPerubahanResourcePemain(Resource resourcePengubah) {
}

void KeluarDariGame() {
	puts("Jaa matane");
	exit(0);
}

/* Main */
int main () {
	/* KAMUS */
	boolean isIngame = false;
	boolean isPrepPhase = true, isMainPhase = false;
	init();
	initCommands();

	unsigned totalAksi = 0;
	Resource totalResourceAksi;

	IsiTotalResourceAksi(&totalResourceAksi);

	/* ALGORITMA */

	/* *** Helper buat debug  */
	ArrayElType el;
	ATangibleWahana w = (ATangibleWahana) malloc(sizeof(TangibleWahana));
	el.id = ((WahanaTree) AvailableWahana.arr[1].metadata)->upgradeInfo.id;
	el.info = ((WahanaTree) AvailableWahana.arr[1].metadata)->upgradeInfo.id;
	w->baseTree = ((WahanaTree) AvailableWahana.arr[1].metadata);
	w->currentUpgradeID = el.id;
	w->posisi = MakePoint(Absis(playerPos), Ordinat(playerPos)+1);
	w->idMap = 1;
	el.metadata = w;

	InsArrLast(&BuiltWahana, el);
	/* Helper buat debug ***  */

	/* Pembacaan file wahana dilakukan di init() */

	// Accept input
	printf("Willy Wangky no Fum Factory e Youkoso\n");

	ShowMenu(); printf("❯ ");
	STARTKATA();

	do{
		JAM durasiP = DetikToJAM(Durasi(currentJam, OpeningJam));
		JAM durasiM = DetikToJAM(Durasi(currentJam, ClosingJam));
		// main game loop
		if(IsKataSama(CKata, newC) && !isIngame) {
			// ke new
			printf("Masukkan nama: ");
			IgnoreBlank();
			ADVKATA();
			SalinKataKe(&Nama);
			printf("Selamat datang, ");
			TulisKataKe(Nama, stdout);
			printf("!\n");
			isIngame = 1;
		} else if(IsKataSama(CKata, load) && !isIngame) {
			// ke load ?
		} else if (IsKataSama(CKata, exitC)) {
			KeluarDariGame();
		} else if (IsKataSama(CKata, inventory) && isIngame) {
			puts("Resource yang kamu miliki:");
			PrintResource(playerResources);
			puts("\nResource yang dibutuhkan untuk eksekusi: ");
			PrintResource(totalResourceAksi);

			Kata _;
			puts("Masukkan apapun untuk melanjutkan...");
			IgnoreBlank();
			ADVKATA();
			SalinKataKe(&_);
		} else if(CKata.Length == 1 && isIngame) {
			// w,a,s,d
			/* jika move berhasil, waktu bertambah */
			if(CKata.TabKata[0] == 'w') MoveW();
			else if(CKata.TabKata[0] == 'a') MoveA();
			else if(CKata.TabKata[0] == 's') MoveS();
			else if(CKata.TabKata[0] == 'd') MoveD();
			else puts("Perintah tidak dikenali.");
		} else if (isIngame && isPrepPhase) {
			if(IsKataSama(CKata, build)){
				Build(&totalAksi, &totalDetikAksi, &totalResourceAksi);
			} else if(IsKataSama(CKata, upgrade)){
				// Upgrade Logic
				/* Jangan lupa tambah durasiP dan uang */
				/*totalAksi++;*/
				Upgrade(&totalAksi, &totalDetikAksi, &totalResourceAksi);
			} else if(IsKataSama(CKata, buy)){
				Buy(&totalAksi, &totalDetikAksi, &totalResourceAksi);
			} else if(IsKataSama(CKata, undo)){
				Undo(&totalAksi, &totalDetikAksi, &totalResourceAksi);
			} else if(IsKataSama(CKata, execute)){
				// Execute Logic
				/* Jangan lupa tambah durasiP dan uang */
				isPrepPhase = false;
				isMainPhase = true;
				/*RandomPengunjung();*/
				totalAksi = 0;
				totalDetikAksi = 0;
				IsiTotalResourceAksi(&totalResourceAksi);
				Execute(&totalResourceAksi);
			} else if(IsKataSama(CKata, mainC)){
				// main Logic
				/* Jangan lupa tambah durasiP dan uang */
				isPrepPhase = false;
				isMainPhase = true;
				totalAksi = 0;
				totalDetikAksi = 0;
				IsiTotalResourceAksi(&totalResourceAksi);
				ToMainPhase();
			} else {
				puts("Perintah tidak dikenali.");
			}
		} else if (isMainPhase && isIngame) {
			if(IsKataSama(CKata, serve)){
				// Serve Logic
				/* Jangan lupa tambah durasiP dan uang */
				SERVE();
				// Sekali serp 15 menit (gatau kenapa, pengen aja)
				currentJam = NextNDetik(currentJam, 900);
			} else if(IsKataSama(CKata, repair)){
				// Repair Logic
				/* Jangan lupa tambah durasiP dan uang */
				REPAIR();
				/* Pertambahan waktu sudah ada di REPAIR() */
				/* Jika berhasil repair, waktu bertambah, 
				   jika tidak tetap */
			} else if(IsKataSama(CKata, detail)){
				// Detail Logic
				DETAIL();
			} else if(IsKataSama(CKata, office) && PointEQ(playerPos, Office(WhichMap(crrntMapID)))){
				// Office Logic
				OFFICE();
			} else if(IsKataSama(CKata, prepare)){
				// Prepare Logic
				isMainPhase = false;
				isPrepPhase = true;
				currentJam = MakeJAM(21, 0, 0);
			} else {
				puts("Perintah tidak dikenali.");
			}
		} else {
			puts("Perintah tidak dikenali.");
		}
		// Akuisisi kata baru kalo gak kosong
		if(!IsKataSama(CKata, exitC)){
			if(!isIngame) ShowMenu();
			else{

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
				printf("\nMoney: %d\n\n", playerResources.uang);

				if (isPrepPhase) {
					printf("Current Time: %02d.%02d\n", currentJam.HH, currentJam.MM);
					printf("Opening Time: %02d.%02d\n", OpeningJam.HH, OpeningJam.MM);
					printf("Time Remaining:");
					if (durasiP.HH != 0) printf(" %d hour%c", durasiP.HH, durasiP.HH > 1 ? 's':'\0');
					if (durasiP.MM != 0) printf(" %d minute%c", durasiP.MM, durasiP.MM > 1 ? 's':'\0');
					if (durasiP.SS != 0) printf(" %d second%c", durasiP.SS, durasiP.SS > 1 ? 's':'\0');
					printf(" (%ld seconds)\n\n", JAMToDetik(durasiP));

					printf("Total aksi yang akan dilakukan: %d\n", totalAksi);
					printf("Total waktu yang dibutuhkan:");
					JAM totalJamAksi = DetikToJAM(totalDetikAksi);
					if (totalJamAksi.HH != 0) printf(" %d hour%c", totalJamAksi.HH, totalJamAksi.HH > 1 ? 's':'\0');
					if (totalJamAksi.MM != 0) printf(" %d minute%c", totalJamAksi.MM, totalJamAksi.MM > 1 ? 's':'\0');
					if (totalJamAksi.SS != 0) printf(" %d second%c", totalJamAksi.SS, totalJamAksi.SS > 1 ? 's':'\0');
					printf(" (%ld seconds)\n", totalDetikAksi);
					printf("Total uang yang dibutuhkan: %d\n", totalResourceAksi.uang);
				} else if (isMainPhase) {
					printf("Current Time: %02d.%02d\n", currentJam.HH, currentJam.MM);
					printf("Closing Time: %02d.%02d\n", ClosingJam.HH, ClosingJam.MM);
					printf("Time Remaining:");
					if (durasiM.HH != 0) printf(" %d hour%c", durasiM.HH, durasiM.HH > 1 ? 's':'\0');
					if (durasiM.MM != 0) printf(" %d minute%c", durasiM.MM, durasiM.MM > 1 ? 's':'\0');
					if (durasiM.SS != 0) printf(" %d second%c", durasiM.SS, durasiM.SS > 1 ? 's':'\0');
					printf(" (%ld seconds)\n\n", JAMToDetik(durasiM));

					/* Print antrian */
					printf("Antrian [%d/%d]:\n", NbElmtQueue(antrianCustomer), MAX_WAHANA);
				}

				puts("");
				
				if(PointEQ(playerPos, Office(WhichMap(crrntMapID))) && isMainPhase && isIngame)
				printf("Masukkan 'office' untuk mengakses office\n");
				printf("Masukkan perintah:\n");
			}
			printf("❯ ");
			IgnoreBlank();
			ADVKATA();
		}
	} while(!EndKata);

	puts("Jaa matane");

	return 0;
}
