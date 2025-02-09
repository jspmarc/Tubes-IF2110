#include <stdlib.h>
#include <stdio.h>
#include "../header/array.h"
#include "boolean.h"

/**
 * Fungsi untuk membuat elemen padding saat melakukan shift
 * Elemen padding adalah struct terdiri dari 2 integer bernilai val,
 * id dan info nya
 *
 * Returns elemen padding berupa struct berisi 0
 */
ArrayElType MakePadding(int val) {
    ArrayElType E;

    E.id = val;
    E.info = val;

    return E;
}

/**
 * Fungsi bantuan untuk mencari kesamaan diantara dua buah struct dengan
 * data id dan info
 *
 * ArrayElType Item1 - variabel pertama dengan tipe data ArrayElType yang ingin dicocokan
 * ArrayElType Item2 - variabel kedua dengan tipe data ArrayElType yang ingin dicocokan
 */

boolean SameItem(ArrayElType Item1, ArrayElType Item2) {
    return Item1.id == Item2.id
        && Item1.info == Item2.info;
}

void CreateArray(array *A, unsigned size) {
    A->arr = (ArrayElType *) malloc(size * sizeof(ArrayElType));

    if (A->arr == NULL) { /* arr gagal dialokasikan */
        free(A->arr);
        puts("An error has occured on allocating memory, please try re-running the program");
        exit(1);
    }

    A->MaxEl = size;
    A->NbEl = 0;
}

void DeleteArray(array *A) {
    free(A->arr);
    A->NbEl = -1;
    A->MaxEl = 0;
}

void GrowArray(array *A, unsigned newSize) {
    A->arr = (ArrayElType*) reallocarray(A->arr, newSize, sizeof(ArrayElType));
    A->MaxEl = newSize;
}

void ShrinkArray(array *A, unsigned newSize) {
    if (A->NbEl <= newSize) {
        A->arr = (ArrayElType*) reallocarray(A->arr, newSize, sizeof(ArrayElType));
        A->MaxEl = newSize;
    } else { /* Ukuran baru lebih kecil dari banyak elemen */
        puts("Something bad happened, please try re-running the program");
        exit(1);
    }
}

boolean IsArrEmpty(array A) {
    return A.NbEl == 0;
}

boolean IsArrFull(array A) {
    return A.NbEl == A.MaxEl;
}

int SearchArrEl(array A, ArrayElType El) {
    boolean found = false;
    int i;

    if (IsArrEmpty(A))
        found = false;

    for (i = 0; i < A.NbEl && !SameItem(A.arr[i], El); ++i);
    found = i < A.NbEl;

    return found ? i : -1;
}

ArrayElType DelArrFirst(array *A) {
    ArrayElType retVal;
    if (!IsArrEmpty(*A)) {
        retVal = A->arr[0];
        ShiftArrLeft(A, 1);
    }

    return retVal;
}
ArrayElType DelArrLast(array *A) { /* TODO: Bug */
    ArrayElType retVal;
    if(!IsArrEmpty(*A)) {
        retVal = A->arr[--(A->NbEl)];
    }

    return retVal;
}
void InsArrFirst(array *A, ArrayElType X) { /* TODO: Bug */
    if (!IsArrFull(*A)) {
        if (!IsArrEmpty(*A)) {
            ShiftArrRight(A, 1); /* Ada yg salah */
        }
        A->arr[0] = X;
        A->NbEl++;
    } else { /* Array penuh */
        puts("Array penuh");
    }
}
void InsArrLast(array *A, ArrayElType X) {
    if (!IsArrFull(*A)) {
        A->arr[(A->NbEl)++] = X;
    } else { /* Array penuh */
        puts("Array penuh");
    }
}

void ShiftArrLeft(array *A, int n) {
    if (n < 0) {
        n *= (-1);
        ShiftArrRight(A, n);
    } else if (n >= A->NbEl) {
        /* kalau jumlah pergeseran lebih besar dari jumlah elemen,
         * akan dilakukan pengosongan elemen array
         */
        A->NbEl = 0;
    } else {
        int i,j;
        for (i = 0, j = n; j < (A->NbEl); i++, j++) {
            A->arr[i] = A->arr[j];
        }

        A->NbEl -= n;
    }
}
void ShiftArrRight(array *A, int n) {
    if (n < 0) {
        n *= (-1);
        ShiftArrLeft(A, n);
    } else if (n >= A->MaxEl) {
        for (int i = 0; i < A->MaxEl; ++i) {
            A->arr[i] = MakePadding(0);
        }

        A->NbEl = A->MaxEl;
    } else {
        int i, j;
        for (i = (A->NbEl)-1, j = n-1; j >= 0; ++i, --j) {
            A->arr[j] = A->arr[i];
        }
        for (; i > -1; A->arr[i--] = MakePadding(0));
    }
}

// void SortArr(array *A, boolean asc) {
//     /* Implementasi Sort dengan Insertion Sort */
//     int i, j;
//     ArrayElType k;

//     i = 1;
//     while(i < A->NbEl){
//     k = (A->arr)[i];
//     j = i - 1;
//     while(
//         j >= 0 &&
//         (
//         ((A->arr)[j].info < k.info && asc) || // info Key lebih kecil, ingin ascending
//         ((A->arr[j].info > k.info && !asc)) // info Key lebih besar, ingin descending
//              )
//     ) {
//         // "geser" array ke arah key, jalan ke "awal" array
//         A->arr[j+1] = A->arr[j];
//         j--;
//     }
//     // taruh key di tempat yang seharusnya
//     A->arr[j] = k;
//     i++;
//     }
// }

void CopyArr(array in, array * out) {
    // Jadi void karena biar ga mem leak
    int i = 0;
    if (out->MaxEl < in.NbEl) GrowArray(out, in.NbEl);
    if (out->MaxEl > in.NbEl) ShrinkArray(out, in.NbEl);
    while (out->NbEl != in.NbEl) {
        InsArrLast(out, in.arr[i++]);
    }
}

void PrintArr(array A) {
    printf("[");
    for (int i = 0; i < A.NbEl; ++i) {
        printf("\n\t{\n\t\tid: %d,\n\t\tinfo: %d\n\t}", A.arr[i].id, A.arr[i].info);
        if (i != A.NbEl-1) printf(",");
    }
    printf("\n]");
}
