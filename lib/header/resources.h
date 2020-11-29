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
Material *getMaterialByID(array source, char id);
Material *getMaterialByName(array source, Kata Nama);

/**
 * Fungsi untuk memeriksa apakah array of materials pada matYangMauDikurangi mencukupi
 * kebutuhan pada matPengurang
 */
boolean IsMaterialsEnough(array matYangMauDikurangi, array matPengurang);

/**
 * Fungsi untuk memeriksa apakah resource pada resYangMauDikurangi mencukupi
 * kebutuhan pada resPengurang
 */
boolean IsResourcesEnough(Resource resYangMauDikurangi, Resource resPengurang);

/**
 * FUngsi untuk menambahkan dua buah resource
 */
void TambahDuaResource(Resource res1, Resource res2, Resource *result);

/**
 * FUngsi untuk mengurangi res1 oleh res2
 */
void KurangDuaResource(Resource res1, Resource res2, Resource *result);

/**
 * Fungsi untuk menuliskan isi resource ke layar
 */
void PrintResource(Resource R);
#endif
