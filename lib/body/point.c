/* File: point.c */
/* Tanggal: 02 September 2020
 * 13519164 Josep Marcello */
/* *** Realisasi ABSTRACT DATA TYPE Point *** */

#include "../header/point.h"
#include <stdio.h>
#include <math.h>

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk Point *** */
Point MakePoint (int X, int Y) {
    /*KAMUS LOKAL*/
    Point p;

    /*ALGORITMA*/
    Absis(p) = X;
    Ordinat(p) = Y;

    return p;
}

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */
void BacaPoint (Point * P) {
    /*KAMUS LOKAL*/
    int x, y;

     /*ALGORITMA*/
    scanf("%d %d", &x, &y);
    *P = MakePoint(x, y);
}
void TulisPoint (Point P) {
    /*ALGORITMA*/
    printf("(%d,%d)", Absis(P), Ordinat(P));
}

/* *** Kelompok operasi relasional terhadap Point *** */
boolean PointEQ (Point P1, Point P2) {
    /*ALGORITMA*/
    return Absis(P1) == Absis(P2) && Ordinat(P1) == Ordinat(P2);
}
boolean PointNE (Point P1, Point P2) {
    /*ALGORITMA*/
    return !( PointEQ(P1, P2) );
}

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
Point NextX (Point P) {
    /*ALGORITMA*/
    return MakePoint(Absis(P)+1, Ordinat(P));
}
Point NextY (Point P) {
    /*ALGORITMA*/
    return MakePoint(Absis(P), Ordinat(P)+1);
}
Point BeforeX (Point P) {
    /*ALGORITMA*/
    return MakePoint(Absis(P)-1, Ordinat(P));
}
Point BeforeY (Point P) {
    /*ALGORITMA*/
    return MakePoint(Absis(P), Ordinat(P)-1);
}

void Geser (Point *P, int deltaX, int deltaY) {
    /* ALGORITMA */
    Absis(*P) += deltaX;
    Ordinat(*P) += deltaY;
}
