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

void ShowMenu() {
	printf("new : New Game\n");
	printf("load : Load Game\n");
	printf("exit : Exit Game\n");
}

/* Main */
int main () {
	/* KAMUS */
	boolean isIngame = false;
	init();
	initCommands();

	long totalDetikAksi = 0; int totalUangAksi = 0;
	unsigned totalAksi = 0;

	JAM durasi = DetikToJAM(Durasi(currentJam, OpeningJam));

	/* ALGORITMA */
	printf("\n");
	/* Pembacaan file wahana dilakukan di init() */
	// Accept input
	printf("Willy Wangky no Fum Factory e Youkoso\n");

	ShowMenu(); printf("❯ ");
	STARTKATA();

	do{
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
		} else if (isIngame) {
			if(CKata.Length == 1){
				// w,a,s,d
				if(CKata.TabKata[0] == 'w') MoveW();
				else if(CKata.TabKata[0] == 'a') MoveA();
				else if(CKata.TabKata[0] == 's') MoveS();
				else if(CKata.TabKata[0] == 'd') MoveD();
				else puts("Perintah tidak dikenali");

			} else if(IsKataSama(CKata, build)){
				Kata Wahana;
				int idxWahana;
				// Build Logic
				printf("Ingin membangun apa?\nList:\n");
				for (int i = 0; i < AvailableWahana.NbEl; ++i) {
					printf("  - ");
					TulisKataKe(Akar((WahanaTree) AvailableWahana.arr[i].metadata).nama, stdout);
					puts("");
				}
				printf("\n❯ ");
				/* Ngebaca wahana yang mau dibangun */
				IgnoreBlank();
				ADVKATA();
				SalinKataKe(&Wahana);

				for (idxWahana = 0;
					idxWahana < AvailableWahana.NbEl && !IsKataSama(Akar((WahanaTree) AvailableWahana.arr[idxWahana].metadata).nama, Wahana);
					++idxWahana);

				if (idxWahana >= AvailableWahana.NbEl) {
					puts("Wahana itu tidak ada dan tidak nyata");
				} else {
					/* *** RENDER WAHANA DI PETA *** */
					/* Yg skrg boleh diapus aja */
					MAP currentMap;

					currentMap = WhichMap(crrntMapID);
					if (Ordinat(BeforeY(playerPos)) != 0) {
						/* Render tulisan W */
						Ordinat(playerPos)--;
					} else if (Absis(BeforeX(playerPos)) != 0) {
						/* Render tulisan W */
						Absis(playerPos)--;
					} else if (Ordinat(NextY(playerPos)) == Ordinat(currentMap.MapSize)+1) {
						/* Render tulisan W */
						Ordinat(playerPos)++;
					} else {}
					/* *** END RENDER WAHANA DI PETA *** */

					/* Cek bisa bangun wahana atau nggak */

					/* Kalo bisa bangun */
					BuildWahana(Akar((WahanaTree) AvailableWahana.arr[idxWahana].metadata), playerPos);
					totalAksi++;
					totalDetikAksi += JAMToDetik(MakeJAM(0, 30, 0)); /* TODO: Harusnya dependant sama DoableActions */
					totalUangAksi += Akar((WahanaTree) AvailableWahana.arr[idxWahana].metadata).UpgradeCost.uang;
				}
			} else if(IsKataSama(CKata, upgrade)){
				// Upgrade Logic
				/* Jangan lupa tambah durasi dan uang */
				/*totalAksi++;*/
			} else if(IsKataSama(CKata, buy)){
				// Buy Logic
				/* Jangan lupa tambah durasi dan uang */
				/*BuyResource();*/
				Kata input,
					 splitInput[2],
					 namaMaterial;
				int qty;
				Material boughtMaterial;

				printf("Ingin membeli apa?\nList:\n");
				for (int i = 0; i < BuyableMaterials.NbEl; ++i) {
							printf("  - ");
							TulisKataKe(((Material*) BuyableMaterials.arr[i].metadata)->namaMaterial, stdout);
					printf("\n");
				}
				printf("\n❯ ");
				/* Ngebaca material yang mau dibeli */
				IgnoreBlank();
				ADVKATA();
				SalinKataKe(&input);

				/* Nge-split input jadi quantity dan nama material */
				int j = 0, k = 0;
				char C = input.TabKata[k];
				while (j < 2) {
					int i = 0;
					while (C != ' ' && C != '\0' && k < input.Length) {
						splitInput[j].TabKata[i++] = C;
						C = input.TabKata[++k];
					}
					splitInput[j].TabKata[i] = '\0';
					splitInput[j].Length = i;
					C = input.TabKata[++k];
					++j;
				}

				/* Nyocokin nama material dengan material yang ada di array of
				 * buyable materials */
				namaMaterial = splitInput[1];
				boolean found = false;
				for (int i = 0; i < BuyableMaterials.NbEl && !found; ++i) {
					Material curMater = *((Material *) BuyableMaterials.arr[i].metadata);
					if (IsKataSama(curMater.namaMaterial, namaMaterial)) {
						found = true;
						boughtMaterial = curMater;
					}
				}

				/* Nge-parse Kata ke int */
				qty = 0;
				for (int i = 0; i < splitInput[0].Length && found; ++i) {
					int addVal = splitInput[0].TabKata[i] - '0';
					qty *= 10;

					if (addVal > 9 || addVal < 0) {
						qty = -1;
						break;
					} else qty += addVal;
				}

				/* Dah siap buat dimasukin ke actionStack, tinggal dicek aja
				 * resource player cukup buat beli atau nggak */
				int materialID = boughtMaterial.idMaterial;
				if (qty != -1 && found) {
					materialID = getMaterialId(namaMaterial);
					/* Ngecek bisa bangun atau nggak */

					/* Kalo bisa */
					BuyResource(qty, materialID, boughtMaterial.biayaMaterial);
					totalAksi++;
					totalDetikAksi += JAMToDetik(MakeJAM(0, 15, 0)); /* TODO: Harusnya dependant sama DoableActions */
					totalUangAksi += qty * boughtMaterial.biayaMaterial;
				} else {
					puts("Gagal membeli material karena jumlah pembelian tidak valid atau karena material tidak ada.");
				}

				/*totalAksi++;*/
			} else if(IsKataSama(CKata, undo)){
				// Undo Logic
				/* Jangan lupa tambah durasi dan uang */
				if (totalAksi == 0) {
					puts("Tidak ada aksi yang dapat diurungkan");
				} else {
					UndoData data;
					ATangibleWahana infoTangibleWahana;
					actBuy *infoBuyMaterial;

					data = Undo();
					totalAksi--;
					totalDetikAksi -= JAMToDetik(data.prop.durasiAksi);

					switch (data.prop.idAksi) {
						case BUILD:
							infoTangibleWahana = (ATangibleWahana) data.infoAksi;
							totalUangAksi -= TreeWahana(infoTangibleWahana).UpgradeCost.uang;
							break;
						case UPGRADE:
							break;
						case BUY:
							infoBuyMaterial = (actBuy *) data.infoAksi;
							totalUangAksi -= infoBuyMaterial->qty * infoBuyMaterial->harga;
							break;
					}
				}
			} else if(IsKataSama(CKata, execute)){
				// Execute Logic
				/* Jangan lupa tambah durasi dan uang */
				/*totalAksi++;*/
			} else if(IsKataSama(CKata, mainC)){
				// main Logic
				/* Jangan lupa tambah durasi dan uang */
				/*totalAksi++;*/
			} else if(IsKataSama(CKata, serve)){
				// Serve Logic
				/* Jangan lupa tambah durasi dan uang */
				/*totalAksi++;*/
			} else if(IsKataSama(CKata, repair)){
				// Repair Logic
				/* Jangan lupa tambah durasi dan uang */
				/*totalAksi++;*/
			} else if(IsKataSama(CKata, detail)){
				// Detail Logic
				/* Jangan lupa tambah durasi dan uang */
				/*totalAksi++;*/
			} else if(IsKataSama(CKata, office)){
				// Office Logic
				/* Jangan lupa tambah durasi dan uang */
				/*totalAksi++;*/
			} else if(IsKataSama(CKata, prepare)){
				// Prepare Logic
				/* Jangan lupa tambah durasi dan uang */
				/*totalAksi++;*/
			} else{
				// input gak valid...
			}
			// perintah lain lagi: main phase, etc etc
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
				printf("\nMoney: %d\n", playerResources.uang);
				printf("Current Time: %02d.%02d\n", currentJam.HH, currentJam.MM);
				printf("Opening Time: %02d.%02d\n", OpeningJam.HH, OpeningJam.MM);
				printf("Time Remaining:");
				if (durasi.HH != 0) printf(" %d hour%c", durasi.HH, durasi.HH > 1 ? 's':'\0');
				if (durasi.MM != 0) printf(" %d minute%c", durasi.MM, durasi.MM > 1 ? 's':'\0');
				if (durasi.SS != 0) printf(" %d second%c", durasi.SS, durasi.SS > 1 ? 's':'\0');
				printf(" (%ld seconds)\n", JAMToDetik(durasi));

				printf("Total aksi yang akan dilakukan: %d\n", totalAksi);
				printf("Total waktu yang dibutuhkan:");
				JAM totalJamAksi = DetikToJAM(totalDetikAksi);
				if (totalJamAksi.HH != 0) printf(" %d hour%c", totalJamAksi.HH, totalJamAksi.HH > 1 ? 's':'\0');
				if (totalJamAksi.MM != 0) printf(" %d minute%c", totalJamAksi.MM, totalJamAksi.MM > 1 ? 's':'\0');
				if (totalJamAksi.SS != 0) printf(" %d second%c", totalJamAksi.SS, totalJamAksi.SS > 1 ? 's':'\0');
				printf(" (%ld seconds)\n", totalDetikAksi);
				printf("Total uang yang dibutuhkan: %d\n", totalUangAksi);

				puts("");
				printf("Masukkan perintah:\n");
			}
			printf("❯ ");
			IgnoreBlank();
			ADVKATA();
		}
	} while(!IsKataSama(CKata, exitC) && !EndKata);

	printf("Jaa matane\n");

	return 0;
}
