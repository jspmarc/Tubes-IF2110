#include "mesinkata.h"
#include "jam.h"
#include "array.h"

#ifndef RESOURCES_H
#define RESOURCES_H

/* Spek (harga dan nama) material yg dpt dibeli */
typedef struct {
    unsigned char idMaterial;
    unsigned short biayaMaterial; /* Harga material */
    int jumlahMaterial; /* 0x7fffffff jika diakses saat akan dibeli, selain itu menggambarkan banyak material yg dimiliki */
    Kata namaMaterial; /* Nama material */
} Material;

typedef struct {
    int uang; /* Banyak uang yang dimiliki pemain */
    array materials; /* Array of Material, id material berkoresponden dengan index, klo ga punya bikin jumlah-nya jadi 0 */
} Resource;

typedef struct {
	int qty;
	int harga;
	unsigned char id;
} actBuy;

//unsigned char getMaterialId(Kata K);
//Kata getMaterialName(char id);
//unsigned short getMaterialPrice(char id);
Material *getMaterialByID(char id);
Material *getMaterialByName(Kata Nama);
#endif
