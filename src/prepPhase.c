#include "../lib/header/wahana.h"
#include "../lib/header/stacklist.h"
#include "../lib/header/globals.h"
#include <stdio.h>

void Undo() {
    void* t;
    t = NULL;
    Pop(&actionStack, t);
}
