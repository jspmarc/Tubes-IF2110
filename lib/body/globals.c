#include "../header/globals.h"
#include "../header/parser.h"
#include "../header/resources.h"

/* State */
Stack actionStack;
Resource playerResources;
JAM currentJam;
Kata Nama;
array BuiltWahana;
array toBeBuiltWahana;

/* Data */
array DoableActions;
array AvailableWahana;
array BuyableMaterials;
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

void __isiDoableActions() {
	DoableActions.arr[0].id = 0x7fffffff;
	DoableActions.arr[0].info = 0x7fffffff;

	DoableActions.arr[BUILD].id = BUILD;
	DoableActions.arr[BUILD].info = JAMToDetik(MakeJAM(1, 0, 0));

	DoableActions.arr[UPGRADE].id = UPGRADE;
	DoableActions.arr[UPGRADE].info = JAMToDetik(MakeJAM(0, 30, 0));

	DoableActions.arr[BUY].id = BUY;
	DoableActions.arr[BUY].info = JAMToDetik(MakeJAM(0, 15, 0));
}

void init() {
	FILE *f;
	CreateEmptyStack(&actionStack);

	playerResources.uang = START_MONEY;

	CreateArray(&DoableActions, BANYAK_AKSI);
	__isiDoableActions();

	CreateArray(&BuiltWahana, MAX_WAHANA);
	CreateArray(&toBeBuiltWahana, MAX_WAHANA);
	CreateArray(&AvailableWahana, MAX_WAHANA);
	CreateArray(&BuyableMaterials, MAX_MATERIAL);

	currentJam = MakeJAM(21, 0, 0);
	OpeningJam = MakeJAM(9, 0, 0);

	InitiateMap();

	f = fopen("./data/wahana.txt", "r");
	StartParser(f);
	AvailableWahana = ReadTreeArray();
	fclose(f);

	f = fopen("./data/materials.txt", "r");
	StartParser(f);
	BuyableMaterials = ReadMaterialArray();
	fclose(f);
}

