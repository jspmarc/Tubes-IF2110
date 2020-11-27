/* ADT Upgrade Wahana */
/* Implementasi dengan menggunakan tree */
/* Untuk membeli wahana berarti kita mengambil node upgrade pertama */

#include "../header/wahana.h"
#include "../header/str.h"
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

UpgradeType BuatSimpulKosong(unsigned char id){
	UpgradeType simpul;
	simpul.id = id;
	return simpul;
}

UpgradeType IsiSimpul(unsigned char id, unsigned short kapasitas, unsigned int harga,
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

void UbahIsiSimpul(WahanaTree *P, unsigned char id, unsigned short kapasitas, unsigned int harga,
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
			TulisKataKe(Akar(P).nama, stdout);
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
    else TulisKataKe(Akar(P).nama, stdout);
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

addrNode SearchUpgrade(WahanaTree P, unsigned char id){
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

    return tf;
}

WahanaUpgradeStack UpgradeWahana(ATangibleWahana T, unsigned char id){
	WahanaUpgradeStack s;
	s = (WahanaUpgradeStack)malloc(sizeof(WahanaUpgradeInfo));
	TangibleWahana(s) = T;
	UpgradeID(s) = id;
	return s;
}
void ExecUpgrade(WahanaUpgradeStack Upgrade){
	// do stuff
	// free WahanaUpgradeStack: avoid memory leak!
	free(Upgrade);
}
