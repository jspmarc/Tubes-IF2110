#include "prepPhase.h"
#include "../lib/header/wahana.h"
#include "../lib/header/stacklist.h"
#include "../lib/header/globals.h"
#include "../lib/header/resources.h"
#include <stdio.h>

void Execute(Resource *totalResourceAksi){
	// Do execute stuff
	// Pop from Stack then pop some more?
	Stack A;
	StackInfoType t;
	PropertiAksi prop;

	// Step 1. reverse the order
	CreateEmptyStack(&A);
	while(!IsStackEmpty(actionStack)){
		Pop(&actionStack, &t, &prop);
		Push(&A, t, prop);
	}

	// Step 2. execute them 1-by-1
	while(!IsStackEmpty(A)){
		Pop(&A, &t, &prop);
		switch(IdAksi(prop)){
			case BUILD:
				// execute build;
				ExecBuild((ATangibleWahana)t, totalResourceAksi);
				break;
			case UPGRADE:
				// execute upgrade;
				ExecUpgrade((WahanaUpgradeStack)t, totalResourceAksi);
				break;
			case BUY:
				// execute buy;
				ExecBuy(*(actBuy *)t, totalResourceAksi);
				break;
		}
		// The time is already taken account of, don't need to check
	}

	ToMainPhase();
}

void BuildWahana(WahanaTree Wahana, Point Loc) {
	ATangibleWahana w;
	PropertiAksi prop;
	ArrayElType el;

	w = (ATangibleWahana) malloc(sizeof(TangibleWahana));
	IDMap(w) = crrntMapID; // Menyimpan id-map player saat ini
	WahanaPoint(w) = Loc;
	TreeWahana(w) = Wahana;
	UpgradeId(w) = Wahana->upgradeInfo.id;
	w->status = true;
	w->used = 0;
	w->usedTotal = 0;

	el.id = Wahana->upgradeInfo.id;
	el.info = 0;
	el.metadata = w;

	InsArrLast(&toBeBuiltWahana, el);

	DurasiAksi(prop) = DetikToJAM(DoableActions.arr[BUILD].info);
	IdAksi(prop) = BUILD;
	Push(&actionStack, (void *) w, prop);
}
void ExecBuild(ATangibleWahana Wahana, Resource *totalResourceAksi){
	ArrayElType el;
	Resource *tempResource = (Resource  *) malloc(sizeof(Resource));

	/* Pindahin dari array toBeBuiltWahana ke BuiltWahana */
	el = DelArrLast(&toBeBuiltWahana);
	InsArrLast(&BuiltWahana, el);

	/* Kurangi resource player */
	KurangDuaResource(playerResources, ((ATangibleWahana) el.metadata)->baseTree->upgradeInfo.UpgradeCost, tempResource);
	playerResources = *tempResource;

	free(tempResource);
}

void UpgradeWahana(ATangibleWahana T, unsigned int id){
	WahanaUpgradeStack s;
	s = (WahanaUpgradeStack)malloc(sizeof(WahanaUpgradeInfo));
	TangibleWahana(s) = T;
	UpgradeID(s) = id;

	PropertiAksi prop;
	prop.durasiAksi = DetikToJAM(DoableActions.arr[UPGRADE].info);
	prop.idAksi = UPGRADE;

	Push(&actionStack, s, prop);
}
void ExecUpgrade(WahanaUpgradeStack Upgrade, Resource *totalResourceAksi){
	// do stuff
	// free WahanaUpgradeStack: avoid memory leak!
	int id = UpgradeID(Upgrade);
	ATangibleWahana TW = TangibleWahana(Upgrade);
	Resource cost = Akar(SearchUpgrade(TW->baseTree, id)).UpgradeCost;
	TW->currentUpgradeID = id;
	Resource *temp = (Resource *)malloc(sizeof(Resource));
	KurangDuaResource(playerResources, cost, temp);
	playerResources = *temp;
	free(temp);
	free(Upgrade);
}

