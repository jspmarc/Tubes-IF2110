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

Material *getMaterialByID(array source, char id) {
	Material *pmat = NULL;
	int i = 0;
	boolean found = false;
	for(; i < source.NbEl && !found; ++i) {
		if (((Material *) source.arr[i].metadata)->idMaterial == id) {
			pmat = ((Material *) source.arr[i].metadata);
			found = true;
		}
	}

	return pmat;
}

Material *getMaterialByName(array source, Kata Nama) {
	Material *pmat = NULL;
	int i = 0;
	boolean found = false;
	for(; i < source.NbEl && !found; ++i) {
		if (IsKataSama(Nama, ((Material *) source.arr[i].metadata)->namaMaterial)) {
			pmat = ((Material *) source.arr[i].metadata);
			found = true;
		}
	}

	return pmat;
}

boolean IsMaterialsEnough(array matYangMauDikurangi, array matPengurang) {
	boolean bisa = true;

	if (matYangMauDikurangi.NbEl < matPengurang.NbEl) {
		/* Harusnya tidak terjadi seperti ini */
		puts("Sebuah kesalahan telah terjadi. Mohon mengontak pembuat program.");
		exit(20);
	}

	for (int i = 0; i < matPengurang.NbEl && bisa; ++i) {
		Material matPengurangSekarang = *((Material *) matPengurang.arr[i].metadata),
				 matYangMauDikurangiSekarang = *getMaterialByID(matPengurang, matPengurangSekarang.idMaterial);
		bisa = bisa && matPengurangSekarang.jumlahMaterial <= matYangMauDikurangiSekarang.jumlahMaterial;
	}

	return bisa;
}

boolean IsResourcesEnough(Resource resYangMauDikurangi, Resource resPengurang) {
	return resYangMauDikurangi.uang >= resPengurang.uang
	&& IsMaterialsEnough(resYangMauDikurangi.materials, resPengurang.materials);
}

void TambahDuaResource(Resource res1, Resource res2, Resource *result) {
	result->uang = res1.uang + res2.uang;

	CreateArray(&result->materials, MAX_MATERIAL);

	if (res1.materials.NbEl >= res2.materials.NbEl) {
		for (int i = 0; i < res1.materials.NbEl; ++i) {
			Material *matRes1 = (Material *) res1.materials.arr[i].metadata;
			result->materials.arr[i].metadata = (Material *) malloc(sizeof(Material));
			if (i < res2.materials.NbEl) {
				Material *matRes2 = getMaterialByName(res2.materials, matRes1->namaMaterial);

				((Material *) result->materials.arr[i].metadata)->jumlahMaterial
					= matRes1->jumlahMaterial + matRes2->jumlahMaterial;
			} else {
				((Material *) result->materials.arr[i].metadata)->jumlahMaterial
					= matRes1->jumlahMaterial;
			}
			Kata namaMaterial = ((Material *) res1.materials.arr[i].metadata)->namaMaterial;
			int id = ((Material *) res1.materials.arr[i].metadata)->idMaterial;
			((Material *) result->materials.arr[i].metadata)->namaMaterial = namaMaterial;
			((Material *) result->materials.arr[i].metadata)->idMaterial = id;
		}

		result->materials.NbEl = res1.materials.NbEl;
	} else {
		for (int i = 0; i < res2.materials.NbEl; ++i) {
			Material *matres2 = (Material *) res2.materials.arr[i].metadata;
			result->materials.arr[i].metadata = (Material *) malloc(sizeof(Material));
			if (i < res1.materials.NbEl) {
				Material *matres1 = getMaterialByName(res1.materials, matres2->namaMaterial);

				((Material *) result->materials.arr[i].metadata)->jumlahMaterial
					= matres2->jumlahMaterial + matres1->jumlahMaterial;
			} else {
				((Material *) result->materials.arr[i].metadata)->jumlahMaterial
					= matres2->jumlahMaterial;
			}
			Kata namaMaterial = ((Material *) res2.materials.arr[i].metadata)->namaMaterial;
			int id = ((Material *) res2.materials.arr[i].metadata)->idMaterial;
			((Material *) result->materials.arr[i].metadata)->namaMaterial = namaMaterial;
			((Material *) result->materials.arr[i].metadata)->idMaterial = id;
		}

		result->materials.NbEl = res2.materials.NbEl;
	}
}

void KurangDuaResource(Resource res1, Resource res2, Resource *result) {
	result->uang = res1.uang - res2.uang;

	CreateArray(&result->materials, MAX_MATERIAL);

	if (res1.materials.NbEl >= res2.materials.NbEl) {
		for (int i = 0; i < res1.materials.NbEl; ++i) {
			Material *matRes1 = (Material *) res1.materials.arr[i].metadata;
			result->materials.arr[i].metadata = (Material *) malloc(sizeof(Material));
			if (i < res2.materials.NbEl) {
				Material *matRes2 = getMaterialByName(res2.materials, matRes1->namaMaterial);

				((Material *) result->materials.arr[i].metadata)->jumlahMaterial
					= matRes1->jumlahMaterial - matRes2->jumlahMaterial;
			} else {
				((Material *) result->materials.arr[i].metadata)->jumlahMaterial
					= matRes1->jumlahMaterial;
			}
			Kata namaMaterial = ((Material *) res1.materials.arr[i].metadata)->namaMaterial;
			int id = ((Material *) res1.materials.arr[i].metadata)->idMaterial;
			((Material *) result->materials.arr[i].metadata)->namaMaterial = namaMaterial;
			((Material *) result->materials.arr[i].metadata)->idMaterial = id;
		}

		result->materials.NbEl = res1.materials.NbEl;
	} else {
		for (int i = 0; i < res2.materials.NbEl; ++i) {
			Material *matres2 = (Material *) res2.materials.arr[i].metadata;
			result->materials.arr[i].metadata = (Material *) malloc(sizeof(Material));
			if (i < res1.materials.NbEl) {
				Material *matres1 = getMaterialByName(res1.materials, matres2->namaMaterial);

				((Material *) result->materials.arr[i].metadata)->jumlahMaterial
					= matres2->jumlahMaterial - matres1->jumlahMaterial;
			} else {
				((Material *) result->materials.arr[i].metadata)->jumlahMaterial
					= matres2->jumlahMaterial;
			}
			Kata namaMaterial = ((Material *) res2.materials.arr[i].metadata)->namaMaterial;
			int id = ((Material *) res2.materials.arr[i].metadata)->idMaterial;
			((Material *) result->materials.arr[i].metadata)->namaMaterial = namaMaterial;
			((Material *) result->materials.arr[i].metadata)->idMaterial = id;
		}

		result->materials.NbEl = res2.materials.NbEl;
	}
}

void PrintResource(Resource R) {
	printf("Uang: %d\n", R.uang);
	puts("Materials:");
	for (int i = 0; i < R.materials.NbEl; ++i) {
		printf("  - ");
		TulisKataKe(((Material *) R.materials.arr[i].metadata)->namaMaterial, stdout);
		printf(": %d\n", ((Material *) R.materials.arr[i].metadata)->jumlahMaterial);
	}
}
