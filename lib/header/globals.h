#include "stacklist.h"
#include "resources.h"
#include "jam.h"
#include "point.h"
#include "prioqueuell.h"
#include "map.h"

#ifndef _GAME_GLOBAL_H
#define _GAME_GLOBAL_H

#define START_MONEY 300000
#define MAX_WAHANA 6
#define MAX_MATERIAL 5
#define MAX_ANTRIAN  10
#define MAX_QESABARAN 11
#define JUMLAH_MATERIAL_DAPAT_DIBELI 0x7fffffff

#define BANYAK_AKSI 10

/* List ID aksi: (Prep phase)
 * ID   -   Aksi
 * 1    -   Build
 * 2    -   Upgrade
 * 3    -   Buy
 * 4    -   Undo
 * 5    -   Execute
 * 6    -   Main (play)
 */
#define BUILD 1
#define UPGRADE 2
#define BUY 3

/* State */
extern Stack actionStack;
extern Queue antrianCustomer;
extern Resource playerResources;
extern JAM currentJam;
extern Kata Nama;
extern array BuiltWahana; /* Menyimpan wahana yang sudah dibuat, array of ATangibleWahana. */
extern array toBeBuiltWahana; /* array of ATangibleWahana */

/* Data */
extern array DoableActions; /* Nyimpen array of aksi */
extern array BuyableMaterials; /* Nyimpen array of struct Material */
extern array AvailableWahana; /* Nyimpen array of struct WahanaTree */
extern JAM OpeningJam;
extern JAM ClosingJam;

/* Map */
extern MAP map1;
extern MAP map2;
extern MAP map3;
extern MAP map4;

extern Point playerPos;
extern int crrntMapID;

extern Graph jaringanMap;

void init();

#endif
