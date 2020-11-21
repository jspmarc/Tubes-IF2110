#include "../lib/header/wahana.h"
#include "../lib/header/stacklist.h"
#include "./main.c"
#include <stdio.h>

Resource buildResources[] = {
}

void GameBuild(Resource playerResources) {
    /** Resource dibutuhkan dan durasiPembuatan ditentukan oleh tipe wahana
     * lalu ditentukan kapasitas dan ukuran wahana */
    BuildWahana(&playerResources, resourceDibutuhkan, durasiPembuatan)
    Push(&actionStack, 1);
}
