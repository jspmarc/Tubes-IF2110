/* ADT Upgrade Wahana */
/* Implementasi dengan menggunakan tree */
/* Untuk membeli wahana berarti kita mengambil node upgrade pertama */

#include "boolean.h"
#include "resources.h"
#include "jam.h"

#ifndef WAHANA_H
#define WAHANA_H

typedef struct {
    unsigned char id; /* ID wahana (ID tree-nya, unik) */
    unsigned short kapasitas; /* Kapasitas wahana */
    unsigned int harga; /* Harga untuk naikin wahana */
    JAM durasi; /* Durasi naikin wahana */
    char* nama; /* Nama wahana */
    Resource UpgradeCost; /* Resource yg dibutuhkan untuk upgrade */
    boolean isTaken; /* Upgrade sudah diambil */
} UpgradeType;

typedef struct tUpN* addrNode;
typedef struct tUpN{
    addrNode left; /* Leaf kiri upgrade */
    addrNode right; /* Leaf kanan upgrade */
    UpgradeType upgradeInfo; /* info dari (upgrade) wahana untuk node */
} UpNode;


/* Definisi PohonBiner : */
/* Pohon Biner kosong : P = Nil */
typedef addrNode WahanaTree;

/* *** PROTOTYPE *** */

/* *** Selektor *** */
#define Akar(P) (P)->upgradeInfo
#define Left(P) (P)->left
#define Right(P) (P)->right

/* *** Konstruktor *** */
/* Menghasilkan sebuah pohon biner dari Akar, L, dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (Nil) jika alokasi gagal */
WahanaTree Tree(UpgradeType Akar, WahanaTree L, WahanaTree R);
/* I.S. Akar, L, R terdefinisi. P Sembarang */
/* F.S. Membentuk pohon P dengan Akar(P)=Akar, Left(P)=L, dan Right(P)=R
   jika alokasi berhasil. P = Nil jika alokasi gagal. */
void MakeTree(UpgradeType Akar, WahanaTree L, WahanaTree R, WahanaTree *P);

void MakeDaun(char* name, char* desc, Resource resourceCost);

/* Manajemen Memory */
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak Nil, dan misalnya menghasilkan P,
  maka Akar(P) = X, Left(P) = Nil, Right(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
addrNode AlokasiNodeTree(char* name, char* desc, Resource r);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */
void DealokasiNodeTree(addrNode P);

/* I.S. P boleh kosong */
/* F.S. P bertambah simpulnya, dengan X sebagai simpul daun terkiri */
void AddDaunTerkiri(WahanaTree *P, UpgradeType X);
/* I.S. P tidak kosong, X adalah salah satu daun Pohon Biner P */
/* F.S. P bertambah simpulnya, dengan Y sebagai anak kiri X (jika Kiri = true), atau
        sebagai anak Kanan X (jika Kiri = false) */
/*		Jika ada > 1 daun bernilai X, diambil daun yang paling kiri */
void AddDaun(WahanaTree *P, UpgradeType X, UpgradeType Y, boolean Kiri);
/* I.S. P tidak kosong */
/* F.S. P dihapus daun terkirinya, dan didealokasi, dengan X adalah info yang semula
        disimpan pada daun terkiri yang dihapus */
void DelDaunTerkiri(WahanaTree *P, UpgradeType *X);
/* I.S. P tidak kosong, minimum ada 1 daun bernilai X. */
/* F.S. Semua daun bernilai X dihapus dari P. */
void DelDaun(WahanaTree *P, UpgradeType X);

/* *** Traversal *** */
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara preorder: akar, pohon kiri, dan pohon kanan.
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup ().
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh:
   (A()()) adalah pohon dengan 1 elemen dengan akar A
   (A(B()())(C()())) adalah pohon dengan akar A dan subpohon kiri (B()()) dan subpohon kanan (C()()) */
void PrintPreorder(WahanaTree P);
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara inorder: pohon kiri, akar, dan pohon kanan.
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup ().
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh:
   (()A()) adalah pohon dengan 1 elemen dengan akar A
   ((()B())A(()C())) adalah pohon dengan akar A dan subpohon kiri (()B()) dan subpohon kanan (()C()) */
void PrintInorder(WahanaTree P);
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara postorder: pohon kiri, pohon kanan, dan akar.
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup ().
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh:
   (()()A) adalah pohon dengan 1 elemen dengan akar A
   ((()()B)(()()C)A) adalah pohon dengan akar A dan subpohon kiri (()()B) dan subpohon kanan (()()C) */
void PrintPostorder(WahanaTree P);
/* I.S. P terdefinisi, h adalah jarak indentasi (spasi) */
/* F.S. Semua simpul P sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */
/* Contoh, jika h = 2:
1) Pohon preorder: (A()()) akan ditulis sbb:
A
2) Pohon preorder: (A(B()())(C()())) akan ditulis sbb:
A
  B
  C
3) Pohon preorder: (A(B(D()())())(C()(E()()))) akan ditulis sbb:
A
  B
    D
  C
    E
*/
void PrintTree(WahanaTree P, int h);

void BuildWahana();
void ExecBuild();

void UpgradeWahana();
void ExecUpgrade();

#endif