void BuyResource(int qty, char unsigned materialID, int harga) {
	actBuy *a;
	a = (actBuy *) malloc(sizeof(actBuy));
	a->qty = qty; /* Banyak pembelian */
	a->harga = harga;
	a->id = materialID; /* nama dari barang yang dibeli (tipe data kata) */

	PropertiAksi prop;
	prop.durasiAksi = DetikToJAM(DoableActions.arr[BUY].info);
	prop.idAksi = BUY;

	Push(&actionStack, a, prop);
}

void ExecBuy(actBuy aB, Resource *totalResourceAksi) {
	Material *mater = getMaterialByID(BuyableMaterials, aB.id);
	int harga, i = 0;

	/* Akan mencari indeks di mana ditemukan material dengan nama sesuai
	 * variabel `mater` pada playerResources */
	for (; !IsKataSama(mater->namaMaterial, ((Material *) playerResources.materials.arr[i].metadata)->namaMaterial); ++i);
	((Material *) playerResources.materials.arr[i].metadata)->jumlahMaterial += aB.qty;

	harga = playerResources.materials.arr[i].info;
	/*playerResources.uang -= harga * aB.qty;*/
	
	Resource *tampung = (Resource *) malloc(sizeof(Resource)),
			 *temp = (Resource *) malloc(sizeof(Resource));
	tampung->uang = harga * aB.qty;
	CreateArray(&tampung->materials, MAX_MATERIAL);
	tampung->materials.arr[0].metadata = (Material *) malloc(sizeof(Material));
	*((Material *) tampung->materials.arr[0].metadata) = *mater;

	((Material *) tampung->materials.arr[0].metadata)->jumlahMaterial = aB.qty;
	KurangDuaResource(playerResources, *tampung, temp);

    playerResources = *temp;
}

void ToMainPhase(){
	// Go to main phase
	// Pop items from stack, do not execute any
	StackInfoType t;
	PropertiAksi p;
	while(!IsStackEmpty(actionStack)){
		Pop(&actionStack, &t, &p);
	}
	currentJam = MakeJAM(9, 0, 0);
}

void Save(){
	// Save state, something something hard to do
}

