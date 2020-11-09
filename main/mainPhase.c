/* FILE: mainPhase.c */
/* Author: 13519012 Kahfi Soobhan Zulkifli
           13519116 Jeane Mikha Erwansyah */

#include <stdio.h>
#include "./../header/boolean.h"
#include "./../header/str.c"
#include "./../header/prioqueuechar.h"

void SERVE (char * wahana) {
    /* Memakan waktu */
    /* SERVE {input: type pengunjung, wahana, wahana.antrian} */
    int i;
    PrioQueueChar Q;

    for (i = 0; i < len(daftar_wahana); i++) { //ini mau akses array wahana, buat ngecek bener atau nggak
        if (strIsEqual(wahana, daftar_wahana[i])) {
            Q = daftar_antrian_wahana[i]; //masih asumsi kalau daftar antrian per wahana berbentuk array
            Dequeue(&Q, Head(Q));

        }
    } 

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

int main () {
    printf("Selamat datang, pengunjung sekalian di Willy Wangky\n");
    printf("Jangan lupa untuk mengantri dan tetap menjaga jarak antar pengunjung\n");
    printf("Terima kasih\n");


    

    return 0;
}