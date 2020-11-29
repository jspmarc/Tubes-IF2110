/* ADT Upgrade Wahana */
/* Implementasi dengan menggunakan tree */
/* Untuk membeli wahana berarti kita mengambil node upgrade pertama */

#include "../header/wahana.h"
#include "../header/str.h"
#include "../header/map.h"
#include <stdlib.h>
#include <stdio.h>

WahanaTree Tree(UpgradeType Akar, WahanaTree L, WahanaTree R) {
	WahanaTree WT;

	WT = (WahanaTree) malloc(sizeof(UpNode));
	Akar(WT) = Akar;
	Left(WT) = L;
	Right(WT) = R;

	return WT;
}

void MakeTree(UpgradeType Akar, WahanaTree L, WahanaTree R, WahanaTree *P) {
	*P = Tree(Akar, L, R);
}

UpgradeType BuatSimpulKosong(unsigned int id){
	UpgradeType simpul;
	simpul.id = id;
	return simpul;
}

UpgradeType IsiSimpul(unsigned int id, unsigned short kapasitas, unsigned int harga,
			JAM durasi, Kata nama, Kata description, Resource upCost) {
	UpgradeType simpul;

	simpul.id = id;
	simpul.kapasitas = kapasitas;
	simpul.harga = harga;
	simpul.durasi = durasi;
	simpul.nama = nama;
	simpul.description = description;
	simpul.UpgradeCost = upCost;
	simpul.isTaken = false;

	return simpul;
}

void UbahIsiSimpul(WahanaTree *P, unsigned int id, unsigned short kapasitas, unsigned int harga,
			JAM durasi, Kata nama, Kata description, Resource upCost) {
	UpgradeType *simpul;

	simpul = &Akar(SearchUpgrade(*P, id));
	simpul->kapasitas = kapasitas;
	simpul->harga = harga;
	simpul->durasi = durasi;
	SalinKataDariKe(nama, &(simpul->nama));
	SalinKataDariKe(description, &(simpul->description));
	simpul->UpgradeCost = upCost;
	simpul->isTaken = false;
}

addrNode AlokasiNodeTree(UpgradeType UT) {
	addrNode node = (addrNode) malloc(sizeof(UpNode));

	Akar(node) = IsiSimpul(UT.id, UT.kapasitas, UT.harga, UT.durasi, UT.nama,
							UT.description, UT.UpgradeCost);
	Left(node) = NULL;
	Right(node) = NULL;

	return node;
}
void DealokasiNodeTree(addrNode P) {
	P = NULL;
	free(P);
}

boolean IsTreeEmpty(WahanaTree P) {
	return P == NULL;
}
boolean IsTreeOneElmt(WahanaTree P) {
	return P != NULL && Left(P) == NULL && Right(P) == NULL;
}
boolean IsUnerLeft(WahanaTree P) {
	return (!IsTreeEmpty(P) && ((Right(P) == NULL) && (Left(P) != NULL)));
}
boolean IsUnerRight(WahanaTree P) {
	return (!IsTreeEmpty(P) && ((Left(P) == NULL) && (Right(P) != NULL)));
}
boolean IsBiner(WahanaTree P) {
	return (!IsTreeEmpty(P) && (Left(P) != NULL && Right(P) != NULL));
}

