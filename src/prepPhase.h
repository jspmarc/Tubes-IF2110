#include "../lib/header/wahana.h"
#include "../lib/header/stacklist.h"
#include "../lib/header/globals.h"
#include "../lib/header/resources.h"
#include <stdio.h>

#ifndef PREPPHASE_H
#define PREPPHASE_H

/* Strutkur data untuk mmebantu pemindahan data dari undo ke program utama */
typedef struct {
    JAM durasiAksi; /* Durasi untuk melakukan aksi yang di-undo */
    StackInfoType infoAksi; /* Info dari aksi yg diundo (pointer ke struct) */
} UndoData;

extern Stack actionStack;

void Execute();

void ToMainPhase();

void Save();

void BuildWahana(UpgradeType Wahana, Point Loc);

void ExecBuild(ATangibleWahana Wahana);

void Upgrade();

void ExecuteUpgrade();

UndoData Undo();
#endif
