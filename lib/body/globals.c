#include "../header/globals.h"

Stack actionStack;
Resource playerResources;
Kata Nama;
array BuiltWahana;

/* Map stuffs */
MAP map1;
MAP map2;
MAP map3;
MAP map4;

Point playerPos;
int crrntMapID;

Graph jaringanMap;
/* end of map stuffs */

void init() {
    CreateEmptyStack(&actionStack);

    playerResources.uang = START_MONEY;
    CreateArray(&BuiltWahana, 10); // 10 wahana should be enough, can be extended

    InitiateMap();
    // TestTheMap();
}