void AddDaunTerkiri(WahanaTree *P, UpgradeType X) {
	if (IsTreeEmpty(*P)) {
		addrNode Pn = AlokasiNodeTree(X);
		*P = Pn;
	} else if (IsTreeOneElmt(*P)) {
		addrNode Pn = AlokasiNodeTree(X);
		Left(*P) = Pn;
	} else AddDaunTerkiri(&Left(*P), X);
}
void AddDaun(WahanaTree *P, UpgradeType X, UpgradeType Y, boolean Kiri) {
	if (( IsTreeOneElmt(*P)
			|| (Left(*P) == NULL && Right(*P) != NULL)
			|| (Left(*P) != NULL && Right(*P) == NULL)) && IsInfoNodeSame(Akar(*P), X)) {
		if (Kiri) Left(*P) = AlokasiNodeTree(Y);
		else Right(*P) = AlokasiNodeTree(Y);
	} else {
		if (SearchTree(Left(*P), X)) AddDaun(&Left(*P), X, Y, Kiri);
		else AddDaun(&Right(*P), X, Y, Kiri);
	}
}
void DelDaunTerkiri(WahanaTree *P, UpgradeType *X) {
	if (IsTreeOneElmt(*P)) {
		WahanaTree Pn = *P;
		*X = Akar(Pn);
		*P = NULL;
		DealokasiNodeTree(Pn);
	} else {
		if (IsUnerLeft(*P) && !IsTreeEmpty(Left(*P)))
			DelDaunTerkiri(&Left(*P), X);
		else if (IsUnerRight(*P) && !IsTreeEmpty(Right(*P)))
			DelDaunTerkiri(&Right(*P), X);
		else if (!IsTreeEmpty(Left(*P)))
			DelDaunTerkiri(&Left(*P), X);
		else if (!IsTreeEmpty(Right(*P)))
			DelDaunTerkiri(&Right(*P), X);
	}
}
void DelDaun(WahanaTree *P, UpgradeType X) {
	if (!IsTreeEmpty(*P)) {
		if (IsTreeOneElmt(*P) && IsInfoNodeSame(Akar(*P), X)) {
			*P = NULL;
			DealokasiNodeTree(*P);
		} else {
			DelDaun(&Left(*P), X);
			DelDaun(&Right(*P), X);
		}
	}
}

void PrintPreorder(WahanaTree P) {
		printf("(");
		if(!IsTreeEmpty(P)){
			/*TulisKataKe(Akar(P).nama, stdout);*/
			printf("%d", Akar(P).id);
			PrintPreorder(Left(P));
			PrintPreorder(Right(P));
		}
		printf(")");
}
void PrintInorder(WahanaTree P) {
		printf("(");
		if(!IsTreeEmpty(P)){
			PrintPreorder(Left(P));
			TulisKataKe(Akar(P).nama, stdout);
			PrintPreorder(Right(P));
		}
		printf(")");
}
void PrintPostorder(WahanaTree P) {
		printf("(");
		if(!IsTreeEmpty(P)){
			PrintPreorder(Left(P));
			PrintPreorder(Right(P));
			TulisKataKe(Akar(P).nama, stdout);
		}
		printf(")");
}
void PrintIndent(WahanaTree P, int h, int Depth) {
	if (IsTreeEmpty(P)); /* do nothing */
	else {
		TulisKataKe(Akar(P).nama, stdout);
		printf("\n");
	}
	if(!IsTreeOneElmt(P)) {
		if (!IsTreeEmpty(Left(P))) {
			fprintf(stdout, "%*s", h+(h*Depth), "");
			PrintIndent(Left(P), h, Depth+1);
		}
		if (!IsTreeEmpty(Right(P))) {
			fprintf(stdout, "%*s", h+(h*Depth), "");
			PrintIndent(Right(P), h, Depth+1);
		}
	}
}
void PrintTree(WahanaTree P, int h) {
	PrintIndent(P, h, 0);
}

boolean SearchTree(WahanaTree P, UpgradeType X) {
	if (IsTreeEmpty(P)) return false;
	else {
		if (IsInfoNodeSame(Akar(P), X)) return true;
		else return SearchTree(Left(P), X) || SearchTree(Right(P), X);
	}
}

addrNode SearchUpgrade(WahanaTree P, unsigned int id){
	addrNode R;
	if(IsTreeEmpty(P)) return NULL;
	if(Akar(P).id == id) return P;
	R = SearchUpgrade(Left(P), id);
	if(R == NULL) R = SearchUpgrade(Right(P), id);
	return R;
}