void Build(unsigned *totalAksi, long *totalDetikAksi, Resource *totalResourceAksi){
	Kata Wahana;
	int idxWahana;
	boolean bisaBangun = true;
	MAP map = WhichMap(crrntMapID);
	// Build Logic

	/* Cek bisa bangun atau nggak secara geografis */
	bisaBangun = bisaBangun
	&& !isNutupinGate(playerPos)
	&& PointNEQ(map.Office, playerPos)
	&& PointNEQ(map.Antrian, playerPos);

	if (BuiltWahana.NbEl == AvailableWahana.NbEl) {
		puts("Kamu sudah membangun semua wahana yang mungkin pada permainan ini.");
		return;
	}
	if (!bisaBangun) {
		puts("Tidak dapat membangun di posisi ini.");
		return;
	}
	
	printf("Ingin membangun apa?\nList:\n");
	for (int i = 0; i < AvailableWahana.NbEl; ++i) {
		printf("  - ");
		TulisKataKe(Akar((WahanaTree) AvailableWahana.arr[i].metadata).nama, stdout);
		puts("");
	}
	printf("\n❯ ");
	/* Ngebaca wahana yang mau dibangun */
	IgnoreBlank();
	ADVKATA();
	SalinKataKe(&Wahana);

	/* Nyari elemen dari array AvailableWahana */
	for (idxWahana = 0;
		idxWahana < AvailableWahana.NbEl && !IsKataSama(Akar((WahanaTree) AvailableWahana.arr[idxWahana].metadata).nama, Wahana);
		++idxWahana);

	/* The ugly parts */
	if (idxWahana >= AvailableWahana.NbEl) {
		puts("Wahana itu tidak ada dan tidak nyata");
	} else {
		/* Cek bisa bangun wahana atau nggak */

		/* Secara resource */
		Resource *resourceSetelahBerubah;
		resourceSetelahBerubah = (Resource *) malloc(sizeof(Resource));
		if (resourceSetelahBerubah == NULL) {
			puts("Bruh moment");
			exit(69);
		}
		TambahDuaResource(*totalResourceAksi, ((WahanaTree) AvailableWahana.arr[idxWahana].metadata)->upgradeInfo.UpgradeCost, resourceSetelahBerubah);
		bisaBangun = IsResourcesEnough(playerResources, *resourceSetelahBerubah);

		/* Bangunan udah dibangun */
		boolean udahDibangun = false;
		for (int i = 0; i < BuiltWahana.NbEl; ++i) {
			udahDibangun = IsKataSama((((ATangibleWahana) BuiltWahana.arr[i].metadata)->baseTree)->upgradeInfo.nama, Wahana);
		}
		for (int i = 0; i < toBeBuiltWahana.NbEl; ++i) {
			udahDibangun = IsKataSama((((ATangibleWahana) toBeBuiltWahana.arr[i].metadata)->baseTree)->upgradeInfo.nama, Wahana);
		}
		bisaBangun = bisaBangun && !udahDibangun;

		if (bisaBangun) {
			/* Kalo bisa bangun */
			BuildWahana((WahanaTree) AvailableWahana.arr[idxWahana].metadata, playerPos);
			(*totalAksi)++;
			*totalDetikAksi += DoableActions.arr[BUILD].info;
			*totalResourceAksi = *resourceSetelahBerubah;
		} else if (udahDibangun) {
			puts("Wahana sudah pernah dibangun.");
		} else {
			puts("Tidak dapat membangun karena material atau uang mu kurang.");
		}

		free(resourceSetelahBerubah);
	}
}

void Upgrade(unsigned *totalAksi, long *totalDetikAksi, Resource *totalResourceAksi){
	ATangibleWahana wahanaTerdekat;
	WahanaTree upgradeBersangkutan;
	Kata Wahana;

	wahanaTerdekat = InteraksiWahanaSekitarPosisi(playerPos);
	if (wahanaTerdekat == NULL) return;
	upgradeBersangkutan = cariUpgrade(wahanaTerdekat->baseTree, wahanaTerdekat->currentUpgradeID);


	/* List Upgrade */
	addrNode L = Left(upgradeBersangkutan),
			 R = Right(upgradeBersangkutan);

	printf("Ingin melakukan upgrade apa?\n");

	if (L != NULL) {
		printf(" - ");
		TulisKataKe(L->upgradeInfo.nama, stdout);
		puts("");
	}
	if (R != NULL) {
		printf(" - ");
		TulisKataKe(R->upgradeInfo.nama, stdout);
		puts("");
	}
	if (L == NULL && R == NULL) {
		puts("Wahana ini sudah tidak bisa diupgrade.");
		return;
	}

	printf("\n❯ ");
	/* Ngebaca wahana yang mau diupgrade */
	IgnoreBlank();
	ADVKATA();
	SalinKataKe(&Wahana);

	if (IsKataSama(L->upgradeInfo.nama, Wahana)) {
		boolean bisaBangun = true;
		/* Cek resource cukup atau nggak */

		/* Secara resource */
		Resource *resourceSetelahBerubah;
		resourceSetelahBerubah = (Resource *) malloc(sizeof(Resource));
		TambahDuaResource(*totalResourceAksi, L->upgradeInfo.UpgradeCost, resourceSetelahBerubah);
		bisaBangun = IsResourcesEnough(playerResources, *resourceSetelahBerubah);

		if (bisaBangun) {
            UpgradeWahana(wahanaTerdekat, L->upgradeInfo.id);
			(*totalAksi)++;
			*totalDetikAksi += DoableActions.arr[UPGRADE].info;
			Resource *temp = (Resource *) malloc(sizeof(Resource));
			TambahDuaResource(*totalResourceAksi, L->upgradeInfo.UpgradeCost, temp);
			*totalResourceAksi = *temp;
			free(temp);
		} else {
			puts("Resource tidak cukup untuk upgrade.");
		}

		free(resourceSetelahBerubah);
	} else if (IsKataSama(R->upgradeInfo.nama, Wahana)) {
		boolean bisaBangun = true;
		/* Cek resource cukup atau nggak */

		/* Secara resource */
		Resource *resourceSetelahBerubah;
		resourceSetelahBerubah = (Resource *) malloc(sizeof(Resource));
		TambahDuaResource(*totalResourceAksi, L->upgradeInfo.UpgradeCost, resourceSetelahBerubah);
		bisaBangun = IsResourcesEnough(playerResources, *resourceSetelahBerubah);

		if (bisaBangun) {
			UpgradeWahana(wahanaTerdekat, R->upgradeInfo.id);
			(*totalAksi)++;
			*totalDetikAksi += DoableActions.arr[UPGRADE].info;
			Resource *temp = (Resource *) malloc(sizeof(Resource));
			TambahDuaResource(*totalResourceAksi, L->upgradeInfo.UpgradeCost, temp);
			*totalResourceAksi = *temp;
			free(temp);
		} else {
			puts("Resource tidak cukup untuk upgrade.");
		}

		free(resourceSetelahBerubah);
	} else {
		puts("Masukkan tidak valid.");
	}
}

