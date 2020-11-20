/* FILE : map.c */
/* */

#include "../lib/header/matriks.h"
#include "../lib/header/point.h"
#include <stdio.h>

MATRIKS StartMap (int NBrs, int NKol) {
  MATRIKS M;

  /* +2 untuk pagar */
  MakeMATRIKS(NBrs+2, NKol+2, &M);
  for (int i = 0; i <= GetLastIdxBrs(M); i++) {
      for (int j = 0; j <= GetLastIdxKol(M); j++) {
        if (i == 0 || i == GetLastIdxBrs(M) || j == 0 || j == GetLastIdxKol(M)) {
          Elmt(M, i, j) = '#';
        } else {
          Elmt(M, i, j) = '*';
        }
      }
  }
  return M;
}

void Map() {
  /* KAMUS */
  int x;
  int y;
  int MapSize;

  /* ALGORITMA */
  /* Buat peta dasar */
  MapSize = 5;
  MATRIKS Map = StartMap(MapSize, MapSize);
  Point PlayerLoc = MakePoint(MapSize/2 + 1, MapSize/2 + 1);
  x = Absis(PlayerLoc);
  y = Ordinat(PlayerLoc);
  Elmt(Map, x, y) = 'P';
}

void MoveW (MATRIKS *Map, Point *PlayerLoc) {
  /* KAMUS */
  int x;
  int y;

  /* ALGORITMA */
  // Jika tidak nabrak
  if (Ordinat(*PlayerLoc) != GetFirstIdxKol(*Map)+1) {
    // Convert double to int
    // Ubah lokasi tag 'P' menjadi '*'
    x = Absis(*PlayerLoc);
    y = Ordinat(*PlayerLoc);
    Elmt(*Map, x, y) = '*';

    // Ubah lokasi tag 'P' dari '*' menjadi 'P'
    Ordinat(*PlayerLoc)--;
    Elmt(*Map, x, y--) = 'P';
  }
}

void MoveA (MATRIKS *Map, Point *PlayerLoc) {
  /* KAMUS */
  int x;
  int y;

  /* ALGORITMA */
  if (Ordinat(*PlayerLoc) != GetFirstIdxBrs(*Map)+1) {
    // Ubah lokasi tag 'P' menjadi '*'
    x = Absis(*PlayerLoc);
    y = Ordinat(*PlayerLoc);
    Elmt(*Map, x, y) = '*';

    // Ubah lokasi tag 'P' dari '*' menjadi 'P'
    Absis(*PlayerLoc)--;
    Elmt(*Map, x--, y) = 'P';
  }
}

void MoveS (MATRIKS *Map, Point *PlayerLoc) {
  /* KAMUS */
  int x;
  int y;

  /* ALGORITMA */
  if (Ordinat(*PlayerLoc) != GetLastIdxKol(*Map)-1) {
    // Ubah lokasi tag 'P' menjadi '*'
    x = Absis(*PlayerLoc);
    y = Ordinat(*PlayerLoc);
    Elmt(*Map, x, y) = '*';

    // Ubah lokasi tag 'P' dari '*' menjadi 'P'
    Ordinat(*PlayerLoc)++;
    Elmt(*Map, x, y++) = 'P';
  }
}

void MoveD (MATRIKS *Map, Point *PlayerLoc) {
  /* KAMUS */
  int x;
  int y;

  /* ALGORITMA */
  if (Ordinat(*PlayerLoc) != GetLastIdxBrs(*Map)-1) {
    Absis(*PlayerLoc)++;
    // Ubah lokasi tag 'P' menjadi '*'
    x = Absis(*PlayerLoc);
    y = Ordinat(*PlayerLoc);
    Elmt(*Map, x, y) = '*';

    // Ubah lokasi tag 'P' dari '*' menjadi 'P'
    Absis(*PlayerLoc)++;
    Elmt(*Map, x++, y) = 'P';
  }
}