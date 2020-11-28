#include <stdlib.h>
#include <stdio.h>
#include "../header/point.h"
#include "boolean.h"

#define nl printf("\n")

int main() {
    // Kamus
    Point P1;
    Point P2;
    Point P3;

    // ALgoritma
    printf("BACA TULIS POINT");nl;
    printf("masukkan x dan y (x y): ");
    BacaPoint(&P1);
    printf("point P1: ");
    TulisPoint(P1);nl;
    printf("point P2: ");
    P2 = MakePoint(Absis(P1),Ordinat(P1));
    TulisPoint(P2);nl;
    nl;

    printf("EKUIVALENSI");nl;
    if(PointEQ(P1,P2)) printf("point p1 dan p2 sama\n");
    if(PointNEQ(P1,P2)) printf("point p1 dan p2 tidak sama\n");nl;

    printf("GESER-GESER POINT");nl;
    printf("P1: ");TulisPoint(P1);nl;
    printf("next x: ");P3 = NextX(P1);TulisPoint(P3);nl;
    printf("next y: ");P3 = NextY(P1);TulisPoint(P3);nl;
    printf("before x: ");P3 = BeforeX(P1);TulisPoint(P3);nl;
    printf("before y: ");P3 = BeforeY(P1);TulisPoint(P3);nl;
    printf("point p1 digeser 3,3 -> "); Geser(&P1,3,3);TulisPoint(P1);
    nl;
    return 0;
}
