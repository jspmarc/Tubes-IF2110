#ifndef ARRAY_H
#define ARRAY_H

#include "boolean.h"

#define PadVal 0

/*
 * ini adalah ADT List implementasi array
 * digunakan untuk menyimpan ID daftar aksi beserta durasi (dalam detik)
 * atau menyimpan ID barang dan harganya.
 */

/**
 * Struktur data untuk elemen array
 */
typedef struct {
    int id; /* ID aksi atau barang */
    int info; /* durasi (dalam detik) atau harga barang */
} ArrayElType;

/**
 * Stuktur data array
 *
 * array kosong memiliki NbEl 0
 * array tidak terdefinisi memiliki MaxEl 0
 */
typedef struct {
    ArrayElType *arr; /* Untuk menyimpan elemen-elemen */
    unsigned NbEl; /* Banyak elemen "saat ini" */
    unsigned MaxEl; /* Banyak elemen maksimum */
} array;

/**
 * Prosedur membuat array kosong dan membuat array seukuran size
 *
 * array *A - Pointer ke array yang ingin dibuat
 * unsigned size - banyak elemen maksimum yang dapat ditampung array
 */
void CreateArray(array *A, unsigned size);
/**
 * Prosedur menghapus array. Mengosongkan array dan membuat array menjadi
 * tidak terdefinisi
 *
 * array *A - Pointer ke array yang ingin dihapus
 */
void DeleteArray(array *A);
/**
 * Prosedur untuk memperbesar ukuran (banyak elemen yang dapat ditampung) array
 *
 * array *A - pointer ke array yang ingin diperbesar
 * unsigned newSize - ukuran array baru
 */
void GrowArray(array *A, unsigned newSize);
/**
 * Prosedur untuk mengecilkan ukuran (banyak elemen yang dapat ditampung) array
 *
 * array *A - pointer ke array yang ingin diperkecil
 * unsigned newSize - ukuran array baru
 */
void ShrinkArray(array *A, unsigned newSize);

/**
 * Fungsi untuk menentukan array kosong atau tidak
 *
 * array A - Array yang ingin ditentukan kekosongannya
 * Returns true jika A kosong, false jika A tidak kosong
 */
boolean IsArrEmpty(array A);
/**
 * Fungsi untuk menentukan array penuh atau tidak
 *
 * array A - Array yang ingin ditentukan kepenuhannya
 * Returns true jika A penuh, false jika A tidak penuh
 */
boolean IsArrFull(array A);
/**
 * Fungsi untuk mencari El pada array. Fungsi akan mengembalikan
 * indeks dari El. Jika tidak ditemukan, akan mengembalikan -1
 *
 * array A - array yang harusnya menyimpan El
 * ArrayElType El - Elemen yang dicari
 * Returns indeks El di A
 */
int SearchArrEl(array A, ArrayElType El);

/**
 * Prosedur untuk menghapus elemen pertama dari array. Prosedur ini
 * akan mengubah properti NbEl dari array
 *
 * array *A - pointer ke array yang yang ingin dihapus elemen pertamanya
 * Returns elemen yang dihapus
 */
ArrayElType DelArrFirst(array *A);
/**
 * Prosedur untuk menghapus elemen terakhir dari array. Prosedur ini
 * akan mengurangi properti NbEl dari array sebanyak 1. Jika array kosong, akan
 * mengembalikan ArrayElType berisi 0
 *
 * array *A - pointer ke array yang ingin dihapus elemen terakhirnya
 * Returns elemen yang dihapus
 */
ArrayElType DelArrLast(array *A);
/**
 * Prosedur untuk menambahkan elemen ke akhir array. Jika array penuh, akan
 * keluar warning dan tidak dilakukan apa-apa. Prosedur ini akan mengurangi
 * properti NbEl dari array sebanyak 1. Jika array kosong, akan mengembalikan
 * ArrayElType berisi 0
 *
 * array *A - pointer ke array yang ingin ditambahkan elemen baru
 * ArrayElType El - elemen yang ingin ditambahkan ke array
 */
void InsArrFirst(array *A, ArrayElType X);
/**
 * Prosedur untuk menambahkan elemen ke awal array. Jika array penuh, akan
 * keluar warning dan tidak dilakukan apa-apa. Prosedur ini
 * akan menambah properti NbEl dari array sebanyak 1
 *
 * array *A - pointer ke array yang ingin ditambahkan elemen baru
 * ArrayElType El - elemen yang ingin ditambahkan ke array
 */
void InsArrLast(array *A, ArrayElType X);

/**
 * Prosedur untuk menggeser semua elemen ke kiri sebanyak n kali. Akan
 * mengurangi properti NbEl sebanyak n. Kalau n lebih besar dari jumlah elemen
 * di array, akan dilakukan "pengosongan" array
 *
 * Array *A - pointer ke array yang ingin digeser
 * unsigned n - banyak pergeseran, jika negatif akan digeser ke kanan
 */
void ShiftArrLeft(array *A, int n);
/**
 * Prosedur untuk menggeser semua elemen ke kanan sebanyak n kali. Akan
 * melakukan padding elemen di depan. Elemen untuk padding idealnya adalah 0
 * atau apapun yang diisi dengan hanya PadVal, tapi bebas ditentukan saat
 * implementasi. Kalau n lebih kecil dari elemeen maksimum akan menambah
 * properti NbEl sebanyak n, selain itu akan dilakukan pengisian array dengan
 * elemen padding, sehingga NbEl-nya sama dengan MaxEl-nya.
 *
 * Array *A - pointer ke array yang ingin digeser
 * unsigned n - banyak pergeseran, jika negatif akan digeser ke kiri
 */
void ShiftArrRight(array *A, int n);

/**
 * Fungsi untuk melakukan sorting/pengurutan
 *
 * array *A - pointer ke array yang ingin di-sort
 * boolean asc - jika true, array di-sort secara ascending, jika false
 * descending
 */
void SortArr(array *A, boolean asc);

/**
 * Fungsi untuk menyalin A1
 *
 * array A1 - array yang ingin disalin
 * Returns array salinan A1
 */
array CopyArr(array A1);

/**
 * Prosedur untuk menuliskan isi array
 *
 * array A - array yang ingin diprint
 */
void PrintArr(array A);

#endif
