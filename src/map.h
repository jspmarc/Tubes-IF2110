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

#ifndef MAP_H
#define MAP_H

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

#define ID(M) (M).MapID
#define NBrs(M) (M).NBrs
#define NKol(M) (M).NKol
#define Gate1(M) (M).Gate1
#define Gate2(M) (M).Gate2
#define Office(M) (M).Office
#define Antrian(M) (M).Antrian

extern MAP map1;
extern MAP map2;
extern MAP map3;
extern MAP map4;

extern Point playerPos;
extern int crrntMapID;

extern int jaringanMap;

  /* Return nilai tengah dari suatu bilangan */
int MiddleOf(indeks N);

void InitiateMapGraph();
/* Menginisiasi Graph yang menghubungkan peta-peta(nodes) */

MAP WhichMap();
/* Mengembalikan map sesuai crrntMapID */

void ShowMap();
/* Membuat matriks peta lokasi player dan menampilkannya 
    bersama elemen-elemen yang ada */

/* *** PERGERAKAN PLAYER ***  */
void MoveW ();
/* Pemain bergerak ke atas, ordinat pemain berkurang */
/* if di atas pemain == tembok, then tidak berubah */
/* if di atas pemain == gate, then pindah currentmap */

void MoveA ();
/* Pemain bergerak ke kiri, absis pemain berkurang */
/* if di kiri pemain == tembok, then tidak berubah */
/* if di kiri pemain == gate, then pindah currentmap */

void MoveS ();
/* Pemain bergerak ke bawah, ordinat pemain bertambah */
/* if di bawah pemain == tembok, then tidak berubah */
/* if di bawah pemain == gate, then pindah currentmap */

void MoveD ();
/* Pemain bergerak ke kanan, absis pemain bertambah */
/* if di kanan pemain == tembok, then tidak berubah */
/* if di kanan pemain == gate, then pindah currentmap */

#endif
