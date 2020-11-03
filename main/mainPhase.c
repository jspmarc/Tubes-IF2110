/* FILE: mainPhase.c */
/* Author: Kahfi */

#include <stdio.h>
#include "./../header/boolean.h"
#include "./../header/str.c"
#include "./../header/prioqueuechar.h"

void SERVE (char * wahana) {
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

}

void DETAIL () {

}

void OFFICE () {

}

void PREPARE () {

}

int main () {
    printf("Selamat datang, pengunjung sekalian di Willy Wangky\n");
    printf("Jangan lupa untuk mengantri dan tetap menjaga jarak antar pengunjung\n");
    printf("Terima kasih\n");


    

    return 0;
}