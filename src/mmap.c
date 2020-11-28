/* File : mmap.c */
/* File untuk debug(?) ADT dan fungsi map di map.c */

#include "../lib/header/map.h"
#include "../lib/header/globals.h"

#include <stdio.h>
#include <math.h>

int main () {
    Absis(playerPos) = 1;
    Ordinat(playerPos) = 1;
    crrntMapID = 1;

    /* Keterangan :
        MiddleOf(X + 2) - 1;
        + 2 untuk offset pagar.
        - 1 untuk offset karena indeks yang dipakai dari 0.
    */

    /* inisiasi map1 */
    ID(map1) = 1;
    NBrs(map1) = 5;
    NKol(map1) = 5;
    Absis(Gate1(map1)) = 0;
    Ordinat(Gate1(map1)) = MiddleOf(NBrs(map1) + 2) - 1;
    Absis(Gate2(map1)) = MiddleOf(NKol(map1) + 2) - 1 ;
    Ordinat(Gate2(map1)) = NBrs(map1) + 1;
    Absis(Office(map1)) = MiddleOf(NKol(map1) + 2) - 1;
    Ordinat(Office(map1)) = MiddleOf(NBrs(map1) + 2) - 1;
    Absis(Antrian(map1)) = MiddleOf(NKol(map1) + 2);
    Ordinat(Antrian(map1)) = MiddleOf(NBrs(map1) + 2);

    /* inisiasi map2 */
    ID(map2) = 2;
    NBrs(map2) = 5;
    NKol(map2) = 5;
    Absis(Gate1(map2)) = NKol(map2) + 1;
    Ordinat(Gate1(map2)) = MiddleOf(NBrs(map2) + 2) - 1;
    Absis(Gate2(map2)) = MiddleOf(NKol(map2) + 2) - 1;
    Ordinat(Gate2(map2)) = NBrs(map2) + 1;
    Absis(Office(map2)) = MiddleOf(NKol(map2) + 2) - 1;
    Ordinat(Office(map2)) = MiddleOf(NBrs(map2) + 2) - 1;
    Absis(Antrian(map2)) = MiddleOf(NKol(map2) + 2);
    Ordinat(Antrian(map2)) = MiddleOf(NBrs(map2)+ 2);

    /* inisiasi map3 */
    ID(map3) = 3;
    NBrs(map3) = 5;
    NKol(map3) = 5;
    Absis(Gate1(map3)) = NKol(map3) + 1;
    Ordinat(Gate1(map3)) = MiddleOf(NBrs(map3) + 2) - 1;
    Absis(Gate2(map3)) = MiddleOf(NKol(map3) + 2) -1;
    Ordinat(Gate2(map3)) = 0;
    Absis(Office(map3)) = MiddleOf(NKol(map3) + 2) - 1;
    Ordinat(Office(map3)) = MiddleOf(NBrs(map3) + 2) - 1;
    Absis(Antrian(map3)) = MiddleOf(NKol(map3) + 2);
    Ordinat(Antrian(map3)) = MiddleOf(NBrs(map3) + 2);

    /* inisiasi map4 */
    ID(map4) = 4;
    NBrs(map4) = 5;
    NKol(map4) = 5;
    Absis(Gate1(map4)) = 0;
    Ordinat(Gate1(map4)) = MiddleOf(NBrs(map4) + 2) - 1;
    Absis(Gate2(map4)) = MiddleOf(NKol(map4) + 2) - 1;
    Ordinat(Gate2(map4)) = 0;
    Absis(Office(map4)) = MiddleOf(NKol(map4) + 2) - 1;
    Ordinat(Office(map4)) = MiddleOf(NBrs(map4) + 2) - 1;
    Absis(Antrian(map4)) = MiddleOf(NKol(map4) + 2);
    Ordinat(Antrian(map4)) = MiddleOf(NBrs(map4) + 2);
    
    InitiateMapGraph();
    printf("%d\n", crrntMapID);
    ShowMap();
    MoveS();
    ShowMap();
    MoveS();
    ShowMap();
    MoveA();
    ShowMap();
    

    printf("%d\n", crrntMapID);
    MoveD();
    ShowMap();

    printf("%d\n", crrntMapID);
    MoveA();
    ShowMap();
    printf("%d\n", crrntMapID);
    MoveA();
    ShowMap();
    MoveS();
    ShowMap();
    MoveA();
    ShowMap();
    MoveS();
    ShowMap();
    MoveS();
    ShowMap();
    printf("%d\n", crrntMapID);

    MoveS();
    ShowMap();
    MoveS();
    ShowMap();


    printf("%d\n", crrntMapID);
    MoveW();
    ShowMap();
    MoveW();
    ShowMap();
    MoveW();
    ShowMap();

    printf("%d\n", crrntMapID);
    MoveW();
    ShowMap();
    MoveD();
    ShowMap();
    MoveW();
    ShowMap();
    MoveD();
    ShowMap();
    MoveD();
    ShowMap();

    printf("%d\n", crrntMapID);
    MoveD();
    ShowMap();
    MoveD();
    ShowMap();

    return 0;

    /* gcc -o tes src/mmap.c src/map.c lib/body/matriks.c lib/body/point.c lib/body/graph.c */
}
