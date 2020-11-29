/* FILE: mainPhase.c */
/* Author: 13519012 Kahfi Soobhan Zulkifli
           13519116 Jeane Mikha Erwansyah */

#include <stdio.h>
#include <stdlib.h>
#include "./../lib/header/boolean.h"
#include "./../lib/header/str.h"
#include "./../lib/header/prioqueuell.h"
#include "./../lib/header/jam.h"
#include "./../lib/header/wahana.h"
#include "./../lib/header/globals.h"
#include "./../lib/header/map.h"

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
    int count;
    ArrayElType el;

    wahana = WahanaSekitarPosisi(playerPos);
    if(wahana.NbEl != 0) {
        /*
        while (count <= wahana.NbEl) {
            
            status = "Berfungsi";
            printf("// Melihat detail wahana //\n");
            printf("// Nama         : \n");
            printf("// Lokasi       : \n");
            printf("// Upgrades(s)  : \n");
            printf("// History      : \n");
            printf("// Status       : %s\n\n", status);
            count++;
        }
        */
    } else {
        printf("Tidak ada wahana di sekitarmu.\n\n");
    }
    return;
}

void OFFICE () {
    /* Tidak memakan waktu */
    // Kamus Lokal
    char perintah[50];
    int A,B,C,D;

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
            //<Masukkan Tampilan Details>
            // Tampilkan list wahana,lalu pilih wahana untuk ditampilkan detailnya //
        } else if(strIsEqual(perintah,"Report")) {
            do {
                printf("Daftar wahana: \n");
                printf("- TBFO\n");
                printf("- Alstrukdat\n");
                printf("- Algeo\n");
                printf("- Matdis\n");
                printf("- Orkom\n");
                printf("- Logkom\n");
                printf("\nMasukkan nama wahana: \n");
                scanf("%s",perintah);
            } while(!strIsEqual(perintah,"TBFO") ||
                    !strIsEqual(perintah,"Alstrukdat") ||
                    !strIsEqual(perintah,"Algeo") ||
                    !strIsEqual(perintah,"Matdis") ||
                    !strIsEqual(perintah,"Orkom") ||
                    !strIsEqual(perintah,"Logkom"));
            
            // mungkin pake switch case?
            if(strIsEqual(perintah,"TBFO")) {
                A = /* ADT */; B = /* ADT */; C = /* ADT */; D = /* ADT */;
            } else if(strIsEqual(perintah,"Alstrukdat")) {
                A = /* ADT */; B = /* ADT */; C = /* ADT */; D = /* ADT */;
            } else if(strIsEqual(perintah,"Algeo")) {
                A = /* ADT */; B = /* ADT */; C = /* ADT */; D = /* ADT */;
            } else if(strIsEqual(perintah,"Matdis")) {
                A = /* ADT */; B = /* ADT */; C = /* ADT */; D = /* ADT */;
            } else if(strIsEqual(perintah,"Orkom")) {
                A = /* ADT */; B = /* ADT */; C = /* ADT */; D = /* ADT */;
            } else { // if(strIsEqual(perintah,"Logkom"))
                A = /* ADT */; B = /* ADT */; C = /* ADT */; D = /* ADT */;
            }
            printf("Banyak kali wahana dinaiki           : %d kali\n",A);
            printf("Penghasilan wahana                   : %d\n",B);
            printf("Banyak kali wahana dinaiki hari ini  : %d kali\n",C);
            printf("Penghasilan wahana hari ini          : %d\n\n",D);
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
