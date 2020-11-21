#include "../lib/header/wahana.h"
#include "../lib/header/stacklist.h"
#include "../lib/header/globals.h"
#include <stdio.h>

Stack actionStack;

void Undo() {
    void* _;
    Pop(&actionStack, _);
}
