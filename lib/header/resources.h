#include "mesinkata.h"

#ifndef RESOURCES_H
#define RESOURCES_H

#define hargaLogam 100
#define hargaNonLogam 50
#define hargaMetaloid 75

/* *** ADT resource *** */
/* ADT untuk resource yang dibutuhkan untuk membangun & mengupgrade
 * wahana serta ADT untuk menyimpan resource yang dimiliki pemain
 */

typedef struct {
    unsigned int uang; /* Uang yang dimiliki atau dibutuhkan */
    unsigned int logam; /* Material logam */
    unsigned int nonlogam; /* Material nonlogam */
    unsigned int metaloid; /* Material metaloid/semi-logam */
} Resource;

typedef struct {
    int qty_i; /* banyak barang yang dibeli */
    Kata K; /* barang yang dibeli */
} actBuy;


/**
 * Fungsi untuk membeli resource. Aksi akan ditambahkan ke stack.
 */
void BuyResource();

/**
 * Fungsi untuk mengeksekusi aksi pembelian
 *
 * *rP {Resource} - pointer ke struct resource pemain
 */
void ExecBuy(Resource *rP, actBuy aB);

#endif
