/* *** ADT resource *** */
/* ADT untuk resource yang dibutuhkan untuk membangun & mengupgrade
 * wahana serta ADT untuk menyimpan resource yang dimiliki pemain
 */

#include "../header/resources.h"
#include "../header/mesinkata.h"
#include "../header/stacklist.h"
#include "../header/globals.h"
#include "../header/str.h"
#include <stdio.h>

Stack actionStack;

void copyTabKata(Kata K1, Kata *K2) {
    int i;
    for (i = 0; i < K1.Length; ++i) K2->TabKata[i] = K1.TabKata[i];
    K2->Length = K1.Length;
    K2->TabKata[i] = '\0';
}

int ParseTabKata(Kata K1) {
    int ret = 0;

    for (int i = 0; i < K1.Length; ++i) {
        int addval = K1.TabKata[i] - '0';
        ret *= 10;

        if (addval > 9 || addval < 0) {
            printf("Bukan bilangan\n");
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
    printf("\t-  logam\n");
    printf("\t-  nonlogam\n");
    printf("\t-  metaloid\n");

    STARTKATA();

    copyTabKata(CKata, &qty);
    IgnoreBlank();
    ADVKATA();
    copyTabKata(CKata, &jenis);
    IgnoreBlank();
    ADVKATA();

    if (!EndKata) printf("Input salah\n");
    else {
        actBuy a;

        qty_i = ParseTabKata(qty); /* Pengecekan input */
        a.qty_i = qty_i;
        if (strIsEqual(jenis.TabKata, "logam")
            || strIsEqual(jenis.TabKata, "nonlogam")
            || strIsEqual(jenis.TabKata, "metaloid")) {
            a.K = jenis;
            if (qty_i != -1) Push(&actionStack, &a, BUY);
        }
        else printf("Bukan bahan yang bisa dibeli.\n");
    }
}

void ExecBuy(Resource *rP, actBuy aB) {
    char* asd = aB.K.TabKata;
    if (strIsEqual(asd, "logam")) {
        rP->logam += aB.qty_i;
        rP->uang -= aB.qty_i*hargaLogam;
    } else if (strIsEqual(asd, "nonlogam")) {
        rP->nonlogam += aB.qty_i;
        rP->uang -= aB.qty_i*hargaNonLogam;
    } else /*TabKata === "metaloid" */ {
        rP->metaloid += aB.qty_i;
        rP->uang -= aB.qty_i*hargaMetaloid;
    }
}
