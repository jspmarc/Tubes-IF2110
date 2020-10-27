/* File: jam.c */
/* Tanggal: 2 September 2020 */
/* Definisi ADT JAM */
/* Josep Marcello
 * 13519164 */

#include "jam.h"
#include <stdio.h>

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsJAMValid (int H, int M, int S)
/* Mengirim true  jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
{
    return ( 0 <= H && H <= 23 &&
             0 <= M && M <= 59 &&
             0 <= S && S <= 59 );
}

/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
JAM MakeJAM (int HH, int MM, int SS)
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk JAM */
{
    /* KAMUS LOKAL */
    JAM guaCapek;

    /* ALGORITMA */
    Hour(guaCapek) = HH;
    Minute(guaCapek) = MM;
    Second(guaCapek) = SS;

    return guaCapek;
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaJAM (JAM * J)
/* I.S. : J tidak terdefinisi */
/* F.S. : J terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk J */
/* yang valid. Tidak mungkin menghasilkan J yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika JAM tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
   diulangi hingga didapatkan jam yang valid. */
/* Contoh:
   60 3 4
   Jam tidak valid
   1 3 4
   --> akan terbentuk JAM <1,3,4> */
{
    /* KAMUS LOKAL */
    int gua,mau,mati;
    /* ALGORITMA */
    scanf("%d %d %d", &gua, &mau, &mati);
    while (!IsJAMValid(gua, mau, mati) ) {
        printf("Jam tidak valid\n");
        scanf("%d %d %d", &gua, &mau, &mati);
    }

    Hour(*J) = gua;
    Minute(*J) = mau;
    Second(*J) = mati;
}

void TulisJAM (JAM J)
/* I.S. : J sembarang */
/* F.S. :   Nilai J ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen J ke layar dalam format HH:MM:SS
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.
   Jika jam / menit / detik hanya satu digit, tuliskan satu digit tanpa 0 di depannya. */
{
    /* ALGORITMA */
    printf("%d:%d:%d", Hour(J), Minute(J), Second(J));
}

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long JAMToDetik (JAM J)
/* Diberikan sebuah JAM, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
/* Rumus : detik = 3600*HH + 60*MM + SS */
/* Nilai maksimum = 3600*23+59*60+59 */
{
    /* ALGORITMA */
    return Hour(J)*3600 + Minute(J)*60 + Second(J);
}

JAM DetikToJAM (long N)
/* Mengirim  konversi detik ke JAM */
/* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah detik yang
   mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus:
   N1 = N mod 86400, baru N1 dikonversi menjadi JAM */
{
    /* KAMUS LOKAL */
    int j,m,d;
    /* ALGORITMA */
    if (N < 0) N += 86400;
    N %= 86400;

    j = N/3600;
    m = (N%3600)/60;
    d = N%60;

    return MakeJAM(j, m, d);
}

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean JEQ (JAM J1, JAM J2)
/* Mengirimkan true jika J1=J2, false jika tidak */
{
    /* ALGORITMA */
    return ( Hour(J1) == Hour(J2) &&
             Minute(J1) == Minute(J2) &&
             Second(J1) == Second(J2) );
}
boolean JNEQ (JAM J1, JAM J2)
/* Mengirimkan true jika J1 tidak sama dengan J2 */
{
    /* ALGORITMA */
    return !JEQ(J1, J2);
}
boolean JLT (JAM J1, JAM J2)
/* Mengirimkan true jika J1<J2, false jika tidak */
{
    /* ALGORITMA */
    return JAMToDetik(J1) < JAMToDetik(J2);
}
boolean JGT (JAM J1, JAM J2)
/* Mengirimkan true jika J1>J2, false jika tidak */
{
    /* ALGORITMA */
    return JAMToDetik(J1) > JAMToDetik(J2);
}
/* *** Operator aritmatika JAM *** */
JAM NextDetik (JAM J)
/* Mengirim 1 detik setelah J dalam bentuk JAM */
{
    /* ALGORITMA */
    /*if (++Second(J) == 60) {*/
        /*if (Minute(J)+1 == 60) {*/
            /*if (Hour(J)+1 == 24)*/
                /*Hour(J) -= 24+1;*/
            /*Minute(J) -= 60+1;*/
        /*}*/
        /*Second(J) -= 60;*/
    /*}*/

    /*return J;*/

    return DetikToJAM(JAMToDetik(J)+1);
}
JAM NextNDetik (JAM J, int N)
/* Mengirim N detik setelah J dalam bentuk JAM */
{
    /* ALGORITMA */
    /*for (int i = 0; i < N; ++i)*/
        /*J = NextDetik(J);*/

    /*return J;*/

    return DetikToJAM(JAMToDetik(J)+N);
}
JAM PrevDetik (JAM J)
/* Mengirim 1 detik sebelum J dalam bentuk JAM */
{
    /* KAMUS LOKAL */
    /*long JdlmDet = JAMToDetik(J)-1;*/
    /* ALGORITMA */
    /*if (--Second(J) == -1) {*/
        /*if (Minute(J)-1 == -1) {*/
            /*if (Hour(J)-1 == -1)*/
                /*Hour(J) += 24;*/
            /*Minute(J) += 60;*/
        /*}*/
        /*Second(J) += 60;*/
    /*}*/

    /*return J;*/

    /*if ( JdlmDet < 0 )*/
        /*JdlmDet += 86400;*/

    return DetikToJAM(JAMToDetik(J)-1);
}
JAM PrevNDetik (JAM J, int N)
/* Mengirim N detik sebelum J dalam bentuk JAM */
{
    /* KAMUS LOKAL */
    /*long JdlmDet = JAMToDetik(J)-N;*/
    /* ALGORITMA */
    /*for (int i = 0; i < N; ++i)*/
        /*J = PrevDetik(J);*/

    /*return J;*/

    /*if ( JdlmDet < 0 )*/
        /*JdlmDet += 86400;*/

    return DetikToJAM(JAMToDetik(J)-N);
}
/* *** Kelompok Operator Aritmetika *** */
long Durasi (JAM JAw, JAM JAkh)
/* Mengirim JAkh-JAw dlm Detik, dengan kalkulasi */
/* Jika JAw > JAkh, maka JAkh adalah 1 hari setelah JAw */
{
    /* ALGORITMA */
    return JAMToDetik(JAw) <= JAMToDetik(JAkh) ?
                JAMToDetik(JAkh) - JAMToDetik(JAw) :
                JAMToDetik(JAkh)+86400 - JAMToDetik(JAw);
}
