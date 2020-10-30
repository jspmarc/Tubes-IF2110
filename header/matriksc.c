/* File: matriks.c
 * Realisasi ADT matriks
 * Josep Marcello
 * 13519164 */

/* ******** Definisi TYPE MATRIKS dengan indeks dan elemen integer ******** */

#include "boolean.h"
#include "matriksc.h"
#include <stdio.h>

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M)
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di
 * "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    NBrsEff(*M) = NB;
    NKolEff(*M) = NK;
}

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j)
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return (BrsMin <= i && i <=BrsMax) && (KolMin <= j && j <= KolMax);
}

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terkecil M */
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return BrsMin;
}
indeks GetFirstIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terkecil M */
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return KolMin;
}
indeks GetLastIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terbesar M */
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return NBrsEff(M)-1;
}
indeks GetLastIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terbesar M */
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return NKolEff(M)-1;
}
boolean IsIdxEff (MATRIKS M, indeks i, indeks j)
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return (BrsMin <= i && i <= GetLastIdxBrs(M)) &&
            (KolMin <= j && j <= GetFirstIdxKol(M));
}
ElType GetElmtDiagonal (MATRIKS M, indeks i)
/* Mengirimkan elemen M(i,i) */
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return Elmt(M, i, i);
}

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl)
/* Melakukan assignment MHsl  MIn */
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    NBrsEff(*MHsl) = NBrsEff(MIn);
    NKolEff(*MHsl) = NKolEff(MIn);

    for (indeks i = GetFirstIdxBrs(MIn); i <= GetLastIdxBrs(MIn); ++i)
        for (indeks j = GetFirstIdxKol(MIn); j <= GetLastIdxKol(MIn); ++j)
            Elmt(*MHsl, i, j) = Elmt(MIn, i, j);
}

/* ********** KELOMPOK BACA/TULIS ********** */
void BacaMATRIKS (MATRIKS * M, int NB, int NK)
/* I.S. IsIdxValid(NB,NK) */
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10
*/
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    MakeMATRIKS(NB, NK, M);

    for (indeks i = GetFirstIdxBrs(*M); i < NB; ++i)
        for (indeks j = GetFirstIdxKol(*M); j < NK; ++j)
            scanf("%c", &Elmt(*M, i, j));
}
void TulisMATRIKS (MATRIKS M)
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing
 * elemen per baris dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris
 * dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    for (indeks i = GetFirstIdxBrs(M); i < M.NBrsEff; ++i)
    {
        for (indeks j = GetFirstIdxKol(M); j < M.NKolEff; ++j)
        {
            if (j != NKolEff(M)-1)
                printf("%c ", Elmt(M, i, j));
            else if (j == GetLastIdxKol(M) && i != GetLastIdxBrs(M))
                printf("%c\n", Elmt(M, i, j));
            else /* j == Last Idx Kol and i == Last idx brs */
                printf("%c", Elmt(M, i, j));
        }
    }
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */
boolean EQ (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 = M2, yaitu NBElmt(M1) = NBElmt(M2) dan */
/* untuk setiap i,j yang merupakan indeks baris dan kolom M1(i,j) = M2(i,j) */
/* Juga merupakan strong EQ karena GetFirstIdxBrs(M1) = GetFirstIdxBrs(M2)
   dan GetLastIdxKol(M1) = GetLastIdxKol(M2) */
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    if (NBElmt(M1) != NBElmt(M2) || !EQSize(M1, M2))
        return false;

    for (indeks i = GetFirstIdxBrs(M1); i <= GetLastIdxBrs(M1); ++i)
        for (indeks j = GetFirstIdxKol(M1); j <= GetLastIdxKol(M1); ++j)
            if (Elmt(M1, i, j) != Elmt(M2, i, j))
                return false;

    return true;
}
boolean NEQ (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 tidak sama dengan M2 */
{
    return !EQ(M1, M2);
}
boolean EQSize (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu GetBrsEff(M1) = GetNBrsEff (M2) dan GetNKolEff (M1) = GetNKolEff (M2) */
{
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
boolean IsBujurSangkar (MATRIKS M)
/* Mengirimkan true jika M adalah matriks dg ukuran baris dan kolom sama */
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return NBrsEff(M) == NKolEff(M);
}
boolean IsSimetri (MATRIKS M)
/* Mengirimkan true jika M adalah matriks simetri : IsBujurSangkar(M)
   dan untuk setiap elemen M, M(i,j)=M(j,i) */
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    if (!IsBujurSangkar(M))
        return false;

    for (indeks i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); ++i)
    {
        for (indeks j = GetFirstIdxKol(M); j <= GetLastIdxKol(M) && i > j; ++j)
        {
            if (i == j)
                continue;
            if (Elmt(M, i, j) != Elmt(M, j, i))
                return false;
        }
    }

    return true;
}

void Transpose (MATRIKS * M)
/* I.S. M terdefinisi dan IsBujursangkar(M) */
/* F.S. M "di-transpose", yaitu setiap elemen M(i,j) ditukar nilainya dengan
 * elemen M(j,i) */
{
    /* KAMUS LOKAL */
    ElType temp;

    /* ALGORITMA */
    if (IsBujurSangkar(*M))
    {
        for (indeks i = GetFirstIdxBrs(*M); i <= GetLastIdxBrs(*M); ++i)
        {
            for (indeks j = GetFirstIdxKol(*M);
                    j <= GetLastIdxKol(*M) && i > j; ++j)
            {
                temp = Elmt(*M, i, j);
                Elmt(*M, i,j) = Elmt(*M, j, i);
                Elmt(*M, j, i) = temp;
            }
        }
    }
}
