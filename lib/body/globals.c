#include "../header/globals.h"
#include "../header/parser.h"

Stack actionStack;
Resource playerResources;
Kata Nama;
array BuiltWahana;
array wahanaFromFile;

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
	CreateArray(&wahanaFromFile, MAX_WAHANA);

	InitiateMap();

	f = fopen("test.txt", "r");
	StartParser(f);
	wahanaFromFile = ReadTreeArray();
	// TestTheMap();
}

