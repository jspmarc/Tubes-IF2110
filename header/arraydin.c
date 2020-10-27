/* Josep Marcello
 * 13519164
 * 15 September 2020*/
/* File: arraydin.c */

/* Realisasi TABEL INTEGER */
/* Berisi realisasi pemrosesan tabel integer */
/* Penempatan elemen selalu rapat kiri */
/* Versi II : dengan banyaknya elemen didefinisikan secara eksplisit,
  memori tabel dinamik */

#include "arraydin.h"
#include <stdlib.h>
#include <stdio.h>

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmpty(TabInt *T, int maxel)
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel */
{
    /* ALGORITMA */
    TI(*T) = (ElType *) malloc(maxel*sizeof(ElType));
    MaxEl(*T) = maxel;
    Neff(*T) = 0;
}

void Dealokasi(TabInt *T)
/* I.S. T terdefinisi; */
/* F.S. TI(T) dikembalikan ke system, MaxEl(T)=0; Neff(T)=0 */
{
    /* ALGORITMA */
    free(TI(*T));
    Neff(*T) = 0;
    MaxEl(*T) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmt(TabInt T)
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
{
    /* ALGORITMA */
    return Neff(T);
}

/* *** Daya tampung container *** */
int MaxElement(TabInt T)
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
{
    /* ALGORITMA */
    return MaxEl(T);
}

/* *** Selektor INDEKS *** */
IdxType GetFirstIdx(TabInt T)
/* Mengirimkan indeks elemen T pertama */
/* Prekondisi : Tabel T tidak kosong */
{
    /* ALGORITMA */
    /*return IsEmpty(T) ? IdxUndef : IdxMin;*/
    return IdxMin;
}
IdxType GetLastIdx(TabInt T)
/* Mengirimkan indeks elemen T terakhir */
/* Prekondisi : Tabel T tidak kosong */
{
    /* ALGORITMA */
    return NbElmt(T)-1;
}

/* ********** Test Indeks yang valid ********** */
boolean IsIdxValid(TabInt T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
{
    /* ALGORITMA */
    return IdxMin <= i && i < MaxElement(T);
}
boolean IsIdxEff(TabInt T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
{
    /* ALGORITMA */
    return IdxMin <= i && i < NbElmt(T);
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmpty(TabInt T)
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
{
    /* ALGORITMA */
    return Neff(T) == 0;
}
/* *** Test tabel penuh *** */
boolean IsFull(TabInt T)
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
{
    /* ALGORITMA */
    return NbElmt(T) == MaxElement(T);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void BacaIsi(TabInt *T)
/* I.S. T sembarang dan sudah dialokasikan sebelumnya */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxElement(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxElement(T); Lakukan N kali: Baca elemen mulai dari indeks
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
/* ASUMSI: MaxEl menggunakan IdxMax yg nilainya 100 */
{
    /* KAMUS LOKAL */
    IdxType N;

    /* ALGORITMA */
    do
    {
        scanf("%d", &N);
    } while(!IsIdxValid(*T, N == 0 ? 0 : N-1));

    /* 0 <= N <= MaxElement(*T) */
    for (IdxType i = IdxMin; i < N; ++i)
        scanf( "%d", &Elmt(*T, i) );

    Neff(*T) = N;
}
void TulisIsiTab(TabInt T)
/*Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
  antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
  di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
{
    /* ALGORITMA */
    printf("[");
    if (!IsEmpty(T))
    {
        for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T); ++i)
        {
            if (i < NbElmt(T)-1)
                printf("%d,", Elmt(T, i));
            else
                printf("%d", Elmt(T, i));
        }
    }
    printf("]");
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika tabel : Penjumlahan, pengurangan, perkalian, ... *** */
TabInt PlusMinusTab(TabInt T1, TabInt T2, boolean plus)
/* Prekondisi : T1 dan T2 memiliki Neff sama dan tidak kosong */
/* Jika plus = true, mengirimkan  T1+T2, yaitu setiap elemen T1 dan T2 pada
 * indeks yang sama dijumlahkan */
/* Jika plus = false, mengirimkan T1-T2, yaitu setiap elemen T1 dikurangi
 * elemen T2 pada indeks yang sama */
{
    /* KAMUS LOKAL */
    TabInt TRes;

    /* ALGORITMA */
    MakeEmpty(&TRes, MaxElement(T1));

    if (!IsEmpty(T1) && !IsEmpty(T2) && Neff(T1) == Neff(T2))
    {
        if (plus)
            for (IdxType i = GetFirstIdx(T1); i <= GetLastIdx(T1); ++i)
                Elmt(TRes, i) = Elmt(T1, i) + Elmt(T2, i);
        else
            for (IdxType i = GetFirstIdx(T1); i <= GetLastIdx(T1); ++i)
                Elmt(TRes, i) = Elmt(T1, i) - Elmt(T2, i);

        Neff(TRes) = NbElmt(T1);
        CopyTab(TRes, &T1);
    }

    Dealokasi(&TRes);
    return T1;
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan tabel : < =, > *** */
boolean IsEQ(TabInt T1, TabInt T2)
/* Mengirimkan true jika T1 sama dengan T2 yaitu jika Neff T1 = T2 dan semua elemennya sama */
{
    /* ALGORITMA */
    if (Neff(T1) != Neff(T2))
        return false;

    for (IdxType i = GetFirstIdx(T1); i <= GetLastIdx(T2); ++i)
        if (Elmt(T1, i) != Elmt(T2, i))
            return false;

    return true;
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType Search1(TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */
{
    /* ALGORITMA */
    if (IsEmpty(T))
        return IdxUndef;

    for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T); ++i)
        if (X == Elmt(T, i))
            return i;

    return IdxUndef;
}
boolean SearchB(TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */
{
    /* ALGORITMA */
    return Search1(T, X) != -1;
}

/* ********** NILAI EKSTREM ********** */
void MaxMin(TabInt T, ElType *Max, ElType *Min)
/* I.S. Tabel T tidak kosong */
/* F.S. Max berisi nilai maksimum T;
        Min berisi nilai minimum T */
{
    /* ALGORITMA */
    *Max = Elmt(T, GetFirstIdx(T));
    *Min = Elmt(T, GetFirstIdx(T));

    for (IdxType i = GetFirstIdx(T)+1; i <= GetLastIdx(T); ++i)
    {
        *Max = Elmt(T, i) > *Max ? Elmt(T, i) : *Max;
        *Min = Elmt(T, i) < *Min ? Elmt(T, i) : *Min;
    }
}

/* ********** OPERASI LAIN ********** */
void CopyTab(TabInt Tin, TabInt *Tout)
/* I.S. Tin terdefinisi tidak kosong, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (identik, Neff dan MaxEl sama) */
/* Proses : Menyalin isi Tin ke Tout */
{
    /* ALGORITMA */
    /*if (!IsEmpty(*Tout))*/
    MakeEmpty(Tout, MaxElement(Tin));

    /**Tout = Tin;*/
    Neff(*Tout) = NbElmt(Tin);
    MaxEl(*Tout) = MaxElement(Tin);
    for (ElType i = GetFirstIdx(Tin); i <= GetLastIdx(Tin); ++i)
        Elmt(*Tout, i) = Elmt(Tin, i);
}
ElType SumTab(TabInt T)
/* Menghasilkan hasil penjumlahan semua elemen T */
/* Jika T kosong menghasilkan 0 */
{
    /* KAMUS LOKAL */
    ElType sum = 0;

    /* ALGORITMA */
    for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T); ++i)
        sum += Elmt(T, i);

    return sum;
}
int CountX(TabInt T, ElType X)
/* Menghasilkan berapa banyak kemunculan X di T */
/* Jika T kosong menghasilkan 0 */
{
    /* KAMUS LOKAL */
    int count = 0;

    /* ALGORITMA */
    for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T); ++i)
        if  (Elmt(T, i) == X)
            ++count;

    return count;
}
boolean IsAllGenap(TabInt T)
/* Menghailkan true jika semua elemen T genap. T boleh kosong */
{
    /* KAMUS LOKAL */
    boolean Even = true;

    /* KAMUS LOKAL */
    for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T) && Even; ++i)
        if (Elmt(T, i)%2 != 0)
            Even = false;

    return Even;
}

