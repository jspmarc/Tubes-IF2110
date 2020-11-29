/* FILE: mainPhase.c */

#include <stdio.h>
#include <stdlib.h>
#include "./../lib/header/boolean.h"
#include "./../lib/header/str.h"
#include "./../lib/header/prioqueuell.h"
#include "./../lib/header/jam.h"
#include "./../lib/header/wahana.h"
#include "./../lib/header/globals.h"
#include "./../lib/header/map.h"

#define nl printf("\n")

void SERVE () {
    /* Memakan waktu */
    /* SERVE {input: type pengunjung, wahana, wahana.antrian} */

    ShowMap();

}

void REPAIR () {
    /* Memakan waktu */

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
    int idxWahana;
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
                int A,B,C,D;
                
                // if(strIsEqual(inputWahana,"TBFO")) {
                //     // A = /* ADT */; B = /* ADT */; C = /* ADT */; D = /* ADT */;
                // } else if(strIsEqual(inputWahana,"Alstrukdat")) {
                //     // A = /* ADT */; B = /* ADT */; C = /* ADT */; D = /* ADT */;
                // } else if(strIsEqual(inputWahana,"Algeo")) {
                //     // A = /* ADT */; B = /* ADT */; C = /* ADT */; D = /* ADT */;
                // } else if(strIsEqual(inputWahana,"Matdis")) {
                //     // A = /* ADT */; B = /* ADT */; C = /* ADT */; D = /* ADT */;
                // } else if(strIsEqual(inputWahana,"Orkom")) {
                //     // A = /* ADT */; B = /* ADT */; C = /* ADT */; D = /* ADT */;
                // } else { // if(strIsEqual(perintah,"Logkom"))
                //     // A = /* ADT */; B = /* ADT */; C = /* ADT */; D = /* ADT */;
                // }
                printf("Banyak kali wahana dinaiki           : %d kali\n",A);
                printf("Penghasilan wahana                   : %d\n",B);
                printf("Banyak kali wahana dinaiki hari ini  : %d kali\n",C);
                printf("Penghasilan wahana hari ini          : %d\n\n",D);
            } else {
                printf("Belum ada wahana yang telah dibangun.\n");
            }
        } else if(strIsEqual(perintah,"Exit")) {
            printf("// Keluar dari office mode //\n");
            return;
        }
    } while (true);
}

void PREPARE () {
    /* Tidak memakan waktu */
    /* PREPARE {kosongkan antrian,--> prep phase} */

    return;
}

int MainPhase() {
    Queue Q;
    int i;
    /*char * perintah;*/
    char perintah[50];
    boolean open = true;
    JAM cur, close;

    printf("Selamat datang, pengunjung sekalian di Willy Wangky\n");
    printf("Jangan lupa untuk mengantri dan tetap menjaga jarak antar pengunjung\n");
    printf("Terima kasih\n");

    CreateEmptyQueue(&Q);
    for (i = 0; i < 5; i++) {
        Enqueue(&Q, i, 3);
        Enqueue(&Q, i+1, 1);
        Enqueue(&Q, i+2, 2);
    }
    
    while (open && JNEQ(cur, close)) {
        scanf("%s",perintah);
        // printf("%s\n",perintah);

        if (strIsEqual(perintah,"serve")) {
            SERVE();
        } else if (strIsEqual(perintah,"repair")) {
            REPAIR();
        } else if (strIsEqual(perintah,"detail")) {
            DETAIL();
        } else if (strIsEqual(perintah,"office")) {
            OFFICE();
        } else if (strIsEqual(perintah,"prepare")) {
            PREPARE();
        } else {
            printf("Masukan Anda salah. Silakan ulangi lagi!");
        }
    }

    return 0;
}