void Buy(unsigned *totalAksi, long *totalDetikAksi, Resource *totalResourceAksi){
	// Buy Logic
	/* Jangan lupa tambah durasi dan uang */
	/*BuyResource();*/
	Kata input,
		 splitInput[2],
		 namaMaterial;
	int qty;
	Material *boughtMaterial;

	printf("Ingin membeli apa?\nList:\n");
	for (int i = 0; i < BuyableMaterials.NbEl; ++i) {
				printf("  - ");
				TulisKataKe(((Material*) BuyableMaterials.arr[i].metadata)->namaMaterial, stdout);
		printf("\n");
	}
	printf("\n❯ ");
	/* Ngebaca material yang mau dibeli */
	IgnoreBlank();
	ADVKATA();
	SalinKataKe(&input);

	/* Nge-split input jadi quantity dan nama material */
	int j = 0, k = 0;
	char C = input.TabKata[k];
	while (j < 2) {
		int i = 0;
		while (C != ' ' && C != '\0' && k < input.Length) {
			splitInput[j].TabKata[i++] = C;
			C = input.TabKata[++k];
		}
		splitInput[j].TabKata[i] = '\0';
		splitInput[j].Length = i;
		C = input.TabKata[++k];
		++j;
	}

	/* Nyocokin nama material dengan material yang ada di array of
	 * buyable materials */
	namaMaterial = splitInput[1];
	boolean found = false;
	boughtMaterial = getMaterialByName(BuyableMaterials, namaMaterial);

	found = boughtMaterial != NULL;
	if (!found) {
		puts("Material itu tidak dijual.");
		return;
	}

	/* Nge-parse Kata ke int */
	qty = 0;
	for (int i = 0; i < splitInput[0].Length && found; ++i) {
		int addVal = splitInput[0].TabKata[i] - '0';
		qty *= 10;

		if (addVal > 9 || addVal < 0) {
			qty = -1;
			puts("Jumlah pembelian tidak valid.");
			return;
		} else qty += addVal;
	}

	/* Dah siap buat dimasukin ke actionStack, tinggal dicek aja
	 * resource player cukup buat beli atau nggak */
	int materialID = boughtMaterial->idMaterial;
	if (qty != -1 && found) {
		/* Ngecek bisa beli atau nggak */

		if (playerResources.uang < totalResourceAksi->uang + boughtMaterial->biayaMaterial * qty) {
			puts("Gagal membeli karena uang tidak cukup.");
		} else {
			/* Kalo bisa */
			BuyResource(qty, materialID, boughtMaterial->biayaMaterial);
			(*totalAksi)++;
			*totalDetikAksi += DoableActions.arr[BUY].info;

			Resource Res, *pRes = (Resource *) malloc(sizeof(Resource));
			Res.uang = -(qty*boughtMaterial->biayaMaterial);
			CreateArray(&Res.materials, MAX_MATERIAL);
			Res.materials.arr[0].metadata = (Material *) malloc(sizeof(Material));
			*((Material *) Res.materials.arr[0].metadata) = *((Material *)boughtMaterial);
			((Material *) Res.materials.arr[0].metadata)->jumlahMaterial = qty;
			Res.materials.NbEl = 1;

			KurangDuaResource(*totalResourceAksi, Res, pRes);
			*totalResourceAksi = *pRes;

			free(pRes);
			free(Res.materials.arr[0].metadata);
		}
	} else {
		puts("Gagal membeli material karena jumlah pembelian tidak valid atau karena material tidak ada.");
	}
}

