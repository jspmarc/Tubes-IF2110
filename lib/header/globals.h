#include "stacklist.h"
#include "resources.h"
#include "jam.h"
#include "point.h"
#include "prioqueuell.h"
#include "map.h"

#ifndef _GAME_GLOBAL_H
#define _GAME_GLOBAL_H

#define START_MONEY 100000
#define MAX_WAHANA 10 // 10 wahana should be enough, can be extended
#define MAX_MATERIAL 25
#define JUMLAH_MATERIAL_DAPAT_DIBELI 0x7fffffff

#define BANYAK_AKSI 15

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
#define SERVE 4

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
