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
//    int i;
//    for (i = 0; i < K1.Length; ++i) K2->TabKata[i] = K1.TabKata[i];
//    K2->Length = K1.Length;
//    K2->TabKata[i] = '\0';
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

void BuyResource() {
    Kata qty, jenis;
    int qty_i;

    printf("Ingin membeli apa?\nList:\n");
    for (int i = 0; i < BuyableMaterials.NbEl; ++i) {
				printf("- ");
				TulisKataKe(((Material*) BuyableMaterials.arr)->namaMaterial, stdout);
        printf("\n");
    }

    STARTKATA(stdin);

    SalinKataKe(&qty);
    IgnoreBlank();
    ADVKATA();
    SalinKataKe(&jenis);
    IgnoreBlank();
    ADVKATA();

    if (!EndKata) printf("Input salah\n");
    else {
        actBuy a;

        qty_i = ParseTabKata(qty); /* Pengecekan input */
        a.qty = qty_i; /* Banyak pembelian */
        a.id = getMaterialId(jenis); /* nama dari barang yang dibeli (tipe data kata) */
        PropertiAksi prop;
        prop.durasiAksi = MakeJAM(0, 30, 0);
        prop.idAksi = BUY;
        if (qty_i != -1 && qty_i > 0) Push(&actionStack, &a, prop);
        else if (qty_i <= 0) puts("Pembelian minimal 1");
    }
}

void ExecBuy(actBuy aB, JAM *curJam) {
    Kata asd = getMaterialName(aB.id);
    int harga, i = 0;

    /* Akan mencari indeks di mana ditemukan material dengan nama sesuai
     * variabel `asd` pada playerResources */
    for (; !IsKataSama(asd, playerResources.materials[i].namaMaterial); ++i);
    playerResources.materials[i].jumlahMaterial += aB.qty;

    harga = playerResources.materials[i].biayaMaterial;
    playerResources.uang -= harga * aB.qty;

    *curJam = DetikToJAM(JAMToDetik(*curJam) - LAMA_BELI);
}

unsigned char getMaterialId(Kata K){
	int i;
	Material* M;
	unsigned char id = 0;
	boolean found;
	for(i = 0; i < BuyableMaterials.NbEl && !found; i++){
		M = (Material *)BuyableMaterials.arr;
		if(IsKataSama(M->namaMaterial, K)){
			id = M->idMaterial;
			found = true;
		}
	}
	return id;
}

Kata getMaterialName(unsigned char id){
	int i;
	Kata c;
	Material* M;
	boolean found;
	for(i = 0; i < BuyableMaterials.NbEl && !found; i++){
		M = (Material *)BuyableMaterials.arr;
		if(M->idMaterial == id){
			c = M->namaMaterial;
			found = true;
		}
	}
	return c;
}