void ExecuteBuy(Material M){
}

void Undo(unsigned *totalAksi, long *totalDetikAksi, Resource *totalResourceAksi) {
	// Undo Logic
	UndoData data;

	if (*totalAksi == 0) {
		puts("Tidak ada aksi yang dapat diurungkan");
	} else {
		Pop(&actionStack, (StackInfoType) &data.infoAksi, &data.prop);

		ATangibleWahana infoTangibleWahana;
		actBuy *infoBuyMaterial;

		(*totalAksi)--;
		*totalDetikAksi -= JAMToDetik(data.prop.durasiAksi);

		Resource *temp, *perubahan;
		switch (data.prop.idAksi) {
			case BUILD:
				infoTangibleWahana = (ATangibleWahana) data.infoAksi;

				temp = (Resource *) malloc(sizeof(Resource));
				KurangDuaResource(*totalResourceAksi, ((ATangibleWahana) data.infoAksi)->baseTree->upgradeInfo.UpgradeCost, temp);
				*totalResourceAksi = *temp;

				DelArrLast(&toBeBuiltWahana);

				break;
			case UPGRADE:
				infoTangibleWahana = TangibleWahana((WahanaUpgradeStack) data.infoAksi);
				addrNode n = SearchUpgrade(infoTangibleWahana->baseTree, UpgradeID((WahanaUpgradeStack) data.infoAksi));
				temp = (Resource *)malloc(sizeof(Resource));
				KurangDuaResource(*totalResourceAksi, n->upgradeInfo.UpgradeCost , temp);
				*totalResourceAksi = *temp;
				break;
			case BUY:
				infoBuyMaterial = (actBuy *) data.infoAksi;
				/*totalResourceAksi->uang -= infoBuyMaterial->qty * infoBuyMaterial->harga;*/

				temp = (Resource *) malloc(sizeof(Resource));
				perubahan = (Resource *) malloc(sizeof(Resource));
				perubahan->uang = infoBuyMaterial->qty * infoBuyMaterial->harga * -1;
				CreateArray(&perubahan->materials, 1);
				perubahan->materials.arr[0].metadata = (Material *) malloc(sizeof(Material));
				*((Material *) perubahan->materials.arr[0].metadata) = *getMaterialByID(BuyableMaterials, infoBuyMaterial->id);
				((Material *) perubahan->materials.arr[0].metadata)->jumlahMaterial = infoBuyMaterial->qty;
				perubahan->materials.NbEl = 1;
				TambahDuaResource(*totalResourceAksi, *perubahan, temp);
				*totalResourceAksi = *temp;

				break;
		}
	free(temp);
	free((WahanaUpgradeStack) data.infoAksi);
	}
}
