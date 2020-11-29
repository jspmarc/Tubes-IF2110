/* FILE : map.c */
/* */

#include "../header/map.h"
#include "../header/globals.h"
#include "../header/parser.h"
#include <stdio.h>
#include <stdlib.h>

/* Gate1 : yang di sumbu y */
/* Gate2 : yang di sumbu x */
// typedef struct {
//   int MapID;
//	 Point MapSize;
//   Point Gate1;
//   Point Gate2;
//   Point Office;
//   Point Antrian;
// } MAP;

// #define ID(M) (M).MapID
// #define MapSize(M) (M).MapSize;
// #define NBrs(M) Ordinat(MapSize(M));
// #define NKol(M) Absis(MapSize(M));
// #define Gate1(M) (M).Gate1
// #define Gate2(M) (M).Gate2
// #define Office(M) (M).Office
// #define Antrian(M) (M).Antrian

int MiddleOf(indeks N) {
  /* Return nilai tengah dari suatu bilangan */
  return (N/2 + N%2);
}

void InitiateMapGraph() {
	/* Ada 4 peta = 4 node */
	/* Edge yang dimasukkan vertical dulu baru horizontal */
	GraphFirst(jaringanMap) = AlokNode(1);
	
	InsertEdge(&jaringanMap, 1, 4);
	InsertEdge(&jaringanMap, 1, 2);

	InsertEdge(&jaringanMap, 2, 3);
	InsertEdge(&jaringanMap, 2, 1);

	InsertEdge(&jaringanMap, 3, 2);
	InsertEdge(&jaringanMap, 3, 4);

	InsertEdge(&jaringanMap, 4, 1);
	InsertEdge(&jaringanMap, 4, 3);
}

MAP WhichMap(int id) {
	if (id == 1) {
		return map1;
	} else if (id == 2) {
		return map2;
	} else if (id == 3) {
		return map3;
	} else { /* if (id == 4) */
		return map4;
	}
}

