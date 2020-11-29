/* *** ADT resource *** */
/* ADT untuk resource yang dibutuhkan untuk membangun & mengupgrade
 * wahana serta ADT untuk menyimpan resource yang dimiliki pemain
 */

#include "../header/resources.h"
#include "../header/stacklist.h"
#include "../header/mesinkata.h"
#include "../header/globals.h"
#include "../header/str.h"
#include <stdio.h>

//Stack actionStack;
//Resource playerResources;
/*array BuyableMaterials;*/

void InitResources() {
	CreateArray(&BuyableMaterials, MAX_MATERIAL);
	/* Baca dari file */
}

//void copyTabKata(Kata K1, Kata *K2) {
//	  int i;
//	  for (i = 0; i < K1.Length; ++i) K2->TabKata[i] = K1.TabKata[i];
//	  K2->Length = K1.Length;
//	  K2->TabKata[i] = '\0';
//}
//
int ParseTabKata(Kata K1) {
	int ret = 0;

	for (int i = 0; i < K1.Length; ++i) {
		int addval = K1.TabKata[i] - '0';
		ret *= 10;

		if (addval > 9 || addval < 0) {
			printf("Bukan bilangan atau bilangan tidak valid\n");
			ret = -1;
			break;
		} else ret += addval;
	}

	return ret;
}

/*Kata getMaterialName(char id){*/
	/*int i;*/
	/*Kata c;*/
	/*boolean found;*/
	/*for(i = 0; i < BuyableMaterials.NbEl && !found; i++){*/
		/*if (((Material *) BuyableMaterials.arr[i].metadata)->idMaterial == id) {*/
			/*c = ((Material *) BuyableMaterials.arr[i].metadata)->namaMaterial;*/
			/*found = true;*/
		/*}*/
	/*}*/
	/*return c;*/
/*}*/

/*unsigned short getMaterialPrice(char id);*/

Material *getMaterialByID(char id) {
	Material *pmat = NULL;
	int i = 0;
	boolean found = false;
	for(; i < BuyableMaterials.NbEl && !found; ++i) {
		if (((Material *) BuyableMaterials.arr[i].metadata)->idMaterial == id) {
			pmat = ((Material *) BuyableMaterials.arr[i].metadata);
			found = true;
		}
	}

	return pmat;
}

Material *getMaterialByName(Kata Nama) {
	Material *pmat = NULL;
	int i = 0;
	boolean found = false;
	for(; i < BuyableMaterials.NbEl && !found; ++i) {
		if (IsKataSama(Nama, ((Material *) BuyableMaterials.arr[i].metadata)->namaMaterial)) {
			pmat = ((Material *) BuyableMaterials.arr[i].metadata);
			found = true;
		}
	}

	return pmat;
}
