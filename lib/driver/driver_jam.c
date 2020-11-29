#include <stdlib.h>
#include <stdio.h>
#include "../header/jam.h"
#include "boolean.h"

#define nl printf("\n")

int main() {
    // Kamus
    char ctemp;
    JAM J,K;
    long ngikutinlogkomyes;

    // ALgoritma
    printf("BACA JAM");nl;
    BacaJAM(&J);nl;

    printf("JAM -> DETIK");nl;
    ngikutinlogkomyes = JAMToDetik(J);
    printf("%ld", ngikutinlogkomyes);nl;
    printf("DETIK + 1000s-> JAM");nl;
    K = DetikToJAM(ngikutinlogkomyes+1000l);
    TulisJAM(K);nl;nl;

    printf("PRINT JAM");nl;
    printf("jam 1 ");
    TulisJAM(J);nl;
    printf("jam 2 ");
    TulisJAM(K);nl;nl;
    
    printf("DURASI JAM");nl;
    ngikutinlogkomyes = Durasi(J,K);
    printf("%ld detik\n", ngikutinlogkomyes);nl;

    printf("EQUIVALENCE");nl;
    if (JEQ(J,K)) printf("Jam 1 dan Jam 2 sama\n");
    if (JNEQ(J,K)) printf("Jam 1 dan Jam 2 beda\n");
    if (JLT(J,K)) printf("Jam 1 kurang dari Jam 2\n");
    if (JGT(J,K)) printf("Jam 1 lebih dari Jam 2\n");nl;
    
    printf("NEXT/PREV");nl;
    printf("jam 1 \t\t\t");
    TulisJAM(J);nl;
    printf("jam 1 next detik\t");
    NextDetik(J);
    TulisJAM(J);nl;
    printf("jam 1 prev detik\t");
    PrevDetik(J);
    TulisJAM(J);nl;
    printf("jam 1 prev 1000 detik\t");
    PrevNDetik(J, 1000);
    TulisJAM(J);nl;
    printf("jam 1 next 1000 detik\t");
    NextNDetik(J, 1000);
    TulisJAM(J);nl;
    printf("END OF PROGRAM\n");
    return 0;
}