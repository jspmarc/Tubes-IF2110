/* File: point.c */
/* Tanggal: 02 September 2020
 * 13519164 Josep Marcello */
/* *** Realisasi ABSTRACT DATA TYPE Point *** */

#include "../header/point.h"
#include <stdio.h>
#include <math.h>

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk Point *** */
Point MakePoint (double X, double Y) {
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
    double x, y;

     /*ALGORITMA*/
    scanf("%lf %lf", &x, &y);
    *P = MakePoint(x, y);
}
void TulisPoint (Point P) {
    /*ALGORITMA*/
    printf("(%.2f,%.2f)", Absis(P), Ordinat(P));
}

/* *** Kelompok operasi relasional terhadap Point *** */
boolean EQ (Point P1, Point P2) {
    /*ALGORITMA*/
    return Absis(P1) == Absis(P2) && Ordinat(P1) == Ordinat(P2);
}
boolean NEQ (Point P1, Point P2) {
    /*ALGORITMA*/
    return !( EQ(P1, P2) );
}

/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin (Point P) {
    /*ALGORITMA*/
    return ( Absis(P) == 0 && Ordinat(P) == 0 );
}
boolean IsOnSbX (Point P) {
    /*ALGORITMA*/
    return Ordinat(P) == 0;
}
boolean IsOnSbY (Point P) {
    /*ALGORITMA*/
    return Absis(P) == 0;
}
int Kuadran (Point P) {
    /*ALGORITMA*/
    if (IsOnSbX(P) || IsOnSbY(P) || IsOrigin(P)) return -1;
    /* Jika bukan titik origin, bukan di sumbu x, atau bukan di sumbu y */
    else if (Absis(P) > 0) return Ordinat(P) > 0 ? 1 : 4;
    /* Absis negatif dan titik tidak di sumbu X atau sumbu Y */
    return Ordinat(P) > 0 ? 2 : 3; }

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
Point NextX (Point P) {
    /*ALGORITMA*/
    return MakePoint(Absis(P)+1, Ordinat(P));
}
Point NextY (Point P) {
    /*ALGORITMA*/
    return MakePoint(Absis(P), Ordinat(P)+1);
}
Point PlusDelta (Point P, double deltaX, double deltaY) {
    /* ALGORITMA */
    return MakePoint(Absis(P)+deltaX, Ordinat(P)+deltaY);
}
Point MirrorOf (Point P, boolean SbX) {
    /* ALGORITMA */
    if (SbX)
        return MakePoint(Absis(P), -1*Ordinat(P));
    else /* SbX == false */
        return MakePoint(-1*Absis(P), Ordinat(P));
}
double Jarak0 (Point P) {
    /* ALGORITMA */
    return sqrt( (Absis(P) * Absis(P))
               + (Ordinat(P) * Ordinat(P)) );
}
double Panjang (Point P1, Point P2) {
    /* KAMUS LOKAL */
    double selX, selY;
    /*ALGORITMA*/
    selX = Absis(P1) - Absis(P2);
    selY = Ordinat(P1) - Ordinat(P2);

    return sqrt( (selX * selX)
               + (selY * selY) );
}
void Geser (Point *P, double deltaX, double deltaY) {
    /* ALGORITMA */
    Absis(*P) += deltaX;
    Ordinat(*P) += deltaY;
}
void GeserKeSbX (Point *P) {
    /* ALGORITMA */
    Ordinat(*P) = 0;
}

void GeserKeSbY (Point *P) {
    /* ALGORITMA */
    Absis(*P) = 0;
}

void Mirror (Point *P, boolean SbX) {
    /* ALGORITMA */
    if (SbX) Ordinat(*P) = -1 * Ordinat(*P);
    else Absis(*P) = -1 * Absis(*P);
}

void Putar (Point *P, double Sudut) {
    /* KAMUS LOKAL */
    const double PI = 3.14159265;
    double Abs = Absis(*P);
    double Ord = Ordinat(*P);
    /* ALGORITMA */
    Sudut = -Sudut;

    /*x’ = x cos α – y sin α*/
    Absis(*P) = Abs * cos(Sudut * PI / 180) -
                Ord * sin(Sudut * PI / 180);

    /*y’ = x sin α + y cos α*/
    Ordinat(*P) = Abs * sin(Sudut * PI / 180) +
                  Ord * cos(Sudut * PI / 180);
}
