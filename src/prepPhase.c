#include "prepPhase.h"
#include "../lib/header/wahana.h"
#include "../lib/header/stacklist.h"
#include "../lib/header/globals.h"
#include "../lib/header/resources.h"
#include <stdio.h>

void Execute(){
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
				ExecBuild((ATangibleWahana)t);
				break;
			case UPGRADE:
				// execute upgrade;
				ExecUpgrade((WahanaUpgradeStack)t);
				break;
			case BUY:
				// execute buy;
				ExecBuy(*(actBuy *)t);
				break;
		}
		// The time is already taken account of, don't need to check
	}
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

	el.id = Wahana->upgradeInfo.id;
	el.info = 0;
	el.metadata = w;

	InsArrLast(&toBeBuiltWahana, el);

	DurasiAksi(prop) = DetikToJAM(DoableActions.arr[BUILD].info);
	IdAksi(prop) = BUILD;
	Push(&actionStack, (void *) w, prop);
}
void ExecBuild(ATangibleWahana Wahana){
	// Store ATangibleWahana somehow
	// Do not free ATangibleWahana, because we need it.
	ArrayElType el;
	el = DelArrLast(&toBeBuiltWahana);
	InsArrLast(&BuiltWahana, el);
}

void UpgradeWahana(ATangibleWahana T, unsigned char id){
	WahanaUpgradeStack s;
	s = (WahanaUpgradeStack)malloc(sizeof(WahanaUpgradeInfo));
	TangibleWahana(s) = T;
	UpgradeID(s) = id;
	/*return s;*/
}
void ExecUpgrade(WahanaUpgradeStack Upgrade){
	// do stuff
	// free WahanaUpgradeStack: avoid memory leak!
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

void ExecBuy(actBuy aB) {
	/*Kata asd = getMaterialName(aB.id);*/
	Material *mater = getMaterialByID(BuyableMaterials, aB.id);
	int harga, i = 0;

	/* Akan mencari indeks di mana ditemukan material dengan nama sesuai
	 * variabel `asd` pada playerResources */
	for (; !IsKataSama(mater->namaMaterial, ((Material *) playerResources.materials.arr[i].metadata)->namaMaterial); ++i);
	((Material *) playerResources.materials.arr[i].metadata)->jumlahMaterial += aB.qty;

	harga = playerResources.materials.arr[i].info;
	playerResources.uang -= harga * aB.qty;
}

void ToMainPhase(){
	// Go to main phase
	// Pop items from stack, do not execute any
	StackInfoType t;
	PropertiAksi p;
	while(!IsStackEmpty(actionStack)){
		Pop(&actionStack, &t, &p);
	}
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
			/**totalUangAksi += Akar((WahanaTree) AvailableWahana.arr[idxWahana].metadata).UpgradeCost.uang;*/
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
			/*UpgradeWahana(wahanaTerdekat, L->upgradeInfo.id);*/
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
			/*UpgradeWahana(wahanaTerdekat, R->upgradeInfo.id);*/
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

		/* Kalo bisa */
		BuyResource(qty, materialID, boughtMaterial->biayaMaterial);
		(*totalAksi)++;
		*totalDetikAksi += DoableActions.arr[BUY].info;
		totalResourceAksi->uang += qty * boughtMaterial->biayaMaterial;
	} else {
		puts("Gagal membeli material karena jumlah pembelian tidak valid atau karena material tidak ada.");
	}
}

void ExecuteBuy(Material M){
}

void Undo(unsigned *totalAksi, long *totalDetikAksi, Resource *totalResourceAksi) {
	// Undo Logic
	UndoData data;

	Pop(&actionStack, (StackInfoType) &data.infoAksi, &data.prop);

	if (*totalAksi == 0) {
		puts("Tidak ada aksi yang dapat diurungkan");
	} else {
		ATangibleWahana infoTangibleWahana;
		actBuy *infoBuyMaterial;

		(*totalAksi)--;
		*totalDetikAksi -= JAMToDetik(data.prop.durasiAksi);

		switch (data.prop.idAksi) {
			case BUILD:
				infoTangibleWahana = (ATangibleWahana) data.infoAksi;

				Resource *temp = (Resource *) malloc(sizeof(Resource));
				KurangDuaResource(*totalResourceAksi, ((ATangibleWahana) data.infoAksi)->baseTree->upgradeInfo.UpgradeCost, temp);
				*totalResourceAksi = *temp;

				DelArrLast(&toBeBuiltWahana);

				free(temp);
				break;
			case UPGRADE:
				break;
			case BUY:
				infoBuyMaterial = (actBuy *) data.infoAksi;
				totalResourceAksi->uang -= infoBuyMaterial->qty * infoBuyMaterial->harga;
				break;
		}
	}
}
