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

#include "matriks.h"
#include "point.h"
#include "graph.h"
#include "array.h"
#include "listlinier.h"
#include "wahana.h"
#include <stdio.h>

#ifndef MAP_H
#define MAP_H

/* Gate1 : yang di sumbu y */
/* Gate2 : yang di sumbu x */
typedef struct {
  int MapID;
  Point MapSize;
  Point Gate1;
  Point Gate2;
  Point Office;
  Point Antrian;
} MAP;

#define ID(M) (M).MapID
#define MapSize(M) (M).MapSize
#define NBrs(M) Ordinat(MapSize(M))
#define NKol(M) Absis(MapSize(M))
#define Gate1(M) (M).Gate1
#define Gate2(M) (M).Gate2
#define Office(M) (M).Office
#define Antrian(M) (M).Antrian

// extern MAP map1;
// extern MAP map2;
// extern MAP map3;
// extern MAP map4;

// extern Point playerPos;
// extern int crrntMapID;

// extern int jaringanMap;

boolean isNutupinGate(Point titiek);
/* Memeriksa apakah titiek menutupi gate */
/*
    Jika di kanan atau kiri gate1 atau
    di kanan atau di kiri gate2 dari map
*/

int MiddleOf(indeks N);
/* Return nilai tengah dari suatu bilangan */

void InitiateMapGraph();
/* Menginisiasi Graph yang menghubungkan peta-peta(nodes) */

MAP WhichMap(int id);
/* Mengembalikan map sesuai id */

void ShowMap();
/* Membuat matriks peta lokasi player dan menampilkannya 
    bersama elemen-elemen yang ada */

/* *** PERGERAKAN PLAYER ***  */
void MoveW ();
/* Pemain bergerak ke atas, ordinat pemain berkurang */
/* if di atas pemain == tembok, then tidak{Psho} berubah */
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

void InitiateMap();
/* Menyiapkan peta */

/**
 * Fungsi untuk mencari wahana seitar position (sebagai argumen), kemudian
 * hasil pencarian akan dimasukkan ke dalam suatu array
 */
array WahanaSekitarPosisi(Point position);

ATangibleWahana InteraksiWahanaSekitarPosisi(Point position);

#endif
