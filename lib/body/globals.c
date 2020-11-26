#include "../header/globals.h"

Stack actionStack;
Resource playerResources;
Kata Nama;
array BuiltWahana;

void init() {
    CreateEmptyStack(&actionStack);

    playerResources.uang = START_MONEY;
    CreateArray(&BuiltWahana, 10); // 10 wahana should be enough, can be extended
}
