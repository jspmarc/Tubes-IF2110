/* FILE: mainPhase.c */

#include <stdio.h>
#include <stdlib.h>
#include "./../lib/header/boolean.h"
#include "./../lib/header/str.h"
#include "./../lib/header/prioqueuell.h"
#include "./../lib/header/jam.h"
#include "./../lib/header/wahana.h"
#include "./../lib/header/globals.h"
#include "./../lib/header/map.h"

#ifndef MAINPHASE_H
#define MAINPHASE_H

void RandomPengunjung();
/* Merandom pengunjung untuk simulasi main */
/* antrianCustomer sudah terisi sebanyak nPengunjung dengan kesabaran dan prioritas random dan listlinier berisi wahana yang ingin dinaiki */

void printUpgrade();
void printHistory();
ATangibleWahana bacaInputWahana();

/* Memakan waktu */
/* SERVE {input: type pengunjung, wahana, wahana.antrian} */
void SERVE();
/* Memakan waktu */
/* REPAIR {input: wahana} */
void REPAIR();
/* Tidak memakan waktu */
/* DETAIL {input: wahana} */
void DETAIL();
/* Tidak memakan waktu */
/* OFFICE {input: office} */
void OFFICE();
#endif
