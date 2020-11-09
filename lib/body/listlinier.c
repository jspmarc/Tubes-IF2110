/* File : listlinier.c */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */
/* infotype adalah integer */
#include "../header/listlinier.h"
#include "boolean.h"
#include <stdlib.h>
#include <stdio.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/

/* Mengirim true jika list kosong */
boolean IsEmpty (List L)
{
    return First(L) == Nil;
}

/****************** PEMBUATAN LIST KOSONG ******************/

/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
void CreateEmpty (List *L)
{
    First(*L) = Nil;
}

/****************** Manajemen Memori ******************/

/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
address Alokasi (infotype X)
{
    address P;

    P = (address) malloc(sizeof(ElmtList));
    if  (P != Nil)
    {
        Info(P) = X;
        Next(P) = Nil;
    }

    return P;
}

/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
void Dealokasi (address *P)
{
    free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
/* Mencari apakah ada elemen list dengan info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
address Search (List L, infotype X)
{
    address P;

    P =  First(L);
    if (!IsEmpty(L))
    {
        while (Info(P) != X && Next(P) != Nil)
            P = Next(P);

        return Info(P) == X ? P : Nil;
    }
    else
        return Nil;
}

/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
boolean FSearch (List L, address P)
{
    address curP;

    curP = First(L);
    while (curP != P && curP != Nil)
        curP = Next(curP);

    return curP == Nil;
}

/* Mengirimkan address elemen sebelum elemen yang nilainya=X */
/* Mencari apakah ada elemen list dengan Info(P)=X */
/* Jika ada, mengirimkan address Prec, dengan Next(Prec)=P dan Info(P)=X. */
/* Jika tidak ada, mengirimkan Nil */
/* Jika P adalah elemen pertama, maka Prec=Nil */
/* Search dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah Search akan dilakukan operasi lain */
address SearchPrec (List L, infotype X)
{
    address P;

    P = First(L);
    if (IsEmpty(L) || Info(P) == X)
        return Nil;

    for(; Info(Next(P)) != X && Next(Next(P)) != Nil; P = Next(P));

    /* Info(Next(P)) == X atau P satu node sebelum node terakhir */

    if (Info(Next(P)) == X)
        return P;

    /* Artinya Info(Next(P)) bukan X, meskipun P satu node sebelum node
     * terakhir, akan tetap masuk ke if apabila X ada di Info node terakhir */
    return Nil;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVFirst (List *L, infotype X)
{
    address P;

    P = Alokasi(X);
    if (P != Nil)
        InsertFirst(L, P);
}
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
void InsVLast (List *L, infotype X)
{
    address P;

    P = Alokasi(X);
    if (P != Nil)
        InsertLast(L, P);
}

/*** PENGHAPUSAN ELEMEN ***/
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void DelVFirst (List *L, infotype *X)
{
    address P;

    DelFirst(L, &P);
    *X = Info(P);
    Dealokasi(&P);
}
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
void DelVLast (List *L, infotype *X)
{
    address P;

    DelLast(L, &P);
    *X = Info(P);
    Dealokasi(&P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
void InsertFirst (List *L, address P)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
    Next(P) = First(*L);
    First(*L) = P;
}
void InsertAfter (List *L, address P, address Prec)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
    Next(P) = Next(Prec);
    Next(Prec) = P;
}
void InsertLast (List *L, address P)
{
    address curNode;

    if (IsEmpty(*L))
        InsertFirst(L, P);
    else
    {
        curNode = First(*L);
        while (Next(curNode) != Nil)
            curNode = Next(curNode);

        Next(curNode) = P;
    }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void DelFirst (List *L, address *P)
{
    *P = First(*L);
    First(*L) = Next(*P);
}
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
void DelP (List *L, infotype X)
{
    address P, bP;

    if (!IsEmpty(*L))
    {
        P = First(*L);
        bP = Nil;
        while (Info(P) != X && Next(P) != Nil)
        {
            bP = P;
            P = Next(P);
        }

        if (bP == Nil && Info(P) == X) /* X adalah elemen pertama */
        {
            DelFirst(L, &bP);
            Dealokasi(&P);
        }
        else if (Info(P) == X)
        {
            Next(bP) = Next(P);
            Dealokasi(&P);
        }
    }
}
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
void DelLast (List *L, address *P)
{
    address V, beforeV;

    V = First(*L);
    beforeV = Nil;
    while (Next(V) != Nil)
    {
        beforeV = V;
        V = Next(V);
    }

    *P = V;
    if (beforeV != Nil) /* Bukan elemen pertama */
        Next(beforeV) = Nil;
    else
        First(*L) = Nil;
}
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
void DelAfter (List *L, address *Pdel, address Prec)
{
    /* Pdel adalah node setelah Prec, node yang mau dihapus */
    *Pdel = Next(Prec);

    Next(Prec) = Next(*Pdel);
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
void PrintInfo (List L)
{
    printf("[");
    for (address P = First(L); P != Nil; P = Next(P))
    {
        if (Next(P) != Nil)
            printf("%d,", Info(P));
        else
            printf("%d", Info(P));
    }
    printf("]");
}
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
int NbElmt (List L)
{
    int count = 0;

    for (address P = First(L); P != Nil; P = Next(P), ++count);

    return count;
}

/*** Prekondisi untuk Max/Min/rata-rata : List tidak kosong ***/
/* Mengirimkan nilai info(P) yang maksimum */
infotype Max (List L)
{
    address P;
    infotype max;

    P = First(L);
    max = Info(P);
    P = Next(P);
    for (; P != Nil; P = Next(P))
        max = Info(P) > max ? Info(P) : max;

    return max;
}
/* Mengirimkan address P, dengan info(P) yang bernilai maksimum */
address AdrMax (List L)
{
    address P, maxP;

    P = First(L);
    maxP = P;
    P = Next(P);
    for (; P != Nil; P = Next(P))
        maxP = Info(maxP) > Info(P) ? maxP : P;

    return maxP;
}
/* Mengirimkan nilai info(P) yang minimum */
infotype Min (List L)
{
    address P;
    infotype min;

    P = First(L);
    min = Info(P);
    P = Next(P);
    for (; P != Nil; P = Next(P))
        min = Info(P) < min ? Info(P) : min;

    return min;
}
/* Mengirimkan address P, dengan info(P) yang bernilai minimum */
address AdrMin (List L)
{
    address P, minP;

    P = First(L);
    minP = P;
    P = Next(P);
    for (; P != Nil; P = Next(P))
        minP = Info(minP) < Info(P) ? minP : P;

    return minP;
}
/* Mengirimkan nilai rata-rata info(P) */
float Average (List L)
{
    address P = First(L);
    float sum = 0;
    int count = 0;

    for(; P != Nil; sum += Info(P), ++count, P = Next(P));

    return sum/count;
}

/****************** PROSES TERHADAP LIST ******************/
/* Delete semua elemen list dan alamat elemen di-dealokasi */
void DelAll (List *L)
{
    infotype _;

    for (address P = First(*L); Next(P) != Nil;)
    {
        address tempP;
        DelLast(L, &tempP);
        Dealokasi(&tempP);
    }

    /* P ada di node terakhir */
    DelVFirst(L, &_);
}

/* I.S. sembarang. */
/* F.S. elemen list dibalik : */
/* Elemen terakhir menjadi elemen pertama, dan seterusnya. */
/* Membalik elemen list, tanpa melakukan alokasi/dealokasi. */
/* Credit to Suggoi */
void InversList (List *L)
{
    address P, tempP;
    int Q;

    if (!IsEmpty(*L))
    {
        DelLast(L, &tempP);
        InsertFirst(L, tempP);
        P = tempP;

        Q = NbElmt(*L)-1;
        while(Q--)
        {
            DelLast(L, &tempP);
            InsertAfter(L, tempP, P);
            P = tempP;
        }
    }
}

/* Mengirimkan list baru, hasil invers dari L */
/* dengan menyalin semua elemn list. Alokasi mungkin gagal. */
/* Jika alokasi gagal, hasilnya list kosong */
/* dan semua elemen yang terlanjur di-alokasi, harus didealokasi */
List FInversList (List L)
{
    List newL;

    CreateEmpty(&newL);
    CpAlokList(L, &newL);
    InversList(&newL);

    return newL;
}

/* I.S. L1 sembarang. F.S. L2=L1 */
/* L1 dan L2 "menunjuk" kepada list yang sama.*/
/* Tidak ada alokasi/dealokasi elemen */
void CopyList (List *L1, List *L2)
{
    First(*L2) = First(*L1);
}

/* Mengirimkan list yang merupakan salinan L */
/* dengan melakukan alokasi. */
/* Jika ada alokasi gagal, hasilnya list kosong dan */
/* semua elemen yang terlanjur di-alokasi, harus didealokasi */
List FCopyList (List L)
{
    address P, P2, newP2;
    List L2;

    /* Menyalin elemen pertama */
    P = First(L);
    CreateEmpty(&L2);
    P2 = Alokasi(Info(P));
    if (P2 == Nil) /* Alokasi gagal */
        return L2;
    First(L2) = P2;

    P = Next(P);

    /* P menunjuk ke node kedua */

    for (; P != Nil; P = Next(P), P2 = Next(P2))
    {
        newP2 = Alokasi(Info(P));
        if (newP2 == Nil) /* Alokasi gagal */
        {
            DelAll(&L2);
            return L2;
        }
        Next(P2) = newP2;
    }

    return L2;
}

/* I.S. Lin sembarang. */
/* F.S. Jika semua alokasi berhasil,maka Lout berisi hasil copy Lin */
/* Jika ada alokasi yang gagal, maka Lout=Nil dan semua elemen yang terlanjur dialokasi, didealokasi */
/* dengan melakukan alokasi elemen. */
/* Lout adalah list kosong jika ada alokasi elemen yang gagal */
void CpAlokList (List Lin, List *Lout)
{
    address P, P2, newP2;

    /* Menyalin elemen pertama */
    P = First(Lin);
    P2 = Alokasi(Info(P));
    if (P2 == Nil) /* Alokasi gagal */
        return;
    First(*Lout) = P2;

    P = Next(P);

    /* P menunjuk ke node kedua */

    for (; P != Nil; P = Next(P), P2 = Next(P2))
    {
        newP2 = Alokasi(Info(P));
        if (newP2 == Nil) /* Alokasi gagal */
        {
            DelAll(Lout);
            return;
        }
        Next(P2) = newP2;
    }
}

/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 & L2 */
/* Jika semua alokasi berhasil, maka L3 adalah hasil konkatenasi*/
/* Jika ada alokasi yang gagal, semua elemen yang sudah dialokasi */
/* harus di-dealokasi dan L3=Nil*/
/* Konkatenasi dua buah list : L1 & L2 menghasilkan L3 yang "baru" */
/* Elemen L3 adalah hasil alokasi elemen yang “baru”. */
/* Jika ada alokasi yang gagal, maka L3 harus bernilai Nil*/
/* dan semua elemen yang pernah dialokasi didealokasi */
void Konkat (List L1, List L2, List * L3)
{
    List L4, L5;

    CreateEmpty(&L4);
    CreateEmpty(&L5);

    if (!IsEmpty(L1)) /* L1 tidak kosong  */
    {
        CpAlokList(L1, &L4);
        if (IsEmpty(L2)) /* L1 tidak kosong, L2 kosong */
        {
            CpAlokList(L4, L3);
            return;
        }
        /* L1 dan L2 tidak kosong */
        CpAlokList(L2, &L5);
        Konkat1(&L4, &L5, L3);
    }
    if (IsEmpty(L1) && !IsEmpty(L2)) /* L1 kosong, L2 tidak kosong */
    {
        CpAlokList(L2, L3);
        PrintInfo(*L3);
        return;
    }
}

/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */
void Konkat1 (List *L1, List *L2, List *L3)
{
    address lastL1;

    if  (!IsEmpty(*L1) || !IsEmpty(*L2))
    {
        First(*L3) = First(*L1);

        if (!IsEmpty(*L1))
        {
            lastL1 = First(*L1);
            for(; Next(lastL1) != Nil; lastL1 = Next(lastL1));
            Next(lastL1) = First(*L2);
        }
        else
        {
            First(*L3) = First(*L2);
        }

        First(*L1) = Nil;
        First(*L2) = Nil;
    }
}

/* I.S. L mungkin kosong */
/* F.S. Berdasarkan L, dibentuk dua buah list L1 dan L2 */
/* L tidak berubah: untuk membentuk L1 dan L2 harus alokasi */
/* L1 berisi separuh elemen L dan L2 berisi sisa elemen L */
/* Jika elemen L ganjil, maka separuh adalah NbElmt(L) div 2 */
void PecahList (List *L1, List *L2, List L){
  int i, count;
  address P;

  count = NbElmt(L)/2;
  i = 0;
  CreateEmpty(L1);
  P = First(L);
  while(i < count){
    InsertLast(L1, Alokasi(Info(P)));
    P = Next(P);
    i++;
  }
  CreateEmpty(L2);
  while(P != Nil){
    InsertLast(L2, Alokasi(Info(P)));
    P = Next(P);
  }
}
