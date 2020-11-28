#include "../header/globals.h"
#include "../header/parser.h"

/* State */
Stack actionStack;
Resource playerResources;
JAM currentJam;
Kata Nama;
array BuiltWahana;

/* Data */
array AvailableWahana;
JAM OpeningJam;
JAM ClosingJam;

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
	FILE *f;
	CreateEmptyStack(&actionStack);

	playerResources.uang = START_MONEY;
	CreateArray(&BuiltWahana, MAX_WAHANA);
	CreateArray(&AvailableWahana, MAX_WAHANA);

	currentJam = MakeJAM(21, 0, 0);
	OpeningJam = MakeJAM(9, 0, 0);

	InitiateMap();

	f = fopen("./data/wahana.txt", "r");
	StartParser(f);
	AvailableWahana = ReadTreeArray();
	// TestTheMap();
}

