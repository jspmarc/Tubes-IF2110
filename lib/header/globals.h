#include "./stacklist.h"
#include "./resources.h"

/* List ID aksi: (Prep phase)
 * ID   -   Aksi
 * 1    -   Build
 * 2    -   Upgrade
 * 3    -   Buy
 * 4    -   Undo
 * 5    -   Execute
 * 6    -   Main (play)
 */
extern Stack actionStack;
extern Resource playerResources;

void init();

/*
void init() {
    playerResources.logam = 0;
    playerResources.nonlogam = 0;
    playerResources.metaloid = 0;
    playerResources.uang = 0;

    CreateEmptyStack(&actionStack);
}
*/
