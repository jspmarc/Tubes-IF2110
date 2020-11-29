#include "mesinkata.h"
#include "jam.h"
#include "array.h"

#ifndef RESOURCES_H
#define RESOURCES_H

#define MAX_MATERIAL 1000
#define JUMLAH_MATERIAL_DAPAT_DIBELI 0x7fffffff

#define LAMA_BELI 1800 

/* Spek (harga dan nama) material yg dpt dibeli */
typedef struct {
    unsigned char idMaterial;
    unsigned short biayaMaterial; /* Harga material */
    int jumlahMaterial; /* 0x7fffffff jika diakses saat akan dibeli, selain itu menggambarkan banyak material yg dimiliki */
    Kata namaMaterial; /* Nama material */
} Material;

typedef struct {
    int uang; /* Banyak uang yang dimiliki pemain */
    Material materials[MAX_MATERIAL]; /* Array of PlayerMaterial, id material berkoresponden dengan index, klo ga punya bikin jumlah-nya jadi 0 */
} Resource;

typedef struct {
	int qty;
	unsigned char id;
} actBuy;

unsigned char getMaterialId(Kata K);
Kata getMaterialName(char id);

void BuyResource(int qty, char unsigned materialID);
void ExecBuy(actBuy aB, JAM *curJam);
#endif
