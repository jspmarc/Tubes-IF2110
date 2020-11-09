#include <stdlib.h>
#include <stdio.h>
#include "../header/array.h"

/* I.S.: A tidak terdefinisi, nbEl dan elType terdefinisi
 * F.S.: A terdefinisi
 */
void CreateEmpty(Array *A, int NbEl, char ElType) {
    switch (ElType) {
        case 'c':
            A->ElSize = 1;
            break;
        case 's':
            A->ElSize = 2;
            break;
        case 'f':
        case 'i':
            A->ElSize = 4;
            break;
        case 'l':
        case 'd':
            A->ElSize = 8;
            break;
    }

    A->Arr = malloc(NbEl*A->ElSize);
    if (A->Arr == NULL) {
        puts("Can't allocate memory when creating a new array.");
        exit(1);
    } else {
        A->NbEl = NbEl;
        A->ElType = ElType;
    }
}

/* I.S.: A terdefinisi
 * F.S.: A tidak terdefinisi
 */
void DeleteArray(Array *A)
{
    free(A->Arr);
}

/* I.S.: A terdefinisi, mungkin kosong
 * F.S.: Nilai elemen di indeks idx pada array A adalah nilai yang ditunjuk *el
 */
void SetEl(Array *A, unsigned int Idx, char El) {
    if (Idx >= A->NbEl){
        puts("Index out of bound");
        exit(1);
    }

    *((char*) (A->Arr)+Idx) = El;
}


/* Mengembalikan pointer void ke elemen di array A pada indeks ke-idx */
void* GetEl(Array A, unsigned idx) {
    if (idx >= A.NbEl){
        puts("Index out of bound");
        exit(1);
    }

    unsigned char S = A.ElSize;
    return (void*) (A.Arr+(idx*S));
}

void UnShift(Array *A, void *NewEl) {

}
