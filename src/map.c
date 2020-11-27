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
// #include "../lib/header/globals.h"
#include <stdio.h>
#include <stdlib.h>

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

MAP map1;
MAP map2;
MAP map3;
MAP map4;

Point playerPos;
int crrntMapID;

Graph jaringanMap;

int MiddleOf(indeks N) {
  /* Return nilai tengah dari suatu bilangan */
  return (N/2 + N%2);
}

void InitiateMapGraph() {
	/* Ada 4 peta = 4 node */
	/* Edge yang dimasukkan vertical dulu baru horizontal */
	adrNode Pn;


	GraphFirst(jaringanMap) = AlokNode(1);
	
	InsertEdge(&jaringanMap, 1, 4);
	InsertEdge(&jaringanMap, 1, 2);

	InsertNode(&jaringanMap, 2, &Pn);
	InsertEdge(&jaringanMap, 2, 3);
	InsertEdge(&jaringanMap, 2, 1);

	InsertNode(&jaringanMap, 2, &Pn);
	InsertEdge(&jaringanMap, 3, 2);
	InsertEdge(&jaringanMap, 3, 4);

	InsertNode(&jaringanMap, 2, &Pn);
	InsertEdge(&jaringanMap, 4, 1);
	InsertEdge(&jaringanMap, 4, 3);
}

MAP WhichMap() {
	if (crrntMapID == 1) {
		return map1;
	} else if (crrntMapID == 2) {
		return map2;
	} else if (crrntMapID == 3) {
		return map3;
	} else if (crrntMapID == 4) {
		return map4;
	}
}

void ShowMap() {
  MATRIKS peta;
	MAP map;

	map = WhichMap();

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
    Elmt(peta, Ordinat(Gate1(map)), Absis(Gate1(map))) = '<';
  } else if ((crrntMapID == 2) || (crrntMapID == 3)) {
    Elmt(peta, Ordinat(Gate1(map)), Absis(Gate1(map))) = '>';
  }

  if ((crrntMapID == 1) || (crrntMapID == 2)) {
    Elmt(peta, Ordinat(Gate2(map)), Absis(Gate2(map))) = 'v';
  } else if ((crrntMapID == 3) || (crrntMapID == 4)) {
    Elmt(peta, Ordinat(Gate2(map)), Absis(Gate2(map))) = '^';
  }

  Elmt(peta, Ordinat(Office(map)), Absis(Office(map))) = 'O';
  Elmt(peta, Ordinat(Antrian(map)), Absis(Antrian(map))) = 'A';
  Elmt(peta, Ordinat(playerPos), Absis(playerPos)) = 'P';


  TulisMATRIKS(peta); printf("\n");
}

void MoveW () {
  /* KAMUS */
	MAP map;

  /* ALGORITMA */
	map = WhichMap();
  // player ke arah utara
  Ordinat(playerPos)--;
  // jika player masuk tembok
  if (Ordinat(playerPos) == 0) {
    // eh temboknya ternyata pager
    if (PointEQ(playerPos, Gate2(map))) {
      /* pindah currentmap */
			if (crrntMapID == 3) {
				if (SearchEdge(jaringanMap, 3, 2) != Nil) {
					crrntMapID = 2;
					Ordinat(playerPos) = NBrs(map);
					Absis(playerPos) = Absis(Gate2(map));
				}
			} else if (crrntMapID == 4) {
				if (SearchEdge(jaringanMap, 4, 1) != Nil) {
					crrntMapID = 1;
					Ordinat(playerPos) = NBrs(map);
					Absis(playerPos) = Absis(Gate2(map));
				}
			}
    } else {
      /* mundur lagi, keluar dari tembok */
      Ordinat(playerPos)++;
    }
  }
}

void MoveA () {
  /* KAMUS */
	MAP map;

  /* ALGORITMA */
	map = WhichMap();
  // player ke arah utara
  Absis(playerPos)--;
  // jika player masuk tembok
  if (Absis(playerPos) == 0) {
    // eh temboknya ternyata pager
    if (PointEQ(playerPos, Gate1(map))) {
      /* pindah currentmap */
			if (crrntMapID == 1) {
				printf("%p\n", SearchEdge(jaringanMap, 1, 2));
				if (SearchEdge(jaringanMap, 1, 2) != Nil) {
					crrntMapID = 2;
					Ordinat(playerPos) = Ordinat(Gate1(map));
					Absis(playerPos) = NKol(map);
				}
			} else if (crrntMapID == 4) {
				if (SearchEdge(jaringanMap, 4, 3) != Nil) {
					crrntMapID = 3;
					Ordinat(playerPos) = Ordinat(Gate1(map));
					Absis(playerPos) = NKol(map);
				}
			}
    } else {
      /* mundur lagi, keluar dari tembok */
      Absis(playerPos)++;
    }
  }
}

void MoveS () {
  /* KAMUS */
	MAP map;

  /* ALGORITMA */
	map = WhichMap();
  // player ke arah utara
  Ordinat(playerPos)++;
  // jika player masuk tembok
  if (Ordinat(playerPos) == NBrs(map) + 1) {
    // eh temboknya ternyata pager
    if (PointEQ(playerPos, Gate2(map))) {
      /* pindah currentmap */
			if (crrntMapID == 1) {
				if (SearchEdge(jaringanMap, 1, 4) != Nil) {
					crrntMapID = 4;
					Ordinat(playerPos) = 1;
					Absis(playerPos) = Absis(Gate2(map));
				}
			} else if (crrntMapID == 2) {
				if (SearchEdge(jaringanMap, 2, 3) != Nil) {
					crrntMapID = 3;
					Ordinat(playerPos) = 1;
					Absis(playerPos) = Absis(Gate2(map));
				}
			}
    } else {
      /* mundur lagi, keluar dari tembok */
      Ordinat(playerPos)--;
    }
  }
}

void MoveD () {
  /* KAMUS */
	MAP map;

  /* ALGORITMA */
	map = WhichMap();

  // player ke arah utara
  Absis(playerPos)++;
  // jika player masuk tembok
  if (Absis(playerPos) == NKol(map) + 1) {
    // eh temboknya ternyata pager
    if (PointEQ(playerPos, Gate1(map))) {
      /* pindah currentmap */
			if (crrntMapID == 2) {
				if (SearchEdge(jaringanMap, 2, 1) != Nil) {
					crrntMapID = 1;
					Ordinat(playerPos) = Ordinat(Gate1(map));
					Absis(playerPos) = 1;
				}
			} else if (crrntMapID == 3) {
				if (SearchEdge(jaringanMap, 3, 4) != Nil) {
					crrntMapID = 4;
					Ordinat(playerPos) = Ordinat(Gate1(map));
					Absis(playerPos) = 1;
				}
			}
    } else {
      /* mundur lagi, keluar dari tembok */
      Absis(playerPos)--;
    }
  }
}
