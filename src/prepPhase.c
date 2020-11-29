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

void BuildWahana(UpgradeType Wahana, Point Loc) {
	ATangibleWahana w;
	PropertiAksi prop;
	ArrayElType el;
	w = (ATangibleWahana) malloc(sizeof(TangibleWahana));
	WahanaPoint(w) = Loc;
	TreeWahana(w) = Wahana;
	UpgradeId(w) = Wahana.id;

	el.id = Wahana.id;
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

	for (idxWahana = 0;
		idxWahana < AvailableWahana.NbEl && !IsKataSama(Akar((WahanaTree) AvailableWahana.arr[idxWahana].metadata).nama, Wahana);
		++idxWahana);

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
		BuildWahana(Akar((WahanaTree) AvailableWahana.arr[idxWahana].metadata), playerPos);
		(*totalAksi)++;
		*totalDetikAksi += DoableActions.arr[BUILD].info;
		*totalUangAksi += Akar((WahanaTree) AvailableWahana.arr[idxWahana].metadata).UpgradeCost.uang;
	}
}

void Upgrade(){
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
				*totalUangAksi -= TreeWahana(infoTangibleWahana).UpgradeCost.uang;
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
