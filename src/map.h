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

#define Number(M) (M).Number
#define NBrs(M) (M).NBrs
#define NKol(M) (M).NKol
#define Gate1(M) (M).Gate1
#define Gate2(M) (M).Gate2
#define Office(M) (M).Office
#define Antrian(M) (M).Antrian

extern MAP Map1;
extern MAP Map2;
extern MAP Map3;
extern MAP Map4;

extern Point playerPos;
extern int crrntMapID;

  /* Return nilai tengah dari suatu bilangan */
int MiddleOf(indeks N);

void ShowMap(int crrntMapID, Point playerPos, MAP map);
void MoveW (MAP map);
void MoveA (MAP map);
void MoveS (MAP map);
void MoveD (MAP map);
#endif
