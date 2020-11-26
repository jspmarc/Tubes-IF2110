#include "../lib/header/wahana.h"
#include "../lib/header/stacklist.h"
#include "../lib/header/globals.h"
#include "../lib/header/resources.h"
#include <stdio.h>

#ifndef PREPPHASE_H
#define PREPPHASE_H

extern Stack actionStack;

void Execute();

void ToMainPhase();

void Save();

void BuildWahana(UpgradeType Wahana, Point Loc);

void ExecBuild(ATangibleWahana Wahana);

void Upgrade();

void ExecuteUpgrade();

void Undo();
#endif
