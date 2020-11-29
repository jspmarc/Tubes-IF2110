/* FILE: mainPhase.c */

#include <stdio.h>
#include <stdlib.h>
#include "mainPhase.h"
#include "./../lib/header/boolean.h"
#include "./../lib/header/str.h"
#include "./../lib/header/prioqueuell.h"
#include "./../lib/header/jam.h"
#include "./../lib/header/wahana.h"
#include "./../lib/header/globals.h"
#include "./../lib/header/map.h"

#define nl printf("\n")

void SERVE() {
    /* Memakan waktu */
    /* SERVE {input: type pengunjung, wahana, wahana.antrian} */
    address pengunjung;
    infotype idWahanaYangSudahDikunjungi;

    // jika tidak ada wahana yang ingin dikunjungi, keluar antrian
    Dequeue(&antrianCustomer, &pengunjung);

    // Serve berlaku untuk pengunjung pertama antrian tiap command
    // Jika masih ada wahana yang ingin dikunjungi
    if (!IsEmpty(wahanaID(pengunjung))) {
        // Masuk kembali ke antrian, prioritas bertambah
        DelLLVFirst(&wahanaID(pengunjung), &idWahanaYangSudahDikunjungi);
        if (Prio(pengunjung) == 5) Prio(pengunjung) = 4; // Jika prioritas sudah 5, tak bisa bertambah
        Enqueue(&antrianCustomer, &pengunjung);
    }

    /* Uang bertambah */
    int i = 0;
    while ((i < BuiltWahana.NbEl) && ((BuiltWahana.arr[i].id) == Info(LLFirst(wahanaID(Head(antrianCustomer)))))) {
        i++;
    }

    // ID Wahana yang diinginkan pengunjung ketemu
    if ((BuiltWahana.arr[i].id) == Info(LLFirst(wahanaID(Head(antrianCustomer))))) {
        playerResources.uang += ((((ATangibleWahana) BuiltWahana.arr[i].metadata)->baseTree)->upgradeInfo).harga;
        (((ATangibleWahana) BuiltWahana.arr[i].metadata)->used) += 1;
        (((ATangibleWahana) BuiltWahana.arr[i].metadata)->usedTotal) += 1;
    }
}

void REPAIR () {
    /* Memakan waktu */
    // berarti abis benerin atangiblewahana->status jadi 1
    array wahanaSekitarPlayer;
	addrNode upgradeBersangkutan;
	Kata Wahana;
	ATangibleWahana wahanaTerdekat;

    wahanaSekitarPlayer = WahanaSekitarPosisi(playerPos);
    if (wahanaSekitarPlayer.NbEl == 1) {
        if (((ATangibleWahana) wahanaSekitarPlayer.arr[0].metadata)->status == 1)
            puts("Wahana tidak rusak.");
        else {
            ((ATangibleWahana) wahanaSekitarPlayer.arr[0].metadata)->status = 1;
            /* Bayar harga repair (1/2 harga build) */
            playerResources.uang -= Akar((WahanaTree) AvailableWahana.arr[0].metadata).UpgradeCost.uang;
            currentJam = NextNDetik(currentJam, 900);
            puts("Wahana telah diperbaiki.");
        }
    } else if (wahanaSekitarPlayer.NbEl > 1) {
		int idxWahana;
		puts("Mau berinteraksi dengan wahana apa?");
		/* Ngeprint nama wahana */
		for (int i = 0; i < wahanaSekitarPlayer.NbEl; ++i) {
			Kata namaWahana;
			int wahanaUpgradeId = ((ATangibleWahana) wahanaSekitarPlayer.arr[i].metadata)->currentUpgradeID;
    
			/* Dicari yang cocok upgradenya */
			upgradeBersangkutan = cariUpgrade(((ATangibleWahana) wahanaSekitarPlayer.arr[i].metadata)->baseTree, wahanaUpgradeId);

			SalinKataDariKe(upgradeBersangkutan->upgradeInfo.nama, &namaWahana);
			printf("  -");
			TulisKataKe(namaWahana, stdout);
		}
		printf("\n❯ ");
		/* Ngebaca wahana yang mau diupgrade */
		IgnoreBlank();
		ADVKATA();
		SalinKataKe(&Wahana);

		for (idxWahana = 0; idxWahana < wahanaSekitarPlayer.NbEl; ++idxWahana) {
			upgradeBersangkutan = cariUpgrade(((ATangibleWahana) wahanaSekitarPlayer.arr[idxWahana].metadata)->baseTree, ((ATangibleWahana) wahanaSekitarPlayer.arr[idxWahana].metadata)->currentUpgradeID);

			if (IsKataSama(upgradeBersangkutan->upgradeInfo.nama, Wahana)) {
               if (((ATangibleWahana) wahanaSekitarPlayer.arr[idxWahana].metadata)->status == 1)
                    puts("Wahana tidak rusak.");
                else {
                    ((ATangibleWahana) wahanaSekitarPlayer.arr[idxWahana].metadata)->status = 1;
                    playerResources.uang -= Akar((WahanaTree) AvailableWahana.arr[idxWahana].metadata).UpgradeCost.uang;
                    currentJam = NextNDetik(currentJam, 900);
                    puts("Wahana telah diperbaiki.");
                }
                break;
			}
		}
		if (idxWahana == wahanaSekitarPlayer.NbEl) puts("Tidak ada wahana dengan nama itu di sekitarmu.");
    } else { /* Tidak ada wahana di sekitar */
		puts("Tidak ada wahana di sekitarmu yang bisa diupgrade.");
    }
    return;
}

