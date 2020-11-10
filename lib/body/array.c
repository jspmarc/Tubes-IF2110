#include <stdlib.h>
#include <stdio.h>
#include "../header/array.h"
#include "boolean.h"

/**
 * Fungsi untuk membuat elemen padding saat melakukan shift
 * Elemen padding adalah struct terdiri dari 2 integer bernilai 0,
 * id dan info
 *
 * Returns elemen padding berupa struct berisi 0
 */
ElType MakePadding() {
    ElType E;

    E.id = 0;
    E.info = 0;

    return E;
}

/**
 * Fungsi bantuan untuk mencari kesamaan diantara dua buah struct dengan
 * data id dan info
 *
 * ElType Item1 - variabel pertama dengan tipe data ElType yang ingin dicocokan
 * ElType Item2 - variabel kedua dengan tipe data ElType yang ingin dicocokan
 */

boolean SameItem(ElType Item1, ElType Item2) {
    return Item1.id == Item2.id
        && Item1.info == Item2.info;
}

void CreateArray(array *A, unsigned size) {
    A->arr = (ElType *) malloc(size * sizeof(ElType));

    if (A->arr == NULL) { /* arr gagal dialokasikan */
        free(A->arr);
        puts("An error has occured on allocating memory, please try re-running the program");
        exit(1);
    }

    A->MaxEl = size;
    A->NbEl = -1;
}

void DeleteArray(array *A) {
    free(A->arr);
    A->NbEl = -1;
    A->MaxEl = 0;
}

void GrowArray(array *A, unsigned newSize) {
    A->arr = (ElType*) reallocarray(A->arr, newSize, sizeof(ElType));
    A->MaxEl = newSize;
}

void ShrinkArray(array *A, unsigned newSize) {
    if (A->NbEl <= newSize) {
        A->arr = (ElType*) reallocarray(A->arr, newSize, sizeof(ElType));
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

int SearchArrEl(array A, ElType El) {
    boolean found = false;
    int i;

    if (IsArrEmpty(A))
        found = false;

    for (i = 0; i < A.NbEl && !SameItem(A.arr[i], El); ++i);
    found = i < A.NbEl;

    return found ? i : -1;
}

ElType DelArrFirst(array *A) {
    ElType retVal = MakePadding();
    if (!IsArrEmpty(*A)) {
        retVal = A->arr[0];
        ShiftArrLeft(A, 1);
    }

    return retVal;
}
ElType DelArrLast(array *A) {
    ElType retVal = MakePadding();
    if(!IsArrEmpty(*A)) {
        retVal = A->arr[A->NbEl--];
    }

    return retVal;
}
void InsArrFirst(array *A, ElType X) {
    if (!IsArrFull(*A)) {
        if (!IsArrEmpty(*A)) {
            ShiftArrRight(A, 1);
        }
        A->arr[0] = X;
    } else { /* Array penuh */
        puts("Array penuh");
    }
}
void InsArrLast(array *A, ElType X) {
    if (!IsArrFull(*A)) {
        if (!IsArrEmpty(*A)) {
            A->arr[0] = X;
        } else {
            A->arr[A->NbEl] = X;
        }
        A->NbEl++;
    } else { /* Array penuh */
        puts("Array penuh");
    }
}

void ShiftArrLeft(array *A, int n) {
    if (n > A->NbEl) {
        /* kalau jumlah pergeseran lebih besar dari jumlah elemen,
         * akan dilakukan pengosongan elemen array
         */
        A->NbEl = 0;
    } else {
        for (int i = n-1; i < A->NbEl-1; ++i) {
            A->arr[i-n] = A->arr[i+1];
        }

        A->NbEl -= n;
    }
}
void ShiftArrRight(array *A, int n) {
    if (n > A->MaxEl) {
        for (int i = 0; i < A->MaxEl; ++i) {
            A->arr[i] = MakePadding();
        }

        A->NbEl = A->MaxEl;
    } else {
        /* TODO */
    }
}

void SortArr(array *A, boolean asc) {
    /* Pada implementasi ini, di-sort berdasarkan id */
    /* TODO */
}

array CopyArr(array A1) {
    array A2;
    int i = 0;

    CreateArray(&A2, A1.MaxEl);
    while (A2.NbEl != A1.NbEl) {
        InsLast(&A2, A1.arr[i++]);
    }

    return A2;
}

void PrintArr(array A) {
    printf("[");
    for (int i = 0; i < A.NbEl; ++i) {
        if (i != A.NbEl-1) {
            printf("\n\t{\n\t\tid: %d,\n\t\tinfo: %d\n\t},", A.arr[i].id, A.arr[i].info);
        } else {
            printf("\n\t{\n\t\tid: %d,\n\t\tinfo: %d\n\t},", A.arr[i].id, A.arr[i].info);
        }
    }
    printf("\n]");
}
