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
//   LL Buildings;
//   Point Office;
//   Point Antrian;
// } MAP;

// #define ID(M) (M).MapID
// #define MapSize(M) (M).MapSize;
// #define NBrs(M) Ordinat(MapSize(M));
// #define NKol(M) Absis(MapSize(M));
// #define Gate1(M) (M).Gate1
// #define Gate2(M) (M).Gate2
// #define Buildings(M) (M).Buildings
// #define Office(M) (M).Office
// #define Antrian(M) (M).Antrian

boolean isNutupinGate (Point titiek) {
	MAP map;

	map = WhichMap(crrntMapID);

	return (PointEQ(titiek, NextX(Gate1(map))) || PointEQ(titiek, BeforeX(Gate1(map))) ||
	PointEQ(titiek, NextY(Gate2(map))) || PointEQ(titiek, BeforeY(Gate2(map))));
}

int MiddleOf(indeks N) {
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

	/* Render wahana yang sudah dibuat */
	for (int i = 0; i < BuiltWahana.NbEl; i++) {
		if (IDMap((ATangibleWahana) BuiltWahana.arr[i].metadata) == crrntMapID) {
			Elmt(peta, Ordinat(WahanaPoint((ATangibleWahana) BuiltWahana.arr[i].metadata)), Absis(WahanaPoint((ATangibleWahana) BuiltWahana.arr[i].metadata))) = 'W';
		}
	}

  Elmt(peta, Ordinat(playerPos), Absis(playerPos)) = 'P';
  TulisMATRIKS(peta); printf("\n");
}

void MoveW () {
  /* KAMUS */
	MAP map;

  /* ALGORITMA */
	map = WhichMap(crrntMapID);
  // player ke arah timur
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
  } else {
		for (int i = 0; i < BuiltWahana.NbEl; i++) {
			if (IDMap((ATangibleWahana) BuiltWahana.arr[i].metadata) == crrntMapID && 
			(PointEQ(playerPos, WahanaPoint((ATangibleWahana) BuiltWahana.arr[i].metadata)))) {
				Ordinat(playerPos)++;
				break;
			}
		}
  }
}

void MoveA () {
  /* KAMUS */
	MAP map;

  /* ALGORITMA */
	map = WhichMap(crrntMapID);
  // player ke arah barat
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
  } else {
		for (int i = 0; i < BuiltWahana.NbEl; i++) {
			if (IDMap((ATangibleWahana) BuiltWahana.arr[i].metadata) == crrntMapID && 
			(PointEQ(playerPos, WahanaPoint((ATangibleWahana) BuiltWahana.arr[i].metadata)))) {
				Absis(playerPos)++;
				break;
			}
		}
  }
}

void MoveS () {
  /* KAMUS */
	MAP map;

  /* ALGORITMA */
	map = WhichMap(crrntMapID);
  // player ke arah selatan
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
  } else {
		for (int i = 0; i < BuiltWahana.NbEl; i++) {
			if (IDMap((ATangibleWahana) BuiltWahana.arr[i].metadata) == crrntMapID && 
			(PointEQ(playerPos, WahanaPoint((ATangibleWahana) BuiltWahana.arr[i].metadata)))) {
				Ordinat(playerPos)--;
				break;
			}
		}
  }
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
  } else {
		for (int i = 0; i < BuiltWahana.NbEl; i++) {
			if (IDMap((ATangibleWahana) BuiltWahana.arr[i].metadata) == crrntMapID && 
			(PointEQ(playerPos, WahanaPoint((ATangibleWahana) BuiltWahana.arr[i].metadata)))) {
				Absis(playerPos)--;
				break;
			}
		}
  }
}

void InitiateMap() {
    crrntMapID = 1;
    playerPos = MakePoint(3, 3);

    InitiateMapGraph();
}

array WahanaSekitarPosisi(Point position) {
	/* ATangibleWahana */
	array wahanaSekitarPlayer;

	CreateArray(&wahanaSekitarPlayer, MAX_WAHANA);

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
