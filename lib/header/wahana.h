/* ADT Upgrade Wahana */
/* Implementasi dengan menggunakan tree */
/* Untuk membeli wahana berarti kita mengambil node upgrade pertama */

#include "boolean.h"
#include "resources.h"
#include "jam.h"
#include "point.h"

#ifndef WAHANA_H
#define WAHANA_H

/* Isi simpul setiap upgrade. Dapat mengubah semua properti wahana */
typedef struct {
    unsigned int id; /* ID wahana (ID tree-nya, unik) */
    unsigned short kapasitas; /* Kapasitas wahana */
    unsigned int harga; /* Harga untuk naikin wahana */
    JAM durasi; /* Durasi naikin wahana */
    Kata nama; /* Nama wahana */
    Kata description; /* Deskripsi wahana */
    Resource UpgradeCost; /* Resource yg dibutuhkan untuk upgrade */
    boolean isTaken; /* Upgrade sudah diambil */
} UpgradeType;

/* pointer ke simpul tree */
typedef struct tUpN* addrNode;
/* simpul pada tree */
typedef struct tUpN{
    addrNode left; /* Leaf kiri upgrade */
    addrNode right; /* Leaf kanan upgrade */
    UpgradeType upgradeInfo; /* info dari (upgrade) wahana untuk node */
} UpNode;

/* untuk menyimpan metadata tambahan pada wahana: posisi */
typedef struct TangibleWahana {
	addrNode baseTree;
    int idMap;
	Point posisi;
	unsigned int currentUpgradeID;
    int status; /* 0 - rusak; 1 - berfungsi */
    int used;
    int usedTotal;
} TangibleWahana;
typedef struct TangibleWahana* ATangibleWahana;

/* Definisi Selektor TangibleWahana */
#define IDMap(W) (W)->idMap
#define WahanaPoint(W) (W)->posisi
#define TreeWahana(W) (W)->baseTree
#define UpgradeId(W) (W)->currentUpgradeID

typedef struct WahanaUpgrade{
	ATangibleWahana Wahana;
	unsigned int idUpgrade;
} WahanaUpgradeInfo;
typedef struct WahanaUpgrade* WahanaUpgradeStack;

#define TangibleWahana(P) (P)->Wahana
#define UpgradeID(P) (P)->idUpgrade


/* Definisi WahanaTree : */
/* WahanaTree kosong : P = Nil */

/* Menyimpan informasi tentang wahana dan upgrade-nya */
typedef addrNode WahanaTree;
/* nama node/daun pertama di tiap upgrade tree */
typedef addrNode Wahana;

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
/**
 * Fungsi untuk membuat isi simpul (akar) dari suatu node/simpul.
 *
 * id - id tree wahana
 * kapasitas - kapasitas wahana di node yang ingin diisi
 * harga - harga wahana di node yang ingin diisi
 * durasi - durasi penggunaan wahana di node yang ingin diisi
 * nama - nama wahan di node yang ingin diisi
 * description - deskripsi wahana di node yang ingin diisi
 * cost - harga untuk mengupgrade/mengambil node yang ingin diisi
 */
UpgradeType IsiSimpul(unsigned int id, unsigned short kapasitas, unsigned int harga,
            JAM durasi, Kata nama, Kata description, Resource upCost);

/**
 * Fungsi untuk membuat Simpul kosong dengan ID yang diberikan.
 */
UpgradeType BuatSimpulKosong(unsigned int id);

/**
 * Fungsi untuk membuat isi simpul (akar) dari suatu node/simpul.
 *
 * id - id tree wahana
 * kapasitas - kapasitas wahana di node yang ingin diisi
 * harga - harga wahana di node yang ingin diisi
 * durasi - durasi penggunaan wahana di node yang ingin diisi
 * nama - nama wahan di node yang ingin diisi
 * description - deskripsi wahana di node yang ingin diisi
 * cost - harga untuk mengupgrade/mengambil node yang ingin diisi
 */
void UbahIsiSimpul(WahanaTree *P, unsigned int id, unsigned short kapasitas, unsigned int harga,
            JAM durasi, Kata nama, Kata description, Resource upCost);

/* Manajemen Memory */
/**
 * Mengirimkan addrNode hasil alokasi sebuah elemen
 * Jika alokasi berhasil, maka addrNode tidak Nil, dan misalnya menghasilkan P,
   maka Akar(P) = X, Left(P) = Nil, Right(P)=Nil
 * Jika alokasi gagal, mengirimkan Nil
 *
 * UT - struct berisi informasi node
 */
addrNode AlokasiNodeTree(UpgradeType UT);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */
void DealokasiNodeTree(addrNode P);

/* *** Predikat-Predikat Penting *** */
/* Mengirimkan true jika P adalah pohon biner kosong */
boolean IsTreeEmpty(WahanaTree P);
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */
boolean IsTreeOneElmt(WahanaTree P);
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */
boolean IsUnerLeft(WahanaTree P);
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/
boolean IsUnerRight(WahanaTree P);
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon biner: mempunyai subpohon kiri dan subpohon kanan*/
boolean IsBiner(WahanaTree P);

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

/* *** Searching *** */
/* Mengirimkan true jika ada node dari P yang bernilai X */
boolean SearchTree(WahanaTree P, UpgradeType X);

/**
 * Fungsi untuk mencari node dengan id id.
 *
 * id - id wahana
 */
addrNode SearchUpgrade(WahanaTree P, unsigned int id);

/**
 * Fungsi untuk memeriksa isi informasi dari antara 2 struct info node sama
 * atau tidak
 *
 * UT1 - Struct informasi node pertama
 * UT2 - struct informasi node kedua
 */
boolean IsInfoNodeSame(UpgradeType UT1, UpgradeType UT2);

///**
// * Fungsi untuk mempersiapkan pembangunan wahanna.
// * Sama saja dengan mengamil upgrade ke-0 wahana.
// * Akan memasukkan aksi ini ke stackAksi (variabel global)
// *
// * Wahana - Tree Wahana yang akan di-bangun
// * Loc - Lokasi pembangunan
// */
//ATangibleWahana BuildWahana(UpgradeType Wahana, Point Loc);
///**
// * Fungsi untuk mengeksekusi aksi build dari stackAksi (variabel global)
// * Akan mengepop aksi ini dari stackAksi (variabel global)
// *
// * Wahana - TangibleWahana dari Stack
// */

/**
 * Fungsi buat nyari upgrade dari suatu wahana.
 * Kalau tidak ditemukan, akan mengembalikan Nil.
 */
addrNode cariUpgrade (WahanaTree wahana, int UpID);

boolean hasUpgradeName(WahanaTree wahana, Kata nama);

void PrintPathTo(WahanaTree wahana, Kata nama);

#endif
