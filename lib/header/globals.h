#include "stacklist.h"
#include "resources.h"
#include "jam.h"
#include "point.h"
#include "prioqueuell.h"

#ifndef _GAME_GLOBAL_H
#define _GAME_GLOBAL_H

#define START_MONEY 100000;

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
extern Point playerPos;
extern int crrntMapID;
extern JAM currentJam;

/* Data */
extern array DoableActions; /* Nyimpen array of struct aksi */
extern array BuyableMaterials; /* Nyimpen array of struct material */
extern array AvailableWahana; /* Nyimpen array of struct wahana */

void init();

#endif
