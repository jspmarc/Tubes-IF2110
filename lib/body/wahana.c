/* File: wahana.c */
/* File header untuk ADT Wahana */

#include "../header/wahana.h"
#include "../header/stacklist.h"
#include "../header/globals.h"
#include <stdlib.h>

/* *** ADT Wahana *** */
/* Menyimpan struct untuk wahana, lalu fungsi dan prosedur seperti selektor,
 * konstruktor, dan lain-lain
 */
void BuildWahana(unsigned char idWahana, JAM durasiPembuatan) {
}
Wahana ExecBuild();

void UpgradeWahana(Wahana *W, Resource *resourcePemain, JAM durasiUpgrade);
void  ExecUpgrd();

void Break(Wahana *W) {
    if (random()%101 <= 10) W->rideable = false;
}

void Repair(Wahana *W, Resource *resourcePemain, JAM durasiPerbaikan);

void WahanaDetail(Wahana *W);
