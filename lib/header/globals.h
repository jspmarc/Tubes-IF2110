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

/* List ID aksi: (Prep phase)
 * ID   -   Aksi
 * 1    -   Build
 * 2    -   Upgrade
 * 3    -   Buy
 * 4    -   Undo
 * 5    -   Execute
 * 6    -   Main (play)
*/

/* State */
extern Stack actionStack;
extern Queue antrianCustomer;
extern Resource playerResources;
extern JAM currentJam;
extern Kata Nama;
extern array BuiltWahana; /* Menyimpan wahana yang sudah dibuat, array of TangibleWahana. */

/* Data */
extern array DoableActions; /* Nyimpen array of struct aksi */
extern array BuyableMaterials; /* Nyimpen array of struct material */
extern array AvailableWahana; /* Nyimpen array of struct wahana */
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
