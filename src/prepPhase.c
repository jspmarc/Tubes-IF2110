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
				ExecBuy(*(actBuy *)t, &DurasiAksi(prop));
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

void Build(unsigned *totalAksi, int *totalUangAksi, long *totalDetikAksi){
	Kata Wahana;
	int idxWahana;
	// Build Logic

	if (BuiltWahana.NbEl == AvailableWahana.NbEl) {
		puts("Kamu sudah membangun semua wahana yang mungkin pada permainan ini.");
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
		/* *** RENDER WAHANA DI PETA *** */
		/* Yg skrg boleh diapus aja */
		MAP currentMap;

		currentMap = WhichMap(crrntMapID);
		if (Ordinat(BeforeY(playerPos)) != 0) {
			/* Render tulisan W */
			Ordinat(playerPos)--;
		} else if (Absis(BeforeX(playerPos)) != 0) {
			/* Render tulisan W */
			Absis(playerPos)--;
		} else if (Ordinat(NextY(playerPos)) == Ordinat(currentMap.MapSize)+1) {
			/* Render tulisan W */
			Ordinat(playerPos)++;
		} else {}
		/* *** END RENDER WAHANA DI PETA *** */

		/* Cek bisa bangun wahana atau nggak */

		/* Kalo bisa bangun */
		BuildWahana((WahanaTree) AvailableWahana.arr[idxWahana].metadata, playerPos);
		(*totalAksi)++;
		*totalDetikAksi += DoableActions.arr[BUILD].info;
		*totalUangAksi += Akar((WahanaTree) AvailableWahana.arr[idxWahana].metadata).UpgradeCost.uang;
	}
}

void Upgrade(unsigned *totalAksi, int *totalUangAksi, long *totalDetikAksi){
	ATangibleWahana wahanaTerdekat;
	Kata Wahana;
	/* ATangibleWahana */
	array wahanaSekitarPlayer;
	addrNode upgradeBersangkutan;

	/* Nyariin wahana sekitar pemain */
	wahanaSekitarPlayer = WahanaSekitarPosisi(playerPos);

	/* Kalau wahana sekitar pemain ada lebih dari 1 */
	if (wahanaSekitarPlayer.NbEl > 1) {
		int idxWahana;
		puts("Mau berinteraksi dengan wahana apa?");
		/* Ngeprint nama wahana */
		for (int i = 0; i < wahanaSekitarPlayer.NbEl; ++i) {
			Kata namaWahana;
			int wahanaUpgradeId = ((ATangibleWahana) wahanaSekitarPlayer.arr[i].metadata)->currentUpgradeID;

			/* Dicari yang cocok upgradenya */
			upgradeBersangkutan = cariUpgrade(((ATangibleWahana) wahanaSekitarPlayer.arr[i].metadata)->baseTree, wahanaUpgradeId);

			SalinKataDariKe(upgradeBersangkutan->upgradeInfo.nama, &namaWahana);
			printf("  -");
			TulisKataKe(namaWahana, stdout);
		}
		printf("\n❯ ");
		/* Ngebaca wahana yang mau diupgrade */
		IgnoreBlank();
		ADVKATA();
		SalinKataKe(&Wahana);

		for (idxWahana = 0; idxWahana < wahanaSekitarPlayer.NbEl; ++idxWahana) {
			upgradeBersangkutan = cariUpgrade(((ATangibleWahana) wahanaSekitarPlayer.arr[idxWahana].metadata)->baseTree, ((ATangibleWahana) wahanaSekitarPlayer.arr[idxWahana].metadata)->currentUpgradeID);

			if (IsKataSama(upgradeBersangkutan->upgradeInfo.nama, Wahana)) break;
		}

		if (idxWahana == wahanaSekitarPlayer.NbEl) puts("Tidak ada wahana dengan nama itu di sekitarmu.");
	} else if (wahanaSekitarPlayer.NbEl < 1) {
		puts("Tidak ada wahana di sekitarmu yang bisa diupgrade.");
	} else { /* wahanaSekitarPlayer.NbEl == 1 */
		upgradeBersangkutan = cariUpgrade(((ATangibleWahana) wahanaSekitarPlayer.arr[0].metadata)->baseTree, ((ATangibleWahana) wahanaSekitarPlayer.arr[0].metadata)->currentUpgradeID);
	}

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

	printf("\n❯ ");
	/* Ngebaca wahana yang mau diupgrade */
	IgnoreBlank();
	ADVKATA();
	SalinKataKe(&Wahana);
}

void Buy(unsigned *totalAksi, int *totalUangAksi, long *totalDetikAksi){
	// Buy Logic
	/* Jangan lupa tambah durasi dan uang */
	/*BuyResource();*/
	Kata input,
		 splitInput[2],
		 namaMaterial;
	int qty;
	Material boughtMaterial;

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
	for (int i = 0; i < BuyableMaterials.NbEl && !found; ++i) {
		Material curMater = *((Material *) BuyableMaterials.arr[i].metadata);
		if (IsKataSama(curMater.namaMaterial, namaMaterial)) {
			found = true;
			boughtMaterial = curMater;
		}
	}

	/* Nge-parse Kata ke int */
	qty = 0;
	for (int i = 0; i < splitInput[0].Length && found; ++i) {
		int addVal = splitInput[0].TabKata[i] - '0';
		qty *= 10;

		if (addVal > 9 || addVal < 0) {
			qty = -1;
			break;
		} else qty += addVal;
	}

	/* Dah siap buat dimasukin ke actionStack, tinggal dicek aja
	 * resource player cukup buat beli atau nggak */
	int materialID = boughtMaterial.idMaterial;
	if (qty != -1 && found) {
		materialID = getMaterialId(namaMaterial);

		/* Ngecek bisa beli atau nggak */

		/* Kalo bisa */
		BuyResource(qty, materialID, boughtMaterial.biayaMaterial);
		(*totalAksi)++;
		*totalDetikAksi += DoableActions.arr[BUY].info; /* TODO: Harusnya dependant sama DoableActions */
		*totalUangAksi += qty * boughtMaterial.biayaMaterial;
	} else {
		puts("Gagal membeli material karena jumlah pembelian tidak valid atau karena material tidak ada.");
	}
}

void ExecuteBuy(Material M){
}

void Undo(unsigned *totalAksi, int *totalUangAksi, long *totalDetikAksi) {
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
				*totalUangAksi -= TreeWahana(infoTangibleWahana)->upgradeInfo.UpgradeCost.uang;
				break;
			case UPGRADE:
				break;
			case BUY:
				infoBuyMaterial = (actBuy *) data.infoAksi;
				*totalUangAksi -= infoBuyMaterial->qty * infoBuyMaterial->harga;
				break;
		}
	}
}
