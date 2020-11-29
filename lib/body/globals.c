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

void __isiPlayerResources() {
	playerResources.uang = START_MONEY;
	CreateArray(&playerResources.materials, MAX_MATERIAL);

	for (int i = 0; i < BuyableMaterials.NbEl; ++i) {
		Material *mater = (Material *) malloc(sizeof(Material));
		if (mater == NULL) {
			printf("bruh moment");
			exit(69);
		}
		ArrayElType el;

		mater->biayaMaterial = ((Material *) BuyableMaterials.arr[i].metadata)->biayaMaterial;
		mater->idMaterial = ((Material *) BuyableMaterials.arr[i].metadata)->idMaterial;
		mater->jumlahMaterial = 0;
		SalinKataDariKe(((Material *) BuyableMaterials.arr[i].metadata)->namaMaterial, &(mater->namaMaterial));

		el.id = mater->idMaterial;
		el.info = mater->biayaMaterial;
		el.metadata = mater;

		InsArrLast(&playerResources.materials, el);
	}
}

void init() {
	FILE *f;
	CreateEmptyStack(&actionStack);

	CreateArray(&DoableActions, BANYAK_AKSI);
	__isiDoableActions();

	CreateArray(&BuiltWahana, MAX_WAHANA);
	CreateArray(&toBeBuiltWahana, MAX_WAHANA);
	CreateArray(&AvailableWahana, MAX_WAHANA);
	CreateArray(&BuyableMaterials, MAX_MATERIAL);

	currentJam = MakeJAM(21, 0, 0);
	OpeningJam = MakeJAM(9, 0, 0);

	/* inisiasi map1 */
	f = fopen("data/map1.txt", "r");
	StartParser(f);
	map1 = ParserMap(1);
	fclose(f);

	/* inisiasi map2 */
	f = fopen("data/map2.txt", "r");
	StartParser(f);
	map2 = ParserMap(2);
	fclose(f);

	/* inisiasi map3 */
	f = fopen("data/map3.txt", "r");
	StartParser(f);
	map3 = ParserMap(3);
	fclose(f);

	/* inisiasi map4 */
	f = fopen("data/map4.txt", "r");
	StartParser(f);
	map4 = ParserMap(4);
	fclose(f);

	InitiateMap(); /* Initiate data peta lainnya */

	f = fopen("./data/materials.txt", "r");
	StartParser(f);
	BuyableMaterials = ReadMaterialArray();
	fclose(f);

	f = fopen("./data/wahana.txt", "r");
	StartParser(f);
	AvailableWahana = ReadTreeArray();
	fclose(f);

	__isiPlayerResources();
}
