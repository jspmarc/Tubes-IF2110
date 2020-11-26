/* File : listlinier.h */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi addressLL dengan pointer */
/* infotype adalah integer */

#ifndef listlinier_H
#define listlinier_H

#include "boolean.h"

#define Nil NULL

typedef int infotype;
typedef struct tElmtlist *addressLL;
typedef struct tElmtlist {
	infotype info;
	addressLL next;
} ElmtLL;
typedef struct {
	addressLL First;
} LL;

/* Definisi list : */
/* LL kosong : LLFirst(L) = Nil */
/* Setiap elemen dengan addressLL P dapat diacu Info(P), LLNext(P) */
/* Elemen terakhir list : jika addressLLnya Last, maka LLNext(Last)=Nil */
#define Info(P) (P)->info
#define LLNext(P) (P)->Next
#define LLFirst(L) ((L).First)

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/

/* Mengirim true jika list kosong */
boolean IsEmpty (LL L);

/****************** PEMBUATAN LIST KOSONG ******************/

/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
void CreateEmpty (LL *L);

/****************** Manajemen Memori ******************/

/* Mengirimkan addressLL hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressLL tidak nil, dan misalnya */
/* menghasilkan P, maka info(P)=X, LLNext(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
addressLL AlokasiLL (infotype X);

/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressLL P */
void Dealokasi (addressLL *P);

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
/* Mencari apakah ada elemen list dengan info(P)= X */
/* Jika ada, mengirimkan addressLL elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
addressLL Search (LL L, infotype X);
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
boolean FSearch (LL L, addressLL P);
/* Mengirimkan addressLL elemen sebelum elemen yang nilainya=X */
/* Mencari apakah ada elemen list dengan Info(P)=X */
/* Jika ada, mengirimkan addressLL Prec, dengan LLNext(Prec)=P dan Info(P)=X. */
/* Jika tidak ada, mengirimkan Nil */
/* Jika P adalah elemen pertama, maka Prec=Nil */
/* Search dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah Search akan dilakukan operasi lain */
addressLL SearchPrec (LL L, infotype X);

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVFirst (LL *L, infotype X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
void InsVLast (LL *L, infotype X);

/*** PENGHAPUSAN ELEMEN ***/
/* I.S. LL L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void DelVFirst (LL *L, infotype *X);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
void DelVLast (LL *L, infotype *X);

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-addressLL P sebagai elemen pertama */
void InsertFirst (LL *L, addressLL P);
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
void InsertAfter (LL *L, addressLL P, addressLL Prec);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
void InsertLast (LL *L, addressLL P);

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
/* I.S. LL tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void DelFirst (LL *L, addressLL *P);
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddressLL P, dengan info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan info(P)=X, maka list tetap */
/* LL mungkin menjadi kosong karena penghapusan */
void DelP (LL *L, infotype X);
/* I.S. LL tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
void DelLast (LL *L, addressLL *P);
/* I.S. LL tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus LLNext(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
void DelAfter (LL *L, addressLL *Pdel, addressLL Prec);

/****************** PROSES SEMUA ELEMEN LIST ******************/
/* I.S. LL mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
void PrintInfo (LL L);
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
int NbElmt (LL L);

/*** Prekondisi untuk Max/Min/rata-rata : LL tidak kosong ***/
/* Mengirimkan nilai info(P) yang maksimum */
infotype Max (LL L);
/* Mengirimkan addressLL P, dengan info(P) yang bernilai maksimum */
addressLL AdrMax (LL L);
/* Mengirimkan nilai info(P) yang minimum */
infotype Min (LL L);
/* Mengirimkan addressLL P, dengan info(P) yang bernilai minimum */
addressLL AdrMin (LL L);
/* Mengirimkan nilai rata-rata info(P) */
float Average (LL L);

/****************** PROSES TERHADAP LIST ******************/
/* Delete semua elemen list dan alamat elemen di-dealokasi */
void DelAll (LL *L);

/* I.S. sembarang. */
/* F.S. elemen list dibalik : */
/* Elemen terakhir menjadi elemen pertama, dan seterusnya. */
/* Membalik elemen list, tanpa melakukan alokasi/dealokasi. */
void InversLL (LL *L);

/* Mengirimkan list baru, hasil invers dari L */
/* dengan menyalin semua elemn list. AlokasiLL mungkin gagal. */
/* Jika alokasi gagal, hasilnya list kosong */
/* dan semua elemen yang terlanjur di-alokasi, harus didealokasi */
LL FInversLL (LL L);

/* I.S. L1 sembarang. F.S. L2=L1 */
/* L1 dan L2 "menunjuk" kepada list yang sama.*/
/* Tidak ada alokasi/dealokasi elemen */
void CopyLL (LL *L1, LL *L2);

/* Mengirimkan list yang merupakan salinan L */
/* dengan melakukan alokasi. */
/* Jika ada alokasi gagal, hasilnya list kosong dan */
/* semua elemen yang terlanjur di-alokasi, harus didealokasi */
LL FCopyLL (LL L);

/* I.S. Lin sembarang. */
/* F.S. Jika semua alokasi berhasil,maka Lout berisi hasil copy Lin */
/* Jika ada alokasi yang gagal, maka Lout=Nil dan semua elemen yang terlanjur dialokasi, didealokasi */
/* dengan melakukan alokasi elemen. */
/* Lout adalah list kosong jika ada alokasi elemen yang gagal */
void CpAlokLL (LL Lin, LL *Lout);

/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 & L2 */
/* Jika semua alokasi berhasil, maka L3 adalah hasil konkatenasi*/
/* Jika ada alokasi yang gagal, semua elemen yang sudah dialokasi */
/* harus di-dealokasi dan L3=Nil*/
/* Konkatenasi dua buah list : L1 & L2 menghasilkan L3 yang "baru" */
/* Elemen L3 adalah hasil alokasi elemen yang “baru”. */
/* Jika ada alokasi yang gagal, maka L3 harus bernilai Nil*/
/* dan semua elemen yang pernah dialokasi didealokasi */
void Konkat (LL L1, LL L2, LL * L3);

/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */
void Konkat1 (LL *L1, LL *L2, LL *L3);

/* I.S. L mungkin kosong */
/* F.S. Berdasarkan L, dibentuk dua buah list L1 dan L2 */
/* L tidak berubah: untuk membentuk L1 dan L2 harus alokasi */
/* L1 berisi separuh elemen L dan L2 berisi sisa elemen L */
/* Jika elemen L ganjil, maka separuh adalah NbElmt(L) div 2 */
void PecahLL (LL *L1, LL *L2, LL L);

#endif