void ShowMap() {
  MATRIKS peta;
	MAP map;

	map = WhichMap(crrntMapID);

  MakeMATRIKS(NBrs(map)+2, NKol(map)+2, &peta);
  for (int i = 0; i <= GetLastIdxBrs(peta); i++) {
    for (int j = 0; j <= GetLastIdxKol(peta); j++) {
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
	map = WhichMap(crrntMapID);
  // player ke arah utara
  Ordinat(playerPos)--;
  // jika player masuk tembok
  if (Ordinat(playerPos) == 0) {
    // eh temboknya ternyata pager
    if (PointEQ(playerPos, Gate2(map))) {
      /* pindah currentmap */
        if ((crrntMapID == 3) && (SearchEdge(jaringanMap, 3, 2) != Nil)) {
					crrntMapID = 2;
					map = WhichMap(crrntMapID);
					Ordinat(playerPos) = NBrs(map);
					Absis(playerPos) = Absis(Gate2(map));
        } else if ((crrntMapID == 4) && (SearchEdge(jaringanMap, 4, 1) != Nil)) {
					crrntMapID = 1;
					map = WhichMap(crrntMapID);
					Ordinat(playerPos) = NBrs(map);
					Absis(playerPos) = Absis(Gate2(map));
        }
    } else {
      /* mundur lagi, keluar dari tembok */
      Ordinat(playerPos)++;
    }
  } /* else if (wahana) { // If ada wahana, ga bisa dilewatin
      Ordinat(playerPos)++;
  } */
}

void MoveA () {
  /* KAMUS */
	MAP map;

  /* ALGORITMA */
	map = WhichMap(crrntMapID);
  // player ke arah utara
  Absis(playerPos)--;
  // jika player masuk tembok
  if (Absis(playerPos) == 0) {
    // eh temboknya ternyata pager
    if (PointEQ(playerPos, Gate1(map))) {
      /* pindah currentmap */
			if ((crrntMapID == 1) && (SearchEdge(jaringanMap, 1, 2) != Nil)) {
				crrntMapID = 2;
				map = WhichMap(crrntMapID);
				Ordinat(playerPos) = Ordinat(Gate1(map));
				Absis(playerPos) = NKol(map);
			} else if ((crrntMapID == 4) && (SearchEdge(jaringanMap, 4, 3) != Nil)) {
				crrntMapID = 3;
				map = WhichMap(crrntMapID);
				Ordinat(playerPos) = Ordinat(Gate1(map));
				Absis(playerPos) = NKol(map);
			}
    } else {
      /* mundur lagi, keluar dari tembok */
      Absis(playerPos)++;
    }
  } /* else if (wahana) { // If ada wahana, ga bisa dilewatin
      Absis(playerPos)++;
  } */
}

void MoveS () {
  /* KAMUS */
	MAP map;

  /* ALGORITMA */
	map = WhichMap(crrntMapID);
  // player ke arah utara
  Ordinat(playerPos)++;
  // jika player masuk tembok
  if (Ordinat(playerPos) == NBrs(map) + 1) {
    // eh temboknya ternyata pager
    if (PointEQ(playerPos, Gate2(map))) {
      /* pindah currentmap */
			if ((crrntMapID == 1) && (SearchEdge(jaringanMap, 1, 4) != Nil)) {
				crrntMapID = 4;
				map = WhichMap(crrntMapID);
				Ordinat(playerPos) = 1;
				Absis(playerPos) = Absis(Gate2(map));
			} else if ((crrntMapID == 2) && (SearchEdge(jaringanMap, 2, 3) != Nil)) {
				crrntMapID = 3;
				map = WhichMap(crrntMapID);
				Ordinat(playerPos) = 1;
				Absis(playerPos) = Absis(Gate2(map));
			}
    } else {
      /* mundur lagi, keluar dari tembok */
      Ordinat(playerPos)--;
    }
  } /* else if (wahana) { // If ada wahana, ga bisa dilewatin
      Ordinat(playerPos)--;
  } */
}

void MoveD () {
  /* KAMUS */
	MAP map;

  /* ALGORITMA */
	map = WhichMap(crrntMapID);

  // player ke arah utara
  Absis(playerPos)++;
  // jika player masuk tembok
  if (Absis(playerPos) == NKol(map) + 1) {
    // eh temboknya ternyata pager
    if (PointEQ(playerPos, Gate1(map))) {
      /* pindah currentmap */
			if ((crrntMapID == 2) && (SearchEdge(jaringanMap, 2, 1) != Nil)) {
				crrntMapID = 1;
				map = WhichMap(crrntMapID);
				Ordinat(playerPos) = Ordinat(Gate1(map));
				Absis(playerPos) = 1;
			} else if ((crrntMapID == 3) && (SearchEdge(jaringanMap, 3, 4) != Nil)) {
				crrntMapID = 4;
				map = WhichMap(crrntMapID);
				Ordinat(playerPos) = Ordinat(Gate1(map));
				Absis(playerPos) = 1;
			}
    } else {
      /* mundur lagi, keluar dari tembok */
      Absis(playerPos)--;
    }
  } /* else if (wahana) { // If ada wahana, ga bisa dilewatin
      Absis (playerPos)--;
  } */
}

void InitiateMap() {
    /* ../../data/mapX.txt */
    /* n = 19 */
    crrntMapID = 1;
    playerPos = MakePoint(3, 3);

    /* 
			Keterangan :
        MiddleOf(X + 2) - 1;
        + 2 untuk offset pagar.
        - 1 untuk offset karena indeks yang dipakai dari 0.
    */

    /* inisiasi map1 */
    
	FILE *f = fopen("data/map1.txt", "r");
	StartParser(f);
	map1 = ParserMap(1);

    // ID(map1) = 1;
    // MapSize(map1) = MakePoint(5, 5);
    // Absis(Gate1(map1)) = 0;
    // Ordinat(Gate1(map1)) = MiddleOf(NBrs(map1) + 2) - 1;
    // Absis(Gate2(map1)) = MiddleOf(NKol(map1) + 2) - 1 ;
    // Ordinat(Gate2(map1)) = NBrs(map1) + 1;
    // Absis(Office(map1)) = MiddleOf(NKol(map1) + 2) - 1;
    // Ordinat(Office(map1)) = MiddleOf(NBrs(map1) + 2) - 1;
    // Absis(Antrian(map1)) = MiddleOf(NKol(map1) + 2);
    // Ordinat(Antrian(map1)) = MiddleOf(NBrs(map1) + 2);

    /* inisiasi map2 */
    f = fopen("data/map2.txt", "r");
	StartParser(f);
    map2 = ParserMap(2);

    // ID(map2) = 2;
    // NBrs(map2) = 5;
    // NKol(map2) = 5;
    // Absis(Gate1(map2)) = NKol(map2) + 1;
    // Ordinat(Gate1(map2)) = MiddleOf(NBrs(map2) + 2) - 1;
    // Absis(Gate2(map2)) = MiddleOf(NKol(map2) + 2) - 1;
    // Ordinat(Gate2(map2)) = NBrs(map2) + 1;
    // Absis(Office(map2)) = MiddleOf(NKol(map2) + 2) - 1;
    // Ordinat(Office(map2)) = MiddleOf(NBrs(map2) + 2) - 1;
    // Absis(Antrian(map2)) = MiddleOf(NKol(map2) + 2);
    // Ordinat(Antrian(map2)) = MiddleOf(NBrs(map2)+ 2);

    /* inisiasi map3 */
    f = fopen("data/map3.txt", "r");
	StartParser(f);
    map3 = ParserMap(3);

    // ID(map3) = 3;
    // NBrs(map3) = 5;
    // NKol(map3) = 5;
    // Absis(Gate1(map3)) = NKol(map3) + 1;
    // Ordinat(Gate1(map3)) = MiddleOf(NBrs(map3) + 2) - 1;
    // Absis(Gate2(map3)) = MiddleOf(NKol(map3) + 2) -1;
    // Ordinat(Gate2(map3)) = 0;
    // Absis(Office(map3)) = MiddleOf(NKol(map3) + 2) - 1;
    // Ordinat(Office(map3)) = MiddleOf(NBrs(map3) + 2) - 1;
    // Absis(Antrian(map3)) = MiddleOf(NKol(map3) + 2);
    // Ordinat(Antrian(map3)) = MiddleOf(NBrs(map3) + 2);

    /* inisiasi map4 */
    f = fopen("data/map4.txt", "r");
	StartParser(f);
    map4 = ParserMap(4);

    // ID(map4) = 4;
    // NBrs(map4) = 5;
    // NKol(map4) = 5;
    // Absis(Gate1(map4)) = 0;
    // Ordinat(Gate1(map4)) = MiddleOf(NBrs(map4) + 2) - 1;
    // Absis(Gate2(map4)) = MiddleOf(NKol(map4) + 2) - 1;
    // Ordinat(Gate2(map4)) = 0;
    // Absis(Office(map4)) = MiddleOf(NKol(map4) + 2) - 1;
    // Ordinat(Office(map4)) = MiddleOf(NBrs(map4) + 2) - 1;
    // Absis(Antrian(map4)) = MiddleOf(NKol(map4) + 2);
    // Ordinat(Antrian(map4)) = MiddleOf(NBrs(map4) + 2);
    
    InitiateMapGraph();
}


boolean InteractOffice() {
	MAP map;

	map = WhichMap(crrntMapID);
	return PointEQ(playerPos, Office(map)) || 
					PointEQ(playerPos, NextX(Office(map))) || 
					PointEQ(playerPos, NextY(Office(map))) || 
					PointEQ(playerPos, BeforeX(Office(map))) ||
					PointEQ(playerPos, BeforeY(Office(map)));
}

boolean InteractWahana() {
	/* Not finished yet */
	// MAP map;

	// map = WhichMap(crrntMapID);
	/* how does the wahana disimpan? */
	return false;
}

array WahanaSekitarPosisi(Point position) {
	/* ATangibleWahana */
	array wahanaSekitarPlayer;

	/* Nyariin wahana sekitar pemain */
	for (int i = 0; i < BuiltWahana.NbEl; ++i) {
		ATangibleWahana wahanaDekatPlayer = ((ATangibleWahana) BuiltWahana.arr[i].metadata);
		Point bX = BeforeX(position), bY = BeforeY(position),
			  nX = NextX(position), nY = NextY(position);

		if (PointEQ(wahanaDekatPlayer->posisi, bX)
			|| PointEQ(wahanaDekatPlayer->posisi, bY)
			|| PointEQ(wahanaDekatPlayer->posisi, nX)
			|| PointEQ(wahanaDekatPlayer->posisi, nY)) {
			ArrayElType el;
			
			el.id = wahanaDekatPlayer->currentUpgradeID;
			el.info = wahanaDekatPlayer->currentUpgradeID;
			el.metadata = wahanaDekatPlayer;

			InsArrLast(&wahanaSekitarPlayer, el);
		}
	}

	return wahanaSekitarPlayer;
}
