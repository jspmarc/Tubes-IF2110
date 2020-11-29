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

void ExecBuild(ATangibleWahana Wahana);

void ToMainPhase();

void Save();

void Build(unsigned *totalAksi, int *totalUangAksi, long *totalDetikAksi);

void Upgrade(unsigned *totalAksi, int *totalUangAksi, long *totalDetikAksi);

void Buy(unsigned *totalAksi, int *totalUangAksi, long *totalDetikAksi);

void ExecuteUpgrade();

void Undo(unsigned *totalAksi, int *totalUangAksi, long *totalDetikAksi);
#endif
