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
#include "map.h"

void SERVE () {
    /* Memakan waktu */
    /* SERVE {input: type pengunjung, wahana, wahana.antrian} */

    ShowMap(crrntMapID, playerPos, Map1);

}

void REPAIR () {
    /* Memakan waktu */
    /* REPAIR {input: wahana} */

    return;
}

void DETAIL () {
    /* Tidak memakan waktu */
    /* DETAIL {input: wahana} */

    return;
}

void OFFICE () {
    /* Tidak memakan waktu */
    /* OFFICE {input: office} */

    return;
}

void PREPARE () {
    /* Tidak memakan waktu */
    /* PREPARE {kosongkan antrian, --> prep phase} */

    return;
}

int MainPhase() {
    Queue Q;
    int i;
    char * perintah;
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
        scanf("%c", perintah);

        if (strIsEqual(perintah, "serve")) {
            SERVE();
        } else if (strIsEqual(perintah, "repair")) {
            REPAIR();
        } else if (strIsEqual(perintah, "detail")) {
            DETAIL();
        } else if (strIsEqual(perintah, "office")) {
            OFFICE();
        } else if (strIsEqual(perintah, "prepare")) {
            PREPARE();
        } else {
            printf("Masukan Anda salah. Silakan ulangi lagi!");
        }
    }

    return 0;
}
