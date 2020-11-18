/* File: wahana.h */
/* File header untuk ADT Wahana */

#include "./point.h"
#include "./jam.h"
#include "./upgradeWahana.h"

/* *** ADT Wahana *** */
/* Menyimpan struct untuk wahana, lalu fungsi dan prosedur seperti selektor,
 * konstruktor, dan lain-lain
 */

#ifndef WAHANA_H
#define WAHANA_H

/* tipe data wahana terdiri dari:
 *  - nama -> nama wahana (string)
 *  - deskripsi -> deskripsi wahana (string)
 *  - idTipe ->
 */
typedef struct {
    char* nama; /* string */
    char* deskripsi; /* string */
    unsigned char idTipe; /* angka */
    unsigned char durasi; /* angka, dalam menit */
    unsigned short kapasitas; /* angka */
    unsigned int harga; /* angka */
    Point ukuran; /*    (X: ukuran panjang, Y: ukuran lebar) */
    Point lokasi; /*    (X: lokasi di sepanjang sumbu X,
                        ;Y: lokasi di sepanjang sunbu Y) */
    UpgradeTree upgrade; /* Upgrade tree/path untuk wahana */
} wahana;

#endif