boolean IsInfoNodeSame(UpgradeType UT1, UpgradeType UT2) {
	boolean tf = true;

	tf = tf && (UT1.id == UT2.id);
	tf = tf && (UT1.kapasitas == UT2.kapasitas);
	tf = tf && (UT1.harga == UT2.harga);
	tf = tf && (JAMToDetik(UT1.durasi) == JAMToDetik(UT2.durasi));
	tf = tf && (IsKataSama(UT1.nama, UT2.nama));
	tf = tf && (IsKataSama(UT1.description, UT2.description));
	tf = tf && (UT1.isTaken == UT2.isTaken);
	tf = tf && (UT1.UpgradeCost.uang == UT2.UpgradeCost.uang);
	tf = tf && (true); /* Ngecek array materials sama atau tidak */
	if (UT1.UpgradeCost.materials.NbEl == UT2.UpgradeCost.materials.NbEl) {
		for (int i = 0; i < UT1.UpgradeCost.materials.NbEl && tf; ++i) {
			tf = tf && ((Material *) UT1.UpgradeCost.materials.arr[i].metadata)->biayaMaterial == ((Material *) UT2.UpgradeCost.materials.arr[i].metadata)->biayaMaterial;
			tf = tf && ((Material *) UT1.UpgradeCost.materials.arr[i].metadata)->idMaterial == ((Material *) UT2.UpgradeCost.materials.arr[i].metadata)->idMaterial;
			tf = tf && ((Material *) UT1.UpgradeCost.materials.arr[i].metadata)->jumlahMaterial == ((Material *) UT2.UpgradeCost.materials.arr[i].metadata)->jumlahMaterial;
			tf = tf && IsKataSama(((Material *) UT1.UpgradeCost.materials.arr[i].metadata)->namaMaterial, ((Material *) UT2.UpgradeCost.materials.arr[i].metadata)->namaMaterial);
		}
	} else {
		tf = false;
	}

	return tf;
}

addrNode cariUpgrade (WahanaTree wahana, int UpID) {
	if (IsTreeEmpty(wahana)) return NULL;
	else if (IsTreeOneElmt(wahana)) {
		if (wahana->upgradeInfo.id == UpID) return wahana;
		else return NULL;
	} else {
		if (wahana->upgradeInfo.id == UpID) return wahana;
		else {
			addrNode retSimpul = NULL;

			retSimpul = cariUpgrade(wahana->left, UpID);
			if (retSimpul == NULL) retSimpul = cariUpgrade(wahana->right, UpID);

			return retSimpul;
		}
	}
}

ATangibleWahana InteraksiWahanaSekitarPosisi(Point position) {
	/* ATangibleWahana */
	array wahanaSekitarPlayer;
	addrNode upgradeBersangkutan;
	Kata Wahana;
	ATangibleWahana wahanaTerdekat;

	/* Nyariin wahana sekitar pemain */
	wahanaSekitarPlayer = WahanaSekitarPosisi(position);

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

			if (IsKataSama(upgradeBersangkutan->upgradeInfo.nama, Wahana)) {
				wahanaTerdekat = (ATangibleWahana) wahanaSekitarPlayer.arr[idxWahana].metadata;
				break;
			}
		}

		if (idxWahana == wahanaSekitarPlayer.NbEl) puts("Tidak ada wahana dengan nama itu di sekitarmu.");
	} else if (wahanaSekitarPlayer.NbEl < 1) {
		puts("Tidak ada wahana di sekitarmu yang bisa diupgrade.");
		wahanaTerdekat = NULL;
	} else { /* wahanaSekitarPlayer.NbEl == 1 */
		wahanaTerdekat = (ATangibleWahana) wahanaSekitarPlayer.arr[0].metadata;
	}

	return wahanaTerdekat;
}

boolean hasUpgradeName(WahanaTree wahana, Kata nama){
	if(wahana == NULL) return 0;
	if(IsKataSama(Akar(wahana).nama, nama)) return 1;
	return hasUpgradeName(Left(wahana), nama) || hasUpgradeName(Right(wahana), nama);
}

void PrintPathTo(WahanaTree wahana, Kata nama){
	if(wahana == NULL) return;
	TulisKataKe(nama, stdout);
	if(!IsKataSama(Akar(wahana).nama, nama)){
		printf("->");
		if(hasUpgradeName(Left(wahana), nama))
			PrintPathTo(Left(wahana), nama);
		else if(hasUpgradeName(Right(wahana), nama))
		 	PrintPathTo(Right(wahana), nama);
	}
}