void DETAIL () {
    /* Tidak memakan waktu */
    // Kamus Lokal
    char *status;
    array wahana;
    int idxWahana;
    Kata namaWahana;
    ATangibleWahana atWahana;

    wahana = WahanaSekitarPosisi(playerPos);
    if(wahana.NbEl != 0) {
        printf("// Melihat detail wahana //\n");
        for (idxWahana = 0; idxWahana < wahana.NbEl; idxWahana++) {
            atWahana = wahana.arr[idxWahana].metadata;
            namaWahana = atWahana->baseTree->upgradeInfo.nama;
            printf("// Nama         : "); TulisKataKe(namaWahana,stdout); nl;
            printf("// Lokasi       : "); TulisPoint(atWahana->posisi); nl;
            printf("// Upgrades(s)  : "); /* ini or pohon */ nl;
            printf("// History      : "); /* ini naon */ nl;
            if (atWahana->status == '1') status = "Berfungsi";
            else status = "Rusak";
            printf("// Status       : %s\n\n", status);
            idxWahana++;
        }
    } else {
        printf("Tidak ada wahana di sekitarmu.\n\n");
    }
    return;
}

ATangibleWahana bacaInputWahana() {
    // Kamus Lokal
    Kata perintah;
    int i;
    Kata nama;
    boolean found;
    ATangibleWahana wahana;

    // Algoritma
    do {
        found = false;
        printf("Daftar wahana: \n");
        for (i = 0; i < BuiltWahana.NbEl; i++) {
            nama = ((ATangibleWahana) BuiltWahana.arr[i].metadata)->baseTree->upgradeInfo.nama;
            printf("- "); TulisKataKe(nama,stdout);nl;
        }
        nl;
        printf("\nMasukkan nama wahana: \n");
        IgnoreBlank();
        ADVKATA();
        SalinKataKe(&perintah);
        for (i = 0; i < BuiltWahana.NbEl && !found; i++) {
            wahana = BuiltWahana.arr[i].metadata;
            nama = wahana->baseTree->upgradeInfo.nama;
            if (IsKataSama(perintah, nama)) found = true;
        }
    } while(!found);

    return wahana;
}

void OFFICE () {
    /* Tidak memakan waktu */
    // Kamus Lokal
    char perintah[50];
    ATangibleWahana wahana;
    char * status;

    // Algoritma
    printf("// Memasukin office mode //\n");
    do {    
        do {
            printf("Masukkan perintah (Details / Report / Exit):\n");
            scanf("%s",perintah);
        } while(!strIsEqual(perintah,"Details") ||
                !strIsEqual(perintah,"Report") ||
                !strIsEqual(perintah,"Exit"));

        if(strIsEqual(perintah,"Details")) {
            if(BuiltWahana.NbEl != 0) {
                wahana = bacaInputWahana();
                printf("// Nama         : "); TulisKataKe(wahana->baseTree->upgradeInfo.nama,stdout); nl;
                printf("// Lokasi       : "); TulisPoint(wahana->posisi); nl;
                printf("// Upgrades(s)  : "); /* ini or pohon */ nl;
                printf("// History      : "); /* ini naon */ nl;
                if (wahana->status == '1') status = "Berfungsi";
                else status = "Rusak";
                printf("// Status       : %s\n\n", status);
            } else {
                printf("Belum ada wahana yang telah dibangun.\n");
            }

        } else if(strIsEqual(perintah,"Report")) {
            if(BuiltWahana.NbEl != 0) {
                wahana = bacaInputWahana();
                int money;
                int moneeeeeeeey;
                int harga;

                harga = wahana->baseTree->upgradeInfo.harga;
                money = wahana->used * harga;
                moneeeeeeeey = wahana->used * harga;
                printf("Banyak kali wahana dinaiki           : %d kali\n",wahana->usedTotal);
                printf("Penghasilan wahana                   : %d\n",moneeeeeeeey);
                printf("Banyak kali wahana dinaiki hari ini  : %d kali\n",wahana->used);
                printf("Penghasilan wahana hari ini          : %d\n\n",money);
            } else {
                printf("Belum ada wahana yang telah dibangun.\n");
            }
        } else if(strIsEqual(perintah,"Exit")) {
            printf("// Keluar dari office mode //\n");
            return;
        }
    } while (true);
}
