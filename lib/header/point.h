/* File: point.h */
/* Tanggal: 28 Agustus 2016 */
/* *** Definisi ABSTRACT DATA TYPE Point *** */

#ifndef Point_H
#define Point_H

#include "boolean.h"
#include <stdio.h>

typedef struct {
	double X; /* absis   */
	double Y; /* ordinat */
} Point;

/* *** Notasi Akses: Selektor Point *** */
#define Absis(P) (P).X
#define Ordinat(P) (P).Y

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk Point *** */
/* Membentuk sebuah Point dari komponen-komponennya */
Point MakePoint (double X, double Y);

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

/* *** Kelompok menentukan di mana P berada *** */
/* Menghasilkan true jika P adalah titik origin */
boolean IsPointOrigin (Point P);
/* Menghasilkan true jika P terletak Pada sumbu X */
boolean IsPointOnSbX (Point P);
/* Menghasilkan true jika P terletak pada sumbu Y */
boolean IsPointOnSbY (Point P);
/* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
/* Prekondisi : P bukan titik origin, */
/*              dan P tidak terletak di salah satu sumbu */
int Kuadran (Point P);

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
/* Mengirim salinan P dengan absis ditambah satu */
Point NextX (Point P);
/* Mengirim salinan P dengan ordinat ditambah satu */
Point NextY (Point P);
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
Point PlusDelta (Point P, double deltaX, double deltaY);
/* Menghasilkan salinan P yang dicerminkan terhadap salah satu sumbu */
/* Jika SbX bernilai true, maka dicerminkan terhadap sumbu X */
/* Jika SbX bernilai false, maka dicerminkan terhadap sumbu Y */
Point MirrorOf (Point P, boolean SbX);
/* Menghitung jarak P ke (0,0) */
double Jarak0 (Point P);
/* Menghitung panjang garis yang dibentuk P1 dan P2 */
/* Perhatikanlah bahwa di sini spec fungsi kurang baik sebab menyangkut ADT Garis. */
/* Tuliskan spec fungsi yang lebih tepat. */
double Panjang (Point P1, Point P2);
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
void Geser (Point *P, double deltaX, double deltaY);
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
void GeserKeSbX (Point *P);
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */
void GeserKeSbY (Point *P);
/* I.S. P terdefinisi */
/* F.S. P dicerminkan tergantung nilai SbX atau SbY */
/* Jika SbX true maka dicerminkan terhadap sumbu X */
/* Jika SbX false maka dicerminkan terhadap sumbu Y */
void Mirror (Point *P, boolean SbX);
/* I.S. P terdefinisi */
/* F.S. P digeser sebesar Sudut derajat dengan sumbu titik (0,0) searah jarum jam*/
void Putar (Point *P, double Sudut);

#endif