/* ********** SORTING ********** */
void Sort(TabInt *T, boolean asc)
/* I.S. T boleh kosong */
/* F.S. Jika asc = true, T terurut membesar */
/*      Jika asc = false, T terurut mengecil */
/* Proses : Mengurutkan T dengan salah satu algoritma sorting,
  algoritma bebas */
{
    /* KAMUS LOKAL */
    IdxType L, R, mid,
            i, j, k;
    TabInt TL, TR;

    /* ALGORITMA */
    if (GetLastIdx(*T) > GetFirstIdx(*T))
    {
        mid = GetFirstIdx(*T) + (GetLastIdx(*T) - GetFirstIdx(*T))/2;
        L = GetFirstIdx(*T);
        R = mid+1;

        MakeEmpty(&TL, MaxElement(*T)/2 + 1);
        MakeEmpty(&TR, MaxElement(*T)/2 + 1);

        for (i = L; i <= mid; ++i)
            Elmt(TL, i) =  Elmt(*T, i);
        Neff(TL) = i;

        for (i = R; i <= GetLastIdx(*T); ++i)
            Elmt(TR, i-R) =  Elmt(*T, i);
        Neff(TR) = i-(mid+1);

        Sort(&TL, asc);
        Sort(&TR, asc);

        i = GetFirstIdx(TL); j = GetFirstIdx(TR); k = GetFirstIdx(*T);
        if (asc)
        {
            while(i <= GetLastIdx(TL) && j <= GetLastIdx(TR))
            {
                if (Elmt(TL, i) < Elmt(TR, j))
                    Elmt(*T, k++) = Elmt(TL, i++);
                else
                    Elmt(*T, k++) = Elmt(TR, j++);
            }
        }
        else
        {
            while(i <= GetLastIdx(TL) && j <= GetLastIdx(TR))
            {
                if (Elmt(TL, i) > Elmt(TR, j))
                    Elmt(*T, k++) = Elmt(TL, i++);
                else
                    Elmt(*T, k++) = Elmt(TR, j++);
            }
        }

        while (i <= GetLastIdx(TL))
            Elmt(*T, k++) = Elmt(TL, i++);
        while (j <= GetLastIdx(TR))
            Elmt(*T, k++) = Elmt(TR, j++);

        Dealokasi(&TL);
        Dealokasi(&TR);
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void AddAsLastEl(TabInt *T, ElType X)
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
{
    /* ALGORITMA */
    if (!IsFull(*T))
        Elmt(*T, Neff(*T)++) = X;
}
/* ********** MENGHAPUS ELEMEN ********** */
void DelLastEl(TabInt *T, ElType *X)
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
{
    /* ALGORITMA */
    if (!IsEmpty(*T))
        *X = Elmt(*T, --Neff(*T));
}

/* ********* MENGUBAH UKURAN ARRAY ********* */
void GrowTab(TabInt *T, int num)
/* Proses : Menambahkan max element sebanyak num */
/* I.S. Tabel sudah terdefinisi */
/* F.S. Ukuran tabel bertambah sebanyak num */
{
    /* KAMUS LOKAL */
    TabInt temp1;

    /* ALGORITMA */
    MakeEmpty(&temp1, MaxElement(*T));
    CopyTab(*T, &temp1);

    Dealokasi(T);
    MakeEmpty(T, MaxElement(temp1)+num);

    Neff(*T) = Neff(temp1);
    for (IdxType i = GetFirstIdx(temp1); i  <= GetLastIdx(temp1);  ++i)
        Elmt(*T, i) = Elmt(temp1, i);

    /*CopyTab(temp1, T);*/
    Dealokasi(&temp1);

    /*MaxEl(*T) += num;*/
}

void ShrinkTab(TabInt *T, int num)
/* Proses : Mengurangi max element sebanyak num */
/* I.S. Tabel sudah terdefinisi, ukuran MaxEl > num, dan Neff < MaxEl - num. */
/* F.S. Ukuran tabel berkurang sebanyak num. */
{
    /* KAMUS LOKAL */
    TabInt tempTab;

    /* ALGORITMA */
    if (num < MaxEl(*T) && Neff(*T) < MaxEl(*T)-num)
    {
        MakeEmpty(&tempTab, MaxElement(*T));
        CopyTab(*T, &tempTab);

        Dealokasi(T);
        MakeEmpty(T, MaxElement(tempTab)-num);

        Neff(*T) = Neff(tempTab);
        for (IdxType i = GetFirstIdx(tempTab); i <= GetLastIdx(tempTab); ++i)
            Elmt(*T, i) = Elmt(tempTab, i);

        /*CopyTab(tempTab, T);*/
        Dealokasi(&tempTab);

        /*MaxEl(*T) -= num;*/
    }
}

void CompactTab(TabInt *T)
/* Proses : Mengurangi max element sehingga Neff = MaxEl */
/* I.S. Tabel tidak kosong */
/* F.S. Ukuran MaxEl = Neff */
{
    /* KAMUS LOKAL */
    TabInt tempTab;

    /* ALGORITMA */
    if (!IsEmpty(*T))
    {
        MakeEmpty(&tempTab, MaxElement(*T));
        CopyTab(*T, &tempTab);

        Dealokasi(T);
        MakeEmpty(T, NbElmt(tempTab));

        CopyTab(tempTab, T);
        Dealokasi(&tempTab);

        MaxEl(*T) = NbElmt(*T);
    }
}
