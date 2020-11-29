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

boolean IsMaterialsEnough(array matYangMauDikurangi, array matPengurang) {
	boolean bisa = true;

	if (matYangMauDikurangi.NbEl < matPengurang.NbEl) {
		/* Harusnya tidak terjadi seperti ini */
		puts("Sebuah kesalahan telah terjadi. Mohon mengontak pembuat program.");
		exit(20);
	}

	for (int i = 0; i < matPengurang.NbEl && bisa; ++i) {
		Material matPengurangSekarang = *((Material *) matPengurang.arr[i].metadata),
				 matYangMauDikurangiSekarang = *getMaterialByID(matPengurangSekarang.idMaterial);
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

	printf("%d\t%d\n",res1.materials.NbEl, res2.materials.NbEl);
	if (res1.materials.NbEl >= res2.materials.NbEl) {
		PrintArr(res1.materials);
		puts("");
		for (int i = 0; i < res1.materials.NbEl; ++i) {
			printf("%d\n", i);
			if (i < res2.materials.NbEl) {
				puts("Apel");
				Material *matRes1 = (Material *) res1.materials.arr[i].metadata;
				Material *matRes2 = getMaterialByID(matRes1->idMaterial);
				puts("Semangka");

				((Material *) result->materials.arr[i].metadata)->jumlahMaterial
					= matRes1->jumlahMaterial + matRes2->jumlahMaterial;
				puts("Mangga");
			} else {
				puts("Pisang gede");
				Material *matRes1 = (Material *) res1.materials.arr[i].metadata;
				((Material *) result->materials.arr[i].metadata)->jumlahMaterial
					= matRes1->jumlahMaterial;
			}
		}
	} else {
		for (int i = 0; i < res2.materials.NbEl; ++i) {
			if (i < res1.materials.NbEl) {
				Material *matRes2 = (Material *) res1.materials.arr[i].metadata;
				Material *matRes1 = getMaterialByID(matRes2->idMaterial);

				((Material *) result->materials.arr[i].metadata)->jumlahMaterial
					= matRes1->jumlahMaterial + matRes2->jumlahMaterial;
			} else {
				((Material *) result->materials.arr[i].metadata)->jumlahMaterial
					= ((Material *) res2.materials.arr[i].metadata)->jumlahMaterial;
			}
		}
	}
}

void KurangDuaResource(Resource res1, Resource res2, Resource *result) {
	Resource ret;

	ret.uang = res1.uang - res2.uang;

	unsigned bigger = res1.materials.NbEl >= res2.materials.NbEl ?
						res1.materials.MaxEl : res2.materials.NbEl;

	CreateArray(&ret.materials, bigger);

	for (int i = 0; i < bigger; ++i) {
		if (i < res2.materials.NbEl) {
			Material *matRes1 = (Material *) res1.materials.arr[i].metadata,
					 *matRes2 = getMaterialByID(matRes1->idMaterial);

			((Material *) ret.materials.arr[i].metadata)->jumlahMaterial
				= matRes1->jumlahMaterial - matRes2->jumlahMaterial;
		} else {
			((Material *) ret.materials.arr[i].metadata)->jumlahMaterial
				= ((Material *) res1.materials.arr[i].metadata)->jumlahMaterial;
		}
	}
}
