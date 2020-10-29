/* ADT Array dinamis
 * Dengan tipe data dibebaskan*/

/* Elemen selalu berdempetan
 * Rata kiri
 * Tipe data pasti signed */

/* Kamus ukuran tipe data:
 * char: elSize = 1 (kode: c)
 * short: elSize = 2 (kode: s)
 * int: elSize = 4 (kode: i)
 * long: elSize = 8 (kode: l)
 * float: elSize = 4 (kode: f)
 * double: elSize = 8 (kode: d)
 */

#ifndef _ARRAY_H
#define _ARRAY_H

typedef struct {
    void *Arr;
    unsigned char ElSize;
    char ElType;
    unsigned NbEl;
} Array;

#define Nil -1;
#define FirstIdx 0;

/* I.S.: A tidak terdefinisi, nbEl dan elType terdefinisi
 * F.S.: A terdefinisi
 */
void CreateEmpty(Array *A, int NbEl, char ElType);

/* I.S.: A terdefinisi
 * F.S.: A tidak terdefinisi
 */
void DeleteArray(Array *A);

/* Mengubah nilai elemen di array a pada index ke-idx dengan elemen yg ditunjuk *el */
/* I.S.: A terdefinisi, mungkin kosong
 * F.S.: Nilai elemen di indeks idx pada array A adalah nilai yang ditunjuk *el
 */
void SetEl(Array *A, unsigned Idx, char El);
void SetEl(Array *A, unsigned Idx, short El);
void SetEl(Array *A, unsigned Idx, int El);
void SetEl(Array *A, unsigned Idx, long El);
void SetEl(Array *A, unsigned Idx, float El);
void SetEl(Array *A, unsigned Idx, double El);

/* Mengembalikan pointer void ke elemen di array A pada indeks ke-idx */
void* GetEl(Array A, unsigned Idx);

/* I.S.: Array A terdefinisi, mungkin kosong
 * F.S.: *NewEl menjadi elemen pertama *A, *A digeser ke kanan
 */
void UnShift(Array *A, void *NewEl);

/* I.S.: Array A terdefinisi
 * F.S.: Menghapus elemen pertama A lalu menaruhnya di *El, *A digeser ke kiri
 */
void* Shift(Array *A);

#endif
