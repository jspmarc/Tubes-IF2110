/* File: point.h */
/* Tanggal: 28 Agustus 2016 */
/* *** Definisi ABSTRACT DATA TYPE Point *** */

#ifndef Point_H
#define Point_H

#include "boolean.h"
#include <stdio.h>

typedef struct {
    int X; /* absis   */
    int Y; /* ordinat */
} Point;

/* *** Notasi Akses: Selektor Point *** */
#define Absis(P) (P).X
#define Ordinat(P) (P).Y

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk Point *** */
/* Membentuk sebuah Point dari komponen-komponennya */
Point MakePoint (int X, int Y);

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */

/* Membaca nilai absis dan ordinat dari keyboard dan membentuk
   Point P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2
   akan membentuk Point <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
void BacaPoint (Point * P);
/* Nilai P ditulis ke layar dengan format "(X,Y)"
   tanpa spasi, enter, atau karakter lain di depan, belakang,
   atau di antaranya
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */
void TulisPoint (Point P);

/* *** Kelompok operasi relasional terhadap Point *** */
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
boolean PointEQ (Point P1, Point P2);
/* Mengirimkan true jika P1 tidak sama dengan P2 */
boolean PointNEQ (Point P1, Point P2);

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
/* Mengirim salinan P dengan absis ditambah satu */
Point NextX (Point P);
/* Mengirim salinan P dengan ordinat ditambah satu */
Point NextY (Point P);
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
void Geser (Point *P, int deltaX, int deltaY);

#endif
