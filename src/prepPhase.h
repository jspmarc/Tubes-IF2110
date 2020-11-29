#include "../lib/header/wahana.h"
#include "../lib/header/stacklist.h"
#include "../lib/header/globals.h"
#include "../lib/header/resources.h"
#include <stdio.h>

#ifndef PREPPHASE_H
#define PREPPHASE_H

/* Strutkur data untuk mmebantu pemindahan data dari undo ke program utama */
typedef struct {
    PropertiAksi prop; /* Durasi untuk melakukan aksi yang di-undo */
    StackInfoType infoAksi; /* Info dari aksi yg diundo (pointer ke struct) */
} UndoData;

extern Stack actionStack;

void Execute();

void BuildWahana(WahanaTree Wahana, Point Loc);

void ExecBuild(ATangibleWahana Wahana, Resource *totalResourceAksi);

/**
 * Fungsi untuk mempersiapkan upgrade wahanna.
 * Pemain harus memilih upgrade ke daun kiri atau kanan.
 * Sama seperti build, tapi bkn mengambil simpul pertama, melainkan simpul
 * lainnya
 * Akan memasukkan aksi ini ke stackAksi (variabel global)
 *
 * Upgrade - WahanaUpgradeStack
 */
void UpgradeWahana(ATangibleWahana T, unsigned int id);
/**
 * Fungsi untuk mengeksekusi aksi upgrade dari stackAksi (variabel global)
 * Akan mengepop aksi ini dari stackAksi (variabel global)
 *
 * *Wahana - Wahana yang sudah dibangun
 * id - ID Node tree, bagian upgrade
 */
void ExecUpgrade(WahanaUpgradeStack Upgrad, Resource *totalResourceAksi);

void BuyResource(int qty, char unsigned materialID, int harga);

void ExecBuy(actBuy aB, Resource *totalResourceAksi);

void ToMainPhase();

void Save();

void Build(unsigned *totalAksi, long *totalDetikAksi, Resource *totalResourceAksi);

void Upgrade(unsigned *totalAksi, long *totalDetikAks, Resource *totalResourceAksi);

void Buy(unsigned *totalAksi, long *totalDetikAks, Resource *totalResourceAksi);

void ExecuteUpgrade();

void Undo(unsigned *totalAksi, long *totalDetikAks, Resource *totalResourceAksi);
#endif
