/* File: jam.c */
/* Tanggal: 2 September 2020 */
/* Definisi ADT JAM */
/* Josep Marcello
 * 13519164 */

#include "../header/jam.h"
#include <stdio.h>

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsJAMValid (int H, int M, int S) {
    return ( 0 <= H && H <= 23 &&
             0 <= M && M <= 59 &&
             0 <= S && S <= 59 );
}

/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
JAM MakeJAM (int HH, int MM, int SS) {
    /* KAMUS LOKAL */
    JAM guaCapek;

    /* ALGORITMA */
    Hour(guaCapek) = HH;
    Minute(guaCapek) = MM;
    Second(guaCapek) = SS;

    return guaCapek;
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaJAM (JAM * J) {
    /* KAMUS LOKAL */
    int gua,mau,mati;
    /* ALGORITMA */
    scanf("%d %d %d", &gua, &mau, &mati);
    while (!IsJAMValid(gua, mau, mati) ) {
        printf("Jam tidak valid\n");
        scanf("%d %d %d", &gua, &mau, &mati);
    }

    Hour(*J) = gua;
    Minute(*J) = mau;
    Second(*J) = mati;
}

void TulisJAM (JAM J) {
    /* ALGORITMA */
    printf("%d:%d:%d", Hour(J), Minute(J), Second(J));
}

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long JAMToDetik (JAM J) {
    /* ALGORITMA */
    return Hour(J)*3600 + Minute(J)*60 + Second(J);
}

JAM DetikToJAM (long N) {
    /* KAMUS LOKAL */
    int j,m,d;
    /* ALGORITMA */
    if (N < 0) N += 86400;
    N %= 86400;

    j = N/3600;
    m = (N%3600)/60;
    d = N%60;

    return MakeJAM(j, m, d);
}

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean JEQ (JAM J1, JAM J2) {
    /* ALGORITMA */
    return ( Hour(J1) == Hour(J2) &&
             Minute(J1) == Minute(J2) &&
             Second(J1) == Second(J2) );
}
boolean JNEQ (JAM J1, JAM J2) {
    /* ALGORITMA */
    return !JEQ(J1, J2);
}
boolean JLT (JAM J1, JAM J2) {
    /* ALGORITMA */
    return JAMToDetik(J1) < JAMToDetik(J2);
}
boolean JGT (JAM J1, JAM J2) {
    /* ALGORITMA */
    return JAMToDetik(J1) > JAMToDetik(J2);
}
/* *** Operator aritmatika JAM *** */
JAM NextDetik (JAM J) {
    return DetikToJAM(JAMToDetik(J)+1);
}
JAM NextNDetik (JAM J, int N) {
    return DetikToJAM(JAMToDetik(J)+N);
}
JAM PrevDetik (JAM J) {
    return DetikToJAM(JAMToDetik(J)-1);
}
JAM PrevNDetik (JAM J, int N) {
    return DetikToJAM(JAMToDetik(J)-N);
}
/* *** Kelompok Operator Aritmetika *** */
long Durasi (JAM JAw, JAM JAkh) {
    /* ALGORITMA */
    return JAMToDetik(JAw) <= JAMToDetik(JAkh) ?
                JAMToDetik(JAkh) - JAMToDetik(JAw) :
                JAMToDetik(JAkh)+86400 - JAMToDetik(JAw);
}
