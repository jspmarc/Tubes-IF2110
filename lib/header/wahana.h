/* File: wahana.h */
/* File header untuk ADT Wahana */

#include "./point.h"
#include "./jam.h"
#include "./upgradeWahana.h"
#include "./resources.h"

/* *** ADT Wahana *** */
/* Menyimpan struct untuk wahana, lalu fungsi dan prosedur seperti selektor,
 * konstruktor, dan lain-lain
 */

#ifndef WAHANA_H
#define WAHANA_H

/* tipe data wahana terdiri dari:
 *  - idTipe (1 byte integer, char) -> tipe wahana
 *  - durasi (1 byte integer, char) -> durasi menggunakan wahana
 *  - kapasitas (2 byte integer, short) -> kapasitas wahana
 *  - harga (int) -> harga untuk menaiki wahana
 *  - ukuran (Point) -> ukuran wahana
 *  - lokasi (Point) -> lokasi wahana
 *  - nama (String) -> nama wahana
 *  - deskripsi (String) -> deskripsi wahana
 *
 * di spek ada: `History Upgrade Wahana` itu kayaknya bakal dihandle fungsi
 */
typedef struct {
    unsigned char idTipe; /* tipe wahana (char) */
    unsigned char durasi; /* durasi menggunakan wahana, dalam menit (char) */
    unsigned short kapasitas; /* banyak pemain wahana (short) */
    unsigned int harga; /* harga maniki wahana (int) */
    Point ukuran; /*    (X: ukuran panjang, Y: ukuran lebar) (Point) */
    Point lokasi; /*    (X: lokasi di sepanjang sumbu X,
                        ;Y: lokasi di sepanjang sunbu Y) (Point) */
    UpgradeTree upgradePath; /* Upgrade tree/path untuk wahana (UpgradeTree) */
    char* nama; /* Nama wahana (string) */
    char* deskripsi; /* Deskripsi wahana (string) */
    boolean rideable; /* Kalo rusak ini jadi false (boolelan) */
} Wahana;

/**
 * Fungsi untuk membangun sebuah wahana.
 * Properti dan resource untuk build wahana ditentukan oleh tipe wahana.
 *
 * - *ResourcePemain (Resource) pointer ke resources yang dimiliki pemain
 * - idWahana (unsigned char) resources yang dibutuhkan untuk membangun
 * - durasiPembuatan (JAM) waktu yang dibutuhkan untuk membuat wahana
 */
Wahana BuildWahana(Resource *resourcePemain
                   , unsigned char idWahana
                   , JAM durasiPembuatan);

/**
 * Fungsi untuk mengupgrade sebuah wahana.
 * Upgrade akan menambah kapasitas wahana dan juga ukuran.
 * Resource yang dibutuhkan untuk upgrade akan ditentukan oleh tipe wahana.
 *
 * - *W (Wahana) pointer ke wahana yang ingin diupgrade
 * - *ResourcePemain (Resource) pointer ke resources yang dimiliki pemain
 * - ResourceDibutuhkan (Resource) resources yang dibutuhkan untuk mengupgrade
 * - durasiPembuatan (JAM) waktu yang dibutuhkan untuk mengupgrade wahana
 */
void UpgradeWahana(Wahana *W, Resource *resourcePemain, JAM durasiUpgrade);

void Break(Wahana *W);

void Repair(Wahana *W, Resource *resourcePemain, JAM durasiPerbaikan);

#endif
