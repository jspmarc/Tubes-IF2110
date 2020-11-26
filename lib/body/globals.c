#include "../header/globals.h"

Stack actionStack;
Resource playerResources;

void init() {
    CreateEmptyStack(&actionStack);

    playerResources.uang = START_MONEY;
}
