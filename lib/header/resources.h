#include "mesinkata.h"

#ifndef RESOURCES_H
#define RESOURCES_H

#define BanyakMaterial 100

/* *** ADT resource *** */
/* ADT untuk resource yang dibutuhkan untuk membangun & mengupgrade
 * wahana serta ADT untuk menyimpan resource yang dimiliki pemain
 */

typedef struct {
    char* NamaMaterial;
    int harga;
} Material;

typedef struct {
    Material ListMaterial[BanyakMaterial]; /* List material */
    int uang; /* duit (aku mau kaya) */
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
