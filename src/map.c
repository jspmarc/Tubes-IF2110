/* FILE : map.c */
/* */


/* Bentuk map */
/*
  2             1
  #######       #######
  #*****#       #*****#
  #*****#       #*****#
  #*****>       <*****#
  #*****#       #*****#
  #*****#       #*****#
  ###v###       ###v###
  
  3             4
  ###^###       ###^###
  #*****#       #*****#
  #*****#       #*****#
  #*****>       <*****#
  #*****#       #*****#
  #*****#       #*****#
  #######       #######
*/

#include "../lib/header/matriks.h"
#include "../lib/header/point.h"
#include "../lib/header/graph.h"
#include "../lib/header/globals.h"
#include <stdio.h>

/* Gate1 : yang di sumbu y */
/* Gate2 : yang di sumbu x */
typedef struct {
  int MapID;
  int NBrs;
  int NKol;
  Point Gate1;
  Point Gate2;
  Point Office;
  Point Antrian;
} MAP;

#define Number(M) (M).Number
#define NBrs(M) (M).NBrs
#define NKol(M) (M).NKol
#define Gate1(M) (M).Gate1
#define Gate2(M) (M).Gate2
#define Office(M) (M).Office
#define Antrian(M) (M).Antrian

MAP Map1;
MAP Map2;
MAP Map3;
MAP Map4;

Point playerPos;
int crrntMapID;

int MiddleOf(indeks N) {
  /* Return nilai tengah dari suatu bilangan */
  return (N/2 + N%2);
}

void ShowMap(int crrntMapID, Point playerPos, MAP map) {
  MATRIKS peta;
  MakeMATRIKS(NBrs(map)+2, NKol(map)+2, &peta);
  for (int i = 0; i <= GetLastIdxBrs(peta); i++) {
    for (int j = 0; j <= GetLastIdxBrs(peta); j++) {
      if (i == 0 || i == GetLastIdxBrs(peta) || j == 0 || j == GetLastIdxKol(peta)) {
        Elmt(peta, i, j) = '#';
      } else {
        Elmt(peta, i, j) = '-';
      }
    }
  }

  if ((crrntMapID == 1) || (crrntMapID == 4)) {
    Elmt(peta, Absis(Gate1(map)), Ordinat(Gate1(map))) = '<';
  } else if ((crrntMapID == 2) || (crrntMapID == 3)) {
    Elmt(peta, Absis(Gate1(map)), Ordinat(Gate1(map))) = '>';
  }

  if ((crrntMapID == 1) || (crrntMapID == 4)) {
    Elmt(peta, Absis(Gate2(map)), Ordinat(Gate2(map))) = 'v';
  } else if ((crrntMapID == 2) || (crrntMapID == 3)) {
    Elmt(peta, Absis(Gate2(map)), Ordinat(Gate2(map))) = '^';
  }

  Elmt(peta, Absis(Office(map)), Ordinat(Office(map))) = 'O';
  Elmt(peta, Absis(Antrian(map)), Ordinat(Antrian(map))) = 'A';
  Elmt(peta, Absis(playerPos), Ordinat(playerPos)) = 'P';


  TulisMATRIKS(peta); printf("\n");
}

void MoveW (MAP map) {
  /* KAMUS */
  int x;
  int y;

  /* ALGORITMA */
  // player ke arah utara
  Ordinat(playerPos)--;
  // jika player masuk tembok
  if (Ordinat(playerPos) == 0) {
    // eh temboknya ternyata pager
    if (PointEQ(playerPos, Gate2(map))) {
      /* pindah */
    } else {
      /* mundur lagi, keluar dari tembok */
      Ordinat(playerPos)++;
    }
  }
}

void MoveA (MAP map) {
  /* KAMUS */
  int x;
  int y;

  /* ALGORITMA */
  // player ke arah utara
  Absis(playerPos)--;
  // jika player masuk tembok
  if (Absis(playerPos) == 0) {
    // eh temboknya ternyata pager
    if (PointEQ(playerPos, Gate1(map))) {
      /* pindah */
    } else {
      /* mundur lagi, keluar dari tembok */
      Absis(playerPos)++;
    }
  }
}

void MoveS (MAP map) {
  /* KAMUS */
  int x;
  int y;

  /* ALGORITMA */
  // player ke arah utara
  Ordinat(playerPos)++;
  // jika player masuk tembok
  if (Ordinat(playerPos) == NBrs(map)) {
    // eh temboknya ternyata pager
    if (PointEQ(playerPos, Gate2(map))) {
      /* pindah */
    } else {
      /* mundur lagi, keluar dari tembok */
      Ordinat(playerPos)--;
    }
  }
}

void MoveD (MAP map) {
  /* KAMUS */
  int x;
  int y;

  /* ALGORITMA */
  // player ke arah utara
  Absis(playerPos)++;
  // jika player masuk tembok
  if (Absis(playerPos) == NKol(map)) {
    // eh temboknya ternyata pager
    if (PointEQ(playerPos, Gate1(map))) {
      /* pindah */
    } else {
      /* mundur lagi, keluar dari tembok */
      Absis(playerPos)--;
    }
  }
}