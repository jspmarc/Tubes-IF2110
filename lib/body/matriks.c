/* File: matriks.c
 * Realisasi ADT matriks
 * Josep Marcello
 * 13519164 */

/* ******** Definisi TYPE MATRIKS dengan indeks dan elemen integer ******** */

#include "boolean.h"
#include "../header/matriks.h"
#include <stdio.h>

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M) {
    /* KAMUS LOKAL */
    /* ALGORITMA */
    NBrsEff(*M) = NB;
    NKolEff(*M) = NK;
}

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j) {
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return (BrsMin <= i && i <=BrsMax) && (KolMin <= j && j <= KolMax);
}

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M) {
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return BrsMin;
}
indeks GetFirstIdxKol (MATRIKS M) {
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return KolMin;
}
indeks GetLastIdxBrs (MATRIKS M) {
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return NBrsEff(M)-1;
}
indeks GetLastIdxKol (MATRIKS M) {
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return NKolEff(M)-1;
}
boolean IsIdxEff (MATRIKS M, indeks i, indeks j) {
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return (BrsMin <= i && i <= GetLastIdxBrs(M)) &&
            (KolMin <= j && j <= GetFirstIdxKol(M));
}
MatriksElType GetElmtDiagonal (MATRIKS M, indeks i) {
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return Elmt(M, i, i);
}

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl) {
    /* KAMUS LOKAL */
    /* ALGORITMA */
    NBrsEff(*MHsl) = NBrsEff(MIn);
    NKolEff(*MHsl) = NKolEff(MIn);

    for (indeks i = GetFirstIdxBrs(MIn); i <= GetLastIdxBrs(MIn); ++i)
        for (indeks j = GetFirstIdxKol(MIn); j <= GetLastIdxKol(MIn); ++j)
            Elmt(*MHsl, i, j) = Elmt(MIn, i, j);
}

/* ********** KELOMPOK BACA/TULIS ********** */
void BacaMATRIKS (MATRIKS * M, int NB, int NK) {
    /* KAMUS LOKAL */
    /* ALGORITMA */
    MakeMATRIKS(NB, NK, M);

    for (indeks i = GetFirstIdxBrs(*M); i < NB; ++i)
        for (indeks j = GetFirstIdxKol(*M); j < NK; ++j)
            scanf("%c", &Elmt(*M, i, j));
}
void TulisMATRIKS (MATRIKS M) {
    /* KAMUS LOKAL */
    /* ALGORITMA */
    for (indeks i = GetFirstIdxBrs(M); i < GetLastIdxBrs(M)+1; i++) {
        for (indeks j = GetFirstIdxKol(M); j < GetLastIdxKol(M)+1; j++) {
            if (j != GetLastIdxKol(M)) printf("%c ", Elmt(M, i, j));
            else if (i != GetLastIdxBrs(M)) printf("%c\n", Elmt(M, i, j));
            else printf("%c", Elmt(M, i, j));
        }
    }
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */
boolean MatriksEQ (MATRIKS M1, MATRIKS M2) {
    /* KAMUS LOKAL */
    /* ALGORITMA */
    if (NBElmt(M1) != NBElmt(M2) || !MatriksEQSize(M1, M2))
        return false;

    for (indeks i = GetFirstIdxBrs(M1); i <= GetLastIdxBrs(M1); ++i)
        for (indeks j = GetFirstIdxKol(M1); j <= GetLastIdxKol(M1); ++j)
            if (Elmt(M1, i, j) != Elmt(M2, i, j))
                return false;

    return true;
}
boolean MatriksNE (MATRIKS M1, MATRIKS M2) {
    return !MatriksEQ(M1, M2);
}
boolean MatriksEQSize (MATRIKS M1, MATRIKS M2) {
    return (NBrsEff(M1) == NBrsEff(M2) && NKolEff(M1) == NKolEff(M2));
}

/* ********** Operasi lain ********** */
int NBElmt (MATRIKS M)
/* Mengirimkan banyaknya elemen M */
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return NKolEff(M) * NBrsEff(M);
}

/* ********** KELOMPOK TEST TERHADAP MATRIKS ********** */
boolean IsBujurSangkar (MATRIKS M) {
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return NBrsEff(M) == NKolEff(M);
}
boolean IsSimetri (MATRIKS M) {
    /* KAMUS LOKAL */
    /* ALGORITMA */
    if (!IsBujurSangkar(M))
        return false;

    for (indeks i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); ++i) {
        for (indeks j = GetFirstIdxKol(M); j <= GetLastIdxKol(M) && i > j; ++j) {
            if (i == j) continue;
            if (Elmt(M, i, j) != Elmt(M, j, i)) return false;
        }
    }

    return true;
}

void Transpose (MATRIKS * M) {
    /* KAMUS LOKAL */
    MatriksElType temp;

    /* ALGORITMA */
    if (IsBujurSangkar(*M)) {
        for (indeks i = GetFirstIdxBrs(*M); i <= GetLastIdxBrs(*M); ++i) {
            for (indeks j = GetFirstIdxKol(*M);
                    j <= GetLastIdxKol(*M) && i > j; ++j) {
                temp = Elmt(*M, i, j);
                Elmt(*M, i,j) = Elmt(*M, j, i);
                Elmt(*M, j, i) = temp;
            }
        }
    }
}
